#include "reveivedialog.h"
#include "ui_reveivedialog.h"

ReveiveDialog::ReveiveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReveiveDialog)
{
    ui->setupUi(this);
    i=0;
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);
    initTcp();
    newListen();

}

ReveiveDialog::~ReveiveDialog()
{
    delete ui;
}


void ReveiveDialog::initTcp()
{
    fileServer=new QTcpServer(this);
    fileSocket=new QTcpSocket(this);

    connect(fileServer,SIGNAL(newConnection()),SLOT(fileConnection()));
    connect(fileSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数
}


void ReveiveDialog::initUdp()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, 1144);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
    file.setFileName(filename) ;
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Unbuffered))
        return;
    QDataStream out(&file);
    connect(&timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    ui->progressBar->reset();
    state=1;
    timer.stop();
    ui->progressBar->setMaximum(fileSize);
}

void ReveiveDialog::newListen()
{
    if(!fileServer->listen(QHostAddress::AnyIPv4,6665)){
        qDebug()<<fileServer->errorString();
        fileServer->close();
    }
}

void ReveiveDialog::fileConnection()
{
    fileSocket=fileServer->nextPendingConnection();
    connect(fileSocket,SIGNAL(readyRead()),SLOT(fileSlot()));
    sendIP=fileSocket->peerAddress().toString();
}

void ReveiveDialog::fileSlot()
{
    QString data=fileSocket->readAll();
    QStringList list=data.split("#");
    if(list[0]=="m"){
        filename=list[1];
        bool ok;
        fileSize=list[2].toInt(&ok,10);
        qDebug()<<"filesize"<<fileSize;
        QString bs="m";
        QString send=bs+"#true";
        fileSocket->write(send.toLatin1());
        QString word="来自"+fileSocket->peerAddress().toString()+"的文件"+filename+"开始接收";
        ui->textBrowser->append(word);
        initUdp();
    }
    else
        return;
}



void ReveiveDialog::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<fileSocket->errorString();   //输出出错信息
}

void ReveiveDialog::readPendingDatagrams()
{
    char pkt_buf[sizeof(struct Packet)];
    struct AckPacket ack;
    struct Packet *pkt=NULL;
    QDataStream out(&file);
    if(expected_seq_no==0){
        begintime.start();
        endtime.start();
    }
    while(udpSocket->hasPendingDatagrams())
    {

        udpSocket->readDatagram((char*)&pkt_buf,(qint64)sizeof(struct Packet));
        pkt = (struct Packet *) pkt_buf;

        if(pkt->seq == (unsigned int)expected_seq_no && pkt->checksum == packet_checksum(pkt)) {
            int data_size = pkt->len - 8;
            //file.write(pkt->data);
            int len=out.writeRawData(pkt->data,data_size);
            bytesReceived=file.size();
            expected_seq_no++;
        }
        /*send ACK*/
        ack.ack = expected_seq_no-1;
        ack.checksum = ack_packet_checksum(&ack);
        if(bytesReceived>=fileSize){
            if(begintime.msecsTo(endtime)==0)
            {
                endtime.start();
                QString v="接收完成，平均速率为"+QString::number(fileSize/(begintime.msecsTo(endtime)))+"KB/S";
                ui->textBrowser->append(v);
                timer.stop();
            }
            ack.len=0;
        }
        else{
            ack.len = 8;
            timer.stop();
            timer.start(10000);
        }
        udpSocket->writeDatagram((char *)&ack,sizeof(struct AckPacket),QHostAddress(sendIP),2244);
    }
    ui->progressBar->setValue(bytesReceived);
    ui->progressBar->setFormat("%p%");
}

void ReveiveDialog::handleTimeout()
{
    timer.stop();
    state=0;
}

void ReveiveDialog::closeEvent(QCloseEvent *)
{
    if(file.exists())
        file.close();
    timer.stop();
    delete udpSocket;
    this->close();
}

