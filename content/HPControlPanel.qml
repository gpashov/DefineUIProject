import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: backgraoundImage.width
    height: backgraoundImage.height
    property alias statusImageState: statusImage.state
    property alias colorIndicatorState: colorIndicator.state
    state: "opened"
    property alias backgraoundImageSource: backgraoundImage.source

    Image {
        id: backgraoundImage
        source: "images/c004_MenuTrtHP1.png"
        fillMode: Image.PreserveAspectFit
    }

    VacuumButton {
        id: vacuumButton
        x: 146
        y: 45
    }

    TwoStateButton {
        id: playButton
        x: 65
        y: 45
        imageSourceReleased: "images/c038_BotonPlayMarcaAgua.png"
        imageSourcePressed: "images/c036_BotonPlayPress.png"
    }

    ThreeStateButton {
        id: timerButton
        x: 65
        y: 123
        imageSourcePressed: "images/c048_RelojTemporizadorPress.png"
        imageSourceReleased: "images/c049_RelojTemporizadorRls.png"
        imageSourceDisabled: "images/c050_RelojTemporizadorMarcaAgua.png"
    }

    HPTimeRemaining {
        id: timeRemaining
        x: timerButton.x
        y: timerButton.y
    }

    HPColorIndicator {
        id: colorIndicator
        x: 121
        y: 162
        state1ImageSource: "images/c005__MenuTrtHP1_Aro1.png"
        state2ImageSource: "images/c005_MenuTrtHP1_Aro2.png"
        state: "State2"
    }

    HPLeftStatusImage {
        id: statusImage
        x: 151
        y: 194
        anchors.verticalCenterOffset: 0
    }

    Image {
        id: indicatorButton
        y: 147
        anchors.left: indicatorCool.left
        source: "images/c188_IndicadorBotonHP2Off.png"
        anchors.leftMargin: 0
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: indicatorRfid
        y: 198
        anchors.left: indicatorCool.left
        source: "images/c187_IndicadorRFIDHP2Off.png"
        anchors.leftMargin: 0
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: indicatorVacuum
        y: 98
        anchors.left: indicatorCool.left
        source: "images/c189_IndicadorVacHP2Off.png"
        anchors.leftMargin: 0
        fillMode: Image.PreserveAspectFit
    }


    Image {
        id: indicatorCool
        x: 20
        y: 47
        source: "images/c190_IndicadorFrioHP2Off.png"
        fillMode: Image.PreserveAspectFit
    }


    HPTypeNameLeft {
        id: hPTypeNameLeft
        x: 65
        y: 196
        visible: false
        state: "CurvedState"
    }

    HPTypeNameRight {
        id: hPTypeNameRight
        x: 122
        y: 196
        visible: false
        state: "CurvedState"
    }

    HPResucctionCount {
        id: hpResucctionCount
        x: 197
        y: 32
    }

    PopupTestVacuumSmall {
        id: popupTestVacuumSmall
        x: 209
        y: 45
    }






    states: [
        State {
            name: "hp1State"

            PropertyChanges {
                target: hPTypeNameLeft
                visible: true
            }

            PropertyChanges {
                target: colorIndicator
                x: 121
            }

            PropertyChanges {
                target: popupTestVacuumSmall
                state: "leftState"
            }
        },
        State {
            name: "hp2State"

            PropertyChanges {
                target: backgraoundImage
                source: "images/c012_MenuTrtHP2.png"
            }

            PropertyChanges {
                target: indicatorCool
                x: 233
            }

            PropertyChanges {
                target: colorIndicator
                x: -24
                y: 162
                state1ImageSource: "images/c013_MenuTrtHP2_Aro1.png"
                state2ImageSource: "images/c013_MenuTrtHP2_Aro2.png"
            }

            PropertyChanges {
                target: playButton
                x: 150
                y: 44
            }

            PropertyChanges {
                target: statusImage
                x: 4
                y: 194
            }

            PropertyChanges {
                target: timerButton
                x: 70
            }

            PropertyChanges {
                target: vacuumButton
                x: 70
                y: 44
            }

            PropertyChanges {
                target: hPTypeNameRight
                visible: true
            }

            PropertyChanges {
                target: hpResucctionCount
                x: 57
            }

            PropertyChanges {
                target: popupTestVacuumSmall
                x: -138
                y: 43
                state: "RightState"
            }
        },
        State {
            name: "hp3State"

            PropertyChanges {
                target: backgraoundImage
                source: "images/c020_MenuTrtHP3.png"
            }

            PropertyChanges {
                target: indicatorCool
                x: 23
                y: 115
            }

            PropertyChanges {
                target: indicatorVacuum
                y: 166
            }

            PropertyChanges {
                target: indicatorButton
                y: 215
            }

            PropertyChanges {
                target: indicatorRfid
                y: 266
            }

            PropertyChanges {
                target: colorIndicator
                x: 124
                y: -13
                state2ImageSource: "images/c021_MenuTrtHP3_Aro2.png"
                state1ImageSource: "images/c021_MenuTrtHP3_Aro1.png"
            }

            PropertyChanges {
                target: playButton
                y: 223
            }

            PropertyChanges {
                target: vacuumButton
                y: 223
            }

            PropertyChanges {
                target: timerButton
                y: 154
            }

            PropertyChanges {
                target: hPTypeNameLeft
                y: 111
                visible: true
            }

            PropertyChanges {
                target: statusImage
                y: 11
            }

            PropertyChanges {
                target: hpResucctionCount
                y: 270
            }

            PropertyChanges {
                target: popupTestVacuumSmall
                x: 210
                y: 223
                state: "leftState"
            }
        },
        State {
            name: "hp4State"

            PropertyChanges {
                target: backgraoundImage
                source: "images/c028_MenuTrtHP4.png"
            }

            PropertyChanges {
                target: indicatorCool
                x: 233
                y: 115
            }

            PropertyChanges {
                target: indicatorVacuum
                y: 166
            }

            PropertyChanges {
                target: indicatorButton
                y: 215
            }

            PropertyChanges {
                target: indicatorRfid
                y: 266
            }

            PropertyChanges {
                target: colorIndicator
                x: -22
                y: -10
                state2ImageSource: "images/c029_MenuTrtHP4_Aro2.png"
                state1ImageSource: "images/c029_MenuTrtHP4_Aro1.png"
            }

            PropertyChanges {
                target: playButton
                x: 150
                y: 223
            }

            PropertyChanges {
                target: vacuumButton
                x: 70
                y: 223
            }

            PropertyChanges {
                target: timerButton
                x: 70
                y: 154
            }

            PropertyChanges {
                target: hPTypeNameRight
                y: 111
                visible: true
            }

            PropertyChanges {
                target: statusImage
                x: 4
                y: 11
            }

            PropertyChanges {
                target: hpResucctionCount
                x: 57
                y: 270
            }

            PropertyChanges {
                target: popupTestVacuumSmall
                x: -138
                y: 222
                state: "RightState"
            }
        }
    ]



}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.66;height:338;width:287}
}
##^##*/
