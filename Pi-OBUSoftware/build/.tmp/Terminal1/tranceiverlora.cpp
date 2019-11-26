#include "tranceiverlora.h"
#include "readfile.h"
tranceiverlora::tranceiverlora(QObject *parent):QObject(parent)
{
    timer = new QTimer(this);
    timer->setInterval(1000);
	readfile x;
    qDebug()<<x.LORA_PORT_DEFAULT;
    PortSettings settings = {BAUD9600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};
    port = new QextSerialPort(x.LORA_PORT_DEFAULT, settings, QextSerialPort::Polling);
    enumerator = new QextSerialEnumerator(this);
    enumerator->setUpNotifications();
    connect(timer, SIGNAL(timeout()), SLOT(readDataLR()));
    connect(port, SIGNAL(readyRead()), SLOT(readDataLR()));
}

void tranceiverlora::requestWorkLR()
{
    emit workRequestedLR();
}
void tranceiverlora::doWorkLR()
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

void tranceiverlora::WriteAppend(QString FileName, QString Image)
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

int tranceiverlora::CheckCodeLora(QString code)
{
    if(!code.compare("#LD")) return 1;
    if(!code.compare("#LA")) return 1;
    if(!code.compare("#L1")) return 4;
    if(!code.compare("#LJ")) return 3;
    if(!code.compare("#LR")) return 2;
    if(!code.compare("#LB")) return 2;
    if(!code.compare("#LS")) return 5;
    return 0;
}
void tranceiverlora::writeData(QString cmd)
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
        qDebug() << ba[i] << endl;
    }
    port->write(cmd.toLocal8Bit());
    //port->write(ba);

}

