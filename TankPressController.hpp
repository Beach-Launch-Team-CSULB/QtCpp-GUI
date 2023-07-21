#ifndef TANKPRESSCONTROLLER_HPP
#define TANKPRESSCONTROLLER_HPP

#include <QObject>
#include <QList>
#include <QVariant>
#include <qqml.h>
#include "Node.hpp"

class TankPressController : public QObject
{
public:
    // add ENUM
    enum class TankPressControllerState
    {
        PASSIVE = 0,
        STANDBY = 1,
        BANG_BANG_ACTIVE = 2,
        REG_PRESS_ACTIVE = 3,
        HI_PRESS_PASSTHROUGH_VENT = 4,
        ARMED = 5,
        PROP_TANK_VENT = 6,
        HI_VENT = 7,
        ABORT = 8,
        TEST_PASSTHROUGH = 9,
        OFF_NOMINAL_PASSTHROUGH = 10,
        AUTOSEQUENCE_COMMANDED = 11,
        CONTROLLER_STATE_SIZE = 12
    };
    Q_ENUM(TankPressControllerState)
private:
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("C++ instantiation only")

    QString _name = "";
    quint16 _id = 0;
    quint16 _nodeID = 0;
    QVariant _state {QVariant(static_cast<quint8>(TankPressControllerState::PASSIVE))};


    float _Kp = 0;
    float _Ki = 0;
    float _Kd = 0;
    float _ventFailsafePressure = 0;
    float _controllerThreshold = 0;
    quint32 _valveMinEnergizeTime = 0;
    quint32 _valveMinDeEnergizeTime = 0;
    Q_PROPERTY(QString name READ name CONSTANT)

    Q_PROPERTY(quint16 id READ id CONSTANT)

    Q_PROPERTY(quint16 nodeID READ nodeID CONSTANT)

    Q_PROPERTY(QVariant state READ state NOTIFY stateChanged)

    Q_PROPERTY(float Kp READ Kp NOTIFY KpChanged)

    Q_PROPERTY(float Ki READ Ki NOTIFY KiChanged)

    Q_PROPERTY(float Kd READ Kd NOTIFY KdChanged)

    Q_PROPERTY(float ventFailsafePressure READ ventFailsafePressure NOTIFY ventFailsafePressureChanged)

    Q_PROPERTY(float controllerThreshold READ controllerThreshold NOTIFY controllerThresholdChanged)

    Q_PROPERTY(quint32 valveMinEnergizeTime READ valveMinEnergizeTime NOTIFY valveMinEnergizeTimeChanged)

    Q_PROPERTY(quint32 valveMinDeEnergizeTime READ valveMinDeEnergizeTime NOTIFY valveMinDeEnergizeTimeChanged)

public:
    explicit TankPressController(QObject *parent = nullptr, QList<QVariant> args = {0,0,0,0});

    QString name() const;

    quint16 id() const;

    quint16 nodeID() const;

    QVariant state() const;
    void setState(QVariant newState);

    float Kp() const;
    void setKp(float newKp);

    float Ki() const;
    void setKi(float newKi);

    float Kd() const;
    void setKd(float newKd);

    float ventFailsafePressure() const;
    void setVentFailsafePressure(float newVentFailsafePressure);

    float controllerThreshold() const;
    void setControllerThreshold(float newControllerThreshold);

    quint32 valveMinEnergizeTime() const;
    void setValveMinEnergizeTime(quint32 newValveMinEnergizeTime);

    quint32 valveMinDeEnergizeTime() const;
    void setValveMinDeEnergizeTime(quint32 newValveMinDeEnergizeTime);

signals:
    void KpChanged();

    void KiChanged();

    void KdChanged();

    void stateChanged();

    void ventFailsafePressureChanged();

    void controllerThresholdChanged();

    void valveMinEnergizeTimeChanged();

    void valveMinDeEnergizeTimeChanged();

public slots:
    void onTankPressControllerReceivedFD(const QList<QByteArray>& data);
};
Q_DECLARE_METATYPE(TankPressController)

#endif // TANKPRESSCONTROLLER_HPP
