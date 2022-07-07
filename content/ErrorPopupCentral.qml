import QtQuick 2.15
import QtQuick.Controls 2.15
import define.enums 1.0

Item {
    id: item1
    width: backgroundImg.width
    height: backgroundImg.height

    Image {
        id: backgroundImg
        x: 0
        y: 0
        source: "images/c234_AlarmaFondoCentral2.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: errorCodeTxt
        x: 217
        y: 63
        width: 134
        height: 36
        color: "#005870"
        text: "123456"
        font.pixelSize: 34
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
    }

    ErrorMessageImage {
        id: errorMessageImg
        x: 25
        y: 76
    }

    TwoStateButton {
        id: okButton
        x: 242
        y: 127
        imageSourceReleased: "images/c356_BotonAlarmaCentralOkRls.png"
        imageSourcePressed: "images/c357_BotonAlarmaCentralOkPress.png"
        button.onReleased: cbkWpr.butPopUpErrOk(AppEnumsNs.ButPopUpErrOkUC)
    }
}



/*##^##
Designer {
    D{i:0;height:334;width:284}
}
##^##*/
