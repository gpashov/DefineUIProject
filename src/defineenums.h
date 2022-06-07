#ifndef DEFINEENUMS_H
#define DEFINEENUMS_H

#include <QObject>
#include <QtQml/qqml.h>

class DefineEnums : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("The class Enums contains only enumerators. Object of this class cannot be created.");
    Q_ENUMS(EWarnings)
    Q_ENUMS(ELanguages)
    Q_ENUMS(ESuctionLevel)
    Q_ENUMS(ETimeSelector)
    Q_ENUMS(EBodyGender)
    Q_ENUMS(ETreatmentZone)
    Q_ENUMS(EBlinkIndicators)
    Q_ENUMS(EAppGUIScreen)
    Q_ENUMS(ECleanUpStatus)
    Q_ENUMS(ETreatmentArea)
public:
    explicit DefineEnums(QObject *parent = nullptr);

//    typedef enum
//    {
//        CheckFilter,
//        CheckSETA,
//        CheckRFID,
//        CheckConnectionHP1,
//        CheckConnectionHP2,
//        CheckConnectionHP3,
//        CheckConnectionHP4,
//        CheckTreatmentHP1,
//        CheckTreatmentHP2,
//        CheckTreatmentHP3,
//        CheckTreatmentHP4,
//        ENDofTreatmentHP,

//        MaxFatigueSteps
//    }cAppGUI_FATIGA_steps;

//    typedef enum
//    {
//        HP1_Page = 1,
//        HP2_Page,
//        HP3_Page,
//        HP4_Page,
//        MachinePage,
//        HP_Commands_Page,
//        MachineDefPage,

//        MaxNumSATpages
//    }cAppGUI_SATscreen_Pages;

//    typedef enum
//    {
//        App_GUI_CfgScr_FW_loading_0,
//        App_GUI_CfgScr_FW_loading_20,
//        App_GUI_CfgScr_FW_loading_40,
//        App_GUI_CfgScr_FW_loading_60,
//        App_GUI_CfgScr_FW_loading_80,
//        App_GUI_CfgScr_FW_loading_100,

//        App_GUI_CfgScr_FW_loading_max
//    }cAppGUIcfgScrLoadingNewFW;

    typedef enum EWarnings
    {
        EWarningWaterLevelLow,
        EWarningWaterLevelMedium,
        EWarningRoomTemperature,
        EWarningRFID,
        EWarningRTC,
        EWarningRearFilter,

        EWarningCount
    } TEWarnings;

    typedef enum ELanguages
    {
        ELanguagesNone,

        ELanguagesFrench,
        ELanguagesSpanishCastilian,
        ELanguagesEnglish,
        ELanguagesItalian,
        ELanguagesGerman,
        ELanguagesPolish,
        ELanguagesRussian,
        ELanguagesPortugues,
        ELanguagesChinese,
        ELanguagesJapanese,
        ELanguagesKorean,

        ELanguagesCount
    } TELanguages;

//    typedef enum
//    {
//        App_GUI_Sin_pais,

//        App_GUI_USA,
//        App_GUI_CHINA,
//        App_GUI_JAPON,
//        App_GUI_ESPANA,
//        App_GUI_GREAT_BRITAIN,
//        App_GUI_IRELAND,
//        App_GUI_NETHERLAND,
//        App_GUI_ALEMANIA,
//        App_GUI_ITALIA,
//        App_GUI_FRANCIA,

//        App_GUI_OTROS,

//        App_GUI_Different_Countries
//    }cApp_GUI_differentCountries;

    typedef enum ESuctionLevel
    {
        ESuctionLevelLow,
        ESuctionLevelMedium,
        ESuctionLevelHigh,
        ESuctionLevelSelector,

        ESuctionLevelCount
    } TESuctionLevel;

    typedef enum ETimeSelector
    {
        ETimeSelector1SelectedTime,
        ETimeSelector2SelectedTime,
        ETimeSelector,

        ETimeSelectorCount
    } TETimeSelector;

//    typedef enum
//    {
//        App_GUI_but_Play,
//        App_GUI_but_Vacc,
//        App_GUI_but_Time,

//        App_GUI_Max_num_but
//    }cAppGUIctrMenuBut;

