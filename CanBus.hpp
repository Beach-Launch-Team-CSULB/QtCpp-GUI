/*
REWORK THIS. SHOULD NEVER INHERIT QCanBusDevice
Migrate to FrameHandler
*/
#ifndef CanBus_HPP
#define CanBus_HPP

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

enum class commandAuthority
{

};

/*!
 * @brief
 * Receive commands from the Alara to update the GUI
 */
class CanBus : public QCanBusDevice, public QRunnable // REWORK: DO NOT INHERIT FROM QcanBusDevice
{
private:
    Q_OBJECT

    // call readFrame() then dissect the frame and pass in? ////////////////////////////////////////////////////
    //inline static QBitArray Sensors {1028}; // inline
    QBitArray _sensors {QBitArray(1028)};
    QBitArray _sensorTimeStamps {QBitArray(1028)};
    QBitArray _valves {QBitArray(64)};
    QBitArray _valvesRenegadeEngine {QBitArray(64)};
    QBitArray _valvesRenegadeProp {QBitArray(64)};
    QList<QBitArray> _controllers {QBitArray(50),QBitArray(50),QBitArray(50),QBitArray(50),
                                 QBitArray(50),QBitArray(50),QBitArray(50),QBitArray(50),
                                 QBitArray(50),QBitArray(50),QBitArray(50),QBitArray(50),};
    QList<QString> _vehicleStates {"Setup",
                                  "Passive",
                                  "Standby",
                                  "Test",
                                  "Abort",
                                  "Vent",
                                  "OFF Nominal",
                                  "Hi Press Arm",
                                  "Hi Press Pressurized",
                                  "Tank Press Arm",
                                  "Tank Press Pressurized",
                                  "Fire Arm",
                                  "Fire"};

    QString _noteStatusBang {_vehicleStates.at(0)};
    QString _nodeStatusRenegadeEngine {_vehicleStates.at(0)};
    QString _nodeStatusRenegadeProp {_vehicleStates.at(0)};


    qint32 _autoSequenceTime {0};
    qint32 _throttlePoint;

    QList<QCanBusFrame> _dataFrameList;
    QCanBusFrame _dataFrame{0,0}; // ID and Data are 0, to be set by methods
    QCanBusFrame _remoteFrame{0,0};

    QString _error{"No error"};
    bool _loop {true};
    bool _state {false};


public:

    explicit CanBus(QObject *parent = nullptr);
    //~CanBus(); Linker error

    CanBus(const CanBus& _) = delete;
    CanBus( CanBus&& _) = delete;

    // implementation of virtual functions


    bool state() const;
    void setState(bool newState);

    void run() override;

signals:
    bool sensorReceived(quint32 ID, QByteArray data);
    bool valveReceived(quint32 ID, QByteArray data);
    bool stateReceived(quint32 ID, QByteArray data);

public slots:

    // REWORK: THESE SLOTS SHOULD JUST CONNECT STRAIGHT TO the QCanBusDevice signals.
    void onErrorOccurred();
    void onFramesReceived(); // store a frame in the _dataFrame variable
    void onFramesWritten();
    void onStateChanged(QCanBusDevice::CanBusDeviceState state);

    // maybe make a bunch of command public slots to send commands to valves and stuff

};

QCanBusFrame remoteFrameConstruct(QCanBusFrame::FrameId ID, const QByteArray& data); // pass into the writeFrame method.
// this function is in the CanBus thread, but it will always be called from the main thread. Should look into thread safety.
// also should it be a method instead of a function? - SOLUTION: make this a method, then use slots and signals
#endif // CanBus_HPP
