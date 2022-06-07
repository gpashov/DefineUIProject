import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0

Item {
    id: item1
    width: Constants.width
    height: Constants.height

    BodySilhouette {
        id: bodySilhouette
    }


    BodyAreaZoomed {
        id: bodyAreaZoomed
        areaState: 1
        genderState: "maleState"
        visible: false
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
        statusImageState: "HpNotConnected"
    }

    HPControlPanel {
        id: controlPanelHp2
        anchors.right: parent.right
        anchors.top: parent.top
        state: "hp2State"
        colorIndicatorState: "State2"
        statusImageState: "HpNotConnected"
    }

    HPControlPanel {
        id: controlPanelHp3
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        state: "hp3State"
        colorIndicatorState: "State2"
        statusImageState: "HpNotConnected"
    }

    HPControlPanel {
        id: controlPanelHp4
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        state: "hp4State"
        colorIndicatorState: "State1"
        statusImageState: "HpNotConnected"
    }
    InfoSwitch {
        id: infoSwitch
    }

    ErrorPopups {
        id: errorPopups
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.5;height:768;width:1024}
}
##^##*/
