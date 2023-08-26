#include "Valve.hpp"

Valve::Valve(QObject *parent, QList<QVariant> args)
    : QObject{parent}, _name{args.at(0).toString()},
      _ID{static_cast<quint16>(args.at(1).toUInt())},
      _HP_channel{static_cast<quint16>(args.at(2).toUInt())},
      _commandOff{static_cast<quint16>(args.at(3).toUInt())},
      _commandOn{static_cast<quint16>(args.at(4).toUInt())},
      _something_to_do_with_text_styling{static_cast<quint16>(args.at(5).toUInt())},
      _valveNode{static_cast<Node::NodeID>(args.at(6).toUInt())}
{
    qInfo() << _name << " " <<_valveNode;
}
void Valve::onValveReceived(quint16 HP1, quint16 HP2, QList<QByteArray> data)
{
    /* this needs rework
    qInfo() << "Enter Valve::onValveReceived function with object ID: " << _ID;
    // check for valve ID before doing anything.
    switch(_valveNode)
    {
    case Node::NodeID::ENGINE_NODE:
        switch (_HP_channel)    // only HP's 1,2,3,4,5,7,8 are used.
        {                       // HP values are 0,1,2, corresponding to the closed, open, firecommanded states
        case 1:     setValveState(_valveStates.at(HP1)); return;                             // HP
        case 2:     setValveState(_valveStates.at(HP2)); return;                             // HPV
        case 3:     setValveState(_valveStates.at(data.at(0).toInt(nullptr, 16)));return;    // FMV
        case 4:     setValveState(_valveStates.at(data.at(1).toInt(nullptr, 16)));return;    // LMV
        case 5:     setValveState(_valveStates.at(data.at(2).toInt(nullptr, 16)));return;    // IGN1
        case 6:     setValveState(_valveStates.at(data.at(3).toInt(nullptr, 16)));return;    // not used
        case 7:     setValveState(_valveStates.at(data.at(4).toInt(nullptr, 16)));return;    // IGN2
        case 8:     setValveState(_valveStates.at(data.at(5).toInt(nullptr, 16)));return;    // not used
        case 9:     setValveState(_valveStates.at(data.at(6).toInt(nullptr, 16)));return;    // not used
        case 10:    setValveState(_valveStates.at(data.at(7).toInt(nullptr, 16)));return;    // not used
        }
        break;
    case Node::NodeID::PROP_NODE:
        switch (_HP_channel)
        {
        case 1:                                                                     // LV
            if (HP1 == 1) setValveState(_valveStates.at(0)); // Might need to make a setReverseState function.
            else if (HP1 == 0) setValveState(_valveStates.at(1));
            return;
            // Test and see if LV already receives the reverted state from the python gui
        case 2: setValveState(_valveStates.at(HP2)); return;// not used
        case 3: setValveState(_valveStates.at(data.at(0).toInt(nullptr, 16)));   return; // LDR
        case 4: setValveState(_valveStates.at(data.at(1).toInt(nullptr, 16)));   return; // LDV
        case 5: setValveState(_valveStates.at(data.at(2).toInt(nullptr, 16)));   return; // FV
        case 6: setValveState(_valveStates.at(data.at(3).toInt(nullptr, 16)));   return; // not used
        case 7: setValveState(_valveStates.at(data.at(4).toInt(nullptr, 16)));   return; // FDR
        case 8: setValveState(_valveStates.at(data.at(5).toInt(nullptr, 16)));   return; // FDV
        case 9: setValveState(_valveStates.at(data.at(6).toInt(nullptr, 16)));   return; // not used
        case 10:setValveState(_valveStates.at(data.at(7).toInt(nullptr, 16)));   return; // not used
        }
        break;
    case Node::NodeID::PASA_NODE:
        switch (_HP_channel)
        {
        case 1:     setValveState(_valveStates.at(HP1)); return;
        case 2:     setValveState(_valveStates.at(HP2)); return;
        case 3:     setValveState(_valveStates.at(data.at(0).toInt(nullptr, 16)));return;
        case 4:     setValveState(_valveStates.at(data.at(1).toInt(nullptr, 16)));return;
        case 5:     setValveState(_valveStates.at(data.at(2).toInt(nullptr, 16)));return;
        case 6:     setValveState(_valveStates.at(data.at(3).toInt(nullptr, 16)));return;
        case 7:     setValveState(_valveStates.at(data.at(4).toInt(nullptr, 16)));return;
        case 8:     setValveState(_valveStates.at(data.at(5).toInt(nullptr, 16)));return;
        case 9:     setValveState(_valveStates.at(data.at(6).toInt(nullptr, 16)));return;
        case 10:    setValveState(_valveStates.at(data.at(7).toInt(nullptr, 16)));return;
        }
        break;
    }
*/
}

void Valve::onValveReceivedFD(const QList<QByteArray>& data)
{
    qInfo() << "Enter Valve::onValveReceivedID function with object ID: " << _ID;
    for (int i = 0; i < data.length(); i = i + 2)
    {
        if (_ID == data.at(i).toUInt(nullptr,16))
        {
            if(_ID == 26 || _ID == 27) //Pyro's ID's
            {
                setPyroState(data.at(i+1).toUInt(nullptr,16));
                break;
            }
            else
            {
                //setValveState(static_cast<Valve::ValveState>(data.at(i+1).toUInt(nullptr,16)));
                setValveState(data.at(i+1).toUInt(nullptr,16));
                break;
            }

        }
    }
}

QVariant Valve::valveState() const
{
    return _valveState;
}

void Valve::setValveState(QVariant newValveState)
{
    if (_valveState == newValveState) return;
    _valveState = newValveState;
    emit ValveStateChanged(); // for QML to handle
}

QVariant Valve::pyroState() const
{
    return _pyroState;
}

void Valve::setPyroState(QVariant newPyroState)
{
    if (_pyroState == newPyroState)
        return;
    _pyroState = newPyroState;
    emit pyroStateChanged();
}

QString Valve::name()
{
    return _name;
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

