/********************************************************************************
** Form generated from reading UI file 'setupserialportdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUPSERIALPORTDIALOG_H
#define UI_SETUPSERIALPORTDIALOG_H

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
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetupSerialPortDialog
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *boxTranceiverPort;
    QComboBox *boxTranceiverBaudrate;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QFrame *line;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *boxGpsPort;
    QComboBox *boxGpsBaudrate;
    QPushButton *btnRefresh;

    void setupUi(QDialog *SetupSerialPortDialog)
    {
        if (SetupSerialPortDialog->objectName().isEmpty())
            SetupSerialPortDialog->setObjectName(QString::fromUtf8("SetupSerialPortDialog"));
        SetupSerialPortDialog->resize(505, 236);
        buttonBox = new QDialogButtonBox(SetupSerialPortDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(150, 190, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        boxTranceiverPort = new QComboBox(SetupSerialPortDialog);
        boxTranceiverPort->setObjectName(QString::fromUtf8("boxTranceiverPort"));
        boxTranceiverPort->setGeometry(QRect(120, 60, 131, 31));
        boxTranceiverBaudrate = new QComboBox(SetupSerialPortDialog);
        boxTranceiverBaudrate->setObjectName(QString::fromUtf8("boxTranceiverBaudrate"));
        boxTranceiverBaudrate->setGeometry(QRect(120, 120, 131, 31));
        label = new QLabel(SetupSerialPortDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 81, 17));
        label_2 = new QLabel(SetupSerialPortDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 70, 62, 17));
        label_3 = new QLabel(SetupSerialPortDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 130, 71, 17));
        line = new QFrame(SetupSerialPortDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(253, 0, 20, 171));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(SetupSerialPortDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(280, 20, 62, 17));
        label_5 = new QLabel(SetupSerialPortDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(280, 70, 51, 17));
        label_6 = new QLabel(SetupSerialPortDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(280, 130, 81, 17));
        boxGpsPort = new QComboBox(SetupSerialPortDialog);
        boxGpsPort->setObjectName(QString::fromUtf8("boxGpsPort"));
        boxGpsPort->setGeometry(QRect(360, 60, 131, 31));
        boxGpsBaudrate = new QComboBox(SetupSerialPortDialog);
        boxGpsBaudrate->setObjectName(QString::fromUtf8("boxGpsBaudrate"));
        boxGpsBaudrate->setGeometry(QRect(360, 120, 131, 31));
        btnRefresh = new QPushButton(SetupSerialPortDialog);
        btnRefresh->setObjectName(QString::fromUtf8("btnRefresh"));
        btnRefresh->setGeometry(QRect(40, 190, 93, 27));

        retranslateUi(SetupSerialPortDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SetupSerialPortDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SetupSerialPortDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SetupSerialPortDialog);
    } // setupUi

    void retranslateUi(QDialog *SetupSerialPortDialog)
    {
        SetupSerialPortDialog->setWindowTitle(QApplication::translate("SetupSerialPortDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SetupSerialPortDialog", "Tranceiver", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SetupSerialPortDialog", "Port", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SetupSerialPortDialog", "Baudrate", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SetupSerialPortDialog", "GPS", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SetupSerialPortDialog", "Port", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SetupSerialPortDialog", "Baudrate", 0, QApplication::UnicodeUTF8));
        btnRefresh->setText(QApplication::translate("SetupSerialPortDialog", "Refresh", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SetupSerialPortDialog: public Ui_SetupSerialPortDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUPSERIALPORTDIALOG_H
