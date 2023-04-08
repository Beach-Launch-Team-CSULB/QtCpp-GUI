import QtQuick
import QtQuick.Controls
// do qmlregistertypes for QML_ELEMENT
// scrollbars

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
            QtQML.invokeMethod(other, bbb.text, a,b);
        }
    }

    //Connections for connecting signals in C++ and Slots in
    //{
    //    target:
    //    on<SignalName>
    //}
}
