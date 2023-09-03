import QtQuick

Item {
    id: engineControllerState

    property int fontSize: 20

    property alias engineControllerStateTextForMain : engineControllerStateText

    state: "0"

    Text {
        id: engineControllerStateText
        text: "State : N/A"
        anchors.left: parent.left
        anchors.top: parent.top
        font.pixelSize: fontSize
        color: "orange"
    }

    states: [
        State {
            name: "0"
            PropertyChanges {
                target: engineControllerStateText
                text: "State : PASSIVE"
            }
        },
        State {
            name: "1"
            PropertyChanges {
                target: engineControllerStateText
                text: "State : ACTIVE"
            }
        },
        State {
            name: "2"
            PropertyChanges {
                target: engineControllerStateText
                text: "State : CHILL"
            }
        },
        State {
            name: "3"
            PropertyChanges {
                target: engineControllerStateText
                text: "State : PURGE"
            }
        },
        State {
            name: "4"
            PropertyChanges {
                target: engineControllerStateText
                text: "State : SHUTDOWN"
            }
        },
        State {
            name: "5"
            PropertyChanges {
                target: engineControllerStateText
                text: "State : ARMED"
            }
        },
        State {
            name: "6"
            PropertyChanges {
                target: engineControllerStateText
                text: "State : TEST"
            }
        },
        State {
            name: "7"
            PropertyChanges {
                target: engineControllerStateText
                text: "State : OFF NOMINAL"
            }
        },
        State {
            name: "8"
            PropertyChanges {
                target: engineControllerStateText
                text: "State : FIRING"
            }
        },
        State {
            name: "9"
            PropertyChanges {
                target: engineControllerStateText
                text: "State : CONTROLLER_STATE_SIZE"
            }
        }
    ]

    /*        PASSIVE = 0,
        ACTIVE = 1,
        CHILL = 2,
        PURGE = 3,
        SHUTDOWN = 4,
        ARMED = 5,
        TEST_PASSTHROUGH = 6,
        OFF_NOMINAL_PASSTHROUGH = 7,
        FIRING_AUTOSEQUENCE = 8,
        CONTROLLER_STATE_SIZE= 9*/
}
