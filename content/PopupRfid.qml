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

        Connections {
            target: wdgWpr
            onRfidPopupLabelChanged: (idImg) => {
                                         switch(idImg) {
                                             case AppEnumsNs.C182_PopUpRFIDlabelZ0: labelImg.source = "images/c182_PopUpRFIDlabelZ0.png"; break;
                                             case AppEnumsNs.C182_PopUpRFIDlabelZ1: labelImg.source = "images/c182_PopUpRFIDlabelZ1.png"; break;
                                             case AppEnumsNs.C182_PopUpRFIDlabelZ2: labelImg.source = "images/c182_PopUpRFIDlabelZ2.png"; break;
                                             case AppEnumsNs.C182_PopUpRFIDlabelZ3: labelImg.source = "images/c182_PopUpRFIDlabelZ3.png"; break;
                                             case AppEnumsNs.C182_PopUpRFIDlabelDM: labelImg.source = "images/c182_PopUpRFIDlabelDM.png"; break;
                                         }
                                     }
        }
    }

    Image {
        id: statusImg
        x: 488
        y: 484
        source: "images/c182_PopUpRFIDsuccess.png"
        fillMode: Image.PreserveAspectFit

        Connections {
            target: wdgWpr
            onRfidPopupStatusChanged: (idImg) => {
                                         switch(idImg) {
                                             case AppEnumsNs.C182_PopUpRFIDsuccess: statusImg.source = "images/c182_PopUpRFIDsuccess.png"; break;
                                             case AppEnumsNs.C182_PopUpRFIDfail:    statusImg.source = "images/c182_PopUpRFIDfail.png"; break;
                                             case AppEnumsNs.C182_PopUpRFIDunknown: statusImg.source = "images/c182_PopUpRFIDunknown.png"; break;
                                             case AppEnumsNs.C182_PopUpRFIDwrong:   statusImg.source = "images/c182_PopUpRFIDwrong.png"; break;
                                             case AppEnumsNs.C233_ImgPixelBlanco:   statusImg.source = "images/c233_ImgPixelBlanco.png"; break;
                                         }
                                     }
        }
    }

    Button {
        id: button
        x: 435
        y: 269
        width: 154
        height: 64
        text: ""
        opacity: 0
        onReleased: cbkWpr.butReuseRFIDlabel()

        Connections {
            target: wdgWpr
            onRfidPopupReuseLabelEnabled: (isEnabled) => button.enabled = isEnabled
        }
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

        Connections {
            target: wdgWpr
            onRfidPopupRestTimeVisibilityChanged: (newVisibility) => restTimeText.visible = newVisibility
            onRfidPopupRestTimeUpdated: (newTime) => restTimeText.text = newTime
        }
    }

    PopupHpColorBar {
        id: popupHpColorBar
        x: 0
        y: 0
        state: "hp1State"

        Connections {
            target: wdgWpr
            onRfidPopupColorBarChanged: (hpIndex) => popupHpColorBar.state = popupHpColorBar.states[hpIndex]
        }
    }

    onVisibleChanged: cbkWpr.popupVisibleChanged(AppEnumsNs.PopUpRFID, visible)
}




