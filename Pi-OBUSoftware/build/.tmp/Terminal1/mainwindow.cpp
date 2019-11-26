#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QDebug>
#include <QtWebKit>
#include <QThread>
#include <QFile>
#include <QTime>
#include "filedata.h"
#include <QFileDialog>
#include "data.h"
#include "math.h"
#include "QDir"
#include "QCoreApplication"
#include "QEventLoop"
#include "QPrintDialog"
#include "QPrinter"
#include "QTextCursor"
#include "qtmosq.h"
#include "readfile.h"
#include "confmqtt.h"
//#include <wiringPi.h>

//class WebPage : public QWebPage
//{
//    public:  WebPage(QObject * p = 0) : QWebPage(p) {}
//    private: QString userAgentForUrl(const QUrl&) const { return "Chrome/1.0"; }
//};
confmqtt xx;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    joinedMac = new int[20];
    joinedAddress = new QString[20];
    indexJoined = 0;
    http1 = new QNetworkAccessManager(this);
    console = new Console;
    console->setEnabled(true);
    console->setLocalEchoEnabled(true);
    ui->layConsole->addWidget(console);
//	setenv("WIRINGPI_GPIOMEM","1",1);
//	wiringPiSetup();
//	pinMode(0,OUTPUT);
//	pinMode(2,OUTPUT);
//	digitalWrite(0,LOW);
//	digitalWrite(2,LOW);
    led = new HLed();
    led->turnOff();
//    QString pic_path=QDir::currentPath().toAscii()+"/logo/logo.jpg";
//    QPixmap pix(pic_path);
//    ui->lb_pic->setPixmap(pix);

//    ui->layLed->addWidget(led);
    //display time run
    ui->runL->hide();
    ui->runP->hide();
    ui->countdowL->hide();
    ui->countdowP->hide();
    //
    timerP = new QTimer();
    timerL = new QTimer();
    //init Data
    hash["62"] = "05";
    hash["61"] = "08";
    d1 = 20, d2 =20;
    receivedFlag = false;
    //nxt cmt
//    connect(this,SIGNAL(readySend()),SLOT(sendtoWeb()));
    //connect(this,SIGNAL(readySend()),SLOT(sendMqtt()));

    // GPS
    gps = new GPS();
    gpsStarted = false;
    gpsDataReceived = false;
    thread_gps = new QThread();

    gps->moveToThread(thread_gps);
    connect(gps, SIGNAL(workRequested()), thread_gps, SLOT(start()));
    connect(thread_gps, SIGNAL(started()), gps, SLOT(doWork()));
    connect(gps, SIGNAL(receivedData(QString)), SLOT(onGpsData(QString)));

    // Tranceiver
    tranceiver = new Tranceiver();
    tranceiverStarted = false;
    thread_tranceiver = new QThread();
    tranceiver->moveToThread(thread_tranceiver);
    connect(tranceiver, SIGNAL(workRequested()), thread_tranceiver, SLOT(start()));
    connect(thread_tranceiver, SIGNAL(started()), tranceiver, SLOT(doWork()));
    connect(tranceiver, SIGNAL(receivedData(QString)), SLOT(onTranceiverData(QString)));
    connect(tranceiver, SIGNAL(receiveCompletely(QString,QString)), this, SLOT(sendImageToWeb(QString,QString)));
    connect(tranceiver, SIGNAL(nodeJoin(int, QString)), SLOT(onNodeJoin(int, QString)));
    connect(tranceiver, SIGNAL(ImageReceived(QString)), SLOT(onImageReceived(QString)));
    connect(ui->btnOpenClose, SIGNAL(clicked()), SLOT(onOpenCloseButtonClicked()));
    connect(tranceiver, SIGNAL(tempAndHum(QString)), SLOT(onTempAndHum(QString)));
    connect(tranceiver, SIGNAL(tempAndHum1(QString)), SLOT(onTempAndHum1(QString)));
    connect(tranceiver,SIGNAL(sendTandH(int,double,double)),SLOT(SendAITH(int,double,double)));
    connect(tranceiver, SIGNAL(completeLux(QString)), SLOT(oncompleteLux(QString)));
    connect(tranceiver,SIGNAL(sendLux(int,double)),SLOT(SendAILUX(int,double)));
    connect(tranceiver,SIGNAL(TempHumi_t(int,double,double)),SLOT(onTempHumi(int,double,double)));
    connect(tranceiver,SIGNAL(Lux_t(int,double)),SLOT(onLux_t(int,double)));
    //sendMqttData
    //Lora
    lora = new tranceiverlora();
    loraStarted =false;
    thread_lora =new QThread();
    lora->moveToThread(thread_lora);
    connect(lora, SIGNAL(workRequestedLR()), thread_lora, SLOT(start()));
    connect(thread_lora,SIGNAL(started()),lora,SLOT(doWorkLR()));
    connect(lora, SIGNAL(receivedDataLR(QString)), SLOT(onreceivedDataLR(QString)));
    //connect(lora, SIGNAL(receivedDataLR(QString)), SLOT(onTranceiverDataLI(QString)));
    connect(lora, SIGNAL(tempAndHum(QString)), SLOT(onTempAndHumLR(QString)));
    //connect(lora, SIGNAL(sendTandH(int,double,double)), SLOT(sendMqttTandHLR(int,double,double)));
    connect(lora, SIGNAL(sendMois(int,int)), SLOT(SendAIMois(int,int)));
    connect(lora, SIGNAL(completeMois(QString)), SLOT(oncompleteMois(QString)));
    connect(lora,SIGNAL(nodeJoinLR(int)),SLOT(onNodeJoinLR(int)));
    connect(lora,SIGNAL(completeDust(QString)), SLOT(oncompleteDust(QString)));
    connect(lora,SIGNAL(sendDust(int,double)),SLOT(SendAIDD(int,double)));
    connect(lora,SIGNAL(sendWarning(int)),SLOT(SendWarningDust(int)));
    connect(lora,SIGNAL(Mois_t(int,double)),SLOT(onMois_t(int,double)));
    connect(lora,SIGNAL(completeST(QString)),SLOT(onST(QString)));
    connect(lora,SIGNAL(runTimerL(int)),SLOT(onrunTimerL(int)));
    connect(lora,SIGNAL(runTimerP(int)),SLOT(onrunTimerP(int)));
    connect(lora,SIGNAL(offL()),SLOT(onoffL()));
    connect(lora,SIGNAL(offP()),SLOT(onoffP()));
//    connect(lora,SIGNAL(LRHTD(int,int,int)),SLOT(onLRHTD(int,int,int));
    initMap(true);

    connect(ui->actionLinphone, SIGNAL(triggered()), SLOT(startLinphone()));
    connect(ui->actionQuit, SIGNAL(triggered()), SLOT(close()));
    connect(ui->actionAbout_2, SIGNAL(triggered()), SLOT(ShowAbout()));
    connect(ui->actionRetask_One, SIGNAL(triggered()), SLOT(RetaskOne()));
    connect(ui->actionRetask_All, SIGNAL(triggered()), SLOT(RetaskAll()));
    connect(ui->actionNew, SIGNAL(triggered()), SLOT(AddNewSensor()));
    connect(ui->actionEdit_Place, SIGNAL(triggered()), SLOT(EditSensorPlace()));
    connect(ui->actionInformation, SIGNAL(triggered()), SLOT(ShowSensorInformation()));
    connect(ui->actionStartup_Location_Map, SIGNAL(triggered()), SLOT(StartupLocation()));
    connect(ui->actionSerial_Port, SIGNAL(triggered()), SLOT(SetupSerialPort()));
    connect(ui->actionServer, SIGNAL(triggered()), SLOT(SendToServer()));

    //connect(ui->bt_Broadcast, SIGNAL(clicked()), SLOT(sendBroadcast()));
    //nxt cmt
    //timer on Pump and Light

    connect(timerP, SIGNAL(timeout()), this, SLOT(oncountdownP()));

    connect(timerL, SIGNAL(timeout()), this, SLOT(oncountdownL()));
    //
    //connect(ui->bt_Broadcast, SIGNAL(clicked()), SLOT(sendtoWeb()));

    //connect(ui->btnSendLora, SIGNAL(clicked()), this, SLOT(onCommandLR()));

    setWindowTitle(tr("Gateway IOT "));

    //SetupSerialPort(); //Open dialog config Port cho Emboard va GPS khi mois chay chuong trinh
    //populateJavaScriptWindowObject();
    setDate();

    //<Chinh sua code cho UAV>

    /*
     * thiet dat thoi gian time_out cho UAV gui lenh lay du lieu
     */

   // int time_out = 30000;
    //fileName = "/home/lab411/Desktop/LogfileUAV/logfile_" + QDate::currentDate().toString() + "_" + QTime::currentTime().toString();
    AlwaysOpenPort();
    AlwaysOpenPortLR();
    SetupPortSerial();

//    </Chinh sua code cho UAV>
    lib_init();
    mqttConnect();
    qDebug()<<"okoko";
}
// load output.txt

void MainWindow::onrunTimerL(int time){   \
    timerL->start(1000);
    sTimeL=time;
    ui->runL->show();
    ui->countdowL->show();

}
void MainWindow::onrunTimerP(int time){   \
    timerP->start(1000);
    sTimeP=time;
    ui->runP->show();
    ui->countdowP->show();
}
void MainWindow::oncountdownP(){
    sTimeP--;
    if (sTimeP==0) // countdown has finished
    {
        timerP->stop();
        onLR(90,4);
        ui->runP->hide();
        ui->countdowP->hide();
    }
    else {
        int hour=sTimeP/3600;
        int minute=(sTimeP%3600)/60;
        int second =(sTimeP%3600)%60;
        QString display = QString::number(hour)+":"+QString::number(minute)+":"+QString::number(second);
        ui->countdowP->setText(display);
    }

}
void MainWindow::oncountdownL(){
    sTimeL--;
    if (sTimeL==0) // countdown has finished
    {
        timerL->stop();
        onLR(90,2);
        ui->runL->hide();
        ui->countdowL->hide();
        //ui->label_clock->hide();
    }
    else {
        int hour=sTimeL/3600;
        int minute=(sTimeL%3600)/60;
        int second =(sTimeL%3600)%60;
        QString display = QString::number(hour)+":"+QString::number(minute)+":"+QString::number(second);
        ui->countdowL->setText(display);
    }
}
void MainWindow::onoffL(){
    qDebug()<<"off";
    timerL->stop();
    //onLR(90,2);
    ui->runL->hide();
    ui->countdowL->hide();
}
void MainWindow::onoffP(){
    timerP->stop();
//    onLR(90,2);
    ui->runP->hide();
    ui->countdowP->hide();
}

