import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0

Item {
    id: item1
    width: Constants.width
    height: Constants.height
    property alias tinyCurvedVisible: watermarkTinyCurvedImg.visible
    property alias tinyVisible: watermarkTinyImg.visible
    property alias angledVisible: watermarkAngledImg.visible
    property alias straightVisible: watermarkStraightImg.visible
    property alias ovalCurvedVisible: watermarkOvalCurvedImg.visible
    property alias tightVisible: watermarkTightImg.visible
    property alias doubleVisible: watermarkDoubleImg.visible
    property alias ovalVisible: watermarkOvalImg.visible
    property alias curvedVisible: watermarkCurvedImg.visible

    Image {
        id: recommendedHpBackgroundImg
        x: 311
        y: 178
        source: "images/c284_PopUpSugerenciasFondo_03.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: watermarkCurvedImg
        x: 357
        y: 214
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
        x: 577
        anchors.top: watermarkCurvedImg.top
        source: "images/c290_PopUpMarcaaguaDouble.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: watermarkOvalImg
        x: 468
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
        y: 477
        anchors.left: watermarkCurvedImg.left
        source: "images/c293_PopUpMarcaaguaAngled.png"
        fillMode: Image.PreserveAspectFit
    }

    onVisibleChanged: cbkWpr.popupVisibleChanged(AppEnumsNs.popUpRecomm, visible)
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
