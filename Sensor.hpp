#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <QObject>
#include <QList>
#include <QVariant>
#include <qqml.h>
//dd
class Sensor : public QObject
{
public:
    enum class SensorState
    {
        OFF = 1,
        ON = 2
    };
    Q_ENUM(SensorState)
private:
    Q_OBJECT

    // Expose object's properties to QML
    Q_PROPERTY(float value READ value NOTIFY valueChanged)
    Q_PROPERTY(Sensor::SensorState state READ state NOTIFY stateChanged)
    Q_PROPERTY(quint16 rawSensorID READ rawSensorID CONSTANT)
    QML_ELEMENT
    QML_UNCREATABLE("C++ instantiation only")

    SensorState _state; // for turning on or off. SET BY *RECEIVED* CAN FRAME
    QString _name;
    quint16 _sensorID;
    quint16 _rawSensorID;
    quint16 _convertedSensorID;
    float _value = {0.0f}; // SET BY *RECEIVED* CAN FRAME
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
