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

    Component.onCompleted: {
        console.log(window.aaaaa)
    }
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
            defaultSensor: window.main_defaultGraphQMLSensor1

            Connections {
                target: graphQML1
                onComboBoxIndexChanged: {
                    window.main_defaultGraphQMLSensor1 = index
                }
            }

            //width: 200
            //height: 200
        }
        GraphQML {
            id: graphQML2
            defaultSensor: window.main_defaultGraphQMLSensor2

            Connections {
                target: graphQML2
                onComboBoxIndexChanged: {
                    window.main_defaultGraphQMLSensor2 = index
                }
            }
            //width: 200
            //height: 200
        }
        GraphQML {
            id: graphQML3
            defaultSensor: window.main_defaultGraphQMLSensor3

            Connections {
                target: graphQML3
                onComboBoxIndexChanged: {
                    window.main_defaultGraphQMLSensor3 = index
                }
            }
            //width: 200
            //height: 200
        }
        GraphQML {
            id: graphQML4
            defaultSensor: window.main_defaultGraphQMLSensor4


            Connections {
                target: graphQML4
                onComboBoxIndexChanged: {
                    window.main_defaultGraphQMLSensor4 = index
                }
            }
            //width: 200
            //height: 200
        }
        GraphQML {
            id: graphQML5
            defaultSensor: window.main_defaultGraphQMLSensor5

            Connections {
                target: graphQML5
                onComboBoxIndexChanged: {
                    window.main_defaultGraphQMLSensor5 = index
                }
            }
            //width: 200
            //height: 200
        }
        GraphQML {
            id: graphQML6
            defaultSensor: window.main_defaultGraphQMLSensor6

            Connections {
                target: graphQML6
                onComboBoxIndexChanged: {
                    window.main_defaultGraphQMLSensor6 = index
                }
            }
            //width: 200
            //height: 200
        }


    }

    SensorQML {
        x: 916
        y: 685
        width: 50
        height: 50
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ValveQML {
        id: hiPress
        x: 280
        y: 40

        valveID: frameHandler.valves.HP.ID
        valveName: frameHandler.valves.HP.name
        state: frameHandler.valves.HP.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.HP.commandOff
        valveCommandOn: frameHandler.valves.HP.commandOn



        Component.onCompleted: {

        }
    }

    ValveQML {
        id: hiPressVent
        x: 331
        y: 75

        valveID: frameHandler.valves.HPV.ID
        valveName: frameHandler.valves.HPV.name
        state: frameHandler.valves.HPV.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.HPV.commandOff
        valveCommandOn: frameHandler.valves.HPV.commandOn


        Component.onCompleted: {

        }
    }

    ValveQML {
        id: loxDomeVent
        x: 384
        y: 118

        valveID: frameHandler.valves.LDV.ID
        valveName: frameHandler.valves.LDV.name
        state: frameHandler.valves.LDV.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.LDV.commandOff
        valveCommandOn: frameHandler.valves.LDV.commandOn
    }


    ValveQML {
        id: loxVent
        x: 431
        y: 182

        valveID: frameHandler.valves.LV.ID
        valveName: frameHandler.valves.LV.name
        state: frameHandler.valves.LV.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.LV.commandOff
        valveCommandOn: frameHandler.valves.LV.commandOn
    }

    ValveQML {
        id: loxDomeReg
        x: 466
        y: 118
        valveID: frameHandler.valves.LDR.ID
        valveName: frameHandler.valves.LDR.name
        state: frameHandler.valves.LDR.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.LDR.commandOff
        valveCommandOn: frameHandler.valves.LDR.commandOn


        Component.onCompleted: {

        }
    }


    ValveQML {
        id: fuelDomeReg
        x: 569
        y: 118
        valveID: frameHandler.valves.FDR.ID
        valveName: frameHandler.valves.FDR.name
        state: frameHandler.valves.FDR.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.FDR.commandOff
        valveCommandOn: frameHandler.valves.FDR.commandOn
    }


    ValveQML {
        id: fuelVent
        x: 609
        y: 182
        valveID: frameHandler.valves.FV.ID
        valveName: frameHandler.valves.FV.name
        state: frameHandler.valves.FV.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.FV.commandOff
        valveCommandOn: frameHandler.valves.FV.commandOn
    }


    ValveQML {
        id: fuelDomeVent
        x: 654
        y: 118
        valveID: frameHandler.valves.FDV.ID
        valveName: frameHandler.valves.FDV.name
        state: frameHandler.valves.FDV.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.FDV.commandOff
        valveCommandOn: frameHandler.valves.FDV.commandOn
    }



    ValveQML {
        id: loxMainValve
        x: 440
        y: 295
        valveID: frameHandler.valves.LMV.ID
        valveName: frameHandler.valves.LMV.name
        state: frameHandler.valves.LMV.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.LMV.commandOff
        valveCommandOn: frameHandler.valves.LMV.commandOn
    }

    ValveQML {
        id: fuelMainValve
        x: 580
        y: 295
        valveID: frameHandler.valves.FMV.ID
        valveName: frameHandler.valves.FMV.name
        state: frameHandler.valves.FMV.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.FMV.commandOff
        valveCommandOn: frameHandler.valves.FMV.commandOn
    }

    ValveQML {
        id: igniter1
        x: 440
        y: 367
        valveID: frameHandler.valves.IGN1.ID
        valveName: frameHandler.valves.IGN1.name
        state: frameHandler.valves.IGN1.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.IGN1.commandOff
        valveCommandOn: frameHandler.valves.IGN1.commandOn
    }

    ValveQML {
        id: igniter2
        x: 580
        y: 367
        valveID: frameHandler.valves.IGN2.ID
        valveName: frameHandler.valves.IGN2.name
        state: frameHandler.valves.IGN2.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.IGN2.commandOff
        valveCommandOn: frameHandler.valves.IGN2.commandOn
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
            //console.log(window.aaaaa)
            //window.aaaaa = "BBBBBBBBBBBBBBB"

            console.log("ValveID: " + frameHandler.valves.HP.ID)

            //            console.log(ValveEnums.ValveState.FIRE_COMMANDED)
            //            console.log(ValveEnums.PyroState.FIRED)
            //            console.log(frameHandler.sensors)

            //            console.log(frameHandler.tankPressControllers.HiPressTankController)
            //            console.log(frameHandler.tankPressControllers.HiPressTankController.ventFailsafePressure)
            //            console.log(TankPressControllerEnums.OFF_NOMINAL_PASSTHROUGH)
            //            console.log(frameHandler.sendFrame(1,"1Y9b"));
            //            console.log(frameHandler.engineControllers.Engine1)
            console.log(frameHandler.logger.outputLogMessage("from QML"))
            //pageLoader.source = "MainPage1.qml"

            //TEST COMMIT 2
            //window.color = "#4c5169"

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
        x: 129
        y: 380
        width: 159
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
        x: 0
        width: 129
        anchors.top: parent.top
        anchors.bottom: frame1.bottom
        anchors.topMargin: 115
        anchors.bottomMargin: 0

        Column {
            id: column
            anchors.fill: parent
            anchors.bottomMargin: 0
            anchors.rightMargin: 0

            AutosequenceButton {
                id: autosequenceButton
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.leftMargin: 0
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

    Frame {
        id: frame7
        x: 704
        y: 20
        width: 200
        height: 441

        Text {
            id: text1
            x: 27
            y: 168
            color: "#f8f7f7"
            text: qsTr("STATES AND NODES STUFF")
            font.pixelSize: 12
        }

        Text {
            id: text2
            x: 27
            y: 362
            color: "#f8f7f7"
            text: qsTr("AUTOSEQUENCE TIMER")
            font.pixelSize: 12
        }
    }

    Frame {
        id: frame8
        x: 504
        y: 20
        width: 171
        height: 60

        Text {
            id: text3
            x: 43
            y: 21
            color: "#fbfbfb"
            text: qsTr("High Press Stuff")
            font.pixelSize: 12
        }
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
