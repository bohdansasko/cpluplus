/****************************************************************************
** Meta object code from reading C++ file 'bonus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "bonus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bonus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CBonus_t {
    QByteArrayData data[6];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CBonus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CBonus_t qt_meta_stringdata_CBonus = {
    {
QT_MOC_LITERAL(0, 0, 6), // "CBonus"
QT_MOC_LITERAL(1, 7, 21), // "signalSendRemoveBonus"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 13), // "slotShowScore"
QT_MOC_LITERAL(4, 44, 17), // "slotSendShowBonus"
QT_MOC_LITERAL(5, 62, 19) // "slotSendRemoveBonus"

    },
    "CBonus\0signalSendRemoveBonus\0\0"
    "slotShowScore\0slotSendShowBonus\0"
    "slotSendRemoveBonus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CBonus[] = {

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
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CBonus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CBonus *_t = static_cast<CBonus *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSendRemoveBonus(); break;
        case 1: _t->slotShowScore(); break;
        case 2: _t->slotSendShowBonus(); break;
        case 3: _t->slotSendRemoveBonus(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CBonus::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CBonus::signalSendRemoveBonus)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CBonus::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CBonus.data,
      qt_meta_data_CBonus,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CBonus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CBonus::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CBonus.stringdata0))
        return static_cast<void*>(const_cast< CBonus*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< CBonus*>(this));
    return QObject::qt_metacast(_clname);
}

int CBonus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void CBonus::signalSendRemoveBonus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
