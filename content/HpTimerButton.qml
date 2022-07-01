import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0
import define.enums 1.0

TwoStateButton {
    id: customSwitch
    states: [
        State {
            name: "offState"
        },
        State {
            name: "onState"

            PropertyChanges {
                target: customSwitch
                imageSourceReleased: "images/c049_RelojTemporizadorRls.png"
                imageSourcePressed: "images/c048_RelojTemporizadorPress.png"
            }
        }
    ]

    imageSourceReleased: "images/c050_RelojTemporizadorMarcaAgua.png"
    imageSourcePressed: "images/c050_RelojTemporizadorMarcaAgua.png"
}






/*##^##
Designer {
    D{i:0;autoSize:true;height:0;width:0}
}
##^##*/
