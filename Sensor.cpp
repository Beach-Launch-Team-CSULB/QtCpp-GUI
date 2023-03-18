#include "Sensor.hpp"

Sensor::Sensor(QObject *parent, QList<QVariant> args)
    : QObject{parent}, _name{args.at(0).toString()},
      _rawSensorID{static_cast<quint16>(args.at(1).toInt())},
      _convertedSensorID{static_cast<quint16>(args.at(2).toInt())}
{

}

void Sensor::onSensorReceived(quint32 ID, QByteArray data)
{
    // check for sensor ID before doing anything
}


float Sensor::value() const
{
    return _value;
}


quint16 Sensor::state() const
{
    return _state;
}

void Sensor::setState(quint16 newState)
{
    _state = newState;
}
