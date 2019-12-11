/****************************************************************************
** Meta object code from reading C++ file 'retasksensordialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Terminal1/Dialog/retasksensordialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'retasksensordialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RetaskSensorDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RetaskSensorDialog[] = {
    "RetaskSensorDialog\0\0"
    "on_cbxMac_currentIndexChanged(QString)\0"
};

void RetaskSensorDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RetaskSensorDialog *_t = static_cast<RetaskSensorDialog *>(_o);
        switch (_id) {
        case 0: _t->on_cbxMac_currentIndexChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RetaskSensorDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RetaskSensorDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_RetaskSensorDialog,
      qt_meta_data_RetaskSensorDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RetaskSensorDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RetaskSensorDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RetaskSensorDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RetaskSensorDialog))
        return static_cast<void*>(const_cast< RetaskSensorDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int RetaskSensorDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
