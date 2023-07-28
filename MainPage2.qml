import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts

import FrameHandlerEnums
import SensorEnums
import HPSensorEnums
import ValveEnums
import NodeIDEnums
import AutosequenceEnums
import TankPressControllerEnums
import EngineControllerEnums
Item {
    id: mainPage2
    visible: true
    width: 1535
    height: 735
    //anchors.fill: parent
    //title: qsTr(appDir + " --- Theseus GUI - window 2")

    Rectangle{
        id: testRect2
        width: 200
        height: 200
        color: "#6f8f6f"

        anchors {

        }

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter


        Text{
            id: testText2
            text: "Page2"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    GridView {

    }
}
