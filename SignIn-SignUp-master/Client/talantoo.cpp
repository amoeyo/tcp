#include "talantoo.h"
#include "ui_talantoo.h"

#define ip "192.168.1.3"
#define port 8000

TalantOO::TalantOO(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TalantOO)
{
    ui->setupUi(this);
    init();
}

TalantOO::~TalantOO()
{
    delete ui;
}

void TalantOO::init()
{
    fusrSocket=new QTcpSocket(this);
    tcpSocket_1=new QTcpSocket(this);
    chatServer=new QTcpServer(this);

    newListen();
    connect(chatServer,SIGNAL(newConnection()),SLOT(acceptConnection()));
    connect(fusrSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));
    connect(fusrSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数
    connect(tcpSocket_1,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数
    connect(tcpSocket_1,SIGNAL(readyRead()),this,SLOT(onReciveData()));
}




void TalantOO::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<fusrSocket->errorString();   //输出出错信息
}


void TalantOO::readMessages()
{
    QString data=fusrSocket->readAll();
    QStringList list=data.split("#");
    if(list[0]=="f" && list[1]=="true"){
        QMessageBox::information(this,"信息提示","找到用户!",QMessageBox::Ok);
        chatip=list[2];
    }
    else if(list[0]=="f" && list[1]=="false")
        QMessageBox::information(this,"信息提示","失败,用户不存在！",QMessageBox::Ok);
    else
        return;
}

void TalantOO::onReciveData()
{
    QString data=tcpSocket_1->readAll();
    ui->textBrowser->setText(data);

}


void TalantOO::newListen()
{
    if(!chatServer->listen(QHostAddress::AnyIPv4,6666)){
        qDebug()<<chatServer->errorString();
        chatServer->close();
    }
}

void TalantOO::acceptConnection()
{
    tcpSocket_1 = chatServer->nextPendingConnection();
    chatip=tcpSocket_1->peerAddress().toString();
    qDebug()<<chatip;
    connect(tcpSocket_1,SIGNAL(readyRead()),SLOT(onReciveData()));
}

void TalantOO::on_connectPbt_clicked()
{
    fusrSocket->abort();
    fusrSocket->connectToHost(ip,port);//连接到服务器获取对方用户ip地址
    ui->textBrowser->setText("连接到服务器");
    QString user=ui->usrLet->text();
    if(user=="")
        QMessageBox::information(this,"信息提示","请输入用户名！",QMessageBox::Ok);
    if(user==username)
        QMessageBox::information(this,"警告","请不要自问自答！",QMessageBox::Ok);
    QString bs="f";
    QString data=bs+"#"+user;
    chatname=user;
    if(fusrSocket->write(data.toLatin1())==-1){
        qDebug()<<"unconnected";
    }
}

void TalantOO::on_sendmessPbt_clicked()
{
    tcpSocket_1->abort();
    tcpSocket_1->connectToHost(chatip,6666);
    qDebug()<<chatip;
    ui->textBrowser->setText("连接到目标用户");
    QString textEdit = ui->sendmessLet->text();
    QString strData =QString::fromLocal8Bit("Time: ") + QTime::currentTime().toString() + "\n" + textEdit.toLocal8Bit() + "\n";
    strData += username;
    ui->textBrowser->setText(strData);
    tcpSocket_1->write(strData.toLatin1());
}
