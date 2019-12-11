/********************************************************************************
** Form generated from reading UI file 'retskalldialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RETSKALLDIALOG_H
#define UI_RETSKALLDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_RetskAllDialog
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *cbxFunc1;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *cbxFunc2;
    QComboBox *cbxFunc3;

    void setupUi(QDialog *RetskAllDialog)
    {
        if (RetskAllDialog->objectName().isEmpty())
            RetskAllDialog->setObjectName(QString::fromUtf8("RetskAllDialog"));
        RetskAllDialog->resize(335, 255);
        buttonBox = new QDialogButtonBox(RetskAllDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(20, 200, 291, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        cbxFunc1 = new QComboBox(RetskAllDialog);
        cbxFunc1->setObjectName(QString::fromUtf8("cbxFunc1"));
        cbxFunc1->setGeometry(QRect(150, 20, 161, 27));
        label = new QLabel(RetskAllDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 91, 17));
        label_2 = new QLabel(RetskAllDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 90, 91, 17));
        label_3 = new QLabel(RetskAllDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 150, 81, 17));
        cbxFunc2 = new QComboBox(RetskAllDialog);
        cbxFunc2->setObjectName(QString::fromUtf8("cbxFunc2"));
        cbxFunc2->setGeometry(QRect(150, 80, 161, 27));
        cbxFunc3 = new QComboBox(RetskAllDialog);
        cbxFunc3->setObjectName(QString::fromUtf8("cbxFunc3"));
        cbxFunc3->setGeometry(QRect(150, 140, 161, 27));

        retranslateUi(RetskAllDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), RetskAllDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RetskAllDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(RetskAllDialog);
    } // setupUi

    void retranslateUi(QDialog *RetskAllDialog)
    {
        RetskAllDialog->setWindowTitle(QApplication::translate("RetskAllDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        cbxFunc1->clear();
        cbxFunc1->insertItems(0, QStringList()
         << QApplication::translate("RetskAllDialog", "Disable", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("RetskAllDialog", "Enable", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("RetskAllDialog", "Function 1", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("RetskAllDialog", "Function 2", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("RetskAllDialog", "Function 3", 0, QApplication::UnicodeUTF8));
        cbxFunc2->clear();
        cbxFunc2->insertItems(0, QStringList()
         << QApplication::translate("RetskAllDialog", "Disable", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("RetskAllDialog", "Enable", 0, QApplication::UnicodeUTF8)
        );
        cbxFunc3->clear();
        cbxFunc3->insertItems(0, QStringList()
         << QApplication::translate("RetskAllDialog", "Disable", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("RetskAllDialog", "Enable", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class RetskAllDialog: public Ui_RetskAllDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RETSKALLDIALOG_H
