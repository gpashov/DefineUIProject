import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: switchOffImg.width
    height: switchOffImg.height
    property alias offStateImageSource: switchOffImg.source
    property alias onStateImageSource: switchOnImg.source
    property bool switchState: false


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
        onReleased: switchState = !switchState
    }

    states: [
        State {
            name: "offState"
            when: !item1.switchState
        },
        State {
            name: "onState"
            when: item1.switchState

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
