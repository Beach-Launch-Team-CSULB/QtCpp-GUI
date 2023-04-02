#ifndef COMMANDSTATE_HPP
#define COMMANDSTATE_HPP

#include <QObject>
#include <QString>
#include <qqml.h>
#include "FrameHandler.hpp" // <----- This always stays here

// Only used to construct frames to send to the Alaras
struct CommandState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString stateName READ stateName CONSTANT)
    //Q_PROPERTY(FrameHandler::VehicleState vehicleState READ vehicleState CONSTANT)
    Q_PROPERTY(QString commandID READ commandID CONSTANT)
    Q_PROPERTY(QString commandOff READ commandOff CONSTANT)
    Q_PROPERTY(QString commandOn READ commandOn CONSTANT)
    Q_PROPERTY(bool isArmState READ isArmState CONSTANT)

    QML_UNCREATABLE("C++ instantiation only")
public:
    //FrameHandler::VehicleState _vehicleState;   // should only be TEST, ABORT, VENT, OFF_NOMINAL
                                                // HI_PRESS_ARM, HI_PRESS_PRESSURIZED,
                                                // TANK_PRESS_ARM, TANK_PRESS_PRESSURIZED, FIRE_ARMED, FIRE.

    // Also there are 2 instances of OFF_NOMINAL

    //QString _stateID;
    QString _stateName;
    QString _commandID;
    QString _commandOff;
    QString _commandOn;
    bool _isArmState;

    //explicit CommandState(FrameHandler::VehicleState vehicleState,const QString& stateName,const quint16& commandID,const quint16& commandOff,const quint16& commandOn, bool isArmState, QObject *parent = nullptr)
    //    : QObject{parent},
    //      _stateName{stateName},
    //      _vehicleState{vehicleState},
    //      _commandID{QString::number(commandID, 16)},
    //      _commandOff{QString::number(commandOff, 16)},
    //      _commandOn{QString::number(commandOn, 16)},
    //      _isArmState{isArmState}
    //{
//
    //}

    explicit CommandState(const QString& stateName,const quint16& commandID,const quint16& commandOff,const quint16& commandOn, bool isArmState, QObject *parent = nullptr)
        :QObject{parent},
        _stateName{stateName},
        _commandID{QString::number(commandID, 16)},
        _commandOff{QString::number(commandOff, 16)},
        _commandOn{QString::number(commandOn, 16)},
        _isArmState{isArmState}
    {

    }

    QString stateName() {return _stateName;}
    //FrameHandler::VehicleState vehicleState() {return _vehicleState;}
    QString commandID() {return _commandID;}
    QString commandOff() {return _commandOff;}
    QString commandOn() {return _commandOn;}
    bool isArmState() {return _isArmState;}
};

#endif // COMMANDSTATE_HPP
