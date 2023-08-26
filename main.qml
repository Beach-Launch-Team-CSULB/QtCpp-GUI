import QtQuick
import QtQuick.Controls
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


Window {
    //ApplicationWindow{
    id: window
    width: 1550//640 // If there is a need to use a bigger monitor, then adjust width and height and position of
    height: 785 //480 // everything in accordance to that monitor's size
    visible: true
    title: appDir + " --- Theseus GUI"

    property string fileAppDir: "file:///" + appDir
    property string commandFrameID: (1).toString(16)
    property string objectConfigurationFrameID: (2).toString(16)
    property string nextLine : "\n                "

    // Rememberances for loaders
    property int main_defaultGraphQMLSensor1: 5
    property int main_defaultGraphQMLSensor2: 6
    property int main_defaultGraphQMLSensor3: 3
    property int main_defaultGraphQMLSensor4: 4
    property int main_defaultGraphQMLSensor5: 11
    property int main_defaultGraphQMLSensor6: 12

    Shortcut {
        sequence: "1"
        onActivated: {
            mainPage1Button.toggle();
            mainLoader.source = "MainPage1.qml"
            logScrollView.visible = true
            en_dis_logging_button.visible = true
            logFlushButton.visible = true
        }
    }
    Shortcut {
        sequence: "2"
        onActivated: {
            mainPage2Button.toggle();
            mainLoader.source = "MainPage2.qml"
            logScrollView.visible = false
            en_dis_logging_button.visible = false
            logFlushButton.visible = false
        }
    }
    Shortcut {
        sequence: "3"
        onActivated: {
            mainPage3Button.toggle();
            mainLoader.source = "MainPage3.qml"
            logScrollView.visible = false
            en_dis_logging_button.visible = false
            logFlushButton.visible = false
        }
    }
    Shortcut {
        sequence: "4"
        onActivated: {
            mainPage4Button.toggle();
            mainLoader.source = "MainPage4.qml"
            logScrollView.visible = false
            en_dis_logging_button.visible = false
            logFlushButton.visible = false
        }
    }
    Shortcut {
        sequence: "5"
        onActivated: {
            mainPage5Button.toggle();
            mainLoader.source = "MainPage5.qml"
            logScrollView.visible = false
            en_dis_logging_button.visible = false
            logFlushButton.visible = false
        }
    }




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
            id: tabBar
            x: 590
            y: 0
            width: 315
            height: 50
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

            TabButton {
                id: mainPage1Button
                x: 581
                width: 49
                text: qsTr("Main")
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: -1
                anchors.topMargin: 0
                onClicked:
                {
                    mainLoader.source = "MainPage1.qml"
                    logScrollView.visible = true
                    en_dis_logging_button.visible = true
                    logFlushButton.visible = true
                }
            }

            TabButton {
                id: mainPage2Button
                x: 629
                width: 55
                text: qsTr("Tanks")
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.topMargin: -3
                onClicked:
                {
                    mainLoader.source = "MainPage2.qml"
                    logScrollView.visible = false
                    en_dis_logging_button.visible = false
                    logFlushButton.visible = false
                }
            }

            TabButton {
                id: mainPage3Button
                x: 102
                width: 69
                text: qsTr("Sensors")
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.topMargin: -3 // DO BAR GRAPHS FOR THE SENSORS(OR TANKS) TO SAVE DATA POINTS!!!!
                onClicked:
                {
                    mainLoader.source = "MainPage3.qml"
                    logScrollView.visible = false
                    en_dis_logging_button.visible = false
                    logFlushButton.visible = false
                }

            }
            TabButton {
                id: mainPage4Button
                x: 170
                width: 91
                text: qsTr("GNC/Telemetry")
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.topMargin: -3
                onClicked:
                {
                    //var component = Qt.createComponent("GraphQML.qml");
                    //var windowy    = component.createObject(window);
                    //windowy.show();
                    mainLoader.source = "MainPage4.qml"
                    logScrollView.visible = false
                    en_dis_logging_button.visible = false
                    logFlushButton.visible = false
                }
            }

            TabButton {
                id: mainPage5Button
                x: 261
                y: -3
                text: "Cameras"
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.topMargin: -3
                onClicked:
                {

                }
            }
        }

        ToolBar {
            id: toolBar
            y: 26
            width: 360
            height: 20
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.leftMargin: 0

            ToolButton {
                id: toolButton
                width: 87
                text: "Tool Button 1" // Do pictures instead
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.leftMargin: -6
                anchors.bottomMargin: 0
                anchors.topMargin: 0
                onClicked: {
                    console.log(toolButton.text + " clicked")
                }
            }

            ToolButton {
                id: toolButton1
                text: "Tool Button 2" // Do pictures instead
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
            x: 1116
            y: 0
            width: 419
            height: 50
            color: "#fc0c0c"
            text: frameHandler.logger.digitalDateTime.toLocaleString()
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
            //focus: false
            activeFocusOnPress: false
            readOnly: true
            width: logScrollView.width
            height: 140
            //anchors.fill: parent
            //onActiveFocusChanged: {

            //}
        }

    }

    Connections {
        target: frameHandler.logger
        onLogMessageOutput:
        {
            if (en_dis_logging_button.state === "1")
            {
                // Flush log buffer here when logging is enabled again
                // logTextArea.append(buffer) // buffer should be QString in C++
                // frameHandler.logger.clearBuffer();
                if (frameHandler.logger.messageBuffer.length > 1)
                {
                    logTextArea.append(frameHandler.logger.messageBuffer);
                    frameHandler.logger.clearMessageBuffer();
                }



                console.log(message) // do textArea.append shit,
                logTextArea.append(message)
                //logTextArea.append(logTextArea.lineCount)
                //logTextArea.append(logTextArea.length)
                logScrollView.contentItem.contentY = logTextArea.height - logScrollView.contentItem.height
                logScrollView.contentItem.contentX = 0
                while (logTextArea.length >= 10000)
                {
                    logTextArea.remove(0, 200)
                }


                if (true)
                {

                }
                else if( true)
                {
                    //logScrollView.contentItem.contentY
                }
            }
            else if (en_dis_logging_button.state === "0")
            {
                // Make a buffer in C++, and when logging is disabled, logs are stored
                // in that buffer instead and flushed when logging is enabled again
                frameHandler.logger.loadUpMessageBuffer(message);
            }
        }
    }

    MenuBar{
        id: mainMenuBar
        y: 0
        width: 360
        height: 30
        anchors.left: parent.left
        anchors.leftMargin: 0

        // Make a menu for selecting objects to configure via can frame
        Menu {
            title: "CAN"
            Action {
                text: "&Connect CAN"
                shortcut: "Ctrl+C"
                onTriggered: {
                    frameHandler.connectCan();
                }
            }
            Action {
                text: "&Disconnect CAN"
                shortcut: "Ctrl+D"
                onTriggered: {
                    frameHandler.disconnectCan();
                }
            }
        }
        Menu {
            title: "Object configuration" // append ... at the end to indicate the opening of a new popup/stackview/window to configure the object
            Action { text: "Configure object 1..."} // open a popup/stackview/window to configure the object and a button to send the configuration command via CAN
            Action { text: "Configure object 2..."} // open a popup/stackview/window to configure the object and a button to send the configuration command via CAN
            Action { text: "Configure object 3..."} // open a popup/stackview/window to configure the object and a button to send the configuration command via CAN
            Action { text: "Configure object 4..."} // open a popup/stackview/window to configure the object and a button to send the configuration command via CAN
            Action { text: "Configure object 1..."} // ALSO PUT NAME OF THE OBJECT BEING CONFIGURED IN THE POPUP TO NOTIFY WHAT IS BEING CHANGED
            Action { text: "Configure object 2..."}
            Action { text: "Configure object 3..."}
            Action { text: "Configure object 4..."}
            Action { text: "Configure object 1..."}
            Action { text: "Configure object 2..."}
            Action { text: "Configure object 3..."}
            Action { text: "Configure object 4..."}
            Action { text: "Configure object 1..."}
            Action { text: "Configure object 2..."}
            Action { text: "Configure object 3..."}
            Action { text: "Configure object 4..."}
            Action { text: "Configure object 1..."}
            Action { text: "Configure object 2..."}
            Action { text: "Configure object 3..."}
            Action { text: "Configure object 4..."}
            Action { text: "Configure object 1..."}
            Action { text: "Configure object 2..."}
            Action { text: "Configure object 3..."}
            Action { text: "Configure object 4..."}
            Action { text: "Configure object 1..."}
            Action { text: "Configure object 2..."}
            Action { text: "Configure object 3..."}
            Action { text: "Configure object 4..."}
            Action { text: "Configure object 1..."}
            Action { text: "Configure object 2..."}
            Action { text: "Configure object 3..."}
            Action { text: "Configure object 4..."}
            Action { text: "Configure object 1..."}
            Action { text: "Configure object 2..."}
            Action { text: "Configure object 3..."}
            Action { text: "Configure object 4..."}
            Action { text: "Configure object 1..."}
            Action { text: "Configure object 2..."}
            Action { text: "Configure object 3..."}
            Action { text: "Configure object 4..."}
            Action { text: "Configure object 1..."}
            Action { text: "Configure object 2..."}
            Action { text: "Configure object 3..."}
            Action { text: "Configure object 4..."}
            Action { text: "Configure object 1..."}
            Action { text: "Configure object 2..."}
            Action { text: "Configure object 3..."}
            Action { text: "Configure object 4..."}
            Action { text: "Configure object 1..."}
            Action { text: "Configure object 2..."}
            Action { text: "Configure object 3..."}
            Action { text: "Configure object 4..."}
        }
        Menu {
            title: "Sensor rates"
            Action {
                text: "All Sensors Off"
            }
            Action {
                text: "All Sensors Slow"
            }
            Action {
                text: "All Sensors Medium"
            }
            Action {
                text: "All Sensors Fast"
            }
            Action {
                text: "All Sensors Calibration"
            }
        }

    }
    Button {
        id: logFlushButton
        x: 130
        y: 568
        width: 85
        height: 54
        text: "Flush Logs"
        visible: true
        antialiasing: true
        onClicked: {
            if (en_dis_logging_button.state === "1" && frameHandler.logger.messageBuffer.length > 1)
            {
                frameHandler.logger.outputLogMessage("Log buffer flushed");
            }
        }
    }
