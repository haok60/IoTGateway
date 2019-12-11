/****************************************************************************
** Meta object code from reading C++ file 'sensorinformationdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Terminal1/Dialog/sensorinformationdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sensorinformationdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SensorInformationDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x08,
      42,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SensorInformationDialog[] = {
    "SensorInformationDialog\0\0SetView(QString)\0"
    "on_btnClose_clicked()\0"
};

void SensorInformationDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SensorInformationDialog *_t = static_cast<SensorInformationDialog *>(_o);
        switch (_id) {
        case 0: _t->SetView((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_btnClose_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SensorInformationDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SensorInformationDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SensorInformationDialog,
      qt_meta_data_SensorInformationDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SensorInformationDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SensorInformationDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SensorInformationDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SensorInformationDialog))
        return static_cast<void*>(const_cast< SensorInformationDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SensorInformationDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
