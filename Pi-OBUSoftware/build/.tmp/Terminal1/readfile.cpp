#include "readfile.h"
#include "qdebug.h"
readfile::readfile()
{
    QFile File1(conf.DATA_SUPPORT);
    File1.open(QIODevice::ReadWrite);
    QTextStream in(&File1);
    this->IMAGES_PATH = in.readLine();
    this->DATA_PATH = in.readLine();
    this->GPS_FILE = in.readLine();
    this->HISTORY_FILE = in.readLine();
    this->LOG_FILE = in.readLine();
    this->TIME_DETECT = in.readLine();
    this->TRANCEIVER_PORT_DEFAULT = in.readLine();
    this->TRANCEIVER_BAUDRATE_DEFAULT = in.readLine().toInt();
    this->GPS_PORT_DEFAULT = in.readLine();
    this->GPS_BAUDRATE_DEFAULT = in.readLine().toInt();
    this->LORA_PORT_DEFAULT = in.readLine();
    this->LORA_BAUDRATE_DEFAULT = in.readLine().toInt();
    this->CONF_THRESOL = in.readLine();
//    this->hostMqtt = in.readLine();
//    this->portMqtt = in.readLine().toInt();
    File1.close();
//    QFile File(CONF_MQTT);
//    File.open(QIODevice::ReadWrite);
//    QTextStream in1(&File);
//    this->hostMqtt = in1.readLine();
//    this->portMqtt = in1.readLine().toInt();
//    File.close();
}

//void read_MQTT()
//{
//    QFile File(CONF_MQTT);
//    File.open(QIODevice::ReadWrite);
//    QTextStream in(&File);
//    this->hostMqtt = in.readLine();
//    this->portMqtt = in.readLine().toInt();
//    File.close();
//}
//void readfile::read()
//{
//    this->IMAGES_PATH = "a";
//    DATA::DATA_PATH = "b";
//    DATA::GPS_FILE = "c";
//    DATA::HISTORY_FILE = "d";
//    DATA::LOG_FILE = "e";
//    DATA::TIME_DETECT = "f";
//    DATA::TRANCEIVER_PORT_DEFAULT = "g";
//    DATA::TRANCEIVER_BAUDRATE_DEFAULT = 1;
//    DATA::GPS_PORT_DEFAULT = "h";
//    DATA::GPS_BAUDRATE_DEFAULT = 2;
//    DATA::hostMqtt = "i";
//    DATA::portMqtt = 3;

//}

