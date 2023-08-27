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
import LoggerEnums

Item {
    id: autosequenceQML
    width: 60
    height: 60

    state: "0"
    property real timerValue: 0

    Text {
        id: textState
        text: "Standby"
        anchors.left: parent.left
        anchors.leftMargin: 0
        color: "white"
        font.pixelSize: 25
    }

    Text {
        id: textTimer
        y: 30
        text: "T " + timerValue.toFixed(2) + " s"
        anchors.left: parent.left
        font.pixelSize: 45
        anchors.leftMargin: 0
    }

    states: [
        State{
            name: "0" // standby
            PropertyChanges {
                target: textState
                text: "Standby"
                color: "white"
            }
            PropertyChanges {
                target: textTimer
                color: "white"
            }
        },
        State{
            name: "1" // runCommanded
            PropertyChanges {
                target: textState
                text: "RunCommanded"
                color: "orange"
            }
            PropertyChanges {
                target: textTimer
                color: "orange"
            }
        },
        State{
            name: "2" // Running
            PropertyChanges {
                target: textState
                text: "Running"
                color: "lawngreen"
            }
            PropertyChanges {
                target: textTimer
                color: "lawngreen"
            }
        },
        State{
            name: "3" // Hold
            PropertyChanges {
                target: textState
                text: "Hold"
                color: "yellow"
            }
            PropertyChanges {
                target: textTimer
                color: "yellow"
            }
        }
    ]
}
