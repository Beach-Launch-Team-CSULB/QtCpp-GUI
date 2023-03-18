import QtQuick
import QtQuick.Controls
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
}
