#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <QObject>
#include <QList>
#include <QVariant>

enum sensorState // can't make it enum class due to Qvariant
{
    off = 1,
    on = 2
};

//dd
class Sensor : public QObject
{
    Q_OBJECT

    // Expose object's properties to QML
    Q_PROPERTY(float value READ value NOTIFY valueChanged)
    Q_PROPERTY(quint16 state READ state NOTIFY stateChanged)

    sensorState _state; // for turning on or off. SET BY *RECEIVED* CAN FRAME
    QString _name;
    quint16 _sensorID;
    quint16 _rawSensorID;
    quint16 _convertedSensorID;



    float _value = {0.0f}; // SET BY *RECEIVED* CAN FRAME
public:
    explicit Sensor(QObject *parent = nullptr, QList<QVariant> args = {0,0,0,0});
    float value() const;
    quint16 state() const;

    QString name() const;

signals:
    void valueChanged(); // emit in main the thread for QML to handle, where it reads the sensor's value
    void stateChanged();
public slots:
    void onSensorReceived(quint16 ID_A, quint32 ID_B, QList<QByteArray> data); // receive can frames to update the GUI

};

#endif // SENSOR_HPP
