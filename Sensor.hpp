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


class Sensor : public QObject
{
    Q_OBJECT
    quint16 _state; // for turning on or off. SET BY *RECEIVED* CAN FRAME
    QString _name;
    quint16 _rawSensorID;
    quint16 _convertedSensorID;



    float _value = {0.0f}; // SET BY *RECEIVED* CAN FRAME
public:
    explicit Sensor(QObject *parent = nullptr, QList<QVariant> args = {0,0,0,0});
    void refresh();


    float value() const;

    quint16 state() const;
    void setState(quint16 newState);

signals:

public slots:
    void onSensorReceived(quint32 ID, QByteArray data); // receive can frames to update the GUI
};

#endif // SENSOR_HPP
