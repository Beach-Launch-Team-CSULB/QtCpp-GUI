import QtQuick
import QtQuick.Controls
//import QtQuick.Controls.Styles
//import QtQuick.Controls.Material
import QtQuick.Layouts
import QtCharts
import QtMultimedia
// scrollbars

import FrameHandlerEnums
import SensorEnums
import HPSensorEnums
import ValveEnums
import NodeIDEnums
import AutosequenceEnums
import TankPressControllerEnums
import EngineControllerEnums
import LoggerEnums

Item {
    id: vehicleStateQML
    width: 60
    height: 60

    property string nodeName: "WHAT"
    state: "0"

    Text {
        id: nodeState
        anchors.fill: parent
        color: "orange"
        font.pixelSize: 18
    }

    states: [
        State {
            name: "0"
            PropertyChanges {
                target: nodeState
                text: nodeName + " : Setup"
            }
        },
        State {
            name: "1"
            PropertyChanges {
                target: nodeState
                text: nodeName + " : Passive"
            }
        },
        State {
            name: "2"
            PropertyChanges {
                target: nodeState
                text: nodeName + " : Standby"
            }
        },
        State {
            name: "3"
            PropertyChanges {
                target: nodeState
                text: nodeName + " : Test"
            }
        },
        State {
            name: "4"
            PropertyChanges {
                target: nodeState
                text: nodeName + " : Abort"
            }
        },
        State {
            name: "5"
            PropertyChanges {
                target: nodeState
                text: nodeName + " : Vent"
            }
        },
        State {
            name: "6"
            PropertyChanges {
                target: nodeState
                text: nodeName + " : OVERRIDE"
            }
        },
        State {
            name: "7"
            PropertyChanges {
                target: nodeState
                text: nodeName + " : HiPressArm"
            }
        },
        State {
            name: "8"
            PropertyChanges {
                target: nodeState
                text: nodeName + " : HiPressPressurized"
            }
        },
        State {
            name: "9"
            PropertyChanges {
                target: nodeState
                text: nodeName + " : TankPressArm"
            }
        },
        State {
            name: "10"
            PropertyChanges {
                target: nodeState
                text: nodeName + " : TankPressPressurized"
            }
        },
        State {
            name: "11"
            PropertyChanges {
                target: nodeState
                text: nodeName + " : fireArmed"
            }
        },
        State {
            name: "12"
            PropertyChanges {
                target: nodeState
                text: nodeName + " : fire"
            }
        }
    ]
}
