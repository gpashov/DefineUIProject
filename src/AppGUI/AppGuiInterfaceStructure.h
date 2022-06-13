/*
 * AppGuiInterfaceStructure.h
 *
 *  Created on: Mar 25, 2019
 *      Author: ingenieria9
 */

#ifndef APPGUIINTERFACESTRUCTURE_H_
#define APPGUIINTERFACESTRUCTURE_H_

#include <QObject>

#include "GeneralDefines.h"
//#include "PE_Types.h"
#include "../Perifericos/HPcryo.h"
//#include "../GUI/K70_GUI.h"
//#include "../Error/gestionError.h"

#define APP_GUI_NO_TIME_SELECTED 						((cHPcryoTrtTimes)0xFF)
#define APP_GUI_NO_VAC_LVL_SELECTED						((cHPcryoTrtVacLvls)0xFF)
#define APP_GUI_NO_TRT_DOT_SELECTED						0xFF
#define APP_GUI_MAX_DOTS_PER_AREA						15
#define APP_GUI_LOAD_SCR_ANIM_TIME						500
#define APP_GUI_LOAD_SCR_ANIM_IMG_NUM 					8
#define APP_GUI_MAIN_MENU_WID_WHEN_SHOW_NUM				6 
#define APP_GUI_MAIN_MENU_WID_WHEN_HIDE_NUM				1 
#define APP_GUI_POPUP_TIME_WIDGET_LIST_NUM 				4
#define APP_GUI_POPUP_TST_VAC_WIDGET_LIST_NUM 			16/*17*/
#define APP_GUI_POPUP_TST_VAC_SMALL_WIDGET_LIST_NUM 	4
#define APP_GUI_POPUP_RFID_WIDGET_LIST_NUM 				7
#define APP_GUI_POPUP_RECOMMENDATION_WIDGET_LIST_NUM 	11	
#define APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM			8
#define APP_GUI_POPUP_MAQ_CLEAN_WIDGET_LIST_NUM 		3	
#define APP_GUI_POPUP_ERRORES_SAT_WIDGET_LIST_NUM		8			
#define APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_SHOW_NUM		15
#define APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_HIDE_NUM		1
#define APP_GUI_TRT_SCR_CTRL_PNL_COLOUR_STATES_IMGS		2
#define APP_GUI_TRT_SCR_POPUP_TST_VAC_SW_NUM			3
#define APP_GUI_TRT_SCR_NUM_POPUPS						6
#define APP_GUI_NUM_ERR_WIDGETS_WHEN_HP					5
#define APP_GUI_NUM_ERR_WIDGETS_WHEN_UC					4
#define APP_GUI_MAX_DIGITS_CALC_SCREEN					6
#define APP_GUI_CALC_SPECIAL_ACTION_CODE				33
#define APP_GUI_CALC_DECODIFICATION_FACTOR				10000
#define APP_GUI_TRT_LOAD_NEW_HP_IMG						2

#define APP_GUI_TRT_CLEAN_UP_TIMER						1.00

#define APP_GUI_TRT_END_TRT_BEEP_TOUT					15000
#define APP_GUI_TRT_TIME_TO_BEEP						1.00

#define APP_GUI_SAT_MAX_NUMVWR					28

#define APP_GUI_SAT_ERRORES_PERIFS			5

//PDTE: Esto deberia estar definido en GUI.h y NO ESTAR AQUI!!
#define APP_GUI_WIDGETS_FEATURES	GUIfields

#define APP_GUI_BUT_ID				1
#define APP_GUI_SW_ID				2
#define APP_GUI_IMG_VWR_ID 			3
#define APP_GUI_NUM_VWR_ID			4
#define APP_GUI_POPUP_ID			5

#define APP_GUI_POPUP_DISABLE_ALL_WIDGETS	0
#define APP_GUI_POPUP_DISABLE_WIDGET_LIST	1

#define APP_GUI_POPUP_DISPLAYED_MAP_NUM     10
//PDTE: Esto deberia estar definido en GUI.h


/*** DEFINICIONES DE CONSTANTES ***/
namespace AppEnumsNs
{
    Q_NAMESPACE

    typedef enum EAppGUI_HPsIDs
    {
        APP_GUI_HP1_ID,
        APP_GUI_HP2_ID,
        APP_GUI_HP3_ID,
        APP_GUI_HP4_ID,
        APP_GUI_MAXNUM_HP		//Número máximo de manipulos
    } cAppGUI_HPsIds;
    Q_ENUM_NS(EAppGUI_HPsIDs)

    typedef enum EAppGUI_FATIGA_steps
    {
        CheckFilter,
        CheckSETA,
        CheckRFID,
        CheckConnectionHP1,
        CheckConnectionHP2,
        CheckConnectionHP3,
        CheckConnectionHP4,
        CheckTreatmentHP1,
        CheckTreatmentHP2,
        CheckTreatmentHP3,
        CheckTreatmentHP4,
        ENDofTreatmentHP,

        MaxFatigueSteps
    }cAppGUI_FATIGA_steps;
//    Q_ENUM_NS(EAppGUI_FATIGA_steps)

    typedef enum EAppGUI_SATscreen_Pages
    {
        HP1_Page = 1,
        HP2_Page,
        HP3_Page,
        HP4_Page,
        MachinePage,
        HP_Commands_Page,
        MachineDefPage,

        MaxNumSATpages
    }cAppGUI_SATscreen_Pages;
//    Q_ENUM_NS(EAppGUI_SATscreen_Pages)

    typedef enum EAppGUIcfgScrLoadingNewFW
    {
        App_GUI_CfgScr_FW_loading_0,
        App_GUI_CfgScr_FW_loading_20,
        App_GUI_CfgScr_FW_loading_40,
        App_GUI_CfgScr_FW_loading_60,
        App_GUI_CfgScr_FW_loading_80,
        App_GUI_CfgScr_FW_loading_100,

        App_GUI_CfgScr_FW_loading_max
    }cAppGUIcfgScrLoadingNewFW;
//    Q_ENUM_NS(EAppGUIcfgScrLoadingNewFW)

    typedef enum EAppGUImachineWarnings
    {
        App_GUI_Wng_Nivel_Agua_Bajo,
        App_GUI_Wng_Nivel_Agua_Medio,
        App_GUI_Wng_Temp_Amb,
        App_GUI_Wng_RFID,
        App_GUI_Wng_RTC,
        App_GUI_Wng_Filtro_Aire,

        App_GUI_Num_Max_Avisos
    }cAppGUImachineWarnings;
//    Q_ENUM_NS(EAppGUImachineWarnings)

    typedef enum EApp_GUI_differentLanguages
    {
        App_GUI_Sin_idioma,

        App_GUI_Frances,
        App_GUI_Castellano,
        App_GUI_Ingles,
        App_GUI_Italiano,
        App_GUI_Aleman,
        App_GUI_Polaco,
        App_GUI_Ruso,
        App_GUI_Portugues,
        App_GUI_Chino,
        App_GUI_Japones,
        App_GUI_Coreano,

        App_GUI_Different_Languages
    }cApp_GUI_differentLanguages;
//    Q_ENUM_NS(EApp_GUI_differentLanguages)

    typedef enum EApp_GUI_differentCountries
    {
        App_GUI_Sin_pais,

        App_GUI_USA,
        App_GUI_CHINA,
        App_GUI_JAPON,
        App_GUI_ESPANA,
        App_GUI_GREAT_BRITAIN,
        App_GUI_IRELAND,
        App_GUI_NETHERLAND,
        App_GUI_ALEMANIA,
        App_GUI_ITALIA,
        App_GUI_FRANCIA,

        App_GUI_OTROS,

        App_GUI_Different_Countries
    }cApp_GUI_differentCountries;
//    Q_ENUM_NS(EApp_GUI_differentCountries)

    typedef enum EAppGUIVacSmallPopUpwidgetsCoordinates
    {
        App_GUI_VacLowLevel,
        App_GUI_VacMedLevel,
        AppGUI_VacHighLevel,
        AppGUI_VacLevelSelector,

        App_GUI_PopUpVacWidgetCoordinates
    }cAppGUIVacSmallPopUpwidgetsCoordinates;
//    Q_ENUM_NS(EAppGUIVacSmallPopUpwidgetsCoordinates)

    typedef enum EAppGUITimePopUpwidgetsCoordinates
    {
        App_GUI_1selTime,
        App_GUI_2selTime,
        AppGUI_selector,

        App_GUI_PopUpTimeWidgetCoordinates
    }cAppGUITimePopUpwidgetsCoordinates;
//    Q_ENUM_NS(EAppGUITimePopUpwidgetsCoordinates)

    typedef enum EAppGUIctrMenuBut
    {
        App_GUI_but_Play,
        App_GUI_but_Vacc,
        App_GUI_but_Time,

        App_GUI_Max_num_but
    }cAppGUIctrMenuBut;
//    Q_ENUM_NS(EAppGUIctrMenuBut)

    typedef enum EAppGUIdifferentWidgetFeatures
    {
        App_GUI_widget_PRS_img,
        App_GUI_widget_RLS_img,
        App_GUI_widget_ENABLE,

        App_GUI_widget_Features
    }cAppGUIdifferentWidgetFeatures;
//    Q_ENUM_NS(EAppGUIdifferentWidgetFeatures)

    typedef enum EAppGUIsmallTSTvacuumButStates
    {
        App_GUI_but_On,
        App_GUI_but_MarcaAgua,
        App_GUI_but_max
    }cAppGUIsmallTSTvacuumButStates;
//    Q_ENUM_NS(EAppGUIsmallTSTvacuumButStates)

    typedef enum EAppGUIPlayButStates
    {
        App_GUI_Play_but_Off,
        App_GUI_Play_but_On,
        App_GUI_Play_but_TRT_running,
        App_GUI_Play_but_TRT_cancel,
        App_GUI_Play_but_disabled,

        App_GUI_Max_Play_but_states
    }cAppGUIPlayButStates;
//    Q_ENUM_NS(EAppGUIPlayButStates)

