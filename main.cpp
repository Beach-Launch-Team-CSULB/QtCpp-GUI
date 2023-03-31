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
#include "GNC/GNCThread.hpp"

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
    engine.rootContext()->setContextProperty("headquarter", frameHandler);

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
    pool->start(GNC);
    qInfo() << QThread::currentThread();
    return app.exec();
}
