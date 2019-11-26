#include "sensor.h"
#include "filedata.h"
#include "readfile.h"

#include <QString>
#include <QTextStream>
#include <QStringList>

Sensor::Sensor(int m, QObject *parent) : QObject(parent), mac(m){
    readfile x;
    isJoin = false;
    FileData data(x.DATA_PATH);
    QString line = data.searchByMac(mac);
    QStringList list = line.split(",");
    lat = list.value(1);
    lng = list.value(2);
    for(int i = 0; i < NOFFUNC; i++)
    {
        func[i] = list.value(i+3).toInt();
    }
    cur_temp = 0;
}
