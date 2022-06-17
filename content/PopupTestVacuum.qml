import QtQuick 2.15
import QtQuick.Controls 2.15
import define.enums 1.0

Item {
    id: item1
    Image {
        id: c170_PopUpImagenSuccion
        x: 0
        y: 0
        source: "images/c170_PopUpImagenSuccion.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c337_PopupBotonsuccion1Rls
        x: 35
        y: 291
        source: "images/c337_PopupBotonsuccion1Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c339_PopupBotonsuccion2Rls
        x: 35
        y: 226
        source: "images/c339_PopupBotonsuccion2Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c341_PopupBotonsuccion3Rls
        x: 35
        y: 155
        source: "images/c341_PopupBotonsuccion3Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c222_PopUpIndmanoPress
        x: 183
        y: 67
        source: "images/c222_PopUpIndmanoPress.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c222_B_PopUpIndmanoPressx2
        anchors.left: c222_PopUpIndmanoPress.left
        anchors.top: c222_PopUpIndmanoPress.top
        source: "images/c222_B_PopUpIndmanoPressx2.png"
        fillMode: Image.PreserveAspectFit
    }

    TwoStateButton {
        id: testVacuumLvl1Button
        x: 140
        y: 172
        imageSourcePressed: "images/c177_PopUpBotonTestPress.png"
        imageSourceReleased: "images/c176_PopUpBotonTestRls.png"
    }

    TwoStateButton {
        id: testVacuumLvl2Button
        x: 140
        y: 238
        imageSourcePressed: "images/c177_PopUpBotonTestPress.png"
        imageSourceReleased: "images/c176_PopUpBotonTestRls.png"
    }

    TwoStateButton {
        id: testVacuumLvl3Button
        x: 140
        y: 305
        imageSourcePressed: "images/c177_PopUpBotonTestPress.png"
        imageSourceReleased: "images/c176_PopUpBotonTestRls.png"
    }

    TwoStateButton {
        id: testVacuumLvl1Switch
        x: 260
        y: 168
        imageSourcePressed: "images/c180_PopupBotonActivarPress"
        imageSourceReleased: "images/c179_PopupBotonActivarRls"
    }

    TwoStateButton {
        id: testVacuumLvl2Switch
        x: 260
        y: 237
        imageSourcePressed: "images/c180_PopupBotonActivarPress"
        imageSourceReleased: "images/c179_PopupBotonActivarRls"
    }

    TwoStateButton {
        id: testVacuumLvl3Switch
        x: 260
        y: 302
        imageSourcePressed: "images/c180_PopupBotonActivarPress"
        imageSourceReleased: "images/c179_PopupBotonActivarRls"
    }

    PopupHpColorBar {
        id: popupHpColorBar
        x: -1
        y: 389
        state: "hp1State"
    }

    TwoStateButton {
        id: twoStateButton
        x: 134
        y: 347
        imageSourceReleased: "images/c220_PopUpBotonAuto.png"
        imageSourcePressed: "images/c221_PopUpBotonAutoPress.png"
    }

    // TODO Problem: AppEnumsNs.popUpTstVac gives undefined value
    onVisibleChanged: { cbkWpr.popUpVisibleChanged(AppEnumsNs.popUpTstVac, visible); console.log("AppEnumsNs.popUpTstVac: ", AppEnumsNs.popUpTstVac) }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.66;height:480;width:640}
}
##^##*/
