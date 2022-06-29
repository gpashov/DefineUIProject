import QtQuick 2.15
import QtQuick.Controls 2.15
import define.enums 1.0

Item {
    id: statusImage
    property alias statusImageState: statusImage.state

    TwoStateButton {
        id: twoStateButton
        imageSourcePressed: "images/c112_4_ZonaSeleccionadaHP4.png"
        imageSourceReleased: "images/c112_4_ZonaSeleccionadaHP4.png"
        button.onReleased: cbkWpr.butModelImage(AppEnumsNs.APP_GUI_HP4_ID)
    }

    states: [
        State {
            name: "hpNotConnected"
        },
        State {
            name: "hpModelCurvedState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c075_ImgCurvedHP_R_Rls.png"
                imageSourcePressed: "images/c093_ImgCurvedHP_R_Press.png"
            }
        },
        State {
            name: "hpModelTightState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c077_ImgTightHP_R_Rls.png"
                imageSourcePressed: "images/c095_ImgTightHP_R_Press.png"
            }
        },
        State {
            name: "hpModelStraightState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c079_ImgStrightHP_R_Rls.png"
                imageSourcePressed: "images/c097_ImgStrightHP_R_Press.png"
            }
        },
        State {
            name: "hpModelTinyState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c081_ImgTinyHP_R_Rls.png"
                imageSourcePressed: "images/c099_ImgTinyHP_R_Press.png"
            }
        },
        State {
            name: "hpModelTinyCurvedState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c083_ImgTinyCurvedHP_R_Rls.png"
                imageSourcePressed: "images/c101_ImgTinyCurvedHP_R_Press.png"
            }
        },
        State {
            name: "hpModelDoubleState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c085_ImgDoubleHP_R_Rls.png"
                imageSourcePressed: "images/c103_ImgDoubleHP_R_Press.png"
            }
        },
        State {
            name: "hpModelOvalState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c087_ImgOvalHP_R_Rls.png"
                imageSourcePressed: "images/c105_ImgOvalHP_R_Press.png"
            }
        },
        State {
            name: "hpModelOvalCurvedState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c089_ImgOvalCurvedHP_R_Rls.png"
                imageSourcePressed: "images/c107_ImgOvalCurvedHP_R_Press.png"
            }
        },
        State {
            name: "hpModelAngledState"

            PropertyChanges {
                target: twoStateButton
                imageSourceReleased: "images/c091_ImgAngledHP_R_Rls.png"
                imageSourcePressed: "images/c109_ImgAngledHP_R_Press.png"
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
                                            if (hpIndex === AppEnumsNs.APP_GUI_HP4_ID) {
                                                 switch (idImg) {
                                                     case AppEnumsNs.C093_ImgCurvedHP_R_Press:
                                                     case AppEnumsNs.C094_ImgCurvedHP_L_Press: state = "hpModelCurvedState"; break;
                                                     case AppEnumsNs.C095_ImgTightHP_R_Press:
                                                     case AppEnumsNs.C096_ImgTightHP_L_Press: state = "hpModelTightState"; break;
                                                     case AppEnumsNs.C097_ImgStrightHP_R_Press:
                                                     case AppEnumsNs.C098_ImgStrightHP_L_Press: state = "hpModelStraightState"; break;
                                                     case AppEnumsNs.C099_ImgTinyHP_R_Press:
                                                     case AppEnumsNs.C100_ImgTinyHP_L_Press: state = "hpModelTinyState"; break;
                                                     case AppEnumsNs.C101_ImgTinyCurvedHP_R_Press:
                                                     case AppEnumsNs.C102_ImgTinyCurvedHP_L_Press: state = "hpModelTinyCurvedState"; break;
                                                     case AppEnumsNs.C103_ImgDoubleHP_R_Press:
                                                     case AppEnumsNs.C104_ImgDoubleHP_L_Press: state = "hpModelDoubleState"; break;
                                                     case AppEnumsNs.C105_ImgOvalHP_R_Press:
                                                     case AppEnumsNs.C106_ImgOvalHP_L_Press: state = "hpModelOvalState"; break;
                                                     case AppEnumsNs.C107_ImgOvalCurvedHP_R_Press:
                                                     case AppEnumsNs.C108_ImgOvalCurvedHP_L_Press: state = "hpModelOvalCurvedState"; break;
                                                     case AppEnumsNs.C109_ImgAngledHP_R_Press:
                                                     case AppEnumsNs.C110_ImgAngledHP_L_Press: state = "hpModelAngledState"; break;

                                                     case AppEnumsNs.C430_HPalarmaResucciones: state = "WarningRepositionHp"; break;
                                                     case AppEnumsNs.C438_HPalarmaPlicainsuficiente: state = "WarningInsufficientPlica"; break;
                                                     case AppEnumsNs.C233_ImgPixelBlanco:
                                                     default: state = "HpNotConnected"; break;
                                                 }
                                             }
                                         }
    }

    Connections {
        target: wdgWpr
        onHpImageButtonEnabled: (hpIndex, enable) => {
                                    if (hpIndex === AppEnumsNs.APP_GUI_HP4_ID) {
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
