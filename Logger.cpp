#include "Logger.hpp"

Logger::Logger(QObject *parent)
    : QObject{parent}
{
    QObject::connect(&_digitalDateTimeTimer, &QTimer::timeout, this, &Logger::digitalDateTimeDisplay);
    _digitalDateTimeTimer.setInterval(1000);
    _digitalDateTimeTimer.start();
}

QString Logger::messageBuffer() const
{
    return _messageBuffer; // Should modify this such that it newlines in the log window in QML
}

void Logger::setMessageBuffer(const QString &newMessageBuffer)
{
    _messageBuffer = newMessageBuffer;
    emit messageBufferChanged();
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

void Logger::loadUpMessageBuffer(const QString& message)
{
    _messageBuffer = _messageBuffer + message + '\n';
}

void Logger::clearMessageBuffer()
{
    _messageBuffer = "";
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
