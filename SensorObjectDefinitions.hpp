#ifndef SENSOROBJECTDEFINITIONS_HPP
#define SENSOROBJECTDEFINITIONS_HPP
#include <QList>
#include <QVariant>
#include <QMap>
#include "Sensor.hpp"
// {Sensor Name, Raw Sensor ID, Converted Sensor ID, sensor state}
QList<QList<QVariant>> sensorConstructingParameters { // make const QList< const QList< const QVariant>> results in error?
            {"High_Press_1", 70, 3, 81},
            {"High_Press_2", 72, 3, 81},
            {"Fuel_Tank_1", 62, 3, 81},
            {"Fuel_Tank_2", 64, 3, 81},
            {"Lox_Tank_1", 66, 3, 81},
            {"Lox_Tank_2", 68, 3, 81},
            {"Fuel_Dome_Reg", 74, 3, 81},
            {"Lox_Dome_Reg", 76, 3, 81},
            {"Fuel_Prop_Inlet", 58, 2, 81},
            {"Lox_Prop_Inlet", 60, 2, 81},
            {"Fuel_Injector", 54, 2, 81},
            //{"LC1", 37, 37},
            //{"LC2", 43, 43},
            //{"LC3", 49, 49},
            {"Chamber_1", 50, 2, 51},
            {"Chamber_2", 52, 2, 81},
            {"MV_Pneumatic", 56, 2, 81}
    // Underscores instead of spaces to be able to register these objects with the QML engine
};

#endif // SENSOROBJECTDEFINITIONS_HPP
