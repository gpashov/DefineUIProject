import QtQuick 2.15
import QtQuick.Controls 2.15
import DefineUIProject 1.0
import define.enums 1.0

Item {
    id: item1
    width: Constants.width
    height: Constants.height

    // This button is used to prevent the mouse/touch signals get to the other widgets.
    // If this doesn't work try to use MouseArea with propagateComposedEvents: false
    Button {
        id: maskingButton
        width: parent.width
        height: parent.height
        text: ""
        opacity: 0
        visible: false
    }

    ErrorPopupHp {
        id: errorPopupHp1
        visible: false
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 0
        anchors.topMargin: 0
        state: states[AppEnumsNs.APP_GUI_HP1_ID].name
    }

    ErrorPopupHp {
        id: errorPopupHp2
        x: 740
        visible: false
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.rightMargin: 0
        state: states[AppEnumsNs.APP_GUI_HP2_ID].name
    }

    ErrorPopupHp {
        id: errorPopupHp3
        visible: false
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
        state: states[AppEnumsNs.APP_GUI_HP3_ID].name
    }

    ErrorPopupHp {
        id: errorPopupHp4
        x: 740
        y: 0
        visible: false
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 0
        state: states[AppEnumsNs.APP_GUI_HP4_ID].name
    }

    ErrorPopupCentral {
        id: errorPopupCentral
        x: 282
        y: 256
        visible: false
    }

    Connections {
        target: wdgWpr
        onErrorPopupActivated: (hpIndex, isErrorActive) => {
                                   switch(hpIndex) {
                                   case APP_GUI_HP1_ID: errorPopupHp1.visible = isErrorActive; break;
                                   case APP_GUI_HP2_ID: errorPopupHp2.visible = isErrorActive; break;
                                   case APP_GUI_HP3_ID: errorPopupHp3.visible = isErrorActive; break;
                                   case APP_GUI_HP4_ID: errorPopupHp4.visible = isErrorActive; break;
                                   case APP_GUI_MAXNUM_HP: errorPopupCentral.visible = isErrorActive; break;
                                   }

                                   maskUserInteraction()
                               }

        onErrorPopupErrorCodeSet: (hpIndex, errorCode) => {
                                      switch(hpIndex) {
                                      case APP_GUI_HP1_ID: errorPopupHp1.errorCodeTxtText = errorCode; break;
                                      case APP_GUI_HP2_ID: errorPopupHp2.errorCodeTxtText = errorCode; break;
                                      case APP_GUI_HP3_ID: errorPopupHp3.errorCodeTxtText = errorCode; break;
                                      case APP_GUI_HP4_ID: errorPopupHp4.errorCodeTxtText = errorCode; break;
                                      case APP_GUI_MAXNUM_HP: errorPopupCentral.errorCodeTxtText = errorCode; break;
                                      }
                                  }
        onErrorPopupTreatmentTimeSet: (hpIndex, time) => {
                                          switch(hpIndex) {
                                          case APP_GUI_HP1_ID: errorPopupHp1.treatmentTimeTxtText = errorCode; break;
                                          case APP_GUI_HP2_ID: errorPopupHp2.treatmentTimeTxtText = errorCode; break;
                                          case APP_GUI_HP3_ID: errorPopupHp3.treatmentTimeTxtText = errorCode; break;
                                          case APP_GUI_HP4_ID: errorPopupHp4.treatmentTimeTxtText = errorCode; break;
                                          }
                                      }
        onErrorPopupErrorMessageImageSet: (hpIndex, idImg) => {
                                              var errImgState

                                              switch(idImg) {
                                              case AppEnumsNs.C355_signoalarma: errImgState = "standardErrorState"; break;
                                              //case AppEnumsNs.C355_signoalarma: errImgState = "noMessageErrorState"; break;
                                              case AppEnumsNs.C436_HPalarmaDesconexion: errImgState = "releaseHpErrorState"; break;
                                              case AppEnumsNs.C427_HPalarmaObstruccion: errImgState = "obstructionErrorState"; break;
                                              case AppEnumsNs.C429_HPalarmaBoton: errImgState = "setaErrorState"; break;
                                              case AppEnumsNs.C435_HPalarmaTemperatura: errImgState = "temperatureErrorState"; break;
                                              case AppEnumsNs.C460_LimiteResuccionesSuperado: errImgState = "resuctionsErrorState"; break;
                                              case AppEnumsNs.C550_SPIerr: errImgState = "spiErrorState"; break;
                                              case AppEnumsNs.C551_Com485err: errImgState = "com485ErrorState"; break;
                                              case AppEnumsNs.C552_Caudalerr: errImgState = "caudalErrorState"; break;
                                              case AppEnumsNs.C553_PowerErr: errImgState = "powerErrorState"; break;
                                              case AppEnumsNs.C554_RFIDerr: errImgState = "rfidErrorState"; break;
                                              case AppEnumsNs.C555_InsfNTC: errImgState = "insfNtcErrorState"; break;
                                              case AppEnumsNs.C556_ToutVacc: errImgState = "toutVaccErrorState"; break;
                                              case AppEnumsNs.C557_SinTramasMain: errImgState = "noMainThreadErrorState"; break;
                                              case AppEnumsNs.C558_ErrDesconocido: errImgState = "unknownErrorState"; break;
                                              case AppEnumsNs.C559_InternalTemp: errImgState = "internalTempErrorState"; break;
                                              case AppEnumsNs.C560_InternalSensors: errImgState = "internalSensorsErrorState"; break;
                                              case AppEnumsNs.C561_HPdesconfig: errImgState = "hpNotConfiguredErrorState"; break;
                                              case AppEnumsNs.C562_HPalarma: errImgState = "hpAlarmErrorState"; break;
                                              case AppEnumsNs.C563_PCBdanada: errImgState = "pcbDamagedErrorState"; break;
                                              case AppEnumsNs.C564_TestInicialFallo: errImgState = "initialTestFailedErrorState"; break;
                                              }

                                              switch(hpIndex) {
                                              case APP_GUI_HP1_ID: errorPopupHp1.errorMessageImgState = errImgState; break;
                                              case APP_GUI_HP2_ID: errorPopupHp2.errorMessageImgState = errImgState; break;
                                              case APP_GUI_HP3_ID: errorPopupHp3.errorMessageImgState = errImgState; break;
                                              case APP_GUI_HP4_ID: errorPopupHp4.errorMessageImgState = errImgState; break;
                                              case APP_GUI_MAXNUM_HP: errorPopupCentral.errorMessageImgState = errImgState; break;
                                              }
                                          }
    }

    function maskUserInteraction() {
        if ( errorPopupHp1.visible ||
             errorPopupHp2.visible ||
             errorPopupHp3.visible ||
             errorPopupHp4.visible ||
             errorPopupCentral.visible ) {
            maskingButton.visible = true
        }
        else {
            maskingButton.visible = false
        }

    }

}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.66;height:768;width:1024}
}
##^##*/
