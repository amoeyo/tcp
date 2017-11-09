#include "reveivedialog.h"
#include "ui_reveivedialog.h"

ReveiveDialog::ReveiveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReveiveDialog)
{
    ui->setupUi(this);
}

ReveiveDialog::~ReveiveDialog()
{
    delete ui;
}
