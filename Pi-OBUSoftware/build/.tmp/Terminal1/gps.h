#ifndef GPS_H
#define GPS_H

#include <QObject>
#include <QTimer>
#include "qextserialenumerator.h"
#include "qextserialport.h"
#include "define.h"

class GPS : public QObject
{
    Q_OBJECT
public:
    explicit GPS(QObject *parent = 0);
    void requestWork();
    void close();
    void open();
    
signals:
    void receivedData(QString);
    void workRequested();
    
public slots:
    void readData();
    void doWork();

public:
    QTimer *timer;
    QextSerialPort *port;
    QextSerialEnumerator *enumerator;

private:
    void WriteTextAppend(QString, QString);
    
};

#endif // GPS_H
