#include "sensorinformationdialog.h"
#include "ui_sensorinformationdialog.h"
#include "mainwindow.h"
#include "readfile.h"
#include <QDebug>

SensorInformationDialog::SensorInformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorInformationDialog)
{
    readfile x;
    ui->setupUi(this);

    connect(ui->cbxMac, SIGNAL(currentIndexChanged(QString)), this, SLOT(SetView(QString)));

    FileData file(x.DATA_PATH);
    int N = file.length();
    QString line;
    QStringList lst;
    for(int i = 0; i < N; i++){
        line = file.readLine(i+1);
        lst = line.split(",");
        ui->cbxMac->addItem(lst.value(0));
    }
    ui->cbxMac->setCurrentIndex(0);
    line = file.readLine(1);
    lst = line.split(",");
    SetView(lst.value(0));
    setWindowTitle("Node Information");
}

SensorInformationDialog::SensorInformationDialog(int mac, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorInformationDialog)
{
    readfile x;
    startSensor = QString::number(mac);
    ui->setupUi(this);

    connect(ui->cbxMac, SIGNAL(currentTextChanged(QString)), this, SLOT(SetView(QString)));

    FileData file(x.DATA_PATH);
    int N = file.length();
    int index;
    QString line;
    QStringList lst;
    for(int i = 0; i < N; i++){
        line = file.readLine(i+1);
        lst = line.split(",");
        ui->cbxMac->addItem(lst.value(0));
        if(lst.value(0).toInt() == mac) index = i;
    }
    ui->cbxMac->setCurrentIndex(index);
    SetView(startSensor);
    setWindowTitle("Node Information");
}

SensorInformationDialog::~SensorInformationDialog()
{
    delete ui;
}

QString SensorInformationDialog::getStatus(int stt)
{
    switch(stt)
    {
    case 0: return "Enable";
    case 1: return "Disable";
    case 2: return "Not support";
    default: return "N/A";
    }
}

void SensorInformationDialog::SetView(QString mac)
{
    readfile x;
    FileData file(x.DATA_PATH);
    QString line = file.searchByMac(mac.toInt());
    QStringList lst = line.split(",");
    QString str = lst.value(1) + "  ,  " + lst.value(2);
    ui->lblPlace->setText(str);
    ui->lblFunc1->setText(getStatus(lst.value(3).toInt()));
    ui->lblFunc2->setText(getStatus(lst.value(4).toInt()));
    ui->lblFunc3->setText(getStatus(lst.value(5).toInt()));
}

void SensorInformationDialog::on_btnClose_clicked()
{
    this->close();
}
