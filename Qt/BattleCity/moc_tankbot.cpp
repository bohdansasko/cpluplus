/****************************************************************************
** Meta object code from reading C++ file 'tankbot.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BattleCity/tankbot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tankbot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TankBot_t {
    QByteArrayData data[16];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TankBot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TankBot_t qt_meta_stringdata_TankBot = {
    {
QT_MOC_LITERAL(0, 0, 7), // "TankBot"
QT_MOC_LITERAL(1, 8, 18), // "signalOneSearchWay"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 7), // "x_begin"
QT_MOC_LITERAL(4, 36, 7), // "y_begin"
QT_MOC_LITERAL(5, 44, 5), // "x_end"
QT_MOC_LITERAL(6, 50, 5), // "y_end"
QT_MOC_LITERAL(7, 56, 12), // "slotTankShot"
QT_MOC_LITERAL(8, 69, 10), // "senderName"
QT_MOC_LITERAL(9, 80, 22), // "slotForStartSearchPath"
QT_MOC_LITERAL(10, 103, 14), // "slotSearchPath"
QT_MOC_LITERAL(11, 118, 5), // "Atack"
QT_MOC_LITERAL(12, 124, 7), // "xPlayer"
QT_MOC_LITERAL(13, 132, 7), // "yPlayer"
QT_MOC_LITERAL(14, 140, 30), // "slotSearchNewWayAfterCollision"
QT_MOC_LITERAL(15, 171, 9) // "useRotate"

    },
    "TankBot\0signalOneSearchWay\0\0x_begin\0"
    "y_begin\0x_end\0y_end\0slotTankShot\0"
    "senderName\0slotForStartSearchPath\0"
    "slotSearchPath\0Atack\0xPlayer\0yPlayer\0"
    "slotSearchNewWayAfterCollision\0useRotate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TankBot[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   58,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,
      10,    4,   62,    2, 0x0a /* Public */,
      11,    2,   71,    2, 0x0a /* Public */,
      11,    0,   76,    2, 0x0a /* Public */,
      14,    1,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,

       0        // eod
};

void TankBot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TankBot *_t = static_cast<TankBot *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalOneSearchWay((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->slotTankShot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->slotForStartSearchPath(); break;
        case 3: _t->slotSearchPath((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 4: _t->Atack((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->Atack(); break;
        case 6: _t->slotSearchNewWayAfterCollision((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TankBot::*_t)(int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TankBot::signalOneSearchWay)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject TankBot::staticMetaObject = {
    { &Tank::staticMetaObject, qt_meta_stringdata_TankBot.data,
      qt_meta_data_TankBot,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TankBot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TankBot::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TankBot.stringdata0))
        return static_cast<void*>(const_cast< TankBot*>(this));
    return Tank::qt_metacast(_clname);
}

int TankBot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Tank::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TankBot::signalOneSearchWay(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
