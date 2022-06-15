import QtQuick 2.15
import QtQuick.Controls 2.15
import define.enums 1.0

Item {
    id: item1
    width: backgraoundImage.width
    height: backgraoundImage.height
    property alias item1State: item1.state
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

    ThreeStateButton {
        id: temperatureButton
        x: timerButton.x
        y: timerButton.y
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

    HP1ImageButton {
        id: imageButtonHp1
        x: 151
        y: 194
        visible: false
    }

    HP2ImageButton {
        id: imageButtonHp2
        x: imageButtonHp1.x
        y: imageButtonHp1.y
        visible: false
    }

    HP3ImageButton {
        id: imageButtonHp3
        x: imageButtonHp1.x
        y: imageButtonHp1.y
        visible: false
    }

    HP4ImageButton {
        id: imageButtonHp4
        x: imageButtonHp1.x
        y: imageButtonHp1.y
        visible: false
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
        state: hPTypeNameLeft.state
    }

    HPResucctionCount {
        id: hpResuctionCount
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

            PropertyChanges {
                target: imageButtonHp1
                x: 150
                y: 193
                visible: true
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
                x: -25
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
                target: imageButtonHp1
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
                target: hpResuctionCount
                x: 57
            }

            PropertyChanges {
                target: popupTestVacuumSmall
                x: -138
                y: 43
                state: "RightState"
            }

            PropertyChanges {
                target: imageButtonHp2
                x: 5
                visible: true
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
                target: imageButtonHp1
                y: 11
            }

            PropertyChanges {
                target: hpResuctionCount
                y: 270
            }

            PropertyChanges {
                target: popupTestVacuumSmall
                x: 210
                y: 223
                state: "leftState"
            }

            PropertyChanges {
                target: imageButtonHp3
                x: 152
                visible: true
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
                x: -25
                y: -13
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
                target: imageButtonHp1
                x: 4
                y: 11
            }

            PropertyChanges {
                target: hpResuctionCount
                x: 57
                y: 270
            }

            PropertyChanges {
                target: popupTestVacuumSmall
                x: -138
                y: 222
                state: "RightState"
            }

            PropertyChanges {
                target: imageButtonHp4
                x: 6
                visible: true
            }
        }
    ]

    Connections {
        target: wdgWpr
        onHpControlPanelModelTextSet: (hpIndex, idImg) => {
                                          var newState
                                          switch (idImg) {
                                              case AppEnumsNs.c066_NameCurvedHP_L:
                                              case AppEnumsNs.c066_NameCurvedHP_R: newState = "CurvedState"; break;
                                              case AppEnumsNs.c067_NameTightHP_L:
                                              case AppEnumsNs.c067_NameTightHP_R: newState = "TightState"; break;
                                              case AppEnumsNs.c068_NameStarightHP_L:
                                              case AppEnumsNs.c068_NameStraightHP_R: newState = "StraightState"; break;
                                              case AppEnumsNs.c069_NameTinyHP_L:
                                              case AppEnumsNs.c069_NameTinyHP_R: newState = "TinyState"; break;
                                              case AppEnumsNs.c070_NameTinyCurvedHP_L:
                                              case AppEnumsNs.c070_NameTinyCurvedHP_R: newState = "TinyCurvedState"; break;
                                              case AppEnumsNs.c071_NameDoubleHP_L:
                                              case AppEnumsNs.c071_NameDoubleHP_R: newState = "DoubleState"; break;
                                              case AppEnumsNs.c072_NameOvalHP_L:
                                              case AppEnumsNs.c072_NameOvalHP_R: newState = "OvalState"; break;
                                              case AppEnumsNs.c073_NameOvalCurvedHP_L:
                                              case AppEnumsNs.c073_NameOvalCurvedHP_R: newState = "OvalCurvedState"; break;
                                              case AppEnumsNs.c074_NameDeltaHP_L:
                                              case AppEnumsNs.c074_NameDeltaHP_R: newState = "DeltaState"; break;
                                              case AppEnumsNs.c233_ImgPixelBlanco:
                                              default: newState = "BlankState"; break;
                                          }

                                          switch(hpIndex) {
                                              case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { hPTypeNameLeft.state = newState; } break;
                                              case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { hPTypeNameLeft.state = newState; } break;
                                              case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { hPTypeNameLeft.state = newState; } break;
                                              case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { hPTypeNameLeft.state = newState; } break;
                                              default: break;
                                          }
                                      }
    }

    Connections {
        target: wdgWpr
        onTimeRemainingVisibilityChanged: (hpIndex, newVisibility) => {
                                              switch(hpIndex) {
                                                  case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { timeRemaining.visible = newVisibility; } break;
                                                  case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { timeRemaining.visible = newVisibility; } break;
                                                  case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { timeRemaining.visible = newVisibility; } break;
                                                  case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { timeRemaining.visible = newVisibility; } break;
                                                  default: break;
                                              }
                                          }
    }

    Connections {
        target: wdgWpr
        onTimeSelectButtonVisibilityChanged: (hpIndex, newVisibility) => {
                                              switch(hpIndex) {
                                                  case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { timerButton.visible = newVisibility; } break;
                                                  case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { timerButton.visible = newVisibility; } break;
                                                  case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { timerButton.visible = newVisibility; } break;
                                                  case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { timerButton.visible = newVisibility; } break;
                                                  default: break;
                                              }
                                          }
    }

    Connections {
        target: wdgWpr
        onTreatmentTimerBackgroundSet: (hpIndex, isSelectable) => {
                                           var newState = "nonselectableState"
                                           if (isSelectable === true) {
                                               newState = "selectableState"
                                           }

                                           switch(hpIndex) {
                                               case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { timeRemaining.state = newState; } break;
                                               case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { timeRemaining.state = newState; } break;
                                               case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { timeRemaining.state = newState; } break;
                                               case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { timeRemaining.state = newState; } break;
                                               default: break;
                                           }
                                       }
    }

    Connections {
        target: wdgWpr
        onTreatmentTimerSet: (hpIndex, newTime) => {
                                     switch(hpIndex) {
                                         case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { timeRemaining.time = newTime; } break;
                                         case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { timeRemaining.time = newTime; } break;
                                         case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { timeRemaining.time = newTime; } break;
                                         case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { timeRemaining.time = newTime; } break;
                                         default: break;
                                     }
                                 }
    }

    Connections {
        target: wdgWpr
        onResuctionCountVisibilityChanged: (hpIndex, newVisibility) => {
                                     switch(hpIndex) {
                                         case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { hpResuctionCount.visible = newVisibility; } break;
                                         case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { hpResuctionCount.visible = newVisibility; } break;
                                         case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { hpResuctionCount.visible = newVisibility; } break;
                                         case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { hpResuctionCount.visible = newVisibility; } break;
                                         default: break;
                                     }
                                 }
    }

    Connections {
        target: wdgWpr
        onResuctionCountChanged: (hpIndex, resuctionCount) => {
                                     switch(hpIndex) {
                                         case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { hpResuctionCount.resucctionCount = resuctionCount; } break;
                                         case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { hpResuctionCount.resucctionCount = resuctionCount; } break;
                                         case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { hpResuctionCount.resucctionCount = resuctionCount; } break;
                                         case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { hpResuctionCount.resucctionCount = resuctionCount; } break;
                                         default: break;
                                     }
                                 }
    }

    Connections {
        target: wdgWpr
        onIndicatorRfidVisibilityChanged: (hpIndex, newVisibility) => {
                                     switch(hpIndex) {
                                         case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { indicatorRfid.visible = newVisibility; } break;
                                         case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { indicatorRfid.visible = newVisibility; } break;
                                         case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { indicatorRfid.visible = newVisibility; } break;
                                         case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { indicatorRfid.visible = newVisibility; } break;
                                         default: break;
                                     }
                                 }
    }

    Connections {
        target: wdgWpr
        onIndicatorButtonVisibilityChanged: (hpIndex, newVisibility) => {
                                     switch(hpIndex) {
                                         case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { indicatorButton.visible = newVisibility; } break;
                                         case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { indicatorButton.visible = newVisibility; } break;
                                         case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { indicatorButton.visible = newVisibility; } break;
                                         case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { indicatorButton.visible = newVisibility; } break;
                                         default: break;
                                     }
                                 }
    }

    Connections {
        target: wdgWpr
        onIndicatorVacuumVisibilityChanged: (hpIndex, newVisibility) => {
                                     switch(hpIndex) {
                                         case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { indicatorVacuum.visible = newVisibility; } break;
                                         case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { indicatorVacuum.visible = newVisibility; } break;
                                         case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { indicatorVacuum.visible = newVisibility; } break;
                                         case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { indicatorVacuum.visible = newVisibility; } break;
                                         default: break;
                                     }
                                 }
    }

    Connections {
        target: wdgWpr
        onIndicatorCoolingVisibilityChanged: (hpIndex, newVisibility) => {
                                     switch(hpIndex) {
                                         case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { indicatorCool.visible = newVisibility; } break;
                                         case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { indicatorCool.visible = newVisibility; } break;
                                         case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { indicatorCool.visible = newVisibility; } break;
                                         case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { indicatorCool.visible = newVisibility; } break;
                                         default: break;
                                     }
                                 }
    }

    Connections {
        target: wdgWpr
        onTemperatureButtonEnabled: (hpIndex, isEnabled) => {
                                     switch(hpIndex) {
                                         case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { temperatureButton.enabled = isEnabled; } break;
                                         case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { temperatureButton.enabled = isEnabled; } break;
                                         case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { temperatureButton.enabled = isEnabled; } break;
                                         case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { temperatureButton.enabled = isEnabled; } break;
                                         default: break;
                                     }
                                 }
    }
}




