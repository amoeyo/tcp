#ifndef TALANTOO_H
#define TALANTOO_H

#include <QMainWindow>
#include <QtNetwork>
#include <QMessageBox>
#include <QDebug>

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




private slots:
    void displayError(QAbstractSocket::SocketError);

    void acceptConnection(); //接收客户端连接

    void readMessages();

    void onReciveData();  //接收数据

    void on_connectPbt_clicked();

    void on_sendmessPbt_clicked();

private:
    Ui::TalantOO *ui;
    QTcpSocket *fusrSocket;
    QTcpServer *chatServer;
    QTcpSocket *tcpSocket_1;
    bool isserver;
    QString userip;
    QString chatip;

};

#endif // TALANTOO_H
