#ifndef READFILE_H
#define READFILE_H
#include "define.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
class readfile
{
public:
    readfile();
    QString IMAGES_PATH;
    QString DATA_PATH;
    QString GPS_FILE;
    QString HISTORY_FILE;
    QString LOG_FILE;
    QString TIME_DETECT;
    QString TRANCEIVER_PORT_DEFAULT;
    int TRANCEIVER_BAUDRATE_DEFAULT;
    QString LORA_PORT_DEFAULT;
    int LORA_BAUDRATE_DEFAULT;
    QString GPS_PORT_DEFAULT;
    int GPS_BAUDRATE_DEFAULT;
    define conf;
    QString CONF_THRESOL;
//    QString hostMqtt;
//    int portMqtt;


    //void read();
};

#endif // READFILE_H
