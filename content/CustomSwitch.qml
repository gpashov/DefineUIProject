import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: switchOffImg.width
    height: switchOffImg.height
    state: "offState"
    property alias offStateImageSource: switchOffImg.source
    property alias onStateImageSource: switchOnImg.source
    property alias offPressedStateImageSource: switchOffPressedImg.source
    property alias onPressedStateImageSource: switchOnPressedImg.source

    signal onAction
    signal offAction

    Image {
        id: switchOffImg
        source: "images/c045_BotonAutoRls.png"
        fillMode: Image.PreserveAspectFit
        visible: false
    }

    Image {
        id: switchOnImg
        source: "images/c044_BotonAutoPress.png"
        fillMode: Image.PreserveAspectFit
        visible: false
    }

    Image {
        id: switchOffPressedImg
        source: "images/c044_BotonAutoPress.png"
        fillMode: Image.PreserveAspectFit
        visible: false
    }

    Image {
        id: switchOnPressedImg
        source: "images/c045_BotonAutoRls.png"
        fillMode: Image.PreserveAspectFit
        visible: false
    }

    Button {
        id: switchButton
        width: switchOffImg.width
        height: switchOffImg.height
        opacity: 0
        onPressed: {
            // Change switch state
            if (parent.state === "offState") {
                parent.state = "offPressedState"
            }
            else {
                parent.state = "onPressedState"
            }
        }
        onReleased: {
            // Change switch state
            if (parent.state === "offPressedState") {
                parent.state = "onState"
            }
            else {
                parent.state = "offState"
            }

            // Execute switch action by emitting a signal
            if (parent.state === "onState" ) {
                onAction()
            }
            else {
                offAction()
            }
        }
    }

    states: [
        State {
            name: "offState"

            PropertyChanges {
                target: switchOffImg
                visible: true
            }
        },
        State {
            name: "onState"

            PropertyChanges {
                target: switchOnImg
                visible: true
            }
        },
        State {
            name: "offPressedState"

            PropertyChanges {
                target: switchOffPressedImg
                visible: true
            }
        },
        State {
            name: "onPressedState"

            PropertyChanges {
                target: switchOnPressedImg
                visible: true
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;height:86;width:86}
}
##^##*/
