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
        bool loop {true};
    explicit GNCThread(QObject *parent = nullptr);
    ~GNCThread();

signals:

public slots:
    void print();
public:

    void run() override;
};

Q_DECLARE_METATYPE(GNCThread)

#endif // GNCTHREAD_HPP
