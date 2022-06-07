import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: name
    width: curvedImg.width
    height: curvedImg.height

    Image {
        id: curvedImg
        x: 0
        y: 0
        visible: false
        source: "images/c066_NameCurvedHP_L.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: tightImg
        x: 0
        y: 0
        visible: false
        source: "images/c067_NameTightHP_L.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: straightImg
        x: 0
        y: 0
        visible: false
        source: "images/c068_NameStarightHP_L.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: tinyImg
        x: 0
        y: 0
        visible: false
        source: "images/c069_NameTinyHP_L.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: tinyCurvedImg
        x: 0
        y: 0
        visible: false
        source: "images/c070_NameTinyCurvedHP_L.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: doubleImg
        x: 0
        y: 0
        visible: false
        source: "images/c071_NameDoubleHP_L.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: ovalImg
        x: 0
        y: 0
        visible: false
        source: "images/c072_NameOvalHP_L.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: ovalCurvedImg
        x: 0
        y: 0
        visible: false
        source: "images/c073_NameOvalCurvedHP_L.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: deltaImg
        x: 0
        y: 0
        visible: false
        source: "images/c074_NameDeltaHP_L.png"
        fillMode: Image.PreserveAspectFit
    }
    states: [
        State {
            name: "CurvedState"

            PropertyChanges {
                target: curvedImg
                visible: true
            }
        },
        State {
            name: "TightState"

            PropertyChanges {
                target: tightImg
                visible: true
            }
        },
        State {
            name: "StraightState"

            PropertyChanges {
                target: straightImg
                visible: true
            }
        },
        State {
            name: "TinyState"

            PropertyChanges {
                target: tinyImg
                visible: true
            }
        },
        State {
            name: "TinyCurvedState"

            PropertyChanges {
                target: tinyCurvedImg
                visible: true
            }
        },
        State {
            name: "DoubleState"

            PropertyChanges {
                target: doubleImg
                visible: true
            }
        },
        State {
            name: "OvalState"

            PropertyChanges {
                target: ovalImg
                visible: true
            }
        },
        State {
            name: "OvalCurvedState"

            PropertyChanges {
                target: ovalCurvedImg
                visible: true
            }
        },
        State {
            name: "DeltaState"

            PropertyChanges {
                target: deltaImg
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
