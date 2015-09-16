/****************************************************************************
** Meta object code from reading C++ file 'PictureDelegate.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PictureDelegate.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PictureDelegate.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PictureDelegate_t {
    QByteArrayData data[15];
    char stringdata0[275];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PictureDelegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PictureDelegate_t qt_meta_stringdata_PictureDelegate = {
    {
QT_MOC_LITERAL(0, 0, 15), // "PictureDelegate"
QT_MOC_LITERAL(1, 16, 11), // "getAPicture"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 9), // "imageSize"
QT_MOC_LITERAL(4, 39, 11), // "picturePath"
QT_MOC_LITERAL(5, 51, 36), // "Namespace::ImageReaderObject:..."
QT_MOC_LITERAL(6, 88, 14), // "onDestoryMutex"
QT_MOC_LITERAL(7, 103, 35), // "Namespace::ImageReaderObject:..."
QT_MOC_LITERAL(8, 139, 13), // "onDestoryData"
QT_MOC_LITERAL(9, 153, 16), // "PictureDelegate*"
QT_MOC_LITERAL(10, 170, 15), // "pictureDelegate"
QT_MOC_LITERAL(11, 186, 37), // "Namespace::ImageReaderObject:..."
QT_MOC_LITERAL(12, 224, 8), // "ansMutex"
QT_MOC_LITERAL(13, 233, 37), // "Namespace::ImageReaderObject:..."
QT_MOC_LITERAL(14, 271, 3) // "ans"

    },
    "PictureDelegate\0getAPicture\0\0imageSize\0"
    "picturePath\0Namespace::ImageReaderObject::SMutex\0"
    "onDestoryMutex\0Namespace::ImageReaderObject::SBool\0"
    "onDestoryData\0PictureDelegate*\0"
    "pictureDelegate\0Namespace::ImageReaderObject::SSMutex\0"
    "ansMutex\0Namespace::ImageReaderObject::SPixmap\0"
    "ans"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PictureDelegate[] = {

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
       1,    7,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QSize, QMetaType::QString, 0x80000000 | 5, 0x80000000 | 7, 0x80000000 | 9, 0x80000000 | 11, 0x80000000 | 13,    3,    4,    6,    8,   10,   12,   14,

       0        // eod
};

void PictureDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PictureDelegate *_t = static_cast<PictureDelegate *>(_o);
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
            case 4:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PictureDelegate* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PictureDelegate::*_t)(const QSize & , const QString & , Namespace::ImageReaderObject::SMutex , Namespace::ImageReaderObject::SBool , PictureDelegate * , Namespace::ImageReaderObject::SSMutex , Namespace::ImageReaderObject::SPixmap );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PictureDelegate::getAPicture)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject PictureDelegate::staticMetaObject = {
    { &AbstractItemWidget::staticMetaObject, qt_meta_stringdata_PictureDelegate.data,
      qt_meta_data_PictureDelegate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PictureDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PictureDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PictureDelegate.stringdata0))
        return static_cast<void*>(const_cast< PictureDelegate*>(this));
    return AbstractItemWidget::qt_metacast(_clname);
}

int PictureDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractItemWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void PictureDelegate::getAPicture(const QSize & _t1, const QString & _t2, Namespace::ImageReaderObject::SMutex _t3, Namespace::ImageReaderObject::SBool _t4, PictureDelegate * _t5, Namespace::ImageReaderObject::SSMutex _t6, Namespace::ImageReaderObject::SPixmap _t7)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
