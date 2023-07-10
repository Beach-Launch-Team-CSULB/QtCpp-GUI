#include "Sensor.hpp"

Sensor::Sensor(QObject *parent, QList<QVariant> args)
    : QObject{parent}, _name{args.at(0).toString()},
    _rawSensorID{static_cast<quint16>(args.at(1).toInt())},
    _sensorNode{static_cast<quint16>(args.at(2).toInt())},
    _convertedSensorID{static_cast<quint16>(args.at(3).toInt())}
{
    //_sensorID = _rawSensorID + 1;
    _convertedSensorID = _rawSensorID + 1;
}



void Sensor::onSensorReceived(quint16 ID_A, quint32 ID_B, QList<QByteArray> data)
{
    // check for sensor ID before doing anything
    if (_convertedSensorID == ID_A)
    {
        setConvertedValue(static_cast<float>((data.at(0)+ data.at(1)).toInt(nullptr, 16))/10);
        return;
    }
    if (data.length() >= 5)
    {
        if (_convertedSensorID == data.at(2).toInt(nullptr, 16))
        {
            setConvertedValue(static_cast<float>((data.at(3)+ data.at(4)).toInt(nullptr, 16))/10);
            return;
        }

    }
    if (data.length() >= 8)
    {
        if (_convertedSensorID == data.at(2).toInt(nullptr, 16))
        {
            setConvertedValue(static_cast<float>((data.at(6) + data.at(7)).toInt(nullptr, 16))/10);
            return;
        }
    }
    // need to find out how to let QML directly read these values
    // or handle the valueChanged() signal and update the values in the GUI
    // try with QMLtestclass
}

void Sensor::onSensorReceivedFD(const QList<QByteArray>& data)
{
    for (int i = 0; i < data.length(); i = i + 12)
    {
        if(_rawSensorID == data.at(i).toInt(nullptr, 16))
        {
            setState(static_cast<SensorState>(data.at(i+1).toInt(nullptr, 16)));

            quint32 currentTimestamp =  data.at(i+5).toInt(nullptr, 16) +
                                        (data.at(i+4).toInt(nullptr, 16) << 8) +
                                        (data.at(i+3).toInt(nullptr, 16) << 16) +
                                        (data.at(i+2).toInt(nullptr, 16) << 24);
            setTimestamp(currentTimestamp);

            quint16 currentRawValue = data.at(i+7).toInt(nullptr, 16) + (data.at(i+6).toInt(nullptr, 16) << 8);
            setRawValue(currentRawValue);

            quint8 u_8x4[4] = { static_cast<quint8>(data.at(i+8).toUInt(nullptr,16)),
                                static_cast<quint8>(data.at(i+9).toUInt(nullptr,16)),
                                static_cast<quint8>(data.at(i+10).toUInt(nullptr,16)),
                                static_cast<quint8>(data.at(i+11).toUInt(nullptr,16))};
            float currentConvertedValue;
            memcpy(&currentConvertedValue, u_8x4, 4);
            setConvertedValue(currentConvertedValue);
            break;
        }
    }
}

quint32 Sensor::getTimestamp() const
{
    return timestamp;
}

void Sensor::setTimestamp(quint32 newTimestamp)
{
    if (timestamp == newTimestamp)
        return;
    timestamp = newTimestamp;
    emit timestampChanged();
}

QString Sensor::name() const
{
    return _name;
}


float Sensor::rawValue() const
{
    return _rawValue;
}

void Sensor::setRawValue(float newRawValue)
{
    _rawValue = newRawValue;
    emit rawValueChanged(); // QML will handle this signal
}

float Sensor::convertedValue() const
{
    return _convertedValue;
}

void Sensor::setConvertedValue(float newConvertedValue)
{
    _convertedValue = newConvertedValue;
    emit convertedValueChanged();
}

Sensor::SensorState Sensor::state() const
{
    return _state;
}

void Sensor::setState(Sensor::SensorState newState)
{
    _state = newState;
    emit stateChanged();
}

quint16 Sensor::rawSensorID()
{
    return _rawSensorID;
}

Node::NodeID Sensor::sensorNode() const
{
    return _sensorNode;
}
