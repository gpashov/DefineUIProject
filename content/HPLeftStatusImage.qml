import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    id: statusImage
    property alias statusImageState: statusImage.state

    Image {
        id: c112_1_ZonaSeleccionadaHP1
        x: 0
        y: 0
        visible: false
        source: "images/c112_1_ZonaSeleccionadaHP1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c093_ImgCurvedHP_R_Press
        x: 0
        y: 0
        visible: false
        source: "images/c093_ImgCurvedHP_R_Press.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c095_ImgTightHP_R_Press
        x: 0
        y: 0
        visible: false
        source: "images/c095_ImgTightHP_R_Press.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c097_ImgStrightHP_R_Press
        x: 0
        y: 0
        visible: false
        source: "images/c097_ImgStrightHP_R_Press.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c099_ImgTinyHP_R_Press
        x: 0
        y: 0
        visible: false
        source: "images/c099_ImgTinyHP_R_Press.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c101_ImgTinyCurvedHP_R_Press
        x: 0
        y: 0
        visible: false
        source: "images/c101_ImgTinyCurvedHP_R_Press.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c103_ImgDoubleHP_R_Press
        x: 0
        y: 0
        visible: false
        source: "images/c103_ImgDoubleHP_R_Press.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c105_ImgOvalHP_R_Press
        x: 0
        y: 0
        visible: false
        source: "images/c105_ImgOvalHP_R_Press.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c107_ImgOvalCurvedHP_R_Press
        x: 0
        y: 0
        visible: false
        source: "images/c107_ImgOvalCurvedHP_R_Press.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c109_ImgAngledHP_R_Press
        x: 0
        y: 0
        visible: false
        source: "images/c109_ImgAngledHP_R_Press.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c075_ImgCurvedHP_R_Rls
        x: 0
        y: 0
        visible: false
        source: "images/c075_ImgCurvedHP_R_Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c077_ImgTightHP_R_Rls
        x: 0
        y: 0
        visible: false
        source: "images/c077_ImgTightHP_R_Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c079_ImgStrightHP_R_Rls
        x: 0
        y: 0
        visible: false
        source: "images/c079_ImgStrightHP_R_Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c081_ImgTinyHP_R_Rls
        x: 0
        y: 0
        visible: false
        source: "images/c081_ImgTinyHP_R_Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c083_ImgTinyCurvedHP_R_Rls
        x: 0
        y: 0
        visible: false
        source: "images/c083_ImgTinyCurvedHP_R_Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c085_ImgDoubleHP_R_Rls
        x: 0
        y: 0
        visible: false
        source: "images/c085_ImgDoubleHP_R_Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c087_ImgOvalHP_R_Rls
        x: 0
        y: 0
        visible: false
        source: "images/c087_ImgOvalHP_R_Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c089_ImgOvalCurvedHP_R_Rls
        x: 0
        y: 0
        visible: false
        source: "images/c089_ImgOvalCurvedHP_R_Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c091_ImgAngledHP_R_Rls
        x: 0
        y: 0
        visible: false
        source: "images/c091_ImgAngledHP_R_Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c430_HPalarmaResucciones
        x: 0
        y: 0
        visible: false
        source: "images/c430_HPalarmaResucciones.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c438_HPalarmaPlicainsuficiente
        x: 0
        y: 0
        visible: false
        source: "images/c438_HPalarmaPlicainsuficiente.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c439_HPalarmaPlicaOK
        x: 0
        y: 0
        visible: false
        source: "images/c439_HPalarmaPlicaOK.png"
        fillMode: Image.PreserveAspectFit
    }
    states: [
        State {
            name: "HpNotConnected"

            PropertyChanges {
                target: c112_1_ZonaSeleccionadaHP1
                visible: true
            }
        },
        State {
            name: "HpCurvedPress"

            PropertyChanges {
                target: c093_ImgCurvedHP_R_Press
                visible: true
            }
        },
        State {
            name: "HpTightPress"

            PropertyChanges {
                target: c095_ImgTightHP_R_Press
                visible: true
            }
        },
        State {
            name: "HpStraightPress"

            PropertyChanges {
                target: c097_ImgStrightHP_R_Press
                visible: true
            }
        },
        State {
            name: "HpTinyPress"

            PropertyChanges {
                target: c099_ImgTinyHP_R_Press
                visible: true
            }
        },
        State {
            name: "HpTinyCurvedPress"

            PropertyChanges {
                target: c101_ImgTinyCurvedHP_R_Press
                visible: true
            }
        },
        State {
            name: "HpDoublePress"

            PropertyChanges {
                target: c103_ImgDoubleHP_R_Press
                visible: true
            }
        },
        State {
            name: "HpOvalPress"

            PropertyChanges {
                target: c105_ImgOvalHP_R_Press
                visible: true
            }
        },
        State {
            name: "HpOvalCurvedPress"

            PropertyChanges {
                target: c107_ImgOvalCurvedHP_R_Press
                visible: true
            }
        },
        State {
            name: "HpAngledPress"

            PropertyChanges {
                target: c109_ImgAngledHP_R_Press
                visible: true
            }
        },
        State {
            name: "HpCurvedRls"

            PropertyChanges {
                target: c075_ImgCurvedHP_R_Rls
                visible: true
            }
        },
        State {
            name: "HpTightRls"

            PropertyChanges {
                target: c077_ImgTightHP_R_Rls
                visible: true
            }
        },
        State {
            name: "HpStraightRls"

            PropertyChanges {
                target: c079_ImgStrightHP_R_Rls
                visible: true
            }
        },
        State {
            name: "HpTinyRls"

            PropertyChanges {
                target: c081_ImgTinyHP_R_Rls
                visible: true
            }
        },
        State {
            name: "HpTinyCurvedRls"

            PropertyChanges {
                target: c083_ImgTinyCurvedHP_R_Rls
                visible: true
            }
        },
        State {
            name: "HpDoubleRls"

            PropertyChanges {
                target: c085_ImgDoubleHP_R_Rls
                visible: true
            }
        },
        State {
            name: "HpOvalRls"

            PropertyChanges {
                target: c087_ImgOvalHP_R_Rls
                visible: true
            }
        },
        State {
            name: "HpOvalCurvedRls"

            PropertyChanges {
                target: c089_ImgOvalCurvedHP_R_Rls
                visible: true
            }
        },
        State {
            name: "HpAngledRls"

            PropertyChanges {
                target: c091_ImgAngledHP_R_Rls
                visible: true
            }
        },
        State {
            name: "WarningRepositionHp"

            PropertyChanges {
                target: c430_HPalarmaResucciones
                visible: true
            }
        },
        State {
            name: "WarningInsufficientPlica"

            PropertyChanges {
                target: c438_HPalarmaPlicainsuficiente
                visible: true
            }
        },
        State {
            name: "PlicaOK"

            PropertyChanges {
                target: c439_HPalarmaPlicaOK
                visible: true
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;height:0;width:0}
}
##^##*/
