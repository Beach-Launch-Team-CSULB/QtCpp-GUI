#include "Valve.hpp"

Valve::Valve(QObject *parent, QList<QVariant> args)
    : QObject{parent}, _name{args.at(0).toString()},
      _ID{static_cast<quint16>(args.at(1).toInt())},
      _HP_channel{static_cast<quint16>(args.at(2).toInt())},
      _commandOff{static_cast<quint16>(args.at(3).toInt())},
      _commandOn{static_cast<quint16>(args.at(4).toInt())},
      _something_to_do_with_text_styling{static_cast<quint16>(args.at(5).toInt())},
      _valveNode{args.at(6).toInt()}
{
    qInfo() << _name << " " <<_valveNode;
}
void Valve::onValveReceived(quint16 HP1, quint16 HP2, QList<QByteArray> data)
{
    // check for valve ID before doing anything.
    switch(_valveNode)
    {
    case Valve::ValveNode::ENGINE_NODE:
        switch (_HP_channel) // only HP's 1,2,3,4,5,7,8 are used.
        {
        case 1:
            setState(cursed.at(HP1)); // HP values are 0,1,2, corresponding to the closed, open, firecommanded states
            return;
        case 2:
            setState(cursed.at(HP2));
            return;
        case 3:
            setState(cursed.at(data.at(0).toInt(nullptr, 16)));
            return;
        case 4:
            setState(cursed.at(data.at(1).toInt(nullptr, 16)));
            return;
        case 5:
            setState(cursed.at(data.at(2).toInt(nullptr, 16)));
            return;
        case 6: // not used
            setState(cursed.at(data.at(3).toInt(nullptr, 16)));
            return;
        case 7:
            setState(cursed.at(data.at(4).toInt(nullptr, 16)));
            return;
        case 8:
            setState(cursed.at(data.at(5).toInt(nullptr, 16)));
            return;
        case 9: // not used
            setState(cursed.at(data.at(6).toInt(nullptr, 16)));
            return;
        case 10: // not used
            setState(cursed.at(data.at(7).toInt(nullptr, 16)));
            return;
        }
        break;
    case Valve::ValveNode::PROP_NODE:
        switch (_HP_channel)
        {
        case 1:
            setState(cursed.at(HP1));
            return;
        case 2:
            setState(cursed.at(HP2));
            return;
        case 3:
            setState(cursed.at(data.at(0).toInt(nullptr, 16)));
            return;
        case 4:
            setState(cursed.at(data.at(1).toInt(nullptr, 16)));
            return;
        case 5:
            setState(cursed.at(data.at(2).toInt(nullptr, 16)));
            return;
        case 6: // not used
            setState(cursed.at(data.at(3).toInt(nullptr, 16)));
            return;
        case 7:
            setState(cursed.at(data.at(4).toInt(nullptr, 16)));
            return;
        case 8:
            setState(cursed.at(data.at(5).toInt(nullptr, 16)));
            return;
        case 9: // not used
            setState(cursed.at(data.at(6).toInt(nullptr, 16)));
            return;
        case 10: // not used
            setState(cursed.at(data.at(7).toInt(nullptr, 16)));
            return;
        }
        break;
    case Valve::ValveNode::PASA_NODE:
        switch (_HP_channel)
        {
        case 1:
            setState(cursed.at(HP1));
            return;
        case 2:
            setState(cursed.at(HP2));
            return;
        case 3:
            setState(cursed.at(data.at(0).toInt(nullptr, 16)));
            return;
        case 4:
            setState(cursed.at(data.at(1).toInt(nullptr, 16)));
            return;
        case 5:
            setState(cursed.at(data.at(2).toInt(nullptr, 16)));
            return;
        case 6: // not used
            setState(cursed.at(data.at(3).toInt(nullptr, 16)));
            return;
        case 7:
            setState(cursed.at(data.at(4).toInt(nullptr, 16)));
            return;
        case 8:
            setState(cursed.at(data.at(5).toInt(nullptr, 16)));
            return;
        case 9: // not used
            setState(cursed.at(data.at(6).toInt(nullptr, 16)));
            return;
        case 10: // not used
            setState(cursed.at(data.at(7).toInt(nullptr, 16)));
            return;
        }
        break;
    }

}

QString Valve::name() const
{
    return _name;
}


Valve::ValveState Valve::state() const
{
    return _state;
}

void Valve::setState(Valve::ValveState newState)
{
    _state = newState;
    emit stateChanged(); // for QML to handle
}

quint16 Valve::ID()
{
    return _ID;
}

quint16 Valve::commandOff()
{
    return _commandOff;
}

quint16 Valve::commandOn()
{
    return _commandOn;
}