//    typedef enum
//    {
//        App_GUI_widget_PRS_img,
//        App_GUI_widget_RLS_img,
//        App_GUI_widget_ENABLE,

//        App_GUI_widget_Features
//    }cAppGUIdifferentWidgetFeatures;

//    typedef enum
//    {
//        App_GUI_but_On,
//        App_GUI_but_MarcaAgua,
//        App_GUI_but_max
//    }cAppGUIsmallTSTvacuumButStates;

//    typedef enum
//    {
//        App_GUI_Play_but_Off,
//        App_GUI_Play_but_On,
//        App_GUI_Play_but_TRT_running,
//        App_GUI_Play_but_TRT_cancel,
//        App_GUI_Play_but_disabled,

//        App_GUI_Max_Play_but_states
//    }cAppGUIPlayButStates;

//    typedef enum
//    {
//        App_GUI_Vac_but_Off_Left,
//        App_GUI_Vac_but_Off_Right,
//        App_GUI_Vac_but_On_Left,
//        App_GUI_Vac_but_On_Right,
//        App_GUI_Vac_but_VacAjust_Left,
//        App_GUI_Vac_but_VacAjust_Right,
//        App_GUI_Vac_but_disabled,

//        App_GUI_Max_Vac_but_states
//    }cAppGUIVacButStates;

//    typedef enum
//    {
//        App_GUI_Time_but_Off,
//        App_GUI_Time_but_On,
//        App_GUI_Time_but_disabled,

//        App_GUI_Max_Time_but_states
//    }cAppGUITimeButStates;

//    typedef enum		//Codigos de calculadora
//    {
//        AppGUIcalc_NOT_USED,

//        AppGUIcalc_RTC_time,	/*1*/
//        AppGUIcalc_RTC_date,	/*2*/
//        AppGUIcalc_Vaciado,		/*3 - No se usa*/
//        AppGUIcalc_Llenado,		/*4*/
//        AppGUIcalc_SATscreen,	/*5*/
//        AppGUIcalc_FATIGAscreen,/*6*/

//        AppGUIcalc_ProgCurved 		= 11,
//        AppGUIcalc_ProgTight 		= 12,
//        AppGUIcalc_ProgStright 		= 13,
//        AppGUIcalc_ProgTiny 		= 14,
//        AppGUIcalc_ProgTinyCurved 	= 15,
//        AppGUIcalc_ProgDouble 		= 16,
//        AppGUIcalc_ProgOval 		= 17,
//        AppGUIcalc_ProgOvalCurved 	= 18,
//        AppGUIcalc_ProgAngled 		= 19,

//        AppGUIcalc_OscTempIDLEenable	= 35,
//        AppGUIcalc_OscTempIDLEdisable	= 36,

//        AppGUIcalc_ReuseLabelEnable		= 40,
//        AppGUIcalc_ReuseLabelDisable	= 41,

//        AppGUIcalc_TempSlopeEnable		=43,
//        AppGUIcalc_TempSlopeDisable		=44,

//        AppGUIcalc_TempSecureEnable		=46,
//        AppGUIcalc_TempSecureDisable	=47,

//        AppGUIcalc_ErrSecureEnable		=49,
//        AppGUIcalc_ErrSecureDisable		=50,

//        AppGUIcalc_ErrSecureDeltaTempEnable = 52,
//        AppGUIcalc_ErrSecureDeltaTempDisable = 53,

//    //	AppGUIcalc_LangSelectionEnable = 55,
//    //	AppGUIcalc_LangSelectionDisable = 56,


//        AppGUIcalc_EraseLOG = 58,
//        AppGUIcalc_SendASCII_LOG = 60,
//        AppGUIcalc_Send_USB_ASCII_LOG = 62,
//        AppGUIcalc_SendRAW_LOG = 64,
//        AppGUIcalc_Send_USB_RAW_LOG = 66,
//        AppGUIcalc_SendRecent_LOG = 68,
//        AppGUIcalc_Send_USB_Recent_LOG = 70,

//        AppGUIcalc_RecordLOG_enable = 72,
//        AppGUIcalc_RecordLOG_disable = 74,

