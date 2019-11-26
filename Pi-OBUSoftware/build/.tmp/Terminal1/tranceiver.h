#ifndef TRANCEIVER_H
#define TRANCEIVER_H

#include <QObject>
#include <QTimer>
#include "qextserialenumerator.h"
#include "qextserialport.h"
#include "filedata.h"
#include "define.h"
#include <QStringList>
#include "dbmanager.h"
#include <QCoreApplication>

class Tranceiver : public QObject
{
Q_OBJECT
public:
    explicit Tranceiver(QObject *parent = 0);
    void requestWork();
    void writeData(QString);

signals:
    void receivedData(QString);
    void workRequested();
    void ImageReceived(QString);
    void nodeJoin(int, QString);
    void tempAndHum(QString);
    void tempAndHum1(QString);

    void TempHumi_t(int,double, double);
    void receiveCompletely(QString,QString);
    void motionDetected(QString);
    //nxt mqtt
    void sendTandH(int,double,double);
    void completeLux(QString);
    void sendLux(int,double);
    void Lux_t(int, double);
    //

public slots:
    void readData();
    void doWork();
public:
    QTimer *timer;
    QextSerialPort *port;
    QextSerialEnumerator *enumerator;

private:
    int CheckCode(QString);
    void WriteAppend(QString, QString);
    void WriteTextAppend(QString, QString);
    void delay(int secondsToWait);
    QString getStatus(int);
    QString FileName;
	QString FileCompare;


};

#endif // TRANCEIVER_H
