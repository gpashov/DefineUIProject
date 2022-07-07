#ifndef CALLBACKWRAPPER_H
#define CALLBACKWRAPPER_H

#include <QObject>
#include "../AppGUI/AppGuiInterfaceStructure.h"

class CallbackWrapper : public QObject
{
    Q_OBJECT
public:
    explicit CallbackWrapper(QObject *parent = nullptr);

    Q_INVOKABLE void dummy();
    Q_INVOKABLE void butGenderSelect(EAppGUIbodys gender);
    Q_INVOKABLE void butMainMenuShow();
    Q_INVOKABLE void butMainMenuHide();
    Q_INVOKABLE void butHome();
    Q_INVOKABLE void butConfig();
    Q_INVOKABLE void butCalc();
    Q_INVOKABLE void butData();
    Q_INVOKABLE void butWarningOn ();
    Q_INVOKABLE void butWarningOff ();
    Q_INVOKABLE void butCtrlPnlPlay(EAppGUI_HPsIDs hpId);
    Q_INVOKABLE void swCtrlPnlTstVacOn(EAppGUI_HPsIDs hpId);
    Q_INVOKABLE void swCtrlPnlTstVacOff(EAppGUI_HPsIDs hpId);
    Q_INVOKABLE void butSelectTime(EAppGUI_HPsIDs hpId);
    Q_INVOKABLE void butTemperatureVwr (EAppGUI_HPsIDs hpId);
    Q_INVOKABLE void butTRTmodeAutoManual ();
    Q_INVOKABLE void butInfoZoneSelectedOn ();
    Q_INVOKABLE void butInfoZoneSelectedOff ();
    Q_INVOKABLE void butModelImage(EAppGUI_HPsIDs hpId);
    Q_INVOKABLE void butHideCtrlPnl(EAppGUI_HPsIDs hpId);
    Q_INVOKABLE void butShowCtrlPnl(EAppGUI_HPsIDs hpId);
    Q_INVOKABLE void butFullBodyArea(EAppGUIfullBodyAreas bodyArea);
    Q_INVOKABLE void swDotZoneOn(EAppGUIwidgetIDlist widgetId);
    Q_INVOKABLE void swDotZoneOff(EAppGUIwidgetIDlist widgetId);
    //Q_INVOKABLE void CBKbutPopUpOK();
    Q_INVOKABLE void popupVisibleChanged( EAppGUIwidgetIDlist widgetId, bool visible );
    Q_INVOKABLE void butPopUpReturn();
    Q_INVOKABLE void butReuseRFIDlabel ();
    Q_INVOKABLE void butPopUpTimeValue(EAppGUI_HPsIDs hpId, EAppGUIwidgetIDlist buttonId);
    Q_INVOKABLE void butPopUpTstVacManual(EAppGUIwidgetIDlist widgetId);
    Q_INVOKABLE void butPopUpTstVacAuto();
    Q_INVOKABLE void butPopUpVacSmallLvl(EAppGUIwidgetIDlist widgetId);
    Q_INVOKABLE void swPopUpTstVacLvlOn(EAppGUIwidgetIDlist widgetId);
    Q_INVOKABLE void swPopUpTstVacLvlOff(EAppGUIwidgetIDlist widgetId);
    Q_INVOKABLE void butPopUpErrOk(EAppGUIwidgetIDlist widgetId);
    Q_INVOKABLE void buttonNumCalc(uint8 calcNumber);
    Q_INVOKABLE void buttonEnterCalc();
    Q_INVOKABLE void buttonCECalc();
    Q_INVOKABLE void butSoftUpdateCfg ();
    Q_INVOKABLE void butRecargaCoolant ();
    Q_INVOKABLE void swResuctionsVierew ();
    Q_INVOKABLE void swCfgTemperatureViewer ();
    Q_INVOKABLE void butCleanUpHP ();
    Q_INVOKABLE void butCleanUpHPround ();
    Q_INVOKABLE void swLanguage ();
    Q_INVOKABLE void swCountry ();
    Q_INVOKABLE void butPopUpCleanUp ();
    Q_INVOKABLE void butPopUpCleanUpYES ();
    Q_INVOKABLE void butPopUpCleanUpNO ();
    Q_INVOKABLE void butPopUpCleanUpCancel ();
    Q_INVOKABLE void butSATnextPage ();
    Q_INVOKABLE void butSATprevPage ();
    Q_INVOKABLE void swSATVacOn ();
    Q_INVOKABLE void swSATVacOff ();
    Q_INVOKABLE void swSATFrioOn ();
    Q_INVOKABLE void swSATFrioOff ();
    Q_INVOKABLE void swSATrfidOn ();
    Q_INVOKABLE void swSATrfidOff ();
    Q_INVOKABLE void swSATtestLedOn ();
    Q_INVOKABLE void swSATtestLedOff ();
    Q_INVOKABLE void swSATtestLedRGBOn ();
    Q_INVOKABLE void swSATtestLedRGBOff ();
    Q_INVOKABLE void swFATIGUEfailBelloff ();
    Q_INVOKABLE void butOkSATerr ();
    Q_INVOKABLE void loadAnimationEnd();

signals:

};

#endif // CALLBACKWRAPPER_H
