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

    Column {
        id: tankColumn_Page2
        width: 86
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 35
        anchors.topMargin: 60
        anchors.bottomMargin: 0
        anchors.leftMargin: 15

        Rectangle {
            id: tankCOPV_Page2
            width: 75
            height: 170
            color: "#eceab9"
            radius: 37.5
            z: -1
        }

        Rectangle {
            id: tankLox_Page2
            width: 75
            height: 170
            color: "#3c91f4"
            radius: 60
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

        Rectangle {
            id: tankFuel_Page2
            width: 75
            height: 170
            color: "#ad6e19"
            radius: 60
        }
    }

    Column {
        id: tankInfoColumn_Page2
        x: 159
        width: 560
        height: 650
        anchors.top: parent.top
        anchors.topMargin: 60
        spacing: 32

        Rectangle {
            id: tankCOPVRect_Page2
            height: 170
            color: "#00000000"
            border.color: "#eceab9"
            border.width: 2
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            Label {
                y: 5
                color: parent.border.color
                text: "COPV Tank"
                anchors.left: parent.left
                anchors.leftMargin: 5
                font.bold: true
                font.pointSize: 15
            }

            TankStateQML {
                id: tankCOPVStateQML
                x: -132
                width: 35
                height: 26
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: 40
                anchors.leftMargin: 10
                state: frameHandler.tankPressControllers.HiPressTankController.state.toString()
                fontSize: 20
            }

            Text {
                id: tankCOPVKp
                x: 10
                y: 77
                color: "#ffffff"
                text: "Kp : " + frameHandler.tankPressControllers.HiPressTankController.Kp
                font.pointSize: 15
            }

            Text {
                id: tankCOPVKi
                x: 80
                y: 77
                color: "#ffffff"
                text: "Ki : " + frameHandler.tankPressControllers.HiPressTankController.Ki
                font.pointSize: 15
            }

            Text {
                id: tankCOPVKd
                x: 150
                y: 77
                color: "#ffffff"
                text: "Kd : " + frameHandler.tankPressControllers.HiPressTankController.Kd
                font.pointSize: 15
            }

            Text {
                id: tankCOPVControllerThreshold
                x: 10
                y: 110
                color: "#ffffff"
                text: "Contr. Thres. : " + frameHandler.tankPressControllers.HiPressTankController.controllerThreshold
                font.pointSize: 15
            }

            Text {
                id: tankCOPVVentFailsafePressure
                x: 10
                y: 135
                color: "#ffffff"
                text: "Failsafe Press. : " + frameHandler.tankPressControllers.HiPressTankController.ventFailsafePressure + " psi"
                font.pointSize: 15
            }
            //valveMinEnergizeTime
            //valveMinDeEnergizeTime
            Text {
                id:tankCOPVvalveMinEnergizeTime
                x: 240
                y: 40
                color: "#ffffff"
                text: "valveMinEn : " + frameHandler.tankPressControllers.HiPressTankController.valveMinEnergizeTime + " ms"
                font.pointSize: 15
            }

            Text {
                id:tankCOPVvalveMinDeEnergizeTime
                x: 240
                y: 80
                color: "#ffffff"
                text: "valveMinDeEn : " + frameHandler.tankPressControllers.HiPressTankController.valveMinDeEnergizeTime + " ms"
                font.pointSize: 15
            }
        }

        Rectangle {
            id: tankLoxRect_Page2
            height: 170
            color: "#00000000"
            border.color: "#6fd3f4"
            border.width: 2
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            Label {
                y: 5
                color: parent.border.color
                text: "Lox Tank"
                anchors.left: parent.left
                anchors.leftMargin: 5
                font.bold: true
                font.pointSize: 15
            }

            TankStateQML {
                id: tankLoxStateQML
                x: -132
                width: 35
                height: 26
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: 40
                anchors.leftMargin: 10
                state: frameHandler.tankPressControllers.LoxTankController.state.toString()
                fontSize: 20
            }

            Text {
                id: tankLoxKp
                x: 10
                y: 77
                color: "#ffffff"
                text: "Kp : " + frameHandler.tankPressControllers.LoxTankController.Kp
                font.pointSize: 15
            }

            Text {
                id: tankLoxKi
                x: 80
                y: 77
                color: "#ffffff"
                text: "Ki : " + frameHandler.tankPressControllers.LoxTankController.Ki
                font.pointSize: 15
            }

            Text {
                id: tankLoxKd
                x: 150
                y: 77
                color: "#ffffff"
                text: "Kd : " + frameHandler.tankPressControllers.LoxTankController.Kd
                font.pointSize: 15
            }

            Text {
                id: tankLoxControllerThreshold
                x: 10
                y: 110
                color: "#ffffff"
                text: "Contr. Thres. : " + frameHandler.tankPressControllers.LoxTankController.controllerThreshold
                font.pointSize: 15
            }

            Text {
                id: tankLoxVentFailsafePressure
                x: 10
                y: 135
                color: "#ffffff"
                text: "Failsafe Press. : " + frameHandler.tankPressControllers.LoxTankController.ventFailsafePressure + " psi"
                font.pointSize: 15
            }

            Text {
                id:tankLoxvalveMinEnergizeTime
                x: 240
                y: 40
                color: "#ffffff"
                text: "valveMinEn : " + frameHandler.tankPressControllers.LoxTankController.valveMinEnergizeTime + " ms"
                font.pointSize: 15
            }

            Text {
                id:tankLoxvalveMinDeEnergizeTime
                x: 240
                y: 80
                color: "#ffffff"
                text: "valveMinDeEn : " + frameHandler.tankPressControllers.LoxTankController.valveMinDeEnergizeTime + " ms"
                font.pointSize: 15
            }
        }

        Rectangle {
            id: tankFuelRect_Page2
            height: 170
            color: "#00000000"
            border.color: "#ad6e19"
            border.width: 2
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            Label {
                y: 5
                color: parent.border.color
                text: "Fuel Tank"
                anchors.left: parent.left
                anchors.leftMargin: 5
                font.bold: true
                font.pointSize: 15
            }
            TankStateQML {
                id: tankFuelStateQML
                x: -132
                width: 35
                height: 26
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: 40
                anchors.leftMargin: 10
                state: frameHandler.tankPressControllers.FuelTankController.state.toString()
                fontSize: 20
            }

            Text {
                id: tankFuelKp
                x: 10
                y: 77
                color: "#ffffff"
                text: "Kp : " + frameHandler.tankPressControllers.FuelTankController.Kp
                font.pointSize: 15
            }

            Text {
                id: tankFuelKi
                x: 80
                y: 77
                color: "#ffffff"
                text: "Ki : " + frameHandler.tankPressControllers.FuelTankController.Ki
                font.pointSize: 15
            }

            Text {
                id: tankFuelKd
                x: 150
                y: 77
                color: "#ffffff"
                text: "Kd : " + frameHandler.tankPressControllers.FuelTankController.Kd
                font.pointSize: 15
            }

            Text {
                id: tankFuelControllerThreshold
                x: 10
                y: 110
                color: "#ffffff"
                text: "Contr. Thres. : " + frameHandler.tankPressControllers.FuelTankController.controllerThreshold
                font.pointSize: 15
            }

            Text {
                id: tankFuelVentFailsafePressure
                x: 10
                y: 135
                color: "#ffffff"
                text: "Failsafe Press. : " + frameHandler.tankPressControllers.FuelTankController.ventFailsafePressure + " psi"
                font.pointSize: 15
            }

            Text {
                id:tankFuelvalveMinEnergizeTime
                x: 240
                y: 40
                color: "#ffffff"
                text: "valveMinEn : " + frameHandler.tankPressControllers.FuelTankController.valveMinEnergizeTime + " ms"
                font.pointSize: 15
            }

            Text {
                id:tankFuelvalveMinDeEnergizeTime
                x: 240
                y: 80
                color: "#ffffff"
                text: "valveMinDeEn : " + frameHandler.tankPressControllers.FuelTankController.valveMinDeEnergizeTime + " ms"
                font.pointSize: 15
            }
        }
    }


}
