/********************************************************************************
** Form generated from reading UI file 'reveivedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REVEIVEDIALOG_H
#define UI_REVEIVEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_ReveiveDialog
{
public:
    QTextBrowser *textBrowser;
    QProgressBar *progressBar;

    void setupUi(QDialog *ReveiveDialog)
    {
        if (ReveiveDialog->objectName().isEmpty())
            ReveiveDialog->setObjectName(QStringLiteral("ReveiveDialog"));
        ReveiveDialog->resize(537, 363);
        textBrowser = new QTextBrowser(ReveiveDialog);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(20, 20, 501, 271));
        progressBar = new QProgressBar(ReveiveDialog);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(20, 310, 501, 23));
        progressBar->setValue(24);

        retranslateUi(ReveiveDialog);

        QMetaObject::connectSlotsByName(ReveiveDialog);
    } // setupUi

    void retranslateUi(QDialog *ReveiveDialog)
    {
        ReveiveDialog->setWindowTitle(QApplication::translate("ReveiveDialog", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ReveiveDialog: public Ui_ReveiveDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REVEIVEDIALOG_H
