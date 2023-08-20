#ifndef HPSENSOR_HPP
#define HPSENSOR_HPP

#include <QObject>
#include <QList>
#include <QVariant>
#include <qqml.h>
#include "Node.hpp"

class HPSensor : public QObject
{
public:
    enum class SensorState
    {
        OFF =           0,
        ON =            1,
        SLOW =          2,
        MEDIUM =        3,
        FAST =          4,
        CALIBRATION =   5,
    };
    Q_ENUM(SensorState)
private:
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("C++ instantiation only")

    QString _name {""};
    quint16 _id {0};
    quint16 _nodeID{0};
    QVariant _sensorState {QVariant(static_cast<quint8>(HPSensor::SensorState::OFF))};

    quint64 _timestamp {0};
    float _outputValue {0.0f};

    Q_PROPERTY(QString name READ name CONSTANT)

    Q_PROPERTY(quint16 id READ id CONSTANT)

    Q_PROPERTY(quint16 nodeID READ nodeID CONSTANT)

    Q_PROPERTY(QVariant sensorState READ sensorState NOTIFY sensorStateChanged)

    Q_PROPERTY(float outputValue READ outputValue NOTIFY outputValueChanged)

    Q_PROPERTY(quint64 timestamp READ timestamp NOTIFY timestampChanged)

public:
    explicit HPSensor(QObject *parent = nullptr, QList<QVariant> args = {0,0,0});

    QString name() const;
    quint16 id() const;
    quint16 nodeID() const;

    QVariant sensorState() const;
    void setSensorState(QVariant newSensorState);

    float outputValue() const;
    void setOutputValue(float newOutputValue);

    quint64 timestamp() const;
    void setTimestamp(quint64 newTimestamp);

signals:
    void outputValueChanged();
    void timestampChanged();

    void sensorStateChanged();

    void updateGraphQML_outputValue(float x_timestamp, float y_outputValue);
public slots:
    void emitUpdateGraphQML_outputValue();

    void onHPSensorReceivedFD(const QList<QByteArray>& data);

};
Q_DECLARE_METATYPE(HPSensor)
#endif // HPSENSOR_HPP
