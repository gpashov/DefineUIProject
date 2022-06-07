import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0
Item {
    property alias imageReleasedSource: imageReleased.source
    property alias imagePressedSource: imagePressed.source
    property alias interactiveArea: interactiveArea
    width: 210
    height: 191

    Image {
        id: imageReleased
        source: "images/b003_BotonFemeninoRls.png"
    }

    Image {
        id: imagePressed
        source: "images/b002_BotonFemeninoPress.png"
    }

    Button {
        id: interactiveArea
        anchors.fill: parent
        opacity: 0
    }

    state: "releasedState"
    states: [
        State {
            name: "releasedState"
            when: !interactiveArea.pressed

            PropertyChanges {
                target: imagePressed
                visible: false
            }

            PropertyChanges {
                target: imageReleased
                visible: true
            }
        },
        State {
            name: "pressedState"
            when: interactiveArea.pressed

            PropertyChanges {
                target: imageReleased
                visible: false
            }

            PropertyChanges {
                target: imagePressed
                visible: true
            }
        }
    ]
}


