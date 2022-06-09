import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0
import define.enums 1.0

Item {
    id: item1
    width: Constants.width
    height: Constants.height
    property alias genderState: item1.state
    //property string areaState: "torsoState"
    property int areaState: 1

    Connections {
        target: wdgWpr
        onBodyGenderSelected: (gender) => {
                                switch (gender) {
                                case AppEnumsNs.AppGUIbodyFemale:
                                      bodyAreaFemale.visible = true;
                                      bodyAreaMale.visible = false;
                                      break;
                                case AppEnumsNs.AppGUIbodyMale:
                                      bodyAreaFemale.visible = false;
                                      bodyAreaMale.visible = true;
                                      break;
                                }
                            }
    }

    BodyAreaZoomedMale {
        id: bodyAreaMale
        visible: false
        state: states[areaState].name
    }

    BodyAreaZoomedFemale {
        id: bodyAreaFemale
        visible: false
        state: states[areaState].name
    }
    states: [
        State {
            name: "maleState"

            PropertyChanges {
                target: bodyAreaMale
                visible: true
            }
        },
        State {
            name: "femaleState"

            PropertyChanges {
                target: bodyAreaFemale
                visible: true
            }
        }
    ]


}

/*##^##
Designer {
    D{i:0;height:768;width:1024}
}
##^##*/
