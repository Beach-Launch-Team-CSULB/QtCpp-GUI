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


// Need to USE LOADER instead of setting the visibility for performance
// or borrow a laptop from NASA

// OR change up the report rates of the Can3FDController (most likely this approach)

// OR use a QML timer and collect the timestamp and values at certain intervals like 0.1 seconds
// Probably use a timer a get a new laptop
Item {
    id: mainPage2
    visible: true
    width: 1550
    height: 735

    Rectangle {
        id: loxTank
        y: 170
        width: 150
        height: 340
        color: "#3c91f4"
        radius: 60
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -300
    }

    Rectangle {
        id: fuelTank
        x: 4
        y: 170
        width: 150
        height: 340
        color: "#ad6e19"
        radius: 60
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 300
    }
    //anchors.fill: parent
    //title: qsTr(appDir + " --- Theseus GUI - window 2")

    //Component.onCompleted: { // save measure
    //    while(lineSeriesPage2.count > 0)
    //    {
    //        lineSeriesPage2.remove(0);
    //    }
    //}


}