    typedef enum EAppGUIVacButStates
    {
        App_GUI_Vac_but_Off_Left,
        App_GUI_Vac_but_Off_Right,
        App_GUI_Vac_but_On_Left,
        App_GUI_Vac_but_On_Right,
        App_GUI_Vac_but_VacAjust_Left,
        App_GUI_Vac_but_VacAjust_Right,
        App_GUI_Vac_but_disabled,

        App_GUI_Max_Vac_but_states
    }cAppGUIVacButStates;
//    Q_ENUM_NS(EAppGUIVacButStates)

    typedef enum EAppGUITimeButStates
    {
        App_GUI_Time_but_Off,
        App_GUI_Time_but_On,
        App_GUI_Time_but_disabled,

        App_GUI_Max_Time_but_states
    }cAppGUITimeButStates;
//    Q_ENUM_NS(EAppGUITimeButStates)

//    typedef enum EAppGUIwidgetCoordinates
//    {
//        Coordinate_X,
//        Coordinate_Y,
//        Max_coordinates
//    }cAppGUIwidgetCoordinates;
//    Q_ENUM_NS(EAppGUIwidgetCoordinates)

    typedef enum EAppGUIcalcCodes		//Codigos de calculadora
    {
        AppGUIcalc_NOT_USED,

        AppGUIcalc_RTC_time,	/*1*/
        AppGUIcalc_RTC_date,	/*2*/
        AppGUIcalc_Vaciado,		/*3 - No se usa*/
        AppGUIcalc_Llenado,		/*4*/
        AppGUIcalc_SATscreen,	/*5*/
        AppGUIcalc_FATIGAscreen,/*6*/

        AppGUIcalc_ProgCurved 		= 11,
        AppGUIcalc_ProgTight 		= 12,
        AppGUIcalc_ProgStright 		= 13,
        AppGUIcalc_ProgTiny 		= 14,
        AppGUIcalc_ProgTinyCurved 	= 15,
        AppGUIcalc_ProgDouble 		= 16,
        AppGUIcalc_ProgOval 		= 17,
        AppGUIcalc_ProgOvalCurved 	= 18,
        AppGUIcalc_ProgAngled 		= 19,

        AppGUIcalc_OscTempIDLEenable	= 35,
        AppGUIcalc_OscTempIDLEdisable	= 36,

        AppGUIcalc_ReuseLabelEnable		= 40,
        AppGUIcalc_ReuseLabelDisable	= 41,

        AppGUIcalc_TempSlopeEnable		=43,
        AppGUIcalc_TempSlopeDisable		=44,

        AppGUIcalc_TempSecureEnable		=46,
        AppGUIcalc_TempSecureDisable	=47,

        AppGUIcalc_ErrSecureEnable		=49,
        AppGUIcalc_ErrSecureDisable		=50,

        AppGUIcalc_ErrSecureDeltaTempEnable = 52,
        AppGUIcalc_ErrSecureDeltaTempDisable = 53,

    //	AppGUIcalc_LangSelectionEnable = 55,
    //	AppGUIcalc_LangSelectionDisable = 56,


        AppGUIcalc_EraseLOG = 58,
        AppGUIcalc_SendASCII_LOG = 60,
        AppGUIcalc_Send_USB_ASCII_LOG = 62,
        AppGUIcalc_SendRAW_LOG = 64,
        AppGUIcalc_Send_USB_RAW_LOG = 66,
        AppGUIcalc_SendRecent_LOG = 68,
        AppGUIcalc_Send_USB_Recent_LOG = 70,

        AppGUIcalc_RecordLOG_enable = 72,
        AppGUIcalc_RecordLOG_disable = 74,

        AppGUIcalc_GPRS_Del_country = 98, //#JM_GPRS V7790 Borrar los paises pero conservar que la maquina tiene placa
        AppGUIcalc_GPRS_Clear = 99, //#JM_GPRS V7790
        APPGUIcalc_MAX_NUM_CODES
    }cAppGUIcalcCodes;
//    Q_ENUM_NS(EAppGUIcalcCodes)

    typedef enum EAppGUIbodys
    {
        AppGUIbodyMale,
        AppGUIbodyFemale,
        APP_GUI_NUM_BODYS
    }cAppGUIbodys;
    Q_ENUM_NS(EAppGUIbodys)

    typedef enum EAppGUIfullBodyAreas
    {
        AppGUIfullBodyNO_AREA,
        AppGUIfullBodyTorso,
        AppGUIfullBodyPiernas,
        AppGUIfullBodyEspalda,
        AppGUIfullBodyPiernasMuslo,
        AppGUIfullBodyBrazos,
        AppGUIfullBodyCuello,
        APP_GUI_NUM_FULL_BODY_AREAS,
    }cAppGUIfullBodyAreas;
    Q_ENUM_NS(EAppGUIfullBodyAreas)

    typedef enum EAppGUIprsRls
    {
        AppGUIprs,
        AppGUIrls,
        APP_GUI_MAX_PRS_RLS
    }cAppGUIprsRls;
//    Q_ENUM_NS(EAppGUIprsRls)

    typedef enum EAppGUIonOff
    {
        AppGUIoff,
        AppGUIon,
        APP_GUI_MAX_ON_OFF
    }cAppGUIonOff;
//    Q_ENUM_NS(EAppGUIonOff)

    typedef enum EAppGUItstVacDone
    {
        AppGUItstVacNotDone,
        AppGUItstVacDone,
        APP_GUI_MAX_TST_VAC_DONE
    }cAppGUItstVacDone;
//    Q_ENUM_NS(EAppGUItstVacDone)

    typedef enum EAppGUIblinkIndicators
    {
        AppGUIblinkRFID,
        AppGUIblinkPul,
        AppGUIblinkVac,
        AppGUIblinkCooling,
        APP_GUI_MAX_BLINK_INDICATORS
    }cAppGUIblinkIndicators;
//    Q_ENUM_NS(EAppGUIblinkIndicators)

//    // Número de capas.
//    typedef enum EAppGUIlayers
//    {
//        APP_GUI_LAYER0,
//        APP_GUI_LAYER1,
//        APP_GUI_LAYER2,
//        APP_GUI_LAYER3,
//        APP_GUI_LAYER4,
//        APP_GUI_LAYER5,
//        APP_GUI_LAYER6,
//        APP_GUI_LAYER7,
//        APP_GUI_LAYER8,
//        APP_GUI_LAYER9,
//        APP_GUI_NUM_LAYERS,
//    }cAppGUIlayers;
//    Q_ENUM_NS(EAppGUIlayers)

    typedef enum EAppGUIscreen
    {
        APP_GUI_LOAD_SCREEN,
        APP_GUI_INIT_SCREEN,
        APP_GUI_TREATMENT_SCREEN,
        APP_GUI_CALCULATOR_SCREEN,
        APP_GUI_CONFIGURATION_SCREEN,
        APP_GUI_LANGUAGES_SCREEN,
        APP_GUI_SAT_SCREEN,
        APP_GUI_FATIGUE_SCREEN,
        APP_GUI_NUM_SCREENS
    }cAppGUIscreen;
    Q_ENUM_NS(EAppGUIscreen)

    typedef enum EAppGUIcleanUpStatus
    {
        APP_GUI_CLEAN_UP_COUNTDOWN,
        APP_GUI_CLEAN_UP_WAIT_USER,
        APP_GUI_CLEAN_UP_CLEANING,
        APP_GUI_CLEAN_UP_WAIT_VACUM,
        APP_GUI_CLEAN_UP_N_STATUS
    }cAppGUIcleanUpStatus;

    //Zonas de seleccion del tratamiento
    typedef enum
    {
        NO_ZONA,

        PliegueAxilarIzquierdo,
        PliegueAxilarDerecho,
        IntrapectoralIzquierdo,
        IntrapectoralDerecho,
        AbdominalSupraumbricalIzquierdo,
        AbdominalSupraumbricalCentral,
        AbdominalSupraumbricalDerecho,
        AbdominalInfraumbricalIzquierdo,
        AbdominalInfraumbricalCentral,
        AbdominalInfraumbricalDerecho,
        CaderaIzquierdo,
        CaderaDerecho,
        Pubis,
        SenoIzquierdo,
        SenoDerecho,

        TrocantereaIzquierdo,
        TrocantereaDerecho,
        CaraInternaMusloIzquierdo,
        CaraInternaMusloDerecho,
        SuperioRodillaIzquierda,
        SuperiorRodillaDerecha,
        IntRodillaIzquierda,
        IntRodillaDerecha,

        BrazoIzquierdo,
        BrazoDerecho,

        SupraescapularIzquierda,
        SupraescapularDerecha,
        InfraescapularIzquierda,
        InfraescapularDerecha,
        FlancoIzquierdo,
        FlancoDerecho,

        GluteoIzquierdo,
        GluteoDerecho,
        SubgluteoIzquierdo,
        SubgluteoDerecho,
        MusloPosteriorIzquierdo,
        MusloPosterioDerecho,

        PapadaCentral,
        PapadaLateralIzquierdo,
        PapadaLateralDerecho,

        MaxZonas, // Zonas de aplicación tratamiento. La primera zona no se utiliza

        ZonaInit,

    }cAppGUItrtZones;

    typedef enum
    {
        NoGrupo,

        PliegueAxilar,
        Senos,
        Intrapectoral,
        AbdominalSupraumbrical,
        AbdominalInfraumbrical,
        Cadera,

        Trocantereal,
        CaraInternaMuslo,
        SuperiorRodilla,
        InteriorRodilla,

        Brazo,

        Supraescapular,
        Infraescapular,
        Flanco,

        Gluteo,
        Subgluteo,
        MusloPosterior,

        Papada,

        MaxGrupoZonas

    }cAppGUItrtAgrupacionZones;

