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
    id: autosequenceButton
    width: 50
    height: 65

    property string buttonOffName: "N/A"
    property string buttonOnName: "N/A"
    property color fontOnColorFromMain: "sandybrown"
    property color fontOffColorFromMain: "sandybrown"
    property color buttonOffColorFromMain: "gray"
    property color buttonOnColorFromMain: "lawngreen"
    property int fontSize: 12
    //property bool isOverrideButton: false

    state: "off"
    //property string prevState: "0"
    property string vehicleStateEngineNode: "0"
    property string vehicleStatePropNode: "0" //probably need just one since it depends on the node sync status anyway
    property string vehicleStateOnFlag: "0"

    property alias autosequenceMouseAreaForMain: autosequenceMouseArea

    onStateChanged: {
    }

    Connections { // MIGHT BE WRONG, ISSUES MAY ARISE
        target: frameHandler
        onNodeSyncStatusChanged:
        {
            if (frameHandler.nodeSyncStatus === FrameHandlerEnums.IN_SYNC) //probably need just one since it depends on the node sync status anyway
            {
                if (vehicleStateEngineNode !== vehicleStateOnFlag)
                {
                    autosequenceButton.state = "off"
                }
                else //if (vehicleStateEngineNode === vehicleStateOnFlag)
                {
                    autosequenceButton.state = "on"
                }
            }
            else (frameHandler.nodeSyncStatus === FrameHandlerEnums.NOT_IN_SYNC)
            {

            }
        }
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

            onPressed:  {
                buttonScaleUp.start();
            }
            onReleased: {
                buttonScaleDown.start();
            }
        }

        Label {
            id: autosequenceLabel
            text: autosequenceButton.buttonOffName
            color: "white"
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: fontSize
        }

        ScaleAnimator{
            id: buttonScaleUp // when hover over the valve
            target: autosequenceRectangle
            from: 1
            to: 1.15
            duration: 35 // Set this low
            running: false
        }

        ScaleAnimator{
            id: buttonScaleDown // when cursor exits the valve
            target: autosequenceRectangle
            from: 1.15
            to: 1
            duration: 35 // Set this low
            running: false
        }
    }

    states: [

        State {
            name: "off"
            PropertyChanges {
                target: autosequenceRectangle
                color: buttonOffColorFromMain
            }
            PropertyChanges {
                target: autosequenceLabel
                color: fontOffColorFromMain
                text: buttonOffName
            }
        },

        State {
            name: "on"
            PropertyChanges {
                target: autosequenceRectangle
                color: buttonOnColorFromMain
            }
            PropertyChanges {
                target: autosequenceLabel
                color: fontOnColorFromMain
                text: buttonOnName
            }
        }
/*
        State {
            name: "error"
            PropertyChanges {
                target: autosequenceRectangle
                color: "darkorange"
            }
        }
*/
    ]
}
