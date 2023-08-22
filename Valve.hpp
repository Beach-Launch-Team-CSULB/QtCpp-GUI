#ifndef VALVE_HPP
#define VALVE_HPP

#include <QObject>
#include <QList>
#include <QVariant>
#include "Node.hpp"
#include <qqml.h>

class Valve : public QObject
{
public:
    enum class ValveState
    {
        CLOSED =                0,
        OPEN =                  1,
        FIRE_COMMANDED =        2,
        OPEN_COMMANDED =        3,
        CLOSE_COMMANDED =       4,
        OPEN_PROCESS =          5,
        CLOSE_PROCESS =         6,
        BANG_OPEN_COMMANDED =   7,
        BANG_CLOSE_COMMANDED =  8,
        BANG_OPEN_PROCESS =     9,
        BANG_CLOSE_PROCESS  =   10,
        BANGING_OPEN =          11,
        BANGING_CLOSED =        12,
        NULL_RETURN =           13,
        VALVE_STATE_SIZE =      14,
    };
    Q_ENUM(ValveState)

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
    //Q_PROPERTY(Valve::ValveState valveState READ valveState NOTIFY ValveStateChanged)
    Q_PROPERTY(QVariant valveState READ valveState NOTIFY ValveStateChanged)
    Q_PROPERTY(QVariant pyroState READ pyroState NOTIFY pyroStateChanged)
    Q_PROPERTY(quint16 ID READ ID CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(quint16 commandOff READ commandOff CONSTANT)
    Q_PROPERTY(quint16 commandOn READ commandOn CONSTANT)
    QML_ELEMENT
    QML_UNCREATABLE("C++ instantiation only")
    QString _name;
    quint16 _ID;
    //Valve::ValveState _valveState {Valve::ValveState::CLOSED};
    QVariant _valveState {QVariant(static_cast<quint8>(Valve::ValveState::CLOSED))};
    quint16 _HP_channel;

    quint16 _commandOff;
    quint16 _commandOn;


    QList<ValveState> _valveStates {ValveState::CLOSED,
                                    ValveState::OPEN,
                                    ValveState::FIRE_COMMANDED};

    // susge
    quint16 _something_to_do_with_text_styling;
    Node::NodeID _valveNode;

    // Pyro
    QVariant _pyroState {QVariant(static_cast<quint8>(Valve::PyroState::OFF))}; //





public:
    explicit Valve(QObject *parent = nullptr, QList<QVariant> args = {0,0,0,0,0,0,0,0});

    //Valve::ValveState valveState() const;
    //void setValveState(Valve::ValveState newValveState);
    QVariant valveState() const;
    void setValveState(QVariant newValveState);

    QVariant pyroState() const;
    void setPyroState(QVariant newPyroState);

    QString name();
    quint16 ID();
    quint16 commandOff();
    quint16 commandOn();



signals:
    void ValveStateChanged();    // for QML to handle
    void pyroStateChanged();

public slots:
    void onValveReceived(quint16 HP1, quint16 HP2, QList<QByteArray> data); // This is wrong, need to fix
    void onValveReceivedFD(const QList<QByteArray>& data);
};

Q_DECLARE_METATYPE(Valve)

#endif // VALVE_HPP
