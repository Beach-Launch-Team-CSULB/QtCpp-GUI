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
    id: mainPage3
    visible: true
    width: 1535
    height: 735
    //anchors.fill: parent
    //title: qsTr(appDir + " --- Theseus GUI - window 3")
/*
    Tab {
        id: tab
        y: 0
        width: 447
        height: 51
        anchors.horizontalCenter: parent.horizontalCenter
    }
*/

    Rectangle{
        id: testRect3
        width: 200
        height: 200
        color: "#d606367c"
        anchors {

        }

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Text{
            id: testText3
            text: "Page3"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
