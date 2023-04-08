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

    // Probably should make a separate pyro class
    enum class PyroState
    {
        OFF =               0,
        ON =                1,
        FIRE_COMMANDED =    2,
        ON_COMMANDED =      3,
        OFF_COMMANDED =     4,
        FIRED =             5,
        NULL_RETURN =       6,
        PYRO_STATE_SIZE =   7,
    };
    Q_ENUM(PyroState)

private:
    Q_OBJECT

    // Expose object's properties to QML
    Q_PROPERTY(float value READ value NOTIFY valueChanged)
    Q_PROPERTY(Sensor::SensorState state READ state NOTIFY stateChanged)
    Q_PROPERTY(quint16 rawSensorID READ rawSensorID CONSTANT)
    QML_ELEMENT
    QML_UNCREATABLE("C++ instantiation only")

    SensorState _state; // for turning on or off. SET BY *RECEIVED* CAN FRAME
    Node::NodeID _sensorNode; // not initialized yet.
    QString _name;
    quint16 _sensorID;
    quint16 _rawSensorID;
    quint16 _convertedSensorID;
    float _value = {0.0f}; // SET BY *RECEIVED* CAN FRAME. log to a file maybe???
public:
    explicit Sensor(QObject *parent = nullptr, QList<QVariant> args = {0,0,0,0});
    float value() const;
    void setValue(float newValue);
    Sensor::SensorState state() const;
    void setState(Sensor::SensorState newState);
    QString name() const;

    quint16 rawSensorID();

signals:
    void valueChanged(); // emit in main the thread for QML to handle, where it reads the sensor's value
    void stateChanged();
public slots:
    void onSensorReceived(quint16 ID_A, quint32 ID_B, QList<QByteArray> data); // receive can frames to update the GUI
};

#endif // SENSOR_HPP
