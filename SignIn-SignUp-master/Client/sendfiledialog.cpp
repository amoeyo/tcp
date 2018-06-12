#include "sendfiledialog.h"
#include "ui_sendfiledialog.h"
#include <algorithm>

using namespace std;

#define MAX_WINDOW_SIZE 512

#define ip "192.168.5.1"
#define port 8000

SendFileDialog::SendFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendFileDialog)
{
    i=0;
    ui->setupUi(this);
    bytesSend=0;
    sending_window_size=200;
    ui->fileLet->setEnabled(false);
    ui->choosePbt->setEnabled(false);
    ui->sendPbt->setEnabled(false);
    ui->progressBar->reset();
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);
    timepass=0;
    init();

}

SendFileDialog::~SendFileDialog()
{
    free(pkts);
    delete fusrSocket;
    delete udpSocket;
    delete ui;
}

void SendFileDialog::init()
{
    fusrSocket=new QTcpSocket(this);


    connect(fusrSocket,SIGNAL(readyRead()),this,SLOT(readServer()));
    connect(fusrSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数

}

void SendFileDialog::initUdp()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, 2244);
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void SendFileDialog::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<fusrSocket->errorString();   //输出出错信息
}


void SendFileDialog::handleTimeout()
{
    if(sending_window_size == 1)
        timeout_counter++;
    if(timeout_counter>=3) {
        state=0;
        timeout_counter=0;
        //close();
    }
    else
        handle_loss_event();
}

void SendFileDialog::readServer()
{
    QString data=fusrSocket->readAll();
    QStringList list=data.split("#");
    if(list[0]=="f" && list[1]=="true"){
        recieverIP=list[2];
        qDebug()<<"连接到"<<recieverIP;
        ui->linkPbt->setText("已连接");
        ui->linkPbt->setEnabled(false);
        fusrSocket->abort();
        fusrSocket->connectToHost(recieverIP,1111);
        QString bs="p";
        QString send=bs+"#true";
        fusrSocket->write(send.toLatin1());
    }
    else if(list[0]=="f"&&list[1]=="false"){
        QMessageBox::information(this,"信息提示","失败,用户不存在或不在线！",QMessageBox::Ok);
    }
    else if(list[0]=="h"&&list[1]=="true"){
        ui->choosePbt->setEnabled(true);
    }
    else if(list[0]=="m"&&list[1]=="true"){
        qDebug()<<"开始文件传输";
        ui->progressBar->setMaximum(fileSize);
        initUdp();
        startSend();
        //传输数据
    }
    else
        return;
}


void SendFileDialog::readPendingDatagrams()
{   
    char ack_buf[8];

    while(udpSocket->hasPendingDatagrams()){
        int n = udpSocket->readDatagram((char*)&ack_buf,(qint64)sizeof(struct AckPacket));
        if (n < 0){
            return ;
        }

        struct AckPacket* ack = (struct AckPacket *) ack_buf;
        if(ack->len == 8 && ack->checksum == ack_packet_checksum(ack)){
            if(ack->ack < (unsigned int)base) {//ack->ack==base

                if(ack->ack != (unsigned int)last_resent) { //if duplicate ack was sent but for a newly lost pkt
                    duplicate_ack_num ++;
                }
                if(duplicate_ack_num >= 3) {
                    last_resent = ack->ack;
                    handle_loss_event();
                }
            }
            else {
                sending_window_size = min(MAX_WINDOW_SIZE, sending_window_size*2);
                if(resend_base != 0 && resend_base < next_seq_no) {
                    int indx = sending_window_size - (resend_base - (base+1));
                    indx = min(resend_base+indx, next_seq_no);
                    for(int i=resend_base; i<indx; i++) {
                        sendData(i);
                    }
                    resend_base = indx;
                }
            }
            timeout_counter=0;
            base = ack->ack + 1;

            time.start();
        }
        else if(ack->len==0&&state==1)//发送完毕
        {
            state=0;
            QTime end;
            end.start();
            QString out="发送完成，平均速率为"+QString::number(fileSize/(alltime.msecsTo(end)))+"KB/S";
            qDebug()<<out;
        }
    }
    return;
}

void SendFileDialog::handle_loss_event()
{
    sending_window_size = sending_window_size/2;
    if(sending_window_size == 0)
        sending_window_size = 1;
    duplicate_ack_num = 0;
    resend_base = min(base + sending_window_size, next_seq_no);//重发
    for(int i=base; i<resend_base; i++) {
        sendData(i);
    }
    time.start();
}

