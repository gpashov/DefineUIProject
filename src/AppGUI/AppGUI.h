/*
 * pantalla.h
 *
 *  Created on: Nov 24, 2016
 *      Author: ingenieria9
 */

#ifndef APPGUI_H_
#define APPGUI_H_

#include "GeneralDefines.h"
#include "Perifericos/HPcryo.h"
#include "Perifericos/Perifericos.h"
#include "AppGuiInterfaceStructure.h"
//#include "../RTC/RTC.h"
//#include "../BOOT/boot.h"
//#include "../GUI/K70_GUI.h"
//#include "../GUI/NumberViewer/numV.h"

/*	-	Constantes	-	*/
#define APP_GUI_BOTTOM_REF			0		//Variable que indica si el fondo de pantalla se realizará con una imagen o un color solido
#define APP_GUI_BOTTOM_COLOR_REF	0		//Color solido de fondo de pantalla
#define APP_GUI_BRIGHT_INIT			0 		//Nivel de brillo de la pantalla al iniciarse
#define APP_GUI_IMG_COMPRESION_CCN	1 		//Tipo de compresión de las imagenes

#define APP_GUI_LOAD_TIME			500		//Tiempo que tarda en aparecer cada icono de carga

#define APP_GUI_PRESS_BUTTON		1
#define APP_GUI_RLS_BUTTON			0
#define APP_GUI_WIDGET_VISIBLE		1		//Parametro para poner visible un widget
#define APP_GUI_WIDGET_NOT_VISIBLE	0		//Parametro para poner no visible un widget
#define APP_GUI_WIDGET_ENABLE		1		//Parametro para activar un widget
#define APP_GUI_WIDGET_DISABLE		0		//Parametro para desactivar un widget

#define APP_GUI_INDICATORTIME_REF	1000	//Tiempo de parpadeo de los indicadores

#define APP_GUI_30SEC_MILISEC		30000
#define APP_GUI_1SEC_MILISEC		1000

#define APP_GUI_MAX_DIGIT_VWR		2	   	//Número de digitos a representar en el temporizador (4 número y los dos puntos)

#define APP_GUI_MAX_TIME_BLINK_LOAD_HP			700		//Tiempo que transcurre entre imagenes al ir configurandose un manipulo conectado
#define APP_GUI_MAX_TIME_BLINK_HP_CTRL_PANEL	1500

#define APP_GUI_RFID_POPUP_ANIMATION_LOAD_IMGS	3
#define APP_GUI_RFID_POPUP_ANIMATION_LOAD_TIME	200

#define APP_GUI_SAT_SCREEN_NUMVWR_MAX_PAGES		0.9

#define APP_GUI_FATIGUE_5_SEC_MILISEC		5000

/*  -  Constantes  -  */

/*	-	Estructuras	-	*/
typedef struct
{
	uint8 Flag_Wng_Nivel_Agua_Bajo;
	uint8 Flag_Wng_Nivel_Agua_Medio;
	uint8 Flag_Wng_Temp_Amb;
	uint8 Flag_Wng_RFID;
	uint8 Flag_Wng_RTC;
	uint8 Flag_Wng_Filtro_Aire;
	
}tAppGUI_WarningHandler;

typedef struct
{
	uint8 HP_in_cleaning;
	uint8 HP_clean_init_or_end;
	float Timer_count;
	cAppGUIcleanUpStatus status;
}tAppGUI_CleanUPhdlr;

typedef struct
{
	cAppGUIfullBodyAreas selTrtArea;
	uint8 selTrtDot;
	
	cHPcryoTrtTimes selTime;
	cHPcryoTrtVacLvls selVacLvl;
	
	uint8 numResucciones;
	uint32 timeRefResuccionesBlink;
	
	uint8 testedVacLvls[HP_CRYO_VAC_LVL_NUM];
	uint8 isCtrlPnlShow;
	
	uint32 tmrBlink;
	uint8 statusFlagsOnOff[APP_GUI_MAX_BLINK_INDICATORS];
	float trtTime;
	uint8 isTrtDone;
	cHPcryoTrtModes TrtMode;
	cHPcryoTstVaccAutoStates TstVacuumModeScss;
	uint8 showAutoKO;
	uint8 showVacumRetryRqstUsrToMoveHP;
	uint8 alarmVacumRetryRqstUsrToMoveHP;
	
	uint8 ErrorBeep;
	uint8 VwrTemperatureOrTime;
	float TempHP;
	
	tAppGUI_CleanUPhdlr CleanUPhdlr;
}tAppGUIslot;

typedef struct
{
	cAppGUIbodys body;
	cAppGUIfullBodyAreas selTrtArea;
	uint8 selTrtDot;
	cHPcryoTrtTimes timeGroupZones[MaxGrupoZonas];
}tAppGUItrtZoneHandler;

typedef struct
{
	uint32 Tst_vac_but;
	cHPcryoTrtVacLvls selVacLvl;	
	uint8 HPindex;
	uint8 waitingUserStart;
	uint8 waitingUserEnd;
}tAppGUItestVacHandler;

typedef struct
{
	uint8 HPindex;
	cHPcryoTrtTimes selTime;
}tAppGUItimeHandler;

