#ifndef SENDFILEDIALOG_H
#define SENDFILEDIALOG_H

#include <QMainWindow>
#include <QtNetwork>
#include <QMessageBox>
#include <QDebug>

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

private slots:
    void readServer();

    void displayError(QAbstractSocket::SocketError);


    void on_linkPbt_clicked();

    void on_backPbt_clicked();

private:
    Ui::SendFileDialog *ui;
    QString recieverIP;
    bool isconnect;
    QTcpSocket *fusrSocket;

};

#endif // SENDFILEDIALOG_H
