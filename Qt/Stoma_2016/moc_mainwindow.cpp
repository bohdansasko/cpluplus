/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyQLabel_t {
    QByteArrayData data[3];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyQLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyQLabel_t qt_meta_stringdata_MyQLabel = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MyQLabel"
QT_MOC_LITERAL(1, 9, 12), // "mouseClicked"
QT_MOC_LITERAL(2, 22, 0) // ""

    },
    "MyQLabel\0mouseClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyQLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void MyQLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyQLabel *_t = static_cast<MyQLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyQLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyQLabel::mouseClicked)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MyQLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_MyQLabel.data,
      qt_meta_data_MyQLabel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyQLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyQLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyQLabel.stringdata0))
        return static_cast<void*>(const_cast< MyQLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int MyQLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void MyQLabel::mouseClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
struct qt_meta_stringdata_MyQTextEdit_t {
    QByteArrayData data[4];
    char stringdata0[44];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyQTextEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyQTextEdit_t qt_meta_stringdata_MyQTextEdit = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MyQTextEdit"
QT_MOC_LITERAL(1, 12, 11), // "signalLeave"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 18) // "slotSetTextChanged"

    },
    "MyQTextEdit\0signalLeave\0\0slotSetTextChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyQTextEdit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void MyQTextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyQTextEdit *_t = static_cast<MyQTextEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalLeave(); break;
        case 1: _t->slotSetTextChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyQTextEdit::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyQTextEdit::signalLeave)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MyQTextEdit::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata_MyQTextEdit.data,
      qt_meta_data_MyQTextEdit,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyQTextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyQTextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyQTextEdit.stringdata0))
        return static_cast<void*>(const_cast< MyQTextEdit*>(this));
    return QTextEdit::qt_metacast(_clname);
}

int MyQTextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void MyQTextEdit::signalLeave()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
struct qt_meta_stringdata_MySortFilterProxyModel_t {
    QByteArrayData data[1];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MySortFilterProxyModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MySortFilterProxyModel_t qt_meta_stringdata_MySortFilterProxyModel = {
    {
QT_MOC_LITERAL(0, 0, 22) // "MySortFilterProxyModel"

    },
    "MySortFilterProxyModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MySortFilterProxyModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void MySortFilterProxyModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject MySortFilterProxyModel::staticMetaObject = {
    { &QSortFilterProxyModel::staticMetaObject, qt_meta_stringdata_MySortFilterProxyModel.data,
      qt_meta_data_MySortFilterProxyModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MySortFilterProxyModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MySortFilterProxyModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MySortFilterProxyModel.stringdata0))
        return static_cast<void*>(const_cast< MySortFilterProxyModel*>(this));
    return QSortFilterProxyModel::qt_metacast(_clname);
}

int MySortFilterProxyModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSortFilterProxyModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[32];
    char stringdata0[605];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "slotAddPacient"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 17), // "slotSearchPacient"
