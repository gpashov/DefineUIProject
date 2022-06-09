import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0
import define.enums 1.0

Item {
    id: name
    property bool selected: false
    property int hpAssigned: AppEnumsNs.APP_GUI_MAXNUM_HP // no HP assigned
    onSelectedChanged: updateImage()
    onHpAssignedChanged: updateImage()

    Image {
        id: unselectedUnassignedDotImg
        visible: false
        source: "images/c148_ZonaAplicacionManipPunto.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: selectedUnassignedDotImg
        x: 0
        y: 0
        visible: false
        source: "images/c149_ZonaAplicacionManipPuntoSelected.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: unselectedAssignedToHp1Img
        x: 0
        y: 0
        visible: false
        source: "images/c151_ZonaAplicacionManipPuntoHP1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: unselectedAssignedToHp2Img
        x: 0
        y: 0
        visible: false
        source: "images/c152_ZonaAplicacionManipPuntoHP2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: unselectedAssignedToHp3Img
        x: 0
        y: 0
        visible: false
        source: "images/c153_ZonaAplicacionManipPuntoHP3.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: unselectedAssignedToHp4Img
        x: 0
        y: 0
        visible: false
        source: "images/c154_ZonaAplicacionManipPuntoHP4.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: selectedAssignedToHp1Img
        x: 0
        y: 0
        visible: false
        source: "images/c160_ZonaSeleccionadaHP1_seleccionado.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: selectedAssignedToHp2Img
        x: 0
        y: 0
        visible: false
        source: "images/c161_ZonaSeleccionadaHP2_seleccionado.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: selectedAssignedToHp3Img
        x: 0
        y: 0
        visible: false
        source: "images/c162_ZonaSeleccionadaHP3_seleccionado.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: selectedAssignedToHp4Img
        x: 0
        y: 0
        visible: false
        source: "images/c163_ZonaSeleccionadaHP4_seleccionado.png"
        fillMode: Image.PreserveAspectFit
    }
    states: [
        State {
            name: "UnselectedAssignedToHp1State"

            PropertyChanges {
                target: unselectedAssignedToHp1Img
                visible: true
            }
        },
        State {
            name: "UnselectedAssignedToHp2State"

            PropertyChanges {
                target: unselectedAssignedToHp2Img
                visible: true
            }
        },
        State {
            name: "UnselectedAssignedToHp3State"

            PropertyChanges {
                target: unselectedAssignedToHp3Img
                visible: true
            }
        },
        State {
            name: "UnselectedAssignedToHp4State"

            PropertyChanges {
                target: unselectedAssignedToHp4Img
                visible: true
            }
        },
        State {
            name: "UnselectedUnassignedState"

            PropertyChanges {
                target: unselectedUnassignedDotImg
                visible: true
            }
        },
        State {
            name: "SelectedAssignedToHp1State"

            PropertyChanges {
                target: selectedAssignedToHp1Img
                visible: true
            }
        },
        State {
            name: "SelectedAssignedToHp2State"

            PropertyChanges {
                target: selectedAssignedToHp2Img
                visible: true
            }
        },
        State {
            name: "SelectedAssignedToHp3State"

            PropertyChanges {
                target: selectedAssignedToHp3Img
                visible: true
            }
        },
        State {
            name: "SelectedAssignedToHp4State"

            PropertyChanges {
                target: selectedAssignedToHp4Img
                visible: true
            }
        },
        State {
            name: "SelectedUnassignedState"

            PropertyChanges {
                target: selectedUnassignedDotImg
                visible: true
            }
        }
    ]

    function updateImage() {
        if (selected) {
            switch(hpAssigned) {
            case AppEnumsNs.APP_GUI_HP1_ID: state = "SelectedAssignedToHp1State"; break;
            case AppEnumsNs.APP_GUI_HP2_ID: state = "SelectedAssignedToHp2State"; break;
            case AppEnumsNs.APP_GUI_HP3_ID: state = "SelectedAssignedToHp3State"; break;
            case AppEnumsNs.APP_GUI_HP4_ID: state = "SelectedAssignedToHp4State"; break;
            case AppEnumsNs.APP_GUI_MAXNUM_HP: state = "SelectedUnassignedState"; break;
            default: break;
            }
        }
        else {
            switch(hpAssigned) {
            case AppEnumsNs.APP_GUI_HP1_ID: state = "UnselectedAssignedToHp1State"; break;
            case AppEnumsNs.APP_GUI_HP2_ID: state = "UnselectedAssignedToHp2State"; break;
            case AppEnumsNs.APP_GUI_HP3_ID: state = "UnselectedAssignedToHp3State"; break;
            case AppEnumsNs.APP_GUI_HP4_ID: state = "UnselectedAssignedToHp4State"; break;
            case AppEnumsNs.APP_GUI_MAXNUM_HP: state = "UnselectedUnassignedState"; break;
            default: break;
            }
        }
    }
}


/*##^##
Designer {
    D{i:0;height:0;width:0}
}
##^##*/
