import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 138
    height: 138

    Image {
        id: standardImg
        x: 0
        y: 0
        visible: false
        source: "images/c355_signoalarma.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: noMsgImg
        x: 0
        y: 0
        visible: false
        source: "images/c355_signoalarma.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: releaseHpImg
        x: 0
        y: 0
        visible: false
        source: "images/c436_HPalarmaDesconexion.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: obstructionImg
        x: 0
        y: 0
        visible: false
        source: "images/c427_HPalarmaObstruccion.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: setaImg
        x: 0
        y: 0
        visible: false
        source: "images/c429_HPalarmaBoton.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: temperatureImg
        x: 0
        y: 0
        visible: false
        source: "images/c435_HPalarmaTemperatura.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: resuctionsImg
        x: 0
        y: 0
        visible: false
        source: "images/c460_LimiteResuccionesSuperado.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: spiImg
        x: 0
        y: 0
        visible: false
        source: "images/c550_SPIerr.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: com485Img
        x: 0
        y: 0
        visible: false
        source: "images/c551_Com485err.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: caudalImg
        x: 0
        y: 0
        visible: false
        source: "images/c552_Caudalerr.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: powerImg
        x: 0
        y: 0
        visible: false
        source: "images/c553_PowerErr.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: rfidImg
        x: 0
        y: 0
        visible: false
        source: "images/c554_RFIDerr.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: insifucuentesNtcImg
        x: 0
        y: 0
        visible: false
        source: "images/c555_InsfNTC.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: toutVaccImg
        x: 0
        y: 0
        visible: false
        source: "images/c556_ToutVacc.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: noMainThreadImg
        x: 0
        y: 0
        visible: false
        source: "images/c557_SinTramasMain.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: unknownImg
        x: 0
        y: 0
        visible: false
        source: "images/c558_ErrDesconocido.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: internalTempImg
        x: 0
        y: 0
        visible: false
        source: "images/c559_InternalTemp.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: internalSensorsImg
        x: 0
        y: 0
        visible: false
        source: "images/c560_InternalSensors.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: hpNotConfiguredImg
        x: 0
        y: 0
        visible: false
        source: "images/c561_HPdesconfig.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: hpAlarmImg
        x: 0
        y: 0
        visible: false
        source: "images/c562_HPalarma.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: pcbDamagedImg
        x: 0
        y: 0
        visible: false
        source: "images/c563_PCBdanada.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: initialTestFailedImg
        x: 0
        y: 0
        visible: false
        source: "images/c564_TestInicialFallo.png"
        fillMode: Image.PreserveAspectFit
    }
    states: [
        State {
            name: "standardErrorState"

            PropertyChanges {
                target: standardImg
                visible: true
            }
        },
        State {
            name: "noMessageErrorState"

            PropertyChanges {
                target: noMsgImg
                visible: true
            }
        },
        State {
            name: "releaseHpErrorState"

            PropertyChanges {
                target: releaseHpImg
                visible: true
            }
        },
        State {
            name: "obstructionErrorState"

            PropertyChanges {
                target: obstructionImg
                visible: true
            }
        },
        State {
            name: "setaErrorState"

            PropertyChanges {
                target: setaImg
                visible: true
            }
        },
        State {
            name: "temperatureErrorState"

            PropertyChanges {
                target: temperatureImg
                visible: true
            }
        },
        State {
            name: "resuctionsErrorState"

            PropertyChanges {
                target: resuctionsImg
                visible: true
            }
        },
        State {
            name: "spiErrorState"

            PropertyChanges {
                target: spiImg
                visible: true
            }
        },
        State {
            name: "com485ErrorState"

            PropertyChanges {
                target: com485Img
                visible: true
            }
        },
        State {
            name: "caudalErrorState"

            PropertyChanges {
                target: caudalImg
                visible: true
            }
        },
        State {
            name: "powerErrorState"

            PropertyChanges {
                target: powerImg
                visible: true
            }
        },
        State {
            name: "rfidErrorState"

            PropertyChanges {
                target: rfidImg
                visible: true
            }
        },
        State {
            name: "insfNtcErrorState"

            PropertyChanges {
                target: insifucuentesNtcImg
                visible: true
            }
        },
        State {
            name: "toutVaccErrorState"

            PropertyChanges {
                target: toutVaccImg
                visible: true
            }
        },
        State {
            name: "noMainThreadErrorState"

            PropertyChanges {
                target: noMainThreadImg
                visible: true
            }
        },
        State {
            name: "unknownErrorState"

            PropertyChanges {
                target: unknownImg
                visible: true
            }
        },
        State {
            name: "internalTempErrorState"

            PropertyChanges {
                target: internalTempImg
                visible: true
            }
        },
        State {
            name: "internalSensorsErrorState"

            PropertyChanges {
                target: internalSensorsImg
                visible: true
            }
        },
        State {
            name: "hpNotConfiguredErrorState"

            PropertyChanges {
                target: hpNotConfiguredImg
                visible: true
            }
        },
        State {
            name: "hpAlarmErrorState"

            PropertyChanges {
                target: hpAlarmImg
                visible: true
            }
        },
        State {
            name: "pcbDamagedErrorState"

            PropertyChanges {
                target: pcbDamagedImg
                visible: true
            }
        },
        State {
            name: "initialTestFailedErrorState"

            PropertyChanges {
                target: initialTestFailedImg
                visible: true
            }
        }
    ]

}

