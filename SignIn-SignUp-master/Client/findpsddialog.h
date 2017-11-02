#ifndef FINDPSDDIALOG_H
#define FINDPSDDIALOG_H

#include <QDialog>
#include <QtNetwork>
#include <QMessageBox>

namespace Ui {
class FindpsdDialog;
}

class FindpsdDialog : public QDialog
{
    Q_OBJECT

public:
    QString question;
    QString username;
    explicit FindpsdDialog(QWidget *parent = 0);
    ~FindpsdDialog();

protected:
    void init();
    void connectServer();

private slots:
    void displayError(QAbstractSocket::SocketError);
    void readMessages();

    void on_OkPbt_clicked();

    void on_retPbt_clicked();

    void on_pushButton_clicked();

private:
    Ui::FindpsdDialog *ui;
    QTcpSocket *fpsdSocket;
};

#endif // FINDPSDDIALOG_H
