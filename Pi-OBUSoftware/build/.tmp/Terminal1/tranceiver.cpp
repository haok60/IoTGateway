#include "tranceiver.h"
#include <QTime>
#include <QDebug>
#include "data.h"
#include "QDir"
#include "readfile.h"
#include <qmath.h>
#include <QImage>

Tranceiver::Tranceiver(QObject *parent) :
    QObject(parent)
{
    timer = new QTimer(this);
    timer->setInterval(1000);
	readfile x;
    PortSettings settings = {BAUD19200, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};
    port = new QextSerialPort(x.TRANCEIVER_PORT_DEFAULT, settings, QextSerialPort::Polling);
    enumerator = new QextSerialEnumerator(this);
    enumerator->setUpNotifications();
    connect(timer, SIGNAL(timeout()), SLOT(readData()));
    connect(port, SIGNAL(readyRead()), SLOT(readData()));
}

void Tranceiver::requestWork()
{
    emit workRequested();
}

void Tranceiver::doWork()
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

int Tranceiver::CheckCode(QString code)
{
    if(!code.compare("#RC")) return 1;
    if(!code.compare("#JN")) return 2;
    if(!code.compare("#RD")) return 3;
    if(!code.compare("#SC")) return 4;
    if(!code.compare("#SD")) return 5;
    if(!code.compare("#SN")) return 6;
    if(!code.compare("#AD")) return 7;
    if(!code.compare("#AS")) return 8;
    if(!code.compare("#RA")) return 1;
    return 0;
}

QString Tranceiver::getStatus(int num)
{
    switch(num)
    {
    case 0: return "Disable";
    case 1: return "Enable";
    case 2: return "Not Support";
    default: return "N/A";
    }
}

void Tranceiver::WriteAppend(QString FileName, QString Image)
{
    QString str, image;
    int hex;
    int len = Image.length()/2;
    for(int i=0; i < len; i++)
    {
        str = Image.mid(i*2, 2);
        bool ok;
        hex = str.toInt(&ok, 16);
        image += (char) hex;
    }
    QFile file(FileName);
    if(!file.open(QIODevice::Append|QIODevice::Truncate)) return;
    file.write(image.toLatin1());
    file.close();
}

void Tranceiver::WriteTextAppend(QString FileName, QString Text)
{
    QFile file(FileName);
    if(file.open(QIODevice::Append))
    {
        QTextStream stream(&file);
        stream << Text << endl;
    }
}

