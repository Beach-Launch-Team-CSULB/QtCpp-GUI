#ifndef VALVEOBJECTDEFINITIONS_HPP
#define VALVEOBJECTDEFINITIONS_HPP

// Data needed to set up the Valve, Sensors, States
#include <QList>
#include <QVariant>
#include "Valve.hpp"
//{Valve name, Object ID, HP channel, state, Command OFF, command On, "something to do with text styling", "marker for refresh valve function?"}
QList<QList<QVariant>> valveConstructingParameters {
    {"HP", 16, 2, 34, 35, 122, QVariant::fromValue(Node::NodeID::ENGINE_NODE)},
    {"HPV", 17, 1, 32, 33, 121, QVariant::fromValue(Node::NodeID::ENGINE_NODE)},
    {"LDR", 19, 3, 38, 39, 133, QVariant::fromValue(Node::NodeID::PROP_NODE)},
    {"FDR", 22, 7, 44, 45, 137, QVariant::fromValue(Node::NodeID::PROP_NODE)},
    {"LDV", 20, 4, 40, 41, 134, QVariant::fromValue(Node::NodeID::PROP_NODE)},
    {"FDV", 23, 8, 46, 47, 138, QVariant::fromValue(Node::NodeID::PROP_NODE)},
    {"LV", 18, 1, 36, 37, 131, QVariant::fromValue(Node::NodeID::PROP_NODE)},
    {"FV", 21, 5, 42, 43, 135, QVariant::fromValue(Node::NodeID::PROP_NODE)},
    {"LMV", 24, 4, 48, 49, 124, QVariant::fromValue(Node::NodeID::ENGINE_NODE)},
    {"FMV", 25, 3, 50, 51, 123, QVariant::fromValue(Node::NodeID::ENGINE_NODE)},
    {"IGN1", 26, 5, 52, 53, 125, QVariant::fromValue(Node::NodeID::ENGINE_NODE)},
    {"IGN2", 27, 7, 54, 55, 127, QVariant::fromValue(Node::NodeID::ENGINE_NODE)}
};
#endif // VALVEOBJECTDEFINITIONS_HPP
