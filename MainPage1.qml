import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts

// scrollbars
import FrameHandlerEnums
import SensorEnums
import HPSensorEnums
import ValveEnums
import NodeIDEnums
import AutosequenceEnums
import TankPressControllerEnums
import EngineControllerEnums
// things need for button logic: commandStates/currGUIState, valves' states,


// for now, just make a connectCAN and disconnectCAN button, and have everything display in the main window

// Do TableView at some point (displaying can frames is one example)

// install the GUI on multiple laptops in case the gui on one laptop crashes and
// won't start due to memory issues

// for autosequencing, do a ListElement with column layout?

import QtQuick3D.Particles3D 6.4

Item {
    id: mainPage1
    width: 1550
    height: 735
    visible: true
    //anchors.fill: parent
/*
    Rectangle{
        id: testRect1
        width: 200
        height: 200
        color: "#cb5555"
        anchors {
        }

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Text{
            id: testText1
            text: "Page1"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
*/

    // do a Grid for GraphQML.qml

    Grid {
        id: graphGrid
        x: 910
        y: 20
        width: 610
        height: 610

        spacing: 5
        rows: 3
        columns: 2

        GraphQML {
            id: graphQML1
            defaultSensor: 5
            //width: 200
            //height: 200
        }
        GraphQML {
            id: graphQML2
            defaultSensor: 6
            //width: 200
            //height: 200
        }
        GraphQML {
            id: graphQML3
            defaultSensor: 3
            //width: 200
            //height: 200
        }
        GraphQML {
            id: graphQML4
            defaultSensor: 4
            //width: 200
            //height: 200
        }
        GraphQML {
            id: graphQML5
            defaultSensor: 11
            //width: 200
            //height: 200
        }
        GraphQML {
            id: graphQML6
            defaultSensor: 12
            //width: 200
            //height: 200
        }


    }

    SensorQML {
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ValveQML {
        id: fuelDomeReg1
        x: 331
        y: 75
        state: frameHandler.valves.FDR.valveState.toString() // Set state here


        Component.onCompleted: {

        }
    }

    ValveQML {
        id: fuelDomeReg2
        x: 466
        y: 118
        state: frameHandler.valves.FDR.valveState.toString() // Set state here


        Component.onCompleted: {

        }
    }

    ValveQML {
        id: fuelDomeReg5
        x: 280
        y: 40
        state: frameHandler.valves.FDR.valveState.toString() // Set state here


        Component.onCompleted: {

        }
    }


    ValveQML {
        id: valveQML
        x: 569
        y: 118
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML1
        x: 654
        y: 118
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML2
        x: 384
        y: 118
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML3
        x: 431
        y: 182
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML4
        x: 609
        y: 182
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML5
        x: 466
        y: 295
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML6
        x: 580
        y: 299
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML7
        x: 633
        y: 348
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML8
        x: 633
        y: 417
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //GraphQML{

    //}

    Button {
        id: bbb
        x: 129
        y: 113
        width: 89
        height: 50
        text: "Click me"
        onClicked:
        {
            console.log(ValveEnums.ValveState.FIRE_COMMANDED)
            console.log(ValveEnums.PyroState.FIRED)
            console.log(frameHandler.sensors)
            console.log(frameHandler.sensors.High_Press_1)
            console.log(frameHandler.sensors.High_Press_1.rawValue)
            console.log(frameHandler.sensors.High_Press_1.convertedValue)
            console.log(frameHandler.tankPressControllers.HiPressTankController)
            console.log(frameHandler.tankPressControllers.HiPressTankController.ventFailsafePressure)
            console.log(TankPressControllerEnums.OFF_NOMINAL_PASSTHROUGH)
            console.log(frameHandler.sendFrame(1,"1Y9b"));
            console.log(frameHandler.engineControllers.Engine1)
            console.log(frameHandler.logger.outputLogMessage("from QML"))
            //pageLoader.source = "MainPage1.qml"

            //TEST COMMIT 2
            //window.color = "#4c5169"
            //console.log(frameHandler.sensors.High_Press_1.)

            //console.log(frameHandler.sensors.value("HAHA"));
            //frameHandler.connectCan()
            //console.log("frameHandler is NULL " + (frameHandler === null))
            //console.log("frameHandler is undefined " + (frameHandler === undefined))
            //GNC.print()
            //console.log("GNC is NULL " + (GNC === null))
            //console.log("GNC is undefined " + (GNC === undefined))

        }
    }

    Frame {
        id: frame
        x: 0
        y: 64
        width: 267
        height: 51
    }



    Frame {
        id: frame1
        x: 0
        y: 380
        width: 288
        height: 126

        Label {
            id: label
            text: qsTr("Label")
        }
    }

    Frame {
        id: frame2
        x: 370
        y: 515
        width: 215
        height: 104

        Label {
            id: label1
            text: qsTr("Label")
        }
    }

    Frame {
        id: frame3
        x: 370
        y: 618
        width: 200
        height: 109

        Label {
            id: label2
            text: qsTr("Label")
        }
    }

    Frame {
        id: frame4
        x: 5
        y: 113
        width: 124
        height: 226

        Rectangle {
            id: rectangle
            color: "black"
            border.color: "#914040"
            border.width: 4
            anchors.fill: parent
            anchors.leftMargin: -6
            anchors.topMargin: 0
            anchors.rightMargin: -11
            anchors.bottomMargin: -51

            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0.9; color: "white"}
                GradientStop { position: 0.5; color: "black"}
            }
        }
    }

    Frame {
        id: frame5
        x: 585
        y: 515
        width: 215
        height: 104
        Label {
            text: qsTr("Label")
        }
    }

    Frame {
        id: frame6
        x: 569
        y: 618
        width: 200
        height: 104
        Label {
            text: qsTr("Label")
        }
    }

    Rectangle {
        id: rectangle1
        x: 528
        y: 113
        width: 4
        height: 200
        color: "#d71818"
    }

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


    //Connections { // do this to connect signal from C++ to slot in QML

    //}

    //Connections for connecting signals in C++ and Slots in
    //{
    //    target:
    //    on<SignalName>
    //}
}