    /*** LISTADO DE IMAGENES Y WIDGETS ***/
    // Imágenes de la Interface
//    typedef enum EAppGUIimageIDlist
//    {
    //	a001_FondoLogoCooltechDefine,
    //	a002_CargaLogotipo1,
    //	a003_CargaLogotipo2,
    //	a004_CargaLogotipo3,
    //	a005_CargaLogotipo4,
    //	a006_CargaLogotipo5,
    //	a007_CargaLogotipo6,
    //	a008_CargaLogotipo7,
    //	a009_CargaLogotipo8,
    //	b001_FondoLogoSiluetasHombreMujer,
    //	b002_BotonFemeninoPress,
    //	b003_BotonFemeninoRls,
    //	b004_TscBotonFemenino,
    //	b005_BotonMasculinoPress,
    //	b006_BotonMasculinoRls,
    //	b007_TscBotonMasculino,
    //	b008_SwMenuRls,
    //	b009_TscSwMenuRls,
    //	b010_SwMenuPress,
    //	b011_TscSwMenuPress,
    //	b012_BotonHomeMarcaAgua,
    //	b012_BotonHomeMarcaAgua1,
    //	b013_BotonHomePress,
    //	b014_BotonHomeRls,
    //	b015_TscBotonHome,
    //	b016_BotonConfigPress,
    //	b017_BotonConfigRls,
    //	b018_BotonConfigMarcaAgua,
    //	b018_BotonConfigMarcaAgua1,
    //	b019_TscBotonConfig,
    //	b020_BotonCalculadoraMarcaAgua,
    //	b020_BotonCalculadoraMarcaAgua1,
    //	b021_BotonCalculadoraPress,
    //	b022_BotonCalculadoraRls,
    //	b023_TscBotonCalculadora,
    //	b024_BotonIdiomasMarcaAgua,
    //	b024_BotonIdiomasMarcaAgua1,
    //	b025_BotonIdiomasPress,
    //	b026_BotonIdiomasRls,
    //	b027_TscBotonIdiomas,
    //	b028_BotonAvisosMarcaAgua,
    //	b028_BotonAvisosMarcaAgua1,
    //	b029_BotonAvisosPress,
    //	b030_BotonAvisosRls,
    //	b031_TscBotonAvisos,
    //	b032_ImgNotificacion,
    //	b032_ImgNotificacion2,
    //	c001_FondoLogo,
    //	c002_SiluetaMujerFrenteEspalda,
    //	c003_SiluetaHombreFrenteEspalda,
    //	c004_MenuTrtHP1,
    //	c005_MenuTrtHP1_Aro2,
    //	c005_TscMenuTrtHP1Rls,
    //	c005__MenuTrtHP1_Aro1,
    //	c006_MenuTrtHP1Press,
    //	c007_TscMenuTrtHP1Press,
    //	c012_MenuTrtHP2,
    //	c013_MenuTrtHP2_Aro1,
    //	c013_MenuTrtHP2_Aro2,
    //	c013_TscMenuTrtHP2Rls,
    //	c014_MenuTrtHP2Press,
    //	c015_TscMenuTrtHP2Press,
    //	c020_MenuTrtHP3,
    //	c021_MenuTrtHP3_Aro1,
    //	c021_MenuTrtHP3_Aro2,
    //	c021_TscMenuTrtHP3Rls,
    //	c022_MenuTrtHP3Press,
    //	c023_TscMenuTrtHP3Press,
    //	c028_MenuTrtHP4,
    //	c029_MenuTrtHP4_Aro1,
    //	c029_MenuTrtHP4_Aro2,
    //	c029_TscMenuTrtHP4Rls,
    //	c030_MenuTrtHP4Press,
    //	c031_TscMenuTrtHP4Press,
    //	c033_BotonStopPress,
    //	c034_BotonStopRls,
    //	c035_BotonPlayPress,
    //	c036_BotonPlayPress,
    //	c037_BotonPlayRls,
    //	c038_BotonPlayMarcaAgua,
    //	c039_TscBotonPlay,
    //	c040_BotonVacuum1PressLeft,
    //	c040_BotonVacuum1PressRight,
    //	c040_BotonVacuum2PressLeft,
    //	c040_BotonVacuum2PressRight,
    //	c040_BotonVacuum3PressLeft,
    //	c040_BotonVacuum3PressRight,
    //	c041_BotonVacuum1RlsLeft,
    //	c041_BotonVacuum1RlsRight,
    //	c041_BotonVacuum2RlsLeft,
    //	c041_BotonVacuum2RlsRight,
    //	c041_BotonVacuum3RlsLeft,
    //	c041_BotonVacuum3RlsRight,
    //	c042_BotonVacuum1MarcaAguaLeft,
    //	c042_BotonVacuum1MarcaAguaRight,
    //	c042_BotonVacuum2MarcaAguaLeft,
    //	c042_BotonVacuum2MarcaAguaRight,
    //	c042_BotonVacuum3MarcaAguaLeft,
    //	c042_BotonVacuum3MarcaAguaRight,
    //	c043_TscBotonVacuum,
    //	c044_BotonAutoPress,
    //	c044_B_TscBotonAuto,
    //	c045_BotonAutoRls,
    //	c046_Auto,
    //	c047_FondoNumVwrBlanco,
    //	c047_FondoTemporizador,
    //	c048_RelojTemporizadorPress,
    //	c049_RelojTemporizadorRls,
    //	c050_RelojTemporizadorMarcaAgua,
    //	c051_TscrRelojTemporizador,
    //	c052_Numero1,
    //	c053_Numero2,
    //	c054_Numero3,
    //	c055_Numero4,
    //	c056_Numero5,
    //	c057_Numero6,
    //	c058_Numero7,
    //	c059_Numero8,
    //	c060_Numero9,
    //	c061_Numero0,
    //	c062_CaracterDosPuntos,
    //	c063_CaracterComa,
    //	c064_CaracterPunto,
    //	c065_CaracterNegativo,
    //	c066_NameCurvedHP_L,
    //	c066_NameCurvedHP_R,
    //	c067_NameTightHP_L,
    //	c067_NameTightHP_R,
    //	c068_NameStarightHP_L,
    //	c068_NameStraightHP_R,
    //	c069_NameTinyHP_L,
    //	c069_NameTinyHP_R,
    //	c070_NameTinyCurvedHP_L,
    //	c070_NameTinyCurvedHP_R,
    //	c071_NameDoubleHP_L,
    //	c071_NameDoubleHP_R,
    //	c072_NameOvalHP_L,
    //	c072_NameOvalHP_R,
    //	c073_NameOvalCurvedHP_L,
    //	c073_NameOvalCurvedHP_R,
    //	c074_NameDeltaHP_L,
    //	c074_NameDeltaHP_R,
    //	c075_ImgCurvedHP_R_Rls,
    //	c076_ImgCurvedHP_L_Rls,
    //	c077_ImgTightHP_R_Rls,
    //	c078_ImgTightHP_L_Rls,
    //	c079_ImgStrightHP_R_Rls,
    //	c080_ImgStrightHP_L_Rls,
    //	c081_ImgTinyHP_R_Rls,
    //	c082_ImgTinyHP_L_Rls,
    //	c083_ImgTinyCurvedHP_R_Rls,
    //	c084_ImgTinyCurvedHP_L_Rls,
    //	c085_ImgDoubleHP_R_Rls,
    //	c086_ImgDoubleHP_L_Rls,
    //	c087_ImgOvalHP_R_Rls,
    //	c088_ImgOvalHP_L_Rls,
    //	c089_ImgOvalCurvedHP_R_Rls,
    //	c090_ImgOvalCurvedHP_L_Rls,
    //	c091_ImgAngledHP_R_Rls,
    //	c092_ImgAngledHP_L_Rls,
    //	c093_ImgCurvedHP_R_Press,
    //	c094_ImgCurvedHP_L_Press,
    //	c095_ImgTightHP_R_Press,
    //	c096_ImgTightHP_L_Press,
    //	c097_ImgStrightHP_R_Press,
    //	c098_ImgStrightHP_L_Press,
    //	c099_ImgTinyHP_R_Press,
    //	c100_ImgTinyHP_L_Press,
    //	c101_ImgTinyCurvedHP_R_Press,
    //	c102_ImgTinyCurvedHP_L_Press,
    //	c103_ImgDoubleHP_R_Press,
    //	c104_ImgDoubleHP_L_Press,
    //	c105_ImgOvalHP_R_Press,
    //	c106_ImgOvalHP_L_Press,
    //	c107_ImgOvalCurvedHP_R_Press,
    //	c108_ImgOvalCurvedHP_L_Press,
    //	c109_ImgAngledHP_R_Press,
    //	c110_ImgAngledHP_L_Press,
    //	c111_signorelojdown,
    //	c111_signorelojup,
    //	c111_TscImgMan,
    //	c112_1_ZonaSeleccionadaHP1,
    //	c112_2_ZonaSeleccionadaHP2,
    //	c112_3_ZonaSeleccionadaHP3,
    //	c112_4_ZonaSeleccionadaHP4,
    //	c113_BotonTorsoPressMujer,
    //	c114_TscBotonTorsoMujer,
    //	c115_BotonPiernasRlsMujer,
    //	c117_TscBotonPiernasMujer,
    //	c118_BotonBrazosRlsMujer,
    //	c120_TscBotonBrazosMujer,
    //	c121_BotonEspaldaRlsMujer,
    //	c123_TscBotonEspladaMujer,
    //	c124_BotonPiernaMusloRlsMujer,
    //	c126_TscBotonPiernaMusloMujer,
    //	c127_BotonCuelloRlsMujer,
    //	c129_TscBotonCuelloMujer,
    //	c130_BotonTorsoRlsHombre,
    //	c132_TscBotonTorsoHombre,
    //	c133_BotonPiernasRlsHombre,
    //	c135_TscBotonPiernasHombre,
    //	c136_BotonBrazosRlsHombre,
    //	c138_TscBotonBrazosHombre,
    //	c139_BotonEspaldaRlsHombre,
    //	c141_TscBotonEspladaHombre,
    //	c142_BotonPiernaMusloRlsHombre,
    //	c144_TscBotonPiernaMusloHombre,
    //	c145_BotonCuelloRlsHombre,
    //	c147_TscBotonCuelloHombre,
    //	c148_ZonaAplicacionManipPunto,
    //	c149_ZonaAplicacionManipPuntoSelected,
    //	c150_TscZonaAplicacionManipPunto,
    //	c151_ZonaAplicacionManipPuntoHP1,
    //	c152_ZonaAplicacionManipPuntoHP2,
    //	c153_ZonaAplicacionManipPuntoHP3,
    //	c154_ZonaAplicacionManipPuntoHP4,
    //	c155_RetrocesoRls,
    //	c156_RetrocesoPress,
    //	c157_OkeyRls,
    //	c158_OkeyPress2,
    //	c159_TscOkey_Retroceso,
    //	c160_ZonaSeleccionadaHP1,
    //	c160_ZonaSeleccionadaHP1_seleccionado,
    //	c161_ZonaSeleccionadaHP2,
    //	c161_ZonaSeleccionadaHP2_seleccionado,
    //	c162_ZonaSeleccionadaHP3,
    //	c162_ZonaSeleccionadaHP3_seleccionado,
    //	c163_ZonaSeleccionadaHP4,
    //	c163_ZonaSeleccionadaHP4_seleccionado,
    //	c164_PopUpImagenReloj,
    //	c164_Z_PopUpImagenReloj,
    //	c165_PopUpBoton50MinRls,
    //	c166_PopUpBoton50MinPress,
    //	c167_PopUpBoton70MinRls,
    //	c168_PopUpBoton70MinPress,
    //	c169_TscPopUpBoton70and45,
    //	c170_PopUpImagenSuccion,
    //	c176_PopUpBotonTestRls,
    //	c177_PopUpBotonTestPress,
    //	c178_TscPopUpBotonTest,
    //	c179_PopupBotonActivarRls,
    //	c180_PopupBotonActivarPress,
    //	c181_PopupBotonActivarTsc,
    //	c182_PopUpRFIDfail,
    //	c182_PopUpRFIDFondo,
    //	c182_PopUpRFIDlabelDM,
    //	c182_PopUpRFIDlabelZ0,
    //	c182_PopUpRFIDlabelZ1,
    //	c182_PopUpRFIDlabelZ2,
    //	c182_PopUpRFIDlabelZ3,
    //	c182_PopUpRFIDsuccess,
    //	c182_PopUpRFIDunknown,
    //	c182_PopUpRFIDwrong,
    //	c183_IndicadorRFIDHP1Off,
    //	c184_IndicadorBotonHP1Off,
    //	c185_IndicadorVacHP1Off,
    //	c186_IndicadorFrioHP1Off,
    //	c187_IndicadorRFIDHP2Off,
    //	c188_IndicadorBotonHP2Off,
    //	c189_IndicadorVacHP2Off,
    //	c190_IndicadorFrioHP2Off,
    //	c191_IndicadorRFIDHP3Off,
    //	c192_IndicadorBotonHP3Off,
    //	c193_IndicadorVacHP3Off,
    //	c194_IndicadorFrioHP3Off,
    //	c195_IndicadorRFIDHP4Off,
    //	c196_IndicadorBotonHP4Off,
    //	c197_IndicadorVacHP4Off,
    //	c198_IndicadorFrioHP4Off,
    //	c199_BotonGuardarMenuRightPress,
    //	c200_BotonGuardarMenuRightRls,
    //	c201_TscBotonGuardarMenu,
    //	c202_BotonGuardarMenuLeftPress,
    //	c203_BotonGuardarMenuLeftRls,
    //	c205_ImgTorsoMujer,
    //	c206_ImgPiernasMujer,
    //	c207_BrazosEspaldaMujer,
    //	c208_PiernaMusloMujer,
    //	c209_CuelloMujer,
    //	c210_TorsoHombre,
    //	c211_PiernasHombre,
    //	c212_BrazosEspaldaHombre,
    //	c213_PiernaMusloHombre,
    //	c214_CuelloHombre,
    //	c216_PopUpManipHP1,
    //	c217_PopUpManipHP2,
    //	c218_PopUpManipHP3,
    //	c219_PopUpManipHP4,
    //	c220_PopUpBotonAuto,
    //	c221_PopUpBotonAutoPress,
    //	c221_Z_PopupBotonAutoTsc,
    //	c222_B_PopUpIndmanoPressx2,
    //	c222_PopUpIndmanoPress,
    //	c233_ImgPixelBlanco,
    //	c234_AlarmaFondoCentral2,
    //	c234_AlarmaFondoHP1,
    //	c234_AlarmaFondoHP2,
    //	c234_AlarmaFondoHP3,
    //	c234_AlarmaFondoHP4,
    //	c237_Calculadoraboton1Rls,
    //	c238_Calculadoraboton2Rls,
    //	c239_Calculadoraboton3Rls,
    //	c240_Calculadoraboton4Rls,
    //	c241_Calculadoraboton5Rls,
    //	c242_Calculadoraboton6Rls,
    //	c243_Calculadoraboton7Rls,
    //	c244_Calculadoraboton8Rls,
    //	c245_Calculadoraboton9Rls,
    //	c246_CalculadorabotonTsc,
    //	c247_Calculadoraboton0Rls,
    //	c248_Calculadoraboton0Tsc,
    //	c249_Calculadoranumero1,
    //	c250_Calculadoranumero2,
    //	c251_Calculadoranumero3,
    //	c252_Calculadoranumero4,
    //	c253_Calculadoranumero5,
    //	c254_Calculadoranumero6,
    //	c255_Calculadoranumero7,
    //	c256_Calculadoranumero8,
    //	c257_Calculadoranumero9,
    //	c258_Calculadoranumero0,
    //	c259_CalculadorabotonmasRls,
    //	c260_CalculadorabotonmenosRls,
    //	c261_CalculadorabotonCERls,
    //	c262_CalculadorabotonenterRls,
    //	c263_CalculadorabotoncomaRls,
    //	c264_CalculadorabotonenterTsc,
    //	c265_Calculadorafondo_03,
    //	c266_Calculadoraboton1Press,
    //	c267_Calculadoranumero2Press,
    //	c268_Calculadoraboton3Press,
    //	c269_Calculadoraboton4Press,
    //	c270_Calculadoraboton5Press,
    //	c271_Calculadoranumero6Press,
    //	c272_Calculadoraboton7Press,
    //	c273_Calculadoraboton8Press,
    //	c274_Calculadoranumero9Press,
    //	c275_Calculadoraboton0Press,
    //	c275_CalculadorabotonenterPress,
    //	c276_CalculadorabotonmasPress,
    //	c277_CalculadorabotonmenosPress,
    //	c278_CalculadorabotoncomaPress,
    //	c279_CalculadorabotonCEPress,
    //	c280_BackCalculadorafondo,
    //	c281_InfoRls,
    //	c282_InfoPress,
    //	c283_TscInfo,
    //	c284_PopUpSugerenciasFondo_03,
    //	c285_PopUpMarcaaguaCurved,
    //	c286_PopUpMarcaaguaTight,
    //	c287_PopUpMarcaaguaStraight,
    //	c288_PopUpMarcaaguaTiny,
    //	c289_PopUpMarcaaguaTinyCurved,
    //	c290_PopUpMarcaaguaDouble,
    //	c291_PopUpMarcaaguaOval,
    //	c292_PopUpMarcaaguaOvalCurved,
    //	c293_PopUpMarcaaguaAngled,

