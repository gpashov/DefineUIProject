import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0
import define.enums 1.0

Item {
    width: Constants.width
    height: Constants.height
    property alias status: statusImg.visible
    property alias restTime: restTimeText.text

    Image {
        id: backgroundImg
        x: 323
        y: 184
        source: "images/c182_PopUpRFIDFondo.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: labelImg
        x: 410
        y: 334
        source: "images/c182_PopUpRFIDlabelDM.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: statusImg
        x: 488
        y: 484
        source: "images/c182_PopUpRFIDsuccess.png"
        fillMode: Image.PreserveAspectFit
    }

    Button {
        id: button
        x: 435
        y: 269
        width: 154
        height: 64
        text: ""
        opacity: 0
    }

    Text {
        id: restTimeText
        x: button.x
        y: button.y
        width: button.width
        height: button.height
        color: "#00455b"
        text: "0:00"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Verdana"
    }

    // TODO Problem: AppEnumsNs.popUpRFID gives undefined value
    onVisibleChanged: { cbkWpr.popUpVisibleChanged(AppEnumsNs.popUpRFID, visible); console.log("AppEnumsNs.popUpRFID: ", AppEnumsNs.popUpRFID) }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.33;height:0;width:0}
}
##^##*/
