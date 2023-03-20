#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
//#include <QtQML>
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

    QGuiApplication app(argc, argv);
    // Setup
///////////////////////////////////////////////////////////////////////////////////////////////////
    QMap<QString,Sensor*> sensors;
    foreach(auto& sensorContructingParameter, sensorConstructingParameters) //sensor key List
    {                                                                       //{"High_Press 1"} {"High_Press 2"} {"Fuel_Tank 1"} {"Fuel_Tank 2"}
        sensors.insert(sensorContructingParameter.at(0).toString(),         //{"Lox_Tank 1"} {"Lox_Tank 2"} {"Fuel_Dome_Reg"} {"Lox_Dome_Reg"}
                       new Sensor{&app, sensorContructingParameter});    //{"Fuel_Prop_Inlet"} {"Lox_Prop_Inlet"} {"Fuel Injector"}
    }                                                                       //{"LC1"} {"LC2"} {"LC3"} {"Chamber_1"} {"Chamber_2"} {"MV_Pneumatic}
    //sensors.value("High Press 1"); // kinda scuffed?

    QMap<QString,Valve*> valves;
    foreach(auto& valveConstructingParameter, valveConstructingParameters)  // valve key list
    {                                                                       //{"HV"} {"HP"} {"LDR"} {"FDR"} {"LDV"}
        valves.insert(valveConstructingParameter.at(0).toString(),          // {"FDV"} {"LV"} {"FV"}
                       new Valve{&app, valveConstructingParameter});      //{"LMV"} {"FMV"} {"IGN1"} {"IGN2"}
    }

    //valves.value("IGN1")->;
/////////////////////////////////////////////////////////////////////////////////////////////////////
    QDir appDir {QGuiApplication::applicationDirPath()};
    QThreadPool* pool {QThreadPool::globalInstance()};
    QThread::currentThread()->setObjectName("Main Event Thread");
    pool->setMaxThreadCount(pool->maxThreadCount());

    qInfo() << appDir.absolutePath();
//////////////////////////////////////////////////////////////

    FrameHandler *frameHandler = new FrameHandler(&app);
    //frameHandler->connectCan(); //Make a button for this
    //frameHandler->disconnectCan(); // make a button for this


    frameHandler->setAutoDelete(true);  //hmmmmmmmmmmmmmm might crash

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

    // Expose objects to the QML engine
    foreach(auto sensor, sensors)
    {
        engine.rootContext()->setContextProperty(sensor->name(), sensor);
    }
    foreach(auto valve, valves)
    {
        engine.rootContext()->setContextProperty(valve->name(), valve);
    }


    // Register C++ objects to QML objects and vice versa. (expose c++ data to QML as a property)
    // also register actionable items in QML and use signals and slots to connect
    // signals emitted by those QML items to the C++ objects.

    // QQmlComponent component(&engine, QUrl("qrc:/BLT-GUI-Maker/MyItem.qml));

    // Create an instance of the component
    // QObject* qmlObject {component.create()};



    const QUrl url(u"qrc:/BLT-GUI-Maker/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    // How to load multiple windows
    engine.load(url);
    engine.load(url);

    // Starting threads, where the application begins running:

    pool->start(frameHandler);
    return app.exec();
}
