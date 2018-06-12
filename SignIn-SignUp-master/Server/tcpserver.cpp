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
        if(ret)
            recordSignUp(list[1]);
    }
    else if(list[0]=="c") //找回密码
        ret=checkQuestion(list[1]);
    else if(list[0]=="d") //检查答案
        ret=checkAnswer(list[1],list[2]);
    else if(list[0]=="f")//查找ip
        ret=findIpAddr(list[1]);
    else if(list[0]=="o")
        ret=recordOfflineMessages(list[1],list[2]);
    else if(list[0]=="z"){
        ret=deleteFile(list[1]);
    }
    else if(list[0]=="g"){
        ret=findOfflineMessages(list[1]);
    }
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
        if(list[0]=="g")
            sendData=sendData+"#"+offline;
    }
    else{
        sendData+="#false";
        if(list[0]=="f"){
            ret=findUser(list[1]);
            if(ret)
                sendData += "#true";
            else
                sendData += "#false";
        }
    }

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
        QString datas=passward+"#"+question+"#"+answer;
        QString data;
        Encryption(key,datas,data);//加密
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
    QString filename_1;
    filename=username+"info";
    filename_1=username+"signup";
    bool ret;
    QFile file(filename);
    QFile file_1(filename_1);
    if(file_1.exists()){
        qDebug()<<"用户已登录";
        ret=false;
    }
    else if(file.exists()){
        if(!file.open(QIODevice::ReadWrite)){
            qDebug()<<"用户文件打开失败";
            ret=false;
        }
        else{
            qDebug()<<"用户文件打开成功";
            QString datas;
            QString data;
            QTextStream in(&file);
            //读取一行数据
            datas=in.readLine();
            Decryption(key,datas,data);
            qDebug()<<data;
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
            QString datas;
            QString data;
            QTextStream in(&file);
            //读取一行数据
            datas=in.readLine();
            Decryption(key,datas,data);
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
            QString datas;
            QString data;
            QTextStream in(&file);
            //读取一行数据

            datas=in.readLine();
            Decryption(key,datas,data);
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
    QString filename=username+"signup";
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
    filename=username+"signup";
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
        qDebug()<<"用户登陆信息不存在";
        ret=false;
    }
    file.close();
    return ret;
}

bool TcpServer::recordOfflineMessages(QString username,QString data)
{
    qDebug()<<"用户"<<username<<"离线消息文件创建";
    QString datas;
    QString filename=username+"record";
    QFile file(filename);
    bool ret;
    if(!file.open(QIODevice::ReadWrite |QIODevice::Text)){
        qDebug()<<"用户离线消息文件创建失败";
        ret=false;
    }
    qint64 length = -1;
    length = file.write(data.toLatin1(),data.length());
    if(length==-1){
        qDebug()<<"文件写入失败";
        ret=false;
    }
    else{
        qDebug()<<"用户"<<username<<"离线消息写入成功";
        ret=true;
        file.close();
    }
    return ret;
}

bool TcpServer::deleteFile(QString username)
{
    qDebug()<<"用户"<<username<<"退出";
    QString filename=username+"signup";
    QFile file(filename);
    if(file.exists())
        file.remove();
    qDebug()<<"删除用户文件";
    return true;
}

bool TcpServer::findUser(QString username)
{
    qDebug()<<"查找用户"<<username<<"是否存在";
    QString filename;
    filename=username+"info";
    bool ret;
    QFile file(filename);
    if(file.exists()){
        ret=true;
    }
    else{
        qDebug()<<"用户信息不存在";
        ret=false;
    }
    file.close();
    return ret;
}

bool TcpServer::findOfflineMessages(QString username)
{
    qDebug()<<"用户"<<username<<"发送离线信息";
    QString filename;
    filename=username+"record";
    bool ret;
    QFile file(filename);
    if(file.exists()){
        if(!file.open(QIODevice::ReadWrite)){
            qDebug()<<"离线消息打开失败";
            ret=false;
        }
        else{
            qDebug()<<"离线消息打开成功";
            QString data=file.readAll();
            offline=data;
            ret=true;
        }
    }
    else{
        qDebug()<<"用户不存在";
        ret=false;
    }
    file.remove();
    return ret;
}

void  TcpServer::Encryption(int a, const QString strs, QString &results)
{
    char* str;
    char result[50];
    /* QString转char* */
    QByteArray ba=strs.toLatin1();
    str=ba.data();
    int i;
    for(i = 0; str[i] != '\0'; i ++){
        result[i] = str[i]+(a+i);
    }
    result[i] = '\0';
    /* char*转QString */
    results=QString(QLatin1String(result));
}

void TcpServer::Decryption(int a, const QString strs, QString &results)
{
    char* str;
    char result[50];
    QByteArray ba=strs.toLatin1();
    str=ba.data();
    int i;
    for(i = 0; str[i] != '\0'; i ++){
        result[i] = str[i]-(a+i);
    }
    result[i] = '\0';
    results=QString(QLatin1String(result));
}
