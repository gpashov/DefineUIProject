import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0

Item {
    id: item1
    width: Constants.width
    height: Constants.height

    ErrorPopupHp {
        id: errorPopupHp1
        visible: false
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 0
        anchors.topMargin: 0
        state: states[0].name
    }

    ErrorPopupHp {
        id: errorPopupHp2
        x: 740
        visible: false
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.rightMargin: 0
        state: states[1].name
    }

    ErrorPopupHp {
        id: errorPopupHp3
        visible: false
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
        state: states[2].name
    }

    ErrorPopupHp {
        id: errorPopupHp4
        x: 740
        y: 0
        visible: false
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 0
        state: states[3].name
    }

    ErrorPopupCentral {
        id: errorPopupCentral
        x: 282
        y: 256
        visible: false
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66;height:768;width:1024}
}
##^##*/