QT_MOC_LITERAL(4, 45, 2), // "id"
QT_MOC_LITERAL(5, 48, 20), // "slotOpenDialogSearch"
QT_MOC_LITERAL(6, 69, 15), // "slotChangePhoto"
QT_MOC_LITERAL(7, 85, 17), // "slotDeletePacient"
QT_MOC_LITERAL(8, 103, 15), // "slotDeletePhoto"
QT_MOC_LITERAL(9, 119, 26), // "slotDeleteInfoFromDataView"
QT_MOC_LITERAL(10, 146, 18), // "slotUpdateBadTeeth"
QT_MOC_LITERAL(11, 165, 6), // "nOfBad"
QT_MOC_LITERAL(12, 172, 18), // "slotDeleteTeethImg"
QT_MOC_LITERAL(13, 191, 15), // "slotDeleteTeeth"
QT_MOC_LITERAL(14, 207, 20), // "slotPaintRectInTeeth"
QT_MOC_LITERAL(15, 228, 18), // "slotAddTeethImages"
QT_MOC_LITERAL(16, 247, 36), // "slotDownloadTeethImgsSelected..."
QT_MOC_LITERAL(17, 284, 12), // "currentTeeth"
QT_MOC_LITERAL(18, 297, 22), // "slotShowMoreInfoATeeth"
QT_MOC_LITERAL(19, 320, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(20, 337, 25), // "slotShowTeethInListWidget"
QT_MOC_LITERAL(21, 363, 2), // "ci"
QT_MOC_LITERAL(22, 366, 23), // "slotUpdateStatusOfTeeth"
QT_MOC_LITERAL(23, 390, 21), // "slotUpdateDateOfTeeth"
QT_MOC_LITERAL(24, 412, 22), // "slotUpdateDateViewMore"
QT_MOC_LITERAL(25, 435, 25), // "slotOpenDialogAddDataView"
QT_MOC_LITERAL(26, 461, 15), // "slotAddDateView"
QT_MOC_LITERAL(27, 477, 25), // "slotUpdateInfoAboutClient"
QT_MOC_LITERAL(28, 503, 31), // "slotDownloadDataInComponentTab1"
QT_MOC_LITERAL(29, 535, 5), // "index"
QT_MOC_LITERAL(30, 541, 31), // "slotDownloadDataInComponentTab2"
QT_MOC_LITERAL(31, 573, 31) // "slotDownloadDataInComponentTab3"

    },
    "MainWindow\0slotAddPacient\0\0slotSearchPacient\0"
    "id\0slotOpenDialogSearch\0slotChangePhoto\0"
    "slotDeletePacient\0slotDeletePhoto\0"
    "slotDeleteInfoFromDataView\0"
    "slotUpdateBadTeeth\0nOfBad\0slotDeleteTeethImg\0"
    "slotDeleteTeeth\0slotPaintRectInTeeth\0"
    "slotAddTeethImages\0"
    "slotDownloadTeethImgsSelectedPacient\0"
    "currentTeeth\0slotShowMoreInfoATeeth\0"
    "QListWidgetItem*\0slotShowTeethInListWidget\0"
    "ci\0slotUpdateStatusOfTeeth\0"
    "slotUpdateDateOfTeeth\0slotUpdateDateViewMore\0"
    "slotOpenDialogAddDataView\0slotAddDateView\0"
    "slotUpdateInfoAboutClient\0"
    "slotDownloadDataInComponentTab1\0index\0"
    "slotDownloadDataInComponentTab2\0"
    "slotDownloadDataInComponentTab3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  134,    2, 0x08 /* Private */,
       3,    1,  135,    2, 0x08 /* Private */,
       5,    0,  138,    2, 0x08 /* Private */,
       6,    0,  139,    2, 0x08 /* Private */,
       7,    0,  140,    2, 0x08 /* Private */,
       8,    0,  141,    2, 0x08 /* Private */,
       9,    0,  142,    2, 0x08 /* Private */,
      10,    1,  143,    2, 0x08 /* Private */,
      12,    0,  146,    2, 0x08 /* Private */,
      13,    0,  147,    2, 0x08 /* Private */,
      14,    0,  148,    2, 0x08 /* Private */,
      15,    0,  149,    2, 0x08 /* Private */,
      16,    1,  150,    2, 0x08 /* Private */,
      18,    1,  153,    2, 0x08 /* Private */,
      20,    1,  156,    2, 0x08 /* Private */,
      22,    0,  159,    2, 0x08 /* Private */,
      23,    1,  160,    2, 0x08 /* Private */,
      24,    0,  163,    2, 0x08 /* Private */,
      25,    0,  164,    2, 0x08 /* Private */,
      26,    2,  165,    2, 0x08 /* Private */,
      27,    0,  170,    2, 0x08 /* Private */,
      28,    1,  171,    2, 0x08 /* Private */,
      30,    1,  174,    2, 0x08 /* Private */,
      31,    1,  177,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, 0x80000000 | 19,    2,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate, QMetaType::QString,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   29,
    QMetaType::Void, QMetaType::QModelIndex,   29,
    QMetaType::Void, QMetaType::QModelIndex,   29,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotAddPacient(); break;
        case 1: _t->slotSearchPacient((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slotOpenDialogSearch(); break;
        case 3: _t->slotChangePhoto(); break;
        case 4: _t->slotDeletePacient(); break;
        case 5: _t->slotDeletePhoto(); break;
        case 6: _t->slotDeleteInfoFromDataView(); break;
        case 7: _t->slotUpdateBadTeeth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slotDeleteTeethImg(); break;
        case 9: _t->slotDeleteTeeth(); break;
        case 10: _t->slotPaintRectInTeeth(); break;
        case 11: _t->slotAddTeethImages(); break;
        case 12: _t->slotDownloadTeethImgsSelectedPacient((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->slotShowMoreInfoATeeth((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 14: _t->slotShowTeethInListWidget((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->slotUpdateStatusOfTeeth(); break;
        case 16: _t->slotUpdateDateOfTeeth((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 17: _t->slotUpdateDateViewMore(); break;
        case 18: _t->slotOpenDialogAddDataView(); break;
        case 19: _t->slotAddDateView((*reinterpret_cast< QDate(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 20: _t->slotUpdateInfoAboutClient(); break;
        case 21: _t->slotDownloadDataInComponentTab1((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 22: _t->slotDownloadDataInComponentTab2((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 23: _t->slotDownloadDataInComponentTab3((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 24;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
