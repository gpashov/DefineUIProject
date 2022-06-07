import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: 1024
    height: 768

    CustomSwitch {
        id: infoSwitch
        x: 778
        y: 352
        onStateImageSource: "images/c282_InfoPress.png"
        offStateImageSource: "images/c281_InfoRls.png"
        onSwitchStateChanged: {
            if (switchState) {
                cbkWpr.butInfoZoneSelectedOn()
            }
            else {
                cbkWpr.butInfoZoneSelectedOff()
            }
        }
    }
}
