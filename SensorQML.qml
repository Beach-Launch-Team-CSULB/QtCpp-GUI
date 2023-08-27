import QtQuick
import QtQuick.Controls
//Value next to sensors???
// do a GridView
Item {
    id: root
    width: 50
    height: 50

    property string name: "N/A"

    property int fontSize : 12

    property real sensorValue: 0.0 //frameHandler.sensors.Lox_Tank_1.rawValue.toFixed(2)

    property real safeThreshold: 400.0
    property real warningThreshold: 700.0
    property real criticalThreshold: 1000.0

    property color safeColor    : "white"
    property color warningColor : "yellow"
    property color criticalColor: "orange"
    property color runnnColor   : "red"

    state: "safe"

    //frameHandler.sensors.Lox_Tank_1.rawValue.toFixed(2) + " psi"
    // do a GridView in MainPage.qml
    Text {
        id: value
        anchors.fill: parent

        //color: safeColor
        text: name + ": " + sensorValue.toFixed(2) + " psi"  //Change colors of text if pressure approaches certain threshold
        //text: qsTr("Text\n" + frameHandler.sensors.Lox_Tank_1.timestamp.toFixed(2) + " s" )
        font.pixelSize: fontSize
    }

    states: [
        State {
            name: "safe"
            PropertyChanges {
                target: value
                color: safeColor
            }
        },
        State {
            name: "warning"
            PropertyChanges {
                target: value
                color: warningColor
            }
        },
        State {
            name: "critical"
            PropertyChanges {
                target: value
                color: criticalColor
            }
        },
        State {
            name: "RUNNN"
            PropertyChanges {
                target: value
                color: runnnColor
            }
        }
    ]
}
