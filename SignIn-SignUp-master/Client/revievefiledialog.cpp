#include "revievefiledialog.h"
#include "ui_revievefiledialog.h"

revievefiledialog::revievefiledialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::revievefiledialog)
{
    ui->setupUi(this);
}

revievefiledialog::~revievefiledialog()
{
    delete ui;
}
