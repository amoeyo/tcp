#include "sendfiledialog.h"
#include "ui_sendfiledialog.h"

#define ip "192.168.1.3"
#define port 8000

SendFileDialog::SendFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendFileDialog)
{
    ui->setupUi(this);
    isconnect=false;
    ui->fileLet->setEnabled(false);
    init();
}

SendFileDialog::~SendFileDialog()
{
    delete ui;
}

void SendFileDialog::init()
{
    fusrSocket=new QTcpSocket(this);

    connect(fusrSocket,SIGNAL(readyRead()),this,SLOT(readServer()));
    connect(fusrSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数
}

void SendFileDialog::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<fusrSocket->errorString();   //输出出错信息
}

void SendFileDialog::readServer()
{
    QString data=fusrSocket->readAll();
    QStringList list=data.split("#");
    if(list[0]=="f" && list[1]=="true"){
        recieverIP=list[2];
        ui->linkPbt->setText("已连接");
        ui->linkPbt->setEnabled(false);
        fusrSocket->abort();
        fusrSocket->connectToHost(recieverIP,6665);
        QString bs="p";
        QString send=bs+"#true";
        fusrSocket->write(send.toLatin1());
    }
    else if(list[0]=="f"&&list[1]=="false"){
        QMessageBox::information(this,"信息提示","失败,用户不存在或不在线！",QMessageBox::Ok);
    }
    else if(list[0]=="h"&&list[1]=="true"){
        ui->fileLet->setEnabled(true);
    }
    else
        return;

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
    ui->linkPbt->setText("连接");
    ui->linkPbt->setEnabled(true);
    this->close();
}
