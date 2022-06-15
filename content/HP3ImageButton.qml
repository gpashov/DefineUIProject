import QtQuick 2.15
import QtQuick.Controls 2.15
import define.enums 1.0

Item {
    id: statusImage
    property alias statusImageState: statusImage.state

    TwoStateButton {
        id: twoStateButton
        imageSourcePressed: "images/c112_3_ZonaSeleccionadaHP3.png"
        imageSourceReleased: "images/c112_3_ZonaSeleccionadaHP3.png"
    }

    states: [
        State {
            name: "hpNotConnected"
        },
        State {
            name: "hpModelCurvedState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c076_ImgCurvedHP_L_Rls.png"
                imageSourcePressed: "images/c094_ImgCurvedHP_L_Press.png"
            }
        },
        State {
            name: "hpModelTightState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c078_ImgTightHP_L_Rls.png"
                imageSourcePressed: "images/c096_ImgTightHP_L_Press.png"
            }
        },
        State {
            name: "hpModelStraightState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c080_ImgStrightHP_L_Rls.png"
                imageSourcePressed: "images/c098_ImgStrightHP_L_Press.png"
            }
        },
        State {
            name: "hpModelTinyState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c082_ImgTinyHP_L_Rls.png"
                imageSourcePressed: "images/c100_ImgTinyHP_L_Press.png"
            }
        },
        State {
            name: "hpModelTinyCurvedState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c084_ImgTinyCurvedHP_L_Rls.png"
                imageSourcePressed: "images/c102_ImgTinyCurvedHP_L_Press.png"
            }
        },
        State {
            name: "hpModelDoubleState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c086_ImgDoubleHP_L_Rls.png"
                imageSourcePressed: "images/c104_ImgDoubleHP_L_Press.png"
            }
        },
        State {
            name: "hpModelOvalState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c088_ImgOvalHP_L_Rls.png"
                imageSourcePressed: "images/c106_ImgOvalHP_L_Press.png"
            }
        },
        State {
            name: "hpModelOvalCurvedState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c090_ImgOvalCurvedHP_L_Rls.png"
                imageSourcePressed: "images/c108_ImgOvalCurvedHP_L_Press.png"
            }
        },
        State {
            name: "hpModelAngledState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c092_ImgAngledHP_L_Rls.png"
                imageSourcePressed: "images/c110_ImgAngledHP_L_Press.png"
            }
        },
        State {
            name: "WarningRepositionHp"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c430_HPalarmaResucciones.png"
                imageSourcePressed: "images/c430_HPalarmaResucciones.png"
            }
        },
        State {
            name: "WarningInsufficientPlica"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c438_HPalarmaPlicainsuficiente.png"
                imageSourcePressed: "images/c438_HPalarmaPlicainsuficiente.png"
            }
        }
    ]

    Connections {
        target: wdgWpr
        onHpControlPanelButtonImagesSet: (hpIndex, idImg) => {
                                            if (hpIndex === AppEnumsNs.APP_GUI_HP3_ID) {
                                                 switch (idImg) {
                                                     case AppEnumsNs.c093_ImgCurvedHP_R_Press:
                                                     case AppEnumsNs.c094_ImgCurvedHP_L_Press: state = "hpModelCurvedState"; break;
                                                     case AppEnumsNs.c095_ImgTightHP_R_Press:
                                                     case AppEnumsNs.c096_ImgTightHP_L_Press: state = "hpModelTightState"; break;
                                                     case AppEnumsNs.c097_ImgStrightHP_R_Press:
                                                     case AppEnumsNs.c098_ImgStrightHP_L_Press: state = "hpModelStraightState"; break;
                                                     case AppEnumsNs.c099_ImgTinyHP_R_Press:
                                                     case AppEnumsNs.c100_ImgTinyHP_L_Press: state = "hpModelTinyState"; break;
                                                     case AppEnumsNs.c101_ImgTinyCurvedHP_R_Press:
                                                     case AppEnumsNs.c102_ImgTinyCurvedHP_L_Press: state = "hpModelTinyCurvedState"; break;
                                                     case AppEnumsNs.c103_ImgDoubleHP_R_Press:
                                                     case AppEnumsNs.c104_ImgDoubleHP_L_Press: state = "hpModelDoubleState"; break;
                                                     case AppEnumsNs.c105_ImgOvalHP_R_Press:
                                                     case AppEnumsNs.c106_ImgOvalHP_L_Press: state = "hpModelOvalState"; break;
                                                     case AppEnumsNs.c107_ImgOvalCurvedHP_R_Press:
                                                     case AppEnumsNs.c108_ImgOvalCurvedHP_L_Press: state = "hpModelOvalCurvedState"; break;
                                                     case AppEnumsNs.c109_ImgAngledHP_R_Press:
                                                     case AppEnumsNs.c110_ImgAngledHP_L_Press: state = "hpModelAngledState"; break;

                                                     case AppEnumsNs.c430_HPalarmaResucciones: state = "WarningRepositionHp"; break;
                                                     case AppEnumsNs.c438_HPalarmaPlicainsuficiente: state = "WarningInsufficientPlica"; break;
                                                     case AppEnumsNs.c233_ImgPixelBlanco:
                                                     default: state = "HpNotConnected"; break;
                                                 }
                                             }
                                         }
    }

    Connections {
        target: wdgWpr
        onHpImageButtonEnabled: (hpIndex, enable) => {
                                    if (hpIndex === AppEnumsNs.APP_GUI_HP3_ID) {
                                        imageButton.enabled = enable;
                                    }
                                }
    }
}

/*##^##
Designer {
    D{i:0;height:0;width:0}
}
##^##*/
