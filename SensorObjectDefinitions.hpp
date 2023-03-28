#ifndef SENSOROBJECTDEFINITIONS_HPP
#define SENSOROBJECTDEFINITIONS_HPP

#include <QList>
#include <QVariant>
#include <QMap>
#include "Sensor.hpp"
// {Sensor Name, Raw Sensor ID, Converted Sensor ID, sensor state}
QList<QList<QVariant>> sensorConstructingParameters { // make const QList< const QList< const QVariant>> results in error?
            {"High_Press_1", 70, 81, sensorState::off},
            {"High_Press_2", 72, 81, sensorState::off},
            {"Fuel_Tank_1", 62, 81, sensorState::off},
            {"Fuel_Tank_2", 64, 81, sensorState::off},
            {"Lox_Tank_1", 66, 81, sensorState::off},
            {"Lox_Tank_2", 68, 81, sensorState::off},
            {"Fuel_Dome_Reg", 74, 81, sensorState::off},
            {"Lox_Dome_Reg", 76, 81, sensorState::off},
            {"Fuel_Prop_Inlet", 58, 81, sensorState::off},
            {"Lox_Prop_Inlet", 60, 81, sensorState::off},
            {"Fuel_Injector", 54, 81, sensorState::off},
            {"LC1", 37, 37, sensorState::off},
            {"LC2", 43, 43, sensorState::off},
            {"LC3", 49, 49, sensorState::off},
            {"Chamber_1", 50, 51, sensorState::off},
            {"Chamber_2", 52, 81, sensorState::off},
            {"MV_Pneumatic", 56, 81, sensorState::off}
    // Underscores instead of spaces to be able to register these objects with the QML engine
};

// blow me
//Sensor* highPress1 = new Sensor{nullptr, sensorConstructingParameters.at(1)};
//Sensor* highPress2 = new Sensor{nullptr, sensorConstructingParameters.at(2)};
//Sensor* fuelTank1 = new Sensor{nullptr, sensorConstructingParameters.at(3)};
//Sensor* fuelTank2 = new Sensor{nullptr, sensorConstructingParameters.at(4)};
//Sensor* loxTank1 = new Sensor{nullptr, sensorConstructingParameters.at(5)};
//Sensor* loxTank2 = new Sensor{nullptr, sensorConstructingParameters.at(6)};
//Sensor* fuelDomeReg = new Sensor{nullptr, sensorConstructingParameters.at(7)};
//Sensor* loxDomeReg = new Sensor{nullptr, sensorConstructingParameters.at(8)};
//Sensor* fuelPropInlet = new Sensor{nullptr, sensorConstructingParameters.at(9)};
//Sensor* loxPropInlet = new Sensor{nullptr, sensorConstructingParameters.at(10)};
//Sensor* fuelInjector = new Sensor{nullptr, sensorConstructingParameters.at(11)};
//Sensor* LC1 = new Sensor{nullptr, sensorConstructingParameters.at(12)};
//Sensor* LC2 = new Sensor{nullptr, sensorConstructingParameters.at(13)};
//Sensor* LC3 = new Sensor{nullptr, sensorConstructingParameters.at(14)};
//Sensor* chamber1 = new Sensor{nullptr, sensorConstructingParameters.at(15)};
//Sensor* chamber2 = new Sensor{nullptr, sensorConstructingParameters.at(16)};
//Sensor* MVPneumatic = new Sensor{nullptr, sensorConstructingParameters.at(17)};
// or don't actually
//QList<Sensor*> sensors {highPress1, highPress2, fuelTank1, fuelTank2,
//                       loxTank1, loxTank2, fuelDomeReg, loxDomeReg,
//                       fuelPropInlet, loxPropInlet, fuelInjector,
//                       LC1,LC2,LC3, chamber1, chamber2, MVPneumatic};
// lmao
#endif // SENSOROBJECTDEFINITIONS_HPP
