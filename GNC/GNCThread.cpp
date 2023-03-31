#include "GNCThread.hpp"

GNCThread::GNCThread(QObject *parent)
    : QObject{parent}
{

}

void GNCThread::run()
{
    qInfo() << QThread::currentThread();
    qInfo() << "GNC SAID HELLO";
    qInfo() << "GNC SAID HELLO";
    qInfo() << "GNC SAID HELLO";
}
