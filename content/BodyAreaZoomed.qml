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
        onBodyGenderSelected: (gender) => {
                                switch (gender) {
                                case AppEnumsNs.AppGUIbodyFemale:
                                      state = "femaleState"
                                      break;
                                case AppEnumsNs.AppGUIbodyMale:
                                      state = "maleState"
                                      break;
                                }
                            }
    }

    BodyAreaZoomedMale {
        id: bodyAreaMale
        visible: false
    }

    BodyAreaZoomedFemale {
        id: bodyAreaFemale
        visible: false
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
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
