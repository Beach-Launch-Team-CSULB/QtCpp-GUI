import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: 40
    height: width

    property int valveState: 0 // use Qt.toString(1) to convert a number to string for state
    property color enableOff: "red"
    property color enableOn: "green"
    property color enableStale: "yellow"

    property int fontSize: 9

    property string valveName: "VALVE"
    property int valveID: 0

    property int valveCommandOff: 0 // Convert to hex, then from hex convert to string.
    property int valveCommandOn: 0 // The extra step could be cut if the conversion to hex results in a string


    property alias valveRectItem: valveRect

    property alias valveLabelItem: valveLabel


    property alias valveImageItem: valveImage //source is set from main qml

    property alias valveMouseAreaForMain: valveMouseArea

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
        border.color: "white"
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
            text: root.valveName
            anchors.verticalCenter: parent.verticalCenter
            anchors.bottom: parent.bottom
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: fontSize
            anchors.bottomMargin: 15
            anchors.horizontalCenter: parent.horizontalCenter
        }

        MouseArea
        {
            id: valveMouseArea // use an alias to expose this to main to handle the doubleClicked signal there. Send on/off commands during offNominal
            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true
            enabled: true
            onDoubleClicked: // Only Clickable (ie sending valve commands) when vehicle state is in offNominaloffNominaloffNominaloffNominal
            {

                // if (VehicleState === a number that represents nominal (which is 6))
                //{
                console.log(valveName);
                console.log(valveID);
                console.log(valveCommandOff);
                console.log(valveCommandOn);
                console.log(valveCommandOff.toString(16));
                console.log(valveCommandOn.toString(16));
                console.log("State before click" + root.state)
                if (root.state === "0") // Closed //TESTING ONLY. this directly sets the state in the frontend using QML, which
                                        // interferes with the backend and makes it stop working
                {
                    frameHandler.sendFrame(window.commandFrameID, valveCommandOn.toString(16))  // nominal

                }
                else
                {
                    frameHandler.sendFrame(window.commandFrameID, valveCommandOff.toString(16))  // nominal
                }
                /*
                else if (root.state === "1") // Open
                {
                    // frameHandler.sendFrame(valveID, valveCommandOff.toString(16)) // nominal

                }
                else if (root.state === "2") // FireCommanded
                {
                    root.state = "3" // delete this later on
                }
                else if (root.state === "3") // OpenCommanded
                {
                    root.state = "4" // delete this later on
                }
                else if (root.state === "4") // CloseCommanded
                {
                    //root.state = "0" // delete this later on
                }
                */
                console.log("State after click" + root.state)
                //}

                // if (VehicleState === a number that represents nominal)
                //  {
                //  }

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
                color: "red"
            }
            PropertyChanges {
                target: gradientStop2;
                color: "red"
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
                color: "lawngreen"
            }
            PropertyChanges {
                target: gradientStop2;
                color: "lawngreen"
            }
            PropertyChanges {
                target: gradientStop3;
                color: "lawngreen"
            }
            PropertyChanges {
                target: gradientStop4;
                color: "lawngreen"
            }
        },

        State {
            name: "2" // FireCommanded
            PropertyChanges {
                target: gradientStop1;
                color: "darkorange"
            }
            PropertyChanges {
                target: gradientStop2;
                color: "darkorange"
            }
            PropertyChanges {
                target: gradientStop3;
                color: "darkorange"
            }
            PropertyChanges {
                target: gradientStop4;
                color: "darkorange"
            }
        },

        State {
            name: "3" // OpenCommanded
            PropertyChanges {
                target: gradientStop1;
                color: "darkorange"
            }
            PropertyChanges {
                target: gradientStop2;
                color: "darkorange"
            }
            PropertyChanges {
                target: gradientStop3;
                color: "lawngreen"
            }
            PropertyChanges {
                target: gradientStop4;
                color: "lawngreen"
            }
        },

        State {
            name: "4" // CloseCommanded
            PropertyChanges {
                target: gradientStop1;
                color: "gold"
            }
            PropertyChanges {
                target: gradientStop2;
                color: "gold"
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
