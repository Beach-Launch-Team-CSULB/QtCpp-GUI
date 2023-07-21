
#ifndef LOADCELLSENSOR_HPP
#define LOADCELLSENSOR_HPP


#include <QObject>


class LoadCellSensor : public QObject
{
    Q_OBJECT
public:
    explicit LoadCellSensor(QObject *parent = nullptr);

signals:

};

#endif // LOADCELLSENSOR_HPP
