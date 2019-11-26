#include "configthreshold.h"
#include "ui_configthreshold.h"
#include <QDebug>
configThreshold::configThreshold(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configThreshold)
{
    ui->setupUi(this);
    ui->timeValue->setSingleStep(0.1);
    ui->timeValueL->setSingleStep(0.1);
    QFile file("./WSAN/thresol.txt");
        QLabel *testLabel= new QLabel;

        QString line;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream stream(&file);
                DATA::temp_t = stream.readLine().toDouble();
                testLabel->setText(line+"\n");
                qDebug()<<DATA::temp_t;
                DATA::hump_t=stream.readLine().toDouble();
                DATA::lux_t=stream.readLine().toDouble();
                DATA::mois_t=stream.readLine().toInt();
                DATA::mois_t2 = stream.readLine().toInt();
                DATA::time_P=stream.readLine().toDouble();
                DATA::time_L=stream.readLine().toDouble();

        }
        file.close();
        ui->dsb_Temp->setValue(DATA::temp_t);
        ui->dsb_Humi->setValue(DATA::hump_t);
        ui->dsb_Light->setValue(DATA::lux_t);
        ui->dsb_mois->setValue(DATA::mois_t);
        ui->dsb_mois_2->setValue(DATA::mois_t2);
        ui->timeValue->setValue(DATA::time_P);
        ui->timeValueL->setValue(DATA::time_L);

}

configThreshold::~configThreshold()
{
    delete ui;
}

void configThreshold::on_btn_accept_clicked()
{

    DATA::temp_t=ui->dsb_Temp->value();
    //qDebug()<<DATA::temp_t;
    DATA::hump_t=ui->dsb_Humi->value();
    //qDebug()<<DATA::hump_t;
    DATA::lux_t=ui->dsb_Light->value();
    //qDebug()<<DATA::lux_t;
    DATA::mois_t=ui->dsb_mois->value();
    DATA::mois_t2=ui->dsb_mois_2->value();
    DATA::time_P=ui->timeValue->value();
    DATA::time_L=ui->timeValueL->value();
    QString filename = "./WSAN/thresol.txt";
    QFile file( filename );
    if (file.open(QIODevice::ReadWrite)){
        QTextStream stream(&file);
        stream << clearenv();
        stream << DATA::temp_t << endl;
        stream << DATA::hump_t << endl;
        stream << DATA::lux_t << endl;
        stream << DATA::mois_t << endl;
        stream << DATA::mois_t2 << endl;
        stream <<DATA::time_P<<endl;
        stream <<DATA::time_L;
    }
    this->close();
}

void configThreshold::on_pushButton_2_clicked()
{
    this ->close();
}
