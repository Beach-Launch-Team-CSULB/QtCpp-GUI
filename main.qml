import QtQuick
import QtQuick.Controls
// do qmlregistertypes for QML_ELEMENT
// scrollbars
//import FrameHandlerEnums 1.0
// things need for button logic: commandStates/currGUIState, valves' states,



Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


    Button {
        id: bbb
        text: "Click me"
        onClicked:
        {
            //console.log(FrameHandler.VehicleState.STANDBY);
            //console.log(FrameHandler.MissionState.STANDBY);
            //justAFrameHandler.connectCan();
            //frameHandler.connectCan();
            //QtQML.invokeMethod(other, bbb.text, a,b);
            if (frameHandler !== null && frameHandler !== undefined)
            {
                frameHandler.connectCan();
            }
            else
            {
                console.error("frameHandler is null or undefined");
                console.error(frameHandler === null); // maybe it's null because I did some weird shit in the cpp file
                console.error(frameHandler === undefined);
            }
            GNC.print();
        }
    }

    //Connections for connecting signals in C++ and Slots in
    //{
    //    target:
    //    on<SignalName>
    //}
}
