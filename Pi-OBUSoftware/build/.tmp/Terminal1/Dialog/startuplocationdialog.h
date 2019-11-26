#ifndef STARTUPLOCATIONDIALOG_H
#define STARTUPLOCATIONDIALOG_H

#include <QDialog>

namespace Ui {
class StartupLocationDialog;
}

class StartupLocationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit StartupLocationDialog(QWidget *parent = 0);
    ~StartupLocationDialog();

private:
    void accept();
    
private:
    Ui::StartupLocationDialog *ui;
    QString m_organizationName, m_appName;
};

#endif // STARTUPLOCATIONDIALOG_H
