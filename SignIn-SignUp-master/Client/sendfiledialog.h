#ifndef SENDFILEDIALOG_H
#define SENDFILEDIALOG_H

#include <QDialog>
#include <QtNetwork>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <packet.h>
#include <QTimer>
#include <QTime>


namespace Ui {
class SendFileDialog;
}

class SendFileDialog : public QDialog
{
    Q_OBJECT

public:
    QString sender;
    QString reciever;
    QString senderIP;
    explicit SendFileDialog(QWidget *parent = 0);
    ~SendFileDialog();

protected:
    void init();
    void initUdp();
    void handle_loss_event();
    void sendData(int i);
    void startSend();

private slots:
    void readServer();

    void displayError(QAbstractSocket::SocketError);

    void readPendingDatagrams();


    void handleTimeout();


    void on_linkPbt_clicked();

    void on_backPbt_clicked();

    void on_choosePbt_clicked();

    void on_sendPbt_clicked();

private:
    Ui::SendFileDialog *ui;
    QString recieverIP;
    QString fileName;
    qint64 fileSize;        //文件大小
    qint64 sendSize=0;        //已经发送大小
    QTimer *timer=new QTimer(this);           //定时器
    bool isconnect;
    QFile file;
    QTcpSocket *fusrSocket;
    QUdpSocket *udpSocket;
    QByteArray backupData;
    int i;
    bool flag;
    int expected_seq_no = 0;
    int sending_window_size;//滑动窗口大小
    int remaining_chunks;
    int base=0,  next_seq_no=0;
    int duplicate_ack_num=0, resend_base=0;
    int timeout=2;
    int timepass;
    int last_resent=0, timeout_counter=0;
    struct Packet *pkts;
    QTime alltime;
    QTime time;
    int state;
    qint64 bytesSend;

};



#endif // SENDFILEDIALOG_H
