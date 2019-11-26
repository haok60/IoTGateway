#ifndef EDITSENSORPLACEDIALOG_H
#define EDITSENSORPLACEDIALOG_H

#include <QDialog>

namespace Ui {
class EditSensorPlaceDialog;
}

class EditSensorPlaceDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditSensorPlaceDialog(QWidget *parent = 0);
    ~EditSensorPlaceDialog();

private:
    void accept();

private slots:
    void SetView(QString);
    
private:
    Ui::EditSensorPlaceDialog *ui;
};

#endif // EDITSENSORPLACEDIALOG_H
