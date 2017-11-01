#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtNetwork>
#include <QTimer>
#include <QDebug>

namespace Ui {
class TcpServer;
}

class TcpServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = 0);
    ~TcpServer();

    bool checkSignIn(QString username,QString passward,QString question,QString answer);
    bool checkSignUp(QString username,QString passward);

protected:
    void init();                         // 初始化函数用于完成一些诸如信号与槽之间的联系和变量初始化工作

private slots:
    void on_startBtn_clicked();

    void acceptConnection();

    void receiveData();

    void displayError(QAbstractSocket::SocketError);

private:
    Ui::TcpServer *ui;
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    QTimer *timer;
};

#endif // TCPSERVER_H
