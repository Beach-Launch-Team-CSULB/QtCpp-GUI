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
    width: 1550//640
    height: 785 //480
    visible: true
    title: qsTr(appDir + " --- Theseus GUI")


    Component.onCompleted: { // Top level setup, and signal & handler connections (maybe)
    }

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            //GradientStop { position: 0.0; color: "grey"}
            GradientStop { position: 0.05; color: "black"} //black
            GradientStop { position: 0.25; color: "darkblue"} // darkblue
            GradientStop { position: 0.95; color: "darkblue"} //darkblue  //#575757
            //GradientStop { position: 1; color: "grey"}
        }
    }

    StatusBar {
        id: statusBar

        TabBar {
            x: 590
            y: 0
            width: 236
            height: 42

            TabButton {
                id: mainPage1Button
                x: 581
                y: 0
                width: 49
                height: 26
                text: qsTr("Main")
                onClicked:
                {
                    mainLoader.source = "MainPage1.qml"
                    logScrollView.visible = true
                    en_dis_logging_button.visible = true
                }
            }

            TabButton {
                id: mainPage2Button
                x: 629
                y: 0
                width: 55
                height: 26
                text: qsTr("Tanks")
                onClicked:
                {
                    mainLoader.source = "MainPage2.qml"
                    logScrollView.visible = false
                    en_dis_logging_button.visible = false
                }
            }

            TabButton {
                id: mainPage3Button
                x: 102
                y: -3
                width: 69
                height: 26
                text: qsTr("Sensors")
                onClicked:
                {
                    mainLoader.source = "MainPage3.qml"
                    logScrollView.visible = false
                    en_dis_logging_button.visible = false
                }

            }
            TabButton {
                id: mainPage4Button
                x: 720
                y: 0
                width: 66
                height: 26
                text: qsTr("Dumpster")
                onClicked:
                {
                    mainLoader.source = "MainPage3.qml"
                    logScrollView.visible = false
                    en_dis_logging_button.visible = false
                }

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
    ///////////////////////////

    ScrollView {
        id: logScrollView
        visible: true
        clip: false
        x: 0
        y: 647
        z: 1
        width: 335
        height: 138

        TextArea {
            id: logTextArea
            color: "blue"
            placeholderText: "No log messages received..."
            placeholderTextColor: "gray"
            focus: false
            activeFocusOnPress: true
            width: logScrollView.width
            height: 140
            //anchors.fill: parent
            //onActiveFocusChanged: {

            //}

            function appendAndScroll(message)
            {
                var maxScrollPosition = logScrollView.contentItem.height - logScrollView.height;
                var atBottom = logScrollView.contentItem.contentY === maxScrollPosition;
                var currentHeight = logScrollView.contentItem.contentY

                if(atBottom)
                {
                    logTextArea.append(message)
                }
                else
                {
                    logTextArea.append(message)
                    //logScrollView.contentItem.contentY = currentHeight
                }
            }
        }

    }

    Connections {
        target: frameHandler.logger
        onLogMessageOutput:
        {
            console.log(message) // do textArea.append shit,
            // scrollView.contentItem.contentY = asdasdds - asdasdasd;
            //logTextArea.append(message)
            logTextArea.appendAndScroll(message)
            logTextArea.appendAndScroll(logTextArea.lineCount)
            logTextArea.appendAndScroll(logTextArea.length)
            while (logTextArea.length >= 10000)
            {
                logTextArea.remove(0, 200)
            }

            // Probably needs to do a flag that enables or disables logging so that user can scroll up and down
            // do an enable and a disable button
            // To let the user know, do this:
            // When enable button is clicked, it changes its color to green
            // when disable button is clicked, it changes its color to red
            // or do just one button that combines both features.

            //if (logTextArea.contentHeight >= logScrollView.height)
            //{
            //    console.log("logScrollView is at the bottom")
            console.log("before: " + logScrollView.contentItem.contentY)
            //logScrollView.contentItem.contentY = 0//logTextArea.height - logScrollView.contentItem.height
            //}
            console.log("after: " + logScrollView.contentItem.contentY)
            //console.log("before: " + logScrollView.contentItem.contentX)
            //console.log("before: " + logScrollView.contentItem.contentX)
            console.log(logTextArea.height)
            console.log(logScrollView.contentItem.height)

            if (true)
            {

            }
            else if( true)
            {
                //logScrollView.contentItem.contentY
            }

        }
    }

    Rectangle {
        id: logRectangle
        visible: logScrollView.visible
        rotation: 0
        x: 0
        y: 647
        width: 335
        height: 140
    }

    // Do the said logic for the en_dis_logging_button to enable/disable logging

    Rectangle {
        id: en_dis_logging_button
        x: 0
        y: 566
        width: 100
        height: 55
        color: "#7df885"
        radius: 11
        border.color: "#000000"
        // Do states for switching between enable and disable logging

        Label {
            id: label
            x: 10
            text: qsTr("Enable/Disable logging")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            anchors.rightMargin: 0
            anchors.leftMargin: 0
        }
    }

    Rectangle {
        id: rectangle2
        visible: logScrollView.visible
        y: 373
        width: 308
        height: 20
        color: "#ffffff"
        border.color: "#914040"
        border.width: 2
        anchors.left: logScrollView.left
        anchors.bottom: logScrollView.top
        anchors.right: logScrollView.right
        anchors.leftMargin: 0
        anchors.bottomMargin: 0

        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.9; color: "black"}
            GradientStop { position: 0.5; color: "blue"}
        }

        Label {
            id: label3
            y: -16
            z: 1
            width: 81
            height: 16
            visible: true
            color: "red"
            text: qsTr("Log Messages")
            anchors.fill: parent
            anchors.leftMargin: 5
        }
    }


}
