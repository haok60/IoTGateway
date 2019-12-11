/********************************************************************************
** Form generated from reading UI file 'retasksensordialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RETASKSENSORDIALOG_H
#define UI_RETASKSENSORDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_RetaskSensorDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QComboBox *cbxMac;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *lblFunc1;
    QLabel *lblFunc2;
    QLabel *lblFunc3;
    QFrame *line;
    QLabel *label_8;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *cbxFunc1;
    QComboBox *cbxFunc2;
    QComboBox *cbxFunc3;

    void setupUi(QDialog *RetaskSensorDialog)
    {
        if (RetaskSensorDialog->objectName().isEmpty())
            RetaskSensorDialog->setObjectName(QString::fromUtf8("RetaskSensorDialog"));
        RetaskSensorDialog->resize(615, 300);
        buttonBox = new QDialogButtonBox(RetaskSensorDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(250, 260, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(RetaskSensorDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 121, 17));
        cbxMac = new QComboBox(RetaskSensorDialog);
        cbxMac->setObjectName(QString::fromUtf8("cbxMac"));
        cbxMac->setGeometry(QRect(150, 10, 85, 27));
        label_2 = new QLabel(RetaskSensorDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 60, 91, 17));
        label_3 = new QLabel(RetaskSensorDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 110, 81, 17));
        label_4 = new QLabel(RetaskSensorDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 160, 81, 17));
        lblFunc1 = new QLabel(RetaskSensorDialog);
        lblFunc1->setObjectName(QString::fromUtf8("lblFunc1"));
        lblFunc1->setGeometry(QRect(120, 60, 121, 17));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lblFunc1->setFont(font);
        lblFunc2 = new QLabel(RetaskSensorDialog);
        lblFunc2->setObjectName(QString::fromUtf8("lblFunc2"));
        lblFunc2->setGeometry(QRect(130, 110, 121, 17));
        lblFunc2->setFont(font);
        lblFunc3 = new QLabel(RetaskSensorDialog);
        lblFunc3->setObjectName(QString::fromUtf8("lblFunc3"));
        lblFunc3->setGeometry(QRect(140, 160, 121, 17));
        lblFunc3->setFont(font);
        line = new QFrame(RetaskSensorDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(270, 0, 20, 261));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label_8 = new QLabel(RetaskSensorDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(320, 20, 81, 17));
        label_8->setFont(font);
        label_5 = new QLabel(RetaskSensorDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(320, 60, 81, 17));
        label_6 = new QLabel(RetaskSensorDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(320, 110, 81, 17));
        label_7 = new QLabel(RetaskSensorDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(320, 160, 81, 17));
        cbxFunc1 = new QComboBox(RetaskSensorDialog);
        cbxFunc1->setObjectName(QString::fromUtf8("cbxFunc1"));
        cbxFunc1->setGeometry(QRect(410, 50, 191, 27));
        cbxFunc2 = new QComboBox(RetaskSensorDialog);
        cbxFunc2->setObjectName(QString::fromUtf8("cbxFunc2"));
        cbxFunc2->setGeometry(QRect(410, 100, 191, 27));
        cbxFunc3 = new QComboBox(RetaskSensorDialog);
        cbxFunc3->setObjectName(QString::fromUtf8("cbxFunc3"));
        cbxFunc3->setGeometry(QRect(410, 150, 191, 27));

        retranslateUi(RetaskSensorDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), RetaskSensorDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RetaskSensorDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(RetaskSensorDialog);
    } // setupUi

    void retranslateUi(QDialog *RetaskSensorDialog)
    {
        RetaskSensorDialog->setWindowTitle(QApplication::translate("RetaskSensorDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RetaskSensorDialog", "Status of sensor", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("RetaskSensorDialog", "Function 1: ", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("RetaskSensorDialog", "Function 2:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("RetaskSensorDialog", "Function 3:", 0, QApplication::UnicodeUTF8));
        lblFunc1->setText(QString());
        lblFunc2->setText(QString());
        lblFunc3->setText(QString());
        label_8->setText(QApplication::translate("RetaskSensorDialog", "Retasking", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("RetaskSensorDialog", "Function 1", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("RetaskSensorDialog", "Function 2", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("RetaskSensorDialog", "Function 3", 0, QApplication::UnicodeUTF8));
        cbxFunc1->clear();
        cbxFunc1->insertItems(0, QStringList()
         << QApplication::translate("RetaskSensorDialog", "Disable", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("RetaskSensorDialog", "Enable", 0, QApplication::UnicodeUTF8)
        );
        cbxFunc2->clear();
        cbxFunc2->insertItems(0, QStringList()
         << QApplication::translate("RetaskSensorDialog", "Disable", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("RetaskSensorDialog", "Enable", 0, QApplication::UnicodeUTF8)
        );
        cbxFunc3->clear();
        cbxFunc3->insertItems(0, QStringList()
         << QApplication::translate("RetaskSensorDialog", "Disable", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("RetaskSensorDialog", "Enable", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class RetaskSensorDialog: public Ui_RetaskSensorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RETASKSENSORDIALOG_H
