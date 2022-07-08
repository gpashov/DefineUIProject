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
    }

    TwoStateButton {
        id: cleanBtn
        x: 44
        y: 178
        imageSourceReleased: "images/c456_MenuLimpiezaClean_Rls.png"
        imageSourcePressed: "images/c457_MenuLimpiezaClean_Press.png"
        button.onReleased:  {
            switch (parent.state) {
            case "hp1State": cbkWpr.butPopUpCleanUp(AppEnumsNs.APP_GUI_HP1_ID); break;
            case "hp2State": cbkWpr.butPopUpCleanUp(AppEnumsNs.APP_GUI_HP2_ID); break;
            case "hp3State": cbkWpr.butPopUpCleanUp(AppEnumsNs.APP_GUI_HP3_ID); break;
            case "hp4State": cbkWpr.butPopUpCleanUp(AppEnumsNs.APP_GUI_HP4_ID); break;
            default: break;
            }
        }
    }

    TwoStateButton {
        id: yesBtn
        x: 44
        y: 101
        imageSourceReleased: "images/c453_MenuAlarmaOK_rls.png"
        imageSourcePressed: "images/c452_MenuAlarmaOK_press.png"
        button.onReleased:  {
            switch (parent.state) {
            case "hp1State": cbkWpr.butPopUpCleanUpYES(AppEnumsNs.APP_GUI_HP1_ID); break;
            case "hp2State": cbkWpr.butPopUpCleanUpYES(AppEnumsNs.APP_GUI_HP2_ID); break;
            case "hp3State": cbkWpr.butPopUpCleanUpYES(AppEnumsNs.APP_GUI_HP3_ID); break;
            case "hp4State": cbkWpr.butPopUpCleanUpYES(AppEnumsNs.APP_GUI_HP4_ID); break;
            default: break;
            }
        }
    }

    TwoStateButton {
        id: noBtn
        x: 121
        y: 101
        imageSourceReleased: "images/c455_MenuAlarmaNO_rls.png"
        imageSourcePressed: "images/c454_MenuAlarmaNO_press.png"
        button.onReleased:  {
            switch (parent.state) {
            case "hp1State": cbkWpr.butPopUpCleanUpNO(AppEnumsNs.APP_GUI_HP1_ID); break;
            case "hp2State": cbkWpr.butPopUpCleanUpNO(AppEnumsNs.APP_GUI_HP2_ID); break;
            case "hp3State": cbkWpr.butPopUpCleanUpNO(AppEnumsNs.APP_GUI_HP3_ID); break;
            case "hp4State": cbkWpr.butPopUpCleanUpNO(AppEnumsNs.APP_GUI_HP4_ID); break;
            default: break;
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
    }

    Image {
        id: cleanImg
        x: 149
        y: 191
        source: "images/c082_ImgTinyHP_L_Rls.png"
        fillMode: Image.PreserveAspectFit
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
}



/*##^##
Designer {
    D{i:0;height:334;width:284}
}
##^##*/
