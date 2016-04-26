/****************************************************************************
** Meta object code from reading C++ file 'tank.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BattleCity/tank.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tank.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Tank_t {
    QByteArrayData data[10];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tank_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tank_t qt_meta_stringdata_Tank = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Tank"
QT_MOC_LITERAL(1, 5, 10), // "signalShot"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 10), // "typeObject"
QT_MOC_LITERAL(4, 28, 14), // "signalGameOver"
QT_MOC_LITERAL(5, 43, 18), // "signalSearchNewWay"
QT_MOC_LITERAL(6, 62, 9), // "useRotate"
QT_MOC_LITERAL(7, 72, 12), // "slotMoveTank"
QT_MOC_LITERAL(8, 85, 13), // "slotAllowShot"
QT_MOC_LITERAL(9, 99, 12) // "slotGameOver"

    },
    "Tank\0signalShot\0\0typeObject\0signalGameOver\0"
    "signalSearchNewWay\0useRotate\0slotMoveTank\0"
    "slotAllowShot\0slotGameOver"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tank[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    0,   47,    2, 0x06 /* Public */,
       5,    1,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   51,    2, 0x0a /* Public */,
       8,    0,   52,    2, 0x0a /* Public */,
       9,    0,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Tank::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Tank *_t = static_cast<Tank *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalShot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->signalGameOver(); break;
        case 2: _t->signalSearchNewWay((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->slotMoveTank(); break;
        case 4: _t->slotAllowShot(); break;
        case 5: _t->slotGameOver(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Tank::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Tank::signalShot)) {
                *result = 0;
            }
        }
        {
            typedef void (Tank::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Tank::signalGameOver)) {
                *result = 1;
            }
        }
        {
            typedef void (Tank::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Tank::signalSearchNewWay)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject Tank::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Tank.data,
      qt_meta_data_Tank,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Tank::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tank::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Tank.stringdata0))
        return static_cast<void*>(const_cast< Tank*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< Tank*>(this));
    return QObject::qt_metacast(_clname);
}

int Tank::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Tank::signalShot(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Tank::signalGameOver()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Tank::signalSearchNewWay(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
