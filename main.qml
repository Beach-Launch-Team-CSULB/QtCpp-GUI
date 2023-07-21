import QtQuick
import QtQuick.Controls
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

// install the GUI on multiple laptops in case the gui on one laptop crashes and
// won't start due to memory issues
Window {
    id: window
    width: 1920//640
    height: 785 //480
    visible: true
    title: qsTr(appDir + " --- Theseus GUI")
    //color: "#c9ab65"
    //color: "#575757"
    //color: "#404040"
    color: "gray"
    Component.onCompleted: { // Top level signal and handler connections
        fuelDomeReg1.someSignal

    }

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "grey"}
            GradientStop { position: 0.05; color: "#575757"}
            GradientStop { position: 0.5; color: "#575757"}
            GradientStop { position: 0.95; color: "#575757"}
            GradientStop { position: 1; color: "grey"}
        }
    }


    ComboBox {
        id: comboBox1
        x: 1130
        y: 66
        width: 67
        height: 24

        //model: ["sensor 1","sensor 2", "sensor 3"]
        model: ListModel { // make a separate model using another .qml for this???
                 id: graphModel1
                 ListElement { text: "sensor 1" }
                 ListElement { text: "sensor 2" }
                 ListElement { text: "sensor 3" }
             }

        //delegate: ItemDelegate { //represents how elements are rendered
        //    width: parent.width
        //}

    }

    ComboBox {
        id: comboBox2
        x: 1130
        y: 189
        width: 67
        height: 23

        //model: ["sensor 1","sensor 2", "sensor 3"]
        model: ListModel { // make a separate model using another .qml for this???
                 id: graphModel2
                 ListElement { text: "sensor 1" }
                 ListElement { text: "sensor 2" }
                 ListElement { text: "sensor 3" }
             }

        //delegate: ItemDelegate { //represents how elements are rendered
        //    width: parent.width
        //}

    }

    ComboBox {
        id: comboBox3
        x: 1130
        y: 318
        width: 67
        height: 18

        //model: ["sensor 1","sensor 2", "sensor 3"]
        model: ListModel { // make a separate model using another .qml for this???
                 id: graphModel3
                 ListElement { text: "sensor 1" }
                 ListElement { text: "sensor 2" }
                 ListElement { text: "sensor 3" }
             }

        //delegate: ItemDelegate { //represents how elements are rendered
        //    width: parent.width
        //}

    }

    ComboBox {
        id: comboBox4
        x: 1362
        y: 66
        width: 67
        height: 24

        //model: ["sensor 1","sensor 2", "sensor 3"]
        model: ListModel { // make a separate model using another .qml for this???
                 id: graphModel4
                 ListElement { text: "sensor 1" }
                 ListElement { text: "sensor 2" }
                 ListElement { text: "sensor 3" }
             }

        //delegate: ItemDelegate { //represents how elements are rendered
        //    width: parent.width
        //}

    }

    ComboBox {
        id: comboBox5
        x: 1362
        y: 189
        width: 67
        height: 24

        //model: ["sensor 1","sensor 2", "sensor 3"]
        model: ListModel { // make a separate model using another .qml for this???
                 id: graphModel5
                 ListElement { text: "sensor 1" }
                 ListElement { text: "sensor 2" }
                 ListElement { text: "sensor 3" }
             }

        //delegate: ItemDelegate { //represents how elements are rendered
        //    width: parent.width
        //}

    }

    ComboBox {
        id: comboBox6
        x: 1362
        y: 315
        width: 67
        height: 24

        //model: ["sensor 1","sensor 2", "sensor 3"]
        model: ListModel { // make a separate model using another .qml for this???
                 id: graphModel6
                 ListElement { text: "sensor 1" }
                 ListElement { text: "sensor 2" }
                 ListElement { text: "sensor 3" }
             }

        //delegate: ItemDelegate { //represents how elements are rendered
        //    width: parent.width
        //}

    }

    SensorQML {

    }

    ValveQML {
        id: fuelDomeReg1
        x: 532
        y: 121
        state: frameHandler.valves.FDR.valveState.toString() // Set state here


        Component.onCompleted: {

        }
    }

    ValveQML {
        id: fuelDomeReg2
        x: 358
        y: 189
        state: frameHandler.valves.FDR.valveState.toString() // Set state here


        Component.onCompleted: {

        }
    }

    ValveQML {
        id: fuelDomeReg5
        x: 240
        y: 121
        state: frameHandler.valves.FDR.valveState.toString() // Set state here


        Component.onCompleted: {

        }
    }

    GraphQML{

    }

    Button {
        id: bbb
        x: 212
        y: 290
        width: 88
        height: 69
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

    TabBar { // Switch between different windows
        id: tabBar
        x: 413
        y: 0
        width: 333
        height: 60

        TabButton {
            id: tabButton
            height: 30
            text: qsTr("Tab Button")
        }

        TabButton {
            id: tabButton1
            height: 30
            text: qsTr("Tab Button")
        }

        TabButton {
            id: tabButton2 // Telemetry window??
            height: 30
            text: qsTr("Tab Button")
        }
    }

    Frame {
        id: frame1
        x: 0
        y: 515
        width: 288
        height: 270

        Label {
            id: label
            text: qsTr("Label")
        }
    }

    Frame {
        id: frame2
        x: 1089
        y: 676
        width: 215
        height: 109

        Label {
            id: label1
            text: qsTr("Label")
        }
    }

    Frame {
        id: frame3
        x: 1303
        y: 676
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
        height: 404

        Rectangle {
            id: rectangle
            color: "black"
            border.color: "#914040"
            border.width: 4
            anchors.fill: parent
            anchors.leftMargin: -6
            anchors.topMargin: 0
            anchors.rightMargin: -11
            anchors.bottomMargin: -11
        }
    }

    Frame {
        id: frame5
        x: 1089
        y: 571
        width: 215
        height: 104
        Label {
            text: qsTr("Label")
        }
    }

    Frame {
        id: frame6
        x: 1303
        y: 571
        width: 200
        height: 104
        Label {
            text: qsTr("Label")
        }
    }

    ToolBar {
        id: toolBar
        width: 360

        ToolButton {
            id: toolButton
            width: 60
            text: qsTr("Tool Button")
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: -6
            anchors.bottomMargin: 0
            anchors.topMargin: 0
        }

        ToolButton {
            id: toolButton1
            text: qsTr("Tool Button")
            anchors.left: toolButton.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 0
            anchors.bottomMargin: 0
            anchors.topMargin: 0
        }
    }

    //Connections { // do this to connect signal from C++ to slot in QML

    //}

    //Connections for connecting signals in C++ and Slots in
    //{
    //    target:
    //    on<SignalName>
    //}
}