void tranceiverlora::WriteTextAppend(QString FileName, QString Text)
{
    QFile file(FileName);
    if(file.open(QIODevice::Append))
    {
        QTextStream stream(&file);
        stream << Text << endl;
    }
}
void tranceiverlora::readDataLR()
{
    readfile x;
    int t = port->bytesAvailable();
    if (t) {
        QString Code, Start, End, Image, my_Imgage;
        QByteArray ba = port->readAll();
        QString test(ba);
        //WriteTextAppend(x.LOG_FILE,test + "------------------------------------------\n");
        char* tmp = ba.data();
        char line[2048];
        QString Line;
        int i;
        int j = 0;
        for(i=0;i<t;i++){
            if(tmp[i] == '\n'){
                line[j] = '\0';
                Line = QString::fromLocal8Bit(line);
                if(j > 1){
                    emit receivedDataLR(Line);
                }
                //WriteTextAppend(x.LOG_FILE, Line + "***************************************\n");
                //qDebug()<< "Line:  "<< Line;
                Code = Line.mid(0,3);

                switch(CheckCodeLora(Code)){
                case 1:// Take temperature and humidity
                    {
                        bool ok;
//                        unsigned int td = Line.mid(5,4).toUInt(&ok, 16);
//                        unsigned int rhd = Line.mid(9,4).toUInt(&ok, 16);
//                        double temp = (double)(td*0.01 - 39.6);
//                        double rh_lind = (double)(0.0367*rhd - 0.0000015955*rhd*rhd - 2.0468);
//                        double humi = (double)((temp - 25)*(0.01 + 0.00008*rhd) + rh_lind);
//                        int mac= Line.mid(3,2).toUInt(&ok);
//                        if(humi > 100) humi = 100;
//                        if(humi < 0) humi = 0;
//                        QTime time;
//                        QString t = time.currentTime().toString("hh-mm-ss");
//                        QDate date;
//                        QString d = date.currentDate().toString("dd/MM/yyyy");
//                        QString tmp = Line.mid(3,2) + ":" + Line.mid(3,2) + ":" + QString::number(temp) + ":" + QString::number(humi);

//    //                    tmp = "\nThong tin nhiet do, do am tu sensor ";
//    //                    tmp += Line.mid(8,2);
//    //                    tmp += ", dia chi Ip ";
//    //                    tmp += Line.mid(4, 4);
//    //                    tmp += "\nNhiet do:        ";
//    //                    tmp += QString::number(temp);
//    //                    tmp += "\nDo am:           ";
//    //                    tmp += QString::number(humi);
//    //                    tmp += "\n";

//                        DATA::temp= QString::number(temp);
//                        DATA::hump= QString::number(humi);
//                        emit tempAndHum(tmp);
//                        emit sendTandH(mac,temp,humi);
//                        QString data = d+":"+t+":"+Line.mid(3,2) + ":" + QString::number(temp) + ":" + QString::number(humi);
//                        WriteTextAppend(x.HISTORY_FILE, data);
                        float mac=Line.mid(4,2).toInt(&ok,10);
                        float td=Line.mid(6,4).toFloat(&ok)/100;
                        float rhd=Line.mid(10).toFloat(&ok)/100;
                        QString tmp= QString::number(mac) +":" + QString::number(td) +":"+ QString::number(rhd);
//                        emit LRHTD(mac,td,rhd);
                        emit tempAndHum(tmp);
                        break;
                    }
                case 2://Take Soil Moisture
                    {
                        bool ok;
                        int Mois = Line.mid(6).toInt(&ok,16);
                        int mac = Line.mid(4,2).toInt(&ok,10);
                        QString tmp = Line.mid(5,2) + ":" + QString::number(Mois);
                        emit sendMois(mac,Mois);
                        emit completeMois(tmp);
						emit Mois_t(mac,Mois);
                        break;
                }
                case 3://node join
                {
                    bool ok;
                    QString mac = Line.mid(4,2);
                    DATA::mac = mac;
                    int tmp = mac.toInt(&ok, 10);
                    emit nodeJoinLR(tmp);
                    break;
                }
                case 4: //take dust
                {
                    bool ok;
                    int Dust_mesure = Line.mid(6,2).toInt(&ok,16);
                    int mac = Line.mid(4,2).toInt(&ok,10);
                    double Vo = (double)(5.00*Dust_mesure)/1024.00;
                    double dustDensity = (double)(Vo-0.6)*0.2*1000;
                    int wrc;
                    if(dustDensity<=15.4)wrc=1;
                    else if(dustDensity<=40.4)wrc=2;
                    else if(dustDensity<=65.4)wrc=3;
                    else if(dustDensity<=250.4)wrc=4;
                    else wrc=5;
                    if(wrc!=DATA::warningDust){
                        DATA::warningDust=wrc;
                        emit sendWarning(wrc);
                    }

                    QString tmp = mac + ":" + QString::number(dustDensity);
                    emit sendDust(mac,dustDensity);
                    emit completeDust(tmp);
                    qDebug()<<"dust mesure :"<<Dust_mesure;
                    //qDebug()<<Dust<<" : "<<mac;
                    break;
                }
                case 5:
                {
                    bool ok;
                    QString mac = Line.mid(4,2);
                    int status= Line.mid(6,2).toInt(&ok,10);
                    QString st;int time1;
                    switch (status) {
                    case 1:
                        st="On Light Complete";
                        DATA::onLight=true;
                        time1=DATA::time_L*60;
                        emit runTimerL(time1);
                        break;
                    case 2:
                        st="Off Light Complete";
                        DATA::onLight=false;
                        emit offL();
                        break;
                    case 3:{
                        st="On Pump Complete";
                        DATA::onPump=true;
                        time1=DATA::time_P*60;
                        qDebug()<<time1;
                        emit runTimerP(time1);
                        break;}
                    case 4:
                        st="Off Pump Complete";
                        DATA::onPump=false;
                        emit offP();
                        break;
                    default:
                        break;
                    }
                    QString tmp= "Node "+mac +":"+st;
                    emit completeST(tmp);
                    break;
                }
                default : break;
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



