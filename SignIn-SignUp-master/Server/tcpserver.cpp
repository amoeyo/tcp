#include "tcpserver.h"
#include "ui_tcpserver.h"


TcpServer::TcpServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    init();
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::init()
{
    this->tcpServer=new QTcpServer(this);
    this->tcpSocket=new QTcpSocket(this);

    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
                     this,SLOT(displayError(QAbstractSocket::SocketError)));
}


void TcpServer::receiveData()
{
    QString data=tcpSocket->readAll();
    QStringList list=data.split("#");
    bool ret=0;
    if(list[0]=="a")     //注册
        ret=checkSignIn(list[1],list[2],list[3],list[4]);
    else if(list[0]=="b")  //登录
        ret=checkSignUp(list[1],list[2]);
    else
        return;
    QString sendData=list[0];
    if(ret)
        sendData+="#true";
    else
        sendData+="#false";
    qDebug()<<sendData;
}

void TcpServer::on_startBtn_clicked()
{
    ui->startBtn->setEnabled(false);
    if(!tcpServer->listen(QHostAddress::Any,8000))
    {
        qDebug()<<tcpServer->errorString();
        close();
        return;
    }
}


void TcpServer::acceptConnection()
{
    tcpSocket=tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveData()));
}

void TcpServer::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();
    tcpSocket->close();
}

bool TcpServer::checkSignIn(QString username,QString passward,QString question,QString answer)
{
    QFile file(username);
    if(file.exists()){
        return false;
    }
    else{
        QString data=passward+"#"+question+"#"+answer;
        if(!file.open(QIODevice::ReadWrite)){
            qDebug()<<"文件创建失败";
            return false;
        }
        qint64 length = -1;
        length = file.write(data.toLatin1(),data.length());
        if(length==-1){
            qDebug()<<"文件写入失败";
            return false;
        }
        else{
            qDebug()<<"用户"<<username<<"注册";
            file.close();
            return true;
        }
    }
    return false;
}

bool TcpServer::checkSignUp(QString username, QString passward)
{
    QFile file(username);
    if(file.exists()){
        if(!file.open(QIODevice::ReadWrite)){
            qDebug()<<"用户文件打开失败";
        }
        else{
            qDebug()<<"用户文件打开成功";
            QString data;
            QTextStream in(&file);
            //读取一行数据
            data=in.readLine();
            QStringList list=data.split("#");
            if(list[0]==passward){
                qDebug()<<"用户"<<username<<"登陆";
                file.close();
                return true;
            }
        }
    }
    else{
        qDebug()<<"用户不存在";
    }
    file.close();
    return false;
}
