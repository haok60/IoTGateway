#include "newsensordialog.h"
#include "ui_newsensordialog.h"
#include "filedata.h"
#include "mainwindow.h"
#include "readfile.h"

NewSensorDialog::NewSensorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSensorDialog)
{
    ui->setupUi(this);
    setWindowTitle("New Node");
}

NewSensorDialog::~NewSensorDialog()
{
    delete ui;
}

void NewSensorDialog::accept()
{
    readfile x;
    QString lat = ui->lineLatNew->text();
    QString lng = ui->lineLngNew->text();
    QString mac = ui->lineMacNew->text();
    QString cluster = ui->lineClusterNew->text();
    int func1 = ui->cbxFunc1New->currentIndex();
    int func2 = ui->cbxFunc2New->currentIndex();
    int func3 = ui->cbxFunc3New->currentIndex();
    FileData file(x.DATA_PATH);
    FileData fileHist(x.HISTORY_FILE);
    if(!mac.isEmpty())
    {
        QString str = mac + "," + lat + "," + lng + "," + QString::number(func1) + "," +QString::number(func2) + "," + QString::number(func3)+"," + cluster;
        QString strH = mac + ":0:0";
        if(file.searchByMac(mac.toInt()).isEmpty()) file.writeAppend(str);
        if(fileHist.searchByMac(mac.toInt()).isEmpty()) fileHist.writeAppend(strH);
    }

    QDialog::accept();
}
