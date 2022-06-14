import QtQuick 2.15
import QtQuick.Controls 2.15
import define.enums 1.0

Item {
    id: statusImage
    property alias statusImageState: statusImage.state

    TwoStateButton {
        id: imageButton
        imageSourcePressed: "images/c112_1_ZonaSeleccionadaHP1.png"
        imageSourceReleased: "images/c112_1_ZonaSeleccionadaHP1.png"
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
                                            if (hpIndex === AppEnumsNs.APP_GUI_HP1_ID) {
                                                 switch (idImg) {
                                                     case c093_ImgCurvedHP_R_Press:
                                                     case c094_ImgCurvedHP_L_Press: state = "hpModelCurvedState"; break;
                                                     case c095_ImgTightHP_R_Press:
                                                     case c096_ImgTightHP_L_Press: state = "hpModelTightState"; break;
                                                     case c097_ImgStrightHP_R_Press:
                                                     case c098_ImgStrightHP_L_Press: state = "hpModelStraightState"; break;
                                                     case c099_ImgTinyHP_R_Press:
                                                     case c100_ImgTinyHP_L_Press: state = "hpModelTinyState"; break;
                                                     case c101_ImgTinyCurvedHP_R_Press:
                                                     case c102_ImgTinyCurvedHP_L_Press: state = "hpModelTinyCurvedState"; break;
                                                     case c103_ImgDoubleHP_R_Press:
                                                     case c104_ImgDoubleHP_L_Press: state = "hpModelDoubleState"; break;
                                                     case c105_ImgOvalHP_R_Press:
                                                     case c106_ImgOvalHP_L_Press: state = "hpModelOvalState"; break;
                                                     case c107_ImgOvalCurvedHP_R_Press:
                                                     case c108_ImgOvalCurvedHP_L_Press: state = "hpModelOvalCurvedState"; break;
                                                     case c109_ImgAngledHP_R_Press:
                                                     case c110_ImgAngledHP_L_Press: state = "hpModelAngledState"; break;

                                                     case c430_HPalarmaResucciones: state = "WarningRepositionHp"; break;
                                                     case c438_HPalarmaPlicainsuficiente: state = "WarningInsufficientPlica"; break;
                                                     case c233_ImgPixelBlanco:
                                                     default: state = "HpNotConnected"; break;
                                                 }
                                             }
                                         }
    }

    Connections {
        target: wdgWpr
        onHpImageButtonEnabled: (hpIndex, enable) => {
                                    if (hpIndex === AppEnumsNs.APP_GUI_HP1_ID) {
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
