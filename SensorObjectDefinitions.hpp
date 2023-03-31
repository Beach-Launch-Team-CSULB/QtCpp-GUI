#ifndef SENSOROBJECTDEFINITIONS_HPP
#define SENSOROBJECTDEFINITIONS_HPP

#include <QList>
#include <QVariant>
#include <QMap>
#include "Sensor.hpp"
// {Sensor Name, Raw Sensor ID, Converted Sensor ID, sensor state}
QList<QList<QVariant>> sensorConstructingParameters { // make const QList< const QList< const QVariant>> results in error?
            {"High_Press_1", 70, 81},
            {"High_Press_2", 72, 81},
            {"Fuel_Tank_1", 62, 81},
            {"Fuel_Tank_2", 64, 81},
            {"Lox_Tank_1", 66, 81},
            {"Lox_Tank_2", 68, 81},
            {"Fuel_Dome_Reg", 74, 81},
            {"Lox_Dome_Reg", 76, 81},
            {"Fuel_Prop_Inlet", 58, 81},
            {"Lox_Prop_Inlet", 60, 81},
            {"Fuel_Injector", 54, 81},
            {"LC1", 37, 37},
            {"LC2", 43, 43},
            {"LC3", 49, 49},
            {"Chamber_1", 50, 51},
            {"Chamber_2", 52, 81},
            {"MV_Pneumatic", 56, 81}
    // Underscores instead of spaces to be able to register these objects with the QML engine
};

#endif // SENSOROBJECTDEFINITIONS_HPP
