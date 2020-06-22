#include "tranceiverlora.h"
#include "readfile.h"
#include "dbmanager.h"
tranceiverlora::tranceiverlora(QObject *parent):QObject(parent)
{
    timer = new QTimer(this);
    timer->setInterval(1000);
	readfile x;
    //qDebug()<<x.LORA_PORT_DEFAULT;
    PortSettings settings = {BAUD9600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};
    port = new QextSerialPort("ttyUSB0", settings, QextSerialPort::Polling);
    enumerator = new QextSerialEnumerator(this);
    //enumerator->setUpNotifications();
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
    if(!code.compare("#LE")) return 2;
    if(!code.compare("#LJ")) return 3;
    if(!code.compare("#LR")) return 4;
    if(!code.compare("#LB")) return 4;
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
    //static float Voc=0.6;
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
                        int td = Line.mid(6,4).toInt(&ok,16);
                        int hd = Line.mid(10,4).toInt(&ok,16);
                        int mac = Line.mid(4,2).toInt(&ok,10);
                        double temp = (double)td/100.00;
                        double humi = (double)hd/100.00;
                        QString tmp= QString::number(mac) +":" + QString::number(temp) +":"+ QString::number(humi);

                        emit sendTemp(mac,temp,"temperature");
                        emit sendHumi(mac,humi,"humidity");
                        emit tempAndHum(tmp);
                        //DbManager db;
                        //emit insertdata(mac,dustDensity1,"dust");
                        //bool a = db.insertdata(mac,dustDensity1,"dust");
                        //qDebug()<<a;
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
                        emit insertdata(mac,Mois,"moisture");
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
                    qDebug()<<"dust mesure :"<<Dust_mesure;
//                    if(Vo<Voc)
//                    {
//                        Voc = Vo;
//                        break;
//                    }
                    double dustDensity = (double)(Vo)*0.2*1000;
                    double dustDensity1 = ((int)(dustDensity * 100 + .5) / 100.0);;
//                    int wrc;
//                    if(dustDensity<=15.4)wrc=1;
//                    else if(dustDensity<=40.4)wrc=2;
//                    else if(dustDensity<=65.4)wrc=3;
//                    else if(dustDensity<=250.4)wrc=4;
//                    else wrc=5;
//                    if(wrc!=DATA::warningDust){
//                        DATA::warningDust=wrc;
//                        emit sendWarning(wrc);
//                    }

                    QString tmp = Line.mid(4,2) + ":" + QString::number(dustDensity1);
                    emit sendDust(mac,dustDensity1);
                    emit completeDust(tmp);
                    DbManager db;
                    //emit insertdata(mac,dustDensity1,"dust");
                    bool a = db.insertdata(mac,dustDensity1,"dust");
                    qDebug()<<a;
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
                        emit runTimerL((int)time1);
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
                        emit runTimerP((int)time1);
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



