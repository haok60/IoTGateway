#include "editsensorplacedialog.h"
#include "ui_editsensorplacedialog.h"
#include "filedata.h"
#include "mainwindow.h"
#include "readfile.h"
EditSensorPlaceDialog::EditSensorPlaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditSensorPlaceDialog)
{
    readfile x;
    ui->setupUi(this);

    connect(ui->cbxMac, SIGNAL(currentTextChanged(QString)), this, SLOT(SetView(QString)));

    FileData file(x.DATA_PATH);
    int N = file.length();
    QString line;
    QStringList lst;
    for(int i = 0; i < N; i++){
        line = file.readLine(i+1);
        lst = line.split(",");
        ui->cbxMac->addItem(lst.value(0));
    }
    setWindowTitle("Edit Node Place");
}

EditSensorPlaceDialog::~EditSensorPlaceDialog()
{
    delete ui;
}

void EditSensorPlaceDialog::accept()
{
    readfile x;
    FileData file(x.DATA_PATH);
    int mac = ui->cbxMac->currentText().toInt();
    QString line = file.searchByMac(mac);
    QStringList lst = line.split(",");
    QString lat = ui->lineLat->text();
    QString lng = ui->lineLng->text();
    if(lat.isEmpty()) lat = lst.value(1);
    if(lng.isEmpty()) lng = lst.value(2);
    QString str = lst.value(0) + "," + lat + "," + lng + "," + lst.value(3) + "," + lst.value(4) + "," +lst.value(5);
    file.EditByMac(mac, str);

    QDialog::accept();
}

void EditSensorPlaceDialog::SetView(QString mac)
{
    readfile x;
    FileData file(x.DATA_PATH);
    QString line = file.searchByMac(mac.toInt());
    QStringList lst = line.split(",");
    ui->lineLat->setText(lst.value(1));
    ui->lineLng->setText(lst.value(2));
}
