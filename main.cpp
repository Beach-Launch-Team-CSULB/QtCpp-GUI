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

#include <Windows.h>

//make a function to create can bus objects instead????
// another function to connect?

int main(int argc, char *argv[])
{

    quint16 DANGERZONE {300};
    quint16 NODEID {8};
    quint16 VERIFICATIONID {166};
    CommandState TEST                   {"TEST",1,3,5,false};
    CommandState ABORT                  {"ABORT",1,3,7,false};
    CommandState VENT                   {"VENT",1,3,9,false};
    CommandState OFF_NOMINAL            {"OFF_NOMINAL",1,22,23,false};
    CommandState HI_PRESS_ARM           {"HI_PRESS_ARM", 1,10,11,true};
    CommandState HI_PRESS_PRESSURIZED   {"HI_PRESS_PRESSURIZED",1,12,13,false};
    CommandState TANK_PRESS_ARM         {"TANK_PRESS_ARM",1,14,15,true};
    CommandState TANK_PRESS_PRESSURIZED {"TANK_PRESS_PRESSURIZED",1,16,17,false};
    CommandState FIRE_ARMED             {"FIRE_ARMED",1,18,19,true};
    CommandState FIRE                   {"FIRE",1,20,21,false};
    QList<CommandState*> commandList {&TEST,&ABORT,&VENT,&OFF_NOMINAL,&HI_PRESS_ARM,
                                     &HI_PRESS_PRESSURIZED, &TANK_PRESS_ARM,
                                     &TANK_PRESS_PRESSURIZED, &FIRE_ARMED,&FIRE}; // for the sole purpose of setcontextproperty


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

    foreach(CommandState* command, commandList) //expose every single command to QML
    {
        engine.rootContext()->setContextProperty(command->stateName(), command);
    }

    engine.rootContext()->setContextProperty("frameHandler", frameHandler);
    engine.rootContext()->setContextProperty("GNC", GNC);

    qmlRegisterUncreatableType<FrameHandler>("FrameHandlerEnums", 1,0, "FrameHandler", "C++ instantantiation only");

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
