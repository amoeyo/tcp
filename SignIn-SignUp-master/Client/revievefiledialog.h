#ifndef REVIEVEFILEDIALOG_H
#define REVIEVEFILEDIALOG_H

#include <QDialog>

namespace Ui {
class revievefiledialog;
}

class revievefiledialog : public QDialog
{
    Q_OBJECT

public:
    explicit revievefiledialog(QWidget *parent = 0);
    ~revievefiledialog();

private:
    Ui::revievefiledialog *ui;
};

#endif // REVIEVEFILEDIALOG_H
