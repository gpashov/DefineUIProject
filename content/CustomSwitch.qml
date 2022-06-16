import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: switchOffImg.width
    height: switchOffImg.height
    state: "offState"
    property alias offStateImageSource: switchOffImg.source
    property alias onStateImageSource: switchOnImg.source
    property alias switchState: switchButton.switchState

    signal onAction
    signal offAction

    Image {
        id: switchOffImg
        source: "images/c045_BotonAutoRls.png"
        fillMode: Image.PreserveAspectFit
        visible: true
    }

    Image {
        id: switchOnImg
        source: "images/c044_BotonAutoPress.png"
        fillMode: Image.PreserveAspectFit
        visible: false
    }

    Button {
        id: switchButton
        width: switchOffImg.width
        height: switchOffImg.height
        opacity: 0
        property bool switchState: false
        onReleased: {
            // Change switch state
//            switchState = !switchState
            // Execute switch action by emitting a signal
            if (switchState == false /*true*/ ) {
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
            when: !switchButton.switchState
        },
        State {
            name: "onState"
            when: switchButton.switchState

            PropertyChanges {
                target: switchOnImg
                visible: true
            }

            PropertyChanges {
                target: switchOffImg
                visible: false
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;height:86;width:86}
}
##^##*/
