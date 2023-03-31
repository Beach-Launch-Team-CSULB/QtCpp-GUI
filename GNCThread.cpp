#include "GNCThread.hpp"

GNCThread::GNCThread(QObject *parent)
    : QObject{parent}
{

}

quint16 RoundTo100 (quint16 number)
{
    return ((number+49)/100)*100;
}

void GNCThread::run()
{
    qInfo() << QThread::currentThread();
    qInfo() << "GNC SAID HELLO";
    qInfo() << "GNC SAID HELLO";
    qInfo() << "GNC SAID HELLO";
    qInfo() << "Rounded: " << (RoundTo100(1502)-1000)/100;
    qInfo() << "Modulus:"  << 1504 % 100;
}