/*
    Button {
        id: resetLogViewButton
        x: 180
        y: 568
        width: 85
        height: 54
        text: "Reset Log View"
        visible: true
        antialiasing: true
    }
*/
    Rectangle {
        id: logRectangle
        visible: logScrollView.visible
        rotation: 0
        x: 0
        y: 647
        width: 335
        height: 140
    }

    //    // Do the said logic for the en_dis_logging_button to enable/disable logging

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
        state: "1" // enabled by default

        MouseArea
        {
            id: logMouseArea
            anchors.fill: en_dis_logging_button
            acceptedButtons: Qt.LeftButton
            hoverEnabled: true
            enabled: true
            onClicked: {
                parseInt(en_dis_logging_button.state) ? en_dis_logging_button.state = "0" : en_dis_logging_button.state = "1"
            }
        }

        Label {
            id: logButtonLabel
            x: 10
            text: qsTr(" ")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            anchors.rightMargin: 0
            anchors.leftMargin: 0
        }

        states: [ // Name the states with string instead of int to distinguish between C++ and QML
            State{
                name: "0" // Disable
                PropertyChanges {
                    target: en_dis_logging_button
                    color: "red"
                }
                PropertyChanges {
                    target: logButtonLabel
                    text: "Logging Disabled"
                }
            },

            State{
                name: "1" // Enable
                PropertyChanges {
                    target: en_dis_logging_button
                    color: "lawngreen"
                }
                PropertyChanges {
                    target: logButtonLabel
                    text: "Logging Enabled"
                }
            }
        ]
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
            id: logLabel
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
