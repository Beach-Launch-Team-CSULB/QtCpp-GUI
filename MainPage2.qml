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
    //anchors.fill: parent
    //title: qsTr(appDir + " --- Theseus GUI - window 2")

    //Component.onCompleted: { // save measure
    //    while(lineSeriesPage2.count > 0)
    //    {
    //        lineSeriesPage2.remove(0);
    //    }
    //}

    function appendAndAdjustView(x, y, lineSeries, safeThreshold = 700, warningThreshold = 1000, criticalThreshold = 1200)    // member variables of the object linesSeries are passed by reference, so lineSeries.someMember should
                                            // affect the someMember variable of the original object
    {
        console.log("enter appendAndAdjustView()");
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
            chartViewPage2.titleColor = "white"
        }
        else if (safeThreshold <= y && y < warningThreshold) // && y < 1000
        {
            lineSeries.axisX.labelsColor = "orange"
            lineSeries.axisX.color = "orange"
            lineSeries.axisY.labelsColor = "orange"
            lineSeries.axisY.color = "orange"
            chartViewPage2.titleColor = "orange"
        }
        else if (warningThreshold <= y && y < criticalThreshold)
        {
            lineSeries.axisX.labelsColor = "red"
            lineSeries.axisX.color = "red"
            lineSeries.axisY.labelsColor = "red"
            lineSeries.axisY.color = "red"
            chartViewPage2.titleColor = "red"
        }
        else if (y >= criticalThreshold)
        {
            lineSeries.axisX.labelsColor = "pink"
            lineSeries.axisX.color = "pink"
            lineSeries.axisY.labelsColor = "pink"
            lineSeries.axisY.color = "pink"
            chartViewPage2.titleColor = "pink"
            // for Critical point use ternary operator for cool flashing a cool flashing effect
        }
    }


    //Connections {
    //    target: frameHandler.sensors.Lox_Tank_1
    //    onUpdateGraphQML_rawValue: {
    //        appendAndAdjustView(x_timestamp, y_rawValue, lineSeriesPage2); //lineSeriesPage2.yMin
    //        //appendAndAdjustView(x_timestamp, y_rawValue, lineSeriesPage3);
    //    }
    //}

    Button {
        id: page2butt
        x: 287
        y: 200
        z: 3
        width: 89
        height: 50
        text: "Click me"
        onClicked:
        {
            //chartViewPage2.visible ? chartViewPage2.visible = false : chartViewPage2.visible = true
            //lineSeriesPage2.append(5,7);
            appendAndAdjustView(500,700,lineSeriesPage2);
            //lineSeriesPage2.append(35,10);

            //valuesAxisX.min = 0;
            //valuesAxisX.max = 40;
            //lineSeriesPage2.axisX.min = 3;
            //lineSeriesPage2.axisX.max = 30;
            //lineSeriesPage2.remove(0); // do this + append + change the mins and maxes of the axes dynamically. Should do this
            // when the valueChanged() signals of the sensors are emitted
        }
    }

    GridView {

    }

    ChartView {
        id: chartViewPage2
        visible: true
        title: "Accurate Historical Data"
        anchors.fill: parent
        anchors.rightMargin: 655
        legend.visible: false
        antialiasing: true
        theme: ChartView.ChartThemeBlueCerulean

        ValuesAxis {
            id: valuesAxisX
            //titleText: "Time (s)"
            tickCount: 10
            labelsColor: "white"
            color: "white"
            gridVisible: true

        }
        ValuesAxis {
            id: valuesAxisY
            //titleText: "Pressure (psi)"
            tickCount: 10
            labelsColor: "white"
            color: "white"
            gridVisible: true


            //gridLineColor: "white"
            //minorGridVisible: true
            //minorGridLineColor: "pink"
            //shadesBorderColor: "blue"
        }

        LineSeries {
            id: lineSeriesPage2

            axisX: valuesAxisX
            axisY: valuesAxisY
            //useOpenGL: true

        }
    }

    ChartView {
        id: chartViewPage3
        x: 5
        y: 5
        visible: true
        anchors.fill: parent
        anchors.leftMargin: 895


        ValuesAxis {
            id: xAxis2
            tickCount: 10
            max: 20
            min: 0
                    }
        ValuesAxis {
            id: yAxis2
                        tickCount: 10
                        max: 20
                        min: 0
                    }
        LineSeries {
            id: lineSeriesPage3
            axisY: xAxis2
            axisX: yAxis2
        }
        antialiasing: true
        legend.visible: false
        title: "Accurate Historical Data"
        theme: ChartView.ChartThemeBlueCerulean
    }





    // DateTimeAxis is based on QDateTimes so we must convert our JavaScript dates to
    // milliseconds since epoch to make them match the DateTimeAxis values
    function toMsecsSinceEpoch(date) {
        var msecs = date.getTime();
        return msecs;
    }
}