    //	c294_IdiomasfrancesRls,
    //	c295_IdiomasfrancesPress,
    //	c296_TscIdiomasgeneral,
    //	c297_IdiomascastellanoRls,
    //	c298_IdiomascastellanoPress,
    //	c299_IdiomasinglesRls,
    //	c300_IdiomasinglesPress,
    //	c301_IdiomasitalianoRls,
    //	c302_IdiomasitalianoPress,
    //	c303_IdiomasalemanRls,
    //	c304_IdiomasalemanPress,
    //	c305_IdiomaspolacoRls,
    //	c306_IdiomaspolacoPress,
    //	c307_IdiomasrusoRls,
    //	c308_IdiomasrusoPress,
    //	c309_IdiomasportuguesRls,
    //	c310_IdiomasportuguesPress,
    //	c311_IdiomaschinoRls,
    //	c312_IdiomaschinoPress,
    //	c313_IdiomasjaponesRls,
    //	c314_IdiomasjaponesPress,
    //	c315_IdiomascoreanoRls,
    //	c316_IdiomascoreanoPress,

    //	c317_FondoConfiguracion,
    //	c318_Configuracionloading0,
    //	c318_Configuracionloading0_Z,
    //	c318_Configuracionloading20,
    //	c318_Configuracionloading20_Z,
    //	c319_Configuracionloading40,
    //	c319_Configuracionloading40_Z,
    //	c320_Configuracionloading60,
    //	c320_Configuracionloading60_Z,
    //	c321_Configuracionloading80,
    //	c321_Configuracionloading80_Z,
    //	c322_Configuracionloading100,
    //	c322_Configuracionloading100_Z,
    //	c323_2_ConfigBotonRecargaCoolantRls,
    //	c323_ConfgBotondownloadRls,
    //	c324_2_ConfigBotonRecargaCoolantPress,
    //	c324_ConfgBotondownloadPress,
    //	c325_2_ConfigBotonRecargaCoolantTsc,
    //	c325_3_ConfigSwitchResuctionViewerTsc,
    //	c325_ConfgBotondownloadTsc,
    //	c326_Configuracionnumero1,
    //	c327_Configuracionnumero2,
    //	c328_Configuracionnumero3,
    //	c329_Configuracionnumero4,
    //	c330_Configuracionnumero5,
    //	c331_Configuracionnumero6,
    //	c332_Configuracionnumero7,
    //	c333_Configuracionnumero8,
    //	c334_Configuracionnumero9,
    //	c335_Configuracionguion,
    //	c336_Configuracionnumero0,
    //	c337_PopupBotonsuccion1Rls,
    //	c338_PopupBotonsuccion1Press,
    //	c339_PopupBotonsuccion2Rls,
    //	c340_PopupBotonsuccion2Press,
    //	c341_PopupBotonsuccion3Rls,
    //	c342_PopupBotonsuccion3Press,
    //	c343_BotonVacuumSmall1Rls,
    //	c344_BotonVacuumSmall1MarcaAgua,
    //	c344_BotonVacuumSmall1Prs,
    //	c345_BotonVacuumSmall2Rls,
    //	c346_BotonVacuumSmall2MarcaAgua,
    //	c346_BotonVacuumSmall2Prs,
    //	c347_BotonVacuumSmall3Rls,
    //	c348_BotonVacuumSmall3MarcaAgua,
    //	c348_BotonVacuumSmall3Prs,
    //	c349_BotonVacuumDesplegable_L,
    //	c350_BotonVacuumDesplegable_R_03,
    //	c351_TscBotonVacuum1,
    //	c352_BotonVacuum1PressArrowLeft,
    //	c352_BotonVacuum1PressArrowRight,
    //	c352_BotonVacuum2PressArrowLeft,
    //	c352_BotonVacuum2PressArrowRight,
    //	c352_BotonVacuum3PressArrowLeft,
    //	c352_BotonVacuum3PressArrowRight,
    //	c352_FlechaVacuumLeft,
    //	c353_BotonVacuum1RlsArrowLeft,
    //	c353_BotonVacuum1RlsArrowRight,
    //	c353_BotonVacuum2RlsArrowLeft,
    //	c353_BotonVacuum2RlsArrowRight,
    //	c353_BotonVacuum3RlsArrowLeft,
    //	c353_BotonVacuum3RlsArrowRight,
    //	c353_FlechaVacuumRight,
    //	c354_BotonVacuum1MarcaAguaArrowLeft,
    //	c354_BotonVacuum2MarcaAguaArrowLeft,
    //	c354_BotonVacuum3MarcaAguaArrowLeft,
    //	c355_signoalarma,
    //	c356_BotonAlarmaCentralOkRls,
    //	c357_BotonAlarmaCentralOkPress,
    //	c358_BotonAlarmaCentralOkTsc,
    //	c420_Menualarmasfondo,
    //	c421_Menualarmatemppress,
    //	c422_Menualarmafiltropress,
    //	c423_Menualarmarfidpress,
    //	c424_Menualarmaaguamitadpress,
    //	c425_Menualarmasinaguapress,
    //	c426_Menualarmatiempopress,
    //	c427_HPalarmaObstruccion,
    //	c428_HPalarmaLlenadoAgua,
    //	c429_HPalarmaBoton,
    //	c430_HPalarmaResucciones,
    //	c431_HPalarmaLimpieza0,
    //	c432_HPalarmaLimpieza1,
    //	c433_HPalarmaLimpiezacolocar0,
    //	c434_HPalarmaLimpiezacolocar1,
    //	c435_HPalarmaTemperatura,
    //	c436_HPalarmaDesconexion,
    //	c438_HPalarmaPlicainsuficiente,
    //	c439_HPalarmaPlicaOK,
    //	c452_MenuAlarmaOK_press,
    //	c453_MenuAlarmaOK_MarcaAgua,
    //	c453_MenuAlarmaOK_MarcaAgua1,
    //	c453_MenuAlarmaOK_rls,
    //	c453_MenuAlarmaOK_tsc,
    //	c454_MenuAlarmaNO_press,
    //	c455_MenuAlarmaNO_MarcaAgua,
    //	c455_MenuAlarmaNO_MarcaAgua1,
    //	c455_MenuAlarmaNO_rls,
    //	c456_MenuLimpiezaClean_Rls,
    //	c457_MenuLimpiezaClean_Press,
    //	c458_MenuLimpiezaClean_MarcaAgua,
    //	c458_MenuLimpiezaClean_MarcaAgua1,
    //	c460_LimiteResuccionesSuperado,
    //	c461_CaracterComa,
    //	c461_CaracterDosPuntos,
    //	c461_CaracterNegativo,
    //	c461_CaracterPunto,
    //	c461_FondoNumVwrError,
    //	c461_Numero0,
    //	c461_Numero1,
    //	c461_Numero2,
    //	c461_Numero3,
    //	c461_Numero4,
    //	c461_Numero5,
    //	c461_Numero6,
    //	c461_Numero7,
    //	c461_Numero8,
    //	c461_Numero9,
    //	c462_FondoNumVwrErrorVerde,
    //	c463_FondoNumVwrErrorRojo,
    //	c464_FondoNumVwrErrorRojoNegro,
    //	c465_Menu_error_lectortiempo,
    //	c465_tiempo_CaracterBarra,
    //	c465_tiempo_CaracterComa,
    //	c465_tiempo_CaracterDosPuntos,
    //	c465_tiempo_CaracterPunto,
    //	c465_tiempo_Numero0,
    //	c465_tiempo_Numero1,
    //	c465_tiempo_Numero2,
    //	c465_tiempo_Numero3,
    //	c465_tiempo_Numero4,
    //	c465_tiempo_Numero5,
    //	c465_tiempo_Numero6,
    //	c465_tiempo_Numero7,
    //	c465_tiempo_Numero8,
    //	c465_tiempo_Numero9,
    //	c500_Number_0Resuctions,
    //	c501_Number_1Resuctions,
    //	c502_Number_2Resuctions,
    //	c503_Number_3Resuctions,
    //	c504_Number_4Resuctions,
    //	c505_Number_5Resuctions,
    //	c506_Number_6Resuctions,
    //	c507_Number_7Resuctions,
    //	c508_Number_8Resuctions,
    //	c509_Number_9Resuctions,
    //	c510_resuccionindicador,
    //	c512_TempShowboton_Press,
    //	c512_TempShowboton_Rls,
    //	c513_resuccionboton_Press,
    //	c514_resuccionboton_Rls,
    //	c515_Limpiezamanipulox4_Press,
    //	c516_Limpiezamanipulox4_Rls,
    //	c518_LimpiezamanipuloHP3_Rls,
    //	c520_LimpiezamanipuloHP3_Press,
    //	c521_LimpiezamanipuloHP1_Rls,
    //	c522LimpiezamanipuloHP1_Press,
    //	c524_LimpiezamanipuloHP2_Rls,
    //	c525_LimpiezamanipuloHP2_Press,
    //	c527_LimpiezamanipuloHP4_Rls,
    //	c528_LimpiezamanipuloHP4_Press,
    //	c530_botoncancel_MarcaAgua,
    //	c531_botoncancel_Rls,
    //	c532_botoncancel_Press,
    //	c533_fondocontador,
    //	c550_SPIerr,
    //	c551_Com485err,
    //	c552_Caudalerr,
    //	c553_PowerErr,
    //	c554_RFIDerr,
    //	c555_InsfNTC,
    //	c556_ToutVacc,
    //	c557_SinTramasMain,
    //	c558_ErrDesconocido,
    //	c559_InternalTemp,
    //	c560_InternalSensors,
    //	c561_HPdesconfig,
    //	c562_HPalarma,
    //	c563_PCBdanada,
    //	c564_TestInicialFallo,
    //	c600_Number_0_ResucInd,
    //	c601_Number_1_ResucInd,
    //	c602_Number_2_ResucInd,
    //	c603_Number_3_ResucInd,
    //	c604_Number_4_ResucInd,
    //	c605_Number_5_ResucInd,
    //	c606_Number_6_ResucInd,
    //	c607_Number_7_ResucInd,
    //	c608_Number_8_ResucInd,
    //	c609_Number_9_ResucInd,
    //	c610_GPRS_no_coverage,			//V7790 - GPRS coverage

//        APP_GUI_NUM_IMAGES
//    }cAppGUIimageIDlist;
//    Q_ENUM_NS(EAppGUIimageIDlist)

