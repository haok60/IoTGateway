#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include "define.h"

class Sensor : public QObject
{
Q_OBJECT
public:
    explicit Sensor(int, QObject *parent = 0);

public:
    int mac;
    QString ip;
    int func[NOFFUNC];
    bool isJoin;
    QString lat, lng;
    int markerIndex;
    double x0, y0;
    Sensor *clusterHead;
    double cur_temp;
};

#endif // SENSOR_H
