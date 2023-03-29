#include "Sensor.hpp"

Sensor::Sensor(QObject *parent, QList<QVariant> args)
    : QObject{parent}, _name{args.at(0).toString()},
      _rawSensorID{static_cast<quint16>(args.at(1).toInt())},
      _convertedSensorID{static_cast<quint16>(args.at(2).toInt())}
{
    _sensorID = _rawSensorID + 1;
    _convertedSensorID = _rawSensorID + 1;
}

void Sensor::onSensorReceived(quint16 ID_A, quint32 ID_B, QList<QByteArray> data)
{
    // check for sensor ID before doing anything
    if (_convertedSensorID == ID_A)
    {
        setValue((data.at(0)+ data.at(1)).toInt(nullptr, 16));
        return;
    }
    else if (_convertedSensorID == data.at(2).toInt(nullptr, 16))
    {
        setValue((data.at(3)+ data.at(4)).toInt(nullptr, 16));
        return;
    }
    else if (_convertedSensorID == data.at(5).toInt(nullptr, 16))
    {
        setValue((data.at(6)+ data.at(7)).toInt(nullptr, 16));
        return;
    }
    // need to find out how to let QML directly read these values
    // or handle the valueChanged() signal and update the values in the GUI
    // try with QMLtestclass

}

QString Sensor::name() const
{
    return _name;
}


float Sensor::value() const
{
    return _value;
}

void Sensor::setValue(float newValue)
{
    _value = newValue;
    emit valueChanged(); // QML will handle this signal
}

quint16 Sensor::state() const
{
    return _state;
}
