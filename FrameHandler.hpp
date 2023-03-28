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

//enum CommandAuthority
//{
//    view = 0,
//    test = 1,
//    firing = 2,
//    override = 3,
//    absolutism = 4
//};

enum GuiVehicleState // if the vehicle state is in a certain state, only certain commands are allowed sent.
{
    debugMode = 0,
    passivatedState = 1,
    testState = 2,
    abortState = 3,
    ventState = 4,
    Off_Nominal_State = 5,
    Hi_Press_Press_Arm_State = 6,
    Hi_Press_Pressurize_State = 7,
    Tank_Press_Arm_State = 8,
    Tank_Press_State = 9,
    Fire_Arm_State = 10,
    Fire_State = 11,

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
    GuiVehicleState _vehicleState {GuiVehicleState::debugMode}; // set by frames received in this thread,
                                                               // read by the GUI in the main thread

    GuiVehicleState _noteStatusBang {_vehicleState};
    GuiVehicleState _nodeStatusRenegadeEngine {_vehicleState};
    GuiVehicleState _nodeStatusRenegadeProp {_vehicleState};


    QList<QCanBusFrame> _dataFrameList;     // store these frames here to view later on
    QList<QCanBusFrame> _remoteFrameList;   // store these frames here to view later on
    QList<QCanBusFrame> _errorFrameList;    // store these frames here to view later on
    QCanBusFrame _dataFrame{0,0}; // Maybe just create this inside of the onFramesReceived slot?

    QString _busStatus;

    bool _loop {true};
public:
    explicit FrameHandler(QObject *parent = nullptr);
    ~FrameHandler();
    GuiVehicleState getVehicleState() const;

    bool isOperational();

signals:
    bool sensorReceived(quint16 ID_A, quint32 ID_B, QList<QByteArray> data);
    bool valveReceived(quint16 ID_A, quint32 ID_B, QList<QByteArray> data);
    bool stateReceived(quint16 ID_A, QList<QByteArray> data);
    void remoteFrameConstructed(); // might not need

public slots: // slots that handled signals from QML should return void or basic types that can be converted between C++ and QML

    bool connectCan();
    bool disconnectCan();
    QString getBusStatus();

    void onErrorOccurred(QCanBusDevice::CanBusError error);
    void onFramesReceived(); // store a frame in the _dataFrame variable
    void onFramesWritten(quint64 framesCount);
    void onStateChanged(QCanBusDevice::CanBusDeviceState state);

    void sendFrame(QCanBusFrame::FrameId ID, const char* dataHexString); // invoked via a signal in QML

    void setVehicleState(GuiVehicleState newVehicleState);
    // May need to connect QML items to the remoteFrameConstruct method...
public:
    void run() override;
};

#endif // FRAMEHANDLER_HPP
