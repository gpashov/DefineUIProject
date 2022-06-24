import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    readonly property int vacuumLevelMax: 3
    readonly property int stateMax: 6
    readonly property int featuresMax: 2    // press, release
    property string images: [vacuumLevelMax][stateMax][featuresMax]


    TwoStateButton {
        id: twoStateButton
        imageSourceReleased: "images/c042_BotonVacuum1MarcaAguaLeft.png"
        imageSourcePressed: "images/c042_BotonVacuum1MarcaAguaLeft.png"
    }
    states: [
        State {
            name: "offLeftState"
        },
        State {
            name: "offRightState"
        },
        State {
            name: "onLeftState"
        },
        State {
            name: "onRightState"
        },
        State {
            name: "vacAdjLeftState"
        },
        State {
            name: "vacAdjRightState"
        }
    ]

}


/*##^##
Designer {
    D{i:0;autoSize:true;height:0;width:0}
}
##^##*/
