#include "signin_dialog.h"
#include "ui_signin_dialog.h"

#define ip "192.168.1.3"
#define port 8000

signin_Dialog::signin_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signin_Dialog)
{
    ui->setupUi(this);
    init();
    connectServer();
}

signin_Dialog::~signin_Dialog()
{
    delete ui;
}

void signin_Dialog::init()
{
    signSocket=new QTcpSocket(this);
    connect(signSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数
}

void signin_Dialog::connectServer()
{
    connect(signSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));
}

void signin_Dialog::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<signSocket->errorString();   //输出出错信息
}

void signin_Dialog::readMessages()
{
    QString data=signSocket->readAll();
    QStringList list=data.split("#");
    if(list[0]=="a" && list[1]=="true"){
        QMessageBox::information(this,"信息提示","注册成功!",QMessageBox::Ok);
        ui->anslineEdit->clear();
        ui->psdlineEdit->clear();
        ui->queslineEdit->clear();
        ui->userlineEdit->clear();
        this->close();
    }

    else if(list[0]=="a" && list[1]=="false"){
        QMessageBox::information(this,"信息提示","注册失败,用户名已经被注册!",QMessageBox::Ok);
        ui->userlineEdit->clear();
        ui->psdlineEdit->clear();
    }
    else
        return;
}



void signin_Dialog::on_signinPbt_clicked()
{
    signSocket->abort();   //取消已有的连接
    signSocket->connectToHost(ip,port);
    QString username=ui->userlineEdit->text();
    QString passward=ui->psdlineEdit->text();
    QString question=ui->queslineEdit->text();
    QString answer=ui->anslineEdit->text();
    if(username=="" || passward==""||question==""||answer=="")
        QMessageBox::information(this,"警告","输入不能为空",QMessageBox::Ok);
    QString bs="a";
    QString data=bs+"#"+username+"#"+passward+"#"+question+"#"+answer;
    signSocket->write(data.toLatin1());
}


void signin_Dialog::on_backPbt_clicked()
{
    ui->anslineEdit->clear();
    ui->psdlineEdit->clear();
    ui->queslineEdit->clear();
    ui->userlineEdit->clear();
    this->close();
}
