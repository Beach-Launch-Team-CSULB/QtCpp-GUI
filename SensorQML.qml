import QtQuick
import QtQuick.Controls
//Value next to sensors???
// do a GridView
Item {
    id: root

    Text {
        id: text1
        x: 316
        y: 113
        width: 49
        height: 41
        color: "white"
        text: qsTr("Text\n" + frameHandler.sensors.Lox_Tank_1.rawValue.toFixed(2) + " psi" ) //Change colors of text if pressure approaches certain threshold
        font.pixelSize: 15
    }


}
