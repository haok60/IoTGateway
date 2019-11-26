/********************************************************************************
** Form generated from reading UI file 'newsensordialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWSENSORDIALOG_H
#define UI_NEWSENSORDIALOG_H

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

class Ui_NewSensorDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineMacNew;
    QLineEdit *lineLatNew;
    QLineEdit *lineLngNew;
    QComboBox *cbxFunc1New;
    QComboBox *cbxFunc2New;
    QComboBox *cbxFunc3New;
    QLineEdit *lineClusterNew;
    QLabel *label_7;

    void setupUi(QDialog *NewSensorDialog)
    {
        if (NewSensorDialog->objectName().isEmpty())
            NewSensorDialog->setObjectName(QString::fromUtf8("NewSensorDialog"));
        NewSensorDialog->resize(401, 332);
        buttonBox = new QDialogButtonBox(NewSensorDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(50, 300, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(NewSensorDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 70, 71, 17));
        label_2 = new QLabel(NewSensorDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 110, 81, 17));
        label_3 = new QLabel(NewSensorDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 30, 67, 17));
        label_4 = new QLabel(NewSensorDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 190, 67, 17));
        label_5 = new QLabel(NewSensorDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 230, 67, 17));
        label_6 = new QLabel(NewSensorDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 270, 67, 17));
        lineMacNew = new QLineEdit(NewSensorDialog);
        lineMacNew->setObjectName(QString::fromUtf8("lineMacNew"));
        lineMacNew->setGeometry(QRect(150, 20, 231, 27));
        lineLatNew = new QLineEdit(NewSensorDialog);
        lineLatNew->setObjectName(QString::fromUtf8("lineLatNew"));
        lineLatNew->setGeometry(QRect(150, 60, 231, 27));
        lineLngNew = new QLineEdit(NewSensorDialog);
        lineLngNew->setObjectName(QString::fromUtf8("lineLngNew"));
        lineLngNew->setGeometry(QRect(150, 100, 231, 27));
        cbxFunc1New = new QComboBox(NewSensorDialog);
        cbxFunc1New->setObjectName(QString::fromUtf8("cbxFunc1New"));
        cbxFunc1New->setGeometry(QRect(150, 180, 141, 27));
        cbxFunc2New = new QComboBox(NewSensorDialog);
        cbxFunc2New->setObjectName(QString::fromUtf8("cbxFunc2New"));
        cbxFunc2New->setGeometry(QRect(150, 220, 141, 27));
        cbxFunc3New = new QComboBox(NewSensorDialog);
        cbxFunc3New->setObjectName(QString::fromUtf8("cbxFunc3New"));
        cbxFunc3New->setGeometry(QRect(150, 260, 141, 27));
        lineClusterNew = new QLineEdit(NewSensorDialog);
        lineClusterNew->setObjectName(QString::fromUtf8("lineClusterNew"));
        lineClusterNew->setGeometry(QRect(150, 140, 231, 27));
        label_7 = new QLabel(NewSensorDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 150, 111, 17));

        retranslateUi(NewSensorDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewSensorDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewSensorDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewSensorDialog);
    } // setupUi

    void retranslateUi(QDialog *NewSensorDialog)
    {
        NewSensorDialog->setWindowTitle(QApplication::translate("NewSensorDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewSensorDialog", "Lattitude", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewSensorDialog", "Longtitude", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NewSensorDialog", "Mac", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NewSensorDialog", "Func 1", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("NewSensorDialog", "Func 2", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("NewSensorDialog", "Func 3", 0, QApplication::UnicodeUTF8));
        cbxFunc1New->clear();
        cbxFunc1New->insertItems(0, QStringList()
         << QApplication::translate("NewSensorDialog", "Enable", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NewSensorDialog", "Disable", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NewSensorDialog", "Not Support", 0, QApplication::UnicodeUTF8)
        );
        cbxFunc2New->clear();
        cbxFunc2New->insertItems(0, QStringList()
         << QApplication::translate("NewSensorDialog", "Enble", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NewSensorDialog", "Disable", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NewSensorDialog", "Not Support", 0, QApplication::UnicodeUTF8)
        );
        cbxFunc3New->clear();
        cbxFunc3New->insertItems(0, QStringList()
         << QApplication::translate("NewSensorDialog", "Enable", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NewSensorDialog", "Disable", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NewSensorDialog", "Not Support", 0, QApplication::UnicodeUTF8)
        );
        label_7->setText(QApplication::translate("NewSensorDialog", "Cluster head", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewSensorDialog: public Ui_NewSensorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWSENSORDIALOG_H
