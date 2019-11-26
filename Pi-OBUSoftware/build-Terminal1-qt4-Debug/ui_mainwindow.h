/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actSetting;
    QAction *actionLinphone;
    QAction *actionSerial_Port;
    QAction *actionNew;
    QAction *actionEdit_Place;
    QAction *actionInformation;
    QAction *actionRetask_One;
    QAction *actionRetask_All;
    QAction *actionAbout;
    QAction *actionAbout_2;
    QAction *actionServer;
    QAction *actionQuit;
    QAction *actionStartup_Location_Map;
    QAction *actionNew_Zone;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *layConsole;
    QPushButton *btnExit;
    QLabel *lblImage;
    QFrame *line;
    QFrame *line_2;
    QLabel *label_3;
    QPushButton *btnView;
    QPushButton *pushButton;
    QComboBox *boxCommand;
    QComboBox *boxSensor;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *btnPrint;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnOpenClose;
    QPushButton *btnClear;
    QPushButton *btnConfigThreshol;
    QLabel *runP;
    QLabel *runL;
    QLabel *countdowL;
    QLabel *countdowP;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(740, 529);
        actSetting = new QAction(MainWindow);
        actSetting->setObjectName(QString::fromUtf8("actSetting"));
        actionLinphone = new QAction(MainWindow);
        actionLinphone->setObjectName(QString::fromUtf8("actionLinphone"));
        actionSerial_Port = new QAction(MainWindow);
        actionSerial_Port->setObjectName(QString::fromUtf8("actionSerial_Port"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionEdit_Place = new QAction(MainWindow);
        actionEdit_Place->setObjectName(QString::fromUtf8("actionEdit_Place"));
        actionInformation = new QAction(MainWindow);
        actionInformation->setObjectName(QString::fromUtf8("actionInformation"));
        actionRetask_One = new QAction(MainWindow);
        actionRetask_One->setObjectName(QString::fromUtf8("actionRetask_One"));
        actionRetask_All = new QAction(MainWindow);
        actionRetask_All->setObjectName(QString::fromUtf8("actionRetask_All"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout_2 = new QAction(MainWindow);
        actionAbout_2->setObjectName(QString::fromUtf8("actionAbout_2"));
        actionServer = new QAction(MainWindow);
        actionServer->setObjectName(QString::fromUtf8("actionServer"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionStartup_Location_Map = new QAction(MainWindow);
        actionStartup_Location_Map->setObjectName(QString::fromUtf8("actionStartup_Location_Map"));
        actionNew_Zone = new QAction(MainWindow);
        actionNew_Zone->setObjectName(QString::fromUtf8("actionNew_Zone"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 0, 721, 491));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayoutWidget = new QWidget(tab);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 50, 421, 381));
        layConsole = new QVBoxLayout(verticalLayoutWidget);
        layConsole->setSpacing(6);
        layConsole->setContentsMargins(11, 11, 11, 11);
        layConsole->setObjectName(QString::fromUtf8("layConsole"));
        layConsole->setContentsMargins(0, 0, 0, 0);
        btnExit = new QPushButton(tab);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        btnExit->setGeometry(QRect(620, 400, 85, 27));
        lblImage = new QLabel(tab);
        lblImage->setObjectName(QString::fromUtf8("lblImage"));
        lblImage->setGeometry(QRect(420, 240, 271, 161));
        line = new QFrame(tab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(420, 390, 281, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(tab);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(420, 220, 271, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(430, 210, 67, 17));
        btnView = new QPushButton(tab);
        btnView->setObjectName(QString::fromUtf8("btnView"));
        btnView->setGeometry(QRect(430, 400, 96, 27));
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(590, 10, 91, 27));
        boxCommand = new QComboBox(tab);
        boxCommand->setObjectName(QString::fromUtf8("boxCommand"));
        boxCommand->setGeometry(QRect(100, 10, 301, 27));
        boxSensor = new QComboBox(tab);
        boxSensor->setObjectName(QString::fromUtf8("boxSensor"));
        boxSensor->setGeometry(QRect(430, 10, 151, 27));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 20, 81, 17));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(410, 10, 31, 17));
        btnPrint = new QPushButton(tab);
        btnPrint->setObjectName(QString::fromUtf8("btnPrint"));
        btnPrint->setGeometry(QRect(530, 400, 85, 27));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(570, 50, 141, 161));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btnOpenClose = new QPushButton(layoutWidget);
        btnOpenClose->setObjectName(QString::fromUtf8("btnOpenClose"));

        verticalLayout->addWidget(btnOpenClose);

        btnClear = new QPushButton(layoutWidget);
        btnClear->setObjectName(QString::fromUtf8("btnClear"));

        verticalLayout->addWidget(btnClear);

        btnConfigThreshol = new QPushButton(layoutWidget);
        btnConfigThreshol->setObjectName(QString::fromUtf8("btnConfigThreshol"));

        verticalLayout->addWidget(btnConfigThreshol);

        runP = new QLabel(tab);
        runP->setObjectName(QString::fromUtf8("runP"));
        runP->setGeometry(QRect(430, 50, 111, 17));
        runL = new QLabel(tab);
        runL->setObjectName(QString::fromUtf8("runL"));
        runL->setGeometry(QRect(430, 130, 101, 17));
        countdowL = new QLabel(tab);
        countdowL->setObjectName(QString::fromUtf8("countdowL"));
        countdowL->setGeometry(QRect(470, 170, 67, 17));
        countdowP = new QLabel(tab);
        countdowP->setObjectName(QString::fromUtf8("countdowP"));
        countdowP->setGeometry(QRect(460, 90, 67, 17));
        tabWidget->addTab(tab, QString());
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actSetting->setText(QApplication::translate("MainWindow", "Setting", 0, QApplication::UnicodeUTF8));
        actionLinphone->setText(QApplication::translate("MainWindow", "Linphone", 0, QApplication::UnicodeUTF8));
        actionSerial_Port->setText(QApplication::translate("MainWindow", "Setup Serial Port", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindow", "New Node", 0, QApplication::UnicodeUTF8));
        actionEdit_Place->setText(QApplication::translate("MainWindow", "Edit Node Place", 0, QApplication::UnicodeUTF8));
        actionInformation->setText(QApplication::translate("MainWindow", "Node Information", 0, QApplication::UnicodeUTF8));
        actionRetask_One->setText(QApplication::translate("MainWindow", "Retask One", 0, QApplication::UnicodeUTF8));
        actionRetask_All->setText(QApplication::translate("MainWindow", "Retask All", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionAbout_2->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionServer->setText(QApplication::translate("MainWindow", "Server", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionStartup_Location_Map->setText(QApplication::translate("MainWindow", "Startup Location Map", 0, QApplication::UnicodeUTF8));
        actionNew_Zone->setText(QApplication::translate("MainWindow", "New Zone", 0, QApplication::UnicodeUTF8));
        btnExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        lblImage->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "Image", 0, QApplication::UnicodeUTF8));
        btnView->setText(QApplication::translate("MainWindow", "View Image", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Send", 0, QApplication::UnicodeUTF8));
        boxCommand->clear();
        boxCommand->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Take Tempurature and Humidity", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Take Photo", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Take Illuminance", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "ON Pump", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "OFF Pump", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "ON Light", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "OFF Light", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Take Soil Moisture", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Take dust density", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("MainWindow", "Command", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "To", 0, QApplication::UnicodeUTF8));
        btnPrint->setText(QApplication::translate("MainWindow", "Print Text", 0, QApplication::UnicodeUTF8));
        btnOpenClose->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        btnClear->setText(QApplication::translate("MainWindow", "Clear Screen", 0, QApplication::UnicodeUTF8));
        btnConfigThreshol->setText(QApplication::translate("MainWindow", "Config Threshold", 0, QApplication::UnicodeUTF8));
        runP->setText(QApplication::translate("MainWindow", "Time run Pump", 0, QApplication::UnicodeUTF8));
        runL->setText(QApplication::translate("MainWindow", "Time run Light", 0, QApplication::UnicodeUTF8));
        countdowL->setText(QString());
        countdowP->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Home", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
