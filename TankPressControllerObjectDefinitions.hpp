#ifndef TANKPRESSCONTROLLEROBJECTDEFINITIONS_HPP
#define TANKPRESSCONTROLLEROBJECTDEFINITIONS_HPP

#include <QList>
#include <QVariant>
#include <QMap>
#include "Node.hpp"

QList<QList<QVariant>> tankPressControllerConstructingParameters {
    {"HiPressTankController", 2, QVariant::fromValue(Node::NodeID::ENGINE_NODE), 6000},
    {"LoxTankController", 3, QVariant::fromValue(Node::NodeID::PROP_NODE), 0},
    {"FuelTankController", 4, QVariant::fromValue(Node::NodeID::PROP_NODE), 0}
};

#endif // TANKPRESSCONTROLLEROBJECTDEFINITIONS_HPP