void Tranceiver::readData()
{
    readfile x;
    int t = port->bytesAvailable();
    if (t) {
        QString Code, Start, End, Image, my_Imgage;
        QByteArray ba = port->readAll();
        QString test(ba);
        WriteTextAppend(x.LOG_FILE,test + "------------------------------------------\n");
        char* tmp = ba.data();
        char line[1024];
        QString Line;
        int i;
        int j = 0;
        for(i=0;i<t;i++){
            if(tmp[i] == '\n'){
                line[j] = '\0';
                Line = QString::fromLocal8Bit(line);
                if(j > 1){
                    emit receivedData(Line);
                }
                WriteTextAppend(x.LOG_FILE, Line + "***************************************\n");
                //qDebug()<< "Line:  "<< Line;
                Code = Line.mid(0,3);
                switch(CheckCode(Code)){
                case 1: //Take photo
                    {
                        Start = Line.mid(16, 4);
                        End = Line.mid(j-5, 4);
                        if(!Start.compare("FFD8")){
                           DATA::img="";
                            QTime time;
                            QString t = time.currentTime().toString("_hh_mm_ss");
                            QDate date;
                            QString d = date.currentDate().toString("yyyy_MM_dd");
                            //DATA::time = d + t;
                            QDir dir(x.IMAGES_PATH + Line.mid(8,2));
                            if(!dir.exists())
                                dir.mkpath(".");
                            FileName = x.IMAGES_PATH + Line.mid(8,2) +"/" + d + t + ".jpg";
                        }
                        QString  mac=Line.mid(8,2);
                        QString time=QTime::currentTime().toString("hh-mm-ss");
                        time.append(QDate::currentDate().toString("yyyy/MM/dd"));
                        Image = Line.mid(16, j-16);
                        my_Imgage = Line.mid(16,j-17);
                        //qDebug() << my_Imgage;
                        WriteAppend(FileName,Image);
                        DATA::img += my_Imgage;
                        //QString data_web="http://tora1996.pythonanywhere.com/?img=";
                        //QString data_web="http://192.168.0.6:8000/get/?";
                        //http2= new QNetworkAccessManager(this);
                        //data_web.append(Line.mid(4,j-1));
                        //data_web.append(QString::number(temp));

                        emit ImageReceived(FileName);
                        if(!End.compare("FFD9")){
                            FileCompare=x.IMAGES_PATH + mac+"/oldImage.txt";
                            QFile file1(FileCompare);
                            file1.open(QIODevice::ReadWrite);
                            QTextStream in(&file1);
                            QImage pic1(in.readLine());
                            QImage pic2(FileName);
                            QString imax=DATA::img;
                            if(pic1!=pic2){
                                emit receiveCompletely(imax,mac);
                                in<<FileName;
                            }
                            else
                            file1.close();
                            //DATA::img="";
                            emit receivedData("Image Received Completely");

                        }
                        break;
                    }
                case 2: // Node Join
                {
                    QString mac = Line.mid(8,2);
                    if(!mac.compare("B1")) break;
                    else{
                        DATA::mac = mac;
                        bool ok;
                        int tmp = mac.toInt(&ok, 10);
                        QString address = Line.mid(4,4);
                        DATA::Ip = address;
                        //QString debug = mac + "," + address;
                        //emit receivedData(debug);
                        emit nodeJoin(tmp, address);
                        if(mac == "61" || mac == "62"){
                            delay(5);
                        }
                        break;
                    }
                }
            case 3:// Take temperature and humidity
                {
                    bool ok;
                    unsigned int td = Line.mid(10,4).toUInt(&ok, 16);
                    unsigned int rhd = Line.mid(14,4).toUInt(&ok, 16);
                    double temp = (double)(td*0.01 - 39.6);
                    double rh_lind = (double)(0.0367*rhd - 0.0000015955*rhd*rhd - 2.0468);
                    double humi = (double)((temp - 25)*(0.01 + 0.00008*rhd) + rh_lind);
                    int mac= Line.mid(8,2).toUInt(&ok);
                    if(humi > 100) humi = 100;
                    if(humi < 0) humi = 0;
                    QTime time;
                    QString t = time.currentTime().toString("hh-mm-ss");
                    QDate date;
                    QString d = date.currentDate().toString("dd/MM/yyyy");
                    QString tmp = Line.mid(8,2) + ":" + Line.mid(4,4) + ":" + QString::number(temp) + ":" + QString::number(humi);

//                    tmp = "\nThong tin nhiet do, do am tu sensor ";
//                    tmp += Line.mid(8,2);
//                    tmp += ", dia chi Ip ";
//                    tmp += Line.mid(4, 4);
//                    tmp += "\nNhiet do:        ";
//                    tmp += QString::number(temp);
//                    tmp += "\nDo am:           ";
//                    tmp += QString::number(humi);
//                    tmp += "\n";

                    DATA::temp= QString::number(temp);
                    DATA::hump= QString::number(humi);
                    emit tempAndHum(tmp);
                    emit sendTandH(mac,temp,humi);
                    emit TempHumi_t(mac,temp,humi);
                    QString data = d+":"+t+":"+Line.mid(8,2) + ":" + QString::number(temp) + ":" + QString::number(humi);
                    WriteTextAppend(x.HISTORY_FILE, data);
                    break;
                }
            case 4: // Sensor Status
                {
                    QString tmp,sta;
                    if(Line.count()<12) Line.insert(4, QString("0000"));
                    tmp += "\nXac nhan thong tin trang thai tu Sensor ";
                    tmp += Line.mid(8,2);
                    tmp += "\n";
                    int f,f1, f2, f3;
                    f = Line.mid(11,1).toInt();
                    switch(f)
                    {
                    case 0:
                        {
                        sta = "000";
                        break;
                    }
                    case 1:
                        {
                        sta = "001";
                        break;
                    }
                    case 2:
                        {
                        sta = "010";
                        break;
                    }
                    case 3:
                        {
                        sta = "011";
                        break;
                    }
                    case 4:
                        {
                        sta = "100";
                        break;
                    }
                    case 5:
                        {
                        sta = "101";
                        break;
                    }
                    case 6:
                        {
                        sta = "110";
                        break;
                    }
                    case 7:
                        {
                        sta = "111";
                        break;
                    }
                    default: break;
                    }
                    qDebug()<<sta;
                    f1 = sta.mid(2,1).toInt();
                    qDebug()<<f1;
                   // if(f1==1) f1=0;
                     //else if(f1==0) f1 = 1;
                    f2 = sta.mid(1,1).toInt();
                    qDebug()<<f2;
                   // if(f2==1) f2=0;
                    //   else if(f2==0) f2 = 1;
                    f3 = sta.mid(0,1).toInt();
                    qDebug()<<f3;
                  //  if(f3==1) f3=0;
                   //    else if(f3==0) f3 = 1;
                       qDebug() << "f1" << f1 << "f2" << f2 << "f3" << f3;
                    tmp += "   Chuc nang lay nhiet do, do am:   ";
                    tmp += getStatus(f1);
                    tmp += "\n";
                    tmp += "   Chuc nang chup anh:              ";
                    tmp += getStatus(f2);
                    tmp += "\n";
                    tmp += "   Chuc nang bao chay:              ";
                    tmp += getStatus(f3);
                    tmp += "\n\n";
                    emit receivedData(tmp);
                    FileData file(x.DATA_PATH);
                    int mac = Line.mid(8,2).toInt();
                    qDebug()<<mac;
                    QString line = file.searchByMacString(mac);
                    qDebug()<<line;
                    QStringList lst = line.split(",");
                    qDebug()<<lst;
                    tmp = lst[3] + lst[4] + lst[5];
                  //  if(tmp.compare(Line.mid(10,3)))
                    {
                        line = lst[0] + "," + lst[1] + "," + lst[2] + ",";
                        line += QString::number(f1) + "," + QString::number(f2) + "," + QString::number(f3)+","+lst[6];
                        //qDebug() << "line : " << line;
                        file.EditByMac(mac, line);
                    }
                    break;
                }
            case 5: // Function is disable
                {
                    QString tmp;
                    tmp = "Chuc nang vua yeu cau khong duoc ho tro hoac da bi vo hieu hoa tren Sensor ";
                    tmp += Line.mid(8,2);
                    tmp += "\n";
                    emit receivedData(tmp);
                    break;
                }
            case 6:
                {
                    DATA::mac = Line.mid(8,2);
                    DATA::Ip = Line.mid(4,4);
                    QString mac = Line.mid(8,2);
                    QTime time;
                    QString t = time.currentTime().toString("hh:mm:ss");
                    QDate date;
                    QString d = date.currentDate().toString("dd/MM/yyyy");
                    QString tmp = "Phat hien chuyen dong tai Node " + DATA::mac + ", dia chi Ip " + DATA::Ip + "vao luc " + t + ", ngay " + d + "\n";
                    //emit receivedData(tmp);
                    emit motionDetected(mac);
                }
                case 7:// Take temperature and humidity
                    {
                        bool ok;
                        unsigned int td = Line.mid(10,4).toUInt(&ok, 16);
                        unsigned int rhd = Line.mid(14,4).toUInt(&ok, 16);
                        double temp = (double)(td*0.01 - 39.6);
                        double rh_lind = (double)(0.0367*rhd - 0.0000015955*rhd*rhd - 2.0468);
                        double humi = (double)((temp - 25)*(0.01 + 0.00008*rhd) + rh_lind);
                        int mac= Line.mid(8,2).toUInt(&ok);
                        if(humi > 100) humi = 100;
                        if(humi < 0) humi = 0;
                        QTime time;
                        QString t = time.currentTime().toString("hh-mm-ss");
                        QDate date;
                        QString d = date.currentDate().toString("dd/MM/yyyy");
                        QString tmp = Line.mid(8,2) + ":" + Line.mid(4,4) + ":" + QString::number(temp) + ":" + QString::number(humi);
                        DATA::temp= QString::number(temp);
                        DATA::hump= QString::number(humi);
                        emit tempAndHum1(tmp);
                        emit sendTandH(mac,temp,humi);
                        //emit TempHumi_t(mac,temp,humi);
                        QString data = d+":"+t+":"+Line.mid(8,2) + ":" + QString::number(temp) + ":" + QString::number(humi);
                        WriteTextAppend(x.HISTORY_FILE, data);
                        break;
                    }
                case 8:// Take lux
                    {
                        bool ok;
                        unsigned char lsb = Line.mid(10,2).toUInt(&ok, 16);
                        unsigned char msb = Line.mid(12,2).toUInt(&ok, 16);
                        unsigned int exponent=lsb>>4;
                        qDebug()<<exponent;

                        unsigned int mantissa=((lsb&0x0F)<<4)|(msb&0x0F);
                                                qDebug()<<mantissa;
                        double lux=qPow(2,exponent)*mantissa*0.045;
                        //DATA::lux=QString::number(qPow(2,exponent)*mantissa*0.045);
//                        qDebug("xxxx:");
                        qDebug()<<lux;
                        int mac= Line.mid(8,2).toUInt(&ok);
                        QString tmp = Line.mid(8,2) + ":" + Line.mid(4,4) + ":" + QString::number(lux);
                        emit completeLux(tmp);
                        emit sendLux(mac,lux);
                        emit Lux_t(mac,lux);
//                        QString data = d+":"+t+":"+Line.mid(8,2) + ":" + QString::number(temp) + ":" + QString::number(humi);
//                        WriteTextAppend(x.HISTORY_FILE, data);
                        break;
                    }
            default: break;
                }
                j = 0;
            }
            else{
                line[j] = tmp[i];
                j++;
            }
        }
    }
}

void Tranceiver::writeData(QString cmd)
{
    int N = cmd.length();
    int hex_len = N/2;
    int hex_val;
    QString tmp;
    //qDebug() << N << cmd << endl;
    QByteArray ba;
    for(int i = 0; i < hex_len; i++)
    {
        tmp = cmd.mid(i*2, 2);
        bool ok;
        hex_val = tmp.toInt(&ok, 16);
        ba[i] = (char)hex_val;
        //qDebug() << hex_val << endl;
    }
    port->write(ba);
}

void Tranceiver::delay(int secondsToWait){
    QTime dieTime = QTime::currentTime().addSecs(secondsToWait);
    while(QTime::currentTime() < dieTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

