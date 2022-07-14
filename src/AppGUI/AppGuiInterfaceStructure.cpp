/*
 * AppGuiInterfaceStructure.c
 *
 *  Created on: Mar 25, 2019
 *      Author: ingenieria9
 */

/*Includes*/
#include "../Callback/cbk.h"
#include "../Perifericos/HPcryo.h"
#include "AppGuiInterfaceStructure.h"

/*** COMUN EN LAS PANTALLAS ***/
///* Vectores con los widgets a mostrar y habilitar cuando el menu principal esta oculto o visible */
//const uint32 APP_GUI_MAIN_MENU_WID_WHEN_SHOW[APP_GUI_NUM_SCREENS][APP_GUI_MAIN_MENU_WID_WHEN_SHOW_NUM] =
//{
//	{ APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS},	//Pantalla carga
//	{ butInitScrHideMainMenu, imgInitScrHome, butInitScrCfg, butInitScrCalc, butInitScrData, SwInitScrAvisos},							//Pantalla inicio
//	{ butTrtScrHideMainMenu, ButTrtScrHome, ButTrtScrCfg, ButTrtScrCalc, butTrtScrData, SwTrtScrAvisos},								//Pantalla tratamiento
//	{ butCalcScrHideMainMenu, butCalcScrHome, butCalcScrCfg, imgCalcScrCalc, butCalcScrData, SwCalcScrAvisos},							//Pantalla calculadora
//	{ butCfgScrHideMainMenu, butCfgScrHome, imgCfgScrCfg, butCfgScrCalc, butCfgScrData, SwCfgScrAvisos},								//Pantalla configuracion
//	{ butLanScrHideMainMenu, butLanScrHome, butLanScrCfg, butLanScrCalc, imgLanScrData, SwLanScrAvisos},								//Pantalla idiomas
//	{ APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS},	//Pantalla SAT
//	{ APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS}		//Pantalla FATIGA
//};

//const uint32 APP_GUI_MAIN_MENU_WID_WHEN_HIDE[APP_GUI_NUM_SCREENS][APP_GUI_MAIN_MENU_WID_WHEN_HIDE_NUM] =
//{
//	{ APP_GUI_NUM_WIDGETS},				//Pantalla carga
//	{ butInitScrShowMainMenu},			//Pantalla inicio
//	{ butTrtScrShowMainMenu},			//Pantalla tratamiento
//	{ butCalcScrShowMainMenu},			//Pantalla calculadora
//	{ butCfgScrShowMainMenu},			//Pantalla configuracion
//	{ butLanScrShowMainMenu},			//Pantalla idiomas
//	{ APP_GUI_NUM_WIDGETS},				//Pantalla SAT
//	{ APP_GUI_NUM_WIDGETS}				//Pantalla FATIGA
//};

///*** PANTALLA DE CARGA ***/
///* Vector con las imagenes de la animación de la pantalla LOAD */
//const uint32 APP_GUI_LOAD_SCR_ANIM_IMG_LIST[APP_GUI_LOAD_SCR_ANIM_IMG_NUM] =
//{
//		ImgLoadAnim1, imgLoadAnim2, imgLoadAnim3, imgLoadAnim4,
//		imgLoadAnim5, imgLoadAnim6, imgLoadAnim7, imgLoadAnim8
//};

///*** PANTALLA DE INICIO ***/

///*** PANTALLA DE CONFIGURACION ***/

//const uint32 APP_GUI_CFG_SCR_LOADING_NEW_FW_ANIMATION [App_GUI_CfgScr_FW_loading_max] =
//{
//		c318_Configuracionloading0_Z, c318_Configuracionloading20_Z, c319_Configuracionloading40_Z, c320_Configuracionloading60_Z, c321_Configuracionloading80_Z, c322_Configuracionloading100_Z
//};

/*** PANTALLA DE TRATAMIENTO ***/
/* Distribución de slots en pantalla */
const uint8 APP_GUI_SLOT_DISTRIBUTION[APP_GUI_MAXNUM_HP] =
{
    PRF_HW_SLOT1,
    PRF_HW_SLOT3,
    PRF_HW_SLOT2,
    PRF_HW_SLOT4
};

///* Tabla con los ID's de las imagenes de los HP orientados a derecha e izquierda segun
// * el slot */
const uint32 APP_GUI_TRT_SCR_BUT_MODEL_IMG_SIDE_FROM_SLOT_IMG[APP_GUI_MAX_PRS_RLS][APP_GUI_MAXNUM_HP][HP_CRYO_NUM_HP_MODELS] =
{
    //Press
    {
        //Undefined, Curved, Tight, Straight, Tiny, Tiny Curved, Double, Oval, Oval Curved, Angled
        { C233_ImgPixelBlanco, C093_ImgCurvedHP_R_Press, C095_ImgTightHP_R_Press, C097_ImgStrightHP_R_Press, C099_ImgTinyHP_R_Press, C101_ImgTinyCurvedHP_R_Press, C103_ImgDoubleHP_R_Press, C105_ImgOvalHP_R_Press, C107_ImgOvalCurvedHP_R_Press, C109_ImgAngledHP_R_Press},
        { C233_ImgPixelBlanco, C094_ImgCurvedHP_L_Press, C096_ImgTightHP_L_Press, C098_ImgStrightHP_L_Press, C100_ImgTinyHP_L_Press, C102_ImgTinyCurvedHP_L_Press, C104_ImgDoubleHP_L_Press, C106_ImgOvalHP_L_Press, C108_ImgOvalCurvedHP_L_Press, C110_ImgAngledHP_L_Press},
        { C233_ImgPixelBlanco, C093_ImgCurvedHP_R_Press, C095_ImgTightHP_R_Press, C097_ImgStrightHP_R_Press, C099_ImgTinyHP_R_Press, C101_ImgTinyCurvedHP_R_Press, C103_ImgDoubleHP_R_Press, C105_ImgOvalHP_R_Press, C107_ImgOvalCurvedHP_R_Press, C109_ImgAngledHP_R_Press},
        { C233_ImgPixelBlanco, C094_ImgCurvedHP_L_Press, C096_ImgTightHP_L_Press, C098_ImgStrightHP_L_Press, C100_ImgTinyHP_L_Press, C102_ImgTinyCurvedHP_L_Press, C104_ImgDoubleHP_L_Press, C106_ImgOvalHP_L_Press, C108_ImgOvalCurvedHP_L_Press, C110_ImgAngledHP_L_Press}
    },
	
    //Release
    {
        //Undefined, Curved, Tight, Straight, Tiny, Tiny Curved, Double, Oval, Oval Curved, Angled
        { C233_ImgPixelBlanco, C075_ImgCurvedHP_R_Rls, C077_ImgTightHP_R_Rls, C079_ImgStrightHP_R_Rls, C081_ImgTinyHP_R_Rls, C083_ImgTinyCurvedHP_R_Rls, C085_ImgDoubleHP_R_Rls, C087_ImgOvalHP_R_Rls, C089_ImgOvalCurvedHP_R_Rls, C091_ImgAngledHP_R_Rls},
        { C233_ImgPixelBlanco, C076_ImgCurvedHP_L_Rls, C078_ImgTightHP_L_Rls, C080_ImgStrightHP_L_Rls, C082_ImgTinyHP_L_Rls, C084_ImgTinyCurvedHP_L_Rls, C086_ImgDoubleHP_L_Rls, C088_ImgOvalHP_L_Rls, C090_ImgOvalCurvedHP_L_Rls, C092_ImgAngledHP_L_Rls},
        { C233_ImgPixelBlanco, C075_ImgCurvedHP_R_Rls, C077_ImgTightHP_R_Rls, C079_ImgStrightHP_R_Rls, C081_ImgTinyHP_R_Rls, C083_ImgTinyCurvedHP_R_Rls, C085_ImgDoubleHP_R_Rls, C087_ImgOvalHP_R_Rls, C089_ImgOvalCurvedHP_R_Rls, C091_ImgAngledHP_R_Rls},
        { C233_ImgPixelBlanco, C076_ImgCurvedHP_L_Rls, C078_ImgTightHP_L_Rls, C080_ImgStrightHP_L_Rls, C082_ImgTinyHP_L_Rls, C084_ImgTinyCurvedHP_L_Rls, C086_ImgDoubleHP_L_Rls, C088_ImgOvalHP_L_Rls, C090_ImgOvalCurvedHP_L_Rls, C092_ImgAngledHP_L_Rls}
    }
};

const uint32 APP_GUI_TRT_LIST_OF_IMG_HP_RECOMMENDED_PER_ZONE[HP_CRYO_NUM_HP_MODELS] =
 {
         APP_GUI_NUM_WIDGETS, ImgPopUpRecommCurved, ImgPopUpRecommTight, ImgPopUpRecommStright, ImgPopUpRecommTiny, ImgPopUpRecommTinyCurved, ImgPopUpRecommDouble, ImgPopUpRecommOval, ImgPopUpRecommOvalCurved, ImgPopUpRecommAngled
 };

/* Tabla con las imagenes de los slots para los botones de HP del panel de control cuando no hay HP conectado */
const uint32 APP_GUI_TRT_SCR_BUT_MODE_IMG_NO_HP_IMG[APP_GUI_MAXNUM_HP] =
{
        C112_1_ZonaSeleccionadaHP1, C112_2_ZonaSeleccionadaHP2, C112_3_ZonaSeleccionadaHP3, C112_4_ZonaSeleccionadaHP4
};

const uint32 APP_GUI_TRT_SCR_BUT_MODEL_IMG_WIDGETS[APP_GUI_MAXNUM_HP] =
{
        ButModelImageHP1, ButModelImageHP2, ButModelImageHP3, ButModelImageHP4
};

const uint32 APP_GUI_TRT_SCR_BUT_MODE_TRT_WIDGETS[APP_GUI_MAXNUM_HP] =
{
        ButSwtchModeAutoManualHP1, ButSwtchModeAutoManualHP2, ButSwtchModeAutoManualHP3, ButSwtchModeAutoManualHP4
};

///* Listado de widgets que componen el panel de control cuando esta mostrado y cuando esta oculto */
//const uint32 APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_SHOW[APP_GUI_MAXNUM_HP][APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_SHOW_NUM] =
//{
//	{ imgCtrlPnlBckGndHP1, ImgCtrlPnlRFIDblinkHP1, ImgCtrlPnlPulBlinkHP1, ImgCtrlPnlVacBlinkHP1, ImgCtrlPnlCoolingBlinkHP1,
//	  ButCtrlPnlPlayHP1, SwCtrlPnlTstVacHP1, ButSwtchModeAutoManualHP1, NumVwrTimeHP1, ButSelectTimeHP1,
//	  ImgModelTextHP1, ButModelImageHP1, ButHideControlPanelHP1, ImgColourCtrlPnlBckGndHP1, NumVwrResucctionCountHP1},	//HP1
//	{ imgCtrlPnlBckGndHP2, ImgCtrlPnlRFIDblinkHP2, ImgCtrlPnlPulBlinkHP2, ImgCtrlPnlVacBlinkHP2, ImgCtrlPnlCoolingBlinkHP2,
//	  ButCtrlPnlPlayHP2, SwCtrlPnlTstVacHP2, ButSwtchModeAutoManualHP2, NumVwrTimeHP2, ButSelectTimeHP2,
//	  ImgModelTextHP2, ButModelImageHP2, ButHideControlPanelHP2, ImgColourCtrlPnlBckGndHP2, NumVwrResucctionCountHP2},	//HP2
//	{ imgCtrlPnlBckGndHP3, ImgCtrlPnlRFIDblinkHP3, ImgCtrlPnlPulBlinkHP3, ImgCtrlPnlVacBlinkHP3, ImgCtrlPnlCoolingBlinkHP3,
//	  ButCtrlPnlPlayHP3, SwCtrlPnlTstVacHP3, ButSwtchModeAutoManualHP3, NumVwrTimeHP3, ButSelectTimeHP3,
//	  ImgModelTextHP3, ButModelImageHP3, ButHideControlPanelHP3, ImgColourCtrlPnlBckGndHP3, NumVwrResucctionCountHP3},	//HP3
//	{ imgCtrlPnlBckGndHP4, ImgCtrlPnlRFIDblinkHP4, ImgCtrlPnlPulBlinkHP4, ImgCtrlPnlVacBlinkHP4, ImgCtrlPnlCoolingBlinkHP4,
//	  ButCtrlPnlPlayHP4, SwCtrlPnlTstVacHP4, ButSwtchModeAutoManualHP4, NumVwrTimeHP4, ButSelectTimeHP4,
//	  ImgModelTextHP4, ButModelImageHP4, ButHideControlPanelHP4, ImgColourCtrlPnlBckGndHP4, NumVwrResucctionCountHP4}	//HP4
//};

//const uint32 APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_HIDE[APP_GUI_MAXNUM_HP][APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_HIDE_NUM] =
//{
//	{ butShowControlPanelHP1},	//HP1
//	{ butShowControlPanelHP2},	//HP2
//	{ butShowControlPanelHP3},	//HP3
//	{ butShowControlPanelHP4}	//HP4
//};

const uint32 APP_GUI_TRT_SCR_CTRL_PNL_COLOUR_WIDGETS [APP_GUI_MAXNUM_HP] =
{
     ImgColourCtrlPnlBckGndHP1, ImgColourCtrlPnlBckGndHP2, ImgColourCtrlPnlBckGndHP3, ImgColourCtrlPnlBckGndHP4
};

//const uint32 APP_GUI_TRT_SCR_CTRL_PNL_COLOUR_IMGS [APP_GUI_MAXNUM_HP][APP_GUI_TRT_SCR_CTRL_PNL_COLOUR_STATES_IMGS] =
//{
//	{ c005__MenuTrtHP1_Aro1, c005_MenuTrtHP1_Aro2},	//HP1
//	{ c013_MenuTrtHP2_Aro1, c013_MenuTrtHP2_Aro2},	//HP2
//	{ c021_MenuTrtHP3_Aro1, c021_MenuTrtHP3_Aro2},	//HP3
//	{ c029_MenuTrtHP4_Aro1, c029_MenuTrtHP4_Aro2}	//HP4
//};

/* Listado de widgets que componen los popUps de error. Los widgets a deshabilitar son los del
 * panel de control */
const uint32 APP_GUI_TRT_SCR_HP_ERR_WIDGETS[APP_GUI_MAXNUM_HP][APP_GUI_NUM_ERR_WIDGETS_WHEN_HP] =
{
        { ImgPopUpErrBckGndHP1, NumVwrPopUpErrHP1, ImgPopUpErrMsgHP1, ButPopUpErrOkHP1, NumVwrPopUpErrTRTtimeHP1},
        { ImgPopUpErrBckGndHP2, NumVwrPopUpErrHP2, ImgPopUpErrMsgHP2, ButPopUpErrOkHP2, NumVwrPopUpErrTRTtimeHP2},
        { ImgPopUpErrBckGndHP3, NumVwrPopUpErrHP3, ImgPopUpErrMsgHP3, ButPopUpErrOkHP3, NumVwrPopUpErrTRTtimeHP3},
        { ImgPopUpErrBckGndHP4, NumVwrPopUpErrHP4, ImgPopUpErrMsgHP4, ButPopUpErrOkHP4, NumVwrPopUpErrTRTtimeHP4}
};

const uint32 APP_GUI_TRT_SCR_HP_ERR_MSG_IMAGES[Err_msg_max] =
{
        //standard			No_msg			release_HP					Obstruction				SETA				temperatura				  Resucciones
        C355_signoalarma, C355_signoalarma, C436_HPalarmaDesconexion, C427_HPalarmaObstruccion, C429_HPalarmaBoton, C435_HPalarmaTemperatura, C460_LimiteResuccionesSuperado,
        //SPI		Com485			Caudal			Power			RFID		Insifucuentes NTC	Tout Vacc
        C550_SPIerr, C551_Com485err, C552_Caudalerr, C553_PowerErr, C554_RFIDerr, C555_InsfNTC, C556_ToutVacc,
        //SinTramasMain		Desconocido			TemperaturaInterna	SensoresInternos	HP desconfigurado	HP Alarma		PCB dañada
        C557_SinTramasMain, C558_ErrDesconocido, C559_InternalTemp, C560_InternalSensors, C561_HPdesconfig, C562_HPalarma, C563_PCBdanada,
        //Test Inicial
        C564_TestInicialFallo,
};

//const uint32 APP_GUI_TRT_SCR_UC_ERR_WIDGETS[APP_GUI_NUM_ERR_WIDGETS_WHEN_UC] =
//{
//		imgPopUpErrBckGndUC, NumVwrPopUpErrUC, imgPopUpErrMsgUC, butPopUpErrOkUC
//};

//const uint32 APP_GUI_TRT_SCR_UC_ERR_MSG_IMAGES[Err_msg_max] =		//No se está empleando
//{
//		c061_Numero0, c052_Numero1, c053_Numero2, c054_Numero3, c055_Numero4, c056_Numero5
//};

////Indexado a los widgets del proceso de CLEANUP
//const uint32 APP_GUI_TRT_SCR_CLEANUP_BCKGND_WIDGETS[APP_GUI_MAXNUM_HP] =
//{
//		imgPopUpCleanBckGndHP1, imgPopUpCleanBckGndHP2, imgPopUpCleanBckGndHP3, imgPopUpCleanBckGndHP4
//};

//const uint32 APP_GUI_TRT_SCR_CLEANUP_IMAGES_WIDGETS[APP_GUI_MAXNUM_HP] =
//{
//		imgPopUpCleanHP1, imgPopUpCleanHP2, imgPopUpCleanHP3, imgPopUpCleanHP4
//};

//const uint32 APP_GUI_TRT_SCR_CLEANUP_NUM_VIEWER_WIDGETS[APP_GUI_MAXNUM_HP] =
//{
//		NumVwrPopUpCleanHP1, NumVwrPopUpCleanHP2, NumVwrPopUpCleanHP3, NumVwrPopUpCleanHP4
//};

//const uint32 APP_GUI_TRT_SCR_CLEANUP_BUTTON_YES_WIDGETS[APP_GUI_MAXNUM_HP] =
//{
//		butPopUpCleanYESHP1, butPopUpCleanYESHP2, butPopUpCleanYESHP3, butPopUpCleanYESHP4
//};

//const uint32 APP_GUI_TRT_SCR_CLEANUP_BUTTON_NO_WIDGETS[APP_GUI_MAXNUM_HP] =
//{
//		butPopUpCleanNOHP1, butPopUpCleanNOHP2, butPopUpCleanNOHP3, butPopUpCleanNOHP4
//};

//const uint32 APP_GUI_TRT_SCR_CLEANUP_BUTTON_CLEAN_WIDGETS[APP_GUI_MAXNUM_HP] =
//{
//		butPopUpCleanHP1, butPopUpCleanHP2, butPopUpCleanHP3, butPopUpCleanHP4
//};

//const uint32 APP_GUI_TRT_SCR_CLEANUP_BURTTON_CANCEL_WIDGETS [APP_GUI_MAXNUM_HP] =
//{
//		butPopUpCleanCancelHP1, butPopUpCleanCancelHP2, butPopUpCleanCancelHP3, butPopUpCleanCancelHP4
//};

//const uint32 APP_GUI_TRT_SCR_CLEANUP_NUMVWR_CANCELLED_TIMES_WIDGET[APP_GUI_MAXNUM_HP] =
//{
//		NumVwrPopUpCleanNumCancelHP1, NumVwrPopUpCleanNumCancelHP2, NumVwrPopUpCleanNumCancelHP3, NumVwrPopUpCleanNumCancelHP4
//};

//const uint32 APP_GUI_TRT_SCR_CLEANUP_STATUS_IMAGES[APP_GUI_CLEAN_UP_N_STATUS] =
//{
//		c434_HPalarmaLimpiezacolocar1, c433_HPalarmaLimpiezacolocar0, c432_HPalarmaLimpieza1, c431_HPalarmaLimpieza0
//};

//const uint32 APP_GUI_TRT_SCR_CLEANUP_BUTTON_YES_IMAGES[APP_GUI_MAX_ON_OFF] =
//{
//		c453_MenuAlarmaOK_MarcaAgua, c453_MenuAlarmaOK_rls,
//};
//const uint32 APP_GUI_TRT_SCR_CLEANUP_BUTTON_NO_IMAGES[APP_GUI_MAX_ON_OFF] =
//{
//		c455_MenuAlarmaNO_MarcaAgua, c455_MenuAlarmaNO_rls,
//};
//const uint32 APP_GUI_TRT_SCR_CLEANUP_BUTTON_CLEAN_IMAGES[APP_GUI_MAX_ON_OFF] =
//{
//		c458_MenuLimpiezaClean_MarcaAgua, c456_MenuLimpiezaClean_Rls
//};

/* Vector con los widgets para representar los puntos "DOTS" de zona seleccionable */
const uint32 APP_GUI_TRT_SCR_DOT_ZONES_WIDGETS[APP_GUI_MAX_DOTS_PER_AREA] =
{
        SwDotZone0, SwDotZone1, SwDotZone2, SwDotZone3, SwDotZone4, SwDotZone5, SwDotZone6,
        SwDotZone7, SwDotZone8, SwDotZone9, SwDotZone10, SwDotZone11, SwDotZone12, SwDotZone13, SwDotZone14
};

/* Vector con los widgets de los botones de area en full body */
const uint32 APP_GUI_TRT_SCR_FULL_BODY_AREAS_WIDGETS[APP_GUI_NUM_FULL_BODY_AREAS] =
{
        APP_GUI_NUM_WIDGETS,	//AppGUIfullBodyNO_AREA,
        ButFullBodyTorso, 		//AppGUIfullBodyTorso,
        ButFullBodyPiernas, 	//AppGUIfullBodyPiernas,
        ButFullBodyEspalda,		//AppGUIfullBodyEspalda,
        ButFullBodyPiernaMuslo,	//AppGUIfullBodyPiernasMuslo,
        ButFullBodyBrazos,		//AppGUIfullBodyBrazos,ButFullBodyBrazos
        ButFullBodyCuello		//AppGUIfullBodyCuello,
};

/* Vectir con los widgets de los indicadores de zona seleccionada en full body */
const uint32 APP_GUI_TRT_SCR_FULL_BODY_SELECTED_ZONE_WIDGETS[APP_GUI_MAXNUM_HP] =
{
        ImgSelectedTrtZoneHP1, ImgSelectedTrtZoneHP2, ImgSelectedTrtZoneHP3, ImgSelectedTrtZoneHP4
};

//const uint32 APP_GUI_TRT_SCR_POPUP_COLOR_BAR_IMAGES[APP_GUI_MAXNUM_HP] =
//{
//		c216_PopUpManipHP1, c217_PopUpManipHP2, c218_PopUpManipHP3, c219_PopUpManipHP4
//};

//const uint32 APP_GUI_TRT_SCR_POPUP_TST_VAC_LVL_IMAGES[APP_GUI_MAX_TST_VAC_DONE][HP_CRYO_VAC_LVL_NUM] =
//{
//							/*LOW level						MID level						HIGH level		*/
//		/*Tst not Done*/	{ c337_PopupBotonsuccion1Rls, 	c339_PopupBotonsuccion2Rls, 	c341_PopupBotonsuccion3Rls},
//		/*Tst Done*/		{ c338_PopupBotonsuccion1Press, c340_PopupBotonsuccion2Press, 	c342_PopupBotonsuccion3Press}
//};

const uint32 APP_GUI_TRT_SCR_POPUP_TST_VAC_SW_LIST[HP_CRYO_VAC_LVL_NUM] =
{
        //lvl0, lvl1, lvl2
        SwPopUpTstVacLowLvl, SwPopUpTstVacMidLvl, SwPopUpTstVacHighLvl
};

const uint32 APP_GUI_TRT_SCR_POPUP_TST_VAC_IMG_LIST[HP_CRYO_VAC_LVL_NUM] =
{
        //lvl 0, 				lvl 1,					lvl 2
        ImgPopUpTstVacLowLvl, 	ImgPopUpTstVacMidLvl, 	ImgPopUpTstVacHighLvl
};

const uint32 APP_GUI_TRT_SCR_POPUP_TIME_SW_LIST[HP_CRYO_MAX_TIME_LIST] =
{
        //45 min, 50 min, 70 min
        APP_GUI_NUM_WIDGETS, ButPopUpTime50min, ButPopUpTime70min,
};

const uint32 APP_GUI_TRT_SCR_BLINK_INDICATORS_WIDGETS[APP_GUI_MAXNUM_HP][APP_GUI_MAX_BLINK_INDICATORS] =
{
        { ImgCtrlPnlRFIDblinkHP1, ImgCtrlPnlPulBlinkHP1, ImgCtrlPnlVacBlinkHP1, ImgCtrlPnlCoolingBlinkHP1}, //HP1
        { ImgCtrlPnlRFIDblinkHP2, ImgCtrlPnlPulBlinkHP2, ImgCtrlPnlVacBlinkHP2, ImgCtrlPnlCoolingBlinkHP2}, //HP2
        { ImgCtrlPnlRFIDblinkHP3, ImgCtrlPnlPulBlinkHP3, ImgCtrlPnlVacBlinkHP3, ImgCtrlPnlCoolingBlinkHP3}, //HP3
        { ImgCtrlPnlRFIDblinkHP4, ImgCtrlPnlPulBlinkHP4, ImgCtrlPnlVacBlinkHP4, ImgCtrlPnlCoolingBlinkHP4}, //HP4
};

const uint32 APP_GUI_TRT_SCR_HP_MODEL_TEXT_IMG[APP_GUI_MAXNUM_HP][HP_CRYO_NUM_HP_MODELS] =
{
                //Undefined, Curved, Tight, Straight, Tiny, Tiny Curved, Double, Oval, Oval Curved, Angled
        /*HP1*/		{C233_ImgPixelBlanco, C066_NameCurvedHP_L, C067_NameTightHP_L, C068_NameStarightHP_L, C069_NameTinyHP_L,
                    C070_NameTinyCurvedHP_L, C071_NameDoubleHP_L, C072_NameOvalHP_L, C073_NameOvalCurvedHP_L, C074_NameDeltaHP_L},
        /*HP2*/		{C233_ImgPixelBlanco, C066_NameCurvedHP_R, C067_NameTightHP_R, C068_NameStraightHP_R, C069_NameTinyHP_R,
                    C070_NameTinyCurvedHP_R, C071_NameDoubleHP_R, C072_NameOvalHP_R, C073_NameOvalCurvedHP_R, C074_NameDeltaHP_R},
        /*HP3*/		{C233_ImgPixelBlanco, C066_NameCurvedHP_L, C067_NameTightHP_L, C068_NameStarightHP_L, C069_NameTinyHP_L,
                    C070_NameTinyCurvedHP_L, C071_NameDoubleHP_L, C072_NameOvalHP_L, C073_NameOvalCurvedHP_L, C074_NameDeltaHP_L},
        /*HP4*/		{C233_ImgPixelBlanco, C066_NameCurvedHP_R, C067_NameTightHP_R, C068_NameStraightHP_R, C069_NameTinyHP_R,
                    C070_NameTinyCurvedHP_R, C071_NameDoubleHP_R, C072_NameOvalHP_R, C073_NameOvalCurvedHP_R, C074_NameDeltaHP_R},
};

const uint32 APP_GUI_TRT_SCR_HP_MODEL_TEXT_WIDGETS[APP_GUI_MAXNUM_HP] =
{
        ImgModelTextHP1, ImgModelTextHP2, ImgModelTextHP3, ImgModelTextHP4
};

const uint32 APP_GUI_TRT_SCR_BUT_SEL_TIME_WIDGETS[APP_GUI_MAXNUM_HP] =
{
        ButSelectTimeHP1, ButSelectTimeHP2, ButSelectTimeHP3, ButSelectTimeHP4,
};