    // Widgets de la Interface
    typedef enum EAppGUIwidgetIDlist
    {
        //PANTALLA DE CARGA
        imgLoadScrBckGnd,
        imgLoadAnim1,
        imgLoadAnim2,
        imgLoadAnim3,
        imgLoadAnim4,
        imgLoadAnim5,
        imgLoadAnim6,
        imgLoadAnim7,
        imgLoadAnim8,

        //PANTALLA DE INICIO
        imgInitScrBckGnd,
        butSelectWoman,
        butSelectMan,
        imgInitGPRScoverage,		//V7790

        //Menu principal
        butInitScrShowMainMenu,
        butInitScrHideMainMenu,
        imgInitScrHome,
        butInitScrCfg,
        butInitScrCalc,
        butInitScrData,

        swInitScrAvisos,
        imgInitScrNotificacion,
        popupInitScrAvisos,
        imgPopUpInitScrAvisoBckGND,
        imgPopUpInitScrAvisoNivelAguaBajo,
        imgPopUpInitScrAvisoNivelAguaMedio,
        imgPopUpInitScrAvisoTempAmb,
        imgPopUpInitScrAvisoRFID,
        imgPopUpInitScrAvisoRTC,
        imgPopUpInitScrAvisoFiltroAire,

        //PANTALLA DE TRATAMIENTO
        imgTrtScrBckGnd,
        imgFullBodyAndZoom,
        imgTrtGPRScoverage,				//V7790

        //Fondos de los paneles de control
        imgCtrlPnlBckGndHP1,
        imgCtrlPnlBckGndHP2,
        imgCtrlPnlBckGndHP3,
        imgCtrlPnlBckGndHP4,

        //Colores fondos de los paneles de control
        imgColourCtrlPnlBckGndHP1,
        imgColourCtrlPnlBckGndHP2,
        imgColourCtrlPnlBckGndHP3,
        imgColourCtrlPnlBckGndHP4,

        //Indicadores de accion del HP cuando activos, los inactivos forman parte del fondo
        imgCtrlPnlRFIDblinkHP1,
        imgCtrlPnlRFIDblinkHP2,
        imgCtrlPnlRFIDblinkHP3,
        imgCtrlPnlRFIDblinkHP4,
        imgCtrlPnlPulBlinkHP1,
        imgCtrlPnlPulBlinkHP2,
        imgCtrlPnlPulBlinkHP3,
        imgCtrlPnlPulBlinkHP4,
        imgCtrlPnlVacBlinkHP1,
        imgCtrlPnlVacBlinkHP2,
        imgCtrlPnlVacBlinkHP3,
        imgCtrlPnlVacBlinkHP4,
        imgCtrlPnlCoolingBlinkHP1,
        imgCtrlPnlCoolingBlinkHP2,
        imgCtrlPnlCoolingBlinkHP3,
        imgCtrlPnlCoolingBlinkHP4,

        //Botones del panel de control de PLAY y Test Vacum
        butCtrlPnlPlayHP1,
        butCtrlPnlPlayHP2,
        butCtrlPnlPlayHP3,
        butCtrlPnlPlayHP4,
        swCtrlPnlTstVacHP1,
        swCtrlPnlTstVacHP2,
        swCtrlPnlTstVacHP3,
        swCtrlPnlTstVacHP4,

        //Botones (switch) que permite seleccionar modo de tratamiento AUTO o MANUAL
        butSwtchModeAutoManualHP1,
        butSwtchModeAutoManualHP2,
        butSwtchModeAutoManualHP3,
        butSwtchModeAutoManualHP4,

        //Visores de tiempo restante de trt y boton de seleccion de tiempo
        numVwrTimeHP1,
        numVwrTimeHP2,
        numVwrTimeHP3,
        numVwrTimeHP4,
        butSelectTimeHP1,
        butSelectTimeHP2,
        butSelectTimeHP3,
        butSelectTimeHP4,
        butVwrTemperatureHP1,
        butVwrTemperatureHP2,
        butVwrTemperatureHP3,
        butVwrTemperatureHP4,

        //Visor numerico para contabilizar resucciones
        numVwrResucctionCountHP1,
        numVwrResucctionCountHP2,
        numVwrResucctionCountHP3,
        numVwrResucctionCountHP4,

        //Boton con la imagen e imagen con el texto del modelo
        imgModelTextHP1,
        imgModelTextHP2,
        imgModelTextHP3,
        imgModelTextHP4,
        butModelImageHP1,
        butModelImageHP2,
        butModelImageHP3,
        butModelImageHP4,

        //Botonoes de recogida y despliegue del panel de control
        butHideControlPanelHP1,
        butHideControlPanelHP2,
        butHideControlPanelHP3,
        butHideControlPanelHP4,
        butShowControlPanelHP1,
        butShowControlPanelHP2,
        butShowControlPanelHP3,
        butShowControlPanelHP4,

        //Botones de selección de Full body
        butFullBodyTorso,
        butFullBodyPiernas,
        butFullBodyBrazos,
        butFullBodyEspalda,
        butFullBodyPiernaMuslo,
        butFullBodyCuello,

        //Puntos seleccion de zona de tratamiento cuando zoom
        swDotZone0,
        swDotZone1,
        swDotZone2,
        swDotZone3,
        swDotZone4,
        swDotZone5,
        swDotZone6,
        swDotZone7,
        swDotZone8,
        swDotZone9,
        swDotZone10,
        swDotZone11,
        swDotZone12,
        swDotZone13,
        swDotZone14,

        //Punto seleccionado para tratamiento con ese HP a mostrar en full body
        imgSelectedTrtZoneHP1,
        imgSelectedTrtZoneHP2,
        imgSelectedTrtZoneHP3,
        imgSelectedTrtZoneHP4,

        //POPUP's
        //Common
        butPopUpReturn,
        imgPopUpHPcolorBar,

        //PopUp Time widgets
        popUpTime,
        butPopUpTime50min,
        butPopUpTime70min,
        imgPopUpTime1sel,
        imgPopUpTime2sel,

        //PopUp Test Vacum widgets
        popUpTstVac,
        imgPopUpTstVacBckGnd,
        imgPopUpTstVacLowLvl,
        imgPopUpTstVacMidLvl,
        imgPopUpTstVacHighLvl,
        imgPopUpTstVacPulHand,
        imgPopUpTstVacPulHandx2,
        butPopUpTstVacManualLowLvl,
        butPopUpTstVacManualMidLvl,
        butPopUpTstVacManualHighLvl,
        butPopUpTstVacAuto,
        swPopUpTstVacLowLvl,
        swPopUpTstVacMidLvl,
        swPopUpTstVacHighLvl,
        imgPopUpTstVacAUTOstatus,

        //PopUp Test Vacuum 2 widgets
        popUpTstVacSmall,
        imgPopUpVacSelBck,
        butPopUpTstVacSmallLowLvl,
        butPopUpTstVacSmallMedLvl,
        butPopUpTstVacSmallHighLvl,

        //PopUp RFID widgets
        popUpRFID,
        imgPopUpRFIDbckGnd,
        imgPopUpRFIDlabel,
        imgPopUpRFIDresult,
        butPopUpRFIDreuseLabel,
        numVwrPopUpRFIDrestTime,

        //PopUp Recommendation widgets
        swPopUpRecommInfo,
        popUpRecomm,
        imgPopUpRecommbckGnd,
        imgPopUpRecommCurved,
        imgPopUpRecommTight,
        imgPopUpRecommStright,
        imgPopUpRecommTiny,
        imgPopUpRecommTinyCurved,
        imgPopUpRecommDouble,
        imgPopUpRecommOval,
        imgPopUpRecommOvalCurved,
        imgPopUpRecommAngled,

        //Menu Principal
        butTrtScrShowMainMenu,
        butTrtScrHideMainMenu,
        butTrtScrHome,
        butTrtScrCfg,
        butTrtScrCalc,
        butTrtScrData,

        swTrtScrAvisos,
        imgTrtScrNotificacion,
        popupTrtScrAvisos,
        imgPopUpTrtScrAvisoBckGND,
        imgPopUpTrtScrAvisoNivelAguaBajo,
        imgPopUpTrtScrAvisoNivelAguaMedio,
        imgPopUpTrtScrAvisoTempAmb,
        imgPopUpTrtScrAvisoRFID,
        imgPopUpTrtScrAvisoRTC,
        imgPopUpTrtScrAvisoFiltroAire,

        //popUp's Error
        imgPopUpErrBckGndHP1,
        imgPopUpErrBckGndHP2,
        imgPopUpErrBckGndHP3,
        imgPopUpErrBckGndHP4,
        imgPopUpErrBckGndUC,
        numVwrPopUpErrHP1,
        numVwrPopUpErrHP2,
        numVwrPopUpErrHP3,
        numVwrPopUpErrHP4,
        numVwrPopUpErrUC,
        imgPopUpErrMsgHP1,
        imgPopUpErrMsgHP2,
        imgPopUpErrMsgHP3,
        imgPopUpErrMsgHP4,
        imgPopUpErrMsgUC,
        butPopUpErrOkHP1,
        butPopUpErrOkHP2,
        butPopUpErrOkHP3,
        butPopUpErrOkHP4,
        butPopUpErrOkUC,
        numVwrPopUpErrTRTtimeHP1,
        numVwrPopUpErrTRTtimeHP2,
        numVwrPopUpErrTRTtimeHP3,
        numVwrPopUpErrTRTtimeHP4,

        //PopUp's CleanUp
        imgPopUpCleanBckGndHP1,
        imgPopUpCleanBckGndHP2,
        imgPopUpCleanBckGndHP3,
        imgPopUpCleanBckGndHP4,
        numVwrPopUpCleanHP1,
        numVwrPopUpCleanHP2,
        numVwrPopUpCleanHP3,
        numVwrPopUpCleanHP4,
        butPopUpCleanHP1,
        butPopUpCleanHP2,
        butPopUpCleanHP3,
        butPopUpCleanHP4,
        butPopUpCleanYESHP1,
        butPopUpCleanYESHP2,
        butPopUpCleanYESHP3,
        butPopUpCleanYESHP4,
        butPopUpCleanNOHP1,
        butPopUpCleanNOHP2,
        butPopUpCleanNOHP3,
        butPopUpCleanNOHP4,
        imgPopUpCleanHP1,
        imgPopUpCleanHP2,
        imgPopUpCleanHP3,
        imgPopUpCleanHP4,
        butPopUpCleanCancelHP1,
        butPopUpCleanCancelHP2,
        butPopUpCleanCancelHP3,
        butPopUpCleanCancelHP4,
        numVwrPopUpCleanNumCancelHP1,
        numVwrPopUpCleanNumCancelHP2,
        numVwrPopUpCleanNumCancelHP3,
        numVwrPopUpCleanNumCancelHP4,


        //Pantalla de la calculadora
        imgFondoCalcScreen,
        imgCuerpoCalc,
        numVwrPantallaCalc,
        butNum0Calc,
        butNum1Calc,
        butNum2Calc,
        butNum3Calc,
        butNum4Calc,
        butNum5Calc,
        butNum6Calc,
        butNum7Calc,
        butNum8Calc,
        butNum9Calc,
        butMasCalc,
        butMenosCalc,
        butEnterCalc,
        butCECalc,
        butComaCalc,

        //Menu principal - calculadora
        butCalcScrShowMainMenu,
        butCalcScrHideMainMenu,
        butCalcScrHome,
        butCalcScrCfg,
        imgCalcScrCalc,
        butCalcScrData,

        swCalcScrAvisos,
        imgCalcScrNotificacion,
        popupCalcScrAvisos,
        imgPopUpCalcScrAvisoBckGND,
        imgPopUpCalcScrAvisoNivelAguaBajo,
        imgPopUpCalcScrAvisoNivelAguaMedio,
        imgPopUpCalcScrAvisoTempAmb,
        imgPopUpCalcScrAvisoRFID,
        imgPopUpCalcScrAvisoRTC,
        imgPopUpCalcScrAvisoFiltroAire,

        //Pantalla de configuración
        imgFondoCfgScreen,
        imgVentanaCfgCastellano,
        butCfgActualizarSoftware,
        imgSoftwareProgressionUpdateBar,
        numVwrModeloMaqCfg,
        numVwrVersionSoftwareCfg,
        butCfgRecargaCoolant,
        swCfgResuctionViewer,
        swCfgTemperatureViewer,
        butCfgCleanUpHP1,
        butCfgCleanUpHP2,
        butCfgCleanUpHP3,
        butCfgCleanUpHP4,
        butCfgCleanUpRoundHP,
        imgCfgGPRScoverage,		//V7790

        //Menu principal - configuracion
        butCfgScrShowMainMenu,
        butCfgScrHideMainMenu,
        butCfgScrHome,
        imgCfgScrCfg,
        butCfgScrCalc,
        butCfgScrData,

        swCfgScrAvisos,
        imgCfgScrNotificacion,
        popupCfgScrAvisos,
        imgPopUpCfgScrAvisoBckGND,
        imgPopUpCfgScrAvisoNivelAguaBajo,
        imgPopUpCfgScrAvisoNivelAguaMedio,
        imgPopUpCfgScrAvisoTempAmb,
        imgPopUpCfgScrAvisoRFID,
        imgPopUpCfgScrAvisoRTC,
        imgPopUpCfgScrAvisoFiltroAire,

        //Pantalla de idiomas
        imgFondoLanScreen,

        swLanFrances,
        swLanCastellano,
        swLanIngles,
        swLanItaliano,
        swLanAleman,
        swLanPolaco,
        swLanRuso,
        swLanPortugues,
        swLanChino,
        swLanJapones,
        swLanCoreano,

        //Menu principal - idiomas
        butLanScrShowMainMenu,
        butLanScrHideMainMenu,
        butLanScrHome,
        butLanScrCfg,
        butLanScrCalc,
        imgLanScrData,

        swLanScrAvisos,
        imgLanScrNotificacion,
        popupLanScrAvisos,
        imgPopUpLanScrAvisoBckGND,
        imgPopUpLanScrAvisoNivelAguaBajo,
        imgPopUpLanScrAvisoNivelAguaMedio,
        imgPopUpLanScrAvisoTempAmb,
        imgPopUpLanScrAvisoRFID,
        imgPopUpLanScrAvisoRTC,
        imgPopUpLanScrAvisoFiltroAire,

        //Pantalla de SAT
        imgFondoSATscreen,
        butHomeSATscreen,

        numVwrPaginaSATscreen,
        butNextPagSATscreen,
        butPrevPagSATscreen,

        imgVwr1,
        imgVwr2,
        imgVwr3,
        imgVwr4,
        imgVwr5,
        imgVwr6,
        imgVwr7,
        imgVwr8,
        imgVwr9,
        imgVwr10_1,
        imgVwr10_2,
        imgVwr11_1,
        imgVwr11_2,
        imgVwr12_1,
        imgVwr12_2,
        imgVwr13_1,
        imgVwr13_2,
        imgVwr14_1,
        imgVwr14_2,
        imgVwr15_1,
        imgVwr15_2,
        imgVwr16_1,
        imgVwr16_2,
        imgVwr17_1,
        imgVwr17_2,
        imgVwr18_1,
        imgVwr18_2,
        imgVwr19_1,
        imgVwr19_2,
        imgVwr20_1,
        imgVwr20_2,
        imgVwr21_1,
        imgVwr21_2,
        imgVwr22_1,
        imgVwr22_2,
        imgVwr23_1,
        imgVwr23_2,
        imgVwr24_1,
        imgVwr24_2,
        imgVwr25_1,
        imgVwr25_2,
        imgVwr26_1,
        imgVwr26_2,
        imgVwr27_1,
        imgVwr27_2,
        imgVwr28_1,
        imgVwr28_2,

        numVwr1,
        numVwr2,
        numVwr3,
        numVwr4,
        numVwr5,
        numVwr6,
        numVwr7,
        numVwr8,
        numVwr9,
        numVwr10,
        numVwr11,
        numVwr12,
        numVwr13,
        numVwr14,
        numVwr15,
        numVwr16,
        numVwr17,
        numVwr18,
        numVwr19,
        numVwr20,
        numVwr21,
        numVwr22,
        numVwr23,
        numVwr24,
        numVwr25,
        numVwr26,
        numVwr27,
        numVwr28,

        imgVacuum,
        imgFrio,
        imgRFID,
        imgTestLed,
        imgTestLedStatus,
        imgTestLedRGD,
        swVacuum,
        swFrio,
        swRFID,
        swTestLed,
        swTestLedRGB,

        PopupErrorSAT,
        imgVwrFondoErrorSAT,
        numVwrError1,
        numVwrError2,
        numVwrError3,
        numVwrError4,
        numVwrError5,
        butOkerr,

        //Pantalla de FATIGA
        imgFondoFATIGAscreen,
        butHomeFATIGAscreen,

        imgStep1,
        imgStep1status,
        imgStep2,
        imgStep2status,
        imgStep3,
        imgStep3status,
        imgStep4,
        imgStep4statusHP1,
        imgStep4statusHP2,
        imgStep4statusHP3,
        imgStep4statusHP4,
        imgStep5,
        imgStep5statusHP1,
        imgStep5statusHP2,
        imgStep5statusHP3,
        imgStep5statusHP4,
        imgStep6,
        imgStep6status,
        imgStep7,
        imgStep7status,

        numVwrTempAmb,
        numVwrTempBomba,
        numVwrTempRetorno,
        numVwrCaudalRetorno,
        numVwrVtobera,
        numVwrRth,
        numVwrCPI,
        numVwrCaudalRetornoHP1,
        numVwrCaudalRetornoHP2,
        numVwrCaudalRetornoHP3,
        numVwrCaudalRetornoHP4,
        numVwrVacuumHP1,
        numVwrVacuumHP2,
        numVwrVacuumHP3,
        numVwrVacuumHP4,
        numVwrFatigaTime,
        numVwrErrFatiga1,
        numVwrErrFatiga2,
        numVwrErrFatiga3,
        numVwrErrFatiga4,
        numVwrErrFatiga5,

        imgVwrVAC1,
        imgVwrVAC2,
        imgVwrVAC3,
        imgVwrVAC4,
        imgVwrCaudal1,
        imgVwrCaudal2,
        imgVwrCaudal3,
        imgVwrCaudal4,
        imgVwrTempAmb,
        imgVwrTempBomba,
        imgVwrTempRetorno,
        imgVwrCaudalRetorno,
        imgVwrVtobera,
        imgVwrRth,
        imgVwrCPI,				//447

        swFatigueFailBeep,

        APP_GUI_NUM_WIDGETS
    }cAppGUIwidgetIDlist;
    Q_ENUM_NS(EAppGUIwidgetIDlist)
}

