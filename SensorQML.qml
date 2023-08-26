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

    property real sensorRawValue: 0.0 //frameHandler.sensors.Lox_Tank_1.rawValue.toFixed(2)
    property real sensorConvertedValue: 0.0

    property real safeThreshold: 700.0
    property real warningThreshold: 1000.0
    property real criticalThreshold: 1200.0

    property color safeColor    : "white"
    property color warningColor : "yellow"
    property color criticalColor: "red"
    //frameHandler.sensors.Lox_Tank_1.rawValue.toFixed(2) + " psi"
    // do a GridView in MainPage.qml
    Text {
        id: value
        anchors.fill: parent

        color: safeColor
        text: name + ": " + sensorConvertedValue.toFixed(2) + " psi"  //Change colors of text if pressure approaches certain threshold
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
        }
    ]
}
