import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0
import define.enums 1.0

Item {
    id: item1
    width: Constants.width
    height: Constants.height

    Image {
        id: recommendedHpBackgroundImg
        x: 311
        y: 178
        source: "images/c284_PopUpSugerenciasFondo_03.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: watermarkCurvedImg
        x: 356
        y: 213
        source: "images/c285_PopUpMarcaaguaCurved.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: watermarkTightImg
        y: 342
        anchors.left: watermarkCurvedImg.left
        source: "images/c286_PopUpMarcaaguaTight.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: watermarkStraightImg
        anchors.left: watermarkDoubleImg.left
        anchors.top: watermarkTightImg.top
        source: "images/c287_PopUpMarcaaguaStraight.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: watermarkTinyImg
        anchors.left: watermarkOvalImg.left
        anchors.top: watermarkAngledImg.top
        source: "images/c288_PopUpMarcaaguaTiny.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: watermarkTinyCurvedImg
        anchors.left: watermarkDoubleImg.left
        anchors.top: watermarkAngledImg.top
        source: "images/c289_PopUpMarcaaguaTinyCurved.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: watermarkDoubleImg
        x: 575
        anchors.top: watermarkCurvedImg.top
        source: "images/c290_PopUpMarcaaguaDouble.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: watermarkOvalImg
        x: 467
        anchors.top: watermarkCurvedImg.top
        source: "images/c291_PopUpMarcaaguaOval.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: watermarkOvalCurvedImg
        anchors.left: watermarkOvalImg.left
        anchors.top: watermarkTightImg.top
        source: "images/c292_PopUpMarcaaguaOvalCurved.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: watermarkAngledImg
        y: 476
        anchors.left: watermarkCurvedImg.left
        source: "images/c293_PopUpMarcaaguaAngled.png"
        fillMode: Image.PreserveAspectFit
    }

    Connections {
        target: wdgWpr
        onSuggestedHpWatermarkDisplayed: (typeWidgetId, isDispalyed) => {
                                             switch(typeWidgetId) {
                                             case AppEnumsNs.ImgPopUpRecommCurved: watermarkCurvedImg.visible = isDispalyed; break;
                                             case AppEnumsNs.ImgPopUpRecommTight: watermarkTightImg.visible = isDispalyed; break;
                                             case AppEnumsNs.ImgPopUpRecommStright: watermarkStraightImg.visible = isDispalyed; break;
                                             case AppEnumsNs.ImgPopUpRecommTiny: watermarkTinyImg.visible = isDispalyed; break;
                                             case AppEnumsNs.ImgPopUpRecommTinyCurved: watermarkTinyCurvedImg.visible = isDispalyed; break;
                                             case AppEnumsNs.ImgPopUpRecommDouble: watermarkDoubleImg.visible = isDispalyed; break;
                                             case AppEnumsNs.ImgPopUpRecommOval: watermarkOvalImg.visible = isDispalyed; break;
                                             case AppEnumsNs.ImgPopUpRecommOvalCurved: watermarkOvalCurvedImg.visible = isDispalyed; break;
                                             case AppEnumsNs.ImgPopUpRecommAngled: watermarkAngledImg.visible = isDispalyed; break;
                                             default: break;
                                             }
        }
    }
}





/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