const uint32 APP_GUI_TRT_SCR_BUT_CHNG_TIME_TO_TEMP_WIDGETS[APP_GUI_MAXNUM_HP] =
{
        ButVwrTemperatureHP1, ButVwrTemperatureHP2, ButVwrTemperatureHP3, ButVwrTemperatureHP4
};

const uint32 APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[APP_GUI_MAXNUM_HP] =
{
        NumVwrTimeHP1, NumVwrTimeHP2, NumVwrTimeHP3, NumVwrTimeHP4,
};

const uint32 APP_GUI_TRT_SCR_NUM_VWE_RESUCCTIONS_NUM_WIDGETS [APP_GUI_MAXNUM_HP] =
{
        NumVwrResucctionCountHP1, NumVwrResucctionCountHP2, NumVwrResucctionCountHP3, NumVwrResucctionCountHP4,
};

const uint32 APP_GUI_TRT_SCR_BUT_TIME_IMG[App_GUI_Max_Time_but_states][App_GUI_widget_Features] =
{
                    /*	IMG_PRESS							IMG_RLS								ENABLE	*/
        /*Time_OFF*/	{C050_RelojTemporizadorMarcaAgua, 	C050_RelojTemporizadorMarcaAgua, 	0},
        /*Time_ON*/		{C048_RelojTemporizadorPress, 		C049_RelojTemporizadorRls, 			1}
};

const uint32 APP_GUI_TRT_SCR_BUT_PLAY_WIDGETS[APP_GUI_MAXNUM_HP] =
{
        ButCtrlPnlPlayHP1, ButCtrlPnlPlayHP2, ButCtrlPnlPlayHP3, ButCtrlPnlPlayHP4
};

const uint32 APP_GUI_TRT_SCR_BUT_PLAY_IMG[App_GUI_Max_Play_but_states][App_GUI_widget_Features] =
{
                    /*	IMG_PRESS					IMG_RLS						ENABLE	*/
    /*Play_OFF*/		{C038_BotonPlayMarcaAgua, 	C038_BotonPlayMarcaAgua,	0},
    /*Play_ON*/			{C035_BotonPlayPress, 		C037_BotonPlayRls, 			1},
    /*Play_TRT_running*/{C036_BotonPlayPress, 		C036_BotonPlayPress, 		0},
    /*Play_TRT_cancel*/	{C033_BotonStopPress, 		C034_BotonStopRls, 			1}
};

const uint32 APP_GUI_TRT_SCR_BUT_TSTVAC_WIDGETS[APP_GUI_MAXNUM_HP] =
{
        SwCtrlPnlTstVacHP1, SwCtrlPnlTstVacHP2, SwCtrlPnlTstVacHP3, SwCtrlPnlTstVacHP4
};

//const uint32 APP_GUI_TRT_SCR_BUT_VAC_IMG[HP_CRYO_VAC_LVL_NUM][App_GUI_Max_Vac_but_states][App_GUI_widget_Features] =
//{
//        /*Nivel Vac 1*/
//        {					/*(PRS, 							RLS, 								ENABLE)*/
//            /*OFF_L*/		{C042_BotonVacuum1MarcaAguaLeft, 	C042_BotonVacuum1MarcaAguaLeft, 	0},
//            /*OFF_R*/		{C042_BotonVacuum1MarcaAguaRight, 	C042_BotonVacuum1MarcaAguaRight, 	0},
//            /*ON_L*/		{C040_BotonVacuum1PressLeft, 		C041_BotonVacuum1RlsLeft, 			1},
//            /*ON_R*/		{C040_BotonVacuum1PressRight, 		C041_BotonVacuum1RlsRight, 			1},
//            /*VacAdjustL*/	{C352_BotonVacuum1PressArrowLeft, 	C353_BotonVacuum1RlsArrowLeft, 		1},
//            /*VacAdjustR*/	{C352_BotonVacuum1PressArrowRight, 	C353_BotonVacuum1RlsArrowRight, 	1}
//        },
//        /*Nivel Vac 2*/
//        {					/*(PRS, 							RLS, 								ENABLE)*/
//            /*OFF_L*/		{C042_BotonVacuum2MarcaAguaLeft, 	C042_BotonVacuum2MarcaAguaLeft, 	0},
//            /*OFF_R*/		{C042_BotonVacuum2MarcaAguaRight, 	C042_BotonVacuum2MarcaAguaRight, 	0},
//            /*ON_L*/		{C040_BotonVacuum2PressLeft, 		C041_BotonVacuum2RlsLeft, 			1},
//            /*ON_R*/		{C040_BotonVacuum2PressRight, 		C041_BotonVacuum2RlsRight, 			1},
//            /*VacAdjustL*/	{C352_BotonVacuum2PressArrowLeft, 	C353_BotonVacuum2RlsArrowLeft, 		1},
//            /*VacAdjustR*/	{C352_BotonVacuum2PressArrowRight, 	C353_BotonVacuum2RlsArrowRight, 	1}
//        },
//        /*Nivel Vac 3*/
//        {					/*(PRS, 							RLS, 								ENABLE)*/
//            /*OFF_L*/		{C042_BotonVacuum3MarcaAguaLeft,	C042_BotonVacuum3MarcaAguaLeft, 	0},
//            /*OFF_R*/		{C042_BotonVacuum3MarcaAguaRight,	C042_BotonVacuum3MarcaAguaRight, 	0},
//            /*ON_L*/		{C040_BotonVacuum3PressLeft, 		C041_BotonVacuum3RlsLeft, 			1},
//            /*ON_R*/		{C040_BotonVacuum3PressRight, 		C041_BotonVacuum3RlsRight, 			1},
//            /*VacAdjustL*/	{C352_BotonVacuum3PressArrowLeft, 	C353_BotonVacuum3RlsArrowLeft, 		1},
//            /*VacAdjustR*/	{C352_BotonVacuum3PressArrowRight, 	C353_BotonVacuum3RlsArrowRight, 	1}
//        }
//};

///* Cambios de imagenes en diversos widgets */
///* - */
//const uint32 APP_GUI_TRT_LOAD_NEW_HP_CONFIG[APP_GUI_TRT_LOAD_NEW_HP_IMG] =
//{
//		c111_signorelojup, c111_signorelojdown
//};
///* Vectores de widgets gestionados por los PopUps */
///* - RFID */
//const uint32 APP_GUI_POPUP_RFID_WIDGET_LIST[APP_GUI_POPUP_RFID_WIDGET_LIST_NUM] =
//{
//		imgPopUpRFIDbckGnd, ButPopUpReturn, imgPopUpHPcolorBar, imgPopUpRFIDlabel, imgPopUpRFIDresult, butPopUpRFIDreuseLabel, NumVwrPopUpRFIDrestTime
//};

const uint32 APP_GUI_TRT_SCR_POPUP_RFID_LABELS_IMGS [HP_CRYO_NUM_LABELS] =
{
        APP_GUI_NUM_WIDGETS, C182_PopUpRFIDlabelZ0, C182_PopUpRFIDlabelZ1, C182_PopUpRFIDlabelZ2, C182_PopUpRFIDlabelZ3, C182_PopUpRFIDlabelDM, HP_CRYO_PROD_LABEL_PD, APP_GUI_NUM_WIDGETS
};

const uint32 APP_GUI_TRT_SCR_POPUP_RFID_STATUS_IMGS [RFID_MAX_LABEL_OPTIONS] =
{
        C182_PopUpRFIDsuccess, C182_PopUpRFIDfail, C182_PopUpRFIDunknown, C182_PopUpRFIDwrong, C233_ImgPixelBlanco
};

///* - Test Vacum */
//const uint32 APP_GUI_POPUP_TST_VAC_WIDGET_LIST[APP_GUI_POPUP_TST_VAC_WIDGET_LIST_NUM] =
//{
//		imgPopUpTstVacBckGnd,imgPopUpTstVacLowLvl,imgPopUpTstVacMidLvl,imgPopUpTstVacHighLvl,
//		imgPopUpTstVacPulHand,imgPopUpTstVacPulHandx2,butPopUpTstVacManualLowLvl,butPopUpTstVacManualMidLvl,butPopUpTstVacManualHighLvl,
//		butPopUpTstVacAuto,	SwPopUpTstVacLowLvl,SwPopUpTstVacMidLvl,SwPopUpTstVacHighLvl,
//		ButPopUpReturn, /*butPopUpOK,*/ imgPopUpHPcolorBar, imgPopUpTstVacAUTOstatus
//};

///* - Test Vacum SMALL */
//const uint32 APP_GUI_POPUP_TST_VAC_SMALL_WIDGET_LIST[APP_GUI_POPUP_TST_VAC_SMALL_WIDGET_LIST_NUM] =
//{
//		butPopUpTstVacSmallLowLvl, butPopUpTstVacSmallMedLvl, butPopUpTstVacSmallHighLvl, imgPopUpVacSelBck
//};

//const uint32 APP_GUI_POPUP_TST_VAC_SMALL_BUT_IMAGES[HP_CRYO_VAC_LVL_NUM][App_GUI_but_max] =
//{
//						/*On*/						/*MarcaAgua*/
//		/*Low Vac*/		{c343_BotonVacuumSmall1Rls,	c344_BotonVacuumSmall1MarcaAgua	},
//		/*Mid Vac*/		{c345_BotonVacuumSmall2Rls,	c346_BotonVacuumSmall2MarcaAgua	},
//		/*High Vac*/	{c347_BotonVacuumSmall3Rls,	c348_BotonVacuumSmall3MarcaAgua	}
//};

//const uint16 APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[APP_GUI_MAXNUM_HP][App_GUI_PopUpVacWidgetCoordinates][Max_coordinates] =
//{
//			/*	Low Lvl		Med Lvl		High Lvl	Selector*/
//	/*HP1*/		{{176, 44},	{229, 44},	{280, 44},	{162, 34}},		//Coordenadas del popup desplegable de las opciones de vacum para el menú particular de cada aplicador
//	/*HP2*/		{{480, 44},	{528, 44},	{581, 44},	{466, 34}},		//***
//	/*HP3*/		{{176, 518},{229, 518},	{280, 518},	{162, 508}},
//	/*HP4*/		{{480, 518},{528, 518},	{581, 518},	{466, 508}}
//};

//const uint32 APP_GUI_TRT_SCR_POPUP_VAC_SMALL_BCK_IMG[APP_GUI_MAXNUM_HP] =
//{
//		c349_BotonVacuumDesplegable_L, c350_BotonVacuumDesplegable_R_03, c349_BotonVacuumDesplegable_L, c350_BotonVacuumDesplegable_R_03
//};

///* - Tiempo */
//const uint32 APP_GUI_POPUP_TIME_WIDGET_LIST[APP_GUI_POPUP_TIME_WIDGET_LIST_NUM] =
//{
//		butPopUpTime50min, butPopUpTime70min, imgPopUpTime1sel, imgPopUpTime2sel,
//};

//const uint16 APP_GUI_POPUP_TIME_COORDINATES_PER_HP[App_GUI_PopUpTimeWidgetCoordinates][APP_GUI_MAXNUM_HP][Max_coordinates] =
//{
//		//						HP1			HP2			HP3			HP4
//		{	/*Time1*/		{57, 145},	{633, 145},	{57, 505},	{633, 505}	},		//Coordenadas del popup desplegable del tiempo para el menú particular de cada aplicador
//		{	/*Time2*/		{57, 180},	{633, 180},	{57, 540},	{633, 540}	},		//***
//		{	/*Menu*/		{48, 129},	{624, 129},	{48, 490},	{624, 490}	}
//};
///* - Recommendation */
//const uint32 APP_GUI_POPUP_RECOMMENDATION_WIDGET_LIST[APP_GUI_POPUP_RECOMMENDATION_WIDGET_LIST_NUM] =
//{
//		PopUpRecomm, imgPopUpRecommbckGnd, ImgPopUpRecommCurved, ImgPopUpRecommTight, ImgPopUpRecommStright, ImgPopUpRecommTiny,
//		ImgPopUpRecommTinyCurved, ImgPopUpRecommDouble, ImgPopUpRecommOval, ImgPopUpRecommOvalCurved, ImgPopUpRecommAngled,
//		//SwPopUpRecommInfo
//};

//const uint32 APP_GUI_POPUP_AVISOS_INIT_SCRN_WIDGET_LIST[APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM] =
//{
//		PopupInitScrAvisos, imgPopUpInitScrAvisoBckGND, imgPopUpInitScrAvisoNivelAguaBajo, imgPopUpInitScrAvisoNivelAguaMedio, imgPopUpInitScrAvisoTempAmb,
//		imgPopUpInitScrAvisoRFID, imgPopUpInitScrAvisoRTC, imgPopUpInitScrAvisoFiltroAire
//};

//const uint32 APP_GUI_POPUP_AVISOS_TRT_SCRN_WIDGET_LIST[APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM] =
//{
//		PopupTrtScrAvisos, imgPopUpTrtScrAvisoBckGND, imgPopUpTrtScrAvisoNivelAguaBajo, imgPopUpTrtScrAvisoNivelAguaMedio, imgPopUpTrtScrAvisoTempAmb,
//		imgPopUpTrtScrAvisoRFID, imgPopUpTrtScrAvisoRTC, imgPopUpTrtScrAvisoFiltroAire//, SwTrtScrAvisos
//};

//const uint32 APP_GUI_POPUP_AVISOS_CALC_SCRN_WIDGET_LIST[APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM] =
//{
//		PopupCalcScrAvisos, imgPopUpCalcScrAvisoBckGND, imgPopUpCalcScrAvisoNivelAguaBajo, imgPopUpCalcScrAvisoNivelAguaMedio, imgPopUpCalcScrAvisoTempAmb,
//		imgPopUpCalcScrAvisoRFID, imgPopUpCalcScrAvisoRTC, imgPopUpCalcScrAvisoFiltroAire
//};

//const uint32 APP_GUI_POPUP_AVISOS_CFG_SCRN_WIDGET_LIST[APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM] =
//{
//		PopupCfgScrAvisos, imgPopUpCfgScrAvisoBckGND, imgPopUpCfgScrAvisoNivelAguaBajo, imgPopUpCfgScrAvisoNivelAguaMedio, imgPopUpCfgScrAvisoTempAmb,
//		imgPopUpCfgScrAvisoRFID, imgPopUpCfgScrAvisoRTC, imgPopUpCfgScrAvisoFiltroAire
//};

//const uint32 APP_GUI_POPUP_AVISOS_LAN_SCRN_WIDGET_LIST[APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM] =
//{
//		PopupLanScrAvisos, imgPopUpLanScrAvisoBckGND, imgPopUpLanScrAvisoNivelAguaBajo, imgPopUpLanScrAvisoNivelAguaMedio, imgPopUpLanScrAvisoTempAmb,
//		imgPopUpLanScrAvisoRFID, imgPopUpLanScrAvisoRTC, imgPopUpLanScrAvisoFiltroAire
//};

//const uint32 APP_GUI_POPUP_ERRORES_SAT_WIDGET_LIST[APP_GUI_POPUP_ERRORES_SAT_WIDGET_LIST_NUM] =
//{
//		PopupErrorSAT, imgVwrFondoErrorSAT, NumVwrError1, NumVwrError2, NumVwrError3, NumVwrError4, NumVwrError5, butOkerr
//};

const uint32 APP_GUI_AVISOS_POPUP_WIDGET_SCREENS[APP_GUI_NUM_SCREENS] =
{
        APP_GUI_NUM_WIDGETS, PopupInitScrAvisos, PopupTrtScrAvisos,PopupCalcScrAvisos, PopupCfgScrAvisos, PopupLanScrAvisos, APP_GUI_NUM_WIDGETS
};

//const uint32 APP_GUI_AVISOS_SWITCH_WIDGET_SCREENS[APP_GUI_NUM_SCREENS] =
//{
//		APP_GUI_NUM_WIDGETS, SwInitScrAvisos, SwTrtScrAvisos,  SwCalcScrAvisos, SwCfgScrAvisos, SwLanScrAvisos, APP_GUI_NUM_WIDGETS
//};

const uint32 APP_GUI_AVISOS_NOTIFICATIONS_WIDGETS_SCREENS[APP_GUI_NUM_SCREENS] =
{
        APP_GUI_NUM_WIDGETS, ImgInitScrNotificacion, ImgTrtScrNotificacion, ImgCalcScrNotificacion, ImgCfgScrNotificacion, ImgLanScrNotificacion, APP_GUI_NUM_WIDGETS
};

//const uint32 APP_GUI_SAT_ERRORES_NUMVWR_LIST[APP_GUI_SAT_ERRORES_PERIFS] =
//{
//		NumVwrError1, NumVwrError2, NumVwrError3, NumVwrError4, NumVwrError5
//};

//const uint32 APP_GUI_AVISOS_WIDGETS[APP_GUI_NUM_SCREENS][App_GUI_Num_Max_Avisos] =
//{
//	/*Carga*/			{APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS},
//	/*Inicio*/			{imgPopUpInitScrAvisoNivelAguaBajo, imgPopUpInitScrAvisoNivelAguaMedio, imgPopUpInitScrAvisoTempAmb, imgPopUpInitScrAvisoRFID, imgPopUpInitScrAvisoRTC, imgPopUpInitScrAvisoFiltroAire},
//	/*Tratamiento*/		{imgPopUpTrtScrAvisoNivelAguaBajo, imgPopUpTrtScrAvisoNivelAguaMedio, imgPopUpTrtScrAvisoTempAmb, imgPopUpTrtScrAvisoRFID, imgPopUpTrtScrAvisoRTC, imgPopUpTrtScrAvisoFiltroAire},
//	/*Calculadora*/		{imgPopUpCalcScrAvisoNivelAguaBajo, imgPopUpCalcScrAvisoNivelAguaMedio, imgPopUpCalcScrAvisoTempAmb, imgPopUpCalcScrAvisoRFID, imgPopUpCalcScrAvisoRTC, imgPopUpCalcScrAvisoFiltroAire},
//	/*Configuración*/	{imgPopUpCfgScrAvisoNivelAguaBajo, imgPopUpCfgScrAvisoNivelAguaMedio, imgPopUpCfgScrAvisoTempAmb, imgPopUpCfgScrAvisoRFID, imgPopUpCfgScrAvisoRTC, imgPopUpCfgScrAvisoFiltroAire},
//	/*Idiomas*/			{imgPopUpLanScrAvisoNivelAguaBajo, imgPopUpLanScrAvisoNivelAguaMedio, imgPopUpLanScrAvisoTempAmb, imgPopUpLanScrAvisoRFID, imgPopUpLanScrAvisoRTC, imgPopUpLanScrAvisoFiltroAire},
//	/*SAT*/				{APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS},
//	/*FATIGA*/			{APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS}
//};

const uint32 APP_GUI_TRT_SCR_POPUP_WIDGET_LIST[APP_GUI_TRT_SCR_NUM_POPUPS] =
{
        PopUpTime, PopUpTstVac, PopUpRFID, PopUpRecomm, PopUpTstVacSmall, PopupTrtScrAvisos
};

const cAppGUItrtAgrupacionZones APP_GUI_TRT_ZONES_GROUP_ASSOCIATION[APP_GUI_NUM_FULL_BODY_AREAS][APP_GUI_MAX_DOTS_PER_AREA] =
{
        //NO ZONA
        {NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo},
        //Torso
        {PliegueAxilar, PliegueAxilar, Intrapectoral, Intrapectoral, AbdominalSupraumbrical, AbdominalSupraumbrical, AbdominalSupraumbrical,
        AbdominalInfraumbrical, AbdominalInfraumbrical, AbdominalInfraumbrical, NoGrupo, Cadera, Cadera, Senos, Senos},
        //Pierna frontal
        {Trocantereal, Trocantereal, CaraInternaMuslo, CaraInternaMuslo, SuperiorRodilla, SuperiorRodilla, InteriorRodilla, InteriorRodilla,
        NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo},
        //Espalda
        {Supraescapular, Supraescapular, Infraescapular, Infraescapular, Flanco, Flanco,
        NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo},
        //Pierna posterior
        {Gluteo, Gluteo, Subgluteo, Subgluteo, MusloPosterior, MusloPosterior,
        NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo},
        //Brazos
        {Brazo, Brazo,
        NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo},
        //Cuello
        {NoGrupo, Papada, Papada,
        NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo, NoGrupo},
};

