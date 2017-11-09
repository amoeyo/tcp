#ifndef REVEIVEDIALOG_H
#define REVEIVEDIALOG_H

#include <QDialog>

namespace Ui {
class ReveiveDialog;
}

class ReveiveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReveiveDialog(QWidget *parent = 0);
    ~ReveiveDialog();

private:
    Ui::ReveiveDialog *ui;
};

#endif // REVEIVEDIALOG_H
