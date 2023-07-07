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
#include <QStack> // for throttle point
#include <QVarLengthArray>
#include <qqml.h>
//#include <QQmlPropertyMap>
#include <QBitArray> // might need to combine with QList to have QBiteArrayList
#include <QByteArray>
#include <QByteArrayList>
#include <algorithm> // to reverse frame ID bits

#include "Sensor.hpp"
#include "Valve.hpp"
#include "Controller.hpp"
// thread interaction??
#include "GNCThread.hpp"

//enum class CommandAuthority
//{
//    view = 0,
//    test = 1,
//    firing = 2,
//    override = 3,
//    absolutism = 4
//};

/*!
 * @brief
 * Receive commands from the Alara to update the GUI
 */

class FrameHandler : public QObject, public QRunnable
{
public:
    enum class VehicleState // if the vehicle state is in a certain state, only certain commands are allowed sent.
    {
        // These are the God States, they can be reached from any position
            SETUP,      // 0
            PASSIVE,    // 1   // All physical outputs disabled
            STANDBY,    // 2
            TEST,       // 3
            ABORT,      // 4
            VENT,       // 5
            OFF_NOMINAL, // 6   off nominal is for when individual valves are actuated out of sequence


            // These states can only be accessed in sequence, from passive
            HI_PRESS_ARM,             // 7
            HI_PRESS_PRESSURIZED,     // 8
            TANK_PRESS_ARM,           // 9
            TANK_PRESS_PRESSURIZED,   // 10
            FIRE_ARMED,              // 11
            FIRE,                   // 12

    };
    Q_ENUMS(VehicleState)

    enum class MissionState
    {
        // These are the God States, they can be reached from any position
        PASSIVE,                // 0
        STANDBY,                // 1
        STATIC_TEST_ARMED,        // 2
        STATIC_TEST_ACTIVE,       // 3
        POST_TEST,               // 4
        PRELAUNCH,              // 5
        ASCENT_RAIL,             // 6
        ASCENT_FREE_THRUST,       // 7
        ASCENT_FREE_COAST,        // 8
        DESCENT_FREE,            // 9
        DESCENT_PILOT,           // 10
        DESCENT_DROGUE,          // 11
        DESCENT_MAIN,            // 12
        LANDED,                 // 13
    };
    Q_ENUM(MissionState)

    enum class NodeSyncStatus // Should only issue warning if nodes are not in sync or something
    {
        NOT_IN_SYNC = 0,
        IN_SYNC     = 1
    };

private:
    Q_OBJECT
    Q_PROPERTY(QMap<QString,Sensor*> sensors READ sensors CONSTANT)    // Consider using QQmlPropertyMap with values being QVariant if things get a bit wacky
    Q_PROPERTY(QMap<QString,Valve*> valves READ valves CONSTANT)       // Consider using QQmlPropertyMap with values being QVariant if things get a bit wacky
    Q_PROPERTY(VehicleState nodeStatusRenegadeEngine READ nodeStatusRenegadeEngine NOTIFY nodeStatusRenegadeEngineChanged)
    Q_PROPERTY(VehicleState nodeStatusRenegadeProp READ nodeStatusRenegadeProp NOTIFY nodeStatusRenegadePropChanged)
    Q_PROPERTY(VehicleState nodeStatusBang READ nodeStatusBang NOTIFY nodeStatusBangChanged)
    Q_PROPERTY(VehicleState currGUIState READ currGUIState NOTIFY currGUIStateChanged)
    Q_PROPERTY(VehicleState prevGUIState READ prevGUIState NOTIFY prevGUIStateChanged)
    Q_PROPERTY(Controller* controller READ controller CONSTANT)//NOTIFY controllerChanged)
    Q_PROPERTY(QString busStatus READ busStatus NOTIFY busStatusChanged)


    //Q_PROPERTY(QStack<QVarLengthArray<quint32, 2>> throttlePoints READ throttlePoints NOTIFY throttlePoints)
    QML_ELEMENT
    QML_UNCREATABLE("C++ instantiation only")

    QCanBusDevice* _can0 {nullptr};
    QMap<QString, Sensor*> _sensors;    // Consider using QQmlPropertyMap with values being QVariant if things get a bit wacky
    QMap<QString, Valve*> _valves;      // Consider using QQmlPropertyMap with values being QVariant if things get a bit wacky

    VehicleState _nodeStatusRenegadeEngine {VehicleState::SETUP}; // ID A = 514     I think these should be used for the frontend logic
    VehicleState _nodeStatusRenegadeProp {VehicleState::SETUP}; // ID A = 515       I think these should be used for the frontend logic
    VehicleState _nodeStatusBang {VehicleState::SETUP}; // ID A = 520, also dan said there is no ID A = 520

