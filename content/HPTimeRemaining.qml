import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: trtRunningImg.width
    height: trtRunningImg.height

    Image {
        id: trtRunningImg
        source: "images/c047_FondoTemporizador.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: initialImg
        x: 0
        y: 0
        source: "images/c047_FondoNumVwrBlanco.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: timeRemainingTxt
        x: 34
        y: 0
        width: 108
        height: 65
        color: "#015e76"
        text: "70:00"
        font.pixelSize: 36
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    states: [
        State {
            name: "nonselectableState"

            PropertyChanges {
                target: trtRunningImg
                visible: false
            }

            PropertyChanges {
                target: timeRemainingTxt
                x: 24
            }
        },
        State {
            name: "selectableState"

            PropertyChanges {
                target: initialImg
                visible: false
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;height:65;width:155}
}
##^##*/
