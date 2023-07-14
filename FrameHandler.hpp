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
#include <QQmlPropertyMap>
#include <QBitArray> // might need to combine with QList to have QBiteArrayList
#include <QByteArray>
#include <QByteArrayList>
#include <algorithm> // to reverse frame ID bits

#include "Sensor.hpp"
#include "HPSensor.hpp"
#include "Valve.hpp"
#include "Controller.hpp"
#include "Autosequence.hpp"
#include "TankPressController.hpp"
#include "EngineController.hpp"
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

#define AUTOSEQUENCE_ID_OFFSET 50
#define SENSOR_SUITE_ID_OFFSET 150
#define PROP_NODE_STATE_ID_OFFSET 200
#define HP_OBJECT_ID_OFFSET 210
#define HP_SENSOR_ID_OFFSET 220  // HP sensor array has 20 sensors, 10 on Engine Node 2 and another 10 on Prop Node 3
#define SENSOR_ID_OFFSET 230     // normal sensor array has 23 sensors
#define ENGINE_CONTROLLER_ID_OFFSET 250
#define TANK_PRESS_CONTROLLER_ID_OFFSET 260

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
    Q_ENUM(VehicleState)

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

    enum class Command
    {
        // we reserve 0 to be a no command state
        COMMAND_NOCOMMAND = 0,
        COMMAND_passive = 1,                          //Start of global states
        COMMAND_standby = 3,
        COMMAND_test_exit = 4,                      //not implemented yet into state machine
        COMMAND_test = 5,
        COMMAND_abort = 7,
        COMMAND_vent = 9,
        COMMAND_HiPressArm = 11,
        COMMAND_HiPressPressurized = 13,
        COMMAND_TankPressArm = 15,
        COMMAND_TankPressPressurized = 17,
        COMMAND_fireArm = 19,
        COMMAND_fire = 21,                          //End of global states
        COMMAND_ExitOffNominal = 22,
        COMMAND_EnterOffNominal = 23,
        COMMAND_closeHiPress = 32,                  //Start of individual device states
        COMMAND_openHiPress = 33,
        COMMAND_closeHiPressVent = 34,
        COMMAND_openHiPressVent = 35,
        COMMAND_closeLoxVent = 36,
        COMMAND_openLoxVent = 37,
        COMMAND_closeLoxPressValve = 38,
        COMMAND_openLoxPressValve = 39,
        COMMAND_closeLoxPressLineVent = 40,
        COMMAND_openLoxPressLineVent = 41,
        COMMAND_closeFuelVent = 42,
        COMMAND_openFuelVent = 43,
        COMMAND_closeFuelPressValve = 44,
        COMMAND_openFuelPressValve = 45,
        COMMAND_closeFuelPressLineVent = 46,
        COMMAND_openFuelPressLineVent = 47,
        COMMAND_closeLoxMV = 48,
        COMMAND_openLoxMV = 49,
        COMMAND_closeFuelMV = 50,
        COMMAND_openFuelMV = 51,
        COMMAND_engineIgniterPyro1_Off = 52,            //DO NOT MATCH ID FORMAT
        COMMAND_engineIgniterPyro1_On = 53,
        COMMAND_engineIgniterPyro2_Off = 54,
        COMMAND_engineIgniterPyro2_On = 55,                         //End of individual device states
        COMMAND_allSensorsOff = 126,                        //For Calibration Routines/testing
        COMMAND_allSensorsSlow = 127,                       //For Calibration Routines/testing
        COMMAND_allSensorsMedium = 128,                     //For Calibration Routines/testing
        COMMAND_allSensorsFast = 129,                       //For Calibration Routines/testing
        COMMAND_allSensorsCalibration = 130,                //For Calibration Routines/testing
        COMMAND_propProgSetting = 237,                      // placeholder to use for sending specific program
        COMMAND_node1RESET = 238,                            // Use for reset command that writes to internal reset register, needs a following byte to ID the node to be valid
        COMMAND_node2RESET = 239,                            // Use for reset command that writes to internal reset register, needs a following byte to ID the node to be valid
        COMMAND_node3RESET = 240,                            // Use for reset command that writes to internal reset register, needs a following byte to ID the node to be valid
        COMMAND_node4RESET = 241,                            // Use for reset command that writes to internal reset register, needs a following byte to ID the node to be valid
        COMMAND_node5RESET = 242,                            // Use for reset command that writes to internal reset register, needs a following byte to ID the node to be valid
        COMMAND_node6RESET = 243,                            // Use for reset command that writes to internal reset register, needs a following byte to ID the node to be valid
        COMMAND_node7RESET = 244,                            // Use for reset command that writes to internal reset register, needs a following byte to ID the node to be valid
        COMMAND_GLOBALRESET = 254,                          // Use for reset command that writes to internal reset register
        COMMAND_reseved = 255,                              // 255 Reserved for future use
        COMMAND_SIZE, // not a valid command but it is useful for checking if recieved messages are valid commands, see CANRead. Always leave this at the end of the enum listcomm
    };
    Q_ENUM(Command)

    enum class NodeSyncStatus // Should only issue warning if nodes are not in sync or something
    {
        NOT_IN_SYNC = 0,
        IN_SYNC     = 1
    };
    Q_ENUM(NodeSyncStatus)

