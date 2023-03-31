#include "Controller.hpp"

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

float Controller::fuelMVTime()
{
    return _fuelMVTime;
}

void Controller::setFuelMVTime(float newFuelMVTime)
{
    _fuelMVTime = newFuelMVTime;
    emit fuelMVTimeChanged();
}
float Controller::LOXMVTime()
{
    return _LOXMVTime;
}
void Controller::setLOXMVTime(float newLOXMVTime)
{
    _LOXMVTime = newLOXMVTime;
    emit LOXMVTimeChanged();
}
float Controller::IGN1Time()
{
    return _IGN1Time;
}
void Controller::setIGN1Time(float newIGN1Time)
{
    _IGN1Time = newIGN1Time;
    emit IGN1TimeChanged();
}
float Controller::IGN2Time()
{
    return _IGN2Time;
}
void Controller::setIGN2Time(float newIGN2Time)
{
    _IGN2Time = newIGN2Time;
    emit IGN2TimeChanged();
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
