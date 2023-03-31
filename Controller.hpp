#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <qqml.h>
struct Controller : public QObject
{
public:
    Q_OBJECT
    Q_PROPERTY(float fuelMVTime READ fuelMVTime NOTIFY fuelMVTimeChanged)
    Q_PROPERTY(float LOXMVTime READ LOXMVTime NOTIFY LOXMVTimeChanged)
    Q_PROPERTY(float IGN1Time READ IGN1Time NOTIFY IGN1TimeChanged)
    Q_PROPERTY(float IGN2Time READ IGN2Time NOTIFY IGN2TimeChanged)
    Q_PROPERTY(float autosequenceTime READ autosequenceTime NOTIFY autosequenceTimeChanged)
    QML_ELEMENT
public:
    float _fuelMVTime {0.0f};
    float _LOXMVTime {0.0f};
    float _IGN1Time {0.0f};
    float _IGN2Time {0.0f};
    float _autosequenceTime {0.0f};
    quint16 engineControllerID = 5;

    // tank controller hiPress, Lox, Fuel commented out in the python gui

    explicit Controller(QObject *parent = nullptr);

    float fuelMVTime();
    void setFuelMVTime(float newFuelMVTime);
    float LOXMVTime();
    void setLOXMVTime(float newLOXMVTime);
    float IGN1Time();
    void setIGN1Time(float newIGN1Time);
    float IGN2Time();
    void setIGN2Time(float newIGN2Time);

    float autosequenceTime() const;
    void setAutosequenceTime(float newAutosequenceTime);
signals:
    void fuelMVTimeChanged();
    void LOXMVTimeChanged();
    void IGN1TimeChanged();
    void IGN2TimeChanged();
    void autosequenceTimeChanged();
public slots:
};

#endif // CONTROLLER_HPP