using namespace AppEnumsNs;

/*** DEFINICIONES DE TIPOS ***/
typedef struct
{
	uint16 IDimg;
	uint16 imgX;
	uint16 imgY;
}tAppGUIfullBodyImagesTableFields;

typedef struct
{
	uint16 IDimgPrs;
	uint16 imgPrsX;
	uint16 imgPrsY;
	uint16 IDimgRls;
	uint16 imgRlsX;
	uint16 imgRlsY;
	uint16 IDimgTS;
	uint16 imgTS_X;
	uint16 imgTS_Y;	
	uint16 TSrectW;
	uint16 TSrectH;
	uint16 IDimgZoom;
	uint16 imgZoomX;
	uint16 imgZoomY;
}tAppGUIfullBodyAreasTableFields;

typedef struct
{
    uint8 isUsed;

	uint16 imgHPbody_X;
	uint16 imgHPbody_Y;

	cAppGUItrtZones trtZone;
}tAppGUIareaZoomDotsTableFields;

typedef struct
{
    uint16 id;
    uint8 displayed;
} tAppGUIPopUpDisplayed;

/*** VECTORES DE CONSTANTES ***/
//extern const uint32 APP_GUI_MAIN_MENU_WID_WHEN_SHOW[APP_GUI_NUM_SCREENS][APP_GUI_MAIN_MENU_WID_WHEN_SHOW_NUM];
//extern const uint32 APP_GUI_MAIN_MENU_WID_WHEN_HIDE[APP_GUI_NUM_SCREENS][APP_GUI_MAIN_MENU_WID_WHEN_HIDE_NUM];
//extern const uint32 APP_GUI_LOAD_SCR_ANIM_IMG_LIST[APP_GUI_LOAD_SCR_ANIM_IMG_NUM];

