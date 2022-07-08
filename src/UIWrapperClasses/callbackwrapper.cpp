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
    CBKbutDataF(&argWidget);
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

void CallbackWrapper::swCtrlPnlTstVacOn(EAppGUI_HPsIDs hpId)
{
    switch(hpId) {
    case APP_GUI_HP1_ID:argWidget.id = SwCtrlPnlTstVacHP1; break;
    case APP_GUI_HP2_ID:argWidget.id = SwCtrlPnlTstVacHP2; break;
    case APP_GUI_HP3_ID:argWidget.id = SwCtrlPnlTstVacHP3; break;
    case APP_GUI_HP4_ID:argWidget.id = SwCtrlPnlTstVacHP4; break;
    default: argWidget.id = APP_GUI_NUM_WIDGETS; break;
    }

    CBKswCtrlPnlTstVacOnF(&argWidget);
}

void CallbackWrapper::swCtrlPnlTstVacOff(EAppGUI_HPsIDs hpId)
{
    switch(hpId) {
    case APP_GUI_HP1_ID:argWidget.id = SwCtrlPnlTstVacHP1; break;
    case APP_GUI_HP2_ID:argWidget.id = SwCtrlPnlTstVacHP2; break;
    case APP_GUI_HP3_ID:argWidget.id = SwCtrlPnlTstVacHP3; break;
    case APP_GUI_HP4_ID:argWidget.id = SwCtrlPnlTstVacHP4; break;
    default: argWidget.id = APP_GUI_NUM_WIDGETS; break;
    }

    CBKswCtrlPnlTstVacOffF(&argWidget);
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

void CallbackWrapper::butHideCtrlPnl(EAppGUI_HPsIDs hpId)
{
    switch(hpId) {
    case APP_GUI_HP1_ID:argWidget.id = ButHideControlPanelHP1; break;
    case APP_GUI_HP2_ID:argWidget.id = ButHideControlPanelHP2; break;
    case APP_GUI_HP3_ID:argWidget.id = ButHideControlPanelHP3; break;
    case APP_GUI_HP4_ID:argWidget.id = ButHideControlPanelHP4; break;
    default: argWidget.id = APP_GUI_NUM_WIDGETS; break;
    }

    CBKbutHideCtrlPnlF(&argWidget);
}

void CallbackWrapper::butShowCtrlPnl(EAppGUI_HPsIDs hpId)
{
    switch(hpId) {
    case APP_GUI_HP1_ID:argWidget.id = ButShowControlPanelHP1; break;
    case APP_GUI_HP2_ID:argWidget.id = ButShowControlPanelHP2; break;
    case APP_GUI_HP3_ID:argWidget.id = ButShowControlPanelHP3; break;
    case APP_GUI_HP4_ID:argWidget.id = ButShowControlPanelHP4; break;
    default: argWidget.id = APP_GUI_NUM_WIDGETS; break;
    }

    CBKbutShowCtrlPnlF(&argWidget);
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

void CallbackWrapper::butPopUpTstVacManual(EAppGUIwidgetIDlist widgetId)
{
    argWidget.id = widgetId;
    CBKbutPopUpTstVacManualF(&argWidget);
}

void CallbackWrapper::butPopUpTstVacAuto()
{
    CBKbutPopUpTstVacAutoF(&argWidget);
}

void CallbackWrapper::butPopUpVacSmallLvl(EAppGUIwidgetIDlist widgetId)
{
    argWidget.id = widgetId;
    CBKbutPopUpVacSmallLvlF(&argWidget);
}

void CallbackWrapper::swPopUpTstVacLvlOn(EAppGUIwidgetIDlist widgetId)
{
    argWidget.id = widgetId;
    CBKswPopUpTstVacLvlOnF(&argWidget);
}

void CallbackWrapper::swPopUpTstVacLvlOff(EAppGUIwidgetIDlist widgetId)
{
    argWidget.id = widgetId;
    CBKswPopUpTstVacLvlOffF(&argWidget);
}

void CallbackWrapper::butPopUpErrOk(EAppGUIwidgetIDlist widgetId)
{
    argWidget.id = widgetId;
    CBKbutPopUpErrOkF(&argWidget);
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
    CBKbutSoftUpdateCfgF(&argWidget);
}

void CallbackWrapper::butRecargaCoolant()
{
    CBKbutRecargaCoolantF(&argWidget);
}

void CallbackWrapper::swResuctionsVierew()
{
    CBKswResuctionsVierewF(&argWidget);
}

void CallbackWrapper::swCfgTemperatureViewer()
{
    CBKswCfgTemperatureViewerF(&argWidget);
}

void CallbackWrapper::butCleanUpHP(EAppGUI_HPsIDs hpIndex)
{
    switch(hpIndex)
    {
    case APP_GUI_HP1_ID: argWidget.id = ButCfgCleanUpHP1; break;
    case APP_GUI_HP2_ID: argWidget.id = ButCfgCleanUpHP2; break;
    case APP_GUI_HP3_ID: argWidget.id = ButCfgCleanUpHP3; break;
    case APP_GUI_HP4_ID: argWidget.id = ButCfgCleanUpHP4; break;
    default: argWidget.id = APP_GUI_NUM_WIDGETS; break;
    }

    CBKbutCleanUpHPF(&argWidget);
}

void CallbackWrapper::butCleanUpHPround()
{
    CBKbutCleanUpHProundF(&argWidget);
}

void CallbackWrapper::swLanguage(EApp_GUI_differentLanguages languageId)
{
    switch(languageId)
    {
    case App_GUI_Frances: argWidget.id =    SwLanFrances; break;
    case App_GUI_Castellano: argWidget.id = SwLanCastellano; break;
    case App_GUI_Ingles: argWidget.id =     SwLanIngles; break;
    case App_GUI_Italiano: argWidget.id =   SwLanItaliano; break;
    case App_GUI_Aleman: argWidget.id =     SwLanAleman; break;
    case App_GUI_Polaco: argWidget.id =     SwLanPolaco; break;
    case App_GUI_Ruso: argWidget.id =       SwLanRuso; break;
    case App_GUI_Portugues: argWidget.id =  SwLanPortugues; break;
    case App_GUI_Chino: argWidget.id =      SwLanChino; break;
    case App_GUI_Japones: argWidget.id =    SwLanJapones; break;
    case App_GUI_Coreano: argWidget.id =    SwLanCoreano; break;
    default: argWidget.id = APP_GUI_NUM_WIDGETS; break;
    }

    CBKswLanguageF(&argWidget);
}

void CallbackWrapper::swCountry()
{
    argWidget.id = APP_GUI_NUM_WIDGETS;
    CBKswCountryF(&argWidget);
}

void CallbackWrapper::butPopUpCleanUp(EAppGUI_HPsIDs hpIndex)
{
    switch(hpIndex)
    {
    case APP_GUI_HP1_ID: argWidget.id = ButPopUpCleanHP1; break;
    case APP_GUI_HP2_ID: argWidget.id = ButPopUpCleanHP2; break;
    case APP_GUI_HP3_ID: argWidget.id = ButPopUpCleanHP3; break;
    case APP_GUI_HP4_ID: argWidget.id = ButPopUpCleanHP4; break;
    default: argWidget.id = APP_GUI_NUM_WIDGETS; break;
    }

    CBKbutPopUpCleanUpF(&argWidget);
}

void CallbackWrapper::butPopUpCleanUpYES(EAppGUI_HPsIDs hpIndex)
{
    switch(hpIndex)
    {
    case APP_GUI_HP1_ID: argWidget.id = ButPopUpCleanYESHP1; break;
    case APP_GUI_HP2_ID: argWidget.id = ButPopUpCleanYESHP2; break;
    case APP_GUI_HP3_ID: argWidget.id = ButPopUpCleanYESHP3; break;
    case APP_GUI_HP4_ID: argWidget.id = ButPopUpCleanYESHP4; break;
    default: argWidget.id = APP_GUI_NUM_WIDGETS; break;
    }

    CBKbutPopUpCleanUpYESF(&argWidget);
}

void CallbackWrapper::butPopUpCleanUpNO(EAppGUI_HPsIDs hpIndex)
{
    switch(hpIndex)
    {
    case APP_GUI_HP1_ID: argWidget.id = ButPopUpCleanNOHP1; break;
    case APP_GUI_HP2_ID: argWidget.id = ButPopUpCleanNOHP2; break;
    case APP_GUI_HP3_ID: argWidget.id = ButPopUpCleanNOHP3; break;
    case APP_GUI_HP4_ID: argWidget.id = ButPopUpCleanNOHP4; break;
    default: argWidget.id = APP_GUI_NUM_WIDGETS; break;
    }

    CBKbutPopUpCleanUpNOF(&argWidget);
}

void CallbackWrapper::butPopUpCleanUpCancel(EAppGUI_HPsIDs hpIndex)
{
    switch(hpIndex)
    {
    case APP_GUI_HP1_ID: argWidget.id = ButPopUpCleanCancelHP1; break;
    case APP_GUI_HP2_ID: argWidget.id = ButPopUpCleanCancelHP2; break;
    case APP_GUI_HP3_ID: argWidget.id = ButPopUpCleanCancelHP3; break;
    case APP_GUI_HP4_ID: argWidget.id = ButPopUpCleanCancelHP4; break;
    default: argWidget.id = APP_GUI_NUM_WIDGETS; break;
    }

    CBKbutPopUpCleanUpCancelF(&argWidget);
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
