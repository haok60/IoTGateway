#ifndef CONFIGTHRESHOLD_H
#define CONFIGTHRESHOLD_H

#include <QDialog>
#include "data.h"
#include <QFile>
#include <readfile.h>
namespace Ui {
class configThreshold;
}

class configThreshold : public QDialog
{
    Q_OBJECT

public:
    explicit configThreshold(QWidget *parent = 0);
    ~configThreshold();

private slots:
    void on_btn_accept_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::configThreshold *ui;
};

#endif // CONFIGTHRESHOLD_H
