import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: item1

    signal tabClicked

    TabBar { // Switch between different windows
        id: tabBar
        y: 0
        width: 446
        height: 50
        anchors.horizontalCenter: parent.horizontalCenter

        TabButton {
            id: mainPage1
            width: 150
            height: 50
            text: qsTr("Page 1")
            anchors.top: parent.top
            anchors.topMargin: 0
            onClicked: pageLoader.source = "MainPage1.qml"
        }

        TabButton {
            id: mainPage2
            width: 150
            height: 52
            text: qsTr("Page 2")
            anchors.left: tabButton.right
            anchors.top: parent.top
            anchors.leftMargin: 0
            anchors.topMargin: -2
            onClicked: pageLoader.source = "MainPage2.qml"
        }

        TabButton {
            id: mainPage3
            width: 150
            height: 52
            // Telemetry window??
            text: qsTr("Page 3")
            anchors.left: tabButton1.right
            anchors.top: parent.top
            anchors.leftMargin: 0
            anchors.topMargin: -2
            onClicked: pageLoader.source = "MainPage3.qml"
        }

    }
}
