#include "tcpclient.h"
#include "ui_tcpclient.h"

#define ip "192.168.5.1"
#define port 8000

TcpClient::TcpClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    ui->passwardLineEdit->setEchoMode(QLineEdit::Password);  //密码方式显示文本
    init();
    connectServer();
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::init()
{
    tcpSocket=new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数
}

void TcpClient::connectServer()
{
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));
}

void TcpClient::on_sendBtn_clicked()//登陆
{
    tcpSocket->abort();   //取消已有的连接
    tcpSocket->connectToHost(ip,port);
    QString username=ui->userLineEdit->text();
    QString passward=ui->passwardLineEdit->text();
    if(username=="" || passward=="")
        QMessageBox::information(this,"警告","输入不能为空",QMessageBox::Ok);
    QString bs="b";
    QString data=bs+"#"+username+"#"+passward;
    if(tcpSocket->write(data.toLatin1())==-1){
        qDebug()<<"unconnected";
    }
}


void TcpClient::on_signBtn_clicked()
{
    this->hide();
    signin_dlg->show();
    signin_dlg->exec();
    this->show();
}


void TcpClient::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();   //输出出错信息
}


void TcpClient::readMessages()
{
    QString data=tcpSocket->readAll();
    QStringList list=data.split("#");
    if(list[0]=="b" && list[1]=="true"){
        QMessageBox::information(this,"信息提示","登录成功!",QMessageBox::Ok);
        client_dlg->username=list[2];
        client_dlg->show();
        this->close();
    }
    else if(list[0]=="b" && list[1]=="false"){
        QMessageBox::information(this,"信息提示","登录失败!信息错误或用户已登录！",QMessageBox::Ok);
        ui->passwardLineEdit->clear();
    }

    else if(list[0]=="c" && list[1]=="true"){
        findpsd_dlg->username=list[2];//username+question
        findpsd_dlg->question=list[3];
        this->hide();
        findpsd_dlg->show();
        findpsd_dlg->exec();
        this->show();
    }
    else if(list[0]=="d" && list[1]=="true"){
        QMessageBox::information(this,"信息提示",list[2],QMessageBox::Ok);
    }
    else
        return;
}



void TcpClient::on_fpsdPbt_clicked()
{
    tcpSocket->abort();   //取消已有的连接
    tcpSocket->connectToHost(ip,port);
    QString user=ui->userLineEdit->text();
    if(user=="")
        QMessageBox::information(this,"警告","请输入用户名",QMessageBox::Ok);
    QString bs="c";
    QString data=bs+"#"+user;
    if(tcpSocket->write(data.toLatin1())==-1){
        qDebug()<<"unconnected";
    }
}
