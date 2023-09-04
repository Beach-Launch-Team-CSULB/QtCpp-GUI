import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import FrameHandlerEnums
import SensorEnums
import HPSensorEnums
import ValveEnums
import NodeIDEnums
import AutosequenceEnums
import TankPressControllerEnums
import EngineControllerEnums

Item {
    id: tankStateQML
    width: 20
    height: 20

    property int fontSize: 15

    property alias tankStateTextForMain : tankStateText

    Text {
        id: tankStateText
        text: "Tank State : N/A"
        anchors.left: parent.left
        anchors.top: parent.top
        font.pixelSize: fontSize
        color: "orange"
    }

    states: [
        State {
            name: "0" //
            PropertyChanges {
                target: tankStateText
                text: "Tank State : PASSIVE"
            }
        },
        State {
            name: "1" //
            PropertyChanges {
                target: tankStateText
                text: "Tank State : STANDBY"
            }
        },
        State {
            name: "2" //
            PropertyChanges {
                target: tankStateText
                text: "Tank State : BANG BANG ACTIVE"
            }
        },
        State {
            name: "3" //
            PropertyChanges {
                target: tankStateText
                text: "Tank State : REG PRESS ACTIVE"
            }
        },
        State {
            name: "4" //
            PropertyChanges {
                target: tankStateText
                text: "Tank State : HI PRESS VENT"
            }
        },
        State {
            name: "5" //
            PropertyChanges {
                target: tankStateText
                text: "Tank State : ARMED"
            }
        },
        State {
            name: "6" //
            PropertyChanges {
                target: tankStateText
                text: "Tank State : PROP TANK VENT"
            }
        },
        State {
            name: "7" //
            PropertyChanges {
                target: tankStateText
                text: "Tank State : HI VENT"
            }
        },
        State {
            name: "8" //
            PropertyChanges {
                target: tankStateText
                text: "Tank State : ABORT"
            }
        },
        State {
            name: "9" //
            PropertyChanges {
                target: tankStateText
                text: "Tank State : TEST"
            }
        },
        State {
            name: "10" //
            PropertyChanges {
                target: tankStateText
                text: "Tank State : OFF NOMINAL"
            }
        },
        State {
            name: "11" //
            PropertyChanges {
                target: tankStateText
                text: "Tank State : AUTOSEQUENCE COMMANDED"
            }
        },
        State {
            name: "12" //
            PropertyChanges {
                target: tankStateText
                text: "Tank State : CONTROLLER_STATE_SIZE"
            }
        }
    ]
    /*
    PASSIVE = 0,
    STANDBY = 1,
    BANG_BANG_ACTIVE = 2,
    REG_PRESS_ACTIVE = 3,
    HI_PRESS_PASSTHROUGH_VENT = 4,
    ARMED = 5,
    PROP_TANK_VENT = 6,
    HI_VENT = 7,
    ABORT = 8,
    TEST_PASSTHROUGH = 9,
    OFF_NOMINAL_PASSTHROUGH = 10,
    AUTOSEQUENCE_COMMANDED = 11,
    CONTROLLER_STATE_SIZE = 12
    */
}
