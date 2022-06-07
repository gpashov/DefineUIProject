

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: backgroundImg.width
    height: backgroundImg.height
    property alias realTimeClockWarning: realTimeClockWarningImg.visible
    property alias coolantVeryLowWarning: coolantVeryLowWarningImg.visible
    property alias coolantLowWarning: coolantLowWarningImg.visible
    property alias rfidWarning: rfidWarningImg.visible
    property alias rearFilterWarning: rearFilterWarningImg.visible
    property alias roomTemperatureWarning: roomTemperatureWarningImg.visible

    Image {
        id: backgroundImg
        source: "images/c420_Menualarmasfondo.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: realTimeClockWarningImg
        x: 373
        y: 46
        source: "images/c426_Menualarmatiempopress.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: coolantVeryLowWarningImg
        x: 315
        y: 46
        source: "images/c425_Menualarmasinaguapress.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: coolantLowWarningImg
        x: 247
        y: 46
        source: "images/c424_Menualarmaaguamitadpress.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: rfidWarningImg
        x: 170
        y: 46
        source: "images/c423_Menualarmarfidpress.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: rearFilterWarningImg
        x: 103
        y: 46
        source: "images/c422_Menualarmafiltropress.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: roomTemperatureWarningImg
        x: 47
        y: 46
        source: "images/c421_Menualarmatemppress.png"
        fillMode: Image.PreserveAspectFit
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.1}
}
##^##*/

