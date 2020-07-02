/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Terminal1/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      53,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      24,   11,   11,   11, 0x08,
      41,   11,   11,   11, 0x08,
      58,   11,   11,   11, 0x08,
      67,   11,   11,   11, 0x08,
      76,   11,   11,   11, 0x08,
      91,   11,   11,   11, 0x08,
     106,   11,   11,   11, 0x08,
     128,   11,   11,   11, 0x08,
     150,   11,   11,   11, 0x08,
     173,   11,   11,   11, 0x08,
     199,  197,   11,   11, 0x08,
     220,   11,   11,   11, 0x08,
     247,   11,   11,   11, 0x08,
     261,   11,   11,   11, 0x08,
     278,  197,   11,   11, 0x08,
     302,   11,   11,   11, 0x08,
     320,   11,   11,   11, 0x08,
     345,   11,   11,   11, 0x08,
     371,   11,   11,   11, 0x08,
     399,   11,   11,   11, 0x08,
     421,   11,   11,   11, 0x08,
     444,   11,   11,   11, 0x08,
     467,   11,   11,   11, 0x08,
     491,   11,   11,   11, 0x08,
     515,   11,   11,   11, 0x08,
     539,   11,   11,   11, 0x08,
     563,   11,   11,   11, 0x08,
     578,   11,   11,   11, 0x08,
     599,   11,   11,   11, 0x08,
     620,   11,   11,   11, 0x08,
     632,   11,   11,   11, 0x08,
     643,   11,   11,   11, 0x08,
     657,   11,   11,   11, 0x08,
     669,   11,   11,   11, 0x08,
     686,   11,   11,   11, 0x08,
     705,   11,   11,   11, 0x08,
     718,   11,   11,   11, 0x08,
     741,  738,   11,   11, 0x08,
     778,  774,   11,   11, 0x08,
     824,  197,   11,   11, 0x08,
     856,   11,   11,   11, 0x08,
     872,  738,   11,   11, 0x08,
     902,  197,   11,   11, 0x08,
     925,  738,   11,   11, 0x08,
     953,  197,   11,   11, 0x08,
     975,  197,   11,   11, 0x08,
     995,  197,   11,   11, 0x08,
    1016,  197,   11,   11, 0x08,
    1036,  197,   11,   11, 0x08,
    1057,   11,   11,   11, 0x08,
    1071,   11,   11,   11, 0x08,
    1099,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0readySend()\0onrunTimerP(int)\0"
    "onrunTimerL(int)\0onoffP()\0onoffL()\0"
    "oncountdownP()\0oncountdownL()\0"
    "on_btnPrint_clicked()\0on_btnClear_clicked()\0"
    "autoTakePhoto(QString)\0on_pushButton_clicked()\0"
    ",\0sendCommand(int,int)\0"
    "onOpenCloseButtonClicked()\0initMap(bool)\0"
    "initListSensor()\0onNodeJoin(int,QString)\0"
    "onNodeJoinLR(int)\0onImageReceived(QString)\0"
    "onTranceiverData(QString)\0"
    "onTranceiverDataLI(QString)\0"
    "onTempAndHum(QString)\0onTempAndHum1(QString)\0"
    "oncompleteLux(QString)\0oncompleteLux1(QString)\0"
    "onTempAndHumLR(QString)\0oncompleteMois(QString)\0"
    "oncompleteDust(QString)\0SendToServer()\0"
    "on_btnExit_clicked()\0on_btnView_clicked()\0"
    "sendtoWeb()\0sendMqtt()\0mqttConnect()\0"
    "reConnect()\0connectEnabled()\0"
    "subscribePressed()\0subscribed()\0"
    "getSubMQTT(QString)\0,,\0"
    "sendMqttData(int,double,QString)\0,,,\0"
    "sendMqttDataSaved(QString,int,double,QString)\0"
    "sendImageToWeb(QString,QString)\0"
    "sendBroadcast()\0onTempHumi(int,double,double)\0"
    "sendCommandLR(int,int)\0"
    "SendAITH(int,double,double)\0"
    "SendAILUX(int,double)\0SendAIMois(int,int)\0"
    "SendAIDD(int,double)\0onLux_t(int,double)\0"
    "onMois_t(int,double)\0onST(QString)\0"
    "WriteDatatoLogfile(QString)\0"
    "on_btnConfigThreshol_clicked()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->readySend(); break;
        case 1: _t->onrunTimerP((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onrunTimerL((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onoffP(); break;
        case 4: _t->onoffL(); break;
        case 5: _t->oncountdownP(); break;
        case 6: _t->oncountdownL(); break;
        case 7: _t->on_btnPrint_clicked(); break;
        case 8: _t->on_btnClear_clicked(); break;
        case 9: _t->autoTakePhoto((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->on_pushButton_clicked(); break;
        case 11: _t->sendCommand((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->onOpenCloseButtonClicked(); break;
        case 13: _t->initMap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->initListSensor(); break;
        case 15: _t->onNodeJoin((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: _t->onNodeJoinLR((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->onImageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->onTranceiverData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: _t->onTranceiverDataLI((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: _t->onTempAndHum((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->onTempAndHum1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: _t->oncompleteLux((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: _t->oncompleteLux1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: _t->onTempAndHumLR((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 25: _t->oncompleteMois((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 26: _t->oncompleteDust((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 27: _t->SendToServer(); break;
        case 28: _t->on_btnExit_clicked(); break;
        case 29: _t->on_btnView_clicked(); break;
        case 30: _t->sendtoWeb(); break;
        case 31: _t->sendMqtt(); break;
        case 32: _t->mqttConnect(); break;
        case 33: _t->reConnect(); break;
        case 34: _t->connectEnabled(); break;
        case 35: _t->subscribePressed(); break;
        case 36: _t->subscribed(); break;
        case 37: _t->getSubMQTT((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 38: _t->sendMqttData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 39: _t->sendMqttDataSaved((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 40: _t->sendImageToWeb((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 41: _t->sendBroadcast(); break;
        case 42: _t->onTempHumi((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 43: _t->sendCommandLR((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 44: _t->SendAITH((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 45: _t->SendAILUX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 46: _t->SendAIMois((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 47: _t->SendAIDD((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 48: _t->onLux_t((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 49: _t->onMois_t((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 50: _t->onST((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 51: _t->WriteDatatoLogfile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 52: _t->on_btnConfigThreshol_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 53)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 53;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::readySend()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
