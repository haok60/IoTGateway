#include "startuplocationdialog.h"
#include "ui_startuplocationdialog.h"
#include <QSettings>

StartupLocationDialog::StartupLocationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartupLocationDialog)
{
    ui->setupUi(this);
    QSettings settings(m_organizationName, m_appName);
    QString lat = settings.value("latStartup").toString();
    if(lat.isEmpty()) lat = "20.333413";
    QString lng = settings.value("lngStartup").toString();
    if(lng.isEmpty()) lng = "105.597677";
    QString zm = settings.value("zoomStartup").toString();
    if(zm.isEmpty()) zm = "8";
    ui->lineLatStartup->setText(lat);
    ui->lineLngStartup->setText(lng);
    ui->lineZoomStartup->setText(zm);
    setWindowTitle("Set Startup Location");
}

StartupLocationDialog::~StartupLocationDialog()
{
    delete ui;
}

void StartupLocationDialog::accept()
{
    QSettings settings(m_organizationName, m_appName);
    settings.setValue("latStartup", ui->lineLatStartup->text());
    settings.setValue("lngStartup", ui->lineLngStartup->text());
    settings.setValue("zoomStartup", ui->lineZoomStartup->text());

    QDialog::accept();
}
