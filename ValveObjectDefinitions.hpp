#ifndef VALVEOBJECTDEFINITIONS_HPP
#define VALVEOBJECTDEFINITIONS_HPP

// Data needed to set up the Valve, Sensors, States
#include <QList>
#include <QVariant>
#include "Valve.hpp"
//{Valve name, Object ID, HP channel, Normal state, Command OFF, command On, "something to do with text styling", "marker for refresh valve function?"}
QList<QList<QVariant>> valveConstructingParameters {
                {"HV", 16, 2, valveState::normallyOff, 34, 35, 122, 2},
                {"HP", 17, 1, valveState::normallyOff, 32, 33, 121, 2},
                {"LDR", 19, 3, valveState::normallyOff, 38, 39, 133, 3},
                {"FDR", 22, 7, valveState::normallyOff, 44, 45, 137, 3},
                {"LDV", 20, 4, valveState::normallyOff, 40, 41, 134, 3},
                {"FDV", 23, 8, valveState::normallyOff, 46, 47, 138, 3},
                {"LV", 18, 1, valveState::normallyOn, 36, 37, 131, 3},
                {"FV", 21, 5, valveState::normallyOff, 42, 43, 135, 3},
                {"LMV", 24, 4, valveState::normallyOff, 48, 49, 124, 2},
                {"FMV", 25, 3, valveState::normallyOff, 50, 51, 123, 2},
                {"IGN1", 26, 5, valveState::normallyOff, 52, 53, 125, 2},
                {"IGN2", 27, 7, valveState::normallyOff, 54, 55, 127, 2}
    };

#endif // VALVEOBJECTDEFINITIONS_HPP