private:
    Q_OBJECT
    Q_PROPERTY(QQmlPropertyMap* sensors READ sensors CONSTANT)
    Q_PROPERTY(QQmlPropertyMap* HPSensors READ HPSensors CONSTANT)
    Q_PROPERTY(QQmlPropertyMap* valves READ valves CONSTANT)
    Q_PROPERTY(QQmlPropertyMap* autosequences READ autosequences CONSTANT)
    Q_PROPERTY(QQmlPropertyMap* tankPressControllers READ tankPressControllers CONSTANT)
    Q_PROPERTY(QQmlPropertyMap* engineControllers READ engineControllers CONSTANT)
    // ENGINE CONTROLLER!!!!


    Q_PROPERTY(VehicleState nodeStatusRenegadeEngine READ nodeStatusRenegadeEngine NOTIFY nodeStatusRenegadeEngineChanged)
    Q_PROPERTY(VehicleState nodeStatusRenegadeProp READ nodeStatusRenegadeProp NOTIFY nodeStatusRenegadePropChanged)
    Q_PROPERTY(MissionState missionStatusRenegadeEngine READ missionStatusRenegadeEngine NOTIFY missionStatusRenegadeEngineChanged)
    Q_PROPERTY(MissionState missionStatusRenegadeProp READ missionStatusRenegadeProp NOTIFY missionStatusRenegadePropChanged)
    Q_PROPERTY(Command currentCommandRenegadeEngine READ currentCommandRenegadeEngine NOTIFY currentCommandRenegadeEngineChanged)
    Q_PROPERTY(Command currentCommandRenegadeProp READ currentCommandRenegadeProp NOTIFY currentCommandRenegadePropChanged)
    Q_PROPERTY(QString busStatus READ busStatus NOTIFY busStatusChanged)


    //Q_PROPERTY(QStack<QVarLengthArray<quint32, 2>> throttlePoints READ throttlePoints NOTIFY throttlePoints)
    QML_ELEMENT
    QML_UNCREATABLE("C++ instantiation only")

    QCanBusDevice* _can0 {nullptr};
    QQmlPropertyMap _HPSensors {QQmlPropertyMap(this)};
    QQmlPropertyMap _sensors {QQmlPropertyMap(this)};
    QQmlPropertyMap _valves {QQmlPropertyMap(this)};
    QQmlPropertyMap _autosequences {QQmlPropertyMap(this)};
    QQmlPropertyMap _tankPressControllers {QQmlPropertyMap(this)};
    QQmlPropertyMap _engineControllers{QQmlPropertyMap(this)};

    VehicleState _nodeStatusRenegadeEngine {VehicleState::SETUP};
    VehicleState _nodeStatusRenegadeProp {VehicleState::SETUP};
    MissionState _missionStatusRenegadeEngine {MissionState::PASSIVE};
    MissionState _missionStatusRenegadeProp {MissionState::PASSIVE};
    Command _currentCommandRenegadeEngine {Command::COMMAND_NOCOMMAND};
    Command _currentCommandRenegadeProp {Command::COMMAND_NOCOMMAND};
    // Implement this............. Every time other node updates, the setter for this must be called to check if all nodes are in the same state
    NodeSyncStatus _nodeSyncStatus; // updates every time a node changed and checks if all nodes are in the same state

    const QList<VehicleState> _vehicleStates {  VehicleState::SETUP, // This is solely for the vehicleState setter.
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

    const QList<MissionState> _missionStates {MissionState::PASSIVE, // This is solely for the missionState setter.
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

    const QMap<quint16, Command> _commands // This is solely for the command setter.
    {
        {static_cast<quint16>(Command::COMMAND_NOCOMMAND), Command::COMMAND_NOCOMMAND},
        {static_cast<quint16>(Command::COMMAND_passive), Command::COMMAND_passive},
        {static_cast<quint16>(Command::COMMAND_standby), Command::COMMAND_standby},
        {static_cast<quint16>(Command::COMMAND_test_exit), Command::COMMAND_test_exit},
        {static_cast<quint16>(Command::COMMAND_test), Command::COMMAND_test},
        {static_cast<quint16>(Command::COMMAND_abort), Command::COMMAND_abort},
        {static_cast<quint16>(Command::COMMAND_passive), Command::COMMAND_passive},
        {static_cast<quint16>(Command::COMMAND_vent), Command::COMMAND_vent},
        {static_cast<quint16>(Command::COMMAND_HiPressArm), Command::COMMAND_HiPressArm},
        {static_cast<quint16>(Command::COMMAND_HiPressPressurized), Command::COMMAND_HiPressPressurized},
        {static_cast<quint16>(Command::COMMAND_fireArm), Command::COMMAND_fireArm},
        {static_cast<quint16>(Command::COMMAND_fire), Command::COMMAND_fire},
        {static_cast<quint16>(Command::COMMAND_ExitOffNominal), Command::COMMAND_ExitOffNominal},
        {static_cast<quint16>(Command::COMMAND_EnterOffNominal), Command::COMMAND_EnterOffNominal},
        {static_cast<quint16>(Command::COMMAND_closeHiPress), Command::COMMAND_closeHiPress},
        {static_cast<quint16>(Command::COMMAND_openHiPress), Command::COMMAND_openHiPress},
        {static_cast<quint16>(Command::COMMAND_closeHiPressVent), Command::COMMAND_closeHiPressVent},
        {static_cast<quint16>(Command::COMMAND_openHiPressVent), Command::COMMAND_openHiPressVent},
        {static_cast<quint16>(Command::COMMAND_closeLoxVent), Command::COMMAND_closeLoxVent},
        {static_cast<quint16>(Command::COMMAND_openLoxVent), Command::COMMAND_openLoxVent},
        {static_cast<quint16>(Command::COMMAND_closeLoxPressValve), Command::COMMAND_closeLoxPressValve},
        {static_cast<quint16>(Command::COMMAND_openLoxPressValve), Command::COMMAND_openLoxPressValve},
        {static_cast<quint16>(Command::COMMAND_closeLoxPressLineVent), Command::COMMAND_closeLoxPressLineVent},
        {static_cast<quint16>(Command::COMMAND_openLoxPressLineVent), Command::COMMAND_openLoxPressLineVent},
        {static_cast<quint16>(Command::COMMAND_closeFuelVent), Command::COMMAND_closeFuelVent},
        {static_cast<quint16>(Command::COMMAND_openFuelVent), Command::COMMAND_openFuelVent},
        {static_cast<quint16>(Command::COMMAND_closeFuelPressValve), Command::COMMAND_closeFuelPressValve},
        {static_cast<quint16>(Command::COMMAND_openFuelPressValve), Command::COMMAND_openFuelPressValve},
        {static_cast<quint16>(Command::COMMAND_closeFuelPressLineVent), Command::COMMAND_closeFuelPressLineVent},
        {static_cast<quint16>(Command::COMMAND_openFuelPressLineVent), Command::COMMAND_openFuelPressLineVent},
        {static_cast<quint16>(Command::COMMAND_openLoxMV), Command::COMMAND_openLoxMV},
        {static_cast<quint16>(Command::COMMAND_closeFuelMV), Command::COMMAND_closeFuelMV},
        {static_cast<quint16>(Command::COMMAND_openFuelMV), Command::COMMAND_openFuelMV},
        {static_cast<quint16>(Command::COMMAND_engineIgniterPyro1_Off), Command::COMMAND_engineIgniterPyro1_Off},
        {static_cast<quint16>(Command::COMMAND_engineIgniterPyro1_On), Command::COMMAND_engineIgniterPyro1_On},
        {static_cast<quint16>(Command::COMMAND_engineIgniterPyro2_Off), Command::COMMAND_engineIgniterPyro2_Off},
        {static_cast<quint16>(Command::COMMAND_engineIgniterPyro2_On), Command::COMMAND_engineIgniterPyro2_On},
        {static_cast<quint16>(Command::COMMAND_allSensorsOff), Command::COMMAND_allSensorsOff},
        {static_cast<quint16>(Command::COMMAND_allSensorsSlow), Command::COMMAND_allSensorsSlow},
        {static_cast<quint16>(Command::COMMAND_allSensorsMedium), Command::COMMAND_allSensorsMedium},
        {static_cast<quint16>(Command::COMMAND_allSensorsFast), Command::COMMAND_allSensorsFast},
        {static_cast<quint16>(Command::COMMAND_allSensorsCalibration), Command::COMMAND_allSensorsCalibration},
        {static_cast<quint16>(Command::COMMAND_propProgSetting), Command::COMMAND_propProgSetting},
        {static_cast<quint16>(Command::COMMAND_node1RESET), Command::COMMAND_node1RESET},
        {static_cast<quint16>(Command::COMMAND_node2RESET), Command::COMMAND_node2RESET},
        {static_cast<quint16>(Command::COMMAND_node3RESET), Command::COMMAND_node3RESET},
        {static_cast<quint16>(Command::COMMAND_node4RESET), Command::COMMAND_node4RESET},
        {static_cast<quint16>(Command::COMMAND_node5RESET), Command::COMMAND_node5RESET},
        {static_cast<quint16>(Command::COMMAND_node6RESET), Command::COMMAND_node6RESET},
        {static_cast<quint16>(Command::COMMAND_GLOBALRESET), Command::COMMAND_GLOBALRESET},
        {static_cast<quint16>(Command::COMMAND_reseved), Command::COMMAND_reseved},
        {static_cast<quint16>(Command::COMMAND_SIZE), Command::COMMAND_SIZE}
    };

    QStack<QVarLengthArray<quint32, 2>> _throttlePoints;


    QList<QCanBusFrame> _dataFrameList;     // store these frames here to view later on
    QList<QCanBusFrame> _remoteFrameList;   // store these frames here to view later on
    QList<QCanBusFrame> _errorFrameList;    // store these frames here to view later on
    //QCanBusFrame _dataFrame{0,0}; // Maybe just create this inside of the onFramesReceived slot?

    QString _busStatus;


public:
    explicit FrameHandler(QObject *parent = nullptr);
    ~FrameHandler();


    bool isOperational();

    QQmlPropertyMap* sensors();
    QQmlPropertyMap* HPSensors();
    QQmlPropertyMap* valves();
    QQmlPropertyMap* autosequences();
    QQmlPropertyMap* tankPressControllers();
    QQmlPropertyMap* engineControllers();

    FrameHandler::VehicleState nodeStatusRenegadeEngine() const;
    void setNodeStatusRenegadeEngine(FrameHandler::VehicleState newNodeStatusRenegadeEngine);

    FrameHandler::VehicleState nodeStatusRenegadeProp() const;
    void setNodeStatusRenegadeProp(FrameHandler::VehicleState newNodeStatusRenegadeProp);

    FrameHandler::MissionState missionStatusRenegadeEngine() const;
    void setMissionStatusRenegadeEngine(FrameHandler::MissionState newMissionStatusRenegadeEngine);

    FrameHandler::MissionState missionStatusRenegadeProp() const;
    void setMissionStatusRenegadeProp(FrameHandler::MissionState newMissionStatusRenegadeProp);

    FrameHandler::Command currentCommandRenegadeEngine() const;
    void setCurrentCommandRenegadeEngine(FrameHandler::Command newCurrentCommandRenegadeEngine);

    Command currentCommandRenegadeProp() const;
    void setCurrentCommandRenegadeProp(Command newCurrentCommandRenegadeProp);

    QString busStatus() const;
    void getBusStatus();

    void nodeSynchronization(); // don't wanna make bool for other scenarios
signals:
    void sensorReceived(quint16 ID_A, quint32 ID_B, QList<QByteArray> data);
    void valveReceived(quint16 HP1, quint16 HP2, QList<QByteArray> data);
    void stateReceived(quint16 ID_A, QList<QByteArray> data);

    void sensorReceivedFD(const QList<QByteArray>& data);
    void HPSensorReceivedFD(const QList<QByteArray>& data);
    void valveReceivedFD(const QList<QByteArray>& data);
    void stateReceivedFD(const QList<QByteArray>& data);
    void autosequenceReceivedFD(const QList<QByteArray>& data);
    void tankPressControllerReceivedFD(const QList<QByteArray>& data);
    void engineControllerReceivedFD(const QList<QByteArray>& data);

    void nodeStatusRenegadeEngineChanged();
    void nodeStatusRenegadePropChanged();
    void missionStatusRenegadeEngineChanged();
    void missionStatusRenegadePropChanged();
    void currentCommandRenegadeEngineChanged();
    void currentCommandRenegadePropChanged();

    void busStatusChanged();

    void tankPressControllersChanged();

public slots: // slots that handled signals from QML should return void or basic types that can be converted between C++ and QML

    bool connectCan();
    bool disconnectCan();

    void onErrorOccurred(QCanBusDevice::CanBusError error);
    void onFramesReceived(); // store a frame in the _dataFrame variable
    void onFramesWritten(quint64 framesCount);
    void onStateChanged(QCanBusDevice::CanBusDeviceState state);

    void sendFrame(quint32 ID, QString dataHexString, QCanBusFrame::FrameType frameType = QCanBusFrame::DataFrame,
                               bool bitRateSwitch = false , bool extendedFrameFormat = false, bool FlexibleDataRateFormat = false); // invoked via a signal in QML
    // May need to connect QML items to the remoteFrameConstruct method...
public:
    void run() override;


};

Q_DECLARE_METATYPE(FrameHandler)

#endif
