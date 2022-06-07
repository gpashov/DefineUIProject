import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0

Item {
    property alias imageSourceReleased: buttonRlsImg.source
    property alias imageSourcePressed: buttonPressImg.source
    property alias button: button
    width: buttonRlsImg.width
    height: buttonRlsImg.height

    Image {
        id: buttonRlsImg
        fillMode: Image.PreserveAspectFit
        source: "images/c245_Calculadoraboton9Rls.png"
    }

    Image {
        id: buttonPressImg
        visible: false
        fillMode: Image.PreserveAspectFit
        source: "images/c274_Calculadoranumero9Press.png"
    }

    Button {
        id: button
        anchors.fill: buttonRlsImg
        opacity: 0
    }

    states: [
        State {
            name: "buttonReleasedState"
            when: !button.pressed
        },
        State {
            name: "buttonPressedState"
            when: button.pressed

            PropertyChanges {
                target: buttonPressImg
                visible: true
            }

            PropertyChanges {
                target: buttonRlsImg
                visible: false
            }
        }
    ]
}



/*##^##
Designer {
    D{i:0;height:55;width:116}
}
##^##*/
