/****************************************************************************
** Meta object code from reading C++ file 'proxy.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../proxy/proxy.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'proxy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AppProxy_t {
    QByteArrayData data[13];
    char stringdata0[200];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AppProxy_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AppProxy_t qt_meta_stringdata_AppProxy = {
    {
QT_MOC_LITERAL(0, 0, 8), // "AppProxy"
QT_MOC_LITERAL(1, 9, 18), // "startSignalArrived"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 19), // "autheticationArived"
QT_MOC_LITERAL(4, 49, 18), // "firstMessageArived"
QT_MOC_LITERAL(5, 68, 18), // "serverInfoRecieved"
QT_MOC_LITERAL(6, 87, 15), // "filePartArrived"
QT_MOC_LITERAL(7, 103, 10), // "startProxy"
QT_MOC_LITERAL(8, 114, 16), // "acceptConnection"
QT_MOC_LITERAL(9, 131, 16), // "readFirstMessage"
QT_MOC_LITERAL(10, 148, 22), // "autheticationConfirmed"
QT_MOC_LITERAL(11, 171, 15), // "connectToServer"
QT_MOC_LITERAL(12, 187, 12) // "sendToServer"

    },
    "AppProxy\0startSignalArrived\0\0"
    "autheticationArived\0firstMessageArived\0"
    "serverInfoRecieved\0filePartArrived\0"
    "startProxy\0acceptConnection\0"
    "readFirstMessage\0autheticationConfirmed\0"
    "connectToServer\0sendToServer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AppProxy[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,
       6,    0,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    0,   76,    2, 0x0a /* Public */,
      10,    0,   77,    2, 0x0a /* Public */,
      11,    0,   78,    2, 0x0a /* Public */,
      12,    0,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AppProxy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AppProxy *_t = static_cast<AppProxy *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startSignalArrived(); break;
        case 1: _t->autheticationArived(); break;
        case 2: _t->firstMessageArived(); break;
        case 3: _t->serverInfoRecieved(); break;
        case 4: _t->filePartArrived(); break;
        case 5: _t->startProxy(); break;
        case 6: _t->acceptConnection(); break;
        case 7: _t->readFirstMessage(); break;
        case 8: _t->autheticationConfirmed(); break;
        case 9: _t->connectToServer(); break;
        case 10: _t->sendToServer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AppProxy::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AppProxy::startSignalArrived)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AppProxy::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AppProxy::autheticationArived)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (AppProxy::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AppProxy::firstMessageArived)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (AppProxy::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AppProxy::serverInfoRecieved)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (AppProxy::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AppProxy::filePartArrived)) {
                *result = 4;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AppProxy::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AppProxy.data,
      qt_meta_data_AppProxy,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AppProxy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AppProxy::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AppProxy.stringdata0))
        return static_cast<void*>(const_cast< AppProxy*>(this));
    return QObject::qt_metacast(_clname);
}

int AppProxy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void AppProxy::startSignalArrived()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void AppProxy::autheticationArived()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void AppProxy::firstMessageArived()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void AppProxy::serverInfoRecieved()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void AppProxy::filePartArrived()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
