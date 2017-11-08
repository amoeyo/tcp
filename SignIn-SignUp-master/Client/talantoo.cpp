#include "talantoo.h"
#include "ui_talantoo.h"

#define ip "192.168.1.3"
#define port 8000

TalantOO::TalantOO(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TalantOO)
{
    isserver=true;
    isconnect=off;
    pbt=true;
    ui->setupUi(this);
    init();
    newListen();

}

TalantOO::~TalantOO()
{
    delete ui;
}

void TalantOO::init()
{
    fusrSocket=new QTcpSocket(this);
    tcpSocket_1=new QTcpSocket(this);
    tcpSocket_2=new QTcpSocket(this);
    chatServer=new QTcpServer(this);

    connect(chatServer,SIGNAL(newConnection()),SLOT(acceptConnection()));
    connect(fusrSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));
    connect(fusrSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数
    connect(tcpSocket_1,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数
    connect(tcpSocket_2,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数
    connect(tcpSocket_2,SIGNAL(readyRead()),this,SLOT(reciveMessages()));

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
        ui->textBrowser->append("取得对方用户ip地址，连接建立");
        chatip=list[2];
        isconnect=toclient;
        isserver=false;
    }
    else if(list[0]=="f" && list[1]=="false"){
        if(list[2]=="false")
            QMessageBox::information(this,"信息提示","失败,用户不存在！",QMessageBox::Ok);
        else{
            ui->textBrowser->append("用户不在线，可发送离线消息。");
            isconnect=toserver;
        }
    }
    else if(list[0]=="g" && list[1]=="true"){
        ui->textBrowser->append(list[2]);
    }
    else if(list[0]=="g" && list[1]=="false"){
        ui->textBrowser->append("离线消息已发送或为空");
    }
    else if(list[0]=="z"&&list[1]=="true"){
        this->close();
    }
    else
        return;
}

void TalantOO::onReciveData()
{
    QString data=tcpSocket_1->readAll();
    qDebug()<<"server receive";
    mChat = data;
    ui->textBrowser->setText(mChat);
}

void TalantOO::reciveMessages()
{
    QString data=tcpSocket_2->readAll();
    qDebug()<<"client receive";
    mChat = data;
    ui->textBrowser->setText(mChat);
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
    isconnect=toclient;
    connect(tcpSocket_1,SIGNAL(readyRead()),SLOT(onReciveData()));
    if(pbt){
        QMessageBox::information(this,"信息提示","新消息",QMessageBox::Ok);
        pbt=false;
        ui->connectPbt->setText("取消连接");
    }
    qDebug()<<"listen"<<chatip;
}

void TalantOO::on_connectPbt_clicked()
{
    if(pbt){
        fusrSocket->abort();
        fusrSocket->connectToHost(ip,port);//连接到服务器获取对方用户ip地址
        ui->textBrowser->setText("连接到服务器");
        QString user=ui->usrLet->text();
        if(user=="")
            QMessageBox::information(this,"信息提示","请输入用户名！",QMessageBox::Ok);
        if(user==username){
            QMessageBox::information(this,"警告","请不要自问自答！",QMessageBox::Ok);
            return;
        }
        QString bs="f";
        QString data=bs+"#"+user;
        chatname=user;
        if(fusrSocket->write(data.toLatin1())==-1){
            qDebug()<<"unconnected";
        }
        pbt=false;
        ui->connectPbt->setText("取消连接");
    }
    else{//取消连接
        tcpSocket_1->disconnectFromHost();
        tcpSocket_2->disconnectFromHost();
        fusrSocket->disconnectFromHost();
        ui->connectPbt->setText("连接");
        isconnect=off;
        pbt=true;
    }
}

void TalantOO::on_sendmessPbt_clicked()
{
    if(pbt){
        QMessageBox::information(this,"信息提示","请先建立连接！",QMessageBox::Ok);
        return;
    }
    if(isconnect==toclient){
        if(!isserver){
            tcpSocket_2->abort();
            tcpSocket_2->connectToHost(chatip,6666);
            qDebug()<<"Client asks connection";
        }
        QString textEdit = ui->sendmessLet->text();
        QString strData = QTime::currentTime().toString() + "\n" + textEdit.toLocal8Bit() + "\n";
        mChat = mChat + username + " " +strData;
        ui->textBrowser->setText(mChat);
        if(isserver){
            tcpSocket_1->write(mChat.toLatin1());
            qDebug()<<"server send to"<<chatip;
        }
        else{
            tcpSocket_2->write(mChat.toLatin1());
            qDebug()<<"client send to"<<chatip;
        }
    }
    else if(isconnect==toserver){
        QString textEdit = ui->sendmessLet->text();
        QString strData = QTime::currentTime().toString() + "\n" + textEdit.toLocal8Bit() + "\n";
        mChat = mChat + username + " " +strData;
        ui->textBrowser->setText(mChat);
        QString bs="o";
        QString offlineEdit=bs+"#"+chatname+"#"+mChat;
        fusrSocket->write(offlineEdit.toLatin1());
        qDebug()<<"client send to server";
    }
    else
        return;
}


void TalantOO::on_exitPbt_clicked()
{
    fusrSocket->abort();
    fusrSocket->connectToHost(ip,port);
    QString bs="z";
    QString data=bs+"#"+username;
    fusrSocket->write(data.toLatin1());
}

void TalantOO::on_offlinePbt_clicked()
{
    fusrSocket->abort();
    fusrSocket->connectToHost(ip,port);
    QString bs="g";
    QString data=bs+"#"+username;
    fusrSocket->write(data.toLatin1());
}
