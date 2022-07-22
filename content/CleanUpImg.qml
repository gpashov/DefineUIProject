import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: name
    visible: false

    Image {
        id: c434_HPalarmaLimpiezacolocar1
        x: 0
        y: 0
        visible: false
        source: "images/c434_HPalarmaLimpiezacolocar1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c433_HPalarmaLimpiezacolocar0
        x: 0
        y: 0
        visible: false
        source: "images/c433_HPalarmaLimpiezacolocar0.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c432_HPalarmaLimpieza1
        x: 0
        y: 0
        visible: false
        source: "images/c432_HPalarmaLimpieza1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c431_HPalarmaLimpieza0
        x: 0
        y: 0
        visible: false
        source: "images/c431_HPalarmaLimpieza0.png"
        fillMode: Image.PreserveAspectFit
    }
    states: [
        State {
            name: "countdownState"

            PropertyChanges {
                target: c434_HPalarmaLimpiezacolocar1
                visible: true
            }
        },
        State {
            name: "waitUserState"

            PropertyChanges {
                target: c433_HPalarmaLimpiezacolocar0
                visible: true
            }
        },
        State {
            name: "cleaningState"

            PropertyChanges {
                target: c432_HPalarmaLimpieza1
                visible: true
            }
        },
        State {
            name: "waitVacuumState"

            PropertyChanges {
                target: c431_HPalarmaLimpieza0
                visible: true
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;height:136;width:136}
}
##^##*/
