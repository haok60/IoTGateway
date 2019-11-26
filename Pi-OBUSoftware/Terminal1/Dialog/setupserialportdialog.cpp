#include "setupserialportdialog.h"
#include "ui_setupserialportdialog.h"
#include "qextserialport.h"
#include "qextserialenumerator.h"
#include <QSettings>
#include <QDebug>

SetupSerialPortDialog::SetupSerialPortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupSerialPortDialog)
{
    QSettings settings(m_organizationName, m_appName);
    QString port = settings.value("TranceiverPort").toString();
    ui->setupUi(this);
    int N = 0;
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
    {
        ui->boxTranceiverPort->addItem(info.portName);
        N++;
    }
    int index;
    for(int i = 0; i < N; i++)
    {
        if(!port.compare(ui->boxTranceiverPort->itemText(i))) index = i;
    }
    ui->boxTranceiverPort->setCurrentIndex(index);
    ui->boxTranceiverBaudrate->addItem("1200", BAUD1200);
    ui->boxTranceiverBaudrate->addItem("2400", BAUD2400);
    ui->boxTranceiverBaudrate->addItem("4800", BAUD4800);
    ui->boxTranceiverBaudrate->addItem("9600", BAUD9600);
    ui->boxTranceiverBaudrate->addItem("19200", BAUD19200);
    ui->boxTranceiverBaudrate->addItem("38400", BAUD38400);
    ui->boxTranceiverBaudrate->setCurrentIndex(4);

    port = settings.value("GpsPort").toString();
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
        ui->boxGpsPort->addItem(info.portName);
    for(int i = 0; i < N; i++)
    {
        if(!port.compare(ui->boxGpsPort->itemText(i))) index = i;
    }
    ui->boxGpsPort->setCurrentIndex(index);
    ui->boxGpsBaudrate->addItem("1200", BAUD1200);
    ui->boxGpsBaudrate->addItem("2400", BAUD2400);
    ui->boxGpsBaudrate->addItem("4800", BAUD4800);
    ui->boxGpsBaudrate->addItem("9600", BAUD9600);
    ui->boxGpsBaudrate->addItem("19200", BAUD19200);
    ui->boxGpsBaudrate->addItem("38400", BAUD38400);
    ui->boxGpsBaudrate->setCurrentIndex(3);
}

SetupSerialPortDialog::~SetupSerialPortDialog()
{
    delete ui;
}

void SetupSerialPortDialog::changeEvent(QEvent *e)
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

void SetupSerialPortDialog::accept()
{
    QSettings settings(m_organizationName, m_appName);
    settings.setValue("TranceiverPort", ui->boxTranceiverPort->currentText());
    settings.setValue("TranceiverBaudrate", ui->boxTranceiverBaudrate->itemData(ui->boxTranceiverBaudrate->currentIndex()));
    settings.setValue("GpsPort", ui->boxGpsPort->currentText());
    settings.setValue("GpsBaudrate", ui->boxGpsBaudrate->itemData(ui->boxGpsBaudrate->currentIndex()));

    QDialog::accept();
}

void SetupSerialPortDialog::on_btnRefresh_clicked()
{
    ui->boxGpsPort->clear();
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
        ui->boxTranceiverPort->addItem(info.portName);
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
        ui->boxGpsPort->addItem(info.portName);
}
