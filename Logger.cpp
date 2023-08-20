#include "Logger.hpp"

Logger::Logger(QObject *parent)
    : QObject{parent}
{
    QObject::connect(&_digitalDateTimeTimer, &QTimer::timeout, this, &Logger::digitalDateTimeDisplay);
    _digitalDateTimeTimer.setInterval(1000);
    _digitalDateTimeTimer.start();
}

QString Logger::message() const
{
    return _message; // Should modify this such that it newlines in the log window in QML
}

void Logger::setMessage(const QString &newMessage)
{
    _message = newMessage;
    emit messageChanged();
}


void Logger::outputLogMessage(const QString& message)
{
    QString constructedMessage = QTime::currentTime().toString().leftJustified(9, ' ') + "| " + message;
    emit logMessageOutput(constructedMessage);

    // in QML, when the signal is emitted, do textAppend
}


void Logger::digitalDateTimeDisplay()
{
    setDigitalDateTime(QDateTime::currentDateTime());
}

QDateTime Logger::digitalDateTime() const
{
    return _digitalDateTime;
}

void Logger::setDigitalDateTime(const QDateTime &newDigitalDateTime)
{
    _digitalDateTime = newDigitalDateTime;
    emit digitalDateTimeChanged();
}
