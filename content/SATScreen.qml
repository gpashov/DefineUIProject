import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 1024
    height: 768


    SATValue {
        id: pageText
        x: 79
        y: 691
        width: 160
        height: 68
        number: ""
        value: "0-9"
        valueTextHorizontalAlignment: Text.AlignHCenter
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

    TwoStateButton {
        id: homeButton
        y: 678
        imageSourceReleased: "images/b013_BotonHomePress.png"
        imageSourcePressed: "images/b014_BotonHomeRls.png"
        button.onReleased: cbkWpr.butHome()
    }

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
        source: "images/c438_HPalarmaPlicainsuficiente.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: testLedStatusImg
        x: 755
        y: 678
        source: "images/c453_MenuAlarmaOK_MarcaAgua.png"
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
        offPressedStateImageSource: "images/c044_BotonAutoPress.png"
        onPressedStateImageSource: "images/c045_BotonAutoRls.png"
        onOnAction: cbkWpr.swSATFrioOn()
        onOffAction: cbkWpr.swSATFrioOff()
    }

    CustomSwitch {
        id: vacuumSwitch
        x: 467
        y: 717
        offStateImageSource: "images/c045_BotonAutoRls.png"
        onStateImageSource: "images/c044_BotonAutoPress.png"
        offPressedStateImageSource: "images/c044_BotonAutoPress.png"
        onPressedStateImageSource: "images/c045_BotonAutoRls.png"
        onOnAction: cbkWpr.swSATVacOn()
        onOffAction: cbkWpr.swSATVacOff()
    }

    CustomSwitch {
        id: rfidSwitch
        x: 557
        y: 717
        offStateImageSource: "images/c045_BotonAutoRls.png"
        onStateImageSource: "images/c044_BotonAutoPress.png"
        offPressedStateImageSource: "images/c044_BotonAutoPress.png"
        onPressedStateImageSource: "images/c045_BotonAutoRls.png"
        onOnAction: cbkWpr.swSATrfidOn()
        onOffAction: cbkWpr.swSATrfidOff()
    }

    CustomSwitch {
        id: testLedSwitch
        x: 870
        y: 704
        offStateImageSource: "images/c045_BotonAutoRls.png"
        onStateImageSource: "images/c044_BotonAutoPress.png"
        offPressedStateImageSource: "images/c044_BotonAutoPress.png"
        onPressedStateImageSource: "images/c045_BotonAutoRls.png"
        onOnAction: cbkWpr.swSATtestLedOn()
        onOffAction: cbkWpr.swSATtestLedOff()
    }

    CustomSwitch {
        id: testLedRgbSwitch
        x: 646
        y: 717
        offStateImageSource: "images/c045_BotonAutoRls.png"
        onStateImageSource: "images/c044_BotonAutoPress.png"
        offPressedStateImageSource: "images/c044_BotonAutoPress.png"
        onPressedStateImageSource: "images/c045_BotonAutoRls.png"
    }

    Connections {
        target: wdgWpr
        onSatScreenSwVacuumSet: (OnOff) => vacuumSwitch.state = OnOff ? "onState" : "offState"
        onSatScreenSwFrioSet: (OnOff) => coolSwitch.state = OnOff ? "onState" : "offState"
        onSatScreenSwTestLedSet: (OnOff) => testLedSwitch.state = OnOff ? "onState" : "offState"
        onSatScreenSwTestLedRGBSet: (OnOff) => testLedRgbSwitch.state = OnOff ? "onState" : "offState"
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
    D{i:0;formeditorZoom:0.66;height:0;width:0}
}
##^##*/
