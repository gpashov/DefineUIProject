import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0

Item {
    id: item1
    width: backgroundImage.width
    height: backgroundImage.height

    Image {
        id: backgroundImage
        x: 0
        y: 0
        source: "images/c317_FondoConfiguracion.png"
        fillMode: Image.PreserveAspectFit
    }


    TwoStateButton {
        id: updateSoftwareButton
        x: 429
        y: 139
        imageSourcePressed: "images/c324_ConfgBotondownloadPress.png"
        imageSourceReleased: "images/c323_ConfgBotondownloadRls.png"
    }

    Text {
        id: modelText
        x: 79
        y: 90
        width: 161
        height: 31
        color: "#ccccce"
        text: wdgWpr.confModel
        font.pixelSize: 16
    }

    Text {
        id: swVersionText
        y: 153
        width: 161
        height: 31
        color: "#ccccce"
        text: wdgWpr.confVersion
        anchors.left: modelText.left
        font.pixelSize: 16
        anchors.leftMargin: 0
    }


    TwoStateButton {
        id: refillCoolantButton
        x: 423
        y: 228
        imageSourceReleased: "images/c323_2_ConfigBotonRecargaCoolantRls.png"
        imageSourcePressed: "images/c324_2_ConfigBotonRecargaCoolantPress.png"
    }

    TwoStateButton {
        id: vacuumSwitch
        y: 292
        anchors.left: refillCoolantButton.left
        anchors.leftMargin: 0
        imageSourcePressed: "images/c513_resuccionboton_Press.png"
        imageSourceReleased: "images/c514_resuccionboton_Rls.png"
    }

    TwoStateButton {
        id: temperatureSwitch
        y: 369
        anchors.left: refillCoolantButton.left
        imageSourcePressed: "images/c512_TempShowboton_Press.png"
        anchors.leftMargin: 0
        imageSourceReleased: "images/c512_TempShowboton_Rls.png"
    }

    TwoStateButton {
        id: cleanUpHP1Button
        x: 109
        y: 228
        imageSourceReleased: "images/c521_LimpiezamanipuloHP1_Rls.png"
        imageSourcePressed: "images/c522LimpiezamanipuloHP1_Press.png"
    }

    TwoStateButton {
        id: cleanUpHP2Button
        x: 262
        anchors.top: cleanUpHP1Button.top
        imageSourceReleased: "images/c524_LimpiezamanipuloHP2_Rls.png"
        imageSourcePressed: "images/c525_LimpiezamanipuloHP2_Press.png"
    }

    TwoStateButton {
        id: cleanUpHP3Button
        y: 356
        anchors.left: cleanUpHP1Button.left
        imageSourceReleased: "images/c518_LimpiezamanipuloHP3_Rls.png"
        imageSourcePressed: "images/c520_LimpiezamanipuloHP3_Press.png"
    }

    TwoStateButton {
        id: cleanUpHP4Button
        anchors.left: cleanUpHP2Button.left
        anchors.top: cleanUpHP3Button.top
        imageSourceReleased: "images/c527_LimpiezamanipuloHP4_Rls.png"
        imageSourcePressed: "images/c528_LimpiezamanipuloHP4_Press.png"
    }

    TwoStateButton {
        id: cleanUpHPRoundButton
        x: 186
        y: 294
        imageSourceReleased: "images/c516_Limpiezamanipulox4_Rls.png"
        imageSourcePressed: "images/c515_Limpiezamanipulox4_Press.png"
    }
}



/*##^##
Designer {
    D{i:0;height:545;width:581}
}
##^##*/