void SendFileDialog::sendData(int i)
{
    int index = i%MAX_WINDOW_SIZE;

    udpSocket->writeDatagram((char *)&pkts[index],sizeof(struct Packet),QHostAddress(recieverIP),1144);
    while (udpSocket->waitForBytesWritten()) {
    }
}

void SendFileDialog::on_linkPbt_clicked()
{
    fusrSocket->abort();
    fusrSocket->connectToHost(ip,port);//连接到服务器获取对方用户ip地址
    QString reciever=ui->usrLet->text();
    QString bs="f";
    if(reciever=="")
        QMessageBox::information(this,"信息提示","请输入用户名！",QMessageBox::Ok);
    if(reciever==sender){
        QMessageBox::information(this,"警告","发送方用户名",QMessageBox::Ok);
        return;
    }
    QString senddata=bs+"#"+reciever;
    fusrSocket->write(senddata.toLatin1());
}

void SendFileDialog::on_backPbt_clicked()
{
    fusrSocket->disconnectFromHost();
    udpSocket->disconnectFromHost();
    file.close();
    ui->linkPbt->setText("连接");
    ui->linkPbt->setEnabled(true);
    ui->usrLet->clear();
    ui->fileLet->clear();
    this->close();
}

void SendFileDialog::on_choosePbt_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"open","../");
    if(!filePath.isEmpty()){    //路径有效
            fileName.clear();
            fileSize = 0;
            //获取文件信息：名字、大小
            QFileInfo info(filePath);
            fileName = info.fileName();
            fileSize = info.size();
            sendSize = 0;   //已经发送文件大小

            //以只读方式打开文件
            file.setFileName(filePath);
            if(file.open(QIODevice::ReadOnly)==false){
                qDebug()<<"只读方式打开文件失败";
            }
            //提示已经打开的文件路径
            ui->fileLet->setText(filePath);

            //可以发送
            ui->choosePbt->setEnabled(false);  //只能选择一次
            ui->sendPbt->setEnabled(true);
        }
        else{
            QMessageBox::information(this,"警告","文件路径无效",QMessageBox::Ok);
        }

}



void SendFileDialog::on_sendPbt_clicked()
{
    ui->sendPbt->setEnabled(false);
    fusrSocket->abort();
    fusrSocket->connectToHost(recieverIP,6665);
    QString bs="m";
    QString num=QString::number(fileSize,10);
    QString senddata=bs+"#"+fileName+"#"+num;
    fusrSocket->write(senddata.toLatin1());

}

void SendFileDialog::startSend()
{
    int  data_size = 504;
    char buff[data_size];
    state=1;
    struct Packet pkt;//文件打包
    QDataStream in(&file);
    QTime curtime;
    memset(buff,0,data_size);
    //int length = file.readLine(buff,sizeof(buff));
    int length=in.readRawData(buff,data_size);
    qDebug()<<"start send "<<"read file "<<fileSize;
    char buff_next[data_size];
    memset(buff_next,0,data_size);
    //int length_next = file.readLine(buff_next,sizeof(buff_next));
    int length_next=in.readRawData(buff_next,data_size);
    pkts = (struct Packet *)malloc(MAX_WINDOW_SIZE*sizeof(struct Packet));
    time.start();//发送方开始计时
    alltime.start();
    while(length > 0&&state==1){
       QCoreApplication::processEvents();
       //if(udpSocket->hasPendingDatagrams())
         //  readPendingDatagrams();
       curtime.start();
       timepass=time.msecsTo(curtime);
       if(timepass>=10000){
           handleTimeout();
           continue;
       }
       if((resend_base == next_seq_no) && next_seq_no < base+sending_window_size) {//发送窗口内所有序号数据
           pkt.len = length + 8;//?
           pkt.seq = next_seq_no;
           memcpy(pkt.data, buff, data_size);
           pkt.checksum = packet_checksum(&pkt);
           pkts[next_seq_no%MAX_WINDOW_SIZE] = pkt;
           sendSize += length;
           sendData(next_seq_no);
           bytesSend+=length;
           ui->progressBar->setValue(bytesSend);
           ui->progressBar->setFormat("%p%");
           if(next_seq_no == base)
           {
               timeout_counter=0;
               time.start();
           }
           next_seq_no++;
           resend_base++;
           memset(buff,0,data_size);
           memcpy(buff, buff_next, length_next);
           length = length_next;
           memset(buff_next,0,data_size);
           //length_next = file.readLine(buff_next,sizeof(buff_next));
           length_next=in.readRawData(buff_next,data_size);
           //remaining_chunks = length_next;
       }
    }
    return ;
}




