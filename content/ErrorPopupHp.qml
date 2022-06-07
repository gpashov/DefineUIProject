import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: backgroundImg.width
    height: backgroundImg.height

    Image {
        id: backgroundImg
        x: 0
        y: 0
        source: "images/c234_AlarmaFondoHP1.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: errorCodeTxt
        x: 35
        y: 120
        width: 179
        height: 36
        color: "#005870"
        text: "123456"
        font.pixelSize: 34
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
    }

    ErrorMessageImage {
        id: errorMessageImg
        x: 150
        y: 192
    }

    TwoStateButton {
        id: okButton
        x: 36
        y: 205
        imageSourceReleased: "images/c356_BotonAlarmaCentralOkRls.png"
        imageSourcePressed: "images/c357_BotonAlarmaCentralOkPress.png"
    }

    Text {
        id: treatmentTimeTxt
        x: 35
        y: 47
        width: 134
        height: 31
        color: "#005870"
        text: "49:61"
        font.pixelSize: 24
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
    }
    states: [
        State {
            name: "hp1State"
        },
        State {
            name: "hp2State"

            PropertyChanges {
                target: backgroundImg
                source: "images/c234_AlarmaFondoHP2.png"
            }

            PropertyChanges {
                target: errorCodeTxt
                x: 72
            }

            PropertyChanges {
                target: errorMessageImg
                x: -5
            }

            PropertyChanges {
                target: okButton
                x: 185
            }

            PropertyChanges {
                target: treatmentTimeTxt
                x: 72
            }
        },
        State {
            name: "hp3State"

            PropertyChanges {
                target: backgroundImg
                source: "images/c234_AlarmaFondoHP3.png"
            }

            PropertyChanges {
                target: treatmentTimeTxt
                y: 222
                text: "49:61"
            }

            PropertyChanges {
                target: errorCodeTxt
                y: 149
            }

            PropertyChanges {
                target: errorMessageImg
                y: -5
            }

            PropertyChanges {
                target: okButton
                y: 60
            }
        },
        State {
            name: "hp4State"

            PropertyChanges {
                target: backgroundImg
                source: "images/c234_AlarmaFondoHP4.png"
            }

            PropertyChanges {
                target: errorCodeTxt
                x: 72
                y: 149
            }

            PropertyChanges {
                target: errorMessageImg
                x: -5
                y: -5
            }

            PropertyChanges {
                target: okButton
                x: 185
                y: 60
            }

            PropertyChanges {
                target: treatmentTimeTxt
                x: 72
                y: 222
            }
        }
    ]
}



/*##^##
Designer {
    D{i:0;height:334;width:284}
}
##^##*/
