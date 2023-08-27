import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
// do a GridView

import FrameHandlerEnums
import SensorEnums
import HPSensorEnums
import ValveEnums
import NodeIDEnums
import AutosequenceEnums
import TankPressControllerEnums
import EngineControllerEnums
import LoggerEnums

Item {
    id: engineController
    width: 40
    height: width

    property string name: "N/A"
    property int timerValue: 0
    property color fontColor: "black"
    property int fontSize: 15

    Text {
        id: value
        anchors.fill: parent

        color: fontColor
        text: name + ": " + timerValue + " ms"  //Change colors of text if pressure approaches certain threshold
        font.pixelSize: fontSize
    }
}
