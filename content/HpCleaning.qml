import QtQuick 2.15
import QtQuick.Controls 2.15
import define.enums 1.0

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
        id: cleanHpTxt
        x: 44
        y: 37
        width: 134
        height: 36
        color: "#005870"
        text: "123456"
        font.pixelSize: 34
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"

        Connections {
            target: wdgWpr
            onCleanUpTimeSet: (hpIndex, time) => {
                                      switch(hpIndex) {
                                          case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { cleanHpTxt.text = time } break;
                                          case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { cleanHpTxt.text = time } break;
                                          case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { cleanHpTxt.text = time } break;
                                          case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { cleanHpTxt.text = time } break;
                                          default: break;
                                      }
                                  }
        }
    }

    ThreeStateButton {
        id: cleanBtn
        x: 44
        y: 178
        imageSourceReleased: "images/c456_MenuLimpiezaClean_Rls.png"
        imageSourcePressed: "images/c457_MenuLimpiezaClean_Press.png"
        imageSourceDisabled: "image/c458_MenuLimpiezaClean_MarcaAgua.png"
        button.onReleased:  {
            switch (parent.state) {
            case "hp1State": cbkWpr.butPopUpCleanUp(AppEnumsNs.APP_GUI_HP1_ID); break;
            case "hp2State": cbkWpr.butPopUpCleanUp(AppEnumsNs.APP_GUI_HP2_ID); break;
            case "hp3State": cbkWpr.butPopUpCleanUp(AppEnumsNs.APP_GUI_HP3_ID); break;
            case "hp4State": cbkWpr.butPopUpCleanUp(AppEnumsNs.APP_GUI_HP4_ID); break;
            default: break;
            }
        }

        Connections {
            target: wdgWpr
            onCleanUpCleanButtonEnabled: (hpIndex, isEnabled) => {
                                             var newState = "buttonReleasedState"
                                             if (false === isEnabled) {
                                                 newState = "buttonDisabledState"
                                             }

                                             switch(hpIndex) {
                                             case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { cleanBtn.state = newState } break;
                                             case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { cleanBtn.state = newState } break;
                                             case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { cleanBtn.state = newState } break;
                                             case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { cleanBtn.state = newState } break;
                                             default: break;
                                             }
                                         }
        }
    }

    ThreeStateButton {
        id: yesBtn
        x: 44
        y: 101
        imageSourceReleased: "images/c453_MenuAlarmaOK_rls.png"
        imageSourcePressed: "images/c452_MenuAlarmaOK_press.png"
        imageSourceDisabled: "image/c453_MenuAlarmaOK_MarcaAgua.png"
        button.onReleased:  {
            switch (parent.state) {
            case "hp1State": cbkWpr.butPopUpCleanUpYES(AppEnumsNs.APP_GUI_HP1_ID); break;
            case "hp2State": cbkWpr.butPopUpCleanUpYES(AppEnumsNs.APP_GUI_HP2_ID); break;
            case "hp3State": cbkWpr.butPopUpCleanUpYES(AppEnumsNs.APP_GUI_HP3_ID); break;
            case "hp4State": cbkWpr.butPopUpCleanUpYES(AppEnumsNs.APP_GUI_HP4_ID); break;
            default: break;
            }
        }

        Connections {
            target: wdgWpr
            onCleanUpYesButtonEnabled: (hpIndex, isEnabled) => {
                                             var newState = "buttonReleasedState"
                                             if (false === isEnabled) {
                                                 newState = "buttonDisabledState"
                                             }

                                             switch(hpIndex) {
                                             case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { yesBtn.state = newState } break;
                                             case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { yesBtn.state = newState } break;
                                             case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { yesBtn.state = newState } break;
                                             case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { yesBtn.state = newState } break;
                                             default: break;
                                             }
                                         }
        }
    }

    ThreeStateButton {
        id: noBtn
        x: 121
        y: 101
        imageSourceReleased: "images/c455_MenuAlarmaNO_rls.png"
        imageSourcePressed: "images/c454_MenuAlarmaNO_press.png"
        imageSourceDisabled: "image/c455_MenuAlarmaNO_MarcaAgua.png"
        button.onReleased:  {
            switch (parent.state) {
            case "hp1State": cbkWpr.butPopUpCleanUpNO(AppEnumsNs.APP_GUI_HP1_ID); break;
            case "hp2State": cbkWpr.butPopUpCleanUpNO(AppEnumsNs.APP_GUI_HP2_ID); break;
            case "hp3State": cbkWpr.butPopUpCleanUpNO(AppEnumsNs.APP_GUI_HP3_ID); break;
            case "hp4State": cbkWpr.butPopUpCleanUpNO(AppEnumsNs.APP_GUI_HP4_ID); break;
            default: break;
            }
        }

        Connections {
            target: wdgWpr
            onCleanUpNoButtonEnabled: (hpIndex, isEnabled) => {
                                             var newState = "buttonReleasedState"
                                             if (false === isEnabled) {
                                                 newState = "buttonDisabledState"
                                             }

                                             switch(hpIndex) {
                                                 case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { noBtn.state = newState } break;
                                                 case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { noBtn.state = newState } break;
                                                 case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { noBtn.state = newState } break;
                                                 case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { noBtn.state = newState } break;
                                                 default: break;
                                             }
                                         }
        }
    }

    TwoStateButton {
        id: cancelBtn
        x: 17
        y: 252
        imageSourceReleased: "images/c532_botoncancel_Press.png"
        imageSourcePressed: "images/c531_botoncancel_Rls.png"
        button.onReleased:  {
            switch (parent.state) {
            case "hp1State": cbkWpr.butPopUpCleanUpCancel(AppEnumsNs.APP_GUI_HP1_ID); break;
            case "hp2State": cbkWpr.butPopUpCleanUpCancel(AppEnumsNs.APP_GUI_HP2_ID); break;
            case "hp3State": cbkWpr.butPopUpCleanUpCancel(AppEnumsNs.APP_GUI_HP3_ID); break;
            case "hp4State": cbkWpr.butPopUpCleanUpCancel(AppEnumsNs.APP_GUI_HP4_ID); break;
            default: break;
            }
        }

        Connections {
            target: wdgWpr
            onCleanUpCancelButtonEnabled: (hpIndex, isEnabled) => {
                                             switch(hpIndex) {
                                                 case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { cancelBtn.enabled = isEnabled } break;
                                                 case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { cancelBtn.enabled = isEnabled } break;
                                                 case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { cancelBtn.enabled = isEnabled } break;
                                                 case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { cancelBtn.enabled = isEnabled } break;
                                                 default: break;
                                             }
                                         }
        }
    }

    CleanUpImg {
        id: cleanUpImg
        x: 149
        y: 191
    }

    Image {
        id: cancelCounterBackgroundImg
        x: 108
        y: 252
        source: "images/c533_fondocontador.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: cancelCounterTxt
        color: "#005870"
        text: "5"
        anchors.left: cancelCounterBackgroundImg.right
        anchors.right: cancelCounterBackgroundImg.left
        anchors.top: cancelCounterBackgroundImg.bottom
        anchors.bottom: cancelCounterBackgroundImg.top
        font.pixelSize: 24
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"

        Connections {
            target: wdgWpr
            onCleanUpCancelCountSet: (hpIndex, cancelCount) => {
                                      switch(hpIndex) {
                                          case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { cancelCounterTxt.text = cancelCount } break;
                                          case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { cancelCounterTxt.text = cancelCount } break;
                                          case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { cancelCounterTxt.text = cancelCount } break;
                                          case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { cancelCounterTxt.text = cancelCount } break;
                                          default: break;
                                      }
                                  }
        }
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
                target: cleanHpTxt
                x: 80
            }

            PropertyChanges {
                target: cleanBtn
                x: 156
            }

            PropertyChanges {
                target: yesBtn
                x: 80
            }

            PropertyChanges {
                target: noBtn
                x: 156
            }

            PropertyChanges {
                target: cleanImg
                x: -1
            }

            PropertyChanges {
                target: cancelCounterBackgroundImg
                x: 131
            }

            PropertyChanges {
                target: cancelBtn
                x: 176
            }
        },
        State {
            name: "hp3State"

            PropertyChanges {
                target: backgroundImg
                source: "images/c234_AlarmaFondoHP3.png"
            }

            PropertyChanges {
                target: cleanHpTxt
                y: 229
            }

            PropertyChanges {
                target: cleanBtn
                y: 76
            }

            PropertyChanges {
                target: yesBtn
                y: 153
            }

            PropertyChanges {
                target: noBtn
                y: 153
            }

            PropertyChanges {
                target: cancelBtn
                y: 35
            }

            PropertyChanges {
                target: cleanImg
                y: -3
            }

            PropertyChanges {
                target: cancelCounterBackgroundImg
                y: 35
            }
        },
        State {
            name: "hp4State"

            PropertyChanges {
                target: backgroundImg
                source: "images/c234_AlarmaFondoHP4.png"
            }

            PropertyChanges {
                target: cleanHpTxt
                x: 80
                y: 229
            }

            PropertyChanges {
                target: cleanBtn
                x: 156
                y: 76
            }

            PropertyChanges {
                target: cancelCounterBackgroundImg
                x: 131
                y: 35
            }

            PropertyChanges {
                target: cleanImg
                x: -1
                y: -3
            }

            PropertyChanges {
                target: cancelBtn
                x: 176
                y: 35
            }

            PropertyChanges {
                target: noBtn
                x: 156
                y: 153
            }

            PropertyChanges {
                target: yesBtn
                x: 80
                y: 153
            }
        }
    ]

    Connections {
        target: wdgWpr
        onCleanUpPopupImageSet: (hpIndex, idImg) => {
                                    var imgState
                                    switch(idImg) {
                                    case AppEnumsNs.C434_HPalarmaLimpiezacolocar1: imgState = "countdownState"; break;
                                    case AppEnumsNs.C433_HPalarmaLimpiezacolocar0: imgState = "waitUserState"; break;
                                    case AppEnumsNs.C432_HPalarmaLimpieza1: imgState = "cleaningState"; break;
                                    case AppEnumsNs.C431_HPalarmaLimpieza0: imgState = "waitVacuumState"; break;
                                    }

                                      switch(hpIndex) {
                                          case AppEnumsNs.APP_GUI_HP1_ID: if(state === "hp1State") { cleanImg.state = imgState } break;
                                          case AppEnumsNs.APP_GUI_HP2_ID: if(state === "hp2State") { cleanImg.state = imgState } break;
                                          case AppEnumsNs.APP_GUI_HP3_ID: if(state === "hp3State") { cleanImg.state = imgState } break;
                                          case AppEnumsNs.APP_GUI_HP4_ID: if(state === "hp4State") { cleanImg.state = imgState } break;
                                          default: break;
                                      }
                                  }
    }
}





/*##^##
Designer {
    D{i:0;height:334;width:284}
}
##^##*/
