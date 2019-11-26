#ifndef CONFMQTT_H
#define CONFMQTT_H
#include "define.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QByteArray>

class confmqtt
{
public:
    confmqtt();
    QString hostMqtt;
    int portMqtt;
    QString topic1;
    QString topic2;
    QString accessToken;
    define conf;

};

#endif // CONFMQTT_H
