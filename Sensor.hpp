#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <QObject>
#include <QList>
#include <QVariant>
#include <qqml.h>
#include "Node.hpp"
//dd

class Sensor : public QObject
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

    // Expose object's properties to QML
    Q_PROPERTY(quint32 timestamp READ getTimestamp NOTIFY timestampChanged)
    Q_PROPERTY(float rawValue READ rawValue NOTIFY rawValueChanged)
    Q_PROPERTY(float convertedValue READ convertedValue NOTIFY convertedValueChanged)
    Q_PROPERTY(Sensor::SensorState state READ state NOTIFY stateChanged)
    Q_PROPERTY(quint16 rawSensorID READ rawSensorID CONSTANT)
    Q_PROPERTY(Node::NodeID sensorNode READ sensorNode CONSTANT)
    QML_ELEMENT
    QML_UNCREATABLE("C++ instantiation only")

    SensorState _state; // for turning on or off. SET BY *RECEIVED* CAN FRAME
    quint32 timestamp;

    Node::NodeID _sensorNode; // not initialized yet.
    QString _name;
    quint16 _sensorID;
    quint16 _rawSensorID;
    Node::NodeID _sensorNodeID;
    quint16 _convertedSensorID;
    float _rawValue = {0.0f}; // SET BY *RECEIVED* CAN FRAME. log to a file maybe???
    float _convertedValue = {0.0f};

public:
    explicit Sensor(QObject *parent = nullptr, QList<QVariant> args = {0,0,0,0});

    Node::NodeID sensorNode() const;
    QString name() const;


    quint32 getTimestamp() const;
    void setTimestamp(quint32 newTimestamp);

    float rawValue() const;
    void setRawValue(float newRawValue);

    float convertedValue() const;
    void setConvertedValue(float newConvertedValue);

    Sensor::SensorState state() const;
    void setState(Sensor::SensorState newState);

    quint16 rawSensorID();

signals:
    void timestampChanged();
    void rawValueChanged(); // emit in main the thread for QML to handle, where it reads the sensor's rawValue
    void convertedValueChanged();
    void stateChanged();

    void sensorNodeIDChanged();

public slots:
    void onSensorReceived(quint16 ID_A, quint32 ID_B, QList<QByteArray> data); // receive can frames to update the GUI
    void onSensorReceivedFD(const QList<QByteArray>& data);
};

Q_DECLARE_METATYPE(Sensor)
//Q_DECLARE_OPAQUE_POINTER(Sensor) // Not needed as Sensor is derived from QObject

#endif // SENSOR_HPP
