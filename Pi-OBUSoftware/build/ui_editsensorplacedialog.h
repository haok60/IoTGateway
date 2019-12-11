/********************************************************************************
** Form generated from reading UI file 'editsensorplacedialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITSENSORPLACEDIALOG_H
#define UI_EDITSENSORPLACEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_EditSensorPlaceDialog
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *cbxMac;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineLat;
    QLineEdit *lineLng;

    void setupUi(QDialog *EditSensorPlaceDialog)
    {
        if (EditSensorPlaceDialog->objectName().isEmpty())
            EditSensorPlaceDialog->setObjectName(QString::fromUtf8("EditSensorPlaceDialog"));
        EditSensorPlaceDialog->resize(400, 212);
        buttonBox = new QDialogButtonBox(EditSensorPlaceDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(40, 160, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        cbxMac = new QComboBox(EditSensorPlaceDialog);
        cbxMac->setObjectName(QString::fromUtf8("cbxMac"));
        cbxMac->setGeometry(QRect(190, 26, 181, 31));
        label = new QLabel(EditSensorPlaceDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 40, 121, 17));
        label_2 = new QLabel(EditSensorPlaceDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 80, 81, 17));
        label_3 = new QLabel(EditSensorPlaceDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 120, 101, 17));
        lineLat = new QLineEdit(EditSensorPlaceDialog);
        lineLat->setObjectName(QString::fromUtf8("lineLat"));
        lineLat->setGeometry(QRect(190, 70, 181, 27));
        lineLng = new QLineEdit(EditSensorPlaceDialog);
        lineLng->setObjectName(QString::fromUtf8("lineLng"));
        lineLng->setGeometry(QRect(190, 110, 181, 27));

        retranslateUi(EditSensorPlaceDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), EditSensorPlaceDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), EditSensorPlaceDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(EditSensorPlaceDialog);
    } // setupUi

    void retranslateUi(QDialog *EditSensorPlaceDialog)
    {
        EditSensorPlaceDialog->setWindowTitle(QApplication::translate("EditSensorPlaceDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("EditSensorPlaceDialog", "Choose Sensor:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("EditSensorPlaceDialog", "Lattitude", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("EditSensorPlaceDialog", "Longtitude", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditSensorPlaceDialog: public Ui_EditSensorPlaceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITSENSORPLACEDIALOG_H
