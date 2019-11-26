#ifndef NEWSENSORDIALOG_H
#define NEWSENSORDIALOG_H

#include <QDialog>

namespace Ui {
class NewSensorDialog;
}

class NewSensorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewSensorDialog(QWidget *parent = 0);
    ~NewSensorDialog();

private:
    void accept();
    
private:
    Ui::NewSensorDialog *ui;
};

#endif // NEWSENSORDIALOG_H
