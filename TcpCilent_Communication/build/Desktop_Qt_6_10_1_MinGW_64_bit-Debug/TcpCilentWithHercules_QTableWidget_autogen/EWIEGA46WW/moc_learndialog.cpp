/****************************************************************************
** Meta object code from reading C++ file 'learndialog.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../learndialog.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'learndialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN11LearnDialogE_t {};
} // unnamed namespace

template <> constexpr inline auto LearnDialog::qt_create_metaobjectdata<qt_meta_tag_ZN11LearnDialogE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "LearnDialog",
        "learnValueChanged",
        "",
        "value",
        "requestDisconnect",
        "goodCountUpdatedForDisConnectBtn",
        "count",
        "badCountUpdatedForDisConnectBtn",
        "sendTeachData",
        "cameraValue",
        "result",
        "IncomingValue",
        "updateGoodCounter",
        "updateBadCounter",
        "updateTotalCounter",
        "TeachClicked",
        "ClearClicked",
        "closeClicked",
        "DisConnected"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'learnValueChanged'
        QtMocHelpers::SignalData<void(QString)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'requestDisconnect'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'goodCountUpdatedForDisConnectBtn'
        QtMocHelpers::SignalData<void(int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Signal 'badCountUpdatedForDisConnectBtn'
        QtMocHelpers::SignalData<void(int)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Signal 'sendTeachData'
        QtMocHelpers::SignalData<void(QString, QString)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 }, { QMetaType::QString, 10 },
        }}),
        // Slot 'IncomingValue'
        QtMocHelpers::SlotData<void(QString)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Slot 'updateGoodCounter'
        QtMocHelpers::SlotData<void(int)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Slot 'updateBadCounter'
        QtMocHelpers::SlotData<void(int)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Slot 'updateTotalCounter'
        QtMocHelpers::SlotData<void(int)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Slot 'TeachClicked'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'ClearClicked'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'closeClicked'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'DisConnected'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<LearnDialog, qt_meta_tag_ZN11LearnDialogE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject LearnDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11LearnDialogE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11LearnDialogE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11LearnDialogE_t>.metaTypes,
    nullptr
} };

void LearnDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LearnDialog *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->learnValueChanged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->requestDisconnect(); break;
        case 2: _t->goodCountUpdatedForDisConnectBtn((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->badCountUpdatedForDisConnectBtn((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->sendTeachData((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->IncomingValue((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->updateGoodCounter((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->updateBadCounter((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->updateTotalCounter((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->TeachClicked(); break;
        case 10: _t->ClearClicked(); break;
        case 11: _t->closeClicked(); break;
        case 12: _t->DisConnected(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (LearnDialog::*)(QString )>(_a, &LearnDialog::learnValueChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (LearnDialog::*)()>(_a, &LearnDialog::requestDisconnect, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (LearnDialog::*)(int )>(_a, &LearnDialog::goodCountUpdatedForDisConnectBtn, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (LearnDialog::*)(int )>(_a, &LearnDialog::badCountUpdatedForDisConnectBtn, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (LearnDialog::*)(QString , QString )>(_a, &LearnDialog::sendTeachData, 4))
            return;
    }
}

const QMetaObject *LearnDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LearnDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11LearnDialogE_t>.strings))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int LearnDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void LearnDialog::learnValueChanged(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void LearnDialog::requestDisconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LearnDialog::goodCountUpdatedForDisConnectBtn(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void LearnDialog::badCountUpdatedForDisConnectBtn(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void LearnDialog::sendTeachData(QString _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}
QT_WARNING_POP
