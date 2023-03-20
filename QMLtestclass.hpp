#ifndef QMLTESTCLASS_HPP
#define QMLTESTCLASS_HPP

#include <QObject>

// class for testing communication between c++ and QML
class QMLtestclass : public QObject
{
    Q_OBJECT
public:
    explicit QMLtestclass(QObject *parent = nullptr);

signals:

};

#endif // QMLTESTCLASS_HPP
