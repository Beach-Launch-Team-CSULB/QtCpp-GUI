#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// file and directory includes
#include <QFile>
#include <QDir>

// thread includes
#include <QThread>
#include <QThreadPool>
#include <QRunnable>

// CAN BUS includes
#include <QCanBus>
#include <QCanBusDeviceInfo>
#include <QCanBusDevice>
#include <QCanBusFrame>

// Byte and bit includes
#include <QList>
#include <QBitArray>
#include <QByteArray>
#include <QByteArrayList>

// Class file includes
#include "FrameHandler.hpp"
#include "CanBus.hpp"
#include "Sensor.hpp"
#include "Valve.hpp"

#include "SensorObjectDefinitions.hpp"
#include "ValveObjectDefinitions.hpp"

#define WIN1000 // How do I set flags

#ifdef WIN1000
    #include <windows.h>
#elif
    #include <X11/Xlib.h> // on raspberry pi
#endif

//Global variables
QList<const QCanBusFrame> listOfErrorFrames_globalVar;

//make a function to create can bus objects instead????
// another function to connect?

int main(int argc, char *argv[])
{


    // Setup
///////////////////////////////////////////////////////////////////////////////////////////////////
    QMap<QString,Sensor*> sensors;
    foreach(auto& sensorContructingParameter, sensorConstructingParameters) //sensor key List
    {                                                                       //{"High Press 1"} {"High Press 2"} {"Fuel Tank 1"} {"Fuel Tank 2"}
        sensors.insert(sensorContructingParameter.at(0).toString(),         //{"Lox Tank 1"} {"Lox Tank 2"} {"Fuel Dome Reg"} {"Lox Dome Reg"}
                       new Sensor{nullptr, sensorContructingParameter});    //{"Fuel Prop Inlet"} {"Lox Prop Inlet"} {"Fuel Injector"}
    }                                                                       //{"LC1"} {"LC2"} {"LC3"} {"Chamber 1"} {"Chamber 2"} {"MV Pneumatic}
    sensors.value("High Press 1"); // kinda scuffed?

    QMap<QString,Valve*> valves;
    foreach(auto& valveConstructingParameter, valveConstructingParameters)  // valve key list
    {                                                                       //{"HV"} {"HP"} {"LDR"} {"FDR"} {"LDV"}
        valves.insert(valveConstructingParameter.at(0).toString(),          // {"FDV"} {"LV"} {"FV"}
                       new Valve{nullptr, valveConstructingParameter});      //{"LMV"} {"FMV"} {"IGN1"} {"IGN2"}
    }

    //valves.value("IGN1")->;
/////////////////////////////////////////////////////////////////////////////////////////////////////
    QGuiApplication app(argc, argv);
    QDir appDir {QGuiApplication::applicationDirPath()};
    QThreadPool* pool {QThreadPool::globalInstance()};
    QThread::currentThread()->setObjectName("Main Event Thread");
    pool->setMaxThreadCount(pool->maxThreadCount());

    qInfo() << appDir.absolutePath();
//////////////////////////////////////////////////////////////
    // Can Bus
    //QString errorString;
    //QList <QCanBusDevice*> devices;
    //QCanBusDevice *can0 = QCanBus::instance()->createDevice(
    //    QStringLiteral("socketcan"), QStringLiteral("can0"), &errorString);

    FrameHandler *frameHandler = new FrameHandler(); // The CAN BUS pointer should be inside the FH runnable
    frameHandler->connectCan();


    //frameHandler->setAutoDelete(true);  //hmmmmmmmmmmmmmm might crash

    //QObject::connect(can0, &QCanBusDevice::framesReceived, frameHandler, &FrameHandler::onFramesReceived);
    //QObject::connect(can0, &QCanBusDevice::framesWritten, frameHandler, &FrameHandler::onFramesWritten);
    //QObject::connect(can0, &QCanBusDevice::errorOccurred, frameHandler, &FrameHandler::onErrorOccurred);
    //QObject::connect(can0, &QCanBusDevice::stateChanged, frameHandler, &FrameHandler::onStateChanged);

    //can0->setAutoDelete(true); // Why u crash on meeeeeeeee?
    //can0->setObjectName("Can Bus Device");

    //devices.append(can0);

    //can0->setConfigurationParameter(QCanBusDevice::ProtocolKey); // hmm?

///////////////////////////////////////////////////////////////////////////////////////////////
    // Connect signals and slots
    foreach(Sensor* sensor, sensors) // iterating through QMap, value is assigned instead of the key
    {
       QObject::connect(frameHandler, &FrameHandler::sensorReceived, sensor, &Sensor::onSensorReceived, Qt::QueuedConnection);
    }
    foreach(Valve* valve, valves) // iterating through QMap, value is assigned instead of the key
    {
       QObject::connect(frameHandler, &FrameHandler::valveReceived, valve, &Valve::onValveReceived, Qt::QueuedConnection);
    }

    QByteArray data = "0x111111";

    // Also look into signals and slots for lambda functions.

////////////////////////////////////////////////////////////////////////////////////////////////

    //QCanBusDevice::UnconnectedState;
    //QCanBusDevice::CanBusError::ConnectionError;
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("appDir", appDir.absolutePath());
    //engine.rootContext()->setContextProperty("monitorWidth", 99999999999)
    //engine.rootContext()->setContextProperty("monitorHeight", 9999999999)

    // also register actionable items in QML and use signals and slots to connect
    // signals emitted by those items to the
    // QQmlComponent component(&engine, QUrl("qrc:/BLT-GUI-Maker/MyItem.qml));

    // Create an instance of the component
    // QObject* qmlObject {component.create()};



    const QUrl url(u"qrc:/BLT-GUI-Maker/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    // Starting threads, where the application begins running:

    pool->start(frameHandler);
    return app.exec();
}
