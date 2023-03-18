#include "Valve.hpp"

Valve::Valve(QObject *parent, QList<QVariant> args)
    : QObject{parent}, _name{args.at(0).toString()},
      _ID{static_cast<quint16>(args.at(1).toInt())},
      _HP_channel{static_cast<quint16>(args.at(2).toInt())},
      _state{static_cast<quint16>(args.at(3).toInt())},
      _commandOff{static_cast<quint16>(args.at(4).toInt())},
      _commandOn{static_cast<quint16>(args.at(5).toInt())},
      _something_to_do_with_text_styling{static_cast<quint16>(args.at(6).toInt())},
      _marker_for_refresh_valve_function{static_cast<quint16>(args.at(7).toInt())}
{

}

void Valve::onValveReceived(quint32 ID, QByteArray data)
{
    // check for valve ID before doing anything
}


bool Valve::state() const
{
    return _state;
}

void Valve::setState(bool newState)
{
    _state = newState;
}
