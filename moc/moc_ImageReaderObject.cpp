/****************************************************************************
** Meta object code from reading C++ file 'ImageReaderObject.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ImageReaderObject.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageReaderObject.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ImageReaderObject_t {
    QByteArrayData data[15];
    char stringdata0[277];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageReaderObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageReaderObject_t qt_meta_stringdata_ImageReaderObject = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ImageReaderObject"
QT_MOC_LITERAL(1, 18, 11), // "getAPicture"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 9), // "imageSize"
QT_MOC_LITERAL(4, 41, 11), // "picturePath"
QT_MOC_LITERAL(5, 53, 36), // "Namespace::ImageReaderObject:..."
QT_MOC_LITERAL(6, 90, 14), // "onDestoryMutex"
QT_MOC_LITERAL(7, 105, 35), // "Namespace::ImageReaderObject:..."
QT_MOC_LITERAL(8, 141, 13), // "onDestoryData"
QT_MOC_LITERAL(9, 155, 16), // "PictureDelegate*"
QT_MOC_LITERAL(10, 172, 15), // "pictureDelegate"
QT_MOC_LITERAL(11, 188, 37), // "Namespace::ImageReaderObject:..."
QT_MOC_LITERAL(12, 226, 8), // "ansMutex"
QT_MOC_LITERAL(13, 235, 37), // "Namespace::ImageReaderObject:..."
QT_MOC_LITERAL(14, 273, 3) // "ans"

    },
    "ImageReaderObject\0getAPicture\0\0imageSize\0"
    "picturePath\0Namespace::ImageReaderObject::SMutex\0"
    "onDestoryMutex\0Namespace::ImageReaderObject::SBool\0"
    "onDestoryData\0PictureDelegate*\0"
    "pictureDelegate\0Namespace::ImageReaderObject::SSMutex\0"
    "ansMutex\0Namespace::ImageReaderObject::SPixmap\0"
    "ans"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageReaderObject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    7,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QSize, QMetaType::QString, 0x80000000 | 5, 0x80000000 | 7, 0x80000000 | 9, 0x80000000 | 11, 0x80000000 | 13,    3,    4,    6,    8,   10,   12,   14,

       0        // eod
};

void ImageReaderObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageReaderObject *_t = static_cast<ImageReaderObject *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getAPicture((*reinterpret_cast< const QSize(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< Namespace::ImageReaderObject::SMutex(*)>(_a[3])),(*reinterpret_cast< Namespace::ImageReaderObject::SBool(*)>(_a[4])),(*reinterpret_cast< PictureDelegate*(*)>(_a[5])),(*reinterpret_cast< Namespace::ImageReaderObject::SSMutex(*)>(_a[6])),(*reinterpret_cast< Namespace::ImageReaderObject::SPixmap(*)>(_a[7]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Namespace::ImageReaderObject::SBool >(); break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Namespace::ImageReaderObject::SMutex >(); break;
            case 6:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Namespace::ImageReaderObject::SPixmap >(); break;
            case 5:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Namespace::ImageReaderObject::SSMutex >(); break;
            }
            break;
        }
    }
}

const QMetaObject ImageReaderObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ImageReaderObject.data,
      qt_meta_data_ImageReaderObject,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ImageReaderObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageReaderObject::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ImageReaderObject.stringdata0))
        return static_cast<void*>(const_cast< ImageReaderObject*>(this));
    return QObject::qt_metacast(_clname);
}

int ImageReaderObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
