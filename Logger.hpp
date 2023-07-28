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
    QString _message {""};
    QTime _digitalClock = QTime::currentTime();
    QDateTime _digitalDateTime = QDateTime::currentDateTime();
    QTimer _digitalDateTimeTimer;
    Q_PROPERTY(QString message READ message NOTIFY messageChanged)

    Q_PROPERTY(QDateTime digitalDateTime READ digitalDateTime NOTIFY digitalDateTimeChanged)

public:
    explicit Logger(QObject *parent = nullptr);

    QString message() const;
    void setMessage(const QString &newMessage);

    QDateTime digitalDateTime() const;
    void setDigitalDateTime(const QDateTime &newDigitalDateTime);

signals:
    void messageChanged();
    void digitalDateTimeChanged();
    void logMessageOutput(QString message);

public slots:
    void outputLogMessage(const QString& message);
    void digitalDateTimeDisplay();
};

Q_DECLARE_METATYPE(Logger);

#endif // LOGGER_HPP
