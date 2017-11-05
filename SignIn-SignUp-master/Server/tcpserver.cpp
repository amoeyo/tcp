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
    else if(list[0]=="b"){//登陆
        ret=checkSignUp(list[1],list[2]);
        recordSignUp(list[1]);
    }
    else if(list[0]=="c") //找回密码
        ret=checkQuestion(list[1]);
    else if(list[0]=="d") //检查答案
        ret=checkAnswer(list[1],list[2]);
    else if(list[0]=="f")//查找ip
        ret=findIpAddr(list[1]);
    else
        return;
    QString sendData=list[0];
    if(ret){
        sendData+="#true";
        if(list[0]=="b")
            sendData=sendData+"#"+list[1];
        if(list[0]=="c")
            sendData=sendData+"#"+list[1]+"#"+question;
        if(list[0]=="d")
            sendData=sendData+"#"+pass;
        if(list[0]=="f")
            sendData=sendData+"#"+ipaddr;
    }
    else
        sendData+="#false";
    tcpSocket->write(sendData.toLatin1());
}

void TcpServer::on_startBtn_clicked()
{
    ui->startBtn->setEnabled(false);
    if(!tcpServer->listen(QHostAddress::AnyIPv4,8000))
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
    qDebug()<<"用户"<<username<<"请求注册";
    QString filename=username+"info";
    QFile file(filename);
    bool ret;
    if(file.exists()){
        qDebug()<<"用户已存在";
        ret=false;
    }
    else{
        QString data=passward+"#"+question+"#"+answer;
        if(!file.open(QIODevice::ReadWrite)){
            qDebug()<<"用户文件创建失败";
            ret=false;
        }
        qint64 length = -1;
        length = file.write(data.toLatin1(),data.length());
        if(length==-1){
            qDebug()<<"用户文件写入失败";
            ret=false;
        }
        else{
            qDebug()<<"用户"<<username<<"注册成功";
            file.close();
            ret=true;
        }
    }
    return ret;
}

bool TcpServer::checkSignUp(QString username, QString passward)
{
    qDebug()<<"用户"<<username<<"请求登陆";
    QString filename;
    filename=username+"info";
    bool ret;
    QFile file(filename);
    if(file.exists()){
        if(!file.open(QIODevice::ReadWrite)){
            qDebug()<<"用户文件打开失败";
            ret=false;
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
                ret=true;
            }
        }
    }
    else{
        qDebug()<<"用户不存在";
        ret=false;
    }
    file.close();
    return ret;
}

bool TcpServer::checkQuestion(QString username)
{
    qDebug()<<"用户"<<username<<"请求找回密码";
    QString filename;
    filename=username+"info";
    bool ret;
    QFile file(filename);
    if(file.exists()){
        if(!file.open(QIODevice::ReadWrite)){
            qDebug()<<"用户文件打开失败";
            ret=false;
        }
        else{
            qDebug()<<"用户文件打开成功";
            QString data;
            QTextStream in(&file);
            //读取一行数据
            data=in.readLine();
            QStringList list=data.split("#");
            question=list[1];
            ret=true;
        }
    }
    else{
        qDebug()<<"用户不存在";
        ret=false;
    }
    file.close();
    return ret;
}

bool TcpServer::checkAnswer(QString username,QString answer)
{
    qDebug()<<"用户"<<username<<"发送密保答案";
    QString filename;
    filename=username+"info";
    bool ret;
    QFile file(filename);
    if(file.exists()){
        if(!file.open(QIODevice::ReadWrite)){
            qDebug()<<"用户文件打开失败";
            ret=false;
        }
        else{
            qDebug()<<"用户文件打开成功";
            QString data;
            QTextStream in(&file);
            //读取一行数据
            data=in.readLine();
            QStringList list=data.split("#");
            if(list[2]==answer){
                qDebug()<<"用户"<<username<<"密保问题正确";
                pass=list[0];
                ret=true;
            }

        }
    }
    else{
        qDebug()<<"用户不存在";
        ret=false;
    }
    file.close();
    return ret;
}

void TcpServer::recordSignUp(QString username)
{
    qDebug()<<"用户"<<username<<"登陆信息创建";
    QString filename=username+"record";
    QFile file(filename);
    if(file.exists()){
        qDebug()<<"文件已存在";
    }
    else{
        QString data=tcpSocket->peerAddress().toString();
        if(!file.open(QIODevice::ReadWrite)){
            qDebug()<<"用户登陆文件创建失败";
        }
        qint64 length = -1;
        length = file.write(data.toLatin1(),data.length());
        if(length==-1){
            qDebug()<<"用户登陆文件写入失败";
        }
        else{
            qDebug()<<"用户"<<username<<"登陆文件写入成功";
            file.close();
        }
    }
}

bool TcpServer::findIpAddr(QString username)
{
    qDebug()<<"请求用户"<<username<<"IP地址";
    QString filename;
    filename=username+"record";
    bool ret;
    QFile file(filename);
    if(file.exists()){
        if(!file.open(QIODevice::ReadWrite)){
            qDebug()<<"用户登陆文件打开失败";
            ret=false;
        }
        else{
            qDebug()<<"用户登陆文件打开成功";
            QString data;
            QTextStream in(&file);
            //读取一行数据
            ipaddr=in.readLine();
            ret=true;
        }
    }
    else{
        qDebug()<<"用户不存在";
        ret=false;
    }
    file.close();
    return ret;
}
