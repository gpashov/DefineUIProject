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
        argWidget.id = ButSelectWoman;
    }
    else
    {
        argWidget.id = ButSelectMan;
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
    argWidget.id = ButTrtScrHome;
    CBKbutHomeF(&argWidget);
}

void CallbackWrapper::butConfig()
{
    argWidget.id = ButTrtScrCfg;
    CBKbutConfigF(&argWidget);
}

void CallbackWrapper::butCalc()
{
    argWidget.id = ButTrtScrCalc;
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
    case APP_GUI_HP1_ID:argWidget.id = ButCtrlPnlPlayHP1; break;
    case APP_GUI_HP2_ID:argWidget.id = ButCtrlPnlPlayHP2; break;
    case APP_GUI_HP3_ID:argWidget.id = ButCtrlPnlPlayHP3; break;
    case APP_GUI_HP4_ID:argWidget.id = ButCtrlPnlPlayHP4; break;
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

void CallbackWrapper::butSelectTime(EAppGUI_HPsIDs hpId)
{
    switch(hpId) {
    case APP_GUI_HP1_ID:argWidget.id = ButSelectTimeHP1; break;
    case APP_GUI_HP2_ID:argWidget.id = ButSelectTimeHP2; break;
    case APP_GUI_HP3_ID:argWidget.id = ButSelectTimeHP3; break;
    case APP_GUI_HP4_ID:argWidget.id = ButSelectTimeHP4; break;
    default: argWidget.id = APP_GUI_NUM_WIDGETS; break;
    }

    CBKbutSelectTimeF(&argWidget);
}

void CallbackWrapper::butTemperatureVwr(EAppGUI_HPsIDs hpId)
{
    switch(hpId) {
    case APP_GUI_HP1_ID:argWidget.id = ButVwrTemperatureHP1; break;
    case APP_GUI_HP2_ID:argWidget.id = ButVwrTemperatureHP2; break;
    case APP_GUI_HP3_ID:argWidget.id = ButVwrTemperatureHP3; break;
    case APP_GUI_HP4_ID:argWidget.id = ButVwrTemperatureHP4; break;
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
    case APP_GUI_HP1_ID:argWidget.id = ButModelImageHP1; break;
    case APP_GUI_HP2_ID:argWidget.id = ButModelImageHP2; break;
    case APP_GUI_HP3_ID:argWidget.id = ButModelImageHP3; break;
    case APP_GUI_HP4_ID:argWidget.id = ButModelImageHP4; break;
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
    case AppGUIfullBodyTorso: argWidget.id = ButFullBodyTorso; break;
    case AppGUIfullBodyPiernas: argWidget.id = ButFullBodyPiernas; break;
    case AppGUIfullBodyEspalda: argWidget.id = ButFullBodyEspalda; break;
    case AppGUIfullBodyPiernasMuslo: argWidget.id = ButFullBodyPiernaMuslo; break;
    case AppGUIfullBodyBrazos: argWidget.id = ButFullBodyBrazos; break;
    case AppGUIfullBodyCuello: argWidget.id = ButFullBodyCuello; break;
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

void CallbackWrapper::popupVisibleChanged( EAppGUIwidgetIDlist widgetId, bool visible )
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

void CallbackWrapper::butPopUpTimeValue(EAppGUI_HPsIDs hpId, EAppGUIwidgetIDlist buttonId)
{
    argWidget.id = buttonId;
    CBKbutPopUpTimeValueF(&argWidget);
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
    case 0: argWidget.id = ButNum0Calc; break;
    case 1: argWidget.id = ButNum1Calc; break;
    case 2: argWidget.id = ButNum2Calc; break;
    case 3: argWidget.id = ButNum3Calc; break;
    case 4: argWidget.id = ButNum4Calc; break;
    case 5: argWidget.id = ButNum5Calc; break;
    case 6: argWidget.id = ButNum6Calc; break;
    case 7: argWidget.id = ButNum7Calc; break;
    case 8: argWidget.id = ButNum8Calc; break;
    case 9: argWidget.id = ButNum9Calc; break;
    default: return; break;
    }

    CBKbutNumCalcF(&argWidget);
}

void CallbackWrapper::buttonEnterCalc()
{
    argWidget.id = ButEnterCalc;
    CBKbutEnterCalcF(&argWidget);
}

void CallbackWrapper::buttonCECalc()
{
    argWidget.id = ButCECalc;
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

void CallbackWrapper::loadAnimationEnd()
{
    CBKLoadAnimationEnd();
}
