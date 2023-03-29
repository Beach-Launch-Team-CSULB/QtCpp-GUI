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
#include <QMap> // might not need
#include <QQmlPropertyMap>
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

private:
    Q_OBJECT
    Q_PROPERTY(QMap<QString, Sensor*> sensors READ sensors)
    Q_PROPERTY(QMap<QString, Valve*> valves READ valves)
    Q_PROPERTY(VehicleState nodeStatusRenegadeEngine READ nodeStatusRenegadeEngine NOTIFY nodeStatusRenegadeEngineChanged)
    Q_PROPERTY(VehicleState nodeStatusRenegadeProp READ nodeStatusRenegadeProp NOTIFY nodeStatusRenegadePropChanged)
    Q_PROPERTY(VehicleState nodeStatusBang READ nodeStatusBang NOTIFY nodeStatusBangChanged)
    Q_PROPERTY(float autosequenceTime READ autosequenceTime NOTIFY autosequenceTimeChanged)

    QCanBusDevice* _can0 {nullptr}; // hmmmmmmmm
    QMap<QString, Sensor*> _sensors;
    QMap<QString, Valve*> _valves;

    // Should I store all objects like valves and sensors in this thread???
    // If so, then the main event loop will access this thread to read,
    // and this thread can modify stuff inside itself.
    VehicleState _nodeStatusRenegadeEngine {VehicleState::SETUP}; // ID A = 514 , use switch case
    VehicleState _nodeStatusRenegadeProp {VehicleState::SETUP}; // ID A = 515, , use switch case
    VehicleState _nodeStatusBang {VehicleState::SETUP}; // ID A = 520 , use switch case

    VehicleState zero {VehicleState::SETUP};
    VehicleState one {VehicleState::PASSIVE};
    VehicleState two {VehicleState::STANDBY};
    VehicleState three {VehicleState::TEST};
    VehicleState four {VehicleState::ABORT};
    VehicleState five {VehicleState::VENT};
    VehicleState six {VehicleState::OFF_NOMINAL};
    VehicleState seven {VehicleState::HI_PRESS_ARM};
    VehicleState eight {VehicleState::HI_PRESS_PRESSURIZED};
    VehicleState nine {VehicleState::TANK_PRESS_ARM};
    VehicleState ten {VehicleState::TANK_PRESS_PRESSURIZED};
    VehicleState eleven {VehicleState::FIRE_ARMED};
    VehicleState twelve {VehicleState::FIRE};

    QList<VehicleState> cursed {zero,one,two,three,four,five,six,seven,eight,nine,ten,eleven,twelve}; // :D

    float _autosequenceTime {0.0f};


    QList<QCanBusFrame> _dataFrameList;     // store these frames here to view later on
    QList<QCanBusFrame> _remoteFrameList;   // store these frames here to view later on
    QList<QCanBusFrame> _errorFrameList;    // store these frames here to view later on
    //QCanBusFrame _dataFrame{0,0}; // Maybe just create this inside of the onFramesReceived slot?

    QString _busStatus;


    bool _loop {true};
public:
    explicit FrameHandler(QObject *parent = nullptr);
    ~FrameHandler();    


    bool isOperational();

    QMap<QString, Sensor*> sensors() const;
    QMap<QString, Valve*> valves() const;

    float autosequenceTime() const;
    void setAutosequenceTime(float newAutosequenceTime);

    FrameHandler::VehicleState nodeStatusRenegadeEngine() const;
    void setNodeStatusRenegadeEngine(FrameHandler::VehicleState newNodeStatusRenegadeEngine);
    FrameHandler::VehicleState nodeStatusRenegadeProp() const;
    void setNodeStatusRenegadeProp(FrameHandler::VehicleState newNodeStatusRenegadeProp);
    FrameHandler::VehicleState nodeStatusBang() const;
    void setNodeStatusBang(FrameHandler::VehicleState newNodeStatusBang);

signals:
    bool sensorReceived(quint16 ID_A, quint32 ID_B, QList<QByteArray> data);
    bool valveReceived(quint16 ID_A, quint32 ID_B, QList<QByteArray> data);
    bool stateReceived(quint16 ID_A, QList<QByteArray> data);


    void autosequenceTimeChanged();
    void nodeStatusRenegadeEngineChanged();
    void nodeStatusRenegadePropChanged();
    void nodeStatusBangChanged();

public slots: // slots that handled signals from QML should return void or basic types that can be converted between C++ and QML

    bool connectCan();
    bool disconnectCan();
    QString getBusStatus();

    void onErrorOccurred(QCanBusDevice::CanBusError error);
    void onFramesReceived(); // store a frame in the _dataFrame variable
    void onFramesWritten(quint64 framesCount);
    void onStateChanged(QCanBusDevice::CanBusDeviceState state);

    void sendFrame(QCanBusFrame::FrameId ID, const char* dataHexString); // invoked via a signal in QML
    // May need to connect QML items to the remoteFrameConstruct method...
public:
    void run() override;
};

#endif // FRAMEHANDLER_HPP
