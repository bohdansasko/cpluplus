/****************************************************************************
** Meta object code from reading C++ file 'tankforplayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BattleCity/tankforplayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tankforplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TankForPlayer_t {
    QByteArrayData data[9];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TankForPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TankForPlayer_t qt_meta_stringdata_TankForPlayer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "TankForPlayer"
QT_MOC_LITERAL(1, 14, 29), // "signalAddKilledBotToStatistic"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 12), // "slotTankShot"
QT_MOC_LITERAL(4, 58, 10), // "senderName"
QT_MOC_LITERAL(5, 69, 25), // "slotAddDeadBotToStatistic"
QT_MOC_LITERAL(6, 95, 9), // "typeOfBot"
QT_MOC_LITERAL(7, 105, 26), // "slotReceiveTypeOfKilledBot"
QT_MOC_LITERAL(8, 132, 4) // "name"

    },
    "TankForPlayer\0signalAddKilledBotToStatistic\0"
    "\0slotTankShot\0senderName\0"
    "slotAddDeadBotToStatistic\0typeOfBot\0"
    "slotReceiveTypeOfKilledBot\0name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TankForPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   37,    2, 0x0a /* Public */,
       5,    1,   40,    2, 0x0a /* Public */,
       7,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,

       0        // eod
};

void TankForPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TankForPlayer *_t = static_cast<TankForPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalAddKilledBotToStatistic((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->slotTankShot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->slotAddDeadBotToStatistic((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->slotReceiveTypeOfKilledBot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TankForPlayer::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TankForPlayer::signalAddKilledBotToStatistic)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject TankForPlayer::staticMetaObject = {
    { &Tank::staticMetaObject, qt_meta_stringdata_TankForPlayer.data,
      qt_meta_data_TankForPlayer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TankForPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TankForPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TankForPlayer.stringdata0))
        return static_cast<void*>(const_cast< TankForPlayer*>(this));
    return Tank::qt_metacast(_clname);
}

int TankForPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Tank::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TankForPlayer::signalAddKilledBotToStatistic(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
