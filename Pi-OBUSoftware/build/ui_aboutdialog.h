/********************************************************************************
** Form generated from reading UI file 'aboutdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *btnClose;
    QLabel *label_3;
    QLabel *lblContent;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName(QString::fromUtf8("AboutDialog"));
        AboutDialog->resize(529, 431);
        label = new QLabel(AboutDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 20, 311, 31));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(AboutDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 60, 371, 17));
        btnClose = new QPushButton(AboutDialog);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(410, 380, 93, 27));
        label_3 = new QLabel(AboutDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 400, 301, 17));
        QFont font1;
        font1.setItalic(true);
        label_3->setFont(font1);
        lblContent = new QLabel(AboutDialog);
        lblContent->setObjectName(QString::fromUtf8("lblContent"));
        lblContent->setGeometry(QRect(10, 100, 501, 271));

        retranslateUi(AboutDialog);

        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QApplication::translate("AboutDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AboutDialog", "Patrolling Software", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AboutDialog", "by Embedded Networking Research Group - Lab411 - C9", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("AboutDialog", "Close", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AboutDialog", "Hanoi University of Science and Technology", 0, QApplication::UnicodeUTF8));
        lblContent->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H
