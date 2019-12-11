/********************************************************************************
** Form generated from reading UI file 'sensorinformationdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORINFORMATIONDIALOG_H
#define UI_SENSORINFORMATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SensorInformationDialog
{
public:
    QLabel *label;
    QComboBox *cbxMac;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *lblPlace;
    QLabel *lblFunc1;
    QLabel *lblFunc2;
    QLabel *lblFunc3;
    QPushButton *btnClose;

    void setupUi(QDialog *SensorInformationDialog)
    {
        if (SensorInformationDialog->objectName().isEmpty())
            SensorInformationDialog->setObjectName(QString::fromUtf8("SensorInformationDialog"));
        SensorInformationDialog->resize(408, 284);
        label = new QLabel(SensorInformationDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 131, 17));
        cbxMac = new QComboBox(SensorInformationDialog);
        cbxMac->setObjectName(QString::fromUtf8("cbxMac"));
        cbxMac->setGeometry(QRect(160, 10, 161, 27));
        label_2 = new QLabel(SensorInformationDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 60, 61, 17));
        label_3 = new QLabel(SensorInformationDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 100, 81, 17));
        label_4 = new QLabel(SensorInformationDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 140, 81, 21));
        label_5 = new QLabel(SensorInformationDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 180, 81, 17));
        lblPlace = new QLabel(SensorInformationDialog);
        lblPlace->setObjectName(QString::fromUtf8("lblPlace"));
        lblPlace->setGeometry(QRect(130, 60, 241, 17));
        lblFunc1 = new QLabel(SensorInformationDialog);
        lblFunc1->setObjectName(QString::fromUtf8("lblFunc1"));
        lblFunc1->setGeometry(QRect(130, 100, 241, 17));
        lblFunc2 = new QLabel(SensorInformationDialog);
        lblFunc2->setObjectName(QString::fromUtf8("lblFunc2"));
        lblFunc2->setGeometry(QRect(130, 140, 241, 17));
        lblFunc3 = new QLabel(SensorInformationDialog);
        lblFunc3->setObjectName(QString::fromUtf8("lblFunc3"));
        lblFunc3->setGeometry(QRect(130, 180, 241, 17));
        btnClose = new QPushButton(SensorInformationDialog);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(260, 230, 99, 27));

        retranslateUi(SensorInformationDialog);

        QMetaObject::connectSlotsByName(SensorInformationDialog);
    } // setupUi

    void retranslateUi(QDialog *SensorInformationDialog)
    {
        SensorInformationDialog->setWindowTitle(QApplication::translate("SensorInformationDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SensorInformationDialog", "Choose a sensor:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SensorInformationDialog", "Place:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SensorInformationDialog", "Function 1:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SensorInformationDialog", "Function 2:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SensorInformationDialog", "Function 3:", 0, QApplication::UnicodeUTF8));
        lblPlace->setText(QString());
        lblFunc1->setText(QString());
        lblFunc2->setText(QString());
        lblFunc3->setText(QString());
        btnClose->setText(QApplication::translate("SensorInformationDialog", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SensorInformationDialog: public Ui_SensorInformationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORINFORMATIONDIALOG_H
