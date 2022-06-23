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
        x: popupColorHp1Img.x
        y: popupColorHp1Img.y
        visible: false
        source: "images/c217_PopUpManipHP2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: popupColorHp3Img
        x: popupColorHp1Img.x
        y: popupColorHp1Img.y
        visible: false
        source: "images/c218_PopUpManipHP3.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: popupColorHp4Img
        x: popupColorHp1Img.x
        y: popupColorHp1Img.y
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
