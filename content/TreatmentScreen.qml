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
        onBodyZoomed: (zoomed) => { bodySilhouette.visible = !zoomed; BodyAreaZoomed.visible = zoomed }
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
        areaState: 1
        genderState: "maleState"
        visible: !bodySilhouette.visible
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
            onPressed: {
                controlPanelHp1.visible = false
                hidePanelButtonHp1Img.visible = false
                showPanelButtonHp1Img.visible = true
            }
        }

        Connections {
            target: wdgWpr
            onControlPanelHideButtonEnabled: (hpIndex, isEnabled) => {
                                                 if (hpIndex === AppEnumsNs.APP_GUI_HP1_ID) {
                                                     hidePanelHp1Button.enabled = isEnabled
                                                 }
                                             }
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
            onPressed: {
                controlPanelHp1.visible = true
                hidePanelButtonHp1Img.visible = true
                showPanelButtonHp1Img.visible = false
            }
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
            onPressed: {
                controlPanelHp2.visible = false
                hidePanelButtonHp2Img.visible = false
                showPanelButtonHp2Img.visible = true
            }
        }

        Connections {
            target: wdgWpr
            onControlPanelHideButtonEnabled: (hpIndex, isEnabled) => {
                                                 if (hpIndex === AppEnumsNs.APP_GUI_HP2_ID) {
                                                     hidePanelHp2Button.enabled = isEnabled
                                                 }
                                             }
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
            onPressed: {
                controlPanelHp2.visible = true
                hidePanelButtonHp2Img.visible = true
                showPanelButtonHp2Img.visible = false
            }
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
            onPressed: {
                controlPanelHp3.visible = false
                hidePanelButtonHp3Img.visible = false
                showPanelButtonHp3Img.visible = true
            }
        }

        Connections {
            target: wdgWpr
            onControlPanelHideButtonEnabled: (hpIndex, isEnabled) => {
                                                 if (hpIndex === AppEnumsNs.APP_GUI_HP3_ID) {
                                                     hidePanelHp3Button.enabled = isEnabled
                                                 }
                                             }
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
            onPressed: {
                controlPanelHp3.visible = true
                hidePanelButtonHp3Img.visible = true
                showPanelButtonHp3Img.visible = false
            }
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
            onPressed: {
                controlPanelHp4.visible = false
                hidePanelButtonHp4Img.visible = false
                showPanelButtonHp4Img.visible = true
            }
        }

        Connections {
            target: wdgWpr
            onControlPanelHideButtonEnabled: (hpIndex, isEnabled) => {
                                                 if (hpIndex === AppEnumsNs.APP_GUI_HP4_ID) {
                                                     hidePanelHp4Button.enabled = isEnabled
                                                 }
                                             }
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
            onPressed: {
                controlPanelHp4.visible = true
                hidePanelButtonHp4Img.visible = true
                showPanelButtonHp4Img.visible = false
            }
        }
    }

    HPControlPanel {
        id: controlPanelHp1
        anchors.left: parent.left
        anchors.top: parent.top
        state: "hp1State"
        colorIndicatorState: "State1"
    }

    HPControlPanel {
        id: controlPanelHp2
        anchors.right: parent.right
        anchors.top: parent.top
        state: "hp2State"
        colorIndicatorState: "State2"
    }

    HPControlPanel {
        id: controlPanelHp3
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        state: "hp3State"
        colorIndicatorState: "State2"
    }

    HPControlPanel {
        id: controlPanelHp4
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        state: "hp4State"
        colorIndicatorState: "State1"
    }

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

        Connections {
            target: wdgWpr
            onInfoSwitchVisibilityChanged: (newVisibility) => visible = newVisibility
        }

        Connections {
            target: wdgWpr
            onInfoSwitchEnabled: (enable) => enabled = enable
        }
    }

    TwoStateButton {
        id: returnButton
        x: 189
        y: 352
        imageSourcePressed: "images/c156_RetrocesoPress.png"
        imageSourceReleased: "images/c155_RetrocesoRls.png"
        button.onReleased: cbkWpr.butPopUpReturn()

        Connections {
            target: wdgWpr
            onReturnButtonVisibilityChanged: (newVisibility) => visible = newVisibility
        }

        Connections {
            target: wdgWpr
            onReturnButtonEnabled: (enable) => enabled = enable
        }
    }

    ErrorPopups {
        id: errorPopups
    }
}






