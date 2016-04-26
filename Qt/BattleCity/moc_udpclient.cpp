/****************************************************************************
** Meta object code from reading C++ file 'udpclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "udpclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UdpClient_t {
    QByteArrayData data[10];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UdpClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UdpClient_t qt_meta_stringdata_UdpClient = {
    {
QT_MOC_LITERAL(0, 0, 9), // "UdpClient"
QT_MOC_LITERAL(1, 10, 20), // "signalConnectExecute"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 10), // "nameServer"
QT_MOC_LITERAL(4, 43, 29), // "signalReadInformationOpponent"
QT_MOC_LITERAL(5, 73, 1), // "x"
QT_MOC_LITERAL(6, 75, 1), // "y"
QT_MOC_LITERAL(7, 77, 6), // "rotate"
QT_MOC_LITERAL(8, 84, 4), // "shot"
QT_MOC_LITERAL(9, 89, 21) // "slotReadMessageClient"

    },
    "UdpClient\0signalConnectExecute\0\0"
    "nameServer\0signalReadInformationOpponent\0"
    "x\0y\0rotate\0shot\0slotReadMessageClient"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UdpClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    4,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Bool,    5,    6,    7,    8,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void UdpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UdpClient *_t = static_cast<UdpClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalConnectExecute((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->signalReadInformationOpponent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 2: _t->slotReadMessageClient(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UdpClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UdpClient::signalConnectExecute)) {
                *result = 0;
            }
        }
        {
            typedef void (UdpClient::*_t)(int , int , int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UdpClient::signalReadInformationOpponent)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject UdpClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UdpClient.data,
      qt_meta_data_UdpClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UdpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UdpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UdpClient.stringdata0))
        return static_cast<void*>(const_cast< UdpClient*>(this));
    return QObject::qt_metacast(_clname);
}

int UdpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void UdpClient::signalConnectExecute(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UdpClient::signalReadInformationOpponent(int _t1, int _t2, int _t3, bool _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
