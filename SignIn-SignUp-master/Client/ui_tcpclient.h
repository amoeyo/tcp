/********************************************************************************
** Form generated from reading UI file 'tcpclient.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPCLIENT_H
#define UI_TCPCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TcpClient
{
public:
    QWidget *centralWidget;
    QPushButton *sendBtn;
    QPushButton *signBtn;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *passwardLineEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *userLineEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TcpClient)
    {
        if (TcpClient->objectName().isEmpty())
            TcpClient->setObjectName(QStringLiteral("TcpClient"));
        TcpClient->resize(416, 335);
        centralWidget = new QWidget(TcpClient);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sendBtn = new QPushButton(centralWidget);
        sendBtn->setObjectName(QStringLiteral("sendBtn"));
        sendBtn->setGeometry(QRect(210, 180, 71, 23));
        signBtn = new QPushButton(centralWidget);
        signBtn->setObjectName(QStringLiteral("signBtn"));
        signBtn->setGeometry(QRect(91, 181, 72, 23));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 120, 189, 23));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        passwardLineEdit = new QLineEdit(layoutWidget);
        passwardLineEdit->setObjectName(QStringLiteral("passwardLineEdit"));

        horizontalLayout_2->addWidget(passwardLineEdit);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(90, 60, 189, 23));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        userLineEdit = new QLineEdit(layoutWidget1);
        userLineEdit->setObjectName(QStringLiteral("userLineEdit"));

        horizontalLayout->addWidget(userLineEdit);

        TcpClient->setCentralWidget(centralWidget);
        sendBtn->raise();
        signBtn->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        userLineEdit->raise();
        menuBar = new QMenuBar(TcpClient);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 416, 26));
        TcpClient->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TcpClient);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TcpClient->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TcpClient);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TcpClient->setStatusBar(statusBar);

        retranslateUi(TcpClient);

        QMetaObject::connectSlotsByName(TcpClient);
    } // setupUi

    void retranslateUi(QMainWindow *TcpClient)
    {
        TcpClient->setWindowTitle(QApplication::translate("TcpClient", "TcpClient", Q_NULLPTR));
        sendBtn->setText(QApplication::translate("TcpClient", "\347\231\273\345\275\225", Q_NULLPTR));
        signBtn->setText(QApplication::translate("TcpClient", "\346\263\250\345\206\214", Q_NULLPTR));
        label_2->setText(QApplication::translate("TcpClient", "\345\257\206  \347\240\201\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("TcpClient", "\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TcpClient: public Ui_TcpClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENT_H
