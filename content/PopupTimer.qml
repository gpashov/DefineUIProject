import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: time2SelImg.width
    height: time2SelImg.height

    Image {
        id: time1SelImg
        x: 0
        y: 0
        source: "images/c164_PopUpImagenReloj.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: time2SelImg
        x: 0
        y: 0
        source: "images/c164_Z_PopUpImagenReloj.png"
        fillMode: Image.PreserveAspectFit
    }

    TwoStateButton {
        id: time50MinBtn
        imageSourcePressed: "images/c166_PopUpBoton50MinPress.png"
        imageSourceReleased: "images/c165_PopUpBoton50MinRls.png"
    }

    TwoStateButton {
        id: time70MinBtn
        imageSourcePressed: "images/c168_PopUpBoton70MinPress.png"
        imageSourceReleased: "images/c167_PopUpBoton70MinRls.png"
    }

    onVisibleChanged: popUpVisibleChanged(AppEnumsNs.popUpTime, visible)
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
