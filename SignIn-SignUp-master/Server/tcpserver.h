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
    void recordSignUp(QString username);
    bool checkQuestion(QString username);
    bool checkAnswer(QString username,QString answer);
    bool findIpAddr(QString username);
    bool recordOfflineMessages(QString username,QString mchat);
    bool findUser(QString username);
    bool deleteFile(QString username);
    bool findOfflineMessages(QString username);

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
    QString question;
    QString pass;
    QString ipaddr;
    QString offline;
    int key=2;
    void Encryption(int a, const QString strs, QString &results);
    void Decryption(int a, const QString strs, QString &results);
};

#endif // TCPSERVER_H
