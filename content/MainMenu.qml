import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0

Item {
    id: item1
    width: openMenuImage.width
    height: openMenuImage.height
    //state: "openState"

    property alias homeButtonState: homeButton.state
    property alias codesButtonState: codesButton.state
    property alias languagesButtonState: languagesButton.state
    property alias configurationButtonState: configurationButton.state

    Image {
        id: openMenuImage
        source: "images/b010_SwMenuPress.png"
        fillMode: Image.PreserveAspectFit

        Button {
            id: openMenuButton
            width: 60
            height: 46
            anchors.top: parent.top
            x: 253
            opacity: 0
            onReleased: cbkWpr.butMainMenuHide()
        }
    }

    Image {
        id: closedMenuImage
        x: 236
        visible: false
        y: 90
        source: "images/b008_SwMenuRls.png"
        fillMode: Image.PreserveAspectFit
        Button {
            id: closedMenuButton
            anchors.fill: parent
            opacity: 0
            onReleased: cbkWpr.butMainMenuShow()
        }
    }

    MainMenuButtonTemplate
    {
        id: homeButton
        x: 35
        y: 63
        buttonNormalSource: "images/b012_BotonHomeMarcaAgua1.png"
        buttonPressedSource: "images/b013_BotonHomePress.png"
        buttonReleasedSource: "images/b014_BotonHomeRls.png"
        buttonInactiveSource: "images/b012_BotonHomeMarcaAgua.png"
        interactiveArea.onReleased: cbkWpr.butHome()
    }

    MainMenuButtonTemplate
    {
        id: codesButton
        x: 137
        y: 63
        buttonNormalSource: "images/b020_BotonCalculadoraMarcaAgua1.png"
        buttonPressedSource: "images/b021_BotonCalculadoraPress.png"
        buttonReleasedSource: "images/b022_BotonCalculadoraRls.png"
        buttonInactiveSource: "images/b020_BotonCalculadoraMarcaAgua.png"
        interactiveArea.onReleased: cbkWpr.butCalc()
    }

    MainMenuButtonTemplate
    {
        id: languagesButton
        x: 237
        y: 63
        buttonNormalSource: "images/b024_BotonIdiomasMarcaAgua1.png"
        buttonPressedSource: "images/b025_BotonIdiomasPress.png"
        buttonReleasedSource: "images/b026_BotonIdiomasRls.png"
        buttonInactiveSource: "images/b024_BotonIdiomasMarcaAgua.png"
        interactiveArea.onReleased: { /*Languages are not implemented*/ }
        buttonState: "stateInactive"
    }

    MainMenuButtonTemplate
    {
        id: configurationButton
        x: 339
        y: 63
        buttonNormalSource: "images/b018_BotonConfigMarcaAgua1.png"
        buttonPressedSource: "images/b016_BotonConfigPress.png"
        buttonReleasedSource: "images/b017_BotonConfigRls.png"
        buttonInactiveSource: "images/b018_BotonConfigMarcaAgua.png"
        interactiveArea.onReleased: cbkWpr.butConfig()
    }

    CustomSwitch
    {
        id: warningsButton
        x: 439
        y: 63
        offStateImageSource: "images/b030_BotonAvisosRls.png"
        offPressedStateImageSource: "images/b029_BotonAvisosPress.png"
        onStateImageSource: "images/b030_BotonAvisosRls.png"
        onPressedStateImageSource: "images/b029_BotonAvisosPress.png"
        onOnAction: cbkWpr.butWarningOn()
        onOffAction: cbkWpr.butWarningOff()
    }

    Image {
        id: notificationImg
        x: 495
        y: 57
        visible: false
        source: "images/b032_ImgNotificacion.png"
        fillMode: Image.PreserveAspectFit
    }

    states: [
        State {
            name: "closedState"

            PropertyChanges {
                target: openMenuImage
                visible: false
            }

            PropertyChanges {
                target: closedMenuImage
                visible: true
            }

            PropertyChanges {
                target: homeButton
                visible: false
            }

            PropertyChanges {
                target: codesButton
                visible: false
            }

            PropertyChanges {
                target: languagesButton
                visible: false
            }

            PropertyChanges {
                target: configurationButton
                visible: false
            }

            PropertyChanges {
                target: warningsButton
                visible: false
            }

            PropertyChanges {
                target: notificationImg
                x: 307
                y: 82
            }
        },
        State {
            name: "openState"

            PropertyChanges {
                target: openMenuImage
                visible: true
            }
        }
    ]



    // Enable/disable the main menu
    Connections {
        target: wdgWpr
        onMainMenuEnabled: (menuEnabled) => enabled = menuEnabled
    }

    // Open/close the main menu
    Connections {
        target: wdgWpr
        onMainMenuOpened: (menuOpened) => state = menuOpened ? "openState" : "closedState"
    }

    Connections {
        target: wdgWpr
        onMainMenuWarningNotificationDisplayed: (isDisplayed) => notificationImg.visible = isDisplayed
    }
}





/*##^##
Designer {
    D{i:0;height:164;width:573}
}
##^##*/
