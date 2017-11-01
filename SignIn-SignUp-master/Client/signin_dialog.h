#ifndef SIGNIN_DIALOG_H
#define SIGNIN_DIALOG_H

#include <QDialog>
#include <QtNetwork>
#include <QMessageBox>

namespace Ui {
class signin_Dialog;
}

class signin_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit signin_Dialog(QWidget *parent = 0);
    ~signin_Dialog();

protected:
    void init();
    void connectServer();

private slots:
    void displayError(QAbstractSocket::SocketError);
    void readMessages();

    void on_signinPbt_clicked();

private:
    Ui::signin_Dialog *ui;
    QTcpSocket *signSocket;

};

#endif // SIGNIN_DIALOG_H
