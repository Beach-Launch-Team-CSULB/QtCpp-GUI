#ifndef VALVE_HPP
#define VALVE_HPP

#include <QObject>
#include <QList>
#include <QVariant>

enum valveState // can't make it enum class due to Qvariant
{
    Off = 1,
    On = 2,
    normallyOff = 3,
    normallyOn = 4,
};

class Valve : public QObject
{
private:
    Q_OBJECT
    quint16 _state; // potentially dangerous???????
    QString _name;
    quint16 _ID;
    quint16 _HP_channel;

    quint16 _commandOff;
    quint16 _commandOn;

    // susge
    quint16 _something_to_do_with_text_styling;
    quint16 _marker_for_refresh_valve_function;


public:
    explicit Valve(QObject *parent = nullptr, QList<QVariant> args = {0,0,0,0,0,0,0,0});

    bool state() const;
    void setState(bool newState);

signals:

public slots:
    void onValveReceived(quint32 ID, QByteArray data);
};

#endif // VALVE_HPP