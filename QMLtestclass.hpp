#ifndef QMLTESTCLASS_HPP
#define QMLTESTCLASS_HPP

#include <QObject>
#include <qqml.h>

// class for testing communication between c++ and QML
class QMLtestclass : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("C++ instantiation only")
public:
    explicit QMLtestclass(QObject *parent = nullptr);

signals:

};

#endif // QMLTESTCLASS_HPP
