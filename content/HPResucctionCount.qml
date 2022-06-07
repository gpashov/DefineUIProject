import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    width: resuccionIndicadorBackgroundImg.width
    height: resuccionIndicadorBackgroundImg.height

    Image {
        id: resuccionIndicadorBackgroundImg
        x: 0
        y: 0
        source: "images/c510_resuccionindicador.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: hpResucctionCount
        width: resuccionIndicadorBackgroundImg.width
        height: resuccionIndicadorBackgroundImg.height
        color: "#023744"
        text: "12"
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: true
        font.family: "Verdana"
    }
}

/*##^##
Designer {
    D{i:0;height:37;width:37}
}
##^##*/
