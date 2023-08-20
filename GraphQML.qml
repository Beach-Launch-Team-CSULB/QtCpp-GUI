import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts
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
    id: root
    width: 300
    height: 224

    property int defaultSensor: 1

    Component.onCompleted:
    {
        comboBoxGraph.currentIndex = defaultSensor
        loadGraph(defaultSensor);
    }

    function loadGraph(index)
    {
        switch(index)
        {
            case 0:
                graphLoader.sourceComponent = undefined;
                break;
            case 1:
                graphLoader.sourceComponent = high_Press_1;
                break;
            case 2:
                graphLoader.sourceComponent = high_Press_2;
                break;
            case 3:
                graphLoader.sourceComponent = fuel_Tank_1;
                break;
            case 4:
                graphLoader.sourceComponent = fuel_Tank_2;
                break;
            case 5:
                graphLoader.sourceComponent = lox_Tank_1;
                break;
            case 6:
                graphLoader.sourceComponent = lox_Tank_2;
                break;
            case 7:
                graphLoader.sourceComponent = fuel_Dome_Reg;
                break;
            case 8:
                graphLoader.sourceComponent = lox_Dome_Reg;
                break;
            case 9:
                graphLoader.sourceComponent = fuel_Prop_Inlet;
                break;
            case 10:
                graphLoader.sourceComponent = lox_Prop_Inlet;
                break;
            case 11:
                graphLoader.sourceComponent = chamber_1;
                break;
            case 12:
                graphLoader.sourceComponent = chamber_2;
                break;
            case 13:
                graphLoader.sourceComponent = mainValve_Pneumatic;
                break;
            case 14:
                graphLoader.sourceComponent = undefined; // load_Cell_1, not yet implemented
                break;
            case 15:
                graphLoader.sourceComponent = undefined; // load_Cell_2, not yet implemented
                break;
            case 16:
                graphLoader.sourceComponent = undefined; // load_Cell_3, not yet implemented
                break;
            case 17:
                graphLoader.sourceComponent = renEnHP1;
                break;
            case 18:
                graphLoader.sourceComponent = renEnHP2;
                break;
            case 19:
                graphLoader.sourceComponent = renEnHP3;
                break;
            case 20:
                graphLoader.sourceComponent = renEnHP4;
                break;
            case 21:
                graphLoader.sourceComponent = renEnHP5;
                break;
            case 22:
                graphLoader.sourceComponent = renEnHP6;
                break;
            case 23:
                graphLoader.sourceComponent = renEnHP7;
                break;
            case 24:
                graphLoader.sourceComponent = renEnHP8;
                break;
            case 25:
                graphLoader.sourceComponent = renEnHP9;
                break;
            case 26:
                graphLoader.sourceComponent = renEnHP10;
                break;
            case 27:
                graphLoader.sourceComponent = renPropHP1;
                break;
            case 28:
                graphLoader.sourceComponent = renPropHP2;
                break;
            case 29:
                graphLoader.sourceComponent = renPropHP3;
                break;
            case 30:
                graphLoader.sourceComponent = renPropHP4;
                break;
            case 31:
                graphLoader.sourceComponent = renPropHP5;
                break;
            case 32:
                graphLoader.sourceComponent = renPropHP6;
                break;
            case 33:
                graphLoader.sourceComponent = renPropHP7;
                break;
            case 34:
                graphLoader.sourceComponent = renPropHP8;
                break;
            case 35:
                graphLoader.sourceComponent = renPropHP9;
                break;
            case 36:
                graphLoader.sourceComponent = renPropHP10;
                break;
        }
    }

    function appendAndAdjustView(x, y, chartView, lineSeries, safeThreshold = 700, warningThreshold = 1000, criticalThreshold = 1200)    // member variables of the object linesSeries are passed by reference, so lineSeries.someMember should
                                            // affect the someMember variable of the original object
    {
        var numberOfDataPoints = 100;

        var minXMargin = 8; // left of latest data point
        var maxXMargin = 2; // right of latest data point (leave some margin)
        var minYMargin = 80; // bottom of latest data point
        var maxYMargin = 20; // top of latest data point (leave some margin)


        // The range between min and max of x axis (timestamp) should be 0-60
        var minXViewDefault = 0;
        var maxXViewDefault = minXMargin + maxXMargin;
        // The range between min and max of y axis (read value) should be 0-300
        var minYViewDefault = 0;
        var maxYViewDefault = minYMargin + maxYMargin;

        // After calculation for the mins and maxes of x and y axes, if the mins are negative, then set the respective
        // mins and maxes to predefined values, i.e the 4 ViewDefault values .
        if (x - minXMargin <= 0)
        {
            lineSeries.axisX.min = minXViewDefault;
            lineSeries.axisX.max = maxXViewDefault;
        }
        else
        {
            lineSeries.axisX.min = x - minXMargin;
            lineSeries.axisX.max = x + maxXMargin;
        }

        if (y - minYMargin <= 0)
        {
            lineSeries.axisY.min = minYViewDefault;
            lineSeries.axisY.max = maxYViewDefault;
        }
        else
        {
            if (y < lineSeries.axisY.min)
            {
                lineSeries.axisY.min = y - maxYMargin;
                lineSeries.axisY.max = y + minYMargin;
            }
            else if (y > lineSeries.axisY.max)
            {
                lineSeries.axisY.min = y - minYMargin;
                lineSeries.axisY.max = y + maxYMargin;
            }
        }

        lineSeries.append(x,y);
        while(lineSeries.count > numberOfDataPoints) // Starts getting laggy for a total of 1500 data points across all graphs,
        {                                            // I.e.: numberOfDataPoints * sensors on display < 1500
            lineSeries.remove(0);
        }
        if (y < safeThreshold)
        {
            lineSeries.axisX.labelsColor = "white"
            lineSeries.axisX.color = "white"
            lineSeries.axisY.labelsColor = "white"
            lineSeries.axisY.color = "white"
            chartView.titleColor = "white"
        }
        else if (safeThreshold <= y && y < warningThreshold) // && y < 1000
        {
            lineSeries.axisX.labelsColor = "orange"
            lineSeries.axisX.color = "orange"
            lineSeries.axisY.labelsColor = "orange"
            lineSeries.axisY.color = "orange"
            chartView.titleColor = "orange"
        }
        else if (warningThreshold <= y && y < criticalThreshold)
        {
            lineSeries.axisX.labelsColor = "red"
            lineSeries.axisX.color = "red"
            lineSeries.axisY.labelsColor = "red"
            lineSeries.axisY.color = "red"
            chartView.titleColor = "red"
        }
        else if (y >= criticalThreshold)
        {
            lineSeries.axisX.labelsColor = "pink"
            lineSeries.axisX.color = "pink"
            lineSeries.axisY.labelsColor = "pink"
            lineSeries.axisY.color = "pink"
            chartView.titleColor = "pink"
            // for Critical point use ternary operator for cool flashing a cool flashing effect
        }
    }


    function action() {
                    console.log("High_Press_1")
                }

    Loader {
        id: graphLoader
        width: parent.width - 100
        height: parent.height
        anchors.bottomMargin: 0
        anchors.topMargin: 2
        anchors {
            left: parent.left
            leftMargin: 0
            right: parent.right
            top: comboBoxGraph.bottom
            bottom: parent.bottom
        }
        sourceComponent: undefined
    }

    //ListModel

    ListModel {
        id: sensorModel

        // Sensors
        ListElement {  //0
            name: "Select sensor" // graphLoader.sourceComponent = undefined
        }
        ListElement {  //1
            name: "High_Press_1"
        }
        ListElement {  //2
            name: "High_Press_2"
        }
        ListElement {  //3
            name: "Fuel_Tank_1"
        }
        ListElement { //4
            name: "Fuel_Tank_2"
        }
        ListElement { //5
            name: "Lox_Tank_1"
        }
        ListElement { //6
            name: "Lox_Tank_2"
        }
        ListElement { //7
            name: "Fuel_Dome_Reg"
        }
        ListElement { //8
            name: "Lox_Dome_Reg"
        }
        ListElement { //9
            name: "Fuel_Prop_Inlet"
        }
        ListElement { //10
            name: "Lox_Prop_Inlet"
        }
        ListElement { //11
            name: "Chamber_1"
        }
        ListElement { //12
            name: "Chamber_2"
        }
        ListElement { //13
            name: "MV_Pneumatic"
        }

        // Load Cells
        ListElement { //14
            name: "Load_Cell_1"
        }
        ListElement { //15
            name: "Load_Cell_2"
        }
        ListElement { //16
            name: "Load_Cell_3"
        }

        ListElement{ //17
            name: "RenEnHP1"
        }
        ListElement{ //18
            name: "RenEnHP2"
        }
        ListElement{ //19
            name: "RenEnHP3"
        }
        ListElement{  //20
            name: "RenEnHP4"
        }
        ListElement{  //21
            name: "RenEnHP5"
        }
        ListElement{  //22
            name: "RenEnHP6"
        }
        ListElement{  //23
            name: "RenEnHP7"
        }
        ListElement{  //24
            name: "RenEnHP8"
        }
        ListElement{  //25
            name: "RenEnHP9"
        }
        ListElement{  //26
            name: "RenEnHP10"
        }
        ListElement{  //27
            name: "RenPropHP1"
        }
        ListElement{  //28
            name: "RenPropHP2"
        }
        ListElement{  //29
            name: "RenPropHP3"
        }
        ListElement{  //30
            name: "RenPropHP4"
        }
        ListElement{   //31
            name: "RenPropHP5"
        }
        ListElement{   //32
            name: "RenPropHP6"
        }
        ListElement{    //33
            name: "RenPropHP7"
        }
        ListElement{    //34
            name: "RenPropHP8"
        }
        ListElement{   //35
            name: "RenPropHP9"
        }
        ListElement{  //36
            name: "RenPropHP10"
        }
    }

    Component {
        id: high_Press_1
        ChartView {
            id: high_Press_1_ChartView
            title: "High Press 1 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean

            ValuesAxis {
                id:  high_Press_1_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  high_Press_1_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true


                //gridLineColor: "white"
                //minorGridVisible: true
                //minorGridLineColor: "pink"
                //shadesBorderColor: "blue"
            }
            LineSeries {
                id: high_Press_1_LineSeries

                axisX: high_Press_1_valuesAxisX
                axisY: high_Press_1_valuesAxisY
            }
            Connections {
                target: frameHandler.sensors.High_Press_1
                onUpdateGraphQML_convertedValue: {
                    appendAndAdjustView(x_timestamp, y_convertedValue, high_Press_1_ChartView, high_Press_1_LineSeries);
                }
            }
        }
    }

    Component {
        id: high_Press_2
        ChartView {
            id: high_Press_2_ChartView
            title: "High Press 2 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean

            ValuesAxis {
                id:  high_Press_2_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  high_Press_2_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true


                //gridLineColor: "white"
                //minorGridVisible: true
                //minorGridLineColor: "pink"
                //shadesBorderColor: "blue"
            }
            LineSeries {
                id: high_Press_2_LineSeries

                axisX: high_Press_2_valuesAxisX
                axisY: high_Press_2_valuesAxisY
            }
            Connections {
                target: frameHandler.sensors.High_Press_2
                onUpdateGraphQML_convertedValue: {
                    appendAndAdjustView(x_timestamp, y_convertedValue, high_Press_2_ChartView, high_Press_2_LineSeries);
                }
            }
        }
    }

    Component {
        id: fuel_Tank_1
        ChartView {
            id: fuel_Tank_1_ChartView
            title: "Fuel Tank 1 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean

            ValuesAxis {
                id:  fuel_Tank_1_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  fuel_Tank_1_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true


                //gridLineColor: "white"
                //minorGridVisible: true
                //minorGridLineColor: "pink"
                //shadesBorderColor: "blue"
            }
            LineSeries {
                id: fuel_Tank_1_LineSeries

                axisX: fuel_Tank_1_valuesAxisX
                axisY: fuel_Tank_1_valuesAxisY
            }
            Connections {
                target: frameHandler.sensors.Fuel_Tank_1
                onUpdateGraphQML_convertedValue: {
                    appendAndAdjustView(x_timestamp, y_convertedValue, fuel_Tank_1_ChartView, fuel_Tank_1_LineSeries);
                }
            }
        }
    }

    Component {
        id: fuel_Tank_2
        ChartView {
            id: fuel_Tank_2_ChartView
            title: "Fuel Tank 2 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean

            ValuesAxis {
                id:  fuel_Tank_2_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  fuel_Tank_2_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true


                //gridLineColor: "white"
                //minorGridVisible: true
                //minorGridLineColor: "pink"
                //shadesBorderColor: "blue"
            }
            LineSeries {
                id: fuel_Tank_2_LineSeries

                axisX: fuel_Tank_2_valuesAxisX
                axisY: fuel_Tank_2_valuesAxisY
            }
            Connections {
                target: frameHandler.sensors.Fuel_Tank_2
                onUpdateGraphQML_convertedValue: {
                    appendAndAdjustView(x_timestamp, y_convertedValue, fuel_Tank_2_ChartView, fuel_Tank_2_LineSeries);
                }
            }
        }
    }

    Component {
        id: lox_Tank_1
        ChartView {
            id: lox_Tank_1_ChartView
            title: "Lox Tank 1 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean

            ValuesAxis {
                id:  lox_Tank_1_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  lox_Tank_1_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true


                //gridLineColor: "white"
                //minorGridVisible: true
                //minorGridLineColor: "pink"
                //shadesBorderColor: "blue"
            }
            LineSeries {
                id: lox_Tank_1_LineSeries

                axisX: lox_Tank_1_valuesAxisX
                axisY: lox_Tank_1_valuesAxisY
            }
            Connections {
                target: frameHandler.sensors.Lox_Tank_1
                onUpdateGraphQML_convertedValue: {
                    appendAndAdjustView(x_timestamp, y_convertedValue, lox_Tank_1_ChartView, lox_Tank_1_LineSeries);
                }
            }
        }
    }



    Component {
        id: lox_Tank_2
        ChartView {
            id: lox_Tank_2_ChartView
            title: "Lox Tank 2 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean

            ValuesAxis {
                id:  lox_Tank_2_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  lox_Tank_2_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: lox_Tank_2_LineSeries

                axisX: lox_Tank_2_valuesAxisX
                axisY: lox_Tank_2_valuesAxisY
            }
            Connections {
                target: frameHandler.sensors.Lox_Tank_2
                onUpdateGraphQML_convertedValue: {
                    appendAndAdjustView(x_timestamp, y_convertedValue, lox_Tank_2_ChartView, lox_Tank_2_LineSeries);
                }
            }
        }
    }

    Component {
        id: fuel_Dome_Reg
        ChartView {
            id: fuel_Dome_Reg_ChartView
            title: "Fuel Dome Reg (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean

            ValuesAxis {
                id:  fuel_Dome_Reg_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  fuel_Dome_Reg_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: fuel_Dome_Reg_LineSeries
                axisX: fuel_Dome_Reg_valuesAxisX
                axisY: fuel_Dome_Reg_valuesAxisY
            }
            Connections {
                target: frameHandler.sensors.Fuel_Dome_Reg
                onUpdateGraphQML_convertedValue: {
                    appendAndAdjustView(x_timestamp, y_convertedValue, fuel_Dome_Reg_ChartView, fuel_Dome_Reg_LineSeries);
                }
            }
        }
    }

    Component {
        id: lox_Dome_Reg
        ChartView {
            id: lox_Dome_Reg_ChartView
            title: "Lox Dome Reg (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean

            ValuesAxis {
                id:  lox_Dome_Reg_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  lox_Dome_Reg_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: lox_Dome_Reg_LineSeries

                axisX: lox_Dome_Reg_valuesAxisX
                axisY: lox_Dome_Reg_valuesAxisY
            }
            Connections {
                target: frameHandler.sensors.Lox_Dome_Reg
                onUpdateGraphQML_convertedValue: {
                    appendAndAdjustView(x_timestamp, y_convertedValue, lox_Dome_Reg_ChartView, lox_Dome_Reg_LineSeries);
                }
            }
        }
    }

    Component {
        id: fuel_Prop_Inlet
        ChartView {
            id: fuel_Prop_Inlet_ChartView
            title: "Fuel Prop Inlet (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean

            ValuesAxis {
                id:  fuel_Prop_Inlet_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  fuel_Prop_Inlet_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: fuel_Prop_Inlet_LineSeries
                axisX: fuel_Prop_Inlet_valuesAxisX
                axisY: fuel_Prop_Inlet_valuesAxisY
            }
            Connections {
                target: frameHandler.sensors.Fuel_Prop_Inlet
                onUpdateGraphQML_convertedValue: {
                    appendAndAdjustView(x_timestamp, y_convertedValue, fuel_Prop_Inlet_ChartView, fuel_Prop_Inlet_LineSeries);
                }
            }
        }
    }

    Component {
        id: lox_Prop_Inlet
        ChartView {
            id: lox_Prop_Inlet_ChartView
            title: "Lox Prop Inlet (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean

            ValuesAxis {
                id:  lox_Prop_Inlet_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  lox_Prop_Inlet_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: lox_Prop_Inlet_LineSeries
                axisX: lox_Prop_Inlet_valuesAxisX
                axisY: lox_Prop_Inlet_valuesAxisY
            }
            Connections {
                target: frameHandler.sensors.Lox_Prop_Inlet
                onUpdateGraphQML_convertedValue: {
                    appendAndAdjustView(x_timestamp, y_convertedValue, lox_Prop_Inlet_ChartView, lox_Prop_Inlet_LineSeries);
                }
            }
        }
    }

    Component {
        id: chamber_1
        ChartView {
            id: chamber_1_ChartView
            title: "Chamber 1 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean

            ValuesAxis {
                id:  chamber_1_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  chamber_1_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: chamber_1_LineSeries
                axisX: chamber_1_valuesAxisX
                axisY: chamber_1_valuesAxisY
            }
            Connections {
                target: frameHandler.sensors.chamber_1_Inlet
                onUpdateGraphQML_convertedValue: {
                    appendAndAdjustView(x_timestamp, y_convertedValue, chamber_1_ChartView, chamber_1_LineSeries);
                }
            }
        }
    }

    Component {
        id: chamber_2
        ChartView {
            id: chamber_2_ChartView
            title: "Chamber 2 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean

            ValuesAxis {
                id:  chamber_2_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  chamber_2_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: chamber_2_LineSeries
                axisX: chamber_2_valuesAxisX
                axisY: chamber_2_valuesAxisY
            }
            Connections {
                target: frameHandler.sensors.chamber_2_Inlet
                onUpdateGraphQML_convertedValue: {
                    appendAndAdjustView(x_timestamp, y_convertedValue, chamber_2_ChartView, chamber_2_LineSeries);
                }
            }
        }
    }

    Component {
        id: mainValve_Pneumatic
        ChartView {
            id: mainValve_Pneumatic_ChartView
            title: "Main Valve Pneumatic (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean

            ValuesAxis {
                id:  mainValve_Pneumatic_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  mainValve_Pneumatic_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: mainValve_Pneumatic_LineSeries
                axisX: mainValve_Pneumatic_valuesAxisX
                axisY: mainValve_Pneumatic_valuesAxisY
            }
            Connections {
                target: frameHandler.sensors.MainValve_Pneumatic
                onUpdateGraphQML_convertedValue: {
                    appendAndAdjustView(x_timestamp, y_convertedValue, mainValve_Pneumatic_ChartView, mainValve_Pneumatic_LineSeries);
                }
            }
        }
    }

    Component {
        id: load_Cell_1
        ChartView {

        }
    }

    Component {
        id: load_Cell_2
        ChartView {

        }
    }

    Component {
        id: load_Cell_3
        ChartView {

        }
    }

    Component {
        id: renEnHP1
        ChartView {
            id: renEnHP1_ChartView
            title: "Engine High Power 1 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renEnHP1_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renEnHP1_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renEnHP1_LineSeries
                axisX: renEnHP1_valuesAxisX
                axisY: renEnHP1_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadeEngineHP1
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renEnHP1_ChartView, renEnHP1_LineSeries);
                }
            }
        }
    }

    Component {
        id: renEnHP2
        ChartView {
            id: renEnHP2_ChartView
            title: "Engine High Power 2 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renEnHP2_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renEnHP2_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renEnHP2_LineSeries
                axisX: renEnHP2_valuesAxisX
                axisY: renEnHP2_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadeEngineHP2
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renEnHP2_ChartView, renEnHP2_LineSeries);
                }
            }
        }
    }
    Component {
        id: renEnHP3
        ChartView {
            id: renEnHP3_ChartView
            title: "Engine High Power 3 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renEnHP3_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renEnHP3_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renEnHP3_LineSeries
                axisX: renEnHP3_valuesAxisX
                axisY: renEnHP3_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadeEngineHP3
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renEnHP3_ChartView, renEnHP3_LineSeries);
                }
            }
        }
    }
    Component {
        id: renEnHP4
        ChartView {
            id: renEnHP4_ChartView
            title: "Engine High Power 4 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renEnHP4_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renEnHP4_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renEnHP4_LineSeries
                axisX: renEnHP4_valuesAxisX
                axisY: renEnHP4_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadeEngineHP4
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renEnHP4_ChartView, renEnHP4_LineSeries);
                }
            }
        }
    }
    Component {
        id: renEnHP5
        ChartView {
            id: renEnHP5_ChartView
            title: "Engine High Power 5 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renEnHP5_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renEnHP5_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renEnHP5_LineSeries
                axisX: renEnHP5_valuesAxisX
                axisY: renEnHP5_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadeEngineHP5
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renEnHP5_ChartView, renEnHP5_LineSeries);
                }
            }
        }
    }
    Component {
        id: renEnHP6
        ChartView {
            id: renEnHP6_ChartView
            title: "Engine High Power 6 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renEnHP6_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renEnHP6_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renEnHP6_LineSeries
                axisX: renEnHP6_valuesAxisX
                axisY: renEnHP6_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadeEngineHP6
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renEnHP6_ChartView, renEnHP6_LineSeries);
                }
            }
        }
    }
    Component {
        id: renEnHP7
        ChartView {
            id: renEnHP7_ChartView
            title: "Engine High Power 7 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renEnHP7_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renEnHP7_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renEnHP7_LineSeries
                axisX: renEnHP7_valuesAxisX
                axisY: renEnHP7_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadeEngineHP7
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renEnHP7_ChartView, renEnHP7_LineSeries);
                }
            }
        }
    }
    Component {
        id: renEnHP8
        ChartView {
            id: renEnHP8_ChartView
            title: "Engine High Power 8 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renEnHP8_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renEnHP8_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renEnHP8_LineSeries
                axisX: renEnHP8_valuesAxisX
                axisY: renEnHP8_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadeEngineHP8
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renEnHP8_ChartView, renEnHP8_LineSeries);
                }
            }
        }
    }
    Component {
        id: renEnHP9
        ChartView {
            id: renEnHP9_ChartView
            title: "Engine High Power 9 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renEnHP9_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renEnHP9_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renEnHP9_LineSeries
                axisX: renEnHP9_valuesAxisX
                axisY: renEnHP9_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadeEngineHP9
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renEnHP9_ChartView, renEnHP9_LineSeries);
                }
            }
        }
    }
    Component {
        id: renEnHP10
        ChartView {
            id: renEnHP10_ChartView
            title: "Engine High Power 10 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renEnHP10_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renEnHP10_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renEnHP10_LineSeries
                axisX: renEnHP10_valuesAxisX
                axisY: renEnHP10_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadeEngineHP10
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renEnHP10_ChartView, renEnHP10_LineSeries);
                }
            }
        }
    }

    Component {
        id: renPropHP1
        ChartView {
            id: renPropHP1_ChartView
            title: "Prop High Power 10 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renPropHP1_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renPropHP1_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renPropHP1_LineSeries
                axisX: renPropHP1_valuesAxisX
                axisY: renPropHP1_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadePropHP1
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renPropHP1_ChartView, renPropHP1_LineSeries);
                }
            }
        }
    }

    Component {
        id: renPropHP2
        ChartView {
            id: renPropHP2_ChartView
            title: "Prop High Power 2 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renPropHP2_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renPropHP2_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renPropHP2_LineSeries
                axisX: renPropHP2_valuesAxisX
                axisY: renPropHP2_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadePropHP2
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renPropHP2_ChartView, renPropHP2_LineSeries);
                }
            }
        }
    }
    Component {
        id: renPropHP3
        ChartView {
            id: renPropHP3_ChartView
            title: "Prop High Power 3 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renPropHP3_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renPropHP3_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renPropHP3_LineSeries
                axisX: renPropHP3_valuesAxisX
                axisY: renPropHP3_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadePropHP3
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renPropHP3_ChartView, renPropHP3_LineSeries);
                }
            }
        }
    }
    Component {
        id: renPropHP4
        ChartView {
            id: renPropHP4_ChartView
            title: "Prop High Power 4 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renPropHP4_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renPropHP4_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renPropHP4_LineSeries
                axisX: renPropHP4_valuesAxisX
                axisY: renPropHP4_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadePropHP4
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renPropHP4_ChartView, renPropHP4_LineSeries);
                }
            }
        }
    }
    Component {
        id: renPropHP5
        ChartView {
            id: renPropHP5_ChartView
            title: "Prop High Power 5 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renPropHP5_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renPropHP5_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renPropHP5_LineSeries
                axisX: renPropHP5_valuesAxisX
                axisY: renPropHP5_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadePropHP5
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renPropHP5_ChartView, renPropHP5_LineSeries);
                }
            }
        }
    }
    Component {
        id: renPropHP6
        ChartView {
            id: renPropHP6_ChartView
            title: "Prop High Power 6 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renPropHP6_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renPropHP6_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renPropHP6_LineSeries
                axisX: renPropHP6_valuesAxisX
                axisY: renPropHP6_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadePropHP6
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renPropHP6_ChartView, renPropHP6_LineSeries);
                }
            }
        }
    }
    Component {
        id: renPropHP7
        ChartView {
            id: renPropHP7_ChartView
            title: "Prop High Power 7 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renPropHP7_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renPropHP7_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renPropHP7_LineSeries
                axisX: renPropHP7_valuesAxisX
                axisY: renPropHP7_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadePropHP7
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renPropHP7_ChartView, renPropHP7_LineSeries);
                }
            }
        }
    }
    Component {
        id: renPropHP8
        ChartView {
            id: renPropHP8_ChartView
            title: "Prop High Power 8 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renPropHP8_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renPropHP8_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renPropHP8_LineSeries
                axisX: renPropHP8_valuesAxisX
                axisY: renPropHP8_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadePropHP8
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renPropHP8_ChartView, renPropHP8_LineSeries);
                }
            }
        }
    }
    Component {
        id: renPropHP9
        ChartView {
            id: renPropHP9_ChartView
            title: "Prop High Power 9 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renPropHP9_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renPropHP9_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renPropHP9_LineSeries
                axisX: renPropHP9_valuesAxisX
                axisY: renPropHP9_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadePropHP9
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renPropHP9_ChartView, renPropHP9_LineSeries);
                }
            }
        }
    }
    Component {
        id: renPropHP10
        ChartView {
            id: renPropHP10_ChartView
            title: "Prop High Power 10 (Pressure (psi) vs. Time (s))"
            visible: true
            legend.visible: false
            antialiasing: true
            theme: ChartView.ChartThemeBlueCerulean
            ValuesAxis {
                id:  renPropHP10_valuesAxisX
                //titleText: "Time (s)"
                min: 0
                max: 10
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            ValuesAxis {
                id:  renPropHP10_valuesAxisY
                //titleText: "Pressure (psi)"
                min: 0
                max: 100
                tickCount: 5
                labelsColor: "white"
                color: "white"
                gridVisible: true
            }
            LineSeries {
                id: renPropHP10_LineSeries
                axisX: renPropHP10_valuesAxisX
                axisY: renPropHP10_valuesAxisY
            }
            Connections {
                target: frameHandler.HPSensors.RenegadePropHP10
                onUpdateGraphQML_outputValue: {
                    appendAndAdjustView(x_timestamp, y_outputValue, renPropHP10_ChartView, renPropHP10_LineSeries);
                }
            }
        }
    }

    ComboBox {
        id: comboBoxGraph
        width: 105
        height: 20
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.leftMargin: 10
        model: sensorModel

        onActivated: {
            loadGraph(index);

            console.log("comboBoxGraph selected index is:" + currentIndex)
            console.log("comboBoxGraph current index is:" + index)
            console.log("name of graph: " + model.get(currentIndex).name)


            //console.log(ValveEnums.ValveState.FIRE_COMMANDED)
            //console.log(ValveEnums.PyroState.FIRED)
            //console.log(frameHandler.sensors)
            //console.log(frameHandler.sensors.High_Press_1)
            //graphLoader.sourceComponent = comboBoxGraph

            // ChartView.visible = true
            // then set loader.soureComponent = ChartView
        }
    }
}
