/********************************************************************************
** Form generated from reading UI file 'findpsddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDPSDDIALOG_H
#define UI_FINDPSDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FindpsdDialog
{
public:
    QLabel *label;
    QLabel *text_label;
    QLineEdit *ansLineEdit;
    QLabel *label_2;
    QPushButton *OkPbt;
    QPushButton *retPbt;
    QPushButton *pushButton;

    void setupUi(QDialog *FindpsdDialog)
    {
        if (FindpsdDialog->objectName().isEmpty())
            FindpsdDialog->setObjectName(QStringLiteral("FindpsdDialog"));
        FindpsdDialog->resize(511, 386);
        label = new QLabel(FindpsdDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 140, 72, 15));
        text_label = new QLabel(FindpsdDialog);
        text_label->setObjectName(QStringLiteral("text_label"));
        text_label->setGeometry(QRect(160, 140, 111, 16));
        ansLineEdit = new QLineEdit(FindpsdDialog);
        ansLineEdit->setObjectName(QStringLiteral("ansLineEdit"));
        ansLineEdit->setGeometry(QRect(160, 180, 113, 21));
        label_2 = new QLabel(FindpsdDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 180, 72, 15));
        OkPbt = new QPushButton(FindpsdDialog);
        OkPbt->setObjectName(QStringLiteral("OkPbt"));
        OkPbt->setGeometry(QRect(250, 240, 93, 28));
        retPbt = new QPushButton(FindpsdDialog);
        retPbt->setObjectName(QStringLiteral("retPbt"));
        retPbt->setGeometry(QRect(370, 240, 93, 28));
        pushButton = new QPushButton(FindpsdDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(310, 130, 93, 28));

        retranslateUi(FindpsdDialog);

        QMetaObject::connectSlotsByName(FindpsdDialog);
    } // setupUi

    void retranslateUi(QDialog *FindpsdDialog)
    {
        FindpsdDialog->setWindowTitle(QApplication::translate("FindpsdDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("FindpsdDialog", "\345\257\206\344\277\235\351\227\256\351\242\230:", Q_NULLPTR));
        text_label->setText(QString());
        label_2->setText(QApplication::translate("FindpsdDialog", "\347\255\224\346\241\210", Q_NULLPTR));
        OkPbt->setText(QApplication::translate("FindpsdDialog", "\347\241\256\350\256\244", Q_NULLPTR));
        retPbt->setText(QApplication::translate("FindpsdDialog", "\350\277\224\345\233\236", Q_NULLPTR));
        pushButton->setText(QApplication::translate("FindpsdDialog", "\350\216\267\345\276\227\351\227\256\351\242\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FindpsdDialog: public Ui_FindpsdDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDPSDDIALOG_H
