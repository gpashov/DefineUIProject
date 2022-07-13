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
        id: testVacuumLvl1Img
        x: 358
        y: 475
        source: "images/c337_PopupBotonsuccion1Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: testVacuumLvl2Img
        x: testVacuumLvl1Img.x
        y: 410
        source: "images/c339_PopupBotonsuccion2Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: testVacuumLvl3Img
        x: testVacuumLvl1Img.x
        y: 339
        source: "images/c341_PopupBotonsuccion3Rls.png"
        fillMode: Image.PreserveAspectFit
    }

    Connections {
        target: wdgWpr
        onTestVacuumPopupLevelImageSet: (imageWidgetId, status) => {
                                            // For the three levels of vacuum set two types of images depending on the test status, done or not done.
                                            switch(imageWidgetId) {
                                            case AppEnumsNs.ImgPopUpTstVacLowLvl:
                                                if (status === AppEnumsNs.AppGUItstVacNotDone) {
                                                    testVacuumLvl1Img.source = "images/c337_PopupBotonsuccion1Rls.png"
                                                }
                                                    else if (status === AppGUItstVacDone) {
                                                    testVacuumLvl1Img.source = "images/c338_PopupBotonsuccion1Press.png"
                                                }
                                                break;
                                            case AppEnumsNs.ImgPopUpTstVacMidLvl:
                                                if (status === AppEnumsNs.AppGUItstVacNotDone) {
                                                    testVacuumLvl2Img.source = "images/c339_PopupBotonsuccion2Rls.png"
                                                }
                                                    else if (status === AppGUItstVacDone) {
                                                    testVacuumLvl2Img.source = "images/c340_PopupBotonsuccion2Press.png"
                                                }
                                                break;
                                            case AppEnumsNs.ImgPopUpTstVacHighLvl:
                                                if (status === AppEnumsNs.AppGUItstVacNotDone) {
                                                    testVacuumLvl3Img.source = "images/c341_PopupBotonsuccion3Rls.png"
                                                }
                                                    else if (status === AppGUItstVacDone) {
                                                    testVacuumLvl3Img.source = "images/c342_PopupBotonsuccion3Press.png"
                                                }
                                                break;
                                            }
                                        }
    }

    Image {
        id: c222_PopUpIndmanoPress
        x: 506
        y: 251
        source: "images/c222_PopUpIndmanoPress.png"
        fillMode: Image.PreserveAspectFit

        Connections {
            target: wdgWpr
            onTestVacuumPopupPressHandVisibilityChanged: (newVisibility) => c222_PopUpIndmanoPress.visible = newVisibility
        }
    }

    Image {
        id: c222_B_PopUpIndmanoPressx2
        anchors.left: c222_PopUpIndmanoPress.left
        anchors.top: c222_PopUpIndmanoPress.top
        source: "images/c222_B_PopUpIndmanoPressx2.png"
        fillMode: Image.PreserveAspectFit

        Connections {
            target: wdgWpr
            onTestVacuumPopupPressHandX2VisibilityChanged: (newVisibility) => c222_B_PopUpIndmanoPressx2.visible = newVisibility
        }
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

    Connections {
        target: wdgWpr
        onTestVacuumPopupManualTestButtonEnabled: (widgetId, isEnabled) => {
                                                      switch(widgetId) {
                                                      case AppEnumsNs.ButPopUpTstVacManualLowLvl: testVacuumLvl1Button.enable = isEnabled; break;
                                                      case AppEnumsNs.ButPopUpTstVacManualMidLvl: testVacuumLvl2Button.enable = isEnabled; break;
                                                      case AppEnumsNs.ButPopUpTstVacManualHighLvl: testVacuumLvl3Button.enable = isEnabled; break;
                                                      }
                                                  }
    }

    CustomSwitch {
        id: testVacuumLvl1Switch
        x: 582
        y: 486
        offStateImageSource: "images/c179_PopupBotonActivarRls"
        onStateImageSource: "images/c180_PopupBotonActivarPress"
        offPressedStateImageSource: "images/c180_PopupBotonActivarPress"
        onPressedStateImageSource: "images/c179_PopupBotonActivarRls"
        onOnAction: cbkWpr.swPopUpTstVacLvlOn(AppEnumsNs.SwPopUpTstVacLowLvl)
    }

    CustomSwitch {
        id: testVacuumLvl2Switch
        x: testVacuumLvl1Switch.x
        y: 421
        offStateImageSource: "images/c179_PopupBotonActivarRls"
        onStateImageSource: "images/c180_PopupBotonActivarPress"
        offPressedStateImageSource: "images/c180_PopupBotonActivarPress"
        onPressedStateImageSource: "images/c179_PopupBotonActivarRls"
        onOnAction: cbkWpr.swPopUpTstVacLvlOn(AppEnumsNs.SwPopUpTstVacMidLvl)
    }

    CustomSwitch {
        id: testVacuumLvl3Switch
        x: testVacuumLvl1Switch.x
        y: 352
        offStateImageSource: "images/c179_PopupBotonActivarRls"
        onStateImageSource: "images/c180_PopupBotonActivarPress"
        offPressedStateImageSource: "images/c180_PopupBotonActivarPress"
        onPressedStateImageSource: "images/c179_PopupBotonActivarRls"
        onOnAction: cbkWpr.swPopUpTstVacLvlOn(AppEnumsNs.SwPopUpTstVacHighLvl)
    }

    Connections {
        target: wdgWpr

        onTestVacuumPopupSwitchStateChanged: (widgetId, OnOff) => {
                                                 switch(widgetId) {
                                                 case AppEnumsNs.SwPopUpTstVacLowLvl: testVacuumLvl1Switch.state = OnOff ? "onState" : "offState"; break;
                                                 case AppEnumsNs.SwPopUpTstVacMidLvl: testVacuumLvl2Switch.state = OnOff ? "onState" : "offState"; break;
                                                 case AppEnumsNs.SwPopUpTstVacHighLvl: testVacuumLvl3Switch.state = OnOff ? "onState" : "offState"; break;
                                                 }
                                             }

        onTestVacuumPopupSwitchEnabled: (widgetId, isEnabled) => {
                                            switch(widgetId) {
                                            case AppEnumsNs.SwPopUpTstVacLowLvl: testVacuumLvl1Switch.enable = isEnabled; break;
                                            case AppEnumsNs.SwPopUpTstVacMidLvl: testVacuumLvl2Switch.enable = isEnabled; break;
                                            case AppEnumsNs.SwPopUpTstVacHighLvl: testVacuumLvl3Switch.enable = isEnabled; break;
                                            }
                                        }
    }

    PopupHpColorBar {
        id: popupHpColorBar
        x: 0
        y: 0
        state: "hp1State"

        Connections {
            target: wdgWpr
            onTestVacuumPopupColorBarChanged: (hpIndex) => popupHpColorBar.state = popupHpColorBar.states[hpIndex]
        }
    }

    TwoStateButton {
        id: autoButton
        x: 457
        y: 531
        imageSourceReleased: "images/c220_PopUpBotonAuto.png"
        imageSourcePressed: "images/c221_PopUpBotonAutoPress.png"
        button.onReleased: cbkWpr.butPopUpTstVacAuto()

        Connections {
            target: wdgWpr
            onTestVacuumPopupAutoTestButtonEnabled: (isEnabled) => autoButton.enabled = isEnabled
            onTestVacuumPopupAutoButtonVisibilityChanged: (newVisibility) => autoButton.visible = newVisibility
        }
    }

    Image {
        id: autoStatusImg
        x: 576
        y: 192
        source: "images/c439_HPalarmaPlicaOK.png"
        fillMode: Image.PreserveAspectFit

        Connections {
            target: wdgWpr
            onTestVacuumPopupAutoStatusVisibilityChanged: (newVisibility) => autoStatusImg.visible = newVisibility
            onTestVacuumPopupAutoStatusImageChanged: (idImg) => {
                                                         switch(idImg) {
                                                             case AppEnumsNs.C439_HPalarmaPlicaOK: autoStatusImg.source = "images/c439_HPalarmaPlicaOK.png"; break;
                                                             case AppEnumsNs.C438_HPalarmaPlicainsuficiente: autoStatusImg.source = "images/c438_HPalarmaPlicainsuficiente.png"; break;
                                                         }
                                                     }
        }
    }

    onVisibleChanged: cbkWpr.popupVisibleChanged(AppEnumsNs.PopUpTstVac, visible)
}







/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
