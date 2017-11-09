/********************************************************************************
** Form generated from reading UI file 'talantoo.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TALANTOO_H
#define UI_TALANTOO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TalantOO
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout;
    QPushButton *offlinePbt;
    QLineEdit *sendmessLet;
    QPushButton *sendmessPbt;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *usrLet;
    QPushButton *connectPbt;
    QPushButton *exitPbt;
    QPushButton *sendfilePbt;

    void setupUi(QDialog *TalantOO)
    {
        if (TalantOO->objectName().isEmpty())
            TalantOO->setObjectName(QStringLiteral("TalantOO"));
        TalantOO->resize(661, 504);
        verticalLayoutWidget = new QWidget(TalantOO);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 20, 611, 461));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textBrowser = new QTextBrowser(verticalLayoutWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        offlinePbt = new QPushButton(verticalLayoutWidget);
        offlinePbt->setObjectName(QStringLiteral("offlinePbt"));

        horizontalLayout->addWidget(offlinePbt);

        sendmessLet = new QLineEdit(verticalLayoutWidget);
        sendmessLet->setObjectName(QStringLiteral("sendmessLet"));

        horizontalLayout->addWidget(sendmessLet);

        sendmessPbt = new QPushButton(verticalLayoutWidget);
        sendmessPbt->setObjectName(QStringLiteral("sendmessPbt"));

        horizontalLayout->addWidget(sendmessPbt);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        usrLet = new QLineEdit(verticalLayoutWidget);
        usrLet->setObjectName(QStringLiteral("usrLet"));

        horizontalLayout_2->addWidget(usrLet);

        connectPbt = new QPushButton(verticalLayoutWidget);
        connectPbt->setObjectName(QStringLiteral("connectPbt"));

        horizontalLayout_2->addWidget(connectPbt);

        exitPbt = new QPushButton(verticalLayoutWidget);
        exitPbt->setObjectName(QStringLiteral("exitPbt"));

        horizontalLayout_2->addWidget(exitPbt);


        verticalLayout->addLayout(horizontalLayout_2);

        sendfilePbt = new QPushButton(verticalLayoutWidget);
        sendfilePbt->setObjectName(QStringLiteral("sendfilePbt"));

        verticalLayout->addWidget(sendfilePbt);


        retranslateUi(TalantOO);

        QMetaObject::connectSlotsByName(TalantOO);
    } // setupUi

    void retranslateUi(QDialog *TalantOO)
    {
        TalantOO->setWindowTitle(QApplication::translate("TalantOO", "Dialog", Q_NULLPTR));
        offlinePbt->setText(QApplication::translate("TalantOO", "\347\246\273\347\272\277\346\266\210\346\201\257", Q_NULLPTR));
        sendmessLet->setPlaceholderText(QApplication::translate("TalantOO", "\345\234\250\346\255\244\350\276\223\345\205\245\346\266\210\346\201\257", Q_NULLPTR));
        sendmessPbt->setText(QApplication::translate("TalantOO", "\345\217\221\351\200\201\346\266\210\346\201\257", Q_NULLPTR));
        label->setText(QApplication::translate("TalantOO", "\347\233\256\346\240\207\347\224\250\346\210\267", Q_NULLPTR));
        usrLet->setPlaceholderText(QApplication::translate("TalantOO", "\345\234\250\346\255\244\350\276\223\345\205\245\350\277\236\346\216\245\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        connectPbt->setText(QApplication::translate("TalantOO", "\350\277\236\346\216\245", Q_NULLPTR));
        exitPbt->setText(QApplication::translate("TalantOO", "\351\200\200\345\207\272", Q_NULLPTR));
        sendfilePbt->setText(QApplication::translate("TalantOO", "\346\226\207\344\273\266\344\274\240\350\276\223", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TalantOO: public Ui_TalantOO {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TALANTOO_H
