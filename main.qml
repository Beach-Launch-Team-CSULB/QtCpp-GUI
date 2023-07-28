import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts

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
Window {
    //ApplicationWindow{
    id: window
    width: 1535//640
    height: 785 //480
    visible: true
    title: qsTr(appDir + " --- Theseus GUI")


    Component.onCompleted: { // Top level setup, and signal & handler connections (maybe)
    }

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            //GradientStop { position: 0.0; color: "grey"}
            GradientStop { position: 0.05; color: "black"}
            GradientStop { position: 0.25; color: "darkblue"}
            GradientStop { position: 0.95; color: "darkblue"}//#575757
            //GradientStop { position: 1; color: "grey"}
        }
    }

    StatusBar {
        id: statusBar

        TabBar {
            x: 590
            y: 0
            width: 166
            height: 42

            TabButton {
                id: mainPage1Button
                x: 581
                y: 0
                width: 49
                height: 26
                text: qsTr("Main")
                onClicked: mainLoader.source = "MainPage1.qml"
            }

            TabButton {
                id: mainPage2Button
                x: 629
                y: 0
                width: 55
                height: 26
                text: qsTr("Tanks")
                onClicked: mainLoader.source = "MainPage2.qml"

            }

            TabButton {
                id: mainPage3Button
                x: 690
                y: 0
                width: 66
                height: 26
                text: qsTr("Dumpster")
                onClicked: mainLoader.source = "MainPage3.qml"
            }

        }

        ToolBar {
            id: toolBar
            width: 360

            ToolButton {
                id: toolButton
                width: 60
                text: qsTr("Tool Button")
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.leftMargin: -6
                anchors.bottomMargin: 0
                anchors.topMargin: 0
            }

            ToolButton {
                id: toolButton1
                text: qsTr("Tool Button")
                anchors.left: toolButton.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.leftMargin: 0
                anchors.bottomMargin: 0
                anchors.topMargin: 0
            }
        }

        Text {
            id: dateTime
            x: 1191
            y: 0
            width: 344
            height: 50
            color: "#fc0c0c"
            text: qsTr(frameHandler.logger.digitalDateTime.toLocaleString())
            font.pixelSize: 21
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
    /*
    Tab {
        id: tab
        y: 0
        width: 50
        height: 34
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
    }
*/

    Loader {
        id: mainLoader
        anchors {
            left: parent.left
            right: parent.right
            top: statusBar.bottom
            bottom: parent.bottom
        }
        source: "MainPage1.qml"
    }


}
