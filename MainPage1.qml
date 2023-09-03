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

//import QtQuick3D.Particles3D 6.4

Item {
    id: mainPage1
    width: 1550
    height: 735
    visible: true
    //anchors.fill: parent


    Shortcut{
        sequence: "Alt+Q" // abort
        onActivated:
        {
            if (abortButton.state === "off")
            {
                frameHandler.sendFrame(window.commandFrameID, (7).toString(16))
            }
            else if (abortButton.state === "on")
            {
                //frameHandler.sendFrame(window.commandFrameID, )
                //frameHandler.logger.outputLogMessage("Unabort not allowed. Go to vent!")
            }
        }
    }
    Shortcut{
        sequence: "Alt+W" // vent
        onActivated:
        {
            if (ventButton.state === "off")
            {
                frameHandler.sendFrame(window.commandFrameID, (9).toString(16));
            }
            else if (ventButton.state === "on")
            {
                //frameHandler.sendFrame(window.commandFrameID, (3).toString(16)); // enter standby state
            }
        }
    }
    Shortcut{
        sequence: "Alt+Z" // override
        onActivated:
        {
            if (offNominalButton.state === "off")
            {
                frameHandler.sendFrame(window.commandFrameID, (23).toString(16));
            }
            else if (offNominalButton.state === "on")
            {
                frameHandler.sendFrame(window.commandFrameID, (22).toString(16));
            }
        }
    }


    Component.onCompleted: {
        console.log(window.aaaaa)
    }

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
        y: 704
        width: 50
        height: 27

        sensorValue: frameHandler.sensors.Lox_Tank_1.rawValue.toFixed(2)
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ValveQML {
        id: hiPress
        x: 241
        y: 52

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
        x: 292
        y: 87

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
        x: 345
        y: 118

        valveID: frameHandler.valves.LDV.ID
        valveName: frameHandler.valves.LDV.name
        state: frameHandler.valves.LDV.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.LDV.commandOff
        valveCommandOn: frameHandler.valves.LDV.commandOn

    }


    ValveQML {
        id: loxVent
        x: 305
        y: 182

        valveID: frameHandler.valves.LV.ID
        valveName: frameHandler.valves.LV.name
        state: frameHandler.valves.LV.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.LV.commandOff
        valveCommandOn: frameHandler.valves.LV.commandOn
    }

    ValveQML {
        id: loxDomeReg
        x: 427
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
        x: 530
        y: 118
        valveID: frameHandler.valves.FDR.ID
        valveName: frameHandler.valves.FDR.name
        state: frameHandler.valves.FDR.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.FDR.commandOff
        valveCommandOn: frameHandler.valves.FDR.commandOn

    }


    ValveQML {
        id: fuelVent
        x: 649
        y: 182
        valveID: frameHandler.valves.FV.ID
        valveName: frameHandler.valves.FV.name
        state: frameHandler.valves.FV.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.FV.commandOff
        valveCommandOn: frameHandler.valves.FV.commandOn
    }


    ValveQML {
        id: fuelDomeVent
        x: 610
        y: 118
        valveID: frameHandler.valves.FDV.ID
        valveName: frameHandler.valves.FDV.name
        state: frameHandler.valves.FDV.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.FDV.commandOff
        valveCommandOn: frameHandler.valves.FDV.commandOn
    }



    ValveQML {
        id: loxMainValve
        y: 295
        anchors.horizontalCenterOffset: -48
        anchors.horizontalCenter: engineNozzleImage.horizontalCenter
        valveID: frameHandler.valves.LMV.ID
        valveName: frameHandler.valves.LMV.name
        state: frameHandler.valves.LMV.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.LMV.commandOff
        valveCommandOn: frameHandler.valves.LMV.commandOn
    }

    ValveQML {
        id: fuelMainValve
        y: 295
        anchors.horizontalCenterOffset: 48
        anchors.horizontalCenter: engineNozzleImage.horizontalCenter
        valveID: frameHandler.valves.FMV.ID
        valveName: frameHandler.valves.FMV.name
        state: frameHandler.valves.FMV.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.FMV.commandOff
        valveCommandOn: frameHandler.valves.FMV.commandOn
    }

    ValveQML {
        id: igniter1
        y: 367
        anchors.horizontalCenterOffset: -70
        anchors.horizontalCenter: engineNozzleImage.horizontalCenter
        valveID: frameHandler.valves.IGN1.ID
        valveName: frameHandler.valves.IGN1.name
        state: frameHandler.valves.IGN1.valveState.toString() // Set state here

        valveCommandOff: frameHandler.valves.IGN1.commandOff
        valveCommandOn: frameHandler.valves.IGN1.commandOn
    }

    ValveQML {
        id: igniter2
        y: 367
        anchors.horizontalCenterOffset: 70
        anchors.horizontalCenter: engineNozzleImage.horizontalCenter
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
        x: 256
        y: 515
        width: 89
        height: 50
        text: "Click me"
        onClicked:
        {
            //console.log(window.aaaaa)
            //window.aaaaa = "BBBBBBBBBBBBBBB"
            //console.log("ValveID: " + frameHandler.valves.HP.ID)
            /*
              */


            //console.log(FrameHandlerEnums.IN_SYNC)
            for (var sensor in frameHandler.sensors)
            {
                console.log(sensor)
            }
            console.log(frameHandler.sensors.High_Press_Fuel)

            //console.log(frameHandler.COMMAND_closeFuelMV)
            //console.log(frameHandler.COMMAND_closeFuelMV)
            //console.log(frameHandler.nodeSyncStatus === frameHandler.IN_SYNC)

            //console.log(frameHandler.nodeStatusRenegadeProp.toString());
            //console.log(frameHandler.nodeStatusRenegadeProp);
            //console.log(frameHandler.nodeStatusRenegadeEngine.toString());
            //console.log(frameHandler.nodeStatusRenegadeEngine);
            // Test AutosequenceButton


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

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////// SENSOR SECTION /////////////////////////////////////////////////

    Rectangle {
        id: mainValvePneumaticSensorRect
        x: 537
        y: 445
        width: 118
        height: 64
        color: "#00000000"
        border.color: "#7e0cf8"
        border.width: 2

        Label {
            id: mainValvePneumaticLabel
            y: 2
            color: "#9066d5"
            text: "MV Pneumatic"
            anchors.left: parent.left
            font.bold: true
            anchors.leftMargin: 5
            font.pointSize: 9
        }

        SensorQML {
            id: mainValvePneumaticSensor
            x: 5
            y: 25
            width: 50
            height: 35

            name: "MVP "
            safeColor: "white"
            sensorValue: frameHandler.sensors.MV_Pneumatic.convertedValue

            Connections
            {
                target: frameHandler.sensors.MV_Pneumatic
                onUpdateSensorQML_convertedValue:
                {
                    if (mainValvePneumaticSensor.sensorValue <= mainValvePneumaticSensor.safeThreshold )
                    {
                        mainValvePneumaticSensor.state = "safe";
                    }
                    if (mainValvePneumaticSensor.safeThreshold < mainValvePneumaticSensor.sensorValue && mainValvePneumaticSensor.sensorValue <= mainValvePneumaticSensor.warningThreshold )
                    {
                        mainValvePneumaticSensor.state = "warning";
                    }
                    if (mainValvePneumaticSensor.warningThreshold < mainValvePneumaticSensor.sensorValue && mainValvePneumaticSensor.sensorValue <= mainValvePneumaticSensor.criticalThreshold )
                    {
                        mainValvePneumaticSensor.state = "critical";
                    }
                    if (mainValvePneumaticSensor.criticalThreshold < mainValvePneumaticSensor.sensorValue)
                    {
                        mainValvePneumaticSensor.state = "RUNNN";
                    }
                }
            }
        }
    }

    Rectangle {
        id: highPressSensorRect
        x: 363
        y: 445
        width: 168
        height: 64
        color: "#00000000"
        border.color: "#eceab9"
        border.width: 2

        Label {
            id: highPressSensorLabel
            y: 2
            color: parent.border.color
            text: "High Press"
            anchors.left: parent.left
            font.bold: true
            anchors.leftMargin: 5
            font.pointSize: 9
        }

        SensorQML {
            id: highPressLoxSensor
            x: 5
            y: 20
            width: 50
            height: 35

            name: "*HiPress Lox  "
            safeColor: "white"
            sensorValue: frameHandler.sensors.High_Press_Lox.convertedValue

            Connections
            {
                target: frameHandler.sensors.High_Press_Lox
                onUpdateSensorQML_convertedValue:
                {
                    if (highPressLoxSensor.sensorValue <= highPressLoxSensor.safeThreshold )
                    {
                        highPressLoxSensor.state = "safe";
                    }
                    if (highPressLoxSensor.safeThreshold < highPressLoxSensor.sensorValue && highPressLoxSensor.sensorValue <= highPressLoxSensor.warningThreshold )
                    {
                        highPressLoxSensor.state = "warning";
                    }
                    if (highPressLoxSensor.warningThreshold < highPressLoxSensor.sensorValue && highPressLoxSensor.sensorValue <= highPressLoxSensor.criticalThreshold )
                    {
                        highPressLoxSensor.state = "critical";
                    }
                    if (highPressLoxSensor.criticalThreshold < highPressLoxSensor.sensorValue)
                    {
                        highPressLoxSensor.state = "RUNNN";
                    }
                }
            }
        }

        SensorQML {
            id: highPressFuelSensor
            x: 5
            y: 40
            width: 50
            height: 35

            name: "*HiPress Fuel "
            safeColor: "white"
            sensorValue: frameHandler.sensors.High_Press_Fuel.convertedValue

            Connections
            {
                target: frameHandler.sensors.High_Press_Fuel
                onUpdateSensorQML_convertedValue:
                {
                    if (highPressFuelSensor.sensorValue <= highPressFuelSensor.safeThreshold )
                    {
                        highPressFuelSensor.state = "safe";
                    }
                    if (highPressFuelSensor.safeThreshold < highPressFuelSensor.sensorValue && highPressFuelSensor.sensorValue <= highPressFuelSensor.warningThreshold )
                    {
                        highPressFuelSensor.state = "warning";
                    }
                    if (highPressFuelSensor.warningThreshold < highPressFuelSensor.sensorValue && highPressFuelSensor.sensorValue <= highPressFuelSensor.criticalThreshold )
                    {
                        highPressFuelSensor.state = "critical";
                    }
                    if (highPressFuelSensor.criticalThreshold < highPressFuelSensor.sensorValue)
                    {
                        highPressFuelSensor.state = "RUNNN";
                    }
                }
            }
        }
    }

    Rectangle {
        id: loxSensorRect
        x: 361
        y: 515
        width: 170
        height: 130
        color: "transparent"
        border.color: "#6fd3f4"
        border.width: 2

        Label {
            id: loxLabel
            y: 0
            color: parent.border.color
            text: "Lox"
            anchors.left: parent.left
            font.bold: true
            anchors.leftMargin: 5
            font.pointSize: 12
        }

        SensorQML {
            id: loxTankSensor1
            x: 5
            y: 25
            width: 50
            height: 35

            name: "*Lox Tank 1      "
            safeColor: "white"
            sensorValue: frameHandler.sensors.Lox_Tank_1.convertedValue

            Connections
            {
                target: frameHandler.sensors.Lox_Tank_1
                onUpdateSensorQML_convertedValue:
                {
                    if (loxTankSensor1.sensorValue <= loxTankSensor1.safeThreshold )
                    {
                        loxTankSensor1.state = "safe";
                    }
                    if (loxTankSensor1.safeThreshold < loxTankSensor1.sensorValue && loxTankSensor1.sensorValue <= loxTankSensor1.warningThreshold )
                    {
                        loxTankSensor1.state = "warning";
                    }
                    if (loxTankSensor1.warningThreshold < loxTankSensor1.sensorValue && loxTankSensor1.sensorValue <= loxTankSensor1.criticalThreshold )
                    {
                        loxTankSensor1.state = "critical";
                    }
                    if (loxTankSensor1.criticalThreshold < loxTankSensor1.sensorValue)
                    {
                        loxTankSensor1.state = "RUNNN";
                    }
                }
            }
        }

        SensorQML {
            id: loxTankSensor2

            x: 5
            y: 50
            width: 50
            height: 35

            name: "*Lox Tank 2      "
            safeColor: "white"
            sensorValue: frameHandler.sensors.Lox_Tank_2.convertedValue

            Connections {
                target: frameHandler.sensors.Lox_Tank_2
                onUpdateSensorQML_convertedValue: {
                    if (loxTankSensor2.sensorValue <= loxTankSensor2.safeThreshold )
                    {
                        loxTankSensor2.state = "safe";
                    }
                    if (loxTankSensor2.safeThreshold < loxTankSensor2.sensorValue && loxTankSensor2.sensorValue <= loxTankSensor2.warningThreshold )
                    {
                        loxTankSensor2.state = "warning";
                    }
                    if (loxTankSensor2.warningThreshold < loxTankSensor2.sensorValue && loxTankSensor2.sensorValue <= loxTankSensor2.criticalThreshold )
                    {
                        loxTankSensor2.state = "critical";
                    }
                    if (loxTankSensor2.criticalThreshold < loxTankSensor2.sensorValue)
                    {
                        loxTankSensor2.state = "RUNNN";
                    }
                }
            }
        }

        SensorQML {
            id: loxDomeRegSensor

            x: 5
            y: 75
            width: 50
            height: 35

            name: "Lox Dome Reg "
            safeColor: "white"
            sensorValue: frameHandler.sensors.Lox_Dome_Reg.convertedValue

            Connections {
                target: frameHandler.sensors.Lox_Dome_Reg
                onUpdateSensorQML_convertedValue: {
                    if (loxDomeRegSensor.sensorValue <= loxDomeRegSensor.safeThreshold )
                    {
                        loxDomeRegSensor.state = "safe";
                    }
                    if (loxDomeRegSensor.safeThreshold < loxDomeRegSensor.sensorValue && loxDomeRegSensor.sensorValue <= loxDomeRegSensor.warningThreshold )
                    {
                        loxDomeRegSensor.state = "warning";
                    }
                    if (loxDomeRegSensor.warningThreshold < loxDomeRegSensor.sensorValue && loxDomeRegSensor.sensorValue <= loxDomeRegSensor.criticalThreshold )
                    {
                        loxDomeRegSensor.state = "critical";
                    }
                    if (loxDomeRegSensor.criticalThreshold < loxDomeRegSensor.sensorValue)
                    {
                        loxDomeRegSensor.state = "RUNNN";
                    }
                }
            }
        }

        SensorQML {
            id: loxPropInlet

            x: 5
            y: 100
            width: 50
            height: 35

            name: "Lox Prop Inlet  "
            safeColor: "white"
            sensorValue: frameHandler.sensors.Lox_Prop_Inlet.convertedValue

            Connections {
                target: frameHandler.sensors.Lox_Prop_Inlet
                onUpdateSensorQML_convertedValue: {
                    if (loxPropInlet.sensorValue <= loxPropInlet.safeThreshold )
                    {
                        loxPropInlet.state = "safe";
                    }
                    if (loxPropInlet.safeThreshold < loxPropInlet.sensorValue && loxPropInlet.sensorValue <= loxPropInlet.warningThreshold )
                    {
                        loxPropInlet.state = "warning";
                    }
                    if (loxPropInlet.warningThreshold < loxPropInlet.sensorValue && loxPropInlet.sensorValue <= loxPropInlet.criticalThreshold )
                    {
                        loxPropInlet.state = "critical";
                    }
                    if (loxPropInlet.criticalThreshold < loxPropInlet.sensorValue)
                    {
                        loxPropInlet.state = "RUNNN";
                    }
                }
            }
        }
    }

    Rectangle {
        id: fuelSensorRect
        x: 542
        y: 515
        width: 170
        height: 130
        color: "#00000000"
        border.color: "#ad6e19"
        border.width: 2


        Label {
            id: fuelLabel
            color: "#ad6e19"
            text: "Fuel"
            anchors.left: parent.left
            font.bold: true
            font.pointSize: 12
            anchors.leftMargin: 5
        }

        SensorQML {
            id: fuelTankSensor1
            x: 5
            y: 25
            width: 50
            height: 35

            name: "Fuel Tank 1        "
            safeColor: "white"
            sensorValue: frameHandler.sensors.Fuel_Tank_1.convertedValue

            Connections
            {
                target: frameHandler.sensors.Fuel_Tank_1
                onUpdateSensorQML_convertedValue:
                {
                    if (fuelTankSensor1.sensorValue <= fuelTankSensor1.safeThreshold )
                    {
                        fuelTankSensor1.state = "safe";
                    }
                    if (fuelTankSensor1.safeThreshold < fuelTankSensor1.sensorValue && fuelTankSensor1.sensorValue <= fuelTankSensor1.warningThreshold )
                    {
                        fuelTankSensor1.state = "warning";
                    }
                    if (fuelTankSensor1.warningThreshold < fuelTankSensor1.sensorValue && fuelTankSensor1.sensorValue <= fuelTankSensor1.criticalThreshold )
                    {
                        fuelTankSensor1.state = "critical";
                    }
                    if (fuelTankSensor1.criticalThreshold < fuelTankSensor1.sensorValue)
                    {
                        fuelTankSensor1.state = "RUNNN";
                    }
                }
            }
        }

        SensorQML {
            id: fuelTankSensor2

            x: 5
            y: 50
            width: 50
            height: 35

            name: "Fuel Tank 2        "
            safeColor: "white"
            sensorValue: frameHandler.sensors.Fuel_Tank_2.convertedValue

            Connections {
                target: frameHandler.sensors.Fuel_Tank_2
                onUpdateSensorQML_convertedValue: {
                    if (fuelTankSensor2.sensorValue <= fuelTankSensor2.safeThreshold )
                    {
                        fuelTankSensor2.state = "safe";
                    }
                    if (fuelTankSensor2.safeThreshold < fuelTankSensor2.sensorValue && fuelTankSensor2.sensorValue <= fuelTankSensor2.warningThreshold )
                    {
                        fuelTankSensor2.state = "warning";
                    }
                    if (fuelTankSensor2.warningThreshold < fuelTankSensor2.sensorValue && fuelTankSensor2.sensorValue <= fuelTankSensor2.criticalThreshold )
                    {
                        fuelTankSensor2.state = "critical";
                    }
                    if (fuelTankSensor2.criticalThreshold < fuelTankSensor2.sensorValue)
                    {
                        fuelTankSensor2.state = "RUNNN";
                    }
                }
            }
        }

        SensorQML {
            id: fuelDomeRegSensor

            x: 5
            y: 75
            width: 50
            height: 35

            name: "Fuel Dome Reg "
            safeColor: "white"
            sensorValue: frameHandler.sensors.Fuel_Dome_Reg.convertedValue

            Connections {
                target: frameHandler.sensors.Fuel_Dome_Reg
                onUpdateSensorQML_convertedValue: {
                    if (fuelDomeRegSensor.sensorValue <= fuelDomeRegSensor.safeThreshold )
                    {
                        fuelDomeRegSensor.state = "safe";
                    }
                    if (fuelDomeRegSensor.safeThreshold < fuelDomeRegSensor.sensorValue && fuelDomeRegSensor.sensorValue <= fuelDomeRegSensor.warningThreshold )
                    {
                        fuelDomeRegSensor.state = "warning";
                    }
                    if (fuelDomeRegSensor.warningThreshold < fuelDomeRegSensor.sensorValue && fuelDomeRegSensor.sensorValue <= fuelDomeRegSensor.criticalThreshold )
                    {
                        fuelDomeRegSensor.state = "critical";
                    }
                    if (fuelDomeRegSensor.criticalThreshold < fuelDomeRegSensor.sensorValue)
                    {
                        fuelDomeRegSensor.state = "RUNNN";
                    }
                }
            }
        }

        SensorQML {
            id: fuelPropInletSensor

            x: 5
            y: 100
            width: 50
            height: 35

            name: "Fuel Prop Inlet  "
            safeColor: "white"
            sensorValue: frameHandler.sensors.Fuel_Prop_Inlet.convertedValue

            Connections {
                target: frameHandler.sensors.Fuel_Prop_Inlet
                onUpdateSensorQML_convertedValue: {
                    if (fuelPropInletSensor.sensorValue <= fuelPropInletSensor.safeThreshold )
                    {
                        fuelPropInletSensor.state = "safe";
                    }
                    if (fuelPropInletSensor.safeThreshold < fuelPropInletSensor.sensorValue && fuelPropInletSensor.sensorValue <= fuelPropInletSensor.warningThreshold )
                    {
                        fuelPropInletSensor.state = "warning";
                    }
                    if (fuelPropInletSensor.warningThreshold < fuelPropInletSensor.sensorValue && fuelPropInletSensor.sensorValue <= fuelPropInletSensor.criticalThreshold )
                    {
                        fuelPropInletSensor.state = "critical";
                    }
                    if (fuelPropInletSensor.criticalThreshold < fuelPropInletSensor.sensorValue)
                    {
                        fuelPropInletSensor.state = "RUNNN";
                    }
                }
            }
        }
    }

    Rectangle {
        id: miscellaneousSensorRect
        x: 360
        y: 650
        width: 352
        height: 70
        color: "#00000000"
        border.color: "#56f247"
        border.width: 2

        SensorQML {
            id: chamberSensor1

            x: 50
            y: 20
            width: 50
            height: 35

            name: "Chamber 1"
            safeColor: "white"
            sensorValue: frameHandler.sensors.Chamber_1.convertedValue

            Connections {
                target: frameHandler.sensors.Chamber_1
                onUpdateSensorQML_convertedValue: {
                    if (chamberSensor1.sensorValue <= chamberSensor1.safeThreshold )
                    {
                        chamberSensor1.state = "safe";
                    }
                    if (chamberSensor1.safeThreshold < chamberSensor1.sensorValue && chamberSensor1.sensorValue <= chamberSensor1.warningThreshold )
                    {
                        chamberSensor1.state = "warning";
                    }
                    if (chamberSensor1.warningThreshold < chamberSensor1.sensorValue && chamberSensor1.sensorValue <= chamberSensor1.criticalThreshold )
                    {
                        chamberSensor1.state = "critical";
                    }
                    if (chamberSensor1.criticalThreshold < chamberSensor1.sensorValue)
                    {
                        chamberSensor1.state = "RUNNN";
                    }
                }
            }
        }

        SensorQML {
            id: chamberSensor2

            x: 200
            y: 20
            width: 50
            height: 35

            name: "Chamber 2"
            safeColor: "white"
            sensorValue: frameHandler.sensors.Chamber_2.convertedValue

            Connections {
                target: frameHandler.sensors.Chamber_2
                onUpdateSensorQML_convertedValue: {
                    if (chamberSensor2.sensorValue <= chamberSensor2.safeThreshold )
                    {
                        chamberSensor2.state = "safe";
                    }
                    if (chamberSensor2.safeThreshold < chamberSensor2.sensorValue && chamberSensor2.sensorValue <= chamberSensor2.warningThreshold )
                    {
                        chamberSensor2.state = "warning";
                    }
                    if (chamberSensor2.warningThreshold < chamberSensor2.sensorValue && chamberSensor2.sensorValue <= chamberSensor2.criticalThreshold )
                    {
                        chamberSensor2.state = "critical";
                    }
                    if (chamberSensor2.criticalThreshold < chamberSensor2.sensorValue)
                    {
                        chamberSensor2.state = "RUNNN";
                    }
                }
            }
        }

        SensorQML {
            id: loadCellSensor1

            x: 25
            y: 40
            width: 50
            height: 35

            name: "LC 1"
            safeColor: "white"
            warningColor: "white"
            criticalColor: "white"
            sensorValue: frameHandler.sensors.Load_Cell_1.convertedValue
        }

        SensorQML {
            id: loadCellSensor2

            x: 125
            y: 40
            width: 50
            height: 35

            name: "LC 2"
            safeColor: "white"
            warningColor: "white"
            criticalColor: "white"
            sensorValue: frameHandler.sensors.Load_Cell_2.convertedValue
        }

        SensorQML {
            id: loadCellSensor3

            x: 225
            y: 40
            width: 50
            height: 35

            name: "LC 3"
            safeColor: "white"
            warningColor: "white"
            criticalColor: "white"
            sensorValue: frameHandler.sensors.Load_Cell_3.convertedValue
        }
    }

    /////////////////////////////////// SENSOR SECTION /////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////// AUTOSEQUENCE SECTION ///////////////////////////////////////////

    Frame {
        id: autosequenceFrame1
        x: 0
        width: 129
        height: 392
        anchors.top: parent.top
        anchors.topMargin: 115

        Column {
            id: autosequenceColumn1
            anchors.fill: parent
            anchors.bottomMargin: 0
            anchors.rightMargin: 0

            // REMINDER, ALL THESE AUTOSEQUENCE STUFF MIGHT CRASH THE PROGRAMM
            AutosequenceButton {
                id: highPressPressArmButton
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.leftMargin: 0

                buttonOffName: "Hi-Press \nPress Arm"
                buttonOnName: "Hi-Press \nPress Arm"

                vehicleStateEngineNode: frameHandler.nodeStatusRenegadeEngine.toString()
                vehicleStatePropNode: frameHandler.nodeStatusRenegadeProp.toString()
                vehicleStateOnFlag: FrameHandlerEnums.HI_PRESS_ARM// switch colors when the state matches this flag
                autosequenceMouseAreaForMain.onDoubleClicked: {
                    if (highPressPressArmButton.state === "off")
                    {
                        frameHandler.sendFrame(window.commandFrameID, (11).toString(16))
                    }
                    else if (highPressPressArmButton.state === "on")
                    {
                        //frameHandler.sendFrame(window.commandFrameID, )
                        frameHandler.logger.outputLogMessage("HIGH PRESS PRESS ARM NOT ALLOWED" + window.nextLine + "TO BE TURNED OFF!")
                    }
                }
            }

            AutosequenceButton {
                id: highPressPressurizeButton
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.leftMargin: 0

                buttonOffName: "Hi-Press \nPressurize"
                buttonOnName: "Hi-Press \nPressurize"
                vehicleStateEngineNode: frameHandler.nodeStatusRenegadeEngine.toString()
                vehicleStatePropNode: frameHandler.nodeStatusRenegadeProp.toString()
                vehicleStateOnFlag: FrameHandlerEnums.HI_PRESS_PRESSURIZED // switch colors when the state matches this flag
                autosequenceMouseAreaForMain.onDoubleClicked:{
                    if (highPressPressurizeButton.state === "off")
                    {
                        frameHandler.sendFrame(window.commandFrameID, (13).toString(16))
                    }
                    else if (highPressPressurizeButton.state === "on")
                    {
                        //frameHandler.sendFrame(window.commandFrameID, )
                        frameHandler.logger.outputLogMessage("HIGH PRESS PRESSURIZE NOT ALLOWED" + window.nextLine + "TO BE TURNED OFF!")
                    }
                }
            }

            AutosequenceButton {
                id: tankPressArmButton
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.leftMargin: 0

                buttonOffName: "Tank \nPress Arm"
                buttonOnName: "Tank \nPress Arm"
                vehicleStateEngineNode: frameHandler.nodeStatusRenegadeEngine.toString()
                vehicleStatePropNode: frameHandler.nodeStatusRenegadeProp.toString()
                vehicleStateOnFlag: "9" // switch colors when the state matches this flag
                autosequenceMouseAreaForMain.onDoubleClicked: {
                    if (tankPressArmButton.state === "off")
                    {
                        frameHandler.sendFrame(window.commandFrameID, (15).toString(16))
                    }
                    else if (tankPressArmButton.state === "on")
                    {
                        //frameHandler.sendFrame(window.commandFrameID, )
                        frameHandler.logger.outputLogMessage("TANK PRESS ARM NOT ALLOWED" + window.nextLine + "TO BE TURNED OFF!")
                    }
                }
            }

            AutosequenceButton {
                id: tankPressurizeButton
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.leftMargin: 0

                buttonOffName: "Tank \nPressurize"
                buttonOnName: "Tank \nPressurize"
                vehicleStateEngineNode: frameHandler.nodeStatusRenegadeEngine.toString()
                vehicleStatePropNode: frameHandler.nodeStatusRenegadeProp.toString()
                vehicleStateOnFlag: "10" // switch colors when the state matches this flag
                autosequenceMouseAreaForMain.onDoubleClicked: {
                    if (tankPressurizeButton.state === "off")
                    {
                        frameHandler.sendFrame(window.commandFrameID, (17).toString(16))
                    }
                    else if (tankPressurizeButton.state === "on")
                    {
                        //frameHandler.sendFrame(window.commandFrameID, )
                        frameHandler.logger.outputLogMessage("TANK PRESSURIZE NOT ALLOWED" + window.nextLine + "TO BE TURNED OFF!")
                    }
                }
            }
            AutosequenceButton {
                id: fireArmButton
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.leftMargin: 0

                buttonOffName: "Fire \nArm"
                buttonOnName: "Fire \nArm"
                vehicleStateEngineNode: frameHandler.nodeStatusRenegadeEngine.toString()
                vehicleStatePropNode: frameHandler.nodeStatusRenegadeProp.toString()
                vehicleStateOnFlag: "11" // switch colors when the state matches this flag
                autosequenceMouseAreaForMain.onDoubleClicked: {
                    if (fireArmButton.state === "off")
                    {
                        frameHandler.sendFrame(window.commandFrameID, (19).toString(16))
                    }
                    else if (fireArmButton.state === "on")
                    {
                        //frameHandler.sendFrame(window.commandFrameID, )
                        frameHandler.logger.outputLogMessage("TANK PRESSURIZE NOT ALLOWED" + window.nextLine + "TO BE TURNED OFF!")
                    }
                }
            }
            AutosequenceButton {
                id: fireButton
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.leftMargin: 0

                buttonOffName: "Fire"
                buttonOnName: "Fire"
                vehicleStateEngineNode: frameHandler.nodeStatusRenegadeEngine.toString()
                vehicleStatePropNode: frameHandler.nodeStatusRenegadeProp.toString()
                vehicleStateOnFlag: "12" // switch colors when the state matches this flag
                autosequenceMouseAreaForMain.onDoubleClicked: {
                    if (fireButton.state === "off")
                    {
                        frameHandler.sendFrame(window.commandFrameID, (21).toString(16))
                    }
                    else if (fireButton.state === "on")
                    {
                        //frameHandler.sendFrame(window.commandFrameID, )
                        if (true) // true for launch, false for static fire
                        {
                            frameHandler.logger.outputLogMessage("the rocket's gone sir")
                        }
                        else
                        {
                            frameHandler.logger.outputLogMessage("The rocket's fired!")
                        }
                    }
                }
            }

        }
    }

    Frame {
        id: autosequenceFrame2
        x: 129
        y: 230
        width: 89
        height: 150

        Label {
            id: label
            text: qsTr("Label")
        }

        Column {
            id: autosequenceColumn2
            anchors.fill: parent
            anchors.rightMargin: -11
            anchors.bottomMargin: -11
            spacing: 15
            AutosequenceButton {
                id: testButton
                height: 65
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.leftMargin: 0

                fontOnColorFromMain: "violet"
                fontOffColorFromMain: "violet"
                fontSize: 15

                buttonOffName: "TEST"
                buttonOnName: "TEST"
                vehicleStateEngineNode: frameHandler.nodeStatusRenegadeEngine.toString()
                vehicleStatePropNode: frameHandler.nodeStatusRenegadeProp.toString()
                vehicleStateOnFlag: "7" // switch colors when the state matches this flag

                autosequenceMouseAreaForMain.onDoubleClicked: {
                    if (testButton.state === "off")
                    {
                        frameHandler.sendFrame(window.commandFrameID, (5).toString(16));
                    }
                    else if (testButton.state === "on")
                    {
                        //frameHandler.sendFrame(window.commandFrameID, );
                        frameHandler.sendFrame(window.commandFrameID, (3).toString(16)); // enter standby state
                    }
                }
            }

            AutosequenceButton {
                id: offNominalButton
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.leftMargin: 0

                fontOnColorFromMain: "gold"
                fontOffColorFromMain: "red"
                buttonOnColorFromMain: "red"
                buttonOffColorFromMain: "black"
                fontSize: 15
                //isOverrideButton: true // make a separate qml file for override if there is too much deviation

                buttonOffName: "OVERRIDE \nOFF"
                buttonOnName: "OVERRIDE \nON!!!"

                vehicleStateEngineNode: frameHandler.nodeStatusRenegadeEngine.toString()
                vehicleStatePropNode: frameHandler.nodeStatusRenegadeProp.toString()
                vehicleStateOnFlag: "8" // switch colors when the state matches this flag
                autosequenceMouseAreaForMain.onDoubleClicked: {
                    if (offNominalButton.state === "off")
                    {
                        frameHandler.sendFrame(window.commandFrameID, (23).toString(16));
                    }
                    else if (offNominalButton.state === "on")
                    {
                        frameHandler.sendFrame(window.commandFrameID, (22).toString(16));
                    }
                }
            }

        }
    }

    Frame {
        id: autosequenceFrame3
        y: 414
        width: 200
        height: 90
        anchors.left: autosequenceFrame1.right
        anchors.bottom: autosequenceFrame1.bottom
        anchors.bottomMargin: 0
        anchors.leftMargin: 0

        Row {
            id: autosequenceRow3
            anchors.fill: parent

            AutosequenceButton {
                id: abortButton
                anchors.fill: parent
                anchors.rightMargin: -7
                anchors.bottomMargin: -9

                fontOnColorFromMain: "lightseagreen"
                fontOffColorFromMain: "white"
                buttonOnColorFromMain: "blue"
                buttonOffColorFromMain: "red"

                fontSize: 32
                buttonOffName: "ABORT"
                buttonOnName: "ABORTED..."
                vehicleStateEngineNode: frameHandler.nodeStatusRenegadeEngine.toString()
                vehicleStatePropNode: frameHandler.nodeStatusRenegadeProp.toString()
                vehicleStateOnFlag: "7" // switch colors when the state matches this flag
                autosequenceMouseAreaForMain.onDoubleClicked:
                {
                    if (abortButton.state === "off")
                    {
                        frameHandler.sendFrame(window.commandFrameID, (7).toString(16))
                    }
                    else if (abortButton.state === "on")
                    {
                        //frameHandler.sendFrame(window.commandFrameID, )
                        //frameHandler.logger.outputLogMessage("Unabort not allowed. Go to vent!")
                    }
                }
            }
        }
    }

    Frame {
        id: autosequenceFrame4
        x: 241
        y: 336
        width: 88
        height: 63

        AutosequenceButton {
            id: ventButton
            anchors.fill: parent
            anchors.rightMargin: -7
            anchors.bottomMargin: -7
            /*
            fontOnColorFromMain: "white"
            fontOffColorFromMain: "lightseagreen"
            buttonOnColorFromMain: "skyblue"
            buttonOffColorFromMain: "blue"
*/
            fontSize: 15

            buttonOffName: "Vent"
            buttonOnName: "Venting..."
            vehicleStateEngineNode: frameHandler.nodeStatusRenegadeEngine.toString()
            vehicleStatePropNode: frameHandler.nodeStatusRenegadeProp.toString()
            vehicleStateOnFlag: "7" // switch colors when the state matches this flag
            autosequenceMouseAreaForMain.onDoubleClicked: {
                if (ventButton.state === "off")
                {
                    frameHandler.sendFrame(window.commandFrameID, (9).toString(16));
                }
                else if (ventButton.state === "on")
                {
                    //frameHandler.logger.outputLogMessage("Exiting vent, entering standby state...")
                    //frameHandler.sendFrame(window.commandFrameID, (3).toString(16)); // enter standby state
                }
            }
        }
    }

    Frame {
        id: autosequenceFrame5
        width: 89
        height: 127
        anchors.left: fireStateRect.right
        anchors.top: fireStateRect.top
        anchors.topMargin: 0
        anchors.leftMargin: 0

        Column {
            id: column
            anchors.fill: parent
            anchors.rightMargin: -7
            anchors.bottomMargin: -9
            spacing: 5

            AutosequenceButton {
                id: passiveAutosequenceButton
                height: 57
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top

                anchors.leftMargin: 0
                anchors.rightMargin: 0
                anchors.topMargin: 0

                buttonOnName: "Passive"
                buttonOffName: "Passive"
                fontSize: 20

                vehicleStateEngineNode: frameHandler.nodeStatusRenegadeEngine.toString()
                vehicleStatePropNode: frameHandler.nodeStatusRenegadeProp.toString()
                vehicleStateOnFlag: "8" // switch colors when the state matches this flag
                autosequenceMouseAreaForMain.onDoubleClicked: {
                    if (passiveAutosequenceButton.state === "off")
                    {
                        frameHandler.logger.outputLogMessage("Note: this passive state can only" + window.nextLine + " be entered via the standby state");
                        frameHandler.sendFrame(window.commandFrameID, (1).toString(16));
                    }
                    else if ((passiveAutosequenceButton.state === "on"))
                    {
                        frameHandler.logger.outputLogMessage("Exiting passive, entering standby state...")
                        frameHandler.sendFrame(window.commandFrameID, (3).toString(16)); // enter standby state
                    }
                }
            }

            AutosequenceButton {
                id: standbyAutosequenceButton
                height: 60
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: passiveAutosequenceButton.bottom
                anchors.topMargin: 3
                anchors.rightMargin: 0
                anchors.leftMargin: 0

                buttonOnName: "Standby"
                buttonOffName: "Standby"
                fontSize: 20

                vehicleStateEngineNode: frameHandler.nodeStatusRenegadeEngine.toString()
                vehicleStatePropNode: frameHandler.nodeStatusRenegadeProp.toString()
                vehicleStateOnFlag: "7" // switch colors when the state matches this flag

                autosequenceMouseAreaForMain.onDoubleClicked: {
                    if (standbyAutosequenceButton.state === "off")
                    {
                        frameHandler.sendFrame(window.commandFrameID, (3).toString(16)); // enter standby state
                    }
                    else if ((standbyAutosequenceButton.state === "on"))
                    {
                        // Standby is the base state. It should be set off when it enters another state
                        frameHandler.logger.outputLogMessage("Standby is base state and can only go to" + window.nextLine + "a different state")
                    }
                }
            }
        }
    }
    /////////////////////////////////// AUTOSEQUENCE SECTION ///////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    VehicleStateQML {
        id: propNodeState
        x: 5
        y: 5

        nodeName: "Prop Node   "
        state: frameHandler.nodeStatusRenegadeProp.toString()
    }
    VehicleStateQML {
        id: engineNodeState
        x: 5
        y: 25

        nodeName: "Engine Node"
        state: frameHandler.nodeStatusRenegadeEngine.toString()
    }


    Frame {
        id: frame7
        x: 704
        y: 20
        width: 200
        height: 441

        Text {
            id: text1
            color: "#f8f7f7"
            text: "SOME OTHER STUFF"
            anchors.top: parent.top
            font.pixelSize: 15
            horizontalAlignment: Text.AlignHCenter
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: text2
            y: 307
            color: "#f8f7f7"
            text: qsTr("AUTOSEQUENCE TIMER")
            font.pixelSize: 12
            anchors.horizontalCenterOffset: 1
            anchors.horizontalCenter: parent.horizontalCenter
        }

        AutosequenceQML {
            id: autosequenceQML
            x: 15
            y: 329
        }
    }

    Rectangle {
        id: fireStateRect
        x: 0
        y: 58
        width: 129
        height: 57
        color: "#090909"
        radius: 2
        border.color: "#6bd08a1f"
        border.width: 2
    }



    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////// ART SECTION ////////////////////////////////////////////////////

    Rectangle {
        id: tankCOPV
        x: 481
        y: 0
        z:-1
        width: 28
        height: 50

        color: "#eceab9"
        radius: 15
    }
    Rectangle {
        id: tankLox
        x: 386
        y: 214
        width: 29
        height: 65
        color: "#3c91f4"
        radius: 15
        z: -1
    }

    Rectangle {
        id: tankFuel
        x: 581
        y: 214
        width: 29
        height: 65
        color: "#ad6e19"
        radius: 15
        z: -1
    }


    Rectangle {
        id: path1
        x: 493
        y: 40
        z:-1
        width: 5
        height: 80
        color: "#eceab9"
    }

    Rectangle {
        id: path2
        x: 279
        y: 70
        z:-1
        width: 214
        height: 5
        color: "#eceab9"
    }

    Rectangle {
        id: path3
        x: 310
        y: 70
        z: -1
        width: 5
        height: 20
        color: "#eceab9"
    }

    Rectangle {
        id: path4
        y: 93
        width: 200
        height: 5
        color: "#eceab9"
        anchors.horizontalCenterOffset: 2
        anchors.horizontalCenter: path1.horizontalCenter
        z: -1
    }

    Rectangle {
        id: path5
        x: 398
        y: 96
        width: 5
        height: 42
        color: "#eceab9"
        z: -2
    }

    Rectangle {
        id: path6
        x: 593
        y: 96
        width: 5
        height: 42
        color: "#eceab9"
        z: -2
    }

    Rectangle {
        id: path7
        x: 493
        y: 118
        width: 5
        height: 140
        color: "#7e0cf8"
        z: -1
    }


    Rectangle {
        id: path8
        width: 228
        height: 5
        color: "#7e0cf8"
        anchors.verticalCenter: fuelDomeVent.verticalCenter
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: path1.horizontalCenter
        z: -1
    }
    Rectangle {
        id: path9
        x: 398
        y: 135
        width: 5
        height: 80
        color: "#6fd3f4"
        z: -2
    }

    Rectangle {
        id: path10
        x: 398
        y: 275
        width: 5
        height: 45
        color: "#6fd3f4"
        z: -2
    }

    Rectangle {
        id: path11
        x: 402
        y: 315
        width: 82
        height: 5
        color: "#6fd3f4"
        z: -2
    }

    Rectangle {
        id: path12
        x: 593
        y: 135
        width: 5
        height: 80
        color: "#80700a"
        z: -2
    }

    Rectangle {
        id: path13
        x: 593
        y: 275
        width: 5
        height: 45
        color: "#80700a"
        z: -2
    }

    Rectangle {
        id: path14
        x: 504
        y: 315
        width: 94
        height: 5
        color: "#80700a"
        z: -2
    }


    /////////////////////////////////// ART SECTION ////////////////////////////////////////////////////
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
    Image {
        id: engineNozzleImage
        y: 337
        width: 45
        height: 100
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: path1.horizontalCenter

        source: window.fileAppDir + "/resources/GUI Images/Engine Clipart.png"
        fillMode: Image.PreserveAspectFit
    }

    Rectangle {
        id: path15
        x: 484
        y: 315
        width: 5
        height: 45
        color: "#6fd3f4"
        z: -2
    }

    Rectangle {
        id: path16
        x: 503
        y: 315
        width: 5
        height: 45
        color: "#80700a"
        z: -2
    }

    Rectangle {
        id: path17
        x: -4
        y: 253
        width: 99
        height: 5
        color: "#7e0cf8"
        anchors.horizontalCenterOffset: 0
        z: -1
        anchors.horizontalCenter: path1.horizontalCenter
    }

    Rectangle {
        id: path18
        x: 446
        y: 255
        width: 5
        height: 44
        color: "#7e0cf8"
        z: -1
    }

    Rectangle {
        id: path19
        x: 542
        y: 253
        width: 5
        height: 44
        color: "#7e0cf8"
        z: -1
    }

    Text {
        id: shortcutAbort
        x: 335
        y: 419
        width: 33
        height: 20
        color: "#ffffff"
        text: qsTr("Alt+Q")
        font.pixelSize: 12
    }

    Text {
        id: shortcutVent
        x: 335
        y: 358
        width: 33
        height: 20
        color: "#ffffff"
        text: qsTr("Alt+W")
        font.pixelSize: 12
    }

    Text {
        id: shortcutOffNominal
        x: 224
        y: 315
        width: 33
        height: 20
        color: "#ffffff"
        text: qsTr("Alt+Z")
        font.pixelSize: 12
    }

    Rectangle {
        id: path20
        x: 337
        y: 200
        width: 66
        height: 5
        color: "#6fd3f4"
        z: -2
    }

    Rectangle {
        id: path21
        x: 595
        y: 200
        width: 94
        height: 5
        color: "#80700a"
        z: -2
    }

    Rectangle {
        id: engineControllerRect
        x: 718
        y: 467
        width: 186
        height: 253
        color: "#00000000"
        border.color: "#56f247"
        border.width: 2

        Label {
            id: engineControllerLabel
            text: "Engine Controller 1"
            color: parent.border.color
            anchors.top: parent.top
            font.bold: true
            font.pointSize: 12
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
        }

        CountdownTimerQML {
            id: loxMainValveTimer
            x: 10
            y: 90

            name: "Lox MV  "
            fontColor: "#6fd3f4"
            timerValue: frameHandler.engineControllers.Engine1.loxMVAutosequenceActuation
        }

        CountdownTimerQML {
            id: fuelMainValveTimer
            x: 10
            y: 130

            name: "Fuel MV "
            fontColor: "#ad6e19"
            timerValue: frameHandler.engineControllers.Engine1.fuelMVAutosequenceActuation
        }

        CountdownTimerQML {
            id: igniterTimer1
            x: 10
            y: 170

            name: "IGN1      "
            fontColor: "red"
            timerValue: frameHandler.engineControllers.Engine1.igniter1Actuation
        }
        CountdownTimerQML {
            id: igniterTimer2
            x: 10
            y: 210

            name: "IGN2      "
            fontColor: "red"
            timerValue: frameHandler.engineControllers.Engine1.igniter2Actuation
        }

        EngineControllerStateQML {
            id: engineControllerStateQML
            x: 10
            anchors.top: parent.top
            anchors.topMargin: 45
            state: frameHandler.engineControllers.Engine1.state.toString()
        }

    }


}
