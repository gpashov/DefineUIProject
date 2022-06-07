import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0
Item {
    id: item1
    width: Constants.width
    height: Constants.height

    Image {
        id: bodySilhouetteImg
        x: 324
        y: 147
        source: "images/c002_SiluetaMujerFrenteEspalda.png"
        fillMode: Image.PreserveAspectFit
    }

    CustomRadioButton {
        id: torsoRadioButton
        x: 363
        y: 266
        indicatorImageSource: "images/c113_BotonTorsoPressMujer.png"
    }

    CustomRadioButton {
        id: legsRadioButton
        x: 363
        y: 378
        indicatorImageSource: "images/c115_BotonPiernasRlsMujer.png"
    }

    CustomRadioButton {
        id: armsRadioButton
        x: 533
        y: 256
        indicatorImageSource: "images/c118_BotonBrazosRlsMujer.png"
    }

    // This must be on top of the 'arms' button to work properly because they overlap
    CustomRadioButton {
        id: backRadioButton
        x: 564
        y: 260
        indicatorImageSource: "images/c121_BotonEspaldaRlsMujer.png"
    }

    CustomRadioButton {
        id: thighsRadioButton
        x: 554
        y: 387
        indicatorImageSource: "images/c124_BotonPiernaMusloRlsMujer.png"
    }

    CustomRadioButton {
        id: neckRadioButton
        x: 401
        y: 215
        indicatorImageSource: "images/c127_BotonCuelloRlsMujer.png"
    }

    Image {
        id: dotZoneHP1
        x: 370
        y: 294
        source: "images/c160_ZonaSeleccionadaHP1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: dotZoneHP2
        x: 401
        y: 243
        source: "images/c161_ZonaSeleccionadaHP2.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: dotZoneHP3
        x: 369
        y: 340
        source: "images/c162_ZonaSeleccionadaHP3.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: dotZoneHP4
        x: 407
        y: 366
        source: "images/c163_ZonaSeleccionadaHP4.png"
        fillMode: Image.PreserveAspectFit
    }

    states: [
        State {
            name: "femaleState"
        },
        State {
            name: "maleState"

            PropertyChanges {
                target: bodySilhouetteImg
                x: 282
                source: "images/c003_SiluetaHombreFrenteEspalda.png"
            }

            PropertyChanges {
                target: torsoRadioButton
                x: 346
                y: 259
                width: 122
                height: 160
                indicatorImageSource: "images/c130_BotonTorsoRlsHombre.png"
            }

            PropertyChanges {
                target: legsRadioButton
                x: 347
                y: 419
                width: 122
                height: 145
                indicatorImageSource: "images/c133_BotonPiernasRlsHombre.png"
            }

            PropertyChanges {
                target: armsRadioButton
                x: 540
                y: 259
                width: 163
                indicatorImageSource: "images/c136_BotonBrazosRlsHombre.png"
            }

            PropertyChanges {
                target: backRadioButton
                x: 575
                y: 259
                width: 91
                height: 122
                indicatorImageSource: "images/c139_BotonEspaldaRlsHombre.png"
            }

            PropertyChanges {
                target: thighsRadioButton
                x: 571
                y: 380
                width: 102
                height: 146
                indicatorImageSource: "images/c142_BotonPiernaMusloRlsHombre.png"
            }

            PropertyChanges {
                target: neckRadioButton
                x: 378
                y: 224
                width: 55
                indicatorImageSource: "images/c145_BotonCuelloRlsHombre.png"
            }

            PropertyChanges {
                target: dotZoneHP2
                x: 275
                y: 292
            }

            PropertyChanges {
                target: dotZoneHP1
                x: 275
                y: 274
            }

            PropertyChanges {
                target: dotZoneHP3
                x: 275
                y: 310
            }

            PropertyChanges {
                target: dotZoneHP4
                x: 275
                y: 328
            }
        }
    ]

}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25;height:768;width:1024}
}
##^##*/
