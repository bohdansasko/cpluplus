/****************************************************************************
** Meta object code from reading C++ file 'dialogsearchpacient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialogsearchpacient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogsearchpacient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_dialogsearchpacient_t {
    QByteArrayData data[11];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dialogsearchpacient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dialogsearchpacient_t qt_meta_stringdata_dialogsearchpacient = {
    {
QT_MOC_LITERAL(0, 0, 19), // "dialogsearchpacient"
QT_MOC_LITERAL(1, 20, 8), // "sendData"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 2), // "id"
QT_MOC_LITERAL(4, 33, 11), // "findPacient"
QT_MOC_LITERAL(5, 45, 1), // "s"
QT_MOC_LITERAL(6, 47, 10), // "CancelFind"
QT_MOC_LITERAL(7, 58, 10), // "getDetails"
QT_MOC_LITERAL(8, 69, 8), // "getIndex"
QT_MOC_LITERAL(9, 78, 3), // "ind"
QT_MOC_LITERAL(10, 82, 11) // "switchOnBtn"

    },
    "dialogsearchpacient\0sendData\0\0id\0"
    "findPacient\0s\0CancelFind\0getDetails\0"
    "getIndex\0ind\0switchOnBtn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dialogsearchpacient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   47,    2, 0x08 /* Private */,
       6,    0,   50,    2, 0x08 /* Private */,
       7,    0,   51,    2, 0x08 /* Private */,
       8,    1,   52,    2, 0x08 /* Private */,
      10,    1,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    9,
    QMetaType::Void, QMetaType::QModelIndex,    2,

       0        // eod
};

void dialogsearchpacient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        dialogsearchpacient *_t = static_cast<dialogsearchpacient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->findPacient((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->CancelFind(); break;
        case 3: _t->getDetails(); break;
        case 4: _t->getIndex((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 5: _t->switchOnBtn((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (dialogsearchpacient::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&dialogsearchpacient::sendData)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject dialogsearchpacient::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dialogsearchpacient.data,
      qt_meta_data_dialogsearchpacient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *dialogsearchpacient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dialogsearchpacient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_dialogsearchpacient.stringdata0))
        return static_cast<void*>(const_cast< dialogsearchpacient*>(this));
    return QDialog::qt_metacast(_clname);
}

int dialogsearchpacient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void dialogsearchpacient::sendData(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