//extern const uint32 APP_GUI_CFG_SCR_LOADING_NEW_FW_ANIMATION [App_GUI_CfgScr_FW_loading_max];

extern const uint8 APP_GUI_SLOT_DISTRIBUTION[APP_GUI_MAXNUM_HP];

//extern const uint32 APP_GUI_TRT_SCR_BUT_MODEL_IMG_SIDE_FROM_SLOT_IMG[APP_GUI_MAX_PRS_RLS][APP_GUI_MAXNUM_HP][HP_CRYO_NUM_HP_MODELS];
//extern const uint32 APP_GUI_TRT_SCR_BUT_MODE_IMG_NO_HP_IMG[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_TRT_SCR_BUT_MODEL_IMG_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_TRT_SCR_BUT_MODE_TRT_WIDGETS[APP_GUI_MAXNUM_HP];

//extern const uint32 APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_SHOW[APP_GUI_MAXNUM_HP][APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_SHOW_NUM];
//extern const uint32 APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_HIDE[APP_GUI_MAXNUM_HP][APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_HIDE_NUM];
//extern const uint32 APP_GUI_TRT_SCR_CTRL_PNL_COLOUR_IMGS [APP_GUI_MAXNUM_HP][APP_GUI_TRT_SCR_CTRL_PNL_COLOUR_STATES_IMGS];
//extern const uint32 APP_GUI_TRT_SCR_CTRL_PNL_COLOUR_WIDGETS [APP_GUI_MAXNUM_HP];

//extern const uint32 APP_GUI_TRT_SCR_HP_ERR_WIDGETS[APP_GUI_MAXNUM_HP][APP_GUI_NUM_ERR_WIDGETS_WHEN_HP];
//extern const uint32 APP_GUI_TRT_SCR_HP_ERR_MSG_IMAGES[Err_msg_max];
//extern const uint32 APP_GUI_TRT_SCR_UC_ERR_WIDGETS[APP_GUI_NUM_ERR_WIDGETS_WHEN_UC];
//extern const uint32 APP_GUI_TRT_SCR_UC_ERR_MSG_IMAGES[Err_msg_max];

//extern const uint32 APP_GUI_TRT_SCR_CLEANUP_BCKGND_WIDGETS[APP_GUI_MAXNUM_HP];

