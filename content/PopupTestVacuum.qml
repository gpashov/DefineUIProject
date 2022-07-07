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
        y: 487
        imageSourcePressed: "images/c177_PopUpBotonTestPress.png"
        imageSourceReleased: "images/c176_PopUpBotonTestRls.png"
        button.onReleased: cbkWpr.butPopUpTstVacManual(AppEnumsNs.ButPopUpTstVacManualLowLvl)
    }

    TwoStateButton {
        id: testVacuumLvl2Button
        x: testVacuumLvl1Button.x
        y: 420
        imageSourcePressed: "images/c177_PopUpBotonTestPress.png"
        imageSourceReleased: "images/c176_PopUpBotonTestRls.png"
        button.onReleased: cbkWpr.butPopUpTstVacManual(AppEnumsNs.ButPopUpTstVacManualMidLvl)
    }

    TwoStateButton {
        id: testVacuumLvl3Button
        x: testVacuumLvl1Button.x
        y: 353
        imageSourcePressed: "images/c177_PopUpBotonTestPress.png"
        imageSourceReleased: "images/c176_PopUpBotonTestRls.png"
        button.onReleased: cbkWpr.butPopUpTstVacManual(AppEnumsNs.ButPopUpTstVacManualHighLvl)
    }

    CustomSwitch {
        id: testVacuumLvl1Switch
        x: 582
        y: 486
        offStateImageSource: "images/c179_PopupBotonActivarRls"
        onStateImageSource: "images/c180_PopupBotonActivarPress"
        offPressedStateImageSource: "images/c180_PopupBotonActivarPress"
        onPressedStateImageSource: "images/c179_PopupBotonActivarRls"
        onOnAction: {
            cbkWpr.swPopUpTstVacLvlOn(AppEnumsNs.SwPopUpTstVacLowLvl)
            testVacuumLvl2Switch.state = "offState"
            testVacuumLvl3Switch.state = "offState"
        }
    }

    CustomSwitch {
        id: testVacuumLvl2Switch
        x: testVacuumLvl1Switch.x
        y: 421
        offStateImageSource: "images/c179_PopupBotonActivarRls"
        onStateImageSource: "images/c180_PopupBotonActivarPress"
        offPressedStateImageSource: "images/c180_PopupBotonActivarPress"
        onPressedStateImageSource: "images/c179_PopupBotonActivarRls"
        onOnAction: {
            cbkWpr.swPopUpTstVacLvlOn(AppEnumsNs.SwPopUpTstVacMidLvl)
            testVacuumLvl1Switch.state = "offState"
            testVacuumLvl3Switch.state = "offState"
        }
    }

    CustomSwitch {
        id: testVacuumLvl3Switch
        x: testVacuumLvl1Switch.x
        y: 352
        offStateImageSource: "images/c179_PopupBotonActivarRls"
        onStateImageSource: "images/c180_PopupBotonActivarPress"
        offPressedStateImageSource: "images/c180_PopupBotonActivarPress"
        onPressedStateImageSource: "images/c179_PopupBotonActivarRls"
        onOnAction: {
            cbkWpr.swPopUpTstVacLvlOn(AppEnumsNs.SwPopUpTstVacHighLvl)
            testVacuumLvl1Switch.state = "offState"
            testVacuumLvl2Switch.state = "offState"
        }
    }

    PopupHpColorBar {
        id: popupHpColorBar
        x: 0
        y: 0
        state: "hp1State"
    }

    TwoStateButton {
        id: autoButton
        x: 457
        y: 531
        imageSourceReleased: "images/c220_PopUpBotonAuto.png"
        imageSourcePressed: "images/c221_PopUpBotonAutoPress.png"
        button.onReleased: cbkWpr.butPopUpTstVacAuto()
    }

    onVisibleChanged: cbkWpr.popupVisibleChanged(AppEnumsNs.PopUpTstVac, visible)
}





/*##^##
Designer {
    D{i:0;formeditorZoom:1.66}
}
##^##*/
