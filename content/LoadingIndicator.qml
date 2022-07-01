import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0
import QtQuick.Timeline 1.0

Item {
    width: 400
    height: 400

    Image {
        id: a001_FondoLogoCooltechDefine
        x: 0
        y: 0
        source: "images/a001_FondoLogoCooltechDefine.png"
        fillMode: Image.PreserveAspectFit
    }

    Timeline {
        id: timeline
        animations: [
            TimelineAnimation {
                id: timelineAnimation
                running: true
                duration: 4000
                loops: 1
                to: 9
                from: 0
                onFinished: cbkWpr.loadAnimationEnd()
            }
        ]
        enabled: true
        startFrame: 0
        endFrame: 9

        KeyframeGroup {
            target: a002_CargaLogotipo8
            property: "visible"
            Keyframe {
                value: false
                frame: 0
            }

            Keyframe {
                value: true
                frame: 8
            }
        }

        KeyframeGroup {
            target: a002_CargaLogotipo7
            property: "visible"
            Keyframe {
                value: false
                frame: 0
            }

            Keyframe {
                value: true
                frame: 7
            }
        }

        KeyframeGroup {
            target: a002_CargaLogotipo6
            property: "visible"
            Keyframe {
                value: false
                frame: 0
            }

            Keyframe {
                value: true
                frame: 6
            }
        }

        KeyframeGroup {
            target: a002_CargaLogotipo5
            property: "visible"
            Keyframe {
                value: false
                frame: 0
            }

            Keyframe {
                value: true
                frame: 5
            }
        }

        KeyframeGroup {
            target: a002_CargaLogotipo4
            property: "visible"
            Keyframe {
                value: false
                frame: 0
            }

            Keyframe {
                value: true
                frame: 4
            }
        }

        KeyframeGroup {
            target: a002_CargaLogotipo3
            property: "visible"
            Keyframe {
                value: false
                frame: 0
            }

            Keyframe {
                value: true
                frame: 3
            }
        }

        KeyframeGroup {
            target: a002_CargaLogotipo2
            property: "visible"
            Keyframe {
                value: false
                frame: 0
            }

            Keyframe {
                value: true
                frame: 2
            }
        }

        KeyframeGroup {
            target: a002_CargaLogotipo1
            property: "visible"
            Keyframe {
                value: false
                frame: 0
            }

            Keyframe {
                value: true
                frame: 1
            }
        }
    }

    Image {
        id: a002_CargaLogotipo8
        x: 394
        y: 211
        visible: true
        source: "images/a009_CargaLogotipo8.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: a002_CargaLogotipo7
        x: 339
        y: 264
        source: "images/a008_CargaLogotipo7.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: a002_CargaLogotipo6
        x: 339
        y: 382
        source: "images/a007_CargaLogotipo6.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: a002_CargaLogotipo5
        x: 394
        y: 484
        source: "images/a006_CargaLogotipo5.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: a002_CargaLogotipo4
        x: 512
        y: 483
        source: "images/a005_CargaLogotipo4.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: a002_CargaLogotipo3
        x: 610
        y: 383
        source: "images/a004_CargaLogotipo3.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: a002_CargaLogotipo2
        x: 610
        y: 268
        source: "images/a003_CargaLogotipo2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: a002_CargaLogotipo1
        x: 512
        y: 205
        source: "images/a002_CargaLogotipo1.png"
        fillMode: Image.PreserveAspectFit
    }
}


/*##^##
Designer {
    D{i:0;height:400;width:400}D{i:2}
}
##^##*/

