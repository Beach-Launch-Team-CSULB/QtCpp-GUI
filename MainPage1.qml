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
    width: 1535
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

    // do a GridView for GraphQML.qml
    ComboBox {
        id: comboBox1
        x: 1048
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

        onAccepted: {
            // display sensor according to index
        }

        //delegate: ItemDelegate { //represents how elements are rendered
        //    width: parent.width
        //}

    }

    ComboBox {
        id: comboBox2
        x: 1048
        y: 190
        width: 67
        height: 23

        //model: ["sensor 1","sensor 2", "sensor 3"]
        model: ListModel { // make a separate model using another .qml for this???
                 id: graphModel2
                 ListElement { text: "sensor 1" }
                 ListElement { text: "sensor 2" }
                 ListElement { text: "sensor 3" }
             }

        onAccepted: {
            // display sensor according to index
        }

        //delegate: ItemDelegate { //represents how elements are rendered
        //    width: parent.width
        //}

    }

    ListModel {

    }

    ComboBox {
        id: comboBox3
        x: 1048
        y: 321
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
        x: 1303
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
        x: 1303
        y: 190
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
        x: 1303
        y: 316
        width: 67
        height: 24

        //model: ["sensor 1","sensor 2", "sensor 3"]
        model: ListModel { // make a separate model using another .qml for this???
                 id: graphModel6
                 ListElement { text: "sensor 1" }
                 ListElement { text: "sensor 2" }
                 ListElement { text: "sensor 3" }
             }

        currentIndex: 1

        onAccepted: {
            // display sensor according to index
        }

        //delegate: ItemDelegate { //represents how elements are rendered
        //    width: parent.width
        //}

    }

    SensorQML {

    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ValveQML {
        id: fuelDomeReg1
        x: 740
        y: 88
        state: frameHandler.valves.FDR.valveState.toString() // Set state here


        Component.onCompleted: {

        }
    }

    ValveQML {
        id: fuelDomeReg2
        x: 500
        y: 198
        state: frameHandler.valves.FDR.valveState.toString() // Set state here


        Component.onCompleted: {

        }
    }

    ValveQML {
        id: fuelDomeReg5
        x: 817
        y: 39
        state: frameHandler.valves.FDR.valveState.toString() // Set state here


        Component.onCompleted: {

        }
    }


    ValveQML {
        id: valveQML
        x: 662
        y: 197
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML1
        x: 817
        y: 198
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML2
        x: 346
        y: 198
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML3
        x: 408
        y: 279
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML4
        x: 787
        y: 279
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML5
        x: 481
        y: 389
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML6
        x: 683
        y: 389
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML7
        x: 500
        y: 653
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }

    ValveQML {
        id: valveQML8
        x: 668
        y: 653
        state: frameHandler.valves.FDR.valveState.toString() // Set state here
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    GraphQML{

    }

    Connections {
        target: frameHandler.logger
        onLogMessageOutput: {
            console.log(message) // do textArea.append shit,
                                 // scrollView.contentItem.contentY = asdasdds - asdasdasd;
        }
    }

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
            console.log(frameHandler.logger)
            console.log(logger)
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
        y: 515
        width: 288
        height: 140

        Label {
            id: label
            text: qsTr("Label")
        }
    }

    Frame {
        id: frame2
        x: 943
        y: 618
        width: 215
        height: 109

        Label {
            id: label1
            text: qsTr("Label")
        }
    }

    Frame {
        id: frame3
        x: 1158
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

            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0.9; color: "white"}
                GradientStop { position: 0.5; color: "black"}
            }
        }
    }

    Frame {
        id: frame5
        x: 943
        y: 515
        width: 215
        height: 104
        Label {
            text: qsTr("Label")
        }
    }

    Frame {
        id: frame6
        x: 1158
        y: 515
        width: 200
        height: 104
        Label {
            text: qsTr("Label")
        }
    }

    Rectangle {
        id: rectangle1
        x: 599
        y: 113
        width: 4
        height: 200
        color: "#d71818"
    }
    
    ScrollView {
        id: scrollView
        visible: true
        clip: false
        x: 943
        y: 389
        width: 421
        height: 98
        

    }
    Label {
        id: label3
        y: -16
        z: 1
        width: 81
        height: 16
        visible: true
        text: qsTr("Log Messages")
        anchors.left: scrollView.left
        anchors.bottom: scrollView.top
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
    }

    Rectangle {
        id: rectangle2
        y: 373
        width: 308
        height: 16
        color: "#ffffff"
        anchors.left: scrollView.left
        anchors.bottom: scrollView.top
        anchors.leftMargin: 0
        anchors.bottomMargin: 0
    }

    //Connections { // do this to connect signal from C++ to slot in QML

    //}

    //Connections for connecting signals in C++ and Slots in
    //{
    //    target:
    //    on<SignalName>
    //}
}
