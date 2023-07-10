#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <qqml.h>
struct Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 nodeControllerID READ nodeControllerID CONSTANT)

    Q_PROPERTY(quint16 autosequenceID READ autosequenceID CONSTANT)
    Q_PROPERTY(float autosequenceTime READ autosequenceTime NOTIFY autosequenceTimeChanged)

    Q_PROPERTY(quint16 hiPressID READ hiPressID CONSTANT)

    Q_PROPERTY(quint16 LOXID READ LOXID CONSTANT)

    Q_PROPERTY(quint16 fuelID READ fuelID CONSTANT)

    Q_PROPERTY(quint16 engineControllerID READ engineControllerID CONSTANT)
    Q_PROPERTY(float fuelMVTime READ fuelMVTime NOTIFY fuelMVTimeChanged)
    Q_PROPERTY(float LOXMVTime READ LOXMVTime NOTIFY LOXMVTimeChanged)
    Q_PROPERTY(float IGN1Time READ IGN1Time NOTIFY IGN1TimeChanged)
    Q_PROPERTY(float IGN2Time READ IGN2Time NOTIFY IGN2TimeChanged)

    QML_ELEMENT
    QML_UNCREATABLE("C++ instantiation only")
public:
    quint16 _nodeControllerID {0};

    quint16 _autosequenceID {1};
    float _autosequenceTime {0.0f};

    quint16 _hiPressID {2};

    quint16 _LOXID {3};

    quint16 _fuelID {4};

    quint16 _engineControllerID {5};
    float _fuelMVTime {0.0f};
    float _LOXMVTime {0.0f};
    float _IGN1Time {0.0f};
    float _IGN2Time {0.0f};





    // tank controller hiPress, Lox, Fuel commented out in the python gui

    explicit Controller(QObject *parent = nullptr);

    quint16 nodeControllerID();

    quint16 autosequenceID();
    float autosequenceTime() const;
    void setAutosequenceTime(float newAutosequenceTime);

    quint16 hiPressID();

    quint16 LOXID();

    quint16 fuelID();

    quint16 engineControllerID();
    float fuelMVTime();
    void setFuelMVTime(float newFuelMVTime);
    float LOXMVTime();
    void setLOXMVTime(float newLOXMVTime);
    float IGN1Time();
    void setIGN1Time(float newIGN1Time);
    float IGN2Time();
    void setIGN2Time(float newIGN2Time);


signals:
    void fuelMVTimeChanged();
    void LOXMVTimeChanged();
    void IGN1TimeChanged();
    void IGN2TimeChanged();
    void autosequenceTimeChanged();
public slots:
};

Q_DECLARE_METATYPE(Controller)
#endif // CONTROLLER_HPP
