#include "Autosequence.hpp"

Autosequence::Autosequence(QObject *parent, QList<QVariant> args)
    : QObject{parent}, _name{args.at(0).toString()},
    _id{static_cast<quint16>(args.at(1).toUInt(nullptr))},
    _hostNodeID{static_cast<quint16>(args.at(2).toUInt(nullptr))}
{

}


void Autosequence::onAutosequenceReceivedFD(const QList<QByteArray> &data)
{
    qInfo() << "Enter Autosequence::onAutosequenceReceivedFD() function with object ID: " << _id;
    for (int i = 0; i < data.length(); i = i + 10) //Payload size is 10 per object
    {
        if (_id == data.at(0).toUInt(nullptr,16))
        {
            setState(data.at(1).toUInt(nullptr,16));

            quint8 u_8x8[8] = { static_cast<quint8>(data.at(9).toUInt(nullptr,16)),
                               static_cast<quint8>(data.at(8).toUInt(nullptr,16)),
                               static_cast<quint8>(data.at(7).toUInt(nullptr,16)),
                               static_cast<quint8>(data.at(6).toUInt(nullptr,16)),
                               static_cast<quint8>(data.at(5).toUInt(nullptr,16)),
                               static_cast<quint8>(data.at(4).toUInt(nullptr,16)),
                               static_cast<quint8>(data.at(3).toUInt(nullptr,16)),
                               static_cast<quint8>(data.at(2).toUInt(nullptr,16))};
            qint64 currentCountDown {0};
            memcpy(&currentCountDown, u_8x8, 8);
            setCurrentCountdown(currentCountDown);
            break;
        }
    }
}

QString Autosequence::name() const
{
    return _name;
}

quint16 Autosequence::id() const
{
    return _id;
}

quint16 Autosequence::hostNodeID() const
{
    return _hostNodeID;
}

qint64 Autosequence::currentCountdown() const
{
    return _currentCountdown;
}

void Autosequence::setCurrentCountdown(qint64 newCurrentCountdown)
{
    if (_currentCountdown == newCurrentCountdown)
        return;
    _currentCountdown = newCurrentCountdown;
    emit currentCountdownChanged();
}

QVariant Autosequence::state() const
{
    return _state;
}

void Autosequence::setState(QVariant newAutosequenceState)
{
    if (_state == newAutosequenceState)
        return;
    _state = newAutosequenceState;
    emit stateChanged();
}

