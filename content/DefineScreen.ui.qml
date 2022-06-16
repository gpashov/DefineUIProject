

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height
    visible: true
    color: Constants.backgroundColor

    // TODO: initialize to loadingState
    Image {
        id: c001_FondoLogo
        source: "images/c001_FondoLogo.png"
    }

    InitialScreen {
        id: initialScreen
        visible: false
    }

    LoadingIndicator {
        id: loadingIndicator
        visible: false
    }

    TreatmentScreen {
        id: treatmentScreen
        visible: false
    }

    CalcScreen {
        id: codesScreen
        visible: false
    }

    LanguagesScreen {
        id: languagesScreen
        visible: false
    }

    ConfigurationScreen {
        id: configurationScreen
        x: 230
        y: 92
        visible: false
    }

    SATScreen {
        id: satScreen
        visible: false
    }

    FatigueScreen {
        id: fatigueScreen
        visible: false
    }

    Image {
        id: gprsNoCoverageImg
        x: 589
        y: 700
        source: "images/c610_GPRS_no_coverage.png"
        fillMode: Image.PreserveAspectFit
    }

    states: [
        State {
            name: "loadingState"

            PropertyChanges {
                target: loadingIndicator
                visible: true
            }

            PropertyChanges {
                target: mainMenu
                visible: false
            }
        },
        State {
            name: "initialState"

            PropertyChanges {
                target: initialScreen
                visible: true
            }

            PropertyChanges {
                target: mainMenu
                homeButtonState: "stateInactive"
                languagesButtonState: "stateInactive"
            }
        },
        State {
            name: "treatmentState"

            PropertyChanges {
                target: treatmentScreen
                visible: true
            }

            PropertyChanges {
                target: mainMenu
                languagesButtonState: "stateInactive"
            }
        },
        State {
            name: "calculatorState"

            PropertyChanges {
                target: codesScreen
                visible: true
            }

            PropertyChanges {
                target: mainMenu
                codesButtonState: "stateInactive"
                languagesButtonState: "stateInactive"
            }
        },
        State {
            name: "configurationState"

            PropertyChanges {
                target: configurationScreen
                visible: true
            }

            PropertyChanges {
                target: mainMenu
                configurationButtonState: "stateInactive"
                languagesButtonState: "stateInactive"
            }
        },
        State {
            name: "languagesState"

            PropertyChanges {
                target: languagesScreen
                visible: true
            }

            PropertyChanges {
                target: mainMenu
                languagesButtonState: "stateInactive"
            }
        },
        State {
            name: "satState"

            PropertyChanges {
                target: satScreen
                visible: true
            }

            PropertyChanges {
                target: mainMenu
                visible: false
            }
        },
        State {
            name: "fatigueState"

            PropertyChanges {
                target: fatigueScreen
                visible: true
            }

            PropertyChanges {
                target: mainMenu
                visible: false
            }
        }
    ]

    MainMenu {
        id: mainMenu
        x: 230
        y: 614
    }

    PopupSystemWarnings {
        id: systemWarningsPopup
        x: 264
        y: 289
        visible: false
        onVisibleChanged: mainMenu.warningsButtonState = visible ? true : false
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66;height:768;width:1024}
}
##^##*/

