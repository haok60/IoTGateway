/********************************************************************************
** Form generated from reading UI file 'startuplocationdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTUPLOCATIONDIALOG_H
#define UI_STARTUPLOCATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_StartupLocationDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineLatStartup;
    QLineEdit *lineLngStartup;
    QLineEdit *lineZoomStartup;

    void setupUi(QDialog *StartupLocationDialog)
    {
        if (StartupLocationDialog->objectName().isEmpty())
            StartupLocationDialog->setObjectName(QString::fromUtf8("StartupLocationDialog"));
        StartupLocationDialog->resize(400, 196);
        buttonBox = new QDialogButtonBox(StartupLocationDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(40, 150, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(StartupLocationDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 81, 17));
        label_2 = new QLabel(StartupLocationDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 60, 81, 17));
        label_3 = new QLabel(StartupLocationDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 100, 67, 17));
        lineLatStartup = new QLineEdit(StartupLocationDialog);
        lineLatStartup->setObjectName(QString::fromUtf8("lineLatStartup"));
        lineLatStartup->setGeometry(QRect(150, 10, 231, 27));
        lineLngStartup = new QLineEdit(StartupLocationDialog);
        lineLngStartup->setObjectName(QString::fromUtf8("lineLngStartup"));
        lineLngStartup->setGeometry(QRect(150, 50, 231, 27));
        lineZoomStartup = new QLineEdit(StartupLocationDialog);
        lineZoomStartup->setObjectName(QString::fromUtf8("lineZoomStartup"));
        lineZoomStartup->setGeometry(QRect(150, 90, 231, 27));

        retranslateUi(StartupLocationDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), StartupLocationDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), StartupLocationDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(StartupLocationDialog);
    } // setupUi

    void retranslateUi(QDialog *StartupLocationDialog)
    {
        StartupLocationDialog->setWindowTitle(QApplication::translate("StartupLocationDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StartupLocationDialog", "Lattitude", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("StartupLocationDialog", "Longtitude", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("StartupLocationDialog", "Zoom", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StartupLocationDialog: public Ui_StartupLocationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTUPLOCATIONDIALOG_H
