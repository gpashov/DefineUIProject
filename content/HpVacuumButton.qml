import QtQuick 2.15
import QtQuick.Controls 2.15
import define.enums 1.0

Item {
    id: item1
    readonly property int vacuumLevelMax: 3
    property int vacuumLevel: 0
    property int buttonState: AppEnumsNs.App_GUI_Max_Vac_but_states
    property bool positionIsRight: false  // false - left, true - right

    property var prsImagesLeft: [
        // Vacuum level 1
        "images/c042_BotonVacuum1MarcaAguaLeft.png",    /*OFF_L*/
        "images/c040_BotonVacuum1PressLeft.png",        /*ON_L*/
        "images/c352_BotonVacuum1PressArrowLeft.png",   /*VacAdjustL*/

        // Vacuum level 2
        "images/c042_BotonVacuum2MarcaAguaLeft.png",    /*OFF_L*/
        "images/c040_BotonVacuum2PressLeft.png",        /*ON_L*/
        "images/c352_BotonVacuum2PressArrowLeft.png",   /*VacAdjustL*/

        // Vacuum level 3
        "images/c042_BotonVacuum3MarcaAguaLeft.png",    /*OFF_L*/
        "images/c040_BotonVacuum3PressLeft.png",        /*ON_L*/
        "images/c352_BotonVacuum3PressArrowLeft.png",   /*VacAdjustL*/
    ]

    property var rlsImagesLeft: [
        // Vacuum level 1
        "images/c042_BotonVacuum1MarcaAguaLeft.png",    /*OFF_L*/
        "images/c041_BotonVacuum1RlsLeft.png",          /*ON_L*/
        "images/c353_BotonVacuum1RlsArrowLeft.png",     /*VacAdjustL*/

        // Vacuum level 2
        "images/c042_BotonVacuum2MarcaAguaLeft.png",    /*OFF_L*/
        "images/c041_BotonVacuum2RlsLeft.png",          /*ON_L*/
        "images/c353_BotonVacuum2RlsArrowLeft.png",     /*VacAdjustL*/

        // Vacuum level 3
        "images/c042_BotonVacuum3MarcaAguaLeft.png",    /*OFF_L*/
        "images/c041_BotonVacuum3RlsLeft.png",          /*ON_L*/
        "images/c353_BotonVacuum3RlsArrowLeft.png",     /*VacAdjustL*/
    ]

    property var prsImagesRight: [
        // Vacuum level 1
        "images/c042_BotonVacuum1MarcaAguaRight.png",   /*OFF_R*/
        "images/c040_BotonVacuum1PressRight.png",       /*ON_R*/
        "images/c352_BotonVacuum1PressArrowRight.png",  /*VacAdjustR*/

        // Vacuum level 2
        "images/c042_BotonVacuum2MarcaAguaRight.png",   /*OFF_R*/
        "images/c040_BotonVacuum2PressRight.png",       /*ON_R*/
        "images/c352_BotonVacuum2PressArrowRight.png",  /*VacAdjustR*/

        // Vacuum level 3
        "images/c042_BotonVacuum3MarcaAguaRight.png",   /*OFF_R*/
        "images/c040_BotonVacuum3PressRight.png",       /*ON_R*/
        "images/c352_BotonVacuum3PressArrowRight.png"   /*VacAdjustR*/
    ]

    property var rlsImagesRight: [
        // Vacuum level 1
        "images/c042_BotonVacuum1MarcaAguaRight.png",   /*OFF_R*/
        "images/c041_BotonVacuum1RlsRight.png",         /*ON_R*/
        "images/c353_BotonVacuum1RlsArrowRight.png",    /*VacAdjustR*/

        // Vacuum level 2
        "images/c042_BotonVacuum2MarcaAguaRight.png",   /*OFF_R*/
        "images/c041_BotonVacuum2RlsRight.png",         /*ON_R*/
        "images/c353_BotonVacuum2RlsArrowRight.png",    /*VacAdjustR*/

        // Vacuum level 3
        "images/c042_BotonVacuum3MarcaAguaRight.png",   /*OFF_R*/
        "images/c041_BotonVacuum3RlsRight.png",         /*ON_R*/
        "images/c353_BotonVacuum3RlsArrowRight.png"     /*VacAdjustR*/
    ]


    CustomSwitch {
        id: customSwitch
        onStateImageSource: "images/c042_BotonVacuum1MarcaAguaLeft.png"
        offPressedStateImageSource: "images/c042_BotonVacuum1MarcaAguaLeft.png"
        offStateImageSource: "images/c042_BotonVacuum1MarcaAguaLeft.png"
        onPressedStateImageSource: "images/c042_BotonVacuum1MarcaAguaLeft.png"
    }

    onButtonStateChanged: setSwitchImages()
    onVacuumLevelChanged: setSwitchImages()

    function setSwitchImages() {
        if (buttonState !== AppEnumsNs.App_GUI_Vac_but_disabled) {
            if (vacuumLevel < vacuumLevelMax && buttonState < AppEnumsNs.App_GUI_Max_Vac_but_states ) { // Check if the values are not out of range
                customSwitch.onStateImageSource = positionIsRight ? prsImagesRight[ vacuumLevel * vacuumLevelMax + buttonState ] : prsImagesLeft[ vacuumLevel * vacuumLevelMax + buttonState ]
                customSwitch.offPressedStateImageSource = customSwitch.onStateImageSource
                customSwitch.offStateImageSource = positionIsRight ? rlsImagesRight[ vacuumLevel * vacuumLevelMax + buttonState ] : rlsImagesLeft[ vacuumLevel * vacuumLevelMax + buttonState ]
                customSwitch.onPressedStateImageSource = customSwitch.offStateImageSource
            }

            customSwitch.enabled = true
        }
        else
        {
            customSwitch.enabled = false
        }
    }
}



