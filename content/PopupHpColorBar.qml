import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: popupColorHp1Img.width
    height: popupColorHp1Img.height

    Image {
        id: popupColorHp1Img
        x: 0
        y: 0
        visible: false
        source: "images/c216_PopUpManipHP1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: popupColorHp2Img
        x: 0
        y: 0
        visible: false
        source: "images/c217_PopUpManipHP2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: popupColorHp3Img
        x: 0
        y: 0
        visible: false
        source: "images/c218_PopUpManipHP3.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: popupColorHp4Img
        x: 0
        y: 0
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
                visible: true
            }
        },
        State {
            name: "hp3State"

            PropertyChanges {
                target: popupColorHp3Img
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