typedef struct
{
	uint8 HPindex;
	uint8 ReadingLabelFlag;
	uint8 animLoadImg;
	uint8 show_reuse_option;
}tAppGUI_RFIDhdlr;

typedef struct
{
	uint8 isUp;
}tAppGUImainMenuHdlr;

typedef struct
{
	float CalcCode;
	uint8 numDigitsIn;
	
	uint8 RTC_time_flag;
	uint8 RTC_date_flag;
	
	uint8 MachineModeChngFlag;		//V7790
	//uint8 FlagSkipLangSelection;	//V7790
	
	uint8 FillingWater_flag;
}tAppGUI_CalcHandler;

typedef struct
{
	uint8 BOOT_rqst;
	uint32 Boot_animation_tout;
	uint8 BootAnimationImg;
	uint8 FillingWater_flag;
}tAppGUI_CfgHandler;

typedef struct
{
	cAppGUI_SATscreen_Pages Page;
	float PageNum;
	uint8 VacuumSwitch[APP_GUI_MAXNUM_HP];
	uint8 TestLedRGBSwitch[APP_GUI_MAXNUM_HP];
	uint8 FrioSwitch[APP_GUI_MAXNUM_HP];
	uint8 TestLedSwitch[APP_GUI_MAXNUM_HP];
	uint8 RFIDSwitch;
	uint8 RFID_FWversion;

}tAppGUI_SATHandler;


typedef struct
{
	tAppGUI_WarningHandler AppGUI_WarningHandler;
	tAppGUImainMenuHdlr mainMenuHdlr;
	tAppGUI_RFIDhdlr RFIDhdlr;
	tAppGUItimeHandler timeHdlr;
	tAppGUItestVacHandler tstVacHdlr;
	tAppGUItrtZoneHandler trtZoneHdlr;
	tAppGUIslot slot[APP_GUI_MAXNUM_HP];
	cAppGUIscreen screen;
	tAppGUI_CalcHandler CalcHandler;
	tAppGUI_CfgHandler CfgHandler;
	uint8 MachineErrorBeep;
	uint8 EndTRTbeep;
	uint32 EndTRTbeepTout;
	tAppGUI_SATHandler SATHandler;
	uint8 fatigue_fail;
	uint8 WiFiMac[6];
}tAppGUIdata;

extern tAppGUIdata AppGUIdata;

///* - Funciones publicas */
void AppGUIinit();
void AppGUIinit_reconfig (void);
void AppGUIfinish();
void AppGUIchangeScreen( cAppGUIscreen screen);
void AppGUIupdate(void);
uint8 AppGUIisInitRunning( uint8 HPindex);
void AppGUIapplyTimeRestriction( uint8 HPindex, tHPcryoData *HP, tPRFdata *PRF);
uint8 AppGUIisHPaDoubleDummy( tHPcryoData *HP, tPRFdata *PRF);
void AppGUIbuttonManagement (cAppGUIctrMenuBut button, uint8 butt_states, uint8 HPindex);
void AppGUIconnectingHP (uint8 HPindex, uint32 *imgPrsID, uint32 *imgRlsID, uint32 *imgModelText);

/* - Funciones Publicas para los CBK's */
void AppGUIhandleCtrlPanel( uint8 show, uint8 HPindex);
void AppGUIhandleTrtZone( void);
void AppGUIhandleTimePopUp( uint8 show, uint8 HPindex);
void AppGUIhandleTstVacPopUp( uint8 show, uint8 HPindex);
void AppGUIhandleTstVacSMALLPopUp( uint8 show, uint8 HPindex);
void AppGUIhandleRFIDpopUp( uint8 show, uint8 HPindex);
void AppGUI_RFIDpopup_ReuseOption (uint8 option);
uint8 AppGUIIsPopupDisplayed( const cAppGUIwidgetIDlist widgetId );
void AppGUIhandleMainMenu( uint8 show );
void AppGUIclearData( void);
void AppGUIclearSlotData( uint8 HPindex);
void AppGUIhandleErrPopUps( void);
void AppGUIhandleCleanUpPopUps( uint8 show, uint8 HPindex);
void AppGUIhandleMaqCleanPopUps( void);
uint8 AppGUIisTrtRunning( uint8 HPindex, cHPcryoTreatmentStatus *status);
uint8 AppGUIisTstVacRunning( uint8 HPindex, cHPcryoTestVacumStatus *status);
uint8 AppGUIisHPconnected( uint8 HPindex, cHPcryoModels *model);
uint8 AppGUIopenTimePopupPermission( uint8 HPindex, tHPcryoData *HP, tPRFdata *PRF);
float AppGUIcalcTrtTime( uint8 HPindex, uint32 trtElapsedTime_s, uint32 totalTrtTime_s);
void AppGUIhandleRecommendationpopUp( uint8 show, uint8 selTrtDot, cAppGUIfullBodyAreas selTrtArea);
void AppGUIhandleWarningPopUp( uint8 show);
void AppGUIwarningNotification (void);
void AppGUIchangeMenuVwrTemperatureOrTime ( uint8 HPindex);
void AppGUIsetWiFiMAC (uint8 *ptuMAC);
void AppGUI_GPRScoverage( uint8 show, cAppGUIscreen screen);	//V7790

#endif 
