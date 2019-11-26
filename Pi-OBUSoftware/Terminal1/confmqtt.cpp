#include "confmqtt.h"

confmqtt::confmqtt()
{
        QFile File(conf.CONF_MQTT);
        File.open(QIODevice::ReadWrite);
        QTextStream in(&File);
        this->hostMqtt = in.readLine();
        this->portMqtt = in.readLine().toInt();
        this->topic1 = in.readLine();
        this->topic2 = in.readLine();
        this->accessToken= in.readLine();
        File.close();
}

