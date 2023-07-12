import QtQuick
import QtQuick.Controls
// do qmlregistertypes for QML_ELEMENT
// scrollbars
import FrameHandlerEnums
import SensorEnums
import HPSensorEnums
import ValveEnums
import NodeIDEnums
import AutosequenceEnums
import TankPressControllerEnums
// things need for button logic: commandStates/currGUIState, valves' states,

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr(appDir)


    Button {
        id: bbb
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

    //Connections { // do this to connect signal from C++ to slot in QML

    //}

    //Connections for connecting signals in C++ and Slots in
    //{
    //    target:
    //    on<SignalName>
    //}
}
