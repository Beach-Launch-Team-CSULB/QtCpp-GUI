#ifndef ENGINECONTROLLER_HPP
#define ENGINECONTROLLER_HPP

#include <QObject>

class EngineController : public QObject
{
    Q_OBJECT
public:
    explicit EngineController(QObject *parent = nullptr);

signals:

};

#endif // ENGINECONTROLLER_HPP
