#include <QApplication>
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

#include <windows.h>

// Class file includes
#include "FrameHandler.hpp"
#include "GNCThread.hpp"
#include "CommandState.hpp"
#include "DirHelper.hpp"
#define WIN1000 // How do I set flags

//make a function to create can bus objects instead????
// another function to connect?


int main(int argc, char *argv[])
{
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);
    qInfo() << "Hello";
    QQmlApplicationEngine engine;

/////////////////////////////////////////////////////////////////////////////////////////////////////
    QDir appDir {QGuiApplication::applicationDirPath()};
    QThreadPool* pool {QThreadPool::globalInstance()};
    QThread::currentThread()->setObjectName("Main Event Thread");
    pool->setMaxThreadCount(pool->maxThreadCount());

    qInfo() << appDir.absolutePath();
//////////////////////////////////////////////////////////////

    FrameHandler *frameHandler {new FrameHandler(&app)};
    GNCThread *GNC {new GNCThread(&app)};
    frameHandler->setAutoDelete(false);  //hmmmmmmmmmmmmmm might crash
    GNC->setAutoDelete(false);           // might crash
///////////////////////////////////////////////////////////////////////////////////////////////

    // Look into lambda functions for signals and slots.

////////////////////////////////////////////////////////////////////////////////////////////////


    engine.rootContext()->setContextProperty("appDir", appDir.absolutePath());
    //engine.rootContext()->setContextProperty("monitorWidth", GetSystemMetrics(SM_CXSCREEN));
    //engine.rootContext()->setContextProperty("monitorHeight", GetSystemMetrics(SM_CYSCREEN));
    qInfo() << GetSystemMetrics(SM_CXSCREEN);
    qInfo() << GetSystemMetrics(SM_CYSCREEN);
    // Expose objects to the QML engine

    engine.rootContext()->setContextProperty("frameHandler", frameHandler);
    engine.rootContext()->setContextProperty("GNC", GNC);
    engine.rootContext()->setContextProperty("logger", frameHandler->logger()); // may not need
    engine.rootContext()->setContextProperty("qmlEngine", &engine);


    //engine.rootContext()->setContextProperty("frameHandlerSensors", frameHandler->sensors());

    qRegisterMetaType<FrameHandler>();
    qRegisterMetaType<Sensor>();
    qRegisterMetaType<HPSensor>();
    qRegisterMetaType<Valve>();
    qRegisterMetaType<Autosequence>();
    qRegisterMetaType<TankPressController>();
    qRegisterMetaType<Node>();
    qRegisterMetaType<EngineController>();
    qRegisterMetaType<Logger>();

    // Also expose sensors and valves with setContextProperty too using the foreach loop

    qmlRegisterUncreatableType<FrameHandler>("FrameHandlerEnums", 1, 0, "FrameHandlerEnums", "C++ instantiation only");
    qmlRegisterUncreatableType<Sensor>("SensorEnums", 1, 0, "SensorEnums", "C++ instantiation only");
    qmlRegisterUncreatableType<HPSensor>("HPSensorEnums", 1, 0, "HPSensorEnums", "C++ instantiation only");
    qmlRegisterUncreatableType<Valve>("ValveEnums", 1, 0, "ValveEnums", "C++ instantiation only");
    qmlRegisterUncreatableType<Node>("NodeIDEnums", 1, 0, "NodeIDEnums", "C++ instantiation only");
    qmlRegisterUncreatableType<Autosequence>("AutosequenceEnums", 1, 0, "AutosequenceEnums", "C++ instantiation only");
    qmlRegisterUncreatableType<TankPressController>("TankPressControllerEnums", 1, 0, "TankPressControllerEnums", "C++ instantiation only");
    qmlRegisterUncreatableType<EngineController>("EngineControllerEnums", 1, 0, "EngineControllerEnums", "C++ instantiation only");
    qmlRegisterUncreatableType<Logger>("LoggerEnums", 1, 0, "LoggerEnums", "C++ instantiation only");

    // Register C++ objects to QML objects and vice versa. (expose c++ data to QML as a property)
    // also register actionable items in QML and use signals and slots to connect
    // signals emitted by those QML items to the C++ objects.

    // QQmlComponent component(&engine, QUrl("qrc:/BLT-GUI-Maker/MyItem.qml));

    // Create an instance of the component
    // QObject* qmlObject {component.create()};



    const QUrl url(u"file:///C:/CodeStuff/Beach Launch Team/BLT-Theseus-GUI/Main.qml"_qs);


    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    // How to load multiple windows
    engine.load(url);
    //engine.load(url);
    //engine.load(u"file:///C:/CodeStuff/Beach Launch Team/BLT-Theseus-GUI/GraphQML.qml"_qs);
    //engine.load(url); // for each call to load, another object is created. This is ok to do when the frontend ONLY grabs data from the backend
    //engine.load(url); // as a result, each page should ideally do something completely different for optimization

    // Starting threads, where the application begins running:
    pool->start(frameHandler);
    pool->start(GNC);


    // Important
    // Gracefully exits the theads (lol I don't know if this is the correctway)
    QObject::connect(&app, &QGuiApplication::aboutToQuit, frameHandler, &FrameHandler::setLoopToFalse);
    //QObject::connect(&app, &QGuiApplication::aboutToQuit, GNC, &GNC::setLoopToFalse);
    qInfo() << QThread::currentThread();

    qInfo() << " before return app.exec()";
    return app.exec();



}
