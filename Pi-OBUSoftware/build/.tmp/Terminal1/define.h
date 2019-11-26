#ifndef DEFINE_H
#define DEFINE_H

//#define DATA_SUPPORT "/home/nghiemdinhhao/Desktop/WSAN1/Pi-OBUSoftware/WSAN/support.txt"
//#define CONF_MQTT "/home/nghiemdinhhao/Desktop/WSAN1/Pi-OBUSoftware/WSAN/confMQTT.txt"

#define NOFFUNC 3
#define NOSENSOR 5

#define TAKE_TEMP_AND_HUM 0
#define TAKE_PHOTO 1
#define REQUEST_STATUS 2
#define RETASK 3
#include <qstring.h>
#include <QDir>
class define
{
public:
    define();
    QString DATA_SUPPORT;
    QString CONF_MQTT;
};
#endif // DEFINE_H
