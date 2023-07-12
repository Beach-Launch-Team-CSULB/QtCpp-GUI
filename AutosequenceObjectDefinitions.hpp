#ifndef AUTOSEQUENCEOBJECTDEFINITIONS_HPP
#define AUTOSEQUENCEOBJECTDEFINITIONS_HPP

#include <QList>
#include <QVariant>
#include <QMap>
#include "Node.hpp"

QList<QList<QVariant>> autosequenceConstructingParameters {
    {"Autosequence1", 1, QVariant::fromValue(Node::NodeID::ENGINE_NODE)}
};

#endif // AUTOSEQUENCEOBJECTDEFINITIONS_HPP
