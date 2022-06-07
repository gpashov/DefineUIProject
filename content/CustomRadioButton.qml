import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0
RadioButton {
    id: customRadioButton
    width: indicatorImg.width
    height: indicatorImg.height
    text: ""
    property alias indicatorImageSource: indicatorImg.source
    indicator: Image {
        id: indicatorImg
        source: "images/c113_BotonTorsoPressMujer.png"
        visible: false
    }

    property alias backgroundImageSource: backgroundImg.source
    background: Image {
        id: backgroundImg
    }

    onCheckedChanged: indicatorImg.visible = checked
}

/*##^##
Designer {
    D{i:0;height:160;width:122}
}
##^##*/
