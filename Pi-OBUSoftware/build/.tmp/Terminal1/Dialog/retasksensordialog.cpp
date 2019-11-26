#include "retasksensordialog.h"
#include "ui_retasksensordialog.h"
#include <QDebug>
#include "readfile.h"
RetaskSensorDialog::RetaskSensorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RetaskSensorDialog)
{
    ui->setupUi(this);
}

RetaskSensorDialog::~RetaskSensorDialog()
{
    delete ui;
}

void RetaskSensorDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

RetaskSensorDialog::RetaskSensorDialog(QString Mac, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RetaskSensorDialog)
{
    ui->setupUi(this);
    QStringList listMac = Mac.split(",");
    int N = listMac.length();
    for(int i = 0; i < N; i++){
        ui->cbxMac->addItem(listMac.value(i));
    }
    QString mac = ui->cbxMac->currentText();
    if(!mac.isEmpty()) SetView(mac);
    if(Mac.isEmpty()) {
        ui->cbxFunc1->setEnabled(false);
        ui->cbxFunc2->setEnabled(false);
        ui->cbxFunc3->setEnabled(false);
    }

    setWindowTitle("Retask One Node");
}

RetaskSensorDialog::RetaskSensorDialog(QString mac, QString Mac, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RetaskSensorDialog)
{
    ui->setupUi(this);
    QStringList listMac = Mac.split(",");
    int index;
    int N = listMac.length();
    for(int i = 0; i < N; i++){
        ui->cbxMac->addItem(listMac.value(i));
        if(listMac.value(i) == mac) index = i;
    }
    ui->cbxMac->setCurrentIndex(index);
    SetView(mac);

    setWindowTitle("Retask One Node");
}

QString RetaskSensorDialog::getStatus(int stt)
{
    switch(stt)
    {
    case 0: return "Disable";
    case 1: return "Enable";
    case 2: return "Not support";
    default: return "N/A";
    }
}

void RetaskSensorDialog::SetView(QString mac)
{
    readfile x;
    FileData file(x.DATA_PATH);
    QString line = file.searchByMac(mac.toInt());
    QStringList lst = line.split(",");
    f1 = lst.value(3).toInt();
    f2 = lst.value(4).toInt();
    f3 = lst.value(5).toInt();
    qDebug() << "f1: " << f1 << "  f2: " << f2 << " f3 : "  << f3 << endl;
    ui->lblFunc1->setText(getStatus(f1));
    ui->lblFunc2->setText(getStatus(f2));
    ui->lblFunc3->setText(getStatus(f3));
    if(lst.value(3).toInt() == 2)
    {
        ui->cbxFunc1->setCurrentIndex(2);
        ui->cbxFunc1->setEnabled(false);
    } else {
        ui->cbxFunc1->setCurrentIndex(f1);
        ui->cbxFunc1->setEnabled(true);
    }
    if(lst.value(4).toInt() == 2)
    {
        ui->cbxFunc2->setCurrentIndex(2);
        ui->cbxFunc2->setEnabled(false);
    } else {
        ui->cbxFunc1->setCurrentIndex(f2);
        ui->cbxFunc1->setEnabled(true);
    }
    if(lst.value(5).toInt() == 2)
    {
        ui->cbxFunc3->setCurrentIndex(2);
        ui->cbxFunc3->setEnabled(false);
    } else {
        ui->cbxFunc1->setCurrentIndex(f3);
        ui->cbxFunc1->setEnabled(true);
    }
}

void RetaskSensorDialog::accept()
{
    QSettings settings(m_organizationName, m_appName);
    QString mac = ui->cbxMac->currentText();
    if(!mac.isEmpty()){
        settings.setValue("macRetask", ui->cbxMac->currentText());
        int func1 = ui->cbxFunc1->currentIndex();
        int func2 = ui->cbxFunc2->currentIndex();
        int func3 = ui->cbxFunc3->currentIndex();
        qDebug() << "fc1: " << func1 << "  fc2: " << func2 << " fc3 : "  << func3 << endl;
        //&& func3 != f3
        if(f1 < 2 ) settings.setValue("func1Retask", func1);
        else settings.setValue("func1Retask", "");
        if(f2 < 2 ) settings.setValue("func2Retask", func2);
        else settings.setValue("func2Retask", "");
        if(f3 < 2 ) settings.setValue("func3Retask", func3);
        else settings.setValue("func3Retask", "");
    } else settings.setValue("macRetask", "");
    QDialog::accept();
}

void RetaskSensorDialog::on_cbxMac_currentIndexChanged(QString )
{
    SetView(ui->cbxMac->currentText());;
}
