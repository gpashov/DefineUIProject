import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: button
    width: buttonNormal.width
    height: buttonNormal.height
    property alias buttonState: button.state
    property alias buttonNormalSource: buttonNormal.source
    property alias buttonPressedSource: buttonPressed.source
    property alias buttonReleasedSource: buttonReleased.source
    property alias buttonInactiveSource: buttonInactive.source
    property alias interactiveArea: interactiveArea

    states: [
        State {
            name: "statePressed"
            when: interactiveArea.pressed

            PropertyChanges {
                target: buttonPressed
                visible: true
            }

            PropertyChanges {
                target: buttonNormal
                visible: false
            }
        },
        State {
            name: "stateReleased"
            when: !interactiveArea.pressed

            PropertyChanges {
                target: buttonNormal
                visible: false
            }

            PropertyChanges {
                target: buttonReleased
                visible: true
            }
        },
        State {
            name: "stateInactive"

            PropertyChanges {
                target: buttonNormal
                visible: false
            }

            PropertyChanges {
                target: buttonInactive
                visible: true
            }

            PropertyChanges {
                target: interactiveArea
                visible: parent.state !== "stateInactive"
            }
        }
    ]

    Image {
        id: buttonNormal
        x: 0
        y: 0
        source: "images/b018_BotonConfigMarcaAgua1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: buttonPressed
        x: 0
        y: 0
        visible: false
        source: "images/b016_BotonConfigPress.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: buttonReleased
        x: 0
        y: 0
        visible: false
        source: "images/b017_BotonConfigRls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: buttonInactive
        x: 0
        y: 0
        visible: false
        source: "images/b018_BotonConfigMarcaAgua.png"
        fillMode: Image.PreserveAspectFit
    }

    Button {
        id: interactiveArea // the actual button
        visible: parent.state !== "stateInactive"
        opacity: 0
        width: parent.width
        height: parent.height
    }
}

/*##^##
Designer {
    D{i:0;height:86;width:86}
}
##^##*/