    // Implement this............. Every time other node updates, the setter for this must be called to check if all nodes are in the same state
    NodeSyncStatus _nodeSyncStatus; // updates every time a node changed and checks if all nodes are in the same state

    const QList<VehicleState> _vehicleStates {  VehicleState::SETUP,
                                                VehicleState::PASSIVE,
                                                VehicleState::STANDBY,
                                                VehicleState::TEST,
                                                VehicleState::ABORT,
                                                VehicleState::VENT,
                                                VehicleState::OFF_NOMINAL,
                                                VehicleState::HI_PRESS_ARM,
                                                VehicleState::HI_PRESS_PRESSURIZED,
                                                VehicleState::TANK_PRESS_ARM,
                                                VehicleState::TANK_PRESS_PRESSURIZED,
                                                VehicleState::FIRE_ARMED,
                                                VehicleState::FIRE}; // :D

    const QList<MissionState> _missionStates {MissionState::PASSIVE,
                                             MissionState::STANDBY,
                                             MissionState::STATIC_TEST_ARMED,
                                             MissionState::STATIC_TEST_ACTIVE,
                                             MissionState::POST_TEST,
                                             MissionState::PRELAUNCH,
                                             MissionState::ASCENT_RAIL,
                                             MissionState::ASCENT_FREE_THRUST,
                                             MissionState::ASCENT_FREE_COAST,
                                             MissionState::DESCENT_FREE,
                                             MissionState::DESCENT_PILOT,
                                             MissionState::DESCENT_DROGUE,
                                             MissionState::DESCENT_MAIN,
                                             MissionState::LANDED};

    QStack<QVarLengthArray<quint32, 2>> _throttlePoints;
    Controller* _controller {new Controller(this)};

    VehicleState _currGUIState {VehicleState::PASSIVE};
    VehicleState _prevGUIState;



    QList<QCanBusFrame> _dataFrameList;     // store these frames here to view later on
    QList<QCanBusFrame> _remoteFrameList;   // store these frames here to view later on
    QList<QCanBusFrame> _errorFrameList;    // store these frames here to view later on
    //QCanBusFrame _dataFrame{0,0}; // Maybe just create this inside of the onFramesReceived slot?

    QString _busStatus;
public:
    explicit FrameHandler(QObject *parent = nullptr);
    ~FrameHandler();    


    bool isOperational();
    void nodeSynchronization(); // don't wanna make bool for other scenarios

    QMap<QString, Sensor*> sensors() const;
    QMap<QString, Valve*> valves() const;
    FrameHandler::VehicleState nodeStatusRenegadeEngine() const;
    FrameHandler::VehicleState nodeStatusRenegadeProp() const;
    FrameHandler::VehicleState nodeStatusBang() const;
    FrameHandler::VehicleState currGUIState() const;
    FrameHandler::VehicleState prevGUIState() const;
    Controller* controller() const;
    QString busStatus() const;



    void setNodeStatusRenegadeEngine(FrameHandler::VehicleState newNodeStatusRenegadeEngine);
    void setNodeStatusRenegadeProp(FrameHandler::VehicleState newNodeStatusRenegadeProp);
    void setNodeStatusBang(FrameHandler::VehicleState newNodeStatusBang);
    void setcurrGUIState(FrameHandler::VehicleState newCurrGUIState);
    void prevGUIState(FrameHandler::VehicleState newPrevGUIState);
    void getBusStatus();

signals:
    bool sensorReceived(quint16 ID_A, quint32 ID_B, QList<QByteArray> data);
    //bool sensorReceived(); // canFD
    bool valveReceived(quint16 HP1, quint16 HP2, QList<QByteArray> data);
    //bool valveReceived(); // canFD
    bool stateReceived(quint16 ID_A, QList<QByteArray> data);
    //bool StateReceived(); // canFD
    void currGUIStateChanged();
    void prevGUIStateChanged();
    void nodeStatusRenegadeEngineChanged();
    void nodeStatusRenegadePropChanged();
    void nodeStatusBangChanged();

    void controllerChanged();

    void busStatusChanged();

public slots: // slots that handled signals from QML should return void or basic types that can be converted between C++ and QML
    bool connectCan();
    bool disconnectCan();


    void onErrorOccurred(QCanBusDevice::CanBusError error);
    void onFramesReceived(); // store a frame in the _dataFrame variable
    void onFramesWritten(quint64 framesCount);
    void onStateChanged(QCanBusDevice::CanBusDeviceState state);

    Q_INVOKABLE void sendFrame(QCanBusFrame::FrameId ID, QString dataHexString); // invoked via a signal in QML
    // May need to connect QML items to the remoteFrameConstruct method...
public:
    void run() override;
};

#endif // FRAMEHANDLER_HPP
