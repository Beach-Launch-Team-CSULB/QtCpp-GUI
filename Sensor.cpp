#include "Sensor.hpp"

Sensor::Sensor(QObject *parent, QList<QVariant> args)
    : QObject{parent}, _name{args.at(0).toString()},
    _rawSensorID{static_cast<quint16>(args.at(1).toUInt())},
    _sensorNode{static_cast<quint16>(args.at(2).toUInt())},
    _convertedSensorID{static_cast<quint16>(args.at(3).toUInt())}
{
    //_sensorID = _rawSensorID + 1;
    _convertedSensorID = _rawSensorID + 1;
}



void Sensor::onSensorReceived(quint16 ID_A, quint32 ID_B, QList<QByteArray> data)
{
    qInfo() << "Enter Sensor::onSensorReceived() function with object ID: " << _sensorID;
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
    qInfo() << "Enter Sensor::onSensorReceivedFD() function with object ID: " << _sensorID;
    for (int i = 0; i < data.length(); i = i + 16)
    {
        if(_rawSensorID == data.at(i).toUInt(nullptr, 16))
        {
            setState(data.at(i+1).toUInt(nullptr, 16));

            quint64 currentTimestamp =  static_cast<quint64>(data.at(i+9).toUInt(nullptr, 16)) +
                                        (static_cast<quint64>(data.at(i+8).toUInt(nullptr, 16)) << 8) +
                                        (static_cast<quint64>(data.at(i+7).toUInt(nullptr, 16)) << 16) +
                                        (static_cast<quint64>(data.at(i+6).toUInt(nullptr, 16)) << 24) +
                                        (static_cast<quint64>(data.at(i+5).toUInt(nullptr, 16)) << 32) +
                                        (static_cast<quint64>(data.at(i+4).toUInt(nullptr, 16)) << 40) +
                                        (static_cast<quint64>(data.at(i+3).toUInt(nullptr, 16)) << 48) +
                                        (static_cast<quint64>(data.at(i+2).toUInt(nullptr, 16)) << 56);
            setTimestamp(currentTimestamp);

            quint16 currentRawValue = data.at(i+7).toUInt(nullptr, 16) + (data.at(i+6).toUInt(nullptr, 16) << 8);
            setRawValue(currentRawValue);

            quint8 u_8x4[4] = { static_cast<quint8>(data.at(i+12).toUInt(nullptr,16)),
                                static_cast<quint8>(data.at(i+13).toUInt(nullptr,16)),
                                static_cast<quint8>(data.at(i+14).toUInt(nullptr,16)),
                                static_cast<quint8>(data.at(i+15).toUInt(nullptr,16))};
            float currentConvertedValue = 0.0f;
            memcpy(&currentConvertedValue, u_8x4, 4);
            setConvertedValue(currentConvertedValue);
            break;
        }
    }
}

quint64 Sensor::getTimestamp() const
{
    return _timestamp;
}

void Sensor::setTimestamp(quint64 newTimestamp)
{
    if (_timestamp == newTimestamp)
        return;
    _timestamp = newTimestamp;
    emit timestampChanged();
}

QString Sensor::name() const
{
    return _name;
}


float Sensor::rawValue() const
{
    return _rawValue;
    //return _rawValue;
}

void Sensor::setRawValue(float newRawValue)
{
    if(qFuzzyCompare(_rawValue,newRawValue))
        return;
    _rawValue = newRawValue;
    emit rawValueChanged(); // QML will handle this signal
}

float Sensor::convertedValue() const
{
    return _convertedValue;
}

void Sensor::setConvertedValue(float newConvertedValue)
{
    if(qFuzzyCompare(_convertedValue,newConvertedValue));
        return;
    _convertedValue = newConvertedValue;
    emit convertedValueChanged();
}

QVariant Sensor::state() const
{
    return _state;
}

void Sensor::setState(QVariant newState)
{
    if(_state == newState)
        return;
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

