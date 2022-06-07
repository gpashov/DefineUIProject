import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    id: item1
    property alias state1ImageSource: colorIndicator1.source
    property alias state2ImageSource: colorIndicator2.source

    Image {
        id: colorIndicator1
        visible: false
        source: "images/c005__MenuTrtHP1_Aro1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: colorIndicator2
        visible: false
        source: "images/c005_MenuTrtHP1_Aro2.png"
        fillMode: Image.PreserveAspectFit
    }
    states: [
        State {
            name: "State1"

            PropertyChanges {
                target: colorIndicator1
                visible: true
            }
        },
        State {
            name: "State2"

            PropertyChanges {
                target: colorIndicator2
                visible: true
            }
        }
    ]
}


/*##^##
Designer {
    D{i:0;height:0;width:0}
}
##^##*/
