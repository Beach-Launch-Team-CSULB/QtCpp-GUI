import QtQuick

Item {
    height: 50
    anchors {
        left: parent.left
        top: parent.top
        right: parent.right
    }
    Rectangle {
        id: statusBar
        height: parent.height
        anchors.fill: parent
        border.color: "black"
        border.width: 1

        //color: "#003153" //Qt.rbga(0,0,0,0) "#faab4b"

        gradient: Gradient {
            //GradientStop { position: 0.0; color: "grey"}
            GradientStop { position: 0.05; color: "#003153"} //"#003153" //Qt.rbga(0,0,0,0) "#faab4b"
            GradientStop { position: 0.5; color: "#003153"}
            GradientStop { position: 0.99; color: "black"}//#575757
            //GradientStop { position: 1; color: "grey"}
        }
    }

}


