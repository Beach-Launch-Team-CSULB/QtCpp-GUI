#include "TankPressController.hpp"

TankPressController::TankPressController(QObject *parent, QList<QVariant> args)
    : QObject{parent},
    _name{args.at(0).toString()},
    _id{static_cast<quint16>(args.at(1).toUInt(nullptr))},
    _nodeID{static_cast<quint16>(args.at(2).toUInt(nullptr))},
    _ventFailsafePressure{args.at(3).toFloat(nullptr)}
{

}

void TankPressController::onTankPressControllerReceivedFD(const QList<QByteArray> &data)
{
    qInfo() << "Enter TankPressController::onTankPressControllerReceivedFD function with object ID: " << _id;
    for (int i = 0; i < data.length(); i = i + 30)
    {
        if (_id == data.at(i).toUInt(nullptr,16))
        {
            setState(data.at(i+1).toUInt(nullptr,16));

            quint8 u_8x4[4] = {
                static_cast<quint8>(data.at(i+2).toUInt(nullptr,16)),
                static_cast<quint8>(data.at(i+3).toUInt(nullptr,16)),
                static_cast<quint8>(data.at(i+4).toUInt(nullptr,16)),
                static_cast<quint8>(data.at(i+5).toUInt(nullptr,16))
            };
            float Kp = 0.0f;
            memcpy(&Kp, u_8x4, 4);
            setKp(Kp);

            u_8x4[0] = static_cast<quint8>(data.at(i+6).toUInt(nullptr,16));
            u_8x4[1] = static_cast<quint8>(data.at(i+7).toUInt(nullptr,16));
            u_8x4[2] = static_cast<quint8>(data.at(i+8).toUInt(nullptr,16));
            u_8x4[3] = static_cast<quint8>(data.at(i+9).toUInt(nullptr,16));
            float Ki = 0.0f;
            memcpy(&Ki, u_8x4, 4);
            setKi(Ki);

            u_8x4[0] = static_cast<quint8>(data.at(i+10).toUInt(nullptr,16));
            u_8x4[1] = static_cast<quint8>(data.at(i+11).toUInt(nullptr,16));
            u_8x4[2] = static_cast<quint8>(data.at(i+12).toUInt(nullptr,16));
            u_8x4[3] = static_cast<quint8>(data.at(i+13).toUInt(nullptr,16));
            float Kd = 0.0f;
            memcpy(&Kd, u_8x4, 4);
            setKd(Kd);

            u_8x4[0] = static_cast<quint8>(data.at(i+14).toUInt(nullptr,16));
            u_8x4[1] = static_cast<quint8>(data.at(i+15).toUInt(nullptr,16));
            u_8x4[2] = static_cast<quint8>(data.at(i+16).toUInt(nullptr,16));
            u_8x4[3] = static_cast<quint8>(data.at(i+17).toUInt(nullptr,16));
            float controllerThreshold = 0.0f;
            memcpy(&controllerThreshold, u_8x4, 4);
            setControllerThreshold(controllerThreshold);

            u_8x4[0] = static_cast<quint8>(data.at(i+18).toUInt(nullptr,16));
            u_8x4[1] = static_cast<quint8>(data.at(i+19).toUInt(nullptr,16));
            u_8x4[2] = static_cast<quint8>(data.at(i+20).toUInt(nullptr,16));
            u_8x4[3] = static_cast<quint8>(data.at(i+21).toUInt(nullptr,16));
            float ventFailsafePressure = 0.0f;
            memcpy(&ventFailsafePressure, u_8x4, 4);
            setVentFailsafePressure(ventFailsafePressure);

            quint32 valveMinEnergizeTime = data.at(i+25).toUInt(nullptr,16) + (data.at(i+24).toUInt(nullptr,16) << 8)
                                            + (data.at(i+23).toUInt(nullptr,16) << 16) + (data.at(i+22).toUInt(nullptr, 16) << 24);
            setValveMinEnergizeTime(valveMinEnergizeTime);

            quint32 valveMinDeEnergizeTime = data.at(i+29).toUInt(nullptr,16) + (data.at(i+28).toUInt(nullptr,16) << 8)
                                            + (data.at(i+27).toUInt(nullptr,16) << 16) + (data.at(i+26).toUInt(nullptr, 16) << 24);
            setValveMinDeEnergizeTime(valveMinDeEnergizeTime);

            break;
        }
    }
}


QString TankPressController::name() const
{
    return _name;
}

quint16 TankPressController::id() const
{
    return _id;
}

quint16 TankPressController::nodeID() const
{
    return _nodeID;
}

QVariant TankPressController::state() const
{
    return _state;
}

void TankPressController::setState(QVariant newState)
{
    if (_state == newState)
        return;
    _state = newState;
    emit stateChanged();
}

float TankPressController::Kp() const
{
    return _Kp;
}

void TankPressController::setKp(float newKp)
{
    if (qFuzzyCompare(_Kp, newKp))
        return;
    _Kp = newKp;
    emit KpChanged();
}

float TankPressController::Ki() const
{
    return _Ki;
}

void TankPressController::setKi(float newKi)
{
    if (qFuzzyCompare(_Ki, newKi))
        return;
    _Ki = newKi;
    emit KiChanged();
}

float TankPressController::Kd() const
{
    return _Kd;
}

void TankPressController::setKd(float newKd)
{
    if (qFuzzyCompare(_Kd, newKd))
        return;
    _Kd = newKd;
    emit KdChanged();
}

float TankPressController::ventFailsafePressure() const
{
    return _ventFailsafePressure;
}

void TankPressController::setVentFailsafePressure(float newVentFailsafePressure)
{
    if (qFuzzyCompare(_ventFailsafePressure, newVentFailsafePressure))
        return;
    _ventFailsafePressure = newVentFailsafePressure;
    emit ventFailsafePressureChanged();
}

float TankPressController::controllerThreshold() const
{
    return _controllerThreshold;
}

void TankPressController::setControllerThreshold(float newControllerThreshold)
{
    if (qFuzzyCompare(_controllerThreshold, newControllerThreshold))
        return;
    _controllerThreshold = newControllerThreshold;
    emit controllerThresholdChanged();
}

quint32 TankPressController::valveMinEnergizeTime() const
{
    return _valveMinEnergizeTime;
}

void TankPressController::setValveMinEnergizeTime(quint32 newValveMinEnergizeTime)
{
    if (_valveMinEnergizeTime == newValveMinEnergizeTime)
        return;
    _valveMinEnergizeTime = newValveMinEnergizeTime;
    emit valveMinEnergizeTimeChanged();
}

quint32 TankPressController::valveMinDeEnergizeTime() const
{
    return _valveMinDeEnergizeTime;
}

void TankPressController::setValveMinDeEnergizeTime(quint32 newValveMinDeEnergizeTime)
{
    if (_valveMinDeEnergizeTime == newValveMinDeEnergizeTime)
        return;
    _valveMinDeEnergizeTime = newValveMinDeEnergizeTime;
    emit valveMinDeEnergizeTimeChanged();
}


