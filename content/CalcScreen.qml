import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0

Item {
    id: calculator
    width: Constants.width
    height: Constants.height

    Image {
        id: c265_Calculadorafondo_03
        y: 134
        source: "images/c265_Calculadorafondo_03.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }

    TwoStateButton {
        id: calcButtonComma
        x: 486
        y: 499
        imageSourceReleased: "images/c263_CalculadorabotoncomaRls.png"
        imageSourcePressed: "images/c278_CalculadorabotoncomaPress.png"
    }

    TwoStateButton {
        id: calcButtonCE
        x: 637
        y: 248
        imageSourceReleased: "images/c261_CalculadorabotonCERls.png"
        imageSourcePressed: "images/c279_CalculadorabotonCEPress.png"
        button.onReleased: cbkWpr.buttonCECalc()
    }

    TwoStateButton {
        id: calcButtonPlus
        x: 637
        y: 332
        imageSourceReleased: "images/c259_CalculadorabotonmasRls.png"
        imageSourcePressed: "images/c276_CalculadorabotonmasPress.png"
    }

    TwoStateButton {
        id: calcButtonMinus
        x: 637
        y: 416
        imageSourceReleased: "images/c260_CalculadorabotonmenosRls.png"
        imageSourcePressed: "images/c277_CalculadorabotonmenosPress.png"
    }

    TwoStateButton {
        id: calcButtonEnter
        x: 609
        y: 499
        imageSourceReleased: "images/c262_CalculadorabotonenterRls.png"
        imageSourcePressed: "images/c275_CalculadorabotonenterPress.png"
        button.onReleased: cbkWpr.buttonEnterCalc()
    }

    TwoStateButton {
        id: calcButton1
        x: 307
        y: 416
        imageSourceReleased: "images/c237_Calculadoraboton1Rls.png"
        imageSourcePressed: "images/c266_Calculadoraboton1Press.png"
        button.onReleased: cbkWpr.buttonNumCalc(1)
    }

    TwoStateButton {
        id: calcButton2
        x: 397
        y: 416
        imageSourceReleased: "images/c238_Calculadoraboton2Rls.png"
        imageSourcePressed: "images/c267_Calculadoranumero2Press.png"
        button.onPressed: cbkWpr.buttonNumCalc(2)
    }

    TwoStateButton {
        id: calcButton3
        x: 486
        y: 416
        imageSourceReleased: "images/c239_Calculadoraboton3Rls.png"
        imageSourcePressed: "images/c268_Calculadoraboton3Press.png"
        button.onReleased: cbkWpr.buttonNumCalc(3)
    }

    TwoStateButton {
        id: calcButton4
        x: 307
        y: 332
        imageSourceReleased: "images/c240_Calculadoraboton4Rls.png"
        imageSourcePressed: "images/c269_Calculadoraboton4Press.png"
        button.onReleased: cbkWpr.buttonNumCalc(4)
    }

    TwoStateButton {
        id: calcButton5
        x: 397
        y: 332
        imageSourceReleased: "images/c241_Calculadoraboton5Rls.png"
        imageSourcePressed: "images/c270_Calculadoraboton5Press.png"
        button.onReleased: cbkWpr.buttonNumCalc(5)
    }

    TwoStateButton {
        id: calcButton6
        x: 486
        y: 332
        imageSourceReleased: "images/c242_Calculadoraboton6Rls.png"
        imageSourcePressed: "images/c271_Calculadoranumero6Press.png"
        button.onReleased: cbkWpr.buttonNumCalc(6)
    }

    TwoStateButton {
        id: calcButton7
        x: 307
        y: 248
        imageSourceReleased: "images/c243_Calculadoraboton7Rls.png"
        imageSourcePressed: "images/c272_Calculadoraboton7Press.png"
        button.onReleased: cbkWpr.buttonNumCalc(7)
    }

    TwoStateButton {
        id: calcButton8
        x: 397
        y: 248
        imageSourceReleased: "images/c244_Calculadoraboton8Rls.png"
        imageSourcePressed: "images/c273_Calculadoraboton8Press.png"
        button.onPressed: cbkWpr.buttonNumCalc(8)
    }

    TwoStateButton {
        id: calcButton9
        x: 486
        y: 248
        imageSourceReleased: "images/c245_Calculadoraboton9Rls.png"
        imageSourcePressed: "images/c274_Calculadoranumero9Press.png"
        button.onReleased: cbkWpr.buttonNumCalc(9)
    }

    TwoStateButton {
        id: calcButton0
        x: 307
        y: 499
        imageSourceReleased: "images/c247_Calculadoraboton0Rls.png"
        imageSourcePressed: "images/c275_Calculadoraboton0Press.png"
        button.onReleased: cbkWpr.buttonNumCalc(0)
    }

    Text {
        id: displayedNumberText
        x: 365
        y: 146
        width: 330
        height: 76
        color: "#ffffff"
        text: wdgWpr.calcNumber
        font.pixelSize: 62
        horizontalAlignment: Text.AlignRight
        maximumLineCount: 1
        font.bold: false
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.5;height:768;width:1024}
}
##^##*/
