import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: timeRemainingImg.width
    height: timeRemainingImg.height

    Image {
        id: timeRemainingImg
        source: "images/c047_FondoTemporizador.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: timeRemainingTxt
        x: 34
        y: 0
        width: 108
        height: 65
        color: "#015e76"
        text: "70:00"
        font.pixelSize: 36
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }



}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