/* Un '1' indica que ha de mostrarse el aplicador con marca de agua en la recomendación, es decir que no se recomienda ese aplicador para esa zona*/
const uint8 APP_GUI_HP_RECOMMENDED_PER_ZONE[HP_CRYO_NUM_HP_MODELS][APP_GUI_NUM_FULL_BODY_AREAS][APP_GUI_MAX_DOTS_PER_AREA] =
{
        //UNDEFINED
        {	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        },
        //CURVED
        {	//NO_AREA						//TORSO							//PIERNAS						//ESPALDA
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,0,0,0,1,0,0,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,0,0,0,0,1,1,1,1,1,1,1,1,1},
            //PIERNAS_TRASERA				//BRAZOS						//CUELLO
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        //TIGHT
        {	//NO_AREA						//TORSO							//PIERNAS						//ESPALDA
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,0,0,0,0,0,0,0,0,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,0,0,0,0,1,1,1,1,1,1,1,1,1},
            //PIERNAS_TRASERA				//BRAZOS						//CUELLO
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        //STRIGHT
        {	//NO_AREA						//TORSO							//PIERNAS						//ESPALDA
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,0,0,0,0,0,0,1,1,1,1,1},{1,1,0,0,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
            //PIERNAS_TRASERA				//BRAZOS						//CUELLO
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        //TINY
        {	//NO_AREA						//TORSO							//PIERNAS						//ESPALDA
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,0,0,0,0,1,1,1,1,1,1,1},{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
            //PIERNAS_TRASERA				//BRAZOS						//CUELLO
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        //TINY CURVED
        {	//NO_AREA						//TORSO							//PIERNAS						//ESPALDA
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{0,0,0,0,1,1,1,1,1,1,1,1,1,0,0},{1,1,1,1,0,0,0,0,1,1,1,1,1,1,1},{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
            //PIERNAS_TRASERA				//BRAZOS						//CUELLO
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        //DOUBLE
        {	//NO_AREA						//TORSO							//PIERNAS						//ESPALDA
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,0,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            //PIERNAS_TRASERA				//BRAZOS						//CUELLO
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        //OVAL
        {	//NO_AREA						//TORSO							//PIERNAS						//ESPALDA
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,0,1,1,0,0,1,1},{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
            //PIERNAS_TRASERA				//BRAZOS						//CUELLO
            {1,1,0,0,0,0,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        //OVAL CURVED
        {	//NO_AREA						//TORSO							//PIERNAS						//ESPALDA
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,0,1,1,0,0,1,1},{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
            //PIERNAS_TRASERA				//BRAZOS						//CUELLO
            {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        //ANGLED
        {	//NO_AREA						//TORSO							//PIERNAS						//ESPALDA
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,0,1,1,0,0},{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            //PIERNAS_TRASERA				//BRAZOS						//CUELLO
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
};

///* Tablas para la gestión de las areas de selección */
//const tAppGUIfullBodyImagesTableFields APP_GUI_FULL_BODY_IMAGES[APP_GUI_NUM_BODYS] =
//{
//		{ c003_SiluetaHombreFrenteEspalda, APP_GUI_IMG_SILUETA_HOMBRE},		//Hombre
//		{ c002_SiluetaMujerFrenteEspalda, APP_GUI_IMG_SILUETA_MUJER}		//Mujer
//};

//const tAppGUIfullBodyAreasTableFields APP_GUI_FULL_BODY_AREAS_DATA[APP_GUI_NUM_BODYS][APP_GUI_NUM_FULL_BODY_AREAS] =
//{
//	//Hombre
//	{
//		/* ImgPrs ID, imgX, imgY, ImgRls ID, imgX, imgY, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoom, imgX, imgY */
//		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//No area
//		{ c130_BotonTorsoRlsHombre, 		271, 202, c233_ImgPixelBlanco, 	271, 202, c132_TscBotonTorsoHombre, 		271, 202,  95, 125,	c210_TorsoHombre, 			234, 105},	//Torso
//		{ c133_BotonPiernasRlsHombre, 		271, 327, c233_ImgPixelBlanco, 	271, 327, c135_TscBotonPiernasHombre, 		271, 327,  95, 113,	c211_PiernasHombre, 		205, 105},	//Piernas
//		{ c139_BotonEspaldaRlsHombre, 		450, 202, c233_ImgPixelBlanco, 	450, 202, c141_TscBotonEspladaHombre, 		450, 202,  71,  95,	c212_BrazosEspaldaHombre, 	213, 105},	//Espalda
//		{ c142_BotonPiernaMusloRlsHombre, 	446, 296, c233_ImgPixelBlanco, 	446, 296, c144_TscBotonPiernaMusloHombre, 	446, 296,  80, 114,	c213_PiernaMusloHombre, 	213, 105},	//Piernas muslo
//		{ c136_BotonBrazosRlsHombre, 		422, 202, c233_ImgPixelBlanco, 	422, 202, c138_TscBotonBrazosHombre, 		422, 202, 134, 101,	c212_BrazosEspaldaHombre, 	213, 105},	//Brazos
//		{ c145_BotonCuelloRlsHombre, 		296, 175, c233_ImgPixelBlanco, 	296, 175, c147_TscBotonCuelloHombre, 		296, 175,  43,  25,	c214_CuelloHombre, 			205, 140},	//Cuello
		
//	},
//	//Mujer
//	{
//		/* ImgPrs ID, imgX, imgY, ImgRls ID, imgX, imgY, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoom, imgX, imgY */
//		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//No area
//		{ c113_BotonTorsoPressMujer, 		282, 208, c233_ImgPixelBlanco, 	282, 208, c114_TscBotonTorsoMujer, 			282, 208,  91, 126,	c205_ImgTorsoMujer, 		236, 105},	//Torso
//		{ c115_BotonPiernasRlsMujer, 		282, 295, c233_ImgPixelBlanco, 	282, 295, c117_TscBotonPiernasMujer, 		282, 295,  91, 146,	c206_ImgPiernasMujer, 		236, 105},	//Piernas
//		{ c121_BotonEspaldaRlsMujer, 		439, 205, c233_ImgPixelBlanco, 	439, 205, c123_TscBotonEspladaMujer, 		439, 205,  76,  99,	c207_BrazosEspaldaMujer,	236, 105},	//Espalda
//		{ c124_BotonPiernaMusloRlsMujer, 	431, 304, c233_ImgPixelBlanco, 	431, 304, c126_TscBotonPiernaMusloMujer, 	431, 304,  90, 103,	c208_PiernaMusloMujer, 		253, 115},	//Piernas muslo
//		{ c118_BotonBrazosRlsMujer, 		415, 200, c233_ImgPixelBlanco, 	415, 200, c120_TscBotonBrazosMujer, 		415, 200, 121,  95,	c207_BrazosEspaldaMujer,	236, 105},	//Brazos
//		{ c127_BotonCuelloRlsMujer, 		312, 170, c233_ImgPixelBlanco, 	312, 170, c129_TscBotonCuelloMujer, 		312, 170,  32,  25,	c209_CuelloMujer, 			205, 140},	//Cuello
//	}
//};

const tAppGUIareaZoomDotsTableFields APP_GUI_AREA_ZOOM_DOTS[APP_GUI_NUM_BODYS][APP_GUI_NUM_FULL_BODY_AREAS][APP_GUI_MAX_DOTS_PER_AREA] =
{
    //Hombre
    {
    //No Area
        {
            /*isUsed, imgX, imgY, imgOff, imgOn, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoomHP1Off, imgZoomHP2Off, imgZoomHP3Off, imgZoomHP4Off, imgZoomHPOff_X, imgZoomHPOff_Y, imgZoomHP1On, imgZoomHP2On, imgZoomHP3On, imgZoomHP4On, imgZoomHPOn_X, imgZoomHPOn_Y, imgBodyHP1, imgBodyHP2, imgBodyHP3, imgBodyHP4, imgBodyHP_X, imgBodyHP_Y, ZoneName */
            { 0, 0, 0, NO_ZONA}, //Punto0
            { 0, 0, 0, NO_ZONA}, //Punto1
            { 0, 0, 0, NO_ZONA}, //Punto2
            { 0, 0, 0, NO_ZONA}, //Punto3
            { 0, 0, 0, NO_ZONA}, //Punto4
            { 0, 0, 0, NO_ZONA}, //Punto5
            { 0, 0, 0, NO_ZONA}, //Punto6
            { 0, 0, 0, NO_ZONA}, //Punto7
            { 0, 0, 0, NO_ZONA}, //Punto8
            { 0, 0, 0, NO_ZONA}, //Punto9
            { 0, 0, 0, NO_ZONA}, //Punto10
            { 0, 0, 0, NO_ZONA}, //Punto11
            { 0, 0, 0, NO_ZONA}, //Punto12
            { 0, 0, 0, NO_ZONA}, //Punto13
            { 0, 0, 0, NO_ZONA} //Punto14
        },
        //Torso
        {
            /*isUsed, imgX, imgY, imgOff, imgOn, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoomHP1Off, imgZoomHP2Off, imgZoomHP3Off, imgZoomHP4Off, imgZoomHPOff_X, imgZoomHPOff_Y, imgZoomHP1On, imgZoomHP2On, imgZoomHP3On, imgZoomHP4On, imgZoomHPOn_X, imgZoomHPOn_Y, imgBodyHP1, imgBodyHP2, imgBodyHP3, imgBodyHP4, imgBodyHP_X, imgBodyHP_Y, ZoneName */
            { 1, 332, 208, PliegueAxilarIzquierdo}, 			//Punto0
            { 1, 270, 208, PliegueAxilarDerecho}, 			//Punto1
            { 1, 318, 240, IntrapectoralIzquierdo}, 			//Punto2
            { 1, 282, 240, IntrapectoralDerecho}, 			//Punto3
            { 1, 318, 265, AbdominalSupraumbricalIzquierdo}, 	//Punto4
            { 1, 301, 265, AbdominalSupraumbricalCentral}, 	//Punto5
            { 1, 282, 265, AbdominalSupraumbricalDerecho}, 	//Punto6
            { 1, 318, 290, AbdominalInfraumbricalIzquierdo}, 	//Punto7
            { 1, 301, 290, AbdominalInfraumbricalCentral}, 	//Punto8
            { 1, 282, 290, AbdominalInfraumbricalDerecho}, 	//Punto9
            { 0, 301, 310, Pubis}, 							//Punto10
            { 1, 325, 285, CaderaIzquierdo}, 					//Punto11
            { 1, 275, 285, CaderaDerecho}, 					//Punto12
            { 1, 322, 218, SenoIzquierdo}, 			//Punto13
            { 1, 280, 218, SenoDerecho} 			//Punto14
        },
        //Piernas
        {
            /*isUsed, imgX, imgY, imgOff, imgOn, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoomHP1Off, imgZoomHP2Off, imgZoomHP3Off, imgZoomHP4Off, imgZoomHPOff_X, imgZoomHPOff_Y, imgZoomHP1On, imgZoomHP2On, imgZoomHP3On, imgZoomHP4On, imgZoomHPOn_X, imgZoomHPOn_Y, imgBodyHP1, imgBodyHP2, imgBodyHP3, imgBodyHP4, imgBodyHP_X, imgBodyHP_Y, ZoneName */
            { 1, 332, 335, TrocantereaIzquierdo}, 		//Punto0
            { 1, 272, 335, TrocantereaDerecho}, 			//Punto1
            { 1, 310, 360, CaraInternaMusloIzquierdo}, 	//Punto2
            { 1, 290, 360, CaraInternaMusloDerecho}, 		//Punto3
            { 1, 320, 383, SuperioRodillaIzquierda}, 		//Punto4
            { 1, 280, 383, SuperiorRodillaDerecha}, 		//Punto5
            { 1, 310, 395, IntRodillaIzquierda}, 			//Punto6
            { 1, 290, 395, IntRodillaDerecha}, 			//Punto7
            { 0, 0, 0, NO_ZONA}, //Punto8
            { 0, 0, 0, NO_ZONA}, //Punto9
            { 0, 0, 0, NO_ZONA}, //Punto10
            { 0, 0, 0, NO_ZONA}, //Punto11
            { 0, 0, 0, NO_ZONA}, //Punto12
            { 0, 0, 0, NO_ZONA}, //Punto13
            { 0, 0, 0, NO_ZONA} //Punto14
        },
        //Espalda
        {
            /*isUsed, imgX, imgY, imgOff, imgOn, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoomHP1Off, imgZoomHP2Off, imgZoomHP3Off, imgZoomHP4Off, imgZoomHPOff_X, imgZoomHPOff_Y, imgZoomHP1On, imgZoomHP2On, imgZoomHP3On, imgZoomHP4On, imgZoomHPOn_X, imgZoomHPOn_Y, imgBodyHP1, imgBodyHP2, imgBodyHP3, imgBodyHP4, imgBodyHP_X, imgBodyHP_Y, ZoneName */
            { 1, 451, 222, SupraescapularIzquierda}, 	//Punto0
            { 1, 485, 222, SupraescapularDerecha}, 	//Punto1
            { 1, 451, 245, InfraescapularIzquierda}, 	//Punto2
            { 1, 485, 245, InfraescapularDerecha}, 	//Punto3
            { 1, 451, 274, FlancoIzquierdo}, 			//Punto4
            { 1, 485, 274, FlancoDerecho}, 			//Punto5
            { 0, 0, 0, NO_ZONA}, //Punto6
            { 0, 0, 0, NO_ZONA}, //Punto7
            { 0, 0, 0, NO_ZONA}, //Punto8
            { 0, 0, 0, NO_ZONA}, //Punto9
            { 0, 0, 0, NO_ZONA}, //Punto10
            { 0, 0, 0, NO_ZONA}, //Punto11
            { 0, 0, 0, NO_ZONA}, //Punto12
            { 0, 0, 0, NO_ZONA}, //Punto13
            { 0, 0, 0, NO_ZONA} //Punto14
        },
        //Piernas muslo
        {
            /*isUsed, imgX, imgY, imgOff, imgOn, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoomHP1Off, imgZoomHP2Off, imgZoomHP3Off, imgZoomHP4Off, imgZoomHPOff_X, imgZoomHPOff_Y, imgZoomHP1On, imgZoomHP2On, imgZoomHP3On, imgZoomHP4On, imgZoomHPOn_X, imgZoomHPOn_Y, imgBodyHP1, imgBodyHP2, imgBodyHP3, imgBodyHP4, imgBodyHP_X, imgBodyHP_Y, ZoneName */
            { 1, 448, 311, GluteoIzquierdo}, 			//Punto0
            { 1, 489, 311, GluteoDerecho}, 			//Punto1
            { 1, 448, 337, SubgluteoIzquierdo}, 		//Punto2
            { 1, 490, 337, SubgluteoDerecho}, 		//Punto3
            { 1, 448, 358, MusloPosteriorIzquierdo}, 	//Punto4
            { 1, 490, 358, MusloPosterioDerecho}, 	//Punto5
            { 0, 0, 0, NO_ZONA}, //Punto6
            { 0, 0, 0, NO_ZONA}, //Punto7
            { 0, 0, 0, NO_ZONA}, //Punto8
            { 0, 0, 0, NO_ZONA}, //Punto9
            { 0, 0, 0, NO_ZONA}, //Punto10
            { 0, 0, 0, NO_ZONA}, //Punto11
            { 0, 0, 0, NO_ZONA}, //Punto12
            { 0, 0, 0, NO_ZONA}, //Punto13
            { 0, 0, 0, NO_ZONA} //Punto14
        },
        //Brazos
        {
            /*isUsed, imgX, imgY, imgOff, imgOn, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoomHP1Off, imgZoomHP2Off, imgZoomHP3Off, imgZoomHP4Off, imgZoomHPOff_X, imgZoomHPOff_Y, imgZoomHP1On, imgZoomHP2On, imgZoomHP3On, imgZoomHP4On, imgZoomHPOn_X, imgZoomHPOn_Y, imgBodyHP1, imgBodyHP2, imgBodyHP3, imgBodyHP4, imgBodyHP_X, imgBodyHP_Y, ZoneName */
            { 1, 422, 227, BrazoIzquierdo}, 	//Punto0
            { 1, 515, 227, BrazoDerecho}, 	//Punto1
            { 0, 0, 0, NO_ZONA}, //Punto2
            { 0, 0, 0, NO_ZONA}, //Punto3
            { 0, 0, 0, NO_ZONA}, //Punto4
            { 0, 0, 0, NO_ZONA}, //Punto5
            { 0, 0, 0, NO_ZONA}, //Punto6
            { 0, 0, 0, NO_ZONA}, //Punto7
            { 0, 0, 0, NO_ZONA}, //Punto8
            { 0, 0, 0, NO_ZONA}, //Punto9
            { 0, 0, 0, NO_ZONA}, //Punto10
            { 0, 0, 0, NO_ZONA}, //Punto11
            { 0, 0, 0, NO_ZONA}, //Punto12
            { 0, 0, 0, NO_ZONA}, //Punto13
            { 0, 0, 0, NO_ZONA} //Punto14
        },
        //Cuello
        {
            /*isUsed, imgX, imgY, imgOff, imgOn, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoomHP1Off, imgZoomHP2Off, imgZoomHP3Off, imgZoomHP4Off, imgZoomHPOff_X, imgZoomHPOff_Y, imgZoomHP1On, imgZoomHP2On, imgZoomHP3On, imgZoomHP4On, imgZoomHPOn_X, imgZoomHPOn_Y, imgBodyHP1, imgBodyHP2, imgBodyHP3, imgBodyHP4, imgBodyHP_X, imgBodyHP_Y, ZoneName */
            { 1, 300, 175, PapadaCentral}, 			//Punto0
            { 1, 312, 168, PapadaLateralIzquierdo}, 	//Punto1
            { 1, 290, 168, PapadaLateralDerecho}, 	//Punto2
            { 0, 0, 0, NO_ZONA}, //Punto3
            { 0, 0, 0, NO_ZONA}, //Punto4
            { 0, 0, 0, NO_ZONA}, //Punto5
            { 0, 0, 0, NO_ZONA}, //Punto6
            { 0, 0, 0, NO_ZONA}, //Punto7
            { 0, 0, 0, NO_ZONA}, //Punto8
            { 0, 0, 0, NO_ZONA}, //Punto9
            { 0, 0, 0, NO_ZONA}, //Punto10
            { 0, 0, 0, NO_ZONA}, //Punto11
            { 0, 0, 0, NO_ZONA}, //Punto12
            { 0, 0, 0, NO_ZONA}, //Punto13
            { 0, 0, 0, NO_ZONA} //Punto14
        },
    },
    //Mujer
    {
        //No Area
        {
            /*isUsed, imgX, imgY, imgOff, imgOn, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoomHP1Off, imgZoomHP2Off, imgZoomHP3Off, imgZoomHP4Off, imgZoomHPOff_X, imgZoomHPOff_Y, imgZoomHP1On, imgZoomHP2On, imgZoomHP3On, imgZoomHP4On, imgZoomHPOn_X, imgZoomHPOn_Y, imgBodyHP1, imgBodyHP2, imgBodyHP3, imgBodyHP4, imgBodyHP_X, imgBodyHP_Y, ZoneName */
            { 0, 0, 0, NO_ZONA}, //Punto0
            { 0, 0, 0, NO_ZONA}, //Punto1
            { 0, 0, 0, NO_ZONA}, //Punto2
            { 0, 0, 0, NO_ZONA}, //Punto3
            { 0, 0, 0, NO_ZONA}, //Punto4
            { 0, 0, 0, NO_ZONA}, //Punto5
            { 0, 0, 0, NO_ZONA}, //Punto6
            { 0, 0, 0, NO_ZONA}, //Punto7
            { 0, 0, 0, NO_ZONA}, //Punto8
            { 0, 0, 0, NO_ZONA}, //Punto9
            { 0, 0, 0, NO_ZONA}, //Punto10
            { 0, 0, 0, NO_ZONA}, //Punto11
            { 0, 0, 0, NO_ZONA}, //Punto12
            { 0, 0, 0, NO_ZONA}, //Punto13
            { 0, 0, 0, NO_ZONA} //Punto14
        },
        //Torso
        {
            /*isUsed, imgX, imgY, imgOff, imgOn, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoomHP1Off, imgZoomHP2Off, imgZoomHP3Off, imgZoomHP4Off, imgZoomHPOff_X, imgZoomHPOff_Y, imgZoomHP1On, imgZoomHP2On, imgZoomHP3On, imgZoomHP4On, imgZoomHPOn_X, imgZoomHPOn_Y, imgBodyHP1, imgBodyHP2, imgBodyHP3, imgBodyHP4, imgBodyHP_X, imgBodyHP_Y, ZoneName */
            { 1, 342, 208, PliegueAxilarIzquierdo}, 			//Punto0
            { 1, 275, 208, PliegueAxilarDerecho}, 			//Punto1
            { 1, 330, 240, IntrapectoralIzquierdo}, 			//Punto2
            { 1, 290, 240, IntrapectoralDerecho}, 			//Punto3
            { 1, 330, 265, AbdominalSupraumbricalIzquierdo}, 	//Punto4
            { 1, 310, 265, AbdominalSupraumbricalCentral}, 	//Punto5
            { 1, 290, 265, AbdominalSupraumbricalDerecho}, 	//Punto6
            { 1, 330, 290, AbdominalInfraumbricalIzquierdo}, 	//Punto7
            { 1, 310, 290, AbdominalInfraumbricalCentral}, 	//Punto8
            { 1, 290, 290, AbdominalInfraumbricalDerecho}, 	//Punto9
            { 1, 310, 310, Pubis}, 							//Punto10
            { 1, 343, 290, CaderaIzquierdo}, 					//Punto11
            { 1, 277, 290, CaderaDerecho}, 					//Punto12
            { 0, 330, 230, SenoIzquierdo}, 					//Punto13
            { 0, 290, 230, SenoDerecho} 						//Punto14
        },
        //Piernas
        {
            /*isUsed, imgX, imgY, imgOff, imgOn, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoomHP1Off, imgZoomHP2Off, imgZoomHP3Off, imgZoomHP4Off, imgZoomHPOff_X, imgZoomHPOff_Y, imgZoomHP1On, imgZoomHP2On, imgZoomHP3On, imgZoomHP4On, imgZoomHPOn_X, imgZoomHPOn_Y, imgBodyHP1, imgBodyHP2, imgBodyHP3, imgBodyHP4, imgBodyHP_X, imgBodyHP_Y, ZoneName */
            { 1, 342, 335, TrocantereaIzquierdo}, 		//Punto0
            { 1, 277, 335, TrocantereaDerecho}, 			//Punto1
            { 1, 325, 350, CaraInternaMusloIzquierdo}, 	//Punto2
            { 1, 295, 350, CaraInternaMusloDerecho}, 		//Punto3
            { 1, 330, 383, SuperioRodillaIzquierda}, 		//Punto4
            { 1, 290, 383, SuperiorRodillaDerecha}, 		//Punto5
            { 1, 320, 395, IntRodillaIzquierda}, 			//Punto6
            { 1, 300, 395, IntRodillaDerecha}, 			//Punto7
            { 0, 0, 0, NO_ZONA}, //Punto8
            { 0, 0, 0, NO_ZONA}, //Punto9
            { 0, 0, 0, NO_ZONA}, //Punto10
            { 0, 0, 0, NO_ZONA}, //Punto11
            { 0, 0, 0, NO_ZONA}, //Punto12
            { 0, 0, 0, NO_ZONA}, //Punto13
            { 0, 0, 0, NO_ZONA} //Punto14
        },
        //Espalda
        {
            /*isUsed, imgX, imgY, imgOff, imgOn, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoomHP1Off, imgZoomHP2Off, imgZoomHP3Off, imgZoomHP4Off, imgZoomHPOff_X, imgZoomHPOff_Y, imgZoomHP1On, imgZoomHP2On, imgZoomHP3On, imgZoomHP4On, imgZoomHPOn_X, imgZoomHPOn_Y, imgBodyHP1, imgBodyHP2, imgBodyHP3, imgBodyHP4, imgBodyHP_X, imgBodyHP_Y, ZoneName */
            { 1, 441, 222, SupraescapularIzquierda}, 	//Punto0
            { 1, 475, 222, SupraescapularDerecha}, 	//Punto1
            { 1, 441, 245, InfraescapularIzquierda}, 	//Punto2
            { 1, 475, 245, InfraescapularDerecha}, 	//Punto3
            { 1, 441, 274, FlancoIzquierdo}, 			//Punto4
            { 1, 475, 274, FlancoDerecho}, 			//Punto5
            { 0, 0, 0, NO_ZONA}, //Punto6
            { 0, 0, 0, NO_ZONA}, //Punto7
            { 0, 0, 0, NO_ZONA}, //Punto8
            { 0, 0, 0, NO_ZONA}, //Punto9
            { 0, 0, 0, NO_ZONA}, //Punto10
            { 0, 0, 0, NO_ZONA}, //Punto11
            { 0, 0, 0, NO_ZONA}, //Punto12
            { 0, 0, 0, NO_ZONA}, //Punto13
            { 0, 0, 0, NO_ZONA} //Punto14
        },
        //Piernas muslo
        {
            /*isUsed, imgX, imgY, imgOff, imgOn, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoomHP1Off, imgZoomHP2Off, imgZoomHP3Off, imgZoomHP4Off, imgZoomHPOff_X, imgZoomHPOff_Y, imgZoomHP1On, imgZoomHP2On, imgZoomHP3On, imgZoomHP4On, imgZoomHPOn_X, imgZoomHPOn_Y, imgBodyHP1, imgBodyHP2, imgBodyHP3, imgBodyHP4, imgBodyHP_X, imgBodyHP_Y, ZoneName */
            { 1, 438, 321, GluteoIzquierdo}, 			//Punto0
            { 1, 480, 321, GluteoDerecho}, 			//Punto1
            { 1, 438, 347, SubgluteoIzquierdo}, 		//Punto2
            { 1, 480, 347, SubgluteoDerecho}, 		//Punto3
            { 1, 438, 368, MusloPosteriorIzquierdo}, 	//Punto4
            { 1, 480, 368, MusloPosterioDerecho}, 	//Punto5
            { 0, 0, 0, NO_ZONA}, //Punto6
            { 0, 0, 0, NO_ZONA}, //Punto7
            { 0, 0, 0, NO_ZONA}, //Punto8
            { 0, 0, 0, NO_ZONA}, //Punto9
            { 0, 0, 0, NO_ZONA}, //Punto10
            { 0, 0, 0, NO_ZONA}, //Punto11
            { 0, 0, 0, NO_ZONA}, //Punto12
            { 0, 0, 0, NO_ZONA}, //Punto13
            { 0, 0, 0, NO_ZONA} //Punto14
        },
        //Brazos
        {
            /*isUsed, imgX, imgY, imgOff, imgOn, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoomHP1Off, imgZoomHP2Off, imgZoomHP3Off, imgZoomHP4Off, imgZoomHPOff_X, imgZoomHPOff_Y, imgZoomHP1On, imgZoomHP2On, imgZoomHP3On, imgZoomHP4On, imgZoomHPOn_X, imgZoomHPOn_Y, imgBodyHP1, imgBodyHP2, imgBodyHP3, imgBodyHP4, imgBodyHP_X, imgBodyHP_Y, ZoneName */
            { 1, 412, 237, BrazoIzquierdo}, 	//Punto0
            { 1, 505, 237, BrazoDerecho}, 	//Punto1
            { 0, 0, 0, NO_ZONA}, //Punto2
            { 0, 0, 0, NO_ZONA}, //Punto3
            { 0, 0, 0, NO_ZONA}, //Punto4
            { 0, 0, 0, NO_ZONA}, //Punto5
            { 0, 0, 0, NO_ZONA}, //Punto6
            { 0, 0, 0, NO_ZONA}, //Punto7
            { 0, 0, 0, NO_ZONA}, //Punto8
            { 0, 0, 0, NO_ZONA}, //Punto9
            { 0, 0, 0, NO_ZONA}, //Punto10
            { 0, 0, 0, NO_ZONA}, //Punto11
            { 0, 0, 0, NO_ZONA}, //Punto12
            { 0, 0, 0, NO_ZONA}, //Punto13
            { 0, 0, 0, NO_ZONA} //Punto14
        },
        //Cuello
        {
            /*isUsed, imgX, imgY, imgOff, imgOn, imgTS, TsRectX, TsRectY, TsRectW, TsRectH, imgZoomHP1Off, imgZoomHP2Off, imgZoomHP3Off, imgZoomHP4Off, imgZoomHPOff_X, imgZoomHPOff_Y, imgZoomHP1On, imgZoomHP2On, imgZoomHP3On, imgZoomHP4On, imgZoomHPOn_X, imgZoomHPOn_Y, imgBodyHP1, imgBodyHP2, imgBodyHP3, imgBodyHP4, imgBodyHP_X, imgBodyHP_Y, ZoneName */
            { 1, 310, 170, PapadaCentral}, 			//Punto0
            { 1, 320, 163, PapadaLateralIzquierdo}, 	//Punto1
            { 1, 300, 163, PapadaLateralDerecho}, 	//Punto2
            { 0, 0, 0, NO_ZONA}, //Punto3
            { 0, 0, 0, NO_ZONA}, //Punto4
            { 0, 0, 0, NO_ZONA}, //Punto5
            { 0, 0, 0, NO_ZONA}, //Punto6
            { 0, 0, 0, NO_ZONA}, //Punto7
            { 0, 0, 0, NO_ZONA}, //Punto8
            { 0, 0, 0, NO_ZONA}, //Punto9
            { 0, 0, 0, NO_ZONA}, //Punto10
            { 0, 0, 0, NO_ZONA}, //Punto11
            { 0, 0, 0, NO_ZONA}, //Punto12
            { 0, 0, 0, NO_ZONA}, //Punto13
            { 0, 0, 0, NO_ZONA} //Punto14
        },
    }
};

///*Pantalla de Idiomas*/
//const uint32 APP_GUI_LANG_SW_WIDGET_LANG_LIST[App_GUI_Different_Languages]=
//{
//		APP_GUI_NUM_WIDGETS, SwLanFrances, SwLanCastellano, SwLanIngles, SwLanItaliano, SwLanAleman,
//		 SwLanPolaco, SwLanRuso, SwLanPortugues, SwLanChino, SwLanJapones, SwLanCoreano
//};

///*Pantalla de SAT*/
//const uint32 APP_GUI_SAT_NUMVWR_WIDGET_LIST[APP_GUI_SAT_MAX_NUMVWR] =
//{
//		NumVwr1, NumVwr2, NumVwr3, NumVwr4, NumVwr5, NumVwr6, NumVwr7,
//		NumVwr8, NumVwr9, NumVwr10, NumVwr11, NumVwr12, NumVwr13, NumVwr14,
//		NumVwr15, NumVwr16, NumVwr17, NumVwr18, NumVwr19, NumVwr20, NumVwr21,
//		NumVwr22, NumVwr23, NumVwr24, NumVwr25, NumVwr26, NumVwr27, NumVwr28
//};

///*Pantalla de Fatiga*/
//const uint32 APP_GUI_FAT_STATUS_4_HP_WIDGETS[APP_GUI_MAXNUM_HP] =
//{
//		imgStep4statusHP1, imgStep4statusHP2, imgStep4statusHP3, imgStep4statusHP4
//};

//const uint32 APP_GUI_FAT_STATUS_5_HP_WIDGETS[APP_GUI_MAXNUM_HP] =
//{
//		imgStep5statusHP1, imgStep5statusHP2, imgStep5statusHP3, imgStep5statusHP4
//};

//const uint32 APP_GUI_FAT_VALUE_STATUS[EXP_UC_FATIGUE_MAX_VALUE_STATUS] =
//{
//		c047_FondoNumVwrBlanco, c462_FondoNumVwrErrorVerde, c463_FondoNumVwrErrorRojo, c464_FondoNumVwrErrorRojoNegro
//};

//const uint32 APP_GUI_FAT_DIFF_NUM_VWR_VALUES[FatMaxValues] =
//{
//		NumVwrVacuumHP1, NumVwrVacuumHP2, NumVwrVacuumHP3, NumVwrVacuumHP4,
//		NumVwrCaudalRetornoHP1, NumVwrCaudalRetornoHP2, NumVwrCaudalRetornoHP3, NumVwrCaudalRetornoHP4,
//		NumVwrRth, NumVwrTempRetorno, NumVwrCaudalRetorno, NumVwrTempBomba, NumVwrTempAmb, NumVwrVtobera, NumVwrCPI,
//		NumVwrErrFatiga1, NumVwrErrFatiga2,NumVwrErrFatiga3, NumVwrErrFatiga4, NumVwrErrFatiga5
//};

tAppGUIPopUpDisplayed APP_GUI_POPUP_DISPLAYED_MAP[APP_GUI_POPUP_DISPLAYED_MAP_NUM] =
{
    { PopupInitScrAvisos, false },  // Use only this value for the warning popup in all screens
    { PopUpTime, false },
    { PopUpTstVac, false },
    { PopUpTstVacSmall, false },
    { PopUpRFID, false },
    { PopUpRecomm, false },
    { PopupTrtScrAvisos, false },
    { PopupCalcScrAvisos, false },
    { PopupCfgScrAvisos, false },
    { PopupLanScrAvisos, false }
};

////V7790
//const uint32 APP_GUI_GPRS_COVERAGE_WID_BY_SCREEN[APP_GUI_NUM_SCREENS] =
//{
//	/*	Carga, Inicio	Trt		Calc	Config	Idiomas		SAT		FATIGA*/
//		APP_GUI_NUM_WIDGETS, imgInitGPRScoverage, imgTrtGPRScoverage,
//		APP_GUI_NUM_WIDGETS, imgCfgGPRScoverage, APP_GUI_NUM_WIDGETS,
//		APP_GUI_NUM_WIDGETS, APP_GUI_NUM_WIDGETS
//};
////V7790
///* Número de capas por pantalla */
//const uint8 APP_GUI_SCREEN_N_LAYERS[APP_GUI_NUM_SCREENS] =
//{
//	/*	Carga	Inicio	Trt		Calc	Config	Idiomas		SAT		FATIGA*/
//		2, 		4, 		10, 	5,		5, 		4, 			6,		3
//};

///*
//* AÑADIR ENLACE AL EXCEL DONDE EXPLICA EL SIGNIICADO DE CADA PARAMETRO
//*/
//const uint32 APP_GUI_INTERFACE_WIDGETS[APP_GUI_NUM_WIDGETS][APP_GUI_WIDGETS_FEATURES] =
//{
////PANTALLA DE CARGA
//		{ 		ImgLoadScrBckGnd,APP_GUI_LOAD_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER0,
//				a001_FondoLogoCooltechDefine,APP_GUI_IMG_FONDO_CARGA,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgLoadAnim1,APP_GUI_LOAD_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				a002_CargaLogotipo1,APP_GUI_IMG_CIRCULO_CARGA_1,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgLoadAnim2,APP_GUI_LOAD_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				a003_CargaLogotipo2,APP_GUI_IMG_CIRCULO_CARGA_2,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgLoadAnim3,APP_GUI_LOAD_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				a004_CargaLogotipo3,APP_GUI_IMG_CIRCULO_CARGA_3,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgLoadAnim4,APP_GUI_LOAD_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				a005_CargaLogotipo4,APP_GUI_IMG_CIRCULO_CARGA_4,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgLoadAnim5,APP_GUI_LOAD_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				a006_CargaLogotipo5,APP_GUI_IMG_CIRCULO_CARGA_5,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgLoadAnim6,APP_GUI_LOAD_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				a007_CargaLogotipo6,APP_GUI_IMG_CIRCULO_CARGA_6,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0	},
//		{		imgLoadAnim7,APP_GUI_LOAD_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				a008_CargaLogotipo7,APP_GUI_IMG_CIRCULO_CARGA_7,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgLoadAnim8,APP_GUI_LOAD_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				a009_CargaLogotipo8,APP_GUI_IMG_CIRCULO_CARGA_8,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0	},
							
////PANTALLA DE INICIO
//		{		imgInitScrBckGnd,APP_GUI_INIT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER0,
//				b001_FondoLogoSiluetasHombreMujer,APP_GUI_IMG_FONDO_SILUETA_HOMBRE_MUJER,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ButSelectWoman,APP_GUI_INIT_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER1,
//				b002_BotonFemeninoPress,b003_BotonFemeninoRls,APP_GUI_BUT_FEMENINO_TSR_COORD,164,149,
//				CBKdummy,CBKbutGenderSelect,CBKdummy,APP_GUI_BUT_FEMENINO_PRS_COORD,APP_GUI_BUT_FEMENINO_RLS_COORD,b004_TscBotonFemenino,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButSelectMan,APP_GUI_INIT_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER1,
//				b005_BotonMasculinoPress,b006_BotonMasculinoRls,APP_GUI_BUT_MASCULINO_TSR_COORD,166,149,
//				CBKdummy,CBKbutGenderSelect,CBKdummy,APP_GUI_BUT_MASCULINO_PRS_COORD,APP_GUI_BUT_MASCULINO_RLS_COORD,b007_TscBotonMasculino,
//				0,0,0,0,0,0,0,0,0		},
//		{		imgInitGPRScoverage,APP_GUI_INIT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER1,
//				c610_GPRS_no_coverage,APP_GUI_INIT_IMG_GPRS_COVERAGE_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},	//V7790
//		//Menú principal
//		{		butInitScrShowMainMenu,APP_GUI_INIT_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER1,
//				b008_SwMenuRls,b008_SwMenuRls,APP_GUI_BUT_MENU_GLOBAL_TSR_COORD,97,57,
//				CBKdummy,CBKbutMainMenuShow,CBKdummy,APP_GUI_BUT_MENU_GLOBAL_PRS_COORD,APP_GUI_BUT_MENU_GLOBAL_RLS_COORD,b009_TscSwMenuRls,
//				0,0,0,0,0,0,0,0,0		},
//		{		butInitScrHideMainMenu,APP_GUI_INIT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				b010_SwMenuPress,b010_SwMenuPress,APP_GUI_BUT_MENU_GLOBAL_2_TSR_COORD,47,48,
//				CBKdummy,CBKbutMainMenuHide,CBKdummy,APP_GUI_BUT_MENU_GLOBAL_2_PRS_COORD,APP_GUI_BUT_MENU_GLOBAL_2_RLS_COORD,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		imgInitScrHome,APP_GUI_INIT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				b012_BotonHomeMarcaAgua,APP_GUI_IMG_BOTON_HOME_BLOQUEADO,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		butInitScrCfg,APP_GUI_INIT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER3,
//				b016_BotonConfigPress,b017_BotonConfigRls,APP_GUI_BUT_CONFIG_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutConfig,CBKdummy,APP_GUI_BUT_CONFIG_GLOBAL_PRS_COORD,APP_GUI_BUT_CONFIG_GLOBAL_RLS_COORD,b019_TscBotonConfig,
//				0,0,0,0,0,0,0,0,0		},
//		{		butInitScrCalc,APP_GUI_INIT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER3,
//				b021_BotonCalculadoraPress,b022_BotonCalculadoraRls,APP_GUI_BUT_CALCULADORA_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutCalc,CBKdummy,APP_GUI_BUT_CALCULADORA_GLOBAL_PRS_COORD,APP_GUI_BUT_CALCULADORA_GLOBAL_RLS_COORD,b023_TscBotonCalculadora,
//				0,0,0,0,0,0,0,0,0		},
//		{		butInitScrData,APP_GUI_INIT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER3,
//				b025_BotonIdiomasPress,b024_BotonIdiomasMarcaAgua/*b026_BotonIdiomasRls*/,APP_GUI_BUT_IDIOMAS_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutData,CBKdummy,APP_GUI_BUT_IDIOMAS_GLOBAL_PRS_COORD,APP_GUI_BUT_IDIOMAS_GLOBAL_RLS_COORD,b027_TscBotonIdiomas,
//				0,0,0,0,0,0,0,0,0		},
		
//		//avisos
						
//		{		SwInitScrAvisos,APP_GUI_INIT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				b029_BotonAvisosPress,b030_BotonAvisosRls,b029_BotonAvisosPress,b030_BotonAvisosRls,
//				APP_GUI_BUT_AVISOS_GLOBAL_TSR_COORD, 62,62, CBKbutWarningOn, CBKbutWarningOff,APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD,
//				APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD,APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD,APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD, b031_TscBotonAvisos,
//				0,0,0,0},
//		{		ImgInitScrNotificacion,APP_GUI_INIT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				b032_ImgNotificacion,APP_GUI_IMG_AVISO_PENDIENTE_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//		{		PopupInitScrAvisos,APP_GUI_INIT_SCREEN, APP_GUI_POPUP_ID ,1,0,0, APP_GUI_LAYER1,
//				0, 0, APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM,0,APP_GUI_POPUP_DISABLE_ALL_WIDGETS,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//		{		imgPopUpInitScrAvisoBckGND,APP_GUI_INIT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER1,
//				c420_Menualarmasfondo,APP_GUI_IMG_AVISO_POPUP_BCKGND_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpInitScrAvisoNivelAguaBajo,APP_GUI_INIT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				c425_Menualarmasinaguapress,APP_GUI_IMG_AVISO_POPUP_NIVEL_AGUA_BAJO_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpInitScrAvisoNivelAguaMedio,APP_GUI_INIT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				c424_Menualarmaaguamitadpress,APP_GUI_IMG_AVISO_POPUP_NIVEL_AGUA_MEDIO_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpInitScrAvisoTempAmb,APP_GUI_INIT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				c421_Menualarmatemppress,APP_GUI_IMG_AVISO_POPUP_TEMP_AMB_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpInitScrAvisoRFID,APP_GUI_INIT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				c423_Menualarmarfidpress,APP_GUI_IMG_AVISO_POPUP_RFID_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpInitScrAvisoRTC,APP_GUI_INIT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				c426_Menualarmatiempopress,APP_GUI_IMG_AVISO_POPUP_RTC_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpInitScrAvisoFiltroAire,APP_GUI_INIT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				c422_Menualarmafiltropress,APP_GUI_IMG_AVISO_POPUP_FILTRO_AIRE_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//// PANTALLA DE TRATAMIENTO
								
//		{		imgTrtScrBckGnd,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER0,
//				c001_FondoLogo,APP_GUI_IMG_FONDO_PANTALLA_TRT,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{	 	imgFullBodyAndZoom,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c002_SiluetaMujerFrenteEspalda,APP_GUI_IMG_SILUETA_MUJER,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgTrtGPRScoverage,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER1,
//				c610_GPRS_no_coverage,APP_GUI_TRT_IMG_GPRS_COVERAGE_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},	//V7790
//		//Fondos de los paneles de control de los HPs
//		{	 	imgCtrlPnlBckGndHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				c004_MenuTrtHP1,APP_GUI_BUT_MENU_HP_1_RLS_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		{	 	imgCtrlPnlBckGndHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				c012_MenuTrtHP2,APP_GUI_BUT_MENU_HP_2_RLS_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		{	 	imgCtrlPnlBckGndHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				c020_MenuTrtHP3,APP_GUI_BUT_MENU_HP_3_RLS_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		{	 	imgCtrlPnlBckGndHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				c028_MenuTrtHP4,APP_GUI_BUT_MENU_HP_4_RLS_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				
//		//Colores fondos de los paneles de control de los HPs
//		{	 	ImgColourCtrlPnlBckGndHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				c005_MenuTrtHP1_Aro2,APP_GUI_IMG_COLOR_MENU_HP_1,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		{	 	ImgColourCtrlPnlBckGndHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				c013_MenuTrtHP2_Aro2,APP_GUI_IMG_COLOR_MENU_HP_2,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		{	 	ImgColourCtrlPnlBckGndHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				c021_MenuTrtHP3_Aro2,APP_GUI_IMG_COLOR_MENU_HP_3,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		{	 	ImgColourCtrlPnlBckGndHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER1,
//				c029_MenuTrtHP4_Aro2,APP_GUI_IMG_COLOR_MENU_HP_4,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						
//		//Indicador estado HP cuando activado. El fondo contiene la barra de desactivados
//		{		ImgCtrlPnlRFIDblinkHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//				c183_IndicadorRFIDHP1Off,APP_GUI_IMG_INDICADOR_RFID_HP_1,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgCtrlPnlRFIDblinkHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//				c187_IndicadorRFIDHP2Off,APP_GUI_IMG_INDICADOR_RFID_HP_2,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgCtrlPnlRFIDblinkHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//				c191_IndicadorRFIDHP3Off,APP_GUI_IMG_INDICADOR_RFID_HP_3,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgCtrlPnlRFIDblinkHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//				c195_IndicadorRFIDHP4Off,APP_GUI_IMG_INDICADOR_RFID_HP_4,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgCtrlPnlPulBlinkHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//				c184_IndicadorBotonHP1Off,APP_GUI_IMG_INDICADOR_BOTON_HP_1,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgCtrlPnlPulBlinkHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//				c188_IndicadorBotonHP2Off,APP_GUI_IMG_INDICADOR_BOTON_HP_2,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgCtrlPnlPulBlinkHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//				c192_IndicadorBotonHP3Off,APP_GUI_IMG_INDICADOR_BOTON_HP_3,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgCtrlPnlPulBlinkHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//				c196_IndicadorBotonHP4Off,APP_GUI_IMG_INDICADOR_BOTON_HP_4,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgCtrlPnlVacBlinkHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//				c185_IndicadorVacHP1Off,APP_GUI_IMG_INDICADOR_VAC_HP_1,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgCtrlPnlVacBlinkHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//				c189_IndicadorVacHP2Off,APP_GUI_IMG_INDICADOR_VAC_HP_2,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgCtrlPnlVacBlinkHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//			   	c193_IndicadorVacHP3Off,APP_GUI_IMG_INDICADOR_VAC_HP_3,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgCtrlPnlVacBlinkHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//			   	c197_IndicadorVacHP4Off,APP_GUI_IMG_INDICADOR_VAC_HP_4,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgCtrlPnlCoolingBlinkHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//				c186_IndicadorFrioHP1Off,APP_GUI_IMG_INDICADOR_FRIO_HP_1,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgCtrlPnlCoolingBlinkHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//				c190_IndicadorFrioHP2Off,APP_GUI_IMG_INDICADOR_FRIO_HP_2,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgCtrlPnlCoolingBlinkHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//				c194_IndicadorFrioHP3Off,APP_GUI_IMG_INDICADOR_FRIO_HP_3,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgCtrlPnlCoolingBlinkHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER2,
//				c198_IndicadorFrioHP4Off,APP_GUI_IMG_INDICADOR_FRIO_HP_4,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//		//Botones del panel de control de PLAY y Test Vacum
//		{		ButCtrlPnlPlayHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				c036_BotonPlayPress,c038_BotonPlayMarcaAgua,APP_GUI_BUT_PLAY_HP_1_TSR_COORD,55, 55,
//				CBKdummy,CBKbutCtrlPnlPlay,CBKdummy,APP_GUI_BUT_PLAY_HP_1_PRS_COORD,APP_GUI_BUT_PLAY_HP_1_RLS_COORD,c039_TscBotonPlay,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButCtrlPnlPlayHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				c036_BotonPlayPress,c038_BotonPlayMarcaAgua,APP_GUI_BUT_PLAY_HP_2_TSR_COORD,55, 55,
//				CBKdummy,CBKbutCtrlPnlPlay,CBKdummy,APP_GUI_BUT_PLAY_HP_2_PRS_COORD,APP_GUI_BUT_PLAY_HP_2_RLS_COORD,c039_TscBotonPlay,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButCtrlPnlPlayHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				c036_BotonPlayPress,c038_BotonPlayMarcaAgua,APP_GUI_BUT_PLAY_HP_3_TSR_COORD,55, 55,
//				CBKdummy,CBKbutCtrlPnlPlay,CBKdummy,APP_GUI_BUT_PLAY_HP_3_PRS_COORD,APP_GUI_BUT_PLAY_HP_3_RLS_COORD,c039_TscBotonPlay,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButCtrlPnlPlayHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				c036_BotonPlayPress,c038_BotonPlayMarcaAgua,APP_GUI_BUT_PLAY_HP_4_TSR_COORD,55, 55,
//				CBKdummy,CBKbutCtrlPnlPlay,CBKdummy,APP_GUI_BUT_PLAY_HP_4_PRS_COORD,APP_GUI_BUT_PLAY_HP_4_RLS_COORD,c039_TscBotonPlay,
//				0,0,0,0,0,0,0,0,0		},
				

//		{		SwCtrlPnlTstVacHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c040_BotonVacuum2PressLeft,c042_BotonVacuum3MarcaAguaLeft,c040_BotonVacuum2PressLeft,c041_BotonVacuum2RlsLeft,
//				APP_GUI_BUT_VAC_HP_1_PRS_COORD, 55, 55, CBKswCtrlPnlTstVacOn, CBKswCtrlPnlTstVacOff, APP_GUI_BUT_VAC_HP_1_PRS_COORD, APP_GUI_BUT_VAC_HP_1_PRS_COORD, APP_GUI_BUT_VAC_HP_1_PRS_COORD, APP_GUI_BUT_VAC_HP_1_PRS_COORD, c043_TscBotonVacuum },
//		{		SwCtrlPnlTstVacHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c040_BotonVacuum2PressRight,c042_BotonVacuum3MarcaAguaRight,c040_BotonVacuum2PressRight,c041_BotonVacuum2RlsRight,
//				APP_GUI_BUT_VAC_HP_2_PRS_COORD, 55, 55, CBKswCtrlPnlTstVacOn, CBKswCtrlPnlTstVacOff,APP_GUI_BUT_VAC_HP_2_PRS_COORD,APP_GUI_BUT_VAC_HP_2_PRS_COORD,APP_GUI_BUT_VAC_HP_2_PRS_COORD,APP_GUI_BUT_VAC_HP_2_PRS_COORD, c043_TscBotonVacuum },
//		{		SwCtrlPnlTstVacHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c040_BotonVacuum2PressLeft,c042_BotonVacuum3MarcaAguaLeft,c040_BotonVacuum2PressLeft,c041_BotonVacuum2RlsLeft,
//				APP_GUI_BUT_VAC_HP_3_PRS_COORD, 55, 55, CBKswCtrlPnlTstVacOn, CBKswCtrlPnlTstVacOff, APP_GUI_BUT_VAC_HP_3_PRS_COORD,APP_GUI_BUT_VAC_HP_3_PRS_COORD,APP_GUI_BUT_VAC_HP_3_PRS_COORD,APP_GUI_BUT_VAC_HP_3_PRS_COORD, c043_TscBotonVacuum },
//		{		SwCtrlPnlTstVacHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c040_BotonVacuum2PressRight,c042_BotonVacuum3MarcaAguaRight,c040_BotonVacuum2PressRight,c041_BotonVacuum2RlsRight,
//				APP_GUI_BUT_VAC_HP_4_PRS_COORD, 55, 55, CBKswCtrlPnlTstVacOn, CBKswCtrlPnlTstVacOff, APP_GUI_BUT_VAC_HP_4_PRS_COORD,APP_GUI_BUT_VAC_HP_4_PRS_COORD,APP_GUI_BUT_VAC_HP_4_PRS_COORD,APP_GUI_BUT_VAC_HP_4_PRS_COORD, c043_TscBotonVacuum },
				
////		{		butCtrlPnlTstVacHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
////				c040_BotonVacuum2PressLeft,c041_BotonVacuum2RlsLeft,APP_GUI_BUT_VAC_HP_1_TSR_COORD,55, 55,
////				CBKdummy,CBKbutCtrlPnlTstVac,CBKdummy,APP_GUI_BUT_VAC_HP_1_PRS_COORD,APP_GUI_BUT_VAC_HP_1_RLS_COORD,c043_TscBotonVacuum,
////				0,0,0,0,0,0,0,0,0		},
////		{		butCtrlPnlTstVacHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
////				c040_BotonVacuum2PressRight,c041_BotonVacuum2RlsRight,APP_GUI_BUT_VAC_HP_2_TSR_COORD,55, 55,
////				CBKdummy,CBKbutCtrlPnlTstVac,CBKdummy,APP_GUI_BUT_VAC_HP_2_PRS_COORD,APP_GUI_BUT_VAC_HP_2_RLS_COORD,c043_TscBotonVacuum,
////				0,0,0,0,0,0,0,0,0		},
////		{		butCtrlPnlTstVacHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
////				c040_BotonVacuum2PressLeft,c041_BotonVacuum2RlsLeft,APP_GUI_BUT_VAC_HP_3_TSR_COORD,55, 55,
////				CBKdummy,CBKbutCtrlPnlTstVac,CBKdummy,APP_GUI_BUT_VAC_HP_3_PRS_COORD,APP_GUI_BUT_VAC_HP_3_RLS_COORD,c043_TscBotonVacuum,
////				0,0,0,0,0,0,0,0,0		},
////		{		butCtrlPnlTstVacHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
////				c040_BotonVacuum2PressRight,c041_BotonVacuum2RlsRight,APP_GUI_BUT_VAC_HP_4_TSR_COORD,55, 55,
////				CBKdummy,CBKbutCtrlPnlTstVac,CBKdummy,APP_GUI_BUT_VAC_HP_4_PRS_COORD,APP_GUI_BUT_VAC_HP_4_RLS_COORD,c043_TscBotonVacuum,
////				0,0,0,0,0,0,0,0,0		},
				
//		//Switch de indicador de tratamiento AUTO o MANUAL
//		{		ButSwtchModeAutoManualHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c045_BotonAutoRls,c045_BotonAutoRls,APP_GUI_BUT_TRT_AUTO_HP1_TSR_COORD,65,35,
//				CBKbutTRTmodeAutoManual,CBKdummy,CBKdummy,APP_GUI_BUT_TRT_AUTO_HP1_PRS_COORD,APP_GUI_BUT_TRT_AUTO_HP1_RLS_COORD,c044_B_TscBotonAuto,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButSwtchModeAutoManualHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c045_BotonAutoRls,c045_BotonAutoRls,APP_GUI_BUT_TRT_AUTO_HP2_TSR_COORD,65,35,
//				CBKbutTRTmodeAutoManual,CBKdummy,CBKdummy,APP_GUI_BUT_TRT_AUTO_HP2_PRS_COORD,APP_GUI_BUT_TRT_AUTO_HP2_RLS_COORD,c044_B_TscBotonAuto,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButSwtchModeAutoManualHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c045_BotonAutoRls,c045_BotonAutoRls,APP_GUI_BUT_TRT_AUTO_HP3_TSR_COORD,65,35,
//				CBKbutTRTmodeAutoManual,CBKdummy,CBKdummy,APP_GUI_BUT_TRT_AUTO_HP3_PRS_COORD,APP_GUI_BUT_TRT_AUTO_HP3_RLS_COORD,c044_B_TscBotonAuto,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButSwtchModeAutoManualHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c045_BotonAutoRls,c045_BotonAutoRls,APP_GUI_BUT_TRT_AUTO_HP4_TSR_COORD,65,35,
//				CBKbutTRTmodeAutoManual,CBKdummy,CBKdummy,APP_GUI_BUT_TRT_AUTO_HP4_PRS_COORD,APP_GUI_BUT_TRT_AUTO_HP4_RLS_COORD,c044_B_TscBotonAuto,
//				0,0,0,0,0,0,0,0,0		},
		
//		//Visores de tiempo restante de trt
//		{		NumVwrTimeHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				APP_GUI_LAYER3,5,3,16,35,1,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_1,118,57,c047_FondoTemporizador,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c065_CaracterNegativo,c062_CaracterDosPuntos	},
//		{		NumVwrTimeHP2, APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				APP_GUI_LAYER3,5,3,16,35,1,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_2,118,57,c047_FondoTemporizador,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c065_CaracterNegativo,c062_CaracterDosPuntos	},
//		{		NumVwrTimeHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				APP_GUI_LAYER3,5,3,16,35,1,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_3,118,57,c047_FondoTemporizador,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c065_CaracterNegativo,c062_CaracterDosPuntos	},
//		{		NumVwrTimeHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				APP_GUI_LAYER3,5,3,16,35,1,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_4,118,57,c047_FondoTemporizador,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c065_CaracterNegativo,c062_CaracterDosPuntos	},
		
//		{		ButSelectTimeHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER4,
//				c048_RelojTemporizadorPress,c050_RelojTemporizadorMarcaAgua,APP_GUI_BUT_CLK_HP_1_TSR_COORD,129,45,
//				CBKdummy,CBKbutSelectTime,CBKdummy,APP_GUI_BUT_CLK_HP_1_PRS_COORD,APP_GUI_BUT_CLK_HP_1_RLS_COORD,c051_TscrRelojTemporizador,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButSelectTimeHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER4,
//				c048_RelojTemporizadorPress,c050_RelojTemporizadorMarcaAgua,APP_GUI_BUT_CLK_HP_2_TSR_COORD,129,45,
//				CBKdummy,CBKbutSelectTime,CBKdummy,APP_GUI_BUT_CLK_HP_2_PRS_COORD,APP_GUI_BUT_CLK_HP_2_RLS_COORD,c051_TscrRelojTemporizador,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButSelectTimeHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER4,
//				c048_RelojTemporizadorPress,c050_RelojTemporizadorMarcaAgua,APP_GUI_BUT_CLK_HP_3_TSR_COORD,129,45,
//				CBKdummy,CBKbutSelectTime,CBKdummy,APP_GUI_BUT_CLK_HP_3_PRS_COORD,APP_GUI_BUT_CLK_HP_3_RLS_COORD,c051_TscrRelojTemporizador,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButSelectTimeHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER4,
//				c048_RelojTemporizadorPress,c050_RelojTemporizadorMarcaAgua,APP_GUI_BUT_CLK_HP_4_TSR_COORD,129,45,
//				CBKdummy,CBKbutSelectTime,CBKdummy,APP_GUI_BUT_CLK_HP_4_PRS_COORD,APP_GUI_BUT_CLK_HP_4_RLS_COORD,c051_TscrRelojTemporizador,
//				0,0,0,0,0,0,0,0,0		},
				
//		{		ButVwrTemperatureHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER4,
//				c048_RelojTemporizadorPress,c050_RelojTemporizadorMarcaAgua,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_1,129,45,
//				CBKdummy,CBKbutTemperatureVwr,CBKdummy,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_1,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_1,c051_TscrRelojTemporizador,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButVwrTemperatureHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER4,
//				c048_RelojTemporizadorPress,c050_RelojTemporizadorMarcaAgua,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_2,129,45,
//				CBKdummy,CBKbutTemperatureVwr,CBKdummy,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_2,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_2,c051_TscrRelojTemporizador,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButVwrTemperatureHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER4,
//				c048_RelojTemporizadorPress,c050_RelojTemporizadorMarcaAgua,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_3,129,45,
//				CBKdummy,CBKbutTemperatureVwr,CBKdummy,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_3,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_3,c051_TscrRelojTemporizador,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButVwrTemperatureHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER4,
//				c048_RelojTemporizadorPress,c050_RelojTemporizadorMarcaAgua,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_4,129,45,
//				CBKdummy,CBKbutTemperatureVwr,CBKdummy,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_4,APP_GUI_NUM_FONDO_TEMPORIZADOR_HP_4,c051_TscrRelojTemporizador,
//				0,0,0,0,0,0,0,0,0		},
				
//		//Visor numerico para contabilizar resucciones
//		{		NumVwrResucctionCountHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				APP_GUI_LAYER3,2,0,6,11,1,APP_GUI_NUM_FONDO_CUENTA_RESUCCIONES_HP_1,20,29,c510_resuccionindicador,
//				c600_Number_0_ResucInd,c601_Number_1_ResucInd,c602_Number_2_ResucInd,c603_Number_3_ResucInd,c604_Number_4_ResucInd,
//				c605_Number_5_ResucInd,c606_Number_6_ResucInd,c607_Number_7_ResucInd,c608_Number_8_ResucInd,c609_Number_9_ResucInd,
//				c065_CaracterNegativo,c062_CaracterDosPuntos	},
//		{		NumVwrResucctionCountHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				APP_GUI_LAYER3,2,0,6,11,1,APP_GUI_NUM_FONDO_CUENTA_RESUCCIONES_HP_2,20,29,c510_resuccionindicador,
//				c600_Number_0_ResucInd,c601_Number_1_ResucInd,c602_Number_2_ResucInd,c603_Number_3_ResucInd,c604_Number_4_ResucInd,
//				c605_Number_5_ResucInd,c606_Number_6_ResucInd,c607_Number_7_ResucInd,c608_Number_8_ResucInd,c609_Number_9_ResucInd,
//				c065_CaracterNegativo,c062_CaracterDosPuntos	},
//		{		NumVwrResucctionCountHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				APP_GUI_LAYER3,2,0,6,11,1,APP_GUI_NUM_FONDO_CUENTA_RESUCCIONES_HP_3,20,29,c510_resuccionindicador,
//				c600_Number_0_ResucInd,c601_Number_1_ResucInd,c602_Number_2_ResucInd,c603_Number_3_ResucInd,c604_Number_4_ResucInd,
//				c605_Number_5_ResucInd,c606_Number_6_ResucInd,c607_Number_7_ResucInd,c608_Number_8_ResucInd,c609_Number_9_ResucInd,
//				c065_CaracterNegativo,c062_CaracterDosPuntos	},
//		{		NumVwrResucctionCountHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				APP_GUI_LAYER3,2,0,6,11,1,APP_GUI_NUM_FONDO_CUENTA_RESUCCIONES_HP_4,20,29,c510_resuccionindicador,
//				c600_Number_0_ResucInd,c601_Number_1_ResucInd,c602_Number_2_ResucInd,c603_Number_3_ResucInd,c604_Number_4_ResucInd,
//				c605_Number_5_ResucInd,c606_Number_6_ResucInd,c607_Number_7_ResucInd,c608_Number_8_ResucInd,c609_Number_9_ResucInd,
//				c065_CaracterNegativo,c062_CaracterDosPuntos	},
				
		
//		//Boton con la imagen e imagen con el texto del modelo
//		{		ImgModelTextHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				c233_ImgPixelBlanco,APP_GUI_IMG_TYPE_NAME_HP_1,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgModelTextHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				c233_ImgPixelBlanco,APP_GUI_IMG_TYPE_NAME_HP_2,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgModelTextHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				c233_ImgPixelBlanco,APP_GUI_IMG_TYPE_NAME_HP_3,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgModelTextHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				c233_ImgPixelBlanco,APP_GUI_IMG_TYPE_NAME_HP_4,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//		{		ButModelImageHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				c233_ImgPixelBlanco,c233_ImgPixelBlanco,APP_GUI_BUT_TYPE_HP_1_TSR_COORD,105,105,
//				CBKdummy,CBKbutModelImage,CBKdummy,APP_GUI_BUT_TYPE_HP_1_PRS_COORD,APP_GUI_BUT_TYPE_HP_1_RLS_COORD,c111_TscImgMan,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButModelImageHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				c233_ImgPixelBlanco,c233_ImgPixelBlanco,APP_GUI_BUT_TYPE_HP_2_TSR_COORD,105,105,
//				CBKdummy,CBKbutModelImage,CBKdummy,APP_GUI_BUT_TYPE_HP_2_PRS_COORD,APP_GUI_BUT_TYPE_HP_2_RLS_COORD,c111_TscImgMan,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButModelImageHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				c233_ImgPixelBlanco,c233_ImgPixelBlanco,APP_GUI_BUT_TYPE_HP_3_TSR_COORD,105,105,
//				CBKdummy,CBKbutModelImage,CBKdummy,APP_GUI_BUT_TYPE_HP_3_PRS_COORD,APP_GUI_BUT_TYPE_HP_3_RLS_COORD,c111_TscImgMan,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButModelImageHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				c233_ImgPixelBlanco,c233_ImgPixelBlanco,APP_GUI_BUT_TYPE_HP_4_TSR_COORD,105,105,
//				CBKdummy,CBKbutModelImage,CBKdummy,APP_GUI_BUT_TYPE_HP_4_PRS_COORD,APP_GUI_BUT_TYPE_HP_4_RLS_COORD,c111_TscImgMan,
//				0,0,0,0,0,0,0,0,0		},
				
//		//Botonoes de recogida y despliegue del panel de control
//		{		ButHideControlPanelHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER1,
//				c202_BotonGuardarMenuLeftPress,c203_BotonGuardarMenuLeftRls,APP_GUI_BUT_MENU_TRT_HP_1_TSR_COORD,47,48,
//				CBKbutHideCtrlPnl,CBKdummy,CBKdummy,APP_GUI_BUT_MENU_TRT_HP_1_PRS_COORD,APP_GUI_BUT_MENU_TRT_HP_1_RLS_COORD,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButHideControlPanelHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER1,
//				c199_BotonGuardarMenuRightPress,c200_BotonGuardarMenuRightRls,APP_GUI_BUT_MENU_TRT_HP_2_TSR_COORD,47,48,
//				CBKbutHideCtrlPnl,CBKdummy,CBKdummy,APP_GUI_BUT_MENU_TRT_HP_2_PRS_COORD,APP_GUI_BUT_MENU_TRT_HP_2_RLS_COORD,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButHideControlPanelHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER1,
//				c202_BotonGuardarMenuLeftPress,c203_BotonGuardarMenuLeftRls,APP_GUI_BUT_MENU_TRT_HP_3_TSR_COORD,47,48,
//				CBKbutHideCtrlPnl,CBKdummy,CBKdummy,APP_GUI_BUT_MENU_TRT_HP_3_PRS_COORD,APP_GUI_BUT_MENU_TRT_HP_3_RLS_COORD,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButHideControlPanelHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER1,
//				c199_BotonGuardarMenuRightPress,c200_BotonGuardarMenuRightRls,APP_GUI_BUT_MENU_TRT_HP_4_TSR_COORD,47,48,
//				CBKbutHideCtrlPnl,CBKdummy,CBKdummy,APP_GUI_BUT_MENU_TRT_HP_4_PRS_COORD,APP_GUI_BUT_MENU_TRT_HP_4_RLS_COORD,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		butShowControlPanelHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER1,
//				c006_MenuTrtHP1Press,c006_MenuTrtHP1Press,APP_GUI_BUT_GUARDAR_MENU_HP_1_TSR_COORD,95,112,
//				CBKbutShowCtrlPnl,CBKdummy,CBKdummy,APP_GUI_BUT_GUARDAR_MENU_HP_1_PRS_COORD,APP_GUI_BUT_GUARDAR_MENU_HP_1_RLS_COORD,c007_TscMenuTrtHP1Press,
//				0,0,0,0,0,0,0,0,0		},
//		{		butShowControlPanelHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER1,
//				c014_MenuTrtHP2Press,c014_MenuTrtHP2Press,APP_GUI_BUT_GUARDAR_MENU_HP_2_TSR_COORD,95,112,
//				CBKbutShowCtrlPnl,CBKdummy,CBKdummy,APP_GUI_BUT_GUARDAR_MENU_HP_2_PRS_COORD,APP_GUI_BUT_GUARDAR_MENU_HP_2_RLS_COORD,c015_TscMenuTrtHP2Press,
//				0,0,0,0,0,0,0,0,0		},
//		{		butShowControlPanelHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER1,
//				c022_MenuTrtHP3Press,c022_MenuTrtHP3Press,APP_GUI_BUT_GUARDAR_MENU_HP_3_TSR_COORD,95,112,
//				CBKbutShowCtrlPnl,CBKdummy,CBKdummy,APP_GUI_BUT_GUARDAR_MENU_HP_3_PRS_COORD,APP_GUI_BUT_GUARDAR_MENU_HP_3_RLS_COORD,c023_TscMenuTrtHP3Press,
//				0,0,0,0,0,0,0,0,0		},
//		{		butShowControlPanelHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER1,
//				c030_MenuTrtHP4Press,c030_MenuTrtHP4Press,APP_GUI_BUT_GUARDAR_MENU_HP_4_TSR_COORD,95,112,
//				CBKbutShowCtrlPnl,CBKdummy,CBKdummy,APP_GUI_BUT_GUARDAR_MENU_HP_4_PRS_COORD,APP_GUI_BUT_GUARDAR_MENU_HP_4_RLS_COORD,c031_TscMenuTrtHP4Press,
//				0,0,0,0,0,0,0,0,0		},
				
//		//Botones Areas Cuerpo entero

//		{		ButFullBodyTorso,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				c233_ImgPixelBlanco,c113_BotonTorsoPressMujer,APP_GUI_BUT_TORSO_MUJER_TSR_COORD,89,133,
//				CBKdummy,CBKbutFullBodyArea,CBKdummy,APP_GUI_BUT_TORSO_MUJER_PRS_COORD,APP_GUI_BUT_TORSO_MUJER_RLS_COORD,c114_TscBotonTorsoMujer,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButFullBodyPiernas,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				c233_ImgPixelBlanco,c115_BotonPiernasRlsMujer,APP_GUI_BUT_PIERNAS_MUJER_TSR_COORD,83,193,
//				CBKdummy,CBKbutFullBodyArea,CBKdummy,APP_GUI_BUT_PIERNAS_MUJER_PRS_COORD,APP_GUI_BUT_PIERNAS_MUJER_RLS_COORD,c117_TscBotonPiernasMujer,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButFullBodyBrazos,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				c233_ImgPixelBlanco,c118_BotonBrazosRlsMujer,APP_GUI_BUT_BRAZOS_MUJER_TSR_COORD,130,167,
//				CBKdummy,CBKbutFullBodyArea,CBKdummy,APP_GUI_BUT_BRAZOS_MUJER_PRS_COORD,APP_GUI_BUT_BRAZOS_MUJER_RLS_COORD,c120_TscBotonBrazosMujer,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButFullBodyEspalda,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				c233_ImgPixelBlanco,c121_BotonEspaldaRlsMujer,APP_GUI_BUT_ESPALDA_MUJER_TSR_COORD,130,167,
//				CBKdummy,CBKbutFullBodyArea,CBKdummy,APP_GUI_BUT_ESPALDA_MUJER_PRS_COORD,APP_GUI_BUT_ESPALDA_MUJER_RLS_COORD,c123_TscBotonEspladaMujer,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButFullBodyPiernaMuslo,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				c233_ImgPixelBlanco,c124_BotonPiernaMusloRlsMujer,APP_GUI_BUT_MUSLO_MUJER_TSR_COORD,133,232,
//				CBKdummy,CBKbutFullBodyArea,CBKdummy,APP_GUI_BUT_MUSLO_MUJER_PRS_COORD,APP_GUI_BUT_MUSLO_MUJER_RLS_COORD,c126_TscBotonPiernaMusloMujer,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButFullBodyCuello,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				c233_ImgPixelBlanco,c127_BotonCuelloRlsMujer,APP_GUI_BUT_CUELLO_MUJER_TSR_COORD,57,74,
//				CBKdummy,CBKbutFullBodyArea,CBKdummy,APP_GUI_BUT_CUELLO_MUJER_PRS_COORD,APP_GUI_BUT_CUELLO_MUJER_RLS_COORD,c129_TscBotonCuelloMujer,
//				0,0,0,0,0,0,0,0,0		},

//		// Switches con los puntos de las zonas seleccionables
//		{		SwDotZone0,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,
//				0, 0, 32, 32, CBKswDotZoneOn, CBKswDotZoneOff, 0, 0, 0, 0, 0, 0, 0, 0, c150_TscZonaAplicacionManipPunto },
//		{		SwDotZone1,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,
//				0, 0, 32, 32, CBKswDotZoneOn, CBKswDotZoneOff, 0, 0, 0, 0, 0, 0, 0, 0, c150_TscZonaAplicacionManipPunto },
//		{		SwDotZone2,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,
//				0, 0, 32, 32, CBKswDotZoneOn, CBKswDotZoneOff, 0, 0, 0, 0, 0, 0, 0, 0, c150_TscZonaAplicacionManipPunto },
//		{		SwDotZone3,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,
//				0, 0, 32, 32, CBKswDotZoneOn, CBKswDotZoneOff, 0, 0, 0, 0, 0, 0, 0, 0, c150_TscZonaAplicacionManipPunto },
//		{		SwDotZone4,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,
//				0, 0, 32, 32, CBKswDotZoneOn, CBKswDotZoneOff, 0, 0, 0, 0, 0, 0, 0, 0, c150_TscZonaAplicacionManipPunto },
//		{		SwDotZone5,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,
//				0, 0, 32, 32, CBKswDotZoneOn, CBKswDotZoneOff, 0, 0, 0, 0, 0, 0, 0, 0, c150_TscZonaAplicacionManipPunto },
//		{		SwDotZone6,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,
//				0, 0, 32, 32, CBKswDotZoneOn, CBKswDotZoneOff, 0, 0, 0, 0, 0, 0, 0, 0, c150_TscZonaAplicacionManipPunto },
//		{		SwDotZone7,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,
//				0, 0, 32, 32, CBKswDotZoneOn, CBKswDotZoneOff, 0, 0, 0, 0, 0, 0, 0, 0, c150_TscZonaAplicacionManipPunto },
//		{		SwDotZone8,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,
//				0, 0, 32, 32, CBKswDotZoneOn, CBKswDotZoneOff, 0, 0, 0, 0, 0, 0, 0, 0, c150_TscZonaAplicacionManipPunto },
//		{		SwDotZone9,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,
//				0, 0, 32, 32, CBKswDotZoneOn, CBKswDotZoneOff, 0, 0, 0, 0, 0, 0, 0, 0, c150_TscZonaAplicacionManipPunto },
//		{		SwDotZone10,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,
//				0, 0, 32, 32, CBKswDotZoneOn, CBKswDotZoneOff, 0, 0, 0, 0, 0, 0, 0, 0, c150_TscZonaAplicacionManipPunto },
//		{		SwDotZone11,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,
//				0, 0, 32, 32, CBKswDotZoneOn, CBKswDotZoneOff, 0, 0, 0, 0, 0, 0, 0, 0, c150_TscZonaAplicacionManipPunto },
//		{		SwDotZone12,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,
//				0, 0, 32, 32, CBKswDotZoneOn, CBKswDotZoneOff, 0, 0, 0, 0, 0, 0, 0, 0, c150_TscZonaAplicacionManipPunto },
//		{		SwDotZone13,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,
//				0, 0, 32, 32, CBKswDotZoneOn, CBKswDotZoneOff, 0, 0, 0, 0, 0, 0, 0, 0, c150_TscZonaAplicacionManipPunto },
//		{		SwDotZone14,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,c149_ZonaAplicacionManipPuntoSelected,c148_ZonaAplicacionManipPunto,
//				0, 0, 32, 32, CBKswDotZoneOn, CBKswDotZoneOff, 0, 0, 0, 0, 0, 0, 0, 0, c150_TscZonaAplicacionManipPunto },
				
//		//Punto seleccionado para tratamiento con ese HP a mostrar en full body
		
//		{		ImgSelectedTrtZoneHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER3,
//			    c160_ZonaSeleccionadaHP1,APP_GUI_IMG_ZONA_SELECCIONADA_HP_1,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//		{		ImgSelectedTrtZoneHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER3,
//			    c161_ZonaSeleccionadaHP2,APP_GUI_IMG_ZONA_SELECCIONADA_HP_2,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
	
//		{		ImgSelectedTrtZoneHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER3,
//			   	c162_ZonaSeleccionadaHP3,APP_GUI_IMG_ZONA_SELECCIONADA_HP_3,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
	
//		{		ImgSelectedTrtZoneHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,0,APP_GUI_LAYER3,
//			    c163_ZonaSeleccionadaHP4,APP_GUI_IMG_ZONA_SELECCIONADA_HP_4,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
////
//// APP_GUI_BUT_ID okey

							
////	{		Okey,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER1,c158_OkeyPress2,c157_OkeyRls,APP_GUI_BUT_OKEY_TSR_COORD,52,60,
////			CBK_DUMMY,CBK_Okey,CBK_DUMMY,APP_GUI_BUT_OKEY_PRS_COORD,APP_GUI_BUT_OKEY_RLS_COORD,c159_TscOkey_Retroceso,
////			0,0,0,0,0,0,0,0,0		},
//		//POPUPS
//		//Common
////		{		butPopUpOK,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER4,
////				c158_OkeyPress2,c157_OkeyRls,APP_GUI_BUT_OKEY_POPUP_TSR_COORD,48,46,
////				CBKdummy,CBKbutPopUpOK,CBKdummy,APP_GUI_BUT_OKEY_POPUP_PRS_COORD,APP_GUI_BUT_OKEY_POPUP_RLS_COORD,c159_TscOkey_Retroceso,
////				0,0,0,0,0,0,0,0,0		},
//		{		ButPopUpReturn,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER4,
//				c156_RetrocesoPress,c155_RetrocesoRls,APP_GUI_BUT_RETURN_TSR_COORD,48,46,
//				CBKdummy,CBKbutPopUpReturn,CBKdummy,APP_GUI_BUT_RETURN_PRS_COORD,APP_GUI_BUT_RETURN_RLS_COORD,c159_TscOkey_Retroceso,
//				0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpHPcolorBar,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c216_PopUpManipHP1,APP_GUI_IMG_COLOR_POPUP_HP_1,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
			
//		//PopUp Time widgets
//		{		PopUpTime,APP_GUI_TREATMENT_SCREEN, APP_GUI_POPUP_ID ,1,0,0, APP_GUI_LAYER4,
//				0, 0, APP_GUI_POPUP_TIME_WIDGET_LIST_NUM,0,APP_GUI_POPUP_DISABLE_ALL_WIDGETS,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		butPopUpTime50min,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER6,
//				c166_PopUpBoton50MinPress,c165_PopUpBoton50MinRls,APP_GUI_BUT_50_MIN_TSR_COORD,110,27,
//				CBKdummy,CBKbutPopUpTimeValue,CBKdummy,APP_GUI_BUT_50_MIN_PRS_COORD,APP_GUI_BUT_50_MIN_RLS_COORD,c169_TscPopUpBoton70and45,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpTime70min,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER6,
//				c168_PopUpBoton70MinPress,c167_PopUpBoton70MinRls,APP_GUI_BUT_70_MIN_TSR_COORD,110,27,
//				CBKdummy,CBKbutPopUpTimeValue,CBKdummy,APP_GUI_BUT_70_MIN_PRS_COORD,APP_GUI_BUT_70_MIN_RLS_COORD,c169_TscPopUpBoton70and45,
//				0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpTime1sel,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c164_PopUpImagenReloj,0,0,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpTime2sel,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c164_Z_PopUpImagenReloj,0,0,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//		//PopUp Test Vacum widgets
//		{		PopUpTstVac,APP_GUI_TREATMENT_SCREEN, APP_GUI_POPUP_ID ,1,0,0,APP_GUI_LAYER4,
//				0 , 0, APP_GUI_POPUP_TST_VAC_WIDGET_LIST_NUM,0,APP_GUI_POPUP_DISABLE_ALL_WIDGETS,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpTstVacBckGnd,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c170_PopUpImagenSuccion,APP_GUI_IMG_FONDO_POPUP_VACUUM,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpTstVacLowLvl,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c337_PopupBotonsuccion1Rls,APP_GUI_IMG_TST_VAC_LVL_LOW,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpTstVacMidLvl,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c339_PopupBotonsuccion2Rls,APP_GUI_IMG_TST_VAC_LVL_MID,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpTstVacHighLvl,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c341_PopupBotonsuccion3Rls,APP_GUI_IMG_TST_VAC_LVL_HIGH,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
		
//		{		imgPopUpTstVacPulHand,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c222_PopUpIndmanoPress,APP_GUI_IMG_HAND_PRESSING_BUT,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpTstVacPulHandx2,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c222_B_PopUpIndmanoPressx2,APP_GUI_IMG_HAND_PRESSING_BUT,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		butPopUpTstVacManualLowLvl,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c177_PopUpBotonTestPress,c176_PopUpBotonTestRls,APP_GUI_BUT_TEST_VAC_LVL_LOW_TSR_COORD,65,31,
//				CBKdummy,CBKbutPopUpTstVacManual,CBKdummy,APP_GUI_BUT_TEST_VAC_LVL_LOW_PRS_COORD,APP_GUI_BUT_TEST_VAC_LVL_LOW_RLS_COORD,c178_TscPopUpBotonTest,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpTstVacManualMidLvl,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c177_PopUpBotonTestPress,c176_PopUpBotonTestRls,APP_GUI_BUT_TEST_VAC_LVL_MID_TSR_COORD,65,31,
//				CBKdummy,CBKbutPopUpTstVacManual,CBKdummy,APP_GUI_BUT_TEST_VAC_LVL_MID_PRS_COORD,APP_GUI_BUT_TEST_VAC_LVL_MID_RLS_COORD,c178_TscPopUpBotonTest,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpTstVacManualHighLvl,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c177_PopUpBotonTestPress,c176_PopUpBotonTestRls,APP_GUI_BUT_TEST_VAC_LVL_HIGH_TSR_COORD,65,31,
//				CBKdummy,CBKbutPopUpTstVacManual,CBKdummy,APP_GUI_BUT_TEST_VAC_LVL_HIGH_PRS_COORD,APP_GUI_BUT_TEST_VAC_LVL_HIGH_RLS_COORD,c178_TscPopUpBotonTest,
//				0,0,0,0,0,0,0,0,0		},
				
//		{		butPopUpTstVacAuto,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c221_PopUpBotonAutoPress,c220_PopUpBotonAuto,APP_GUI_BUT_AUTO_MODE_VAC_TSR_COORD,108,54,
//				CBKdummy,CBKbutPopUpTstVacAuto,CBKdummy,APP_GUI_BUT_AUTO_MODE_VAC_PRS_COORD,APP_GUI_BUT_AUTO_MODE_VAC_RLS_COORD,c178_TscPopUpBotonTest,
//				0,0,0,0,0,0,0,0,0		},
//		{		SwPopUpTstVacLowLvl,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER5,
//				c180_PopupBotonActivarPress,c179_PopupBotonActivarRls,c180_PopupBotonActivarPress,c179_PopupBotonActivarRls,
//				APP_GUI_IMG_LOW_VACUUM_TSC_COORD, 53,31, CBKswPopUpTstVacLvlOn, CBKswPopUpTstVacLvlOff,APP_GUI_IMG_LOW_VACUUM_SEL,
//				APP_GUI_IMG_LOW_VACUUM_TEST_DONE,APP_GUI_IMG_LOW_VACUUM_SEL,APP_GUI_IMG_LOW_VACUUM_TEST_DONE, c181_PopupBotonActivarTsc,
//				0,0,0,0},
//		{		SwPopUpTstVacMidLvl,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER5,
//				c180_PopupBotonActivarPress,c179_PopupBotonActivarRls,c180_PopupBotonActivarPress,c179_PopupBotonActivarRls,
//				APP_GUI_IMG_MED_VACUUM_TSC_COORD, 53,31, CBKswPopUpTstVacLvlOn, CBKswPopUpTstVacLvlOff,APP_GUI_IMG_MED_VACUUM_SEL,
//				APP_GUI_IMG_MED_VACUUM_TEST_DONE,APP_GUI_IMG_MED_VACUUM_SEL,APP_GUI_IMG_MED_VACUUM_TEST_DONE,c181_PopupBotonActivarTsc,
//				0,0,0,0},
//		{		SwPopUpTstVacHighLvl,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER5,
//				c180_PopupBotonActivarPress,c179_PopupBotonActivarRls,c180_PopupBotonActivarPress,c179_PopupBotonActivarRls,
//				APP_GUI_IMG_HIGH_VACUUM_TSC_COORD, 53,31, CBKswPopUpTstVacLvlOn, CBKswPopUpTstVacLvlOff,APP_GUI_IMG_HIGH_VACUUM_SEL,
//				APP_GUI_IMG_HIGH_VACUUM_TEST_DONE,APP_GUI_IMG_HIGH_VACUUM_SEL,APP_GUI_IMG_HIGH_VACUUM_TEST_DONE,c181_PopupBotonActivarTsc,
//				0,0,0,0},

//		{		imgPopUpTstVacAUTOstatus,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER6,
//				c233_ImgPixelBlanco,APP_GUI_IMG_TEST_VAC_MODE_AUTO_STATUS_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//		//PopUp Test Vacum SMALL widgets
//		{		PopUpTstVacSmall,APP_GUI_TREATMENT_SCREEN, APP_GUI_POPUP_ID ,1,0,0,APP_GUI_LAYER4,
//				0 , 0, APP_GUI_POPUP_TST_VAC_SMALL_WIDGET_LIST_NUM,0,APP_GUI_POPUP_DISABLE_ALL_WIDGETS,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpVacSelBck,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c349_BotonVacuumDesplegable_L,0,0,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		butPopUpTstVacSmallLowLvl,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER6,
//				c344_BotonVacuumSmall1Prs,c343_BotonVacuumSmall1Rls,APP_GUI_BUT_TEST_VAC_LVL_LOW_TSR_COORD,32,44,
//				CBKdummy,CBKbutPopUpVacSmallLvl,CBKdummy,APP_GUI_BUT_TEST_VAC_LVL_LOW_PRS_COORD,APP_GUI_BUT_TEST_VAC_LVL_LOW_RLS_COORD,c283_TscInfo,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpTstVacSmallMedLvl,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER6,
//				c346_BotonVacuumSmall2Prs,c346_BotonVacuumSmall2MarcaAgua,APP_GUI_BUT_TEST_VAC_LVL_MID_TSR_COORD,32,44,
//				CBKdummy,CBKbutPopUpVacSmallLvl,CBKdummy,APP_GUI_BUT_TEST_VAC_LVL_MID_PRS_COORD,APP_GUI_BUT_TEST_VAC_LVL_MID_RLS_COORD,c283_TscInfo,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpTstVacSmallHighLvl,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER6,
//				c348_BotonVacuumSmall3Prs,c347_BotonVacuumSmall3Rls,APP_GUI_BUT_TEST_VAC_LVL_HIGH_TSR_COORD,32,44,
//				CBKdummy,CBKbutPopUpVacSmallLvl,CBKdummy,APP_GUI_BUT_TEST_VAC_LVL_HIGH_PRS_COORD,APP_GUI_BUT_TEST_VAC_LVL_HIGH_RLS_COORD,c283_TscInfo,
//				0,0,0,0,0,0,0,0,0		},
				
//		//PopUp RFID widgets
//		{		PopUpRFID,APP_GUI_TREATMENT_SCREEN, APP_GUI_POPUP_ID ,1,0,0, APP_GUI_LAYER4,
//				0, 0, APP_GUI_POPUP_RFID_WIDGET_LIST_NUM,0,APP_GUI_POPUP_DISABLE_ALL_WIDGETS,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpRFIDbckGnd,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c182_PopUpRFIDFondo,APP_GUI_IMG_FONDO_POPUP_RFID,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//		{		imgPopUpRFIDlabel,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c182_PopUpRFIDlabelDM,APP_GUI_IMG_LABEL_POPUP_RFID,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpRFIDresult,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c182_PopUpRFIDsuccess,APP_GUI_IMG_STATUS_POPUP_RFID,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//        {		butPopUpRFIDreuseLabel,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER6,
//				c233_ImgPixelBlanco,c233_ImgPixelBlanco,APP_GUI_BUT_REUSE_LABEL,121,51,
//				CBKdummy,CBKbutReuseRFIDlabel,CBKdummy,APP_GUI_BUT_REUSE_LABEL,APP_GUI_BUT_REUSE_LABEL,c051_TscrRelojTemporizador,
//				0,0,0,0,0,0,0,0,0		},
//		{		NumVwrPopUpRFIDrestTime,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				APP_GUI_LAYER6,5,3,16,35,1,APP_GUI_NUMVWR_TIME_REUSE_LABEL,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c065_CaracterNegativo,c062_CaracterDosPuntos	},
						
//		//SWITCH INFO
//		{		SwPopUpRecommInfo,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER4,
//				c282_InfoPress,c281_InfoRls,c282_InfoPress,c281_InfoRls,
//				APP_GUI_BUT_INFO_POPUP_RECOMMENDATIONS_TSC, 52,60, CBKbutInfoZoneSelectedOn, CBKbutInfoZoneSelectedOff,APP_GUI_BUT_INFO_POPUP_RECOMMENDATIONS_ON,
//				APP_GUI_BUT_INFO_POPUP_RECOMMENDATIONS_OFF,APP_GUI_BUT_INFO_POPUP_RECOMMENDATIONS_ON,APP_GUI_BUT_INFO_POPUP_RECOMMENDATIONS_OFF, c283_TscInfo,
//				0,0,0,0},
				
//		//PopUp Recommended HP widgets
//		{		PopUpRecomm,APP_GUI_TREATMENT_SCREEN, APP_GUI_POPUP_ID ,1,0,0, APP_GUI_LAYER4,
//				0, 0, APP_GUI_POPUP_RECOMMENDATION_WIDGET_LIST_NUM,0,APP_GUI_POPUP_DISABLE_ALL_WIDGETS,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpRecommbckGnd,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c284_PopUpSugerenciasFondo_03,APP_GUI_IMG_FONDO_POPUP_RECOMMENDATION_HP,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//		{		ImgPopUpRecommCurved,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c285_PopUpMarcaaguaCurved,APP_GUI_IMG_RECOMM_CURVED_HP_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgPopUpRecommTight,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c286_PopUpMarcaaguaTight,APP_GUI_IMG_RECOMM_TIGHT_HP_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgPopUpRecommStright,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c287_PopUpMarcaaguaStraight,APP_GUI_IMG_RECOMM_STRIGHT_HP_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgPopUpRecommTiny,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c288_PopUpMarcaaguaTiny,APP_GUI_IMG_RECOMM_TINY_HP_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgPopUpRecommTinyCurved,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c289_PopUpMarcaaguaTinyCurved,APP_GUI_IMG_RECOMM_TINY_CURVED_HP_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgPopUpRecommDouble,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c290_PopUpMarcaaguaDouble,APP_GUI_IMG_RECOMM_DOUBLE_HP_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgPopUpRecommOval,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c291_PopUpMarcaaguaOval,APP_GUI_IMG_RECOMM_OVAL_HP_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgPopUpRecommOvalCurved,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c292_PopUpMarcaaguaOvalCurved,APP_GUI_IMG_RECOMM_OVAL_CURVED_HP_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		ImgPopUpRecommAngled,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c293_PopUpMarcaaguaAngled,APP_GUI_IMG_RECOMM_ANGLED_HP_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
					 
//		//  Menu  Principal
//		{		butTrtScrShowMainMenu,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER1,
//				b008_SwMenuRls,b008_SwMenuRls,APP_GUI_BUT_MENU_GLOBAL_TSR_COORD,97,57,
//				CBKdummy,CBKbutMainMenuShow,CBKdummy,APP_GUI_BUT_MENU_GLOBAL_PRS_COORD,APP_GUI_BUT_MENU_GLOBAL_RLS_COORD,b009_TscSwMenuRls,
//				0,0,0,0,0,0,0,0,0		},
//		{		butTrtScrHideMainMenu,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				b010_SwMenuPress,b010_SwMenuPress,APP_GUI_BUT_MENU_GLOBAL_2_TSR_COORD,47,48,
//				CBKdummy,CBKbutMainMenuHide,CBKdummy,APP_GUI_BUT_MENU_GLOBAL_2_PRS_COORD,APP_GUI_BUT_MENU_GLOBAL_2_RLS_COORD,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButTrtScrHome,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER3,
//				b013_BotonHomePress,b014_BotonHomeRls,APP_GUI_BUT_HOME_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutHome,CBKdummy,APP_GUI_BUT_HOME_GLOBAL_PRS_COORD,APP_GUI_BUT_HOME_GLOBAL_RLS_COORD,b015_TscBotonHome,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButTrtScrCfg,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER3,
//				b016_BotonConfigPress,b017_BotonConfigRls,APP_GUI_BUT_CONFIG_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutConfig,CBKdummy,APP_GUI_BUT_CONFIG_GLOBAL_PRS_COORD,APP_GUI_BUT_CONFIG_GLOBAL_RLS_COORD,b019_TscBotonConfig,
//				0,0,0,0,0,0,0,0,0		},
//		{		ButTrtScrCalc,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER3,
//				b021_BotonCalculadoraPress,b022_BotonCalculadoraRls,APP_GUI_BUT_CALCULADORA_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutCalc,CBKdummy,APP_GUI_BUT_CALCULADORA_GLOBAL_PRS_COORD,APP_GUI_BUT_CALCULADORA_GLOBAL_RLS_COORD,b023_TscBotonCalculadora,
//				0,0,0,0,0,0,0,0,0		},
//		{		butTrtScrData,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER3,
//				b025_BotonIdiomasPress,b024_BotonIdiomasMarcaAgua/*b026_BotonIdiomasRls*/,APP_GUI_BUT_IDIOMAS_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutData,CBKdummy,APP_GUI_BUT_IDIOMAS_GLOBAL_PRS_COORD,APP_GUI_BUT_IDIOMAS_GLOBAL_RLS_COORD,b027_TscBotonIdiomas,
//				0,0,0,0,0,0,0,0,0		},
//		//avisos
		
//		{		SwTrtScrAvisos,APP_GUI_TREATMENT_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				b029_BotonAvisosPress,b030_BotonAvisosRls,b029_BotonAvisosPress,b030_BotonAvisosRls,
//				APP_GUI_BUT_AVISOS_GLOBAL_TSR_COORD, 62,62, CBKbutWarningOn, CBKbutWarningOff,APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD,
//				APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD,APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD,APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD, b031_TscBotonAvisos,
//				0,0,0,0},
//		{		ImgTrtScrNotificacion,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				b032_ImgNotificacion,APP_GUI_IMG_AVISO_PENDIENTE_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//		{		PopupTrtScrAvisos,APP_GUI_TREATMENT_SCREEN, APP_GUI_POPUP_ID ,1,0,0, APP_GUI_LAYER4,
//				0, 0, APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM,0,APP_GUI_POPUP_DISABLE_ALL_WIDGETS,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//		{		imgPopUpTrtScrAvisoBckGND,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c420_Menualarmasfondo,APP_GUI_IMG_AVISO_POPUP_BCKGND_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpTrtScrAvisoNivelAguaBajo,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c425_Menualarmasinaguapress,APP_GUI_IMG_AVISO_POPUP_NIVEL_AGUA_BAJO_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpTrtScrAvisoNivelAguaMedio,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c424_Menualarmaaguamitadpress,APP_GUI_IMG_AVISO_POPUP_NIVEL_AGUA_MEDIO_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpTrtScrAvisoTempAmb,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c421_Menualarmatemppress,APP_GUI_IMG_AVISO_POPUP_TEMP_AMB_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpTrtScrAvisoRFID,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c423_Menualarmarfidpress,APP_GUI_IMG_AVISO_POPUP_RFID_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpTrtScrAvisoRTC,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c426_Menualarmatiempopress,APP_GUI_IMG_AVISO_POPUP_RTC_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpTrtScrAvisoFiltroAire,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				c422_Menualarmafiltropress,APP_GUI_IMG_AVISO_POPUP_FILTRO_AIRE_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

		
//		//Widgets gestión errores en pantalla de trt
//		{		imgPopUpErrBckGndHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER7,
//				c234_AlarmaFondoHP1,APP_GUI_IMG_ERR_BCKGND_COORD_HP1,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpErrBckGndHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER7,
//				c234_AlarmaFondoHP2,APP_GUI_IMG_ERR_BCKGND_COORD_HP2,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpErrBckGndHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER7,
//				c234_AlarmaFondoHP3,APP_GUI_IMG_ERR_BCKGND_COORD_HP3,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpErrBckGndHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER7,
//				c234_AlarmaFondoHP4,APP_GUI_IMG_ERR_BCKGND_COORD_HP4,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpErrBckGndUC,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER7,
//				c234_AlarmaFondoCentral2,APP_GUI_IMG_ERR_BCKGND_COORD_UC,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//		{		NumVwrPopUpErrHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER8,
//				APP_GUI_LAYER9,5,2,17,21,1,APP_GUI_NUM_VWR_ERR_COORD_HP1,105,42,c461_FondoNumVwrError,
//				c461_Numero0,c461_Numero1,c461_Numero2,c461_Numero3,c461_Numero4,c461_Numero5,c461_Numero6,c461_Numero7,c461_Numero8,c461_Numero9,c461_CaracterNegativo,c461_CaracterDosPuntos	},
//		{		NumVwrPopUpErrHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER8,
//				APP_GUI_LAYER9,5,2,17,21,1,APP_GUI_NUM_VWR_ERR_COORD_HP2,105,42,c461_FondoNumVwrError,
//				c461_Numero0,c461_Numero1,c461_Numero2,c461_Numero3,c461_Numero4,c461_Numero5,c461_Numero6,c461_Numero7,c461_Numero8,c461_Numero9,c461_CaracterNegativo,c461_CaracterDosPuntos	},
//		{		NumVwrPopUpErrHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER8,
//				APP_GUI_LAYER9,5,2,17,21,1,APP_GUI_NUM_VWR_ERR_COORD_HP3,105,42,c461_FondoNumVwrError,
//				c461_Numero0,c461_Numero1,c461_Numero2,c461_Numero3,c461_Numero4,c461_Numero5,c461_Numero6,c461_Numero7,c461_Numero8,c461_Numero9,c461_CaracterNegativo,c461_CaracterDosPuntos	},
//		{		NumVwrPopUpErrHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER8,
//				APP_GUI_LAYER9,5,2,17,21,1,APP_GUI_NUM_VWR_ERR_COORD_HP4,105,42,c461_FondoNumVwrError,
//				c461_Numero0,c461_Numero1,c461_Numero2,c461_Numero3,c461_Numero4,c461_Numero5,c461_Numero6,c461_Numero7,c461_Numero8,c461_Numero9,c461_CaracterNegativo,c461_CaracterDosPuntos	},
//		{		NumVwrPopUpErrUC,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER8,
//				APP_GUI_LAYER9,4,2,17,21,1,APP_GUI_NUM_VWR_ERR_COORD_UC,101,42,c461_FondoNumVwrError,
//				c461_Numero0,c461_Numero1,c461_Numero2,c461_Numero3,c461_Numero4,c461_Numero5,c461_Numero6,c461_Numero7,c461_Numero8,c461_Numero9,c461_CaracterNegativo,c461_CaracterDosPuntos	},
																				
//		{		imgPopUpErrMsgHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER8,
//				c061_Numero0,APP_GUI_IMG_ERR_MSG_COORD_HP1,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpErrMsgHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER8,
//				c061_Numero0,APP_GUI_IMG_ERR_MSG_COORD_HP2,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpErrMsgHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER8,
//				c061_Numero0,APP_GUI_IMG_ERR_MSG_COORD_HP3,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpErrMsgHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER8,
//				c061_Numero0,APP_GUI_IMG_ERR_MSG_COORD_HP4,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpErrMsgUC,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER8,
//				c061_Numero0,APP_GUI_IMG_ERR_MSG_COORD_UC,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
			
//		{		butPopUpErrOkHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER8,
//				c357_BotonAlarmaCentralOkPress,c356_BotonAlarmaCentralOkRls,APP_GUI_BUT_ERR_OK_COORD_HP1,49,49,
//				CBKdummy,CBKbutPopUpErrOk,CBKdummy,APP_GUI_BUT_ERR_OK_COORD_HP1,APP_GUI_BUT_ERR_OK_COORD_HP1,c358_BotonAlarmaCentralOkTsc,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpErrOkHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER8,
//				c357_BotonAlarmaCentralOkPress,c356_BotonAlarmaCentralOkRls,APP_GUI_BUT_ERR_OK_COORD_HP2,49,49,
//				CBKdummy,CBKbutPopUpErrOk,CBKdummy,APP_GUI_BUT_ERR_OK_COORD_HP2,APP_GUI_BUT_ERR_OK_COORD_HP2,c358_BotonAlarmaCentralOkTsc,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpErrOkHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER8,
//				c357_BotonAlarmaCentralOkPress,c356_BotonAlarmaCentralOkRls,APP_GUI_BUT_ERR_OK_COORD_HP3,49,49,
//				CBKdummy,CBKbutPopUpErrOk,CBKdummy,APP_GUI_BUT_ERR_OK_COORD_HP3,APP_GUI_BUT_ERR_OK_COORD_HP3,c358_BotonAlarmaCentralOkTsc,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpErrOkHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER8,
//				c357_BotonAlarmaCentralOkPress,c356_BotonAlarmaCentralOkRls,APP_GUI_BUT_ERR_OK_COORD_HP4,49,49,
//				CBKdummy,CBKbutPopUpErrOk,CBKdummy,APP_GUI_BUT_ERR_OK_COORD_HP4,APP_GUI_BUT_ERR_OK_COORD_HP4,c358_BotonAlarmaCentralOkTsc,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpErrOkUC,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER8,
//				c357_BotonAlarmaCentralOkPress,c356_BotonAlarmaCentralOkRls,APP_GUI_BUT_ERR_OK_COORD_UC,49,49,
//				CBKdummy,CBKbutPopUpErrOk,CBKdummy,APP_GUI_BUT_ERR_OK_COORD_UC,APP_GUI_BUT_ERR_OK_COORD_UC,c358_BotonAlarmaCentralOkTsc,
//				0,0,0,0,0,0,0,0,0		},
					
//		{		NumVwrPopUpErrTRTtimeHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER8,
//				APP_GUI_LAYER9,5,1/*2*/,10/*17*/,21,1,APP_GUI_NUM_VWR_ERR_TRT_TIMR_COORD_HP1,105,42,c465_Menu_error_lectortiempo,
//				c465_tiempo_Numero0,c465_tiempo_Numero1,c465_tiempo_Numero2,c465_tiempo_Numero3,c465_tiempo_Numero4,c465_tiempo_Numero5,c465_tiempo_Numero6,c465_tiempo_Numero7,c465_tiempo_Numero8,c465_tiempo_Numero9,c465_tiempo_CaracterDosPuntos,c465_tiempo_CaracterDosPuntos	},
//		{		NumVwrPopUpErrTRTtimeHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER8,
//				APP_GUI_LAYER9,5,1/*2*/,10/*17*/,21,1,APP_GUI_NUM_VWR_ERR_TRT_TIMR_COORD_HP2,105,42,c465_Menu_error_lectortiempo,
//				c465_tiempo_Numero0,c465_tiempo_Numero1,c465_tiempo_Numero2,c465_tiempo_Numero3,c465_tiempo_Numero4,c465_tiempo_Numero5,c465_tiempo_Numero6,c465_tiempo_Numero7,c465_tiempo_Numero8,c465_tiempo_Numero9,c465_tiempo_CaracterDosPuntos,c465_tiempo_CaracterDosPuntos	},
//		{		NumVwrPopUpErrTRTtimeHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER8,
//				APP_GUI_LAYER9,5,1/*2*/,10/*17*/,21,1,APP_GUI_NUM_VWR_ERR_TRT_TIMR_COORD_HP3,105,42,c465_Menu_error_lectortiempo,
//				c465_tiempo_Numero0,c465_tiempo_Numero1,c465_tiempo_Numero2,c465_tiempo_Numero3,c465_tiempo_Numero4,c465_tiempo_Numero5,c465_tiempo_Numero6,c465_tiempo_Numero7,c465_tiempo_Numero8,c465_tiempo_Numero9,c465_tiempo_CaracterDosPuntos,c465_tiempo_CaracterDosPuntos	},
//		{		NumVwrPopUpErrTRTtimeHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER8,
//				APP_GUI_LAYER9,5,1/*2*/,10/*17*/,21,1,APP_GUI_NUM_VWR_ERR_TRT_TIMR_COORD_HP4,105,42,c465_Menu_error_lectortiempo,
//				c465_tiempo_Numero0,c465_tiempo_Numero1,c465_tiempo_Numero2,c465_tiempo_Numero3,c465_tiempo_Numero4,c465_tiempo_Numero5,c465_tiempo_Numero6,c465_tiempo_Numero7,c465_tiempo_Numero8,c465_tiempo_Numero9,c465_tiempo_CaracterDosPuntos,c465_tiempo_CaracterDosPuntos	},
				
//		//Gestion de limpieza del HP

//		{		imgPopUpCleanBckGndHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c234_AlarmaFondoHP1,APP_GUI_IMG_CLEAN_BCKGND_COORD_HP1,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCleanBckGndHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c234_AlarmaFondoHP2,APP_GUI_IMG_CLEAN_BCKGND_COORD_HP2,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCleanBckGndHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c234_AlarmaFondoHP3,APP_GUI_IMG_CLEAN_BCKGND_COORD_HP3,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCleanBckGndHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c234_AlarmaFondoHP4,APP_GUI_IMG_CLEAN_BCKGND_COORD_HP4,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//		{		NumVwrPopUpCleanHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				APP_GUI_LAYER6,5,2,17,21,1,APP_GUI_NUM_VWR_CLEAN_COORD_HP1,101,42,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c065_CaracterNegativo,c062_CaracterDosPuntos	},
//		{		NumVwrPopUpCleanHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				APP_GUI_LAYER6,5,2,17,21,1,APP_GUI_NUM_VWR_CLEAN_COORD_HP2,101,42,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c065_CaracterNegativo,c062_CaracterDosPuntos	},
//		{		NumVwrPopUpCleanHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				APP_GUI_LAYER6,5,2,17,21,1,APP_GUI_NUM_VWR_CLEAN_COORD_HP3,101,42,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c065_CaracterNegativo,c062_CaracterDosPuntos	},
//		{		NumVwrPopUpCleanHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				APP_GUI_LAYER6,5,2,17,21,1,APP_GUI_NUM_VWR_CLEAN_COORD_HP4,101,42,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c065_CaracterNegativo,c062_CaracterDosPuntos	},
				
//		{		butPopUpCleanHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c457_MenuLimpiezaClean_Press,c456_MenuLimpiezaClean_Rls,APP_GUI_BUT_CLEAN_COORD_HP1,65,65,
//				CBKdummy,CBKbutPopUpCleanUp,CBKdummy,APP_GUI_BUT_CLEAN_COORD_HP1,APP_GUI_BUT_CLEAN_COORD_HP1,c453_MenuAlarmaOK_tsc,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpCleanHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c457_MenuLimpiezaClean_Press,c456_MenuLimpiezaClean_Rls,APP_GUI_BUT_CLEAN_COORD_HP2,65,65,
//				CBKdummy,CBKbutPopUpCleanUp,CBKdummy,APP_GUI_BUT_CLEAN_COORD_HP2,APP_GUI_BUT_CLEAN_COORD_HP2,c453_MenuAlarmaOK_tsc,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpCleanHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c457_MenuLimpiezaClean_Press,c456_MenuLimpiezaClean_Rls,APP_GUI_BUT_CLEAN_COORD_HP3,65,65,
//				CBKdummy,CBKbutPopUpCleanUp,CBKdummy,APP_GUI_BUT_CLEAN_COORD_HP3,APP_GUI_BUT_CLEAN_COORD_HP3,c453_MenuAlarmaOK_tsc,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpCleanHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c457_MenuLimpiezaClean_Press,c456_MenuLimpiezaClean_Rls,APP_GUI_BUT_CLEAN_COORD_HP4,65,65,
//				CBKdummy,CBKbutPopUpCleanUp,CBKdummy,APP_GUI_BUT_CLEAN_COORD_HP4,APP_GUI_BUT_CLEAN_COORD_HP4,c453_MenuAlarmaOK_tsc,
//				0,0,0,0,0,0,0,0,0		},
				
//		{		butPopUpCleanYESHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c452_MenuAlarmaOK_press,c453_MenuAlarmaOK_rls,APP_GUI_BUT_CLEAN_YES_COORD_HP1,65,65,
//				CBKdummy,CBKbutPopUpCleanUpYES,CBKdummy,APP_GUI_BUT_CLEAN_YES_COORD_HP1,APP_GUI_BUT_CLEAN_YES_COORD_HP1,c453_MenuAlarmaOK_tsc,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpCleanYESHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c452_MenuAlarmaOK_press,c453_MenuAlarmaOK_rls,APP_GUI_BUT_CLEAN_YES_COORD_HP2,65,65,
//				CBKdummy,CBKbutPopUpCleanUpYES,CBKdummy,APP_GUI_BUT_CLEAN_YES_COORD_HP2,APP_GUI_BUT_CLEAN_YES_COORD_HP2,c453_MenuAlarmaOK_tsc,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpCleanYESHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c452_MenuAlarmaOK_press,c453_MenuAlarmaOK_rls,APP_GUI_BUT_CLEAN_YES_COORD_HP3,65,65,
//				CBKdummy,CBKbutPopUpCleanUpYES,CBKdummy,APP_GUI_BUT_CLEAN_YES_COORD_HP3,APP_GUI_BUT_CLEAN_YES_COORD_HP3,c453_MenuAlarmaOK_tsc,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpCleanYESHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c452_MenuAlarmaOK_press,c453_MenuAlarmaOK_rls,APP_GUI_BUT_CLEAN_YES_COORD_HP4,65,65,
//				CBKdummy,CBKbutPopUpCleanUpYES,CBKdummy,APP_GUI_BUT_CLEAN_YES_COORD_HP4,APP_GUI_BUT_CLEAN_YES_COORD_HP4,c453_MenuAlarmaOK_tsc,
//				0,0,0,0,0,0,0,0,0		},
						
//		{		butPopUpCleanNOHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c454_MenuAlarmaNO_press,c455_MenuAlarmaNO_rls,APP_GUI_BUT_CLEAN_NO_COORD_HP1,65,65,
//				CBKdummy,CBKbutPopUpCleanUpNO,CBKdummy,APP_GUI_BUT_CLEAN_NO_COORD_HP1,APP_GUI_BUT_CLEAN_NO_COORD_HP1,c453_MenuAlarmaOK_tsc,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpCleanNOHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c454_MenuAlarmaNO_press,c455_MenuAlarmaNO_rls,APP_GUI_BUT_CLEAN_NO_COORD_HP2,65,65,
//				CBKdummy,CBKbutPopUpCleanUpNO,CBKdummy,APP_GUI_BUT_CLEAN_NO_COORD_HP2,APP_GUI_BUT_CLEAN_NO_COORD_HP2,c453_MenuAlarmaOK_tsc,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpCleanNOHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c454_MenuAlarmaNO_press,c455_MenuAlarmaNO_rls,APP_GUI_BUT_CLEAN_NO_COORD_HP3,65,65,
//				CBKdummy,CBKbutPopUpCleanUpNO,CBKdummy,APP_GUI_BUT_CLEAN_NO_COORD_HP3,APP_GUI_BUT_CLEAN_NO_COORD_HP3,c453_MenuAlarmaOK_tsc,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpCleanNOHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c454_MenuAlarmaNO_press,c455_MenuAlarmaNO_rls,APP_GUI_BUT_CLEAN_NO_COORD_HP4,65,65,
//				CBKdummy,CBKbutPopUpCleanUpNO,CBKdummy,APP_GUI_BUT_CLEAN_NO_COORD_HP4,APP_GUI_BUT_CLEAN_NO_COORD_HP4,c453_MenuAlarmaOK_tsc,
//				0,0,0,0,0,0,0,0,0		},
				
//		{		imgPopUpCleanHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c082_ImgTinyHP_L_Rls,APP_GUI_IMG_CLEAN_COORD_HP1,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCleanHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c082_ImgTinyHP_L_Rls,APP_GUI_IMG_CLEAN_COORD_HP2,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCleanHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c082_ImgTinyHP_L_Rls,APP_GUI_IMG_CLEAN_COORD_HP3,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCleanHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c082_ImgTinyHP_L_Rls,APP_GUI_IMG_CLEAN_COORD_HP4,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//		{		butPopUpCleanCancelHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c531_botoncancel_Rls,c532_botoncancel_Press,APP_GUI_BUT_CLEAN_CANCEL_COORD_HP1,49,49,
//				CBKdummy,CBKbutPopUpCleanUpCancel,CBKdummy,APP_GUI_BUT_CLEAN_CANCEL_COORD_HP1,APP_GUI_BUT_CLEAN_CANCEL_COORD_HP1,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpCleanCancelHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c531_botoncancel_Rls,c532_botoncancel_Press,APP_GUI_BUT_CLEAN_CANCEL_COORD_HP2,49,49,
//				CBKdummy,CBKbutPopUpCleanUpCancel,CBKdummy,APP_GUI_BUT_CLEAN_CANCEL_COORD_HP2,APP_GUI_BUT_CLEAN_CANCEL_COORD_HP2,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpCleanCancelHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c531_botoncancel_Rls,c532_botoncancel_Press,APP_GUI_BUT_CLEAN_CANCEL_COORD_HP3,49,49,
//				CBKdummy,CBKbutPopUpCleanUpCancel,CBKdummy,APP_GUI_BUT_CLEAN_CANCEL_COORD_HP3,APP_GUI_BUT_CLEAN_CANCEL_COORD_HP3,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPopUpCleanCancelHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER5,
//				c531_botoncancel_Rls,c532_botoncancel_Press,APP_GUI_BUT_CLEAN_CANCEL_COORD_HP4,49,49,
//				CBKdummy,CBKbutPopUpCleanUpCancel,CBKdummy,APP_GUI_BUT_CLEAN_CANCEL_COORD_HP4,APP_GUI_BUT_CLEAN_CANCEL_COORD_HP4,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
				
//		{		NumVwrPopUpCleanNumCancelHP1,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				APP_GUI_LAYER6,3,0,9,24,1,APP_GUI_NUMVWR_CLEAN_CANCEL_COORD_HP1,30,35,c533_fondocontador,
//				c465_tiempo_Numero0,c465_tiempo_Numero1,c465_tiempo_Numero2,c465_tiempo_Numero3,c465_tiempo_Numero4,c465_tiempo_Numero5,c465_tiempo_Numero6,c465_tiempo_Numero7,c465_tiempo_Numero8,c465_tiempo_Numero9,c465_tiempo_CaracterBarra,c465_tiempo_CaracterBarra	},
//		{		NumVwrPopUpCleanNumCancelHP2,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				APP_GUI_LAYER6,3,0,9,24,1,APP_GUI_NUMVWR_CLEAN_CANCEL_COORD_HP2,30,35,c533_fondocontador,
//				c465_tiempo_Numero0,c465_tiempo_Numero1,c465_tiempo_Numero2,c465_tiempo_Numero3,c465_tiempo_Numero4,c465_tiempo_Numero5,c465_tiempo_Numero6,c465_tiempo_Numero7,c465_tiempo_Numero8,c465_tiempo_Numero9,c465_tiempo_CaracterBarra,c465_tiempo_CaracterBarra	},
//		{		NumVwrPopUpCleanNumCancelHP3,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				APP_GUI_LAYER6,3,0,9,24,1,APP_GUI_NUMVWR_CLEAN_CANCEL_COORD_HP3,30,35,c533_fondocontador,
//				c465_tiempo_Numero0,c465_tiempo_Numero1,c465_tiempo_Numero2,c465_tiempo_Numero3,c465_tiempo_Numero4,c465_tiempo_Numero5,c465_tiempo_Numero6,c465_tiempo_Numero7,c465_tiempo_Numero8,c465_tiempo_Numero9,c465_tiempo_CaracterBarra,c465_tiempo_CaracterBarra	},
//		{		NumVwrPopUpCleanNumCancelHP4,APP_GUI_TREATMENT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER5,
//				APP_GUI_LAYER6,3,0,9,24,1,APP_GUI_NUMVWR_CLEAN_CANCEL_COORD_HP4,30,35,c533_fondocontador,
//				c465_tiempo_Numero0,c465_tiempo_Numero1,c465_tiempo_Numero2,c465_tiempo_Numero3,c465_tiempo_Numero4,c465_tiempo_Numero5,c465_tiempo_Numero6,c465_tiempo_Numero7,c465_tiempo_Numero8,c465_tiempo_Numero9,c465_tiempo_CaracterBarra,c465_tiempo_CaracterBarra	},

					
//				//CALCULADORA
				
//		{		imgFondoCalcScreen,APP_GUI_CALCULATOR_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER0,
//				c280_BackCalculadorafondo,APP_GUI_IMG_FONDO_CALC_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgCuerpoCalc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c265_Calculadorafondo_03,APP_GUI_IMG_CUERPO_CALC_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//		{		NumVwrPantallaCalc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER2,
//				APP_GUI_LAYER3,6,5,36,55,1,APP_GUI_NUM_VWR_PANTALLA_CALC_COORD,380,25,c233_ImgPixelBlanco,
//				c258_Calculadoranumero0,c249_Calculadoranumero1,c250_Calculadoranumero2,c251_Calculadoranumero3,c252_Calculadoranumero4,c253_Calculadoranumero5,c254_Calculadoranumero6,c255_Calculadoranumero7,c256_Calculadoranumero8,c257_Calculadoranumero9,c233_ImgPixelBlanco,c233_ImgPixelBlanco	},
				
//		{		ButNum0Calc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c275_Calculadoraboton0Press,c247_Calculadoraboton0Rls,APP_GUI_BUT_CALC_NUM0_TSR_COORD,130,60,
//				CBKbutNumCalc,CBKdummy,CBKdummy,APP_GUI_BUT_CALC_NUM0_PRS_COORD,APP_GUI_BUT_CALC_NUM0_RLS_COORD,c248_Calculadoraboton0Tsc,
//				0,0,0,0,0,0,0,0,0		},
				
//		{		ButNum1Calc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c266_Calculadoraboton1Press,c237_Calculadoraboton1Rls,APP_GUI_BUT_CALC_NUM1_TSR_COORD,60,60,
//				CBKbutNumCalc,CBKdummy,CBKdummy,APP_GUI_BUT_CALC_NUM1_PRS_COORD,APP_GUI_BUT_CALC_NUM1_RLS_COORD,c246_CalculadorabotonTsc,
//				0,0,0,0,0,0,0,0,0		},

//		{		ButNum2Calc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c267_Calculadoranumero2Press,c238_Calculadoraboton2Rls,APP_GUI_BUT_CALC_NUM2_TSR_COORD,60,60,
//				CBKbutNumCalc,CBKdummy,CBKdummy,APP_GUI_BUT_CALC_NUM2_PRS_COORD,APP_GUI_BUT_CALC_NUM2_RLS_COORD,c246_CalculadorabotonTsc,
//				0,0,0,0,0,0,0,0,0		},

//		{		ButNum3Calc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c268_Calculadoraboton3Press,c239_Calculadoraboton3Rls,APP_GUI_BUT_CALC_NUM3_TSR_COORD,60,60,
//				CBKbutNumCalc,CBKdummy,CBKdummy,APP_GUI_BUT_CALC_NUM3_PRS_COORD,APP_GUI_BUT_CALC_NUM3_RLS_COORD,c246_CalculadorabotonTsc,
//				0,0,0,0,0,0,0,0,0		},

//		{		ButNum4Calc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c269_Calculadoraboton4Press,c240_Calculadoraboton4Rls,APP_GUI_BUT_CALC_NUM4_TSR_COORD,60,60,
//				CBKbutNumCalc,CBKdummy,CBKdummy,APP_GUI_BUT_CALC_NUM4_PRS_COORD,APP_GUI_BUT_CALC_NUM4_RLS_COORD,c246_CalculadorabotonTsc,
//				0,0,0,0,0,0,0,0,0		},

//		{		ButNum5Calc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c270_Calculadoraboton5Press,c241_Calculadoraboton5Rls,APP_GUI_BUT_CALC_NUM5_TSR_COORD,60,60,
//				CBKbutNumCalc,CBKdummy,CBKdummy,APP_GUI_BUT_CALC_NUM5_PRS_COORD,APP_GUI_BUT_CALC_NUM5_RLS_COORD,c246_CalculadorabotonTsc,
//				0,0,0,0,0,0,0,0,0		},

//		{		ButNum6Calc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c271_Calculadoranumero6Press,c242_Calculadoraboton6Rls,APP_GUI_BUT_CALC_NUM6_TSR_COORD,60,60,
//				CBKbutNumCalc,CBKdummy,CBKdummy,APP_GUI_BUT_CALC_NUM6_PRS_COORD,APP_GUI_BUT_CALC_NUM6_RLS_COORD,c246_CalculadorabotonTsc,
//				0,0,0,0,0,0,0,0,0		},

//		{		ButNum7Calc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c272_Calculadoraboton7Press,c243_Calculadoraboton7Rls,APP_GUI_BUT_CALC_NUM7_TSR_COORD,60,60,
//				CBKbutNumCalc,CBKdummy,CBKdummy,APP_GUI_BUT_CALC_NUM7_PRS_COORD,APP_GUI_BUT_CALC_NUM7_RLS_COORD,c246_CalculadorabotonTsc,
//				0,0,0,0,0,0,0,0,0		},

//		{		ButNum8Calc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c273_Calculadoraboton8Press,c244_Calculadoraboton8Rls,APP_GUI_BUT_CALC_NUM8_TSR_COORD,60,60,
//				CBKbutNumCalc,CBKdummy,CBKdummy,APP_GUI_BUT_CALC_NUM8_PRS_COORD,APP_GUI_BUT_CALC_NUM8_RLS_COORD,c246_CalculadorabotonTsc,
//				0,0,0,0,0,0,0,0,0		},

//		{		ButNum9Calc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c274_Calculadoranumero9Press,c245_Calculadoraboton9Rls,APP_GUI_BUT_CALC_NUM9_TSR_COORD,60,60,
//				CBKbutNumCalc,CBKdummy,CBKdummy,APP_GUI_BUT_CALC_NUM9_PRS_COORD,APP_GUI_BUT_CALC_NUM9_RLS_COORD,c246_CalculadorabotonTsc,
//				0,0,0,0,0,0,0,0,0		},
				
				
//		{		butMasCalc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c276_CalculadorabotonmasPress,c259_CalculadorabotonmasRls,APP_GUI_BUT_CALC_MAS_TSR_COORD,60,60,
//				CBKdummy,CBKdummy,CBKdummy,APP_GUI_BUT_CALC_MAS_PRS_COORD,APP_GUI_BUT_CALC_MAS_RLS_COORD,c246_CalculadorabotonTsc,
//				0,0,0,0,0,0,0,0,0		},

//		{		butMenosCalc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c277_CalculadorabotonmenosPress,c260_CalculadorabotonmenosRls,APP_GUI_BUT_CALC_MENOS_TSR_COORD,60,60,
//				CBKdummy,CBKdummy,CBKdummy,APP_GUI_BUT_CALC_MENOS_PRS_COORD,APP_GUI_BUT_CALC_MENOS_RLS_COORD,c246_CalculadorabotonTsc,
//				0,0,0,0,0,0,0,0,0		},

//		{		ButEnterCalc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c275_CalculadorabotonenterPress,c262_CalculadorabotonenterRls,APP_GUI_BUT_CALC_ENTER_TSR_COORD,101,60,
//				CBKdummy,CBKbutEnterCalc,CBKdummy,APP_GUI_BUT_CALC_ENTER_PRS_COORD,APP_GUI_BUT_CALC_ENTER_RLS_COORD,c246_CalculadorabotonTsc,
//				0,0,0,0,0,0,0,0,0		},

//		{		ButCECalc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c279_CalculadorabotonCEPress,c261_CalculadorabotonCERls,APP_GUI_BUT_CALC_CE_TSR_COORD,60,60,
//				CBKbutCECalc,CBKdummy,CBKdummy,APP_GUI_BUT_CALC_CE_PRS_COORD,APP_GUI_BUT_CALC_CE_RLS_COORD,c246_CalculadorabotonTsc,
//				0,0,0,0,0,0,0,0,0		},

//		{		butComaCalc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c278_CalculadorabotoncomaPress,c263_CalculadorabotoncomaRls,APP_GUI_BUT_CALC_COMA_TSR_COORD,60,60,
//				CBKdummy,CBKdummy,CBKdummy,APP_GUI_BUT_CALC_COMA_PRS_COORD,APP_GUI_BUT_CALC_COMA_RLS_COORD,c246_CalculadorabotonTsc,
//				0,0,0,0,0,0,0,0,0		},
				
//			//  Menu  Principal
//		{		butCalcScrShowMainMenu,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER1,
//				b008_SwMenuRls,b008_SwMenuRls,APP_GUI_BUT_MENU_GLOBAL_TSR_COORD,97,57,
//				CBKdummy,CBKbutMainMenuShow,CBKdummy,APP_GUI_BUT_MENU_GLOBAL_PRS_COORD,APP_GUI_BUT_MENU_GLOBAL_RLS_COORD,b009_TscSwMenuRls,
//				0,0,0,0,0,0,0,0,0		},
//		{		butCalcScrHideMainMenu,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER1,
//				b010_SwMenuPress,b010_SwMenuPress,APP_GUI_BUT_MENU_GLOBAL_2_TSR_COORD,47,48,
//				CBKdummy,CBKbutMainMenuHide,CBKdummy,APP_GUI_BUT_MENU_GLOBAL_2_PRS_COORD,APP_GUI_BUT_MENU_GLOBAL_2_RLS_COORD,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		butCalcScrHome,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				b013_BotonHomePress,b014_BotonHomeRls,APP_GUI_BUT_HOME_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutHome,CBKdummy,APP_GUI_BUT_HOME_GLOBAL_PRS_COORD,APP_GUI_BUT_HOME_GLOBAL_RLS_COORD,b015_TscBotonHome,
//				0,0,0,0,0,0,0,0,0		},
//		{		butCalcScrCfg,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				b016_BotonConfigPress,b017_BotonConfigRls,APP_GUI_BUT_CONFIG_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutConfig,CBKdummy,APP_GUI_BUT_CONFIG_GLOBAL_PRS_COORD,APP_GUI_BUT_CONFIG_GLOBAL_RLS_COORD,b019_TscBotonConfig,
//				0,0,0,0,0,0,0,0,0		},
//		{		imgCalcScrCalc,APP_GUI_CALCULATOR_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				b020_BotonCalculadoraMarcaAgua,APP_GUI_BUT_CALCULADORA_GLOBAL_RLS_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		butCalcScrData,APP_GUI_CALCULATOR_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				b025_BotonIdiomasPress,b024_BotonIdiomasMarcaAgua/*b026_BotonIdiomasRls*/,APP_GUI_BUT_IDIOMAS_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutData,CBKdummy,APP_GUI_BUT_IDIOMAS_GLOBAL_PRS_COORD,APP_GUI_BUT_IDIOMAS_GLOBAL_RLS_COORD,b027_TscBotonIdiomas,
//				0,0,0,0,0,0,0,0,0		},
				
//		//avisos
						
//		{		SwCalcScrAvisos,APP_GUI_CALCULATOR_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				b029_BotonAvisosPress,b030_BotonAvisosRls,b029_BotonAvisosPress,b030_BotonAvisosRls,
//				APP_GUI_BUT_AVISOS_GLOBAL_TSR_COORD, 62,62, CBKbutWarningOn, CBKbutWarningOff,APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD,
//				APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD,APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD,APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD, b031_TscBotonAvisos,
//				0,0,0,0},
//		{		ImgCalcScrNotificacion,APP_GUI_CALCULATOR_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				b032_ImgNotificacion,APP_GUI_IMG_AVISO_PENDIENTE_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//		{		PopupCalcScrAvisos,APP_GUI_CALCULATOR_SCREEN, APP_GUI_POPUP_ID ,1,0,0, APP_GUI_LAYER1,
//				0, 0, APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM,0,APP_GUI_POPUP_DISABLE_ALL_WIDGETS,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//		{		imgPopUpCalcScrAvisoBckGND,APP_GUI_CALCULATOR_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				c420_Menualarmasfondo,APP_GUI_IMG_AVISO_POPUP_BCKGND_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCalcScrAvisoNivelAguaBajo,APP_GUI_CALCULATOR_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c425_Menualarmasinaguapress,APP_GUI_IMG_AVISO_POPUP_NIVEL_AGUA_BAJO_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCalcScrAvisoNivelAguaMedio,APP_GUI_CALCULATOR_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c424_Menualarmaaguamitadpress,APP_GUI_IMG_AVISO_POPUP_NIVEL_AGUA_MEDIO_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCalcScrAvisoTempAmb,APP_GUI_CALCULATOR_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c421_Menualarmatemppress,APP_GUI_IMG_AVISO_POPUP_TEMP_AMB_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCalcScrAvisoRFID,APP_GUI_CALCULATOR_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c423_Menualarmarfidpress,APP_GUI_IMG_AVISO_POPUP_RFID_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCalcScrAvisoRTC,APP_GUI_CALCULATOR_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c426_Menualarmatiempopress,APP_GUI_IMG_AVISO_POPUP_RTC_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCalcScrAvisoFiltroAire,APP_GUI_CALCULATOR_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c422_Menualarmafiltropress,APP_GUI_IMG_AVISO_POPUP_FILTRO_AIRE_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//				//CONFIGURACIÓN
//		{		imgFondoCfgScreen,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER0,
//				c280_BackCalculadorafondo,APP_GUI_IMG_FONDO_CFG_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVentanaCfgCastellano,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c317_FondoConfiguracion,APP_GUI_IMG_VENTANA_CFG_CASTELLANO_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		butCfgActualizarSoftware,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c324_ConfgBotondownloadPress,c323_ConfgBotondownloadRls,APP_GUI_BUT_CFG_SOFTW_UPDATE_TSR_COORD,53,48,
//				CBKdummy,CBKbutSoftUpdateCfg,CBKdummy,APP_GUI_BUT_CFG_SOFTW_UPDATE_PRS_COORD,APP_GUI_BUT_CFG_SOFTW_UPDATE_RLS_COORD,c325_ConfgBotondownloadTsc,
//				0,0,0,0,0,0,0,0,0		},
//		{		imgSoftwareProgressionUpdateBar,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER2,
//				c233_ImgPixelBlanco,APP_GUI_CONFIG_UPDATE_BAR_PROGRESSION_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//		{		NumVwrModeloMaqCfg,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER2,
//				APP_GUI_LAYER3,10,1,9,19,1,APP_GUI_NUM_VWR_MODELO_MAQ_CFG_COORD,101,42,c233_ImgPixelBlanco,
//				c336_Configuracionnumero0,c326_Configuracionnumero1,c327_Configuracionnumero2,c328_Configuracionnumero3,c329_Configuracionnumero4,c330_Configuracionnumero5,c331_Configuracionnumero6,c332_Configuracionnumero7,c333_Configuracionnumero8,c334_Configuracionnumero9,c335_Configuracionguion,c335_Configuracionguion	},
			
//		{		NumVwrVersionSoftwareCfg,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER2,
//				APP_GUI_LAYER3,6,1,9,19,1,APP_GUI_NUM_VWR_VERSION_SOFWARE_CFG_COORD,101,42,c233_ImgPixelBlanco,
//				c336_Configuracionnumero0,c326_Configuracionnumero1,c327_Configuracionnumero2,c328_Configuracionnumero3,c329_Configuracionnumero4,c330_Configuracionnumero5,c331_Configuracionnumero6,c332_Configuracionnumero7,c333_Configuracionnumero8,c334_Configuracionnumero9,c335_Configuracionguion,c335_Configuracionguion	},

//		{		butCfgRecargaCoolant,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c324_2_ConfigBotonRecargaCoolantPress,c323_2_ConfigBotonRecargaCoolantRls,APP_GUI_BUT_CFG_COOLANT_RECHARGE_TSR_COORD,53,48,
//				CBKdummy,CBKbutRecargaCoolant,CBKdummy,APP_GUI_BUT_CFG_COOLANT_RECHARGE_PRS_COORD,APP_GUI_BUT_CFG_COOLANT_RECHARGE_RLS_COORD,c325_2_ConfigBotonRecargaCoolantTsc,
//				0,0,0,0,0,0,0,0,0		},
				
//		{		SwCfgResuctionViewer,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_SW_ID,0,0,0,APP_GUI_LAYER2,
//				c513_resuccionboton_Press,c514_resuccionboton_Rls,c513_resuccionboton_Press,c514_resuccionboton_Rls,
//				APP_GUI_BUT_CFG_RESUCTION_VIEWER_TSR_COORD, 62,62, CBKswResuctionsVierew, CBKswResuctionsVierew,APP_GUI_BUT_CFG_RESUCTION_VIEWER_PRS_COORD,
//				APP_GUI_BUT_CFG_RESUCTION_VIEWER_PRS_COORD,APP_GUI_BUT_CFG_RESUCTION_VIEWER_PRS_COORD,APP_GUI_BUT_CFG_RESUCTION_VIEWER_PRS_COORD, c325_3_ConfigSwitchResuctionViewerTsc,
//				0,0,0,0},
				
//		{		SwCfgTemperatureViewer,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_SW_ID,0,0,0,APP_GUI_LAYER2,
//				c512_TempShowboton_Press,c512_TempShowboton_Rls,c512_TempShowboton_Press,c512_TempShowboton_Rls,
//				APP_GUI_BUT_CFG_TEMPERATURE_VIEWER_TSR_COORD, 50,31, CBKswCfgTemperatureViewer, CBKswCfgTemperatureViewer,APP_GUI_BUT_CFG_TEMPERATURE_VIEWER_PRS_COORD,
//				APP_GUI_BUT_CFG_TEMPERATURE_VIEWER_PRS_COORD,APP_GUI_BUT_CFG_TEMPERATURE_VIEWER_PRS_COORD,APP_GUI_BUT_CFG_TEMPERATURE_VIEWER_PRS_COORD, c325_3_ConfigSwitchResuctionViewerTsc,
//				0,0,0,0},
		
//		{		butCfgCleanUpHP1,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c522LimpiezamanipuloHP1_Press,c521_LimpiezamanipuloHP1_Rls,APP_GUI_BUT_CFG_CLEANUP_HP1_COORD,43,43,
//				CBKdummy,CBKbutCleanUpHP,CBKdummy,APP_GUI_BUT_CFG_CLEANUP_HP1_COORD,APP_GUI_BUT_CFG_CLEANUP_HP1_COORD,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		butCfgCleanUpHP2,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c525_LimpiezamanipuloHP2_Press,c524_LimpiezamanipuloHP2_Rls,APP_GUI_BUT_CFG_CLEANUP_HP2_COORD,43,43,
//				CBKdummy,CBKbutCleanUpHP,CBKdummy,APP_GUI_BUT_CFG_CLEANUP_HP2_COORD,APP_GUI_BUT_CFG_CLEANUP_HP2_COORD,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		butCfgCleanUpHP3,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c520_LimpiezamanipuloHP3_Press,c518_LimpiezamanipuloHP3_Rls,APP_GUI_BUT_CFG_CLEANUP_HP3_COORD,43,43,
//				CBKdummy,CBKbutCleanUpHP,CBKdummy,APP_GUI_BUT_CFG_CLEANUP_HP3_COORD,APP_GUI_BUT_CFG_CLEANUP_HP3_COORD,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		butCfgCleanUpHP4,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c528_LimpiezamanipuloHP4_Press,c527_LimpiezamanipuloHP4_Rls,APP_GUI_BUT_CFG_CLEANUP_HP4_COORD,43,43,
//				CBKdummy,CBKbutCleanUpHP,CBKdummy,APP_GUI_BUT_CFG_CLEANUP_HP4_COORD,APP_GUI_BUT_CFG_CLEANUP_HP4_COORD,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		butCfgCleanUpRoundHP,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER2,
//				c515_Limpiezamanipulox4_Press,c516_Limpiezamanipulox4_Rls,APP_GUI_BUT_CFG_CLEANUP_HP_ROUND_COORD,60,60,
//				CBKdummy,CBKbutCleanUpHPround,CBKdummy,APP_GUI_BUT_CFG_CLEANUP_HP_ROUND_COORD,APP_GUI_BUT_CFG_CLEANUP_HP_ROUND_COORD,c325_2_ConfigBotonRecargaCoolantTsc,
//				0,0,0,0,0,0,0,0,0		},
//		{		imgCfgGPRScoverage,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER1,
//				c610_GPRS_no_coverage,APP_GUI_CFG_IMG_GPRS_COVERAGE_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},	//V7790
				
//			//Menu Principal
//		{		butCfgScrShowMainMenu,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER1,
//				b008_SwMenuRls,b008_SwMenuRls,APP_GUI_BUT_MENU_GLOBAL_TSR_COORD,97,57,
//				CBKdummy,CBKbutMainMenuShow,CBKdummy,APP_GUI_BUT_MENU_GLOBAL_PRS_COORD,APP_GUI_BUT_MENU_GLOBAL_RLS_COORD,b009_TscSwMenuRls,
//				0,0,0,0,0,0,0,0,0		},
//		{		butCfgScrHideMainMenu,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				b010_SwMenuPress,b010_SwMenuPress,APP_GUI_BUT_MENU_GLOBAL_2_TSR_COORD,47,48,
//				CBKdummy,CBKbutMainMenuHide,CBKdummy,APP_GUI_BUT_MENU_GLOBAL_2_PRS_COORD,APP_GUI_BUT_MENU_GLOBAL_2_RLS_COORD,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		butCfgScrHome,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER3,
//				b013_BotonHomePress,b014_BotonHomeRls,APP_GUI_BUT_HOME_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutHome,CBKdummy,APP_GUI_BUT_HOME_GLOBAL_PRS_COORD,APP_GUI_BUT_HOME_GLOBAL_RLS_COORD,b015_TscBotonHome,
//				0,0,0,0,0,0,0,0,0		},
//		{		imgCfgScrCfg,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				b018_BotonConfigMarcaAgua,APP_GUI_BUT_CONFIG_GLOBAL_RLS_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		butCfgScrCalc,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER3,
//				b021_BotonCalculadoraPress,b022_BotonCalculadoraRls,APP_GUI_BUT_CALCULADORA_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutCalc,CBKdummy,APP_GUI_BUT_CALCULADORA_GLOBAL_PRS_COORD,APP_GUI_BUT_CALCULADORA_GLOBAL_RLS_COORD,b023_TscBotonCalculadora,
//				0,0,0,0,0,0,0,0,0		},
//		{		butCfgScrData,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER3,
//				b025_BotonIdiomasPress,b024_BotonIdiomasMarcaAgua/*b026_BotonIdiomasRls*/,APP_GUI_BUT_IDIOMAS_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutData,CBKdummy,APP_GUI_BUT_IDIOMAS_GLOBAL_PRS_COORD,APP_GUI_BUT_IDIOMAS_GLOBAL_RLS_COORD,b027_TscBotonIdiomas,
//				0,0,0,0,0,0,0,0,0		},
						
//		//avisos
						
//		{		SwCfgScrAvisos,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				b029_BotonAvisosPress,b030_BotonAvisosRls,b029_BotonAvisosPress,b030_BotonAvisosRls,
//				APP_GUI_BUT_AVISOS_GLOBAL_TSR_COORD, 62,62, CBKbutWarningOn, CBKbutWarningOff,APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD,
//				APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD,APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD,APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD, b031_TscBotonAvisos,
//				0,0,0,0},
//		{		ImgCfgScrNotificacion,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				b032_ImgNotificacion,APP_GUI_IMG_AVISO_PENDIENTE_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//		{		PopupCfgScrAvisos,APP_GUI_CONFIGURATION_SCREEN, APP_GUI_POPUP_ID ,1,0,0, APP_GUI_LAYER1,
//				0, 0, APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM,0,APP_GUI_POPUP_DISABLE_ALL_WIDGETS,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//		{		imgPopUpCfgScrAvisoBckGND,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				c420_Menualarmasfondo,APP_GUI_IMG_AVISO_POPUP_BCKGND_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCfgScrAvisoNivelAguaBajo,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c425_Menualarmasinaguapress,APP_GUI_IMG_AVISO_POPUP_NIVEL_AGUA_BAJO_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCfgScrAvisoNivelAguaMedio,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c424_Menualarmaaguamitadpress,APP_GUI_IMG_AVISO_POPUP_NIVEL_AGUA_MEDIO_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCfgScrAvisoTempAmb,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c421_Menualarmatemppress,APP_GUI_IMG_AVISO_POPUP_TEMP_AMB_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCfgScrAvisoRFID,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c423_Menualarmarfidpress,APP_GUI_IMG_AVISO_POPUP_RFID_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCfgScrAvisoRTC,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c426_Menualarmatiempopress,APP_GUI_IMG_AVISO_POPUP_RTC_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpCfgScrAvisoFiltroAire,APP_GUI_CONFIGURATION_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				c422_Menualarmafiltropress,APP_GUI_IMG_AVISO_POPUP_FILTRO_AIRE_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//				//IDIOMAS
//		{		imgFondoLanScreen,APP_GUI_LANGUAGES_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER0,
//				c280_BackCalculadorafondo,APP_GUI_IMG_FONDO_LAN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
								
//		{		SwLanFrances,APP_GUI_LANGUAGES_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c295_IdiomasfrancesPress,c294_IdiomasfrancesRls,c295_IdiomasfrancesPress,c294_IdiomasfrancesRls,
//				APP_GUI_BUT_LAN_FRANCES_TSR_COORD, 114,122, CBKswLanguage, CBKdummy,APP_GUI_BUT_LAN_FRANCES_PRS_COORD,
//				APP_GUI_BUT_LAN_FRANCES_PRS_COORD,APP_GUI_BUT_LAN_FRANCES_PRS_COORD,APP_GUI_BUT_LAN_FRANCES_PRS_COORD, c296_TscIdiomasgeneral,
//				0,0,0,0},
//		{		SwLanCastellano,APP_GUI_LANGUAGES_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c298_IdiomascastellanoPress,c297_IdiomascastellanoRls,c298_IdiomascastellanoPress,c297_IdiomascastellanoRls,
//				APP_GUI_BUT_LAN_CASTELLANO_TSR_COORD, 114,122, CBKswLanguage, CBKdummy,APP_GUI_BUT_LAN_CASTELLANO_PRS_COORD,
//				APP_GUI_BUT_LAN_CASTELLANO_PRS_COORD,APP_GUI_BUT_LAN_CASTELLANO_PRS_COORD,APP_GUI_BUT_LAN_CASTELLANO_PRS_COORD, c296_TscIdiomasgeneral,
//				0,0,0,0},
//		{		SwLanIngles,APP_GUI_LANGUAGES_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c300_IdiomasinglesPress,c299_IdiomasinglesRls,c300_IdiomasinglesPress,c299_IdiomasinglesRls,
//				APP_GUI_BUT_LAN_INGLES_TSR_COORD, 114,122, CBKswLanguage, CBKdummy,APP_GUI_BUT_LAN_INGLES_PRS_COORD,
//				APP_GUI_BUT_LAN_INGLES_PRS_COORD,APP_GUI_BUT_LAN_INGLES_PRS_COORD,APP_GUI_BUT_LAN_INGLES_PRS_COORD, c296_TscIdiomasgeneral,
//				0,0,0,0},
//		{		SwLanItaliano,APP_GUI_LANGUAGES_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c302_IdiomasitalianoPress,c301_IdiomasitalianoRls,c302_IdiomasitalianoPress,c301_IdiomasitalianoRls,
//				APP_GUI_BUT_LAN_ITALIANO_TSR_COORD, 114,122, CBKswLanguage, CBKdummy,APP_GUI_BUT_LAN_ITALIANO_PRS_COORD,
//				APP_GUI_BUT_LAN_ITALIANO_PRS_COORD,APP_GUI_BUT_LAN_ITALIANO_PRS_COORD,APP_GUI_BUT_LAN_ITALIANO_PRS_COORD, c296_TscIdiomasgeneral,
//				0,0,0,0},
//		{		SwLanAleman,APP_GUI_LANGUAGES_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c304_IdiomasalemanPress,c303_IdiomasalemanRls,c304_IdiomasalemanPress,c303_IdiomasalemanRls,
//				APP_GUI_BUT_LAN_ALEMAN_TSR_COORD, 114,122, CBKswLanguage, CBKdummy,APP_GUI_BUT_LAN_ALEMAN_PRS_COORD,
//				APP_GUI_BUT_LAN_ALEMAN_PRS_COORD,APP_GUI_BUT_LAN_ALEMAN_PRS_COORD,APP_GUI_BUT_LAN_ALEMAN_PRS_COORD, c296_TscIdiomasgeneral,
//				0,0,0,0},
//		{		SwLanPolaco,APP_GUI_LANGUAGES_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c306_IdiomaspolacoPress,c305_IdiomaspolacoRls,c306_IdiomaspolacoPress,c305_IdiomaspolacoRls,
//				APP_GUI_BUT_LAN_POLACO_TSR_COORD, 114,122, CBKswLanguage, CBKdummy,APP_GUI_BUT_LAN_POLACO_PRS_COORD,
//				APP_GUI_BUT_LAN_POLACO_PRS_COORD,APP_GUI_BUT_LAN_POLACO_PRS_COORD,APP_GUI_BUT_LAN_POLACO_PRS_COORD, c296_TscIdiomasgeneral,
//				0,0,0,0},
//		{		SwLanRuso,APP_GUI_LANGUAGES_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c308_IdiomasrusoPress,c307_IdiomasrusoRls,c308_IdiomasrusoPress,c307_IdiomasrusoRls,
//				APP_GUI_BUT_LAN_RUSO_TSR_COORD, 114,122, CBKswLanguage, CBKdummy,APP_GUI_BUT_LAN_RUSO_PRS_COORD,
//				APP_GUI_BUT_LAN_RUSO_PRS_COORD,APP_GUI_BUT_LAN_RUSO_PRS_COORD,APP_GUI_BUT_LAN_RUSO_PRS_COORD, c296_TscIdiomasgeneral,
//				0,0,0,0},
//		{		SwLanPortugues,APP_GUI_LANGUAGES_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c310_IdiomasportuguesPress,c309_IdiomasportuguesRls,c310_IdiomasportuguesPress,c309_IdiomasportuguesRls,
//				APP_GUI_BUT_LAN_PORTUGUES_TSR_COORD, 114,122, CBKswLanguage, CBKdummy,APP_GUI_BUT_LAN_PORTUGUES_PRS_COORD,
//				APP_GUI_BUT_LAN_PORTUGUES_PRS_COORD,APP_GUI_BUT_LAN_PORTUGUES_PRS_COORD,APP_GUI_BUT_LAN_PORTUGUES_PRS_COORD, c296_TscIdiomasgeneral,
//				0,0,0,0},
//		{		SwLanChino,APP_GUI_LANGUAGES_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c312_IdiomaschinoPress,c311_IdiomaschinoRls,c312_IdiomaschinoPress,c311_IdiomaschinoRls,
//				APP_GUI_BUT_LAN_CHINO_TSR_COORD, 114,122, CBKswLanguage, CBKdummy,APP_GUI_BUT_LAN_CHINO_PRS_COORD,
//				APP_GUI_BUT_LAN_CHINO_PRS_COORD,APP_GUI_BUT_LAN_CHINO_PRS_COORD,APP_GUI_BUT_LAN_CHINO_PRS_COORD, c296_TscIdiomasgeneral,
//				0,0,0,0},
//		{		SwLanJapones,APP_GUI_LANGUAGES_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c314_IdiomasjaponesPress,c313_IdiomasjaponesRls,c314_IdiomasjaponesPress,c313_IdiomasjaponesRls,
//				APP_GUI_BUT_LAN_JAPONES_TSR_COORD, 114,122, CBKswLanguage, CBKdummy,APP_GUI_BUT_LAN_JAPONES_PRS_COORD,
//				APP_GUI_BUT_LAN_JAPONES_PRS_COORD,APP_GUI_BUT_LAN_JAPONES_PRS_COORD,APP_GUI_BUT_LAN_JAPONES_PRS_COORD, c296_TscIdiomasgeneral,
//				0,0,0,0},
//		{		SwLanCoreano,APP_GUI_LANGUAGES_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c316_IdiomascoreanoPress,c315_IdiomascoreanoRls,c316_IdiomascoreanoPress,c315_IdiomascoreanoRls,
//				APP_GUI_BUT_LAN_COREANO_TSR_COORD, 114,122, CBKswLanguage, CBKdummy,APP_GUI_BUT_LAN_COREANO_PRS_COORD,
//				APP_GUI_BUT_LAN_COREANO_PRS_COORD,APP_GUI_BUT_LAN_COREANO_PRS_COORD,APP_GUI_BUT_LAN_COREANO_PRS_COORD, c296_TscIdiomasgeneral,
//				0,0,0,0},



//			//Menu Principal
//		{		butLanScrShowMainMenu,APP_GUI_LANGUAGES_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER1,
//				b008_SwMenuRls,b008_SwMenuRls,APP_GUI_BUT_MENU_GLOBAL_TSR_COORD,97,57,
//				CBKdummy,CBKbutMainMenuShow,CBKdummy,APP_GUI_BUT_MENU_GLOBAL_PRS_COORD,APP_GUI_BUT_MENU_GLOBAL_RLS_COORD,b009_TscSwMenuRls,
//				0,0,0,0,0,0,0,0,0		},
//		{		butLanScrHideMainMenu,APP_GUI_LANGUAGES_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER1,
//				b010_SwMenuPress,b010_SwMenuPress,APP_GUI_BUT_MENU_GLOBAL_2_TSR_COORD,47,48,
//				CBKdummy,CBKbutMainMenuHide,CBKdummy,APP_GUI_BUT_MENU_GLOBAL_2_PRS_COORD,APP_GUI_BUT_MENU_GLOBAL_2_RLS_COORD,b011_TscSwMenuPress,
//				0,0,0,0,0,0,0,0,0		},
//		{		butLanScrHome,APP_GUI_LANGUAGES_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				b013_BotonHomePress,b014_BotonHomeRls,APP_GUI_BUT_HOME_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutHome,CBKdummy,APP_GUI_BUT_HOME_GLOBAL_PRS_COORD,APP_GUI_BUT_HOME_GLOBAL_RLS_COORD,b015_TscBotonHome,
//				0,0,0,0,0,0,0,0,0		},
//		{		butLanScrCfg,APP_GUI_LANGUAGES_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				b016_BotonConfigPress,b017_BotonConfigRls,APP_GUI_BUT_CONFIG_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutConfig,CBKdummy,APP_GUI_BUT_CONFIG_GLOBAL_PRS_COORD,APP_GUI_BUT_CONFIG_GLOBAL_RLS_COORD,b019_TscBotonConfig,
//				0,0,0,0,0,0,0,0,0		},
//		{		butLanScrCalc,APP_GUI_LANGUAGES_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER2,
//				b021_BotonCalculadoraPress,b022_BotonCalculadoraRls,APP_GUI_BUT_CALCULADORA_GLOBAL_TSR_COORD,67,69,
//				CBKdummy,CBKbutCalc,CBKdummy,APP_GUI_BUT_CALCULADORA_GLOBAL_PRS_COORD,APP_GUI_BUT_CALCULADORA_GLOBAL_RLS_COORD,b023_TscBotonCalculadora,
//				0,0,0,0,0,0,0,0,0		},
//		{		imgLanScrData,APP_GUI_LANGUAGES_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				b024_BotonIdiomasMarcaAgua,APP_GUI_BUT_IDIOMAS_GLOBAL_RLS_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//		//avisos
								
//		{		SwLanScrAvisos,APP_GUI_LANGUAGES_SCREEN,APP_GUI_SW_ID,1,0,0,APP_GUI_LAYER2,
//				b029_BotonAvisosPress,b030_BotonAvisosRls,b029_BotonAvisosPress,b030_BotonAvisosRls,
//				APP_GUI_BUT_AVISOS_GLOBAL_TSR_COORD, 62,62, CBKbutWarningOn, CBKbutWarningOff,APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD,
//				APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD,APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD,APP_GUI_BUT_AVISOS_GLOBAL_PRS_COORD, b031_TscBotonAvisos,
//				0,0,0,0},
//		{		ImgLanScrNotificacion,APP_GUI_LANGUAGES_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				b032_ImgNotificacion,APP_GUI_IMG_AVISO_PENDIENTE_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//		{		PopupLanScrAvisos,APP_GUI_LANGUAGES_SCREEN, APP_GUI_POPUP_ID ,1,0,0, APP_GUI_LAYER1,
//				0, 0, APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM,0,APP_GUI_POPUP_DISABLE_ALL_WIDGETS,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//		{		imgPopUpLanScrAvisoBckGND,APP_GUI_LANGUAGES_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				c420_Menualarmasfondo,APP_GUI_IMG_AVISO_POPUP_BCKGND_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpLanScrAvisoNivelAguaBajo,APP_GUI_LANGUAGES_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				c425_Menualarmasinaguapress,APP_GUI_IMG_AVISO_POPUP_NIVEL_AGUA_BAJO_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpLanScrAvisoNivelAguaMedio,APP_GUI_LANGUAGES_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				c424_Menualarmaaguamitadpress,APP_GUI_IMG_AVISO_POPUP_NIVEL_AGUA_MEDIO_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpLanScrAvisoTempAmb,APP_GUI_LANGUAGES_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				c421_Menualarmatemppress,APP_GUI_IMG_AVISO_POPUP_TEMP_AMB_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpLanScrAvisoRFID,APP_GUI_LANGUAGES_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				c423_Menualarmarfidpress,APP_GUI_IMG_AVISO_POPUP_RFID_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpLanScrAvisoRTC,APP_GUI_LANGUAGES_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				c426_Menualarmatiempopress,APP_GUI_IMG_AVISO_POPUP_RTC_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgPopUpLanScrAvisoFiltroAire,APP_GUI_LANGUAGES_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				c422_Menualarmafiltropress,APP_GUI_IMG_AVISO_POPUP_FILTRO_AIRE_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//// PANTALLA DE SAT
//		{		imgFondoSATscreen,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER0,
//				c280_BackCalculadorafondo,APP_GUI_IMG_FONDO_SAT_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		butHomeSATscreen,APP_GUI_SAT_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER1,
//				b014_BotonHomeRls,b013_BotonHomePress,APP_GUI_BUT_HOME_SAT_SCREEN_TSCR_COORD,67,69,
//				CBKdummy,CBKbutHome,CBKdummy,APP_GUI_BUT_HOME_SAT_SCREEN_PRS_COORD,APP_GUI_BUT_HOME_SAT_SCREEN_RLS_COORD,b015_TscBotonHome,
//				0,0,0,0,0,0,0,0,0		},
				
//		{		NumVwrPaginaSATscreen,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER3,3,3,16,35,1,APP_GUI_NUMVWR_PAGE_SAT_SCREEN_COORD,91,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c065_CaracterNegativo,c065_CaracterNegativo	},
				
//		{		butNextPagSATscreen,APP_GUI_SAT_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER1,
//				c200_BotonGuardarMenuRightRls,c199_BotonGuardarMenuRightPress,APP_GUI_BUT_NEXT_PAGE_SAT_SCREEN_TSCR_COORD,32,32,
//				CBKdummy/*PRS*/,CBKbutSATnextPage/*RLS*/,CBKdummy,APP_GUI_BUT_NEXT_PAGE_SAT_SCREEN_PRS_COORD,APP_GUI_BUT_NEXT_PAGE_SAT_SCREEN_RLS_COORD,c201_TscBotonGuardarMenu,
//				0,0,0,0,0,0,0,0,0		},
//		{		butPrevPagSATscreen,APP_GUI_SAT_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER1,
//				c203_BotonGuardarMenuLeftRls,c202_BotonGuardarMenuLeftPress,APP_GUI_BUT_PREV_PAGE_SAT_SCREEN_TSCR_COORD,32,32,
//				CBKdummy/*PRS*/,CBKbutSATprevPage/*RLS*/,CBKdummy,APP_GUI_BUT_PREV_PAGE_SAT_SCREEN_PRS_COORD,APP_GUI_BUT_PREV_PAGE_SAT_SCREEN_RLS_COORD,c201_TscBotonGuardarMenu,
//				0,0,0,0,0,0,0,0,0		},
		
//		{		imgVwr1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_NUMVWR_NUM_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_NUMVWR_NUM_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr3,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c054_Numero3,APP_GUI_NUMVWR_NUM_3_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr4,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c055_Numero4,APP_GUI_NUMVWR_NUM_4_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr5,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c056_Numero5,APP_GUI_NUMVWR_NUM_5_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr6,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c057_Numero6,APP_GUI_NUMVWR_NUM_6_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr7,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c058_Numero7,APP_GUI_NUMVWR_NUM_7_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
			
//		{		imgVwr8,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c059_Numero8,APP_GUI_NUMVWR_NUM_8_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr9,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c060_Numero9,APP_GUI_NUMVWR_NUM_9_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr10_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_NUMVWR_NUM_10_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr10_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c061_Numero0,APP_GUI_NUMVWR_NUM_10_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr11_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_NUMVWR_NUM_11_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr11_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_NUMVWR_NUM_11_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr12_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_NUMVWR_NUM_12_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr12_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_NUMVWR_NUM_12_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr13_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_NUMVWR_NUM_13_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr13_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c054_Numero3,APP_GUI_NUMVWR_NUM_13_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr14_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_NUMVWR_NUM_14_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr14_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c055_Numero4,APP_GUI_NUMVWR_NUM_14_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//		{		imgVwr15_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_NUMVWR_NUM_15_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr15_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c056_Numero5,APP_GUI_NUMVWR_NUM_15_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr16_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_NUMVWR_NUM_16_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr16_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c057_Numero6,APP_GUI_NUMVWR_NUM_16_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr17_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_NUMVWR_NUM_17_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr17_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c058_Numero7,APP_GUI_NUMVWR_NUM_17_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr18_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_NUMVWR_NUM_18_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr18_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c059_Numero8,APP_GUI_NUMVWR_NUM_18_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr19_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_NUMVWR_NUM_19_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr19_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c060_Numero9,APP_GUI_NUMVWR_NUM_19_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr20_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_NUMVWR_NUM_20_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr20_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c061_Numero0,APP_GUI_NUMVWR_NUM_20_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr21_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_NUMVWR_NUM_21_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr21_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_NUMVWR_NUM_21_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//		{		imgVwr22_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_NUMVWR_NUM_22_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr22_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_NUMVWR_NUM_22_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr23_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_NUMVWR_NUM_23_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr23_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c054_Numero3,APP_GUI_NUMVWR_NUM_23_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr24_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_NUMVWR_NUM_24_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr24_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c055_Numero4,APP_GUI_NUMVWR_NUM_24_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr25_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_NUMVWR_NUM_25_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr25_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c056_Numero5,APP_GUI_NUMVWR_NUM_25_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr26_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_NUMVWR_NUM_26_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr26_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c057_Numero6,APP_GUI_NUMVWR_NUM_26_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr27_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_NUMVWR_NUM_27_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr27_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c058_Numero7,APP_GUI_NUMVWR_NUM_27_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr28_1,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_NUMVWR_NUM_28_1_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwr28_2,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c059_Numero8,APP_GUI_NUMVWR_NUM_28_2_SAT_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//		{		NumVwr1,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER3,6,3,16,35,1,APP_GUI_NUMVWR_1_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr2,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER3,6,3,16,35,1,APP_GUI_NUMVWR_2_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr3,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER3,6,3,16,35,1,APP_GUI_NUMVWR_3_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr4,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER3,6,3,16,35,1,APP_GUI_NUMVWR_4_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr5,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER3,6,3,16,35,1,APP_GUI_NUMVWR_5_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr6,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER3,6,3,16,35,1,APP_GUI_NUMVWR_6_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr7,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER3,6,3,16,35,1,APP_GUI_NUMVWR_7_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},

//		{		NumVwr8,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_8_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr9,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_9_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr10,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_10_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr11,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_11_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr12,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_12_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr13,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_13_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr14,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_14_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
				
//		{		NumVwr15,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_15_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr16,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_16_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr17,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_17_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr18,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_18_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr19,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_19_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr20,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_20_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr21,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_21_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},

//		{		NumVwr22,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_22_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr23,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_23_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr24,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_24_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr25,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_25_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr26,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_26_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr27,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_27_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwr28,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_28_SAT_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},

//		{		imgVacuum,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c185_IndicadorVacHP1Off,APP_GUI_IMG_VACUUM_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgFrio,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c186_IndicadorFrioHP1Off,APP_GUI_IMG_FRIO_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgRFID,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c183_IndicadorRFIDHP1Off,APP_GUI_IMG_RFID_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgTestLed,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c438_HPalarmaPlicainsuficiente,APP_GUI_IMG_TEST_LED_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgTestLedStatus,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER2,
//				c453_MenuAlarmaOK_MarcaAgua,APP_GUI_IMG_TEST_LED_STATUS_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgTestLedRGD,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				b032_ImgNotificacion,APP_GUI_IMG_TEST_LED_RGB_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
				
//		{		SwVacuum,APP_GUI_SAT_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c044_BotonAutoPress,c045_BotonAutoRls,c044_BotonAutoPress,c045_BotonAutoRls,
//				APP_GUI_SW_VACUUM_COORD, 62,32, CBKswSATVacOn, CBKswSATVacOff,APP_GUI_SW_VACUUM_COORD,
//				APP_GUI_SW_VACUUM_COORD,APP_GUI_SW_VACUUM_COORD,APP_GUI_SW_VACUUM_COORD, c044_B_TscBotonAuto,
//				0,0,0,0},
//		{		SwFrio,APP_GUI_SAT_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c044_BotonAutoPress,c045_BotonAutoRls,c044_BotonAutoPress,c045_BotonAutoRls,
//				APP_GUI_SW_FRIO_COORD, 62,32, CBKswSATFrioOn, CBKswSATFrioOff,APP_GUI_SW_FRIO_COORD,
//				APP_GUI_SW_FRIO_COORD,APP_GUI_SW_FRIO_COORD,APP_GUI_SW_FRIO_COORD, c044_B_TscBotonAuto,
//				0,0,0,0},
//		{		SwRFID,APP_GUI_SAT_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c044_BotonAutoPress,c045_BotonAutoRls,c044_BotonAutoPress,c045_BotonAutoRls,
//				APP_GUI_SW_RFID_COORD, 62,32, CBKswSATrfidOn, CBKswSATrfidOff,APP_GUI_SW_RFID_COORD,
//				APP_GUI_SW_RFID_COORD,APP_GUI_SW_RFID_COORD,APP_GUI_SW_RFID_COORD, c044_B_TscBotonAuto,
//				0,0,0,0},
//		{		SwTestLed,APP_GUI_SAT_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c044_BotonAutoPress,c045_BotonAutoRls,c044_BotonAutoPress,c045_BotonAutoRls,
//				APP_GUI_SW_TEST_LED_COORD, 62,32, CBKswSATtestLedOn, CBKswSATtestLedOff,APP_GUI_SW_TEST_LED_COORD,
//				APP_GUI_SW_TEST_LED_COORD,APP_GUI_SW_TEST_LED_COORD,APP_GUI_SW_TEST_LED_COORD, c044_B_TscBotonAuto,
//				0,0,0,0},
//		{		SwTestLedRGB,APP_GUI_SAT_SCREEN,APP_GUI_SW_ID,1,1,1,APP_GUI_LAYER1,
//				c044_BotonAutoPress,c045_BotonAutoRls,c044_BotonAutoPress,c045_BotonAutoRls,
//				APP_GUI_SW_TEST_LED_RGB_COORD, 62,32, CBKswSATtestLedRGBOn, CBKswSATtestLedRGBOff,APP_GUI_SW_TEST_LED_RGB_COORD,
//				APP_GUI_SW_TEST_LED_RGB_COORD,APP_GUI_SW_TEST_LED_RGB_COORD,APP_GUI_SW_TEST_LED_RGB_COORD, c044_B_TscBotonAuto,
//				0,0,0,0},
		
//		{		PopupErrorSAT,APP_GUI_SAT_SCREEN, APP_GUI_POPUP_ID ,1,0,0, APP_GUI_LAYER3,
//				0, 0, APP_GUI_POPUP_ERRORES_SAT_WIDGET_LIST_NUM,0,APP_GUI_POPUP_DISABLE_ALL_WIDGETS,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwrFondoErrorSAT,APP_GUI_SAT_SCREEN,APP_GUI_IMG_VWR_ID,1,0,0,APP_GUI_LAYER3,
//				c234_AlarmaFondoCentral2,APP_GUI_FONDO_POPUP_ERRORES_SAT_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		NumVwrError1,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				APP_GUI_LAYER5,6,3,16,35,1,APP_GUI_NUMVWR1_POPUP_ERRORES_SAT_COORD,108,57,c461_FondoNumVwrError,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrError2,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				APP_GUI_LAYER5,6,3,16,35,1,APP_GUI_NUMVWR2_POPUP_ERRORES_SAT_COORD,108,57,c461_FondoNumVwrError,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrError3,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				APP_GUI_LAYER5,6,3,16,35,1,APP_GUI_NUMVWR3_POPUP_ERRORES_SAT_COORD,108,57,c461_FondoNumVwrError,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrError4,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				APP_GUI_LAYER5,6,3,16,35,1,APP_GUI_NUMVWR4_POPUP_ERRORES_SAT_COORD,108,57,c461_FondoNumVwrError,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrError5,APP_GUI_SAT_SCREEN,APP_GUI_NUM_VWR_ID,1,0,0,APP_GUI_LAYER4,
//				APP_GUI_LAYER5,6,3,16,35,1,APP_GUI_NUMVWR5_POPUP_ERRORES_SAT_COORD,108,57,c461_FondoNumVwrError,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		butOkerr,APP_GUI_SAT_SCREEN,APP_GUI_BUT_ID,1,0,0,APP_GUI_LAYER4,
//				c357_BotonAlarmaCentralOkPress,c356_BotonAlarmaCentralOkRls,APP_GUI_BUT_OK_POPUP_ERRORES_SAT_COORD,80,76,
//				CBKdummy/*PRS*/,CBKbutOkSATerr/*RLS*/,CBKdummy,APP_GUI_BUT_OK_POPUP_ERRORES_SAT_COORD,APP_GUI_BUT_OK_POPUP_ERRORES_SAT_COORD,c358_BotonAlarmaCentralOkTsc,
//				0,0,0,0,0,0,0,0,0		},
				
				
//		// PANTALLA DE FATIGA
//		{		imgFondoFATIGAscreen,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER0,
//				c280_BackCalculadorafondo,APP_GUI_IMG_FONDO_SAT_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		butHomeFATIGAscreen,APP_GUI_FATIGUE_SCREEN,APP_GUI_BUT_ID,1,1,1,APP_GUI_LAYER1,
//				b014_BotonHomeRls,b013_BotonHomePress,APP_GUI_BUT_HOME_SAT_SCREEN_TSCR_COORD,67,69,
//				CBKdummy,CBKbutHome,CBKdummy,APP_GUI_BUT_HOME_SAT_SCREEN_PRS_COORD,APP_GUI_BUT_HOME_SAT_SCREEN_RLS_COORD,b015_TscBotonHome,
//				0,0,0,0,0,0,0,0,0		},

//		{		imgStep1,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_NUMVWR_NUM_1_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep1status,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c149_ZonaAplicacionManipPuntoSelected,APP_GUI_NUMVWR_STATUS_1_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep2,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_NUMVWR_NUM_2_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep2status,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c149_ZonaAplicacionManipPuntoSelected,APP_GUI_NUMVWR_STATUS_2_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep3,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c054_Numero3,APP_GUI_NUMVWR_NUM_3_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep3status,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c149_ZonaAplicacionManipPuntoSelected,APP_GUI_NUMVWR_STATUS_3_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep4,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c055_Numero4,APP_GUI_NUMVWR_NUM_4_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep4statusHP1,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c149_ZonaAplicacionManipPuntoSelected,APP_GUI_NUMVWR_STATUS_41_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep4statusHP2,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c149_ZonaAplicacionManipPuntoSelected,APP_GUI_NUMVWR_STATUS_42_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep4statusHP3,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c149_ZonaAplicacionManipPuntoSelected,APP_GUI_NUMVWR_STATUS_43_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep4statusHP4,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c149_ZonaAplicacionManipPuntoSelected,APP_GUI_NUMVWR_STATUS_44_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep5,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c056_Numero5,APP_GUI_NUMVWR_NUM_5_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep5statusHP1,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c149_ZonaAplicacionManipPuntoSelected,APP_GUI_NUMVWR_STATUS_51_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep5statusHP2,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c149_ZonaAplicacionManipPuntoSelected,APP_GUI_NUMVWR_STATUS_52_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep5statusHP3,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c149_ZonaAplicacionManipPuntoSelected,APP_GUI_NUMVWR_STATUS_53_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep5statusHP4,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c149_ZonaAplicacionManipPuntoSelected,APP_GUI_NUMVWR_STATUS_54_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep6,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,0,0,0,APP_GUI_LAYER1,
//				c057_Numero6,APP_GUI_NUMVWR_NUM_6_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep6status,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,0,0,0,APP_GUI_LAYER1,
//				c149_ZonaAplicacionManipPuntoSelected,APP_GUI_NUMVWR_STATUS_6_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep7,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,0,0,0,APP_GUI_LAYER1,
//				c058_Numero7,APP_GUI_NUMVWR_NUM_7_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgStep7status,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,0,0,0,APP_GUI_LAYER1,
//				c149_ZonaAplicacionManipPuntoSelected,APP_GUI_NUMVWR_STATUS_7_FATIGUE_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//		{		NumVwrTempAmb,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_TEMPAMB_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrTempBomba,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_TEMPBOMBA_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrTempRetorno,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,6,16,35,1,APP_GUI_NUMVWR_FAT_TEMPRETORNO_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrCaudalRetorno,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_CAUDALRETORNO_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrVtobera,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_VTOBERA_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrRth,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_RTH_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrCPI,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_CPI_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
		
//		{		NumVwrCaudalRetornoHP1,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_CAUDALRETORNO_HP1_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrCaudalRetornoHP2,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_CAUDALRETORNO_HP2_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrCaudalRetornoHP3,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_CAUDALRETORNO_HP3_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrCaudalRetornoHP4,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_CAUDALRETORNO_HP4_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},

//		{		NumVwrVacuumHP1,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_VACUUM_HP1_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrVacuumHP2,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_VACUUM_HP2_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrVacuumHP3,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_VACUUM_HP3_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrVacuumHP4,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_VACUUM_HP4_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
				
//		{		NumVwrFatigaTime,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_TIME_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
				
//		{		imgVwrVAC1,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_IMGVWR_FAT_VACUUM_HP1_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwrVAC2,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_IMGVWR_FAT_VACUUM_HP2_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwrVAC3,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c054_Numero3,APP_GUI_IMGVWR_FAT_VACUUM_HP3_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwrVAC4,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c055_Numero4,APP_GUI_IMGVWR_FAT_VACUUM_HP4_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwrCaudal1,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_IMGVWR_FAT_CAUDALRETORNO_HP1_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwrCaudal2,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_IMGVWR_FAT_CAUDALRETORNO_HP2_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwrCaudal3,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c054_Numero3,APP_GUI_IMGVWR_FAT_CAUDALRETORNO_HP3_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwrCaudal4,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c055_Numero4,APP_GUI_IMGVWR_FAT_CAUDALRETORNO_HP4_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwrTempAmb,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c052_Numero1,APP_GUI_IMGVWR_FAT_TEMPAMB_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwrTempBomba,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c053_Numero2,APP_GUI_IMGVWR_FAT_TEMPBOMBA_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwrTempRetorno,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c054_Numero3,APP_GUI_IMGVWR_FAT_TEMPRETORNO_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwrCaudalRetorno,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c055_Numero4,APP_GUI_IMGVWR_FAT_CAUDALRETORNO_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwrVtobera,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c056_Numero5,APP_GUI_IMGVWR_FAT_VTOBERA_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwrRth,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c057_Numero6,APP_GUI_IMGVWR_FAT_RTH_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},
//		{		imgVwrCPI,APP_GUI_FATIGUE_SCREEN,APP_GUI_IMG_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				c058_Numero7,APP_GUI_IMGVWR_FAT_CPI_SCREEN_COORD,
//				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		},

//		{		NumVwrErrFatiga1,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_ERR_1_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrErrFatiga2,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_ERR_2_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrErrFatiga3,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_ERR_3_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrErrFatiga4,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_ERR_4_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
//		{		NumVwrErrFatiga5,APP_GUI_FATIGUE_SCREEN,APP_GUI_NUM_VWR_ID,1,1,1,APP_GUI_LAYER1,
//				APP_GUI_LAYER2,6,3,16,35,1,APP_GUI_NUMVWR_FAT_ERR_5_SCREEN_COORD,108,57,c047_FondoNumVwrBlanco,
//				c061_Numero0,c052_Numero1,c053_Numero2,c054_Numero3,c055_Numero4,c056_Numero5,c057_Numero6,c058_Numero7,c059_Numero8,c060_Numero9,c064_CaracterPunto,c064_CaracterPunto	},
				
//		{		SwFatigueFailBeep,APP_GUI_FATIGUE_SCREEN,APP_GUI_SW_ID,1,0,1,APP_GUI_LAYER1,
//				b028_BotonAvisosMarcaAgua,b028_BotonAvisosMarcaAgua,b028_BotonAvisosMarcaAgua,b028_BotonAvisosMarcaAgua,
//				APP_GUI_BUT_FATIGUE_FAIL_BELL_FATIGUE_SCREEN_RLS_COORD, 62,32, CBKswFATIGUEfailBelloff, CBKswFATIGUEfailBelloff,APP_GUI_BUT_FATIGUE_FAIL_BELL_FATIGUE_SCREEN_RLS_COORD,
//				APP_GUI_BUT_FATIGUE_FAIL_BELL_FATIGUE_SCREEN_RLS_COORD,APP_GUI_BUT_FATIGUE_FAIL_BELL_FATIGUE_SCREEN_RLS_COORD,APP_GUI_BUT_FATIGUE_FAIL_BELL_FATIGUE_SCREEN_RLS_COORD, b027_TscBotonIdiomas,
//				0,0,0,0},
//};

