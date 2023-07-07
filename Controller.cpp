#include "Controller.hpp"

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

quint16 Controller::nodeControllerID()
{
    return _nodeControllerID;
}

quint16 Controller::autosequenceID()
{
    return _autosequenceID;
}

float Controller::autosequenceTime() const
{
    return _autosequenceTime;
}

void Controller::setAutosequenceTime(float newAutosequenceTime)
{
    _autosequenceTime = newAutosequenceTime;
    emit autosequenceTimeChanged();
}

quint16 Controller::hiPressID()
{
    return _hiPressID;
}

quint16 Controller::LOXID()
{
    return _LOXID;
}

quint16 Controller::fuelID()
{
    return _fuelID;
}

quint16 Controller::engineControllerID()
{
    return _engineControllerID;
}


float Controller::fuelMVTime() const
{
    return _fuelMVTime;
}

void Controller::setFuelMVTime(float newFuelMVTime)
{
    _fuelMVTime = newFuelMVTime;
    emit fuelMVTimeChanged();
}
float Controller::LOXMVTime() const
{
    return _LOXMVTime;
}
void Controller::setLOXMVTime(float newLOXMVTime)
{
    _LOXMVTime = newLOXMVTime;
    emit LOXMVTimeChanged();
}
float Controller::IGN1Time() const
{
    return _IGN1Time;
}
void Controller::setIGN1Time(float newIGN1Time)
{
    _IGN1Time = newIGN1Time;
    emit IGN1TimeChanged();
}
float Controller::IGN2Time() const
{
    return _IGN2Time;
}
void Controller::setIGN2Time(float newIGN2Time)
{
    _IGN2Time = newIGN2Time;
    emit IGN2TimeChanged();
}

