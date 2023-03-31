#ifndef VALVE_HPP
#define VALVE_HPP

#include <QObject>
#include <QList>
#include <QVariant>
#include <qqml.h>
class Valve : public QObject
{
public:
    enum class ValveState
    {
        CLOSED = 0,
        OPEN = 1,
        FIRE_COMMANDED = 2
    };
    Q_ENUM(ValveState)

    enum class ValveNode
    {
        ENGINE_NODE = 2,
        PROP_NODE = 3,
        PASA_NODE = 8
    };
    Q_ENUM(ValveNode)
private:
    Q_OBJECT
    // Expose object's properties to QML
    Q_PROPERTY(Valve::ValveState _state READ state NOTIFY stateChanged)
    QML_ELEMENT
    QString _name;
    quint32 _ID;
    Valve::ValveState _state;
    quint16 _HP_channel;

    quint16 _commandOff;
    quint16 _commandOn;

    ValveState zero {ValveState::CLOSED};
    ValveState one {ValveState::OPEN};
    ValveState two {ValveState::FIRE_COMMANDED};
    QList<ValveState> cursed {zero,one,two};

    // susge
    quint16 _something_to_do_with_text_styling;
    Valve::ValveNode _valveNode;

public:
    explicit Valve(QObject *parent = nullptr, QList<QVariant> args = {0,0,0,0,0,0,0,0});

    Valve::ValveState state() const;
    void setState(Valve::ValveState newState);

    QString name() const;

signals:
    void stateChanged();    // for QML to handle
public slots:
    void onValveReceived(quint16 HP1, quint16 HP2, QList<QByteArray> data);
};

#endif // VALVE_HPP
