import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 1024
    height: 768

    TwoStateButton {
        id: homeButton
        y: 678
        imageSourceReleased: "images/b013_BotonHomePress.png"
        imageSourcePressed: "images/b014_BotonHomeRls.png"
        button.onReleased: cbkWpr.butHome()
    }

    Image {
        id: step1Img
        x: 26
        y: 77
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step2Img
        anchors.left: step1Img.left
        y: 166
        source: "images/c053_Numero2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step3Img
        anchors.left: step1Img.left
        y: 256
        source: "images/c054_Numero3.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step4Img
        anchors.left: step1Img.left
        y: 346
        source: "images/c055_Numero4.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step5Img
        anchors.left: step1Img.left
        y: 435
        source: "images/c056_Numero5.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step6Img
        anchors.left: step1Img.left
        y: 525
        source: "images/c057_Numero6.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step7Img
        anchors.left: step1Img.left
        y: 614
        source: "images/c058_Numero7.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: vac1Img
        x: 269
        anchors.top: step1Img.top
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: vac2Img
        anchors.left: vac1Img.left
        anchors.top: step2Img.top
        source: "images/c053_Numero2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: vac3Img
        anchors.left: vac1Img.left
        anchors.top: step3Img.top
        source: "images/c054_Numero3.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: vac4Img
        anchors.left: vac1Img.left
        anchors.top: step4Img.top
        source: "images/c055_Numero4.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: flow1Img
        x: 806
        anchors.top: step1Img.top
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: flow2Img
        anchors.left: flow1Img.left
        anchors.top: step2Img.top
        source: "images/c053_Numero2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: flow3Img
        anchors.left: flow1Img.left
        anchors.top: step3Img.top
        source: "images/c054_Numero3.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: flow4Img
        anchors.left: flow1Img.left
        anchors.top: step4Img.top
        source: "images/c055_Numero4.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: tampAmbImg
        x: 550
        anchors.top: step1Img.top
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: tempPumpImg
        anchors.left: tampAmbImg.left
        anchors.top: step2Img.top
        source: "images/c053_Numero2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: tempReturnImg
        anchors.left: tampAmbImg.left
        anchors.top: step3Img.top
        source: "images/c054_Numero3.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: flowReturnImg
        anchors.left: tampAmbImg.left
        anchors.top: step4Img.top
        source: "images/c055_Numero4.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: vNozzleImg
        anchors.left: tampAmbImg.left
        anchors.top: step5Img.top
        source: "images/c056_Numero5.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: rthImg
        anchors.left: tampAmbImg.left
        anchors.top: step6Img.top
        source: "images/c057_Numero6.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: cpiImg
        anchors.left: tampAmbImg.left
        anchors.top: step7Img.top
        source: "images/c058_Numero7.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step1StatusImg
        x: 51
        y: 74
        source: "images/c149_ZonaAplicacionManipPuntoSelected.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step2StatusImg
        x: 51
        y: 164
        source: "images/c149_ZonaAplicacionManipPuntoSelected.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step3StatusImg
        x: 51
        y: 253
        source: "images/c149_ZonaAplicacionManipPuntoSelected.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step4StatusHP1Img
        x: 51
        y: 343
        source: "images/c149_ZonaAplicacionManipPuntoSelected.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step4StatusHP2Img
        x: 90
        y: 343
        source: "images/c149_ZonaAplicacionManipPuntoSelected.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step4StatusHP3Img
        x: 128
        y: 343
        source: "images/c149_ZonaAplicacionManipPuntoSelected.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step4StatusHP4Img
        x: 166
        y: 343
        source: "images/c149_ZonaAplicacionManipPuntoSelected.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step5StatusHP1Img
        x: 51
        y: 433
        source: "images/c149_ZonaAplicacionManipPuntoSelected.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step5StatusHP2Img
        x: 90
        y: 433
        source: "images/c149_ZonaAplicacionManipPuntoSelected.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step5StatusHP3Img
        x: 128
        y: 433
        source: "images/c149_ZonaAplicacionManipPuntoSelected.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step5StatusHP4Img
        x: 166
        y: 433
        source: "images/c149_ZonaAplicacionManipPuntoSelected.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step6StatusImg
        x: 51
        y: 522
        source: "images/c149_ZonaAplicacionManipPuntoSelected.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: step7StatusImg
        x: 51
        y: 612
        source: "images/c149_ZonaAplicacionManipPuntoSelected.png"
        fillMode: Image.PreserveAspectFit
    }

    SATValue {
        id: tempAmbNum
        x: 529
        anchors.top: step1Img.top
        anchors.topMargin: -1
        //y: 76
        number: ""
        value: "0.0"
    }

    SATValue {
        id: tempPumpNum
        anchors.left: tempAmbNum.left
        anchors.top: step2Img.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: tempReturnNum
        anchors.left: tempAmbNum.left
        anchors.top: step3Img.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: flowReturnNum
        anchors.left: tempAmbNum.left
        anchors.top: step4Img.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: vNozzleNum
        anchors.left: tempAmbNum.left
        anchors.top: step5Img.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: rthNum
        anchors.left: tempAmbNum.left
        anchors.top: step6Img.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: cpiNum
        anchors.left: tempAmbNum.left
        anchors.top: step7Img.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: flowReturnHP1Num
        x: 785
        anchors.top: step1Img.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: flowReturnHP2Num
        anchors.left: flowReturnHP1Num.left
        anchors.top: step2Img.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: flowReturnHP3Num
        anchors.left: flowReturnHP1Num.left
        anchors.top: step3Img.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: flowReturnHP4Num
        anchors.left: flowReturnHP1Num.left
        anchors.top: step4Img.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: vacuumHP1Num
        x: 273
        anchors.top: step1Img.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: vacuumHP2Num
        anchors.left: vacuumHP1Num.left
        anchors.top: step2Img.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: vacuumHP3Num
        anchors.left: vacuumHP1Num.left
        anchors.top: step3Img.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: vacuumHP4Num
        anchors.left: vacuumHP1Num.left
        anchors.top: step4Img.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: fatigueTimeNum
        x: 64
        y: 512
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: fatigueErr1Num
        x: 128
        y: 691
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: fatigueErr2Num
        x: 294
        anchors.top: fatigueErr1Num.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: fatigueErr3Num
        x: 461
        anchors.top: fatigueErr1Num.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: fatigueErr4Num
        x: 627
        anchors.top: fatigueErr1Num.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    SATValue {
        id: fatigueErr5Num
        x: 794
        anchors.top: fatigueErr1Num.top
        anchors.topMargin: -1
        number: ""
        value: "0.0"
    }

    CustomSwitch {
        id: fatigueFailBeepSwitch
        x: 1
        y: 602
        onStateImageSource: "images/b028_BotonAvisosMarcaAgua.png"
        offStateImageSource: "images/b029_BotonAvisosPress.png"
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
