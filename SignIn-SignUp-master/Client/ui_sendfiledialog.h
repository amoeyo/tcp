/********************************************************************************
** Form generated from reading UI file 'sendfiledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDFILEDIALOG_H
#define UI_SENDFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SendFileDialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *usrLet;
    QPushButton *linkPbt;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *fileLet;
    QPushButton *choosePbt;
    QPushButton *sendPbt;
    QPushButton *backPbt;
    QProgressBar *progressBar;

    void setupUi(QDialog *SendFileDialog)
    {
        if (SendFileDialog->objectName().isEmpty())
            SendFileDialog->setObjectName(QStringLiteral("SendFileDialog"));
        SendFileDialog->resize(568, 286);
        horizontalLayoutWidget = new QWidget(SendFileDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(40, 20, 501, 71));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        usrLet = new QLineEdit(horizontalLayoutWidget);
        usrLet->setObjectName(QStringLiteral("usrLet"));

        horizontalLayout->addWidget(usrLet);

        linkPbt = new QPushButton(horizontalLayoutWidget);
        linkPbt->setObjectName(QStringLiteral("linkPbt"));

        horizontalLayout->addWidget(linkPbt);

        horizontalLayoutWidget_2 = new QWidget(SendFileDialog);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(40, 100, 501, 78));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        fileLet = new QLineEdit(horizontalLayoutWidget_2);
        fileLet->setObjectName(QStringLiteral("fileLet"));

        horizontalLayout_2->addWidget(fileLet);

        choosePbt = new QPushButton(horizontalLayoutWidget_2);
        choosePbt->setObjectName(QStringLiteral("choosePbt"));

        horizontalLayout_2->addWidget(choosePbt);

        sendPbt = new QPushButton(SendFileDialog);
        sendPbt->setObjectName(QStringLiteral("sendPbt"));
        sendPbt->setGeometry(QRect(40, 180, 361, 41));
        backPbt = new QPushButton(SendFileDialog);
        backPbt->setObjectName(QStringLiteral("backPbt"));
        backPbt->setGeometry(QRect(420, 180, 121, 41));
        progressBar = new QProgressBar(SendFileDialog);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(40, 240, 501, 23));
        progressBar->setValue(24);

        retranslateUi(SendFileDialog);

        QMetaObject::connectSlotsByName(SendFileDialog);
    } // setupUi

    void retranslateUi(QDialog *SendFileDialog)
    {
        SendFileDialog->setWindowTitle(QApplication::translate("SendFileDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("SendFileDialog", "\351\200\211\346\213\251\347\233\256\346\240\207\347\224\250\346\210\267", Q_NULLPTR));
        linkPbt->setText(QApplication::translate("SendFileDialog", "\350\277\236\346\216\245", Q_NULLPTR));
        choosePbt->setText(QApplication::translate("SendFileDialog", "\351\200\211\346\213\251\346\226\207\344\273\266", Q_NULLPTR));
        sendPbt->setText(QApplication::translate("SendFileDialog", "\345\217\221\351\200\201", Q_NULLPTR));
        backPbt->setText(QApplication::translate("SendFileDialog", "\350\277\224\345\233\236", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SendFileDialog: public Ui_SendFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDFILEDIALOG_H
