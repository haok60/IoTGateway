#ifndef TRANCEIVERLORA_H
#define TRANCEIVERLORA_H
#include <QObject>
#include <QTimer>
#include "qextserialenumerator.h"
#include "qextserialport.h"
#include "filedata.h"
#include "define.h"
#include <QStringList>
#include <QDebug>
#include "data.h"
#include "QDir"
#include <QTime>
#include <readfile.h>

class tranceiverlora : public QObject
{ Q_OBJECT
public:
   explicit tranceiverlora(QObject *parent = 0);
    void requestWorkLR();
    void writeData(QString);


signals:
    void receivedDataLR(QString);
    void workRequestedLR();
    void ImageReceived(QString);
    void nodeJoinLR(int);
    void tempAndHum(QString);
    void tempAndHum1(QString);

    void receiveCompletely(QString,QString);
    void motionDetected(QString);
    //nxt mqtt
    void sendTandH(int,double,double);
    void completeLux(QString);
    void sendLux(int,double);
    void sendMois(int,int);
    void completeMois(QString);
    void sendDust(int, double);
    void completeDust(QString);
    void sendWarning(int);
    void Mois_t(int,double);
    void completeST(QString);
    void runTimerP(int);
    void runTimerL(int);
    void offP();
    void offL();
    void LRHTD(int,int,int);
    //

public slots:
    void readDataLR();
    void doWorkLR();
public:
    QTimer *timer;
    QextSerialPort *port;
    QextSerialEnumerator *enumerator;

private:
    int CheckCodeLora(QString);
    void WriteAppend(QString, QString);
    void WriteTextAppend(QString, QString);
    void delay(int secondsToWait);
    QString getStatus(int);
    QString FileName;

};

#endif // TRANCEIVERLORA_H
