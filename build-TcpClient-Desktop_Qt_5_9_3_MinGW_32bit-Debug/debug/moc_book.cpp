/****************************************************************************
** Meta object code from reading C++ file 'book.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TcpClient/book.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'book.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Book_t {
    QByteArrayData data[16];
    char stringdata0[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Book_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Book_t qt_meta_stringdata_Book = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Book"
QT_MOC_LITERAL(1, 5, 9), // "createDir"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 9), // "flushFile"
QT_MOC_LITERAL(4, 26, 6), // "delDir"
QT_MOC_LITERAL(5, 33, 10), // "reNameFile"
QT_MOC_LITERAL(6, 44, 8), // "enterDir"
QT_MOC_LITERAL(7, 53, 5), // "index"
QT_MOC_LITERAL(8, 59, 12), // "returnPreDir"
QT_MOC_LITERAL(9, 72, 10), // "uploadFile"
QT_MOC_LITERAL(10, 83, 10), // "delRegFile"
QT_MOC_LITERAL(11, 94, 12), // "downloadFile"
QT_MOC_LITERAL(12, 107, 14), // "uploadFileData"
QT_MOC_LITERAL(13, 122, 9), // "shareFile"
QT_MOC_LITERAL(14, 132, 8), // "moveFile"
QT_MOC_LITERAL(15, 141, 12) // "selectDesDir"

    },
    "Book\0createDir\0\0flushFile\0delDir\0"
    "reNameFile\0enterDir\0index\0returnPreDir\0"
    "uploadFile\0delRegFile\0downloadFile\0"
    "uploadFileData\0shareFile\0moveFile\0"
    "selectDesDir"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Book[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    1,   83,    2, 0x0a /* Public */,
       8,    0,   86,    2, 0x0a /* Public */,
       9,    0,   87,    2, 0x0a /* Public */,
      10,    0,   88,    2, 0x0a /* Public */,
      11,    0,   89,    2, 0x0a /* Public */,
      12,    0,   90,    2, 0x0a /* Public */,
      13,    0,   91,    2, 0x0a /* Public */,
      14,    0,   92,    2, 0x0a /* Public */,
      15,    0,   93,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Book::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Book *_t = static_cast<Book *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createDir(); break;
        case 1: _t->flushFile(); break;
        case 2: _t->delDir(); break;
        case 3: _t->reNameFile(); break;
        case 4: _t->enterDir((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->returnPreDir(); break;
        case 6: _t->uploadFile(); break;
        case 7: _t->delRegFile(); break;
        case 8: _t->downloadFile(); break;
        case 9: _t->uploadFileData(); break;
        case 10: _t->shareFile(); break;
        case 11: _t->moveFile(); break;
        case 12: _t->selectDesDir(); break;
        default: ;
        }
    }
}

const QMetaObject Book::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Book.data,
      qt_meta_data_Book,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Book::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Book::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Book.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Book::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
