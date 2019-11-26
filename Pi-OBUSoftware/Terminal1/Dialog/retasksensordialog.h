#ifndef RETASKSENSORDIALOG_H
#define RETASKSENSORDIALOG_H

#include <QDialog>
#include <QSettings>
#include "filedata.h"
#include "define.h"

namespace Ui {
    class RetaskSensorDialog;
}

class RetaskSensorDialog : public QDialog {
    Q_OBJECT
public:
    RetaskSensorDialog(QWidget *parent = 0);
    explicit RetaskSensorDialog(QString, QWidget *parent = 0);
    explicit RetaskSensorDialog(QString, QString , QWidget *parent = 0);
    ~RetaskSensorDialog();

protected:
    void changeEvent(QEvent *e);

private:
    QString getStatus(int);
    void SetView(QString);
    void accept();

private:
    QString m_organizationName, m_appName;
    int f1, f2, f3;
    Ui::RetaskSensorDialog *ui;

private slots:
    void on_cbxMac_currentIndexChanged(QString );
};

#endif // RETASKSENSORDIALOG_H
