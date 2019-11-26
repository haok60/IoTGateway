#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QDialog>
#include "QAbstractSocket"
#include "QtNetwork"
#include "QHttp"

namespace Ui {
    class ServerDialog;
}

class ServerDialog : public QDialog {
    Q_OBJECT
public:
    explicit ServerDialog(QWidget *parent = 0);
    ~ServerDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ServerDialog *ui;
    QTcpSocket *socket;
    qint16 kichThuoc;
    QNetworkAccessManager *http;

public slots:
    void on_btnCancel_clicked();
    void on_btnSend_clicked();
    void loiSocket(QAbstractSocket::SocketError loi);
    void ketNoi();
    void replyFinished(QNetworkReply *reply);

private slots:
    void on_btnConnect_clicked();
};

#endif // SERVERDIALOG_H
