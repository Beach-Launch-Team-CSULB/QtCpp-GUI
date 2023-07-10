#ifndef THERMOCOUPLE_HPP
#define THERMOCOUPLE_HPP


#include <QObject>


class Thermocouple : public QObject
{
    Q_OBJECT
public:
    explicit Thermocouple(QObject *parent = nullptr);

signals:

};

#endif // THERMOCOUPLE_HPP
