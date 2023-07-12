#include "HPSensor.hpp"

HPSensor::HPSensor(QObject *parent, QList<QVariant> args)
    : QObject{parent},
    _name{args.at(0).toString()},
    _id{static_cast<quint16>(args.at(1).toUInt(nullptr))},
    _nodeID{static_cast<quint16>(args.at(2).toUInt(nullptr))}
{

}

void HPSensor::onHPSensorReceivedFD(const QList<QByteArray> &data)
{
    for(int i = 0; i < data.length(); i = i + 14)
    {
        if(_id == data.at(i).toUInt(nullptr,16))
        {
            setSensorState(static_cast<HPSensor::SensorState>(data.at(i+1).toUInt(nullptr,16)));

            quint64 sensorTimeStamp =   static_cast<quint64>(data.at(i+9).toUInt(nullptr,16)) +
                                        (static_cast<quint64>(data.at(i+8).toUInt(nullptr,16)) << 8) +
                                        (static_cast<quint64>(data.at(i+7).toUInt(nullptr,16)) << 16) +
                                        (static_cast<quint64>(data.at(i+6).toUInt(nullptr,16)) << 24) +
                                        (static_cast<quint64>(data.at(i+5).toUInt(nullptr,16)) << 32) +
                                        (static_cast<quint64>(data.at(i+4).toUInt(nullptr,16)) << 40) +
                                        (static_cast<quint64>(data.at(i+3).toUInt(nullptr,16)) << 48) +
                                        (static_cast<quint64>(data.at(i+2).toUInt(nullptr,16)) << 56);
            setTimestamp(sensorTimeStamp);

            quint8 u_8x4[4] =   {   static_cast<quint8>(data.at(i+10).toUInt(nullptr,16)),
                                    static_cast<quint8>(data.at(i+11).toUInt(nullptr,16)),
                                    static_cast<quint8>(data.at(i+12).toUInt(nullptr,16)),
                                    static_cast<quint8>(data.at(i+13).toUInt(nullptr,16))
                                };
            float currentOutputValue = 0.0f;
            memcpy(&currentOutputValue, u_8x4, 4);
            setOutputValue(currentOutputValue);
            break;
        }
    }
}

QString HPSensor::name() const
{
    return _name;
}

quint16 HPSensor::id() const
{
    return _id;
}

quint16 HPSensor::nodeID() const
{
    return _nodeID;
}


HPSensor::SensorState HPSensor::sensorState() const
{
    return _sensorState;
}

void HPSensor::setSensorState(HPSensor::SensorState newSensorState)
{
    if (_sensorState == newSensorState)
        return;
    _sensorState = newSensorState;
    emit sensorStateChanged();
}

float HPSensor::outputValue() const
{
    return _outputValue;
}


void HPSensor::setOutputValue(float newOutputValue)
{
    if (qFuzzyCompare(_outputValue, newOutputValue))
        return;
    _outputValue = newOutputValue;
    emit outputValueChanged();
}

quint64 HPSensor::timestamp() const
{
    return _timestamp;
}

void HPSensor::setTimestamp(quint64 newTimestamp)
{
    if (_timestamp == newTimestamp)
        return;
    _timestamp = newTimestamp;
    emit timestampChanged();
}


