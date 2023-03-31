#ifndef QMLTESTCLASS_HPP
#define QMLTESTCLASS_HPP

#include <QObject>
#include <qqml.h>

// class for testing communication between c++ and QML
class QMLtestclass : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit QMLtestclass(QObject *parent = nullptr);

signals:

};

#endif // QMLTESTCLASS_HPP
