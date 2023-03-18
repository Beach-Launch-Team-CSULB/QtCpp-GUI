#ifndef FRAMEHANDLER_HPP
#define FRAMEHANDLER_HPP

#include <QObject>

class FrameHandler : public QObject
{
    Q_OBJECT
public:
    explicit FrameHandler(QObject *parent = nullptr);

signals:

};

#endif // FRAMEHANDLER_HPP
