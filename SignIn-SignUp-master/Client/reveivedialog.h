#ifndef REVEIVEDIALOG_H
#define REVEIVEDIALOG_H

#include <QDialog>
#include <QtNetwork>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <packet.h>

namespace Ui {
class ReveiveDialog;
}

class ReveiveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReveiveDialog(QWidget *parent = 0);
    ~ReveiveDialog();

protected:
    void initTcp();
    void initUdp();
    void newListen();
    void closeEvent(QCloseEvent *);

protected slots:
    void displayError(QAbstractSocket::SocketError);
    void fileConnection();
    void fileSlot();
    void readPendingDatagrams();
    void handleTimeout();

private:
    Ui::ReveiveDialog *ui;
    QString filename;
    QTcpServer *fileServer;
    QTcpSocket *fileSocket;
    QUdpSocket *udpSocket;
    QFile file;
    QString sendIP;
    qint64 fileSize;

    int i;
    int state;
    QTimer timer;
    int expected_seq_no = 0, timeout = 4;
    QTime begintime;
    QTime endtime;
    qint64 bytesReceived;


};

#endif // REVEIVEDIALOG_H
