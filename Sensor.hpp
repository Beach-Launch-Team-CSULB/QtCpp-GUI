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
    QML_ELEMENT
    QML_UNCREATABLE("C++ instantiation only")

    QVariant _state {QVariant(static_cast<quint8>(SensorState::OFF))}; // for turning on or off. SET BY *RECEIVED* CAN FRAME
    quint64 _timestamp = 0; // Microseconds

    Node::NodeID _sensorNode; // not initialized yet.
    QString _name = " ";
    quint16 _sensorID;
    quint16 _rawSensorID;
    quint16 _convertedSensorID;
    float _rawValue = {0.0f}; // SET BY *RECEIVED* CAN FRAME. log to a file maybe???
    float _convertedValue = {0.0f};

    // Expose object's properties to QML
    Q_PROPERTY(quint64 timestamp READ getTimestamp NOTIFY timestampChanged)
    Q_PROPERTY(float rawValue READ rawValue NOTIFY rawValueChanged)
    Q_PROPERTY(float convertedValue READ convertedValue NOTIFY convertedValueChanged)
    Q_PROPERTY(QVariant state READ state NOTIFY stateChanged)
    Q_PROPERTY(quint16 rawSensorID READ rawSensorID CONSTANT)
    Q_PROPERTY(Node::NodeID sensorNode READ sensorNode CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)


public:
    explicit Sensor(QObject *parent = nullptr, QList<QVariant> args = {0,0,0,0});


    Node::NodeID sensorNode() const;

    QString name() const;

    quint64 getTimestamp() const;
    void setTimestamp(quint64 newTimestamp);

    float rawValue() const;
    void setRawValue(float newRawValue);

    float convertedValue() const;
    void setConvertedValue(float newConvertedValue);

    QVariant state() const;
    void setState(QVariant newState);

    quint16 rawSensorID();

signals:
    void timestampChanged();
    void rawValueChanged(); // emit in main the thread for QML to handle, where it reads the sensor's rawValue
    void convertedValueChanged();
    void stateChanged();

    void sensorNodeIDChanged();
    void updateGraphQML_rawValue(float x_timestamp, float y_rawValue);
    void updateGraphQML_convertedValue(float x_timestamp, float y_convertedValue);
    void updateSensorQML_rawValue(float rawValue);
    void updateSensorQML_convertedValue(float convertedValue);
public slots:
    void emitUpdateGraphQML_rawValue();
    void emitUpdateGraphQML_convertedValue();

    void onSensorReceived(quint16 ID_A, quint32 ID_B, QList<QByteArray> data); // receive can frames to update the GUI
    void onSensorReceivedFD(const QList<QByteArray>& data);
};

Q_DECLARE_METATYPE(Sensor)
//Q_DECLARE_OPAQUE_POINTER(Sensor) // Not needed as Sensor is derived from QObject

#endif // SENSOR_HPP