//        AppGUIcalc_GPRS_Del_country = 98, //#JM_GPRS V7790 Borrar los paises pero conservar que la maquina tiene placa
//        AppGUIcalc_GPRS_Clear = 99, //#JM_GPRS V7790
//        APPGUIcalc_MAX_NUM_CODES
//    }cAppGUIcalcCodes;

    typedef enum EBodyGender
    {
        TEBodyGenderMale,
        TEBodyGenderFemale,
        TEBodyGenderCount
    } TEBodyGender;

    typedef enum ETreatmentZone
    {
        TETreatmentZoneNone,
        TETreatmentZoneTorso,
        TETreatmentZoneLegs,
        TETreatmentZoneBack,
        TETreatmentZoneThighs,
        TETreatmentZoneArms,
        TETreatmentZoneNeck,
        TETreatmentZoneCount
    } TETreatmentZone;

//    typedef enum
//    {
//        AppGUIoff,
//        AppGUIon,
//        APP_GUI_MAX_ON_OFF
//    }cAppGUIonOff;

//    typedef enum
//    {
//        AppGUItstVacNotDone,
//        AppGUItstVacDone,
//        APP_GUI_MAX_TST_VAC_DONE
//    }cAppGUItstVacDone;

    typedef enum EBlinkIndicators
    {
        TEBlinkIndicatorsRFID,
        TEBlinkIndicatorsButton,
        TEBlinkIndicatorsVac,
        TEBlinkIndicatorsCooling,
        TEBlinkIndicatorsCount
    } TEBlinkIndicators;

//    // Número de capas.
//    typedef enum
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

    typedef enum EAppGUIScreen
    {
        TEAppGUIScreenLoad,
        TEAppGUIScreenInit,
        TEAppGUIScreenTreatment,
        TEAppGUIScreenCodes,
        TEAppGUIScreenConfiguration,
        TEAppGUIScreenLanguages,
        TEAppGUIScreenSat,
        TEAppGUIScreenFatigue,
        TEAppGUIScreenCount
    } TEAppGUIScreen;

    typedef enum ECleanUpStatus
    {
        TECleanUpStatusCountdown,
        TECleanUpStatusWaitUser,
        TECleanUpStatusCleaning,
        TECleanUpStatusWaitVacuum,
        TECleanUpStatusCount
    } TECleanUpStatus;

    // Treatment areas in the zones
    typedef enum ETreatmentArea
    {
        TETreatmentAreaNone, // NO_ZONA,

        // Torso
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

        // Legs
        TrocantereaIzquierdo,
        TrocantereaDerecho,
        CaraInternaMusloIzquierdo,
        CaraInternaMusloDerecho,
        SuperioRodillaIzquierda,
        SuperiorRodillaDerecha,
        IntRodillaIzquierda,
        IntRodillaDerecha,

        // Arms
        BrazoIzquierdo,
        BrazoDerecho,

        // Back
        SupraescapularIzquierda,
        SupraescapularDerecha,
        InfraescapularIzquierda,
        InfraescapularDerecha,
        FlancoIzquierdo,
        FlancoDerecho,

        // Thighs
        GluteoIzquierdo,
        GluteoDerecho,
        SubgluteoIzquierdo,
        SubgluteoDerecho,
        MusloPosteriorIzquierdo,
        MusloPosterioDerecho,

        // Neck
        PapadaCentral,
        PapadaLateralIzquierdo,
        PapadaLateralDerecho,

        MaxZonas, // Zonas de aplicación tratamiento. La primera zona no se utiliza

        ZonaInit,

    } TETreatmentArea;

//    typedef enum
//    {
//        NoGrupo,

//        PliegueAxilar,
//        Senos,
//        Intrapectoral,
//        AbdominalSupraumbrical,
//        AbdominalInfraumbrical,
//        Cadera,

//        Trocantereal,
//        CaraInternaMuslo,
//        SuperiorRodilla,
//        InteriorRodilla,

//        Brazo,

//        Supraescapular,
//        Infraescapular,
//        Flanco,

//        Gluteo,
//        Subgluteo,
//        MusloPosterior,

//        Papada,

//        MaxGrupoZonas

//    }cAppGUItrtAgrupacionZones;

signals:

};

#endif // DEFINEENUMS_H
