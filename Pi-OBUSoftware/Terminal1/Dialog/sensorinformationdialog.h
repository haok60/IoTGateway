#ifndef SENSORINFORMATIONDIALOG_H
#define SENSORINFORMATIONDIALOG_H

#include <QDialog>

namespace Ui {
class SensorInformationDialog;
}

class SensorInformationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SensorInformationDialog(QWidget *parent = 0);
    explicit SensorInformationDialog(int mac, QWidget *parent = 0);
    ~SensorInformationDialog();

private:
    QString getStatus(int);

private slots:
    void SetView(QString);
    
    void on_btnClose_clicked();

private:
    Ui::SensorInformationDialog *ui;
    QString startSensor;
};

#endif // SENSORINFORMATIONDIALOG_H
