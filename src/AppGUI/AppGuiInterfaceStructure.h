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
    Q_ENUM_NS(EAppGUImachineWarnings)

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
    Q_ENUM_NS(EAppGUIPlayButStates)

    typedef enum EAppGUIVacButStates
    {
        App_GUI_Vac_but_Off,
        App_GUI_Vac_but_On,
        App_GUI_Vac_but_VacAjust,
        App_GUI_Vac_but_disabled,

        App_GUI_Max_Vac_but_states
    }cAppGUIVacButStates;
    Q_ENUM_NS(EAppGUIVacButStates)

    typedef enum EAppGUITimeButStates
    {
        App_GUI_Time_but_Off,
        App_GUI_Time_but_On,
        App_GUI_Time_but_disabled,

        App_GUI_Max_Time_but_states
    }cAppGUITimeButStates;
    Q_ENUM_NS(EAppGUITimeButStates)

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
    typedef enum EAppGUIimageIDlist
    {
        A001_FondoLogoCooltechDefine,
        A002_CargaLogotipo1,
        A003_CargaLogotipo2,
        A004_CargaLogotipo3,
        A005_CargaLogotipo4,
        A006_CargaLogotipo5,
        A007_CargaLogotipo6,
        A008_CargaLogotipo7,
        A009_CargaLogotipo8,
        B001_FondoLogoSiluetasHombreMujer,
        B002_BotonFemeninoPress,
        B003_BotonFemeninoRls,
        B004_TscBotonFemenino,
        B005_BotonMasculinoPress,
        B006_BotonMasculinoRls,
        B007_TscBotonMasculino,
        B008_SwMenuRls,
        B009_TscSwMenuRls,
        B010_SwMenuPress,
        B011_TscSwMenuPress,
        B012_BotonHomeMarcaAgua,
        B012_BotonHomeMarcaAgua1,
        B013_BotonHomePress,
        B014_BotonHomeRls,
        B015_TscBotonHome,
        B016_BotonConfigPress,
        B017_BotonConfigRls,
        B018_BotonConfigMarcaAgua,
        B018_BotonConfigMarcaAgua1,
        B019_TscBotonConfig,
        B020_BotonCalculadoraMarcaAgua,
        B020_BotonCalculadoraMarcaAgua1,
        B021_BotonCalculadoraPress,
        B022_BotonCalculadoraRls,
        B023_TscBotonCalculadora,
        B024_BotonIdiomasMarcaAgua,
        B024_BotonIdiomasMarcaAgua1,
        B025_BotonIdiomasPress,
        B026_BotonIdiomasRls,
        B027_TscBotonIdiomas,
        B028_BotonAvisosMarcaAgua,
        B028_BotonAvisosMarcaAgua1,
        B029_BotonAvisosPress,
        B030_BotonAvisosRls,
        B031_TscBotonAvisos,
        B032_ImgNotificacion,
        B032_ImgNotificacion2,
        C001_FondoLogo,
        C002_SiluetaMujerFrenteEspalda,
        C003_SiluetaHombreFrenteEspalda,
        C004_MenuTrtHP1,
        C005_MenuTrtHP1_Aro2,
        C005_TscMenuTrtHP1Rls,
        C005__MenuTrtHP1_Aro1,
        C006_MenuTrtHP1Press,
        C007_TscMenuTrtHP1Press,
        C012_MenuTrtHP2,
        C013_MenuTrtHP2_Aro1,
        C013_MenuTrtHP2_Aro2,
        C013_TscMenuTrtHP2Rls,
        C014_MenuTrtHP2Press,
        C015_TscMenuTrtHP2Press,
        C020_MenuTrtHP3,
        C021_MenuTrtHP3_Aro1,
        C021_MenuTrtHP3_Aro2,
        C021_TscMenuTrtHP3Rls,
        C022_MenuTrtHP3Press,
        C023_TscMenuTrtHP3Press,
        C028_MenuTrtHP4,
        C029_MenuTrtHP4_Aro1,
        C029_MenuTrtHP4_Aro2,
        C029_TscMenuTrtHP4Rls,
        C030_MenuTrtHP4Press,
        C031_TscMenuTrtHP4Press,
        C033_BotonStopPress,
        C034_BotonStopRls,
        C035_BotonPlayPress,
        C036_BotonPlayPress,
        C037_BotonPlayRls,
        C038_BotonPlayMarcaAgua,
        C039_TscBotonPlay,
        C040_BotonVacuum1PressLeft,
        C040_BotonVacuum1PressRight,
        C040_BotonVacuum2PressLeft,
        C040_BotonVacuum2PressRight,
        C040_BotonVacuum3PressLeft,
        C040_BotonVacuum3PressRight,
        C041_BotonVacuum1RlsLeft,
        C041_BotonVacuum1RlsRight,
        C041_BotonVacuum2RlsLeft,
        C041_BotonVacuum2RlsRight,
        C041_BotonVacuum3RlsLeft,
        C041_BotonVacuum3RlsRight,
        C042_BotonVacuum1MarcaAguaLeft,
        C042_BotonVacuum1MarcaAguaRight,
        C042_BotonVacuum2MarcaAguaLeft,
        C042_BotonVacuum2MarcaAguaRight,
        C042_BotonVacuum3MarcaAguaLeft,
        C042_BotonVacuum3MarcaAguaRight,
        C043_TscBotonVacuum,
        C044_BotonAutoPress,
        C044_B_TscBotonAuto,
        C045_BotonAutoRls,
        C046_Auto,
        C047_FondoNumVwrBlanco,
        C047_FondoTemporizador,
        C048_RelojTemporizadorPress,
        C049_RelojTemporizadorRls,
        C050_RelojTemporizadorMarcaAgua,
        C051_TscrRelojTemporizador,
        C052_Numero1,
        C053_Numero2,
        C054_Numero3,
        C055_Numero4,
        C056_Numero5,
        C057_Numero6,
        C058_Numero7,
        C059_Numero8,
        C060_Numero9,
        C061_Numero0,
        C062_CaracterDosPuntos,
        C063_CaracterComa,
        C064_CaracterPunto,
        C065_CaracterNegativo,
        C066_NameCurvedHP_L,
        C066_NameCurvedHP_R,
        C067_NameTightHP_L,
        C067_NameTightHP_R,
        C068_NameStarightHP_L,
        C068_NameStraightHP_R,
        C069_NameTinyHP_L,
        C069_NameTinyHP_R,
        C070_NameTinyCurvedHP_L,
        C070_NameTinyCurvedHP_R,
        C071_NameDoubleHP_L,
        C071_NameDoubleHP_R,
        C072_NameOvalHP_L,
        C072_NameOvalHP_R,
        C073_NameOvalCurvedHP_L,
        C073_NameOvalCurvedHP_R,
        C074_NameDeltaHP_L,
        C074_NameDeltaHP_R,
        C075_ImgCurvedHP_R_Rls,
        C076_ImgCurvedHP_L_Rls,
        C077_ImgTightHP_R_Rls,
        C078_ImgTightHP_L_Rls,
        C079_ImgStrightHP_R_Rls,
        C080_ImgStrightHP_L_Rls,
        C081_ImgTinyHP_R_Rls,
        C082_ImgTinyHP_L_Rls,
        C083_ImgTinyCurvedHP_R_Rls,
        C084_ImgTinyCurvedHP_L_Rls,
        C085_ImgDoubleHP_R_Rls,
        C086_ImgDoubleHP_L_Rls,
        C087_ImgOvalHP_R_Rls,
        C088_ImgOvalHP_L_Rls,
        C089_ImgOvalCurvedHP_R_Rls,
        C090_ImgOvalCurvedHP_L_Rls,
        C091_ImgAngledHP_R_Rls,
        C092_ImgAngledHP_L_Rls,
        C093_ImgCurvedHP_R_Press,
        C094_ImgCurvedHP_L_Press,
        C095_ImgTightHP_R_Press,
        C096_ImgTightHP_L_Press,
        C097_ImgStrightHP_R_Press,
        C098_ImgStrightHP_L_Press,
        C099_ImgTinyHP_R_Press,
        C100_ImgTinyHP_L_Press,
        C101_ImgTinyCurvedHP_R_Press,
        C102_ImgTinyCurvedHP_L_Press,
        C103_ImgDoubleHP_R_Press,
        C104_ImgDoubleHP_L_Press,
        C105_ImgOvalHP_R_Press,
        C106_ImgOvalHP_L_Press,
        C107_ImgOvalCurvedHP_R_Press,
        C108_ImgOvalCurvedHP_L_Press,
        C109_ImgAngledHP_R_Press,
        C110_ImgAngledHP_L_Press,
        C111_signorelojdown,
        C111_signorelojup,
        C111_TscImgMan,
        C112_1_ZonaSeleccionadaHP1,
        C112_2_ZonaSeleccionadaHP2,
        C112_3_ZonaSeleccionadaHP3,
        C112_4_ZonaSeleccionadaHP4,
        C113_BotonTorsoPressMujer,
        C114_TscBotonTorsoMujer,
        C115_BotonPiernasRlsMujer,
        C117_TscBotonPiernasMujer,
        C118_BotonBrazosRlsMujer,
        C120_TscBotonBrazosMujer,
        C121_BotonEspaldaRlsMujer,
        C123_TscBotonEspladaMujer,
        C124_BotonPiernaMusloRlsMujer,
        C126_TscBotonPiernaMusloMujer,
        C127_BotonCuelloRlsMujer,
        C129_TscBotonCuelloMujer,
        C130_BotonTorsoRlsHombre,
        C132_TscBotonTorsoHombre,
        C133_BotonPiernasRlsHombre,
        C135_TscBotonPiernasHombre,
        C136_BotonBrazosRlsHombre,
        C138_TscBotonBrazosHombre,
        C139_BotonEspaldaRlsHombre,
        C141_TscBotonEspladaHombre,
        C142_BotonPiernaMusloRlsHombre,
        C144_TscBotonPiernaMusloHombre,
        C145_BotonCuelloRlsHombre,
        C147_TscBotonCuelloHombre,
        C148_ZonaAplicacionManipPunto,
        C149_ZonaAplicacionManipPuntoSelected,
        C150_TscZonaAplicacionManipPunto,
        C151_ZonaAplicacionManipPuntoHP1,
        C152_ZonaAplicacionManipPuntoHP2,
        C153_ZonaAplicacionManipPuntoHP3,
        C154_ZonaAplicacionManipPuntoHP4,
        C155_RetrocesoRls,
        C156_RetrocesoPress,
        C157_OkeyRls,
        C158_OkeyPress2,
        C159_TscOkey_Retroceso,
        C160_ZonaSeleccionadaHP1,
        C160_ZonaSeleccionadaHP1_seleccionado,
        C161_ZonaSeleccionadaHP2,
        C161_ZonaSeleccionadaHP2_seleccionado,
        C162_ZonaSeleccionadaHP3,
        C162_ZonaSeleccionadaHP3_seleccionado,
        C163_ZonaSeleccionadaHP4,
        C163_ZonaSeleccionadaHP4_seleccionado,
        C164_PopUpImagenReloj,
        C164_Z_PopUpImagenReloj,
        C165_PopUpBoton50MinRls,
        C166_PopUpBoton50MinPress,
        C167_PopUpBoton70MinRls,
        C168_PopUpBoton70MinPress,
        C169_TscPopUpBoton70and45,
        C170_PopUpImagenSuccion,
        C176_PopUpBotonTestRls,
        C177_PopUpBotonTestPress,
        C178_TscPopUpBotonTest,
        C179_PopupBotonActivarRls,
        C180_PopupBotonActivarPress,
        C181_PopupBotonActivarTsc,
        C182_PopUpRFIDfail,
        C182_PopUpRFIDFondo,
        C182_PopUpRFIDlabelDM,
        C182_PopUpRFIDlabelZ0,
        C182_PopUpRFIDlabelZ1,
        C182_PopUpRFIDlabelZ2,
        C182_PopUpRFIDlabelZ3,
        C182_PopUpRFIDsuccess,
        C182_PopUpRFIDunknown,
        C182_PopUpRFIDwrong,
        C183_IndicadorRFIDHP1Off,
        C184_IndicadorBotonHP1Off,
        C185_IndicadorVacHP1Off,
        C186_IndicadorFrioHP1Off,
        C187_IndicadorRFIDHP2Off,
        C188_IndicadorBotonHP2Off,
        C189_IndicadorVacHP2Off,
        C190_IndicadorFrioHP2Off,
        C191_IndicadorRFIDHP3Off,
        C192_IndicadorBotonHP3Off,
        C193_IndicadorVacHP3Off,
        C194_IndicadorFrioHP3Off,
        C195_IndicadorRFIDHP4Off,
        C196_IndicadorBotonHP4Off,
        C197_IndicadorVacHP4Off,
        C198_IndicadorFrioHP4Off,
        C199_BotonGuardarMenuRightPress,
        C200_BotonGuardarMenuRightRls,
        C201_TscBotonGuardarMenu,
        C202_BotonGuardarMenuLeftPress,
        C203_BotonGuardarMenuLeftRls,
        C205_ImgTorsoMujer,
        C206_ImgPiernasMujer,
        C207_BrazosEspaldaMujer,
        C208_PiernaMusloMujer,
        C209_CuelloMujer,
        C210_TorsoHombre,
        C211_PiernasHombre,
        C212_BrazosEspaldaHombre,
        C213_PiernaMusloHombre,
        C214_CuelloHombre,
        C216_PopUpManipHP1,
        C217_PopUpManipHP2,
        C218_PopUpManipHP3,
        C219_PopUpManipHP4,
        C220_PopUpBotonAuto,
        C221_PopUpBotonAutoPress,
        C221_Z_PopupBotonAutoTsc,
        C222_B_PopUpIndmanoPressx2,
        C222_PopUpIndmanoPress,
        C233_ImgPixelBlanco,
        C234_AlarmaFondoCentral2,
        C234_AlarmaFondoHP1,
        C234_AlarmaFondoHP2,
        C234_AlarmaFondoHP3,
        C234_AlarmaFondoHP4,
        C237_Calculadoraboton1Rls,
        C238_Calculadoraboton2Rls,
        C239_Calculadoraboton3Rls,
        C240_Calculadoraboton4Rls,
        C241_Calculadoraboton5Rls,
        C242_Calculadoraboton6Rls,
        C243_Calculadoraboton7Rls,
        C244_Calculadoraboton8Rls,
        C245_Calculadoraboton9Rls,
        C246_CalculadorabotonTsc,
        C247_Calculadoraboton0Rls,
        C248_Calculadoraboton0Tsc,
        C249_Calculadoranumero1,
        C250_Calculadoranumero2,
        C251_Calculadoranumero3,
        C252_Calculadoranumero4,
        C253_Calculadoranumero5,
        C254_Calculadoranumero6,
        C255_Calculadoranumero7,
        C256_Calculadoranumero8,
        C257_Calculadoranumero9,
        C258_Calculadoranumero0,
        C259_CalculadorabotonmasRls,
        C260_CalculadorabotonmenosRls,
        C261_CalculadorabotonCERls,
        C262_CalculadorabotonenterRls,
        C263_CalculadorabotoncomaRls,
        C264_CalculadorabotonenterTsc,
        C265_Calculadorafondo_03,
        C266_Calculadoraboton1Press,
        C267_Calculadoranumero2Press,
        C268_Calculadoraboton3Press,
        C269_Calculadoraboton4Press,
        C270_Calculadoraboton5Press,
        C271_Calculadoranumero6Press,
        C272_Calculadoraboton7Press,
        C273_Calculadoraboton8Press,
        C274_Calculadoranumero9Press,
        C275_Calculadoraboton0Press,
        C275_CalculadorabotonenterPress,
        C276_CalculadorabotonmasPress,
        C277_CalculadorabotonmenosPress,
        C278_CalculadorabotoncomaPress,
        C279_CalculadorabotonCEPress,
        C280_BackCalculadorafondo,
        C281_InfoRls,
        C282_InfoPress,
        C283_TscInfo,
        C284_PopUpSugerenciasFondo_03,
        C285_PopUpMarcaaguaCurved,
        C286_PopUpMarcaaguaTight,
        C287_PopUpMarcaaguaStraight,
        C288_PopUpMarcaaguaTiny,
        C289_PopUpMarcaaguaTinyCurved,
        C290_PopUpMarcaaguaDouble,
        C291_PopUpMarcaaguaOval,
        C292_PopUpMarcaaguaOvalCurved,
        C293_PopUpMarcaaguaAngled,

        C294_IdiomasfrancesRls,
        C295_IdiomasfrancesPress,
        C296_TscIdiomasgeneral,
        C297_IdiomascastellanoRls,
        C298_IdiomascastellanoPress,
        C299_IdiomasinglesRls,
        C300_IdiomasinglesPress,
        C301_IdiomasitalianoRls,
        C302_IdiomasitalianoPress,
        C303_IdiomasalemanRls,
        C304_IdiomasalemanPress,
        C305_IdiomaspolacoRls,
        C306_IdiomaspolacoPress,
        C307_IdiomasrusoRls,
        C308_IdiomasrusoPress,
        C309_IdiomasportuguesRls,
        C310_IdiomasportuguesPress,
        C311_IdiomaschinoRls,
        C312_IdiomaschinoPress,
        C313_IdiomasjaponesRls,
        C314_IdiomasjaponesPress,
        C315_IdiomascoreanoRls,
        C316_IdiomascoreanoPress,

        C317_FondoConfiguracion,
        C318_Configuracionloading0,
        C318_Configuracionloading0_Z,
        C318_Configuracionloading20,
        C318_Configuracionloading20_Z,
        C319_Configuracionloading40,
        C319_Configuracionloading40_Z,
        C320_Configuracionloading60,
        C320_Configuracionloading60_Z,
        C321_Configuracionloading80,
        C321_Configuracionloading80_Z,
        C322_Configuracionloading100,
        C322_Configuracionloading100_Z,
        C323_2_ConfigBotonRecargaCoolantRls,
        C323_ConfgBotondownloadRls,
        C324_2_ConfigBotonRecargaCoolantPress,
        C324_ConfgBotondownloadPress,
        C325_2_ConfigBotonRecargaCoolantTsc,
        C325_3_ConfigSwitchResuctionViewerTsc,
        C325_ConfgBotondownloadTsc,
        C326_Configuracionnumero1,
        C327_Configuracionnumero2,
        C328_Configuracionnumero3,
        C329_Configuracionnumero4,
        C330_Configuracionnumero5,
        C331_Configuracionnumero6,
        C332_Configuracionnumero7,
        C333_Configuracionnumero8,
        C334_Configuracionnumero9,
        C335_Configuracionguion,
        C336_Configuracionnumero0,
        C337_PopupBotonsuccion1Rls,
        C338_PopupBotonsuccion1Press,
        C339_PopupBotonsuccion2Rls,
        C340_PopupBotonsuccion2Press,
        C341_PopupBotonsuccion3Rls,
        C342_PopupBotonsuccion3Press,
        C343_BotonVacuumSmall1Rls,
        C344_BotonVacuumSmall1MarcaAgua,
        C344_BotonVacuumSmall1Prs,
        C345_BotonVacuumSmall2Rls,
        C346_BotonVacuumSmall2MarcaAgua,
        C346_BotonVacuumSmall2Prs,
        C347_BotonVacuumSmall3Rls,
        C348_BotonVacuumSmall3MarcaAgua,
        C348_BotonVacuumSmall3Prs,
        C349_BotonVacuumDesplegable_L,
        C350_BotonVacuumDesplegable_R_03,
        C351_TscBotonVacuum1,
        C352_BotonVacuum1PressArrowLeft,
        C352_BotonVacuum1PressArrowRight,
        C352_BotonVacuum2PressArrowLeft,
        C352_BotonVacuum2PressArrowRight,
        C352_BotonVacuum3PressArrowLeft,
        C352_BotonVacuum3PressArrowRight,
        C352_FlechaVacuumLeft,
        C353_BotonVacuum1RlsArrowLeft,
        C353_BotonVacuum1RlsArrowRight,
        C353_BotonVacuum2RlsArrowLeft,
        C353_BotonVacuum2RlsArrowRight,
        C353_BotonVacuum3RlsArrowLeft,
        C353_BotonVacuum3RlsArrowRight,
        C353_FlechaVacuumRight,
        C354_BotonVacuum1MarcaAguaArrowLeft,
        C354_BotonVacuum2MarcaAguaArrowLeft,
        C354_BotonVacuum3MarcaAguaArrowLeft,
        C355_signoalarma,
        C356_BotonAlarmaCentralOkRls,
        C357_BotonAlarmaCentralOkPress,
        C358_BotonAlarmaCentralOkTsc,
        C420_Menualarmasfondo,
        C421_Menualarmatemppress,
        C422_Menualarmafiltropress,
        C423_Menualarmarfidpress,
        C424_Menualarmaaguamitadpress,
        C425_Menualarmasinaguapress,
        C426_Menualarmatiempopress,
        C427_HPalarmaObstruccion,
        C428_HPalarmaLlenadoAgua,
        C429_HPalarmaBoton,
        C430_HPalarmaResucciones,
        C431_HPalarmaLimpieza0,
        C432_HPalarmaLimpieza1,
        C433_HPalarmaLimpiezacolocar0,
        C434_HPalarmaLimpiezacolocar1,
        C435_HPalarmaTemperatura,
        C436_HPalarmaDesconexion,
        C438_HPalarmaPlicainsuficiente,
        C439_HPalarmaPlicaOK,
        C452_MenuAlarmaOK_press,
        C453_MenuAlarmaOK_MarcaAgua,
        C453_MenuAlarmaOK_MarcaAgua1,
        C453_MenuAlarmaOK_rls,
        C453_MenuAlarmaOK_tsc,
        C454_MenuAlarmaNO_press,
        C455_MenuAlarmaNO_MarcaAgua,
        C455_MenuAlarmaNO_MarcaAgua1,
        C455_MenuAlarmaNO_rls,
        C456_MenuLimpiezaClean_Rls,
        C457_MenuLimpiezaClean_Press,
        C458_MenuLimpiezaClean_MarcaAgua,
        C458_MenuLimpiezaClean_MarcaAgua1,
        C460_LimiteResuccionesSuperado,
        C461_CaracterComa,
        C461_CaracterDosPuntos,
        C461_CaracterNegativo,
        C461_CaracterPunto,
        C461_FondoNumVwrError,
        C461_Numero0,
        C461_Numero1,
        C461_Numero2,
        C461_Numero3,
        C461_Numero4,
        C461_Numero5,
        C461_Numero6,
        C461_Numero7,
        C461_Numero8,
        C461_Numero9,
        C462_FondoNumVwrErrorVerde,
        C463_FondoNumVwrErrorRojo,
        C464_FondoNumVwrErrorRojoNegro,
        C465_Menu_error_lectortiempo,
        C465_tiempo_CaracterBarra,
        C465_tiempo_CaracterComa,
        C465_tiempo_CaracterDosPuntos,
        C465_tiempo_CaracterPunto,
        C465_tiempo_Numero0,
        C465_tiempo_Numero1,
        C465_tiempo_Numero2,
        C465_tiempo_Numero3,
        C465_tiempo_Numero4,
        C465_tiempo_Numero5,
        C465_tiempo_Numero6,
        C465_tiempo_Numero7,
        C465_tiempo_Numero8,
        C465_tiempo_Numero9,
        C500_Number_0Resuctions,
        C501_Number_1Resuctions,
        C502_Number_2Resuctions,
        C503_Number_3Resuctions,
        C504_Number_4Resuctions,
        C505_Number_5Resuctions,
        C506_Number_6Resuctions,
        C507_Number_7Resuctions,
        C508_Number_8Resuctions,
        C509_Number_9Resuctions,
        C510_resuccionindicador,
        C512_TempShowboton_Press,
        C512_TempShowboton_Rls,
        C513_resuccionboton_Press,
        C514_resuccionboton_Rls,
        C515_Limpiezamanipulox4_Press,
        C516_Limpiezamanipulox4_Rls,
        C518_LimpiezamanipuloHP3_Rls,
        C520_LimpiezamanipuloHP3_Press,
        C521_LimpiezamanipuloHP1_Rls,
        C522LimpiezamanipuloHP1_Press,
        C524_LimpiezamanipuloHP2_Rls,
        C525_LimpiezamanipuloHP2_Press,
        C527_LimpiezamanipuloHP4_Rls,
        C528_LimpiezamanipuloHP4_Press,
        C530_botoncancel_MarcaAgua,
        C531_botoncancel_Rls,
        C532_botoncancel_Press,
        C533_fondocontador,
        C550_SPIerr,
        C551_Com485err,
        C552_Caudalerr,
        C553_PowerErr,
        C554_RFIDerr,
        C555_InsfNTC,
        C556_ToutVacc,
        C557_SinTramasMain,
        C558_ErrDesconocido,
        C559_InternalTemp,
        C560_InternalSensors,
        C561_HPdesconfig,
        C562_HPalarma,
        C563_PCBdanada,
        C564_TestInicialFallo,
        C600_Number_0_ResucInd,
        C601_Number_1_ResucInd,
        C602_Number_2_ResucInd,
        C603_Number_3_ResucInd,
        C604_Number_4_ResucInd,
        C605_Number_5_ResucInd,
        C606_Number_6_ResucInd,
        C607_Number_7_ResucInd,
        C608_Number_8_ResucInd,
        C609_Number_9_ResucInd,
        C610_GPRS_no_coverage,			//V7790 - GPRS coverage

        APP_GUI_NUM_IMAGES
    }cAppGUIimageIDlist;
    Q_ENUM_NS(EAppGUIimageIDlist)

    // Widgets de la Interface
    typedef enum EAppGUIwidgetIDlist
    {

        //PANTALLA DE CARGA
        ImgLoadScrBckGnd,
        ImgLoadAnim1,
        ImgLoadAnim2,
        ImgLoadAnim3,
        ImgLoadAnim4,
        ImgLoadAnim5,
        ImgLoadAnim6,
        ImgLoadAnim7,
        ImgLoadAnim8,

        //PANTALLA DE INICIO
        ImgInitScrBckGnd,
        ButSelectWoman,
        ButSelectMan,
        ImgInitGPRScoverage,		//V7790

        //Menu principal
        ButInitScrShowMainMenu,
        ButInitScrHideMainMenu,
        ImgInitScrHome,
        ButInitScrCfg,
        ButInitScrCalc,
        ButInitScrData,

        SwInitScrAvisos,
        ImgInitScrNotificacion,
        PopupInitScrAvisos,
        ImgPopUpInitScrAvisoBckGND,
        ImgPopUpInitScrAvisoNivelAguaBajo,
        ImgPopUpInitScrAvisoNivelAguaMedio,
        ImgPopUpInitScrAvisoTempAmb,
        ImgPopUpInitScrAvisoRFID,
        ImgPopUpInitScrAvisoRTC,
        ImgPopUpInitScrAvisoFiltroAire,

        //PANTALLA DE TRATAMIENTO
        ImgTrtScrBckGnd,
        ImgFullBodyAndZoom,
        ImgTrtGPRScoverage,				//V7790

        //Fondos de los paneles de control
        ImgCtrlPnlBckGndHP1,
        ImgCtrlPnlBckGndHP2,
        ImgCtrlPnlBckGndHP3,
        ImgCtrlPnlBckGndHP4,

        //Colores fondos de los paneles de control
        ImgColourCtrlPnlBckGndHP1,
        ImgColourCtrlPnlBckGndHP2,
        ImgColourCtrlPnlBckGndHP3,
        ImgColourCtrlPnlBckGndHP4,

        //Indicadores de accion del HP cuando activos, los inactivos forman parte del fondo
        ImgCtrlPnlRFIDblinkHP1,
        ImgCtrlPnlRFIDblinkHP2,
        ImgCtrlPnlRFIDblinkHP3,
        ImgCtrlPnlRFIDblinkHP4,
        ImgCtrlPnlPulBlinkHP1,
        ImgCtrlPnlPulBlinkHP2,
        ImgCtrlPnlPulBlinkHP3,
        ImgCtrlPnlPulBlinkHP4,
        ImgCtrlPnlVacBlinkHP1,
        ImgCtrlPnlVacBlinkHP2,
        ImgCtrlPnlVacBlinkHP3,
        ImgCtrlPnlVacBlinkHP4,
        ImgCtrlPnlCoolingBlinkHP1,
        ImgCtrlPnlCoolingBlinkHP2,
        ImgCtrlPnlCoolingBlinkHP3,
        ImgCtrlPnlCoolingBlinkHP4,

        //Botones del panel de control de PLAY y Test Vacum
        ButCtrlPnlPlayHP1,
        ButCtrlPnlPlayHP2,
        ButCtrlPnlPlayHP3,
        ButCtrlPnlPlayHP4,
        SwCtrlPnlTstVacHP1,
        SwCtrlPnlTstVacHP2,
        SwCtrlPnlTstVacHP3,
        SwCtrlPnlTstVacHP4,

        //Botones (switch) que permite seleccionar modo de tratamiento AUTO o MANUAL
        ButSwtchModeAutoManualHP1,
        ButSwtchModeAutoManualHP2,
        ButSwtchModeAutoManualHP3,
        ButSwtchModeAutoManualHP4,

        //Visores de tiempo restante de trt y boton de seleccion de tiempo
        NumVwrTimeHP1,
        NumVwrTimeHP2,
        NumVwrTimeHP3,
        NumVwrTimeHP4,
        ButSelectTimeHP1,
        ButSelectTimeHP2,
        ButSelectTimeHP3,
        ButSelectTimeHP4,
        ButVwrTemperatureHP1,
        ButVwrTemperatureHP2,
        ButVwrTemperatureHP3,
        ButVwrTemperatureHP4,

        //Visor numerico para contabilizar resucciones
        NumVwrResucctionCountHP1,
        NumVwrResucctionCountHP2,
        NumVwrResucctionCountHP3,
        NumVwrResucctionCountHP4,

        //Boton con la imagen e imagen con el texto del modelo
        ImgModelTextHP1,
        ImgModelTextHP2,
        ImgModelTextHP3,
        ImgModelTextHP4,
        ButModelImageHP1,
        ButModelImageHP2,
        ButModelImageHP3,
        ButModelImageHP4,

        //Botonoes de recogida y despliegue del panel de control
        ButHideControlPanelHP1,
        ButHideControlPanelHP2,
        ButHideControlPanelHP3,
        ButHideControlPanelHP4,
        ButShowControlPanelHP1,
        ButShowControlPanelHP2,
        ButShowControlPanelHP3,
        ButShowControlPanelHP4,

        //Botones de selección de Full body
        ButFullBodyTorso,
        ButFullBodyPiernas,
        ButFullBodyBrazos,
        ButFullBodyEspalda,
        ButFullBodyPiernaMuslo,
        ButFullBodyCuello,

        //Puntos seleccion de zona de tratamiento cuando zoom
        SwDotZone0,
        SwDotZone1,
        SwDotZone2,
        SwDotZone3,
        SwDotZone4,
        SwDotZone5,
        SwDotZone6,
        SwDotZone7,
        SwDotZone8,
        SwDotZone9,
        SwDotZone10,
        SwDotZone11,
        SwDotZone12,
        SwDotZone13,
        SwDotZone14,

        //Punto seleccionado para tratamiento con ese HP a mostrar en full body
        ImgSelectedTrtZoneHP1,
        ImgSelectedTrtZoneHP2,
        ImgSelectedTrtZoneHP3,
        ImgSelectedTrtZoneHP4,

        //POPUP's
        //Common
        ButPopUpReturn,
        ImgPopUpHPcolorBar,

        //PopUp Time widgets
        PopUpTime,
        ButPopUpTime50min,
        ButPopUpTime70min,
        ImgPopUpTime1sel,
        ImgPopUpTime2sel,

        //PopUp Test Vacum widgets
        PopUpTstVac,
        ImgPopUpTstVacBckGnd,
        ImgPopUpTstVacLowLvl,
        ImgPopUpTstVacMidLvl,
        ImgPopUpTstVacHighLvl,
        ImgPopUpTstVacPulHand,
        ImgPopUpTstVacPulHandx2,
        ButPopUpTstVacManualLowLvl,
        ButPopUpTstVacManualMidLvl,
        ButPopUpTstVacManualHighLvl,
        ButPopUpTstVacAuto,
        SwPopUpTstVacLowLvl,
        SwPopUpTstVacMidLvl,
        SwPopUpTstVacHighLvl,
        ImgPopUpTstVacAUTOstatus,

        //PopUp Test Vacuum 2 widgets
        PopUpTstVacSmall,
        ImgPopUpVacSelBck,
        ButPopUpTstVacSmallLowLvl,
        ButPopUpTstVacSmallMedLvl,
        ButPopUpTstVacSmallHighLvl,

        //PopUp RFID widgets
        PopUpRFID,
        ImgPopUpRFIDbckGnd,
        ImgPopUpRFIDlabel,
        ImgPopUpRFIDresult,
        ButPopUpRFIDreuseLabel,
        NumVwrPopUpRFIDrestTime,

        //PopUp Recommendation widgets
        SwPopUpRecommInfo,
        PopUpRecomm,
        ImgPopUpRecommbckGnd,
        ImgPopUpRecommCurved,
        ImgPopUpRecommTight,
        ImgPopUpRecommStright,
        ImgPopUpRecommTiny,
        ImgPopUpRecommTinyCurved,
        ImgPopUpRecommDouble,
        ImgPopUpRecommOval,
        ImgPopUpRecommOvalCurved,
        ImgPopUpRecommAngled,

        //Menu Principal
        ButTrtScrShowMainMenu,
        ButTrtScrHideMainMenu,
        ButTrtScrHome,
        ButTrtScrCfg,
        ButTrtScrCalc,
        ButTrtScrData,

        SwTrtScrAvisos,
        ImgTrtScrNotificacion,
        PopupTrtScrAvisos,
        ImgPopUpTrtScrAvisoBckGND,
        ImgPopUpTrtScrAvisoNivelAguaBajo,
        ImgPopUpTrtScrAvisoNivelAguaMedio,
        ImgPopUpTrtScrAvisoTempAmb,
        ImgPopUpTrtScrAvisoRFID,
        ImgPopUpTrtScrAvisoRTC,
        ImgPopUpTrtScrAvisoFiltroAire,

        //popUp's Error
        ImgPopUpErrBckGndHP1,
        ImgPopUpErrBckGndHP2,
        ImgPopUpErrBckGndHP3,
        ImgPopUpErrBckGndHP4,
        ImgPopUpErrBckGndUC,
        NumVwrPopUpErrHP1,
        NumVwrPopUpErrHP2,
        NumVwrPopUpErrHP3,
        NumVwrPopUpErrHP4,
        NumVwrPopUpErrUC,
        ImgPopUpErrMsgHP1,
        ImgPopUpErrMsgHP2,
        ImgPopUpErrMsgHP3,
        ImgPopUpErrMsgHP4,
        ImgPopUpErrMsgUC,
        ButPopUpErrOkHP1,
        ButPopUpErrOkHP2,
        ButPopUpErrOkHP3,
        ButPopUpErrOkHP4,
        ButPopUpErrOkUC,
        NumVwrPopUpErrTRTtimeHP1,
        NumVwrPopUpErrTRTtimeHP2,
        NumVwrPopUpErrTRTtimeHP3,
        NumVwrPopUpErrTRTtimeHP4,

        //PopUp's CleanUp
        ImgPopUpCleanBckGndHP1,
        ImgPopUpCleanBckGndHP2,
        ImgPopUpCleanBckGndHP3,
        ImgPopUpCleanBckGndHP4,
        NumVwrPopUpCleanHP1,
        NumVwrPopUpCleanHP2,
        NumVwrPopUpCleanHP3,
        NumVwrPopUpCleanHP4,
        ButPopUpCleanHP1,
        ButPopUpCleanHP2,
        ButPopUpCleanHP3,
        ButPopUpCleanHP4,
        ButPopUpCleanYESHP1,
        ButPopUpCleanYESHP2,
        ButPopUpCleanYESHP3,
        ButPopUpCleanYESHP4,
        ButPopUpCleanNOHP1,
        ButPopUpCleanNOHP2,
        ButPopUpCleanNOHP3,
        ButPopUpCleanNOHP4,
        ImgPopUpCleanHP1,
        ImgPopUpCleanHP2,
        ImgPopUpCleanHP3,
        ImgPopUpCleanHP4,
        ButPopUpCleanCancelHP1,
        ButPopUpCleanCancelHP2,
        ButPopUpCleanCancelHP3,
        ButPopUpCleanCancelHP4,
        NumVwrPopUpCleanNumCancelHP1,
        NumVwrPopUpCleanNumCancelHP2,
        NumVwrPopUpCleanNumCancelHP3,
        NumVwrPopUpCleanNumCancelHP4,


        //Pantalla de la calculadora
        ImgFondoCalcScreen,
        ImgCuerpoCalc,
        NumVwrPantallaCalc,
        ButNum0Calc,
        ButNum1Calc,
        ButNum2Calc,
        ButNum3Calc,
        ButNum4Calc,
        ButNum5Calc,
        ButNum6Calc,
        ButNum7Calc,
        ButNum8Calc,
        ButNum9Calc,
        ButMasCalc,
        ButMenosCalc,
        ButEnterCalc,
        ButCECalc,
        ButComaCalc,

        //Menu principal - calculadora
        ButCalcScrShowMainMenu,
        ButCalcScrHideMainMenu,
        ButCalcScrHome,
        ButCalcScrCfg,
        ImgCalcScrCalc,
        ButCalcScrData,

        SwCalcScrAvisos,
        ImgCalcScrNotificacion,
        PopupCalcScrAvisos,
        ImgPopUpCalcScrAvisoBckGND,
        ImgPopUpCalcScrAvisoNivelAguaBajo,
        ImgPopUpCalcScrAvisoNivelAguaMedio,
        ImgPopUpCalcScrAvisoTempAmb,
        ImgPopUpCalcScrAvisoRFID,
        ImgPopUpCalcScrAvisoRTC,
        ImgPopUpCalcScrAvisoFiltroAire,

        //Pantalla de configuración
        ImgFondoCfgScreen,
        ImgVentanaCfgCastellano,
        ButCfgActualizarSoftware,
        ImgSoftwareProgressionUpdateBar,
        NumVwrModeloMaqCfg,
        NumVwrVersionSoftwareCfg,
        ButCfgRecargaCoolant,
        SwCfgResuctionViewer,
        SwCfgTemperatureViewer,
        ButCfgCleanUpHP1,
        ButCfgCleanUpHP2,
        ButCfgCleanUpHP3,
        ButCfgCleanUpHP4,
        ButCfgCleanUpRoundHP,
        ImgCfgGPRScoverage,		//V7790

        //Menu principal - configuracion
        ButCfgScrShowMainMenu,
        ButCfgScrHideMainMenu,
        ButCfgScrHome,
        ImgCfgScrCfg,
        ButCfgScrCalc,
        ButCfgScrData,

        SwCfgScrAvisos,
        ImgCfgScrNotificacion,
        PopupCfgScrAvisos,
        ImgPopUpCfgScrAvisoBckGND,
        ImgPopUpCfgScrAvisoNivelAguaBajo,
        ImgPopUpCfgScrAvisoNivelAguaMedio,
        ImgPopUpCfgScrAvisoTempAmb,
        ImgPopUpCfgScrAvisoRFID,
        ImgPopUpCfgScrAvisoRTC,
        ImgPopUpCfgScrAvisoFiltroAire,

        //Pantalla de idiomas
        ImgFondoLanScreen,

        SwLanFrances,
        SwLanCastellano,
        SwLanIngles,
        SwLanItaliano,
        SwLanAleman,
        SwLanPolaco,
        SwLanRuso,
        SwLanPortugues,
        SwLanChino,
        SwLanJapones,
        SwLanCoreano,

        //Menu principal - idiomas
        ButLanScrShowMainMenu,
        ButLanScrHideMainMenu,
        ButLanScrHome,
        ButLanScrCfg,
        ButLanScrCalc,
        ImgLanScrData,

        SwLanScrAvisos,
        ImgLanScrNotificacion,
        PopupLanScrAvisos,
        ImgPopUpLanScrAvisoBckGND,
        ImgPopUpLanScrAvisoNivelAguaBajo,
        ImgPopUpLanScrAvisoNivelAguaMedio,
        ImgPopUpLanScrAvisoTempAmb,
        ImgPopUpLanScrAvisoRFID,
        ImgPopUpLanScrAvisoRTC,
        ImgPopUpLanScrAvisoFiltroAire,

        //Pantalla de SAT
        ImgFondoSATscreen,
        ButHomeSATscreen,

        NumVwrPaginaSATscreen,
        ButNextPagSATscreen,
        ButPrevPagSATscreen,

        ImgVwr1,
        ImgVwr2,
        ImgVwr3,
        ImgVwr4,
        ImgVwr5,
        ImgVwr6,
        ImgVwr7,
        ImgVwr8,
        ImgVwr9,
        ImgVwr10_1,
        ImgVwr10_2,
        ImgVwr11_1,
        ImgVwr11_2,
        ImgVwr12_1,
        ImgVwr12_2,
        ImgVwr13_1,
        ImgVwr13_2,
        ImgVwr14_1,
        ImgVwr14_2,
        ImgVwr15_1,
        ImgVwr15_2,
        ImgVwr16_1,
        ImgVwr16_2,
        ImgVwr17_1,
        ImgVwr17_2,
        ImgVwr18_1,
        ImgVwr18_2,
        ImgVwr19_1,
        ImgVwr19_2,
        ImgVwr20_1,
        ImgVwr20_2,
        ImgVwr21_1,
        ImgVwr21_2,
        ImgVwr22_1,
        ImgVwr22_2,
        ImgVwr23_1,
        ImgVwr23_2,
        ImgVwr24_1,
        ImgVwr24_2,
        ImgVwr25_1,
        ImgVwr25_2,
        ImgVwr26_1,
        ImgVwr26_2,
        ImgVwr27_1,
        ImgVwr27_2,
        ImgVwr28_1,
        ImgVwr28_2,

        NumVwr1,
        NumVwr2,
        NumVwr3,
        NumVwr4,
        NumVwr5,
        NumVwr6,
        NumVwr7,
        NumVwr8,
        NumVwr9,
        NumVwr10,
        NumVwr11,
        NumVwr12,
        NumVwr13,
        NumVwr14,
        NumVwr15,
        NumVwr16,
        NumVwr17,
        NumVwr18,
        NumVwr19,
        NumVwr20,
        NumVwr21,
        NumVwr22,
        NumVwr23,
        NumVwr24,
        NumVwr25,
        NumVwr26,
        NumVwr27,
        NumVwr28,

        ImgVacuum,
        ImgFrio,
        ImgRFID,
        ImgTestLed,
        ImgTestLedStatus,
        ImgTestLedRGD,
        SwVacuum,
        SwFrio,
        SwRFID,
        SwTestLed,
        SwTestLedRGB,

        PopupErrorSAT,
        ImgVwrFondoErrorSAT,
        NumVwrError1,
        NumVwrError2,
        NumVwrError3,
        NumVwrError4,
        NumVwrError5,
        ButOkerr,

        //Pantalla de FATIGA
        ImgFondoFATIGAscreen,
        ButHomeFATIGAscreen,

        ImgStep1,
        ImgStep1status,
        ImgStep2,
        ImgStep2status,
        ImgStep3,
        ImgStep3status,
        ImgStep4,
        ImgStep4statusHP1,
        ImgStep4statusHP2,
        ImgStep4statusHP3,
        ImgStep4statusHP4,
        ImgStep5,
        ImgStep5statusHP1,
        ImgStep5statusHP2,
        ImgStep5statusHP3,
        ImgStep5statusHP4,
        ImgStep6,
        ImgStep6status,
        ImgStep7,
        ImgStep7status,

        NumVwrTempAmb,
        NumVwrTempBomba,
        NumVwrTempRetorno,
        NumVwrCaudalRetorno,
        NumVwrVtobera,
        NumVwrRth,
        NumVwrCPI,
        NumVwrCaudalRetornoHP1,
        NumVwrCaudalRetornoHP2,
        NumVwrCaudalRetornoHP3,
        NumVwrCaudalRetornoHP4,
        NumVwrVacuumHP1,
        NumVwrVacuumHP2,
        NumVwrVacuumHP3,
        NumVwrVacuumHP4,
        NumVwrFatigaTime,
        NumVwrErrFatiga1,
        NumVwrErrFatiga2,
        NumVwrErrFatiga3,
        NumVwrErrFatiga4,
        NumVwrErrFatiga5,

        ImgVwrVAC1,
        ImgVwrVAC2,
        ImgVwrVAC3,
        ImgVwrVAC4,
        ImgVwrCaudal1,
        ImgVwrCaudal2,
        ImgVwrCaudal3,
        ImgVwrCaudal4,
        ImgVwrTempAmb,
        ImgVwrTempBomba,
        ImgVwrTempRetorno,
        ImgVwrCaudalRetorno,
        ImgVwrVtobera,
        ImgVwrRth,
        ImgVwrCPI,

        SwFatigueFailBeep,

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

extern const uint32 APP_GUI_TRT_SCR_BUT_MODEL_IMG_SIDE_FROM_SLOT_IMG[APP_GUI_MAX_PRS_RLS][APP_GUI_MAXNUM_HP][HP_CRYO_NUM_HP_MODELS];
extern const uint32 APP_GUI_TRT_SCR_BUT_MODE_IMG_NO_HP_IMG[APP_GUI_MAXNUM_HP];
extern const uint32 APP_GUI_TRT_SCR_BUT_MODEL_IMG_WIDGETS[APP_GUI_MAXNUM_HP];
extern const uint32 APP_GUI_TRT_SCR_BUT_MODE_TRT_WIDGETS[APP_GUI_MAXNUM_HP];

//extern const uint32 APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_SHOW[APP_GUI_MAXNUM_HP][APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_SHOW_NUM];
//extern const uint32 APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_HIDE[APP_GUI_MAXNUM_HP][APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_HIDE_NUM];
//extern const uint32 APP_GUI_TRT_SCR_CTRL_PNL_COLOUR_IMGS [APP_GUI_MAXNUM_HP][APP_GUI_TRT_SCR_CTRL_PNL_COLOUR_STATES_IMGS];
extern const uint32 APP_GUI_TRT_SCR_CTRL_PNL_COLOUR_WIDGETS [APP_GUI_MAXNUM_HP];

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

extern const uint32 APP_GUI_TRT_SCR_BLINK_INDICATORS_WIDGETS[APP_GUI_MAXNUM_HP][APP_GUI_MAX_BLINK_INDICATORS];
extern const uint32 APP_GUI_TRT_SCR_HP_MODEL_TEXT_IMG[APP_GUI_MAXNUM_HP][HP_CRYO_NUM_HP_MODELS];
extern const uint32 APP_GUI_TRT_SCR_HP_MODEL_TEXT_WIDGETS[APP_GUI_MAXNUM_HP];

extern const uint32 APP_GUI_TRT_SCR_BUT_SEL_TIME_WIDGETS[APP_GUI_MAXNUM_HP];
extern const uint32 APP_GUI_TRT_SCR_BUT_CHNG_TIME_TO_TEMP_WIDGETS[APP_GUI_MAXNUM_HP];
extern const uint32 APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[APP_GUI_MAXNUM_HP];
extern const uint32 APP_GUI_TRT_SCR_NUM_VWE_RESUCCTIONS_NUM_WIDGETS [APP_GUI_MAXNUM_HP];
extern const uint32 APP_GUI_TRT_SCR_BUT_TIME_IMG[App_GUI_Max_Time_but_states][App_GUI_widget_Features];
extern const uint32 APP_GUI_TRT_SCR_BUT_PLAY_WIDGETS[APP_GUI_MAXNUM_HP];
extern const uint32 APP_GUI_TRT_SCR_BUT_PLAY_IMG[App_GUI_Max_Play_but_states][App_GUI_widget_Features];
extern const uint32 APP_GUI_TRT_SCR_BUT_TSTVAC_WIDGETS[APP_GUI_MAXNUM_HP];
extern const uint32 APP_GUI_TRT_SCR_BUT_VAC_IMG[HP_CRYO_VAC_LVL_NUM][App_GUI_Max_Vac_but_states][App_GUI_widget_Features];
                                                       
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
extern const uint32 APP_GUI_AVISOS_NOTIFICATIONS_WIDGETS_SCREENS[APP_GUI_NUM_SCREENS];

//extern const uint32 APP_GUI_SAT_ERRORES_NUMVWR_LIST[APP_GUI_SAT_ERRORES_PERIFS];

extern const uint32 APP_GUI_TRT_SCR_POPUP_WIDGET_LIST[APP_GUI_TRT_SCR_NUM_POPUPS];

//extern const tAppGUIfullBodyImagesTableFields APP_GUI_FULL_BODY_IMAGES[APP_GUI_NUM_BODYS];
//extern const tAppGUIfullBodyAreasTableFields APP_GUI_FULL_BODY_AREAS_DATA[APP_GUI_NUM_BODYS][APP_GUI_NUM_FULL_BODY_AREAS];
extern const tAppGUIareaZoomDotsTableFields APP_GUI_AREA_ZOOM_DOTS[APP_GUI_NUM_BODYS][APP_GUI_NUM_FULL_BODY_AREAS][APP_GUI_MAX_DOTS_PER_AREA];

//extern const uint8	APP_GUI_SCREEN_N_LAYERS[APP_GUI_NUM_SCREENS];
//extern const uint32 APP_GUI_INTERFACE_WIDGETS[APP_GUI_NUM_WIDGETS][APP_GUI_WIDGETS_FEATURES];

//extern const uint32 APP_GUI_TRT_LOAD_NEW_HP_CONFIG[APP_GUI_TRT_LOAD_NEW_HP_IMG];

extern const cAppGUItrtAgrupacionZones APP_GUI_TRT_ZONES_GROUP_ASSOCIATION[APP_GUI_NUM_FULL_BODY_AREAS][APP_GUI_MAX_DOTS_PER_AREA];

extern const uint8 APP_GUI_HP_RECOMMENDED_PER_ZONE[HP_CRYO_NUM_HP_MODELS][APP_GUI_NUM_FULL_BODY_AREAS][APP_GUI_MAX_DOTS_PER_AREA];
extern const uint32 APP_GUI_TRT_LIST_OF_IMG_HP_RECOMMENDED_PER_ZONE[HP_CRYO_NUM_HP_MODELS];

//extern const uint32 APP_GUI_LANG_SW_WIDGET_LANG_LIST[App_GUI_Different_Languages];

//extern const uint32 APP_GUI_SAT_NUMVWR_WIDGET_LIST[APP_GUI_SAT_MAX_NUMVWR];

//extern const uint32 APP_GUI_FAT_STATUS_4_HP_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_FAT_STATUS_5_HP_WIDGETS[APP_GUI_MAXNUM_HP];
//extern const uint32 APP_GUI_FAT_VALUE_STATUS[EXP_UC_FATIGUE_MAX_VALUE_STATUS];
//extern const uint32 APP_GUI_FAT_DIFF_NUM_VWR_VALUES[FatMaxValues];
extern tAppGUIPopUpDisplayed APP_GUI_POPUP_DISPLAYED_MAP[APP_GUI_POPUP_DISPLAYED_MAP_NUM];

//extern const uint32 APP_GUI_GPRS_COVERAGE_WID_BY_SCREEN[APP_GUI_NUM_SCREENS]; //V7790

#endif /* APPGUIINTERFACESTRUCTURE_H_ */
