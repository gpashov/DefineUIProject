import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property alias number: numberText.text
    property alias value: valueText.text

    Text {
        id: numberText
        x: 0
        y: 4
        width: 45
        height: 48
        text: "0"
        color: "#015e76"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }

    Image {
        id: image
        x: 60
        y: 0
        source: "images/c047_FondoNumVwrBlanco.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: valueText
        x: 77
        y: 6
        width: 125
        height: 48
        text: "0.0"
        color: "#015e76"
        font.pixelSize: 40
        horizontalAlignment: Text.AlignRight
        maximumLineCount: 1
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:0;width:0}
}
##^##*/
