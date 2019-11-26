#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "console.h"
#include <QTimer>
#include "qextserialenumerator.h"
#include "qextserialport.h"
#include "hled.h"
#include "gps.h"
#include <QThread>
#include <QList>
#include "sensor.h"
#include "define.h"
#include "tranceiver.h"
#include "tranceiverlora.h"
#include "Dialog/editsensorplacedialog.h"
#include "Dialog/newsensordialog.h"
#include "Dialog/retasksensordialog.h"
#include "Dialog/retskalldialog.h"
#include "Dialog/sensorinformationdialog.h"
#include "Dialog/startuplocationdialog.h"
#include "Dialog/setupserialportdialog.h"
#include "Dialog/aboutdialog.h"
#include "Dialog/serverdialog.h"
#include "Dialog/configthreshold.h"
#include <QNetworkAccessManager>
#include "QHash"
#include "QTime"
#include "qtmosq.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Q_INVOKABLE void mySendCommand(int, int);

protected:
    void changeEvent(QEvent *e);

private:
    QString getIp(int);
    void loadHtmlPage();
    void errorOccured(QString);
    void showMarker(int);
    bool checkJoin(int);
    int getIndexSensor(int);
    int getIndexMarker(int);
    QString findNearestNode();
    void updateListSensor();
    void delay(int secondsToWait);
    int tPredict(QTime t1, QTime t2, double d1, double d2);
    double distance(double lat1, double lng1, double lat2, double lng2);
    double bearing(double lat1, double lng1, double lat2, double lng2);
    double deg2rad(double deg);
    void WriteTextAppend(QString, QString);
    void findLastPoint(QString &lat2, QString &lng2, double lat1, double lng1, double dis, double bear);
    void setDate();

    //for UAV
    void SetupPortSerial();
    void AlwaysOpenPort();
    void AlwaysOpenPortLR();
signals:
    void readySend();
//    void runTimerP(int);
//    void runTimerL(int);

private slots:
    //void on_webView_loadFinished(bool );
//    void on_btngetNearestNode_clicked();
    void onrunTimerP(int);
    void onrunTimerL(int);
    void onoffP();
    void onoffL();
    void oncountdownP();
    void oncountdownL();
    void onCommandLR();
    void on_btnPrint_clicked();
   // void on_btnUpdate_clicked();
    void on_btnClear_clicked();
    void Send_Broadcast();
    void autoTakePhoto(QString);

    void on_pushButton_clicked();
//     on_pushButton_2_clicked();
    Q_INVOKABLE void sendCommand(int, int);
    void onOpenCloseButtonClicked();
    void onGpsData(QString);
    void initMap(bool);
    void initListSensor();
    void onNodeJoin(int, QString);
    void onNodeJoinLR(int);
    void onImageReceived(QString);
    //Map
//    void addMarker(QString);
//    void removeAllMarkers();
//    void ClearMap();
//    void ShowAllSensor(bool);
//    void ShowJoinedSensor(bool);
//    void zoomMap(QString);
//    void gotoPlaceByCoordinate(QString);
//    void populateJavaScriptWindowObject();
    //Tranceiver
    void onTranceiverData(QString);
    void onTranceiverDataLI(QString);
	void onreceivedDataLR(QString);
    void onTempAndHum(QString);
    void onTempAndHum1(QString);
    void oncompleteLux(QString);
    void onTempAndHumLR(QString);
    void oncompleteMois(QString);
    void oncompleteDust(QString);
    //checkbox
    void onGpsStatus(bool);
    //Action
    void startLinphone();
    void ShowAbout();
    void RetaskOne();
    void RetaskAll();
    void AddNewSensor();
    void EditSensorPlace();
    void ShowSensorInformation();
    void StartupLocation();
    void SetupSerialPort();
    void SendToServer();
    //Push button
    void on_btnExit_clicked();
    void on_btnView_clicked();
    //////////////
    void sendtoWeb();
    //mqtt
    void sendMqtt();
    void mqttConnect();
    void connectEnabled();
//    void sendMqttTandH(int,double,double);
//    void sendMqttLux(int,double);
//    void sendMqttTandHLR(int,double,double);
//    void sendMqttDust(int,double);
//    void sendMqttMois(int,int);
    void sendMqttData(int, double, QString);
    void sendMqttDataSaved(QString, int, double, QString);
    //
    void sendImageToWeb(QString,QString);
    void sendBroadcast();
    void onTempHumi(int, double, double);
    void onLR(int,int);
    void SendAITH(int, double, double);
    void SendAILUX(int, double);
    void SendAIMois(int,int);
    void SendAIDD(int , double );
    void SendWarningDust(int);
    void onLux_t(int, double);
    void onMois_t(int, double);
    void onST(QString);
//    void onLRHTD(int,int,int);
    //Graph
    void makePlot();

    /* Chinh sua code cho UAV */
    void WriteDatatoLogfile(QString);
    //void on_pushButton_pressed();

    //void on_pushButton_clicked(bool checked);

    void on_btnConfigThreshol_clicked();



    //void on_btnSendLora_clicked();

private:
    Ui::MainWindow *ui;
    Console *console;
    GPS *gps;
    QThread *thread_gps, *thread_tranceiver, *thread_receivefromweb,*thread_lora;
    HLed *led;
    QString m_organizationName, m_appName;
    bool gpsStarted, tranceiverStarted, gpsDataReceived, sended, detectedFlag, receivedFlag, loraStarted;
    QList<Sensor*> ListSensor;
    QList<bool> ListSensorStt;
    QList<double> ListSensorArg;
    QList<double> ListSensorTemp;
    QList<double> ListSensorDeltaTemp;
    Tranceiver *tranceiver;
    tranceiverlora * lora;
    QNetworkAccessManager *http1;
    int *joinedMac;
    QString *joinedAddress;
    int indexJoined;
    QHash <QString, QString> hash;
    QHash <QString, QTime> movDetectTime;
    QHash <QString, double> maxTemp;
    double d1, d2;
    double a_test, b_test;
    DbManager database;
    /* Chinh sua code cho UAV */
    QTimer *timerP;
    QTimer *timerL;
    int sTimeP,sTimeL;
    QString fileName;
    /************* UAV **********/
    /*mqtt */
    qtmosq* mosq = NULL;
    //

};

#endif // MAINWINDOW_H
