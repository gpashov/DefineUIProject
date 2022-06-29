import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject
import define.enums 1.0

Item {
    id: item1
    width: Constants.width
    height: Constants.height

    Image {
        id: c170_PopUpImagenSuccion
        x: 323
        y: 184
        source: "images/c170_PopUpImagenSuccion.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c337_PopupBotonsuccion1Rls
        x: 358
        y: 475
        source: "images/c337_PopupBotonsuccion1Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c339_PopupBotonsuccion2Rls
        x: c337_PopupBotonsuccion1Rls.x
        y: 410
        source: "images/c339_PopupBotonsuccion2Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c341_PopupBotonsuccion3Rls
        x: c337_PopupBotonsuccion1Rls.x
        y: 339
        source: "images/c341_PopupBotonsuccion3Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c222_PopUpIndmanoPress
        x: 506
        y: 251
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
        x: 463
        y: 489
        imageSourcePressed: "images/c177_PopUpBotonTestPress.png"
        imageSourceReleased: "images/c176_PopUpBotonTestRls.png"
    }

    TwoStateButton {
        id: testVacuumLvl2Button
        x: testVacuumLvl1Button.x
        y: 422
        imageSourcePressed: "images/c177_PopUpBotonTestPress.png"
        imageSourceReleased: "images/c176_PopUpBotonTestRls.png"
    }

    TwoStateButton {
        id: testVacuumLvl3Button
        x: testVacuumLvl1Button.x
        y: 356
        imageSourcePressed: "images/c177_PopUpBotonTestPress.png"
        imageSourceReleased: "images/c176_PopUpBotonTestRls.png"
    }

    TwoStateButton {
        id: testVacuumLvl1Switch
        x: 582
        y: 486
        imageSourcePressed: "images/c180_PopupBotonActivarPress"
        imageSourceReleased: "images/c179_PopupBotonActivarRls"
    }

    TwoStateButton {
        id: testVacuumLvl2Switch
        x: testVacuumLvl1Switch.x
        y: 421
        imageSourcePressed: "images/c180_PopupBotonActivarPress"
        imageSourceReleased: "images/c179_PopupBotonActivarRls"
    }

    TwoStateButton {
        id: testVacuumLvl3Switch
        x: testVacuumLvl1Switch.x
        y: 352
        imageSourcePressed: "images/c180_PopupBotonActivarPress"
        imageSourceReleased: "images/c179_PopupBotonActivarRls"
    }

    PopupHpColorBar {
        id: popupHpColorBar
        x: 0
        y: 0
        state: "hp1State"
    }

    TwoStateButton {
        id: twoStateButton
        x: 457
        y: 531
        imageSourceReleased: "images/c220_PopUpBotonAuto.png"
        imageSourcePressed: "images/c221_PopUpBotonAutoPress.png"
    }

    onVisibleChanged: cbkWpr.popUpVisibleChanged(AppEnumsNs.PopUpTstVac, visible)
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.5;height:0;width:0}
}
##^##*/
