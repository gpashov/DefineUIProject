import QtQuick 2.15
import QtQuick.Controls 2.15
import define.enums 1.0

Item {
    id: item1
    width: backgroundLeftImg.width
    height: backgroundLeftImg.height
    property alias state: item1.state

    Image {
        id: backgroundLeftImg
        x: 0
        y: 0
        source: "images/c349_BotonVacuumDesplegable_L.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: backgroundRightImg
        x: 0
        y: 0
        source: "images/c350_BotonVacuumDesplegable_R_03.png"
        fillMode: Image.PreserveAspectFit
    }

    TwoStateButton {
        id: testVacuumLowLevelButton
        x: 16
        y: 14
        imageSourcePressed: "images/c344_BotonVacuumSmall1Prs.png"
        imageSourceReleased: "images/c343_BotonVacuumSmall1Rls.png"
        button.onReleased: cbkWpr.butPopUpVacSmallLvl(AppEnumsNs.ButPopUpTstVacSmallLowLvl)
    }

    TwoStateButton {
        id: testVacuumMediumLevelButton
        x: 83
        y: 14
        imageSourcePressed: "images/c346_BotonVacuumSmall2Prs.png"
        imageSourceReleased: "images/c346_BotonVacuumSmall2MarcaAgua.png"
        button.onReleased: cbkWpr.butPopUpVacSmallLvl(AppEnumsNs.ButPopUpTstVacSmallMedLvl)
    }

    TwoStateButton {
        id: testVacuumHighLevelButton
        x: 150
        y: 14
        imageSourcePressed: "images/c348_BotonVacuumSmall3Prs.png"
        imageSourceReleased: "images/c347_BotonVacuumSmall3Rls.png"
        button.onReleased: cbkWpr.butPopUpVacSmallLvl(AppEnumsNs.ButPopUpTstVacSmallHighLvl)
    }

    states: [
        State {
            name: "leftState"

            PropertyChanges {
                target: backgroundRightImg
                visible: false
            }
        },
        State {
            name: "RightState"

            PropertyChanges {
                target: backgroundLeftImg
                visible: false
            }

            PropertyChanges {
                target: testVacuumLowLevelButton
                x: 150
                y: 14
            }

            PropertyChanges {
                target: testVacuumHighLevelButton
                x: 13
                y: 14
            }
        }
    ]

    onVisibleChanged: cbkWpr.popupVisibleChanged(AppEnumsNs.PopUpTstVacSmall, visible)
}


