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
#include "GNCThread.hpp"
#include "CommandState.hpp"

#define WIN1000 // How do I set flags

#ifdef WIN1000
    #include <windows.h>
#elif
    #include <X11/Xlib.h> // on raspberry pi
#endif

//make a function to create can bus objects instead????
// another function to connect?

int main(int argc, char *argv[])
{

    quint16 DANGERZONE {300};
    quint16 NODEID {8};
    quint16 VERIFICATIONID {166};


    // TODO: FINISH THE REMAINING COMMANDS.

    QGuiApplication app(argc, argv);
    // Setup
/////////////////////////////////////////////////////////////////////////////////////////////////////
    QDir appDir {QGuiApplication::applicationDirPath()};
    QThreadPool* pool {QThreadPool::globalInstance()};
    QThread::currentThread()->setObjectName("Main Event Thread");
    pool->setMaxThreadCount(pool->maxThreadCount());

    qInfo() << appDir.absolutePath();
//////////////////////////////////////////////////////////////

    FrameHandler *frameHandler {new FrameHandler(&app)};
    GNCThread *GNC {new GNCThread(&app)};
    frameHandler->setAutoDelete(true);  //hmmmmmmmmmmmmmm might crash
    GNC->setAutoDelete(true);           // might crash
///////////////////////////////////////////////////////////////////////////////////////////////

    // Look into lambda functions for signals and slots.

////////////////////////////////////////////////////////////////////////////////////////////////
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("appDir", appDir.absolutePath());
    //engine.rootContext()->setContextProperty("monitorWidth", 99999999999)
    //engine.rootContext()->setContextProperty("monitorHeight", 9999999999)

    // Expose objects to the QML engine
    engine.rootContext()->setContextProperty("DANGERZONE", DANGERZONE);
    engine.rootContext()->setContextProperty("NODEID", NODEID);
    engine.rootContext()->setContextProperty("VERIFICATIONID", VERIFICATIONID);

    engine.rootContext()->setContextProperty("frameHandler", frameHandler);
    engine.rootContext()->setContextProperty("GNC", GNC);

    //engine.rootContext()->setContextProperty("frameHandlerSensors", frameHandler->sensors());
    //qInfo() << frameHandler->sensors().value("High_Press_1"); qInfo() << " HHHHHHHHHHHHHHHHHH";

    qRegisterMetaType<FrameHandler>();
    qRegisterMetaType<Sensor>();
    qRegisterMetaType<HPSensor>();
    qRegisterMetaType<Valve>();
    qRegisterMetaType<Autosequence>();
    qRegisterMetaType<TankPressController>();

    // Also expose sensors and valves with setContextProperty too using the foreach loop

    qmlRegisterUncreatableType<FrameHandler>("FrameHandlerEnums", 1, 0, "FrameHandlerEnums", "C++ instantiation only");
    qmlRegisterUncreatableType<Sensor>("SensorEnums", 1, 0, "SensorEnums", "C++ instantiation only");
    qmlRegisterUncreatableType<HPSensor>("HPSensorEnums", 1, 0, "HPSensorEnums", "C++ instantiation only");
    qmlRegisterUncreatableType<Valve>("ValveEnums", 1, 0, "ValveEnums", "C++ instantiation only");
    qmlRegisterUncreatableType<Node>("NodeIDEnums", 1, 0, "NodeIDEnums", "C++ instantiation only");
    qmlRegisterUncreatableType<Autosequence>("AutosequenceEnums", 1, 0, "AutosequenceEnums", "C++ instantiation only");
    qmlRegisterUncreatableType<TankPressController>("TankPressControllerEnums", 1, 0, "TankPressControllerEnums", "C++ instantiation only");

    // Register C++ objects to QML objects and vice versa. (expose c++ data to QML as a property)
    // also register actionable items in QML and use signals and slots to connect
    // signals emitted by those QML items to the C++ objects.

    // QQmlComponent component(&engine, QUrl("qrc:/BLT-GUI-Maker/MyItem.qml));

    // Create an instance of the component
    // QObject* qmlObject {component.create()};

    //const QUrl url(u"qrc:/BLT-GUI-Maker/main.qml"_qs);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const QUrl url(u"file:///C:/CodeStuff/Beach Launch Team/BLT-GUI-Maker/main.qml"_qs);
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
    pool->start(GNC);
    qInfo() << QThread::currentThread();
    return app.exec();
}
