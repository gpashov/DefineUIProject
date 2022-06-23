#include <QtDebug>
#include "callbackwrapper.h"
#include "../AppGUI/AppGuiInterfaceStructure.h"
#include "../AppGUI/K70_GUI.h"
#include "../Callback/cbk.h"

stWidget argWidget;

CallbackWrapper::CallbackWrapper(QObject *parent)
    : QObject{parent}
{

}

void CallbackWrapper::dummy()
{

}

void CallbackWrapper::butGenderSelect(EAppGUIbodys gender)
{
    if (gender == AppGUIbodyFemale) {
        argWidget.id = butSelectWoman;
    }
    else
    {
        argWidget.id = butSelectMan;
    }
    CBKbutGenderSelectF(&argWidget);
}

void CallbackWrapper::butMainMenuShow()
{
    CBKbutMainMenuShowF();
}

void CallbackWrapper::butMainMenuHide()
{
    CBKbutMainMenuHideF();
}

//void CallbackWrapper::butMainMenuShow()
//{

//}

//void CallbackWrapper::butMainMenuHide()
//{

//}

void CallbackWrapper::butHome()
{
    argWidget.id = butTrtScrHome;
    CBKbutHomeF(&argWidget);
}

void CallbackWrapper::butConfig()
{
    argWidget.id = butTrtScrCfg;
    CBKbutConfigF(&argWidget);
}

void CallbackWrapper::butCalc()
{
    argWidget.id = butTrtScrCalc;
    CBKbutCalcF(&argWidget);
}

void CallbackWrapper::butData()
{

}

void CallbackWrapper::butWarningOn()
{
    CBKbutWarningOnF();
}

void CallbackWrapper::butWarningOff()
{
    CBKbutWarningOffF();
}

void CallbackWrapper::butCtrlPnlPlay(EAppGUI_HPsIDs hpId)
{
    switch(hpId) {
    case APP_GUI_HP1_ID:argWidget.id = butCtrlPnlPlayHP1; break;
    case APP_GUI_HP2_ID:argWidget.id = butCtrlPnlPlayHP2; break;
    case APP_GUI_HP3_ID:argWidget.id = butCtrlPnlPlayHP3; break;
    case APP_GUI_HP4_ID:argWidget.id = butCtrlPnlPlayHP4; break;
    default: argWidget.id = APP_GUI_NUM_WIDGETS; break;
    }

    CBKbutCtrlPnlPlayF(&argWidget);
}

void CallbackWrapper::swCtrlPnlTstVacOn()
{

}

void CallbackWrapper::swCtrlPnlTstVacOff()
{

}

void CallbackWrapper::butSelectTime()
{

}

void CallbackWrapper::butTemperatureVwr(EAppGUI_HPsIDs hpId)
{
    switch(hpId) {
    case APP_GUI_HP1_ID:argWidget.id = butVwrTemperatureHP1; break;
    case APP_GUI_HP2_ID:argWidget.id = butVwrTemperatureHP2; break;
    case APP_GUI_HP3_ID:argWidget.id = butVwrTemperatureHP3; break;
    case APP_GUI_HP4_ID:argWidget.id = butVwrTemperatureHP4; break;
    default: argWidget.id = APP_GUI_NUM_WIDGETS; break;
    }

    CBKbutTemperatureVwrF(&argWidget);
}

void CallbackWrapper::butTRTmodeAutoManual()
{

}

void CallbackWrapper::butInfoZoneSelectedOn()
{
    CBKbutInfoZoneSelectedOnF();
}

void CallbackWrapper::butInfoZoneSelectedOff()
{
    CBKbutInfoZoneSelectedOffF();
}

void CallbackWrapper::butModelImage(EAppGUI_HPsIDs hpId)
{
    switch(hpId) {
    case APP_GUI_HP1_ID:argWidget.id = butModelImageHP1; break;
    case APP_GUI_HP2_ID:argWidget.id = butModelImageHP2; break;
    case APP_GUI_HP3_ID:argWidget.id = butModelImageHP3; break;
    case APP_GUI_HP4_ID:argWidget.id = butModelImageHP4; break;
    default: argWidget.id = APP_GUI_NUM_WIDGETS; break;
    }

    CBKbutModelImageF(&argWidget);
}

void CallbackWrapper::butHideCtrlPnl()
{

}

void CallbackWrapper::butShowCtrlPnl()
{

}

