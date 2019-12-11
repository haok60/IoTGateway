/********************************************************************************
** Form generated from reading UI file 'serverdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERDIALOG_H
#define UI_SERVERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerDialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *cbxConnect;
    QLabel *label;
    QLineEdit *lineIP;
    QLabel *label_2;
    QLineEdit *linePort;
    QTextEdit *txtContent;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnConnect;
    QPushButton *btnCancel;
    QPushButton *btnSend;

    void setupUi(QDialog *ServerDialog)
    {
        if (ServerDialog->objectName().isEmpty())
            ServerDialog->setObjectName(QString::fromUtf8("ServerDialog"));
        ServerDialog->resize(468, 291);
        widget = new QWidget(ServerDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 441, 268));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        cbxConnect = new QComboBox(widget);
        cbxConnect->setObjectName(QString::fromUtf8("cbxConnect"));

        horizontalLayout_2->addWidget(cbxConnect);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineIP = new QLineEdit(widget);
        lineIP->setObjectName(QString::fromUtf8("lineIP"));

        horizontalLayout_2->addWidget(lineIP);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        linePort = new QLineEdit(widget);
        linePort->setObjectName(QString::fromUtf8("linePort"));

        horizontalLayout_2->addWidget(linePort);


        verticalLayout->addLayout(horizontalLayout_2);

        txtContent = new QTextEdit(widget);
        txtContent->setObjectName(QString::fromUtf8("txtContent"));

        verticalLayout->addWidget(txtContent);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnConnect = new QPushButton(widget);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));

        horizontalLayout->addWidget(btnConnect);

        btnCancel = new QPushButton(widget);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout->addWidget(btnCancel);

        btnSend = new QPushButton(widget);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));

        horizontalLayout->addWidget(btnSend);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ServerDialog);

        QMetaObject::connectSlotsByName(ServerDialog);
    } // setupUi

    void retranslateUi(QDialog *ServerDialog)
    {
        ServerDialog->setWindowTitle(QApplication::translate("ServerDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        cbxConnect->clear();
        cbxConnect->insertItems(0, QStringList()
         << QApplication::translate("ServerDialog", "TCPSocket", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ServerDialog", "Http", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("ServerDialog", "IP Address", 0, QApplication::UnicodeUTF8));
        lineIP->setText(QApplication::translate("ServerDialog", "192.168.0.107", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ServerDialog", "Port", 0, QApplication::UnicodeUTF8));
        linePort->setText(QApplication::translate("ServerDialog", "9999", 0, QApplication::UnicodeUTF8));
        btnConnect->setText(QApplication::translate("ServerDialog", "Connect", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("ServerDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        btnSend->setText(QApplication::translate("ServerDialog", "Send", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ServerDialog: public Ui_ServerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERDIALOG_H
