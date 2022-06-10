import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0
import define.enums 1.0

Item {
    id: item1
    width: Constants.width
    height: Constants.height
    property alias state: item1.state

    Image {
        id: torsoImg
        x: 302
        y: 134
        visible: false
        source: "images/c205_ImgTorsoMujer.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: legsImg
        x: 302
        y: 134
        visible: false
        source: "images/c206_ImgPiernasMujer.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: backImg
        x: 302
        y: 134
        visible: false
        source: "images/c207_BrazosEspaldaMujer.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: legsThighsImg
        x: 324
        y: 147
        visible: false
        source: "images/c208_PiernaMusloMujer.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: armsImg
        x: 302
        y: 134
        visible: false
        source: "images/c207_BrazosEspaldaMujer.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: neckImg
        x: 262
        y: 179
        visible: false
        source: "images/c209_CuelloMujer.png"
        fillMode: Image.PreserveAspectFit
    }

    ZoomDot {
        id: dot1
        visible: false
        state: states[0].name
    }

    ZoomDot {
        id: dot2
        x: 0
        y: 0
        visible: false
        state: states[0].name
    }

    ZoomDot {
        id: dot3
        x: 0
        y: 0
        visible: false
        state: states[0].name
    }

    ZoomDot {
        id: dot4
        x: 0
        y: 0
        visible: false
        state: states[0].name
    }

    ZoomDot {
        id: dot5
        x: 0
        y: 0
        visible: false
        state: states[0].name
    }

    ZoomDot {
        id: dot6
        x: 0
        y: 0
        visible: false
        state: states[0].name
    }

    ZoomDot {
        id: dot7
        x: 0
        y: 0
        visible: false
        state: states[0].name
    }

    ZoomDot {
        id: dot8
        x: 0
        y: 0
        visible: false
        state: states[0].name
    }

    ZoomDot {
        id: dot9
        x: 0
        y: 0
        visible: false
        state: states[0].name
    }

    ZoomDot {
        id: dot10
        x: 0
        y: 0
        visible: false
        state: states[0].name
    }

    ZoomDot {
        id: dot11
        x: 0
        y: 0
        visible: false
        state: states[0].name
    }

    ZoomDot {
        id: dot12
        x: 0
        y: 0
        visible: false
        state: states[0].name
    }

    ZoomDot {
        id: dot13
        x: 0
        y: 0
        visible: false
        state: states[0].name
    }

    ZoomDot {
        id: dot14
        x: 0
        y: 0
        visible: false
        state: states[0].name
    }

    ZoomDot {
        id: dot15
        x: 0
        y: 0
        visible: false
        state: states[0].name
    }
    states: [
        State {
            name: "torsoState"

            PropertyChanges {
                target: torsoImg
                visible: true
            }

            PropertyChanges {
                target: dot1
                x: 572
                y: 243
                visible: true
            }

            PropertyChanges {
                target: dot2
                x: 412
                y: 243
                visible: true
            }

            PropertyChanges {
                target: dot3
                x: 541
                y: 323
                visible: true
            }

            PropertyChanges {
                target: dot4
                x: 444
                y: 323
                visible: true
            }

            PropertyChanges {
                target: dot5
                x: 538
                y: 374
                visible: true
            }

            PropertyChanges {
                target: dot6
                x: 493
                y: 374
                visible: true
            }

            PropertyChanges {
                target: dot7
                x: 444
                y: 374
                visible: true
            }

            PropertyChanges {
                target: dot8
                x: 538
                y: 433
                visible: true
            }

            PropertyChanges {
                target: dot9
                x: 493
                y: 433
                visible: true
            }

            PropertyChanges {
                target: dot10
                x: 444
                y: 433
                visible: true
            }

            PropertyChanges {
                target: dot11
                x: 493
                y: 486
                visible: true
            }

            PropertyChanges {
                target: dot12
                x: 576
                y: 422
                visible: true
            }

            PropertyChanges {
                target: dot13
                x: 408
                y: 422
                visible: true
            }
        },
        State {
            name: "legsState"

            PropertyChanges {
                target: legsImg
                visible: true
            }

            PropertyChanges {
                target: dot1
                x: 581
                y: 307
                visible: true
            }

            PropertyChanges {
                target: dot2
                x: 402
                y: 307
                visible: true
            }

            PropertyChanges {
                target: dot3
                x: 504
                y: 346
                visible: true
            }

            PropertyChanges {
                target: dot4
                x: 479
                y: 346
                visible: true
            }

            PropertyChanges {
                target: dot5
                x: 543
                y: 454
                visible: true
            }

            PropertyChanges {
                target: dot6
                x: 447
                y: 454
                visible: true
            }

            PropertyChanges {
                target: dot7
                x: 517
                y: 470
                visible: true
            }

            PropertyChanges {
                target: dot8
                x: 467
                y: 470
                visible: true
            }
        },
        State {
            name: "backState"

            PropertyChanges {
                target: backImg
                visible: true
            }

            PropertyChanges {
                target: dot1
                x: 435
                y: 265
                visible: true
            }

            PropertyChanges {
                target: dot2
                x: 547
                y: 265
                visible: true
            }

            PropertyChanges {
                target: dot3
                x: 452
                y: 334
                visible: true
            }

            PropertyChanges {
                target: dot4
                x: 531
                y: 334
                visible: true
            }

            PropertyChanges {
                target: dot5
                x: 452
                y: 385
                visible: true
            }

            PropertyChanges {
                target: dot6
                x: 531
                y: 385
                visible: true
            }
        },
        State {
            name: "legsThighsState"

            PropertyChanges {
                target: legsThighsImg
                visible: true
            }

            PropertyChanges {
                target: dot1
                x: 435
                y: 265
                visible: true
            }

            PropertyChanges {
                target: dot2
                x: 547
                y: 265
                visible: true
            }

            PropertyChanges {
                target: dot3
                x: 452
                y: 334
                visible: true
            }

            PropertyChanges {
                target: dot4
                x: 531
                y: 334
                visible: true
            }

            PropertyChanges {
                target: dot5
                x: 452
                y: 385
                visible: true
            }

            PropertyChanges {
                target: dot6
                x: 531
                y: 385
                visible: true
            }
        },
        State {
            name: "armsState"

            PropertyChanges {
                target: armsImg
                visible: true
            }

            PropertyChanges {
                target: dot1
                x: 380
                y: 300
                visible: true
            }

            PropertyChanges {
                target: dot2
                x: 600
                y: 300
                visible: true
            }
        },
        State {
            name: "neckState"

            PropertyChanges {
                target: neckImg
                visible: true
            }

            PropertyChanges {
                target: dot1
                x: 492
                y: 291
                visible: true
            }

            PropertyChanges {
                target: dot2
                x: 541
                y: 283
                visible: true
            }

            PropertyChanges {
                target: dot3
                x: 438
                y: 283
                visible: true
            }
        }
    ]

    Connections {
        target: wdgWpr
        onBodyAreaSelected: (area) => {
                                console.log("female     body ")
                                switch(area) {
                                    case AppEnumsNs.AppGUIfullBodyTorso: state = "torsoState"; break;
                                    case AppEnumsNs.AppGUIfullBodyPiernas: state = "torsoState"; break;
                                    case AppEnumsNs.AppGUIfullBodyEspalda: state = "torsoState"; break;
                                    case AppEnumsNs.AppGUIfullBodyPiernasMuslo: state = "torsoState"; break;
                                    case AppEnumsNs.AppGUIfullBodyBrazos: state = "torsoState"; break;
                                    case AppEnumsNs.AppGUIfullBodyCuello: state = "torsoState"; break;
                                    default: break;
                                }
                            }
    }

    Connections {
        target: wdgWpr
        onDotZoneEnabled: (id, enable) => {
                              switch(id) {
                                  case AppEnumsNs.swDotZone0: dot1.enabled = enable; break;
                                  case AppEnumsNs.swDotZone1: dot2.enabled = enable; break;
                                  case AppEnumsNs.swDotZone2: dot3.enabled = enable; break;
                                  case AppEnumsNs.swDotZone3: dot4.enabled = enable; break;
                                  case AppEnumsNs.swDotZone4: dot5.enabled = enable; break;
                                  case AppEnumsNs.swDotZone5: dot6.enabled = enable; break;
                                  case AppEnumsNs.swDotZone6: dot7.enabled = enable; break;
                                  case AppEnumsNs.swDotZone7: dot8.enabled = enable; break;
                                  case AppEnumsNs.swDotZone8: dot9.enabled = enable; break;
                                  case AppEnumsNs.swDotZone9: dot10.enabled = enable; break;
                                  case AppEnumsNs.swDotZone10: dot11.enabled = enable; break;
                                  case AppEnumsNs.swDotZone11: dot12.enabled = enable; break;
                                  case AppEnumsNs.swDotZone12: dot13.enabled = enable; break;
                                  case AppEnumsNs.swDotZone13: dot14.enabled = enable; break;
                                  case AppEnumsNs.swDotZone14: dot15.enabled = enable; break;
                                  default: break;
                              }
                          }
    }

    Connections {
        target: wdgWpr
        onDotZoneHpAssigned: (dot, hpIndex) => {
                             switch(dot) {
                                     case 0: dot1.hpAssigned = hpIndex; break;
                                     case 1: dot2.hpAssigned = hpIndex; break;
                                     case 2: dot3.hpAssigned = hpIndex; break;
                                     case 3: dot4.hpAssigned = hpIndex; break;
                                     case 4: dot5.hpAssigned = hpIndex; break;
                                     case 5: dot6.hpAssigned = hpIndex; break;
                                     case 6: dot7.hpAssigned = hpIndex; break;
                                     case 7: dot8.hpAssigned = hpIndex; break;
                                     case 8: dot9.hpAssigned = hpIndex; break;
                                     case 9: dot10.hpAssigned = hpIndex; break;
                                     case 10: dot11.hpAssigned = hpIndex; break;
                                     case 11: dot12.hpAssigned = hpIndex; break;
                                     case 12: dot13.hpAssigned = hpIndex; break;
                                     case 13: dot14.hpAssigned = hpIndex; break;
                                     case 14: dot15.hpAssigned = hpIndex; break;
                                     default: break;
                                 }
                             }
    }

    Connections {
        target: wdgWpr
        onDotZoneSelected: (dot, isSelected) => {
                             switch(dot) {
                                     case 0: dot1.selected = isSelected; break;
                                     case 1: dot2.selected = isSelected; break;
                                     case 2: dot3.selected = isSelected; break;
                                     case 3: dot4.selected = isSelected; break;
                                     case 4: dot5.selected = isSelected; break;
                                     case 5: dot6.selected = isSelected; break;
                                     case 6: dot7.selected = isSelected; break;
                                     case 7: dot8.selected = isSelected; break;
                                     case 8: dot9.selected = isSelected; break;
                                     case 9: dot10.selected = isSelected; break;
                                     case 10: dot11.selected = isSelected; break;
                                     case 11: dot12.selected = isSelected; break;
                                     case 12: dot13.selected = isSelected; break;
                                     case 13: dot14.selected = isSelected; break;
                                     case 14: dot15.selected = isSelected; break;
                                     default: break;
                                 }
                             }
    }
}


/*##^##
Designer {
    D{i:0;formeditorZoom:0.33;height:536;width:430}
}
##^##*/
