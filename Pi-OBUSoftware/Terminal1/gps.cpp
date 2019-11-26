#include "gps.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include "data.h"
#include "math.h"
#include "QDebug"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "readfile.h"

double initLat=21.005739;
double initLng=105.842308;
double lat=initLat,lng=initLng;
int cnt=0;

GPS::GPS(QObject *parent) :
    QObject(parent)
{
    timer = new QTimer(this);
    timer->setInterval(500);

    PortSettings settings = {BAUD9600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};
    port = new QextSerialPort("ttyUSB0", settings, QextSerialPort::Polling);

    enumerator = new QextSerialEnumerator(this);
    enumerator->setUpNotifications();
    connect(timer, SIGNAL(timeout()), SLOT(readData()));
    connect(port, SIGNAL(readyRead()), SLOT(readData()));
}

void GPS::readData()
{
    readfile x;
       if (port->bytesAvailable()) {
        QByteArray ba = port->readLine();
        QString Line(ba);
        QStringList list = Line.split(",");
        if(!list.value(0).compare("$GPRMC"))
        {
            if(!list.value(3).isEmpty() && !list.value(5).isEmpty())
            {
                QString Lat = list.value(3);
                QString Lng = list.value(5);
                int Nlat = Lat.length();
                int Nlng = Lng.length();
                QString tmp1 = Lat.mid(0, Nlat - 7);
                QString tmp2 = Lat.mid(Nlat - 7, 7);
                double lat = tmp1.toDouble() + tmp2.toDouble()/60;
                tmp1 = Lng.mid(0, Nlng - 7);
                tmp2 = Lng.mid(Nlng - 7, 7);
                double lng = tmp1.toDouble() + tmp2.toDouble()/60;
                QString location = QString::number(lat, 'f', 6) + "," + QString::number(lng,'f', 6);
                DATA::lat = QString::number(lat, 'f', 6);
                DATA::lng = QString::number(lng,'f', 6);
                if(DATA::gps.isEmpty()){
                    WriteTextAppend(x.GPS_FILE, location);
                    //qDebug() << location;
                }
                else {
                    QStringList tmp = DATA::gps.split(",");
                    QString pre_lat = tmp.value(0);
                    QString pre_lng = tmp.value(1);
                    if( (fabs(lat - pre_lat.toDouble()) >= 0.000002) || (fabs(lng - pre_lng.toDouble()) >= 0.000002) )
                    {
                        WriteTextAppend(x.GPS_FILE, location);
                    }
                }
                DATA::gps = location;
                emit receivedData(location);
            }
        }
    }
}

void GPS::requestWork()
{
    emit workRequested();
}

void GPS::close()
{
    port->close();
}

void GPS::open()
{
    port->open(QIODevice::ReadWrite);
}

void GPS::doWork()
{
    if(!port->isOpen())
    {
        port->open(QIODevice::ReadWrite);
    }
    if (port->isOpen() && port->queryMode() == QextSerialPort::Polling)
        timer->start();
    else
        timer->stop();
}

void GPS::WriteTextAppend(QString FileName, QString Text)
{
    QFile file(FileName);
    if(file.open(QIODevice::Append))
    {
        QTextStream stream(&file);
        stream << Text << endl;
    }
}
