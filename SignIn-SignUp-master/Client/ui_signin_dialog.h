/********************************************************************************
** Form generated from reading UI file 'signin_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNIN_DIALOG_H
#define UI_SIGNIN_DIALOG_H

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

class Ui_signin_Dialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *userlineEdit;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *psdlineEdit;
    QLineEdit *queslineEdit;
    QLineEdit *anslineEdit;
    QPushButton *signinPbt;
    QPushButton *backPbt;

    void setupUi(QDialog *signin_Dialog)
    {
        if (signin_Dialog->objectName().isEmpty())
            signin_Dialog->setObjectName(QStringLiteral("signin_Dialog"));
        signin_Dialog->resize(558, 427);
        label = new QLabel(signin_Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 90, 91, 16));
        label_2 = new QLabel(signin_Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(110, 140, 72, 15));
        label_3 = new QLabel(signin_Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 180, 72, 15));
        userlineEdit = new QLineEdit(signin_Dialog);
        userlineEdit->setObjectName(QStringLiteral("userlineEdit"));
        userlineEdit->setGeometry(QRect(210, 130, 113, 21));
        label_4 = new QLabel(signin_Dialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(110, 230, 72, 15));
        label_5 = new QLabel(signin_Dialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(110, 270, 72, 15));
        psdlineEdit = new QLineEdit(signin_Dialog);
        psdlineEdit->setObjectName(QStringLiteral("psdlineEdit"));
        psdlineEdit->setGeometry(QRect(210, 170, 113, 21));
        psdlineEdit->setEchoMode(QLineEdit::Password);
        queslineEdit = new QLineEdit(signin_Dialog);
        queslineEdit->setObjectName(QStringLiteral("queslineEdit"));
        queslineEdit->setGeometry(QRect(210, 220, 113, 21));
        anslineEdit = new QLineEdit(signin_Dialog);
        anslineEdit->setObjectName(QStringLiteral("anslineEdit"));
        anslineEdit->setGeometry(QRect(210, 260, 113, 21));
        signinPbt = new QPushButton(signin_Dialog);
        signinPbt->setObjectName(QStringLiteral("signinPbt"));
        signinPbt->setGeometry(QRect(280, 320, 93, 28));
        backPbt = new QPushButton(signin_Dialog);
        backPbt->setObjectName(QStringLiteral("backPbt"));
        backPbt->setGeometry(QRect(400, 320, 93, 28));

        retranslateUi(signin_Dialog);
        QObject::connect(backPbt, SIGNAL(clicked()), signin_Dialog, SLOT(close()));

        QMetaObject::connectSlotsByName(signin_Dialog);
    } // setupUi

    void retranslateUi(QDialog *signin_Dialog)
    {
        signin_Dialog->setWindowTitle(QApplication::translate("signin_Dialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("signin_Dialog", "\346\226\260\347\224\250\346\210\267\346\263\250\345\206\214", Q_NULLPTR));
        label_2->setText(QApplication::translate("signin_Dialog", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        label_3->setText(QApplication::translate("signin_Dialog", "\345\257\206\347\240\201", Q_NULLPTR));
        label_4->setText(QApplication::translate("signin_Dialog", "\345\257\206\344\277\235\351\227\256\351\242\230", Q_NULLPTR));
        label_5->setText(QApplication::translate("signin_Dialog", "\347\255\224\346\241\210", Q_NULLPTR));
        signinPbt->setText(QApplication::translate("signin_Dialog", "\346\263\250\345\206\214", Q_NULLPTR));
        backPbt->setText(QApplication::translate("signin_Dialog", "\350\277\224\345\233\236", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class signin_Dialog: public Ui_signin_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNIN_DIALOG_H
