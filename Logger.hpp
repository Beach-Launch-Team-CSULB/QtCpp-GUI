#ifndef LOGGER_HPP
#define LOGGER_HPP


#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <qlogging.h>
#include <QFile>
#include <QDir>
#include <QTextStream>

class Logger : public QObject
{
public:
private:
    Q_OBJECT
    QString _messageBuffer {""};
    QTime _digitalClock = QTime::currentTime();
    QDateTime _digitalDateTime = QDateTime::currentDateTime();
    QTimer _digitalDateTimeTimer;
    Q_PROPERTY(QString messageBuffer READ messageBuffer NOTIFY messageBufferChanged)

    Q_PROPERTY(QDateTime digitalDateTime READ digitalDateTime NOTIFY digitalDateTimeChanged)

public:
    explicit Logger(QObject *parent = nullptr);


    QString messageBuffer() const;
    void setMessageBuffer(const QString &newMessageBuffer);

    QDateTime digitalDateTime() const;
    void setDigitalDateTime(const QDateTime &newDigitalDateTime);

signals:
    void messageBufferChanged();
    void digitalDateTimeChanged();
    void logMessageOutput(QString message); // connect via QML Connection

public slots:
    void outputLogMessage(const QString& message);
    void digitalDateTimeDisplay();

    void loadUpMessageBuffer(const QString& message); //HMMMMMMMM
    void clearMessageBuffer();
};

Q_DECLARE_METATYPE(Logger);

#endif // LOGGER_HPP
