import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0
import define.enums 1.0

Item {
    id: item1
    width: Constants.width
    height: Constants.height

    HpCleaning {
        id: cleaningHp1
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 0
        anchors.topMargin: 0
        state: states[0].name
    }

    HpCleaning {
        id: cleaningHp2
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 0
        state: states[1].name
    }

    HpCleaning {
        id: cleaningHp3
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
        state: states[2].name
    }

    HpCleaning {
        id: cleaningHp4
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        state: states[3].name
    }

    Connections {
        target: wdgWpr
        onCleanUpPopupDisplayed: (hpIndex, isDispalyed) => {
                                     switch(hpIndex) {
                                         case AppEnumsNs.APP_GUI_HP1_ID: cleaningHp1.visible = isDisplayed; break;
                                         case AppEnumsNs.APP_GUI_HP2_ID: cleaningHp2.visible = isDisplayed; break;
                                         case AppEnumsNs.APP_GUI_HP3_ID: cleaningHp3.visible = isDisplayed; break;
                                         case AppEnumsNs.APP_GUI_HP4_ID: cleaningHp4.visible = isDisplayed; break;
                                     }
                                 }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.33}
}
##^##*/
