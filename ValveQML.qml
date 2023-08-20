import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: 40
    height: width
    state: "0"

    property int valveState: 0 // use Qt.toString(1) to convert a number to string for state
    property color enableOff: "red"
    property color enableOn: "green"
    property color enableStale: "yellow"


    property alias valveRectItem: valveRect

    property alias valveLabelItem: valveLabel
    property string name: "VALVE"

    property alias valveImageItem: valveImage //source is set from main qml

    property alias valveMouseAreaItem: valveMouseArea

    property alias valveScaleUpItem: valveScaleUp
    property alias valveScaleDownItem: valveScaleDown

    signal someSignal
    // All these items below will pull value from the properties above, which are set my main.qml


    Rectangle {
        id: valveRect
        z: 0
        color: "red"
        radius: width
        anchors.fill: parent
        border.color: "black"
        border.width: 1.2

        //anchors.fill: parent
        gradient: Gradient {
            GradientStop {id: gradientStop1; position: 0.0; color: "yellow"}
            GradientStop {id: gradientStop2; position: 0.05; color: "orange"}
            GradientStop {id: gradientStop3; position: 0.5; color: "red"}
            GradientStop {id: gradientStop4; position: 0.95; color: "red"}
        }

        Popup { // shows more info about the valve. Connect this to a button to show the popup up
            id: valvePopup
            x: 65
            y: -10
            width: 75
            height: 100
            modal: false
            focus: true
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

            Column {

            }
        }
        Label {
            id: valveLabel
            width: 30
            height: 25
            z: 10
            text: root.name
            anchors.verticalCenter: parent.verticalCenter
            anchors.bottom: parent.bottom
            font.pointSize: 7
            anchors.bottomMargin: 15
            anchors.horizontalCenter: parent.horizontalCenter
        }

        MouseArea
        {
            id: valveMouseArea
            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true
            enabled: true
            onDoubleClicked:
            {
                console.log("State before click" + root.state)
                if (root.state === "0") //TESTING ONLY. this directly sets the state in the frontend using QML, which
                                        // interferes with the backend and makes it stop working
                {
                    root.state = "1"
                }
                else if (root.state === "1")
                {
                    root.state = "2"
                }
                else if (root.state === "2")
                {
                    root.state = "3"
                }
                else if (root.state === "3")
                {
                    root.state = "4"
                }
                console.log("State after click" + root.state)
            }
            onEntered:
            {
                valveScaleUp.start()
            }
            onExited:
            {
                valveScaleDown.start()

            }
        }
/*
        RotationAnimation {
            id: animation
            target: valveRect
            loops: Animation.Infinite
            from: valveRect.rotation
            to: 360
            direction: RotationAnimation.Clockwise
            duration: 1000
            running: true
        }
*/
        ScaleAnimator{
            id: valveScaleUp // when hover over the valve
            target: valveRect
            from: 1
            to: 1.15
            duration: 35 // Set this low
            running: false
        }

        ScaleAnimator{
            id: valveScaleDown // when cursor exits the valve
            target: valveRect
            from: 1.15
            to: 1
            duration: 35 // Set this low
            running: false
        }

    }

    Image {
        id: valveImage
        //source:
    }

    Label{

    }

    Button { // Kinda dangerous since its close to the valve, possible to misclick.
             // consider putting these in another window?
        id: button
        y: 45
        width: 41
        height: 15
        text: qsTr("info")
        //font: 10
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: -20
        onClicked:
        {
            valvePopup.open()
        }
    }



    states: [
        State {
            name: "0" // Closed
            PropertyChanges {
                target: gradientStop1;
                color: "yellow"
            }
            PropertyChanges {
                target: gradientStop2;
                color: "yellow"
            }
            PropertyChanges {
                target: gradientStop3;
                color: "red"
            }
            PropertyChanges {
                target: gradientStop4;
                color: "red"
            }
        },

        State {
            name: "1" // Open
            PropertyChanges {
                target: gradientStop1;
                color: "blue"
            }
            PropertyChanges {
                target: gradientStop2;
                color: "blue"
            }
            PropertyChanges {
                target: gradientStop3;
                color: "red"
            }
            PropertyChanges {
                target: gradientStop4;
                color: "red"
            }
        },

        State {
            name: "2" // FireCommanded
            PropertyChanges {
                target: gradientStop1;
                color: "green"
            }
            PropertyChanges {
                target: gradientStop2;
                color: "green"
            }
            PropertyChanges {
                target: gradientStop3;
                color: "red"
            }
            PropertyChanges {
                target: gradientStop4;
                color: "red"
            }
        },

        State {
            name: "3" // OpenCommanded
            PropertyChanges {
                target: gradientStop1;
                color: "pink"
            }
            PropertyChanges {
                target: gradientStop2;
                color: "pink"
            }
            PropertyChanges {
                target: gradientStop3;
                color: "red"
            }
            PropertyChanges {
                target: gradientStop4;
                color: "red"
            }
        },

        State {
            name: "4" // CloseCommanded
            PropertyChanges {
                target: gradientStop1;
                color: "black"
            }
            PropertyChanges {
                target: gradientStop2;
                color: "black"
            }
            PropertyChanges {
                target: gradientStop3;
                color: "red"
            }
            PropertyChanges {
                target: gradientStop4;
                color: "red"
            }
        }
    ]

    Component.onCompleted:
    {

    }
}