/*
 * Ham ghi du lieu thu thap duoc vao file txt. Luu o thu muc ~/Desktop/LogfileUAV
 * Duoc su dung tai cac ham onNodeJoin, onTempAndHum, ~MainWindow
 *
 */
void MainWindow::WriteDatatoLogfile(QString data)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream out(&file);
    out<<data;
    file.close();
}

MainWindow::~MainWindow()
{
    //khi dong chuong trinh. Ket thuc ghi file
    //WriteDatatoLogfile("\n---------------End File----------");
    mosq->mosquittopp::disconnect();
    mosq->loop_stop();
    lib_cleanup();
    delete timerL;
    delete timerP;
    delete mosq;
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/* nxt code
 * auto connect mqtt
 *
*/
void MainWindow::mqttConnect(){
    //confmqtt x;
    char* s,*access;
    QByteArray ba=xx.hostMqtt.toLatin1();
    s = ba.data();
    ba=xx.accessToken.toLatin1();
    access=ba.data();
    //qDebug()<<x.hostMqtt;
   // qDebug()<<"mqtt!!"<<endl;
    mosq=new qtmosq();
    //thingsboard
//    mosq->username_pw_set("vFxbwpQ04fzVqrxnxihI",NULL);

    //mqttcloud
    //qDebug(x.accessToken.toAscii());
//    qDebug(x.hostMqtt.toLatin1());
//    qDebug()<<x.topic1;
    mosq->username_pw_set(access);

    connect (mosq, SIGNAL(connected()), this, SLOT(connectEnabled()));
    mosq->connect_async(s,xx.portMqtt);
    mosq->loop_start();
    //qDebug() <<s;
    //qDebug()<<"end";
}
void MainWindow::connectEnabled(){
    console->insertPlainText("connect to MQTT !!");
}
void MainWindow::sendMqtt(){
//    confmqtt x;
    QByteArray topic = xx.topic1.toAscii();
    QString payload = "{";
//    payload += "\"serialNumber\":\""; payload += serialNumber; payload += "\",";
//    payload += "\"temperature\":"; payload += temperature; payload += ",";
//    payload += "\"model\":\""; payload += model;
    payload += "\"}";
    QByteArray datasend=payload.toLocal8Bit();
    mosq->publish(mosq->getMID(),topic.data(),datasend.size(),datasend.data(),2,false);
    console->insertPlainText("sent data to server!!");
}
void MainWindow::sendMqttData(int mac,double data,QString type)
{
    QString model="T1000";
    QString name="P1-SN-0";
    name.append(QString::number(mac));
    //qDebug()<<name;
    //nxt sua
    QDateTime current = QDateTime::currentDateTime();
    uint timestame = current.toTime_t();
   // qDebug()<<timestame;
    QString payload = "{\"";
    payload +=name;
    payload +="\": [{\"ts\":";
    payload +=QString::number(timestame);payload+="000,\"values\":";
    payload += "{\""+ type+ "\":";
    payload += QString::number(data);
//    payload += "\"threshold_soil-moisture\":"; payload += QString::number(DATA::mois_t);
    payload += "}}]}";
    qDebug()<<payload<<endl;
    QByteArray datasend=payload.toLocal8Bit();
    QByteArray topic= xx.topic2.toAscii();
    mosq->publish(mosq->getMID(),topic.data(),datasend.size(),datasend.data(),2,false);
    console->insertPlainText("Sent data to the server!!! \r\n");
}
void MainWindow::sendMqttDataSaved(QString time, int mac,double data,QString type)
{
    QString model="T1000";
    QString name="P1-SN-0";
    name.append(QString::number(mac));
    //qDebug()<<name;
    //nxt sua
    QDateTime current = QDateTime::currentDateTime();
    uint timestame = current.toTime_t();
   // qDebug()<<timestame;
    QString payload = "{\"";
    payload +=name;
    payload +="\": [{\"ts\":";
    payload +=time;payload+="000,\"values\":";
    payload += "{\""+ type+ "\":";
    payload += QString::number(data);
//    payload += "\"threshold_soil-moisture\":"; payload += QString::number(DATA::mois_t);
    payload += "}}]}";
    qDebug()<<payload<<endl;
    QByteArray datasend=payload.toLocal8Bit();
    QByteArray topic= xx.topic2.toAscii();
    mosq->publish(mosq->getMID(),topic.data(),datasend.size(),datasend.data(),2,false);
    console->insertPlainText("Sent data to the server!!! \r\n");
}
//void MainWindow::sendMqttMois(int mac, int mois)
//{
//    QString model="T1000";
//    QString name="P1-SN-0";
//    name.append(QString::number(mac));
//    //qDebug()<<name;
//    //nxt sua
//    QDateTime current = QDateTime::currentDateTime();
//    uint timestame = current.toTime_t();
//   // qDebug()<<timestame;
//    QString payload = "{\"";
//    payload +=name;
//    payload +="\": [{\"ts\":";
//    payload +=QString::number(timestame);payload+="000,\"values\":";
//    payload += "{\"soil moisture\":"; payload += QString::number(mois); payload +=",";
//    payload += "\"threshold_soil-moisture\":"; payload += QString::number(DATA::mois_t);
//    payload += "}}]}";
//    qDebug()<<payload<<endl;
//    QByteArray datasend=payload.toLocal8Bit();
//    QByteArray topic= xx.topic2.toAscii();
//    mosq->publish(mosq->getMID(),topic.data(),datasend.size(),datasend.data(),2,false);
//    console->insertPlainText("Sent soil moisture data to the server!!! \r\n");

//}
//void MainWindow::sendMqttTandHLR(int mac,double temp,double humi)
//{
////    confmqtt x;
//    QString model="T1000";
//    QString name="P1-SN-0";
//    name.append(QString::number(mac));
//    //qDebug()<<name;
//    //nxt sua
//    QDateTime current = QDateTime::currentDateTime();
//    uint timestame = current.toTime_t();
//   // qDebug()<<timestame;
//    QString payload = "{\"";
//    payload +=name;
//    payload +="\": [{\"ts\":";
//    payload +=QString::number(timestame);payload+="000,\"values\":";
//    payload += "{\"temperature\":"; payload += QString::number(temp); payload += ",";
//    payload += "\"threshold_temperature\":"; payload +=QString::number(DATA::temp_t); payload +=",";
//    payload += "\"humidity\":"; payload += QString::number(humi); payload +=",";
//    payload += "\"threshold_humidity\":"; payload +=QString::number(DATA::hump_t);
//    payload += "}}]}";

///*using tb-gateway*/
////    QString payload="{";
////        payload += "\"serialNumber\":\""; payload +=name ; payload += "\",";
////        payload += "\"temperature\":"; payload += QString::number(temp); payload += ",";
////        payload += "\"humidity\":"; payload += QString::number(humi); payload += ",";
////        payload += "\"model\":\""; payload += model;
////    payload+="\"}";

//    qDebug()<<payload<<endl;
//    QByteArray datasend=payload.toLocal8Bit();
//    QByteArray topic= xx.topic2.toAscii();
//    mosq->publish(mosq->getMID(),topic.data(),datasend.size(),datasend.data(),2,false);
//    console->insertPlainText("vua gui du lieu nhiet do - do am len server!!! \r\n");
//}
//void MainWindow::sendMqttTandH(int mac,double temp,double humi)
//{
////    confmqtt x;
//    QString model="T1000";
//    QString name="P1-SN-0";
//    name.append(QString::number(mac));
//    //qDebug()<<name;
//    //nxt sua
//    QDateTime current = QDateTime::currentDateTime();
//    uint timestame = current.toTime_t();
//   // qDebug()<<timestame;
//    QString payload = "{\"";
//    payload +=name;
//    payload +="\": [{\"ts\":";
//    payload +=QString::number(timestame);payload+="000,\"values\":";
//    payload += "{\"temperature\":"; payload += QString::number(temp); payload += ",";
//    payload += "\"threshold_temperature\":"; payload +=QString::number(DATA::temp_t); payload +=",";
//    payload += "\"humidity\":"; payload += QString::number(humi); payload +=",";
//    payload += "\"threshold_humidity\":"; payload +=QString::number(DATA::hump_t);
//    payload += "}}]}";

///*using tb-gateway*/
////    QString payload="{";
////        payload += "\"serialNumber\":\""; payload +=name ; payload += "\",";
////        payload += "\"temperature\":"; payload += QString::number(temp); payload += ",";
////        payload += "\"humidity\":"; payload += QString::number(humi); payload += ",";
////        payload += "\"model\":\""; payload += model;
////    payload+="\"}";

//    qDebug()<<payload<<endl;
//    QByteArray datasend=payload.toLocal8Bit();
//    QByteArray topic= xx.topic2.toAscii();
//    mosq->publish(mosq->getMID(),topic.data(),datasend.size(),datasend.data(),2,false);
//    console->insertPlainText("Sent temperature-humidity data to the server!!! \r\n");
//}
//void MainWindow::sendMqttLux(int mac,double lux)
//{
////    confmqtt x;
//    QString model="T1000";
//    QString name="P1-SN-0";
//    name.append(QString::number(mac));
//    //qDebug()<<name;
//    //nxt sua
//    QDateTime current = QDateTime::currentDateTime();
//    uint timestame = current.toTime_t();
//   // qDebug()<<timestame;
//    QString payload = "{\"";
//    payload +=name;
//    payload +="\": [{\"ts\":";
//    payload +=QString::number(timestame);payload+="000,\"values\":";
//    payload += "{\"luminance\":"; payload += QString::number(lux); payload +=",";
//    payload += "\"threshold_luminance\":"; payload += QString::number(DATA::lux_t);
//    payload += "}}]}";
//    qDebug()<<payload<<endl;
//    QByteArray datasend=payload.toLocal8Bit();
//    QByteArray topic= xx.topic2.toAscii();
//    mosq->publish(mosq->getMID(),topic.data(),datasend.size(),datasend.data(),2,false);
//    console->insertPlainText("vua gui du lieu anh sang len server!!! \r\n");
//}
//end code mqtt
void MainWindow::loadHtmlPage()
{
    QFile htmlFile(":/html/index.html");
    if( ! htmlFile.open(QFile::ReadOnly) )
    {
        errorOccured( "I can't read html file" );
        return;
    }
}

void MainWindow::errorOccured(QString error)
{
    QMessageBox::warning(this, trUtf8("Error"), error);
}
//void MainWindow::populateJavaScriptWindowObject()
//{
//}

void MainWindow::initMap(bool isok)
{
    if( !isok ) return;
    QSettings settings(m_organizationName, m_appName);
    QString lat = settings.value("latStartup").toString();
    QString lng = settings.value("lngStartup").toString();
    QString place = lat + ", " + lng;
    if( lat.isEmpty() || lng.isEmpty() ) place = "20.333413, 105.597677";
    QString zm = settings.value("zoomStartup").toString();
    if(zm.isEmpty()) zm = "8";
    QString str = place + ", " + zm;

    initListSensor();
}

void MainWindow::initListSensor()
{
    readfile x;
    qDebug() << "init Lior";
    FileData file(x.DATA_PATH);
    FileData data(x.HISTORY_FILE);
    FileData timeData(x.TIME_DETECT);
    int N = file.length();
    int M = data.length();
    int P = timeData.length();
    for(int i = 0; i < N; i++)
    {
        QTime initTime(0,0,0,0);
        QString line = file.readLine(i+1);
        QStringList lst = line.split(",");
        movDetectTime.insert(lst.value(0), initTime);
        maxTemp.insert(lst.value(0), 0);

        for(int j = P-1; j >=0; j--){
            QString timeLine = timeData.readLine(j+1);
            QStringList timeList = timeLine.split(":");
            if(timeList.value(0) == lst.value(0)){
                QTime time(timeList.value(1).toInt(), timeList.value(2).toInt(), timeList.value(3).toInt());
                movDetectTime[lst.value(0)] = time;
                break;
            }
        }

        QString str = lst.value(0) + "," + lst.value(1) + ", " + lst.value(2) + ",";
        for(int j = M-1; j >=0; j--){
            QString data_line = data.readLine(j+1);
            QStringList data_lst = data_line.split(":");
            if(data_lst.value(2) == lst.value(0)){
                //qDebug()<< "ok";
                str += data_lst.value(3) + "," + data_lst.value(4) + "," + lst.value(6);
                ListSensorTemp.push_back(data_lst.value(3).toDouble());
                break;
            }
        }
//        addMarker(str);
        ListSensor.push_back(new Sensor(lst.value(0).toInt()));
        ListSensor.last()->markerIndex = i;
        ListSensor[i]->lat = lst.value(1);
        ListSensor[i]->lng = lst.value(2);
        ListSensor[i]->clusterHead = ListSensor[getIndexMarker(lst.value(6).toInt())];
        double arg = bearing(ListSensor[i]->clusterHead->lat.toDouble(), ListSensor[i]->clusterHead->lng.toDouble(), lst.value(1).toDouble(), lst.value(2).toDouble());
        ListSensorArg.push_back(arg);
        double delta_temp = ListSensorTemp[i] - ListSensorTemp[getIndexMarker(lst.value(6).toInt())];
        ListSensorDeltaTemp.push_back(delta_temp);
        ListSensor[i]->x0 = ListSensorDeltaTemp[i] * sin(ListSensorArg[i]);
        ListSensor[i]->y0 = ListSensorDeltaTemp[i] * cos(ListSensorArg[i]);
        ListSensorStt.push_back(false);





        //qDebug() << "Sensor " << lst.value(0) << ", Argument: " << ListSensorArg[i]*180/M_PI;
        //qDebug() << ListSensor[i]->x0 << " *** " << ListSensor[i]->y0;
        //qDebug() << "Sensor "  << ListSensor[i]->isJoin;
    }
//    QString lat_test, lng_test;
//    findLastPoint(lat_test, lng_test, 53.32055556, 1.7297222, 124800, 1.675894237 );
//    qDebug() << "Test: " << lat_test << " *** " << lng_test ;
//    double dis_test = distance(ListSensor[0]->lat.toDouble(), ListSensor[0]->lng.toDouble(), ListSensor[1]->lat.toDouble(), ListSensor[1]->lng.toDouble());
//    findLastPoint(lat_test, lng_test, ListSensor[0]->lat.toDouble(), ListSensor[0]->lng.toDouble(), dis_test, ListSensorArg[1]);
//    qDebug() << "Test: " << lat_test << " *** " << lng_test ;
//    ClearMap();
}

void MainWindow::updateListSensor()
{
    readfile x;
    qDebug() << "Update List Sensor";
    //qDebug() << "Time Appear Predict: " << tPredict(movDetectTime.value("08"), movDetectTime.value("05"), d1, d2);
    FileData file(x.DATA_PATH);
    FileData data(x.HISTORY_FILE);
    int N = file.length();
    int M = data.length();
    for(int i = 0; i < N; i++)
    {
        QString line = file.readLine(i+1);
        QStringList lst = line.split(",");
        QString str = lst.value(0) + "," + lst.value(1) + ", " + lst.value(2);

//        double dis = distance(DATA::lat.toDouble(), DATA::lng.toDouble(), QString(lst.value(1)).toDouble(), QString(lst.value(2)).toDouble());
//        qDebug() << "Node " << lst.value(0) << ": " << dis;

        for(int j = M-1; j >=0; j--){
            QString data_line = data.readLine(j+1);
            QStringList data_lst = data_line.split(":");
            if(data_lst.value(2) == lst.value(0)){
                str += "," + data_lst.value(3) + "," + data_lst.value(4) + "," + lst.value(6);
                ListSensorTemp[i] = data_lst.value(3).toDouble();
                break;
            }
        }

        if(lst.value(0) == "09"){
            QString time1 = movDetectTime.value("05").toString("hh:mm:ss");
            QString time2 = movDetectTime.value("08").toString("hh:mm:ss");
            QString time3 = movDetectTime.value("09").toString("hh:mm:ss");
            QStringList lTime1 = time1.split(":");
            QStringList lTime2 = time2.split(":");
            QStringList lTime3 = time3.split(":");
            for(int p=0; p<3; p++){
                str += ","+lTime1.value(p);
            }
            for(int q=0; q<3; q++){
                str += ","+lTime2.value(q);
            }
            for(int r=0; r<3; r++){
                str += ","+lTime3.value(r);
            }
            //qDebug() << "Tracking Marker" << str;
        }else
//            addMarker(str);

        ListSensorDeltaTemp[i] = ListSensorTemp[i] - ListSensorTemp[getIndexMarker(lst.value(6).toInt())];
        ListSensor[i]->x0 = ListSensorDeltaTemp[i] * sin(ListSensorArg[i]);
        ListSensor[i]->y0 = ListSensorDeltaTemp[i] * cos(ListSensorArg[i]);
        //qDebug() << i << ListSensorDeltaTemp[i] << ListSensor[i]->x0 << ListSensor[i]->y0;
    }
   // ClearMap();
}

QString MainWindow::getIp(int mac)
{
    if(mac==100) return "FFFF";
    int N = ListSensor.length();
    for(int i = 0; i < N; i++)
    {
        if(ListSensor[i]->mac == mac) {qDebug()<<"ip ne::"<<ListSensor[i]->ip<<endl; return ListSensor[i]->ip;}
    }
    return "";
}

// 506F000$

void MainWindow::sendCommand(int mac, int cmd)
{
    qDebug()<< "Send Command" << mac << cmd;
    //int i = 0;
    QString Ip = getIp(mac);
    QString Cmd = Ip;
  //  QString Cmd1, Cmd2, Cmd3, func1, func2, func3;
    int func1, func2, func3,sta;
    QString s;
    QSettings settings(m_organizationName, m_appName);
    switch(cmd){
    case 0: // Take temperature and humidity
        if(mac < 10){
            DATA::mac = "0" + QString::number(mac);
           // qDebug()<< "mac send data :" <<DATA::mac<<endl;
        }
        else{
            DATA::mac = QString::number(mac);
        }
        DATA::Ip = Ip;
        qDebug()<<"cmd truoc:"<<Cmd<<endl;
        Cmd += "000$";
        qDebug()<<"ip data:"<<DATA::Ip<<endl;
        qDebug()<<"cmd data:"<<Cmd<<endl;
        break;

    case 1: // Take photo
        if(mac < 10){
            DATA::mac = "0" + QString::number(mac);
        }
        else{
            DATA::mac = QString::number(mac);
        }
        DATA::Ip = Ip;
        DATA::img.clear();
        Cmd += "400$";
        break;

//    case 2: // Request Status
//        Cmd += "580$";
//        break;

//    case 3: // Retask
//        func1 = settings.value("func1Retask").toInt();
//        func2 = settings.value("func2Retask").toInt();
//        func3 = settings.value("func3Retask").toInt();
//        sta = func1+func2*2+func3*4;
//        switch(sta)
//        {
//        case 0:s="0";break;
//        case 1:s="1";break;
//        case 2:s="2";break;
//        case 3:s="3";break;
//        case 4:s="4";break;
//        case 5:s="5";break;
//        case 6:s="6";break;
//        case 7:s="7";break;
//        }
//        Cmd+="5"+s +"0$";

//        break;

    case 3: // Warning level 1
        Cmd = "0000011$";
        break;

    case 4: // Warning level 2
        Cmd = "0000021$";
        break;

    case 5: // Warning level 3
        Cmd = "0000031$";
        break;

    case 6: // Warning level 4
        Cmd = "0000041$";
        break;

    case 7: // Warning level 5
        Cmd = "0000051$";
        break;
    case 2: // take illuminance
        if(mac < 10){
            DATA::mac = "0" + QString::number(mac);
           // qDebug()<< "mac send data :" <<DATA::mac<<endl;
        }
        else{
            DATA::mac = QString::number(mac);
        }
        DATA::Ip = Ip;
        qDebug()<<"cmd truoc:"<<Cmd<<endl;
        Cmd += "600$";
        qDebug()<<"ip data:"<<DATA::Ip<<endl;
        qDebug()<<"cmd data:"<<Cmd<<endl;
        break;
    case 9:
        if(mac < 10){
            DATA::mac = "0" + QString::number(mac);
           // qDebug()<< "mac send data :" <<DATA::mac<<endl;
        }
        else{
            DATA::mac = QString::number(mac);
        }
        DATA::Ip = Ip;
        qDebug()<<"cmd truoc:"<<Cmd<<endl;
        Cmd += "610$";
        qDebug()<<"ip data:"<<DATA::Ip<<endl;
        qDebug()<<"cmd data:"<<Cmd<<endl;
        break;
    case 10: //
        if(mac < 10){
            DATA::mac = "0" + QString::number(mac);
           // qDebug()<< "mac send data :" <<DATA::mac<<endl;
        }
        else{
            DATA::mac = QString::number(mac);
        }
        DATA::Ip = Ip;
        qDebug()<<"cmd truoc:"<<Cmd<<endl;
        Cmd += "620$";
        qDebug()<<"ip data:"<<DATA::Ip<<endl;
        qDebug()<<"cmd data:"<<Cmd<<endl;
        break;
    case 11:
        if(mac < 10){
            DATA::mac = "0" + QString::number(mac);
           // qDebug()<< "mac send data :" <<DATA::mac<<endl;
        }
        else{
            DATA::mac = QString::number(mac);
        }
        DATA::Ip = Ip;
        qDebug()<<"cmd truoc:"<<Cmd<<endl;
        Cmd += "630$";
        qDebug()<<"ip data:"<<DATA::Ip<<endl;
        qDebug()<<"cmd data:"<<Cmd<<endl;
        break;
    case 12:
        if(mac < 10){
            DATA::mac = "0" + QString::number(mac);
           // qDebug()<< "mac send data :" <<DATA::mac<<endl;
        }
        else{
            DATA::mac = QString::number(mac);
        }
        DATA::Ip = Ip;
        qDebug()<<"cmd truoc:"<<Cmd<<endl;
        Cmd += "640$";
        qDebug()<<"ip data:"<<DATA::Ip<<endl;
        qDebug()<<"cmd data:"<<Cmd<<endl;
        break;

    default: break;
    }

    if(Cmd.length() > 4) {
       // qDebug()<<"vao duoc roi"<<endl;
        tranceiver->writeData(Cmd);
        QString tmp = "Submit code " + Cmd + "\n";
        console->insertPlainText(tmp);
    }
}

void MainWindow::on_btnExit_clicked()
{
    this->close();
}

void MainWindow::AlwaysOpenPort()
{
    readfile x;
    if(tranceiverStarted)
    {
        if(tranceiver->port->isOpen()){
            tranceiver->port->close();
            led->turnOff();
            ui->btnOpenClose->setText("Open");
            console->insertPlainText("\n-------------- Port Closed -------------\n");
        } else {
            if(tranceiver->port->portName().isEmpty()) tranceiver->port->setPortName(x.TRANCEIVER_PORT_DEFAULT);
            QSettings settings(m_organizationName, m_appName);
            QString tmp = settings.value("TranceiverBaudrate").toString();
            if(tmp.isEmpty()) tranceiver->port->setBaudRate((BaudRateType)x.TRANCEIVER_BAUDRATE_DEFAULT);
            tranceiver->port->open(QIODevice::ReadWrite);
            led->turnOn();
            ui->btnOpenClose->setText("Close");
            console->insertPlainText("\n------------- Port Data Opened ------------\n");
        }
    } else {
        tranceiver->requestWork();
        ui->btnOpenClose->setText("Close");
        led->turnOn();
        console->insertPlainText("\n-------------- Port Data Opened -------------\n");
        tranceiverStarted = true;
    }
}
void MainWindow::AlwaysOpenPortLR()
{
    readfile x;
    if(loraStarted)
    {
        if(lora->port->isOpen()){
            lora->port->close();
            console->insertPlainText("\n-------------- Lora Closed -------------\n");
        } else {
            if(lora->port->portName().isEmpty()) lora->port->setPortName(x.LORA_PORT_DEFAULT);
            QSettings settings(m_organizationName, m_appName);
            QString tmp = settings.value("TranceiverBaudrate").toString();
            if(tmp.isEmpty()) lora->port->setBaudRate((BaudRateType)x.LORA_BAUDRATE_DEFAULT);
            lora->port->open(QIODevice::ReadWrite);
//            led->turnOn();
//            ui->btnOpenClose->setText("Close");
            console->insertPlainText("\n------------- Port Lora Data Opened ------------\n");
        }
    } else {
        lora->requestWorkLR();
        //ui->btnOpenClose->setText("Close");
        //led->turnOn();
        console->insertPlainText("\n-------------- Port Lora Data Opened -------------\n");
        loraStarted = true;
    }
}

void MainWindow::onOpenCloseButtonClicked()
{
    readfile x;
    if(tranceiverStarted)
    {
        if(tranceiver->port->isOpen()){
            tranceiver->port->close();
            led->turnOff();
            ui->btnOpenClose->setText("Open");
            console->insertPlainText("\n-------------- Port Closed -------------\n");
        } else {
            if(tranceiver->port->portName().isEmpty()) tranceiver->port->setPortName(x.TRANCEIVER_PORT_DEFAULT);
            QSettings settings(m_organizationName, m_appName);
            QString tmp = settings.value("TranceiverBaudrate").toString();
            if(tmp.isEmpty()) tranceiver->port->setBaudRate((BaudRateType)x.TRANCEIVER_BAUDRATE_DEFAULT);
            tranceiver->port->open(QIODevice::ReadWrite);
            led->turnOn();
            ui->btnOpenClose->setText("Close");
            console->insertPlainText("\n------------- Port Data Opened ------------\n");
        }
    } else {
        tranceiver->requestWork();
        ui->btnOpenClose->setText("Close");
        led->turnOn();
        console->insertPlainText("\n-------------- Port Data Opened -------------\n");
        tranceiverStarted = true;
    }
}

void MainWindow::onGpsData(QString data)
{

}
void MainWindow::onNodeJoinLR(int mac)
{
    QString tmp = "Node " + QString::number(mac)+ "Join Network\n\r";
    console->insertPlainText(tmp);
    int flag=1;
    for(int i=0; i<(int)ui->boxSensor->size().height();i++){
        if(ui->boxSensor->itemText(i).compare(tmp)==0){
            flag=0; break;
        }

    }
    if(flag) ui->boxSensor->addItem(QString::number(mac), mac);

}
void MainWindow::onNodeJoin(int mac, QString address)
{
    readfile x;
    //console->insertPlainText("Node Join!!!!\n");
    FileData file(x.DATA_PATH);
    QString tmp = "["+QTime::currentTime().toString() + "] "+"Node " + QString::number(mac) + " join the network " + address + "\n";
   // WriteDatatoLogfile(tmp);
    console->insertPlainText(tmp);
    //if(!checkJoin(mac)){
        tmp = "Node " + QString::number(mac);
        int index = getIndexMarker(mac);
        qDebug() << index;
        int flag=1;
        for(int i=0; i<(int)ui->boxSensor->size().height();i++){
            if(ui->boxSensor->itemText(i).compare(tmp)==0){
                flag=0; break;
            }

        }
        if (flag)   ui->boxSensor->addItem(tmp, mac);
        //qDebug() << "Index: " << index;
        if(index >= 0){
            ListSensor[index]->isJoin = true;
            ListSensorStt[index]=true;
            ListSensor[index]->ip = address;
//            joinedMac[indexJoined] = index;
//            joinedAddress[indexJoined] = address;
//            qDebug() <<" joinedMac[" + QString::number(indexJoined) + "]: " << joinedMac[indexJoined];
//            qDebug() << "joinedAddress[" + QString::number(indexJoined) + "]: "  + address;
//            indexJoined++;
//            qDebug() << "indexJoined = " << indexJoined << endl;

        }
    //}
}

void MainWindow::onImageReceived(QString FileName)
{
    QImage image(FileName);
    ui->lblImage->setPixmap (QPixmap::fromImage (image));
}

bool MainWindow::checkJoin(int mac)
{
    int i = getIndexSensor(mac);
    if(i > -1) return ListSensorStt[i];
    return false;
}

int MainWindow::getIndexSensor(int mac)
{
    int N = ListSensor.length();
    for(int i = 0; i < N; i++)
    {
        if(ListSensor[i]->mac == mac) return i;
    }
    return -1;
}

int MainWindow::getIndexMarker(int mac)
{
    int N = ListSensor.length();
    for(int i = 0; i < N; i++)
    {
        if(ListSensor[i]->mac == mac) return ListSensor[i]->markerIndex;
    }
    return -1;
}



//Tranceiver
void MainWindow::onreceivedDataLR(QString data)
{	
	
 console->insertPlainText(data);
}

void MainWindow::onTranceiverData(QString data)
{
	//qDebug()<<insertPlainText(data);
    console->printData(data);
    console->moveCursor(QTextCursor::End);
    QString PUMP;
    QString time_format = "yyyy-MM-dd  HH:mm:ss";
    QDateTime a = QDateTime::currentDateTime();
    QString timestart = a.toString(time_format);
    QDateTime b = a.addSecs(5*60);
    QString timestop = b.toString(time_format);
    if(data=="ON Pompe"){
        PUMP="ON";
    }
    if(data=="OFF Pompe") {
        PUMP="OFF";
    }
    if(data=="ON Pompe"||data=="OFF Pompe")
    {
        console->insertPlainText(data);
        QString model="T1000";
        QString name="PUMP";
        QDateTime current = QDateTime::currentDateTime();
        uint timestame = current.toTime_t();
       // qDebug()<<timestame;
        QString payload = "{\"";
        payload +=name;
        payload +="\": [{\"ts\":";
        payload +=QString::number(timestame);payload+="000,\"values\":";
        payload += "{\"Pump\":"; payload += PUMP;
        payload += "}}]}";

        qDebug()<<payload<<endl;
        QByteArray datasend=payload.toLocal8Bit();
        QByteArray topic= xx.topic2.toAscii();
        mosq->publish(mosq->getMID(),topic.data(),datasend.size(),datasend.data(),2,false);
        //console->insertPlainText("\nsent the lamp-pump data to the server!!! \r\n");
    }
    if(data=="ON Pompe")
    {
        QString model="T1000";
        QString name="PUMP LOG";
        //name.append(QString::number(mac));
        //qDebug()<<name;
        //nxt sua
        QDateTime current = QDateTime::currentDateTime();
        uint timestame = current.toTime_t();
       // qDebug()<<timestame;
        QString payload = "{\"";
        payload +=name;
        payload +="\": [{\"ts\":";
        payload +=QString::number(timestame);payload+="000,\"values\":";
        payload += "{\"Pump\":"; payload += PUMP; payload += ",";
        payload += "\"Start_time\":"; payload +='"'; payload += timestart; payload +='"';payload +=",";
        payload += "\"Stop_time\":"; payload +='"'; payload += timestop; payload +='"';
        payload += "}}]}";

    /*using tb-gateway*/
    //    QString payload="{";
    //        payload += "\"serialNumber\":\""; payload +=name ; payload += "\",";
    //        payload += "\"temperature\":"; payload += QString::number(temp); payload += ",";
    //        payload += "\"humidity\":"; payload += QString::number(humi); payload += ",";
    //        payload += "\"model\":\""; payload += model;
    //    payload+="\"}";

        qDebug()<<payload<<endl;
        QByteArray datasend=payload.toLocal8Bit();
        QByteArray topic= xx.topic2.toAscii();
        mosq->publish(mosq->getMID(),topic.data(),datasend.size(),datasend.data(),2,false);
        console->insertPlainText("\nsent the lamp-pump data to the server!!! \r\n");
    }
}

void MainWindow::onTranceiverDataLI(QString data)
{
	
	//qDebug()<<data;
    //console->printData(data);
    console->moveCursor(QTextCursor::End);
    QString LIGHT;
    QString time_format = "yyyy-MM-dd  HH:mm:ss";
    QDateTime a = QDateTime::currentDateTime();
    QString timestart = a.toString(time_format);
    QDateTime b = a.addSecs(5*60);
    QString timestop = b.toString(time_format);
    if(data=="ON Light"){
        LIGHT="ON";
    }
    if(data=="OFF Light") {
        LIGHT="OFF";
    }
    if(data=="ON Light"||data=="OFF Light")
    {
        console->insertPlainText(data);
        QString model="T1000";
        QString name="PUMP";
        QDateTime current = QDateTime::currentDateTime();
        uint timestame = current.toTime_t();
       // qDebug()<<timestame;
        QString payload = "{\"";
        payload +=name;
        payload +="\": [{\"ts\":";
        payload +=QString::number(timestame);payload+="000,\"values\":";
        payload += "{\"Light\":"; payload += LIGHT;
        payload += "}}]}";

        qDebug()<<payload<<endl;
        QByteArray datasend=payload.toLocal8Bit();
        QByteArray topic= xx.topic2.toAscii();
        mosq->publish(mosq->getMID(),topic.data(),datasend.size(),datasend.data(),2,false);
        //console->insertPlainText("\nsent the lamp-pump data to the server!!! \r\n");
    }
    if(data=="ON Light")
    {
        QString model="T1000";
        QString name="LIGHT LOG";
        //name.append(QString::number(mac));
        //qDebug()<<name;
        //nxt sua
        QDateTime current = QDateTime::currentDateTime();
        uint timestame = current.toTime_t();
       // qDebug()<<timestame;
        QString payload = "{\"";
        payload +=name;
        payload +="\": [{\"ts\":";
        payload +=QString::number(timestame);payload+="000,\"values\":";
        payload += "{\"Light\":"; payload += LIGHT; payload += ",";
        payload += "\"Start_time\":"; payload +='"'; payload += timestart; payload +='"';payload +=",";
        payload += "\"Stop_time\":"; payload +='"'; payload += timestop; payload +='"';
        payload += "}}]}";

    /*using tb-gateway*/
    //    QString payload="{";
    //        payload += "\"serialNumber\":\""; payload +=name ; payload += "\",";
    //        payload += "\"temperature\":"; payload += QString::number(temp); payload += ",";
    //        payload += "\"humidity\":"; payload += QString::number(humi); payload += ",";
    //        payload += "\"model\":\""; payload += model;
    //    payload+="\"}";

        qDebug()<<payload<<endl;
        QByteArray datasend=payload.toLocal8Bit();
        QByteArray topic= xx.topic2.toAscii();
        mosq->publish(mosq->getMID(),topic.data(),datasend.size(),datasend.data(),2,false);
        console->insertPlainText("\nsent the lamp-pump data to the server!!! \r\n");
    }
}

void MainWindow::onTempAndHumLR(QString data)
{
    QString tmp;
    QStringList data_lst = data.split(":");
    console->moveCursor(QTextCursor::End);
//    FileData file(DATA_PATH);
    QString mac = data_lst.value(0);

    tmp = "\n["+QTime::currentTime().toString()+"] " +"information temperature and humidity LoRa\r\n";

    tmp += "Node ";
    tmp += data_lst.value(0);
    tmp += "\nTemperature: ";
    tmp += data_lst.value(1);
    tmp += " oC\nHumiumidity: ";
    tmp += data_lst.value(2);
    tmp += " %";
    bool ok;
    int mac1=data_lst.value(0).toInt(&ok,10);
    double temp =data_lst.value(1).toDouble(&ok);
    double humi =data_lst.value(2).toDouble(&ok);
   // WriteDatatoLogfile(tmp);
    console->insertPlainText(tmp + "\n");
    sendMqttData(mac1,temp,"temparature");
    sendMqttData(mac1,humi,"humidity");
    receivedFlag = true;
//    emit readySend();
}
void MainWindow::onTempAndHum(QString data)
{
    QString tmp;
    QStringList data_lst = data.split(":");
    console->moveCursor(QTextCursor::End);
//    FileData file(DATA_PATH);
    QString mac = data_lst.value(0);
    int index  = getIndexMarker(mac.toInt());
    ListSensor[index]->cur_temp = data_lst.value(2).toDouble();

    tmp = "\n["+QTime::currentTime().toString()+"] " +"information of temperature, humidity from sensor ";
    tmp += data_lst.value(0);
    tmp += ", Address Ip ";
    tmp += data_lst.value(1);
    tmp += "\nTemperature:        ";
    tmp += QString::number(ListSensor[index]->cur_temp);//data_lst.value(2);
    tmp += "\nHumidity:           ";
    tmp += data_lst.value(3);
    tmp += "\n";

    //WriteDatatoLogfile(tmp);
    console->insertPlainText(tmp + "\n");

    //    QString line = file.readLine(index+1);
//    QStringList lst = line.split(",");

//    qDebug() << mac;
//    movDetectTime[mac] = QTime::currentTime();
//    qDebug() << QTime::currentTime() << movDetectTime.value(mac);
//    removeAllMarkers();
//    ListSensor.clear();

//    nxt cmt
    //updateListSensor();


//    QString lat_test, lng_test;
////    QString vector = QString::number(index) + lst.value(1) + "," + lst.value(2);
//    QString vector = lst.value(1) + "," + lst.value(2);
//    double dis = ListSensorDeltaTemp[index] * 20;
//    findLastPoint(lat_test, lng_test, lst.value(1).toDouble(), lst.value(2).toDouble(), dis, ListSensorArg[index]);
//    vector += "," + lat_test + "," + lng_test;
//    //qDebug() << vector;
//    if(lst.value(0) != lst.value(6)){
//        ui->webView->page()->mainFrame()->evaluateJavaScript(QString("clearArrow(%1)").arg(index));
//        ui->webView->page()->mainFrame()->evaluateJavaScript(QString("addTempVector(%1)").arg(vector));
//    }
    receivedFlag = true;
//    emit readySend();
}

void MainWindow::onTempAndHum1(QString data)
{
    QString tmp;
    QStringList data_lst = data.split(":");
    console->moveCursor(QTextCursor::End);
//    FileData file(DATA_PATH);
    QString mac = data_lst.value(0);
    int index  = getIndexMarker(mac.toInt());
    ListSensor[index]->cur_temp = data_lst.value(2).toDouble();

    tmp = "\n["+QTime::currentTime().toString()+"] " +"Periodic information of temperature, humidity from sensor ";
    tmp += data_lst.value(0);
    tmp += ", Address Ip ";
    tmp += data_lst.value(1);
    tmp += "\nTemperature:        ";
    tmp += QString::number(ListSensor[index]->cur_temp);//data_lst.value(2);
    tmp += "\nHumidity:           ";
    tmp += data_lst.value(3);
    tmp += "\n";

   // WriteDatatoLogfile(tmp);
    console->insertPlainText(tmp + "\n");

    //    QString line = file.readLine(index+1);
//    QStringList lst = line.split(",");

//    qDebug() << mac;
//    movDetectTime[mac] = QTime::currentTime();
//    qDebug() << QTime::currentTime() << movDetectTime.value(mac);
//    removeAllMarkers();
//    ListSensor.clear();

//    nxt cmt
    //updateListSensor();

//    QString lat_test, lng_test;
////    QString vector = QString::number(index) + lst.value(1) + "," + lst.value(2);
//    QString vector = lst.value(1) + "," + lst.value(2);
//    double dis = ListSensorDeltaTemp[index] * 20;
//    findLastPoint(lat_test, lng_test, lst.value(1).toDouble(), lst.value(2).toDouble(), dis, ListSensorArg[index]);
//    vector += "," + lat_test + "," + lng_test;
//    //qDebug() << vector;
//    if(lst.value(0) != lst.value(6)){
//        ui->webView->page()->mainFrame()->evaluateJavaScript(QString("clearArrow(%1)").arg(index));
//        ui->webView->page()->mainFrame()->evaluateJavaScript(QString("addTempVector(%1)").arg(vector));
//    }
    receivedFlag = true;
//    emit readySend();
}
void MainWindow::oncompleteLux(QString data)
{
    QString tmp;
    QStringList data_lst = data.split(":");
    console->moveCursor(QTextCursor::End);
//    FileData file(DATA_PATH);
    QString mac = data_lst.value(0);
    //int index  = getIndexMarker(mac.toInt());
    //ListSensor[index]->cur_temp = data_lst.value(2).toDouble();

    tmp = "\n["+QTime::currentTime().toString()+"] " +"information of luminance from sensor ";
    tmp += data_lst.value(0);
    tmp += ", Address Ip ";
    tmp += data_lst.value(1);
    tmp += "\nLuminance:        ";
    tmp += data_lst.value(2);
    tmp += "\n";

    //WriteDatatoLogfile(tmp);
    console->insertPlainText(tmp + "\n");
    receivedFlag = true;
}

void MainWindow::oncompleteMois(QString data)
{
    QString tmp;
    QStringList data_lst = data.split(":");
    console->moveCursor(QTextCursor::End);
//    FileData file(DATA_PATH);
//    QString mac = data_lst.value(0);
    //int index  = getIndexMarker(mac.toInt());
    //ListSensor[index]->cur_temp = data_lst.value(2).toDouble();

    tmp = "\n["+QTime::currentTime().toString()+"] " +"information of soil moisture from sensor ";
//    tmp += data;
//    tmp += ", Address Ip ";
//    tmp += data_lst.value(1);
    tmp += data_lst.value(0);
    tmp += "soil moisture :    ";
    tmp += data_lst.value(1);
    tmp += "%\n";

    //WriteDatatoLogfile(tmp);
    console->insertPlainText(tmp + "\n");
    receivedFlag = true;
}

//Checkbox
void MainWindow::onGpsStatus(bool ok)
{
    if(ok)
    {
        if(gpsStarted) gps->port->open(QIODevice::ReadWrite);
        else
        {
            gps->requestWork();
            gpsStarted = true;
        }
    } else
    {
        if(gps->port->isOpen()) gps->port->close();
    }
}

// Action
void MainWindow::startLinphone()
{
    QProcess *process = new QProcess(this);
    process->start("linphone-3");
}

void MainWindow::ShowAbout()
{
    AboutDialog dialog(this);
    dialog.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dialog.setFixedSize(dialog.size());
    dialog.exec();
}

void MainWindow::RetaskOne()
{
    int N = ListSensor.length();
    QString listMac;
    int mac;
    for(int i = 0; i < N; i++)
    {
        if(ListSensor[i]->isJoin) {
            mac = ListSensor[i]->mac;
            listMac += QString::number(mac);
            listMac += ",";
        }
    }
    listMac.remove(N-1, 1);
    RetaskSensorDialog dialog(listMac, this);
    dialog.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dialog.setFixedSize(dialog.size());
    if(dialog.exec() == QDialog::Accepted){
        QSettings settings(m_organizationName, m_appName);
        QString mac = settings.value("macRetask").toString();
        if(!mac.isEmpty()) sendCommand(mac.toInt(), RETASK);
    }
}

void MainWindow::RetaskAll()
{
    RetskAllDialog dialog(this);
    dialog.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dialog.setFixedSize(dialog.size());
    if(dialog.exec() == QDialog::Accepted){
        int N = ListSensor.length();
        for(int i = 0; i < N; i++)
        {
            if(ListSensor[i]->isJoin)
            {
                sendCommand(ListSensor[i]->mac, RETASK);
            }
        }
    }
}


void MainWindow::AddNewSensor()
{
    NewSensorDialog dialog(this);
    dialog.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dialog.setFixedSize(dialog.size());
    if(dialog.exec() == QDialog::Accepted)
    {
//        removeAllMarkers();
        ListSensor.clear();
        initListSensor();
    }
}

void MainWindow::EditSensorPlace()
{
    EditSensorPlaceDialog dialog(this);
    dialog.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dialog.setFixedSize(dialog.size());
    if(dialog.exec() == QDialog::Accepted)
    {
    }
}

void MainWindow::ShowSensorInformation()
{
    SensorInformationDialog dialog(this);
    dialog.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dialog.setFixedSize(dialog.size());
    dialog.exec();
}

void MainWindow::StartupLocation()
{
    StartupLocationDialog dialog(this);
    dialog.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dialog.setFixedSize(dialog.size());
    if(dialog.exec() == QDialog::Accepted)
    {
        QSettings settings(m_organizationName, m_appName);
        QString lat = settings.value("latStartup").toString();
        QString lng = settings.value("lngStartup").toString();
        QString zm = settings.value("zoomStartup").toString();
        QString place = lat + ", " + lng;
        if(place.isEmpty()) place = "20.333413, 105.597677";
        if(zm.isEmpty()) zm = "8";
//        gotoPlaceByCoordinate(place);
//        zoomMap(zm);
    }
}

/*
 * tu dong mo Port ket noi den Sensor, va GPS
 */
void MainWindow::SetupPortSerial()
{
    readfile x;
    QSettings settings(m_organizationName, m_appName);
    QString port = settings.value("TranceiverPort").toString();
    if(port.isEmpty()) port = x.TRANCEIVER_PORT_DEFAULT;
    tranceiver->port->setPortName(port);
    //int baudrate = settings.value("TranceiverBaudrate").toInt();
    tranceiver->port->setBaudRate(BAUD19200);

    port = settings.value("GpsPort").toString();
    if(port.isEmpty()) port = x.GPS_PORT_DEFAULT;
    gps->port->setPortName(port);
    //baudrate = settings.value("GpsBaudrate").toInt();
//    gps->port->setBaudRate((BaudRateType) baudrate);
    gps->port->setBaudRate(BAUD9600);
}

void MainWindow::SetupSerialPort()
{
    readfile x;
    SetupSerialPortDialog dialog(this);
    dialog.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dialog.setFixedSize(dialog.size());
    if(dialog.exec() == QDialog::Accepted)
    {
        QSettings settings(m_organizationName, m_appName);
        QString port = settings.value("TranceiverPort").toString();
        if(port.isEmpty()) port = x.TRANCEIVER_PORT_DEFAULT;
        tranceiver->port->setPortName(port);
        int baudrate = settings.value("TranceiverBaudrate").toInt();
        tranceiver->port->setBaudRate((BaudRateType)baudrate);

        port = settings.value("GpsPort").toString();
        if(port.isEmpty()) port = x.GPS_PORT_DEFAULT;
        gps->port->setPortName(port);
        baudrate = settings.value("GpsBaudrate").toInt();
        gps->port->setBaudRate((BaudRateType) baudrate);
    }
}

void MainWindow::SendToServer()
{
    ServerDialog dialog(this);
    dialog.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dialog.setFixedSize(dialog.size());
    dialog.exec();
}

//Push Button
void MainWindow::on_btnView_clicked()
{
    readfile x;
    QFileDialog dialog(this);
    dialog.setNameFilter (tr("Image (*.png *.xpm *.jpg *jpeg)"));
    dialog.setViewMode (QFileDialog::Detail);
    QString fileName= QFileDialog::getOpenFileName (this,tr("Open Image"),x.IMAGES_PATH,tr("Image File (*.png *.jpg *.bmp *jpeg)"));
    if(!fileName.isEmpty ()){
        QImage image(fileName);
        ui->lblImage->setPixmap (QPixmap::fromImage (image));
    }
}


void MainWindow::on_pushButton_clicked()
{
    int mac = ui->boxSensor->itemData(ui->boxSensor->currentIndex()).toInt();
    int cmd = ui->boxCommand->currentIndex();
    if(mac >= 0 && cmd >= 0) {
       /* if(cmd == 3)
        {
            RetaskSensorDialog dialog(QString::number(mac), this);
            dialog.exec();
        } else*/
    if (cmd<3){
         sendCommand(mac, cmd);
    }
    else
        onLR(mac,cmd);
    }
}

void MainWindow::Send_Broadcast()
{
    QString Cmd="FFFF000$";
    tranceiver->writeData(Cmd);
    console->insertPlainText(Cmd);
}

void MainWindow::sendtoWeb()
{
    int i=0;
    if((!DATA::lat.isEmpty())&&(!DATA::lng.isEmpty())) i+=1;
    if((!DATA::temp.isEmpty())&&(!DATA::hump.isEmpty())) i+=10;
    QString dataSend;

    switch(i){
    case 1:{
             dataSend = "P" + DATA::mac + DATA::Ip + DATA::lat + DATA::lng;
              break;
        }
    case 10:{
            dataSend = "H" + DATA::mac + DATA::Ip + DATA::temp + DATA::hump;
              break;
        }
    case 11:{
            dataSend = "KP" + DATA::mac + DATA::Ip + DATA::temp + DATA::hump + DATA::lat + DATA::lng;
             break;
        }
    default: break;
    }

    dataSend += "hello world";
    //QString url = "192.168.7.147:8000/sg/sg-master/rx.php?data=hello world";
    QString url="192.168.0.9:8000/?nhietdo=";
    url.append(DATA::temp+"&doam="+DATA::hump);
    //url+=dataSend;
    qDebug()<<"Data send "<<dataSend << " "<<url;
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    http1->get(request);
}

void MainWindow::on_btnClear_clicked()
{
    console->clear();
}

void MainWindow::onCommandLR(){
    QString Cmd="c$";
    lora->writeData(Cmd);
    QString tmp = "Send Code " + Cmd + "\n";
    console->insertPlainText(tmp);
}

void MainWindow::sendImageToWeb(QString imax,QString mac){
    QString str;
    QByteArray im;
    int hex;
    //qDebug()<<DATA::img;
    int len = imax.length()/2;
    for(int i=0; i < len; i++)
    {
        str = imax.mid(i*2, 2);
        bool ok;
        hex = str.toInt(&ok, 16);
        im[i]= (char) hex;
    }
    QString ima=QString::fromAscii(im.toBase64());
    //qDebug()<<ima;
    int a=ima.length();
//    int i=0;
    qDebug()<<a;
    QString image;
    QDateTime current = QDateTime::currentDateTime();
    uint timestame = current.toTime_t();
    QString name="P1-SN-";
    name.append(mac);
   // qDebug()<<timestame;
    for(int i=0; i<5; i++){
        if(i==4)image=ima.mid(i*a/5);
        else
            image=ima.mid(i*a/5,a/5);
        QString payload = "{\"";
        payload +=name;
    //    payload +="\": {\"ts\":";
    //    payload +=QString::number(timestame);payload+="000,\"values\":";
    //    payload += "{\"image\":\""; payload += QString::fromAscii(im.toBase64().data());
    //    payload += "\"}}}";
        payload +="\": [{\"ts\":";
        payload +=QString::number(timestame);payload+="000,\"values\":";
        payload += "{\"image"; payload+=QString::number(i); payload+="\":\""; payload += image;
        payload += "\"}}]}";
        qDebug()<<payload<<endl;

        QByteArray datasend=payload.toLocal8Bit();
        QByteArray topic= xx.topic2.toAscii();
        mosq->publish(mosq->getMID(),topic.data(),datasend.size(),datasend.data(),2,false);
    }

    console->insertPlainText("vua gui du lieu image len server!!!\n\r");
}

QString MainWindow::findNearestNode(){
    readfile x;
    FileData file(x.DATA_PATH);
    int N = file.length();
    double *dis = new double[N];
    for(int i = 0;i < N; i++){
        QString line = file.readLine(i+1);
        QStringList lst = line.split(",");
        double Nodelat = QString (lst.value(1)).toDouble();
        double Nodelng = QString (lst.value(2)).toDouble();
        dis[i] = sqrt(pow((DATA::lat.toDouble() - Nodelat)*110.574, 2) + pow((DATA::lng.toDouble()*cos(DATA::lat.toDouble()) - Nodelng*cos(Nodelat))*111.320, 2));
        //dis[i]  = dis()
    }
    int index = 0;
    for(int j = 0; j < N; j++){
        if(dis[j] < dis[index])
            index = j;
    }
    QString str = file.readLine(index + 1);
    QString mac = QStringList(str.split(",")).value(0);
    delete dis;
    return mac;
}



void MainWindow::delay(int secondsToWait){
    QTime dieTime = QTime::currentTime().addSecs(secondsToWait);
    while(QTime::currentTime() < dieTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

int MainWindow::tPredict(QTime t1, QTime t2, double d1, double d2){
    int time = fabs(t1.secsTo(t2));
    double v = d1/time;
    return int(d2/v);
}

void MainWindow::autoTakePhoto(QString mac){
    readfile x;
    QString my_mac = hash.value(mac);
    QTime t = QTime::currentTime();
    bool ok;
    //qDebug() << t << "-----" << movDetectTime.value(my_mac);
    //qDebug() << fabs(t.msecsTo(movDetectTime.value(my_mac))) << "---" << mac << " - " << my_mac;
    if(fabs(t.msecsTo(movDetectTime.value(my_mac))) > 5000){
        console->insertPlainText("Gui lenh chup anh tu dong toi sensor " + my_mac + "\n");
        sendCommand(my_mac.toInt(&ok,10), 1);
        movDetectTime[my_mac] = t;
        QString str = my_mac + ":" + t.toString("hh:mm:ss");
        WriteTextAppend(x.TIME_DETECT, str );
        //qDebug() << movDetectTime.value(my_mac);
    }
    if(mac == "09"){
        int tmp = movDetectTime.value("05").secsTo(t);
        int timePredict = tPredict(movDetectTime.value("08"), movDetectTime.value("05"), d1, d2);
        if(fabs(tmp - timePredict)/timePredict < 0.05){
            console->insertPlainText("Doi tuong tracking xuat hien tai Sensor 09, gui lenh chup anh\n");
            sendCommand(my_mac.toInt(&ok, 10), 1);
            QString str = my_mac + ":" + t.toString("hh:mm:ss");
            WriteTextAppend(x.TIME_DETECT, str );
            movDetectTime[my_mac] = t;
            detectedFlag = true;
        }
        else{
            console->insertPlainText("Gui lenh chup anh tu dong toi sensor " + my_mac + "\n");
            sendCommand(my_mac.toInt(&ok,10), 1);
            movDetectTime[my_mac] = t;
            QString str = my_mac + ":" + t.toString("hh:mm:ss");
            WriteTextAppend(x.TIME_DETECT, str );
        }
    }
    //updateListSensor();
}

double MainWindow::distance(double lat1, double lng1, double lat2, double lng2){
    double R = 6371;
    double dLat = deg2rad(fabs(lat2 - lat1));
    double dLng = deg2rad(fabs(lng2 - lng1));
    double a = pow(sin(dLat/2),2) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * pow(sin(dLng/2), 2);
    double b = 2 * atan2(sqrt(a), sqrt(1-a));
    return R * b * 1000;
}

double MainWindow::deg2rad(double deg){
   return deg * M_PI/180;
}

void MainWindow::WriteTextAppend(QString FileName, QString Text)
{
    QFile file(FileName);
    if(file.open(QIODevice::Append))
    {
        QTextStream stream(&file);
        stream << Text << endl;
        file.close();
    }
}

//void MainWindow::on_btngetData_clicked()
//{
//    FileData file(DATA_PATH);
//    int N = file.length();
//    double *temp = new double[N];
//    for(int i=0; i<N; i++){
//        QString line = file.readLine(i+1);
//        QStringList lst = line.split(",");
//        double Nodelat = QString (lst.value(1)).toDouble();
//        double Nodelng = QString (lst.value(2)).toDouble();
//        double dis = distance(DATA::lat.toDouble(), DATA::lng.toDouble(), Nodelat, Nodelng);
//        if(dis < 50 && ListSensorStt[i]){
//            sendCommand(QString(lst.value(0)).toInt(), 0);
//            delay(10);
////            while(1){
////                delay(0.5);
////                if(receivedFlag){
////                    FileData tempData(HISTORY_FILE);
////                    QString lineData = tempData.readLine(tempData.length());
////                    QStringList lstData = lineData.split(":");
////                    qDebug() << "Nhiet do " << lstData.value(1);
////                    temp[i] = QString(lstData.value(1)).toDouble();
////                    break;
////                }
////            }
////            for(int j=tempData.length()-1; j>=0; j--){
////                QString lineData = tempData.readLine(j+1);
////                QStringList lstData = lineData.split(":");
////                if(lstData.value(0) == lst.value(0)){
////                    qDebug() << "Nhiet do " << lstData.value(1);
////                    temp[i] = QString(lstData.value(1)).toDouble();
////                    break;
////                }
////            }
//            FileData tempData(HISTORY_FILE);
//            //qDebug() << tempData.length();
//            QString lineData = tempData.readLine(tempData.length());
//            QStringList lstData = lineData.split(":");
//            qDebug() << "Nhiet do " << lstData.value(1);
//            temp[i] = QString(lstData.value(1)).toDouble();
//            maxTemp[lst.value(0)] = temp[i];
//        }
//        else
//            temp[i] = 0;
//        //receivedFlag = false;
//    }
//    int index = 0;
//    for(int k=0; k<N; k++){
////        bool difference = true;
////        for(int j=0; j<=tempIndex.length(); j++){
////            if(j!=0){
////                if(tempIndex[j] == k){
////                    difference = false;
////                    break;
////                }
////            }
////        }
//        //qDebug() << "temp[" <<k<<"] = " << temp[k];
//        //if(difference){
//            if(temp[k] > temp[index])
//                index = k;
//        //}
//    }
//
////    if(temp[index] < lastTemp.last()){
////        for(int m=0; m<N; m++){
////
////        }
////    }
//
//    //tempIndex.push_back(index);
//    //lastTemp.push_back(temp[index]);
//    QString lineResult = file.readLine(index+1);
//    QStringList lstResult = lineResult.split(",");
//    QString str = DATA::lat + "," + DATA::lng + "," + lstResult.value(1) + "," + lstResult.value(2);
//    QString mac = lstResult.value(0);
//    console->insertPlainText("Trong pham vi 50m, Node " + mac + " co nhiet co cao nhat la: " + QString::number(temp[index]) + "\n");
//    ui->webView->page()->mainFrame()->evaluateJavaScript(QString("addDirectionArrow(%1)").arg(str));
//}

void MainWindow::on_btnPrint_clicked()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle(tr("Print Document"));
    QTextCursor c = QTextCursor(console->document());
    console->textCursor() = c;
    if(c.hasSelection())
        dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if(dialog.exec() != QDialog::Accepted){
        return;
    }
    console->document()->print(&printer);
}



double MainWindow::bearing(double lat1, double lng1, double lat2, double lng2){
    double a = cos(deg2rad(lat2)) * sin(deg2rad(lng2 -lng1));
    double b = cos(deg2rad(lat1))*sin(deg2rad(lat2)) - sin(deg2rad(lat1))*cos(deg2rad(lat2))*cos(deg2rad(lng2-lng1));
//    double a = cos(lat2)*sin(lng2-lng1);
//    double b = cos(lat1)*sin(lat2) - sin(lat1)*cos(lat2)*cos(lng2-lng1);
    a_test = a;
    b_test = b;
    return atan2(a,b);
}

void MainWindow::findLastPoint(QString &lat2, QString &lng2, double lat1, double lng1, double dis, double bear){
//    double ad = deg2rad(dis/6371000);
//    lat2 = asin(sin(deg2rad(lat1))*cos(ad) + cos(deg2rad(lat1))*sin(ad)*cos(bear));
//    lng2 = lng1 + atan2(sin(bear)*sin(ad)*cos(deg2rad(lat1)), cos(ad) - sin(deg2rad(lat1))*sin(deg2rad(lat2)));

    lat1 = deg2rad(lat1);
    lng1 = deg2rad(lng1);
    double ad = (dis/6371000);
    double m_lat = asin(sin(lat1)*cos(ad) + cos(lat1)*sin(ad)*cos(bear));
    double m_lng = lng1 + atan2(sin(bear)*sin(ad)*cos(lat1), cos(ad) - sin(lat1)*sin(m_lat));
    m_lat *= 180/M_PI;
    m_lng *= 180/M_PI;
    lat2 = QString::number(m_lat,'f',6);
    lng2 = QString::number(m_lng,'f',6);
}

void MainWindow::mySendCommand(int mac, int cmd)
{
    sendCommand(mac, cmd);
}

void MainWindow::makePlot(){


}

void MainWindow::setDate()
{

}

void MainWindow::sendBroadcast()
{
// QString cmd = "FFFF400$";
//    tranceiver->writeData(cmd);
//            console->insertPlainText("Gui ma lenh: "+cmd+"\n");
    //broadcast Nhiet do do am cho UAV
        QString cmd = "FFFF30$";
        tranceiver->writeData(cmd);
        console->insertPlainText("Gui ma lenh: "+cmd+"\n");

}

void MainWindow::on_btnConfigThreshol_clicked()
{
    configThreshold dialog(this);
    dialog.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    dialog.setFixedSize(dialog.size());
    if(dialog.exec() == QDialog::Accepted)
    {
////        removeAllMarkers();
//        ListSensor.clear();
//        initListSensor();
    }
}

void MainWindow::onTempHumi(int mac, double temp, double humi)
{
    //qDebug()<<DATA::temp<<"AA";
    //if(temp>DATA::temp_t || humi<DATA::hump_t){
        //sendCommand(06,3); //bat may bom
       // onLR(1,3);
    //}
    //else
        //sendCommand(06,4); //tat may bom
        //onLR(1,4);
    if(temp>DATA::temp_t)
    {
        console->insertPlainText("Temperature exceeds the threshold!!");
    }
    if(humi > DATA::hump_t)
    {
        console->insertPlainText("Temperature exceeds the threshold!!");
    }
}

void MainWindow::onLux_t(int mac, double lux)
{
    if(lux<=DATA::lux_t&&!DATA::onLight){
        //sendCommand(06,5);//bat den
        onLR(90,5);
    }
    else if(lux>DATA::lux_t&&DATA::onLight){
        //sendCommand(06,6); //tat den
        onLR(90,6);
    }
}

void MainWindow::onST(QString tmp)
{
    console->moveCursor(QTextCursor::End);
    console->insertPlainText(tmp+"\n\r");

}
//void MainWindow::onLRHTD(int mac, int td, int rhd){
//    float temp=(float)td/100;
//    float humi=(float)rhd/100;
//    sendMqttData(mac,temp,"temparature");
//    sendMqttData(mac,humi,"humidity");

//}

void MainWindow::onMois_t(int mac, double mois)
{
    if(mois<=DATA::mois_t&&!DATA::onPump){
        //sendCommand(06,5);//bat den
        onLR(90,3);//bat bom

    }
    //else {
        //sendCommand(06,6); //tat den
    if(mois>DATA::mois_t2&&DATA::onPump)
    {
        onLR(90,4);//tat bom
    }
    //}
}
void MainWindow::onLR(int mac,int index)
{
    QString Cmd;
    QString tmp;
    switch(index)
    {
    case 3:
        Cmd = QString::number(mac) +"630$";
        tmp = "Send Code " + Cmd +"\n";
        //emit runTimerP();
        break;
    case 4:
        Cmd = QString::number(mac) +"640$";
        tmp = "Send Code " + Cmd +"\n";
        break;
    case 5:
        Cmd = QString::number(mac) +"610$";
        tmp = "Send Code " + Cmd +"\n";
        break;
        //emit runTimerL();
    case 6:
        Cmd = QString::number(mac) +"620$";
        tmp = "Send Code " + Cmd +"\n";

        break;
    case 7:
        Cmd = QString::number(mac) +"500$";
        tmp = "Send Code " + Cmd +"\n";
        break;
    case 8:
        Cmd = "TAKEDUST" + QString::number(mac);
        tmp = "Send Code " + Cmd +"\n";
        break;
    default:
        Cmd="c$";
        tmp = "Send Code " + Cmd + "\n";
    }
    lora->writeData(Cmd);
    console->insertPlainText(tmp);
}

void MainWindow::oncompleteDust(QString data)
{
    QString tmp;
    QStringList data_lst = data.split(":");
    console->moveCursor(QTextCursor::End);
    //QString mac = data_lst.value(0);
    //int index  = getIndexMarker(mac.toInt());
    //ListSensor[index]->cur_temp = data_lst.value(2).toDouble();

    tmp = "\n["+QTime::currentTime().toString()+"] " +"information concentration of dust from sensor ";
    tmp += data_lst.value(0);
    //tmp += ", Address Ip ";
    //tmp += data_lst.value(1);
    tmp += "\nconcentration of dust:        ";
    tmp += data_lst.value(1);
    tmp += "ug/m^3";

    //WriteDatatoLogfile(tmp);
    console->insertPlainText(tmp + "\n");
    receivedFlag = true;
}

//void MainWindow::sendMqttDust(int mac,double dust)
//{
//    QString model="T1000";
//    QString name="P1-SN-0";
//    name.append(QString::number(mac));
//    //qDebug()<<name;
//    //nxt sua
//    QDateTime current = QDateTime::currentDateTime();
//    uint timestame = current.toTime_t();
//   // qDebug()<<timestame;
//    QString payload = "{\"";
//    payload +=name;
//    payload +="\": [{\"ts\":";
//    payload +=QString::number(timestame);payload+="000,\"values\":";
//    payload += "{\"dust density\":"; payload += QString::number(dust);
////    payload += "\"threshold_soil-moisture\":"; payload += QString::number(DATA::mois_t);
//    payload += "}}]}";
//    qDebug()<<payload<<endl;
//    QByteArray datasend=payload.toLocal8Bit();
//    QByteArray topic= xx.topic2.toAscii();
//    mosq->publish(mosq->getMID(),topic.data(),datasend.size(),datasend.data(),2,false);
//    console->insertPlainText("Sent concentration of dust data to the server!!! \r\n");

//}

//
// Sang loc du lieu cho Nhiet do - do am
void MainWindow::SendAITH(int mac, double temp, double humi)
{
                            sendMqttData(mac,temp,"temparature");
                            sendMqttData(mac,humi,"humidity");
//    bool a=database.insertdata(mac,temp,"temperature");
//    if(a)qDebug()<<"123";
//    database.insertdata(mac,humi,"humidity");
//    QString stemp = QString::number(temp, 'f', 2);
//    QString shumi = QString::number(humi, 'f', 2);
//    QString smac;
//    if(temp<10){
//        stemp = "0"+stemp;
//    }
//    if(mac<10){
//        smac.append(QString::number(mac));
//        smac="0"+smac;
//    } else {
//        smac.append(QString::number(mac));
//    }
//    QFile file("./WSAN/AITH.txt");
//        QLabel *testLabel= new QLabel;
//        QString line;
//        qDebug()<<"tes1";
//        if (file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ReadWrite)){
//            QString s;
//            QTextStream stream(&file);
//            qDebug()<<"test2";
//            while (!stream.atEnd()) {
//                QString read = stream.readLine();
//                qDebug()<<read;
//                qDebug()<<read.mid(0,2);
//                if (read.mid(0,2).toInt()==mac) {
//                    qDebug()<<read.mid(3,5);
//                    qDebug()<<read.mid(9,6);
//                    if (read.mid(3,5).toDouble()-temp>1 || read.mid(9,6).toDouble()-humi>1 || read.mid(3,5).toDouble()-temp<-1 || read.mid(9,6).toDouble()-humi<-1 ){
//                        //Them cac ham gui khi co sau khac nhieu
//                        sendMqttData(mac,temp,"temparature");
//                        sendMqttData(mac,humi,"humidity");
//                    } else {
//                        console->insertPlainText("Stable Temperature - Humidity!!! \r\n");
//                    }
//                } else {
//                    qDebug()<<"send new";
//                    if (!read.contains("DELETE")) {
//                        //delete
//                        s.append(read + "\n");
//                    }
//                }
//            }
//            file.resize(0);
//            stream << s;
//            stream <<smac<<":"<<stemp<<":"<<shumi<<endl;
//            testLabel->setText(line+"\n");
//        }
//        file.close();
}

// Sang Lọc du lieu cho anh sang
void MainWindow::SendAILUX(int mac, double lux)
{
        sendMqttData(mac,lux,"lux");
//    database.insertdata(mac,lux,"light");
//    QString slux = QString::number(lux, 'f', 2);
//    QString smac;
//    if(mac<10){
//        smac.append(QString::number(mac));
//        smac="0"+smac;
//    } else {
//        smac.append(QString::number(mac));
//    }
//    QFile file("./WSAN/AILUX.txt");
//        QLabel *testLabel= new QLabel;
//        QString line;
//        qDebug()<<"tes1";
//        if (file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ReadWrite)){
//            QString s;
//            QTextStream stream(&file);
//            qDebug()<<"test2";
//            while (!stream.atEnd()) {
//                QString read = stream.readLine();
//                qDebug()<<read;
//                qDebug()<<read.mid(0,2);
//                if (read.mid(0,2).toInt()==mac) {
//                    //qDebug()<<read.mid(3,5);
//                    //qDebug()<<read.mid(9,6);
//                    if (read.mid(3,5).toDouble()-lux>1 || read.mid(3,5).toDouble()-lux<-1){
//                        //Them cac ham gui khi co sau khac nhieu
//                        sendMqttData(mac,lux,"lux");
//                    } else {
//                        console->insertPlainText("Stable luminance!!! \r\n");
//                    }
//                } else {
//                    qDebug()<<"send new";
//                    if (!read.contains("DELETE")) {
//                        //delete
//                        s.append(read + "\n");
//                    }
//                }
//            }
//            file.resize(0);
//            stream << s;
//            stream <<smac<<":"<<slux<<endl;
//            testLabel->setText(line+"\n");
//        }
//        file.close();
}

// Sang lọc du lieu cho do am dat
void MainWindow::SendAIMois(int mac,int Mois) {
    //QString SMois = QString::number()
    double mois=Mois;
    sendMqttData(mac,mois,"Moisture");
//    QString  smac;
//    if (mac<10) {
//        smac.append(QString::number(mac));
//        smac="0"+smac;
//    } else {
//        smac.append(QString::number(mac));
//    }
//    QFile file("./WSAN/AIMois.txt");
//        QLabel *testLabel= new QLabel;
//        QString line;
//        qDebug()<<"tes1";
//        if (file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ReadWrite)){
//            QString s;
//            QTextStream stream(&file);
//            qDebug()<<"test2";
//            //
//            while (!stream.atEnd()) {
//                QString read = stream.readLine();
//                qDebug()<<read;
//                qDebug()<<read.mid(0,2);
//                if (read.mid(0,2).toInt()==mac) {
//                    //qDebug()<<read.mid(3,5);
//                    //qDebug()<<read.mid(9,6);
//                    if (read.mid(3,5).toDouble()-Mois>1 || read.mid(3,5).toDouble()-Mois<-1){
//                        //Them cac ham gui khi co sau khac nhieu
//                        sendMqttData(mac,Mois,"Moisture");
//                    } else {
//                        console->insertPlainText("Stable luminance!!! \r\n");
//                    }
//                } else {
//                    qDebug()<<"send new";
//                    if (!read.contains("DELETE")) {
//                        //delete
//                        s.append(read + "\n");
//                    }
//                }
//            }
//            //
//            file.resize(0);
//            stream << s;
//            stream <<smac<<":"<<Mois<<endl;
//            testLabel->setText(line+"\n");
//        }
//        file.close();
}
void MainWindow::SendWarningDust(int wr){
	QString Cmd="";
    switch (wr) {
    case 1: // Warning level 1
        Cmd = "0000011$";
        break;

    case 2: // Warning level 2
        Cmd = "0000021$";
        break;

    case 3: // Warning level 3
        Cmd = "0000031$";
        break;

    case 4: // Warning level 4
        Cmd = "0000041$";
        break;

    case 5: // Warning level 5
        Cmd = "0000051$";
        break;
    default:
        break;
    }
    if(Cmd.length() > 4){
	qDebug()<<"hello hao";
        tranceiver->writeData(Cmd);
        QString tmp = "Submit code " + Cmd + "\n";
        console->insertPlainText(tmp);
    }
}

//Sang lọc du lieu cho dust density
void MainWindow::SendAIDD(int mac, double dus){
    QString smac;
    if(mac<10){
        smac.append(QString::number(mac));
        smac="0"+smac;
    } else {
        smac.append(QString::number(mac));
    }
    QFile file("./WSAN/AIDustDensity.txt");
         QLabel *testLabel= new QLabel;
        QString line;
        if(file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ReadWrite)){
            QString s;
            QTextStream stream(&file);
            while (!stream.atEnd()) {
                QString read = stream.readLine();
                qDebug()<<read;
                qDebug()<<read.mid(0,2);
                if (read.mid(0,2).toInt()==mac) {
                    //qDebug()<<read.mid(3,5);
                    //qDebug()<<read.mid(9,6);
                    if (read.mid(3,5).toDouble()-dus>1 || read.mid(3,5).toDouble()-dus<-1){
                        //Them cac ham gui khi co sau khac nhieu
                        sendMqttData(mac,dus,"dust");
                    } else {
                        console->insertPlainText("Stable luminance!!! \r\n");
                    }
                } else {
                    qDebug()<<"send new";
                    if (!read.contains("DELETE")) {
                        //delete
                        s.append(read + "\n");
                    }
                }
            }
            file.resize(0);
            stream << s;
            stream <<smac<<":"<<dus<<endl;
            testLabel->setText(line+"\n");
        }
        file.close();
}


