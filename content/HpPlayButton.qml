import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0

TwoStateButton {
    id: playButton
    imageSourceReleased: "images/c038_BotonPlayMarcaAgua.png"
    imageSourcePressed: "images/c038_BotonPlayMarcaAgua.png"

    states: [
        State {
            name: "offState"
        },
        State {
            name: "onState"

            PropertyChanges {
                target: playButton
                imageSourceReleased: "images/c037_BotonPlayRls.png"
                imageSourcePressed: "images/c035_BotonPlayPress.png"
            }
        },
        State {
            name: "treatmentRunningState"

            PropertyChanges {
                target: playButton
                imageSourceReleased: "images/c036_BotonPlayPress.png"
                imageSourcePressed: "images/c036_BotonPlayPress.png"
            }
        },
        State {
            name: "treatmentCancelState"

            PropertyChanges {
                target: playButton
                imageSourceReleased: "images/c034_BotonStopRls.png"
                imageSourcePressed: "images/c033_BotonStopPress.png"
            }
        }
    ]
}
