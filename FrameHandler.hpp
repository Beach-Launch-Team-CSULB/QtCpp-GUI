#ifndef FRAMEHANDLER_HPP
#define FRAMEHANDLER_HPP

#include <QObject>
#include <QDebug>

#include <QCanBus>
#include <QCanBusDeviceInfo>
#include <QCanBusDevice>
#include <QCanBusFrame>

#include <QString>

#include <QRunnable>
#include <QThread>
#include <QMutex>         // might not need
#include <QMutexLocker>   // might not need

#include <QList>
#include <QMap>
#include <QBitArray> // might need to combine with QList to have QBiteArrayList
#include <QByteArray>
#include <QByteArrayList>

#include "Sensor.hpp"
#include "Valve.hpp"

enum CommandAuthority
{
    view = 0,
    test = 1,
    override = 2,
    absolutism = 3
};

/*!
 * @brief
 * Receive commands from the Alara to update the GUI
 */

class FrameHandler : public QObject, public QRunnable
{
private:
    Q_OBJECT
    QCanBusDevice* _can0 {nullptr}; // hmmmmmmmm

    // Should I store all objects like valves and sensors in this thread???
    // If so, then the main event loop will access this thread to read,
    // and this thread can modify stuff inside itself.

    CommandAuthority commandMode {CommandAuthority::view};  // QML buttons should check this before constructing and sending out frames.
                                                            // Set by the GUI, so this will communicate with the main thread
                                                            // -> Signal and Slots with Queued Connection to ensure thread safety
    QList<QCanBusFrame> _dataFrameList;
    QCanBusFrame _dataFrame{0,0}; // ID and Data are 0, to be set by methods
    QCanBusFrame _remoteFrame{0,0};

    QString _error{"No error"};
    bool _loop {true};
    bool _state {false};
public:
    explicit FrameHandler(QObject *parent = nullptr);

    CommandAuthority getCommandMode() const;


signals:
    bool sensorReceived(quint32 ID, QByteArray data);
    bool valveReceived(quint32 ID, QByteArray data);
    bool stateReceived(quint32 ID, QByteArray data);
    void remoteFrameConstructed(); // might not need

public slots:

    bool connectCan();
    bool disconnectCan();
    QString busStatus();

    void onErrorOccurred();
    void onFramesReceived(); // store a frame in the _dataFrame variable
    void onFramesWritten();
    void onStateChanged(QCanBusDevice::CanBusDeviceState state);

    QCanBusFrame remoteFrameConstruct(QCanBusFrame::FrameId ID, const QByteArray& data); // pass into the writeFrame method.
    void sendFrame(const QCanBusFrame frame) const;
    void setCommandMode(CommandAuthority newCommandMode);
    // May need to connect QML items to the remoteFrameConstruct method...
public:
    void run() override;
};

#endif // FRAMEHANDLER_HPP