void CallbackWrapper::butFullBodyArea(EAppGUIfullBodyAreas bodyArea)
{
    switch(bodyArea) {
    case AppGUIfullBodyTorso: argWidget.id = butFullBodyTorso; break;
    case AppGUIfullBodyPiernas: argWidget.id = butFullBodyPiernas; break;
    case AppGUIfullBodyEspalda: argWidget.id = butFullBodyEspalda; break;
    case AppGUIfullBodyPiernasMuslo: argWidget.id = butFullBodyPiernaMuslo; break;
    case AppGUIfullBodyBrazos: argWidget.id = butFullBodyBrazos; break;
    case AppGUIfullBodyCuello: argWidget.id = butFullBodyCuello; break;
    default: argWidget.id = APP_GUI_NUM_WIDGETS; break;
    }

    CBKbutFullBodyAreaF(&argWidget);
}

void CallbackWrapper::swDotZoneOn(EAppGUIwidgetIDlist widgetId)
{
    argWidget.id = widgetId;
    CBKswDotZoneOnF(&argWidget);
}

void CallbackWrapper::swDotZoneOff(EAppGUIwidgetIDlist widgetId)
{
    argWidget.id = widgetId;
    CBKswDotZoneOffF(&argWidget);
}

void CallbackWrapper::popUpVisibleChanged( EAppGUIwidgetIDlist widgetId, bool visible )
{
    argWidget.id = widgetId;
    CBKpopUpDisplayedF( &argWidget, visible );
}

void CallbackWrapper::butPopUpReturn()
{
    CBKbutPopUpReturnF();
}

void CallbackWrapper::butReuseRFIDlabel()
{

}

void CallbackWrapper::butPopUpTimeValue()
{

}

void CallbackWrapper::butPopUpTstVacManual()
{

}

void CallbackWrapper::butPopUpTstVacAuto()
{

}

void CallbackWrapper::butPopUpVacSmallLvl()
{

}

void CallbackWrapper::swPopUpTstVacLvlOn()
{

}

void CallbackWrapper::swPopUpTstVacLvlOff()
{

}

void CallbackWrapper::butPopUpErrOk()
{

}

void CallbackWrapper::buttonNumCalc(uint8 calcNumber)
{
    switch(calcNumber)
    {
    case 0: argWidget.id = butNum0Calc; break;
    case 1: argWidget.id = butNum1Calc; break;
    case 2: argWidget.id = butNum2Calc; break;
    case 3: argWidget.id = butNum3Calc; break;
    case 4: argWidget.id = butNum4Calc; break;
    case 5: argWidget.id = butNum5Calc; break;
    case 6: argWidget.id = butNum6Calc; break;
    case 7: argWidget.id = butNum7Calc; break;
    case 8: argWidget.id = butNum8Calc; break;
    case 9: argWidget.id = butNum9Calc; break;
    default: return; break;
    }

    CBKbutNumCalcF(&argWidget);
}

void CallbackWrapper::buttonEnterCalc()
{
    argWidget.id = butEnterCalc;
    CBKbutEnterCalcF(&argWidget);
}

void CallbackWrapper::buttonCECalc()
{
    argWidget.id = butCECalc;
    CBKbutCECalcF(&argWidget);
}

void CallbackWrapper::butSoftUpdateCfg()
{

}

void CallbackWrapper::butRecargaCoolant()
{

}

void CallbackWrapper::swResuctionsVierew()
{

}

void CallbackWrapper::swCfgTemperatureViewer()
{

}

void CallbackWrapper::butCleanUpHP()
{

}

void CallbackWrapper::butCleanUpHPround()
{

}

void CallbackWrapper::swLanguage()
{

}

void CallbackWrapper::swCountry()
{

}

void CallbackWrapper::butPopUpCleanUp()
{

}

void CallbackWrapper::butPopUpCleanUpYES()
{

}

void CallbackWrapper::butPopUpCleanUpNO()
{

}

void CallbackWrapper::butPopUpCleanUpCancel()
{

}

void CallbackWrapper::butSATnextPage()
{

}

void CallbackWrapper::butSATprevPage()
{

}

void CallbackWrapper::swSATVacOn()
{

}

void CallbackWrapper::swSATVacOff()
{

}

void CallbackWrapper::swSATFrioOn()
{

}

void CallbackWrapper::swSATFrioOff()
{

}

void CallbackWrapper::swSATrfidOn()
{

}

void CallbackWrapper::swSATrfidOff()
{

}

void CallbackWrapper::swSATtestLedOn()
{

}

void CallbackWrapper::swSATtestLedOff()
{

}

void CallbackWrapper::swSATtestLedRGBOn()
{

}

void CallbackWrapper::swSATtestLedRGBOff()
{

}

void CallbackWrapper::swFATIGUEfailBelloff()
{

}

void CallbackWrapper::butOkSATerr()
{

}
