#include "findpsddialog.h"
#include "ui_findpsddialog.h"

#define ip "192.168.1.3"
#define port 8000

FindpsdDialog::FindpsdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindpsdDialog)
{
    ui->setupUi(this);
    init();
    connectServer();
}

FindpsdDialog::~FindpsdDialog()
{
    delete ui;
}

void FindpsdDialog::init()
{
    fpsdSocket=new QTcpSocket(this);
    connect(fpsdSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数
}

void FindpsdDialog::connectServer()
{
    connect(fpsdSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));
}

void FindpsdDialog::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<fpsdSocket->errorString();   //输出出错信息
}

void FindpsdDialog::readMessages()
{
    QString data=fpsdSocket->readAll();
    QStringList list=data.split("#");
    if(list[0]=="d" && list[1]=="true")
        QMessageBox::information(this,"密码提示",list[2],QMessageBox::Ok);
    else if(list[0]=="d" && list[1]=="false")
        QMessageBox::information(this,"信息提示","找回密码失败,答案错误!",QMessageBox::Ok);
    else
        return;
}




void FindpsdDialog::on_OkPbt_clicked()
{
    fpsdSocket->abort();   //取消已有的连接
    fpsdSocket->connectToHost(ip,port);
    QString answer=ui->ansLineEdit->text();
    if(answer=="")
        QMessageBox::information(this,"警告","答案不能为空",QMessageBox::Ok);
    QString bs="d";
    QString data=bs+"#"+username+"#"+answer;
    fpsdSocket->write(data.toLatin1());
}

void FindpsdDialog::on_retPbt_clicked()
{
    this->close();
}

void FindpsdDialog::on_pushButton_clicked()
{
    ui->text_label->setText(question);
}
