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

}

void CallbackWrapper::butWarningOff()
{

}

void CallbackWrapper::butCtrlPnlPlay()
{

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

void CallbackWrapper::butTemperatureVwr()
{

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

void CallbackWrapper::butModelImage()
{

}

void CallbackWrapper::butHideCtrlPnl()
{

}

void CallbackWrapper::butShowCtrlPnl()
{

}

void CallbackWrapper::butFullBodyArea()
{

}

void CallbackWrapper::swDotZoneOn()
{

}

void CallbackWrapper::swDotZoneOff()
{

}

void CallbackWrapper::popUpVisibleChanged( EAppGUIwidgetIDlist widgetId, bool visible )
{
    argWidget.id = widgetId;
    CBKpopUpDisplayedF( &argWidget, visible );
}

void CallbackWrapper::butPopUpReturn()
{

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
