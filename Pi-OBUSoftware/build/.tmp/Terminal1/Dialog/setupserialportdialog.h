#ifndef SETUPSERIALPORTDIALOG_H
#define SETUPSERIALPORTDIALOG_H

#include <QDialog>

namespace Ui {
    class SetupSerialPortDialog;
}

class SetupSerialPortDialog : public QDialog {
    Q_OBJECT
public:
    SetupSerialPortDialog(QWidget *parent = 0);
    ~SetupSerialPortDialog();

protected:
    void changeEvent(QEvent *e);

private:
    void accept();

private:
    Ui::SetupSerialPortDialog *ui;
    QString m_organizationName, m_appName;

private slots:
    void on_btnRefresh_clicked();
};

#endif // SETUPSERIALPORTDIALOG_H
