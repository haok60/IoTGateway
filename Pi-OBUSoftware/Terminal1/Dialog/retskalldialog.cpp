#include "retskalldialog.h"
#include "ui_retskalldialog.h"
#include <QSettings>

RetskAllDialog::RetskAllDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RetskAllDialog)
{
    ui->setupUi(this);

    setWindowTitle("Retask All Node Joined");
}

RetskAllDialog::~RetskAllDialog()
{
    delete ui;
}

void RetskAllDialog::accept()
{
    QSettings settings(m_organizationName, m_appName);
    settings.setValue("func1Retask", ui->cbxFunc1->currentIndex() + 2);
    settings.setValue("func2Retask", ui->cbxFunc2->currentIndex()+ 2);
    settings.setValue("func3Retask", ui->cbxFunc3->currentIndex()+ 2);

    QDialog::accept();
}
