import QtQuick
import QtQuick.Controls
// do qmlregistertypes for QML_ELEMENT
// scrollbars

import FrameHandlerEnums 1.0
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
            console.log(bbb.text);
            //frameHandler.connectCan();
            GNC.print();
            console.log(GNC === null)
            console.log(GNC === undefined)
        }

    }

    //Connections for connecting signals in C++ and Slots in
    //{
    //    target:
    //    on<SignalName>
    //}
}
