import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
// do a GridView

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
    id: autosequenceButton
    width: 50
    height: 50

    property string buttonName: "N/A"


    state: "0"
    property string prevState: "0"
    property string vehicleStateOnFlag: "0"

    onStateChanged: {

    }


    Rectangle {
        id: autosequenceRectangle
        anchors.fill: parent
        radius: 5
        //color: "gray"

        MouseArea {
            id: autosequenceMouseArea
            anchors.fill: parent
            hoverEnabled: true
            enabled: true

            onDoubleClicked: {

            }

            onPressed:  {
                prevState = autosequenceButton.state
                //then change state
                // Need more work
            }
            onReleased: {
                //then change state
                // Need more work
                autosequenceButton.state = prevState

            }
        }

        Label {
            id: autosequenceLabel
            text: "N/A"
            color: "white"
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }



    states: [
        State {
            name: "0"
            PropertyChanges {
                target: autosequenceRectangle
                color: "gray"
            }
        },
        State {
            name: "1"
            PropertyChanges {
                target: autosequenceRectangle
                color: "lawngreen"
            }
        },
        State {
            name: "2" // pressed
            PropertyChanges {
                target: autosequenceRectangle
                color: "orange"
            }
        }
    ]
}
