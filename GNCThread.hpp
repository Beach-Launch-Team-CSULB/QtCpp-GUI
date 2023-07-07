#ifndef GNCTHREAD_HPP
#define GNCTHREAD_HPP

#include <QObject>
#include <QDebug>
#include <QRunnable>
#include <QThread>
#include <qqml.h>
#include "Node.hpp"

class GNCThread : public QObject, public QRunnable
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("C++ instantiation only")

    Node::NodeID _node {Node::NodeID::TELEMETRY};
public:

    explicit GNCThread(QObject *parent = nullptr);
    ~GNCThread();

signals:

public:
    void run() override;
};

#endif // GNCTHREAD_HPP
