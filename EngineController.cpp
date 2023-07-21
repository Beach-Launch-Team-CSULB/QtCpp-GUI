#include "EngineController.hpp"


EngineController::EngineController(QObject *parent, QList<QVariant> args)
    : QObject{parent},
    _name{args.at(0).toString()},
    _id{static_cast<quint16>(args.at(1).toUInt(nullptr))},
    _nodeID{static_cast<quint16>(args.at(2).toUInt(nullptr))}
{

}

void EngineController::onEngineControllerReceivedFD(const QList<QByteArray> &data)
{
    qInfo() << "Enter EngineController::onEngineControllerReceivedFD function with object ID: " << _id;
    for(int i = 0; i < data.length(); i = i + 18)
    {
        if (_id == data.at(i).toUInt(nullptr,16))
        {
            //setState(static_cast<QVariant>(data.at(i+1).toUInt(nullptr,16))); potentially expensive
            setState(data.at(i+1).toUInt(nullptr,16));
            quint8 u_8x4[4] = {static_cast<quint8>(data.at(i+5).toUInt(nullptr,16)),
                               static_cast<quint8>(data.at(i+4).toUInt(nullptr,16)),
                               static_cast<quint8>(data.at(i+3).toUInt(nullptr,16)),
                               static_cast<quint8>(data.at(i+2).toUInt(nullptr,16))};
            qint32 fuelMVAutosequenceActuation = 0;
            memcpy(&fuelMVAutosequenceActuation, u_8x4, 4);
            setFuelMVAutosequenceActuation(fuelMVAutosequenceActuation);

            u_8x4[0] = static_cast<quint8>(data.at(i+9).toUInt(nullptr,16));
            u_8x4[1] = static_cast<quint8>(data.at(i+8).toUInt(nullptr,16));
            u_8x4[2] = static_cast<quint8>(data.at(i+7).toUInt(nullptr,16));
            u_8x4[3] = static_cast<quint8>(data.at(i+6).toUInt(nullptr,16));
            qint32 loxMVAutosequenceActuation = 0;
            memcpy(&loxMVAutosequenceActuation, u_8x4, 4);
            setLoxMVAutosequenceActuation(loxMVAutosequenceActuation);

            u_8x4[0] = static_cast<quint8>(data.at(i+13).toUInt(nullptr,16));
            u_8x4[1] = static_cast<quint8>(data.at(i+12).toUInt(nullptr,16));
            u_8x4[2] = static_cast<quint8>(data.at(i+11).toUInt(nullptr,16));
            u_8x4[3] = static_cast<quint8>(data.at(i+10).toUInt(nullptr,16));
            qint32 igniter1Actuation = 0;
            memcpy(&igniter1Actuation, u_8x4, 4);
            setIgniter1Actuation(igniter1Actuation);

            u_8x4[0] = static_cast<quint8>(data.at(i+13).toUInt(nullptr,16));
            u_8x4[1] = static_cast<quint8>(data.at(i+12).toUInt(nullptr,16));
            u_8x4[2] = static_cast<quint8>(data.at(i+11).toUInt(nullptr,16));
            u_8x4[3] = static_cast<quint8>(data.at(i+10).toUInt(nullptr,16));
            qint32 igniter2Actuation = 0;
            memcpy(&igniter2Actuation, u_8x4, 4);
            setIgniter2Actuation(igniter2Actuation);
            break;
        }
    }
}


QString EngineController::name() const
{
    return _name;
}

quint16 EngineController::id() const
{
    return _id;
}

quint16 EngineController::nodeID() const
{
    return _nodeID;
}

QVariant EngineController::state() const
{
    return _state;
}

void EngineController::setState(QVariant newState)
{
    if (_state == newState)
        return;
    _state = newState;
    emit stateChanged();
}


qint32 EngineController::fuelMVAutosequenceActuation() const
{
    return _fuelMVAutosequenceActuation;
}

void EngineController::setFuelMVAutosequenceActuation(qint32 newFuelMVAutosequenceActuation)
{
    if (_fuelMVAutosequenceActuation == newFuelMVAutosequenceActuation)
        return;
    _fuelMVAutosequenceActuation = newFuelMVAutosequenceActuation;
    emit fuelMVAutosequenceActuationChanged();
}

qint32 EngineController::loxMVAutosequenceActuation() const
{
    return _loxMVAutosequenceActuation;
}

void EngineController::setLoxMVAutosequenceActuation(qint32 newLoxMVAutosequenceActuation)
{
    if (_loxMVAutosequenceActuation == newLoxMVAutosequenceActuation)
        return;
    _loxMVAutosequenceActuation = newLoxMVAutosequenceActuation;
    emit loxMVAutosequenceActuationChanged();
}

qint32 EngineController::igniter1Actuation() const
{
    return _igniter1Actuation;
}

void EngineController::setIgniter1Actuation(qint32 newIgniter1Actuation)
{
    if (_igniter1Actuation == newIgniter1Actuation)
        return;
    _igniter1Actuation = newIgniter1Actuation;
    emit igniter1ActuationChanged();
}

qint32 EngineController::igniter2Actuation() const
{
    return _igniter2Actuation;
}

void EngineController::setIgniter2Actuation(qint32 newIgniter2Actuation)
{
    if (_igniter2Actuation == newIgniter2Actuation)
        return;
    _igniter2Actuation = newIgniter2Actuation;
    emit igniter2ActuationChanged();
}

