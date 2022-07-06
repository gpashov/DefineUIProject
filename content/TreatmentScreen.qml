import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0
import define.enums 1.0

Item {
    id: item1
    width: Constants.width
    height: Constants.height

    Connections {
        target: wdgWpr
        onBodyZoomed: (zoomed) => { bodySilhouette.visible = !zoomed; bodyAreaZoomed.visible = zoomed }
    }

    Connections {
        target: wdgWpr
        onBodyGenderSelected: (gender) => {
                                  switch(gender) {
                                      case AppEnumsNs.AppGUIbodyMale: bodySilhouette.state = "maleState"; break;
                                      case AppEnumsNs.AppGUIbodyFemale: bodySilhouette.state = "femaleState"; break;
                                      default: break;
                                  }
                              }
    }

    BodySilhouette {
        id: bodySilhouette
    }

    BodyAreaZoomed {
        id: bodyAreaZoomed
    }

    Image {
        id: hidePanelButtonHp1Img
        x: 270
        y: 61
        source: "images/c202_BotonGuardarMenuLeftPress.png"
        fillMode: Image.PreserveAspectFit

        Button {
            id: hidePanelHp1Button
            anchors.fill: parent
            opacity: 0
            onReleased: cbkWpr.butHideCtrlPnl(AppEnumsNs.APP_GUI_HP1_ID)
        }
    }

    Image {
        id: showPanelButtonHp1Img
        x: 0
        y: 0
        visible: false
        source: "images/c006_MenuTrtHP1Press.png"
        fillMode: Image.PreserveAspectFit

        Button {
            id: showPanelHp1Button
            anchors.fill: parent
            opacity: 0
            onReleased: cbkWpr.butShowCtrlPnl(AppEnumsNs.APP_GUI_HP1_ID)
        }
    }

    Image {
        id: hidePanelButtonHp2Img
        x: 714
        y: 61
        source: "images/c199_BotonGuardarMenuRightPress.png"
        fillMode: Image.PreserveAspectFit

        Button {
            id: hidePanelHp2Button
            anchors.fill: parent
            opacity: 0
            onReleased: cbkWpr.butHideCtrlPnl(AppEnumsNs.APP_GUI_HP2_ID)
        }
    }

    Image {
        id: showPanelButtonHp2Img
        visible: false
        anchors.right: parent.right
        anchors.top: parent.top
        source: "images/c014_MenuTrtHP2Press.png"
        fillMode: Image.PreserveAspectFit

        Button {
            id: showPanelHp2Button
            anchors.fill: parent
            opacity: 0
            onReleased: cbkWpr.butShowCtrlPnl(AppEnumsNs.APP_GUI_HP2_ID)
        }
    }

    Image {
        id: hidePanelButtonHp3Img
        x: 273
        y: 663
        source: "images/c202_BotonGuardarMenuLeftPress.png"
        fillMode: Image.PreserveAspectFit

        Button {
            id: hidePanelHp3Button
            anchors.fill: parent
            opacity: 0
            onReleased: cbkWpr.butHideCtrlPnl(AppEnumsNs.APP_GUI_HP3_ID)
        }
    }

    Image {
        id: showPanelButtonHp3Img
        x: 0
        visible: false
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        source: "images/c022_MenuTrtHP3Press.png"
        fillMode: Image.PreserveAspectFit

        Button {
            id: showPanelHp3Button
            anchors.fill: parent
            opacity: 0
            onReleased: cbkWpr.butShowCtrlPnl(AppEnumsNs.APP_GUI_HP3_ID)
        }
    }

    Image {
        id: hidePanelButtonHp4Img
        x: 719
        y: 663
        source: "images/c199_BotonGuardarMenuRightPress.png"
        fillMode: Image.PreserveAspectFit

        Button {
            id: hidePanelHp4Button
            anchors.fill: parent
            opacity: 0
            onReleased: cbkWpr.butHideCtrlPnl(AppEnumsNs.APP_GUI_HP4_ID)
        }
    }

    Image {
        id: showPanelButtonHp4Img
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        visible: false
        source: "images/c030_MenuTrtHP4Press.png"
        fillMode: Image.PreserveAspectFit

        Button {
            id: showPanelHp4Button
            anchors.fill: parent
            opacity: 0
            onReleased: cbkWpr.butShowCtrlPnl(AppEnumsNs.APP_GUI_HP4_ID)
        }
    }

    Connections {
        target: wdgWpr
        onControlPanelHideButtonEnabled: (hpIndex, isEnabled) => {
                                             switch (hpIndex) {
                                                 case AppEnumsNs.APP_GUI_HP1_ID:
                                                     hidePanelHp1Button.enabled = isEnabled
                                                     break;
                                                 case AppEnumsNs.APP_GUI_HP2_ID:
                                                     hidePanelHp2Button.enabled = isEnabled
                                                     break;
                                                 case AppEnumsNs.APP_GUI_HP3_ID:
                                                     hidePanelHp3Button.enabled = isEnabled
                                                     break;
                                                 case AppEnumsNs.APP_GUI_HP4_ID:
                                                     hidePanelHp4Button.enabled = isEnabled
                                                     break;
                                                 default: break;
                                             }
                                         }

        onControlPanelShowButtonEnabled: (hpIndex, isEnabled) => {
                                             switch (hpIndex) {
                                                 case AppEnumsNs.APP_GUI_HP1_ID:
                                                     showPanelHp1Button.enabled = isEnabled
                                                     break;
                                                 case AppEnumsNs.APP_GUI_HP2_ID:
                                                     showPanelHp2Button.enabled = isEnabled
                                                     break;
                                                 case AppEnumsNs.APP_GUI_HP3_ID:
                                                     showPanelHp3Button.enabled = isEnabled
                                                     break;
                                                 case AppEnumsNs.APP_GUI_HP4_ID:
                                                     showPanelHp4Button.enabled = isEnabled
                                                     break;
                                                 default: break;
                                             }
                                         }
    }

    HPControlPanel {
        id: controlPanelHp1
        anchors.left: parent.left
        anchors.top: parent.top
        state: "hp1State"
    }

    HPControlPanel {
        id: controlPanelHp2
        anchors.right: parent.right
        anchors.top: parent.top
        state: "hp2State"
    }

    HPControlPanel {
        id: controlPanelHp3
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        state: "hp3State"
    }

    HPControlPanel {
        id: controlPanelHp4
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        state: "hp4State"
    }

    Connections {
        target: wdgWpr
        onHpControlPanelShown: (hpIndex, isShown) => {
                                   if (isShown) {
                                       switch (hpIndex) {
                                           case AppEnumsNs.APP_GUI_HP1_ID:
                                               controlPanelHp1.visible = true
                                               hidePanelButtonHp1Img.visible = true
                                               showPanelButtonHp1Img.visible = false
                                               break;
                                           case AppEnumsNs.APP_GUI_HP2_ID:
                                               controlPanelHp2.visible = true
                                               hidePanelButtonHp2Img.visible = true
                                               showPanelButtonHp2Img.visible = false
                                               break;
                                           case AppEnumsNs.APP_GUI_HP3_ID:
                                               controlPanelHp3.visible = true
                                               hidePanelButtonHp3Img.visible = true
                                               showPanelButtonHp3Img.visible = false
                                               break;
                                           case AppEnumsNs.APP_GUI_HP4_ID:
                                               controlPanelHp4.visible = true
                                               hidePanelButtonHp4Img.visible = true
                                               showPanelButtonHp4Img.visible = false
                                               break;
                                           default: break;
                                       }
                                   }
                                   else
                                   {
                                       switch (hpIndex) {
                                           case AppEnumsNs.APP_GUI_HP1_ID:
                                               controlPanelHp1.visible = false
                                               hidePanelButtonHp1Img.visible = false
                                               showPanelButtonHp1Img.visible = true
                                               break;
                                           case AppEnumsNs.APP_GUI_HP2_ID:
                                               controlPanelHp2.visible = false
                                               hidePanelButtonHp2Img.visible = false
                                               showPanelButtonHp2Img.visible = true
                                               break;
                                           case AppEnumsNs.APP_GUI_HP3_ID:
                                               controlPanelHp3.visible = false
                                               hidePanelButtonHp3Img.visible = false
                                               showPanelButtonHp3Img.visible = true
                                               break;
                                           case AppEnumsNs.APP_GUI_HP4_ID:
                                               controlPanelHp4.visible = false
                                               hidePanelButtonHp4Img.visible = false
                                               showPanelButtonHp4Img.visible = true
                                               break;
                                           default: break;
                                       }
                                   }
                               }
    }

    CustomSwitch {
        id: infoSwitch
        x: 778
        y: 352
        visible: false
        onStateImageSource: "images/c282_InfoPress.png"
        onPressedStateImageSource: "images/c281_InfoRls.png"
        offStateImageSource: "images/c281_InfoRls.png"
        offPressedStateImageSource: "images/c282_InfoPress.png"
        onOnAction: cbkWpr.butInfoZoneSelectedOn()
        onOffAction: cbkWpr.butInfoZoneSelectedOff()
    }

    Connections {
        target: wdgWpr
        onInfoSwitchVisibilityChanged: (newVisibility) => infoSwitch.visible = newVisibility
    }

    Connections {
        target: wdgWpr
        onInfoSwitchEnabled: (enable) => infoSwitch.enabled = enable
    }

    TwoStateButton {
        id: returnButton
        x: 189
        y: 352
        visible: false
        imageSourcePressed: "images/c156_RetrocesoPress.png"
        imageSourceReleased: "images/c155_RetrocesoRls.png"
        button.onReleased: cbkWpr.butPopUpReturn()

        Connections {
            target: wdgWpr
            onReturnButtonVisibilityChanged: (newVisibility) => returnButton.visible = newVisibility
        }

        Connections {
            target: wdgWpr
            onReturnButtonEnabled: (enable) => returnButton.enabled = enable
        }
    }

    PopupRecommendedHps {
        id: popupRecommendedHps
        visible: false

        Connections {
            target: wdgWpr
            onRecommendedHpsPopupActivated: (isActivated) => popupRecommendedHps.visible = isActivated
        }

        onVisibleChanged: cbkWpr.popupVisibleChanged(AppEnumsNs.PopUpRecomm, visible)
    }

    PopupRfid {
        id: popupRfid
        visible: false

        Connections {
            target: wdgWpr
            onRfidPopupActivated: (isActivated) => visible = isActivated
        }
    }

    PopupTestVacuum {
        id: popupTestVacuum
        visible: false

        Connections {
            target: wdgWpr
            onTestVacuumPopupActivated: (isActivated) => visible = isActivated
        }
    }

    PopupHpColorBar {
        id: popupHpColorBar
        visible: true
    }

    ErrorPopups {
        id: errorPopups
    }





}


















