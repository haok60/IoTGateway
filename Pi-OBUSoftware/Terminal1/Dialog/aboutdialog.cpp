#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    QString str;
    str += "Description: This software use for patrolling in forest, \n\ncollect data, send command to control node in Zigbee sensor network.\n\n";
    str += "New feature in this version are:\n\n";
    str += "- Use google maps for display place of sensor network\n\n";
    str += "- Have GPS module for location\n\n";
    str += "- Note history about activities of OBU.\n\n";
    str += "- Retasking router\n\n";
    str += "- Upgrade firmware through wireless network\n";
    ui->lblContent->setText(str);

    setWindowTitle("About");
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::changeEvent(QEvent *e)
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

void AboutDialog::on_btnClose_clicked()
{
    this->close();
}
