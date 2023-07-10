#ifndef HPSENSOR_HPP
#define HPSENSOR_HPP


#include <QObject>


class HPSensor : public QObject
{
    Q_OBJECT
public:
    explicit HPSensor(QObject *parent = nullptr);

signals:

};

#endif // HPSENSOR_HPP
