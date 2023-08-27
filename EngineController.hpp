#ifndef ENGINECONTROLLER_HPP
#define ENGINECONTROLLER_HPP

#include <QObject>
#include <QList>
#include <QVariant>
#include <qqml.h>
#include "Node.hpp"

class EngineController : public QObject
{
public:
    enum class EngineControllerState
    {
        PASSIVE = 0,
        ACTIVE = 1,
        CHILL = 2,
        PURGE = 3,
        SHUTDOWN = 4,
        ARMED = 5,
        TEST_PASSTHROUGH = 6,
        OFF_NOMINAL_PASSTHROUGH = 7,
        FIRING_AUTOSEQUENCE = 8,
        CONTROLLER_STATE_SIZE= 9
    };
    Q_ENUM(EngineControllerState)
private:
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("C++ instantiation only")

    QString _name {""};
    quint16 _id {0};
    quint16 _nodeID{0};

    QVariant _state {QVariant(static_cast<quint8>(EngineControllerState::PASSIVE))};

    qint32 _fuelMVAutosequenceActuation = -69000000;
    qint32 _loxMVAutosequenceActuation = -70000000;
    qint32 _igniter1Actuation = -71000000;
    qint32 _igniter2Actuation = -72000000;


    Q_PROPERTY(QString name READ name CONSTANT)

    Q_PROPERTY(quint16 id READ id CONSTANT)

    Q_PROPERTY(quint16 nodeID READ nodeID CONSTANT)

    Q_PROPERTY(QVariant state READ state NOTIFY stateChanged)

    Q_PROPERTY(qint32 fuelMVAutosequenceActuation READ fuelMVAutosequenceActuation NOTIFY fuelMVAutosequenceActuationChanged)

    Q_PROPERTY(qint32 loxMVAutosequenceActuation READ loxMVAutosequenceActuation NOTIFY loxMVAutosequenceActuationChanged)

    Q_PROPERTY(qint32 igniter1Actuation READ igniter1Actuation NOTIFY igniter1ActuationChanged)

    Q_PROPERTY(qint32 igniter2Actuation READ igniter2Actuation NOTIFY igniter2ActuationChanged)

public:
    explicit EngineController(QObject *parent = nullptr, QList<QVariant> args = {0,0,0});

    QString name() const;
    quint16 id() const;
    quint16 nodeID() const;

    qint32 fuelMVAutosequenceActuation() const;
    void setFuelMVAutosequenceActuation(qint32 newFuelMVAutosequenceActuation);

    QVariant state() const;
    void setState(QVariant newState);

    qint32 loxMVAutosequenceActuation() const;
    void setLoxMVAutosequenceActuation(qint32 newLoxMVAutosequenceActuation);



    qint32 igniter1Actuation() const;
    void setIgniter1Actuation(qint32 newIgniter1Actuation);

    qint32 igniter2Actuation() const;
    void setIgniter2Actuation(qint32 newIgniter2Actuation);

signals:

    void stateChanged();

    void loxMVAutosequenceActuationChanged();

    void fuelMVAutosequenceActuationChanged();

    void igniter1ActuationChanged();

    void igniter2ActuationChanged();

public slots:
    void onEngineControllerReceivedFD(const QList<QByteArray>& data);
};
Q_DECLARE_METATYPE(EngineController)
#endif // ENGINECONTROLLER_HPP
