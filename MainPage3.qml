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

Item {
    id: mainPage3
    visible: true
    width: 1550
    height: 735
    //anchors.fill: parent
    //title: qsTr(appDir + " --- Theseus GUI - window 3")
/*
    Tab {
        id: tab
        y: 0
        width: 447
        height: 51
        anchors.horizontalCenter: parent.horizontalCenter
    }
*/

    ChartView {
        id: chart
        title: "Top-5 car brand shares in Finland"
        animationDuration: 1000
        anchors.fill: parent
        legend.alignment: Qt.AlignBottom
        antialiasing: true

        theme: ChartView.ChartThemeDark

        property variant othersSlice: 0

        PieSeries {
            id: pieSeries
            PieSlice { label: "Volkswagen"; value: 13.5 }
            PieSlice { label: "Toyota"; value: 10.9 }
            PieSlice { label: "Ford"; value: 8.6 }
            PieSlice { label: "Skoda"; value: 8.2 }
            PieSlice { label: "Volvo"; value: 6.8 }
        }

        Component.onCompleted: {
            // You can also manipulate slices dynamically, like append a slice or set a slice exploded
            othersSlice = pieSeries.append("Others", 52.0);
            pieSeries.find("Volkswagen").exploded = true;
        }
    }
}
