/****************************************************************************
** Meta object code from reading C++ file 'BlockOutletWidget.h'
**
** Created: Mon 9. Jul 11:56:18 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/BlockOutletWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BlockOutletWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BlockOutletWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   19,   18,   18, 0x05,
      46,   42,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      66,   19,   18,   18, 0x0a,
      87,   42,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BlockOutletWidget[] = {
    "BlockOutletWidget\0\0img\0sendPixmap(QImage)\0"
    "str\0sendString(QString)\0updatePixmap(QImage)\0"
    "updateString(QString)\0"
};

void BlockOutletWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BlockOutletWidget *_t = static_cast<BlockOutletWidget *>(_o);
        switch (_id) {
        case 0: _t->sendPixmap((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: _t->sendString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updatePixmap((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 3: _t->updateString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BlockOutletWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BlockOutletWidget::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_BlockOutletWidget,
      qt_meta_data_BlockOutletWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BlockOutletWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BlockOutletWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BlockOutletWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BlockOutletWidget))
        return static_cast<void*>(const_cast< BlockOutletWidget*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int BlockOutletWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void BlockOutletWidget::sendPixmap(const QImage & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BlockOutletWidget::sendString(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
