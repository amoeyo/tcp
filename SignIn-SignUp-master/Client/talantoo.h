#ifndef TALANTOO_H
#define TALANTOO_H

#include <QMainWindow>
#include <QtNetwork>
#include <QMessageBox>
#include <QDebug>
#include <sendfiledialog.h>
#include <reveivedialog.h>

namespace Ui {
class TalantOO;
}

class TalantOO : public QDialog
{
    Q_OBJECT

public:
    explicit TalantOO(QWidget *parent = 0);
    ~TalantOO();

    QString username;
    QString chatname;

protected:
    void init();
    void newListen();
    void connectServer();
    void closeEvent(QCloseEvent *);



private slots:
    void displayError(QAbstractSocket::SocketError);

    void acceptConnection(); //接收客户端连接

    void fileConnection();

    void fileSlot();

    void readMessages();

    void onReciveData();  //接收数据

    void reciveMessages();

    void on_connectPbt_clicked();

    void on_sendmessPbt_clicked();




    void on_exitPbt_clicked();

    void on_offlinePbt_clicked();

    void on_sendfilePbt_clicked();

private:
    Ui::TalantOO *ui;
    QTcpSocket *fusrSocket;
    QTcpServer *chatServer;
    QTcpServer *fileServer;
    QTcpSocket *fileSocket;
    QTcpSocket *tcpSocket_1;
    QTcpSocket *tcpSocket_2;
    bool isserver;
    bool pbt;
    int isconnect;
    QString userip;
    QString chatip;
    QString mChat;
    enum STATE{off,toclient,toserver};
    SendFileDialog *sendfile_dlg=new SendFileDialog;
    ReveiveDialog *receive_dlg=new ReveiveDialog;

};

#endif // TALANTOO_H