extern const uint32 APP_GUI_TRT_SCR_DOT_ZONES_WIDGETS[APP_GUI_MAX_DOTS_PER_AREA];
extern const uint32 APP_GUI_TRT_SCR_FULL_BODY_AREAS_WIDGETS[APP_GUI_NUM_FULL_BODY_AREAS];
extern const uint32 APP_GUI_TRT_SCR_FULL_BODY_SELECTED_ZONE_WIDGETS[APP_GUI_MAXNUM_HP];

//extern const uint32 APP_GUI_TRT_SCR_POPUP_COLOR_BAR_IMAGES[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_TRT_SCR_CLEANUP_IMAGES_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_TRT_SCR_CLEANUP_NUM_VIEWER_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_TRT_SCR_CLEANUP_BUTTON_YES_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_TRT_SCR_CLEANUP_BUTTON_NO_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_TRT_SCR_CLEANUP_BUTTON_CLEAN_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_TRT_SCR_CLEANUP_STATUS_IMAGES[APP_GUI_CLEAN_UP_N_STATUS];
//extern const uint32 APP_GUI_TRT_SCR_CLEANUP_BUTTON_YES_IMAGES[APP_GUI_MAX_ON_OFF];
//extern const uint32 APP_GUI_TRT_SCR_CLEANUP_BUTTON_NO_IMAGES[APP_GUI_MAX_ON_OFF];
//extern const uint32 APP_GUI_TRT_SCR_CLEANUP_BUTTON_CLEAN_IMAGES[APP_GUI_MAX_ON_OFF];
//extern const uint32 APP_GUI_TRT_SCR_CLEANUP_BURTTON_CANCEL_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_TRT_SCR_CLEANUP_NUMVWR_CANCELLED_TIMES_WIDGET[APP_GUI_MAXNUM_HP];

//extern const uint32 APP_GUI_TRT_SCR_POPUP_TST_VAC_LVL_IMAGES[APP_GUI_MAX_TST_VAC_DONE][HP_CRYO_VAC_LVL_NUM];
extern const uint32 APP_GUI_TRT_SCR_POPUP_TST_VAC_SW_LIST[HP_CRYO_VAC_LVL_NUM];
//extern const uint32 APP_GUI_TRT_SCR_POPUP_TST_VAC_IMG_LIST[HP_CRYO_VAC_LVL_NUM];
//extern const uint32 APP_GUI_TRT_SCR_POPUP_TIME_SW_LIST[HP_CRYO_MAX_TIME_LIST];
//extern const uint16 APP_GUI_POPUP_TIME_COORDINATES_PER_HP[App_GUI_PopUpTimeWidgetCoordinates][APP_GUI_MAXNUM_HP][Max_coordinates];
//extern const uint32 APP_GUI_POPUP_TST_VAC_SMALL_WIDGET_LIST[APP_GUI_POPUP_TST_VAC_SMALL_WIDGET_LIST_NUM];
//extern const uint32 APP_GUI_POPUP_TST_VAC_SMALL_BUT_IMAGES[HP_CRYO_VAC_LVL_NUM][App_GUI_but_max];
//extern const uint16 APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[APP_GUI_MAXNUM_HP][App_GUI_PopUpVacWidgetCoordinates][Max_coordinates] ;
//extern const uint32 APP_GUI_TRT_SCR_POPUP_VAC_SMALL_BCK_IMG[APP_GUI_MAXNUM_HP];

//extern const uint32 APP_GUI_TRT_SCR_BLINK_INDICATORS_WIDGETS[APP_GUI_MAXNUM_HP][APP_GUI_MAX_BLINK_INDICATORS];
//extern const uint32 APP_GUI_TRT_SCR_HP_MODEL_TEXT_IMG[APP_GUI_MAXNUM_HP][HP_CRYO_NUM_HP_MODELS];
//extern const uint32 APP_GUI_TRT_SCR_HP_MODEL_TEXT_WIDGETS[APP_GUI_MAXNUM_HP];

//extern const uint32 APP_GUI_TRT_SCR_BUT_SEL_TIME_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_TRT_SCR_BUT_CHNG_TIME_TO_TEMP_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_TRT_SCR_NUM_VWE_RESUCCTIONS_NUM_WIDGETS [APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_TRT_SCR_BUT_TIME_IMG[App_GUI_Max_Time_but_states][App_GUI_widget_Features];
//extern const uint32 APP_GUI_TRT_SCR_BUT_PLAY_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_TRT_SCR_BUT_PLAY_IMG[App_GUI_Max_Play_but_states][App_GUI_widget_Features];
//extern const uint32 APP_GUI_TRT_SCR_BUT_TSTVAC_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_TRT_SCR_BUT_VAC_IMG[HP_CRYO_VAC_LVL_NUM][App_GUI_Max_Vac_but_states][App_GUI_widget_Features];
                                                       
//extern const uint32 APP_GUI_POPUP_RFID_WIDGET_LIST[APP_GUI_POPUP_RFID_WIDGET_LIST_NUM];
//extern const uint32 APP_GUI_TRT_SCR_POPUP_RFID_LABELS_IMGS [HP_CRYO_NUM_LABELS];
//extern const uint32 APP_GUI_TRT_SCR_POPUP_RFID_STATUS_IMGS [RFID_MAX_LABEL_OPTIONS];

//extern const uint32 APP_GUI_POPUP_TST_VAC_WIDGET_LIST[APP_GUI_POPUP_TST_VAC_WIDGET_LIST_NUM];
//extern const uint32 APP_GUI_POPUP_TIME_WIDGET_LIST[APP_GUI_POPUP_TIME_WIDGET_LIST_NUM];
//extern const uint32 APP_GUI_POPUP_RECOMMENDATION_WIDGET_LIST[APP_GUI_POPUP_RECOMMENDATION_WIDGET_LIST_NUM];
//extern const uint32 APP_GUI_POPUP_AVISOS_INIT_SCRN_WIDGET_LIST[APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM];
//extern const uint32 APP_GUI_POPUP_AVISOS_TRT_SCRN_WIDGET_LIST[APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM];
//extern const uint32 APP_GUI_POPUP_AVISOS_CALC_SCRN_WIDGET_LIST[APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM];
//extern const uint32 APP_GUI_POPUP_AVISOS_CFG_SCRN_WIDGET_LIST[APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM];
//extern const uint32 APP_GUI_POPUP_AVISOS_LAN_SCRN_WIDGET_LIST[APP_GUI_POPUP_AVISOS_WIDGET_LIST_NUM];
//extern const uint32 APP_GUI_POPUP_ERRORES_SAT_WIDGET_LIST[APP_GUI_POPUP_ERRORES_SAT_WIDGET_LIST_NUM];

//extern const uint32 APP_GUI_AVISOS_SWITCH_WIDGET_SCREENS[APP_GUI_NUM_SCREENS];
extern const uint32 APP_GUI_AVISOS_POPUP_WIDGET_SCREENS[APP_GUI_NUM_SCREENS];
//extern const uint32 APP_GUI_AVISOS_WIDGETS[APP_GUI_NUM_SCREENS][App_GUI_Num_Max_Avisos];
//extern const uint32 APP_GUI_AVISOS_NOTIFICATIONS_WIDGETS_SCREENS[APP_GUI_NUM_SCREENS];

//extern const uint32 APP_GUI_SAT_ERRORES_NUMVWR_LIST[APP_GUI_SAT_ERRORES_PERIFS];

extern const uint32 APP_GUI_TRT_SCR_POPUP_WIDGET_LIST[APP_GUI_TRT_SCR_NUM_POPUPS];

//extern const tAppGUIfullBodyImagesTableFields APP_GUI_FULL_BODY_IMAGES[APP_GUI_NUM_BODYS];
//extern const tAppGUIfullBodyAreasTableFields APP_GUI_FULL_BODY_AREAS_DATA[APP_GUI_NUM_BODYS][APP_GUI_NUM_FULL_BODY_AREAS];
extern const tAppGUIareaZoomDotsTableFields APP_GUI_AREA_ZOOM_DOTS[APP_GUI_NUM_BODYS][APP_GUI_NUM_FULL_BODY_AREAS][APP_GUI_MAX_DOTS_PER_AREA];

//extern const uint8	APP_GUI_SCREEN_N_LAYERS[APP_GUI_NUM_SCREENS];
//extern const uint32 APP_GUI_INTERFACE_WIDGETS[APP_GUI_NUM_WIDGETS][APP_GUI_WIDGETS_FEATURES];

//extern const uint32 APP_GUI_TRT_LOAD_NEW_HP_CONFIG[APP_GUI_TRT_LOAD_NEW_HP_IMG];

extern const cAppGUItrtAgrupacionZones APP_GUI_TRT_ZONES_GROUP_ASSOCIATION[APP_GUI_NUM_FULL_BODY_AREAS][APP_GUI_MAX_DOTS_PER_AREA];

//extern const uint8 APP_GUI_HP_RECOMMENDED_PER_ZONE[HP_CRYO_NUM_HP_MODELS][APP_GUI_NUM_FULL_BODY_AREAS][APP_GUI_MAX_DOTS_PER_AREA];
//extern const uint32 APP_GUI_TRT_LIST_OF_IMG_HP_RECOMMENDED_PER_ZONE[HP_CRYO_NUM_HP_MODELS];

//extern const uint32 APP_GUI_LANG_SW_WIDGET_LANG_LIST[App_GUI_Different_Languages];

//extern const uint32 APP_GUI_SAT_NUMVWR_WIDGET_LIST[APP_GUI_SAT_MAX_NUMVWR];

//extern const uint32 APP_GUI_FAT_STATUS_4_HP_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_FAT_STATUS_5_HP_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_FAT_VALUE_STATUS[EXP_UC_FATIGUE_MAX_VALUE_STATUS];
//extern const uint32 APP_GUI_FAT_DIFF_NUM_VWR_VALUES[FatMaxValues];
extern tAppGUIPopUpDisplayed APP_GUI_POPUP_DISPLAYED_MAP[APP_GUI_POPUP_DISPLAYED_MAP_NUM];

//extern const uint32 APP_GUI_GPRS_COVERAGE_WID_BY_SCREEN[APP_GUI_NUM_SCREENS]; //V7790

#endif /* APPGUIINTERFACESTRUCTURE_H_ */
