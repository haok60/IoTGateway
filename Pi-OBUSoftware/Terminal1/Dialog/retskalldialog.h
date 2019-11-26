#ifndef RETSKALLDIALOG_H
#define RETSKALLDIALOG_H

#include <QDialog>

namespace Ui {
class RetskAllDialog;
}

class RetskAllDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit RetskAllDialog(QWidget *parent = 0);
    ~RetskAllDialog();

private:
    void accept();
    
private:
    Ui::RetskAllDialog *ui;
    QString m_organizationName, m_appName;
};

#endif // RETSKALLDIALOG_H
