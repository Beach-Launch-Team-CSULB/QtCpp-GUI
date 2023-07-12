#ifndef HPSENSOROBJECTDEFINITIONS_HPP
#define HPSENSOROBJECTDEFINITIONS_HPP

#include <QList>
#include <QVariant>
#include <QMap>
#include "HPSensor.hpp"
#include "Node.hpp"
QList<QList<QVariant>> HPSensorConstructingParameters {
    {"RenegadeEngineHP1", 121, QVariant::fromValue(Node::NodeID::ENGINE_NODE)},
    {"RenegadeEngineHP2", 122, QVariant::fromValue(Node::NodeID::ENGINE_NODE)},
    {"RenegadeEngineHP3", 123, QVariant::fromValue(Node::NodeID::ENGINE_NODE)},
    {"RenegadeEngineHP4", 124, QVariant::fromValue(Node::NodeID::ENGINE_NODE)},
    {"RenegadeEngineHP5", 125, QVariant::fromValue(Node::NodeID::ENGINE_NODE)},
    {"RenegadeEngineHP6", 126, QVariant::fromValue(Node::NodeID::ENGINE_NODE)},
    {"RenegadeEngineHP7", 127, QVariant::fromValue(Node::NodeID::ENGINE_NODE)},
    {"RenegadeEngineHP8", 128, QVariant::fromValue(Node::NodeID::ENGINE_NODE)},
    {"RenegadeEngineHP9", 129, QVariant::fromValue(Node::NodeID::ENGINE_NODE)},
    {"RenegadeEngineHP10", 130, QVariant::fromValue(Node::NodeID::ENGINE_NODE)},
    {"RenegadePropHP1", 131, QVariant::fromValue(Node::NodeID::PROP_NODE)},
    {"RenegadePropHP2", 132, QVariant::fromValue(Node::NodeID::PROP_NODE)},
    {"RenegadePropHP3", 133, QVariant::fromValue(Node::NodeID::PROP_NODE)},
    {"RenegadePropHP4", 134, QVariant::fromValue(Node::NodeID::PROP_NODE)},
    {"RenegadePropHP5", 135, QVariant::fromValue(Node::NodeID::PROP_NODE)},
    {"RenegadePropHP6", 136, QVariant::fromValue(Node::NodeID::PROP_NODE)},
    {"RenegadePropHP7", 137, QVariant::fromValue(Node::NodeID::PROP_NODE)},
    {"RenegadePropHP8", 138, QVariant::fromValue(Node::NodeID::PROP_NODE)},
    {"RenegadePropHP9", 139, QVariant::fromValue(Node::NodeID::PROP_NODE)},
    {"RenegadePropHP10", 140, QVariant::fromValue(Node::NodeID::PROP_NODE)}
};
#endif // HPSENSOROBJECTDEFINITIONS_HPP
