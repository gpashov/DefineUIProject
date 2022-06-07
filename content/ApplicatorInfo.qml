import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: backgraoundImage.width
    height: backgraoundImage.height
    property alias backgraoundImageSource: backgraoundImage.source

    Image {
        id: backgraoundImage
        source: "images/c004_MenuTrtHP1.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c183_IndicadorRFIDHP1Off
        x: 21
        y: 198
        source: "images/c183_IndicadorRFIDHP1Off.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c184_IndicadorBotonHP1Off
        x: 21
        y: 147
        source: "images/c184_IndicadorBotonHP1Off.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c185_IndicadorVacHP1Off
        x: 21
        y: 98
        source: "images/c185_IndicadorVacHP1Off.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: c186_IndicadorFrioHP1Off
        x: 21
        y: 47
        source: "images/c186_IndicadorFrioHP1Off.png"
        fillMode: Image.PreserveAspectFit
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}
}
##^##*/
