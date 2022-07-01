import QtQuick 2.15
import QtQuick.Controls 2.15
import define.enums 1.0

Item {
    id: item1
    width: time2SelImg.width
    height: time2SelImg.height

    property int hpIndex: AppEnumsNs.APP_GUI_MAXNUM_HP

    Image {
        id: time1SelImg
        x: 0
        y: 0
        source: "images/c164_PopUpImagenReloj.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: time2SelImg
        x: 0
        y: 0
        source: "images/c164_Z_PopUpImagenReloj.png"
        fillMode: Image.PreserveAspectFit
    }

    TwoStateButton {
        id: time50MinBtn
        x: 12
        y: 19
        imageSourcePressed: "images/c166_PopUpBoton50MinPress.png"
        imageSourceReleased: "images/c165_PopUpBoton50MinRls.png"
        button.onReleased: cbkWpr.butPopUpTimeValue(hpIndex, ButPopUpTime50min)
    }

    TwoStateButton {
        id: time70MinBtn
        x: 12
        y: 65
        imageSourcePressed: "images/c168_PopUpBoton70MinPress.png"
        imageSourceReleased: "images/c167_PopUpBoton70MinRls.png"
        button.onReleased: cbkWpr.butPopUpTimeValue(hpIndex, ButPopUpTime70min)
    }
    states: [
        State {
            name: "hiddenState"

            PropertyChanges {
                target: time1SelImg
                visible: false
            }

            PropertyChanges {
                target: time2SelImg
                visible: false
            }

            PropertyChanges {
                target: time50MinBtn
                visible: false
            }

            PropertyChanges {
                target: time70MinBtn
                visible: false
            }
        },
        State {
            name: "noTimeSelectedState"

            PropertyChanges {
                target: time1SelImg
                visible: false
            }
        },
        State {
            name: "50TimeSelectedState"

            PropertyChanges {
                target: time2SelImg
                visible: false
            }

            PropertyChanges {
                target: time50MinBtn
                visible: false
            }

            PropertyChanges {
                target: time70MinBtn
                y: 20
            }
        },
        State {
            name: "70TimeSelectedState"

            PropertyChanges {
                target: time70MinBtn
                visible: false
            }

            PropertyChanges {
                target: time2SelImg
                visible: false
            }
        }
    ]

    onStateChanged: cbkWpr.popUpVisibleChanged(AppEnumsNs.PopUpTime, (state !== "hiddenState"))
}




