#ifndef AUTOSEQUENCE_HPP
#define AUTOSEQUENCE_HPP

#include <QObject>
#include <qqml.h>

//#include "AutosequenceObjectDefinitions.hpp"

class Autosequence : public QObject
{
public:
    enum class AutosequenceState
    {
        STANDBY = 0,
        RUN_COMMANDED = 1,
        RUNNING = 2,
        HOLD = 3,
        AUTOSEQUENCE_STATE_SIZE = 4
    };
    Q_ENUM(AutosequenceState)
private:
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("C++ instantiation only")

    Autosequence::AutosequenceState _autosequenceState {Autosequence::AutosequenceState::STANDBY};

    QString _name{""};

    quint16 _id {0};
    quint16 _hostNodeID {0};
    qint64 _currentCountdown {0}; // sent by alaras in microseconds

    //union {
    //    quint8 u_8x8[8];
    //    qint64 int_8byte;
    //};

    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(quint16 id READ id CONSTANT)
    Q_PROPERTY(quint16 hostNodeID READ hostNodeID CONSTANT)

    Q_PROPERTY(qint64 currentCountdown READ currentCountdown NOTIFY currentCountdownChanged)
    Q_PROPERTY(Autosequence::AutosequenceState autosequenceState READ autosequenceState NOTIFY autosequenceStateChanged)


public:
    explicit Autosequence(QObject *parent = nullptr, QList<QVariant> args = {0,0,0});

    QString name() const;

    quint16 id() const;

    quint16 hostNodeID() const;

    qint64 currentCountdown() const;
    void setCurrentCountdown(qint64 newCurrentCountdown);

    Autosequence::AutosequenceState autosequenceState() const;
    void setAutosequenceState(Autosequence::AutosequenceState newAutosequenceState);



signals:

    void idChanged();
    void hostNodeIDChanged();
    void currentCountdownChanged();
    void autosequenceStateChanged();
    void nameChanged();

public slots:
    void onAutosequenceReceivedFD(const QList<QByteArray>& data);
};

Q_DECLARE_METATYPE(Autosequence);

#endif // AUTOSEQUENCE_HPP
