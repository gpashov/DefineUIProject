import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject

Item {
    id: item1
    width: Constants.width
    height: Constants.height

    Image {
        id: popupColorHp1Img
        x: 323
        y: 573
        visible: false
        source: "images/c216_PopUpManipHP1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: popupColorHp2Img
        x: 323
        y: 573
        visible: false
        source: "images/c217_PopUpManipHP2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: popupColorHp3Img
        x: 323
        y: 573
        visible: false
        source: "images/c218_PopUpManipHP3.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: popupColorHp4Img
        x: 323
        y: 573
        visible: false
        source: "images/c219_PopUpManipHP4.png"
        fillMode: Image.PreserveAspectFit
    }
    states: [
        State {
            name: "hp1State"

            PropertyChanges {
                target: popupColorHp1Img
                visible: true
            }
        },
        State {
            name: "hp2State"

            PropertyChanges {
                target: popupColorHp2Img
                x: 321
                y: 572
                visible: true
            }
        },
        State {
            name: "hp3State"

            PropertyChanges {
                target: popupColorHp3Img
                x: 322
                y: 574
                visible: true
            }
        },
        State {
            name: "hp4State"

            PropertyChanges {
                target: popupColorHp4Img
                visible: true
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/
