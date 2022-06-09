/*
 * cbk.h
 *
 *  Created on: Jul 7, 2016
 *      Author: ingenieria9
 */

#ifndef CBK_H_
#define CBK_H_

//#include "PE_Types.h"
//#include "../GeneralDefines.h"

/* Listado de callbacks */
//enum
//{
//	CBKdummy,
//	CBKbutGenderSelect,
//	CBKbutMainMenuShow,
//	CBKbutMainMenuHide,
//	CBKbutHome,
//	CBKbutConfig,
//	CBKbutCalc,
//	CBKbutData,
//	CBKbutWarningOn,
//	CBKbutWarningOff,
//	CBKbutCtrlPnlPlay,
//	CBKswCtrlPnlTstVacOn,
//	CBKswCtrlPnlTstVacOff,
//	CBKbutSelectTime,
//	CBKbutTemperatureVwr,
//	CBKbutTRTmodeAutoManual,
//	CBKbutInfoZoneSelectedOn,
//	CBKbutInfoZoneSelectedOff,
//	CBKbutModelImage,
//	CBKbutHideCtrlPnl,
//	CBKbutShowCtrlPnl,
//	CBKbutFullBodyArea,
//	CBKswDotZoneOn,
//	CBKswDotZoneOff,
//	//CBKbutPopUpOK,
//	CBKbutPopUpReturn,
//	CBKbutReuseRFIDlabel,
//	CBKbutPopUpTimeValue,
//	CBKbutPopUpTstVacManual,
//	CBKbutPopUpTstVacAuto,
//	CBKbutPopUpVacSmallLvl,
//	CBKswPopUpTstVacLvlOn,
//	CBKswPopUpTstVacLvlOff,
//	CBKbutPopUpErrOk,
//	CBKbutPopUpCleanUp,
//	CBKbutPopUpCleanUpYES,
//	CBKbutPopUpCleanUpNO,
//	CBKbutPopUpCleanUpCancel,
//	//Calculadora
//	CBKbutNumCalc,
//	CBKbutEnterCalc,
//	CBKbutCECalc,
//	//Configuracion
//	CBKbutSoftUpdateCfg,
//	CBKbutRecargaCoolant,
//	CBKswResuctionsVierew,
//	CBKswCfgTemperatureViewer,
//	CBKbutCleanUpHP,
//	CBKbutCleanUpHPround,
//	//Idiomas
//	CBKswLanguage,
//	CBKswCountry,
//	//SAT
//	CBKbutSATnextPage,
//	CBKbutSATprevPage,
//	CBKswSATVacOn,
//	CBKswSATVacOff,
//	CBKswSATFrioOn,
//	CBKswSATFrioOff,
//	CBKswSATrfidOn,
//	CBKswSATrfidOff,
//	CBKswSATtestLedOn,
//	CBKswSATtestLedOff,
//	CBKswSATtestLedRGBOn,
//	CBKswSATtestLedRGBOff,
//	CBKbutOkSATerr,
	
//	CBKswFATIGUEfailBelloff,

//};

//Función con el switch case de todos los callbacks
//void *cbkIndex( uint32 cbk);

void CBKdummyF( void *widget);
void CBKbutGenderSelectF( void *widget);
void CBKbutMainMenuShowF();
void CBKbutMainMenuHideF();
void CBKbutHomeF( void *widget);
void CBKbutConfigF( void *widget);
void CBKbutCalcF( void *widget);
void CBKbutDataF( void *widget);
void CBKbutWarningOnF ( void *widget);
void CBKbutWarningOffF ( void *widget);
void CBKbutCtrlPnlPlayF( void *widget);
void CBKswCtrlPnlTstVacOnF( void *widget);
void CBKswCtrlPnlTstVacOffF( void *widget);
void CBKbutSelectTimeF( void *widget);
void CBKbutTemperatureVwrF ( void *widget);
void CBKbutTRTmodeAutoManualF ( void *widget);
void CBKbutInfoZoneSelectedOnF ();
void CBKbutInfoZoneSelectedOffF ();
void CBKbutModelImageF( void *widget);
void CBKbutHideCtrlPnlF( void *widget);
void CBKbutShowCtrlPnlF( void *widget);
void CBKbutFullBodyAreaF( void *widget);
void CBKswDotZoneOnF( void *widget);
void CBKswDotZoneOffF( void *widget);
//void CBKbutPopUpOKF( void *widget);
void CBKpopUpDisplayedF( void *widget, bool visible );
void CBKbutPopUpReturnF();
void CBKbutReuseRFIDlabelF ( void *widget);
void CBKbutPopUpTimeValueF( void *widget);
void CBKbutPopUpTstVacManualF( void *widget);
void CBKbutPopUpTstVacAutoF( void *widget);
void CBKbutPopUpVacSmallLvlF( void *widget);
void CBKswPopUpTstVacLvlOnF( void *widget);
void CBKswPopUpTstVacLvlOffF( void *widget);
void CBKbutPopUpErrOkF( void *widget);
void CBKbutNumCalcF( void *widget);
void CBKbutEnterCalcF( void *widget);
void CBKbutCECalcF( void *widget);
void CBKbutSoftUpdateCfgF ( void *widget);
void CBKbutRecargaCoolantF ( void *widget);
void CBKswResuctionsVierewF ( void *widget);
void CBKswCfgTemperatureViewerF ( void *widget);
void CBKbutCleanUpHPF ( void *widget);
void CBKbutCleanUpHProundF ( void *widget);
void CBKswLanguageF ( void *widget);
void CBKswCountryF ( void *widget);
void CBKbutPopUpCleanUpF ( void *widget);
void CBKbutPopUpCleanUpYESF ( void *widget);
void CBKbutPopUpCleanUpNOF ( void *widget);
void CBKbutPopUpCleanUpCancelF ( void *widget);
void CBKbutSATnextPageF ( void *widget);
void CBKbutSATprevPageF ( void *widget);
void CBKswSATVacOnF ( void *widget);
void CBKswSATVacOffF ( void *widget);
void CBKswSATFrioOnF ( void *widget);
void CBKswSATFrioOffF ( void *widget);
void CBKswSATrfidOnF ( void *widget);
void CBKswSATrfidOffF ( void *widget);
void CBKswSATtestLedOnF ( void *widget);
void CBKswSATtestLedOffF ( void *widget);
void CBKswSATtestLedRGBOnF ( void *widget);
void CBKswSATtestLedRGBOffF ( void *widget);
void CBKswFATIGUEfailBelloffF ( void *widget);
void CBKbutOkSATerrF ( void *widget);


#endif /* CBK_H_ */
