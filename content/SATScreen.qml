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

    Text {
        id: pageText
        x: 141
        y: 691
        color: "#015e76"
        text: "0"
        font.pixelSize: 24
        horizontalAlignment: Text.AlignHCenter
        font.family: "Verdana"
    }

    TwoStateButton {
        id: nextPageButton
        x: 307
        y: 704
        imageSourceReleased: "images/c199_BotonGuardarMenuRightPress.png"
        imageSourcePressed: "images/c200_BotonGuardarMenuRightRls.png"
    }

    TwoStateButton {
        id: prevPageButton
        x: 90
        anchors.top: nextPageButton.top
        anchors.topMargin: 0
        imageSourceReleased: "images/c202_BotonGuardarMenuLeftPress.png"
        imageSourcePressed: "images/c203_BotonGuardarMenuLeftRls.png"
    }
/*
    Image {
        id: num1
        x: 26
        y: 77
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num2
        y: 166
        anchors.left: num1.left
        source: "images/c053_Numero2.png"
        anchors.leftMargin: 0
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num3
        y: 256
        anchors.left: num1.left
        source: "images/c054_Numero3.png"
        anchors.leftMargin: 0
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num4
        y: 346
        anchors.left: num1.left
        source: "images/c055_Numero4.png"
        anchors.leftMargin: 0
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num5
        y: 435
        anchors.left: num1.left
        source: "images/c056_Numero5.png"
        anchors.leftMargin: 0
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num6
        y: 525
        anchors.left: num1.left
        source: "images/c057_Numero6.png"
        anchors.leftMargin: 0
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num7
        y: 614
        anchors.left: num1.left
        source: "images/c058_Numero7.png"
        anchors.leftMargin: 0
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num8
        x: 269
        anchors.top: num1.top
        source: "images/c059_Numero8.png"
        anchors.topMargin: 0
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num9
        anchors.left: num8.left
        anchors.top: num2.top
        source: "images/c060_Numero9.png"
        anchors.leftMargin: 0
        anchors.topMargin: 0
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num10_1
        x: 236
        anchors.top: num3.top
        source: "images/c052_Numero1.png"
        anchors.topMargin: 0
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num10_2
        anchors.left: num8.left
        anchors.top: num3.top
        source: "images/c061_Numero0.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num11_1
        anchors.left: num10_1.left
        anchors.top: num4.top
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num11_2
        anchors.left: num8.left
        anchors.top: num4.top
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num12_1
        anchors.left: num10_1.left
        anchors.top: num5.top
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num12_2
        anchors.left: num8.left
        anchors.top: num5.top
        source: "images/c053_Numero2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num13_1
        anchors.left: num10_1.left
        anchors.top: num6.top
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num13_2
        anchors.left: num8.left
        anchors.top: num6.top
        source: "images/c054_Numero3.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num14_1
        anchors.left: num10_1.left
        anchors.top: num7.top
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num14_2
        anchors.left: num8.left
        anchors.top: num7.top
        source: "images/c055_Numero4.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num15_1
        x: 517
        anchors.top: num1.top
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num15_2
        x: 550
        anchors.top: num1.top
        source: "images/c056_Numero5.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num16_1
        anchors.left: num15_1.left
        anchors.top: num2.top
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num16_2
        anchors.left: num15_2.left
        anchors.top: num2.top
        source: "images/c057_Numero6.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num17_1
        anchors.left: num15_1.left
        anchors.top: num3.top
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num17_2
        anchors.left: num15_2.left
        anchors.top: num3.top
        source: "images/c058_Numero7.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num18_1
        anchors.left: num15_1.left
        anchors.top: num4.top
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num18_2
        anchors.left: num15_2.left
        anchors.top: num4.top
        source: "images/c059_Numero8.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num19_1
        anchors.left: num15_1.left
        anchors.top: num5.top
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num19_2
        anchors.left: num15_2.left
        anchors.top: num5.top
        source: "images/c060_Numero9.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num20_1
        anchors.left: num15_1.left
        anchors.top: num6.top
        source: "images/c053_Numero2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num20_2
        anchors.left: num15_2.left
        anchors.top: num6.top
        source: "images/c061_Numero0.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num21_1
        anchors.left: num15_1.left
        anchors.top: num7.top
        source: "images/c053_Numero2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num21_2
        anchors.left: num15_2.left
        anchors.top: num7.top
        source: "images/c052_Numero1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num22_1
        x: 773
        anchors.top: num1.top
        source: "images/c053_Numero2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num22_2
        x: 806
        anchors.top: num1.top
        source: "images/c053_Numero2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num23_1
        anchors.left: num22_1.left
        anchors.top: num2.top
        source: "images/c053_Numero2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num23_2
        anchors.left: num22_2.left
        anchors.top: num2.top
        source: "images/c054_Numero3.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num24_1
        anchors.left: num22_1.left
        anchors.top: num3.top
        source: "images/c053_Numero2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num24_2
        anchors.left: num22_2.left
        anchors.top: num3.top
        source: "images/c055_Numero4.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num25_1
        anchors.left: num22_1.left
        anchors.top: num4.top
        source: "images/c053_Numero2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num25_2
        anchors.left: num22_2.left
        anchors.top: num4.top
        source: "images/c056_Numero5.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num26_1
        anchors.left: num22_1.left
        anchors.top: num5.top
        source: "images/c053_Numero2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num26_2
        anchors.left: num22_2.left
        anchors.top: num5.top
        source: "images/c057_Numero6.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num27_1
        anchors.left: num22_1.left
        anchors.top: num6.top
        source: "images/c053_Numero2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num27_2
        anchors.left: num22_2.left
        anchors.top: num6.top
        source: "images/c058_Numero7.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num28_1
        anchors.left: num22_1.left
        anchors.top: num7.top
        source: "images/c053_Numero2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: num28_2
        anchors.left: num22_2.left
        anchors.top: num7.top
        source: "images/c059_Numero8.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: valueBackgroundImg01
        anchors.left: val01.left
        anchors.top: val01.top
        source: "images/c047_FondoNumVwrBlanco.png"
    }

    Text {
        id: val01
        x: 64
        y: 64
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Image {
        id: valueBackgroundImg02
        anchors.left: val01.left
        anchors.top: val02.top
        source: "images/c047_FondoNumVwrBlanco.png"
    }

    Text {
        id: val02
        anchors.left: val01.left
        y: 154
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Image {
        id: valueBackgroundImg03
        anchors.left: val01.left
        anchors.top: val03.top
        source: "images/c047_FondoNumVwrBlanco.png"
    }

    Text {
        id: val03
        anchors.left: val01.left
        y: 243
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Image {
        id: valueBackgroundImg04
        anchors.left: val01.left
        anchors.top: val04.top
        source: "images/c047_FondoNumVwrBlanco.png"
    }

    Text {
        id: val04
        anchors.left: val01.left
        y: 333
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Image {
        id: valueBackgroundImg05
        anchors.left: val01.left
        anchors.top: val05.top
        source: "images/c047_FondoNumVwrBlanco.png"
    }

    Text {
        id: val05
        anchors.left: val01.left
        y: 422
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Image {
        id: valueBackgroundImg06
        anchors.left: val01.left
        anchors.top: val06.top
        source: "images/c047_FondoNumVwrBlanco.png"
    }

    Text {
        id: val06
        anchors.left: val01.left
        y: 512
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Image {
        id: valueBackgroundImg07
        anchors.left: val01.left
        anchors.top: val07.top
        source: "images/c047_FondoNumVwrBlanco.png"
    }

    Text {
        id: val07
        anchors.left: val01.left
        y: 602
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Image {
        id: valueBackgroundImg08
        anchors.left: val08.left
        anchors.top: val08.top
        source: "images/c047_FondoNumVwrBlanco.png"
    }

    Text {
        id: val08
        x: 307
        anchors.top: val01.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Image {
        id: valueBackgroundImg09
        anchors.left: val08.left
        anchors.top: val09.top
        source: "images/c047_FondoNumVwrBlanco.png"
    }

    Text {
        id: val09
        anchors.left: val08.left
        anchors.top: val02.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Image {
        id: valueBackgroundImg10
        anchors.left: val08.left
        anchors.top: val10.top
        source: "images/c047_FondoNumVwrBlanco.png"
    }

    Text {
        id: val10
        anchors.left: val08.left
        anchors.top: val03.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Image {
        id: valueBackgroundImg11
        anchors.left: val08.left
        anchors.top: val11.top
        source: "images/c047_FondoNumVwrBlanco.png"
    }

    Text {
        id: val11
        anchors.left: val08.left
        anchors.top: val04.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Image {
        id: valueBackgroundImg12
        anchors.left: val08.left
        anchors.top: val12.top
        source: "images/c047_FondoNumVwrBlanco.png"
    }

    Text {
        id: val12
        anchors.left: val08.left
        anchors.top: val05.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Image {
        id: valueBackgroundImg13
        anchors.left: val08.left
        anchors.top: val13.top
        source: "images/c047_FondoNumVwrBlanco.png"
    }

    Text {
        id: val13
        anchors.left: val08.left
        anchors.top: val06.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Image {
        id: valueBackgroundImg14
        anchors.left: val08.left
        anchors.top: val14.top
        source: "images/c047_FondoNumVwrBlanco.png"
    }

    Text {
        id: val14
        anchors.left: val08.left
        anchors.top: val07.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Image {
        id: valueBackgroundImg15
        anchors.left: val15.left
        anchors.top: val15.top
        source: "images/c047_FondoNumVwrBlanco.png"
    }

    Text {
        id: val15
        x: 559
        anchors.top: val01.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Text {
        id: val16
        anchors.left: val15.left
        anchors.top: val02.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Text {
        id: val17
        anchors.left: val15.left
        anchors.top: val03.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Text {
        id: val18
        anchors.left: val15.left
        anchors.top: val04.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Text {
        id: val19
        anchors.left: val16.left
        anchors.top: val05.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Text {
        id: val20
        anchors.left: val17.left
        anchors.top: val06.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Text {
        id: val21
        anchors.left: val18.left
        anchors.top: val07.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Text {
        id: val22
        x: 845
        anchors.top: val01.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Text {
        id: val23
        anchors.left: val22.left
        anchors.top: val02.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Text {
        id: val24
        anchors.left: val22.left
        anchors.top: val03.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Text {
        id: val25
        anchors.left: val22.left
        anchors.top: val04.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Text {
        id: val26
        anchors.left: val22.left
        anchors.top: val05.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Text {
        id: val27
        anchors.left: val22.left
        anchors.top: val06.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    Text {
        id: val28
        anchors.left: val22.left
        anchors.top: val07.top
        width: 138
        height: 59
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }
*/
    Image {
        id: coolImg
        x: 397
        y: 678
        source: "images/c186_IndicadorFrioHP1Off.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: vacuumImg
        x: 486
        y: 678
        source: "images/c185_IndicadorVacHP1Off.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: rfidImg
        x: 576
        y: 678
        source: "images/c183_IndicadorRFIDHP1Off.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: testLedImg
        x: 730
        y: 653
        source: "images/c184_IndicadorBotonHP1Off.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: testLedStatusImg
        x: 755
        y: 678
        source: "images/c184_IndicadorBotonHP1Off.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: testLedRgbImg
        x: 662
        y: 675
        source: "images/b032_ImgNotificacion.png"
        fillMode: Image.PreserveAspectFit
    }

    CustomSwitch {
        id: coolSwitch
        x: 378
        y: 717
        offStateImageSource: "images/c045_BotonAutoRls.png"
        onStateImageSource: "images/c044_BotonAutoPress.png"
    }

    CustomSwitch {
        id: vacuumSwitch
        x: 467
        y: 717
        offStateImageSource: "images/c045_BotonAutoRls.png"
        onStateImageSource: "images/c044_BotonAutoPress.png"
    }

    CustomSwitch {
        id: rfidSwitch
        x: 557
        y: 717
        offStateImageSource: "images/c045_BotonAutoRls.png"
        onStateImageSource: "images/c044_BotonAutoPress.png"
    }

    CustomSwitch {
        id: testLedSwitch
        x: 870
        y: 704
        offStateImageSource: "images/c045_BotonAutoRls.png"
        onStateImageSource: "images/c044_BotonAutoPress.png"
    }

    CustomSwitch {
        id: testLedRgbSwitch
        x: 646
        y: 717
        offStateImageSource: "images/c045_BotonAutoRls.png"
        onStateImageSource: "images/c044_BotonAutoPress.png"
    }

    SATValue {
        id: satValue01
        x: 4
        y: 64
        number: "1"
        value: "21.2"
    }

    SATValue {
        id: satValue02
        anchors.left: satValue01.left
        y: 153
        number: "2"
        value: "21.2"
    }

    SATValue {
        id: satValue03
        anchors.left: satValue01.left
        y: 242
        number: "3"
        value: "21.2"
    }

    SATValue {
        id: satValue04
        anchors.left: satValue01.left
        y: 331
        number: "4"
        value: "21.2"
    }

    SATValue {
        id: satValue05
        anchors.left: satValue01.left
        y: 420
        number: "5"
        value: "21.2"
    }

    SATValue {
        id: satValue06
        anchors.left: satValue01.left
        y: 509
        number: "6"
        value: "21.2"
    }

    SATValue {
        id: satValue07
        anchors.left: satValue01.left
        y: 598
        visible: true
        number: "7"
        value: "21.2"
    }

    SATValue {
        id: satValue08
        x: 260
        anchors.top: satValue01.top
        visible: true
        number: "8"
        value: "21.2"
    }

    SATValue {
        id: satValue09
        anchors.left: satValue08.left
        anchors.top: satValue02.top
        visible: true
        number: "9"
        value: "21.2"
    }

    SATValue {
        id: satValue10
        anchors.left: satValue08.left
        anchors.top: satValue03.top
        visible: true
        number: "10"
        value: "21.2"
    }

    SATValue {
        id: satValue11
        anchors.left: satValue08.left
        anchors.top: satValue04.top
        visible: true
        number: "11"
        value: "21.2"
    }

    SATValue {
        id: satValue12
        anchors.left: satValue08.left
        anchors.top: satValue05.top
        visible: true
        number: "12"
        value: "21.2"
    }

    SATValue {
        id: satValue13
        anchors.left: satValue08.left
        anchors.top: satValue06.top
        visible: true
        number: "13"
        value: "21.2"
    }

    SATValue {
        id: satValue14
        anchors.left: satValue08.left
        anchors.top: satValue07.top
        visible: true
        number: "14"
        value: "21.2"
    }

    SATValue {
        id: satValue15
        x: 516
        anchors.top: satValue01.top
        visible: true
        number: "15"
        value: "21.2"
    }

    SATValue {
        id: satValue16
        anchors.left: satValue15.left
        anchors.top: satValue02.top
        visible: true
        number: "16"
        value: "21.2"
    }

    SATValue {
        id: satValue17
        anchors.left: satValue15.left
        anchors.top: satValue03.top
        visible: true
        number: "17"
        value: "21.2"
    }

    SATValue {
        id: satValue18
        anchors.left: satValue15.left
        anchors.top: satValue04.top
        visible: true
        number: "18"
        value: "21.2"
    }

    SATValue {
        id: satValue19
        anchors.left: satValue15.left
        anchors.top: satValue05.top
        visible: true
        number: "19"
        value: "21.2"
    }

    SATValue {
        id: satValue20
        anchors.left: satValue15.left
        anchors.top: satValue06.top
        visible: true
        number: "20"
        value: "21.2"
    }

    SATValue {
        id: satValue21
        anchors.left: satValue15.left
        anchors.top: satValue07.top
        visible: true
        number: "21"
        value: "21.2"
    }

    SATValue {
        id: satValue22
        x: 772
        anchors.top: satValue01.top
        visible: true
        number: "22"
        value: "21.2"
    }

    SATValue {
        id: satValue23
        anchors.left: satValue22.left
        anchors.top: satValue02.top
        visible: true
        number: "23"
        value: "21.2"
    }

    SATValue {
        id: satValue24
        anchors.left: satValue22.left
        anchors.top: satValue03.top
        visible: true
        number: "24"
        value: "21.2"
    }

    SATValue {
        id: satValue25
        anchors.left: satValue22.left
        anchors.top: satValue04.top
        visible: true
        number: "25"
        value: "21.2"
    }

    SATValue {
        id: satValue26
        anchors.left: satValue22.left
        anchors.top: satValue05.top
        visible: true
        number: "26"
        value: "21.2"
    }

    SATValue {
        id: satValue27
        anchors.left: satValue22.left
        anchors.top: satValue06.top
        visible: true
        number: "27"
        value: "21.2"
    }

    SATValue {
        id: satValue28
        anchors.left: satValue22.left
        anchors.top: satValue07.top
        visible: true
        number: "28"
        value: "21.2"
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.2;height:0;width:0}
}
##^##*/
