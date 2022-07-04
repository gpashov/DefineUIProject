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
        x: 300
        y: 134
        visible: false
        source: "images/c210_TorsoHombre.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: legsImg
        x: 262
        y: 134
        visible: false
        source: "images/c211_PiernasHombre.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: backImg
        x: 273
        y: 134
        visible: false
        source: "images/c212_BrazosEspaldaHombre.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: legsThighsImg
        x: 273
        y: 134
        visible: false
        source: "images/c213_PiernaMusloHombre.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: armsImg
        x: 273
        y: 134
        visible: false
        source: "images/c212_BrazosEspaldaHombre.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: neckImg
        x: 262
        y: 179
        visible: false
        source: "images/c214_CuelloHombre.png"
        fillMode: Image.PreserveAspectFit
    }

    ZoomDot {
        id: dot1
        x: 0
        y: 0
        visible: false
        state: states[0].name
        dotWidgetIndex: AppEnumsNs.SwDotZone0
    }

    ZoomDot {
        id: dot2
        x: 0
        y: 0
        visible: false
        state: states[0].name
        dotWidgetIndex: AppEnumsNs.SwDotZone1
    }

    ZoomDot {
        id: dot3
        x: 0
        y: 0
        visible: false
        state: states[0].name
        dotWidgetIndex: AppEnumsNs.SwDotZone2
    }

    ZoomDot {
        id: dot4
        x: 0
        y: 0
        visible: false
        state: states[0].name
        dotWidgetIndex: AppEnumsNs.SwDotZone3
    }

    ZoomDot {
        id: dot5
        x: 0
        y: 0
        visible: false
        state: states[0].name
        dotWidgetIndex: AppEnumsNs.SwDotZone4
    }

    ZoomDot {
        id: dot6
        x: 0
        y: 0
        visible: false
        state: states[0].name
        dotWidgetIndex: AppEnumsNs.SwDotZone5
    }

    ZoomDot {
        id: dot7
        x: 0
        y: 0
        visible: false
        state: states[0].name
        dotWidgetIndex: AppEnumsNs.SwDotZone6
    }

    ZoomDot {
        id: dot8
        x: 0
        y: 0
        visible: false
        state: states[0].name
        dotWidgetIndex: AppEnumsNs.SwDotZone7
    }

    ZoomDot {
        id: dot9
        x: 0
        y: 0
        visible: false
        state: states[0].name
        dotWidgetIndex: AppEnumsNs.SwDotZone8
    }

    ZoomDot {
        id: dot10
        x: 0
        y: 0
        visible: false
        state: states[0].name
        dotWidgetIndex: AppEnumsNs.SwDotZone9
    }

    ZoomDot {
        id: dot11
        x: 0
        y: 0
        visible: false
        state: states[0].name
        dotWidgetIndex: AppEnumsNs.SwDotZone10
    }

    ZoomDot {
        id: dot12
        x: 0
        y: 0
        visible: false
        state: states[0].name
        dotWidgetIndex: AppEnumsNs.SwDotZone11
    }

    ZoomDot {
        id: dot13
        x: 0
        y: 0
        visible: false
        state: states[0].name
        dotWidgetIndex: AppEnumsNs.SwDotZone12
    }

    ZoomDot {
        id: dot14
        x: 0
        y: 0
        visible: false
        state: states[0].name
        dotWidgetIndex: AppEnumsNs.SwDotZone13
    }

    ZoomDot {
        id: dot15
        x: 0
        y: 0
        visible: false
        state: states[0].name
        dotWidgetIndex: AppEnumsNs.SwDotZone14
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
                y: 256
                visible: true
            }

            PropertyChanges {
                target: dot2
                x: 411
                y: 256
                visible: true
            }

            PropertyChanges {
                target: dot3
                x: 540
                y: 323
                visible: true
            }

            PropertyChanges {
                target: dot4
                x: 438
                y: 323
                visible: true
            }

            PropertyChanges {
                target: dot5
                x: 540
                y: 374
                visible: true
            }

            PropertyChanges {
                target: dot6
                x: 489
                y: 374
                visible: true
            }

            PropertyChanges {
                target: dot7
                x: 438
                y: 374
                visible: true
            }

            PropertyChanges {
                target: dot8
                x: 540
                y: 433
                visible: true
            }

            PropertyChanges {
                target: dot9
                x: 489
                y: 433
                visible: true
            }

            PropertyChanges {
                target: dot10
                x: 438
                y: 433
                visible: true
            }

            PropertyChanges {
                target: dot11
                x: 489
                y: 486
            }

            PropertyChanges {
                target: dot12
                x: 559
                y: 422
                visible: true
            }

            PropertyChanges {
                target: dot13
                x: 416
                y: 422
                visible: true
            }

            PropertyChanges {
                target: dot14
                x: 540
                y: 269
                visible: true
            }

            PropertyChanges {
                target: dot15
                x: 443
                y: 269
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
                x: 585
                y: 307
                visible: true
            }

            PropertyChanges {
                target: dot2
                x: 397
                y: 307
                visible: true
            }

            PropertyChanges {
                target: dot3
                x: 506
                y: 346
                visible: true
            }

            PropertyChanges {
                target: dot4
                x: 477
                y: 346
                visible: true
            }

            PropertyChanges {
                target: dot5
                x: 544
                y: 454
                visible: true
            }

            PropertyChanges {
                target: dot6
                x: 435
                y: 454
                visible: true
            }

            PropertyChanges {
                target: dot7
                x: 518
                y: 470
                visible: true
            }

            PropertyChanges {
                target: dot8
                x: 465
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
                x: 436
                y: 306
                visible: true
            }

            PropertyChanges {
                target: dot2
                x: 543
                y: 306
                visible: true
            }

            PropertyChanges {
                target: dot3
                x: 436
                y: 365
                visible: true
            }

            PropertyChanges {
                target: dot4
                x: 543
                y: 365
                visible: true
            }

            PropertyChanges {
                target: dot5
                x: 436
                y: 439
                visible: true
            }

            PropertyChanges {
                target: dot6
                x: 543
                y: 439
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
                y: 252
                visible: true
            }

            PropertyChanges {
                target: dot2
                x: 547
                y: 252
                visible: true
            }

            PropertyChanges {
                target: dot3
                x: 435
                y: 321
                visible: true
            }

            PropertyChanges {
                target: dot4
                x: 547
                y: 321
                visible: true
            }

            PropertyChanges {
                target: dot5
                x: 435
                y: 372
                visible: true
            }

            PropertyChanges {
                target: dot6
                x: 547
                y: 372
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
                x: 366
                y: 300
                visible: true
            }

            PropertyChanges {
                target: dot2
                x: 617
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
                x: 490
                y: 323
                visible: true
            }

            PropertyChanges {
                target: dot2
                x: 541
                y: 308
                visible: true
            }

            PropertyChanges {
                target: dot3
                x: 438
                y: 308
                visible: true
            }
        }
    ]

    Connections {
        target: wdgWpr
        onBodyAreaSelected: (area) => {
                                switch(area) {
                                    case AppEnumsNs.AppGUIfullBodyTorso: state = "torsoState"; break;
                                    case AppEnumsNs.AppGUIfullBodyPiernas: state = "legsState"; break;
                                    case AppEnumsNs.AppGUIfullBodyEspalda: state = "backState"; break;
                                    case AppEnumsNs.AppGUIfullBodyPiernasMuslo: state = "legsThighsState"; break;
                                    case AppEnumsNs.AppGUIfullBodyBrazos: state = "armsState"; break;
                                    case AppEnumsNs.AppGUIfullBodyCuello: state = "neckState"; break;
                                    default: break;
                                }
                            }
    }

    Connections {
        target: wdgWpr
        onDotZoneEnabled: (id, enable) => {
                              switch(id) {
                                  case AppEnumsNs.SwDotZone0: dot1.enabled = enable; break;
                                  case AppEnumsNs.SwDotZone1: dot2.enabled = enable; break;
                                  case AppEnumsNs.SwDotZone2: dot3.enabled = enable; break;
                                  case AppEnumsNs.SwDotZone3: dot4.enabled = enable; break;
                                  case AppEnumsNs.SwDotZone4: dot5.enabled = enable; break;
                                  case AppEnumsNs.SwDotZone5: dot6.enabled = enable; break;
                                  case AppEnumsNs.SwDotZone6: dot7.enabled = enable; break;
                                  case AppEnumsNs.SwDotZone7: dot8.enabled = enable; break;
                                  case AppEnumsNs.SwDotZone8: dot9.enabled = enable; break;
                                  case AppEnumsNs.SwDotZone9: dot10.enabled = enable; break;
                                  case AppEnumsNs.SwDotZone10: dot11.enabled = enable; break;
                                  case AppEnumsNs.SwDotZone11: dot12.enabled = enable; break;
                                  case AppEnumsNs.SwDotZone12: dot13.enabled = enable; break;
                                  case AppEnumsNs.SwDotZone13: dot14.enabled = enable; break;
                                  case AppEnumsNs.SwDotZone14: dot15.enabled = enable; break;
                                  default: break;
                              }
                          }
    }

    Connections {
        target: wdgWpr
        onDotZoneHpAssigned: (dot, hpIndex) => {
                             switch(dot) {
                                     case AppEnumsNs.SwDotZone0: dot1.hpAssigned = hpIndex; break;
                                     case AppEnumsNs.SwDotZone1: dot2.hpAssigned = hpIndex; break;
                                     case AppEnumsNs.SwDotZone2: dot3.hpAssigned = hpIndex; break;
                                     case AppEnumsNs.SwDotZone3: dot4.hpAssigned = hpIndex; break;
                                     case AppEnumsNs.SwDotZone4: dot5.hpAssigned = hpIndex; break;
                                     case AppEnumsNs.SwDotZone5: dot6.hpAssigned = hpIndex; break;
                                     case AppEnumsNs.SwDotZone6: dot7.hpAssigned = hpIndex; break;
                                     case AppEnumsNs.SwDotZone7: dot8.hpAssigned = hpIndex; break;
                                     case AppEnumsNs.SwDotZone8: dot9.hpAssigned = hpIndex; break;
                                     case AppEnumsNs.SwDotZone9: dot10.hpAssigned = hpIndex; break;
                                     case AppEnumsNs.SwDotZone10: dot11.hpAssigned = hpIndex; break;
                                     case AppEnumsNs.SwDotZone11: dot12.hpAssigned = hpIndex; break;
                                     case AppEnumsNs.SwDotZone12: dot13.hpAssigned = hpIndex; break;
                                     case AppEnumsNs.SwDotZone13: dot14.hpAssigned = hpIndex; break;
                                     case AppEnumsNs.SwDotZone14: dot15.hpAssigned = hpIndex; break;
                                     default: break;
                                 }
                             }
    }

    Connections {
        target: wdgWpr
        onDotZoneSelected: (dot, isSelected) => {
                             switch(dot) {
                                     case AppEnumsNs.SwDotZone0: dot1.selected = isSelected; break;
                                     case AppEnumsNs.SwDotZone1: dot2.selected = isSelected; break;
                                     case AppEnumsNs.SwDotZone2: dot3.selected = isSelected; break;
                                     case AppEnumsNs.SwDotZone3: dot4.selected = isSelected; break;
                                     case AppEnumsNs.SwDotZone4: dot5.selected = isSelected; break;
                                     case AppEnumsNs.SwDotZone5: dot6.selected = isSelected; break;
                                     case AppEnumsNs.SwDotZone6: dot7.selected = isSelected; break;
                                     case AppEnumsNs.SwDotZone7: dot8.selected = isSelected; break;
                                     case AppEnumsNs.SwDotZone8: dot9.selected = isSelected; break;
                                     case AppEnumsNs.SwDotZone9: dot10.selected = isSelected; break;
                                     case AppEnumsNs.SwDotZone10: dot11.selected = isSelected; break;
                                     case AppEnumsNs.SwDotZone11: dot12.selected = isSelected; break;
                                     case AppEnumsNs.SwDotZone12: dot13.selected = isSelected; break;
                                     case AppEnumsNs.SwDotZone13: dot14.selected = isSelected; break;
                                     case AppEnumsNs.SwDotZone14: dot15.selected = isSelected; break;
                                     default: break;
                                 }
                             }
    }
}



