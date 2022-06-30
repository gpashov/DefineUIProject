/*Librerías*/
#include "GeneralDefines.h"
#include "AppGUI.h"
#include "../AppGUI/AppGuiInterfaceStructure.h"
#include "UIWrapperClasses/widgetswrapper.h"
//#include "K70_GUI.h"
#include "../Perifericos/HPcryo.h"
#include "../Ticks/Ticks.h"
#include "../Error/gestionError.h"
//#include "../Buzzer/Buzzer.h"
#include "App.h"
//#include "HAL_UART_2.h"
#include "../UART/UART.h"
#include "../AppLOG/AppLOG.h"
#include "../GPRS/AppGPRS.h"

/* Constantes */
 typedef enum
{
	APP_GUI_FLG_OFF,
	APP_GUI_FLG_FIX,
	APP_GUI_FLG_BLINK
}cAppGUIstatusFlagshdlr;

const cHPcryoLEDcolors APP_GUI_LED_COLOR_FROM_SLOT[APP_GUI_MAXNUM_HP] =
{
	HP_CRYO_CTLLED_COLOR_LIMON,				//APP_GUI_HP1_ID
	HP_CRYO_CTLLED_COLOR_CELESTE,			//APP_GUI_HP2_ID
	HP_CRYO_CTLLED_COLOR_NARANJA,			//APP_GUI_HP3_ID
	HP_CRYO_CTLLED_COLOR_LILA				//APP_GUI_HP4_ID
};

/* Variables Globales */
tAppGUIdata AppGUIdata;
extern WidgetsWrapper wdgWpr;

/* Definción Funciones Locales */
void AppGUIloadScrInit( void);
void AppGUIinitScrInit( void);
void AppGUItrtScrInit( void);
void AppGUIcfgScrInit( void);
void AppGUIcalcScrInit( void);
void AppGUIdataScrInit( void);
void AppGUIfat0ScrInit( void);
void AppGUIsatScrInit( void);

void AppGUIloadScrUpdate( void);
void AppGUIinitScrUpdate( void);
void AppGUItrtScrUpdate( void);
void AppGUIcfgScrUpdate( void);
void AppGUIcalcScrUpdate( void);
void AppGUIdataScrUpdate( void);
void AppGUIfat0ScrUpdate( void);
void AppGUIsatScrUpdate( void);

void AppGUIsetHPstatusFlags( cAppGUIstatusFlagshdlr RFID, cAppGUIstatusFlagshdlr button,
                             cAppGUIstatusFlagshdlr vacum, cAppGUIstatusFlagshdlr cooling,
                             uint8 HPindex);

uint8 AppGUIisPopUpActive( void);
uint8 AppGUIisRecommPopUpActive (void);
uint8 AppGUIisTimePopUpActive (void);
uint8 AppGUIisVacPopUpActive (void);
uint8 AppGUIisVacSmallPopUpActive (void);
uint8 AppGUIisCleanUpPopUpActive( uint8 HPindex);
uint8 AppGUIisErrorPopUpActive( uint8 HPindex);
uint8 AppGUIisWarningPopUpActive (void);

void AppGUIpanelCtrlColourBlink(void);
float AppGUIsecondsToClock( uint32 seconds);
void AppGUIupdateWarningFlags(void);

uint8 ptu8DataAPPGui[32];

/* Funciones Publicas */
void AppGUIinit()
{
    //Declaracion de variables locales de la función
    uint8 i=0;
	
    //Inicialización de variables
    AppGUIdata.screen = APP_GUI_LOAD_SCREEN;
    AppGUIdata.trtZoneHdlr.body = AppGUIbodyFemale;
    AppGUIclearData();
    for( i = 0; i < APP_GUI_MAXNUM_HP; i++)
    {
        AppGUIdata.slot[i].isCtrlPnlShow = 1;
        AppGUIclearSlotData( i);
    }
    AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Nivel_Agua_Bajo = 0;
    AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Nivel_Agua_Medio = 0;
    AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Temp_Amb = 0;
    AppGUIdata.AppGUI_WarningHandler.Flag_Wng_RFID = 0;
    AppGUIdata.AppGUI_WarningHandler.Flag_Wng_RTC = 0;
    AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Filtro_Aire = 0;
	
    //Inicializamos y configuramos la libreria GUI
//    GUIinit( APP_GUI_IMG_COMPRESION_CCN,srcCCN,srcLUT,APP_GUI_BOTTOM_REF,
//             APP_GUI_BOTTOM_COLOR_REF,APP_GUI_BRIGHT_INIT ,DDRdata);
//    GUIconfigInterface(APP_GUI_INTERFACE_WIDGETS, (uint8)APP_GUI_NUM_SCREENS, (uint32)APP_GUI_NUM_WIDGETS, (uint8*)APP_GUI_SCREEN_N_LAYERS);
	
    //Configuramos las listas de widgets a usar por los PopUps
//    GUIsetPopUpWidgets(PopUpTime, APP_GUI_POPUP_TIME_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopUpTstVac, APP_GUI_POPUP_TST_VAC_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopUpRFID, APP_GUI_POPUP_RFID_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopUpRecomm, APP_GUI_POPUP_RECOMMENDATION_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopUpTstVacSmall, APP_GUI_POPUP_TST_VAC_SMALL_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopupInitScrAvisos, APP_GUI_POPUP_AVISOS_INIT_SCRN_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopupTrtScrAvisos, APP_GUI_POPUP_AVISOS_TRT_SCRN_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopupCalcScrAvisos, APP_GUI_POPUP_AVISOS_CALC_SCRN_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopupCfgScrAvisos, APP_GUI_POPUP_AVISOS_CFG_SCRN_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopupLanScrAvisos, APP_GUI_POPUP_AVISOS_LAN_SCRN_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopupErrorSAT, APP_GUI_POPUP_ERRORES_SAT_WIDGET_LIST, NULL);
	
    /* Finalmente pasamos a la pantalla de LOAD */
    AppGUIchangeScreen( APP_GUI_LOAD_SCREEN);
}

void AppGUIinit_reconfig (void)
{
    //Declaracion de variables locales de la función
    uint8 i=0;
	
    //Inicialización de variables
    AppGUIdata.screen = APP_GUI_LOAD_SCREEN;
    AppGUIdata.trtZoneHdlr.body = AppGUIbodyFemale;
    AppGUIclearData();
    for( i = 0; i < APP_GUI_MAXNUM_HP; i++)
    {
        AppGUIdata.slot[i].isCtrlPnlShow = 1;
        AppGUIclearSlotData( i);
    }
    AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Nivel_Agua_Bajo = 0;
    AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Nivel_Agua_Medio = 0;
    AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Temp_Amb = 0;
    AppGUIdata.AppGUI_WarningHandler.Flag_Wng_RFID = 0;
    AppGUIdata.AppGUI_WarningHandler.Flag_Wng_RTC = 0;
    AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Filtro_Aire = 0;
	
    //Configuramos las listas de widgets a usar por los PopUps
//    GUIsetPopUpWidgets(PopUpTime, APP_GUI_POPUP_TIME_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopUpTstVac, APP_GUI_POPUP_TST_VAC_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopUpRFID, APP_GUI_POPUP_RFID_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopUpRecomm, APP_GUI_POPUP_RECOMMENDATION_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopUpTstVacSmall, APP_GUI_POPUP_TST_VAC_SMALL_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopupInitScrAvisos, APP_GUI_POPUP_AVISOS_INIT_SCRN_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopupTrtScrAvisos, APP_GUI_POPUP_AVISOS_TRT_SCRN_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopupCalcScrAvisos, APP_GUI_POPUP_AVISOS_CALC_SCRN_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopupCfgScrAvisos, APP_GUI_POPUP_AVISOS_CFG_SCRN_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopupLanScrAvisos, APP_GUI_POPUP_AVISOS_LAN_SCRN_WIDGET_LIST, NULL);
//    GUIsetPopUpWidgets(PopupErrorSAT, APP_GUI_POPUP_ERRORES_SAT_WIDGET_LIST, NULL);
	
//    for(i=0;i<APP_GUI_TRT_SCR_NUM_POPUPS;i++){	GUIdisablePopUp( APP_GUI_TRT_SCR_POPUP_WIDGET_LIST[i]);	}
	
    /* Finalmente pasamos a la pantalla de LOAD */
    AppGUIchangeScreen( APP_GUI_LOAD_SCREEN);
}

void AppGUIfinish()
{
//    GUIfinish(DDRdata);
}

void AppGUIchangeScreen( cAppGUIscreen screen)
{
    /* Cerrar electrovalvula*/
    if ((AppGUIdata.screen == APP_GUI_CALCULATOR_SCREEN) || (AppGUIdata.screen == APP_GUI_CONFIGURATION_SCREEN)){ EXP_UChandleVentEV( 0);}
	
    /* LOG modos de funcionamiento - V7790 */
    if((AppGUIdata.screen == APP_GUI_CALCULATOR_SCREEN) && (AppGUIdata.CalcHandler.MachineModeChngFlag == 1))
    {
        AppLOG_saveModes();		/* V7790 - LOG modes */
    }
	
    sprintf((char *)ptu8DataAPPGui, "*************** New Screen\r\n");
    UART_Transmit(INDEX_UART_2, ptu8DataAPPGui, strlen((char *)ptu8DataAPPGui));
    while(UART_TransmitNOTFinished(INDEX_UART_2));
	
    /* Pasamos a la pantalla indicada */
    switch( screen)
    {
        case APP_GUI_LOAD_SCREEN:
//			sprintf((char *)ptu8DataAPPGui, "APP_GUI_LOAD_SCREEN!!! ****************\r\n");
//			UART_Transmit(INDEX_UART_2, ptu8DataAPPGui, strlen((char *)ptu8DataAPPGui));
//			while(UART_TransmitNOTFinished(INDEX_UART_2));
            AppGUIloadScrInit();
            break;
        case APP_GUI_INIT_SCREEN:
//			sprintf((char *)ptu8DataAPPGui, "APP_GUI_INIT_SCREEN!!! ****************\r\n");
//			UART_Transmit(INDEX_UART_2, ptu8DataAPPGui, strlen((char *)ptu8DataAPPGui));
//			while(UART_TransmitNOTFinished(INDEX_UART_2));
            AppGUIinitScrInit();
            break;
        case APP_GUI_TREATMENT_SCREEN:
//			sprintf((char *)ptu8DataAPPGui, "APP_GUI_TREATMENT_SCREEN!!! ****************\r\n");
//			UART_Transmit(INDEX_UART_2, ptu8DataAPPGui, strlen((char *)ptu8DataAPPGui));
//			while(UART_TransmitNOTFinished(INDEX_UART_2));
            AppGUItrtScrInit();
            break;
        case APP_GUI_CALCULATOR_SCREEN:
//			sprintf((char *)ptu8DataAPPGui, "APP_GUI_CALCULATOR_SCREEN!!! ****************\r\n");
//			UART_Transmit(INDEX_UART_2, ptu8DataAPPGui, strlen((char *)ptu8DataAPPGui));
//			while(UART_TransmitNOTFinished(INDEX_UART_2));
            AppGUIcalcScrInit();
            break;
        case APP_GUI_CONFIGURATION_SCREEN:
//			sprintf((char *)ptu8DataAPPGui, "APP_GUI_CONFIGURATION_SCREEN!!! ****************\r\n");
//			UART_Transmit(INDEX_UART_2, ptu8DataAPPGui, strlen((char *)ptu8DataAPPGui));
//			while(UART_TransmitNOTFinished(INDEX_UART_2));
            AppGUIcfgScrInit();
            break;
        case APP_GUI_LANGUAGES_SCREEN:
//			sprintf((char *)ptu8DataAPPGui, "APP_GUI_LANGUAGES_SCREEN!!! ****************\r\n");
//			UART_Transmit(INDEX_UART_2, ptu8DataAPPGui, strlen((char *)ptu8DataAPPGui));
//			while(UART_TransmitNOTFinished(INDEX_UART_2));
            AppGUIdataScrInit();
            break;
        case APP_GUI_SAT_SCREEN:
//			sprintf((char *)ptu8DataAPPGui, "APP_GUI_SAT_SCREEN!!! ****************\r\n");
//			UART_Transmit(INDEX_UART_2, ptu8DataAPPGui, strlen((char *)ptu8DataAPPGui));
//			while(UART_TransmitNOTFinished(INDEX_UART_2));
            AppGUIsatScrInit();
            break;
        case APP_GUI_FATIGUE_SCREEN:
//			sprintf((char *)ptu8DataAPPGui, "APP_GUI_FATIGUE_SCREEN!!! ****************\r\n");
//			UART_Transmit(INDEX_UART_2, ptu8DataAPPGui, strlen((char *)ptu8DataAPPGui));
//			while(UART_TransmitNOTFinished(INDEX_UART_2));
            AppGUIfat0ScrInit();
            break;
        default: break;
    }

    /* Guardamos la pantalla actual */
    AppGUIdata.screen = screen;
}

void AppGUIupdate(void)
{
    //uint32 time_update;
    //uint32 time_refresh;
    //uint32 time_ref1;
    //uint32 time_ref2;
    /* Update de la pantalla activa */
    switch (AppGUIdata.screen)
    {
        case APP_GUI_LOAD_SCREEN: AppGUIloadScrUpdate(); break;
        case APP_GUI_INIT_SCREEN: AppGUIinitScrUpdate(); break;
        case APP_GUI_TREATMENT_SCREEN: AppGUItrtScrUpdate(); break;
        case APP_GUI_CALCULATOR_SCREEN: AppGUIcalcScrUpdate(); break;
        case APP_GUI_CONFIGURATION_SCREEN: AppGUIcfgScrUpdate(); break;
        case APP_GUI_LANGUAGES_SCREEN: AppGUIdataScrUpdate(); break;
        case APP_GUI_SAT_SCREEN: AppGUIsatScrUpdate(); break;
        case APP_GUI_FATIGUE_SCREEN: AppGUIfat0ScrUpdate(); break;
        default: break;
    }
	
    /* Actualizamos el status de cobertura del GPRS. Es un widget usado en
        casi todas las pantallas */ //V7790
    AppGUI_GPRScoverage( appGPRS_get_signal() == 0, AppGUIdata.screen);
	
//    //time_ref1 = TICKS_GetTicks();					//DEBUG
//    /* Update la librería GUI */
//    GUIupdate();
//    //time_update = TICKS_DiffTicks(time_ref1);		//DEBUG
	
//    //time_ref2 = TICKS_GetTicks();					//DEBUG
//    /* Refresco grafico de la librería GUI */
//    GUIrefresh(0);
//    //time_refresh = TICKS_DiffTicks(time_ref2);		//DEBUG
}

/* Funciones publicas para los CBK's */
void AppGUIhandleCtrlPanel( uint8 show, uint8 HPindex)
{
    uint8 i;
    uint8 HPconnected;
    uint8 isPopUp, isTrtRunning;
    //uint8 isRecommPopUp, isRFIDPopUp, isTimePopUp, isVaccSmallPopUp;
    uint32 imgPrsID, imgRlsID, imgModelText;
    cAppGUIPlayButStates butPlayStatus;
    cAppGUIVacButStates butVaccStatus;
    cAppGUITimeButStates butTimeStatus;
    cHPcryoModels model;
    tHPcryoData *HP;
    tPRFdata *PRF;

    /* Obtenemos si hay algún popUp activo para condicionar las habilitaciones pero no
     * las visibilidades. La parte gráfica no se ve afectada */
    isPopUp = ( AppGUIisPopUpActive() ||
                AppGUIisCleanUpPopUpActive( HPindex) ||
                AppGUIisErrorPopUpActive( HPindex));
    //isRecommPopUp = AppGUIisRecommPopUpActive();
    AppGUIisRecommPopUpActive();
    //isTimePopUp = AppGUIisTimePopUpActive();
    AppGUIisTimePopUpActive();
    //isVaccSmallPopUp = AppGUIisVacSmallPopUpActive();
    AppGUIisVacSmallPopUpActive();
    //isRFIDPopUp = AppGUIisRFIDPopUpActive();
    AppGUIisRFIDPopUpActive();
	
    if (HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
    {
        if (AppGUIisHPaDoubleDummy( HP, PRF))
        {
            AppGUIdata.slot[HPindex].isCtrlPnlShow = 0;
            show = 0;
        }
    }
	
    /* Gestion widgets panel de control cuando desplegado */
    for( i = 0; i < APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_SHOW_NUM; i++)
    {
//        GUIsetWidgetVisibility( APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_SHOW[HPindex][i], ( show != 0));
// TODO        GUIsetWidgetEnable( APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_SHOW[HPindex][i], ( show != 0) && !isPopUp);
    }
		
    /* Gestion widgets panel de control cuando oculto */
    for( i = 0; i < APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_HIDE_NUM; i++)
    {
//        GUIsetWidgetVisibility( APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_HIDE[HPindex][i], ( show == 0));
// TODO        GUIsetWidgetEnable( APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_HIDE[HPindex][i], ( show == 0) && !isPopUp);
    }
	
    if (HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
    {
// TODO        if (AppGUIisHPaDoubleDummy( HP, PRF)){	GUIsetWidgetEnable( butShowControlPanelHP1 + HPindex, 0);}
    }
	
    /* Si toca mostrar gestionamos según el estado de diversas variables, si toca ocultar ya esta todo
     * OK con lo anterior */
    if( show)
    {
        /* Obtenemos si el HP esta en tratamiento */
        isTrtRunning = AppGUIisTrtRunning( HPindex, NULL);
		
        /* Gestión del botón con la imagen del HP para ejecutar el vinculo a la zona de trt y
         * el visot de modelo de HP en texto */
        HPconnected = AppGUIisHPconnected( HPindex, &model);
        if( HPconnected)
        {
            if (AppGUIisInitRunning(HPindex)){ AppGUIconnectingHP (HPindex, &imgPrsID, &imgRlsID, &imgModelText);}
            else
            {
                /* Cuando hay HP conectado mostramos la imagen de éste en press y release o bien mostramos
                 * la imagen de modo AutoKO o bien mostramos la imagen de recolocar HP por resucciones */
                if( AppGUIdata.slot[HPindex].showVacumRetryRqstUsrToMoveHP)
                {
                    if(AppGUIdata.slot[HPindex].alarmVacumRetryRqstUsrToMoveHP == 0)	//Si se ha recomendado una recolocación y no se ha lanzado la alarma
                    {
                        BUZZ_Configure(1, 100, PATRO_SO_FINAL_TRT );	//V7750 - Lanzamos la alarma sonora
                        AppGUIdata.slot[HPindex].alarmVacumRetryRqstUsrToMoveHP = 1;	//Indicamos que la alarma ya ha sonado
                    }
                    imgPrsID = C430_HPalarmaResucciones;
//                    imgRlsID = c430_HPalarmaResucciones;
					
                }
                else if( AppGUIdata.slot[HPindex].showAutoKO)
                {
                    imgPrsID = C438_HPalarmaPlicainsuficiente;
//                    imgRlsID = c438_HPalarmaPlicainsuficiente;
                }
                else
                {
                    imgPrsID = APP_GUI_TRT_SCR_BUT_MODEL_IMG_SIDE_FROM_SLOT_IMG[AppGUIprs][HPindex][model];
//                    imgRlsID = APP_GUI_TRT_SCR_BUT_MODEL_IMG_SIDE_FROM_SLOT_IMG[AppGUIrls][HPindex][model];
                }
				
                /* Habilitamos y obtenemos la imagen del texto del modelo*/
                wdgWpr.GUIsetWidgetEnable(	APP_GUI_TRT_SCR_BUT_MODEL_IMG_WIDGETS[HPindex],
                                    (!AppGUIisHPaDoubleDummy( HP, PRF) && (!isPopUp) &&
                                    (AppGUIdata.trtZoneHdlr.selTrtArea != AppGUIfullBodyNO_AREA) &&
                                    (AppGUIdata.trtZoneHdlr.selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED) &&
                                    !isTrtRunning));
                imgModelText = APP_GUI_TRT_SCR_HP_MODEL_TEXT_IMG[HPindex][model];
            }
			
            //Habilitamos el boton de auto/manual
//            GUIsetWidgetEnable( APP_GUI_TRT_SCR_BUT_MODE_TRT_WIDGETS[HPindex], (HPcryoIsAutoModeAvaible(HP, PRF) && !isTrtRunning && (!isPopUp)));
        }
        else
        {
            /* Si no hay HP conectado mostramos la imagen del conector en press y release, deshabilitamos y
             * ponemos la imagen transparente para el texto del modelo */
            imgPrsID = APP_GUI_TRT_SCR_BUT_MODE_IMG_NO_HP_IMG[HPindex];
//            imgRlsID = APP_GUI_TRT_SCR_BUT_MODE_IMG_NO_HP_IMG[HPindex];
// TODO            GUIsetWidgetEnable( APP_GUI_TRT_SCR_BUT_MODEL_IMG_WIDGETS[HPindex], 0);
            imgModelText = C233_ImgPixelBlanco;
// TODO            GUIsetWidgetEnable( APP_GUI_TRT_SCR_BUT_MODE_TRT_WIDGETS[HPindex], 0);
        }
		
        /* - Ponemos las imagenes del boton */
        wdgWpr.GUIsetHpControlPanelImgButton( APP_GUI_TRT_SCR_BUT_MODEL_IMG_WIDGETS[HPindex], (EAppGUIimageIDlist)imgPrsID);
		
        /* - Ponemos el modelo de manípulo en texto */
        wdgWpr.GUIsetImgViewerImage( APP_GUI_TRT_SCR_HP_MODEL_TEXT_WIDGETS[HPindex], imgModelText);
				
        /* Gestion grafica del switch modo AUTO/MANUAL */
#ifdef APP_SW_VER_AUTO_ENABLE
        if (AppGUIdata.slot[HPindex].TrtMode == HP_CRYO_TRT_MODE_MANUAL)
        {
            GUIsetImgButton( APP_GUI_TRT_SCR_BUT_MODE_TRT_WIDGETS[HPindex], c045_BotonAutoRls, 1);
            GUIsetImgButton( APP_GUI_TRT_SCR_BUT_MODE_TRT_WIDGETS[HPindex], c045_BotonAutoRls, 0);
        }
        else if (AppGUIdata.slot[HPindex].TrtMode == HP_CRYO_TRT_MODE_AUTO)
        {
            GUIsetImgButton( APP_GUI_TRT_SCR_BUT_MODE_TRT_WIDGETS[HPindex], c044_BotonAutoPress, 1);
            GUIsetImgButton( APP_GUI_TRT_SCR_BUT_MODE_TRT_WIDGETS[HPindex], c044_BotonAutoPress, 0);
        }
#else
// TODO        GUIsetWidgetEnable( APP_GUI_TRT_SCR_BUT_MODE_TRT_WIDGETS[HPindex], 0);
//        GUIsetWidgetVisibility( APP_GUI_TRT_SCR_BUT_MODE_TRT_WIDGETS[HPindex], 0);
#endif
		
        /* Gestión del visor de tiempo y el boton de selección de tiempo */
        //selected = ( AppGUIdata.slot[HPindex].selTime != APP_GUI_NO_TIME_SELECTED);
        wdgWpr.GUIsetWidgetVisibility( APP_GUI_TRT_SCR_BUT_SEL_TIME_WIDGETS[HPindex], !HPconnected || AppGUIisInitRunning(HPindex) ||(AppGUIdata.slot[HPindex].selTrtArea == APP_GUI_NUM_FULL_BODY_AREAS) || (AppGUIdata.slot[HPindex].selTrtDot == APP_GUI_NO_TRT_DOT_SELECTED));
        wdgWpr.GUIsetWidgetVisibility( APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex], HPconnected && !AppGUIisInitRunning(HPindex) && (AppGUIdata.slot[HPindex].selTrtArea != APP_GUI_NUM_FULL_BODY_AREAS) && (AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED));
//        GUIsetWidgetEnable( APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex], HPconnected  && !isPopUp && !AppGUIisHPaDoubleDummy( HP, PRF));
		
        if (( !AppGUIisInitRunning(HPindex) && HPconnected && !isTrtRunning && (AppGUIdata.slot[HPindex].selTrtArea != APP_GUI_NUM_FULL_BODY_AREAS) && (AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED)))
        {
            AppGUIapplyTimeRestriction( HPindex, HP, PRF);
            AppGUIdata.slot[HPindex].trtTime = AppGUIsecondsToClock( HP_CRYO_TIME_LIST[AppGUIdata.slot[HPindex].selTime]);
        }
		
        if (isTrtRunning)
        {
//            GUIsetWidthNumVwr(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex],108);					//Al iniciarse el tratamiento, ya no se podrá seleccionar el tiempo, así que se quita la flecha y se centran los digitos
//            GUIsetImgNumVwr(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex],c047_FondoNumVwrBlanco);
            wdgWpr.GUISetTreatmentTimerBackground((EAppGUI_HPsIDs)HPindex, true);
			
            /*Al iniciar el tratamiento mostramos el visor de la cuenta de las resucciones*/
            wdgWpr.GUIsetWidgetVisibility(APP_GUI_TRT_SCR_NUM_VWE_RESUCCTIONS_NUM_WIDGETS[HPindex], HPcryoGetTRTplusThree(HP, PRF));
            if(AppGUIdata.slot[HPindex].trtTime != 0){	wdgWpr.GUIsetNumViewerNum(APP_GUI_TRT_SCR_NUM_VWE_RESUCCTIONS_NUM_WIDGETS[HPindex], AppGUIsecondsToClock(HPcryoGetTRTplusThreeTime(HP, PRF)/1000), 0);	}	//V7776
        }
        else
        {	wdgWpr.GUIsetWidgetVisibility(APP_GUI_TRT_SCR_NUM_VWE_RESUCCTIONS_NUM_WIDGETS[HPindex], 0);	}
		
        if(AppGUIdata.slot[HPindex].VwrTemperatureOrTime == 0)
        {
            //GUIsetWidthNumVwr(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex],118);
            wdgWpr.GUIsetNumViewerNum(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex], AppGUIdata.slot[HPindex].trtTime, 2);
        }
        else
        {
            //GUIsetWidthNumVwr(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex],108);
            wdgWpr.GUIsetNumViewerNum(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex], AppGUIdata.slot[HPindex].TempHP, 1);
        }
		
        /* Gestión de los flags indicadores */
        for( i = 0; i < APP_GUI_MAX_BLINK_INDICATORS; i++)
        {
            wdgWpr.GUIsetWidgetVisibility( APP_GUI_TRT_SCR_BLINK_INDICATORS_WIDGETS[HPindex][i],
                                    AppGUIdata.slot[HPindex].statusFlagsOnOff[i]);
        }
		
		
        /* - Gestión del boton de test de vacum , el boton de play y el de time - */
        butPlayStatus = App_GUI_Play_but_Off;
        butVaccStatus = App_GUI_Vac_but_Off;
        butTimeStatus = App_GUI_Time_but_Off;
		
        // Si ya hay asignado al manipulo una zona de tratamiento
        if( AppGUIdata.slot[HPindex].selTrtArea != APP_GUI_NUM_FULL_BODY_AREAS &&
            AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED)
        {
            butTimeStatus = App_GUI_Time_but_On;
            butVaccStatus = App_GUI_Vac_but_On;
        }
        // Si ya tiene el tiempo seleccionado
        if ( AppGUIdata.slot[HPindex].selTime != APP_GUI_NO_TIME_SELECTED)
        {
            butPlayStatus = App_GUI_Play_but_On;
        }
		
        if ((AppGUIdata.slot[HPindex].TrtMode == HP_CRYO_TRT_MODE_AUTO) && (AppGUIdata.slot[HPindex].TstVacuumModeScss != HP_CRYO_TEST_VACUUM_AUTO_DONE_SUCCESS))
        {
            butPlayStatus = App_GUI_Play_but_Off;
        }
        // Si se está inicializando el HP
        // o si no está conectado el HP
        // o si no hay ningún area seleccionada
        // o si no hay ningún punto seleccionado
        if ( AppGUIisInitRunning(HPindex) || !AppGUIisHPconnected( HPindex, &model) ||
            AppGUIdata.slot[HPindex].selTrtArea == APP_GUI_NUM_FULL_BODY_AREAS || AppGUIdata.slot[HPindex].selTrtDot == APP_GUI_NO_TRT_DOT_SELECTED)
        {
            butPlayStatus = App_GUI_Play_but_Off;
            butVaccStatus = App_GUI_Vac_but_Off;
            butTimeStatus = App_GUI_Time_but_Off;
        }
        // Si hay un tratamiento en curso
        if ( isTrtRunning)
        {
            /*if (!isRFIDPopUp && !isVaccSmallPopUp)*/	butPlayStatus = App_GUI_Play_but_TRT_running;
            butVaccStatus = App_GUI_Vac_but_Off;
            butTimeStatus = App_GUI_Time_but_Off;
        }
        // Si en tratamiento se puede reintentar el vacuum
        if (( isTrtRunning) && ( HPcryoTrtVacumRetryAvailable( HP, PRF))/* && !isRFIDPopUp && !isVaccSmallPopUp*/)
        {
            butPlayStatus = App_GUI_Play_but_TRT_cancel;
        }
        // Si en tratamiento se puede reajustar el vacuum
        if (( isTrtRunning) && (HPcryoTrtAdjustVacumAvailable( HP, PRF))/* && !isVaccSmallPopUp && !isRFIDPopUp*/)
        {
            butVaccStatus = App_GUI_Vac_but_VacAjust;
        }
        //Si no tiene permitida la selección de tiempo
        if (HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
        {
            if (!AppGUIopenTimePopupPermission(HPindex, HP, PRF)){	butTimeStatus = App_GUI_Time_but_Off;	}
        }
        // Si hay algún PopUp activado
        if ( isPopUp)
        {
            butPlayStatus = App_GUI_Play_but_disabled;
            butVaccStatus = App_GUI_Vac_but_disabled;
            butTimeStatus = App_GUI_Time_but_disabled;
        }
        // Si el popup de vacuum está activo
        // y es del propio HP
        if (AppGUIdata.tstVacHdlr.HPindex == HPindex)
        {
            if (AppGUIisVacSmallPopUpActive())
            {
                butVaccStatus = App_GUI_Vac_but_VacAjust;
            }
            else if (AppGUIisVacPopUpActive())
            {
                butVaccStatus = App_GUI_Vac_but_On;
            }
        }
        // Si el popup de tiempo está activo
        // y es del propio HP
        if ((AppGUIisTimePopUpActive()) && AppGUIdata.timeHdlr.HPindex == HPindex)
        {
            butTimeStatus = App_GUI_Time_but_On;
        }
        // Si hay manipulo conectado y es un Double Dummy
        if (HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
        {
            if (AppGUIisHPaDoubleDummy( HP, PRF))
            {
                butPlayStatus = App_GUI_Play_but_Off;
                butVaccStatus = App_GUI_Vac_but_Off;
                butTimeStatus = App_GUI_Time_but_Off;
            }
        }
		
        /* - Ponemos la imagen de los botones correspondientes */
        AppGUIbuttonManagement (App_GUI_but_Play, butPlayStatus, HPindex);
        AppGUIbuttonManagement (App_GUI_but_Vacc, butVaccStatus, HPindex);
        AppGUIbuttonManagement (App_GUI_but_Time, butTimeStatus, HPindex);
#ifdef APP_SW_VER_SHOW_TEMPERATURES
        wdgWpr.GUIsetWidgetEnable ( APP_GUI_TRT_SCR_BUT_CHNG_TIME_TO_TEMP_WIDGETS[HPindex], ((isTrtRunning)&(EXP_UCtempViewer ())));
#else
        wdgWpr.GUIsetWidgetEnable ( APP_GUI_TRT_SCR_BUT_CHNG_TIME_TO_TEMP_WIDGETS[HPindex], 0);
#endif

        //AppGUIpanelCtrlColourBlink();

        // TODO
        /* Gestión de los botones de recogida del panel si tenemos el main menu activado, puesto
         * que los tapa debemos deshabilitar los 2 inferiores si el menu esta desplegado */
        if( HPindex == 0 || HPindex == 1)
        { wdgWpr.GUIsetWidgetEnable( ButHideControlPanelHP1 + HPindex, !isPopUp); } //GUARRADA PDTE
        else
        { wdgWpr.GUIsetWidgetEnable( ButHideControlPanelHP1 + HPindex, !AppGUIdata.mainMenuHdlr.isUp && !isPopUp);}
    }
}

void AppGUIhandleTrtZone( void)
{
    cAppGUIbodys body = AppGUIdata.trtZoneHdlr.body;
    cAppGUIfullBodyAreas area = AppGUIdata.trtZoneHdlr.selTrtArea;

    uint32 widID;
//    GUIstRect areaTS;
    uint8 i, HPindex;
    uint16 xOn, yOn, xOff, yOff, imgOn, imgOff;
    uint32 errCode, wrnCode;
    errors_messages errMsg;
    warning_messages wrnMsg;
	
    uint8 isPopUp, isRFIDPopUp, isRecommPopUp, isTimePopUp, isVaccSmallPopUp;
		
    /* Obtenemos si hay algún popUp activo para condicionar las habilitaciones pero no
     * las visibilidades. La parte gráfica no se ve afectada */
    isPopUp = (AppGUIisPopUpActive() | (ERR_interface_msg( Maq, &errCode, &errMsg, &wrnCode, &wrnMsg) == 0));
    isRecommPopUp = AppGUIisRecommPopUpActive();
    isTimePopUp = AppGUIisTimePopUpActive();
    isVaccSmallPopUp = AppGUIisVacSmallPopUpActive();
    isRFIDPopUp = AppGUIisRFIDPopUpActive();
	
    /* Refrescamos visibilidad y habilitado en general */
//    GUIsetWidgetVisibility( imgFullBodyAndZoom, 1);
//    GUIsetWidgetEnable( imgFullBodyAndZoom, 1 && !isPopUp);

    /* Imagen de fondo según estemos en zoom o no */
    if( area != AppGUIfullBodyNO_AREA)
    {
        //Para presentar la información de ayuda a la selección de manipulo. Comprobamos que haya seleccionado un punto, y que esté activado un popup, siendo el de tiempo o el de información
        if( (AppGUIdata.trtZoneHdlr.selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED) && !(isPopUp^(isRecommPopUp/*|isTimePopUp*/|isVaccSmallPopUp|isRFIDPopUp)))
        {
            //De esta forma ponemos visible el botón de info, pero solo se habilita si el popup activo es el de info
            wdgWpr.GUIsetWidgetVisibility( SwPopUpRecommInfo, 1);
            wdgWpr.GUIsetWidgetEnable( SwPopUpRecommInfo, (!isTimePopUp)&(!isVaccSmallPopUp)&(!isRFIDPopUp));
        }
        else
        {
            //En caso contrario deshabilitamos y ponemos invisible el botón de info
            wdgWpr.GUIsetWidgetVisibility( SwPopUpRecommInfo, 0);
            wdgWpr.GUIsetWidgetEnable( SwPopUpRecommInfo, 0);
        }
        /* Estamos en zoom, ponemos la imagen de fondo según el area seleccionada */
//        GUIsetImgViewerImage( imgFullBodyAndZoom, APP_GUI_FULL_BODY_AREAS_DATA[body][area].IDimgZoom);
        wdgWpr.bodyZoom(true);
        wdgWpr.bodyGenderSelect(body);
        wdgWpr.bodyAreaSelect(area);

        /* Ponemos el boton de return si no hay popUp ya que entonces el control lo tiene el popUp */
        if( isPopUp == 0)
        {
            wdgWpr.GUIsetWidgetVisibility( ButPopUpReturn, 1);
            wdgWpr.GUIsetWidgetEnable( ButPopUpReturn, 1);
        }
        else if (AppGUIisRecommPopUpActive() || AppGUIisVacPopUpActive())
        {
            wdgWpr.GUIsetWidgetVisibility( ButPopUpReturn, 0);
            wdgWpr.GUIsetWidgetEnable( ButPopUpReturn, 0);
        }
		
//        /* Ocultamos los botones de full body area */
//        for( i = AppGUIfullBodyTorso; i < APP_GUI_NUM_FULL_BODY_AREAS; i++)
//        {
//            /* Obtenemos el ID del widget */
//            widID = APP_GUI_TRT_SCR_FULL_BODY_AREAS_WIDGETS[i];
			
//            /* Mostrar y habilitar */
//            GUIsetWidgetVisibility( widID, 0);
//            GUIsetWidgetEnable( widID, 0);
//        }
		
        /* Ocultamos las zonas seleccionadas en los HP según esten en el full body */
        for( i = 0; i < APP_GUI_MAXNUM_HP; i++)
        {
            /* Obtenemos el ID del widget */
            widID = APP_GUI_TRT_SCR_FULL_BODY_SELECTED_ZONE_WIDGETS[i];
			
            /* Ocultamos */
            wdgWpr.GUIsetWidgetVisibility( widID, 0);
//            wdgWpr.GUIsetWidgetEnable( widID, 0);
        }
		
        /* Colocamos los puntos necesarios de seleccion de zona */
        for( i = 0; i < APP_GUI_MAX_DOTS_PER_AREA; i++)
        {
            /* Obtenemos el ID del widget */
            widID = APP_GUI_TRT_SCR_DOT_ZONES_WIDGETS[i];
			
            /* Mostramos y habilitamos el punto dependiendo de si es usado */
//            wdgWpr.GUIsetWidgetVisibility( widID, APP_GUI_AREA_ZOOM_DOTS[body][area][i].isUsed);
            wdgWpr.GUIsetWidgetEnable( widID, APP_GUI_AREA_ZOOM_DOTS[body][area][i].isUsed && !isPopUp);
			
            /* Cambiamos las imagenes y las coordenadas si el punto es usado */
            if( APP_GUI_AREA_ZOOM_DOTS[body][area][i].isUsed)
            {
                /* Buscamos si algún HP tiene este punto como seleccionado */
                HPindex = 0;
                while( HPindex < APP_GUI_MAXNUM_HP &&
                       ( APP_GUI_TRT_SCR_DOT_ZONES_WIDGETS[AppGUIdata.slot[HPindex].selTrtDot] != widID ||
                         AppGUIdata.slot[HPindex].selTrtArea != area))
                { HPindex++;}
				
                /* El area de TS y la imagen es independiente de si esta vinculado a un HP o no */
//                areaTS.posx = APP_GUI_AREA_ZOOM_DOTS[body][area][i].TSrectX;
//                areaTS.posy = APP_GUI_AREA_ZOOM_DOTS[body][area][i].TSrectY;
//                areaTS.w = APP_GUI_AREA_ZOOM_DOTS[body][area][i].TSrectW;
//                areaTS.h = APP_GUI_AREA_ZOOM_DOTS[body][area][i].TSrectH;
//                GUIsetSwitchTscImg( widID, APP_GUI_AREA_ZOOM_DOTS[body][area][i].IDimgTS);
				
                /* Segun el resultado de la busqueda */
//                if( HPindex >= APP_GUI_MAXNUM_HP)
//                {
                    /* No lo tiene ningun HP asociado, colocamos las imagenes y coordenadas correspondientes */
//                    xOn = APP_GUI_AREA_ZOOM_DOTS[body][area][i].imgOnOffX;
//                    yOn = APP_GUI_AREA_ZOOM_DOTS[body][area][i].imgOnOffY;
//                    xOff = APP_GUI_AREA_ZOOM_DOTS[body][area][i].imgOnOffX;
//                    yOff = APP_GUI_AREA_ZOOM_DOTS[body][area][i].imgOnOffY;
//                    imgOn = APP_GUI_AREA_ZOOM_DOTS[body][area][i].IDimgOn;
//                    imgOff = APP_GUI_AREA_ZOOM_DOTS[body][area][i].IDimgOff;
//                }
//                else
//                {
                    /* Si esta asociado a un HP, dependiendo de cual asignamos las imagenes */
//                    xOn = APP_GUI_AREA_ZOOM_DOTS[body][area][i].imgHPzoomOn_X;
//                    yOn = APP_GUI_AREA_ZOOM_DOTS[body][area][i].imgHPzoomOn_Y;
//                    xOff = APP_GUI_AREA_ZOOM_DOTS[body][area][i].imgHPzoomOff_X;
//                    yOff = APP_GUI_AREA_ZOOM_DOTS[body][area][i].imgHPzoomOff_Y;
//                    imgOn = APP_GUI_AREA_ZOOM_DOTS[body][area][i].IDimgHPzoomOn[HPindex];
//                    imgOff = APP_GUI_AREA_ZOOM_DOTS[body][area][i].IDimgHPzoomOff[HPindex];
//                }

				
                /* Finalmente configuramos el widget */
//                GUIsetSwitchPosition( widID, xOn, yOn, xOff, yOff, xOn, yOn, xOff, yOff, areaTS);
//                GUIsetSwitchImg( widID, imgOn, imgOff, imgOn, imgOff);

                wdgWpr.dotZoneAssignHp((EAppGUIwidgetIDlist)i, (EAppGUI_HPsIDs)HPindex);
            }
        }
    }
    else
    { // Full body view
        wdgWpr.GUIsetWidgetVisibility( SwPopUpRecommInfo, 0);
        wdgWpr.GUIsetWidgetEnable( SwPopUpRecommInfo, 0);
		
        /* No estamos en zoom, ponemos la imagen de fondo según el cuerpo */
//        GUIsetImgViewerImage( imgFullBodyAndZoom, APP_GUI_FULL_BODY_IMAGES[body].IDimg);
//        GUIsetImgViewerPosition( imgFullBodyAndZoom, APP_GUI_FULL_BODY_IMAGES[body].imgX,
//                                 APP_GUI_FULL_BODY_IMAGES[body].imgY);
        wdgWpr.bodyZoom(false);
        wdgWpr.bodyGenderSelect(body);

        /* Quitamos el boton de return si no ha sido activado el popup de RFID */
        if(!AppGUIisRFIDPopUpActive())
        {
            wdgWpr.GUIsetWidgetVisibility( ButPopUpReturn, 0);
            wdgWpr.GUIsetWidgetEnable( ButPopUpReturn, 0);
        }
		
        /* Ocultamos los puntos de seleccion de zona */
//        for( i = 0; i < APP_GUI_MAX_DOTS_PER_AREA; i++)
//        {
//            /* Obtenemos el ID del widget */
//            widID = APP_GUI_TRT_SCR_DOT_ZONES_WIDGETS[i];
			
//            /* Deshabilitamos el widget y lo deseleccionamos */
//            GUIsetWidgetVisibility( widID, 0);
//            GUIsetWidgetEnable( widID, 0);
//            GUIsetSwitchStatus( widID, 0);
//        }
				
//        /* Mostramos y habilitamos los botones de seleccion de area */
//        for( i = AppGUIfullBodyTorso; i < APP_GUI_NUM_FULL_BODY_AREAS; i++)
//        {
//            /* Obtenemos el ID del widget */
//            widID = APP_GUI_TRT_SCR_FULL_BODY_AREAS_WIDGETS[i];
			
//            /* Mostrar y habilitar */
//            GUIsetWidgetVisibility( widID, 1);
//            GUIsetWidgetEnable( widID, 1 && !isPopUp);
			
            /* Asignamos imagen de press, la de release y la de TSCR */
//            GUIsetImgButton( widID, APP_GUI_FULL_BODY_AREAS_DATA[body][i].IDimgPrs, 1);
//            GUIsetImgButton( widID, APP_GUI_FULL_BODY_AREAS_DATA[body][i].IDimgRls, 0);
//            GUIsetTscImgButton( widID, APP_GUI_FULL_BODY_AREAS_DATA[body][i].IDimgTS);
			
            /* Asignamos las coordenadas de las imagenes y el area de TSCR */
//            areaTS.posx = APP_GUI_FULL_BODY_AREAS_DATA[body][i].imgTS_X;
//            areaTS.posy = APP_GUI_FULL_BODY_AREAS_DATA[body][i].imgTS_Y;
//            areaTS.w = APP_GUI_FULL_BODY_AREAS_DATA[body][i].TSrectW;
//            areaTS.h = APP_GUI_FULL_BODY_AREAS_DATA[body][i].TSrectH;
//            GUIsetButonPosition( widID, APP_GUI_FULL_BODY_AREAS_DATA[body][i].imgPrsX,
//                                 APP_GUI_FULL_BODY_AREAS_DATA[body][i].imgPrsY,
//                                 APP_GUI_FULL_BODY_AREAS_DATA[body][i].imgRlsX,
//                                 APP_GUI_FULL_BODY_AREAS_DATA[body][i].imgRlsY,
//                                 areaTS);
//        }
		
        /* Mostramos las zonas seleccionadas en los HP según esten en el full body */
        for( i = 0; i < APP_GUI_MAXNUM_HP; i++)
        {
            /* Obtenemos el ID del widget */
            widID = APP_GUI_TRT_SCR_FULL_BODY_SELECTED_ZONE_WIDGETS[i];
			
            /* Comprobamos si para este HP hay zona seleccionada */
            if( AppGUIdata.slot[i].selTrtArea != AppGUIfullBodyNO_AREA &&
                AppGUIdata.slot[i].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED)
            {
                /* Mostramos el widget */
                wdgWpr.GUIsetWidgetVisibility( widID, 1);
//                GUIsetWidgetEnable( widID, 1 && !isPopUp);
				
                /* El HP tiene zona de tratamiento seleccionada, ponemos la imagen y coordenadas */
//                imgOn = APP_GUI_AREA_ZOOM_DOTS[body][AppGUIdata.slot[i].selTrtArea][AppGUIdata.slot[i].selTrtDot].IDimgHPbody[i];
                xOn = APP_GUI_AREA_ZOOM_DOTS[body][AppGUIdata.slot[i].selTrtArea][AppGUIdata.slot[i].selTrtDot].imgHPbody_X;
                yOn = APP_GUI_AREA_ZOOM_DOTS[body][AppGUIdata.slot[i].selTrtArea][AppGUIdata.slot[i].selTrtDot].imgHPbody_Y;
//                GUIsetImgViewerImage( widID, imgOn);
                wdgWpr.GUIsetImgViewerPosition( widID, xOn, yOn);
            }
            else
            {
                /* Ocultamos el widget */
                wdgWpr.GUIsetWidgetVisibility( widID, 0);
//                GUIsetWidgetEnable( widID, 0);
            }
        }
    }
}

void AppGUIhandleTimePopUp( uint8 show, uint8 HPindex)
{
    cAppGUITimePopUpState timePopupState = AppEnumsNs::TimePopUpSelectedTimeCount;
	
    /* Según si se quiere mostrar o no */
    if( show)
    {
        /* Activar el popUp */
		
        /* Configuramos el estado de los switches de seleccion si es la primera vez */
        if( AppGUIdata.slot[HPindex].selTime == APP_GUI_NO_TIME_SELECTED)
        {
            timePopupState = AppEnumsNs::TimePopUpSelectedTimeNone;
        }
        else
        {
            if (AppGUIdata.slot[AppGUIdata.timeHdlr.HPindex].selTime == HP_CRYO_TIME_50_MIN)	//Si hay tiempo seleccionado y son los 50min
            {
                timePopupState = AppEnumsNs::TimePopUpSelectedTime50;
            }
            else													//Si el caso es el opuesto, mostramos los 50 min
            {
                timePopupState = AppEnumsNs::TimePopUpSelectedTime70;
            }
        }
    }
    else
    {
        /* Desactivamos el popUp */
        timePopupState = AppEnumsNs::TimePopUpHidden;
//		AppGUIhandleTrtZone();
    }

    wdgWpr.GUIsetTimePopUp((EAppGUI_HPsIDs)HPindex, timePopupState);
}

void AppGUIhandleTstVacPopUp( uint8 show, uint8 HPindex)
{
    uint8 i;
    uint8 isTstRunning;
    static uint8 isFirstTime = 1;
    uint8 autoIsOK;
	
    tPRFdata *PRF;
    tHPcryoData *HP;
	
//    HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF);
	
//    /* Según si se quiere mostrar o no */
//    if( show)
//    {
//        /* Activar el popUp */
//        GUIactivePopUp( PopUpTstVac);

//        /* Configuramos el estado de los switches de seleccion y sus imagenes según se haya realizado ya el
//         * test o no. tambien los deshabilitamos si hay un test de vacum en marcha para el HP en cuestion */
//        for( i = 0; i < HP_CRYO_VAC_LVL_NUM; i++)
//        {
//            /* Estado On Off solo si es la primera vez que entramos para esta aparición del popUp */
//            if( isFirstTime)
//            {
//                GUIsetSwitchStatus( APP_GUI_TRT_SCR_POPUP_TST_VAC_SW_LIST[i], AppGUIdata.tstVacHdlr.selVacLvl == i);
//            }
			
//            /* Imagenes de test done o not done */
//            if (HPcryoTestVacumStatus( HP, PRF) != HP_CRYO_TEST_VAC_RUN_VACUM) GUIsetImgViewerImage(APP_GUI_TRT_SCR_POPUP_TST_VAC_IMG_LIST[i], APP_GUI_TRT_SCR_POPUP_TST_VAC_LVL_IMAGES[AppGUIdata.slot[HPindex].testedVacLvls[i]][i]);
			
//            /* Habilitacion segun haya test en marcha o no */
//            isTstRunning = AppGUIisTstVacRunning( HPindex, NULL);
//            GUIsetWidgetEnable( APP_GUI_TRT_SCR_POPUP_TST_VAC_SW_LIST[i], !isTstRunning);
//        }
		
//        /* Estado de la mano de pulsación de boton Inicio de succión*/
//        if (AppGUIdata.tstVacHdlr.waitingUserStart == 1)		//Si estamos esperando al usuario para que pulse el HP
//        {
//            GUIsetWidgetVisibility( imgPopUpTstVacPulHand, AppGUIdata.slot[HPindex].statusFlagsOnOff[AppGUIblinkPul]);
//        }
//        else{	GUIsetWidgetVisibility( imgPopUpTstVacPulHand, 0);	}		//En cualquier otro caso (no esperando al usuario...) entonces dejamos invisible el widget
		
//        /* Estado de la mano de pulsación de boton Final de succión*/
//        if (AppGUIdata.tstVacHdlr.waitingUserEnd == 1)		//Si estamos esperando al usuario para que pulse el HP
//        {
//            GUIsetWidgetVisibility( imgPopUpTstVacPulHandx2, AppGUIdata.slot[HPindex].statusFlagsOnOff[AppGUIblinkPul]);
			
//            /* Si es modo auto tenemos que gestionar el indicador de plica OK - V7760*/
//            HPcryoTestVacumIsInAutoAndOK( &autoIsOK, HP, PRF);
//            GUIsetWidgetVisibility(imgPopUpTstVacAUTOstatus, HPcryoTestVacIsAuto(HP, PRF));
//            if( autoIsOK != 0){ GUIsetImgViewerImage( imgPopUpTstVacAUTOstatus, c439_HPalarmaPlicaOK);}
//            else{ GUIsetImgViewerImage( imgPopUpTstVacAUTOstatus, c438_HPalarmaPlicainsuficiente);}
//        }
//        else
//        {
//            GUIsetWidgetVisibility( imgPopUpTstVacPulHandx2, 0);
//            GUIsetWidgetVisibility(imgPopUpTstVacAUTOstatus, 0);
//        }		//En cualquier otro caso (no esperando al usuario...) entonces dejamos invisible el widget
		
		
//        if (HPcryoTestVacumStatus( HP, PRF) == HP_CRYO_TEST_VAC_RUN_VACUM && (!HPcryoTestVacIsAuto(HP, PRF)))			//Si el estado del test de vacum es running
//        {
//            if (AppGUIdata.slot[HPindex].statusFlagsOnOff[AppGUIblinkVac])	GUIsetImgViewerImage( APP_GUI_TRT_SCR_POPUP_TST_VAC_IMG_LIST[AppGUIdata.tstVacHdlr.Tst_vac_but], APP_GUI_TRT_SCR_POPUP_TST_VAC_LVL_IMAGES[AppGUItstVacDone][AppGUIdata.tstVacHdlr.Tst_vac_but]);
//            else	GUIsetImgViewerImage( APP_GUI_TRT_SCR_POPUP_TST_VAC_IMG_LIST[AppGUIdata.tstVacHdlr.Tst_vac_but], APP_GUI_TRT_SCR_POPUP_TST_VAC_LVL_IMAGES[AppGUItstVacNotDone][AppGUIdata.tstVacHdlr.Tst_vac_but]);
//        }
		
//        GUIsetWidgetEnable( butPopUpTstVacManualLowLvl, !(AppGUIdata.tstVacHdlr.waitingUserStart | AppGUIdata.tstVacHdlr.waitingUserEnd));
//        GUIsetWidgetEnable( butPopUpTstVacManualMidLvl, !(AppGUIdata.tstVacHdlr.waitingUserStart | AppGUIdata.tstVacHdlr.waitingUserEnd));
//        GUIsetWidgetEnable( butPopUpTstVacManualHighLvl, !(AppGUIdata.tstVacHdlr.waitingUserStart | AppGUIdata.tstVacHdlr.waitingUserEnd));
//        GUIsetWidgetEnable( SwPopUpTstVacLowLvl, (!(AppGUIdata.tstVacHdlr.waitingUserStart | AppGUIdata.tstVacHdlr.waitingUserEnd) && (AppGUIdata.slot[HPindex].TrtMode == HP_CRYO_TRT_MODE_MANUAL)));
//        GUIsetWidgetEnable( SwPopUpTstVacMidLvl, (!(AppGUIdata.tstVacHdlr.waitingUserStart | AppGUIdata.tstVacHdlr.waitingUserEnd) && (AppGUIdata.slot[HPindex].TrtMode == HP_CRYO_TRT_MODE_MANUAL)));
//        GUIsetWidgetEnable( SwPopUpTstVacHighLvl, ( !(AppGUIdata.tstVacHdlr.waitingUserStart | AppGUIdata.tstVacHdlr.waitingUserEnd) && (AppGUIdata.slot[HPindex].TrtMode == HP_CRYO_TRT_MODE_MANUAL)));
//        GUIsetWidgetEnable( APP_GUI_TRT_SCR_BUT_TSTVAC_WIDGETS[HPindex], !(AppGUIdata.tstVacHdlr.waitingUserStart | AppGUIdata.tstVacHdlr.waitingUserEnd));
//        GUIsetWidgetEnable( butPopUpTstVacAuto, (!(AppGUIdata.tstVacHdlr.waitingUserStart | AppGUIdata.tstVacHdlr.waitingUserEnd) && HPcryoIsAutoModeAvaible( HP, PRF)));
		
//        /* Poner en la barra de color de HP la imagen adecuada */
//        GUIsetImgViewerImage( imgPopUpHPcolorBar, APP_GUI_TRT_SCR_POPUP_COLOR_BAR_IMAGES[HPindex]);

//        GUIsetWidgetVisibility(butPopUpTstVacAuto, HPcryoIsAutoModeAvaible( HP, PRF));	//Poner visible el boton test AUTO si está disponible

//        /* Indicamos que ya no es la primera vez */
//        isFirstTime = 0;
//    }
//    else
//    {
//        /* Desactivamos el popUp */
//        GUIdisablePopUp( PopUpTstVac);
		
//        /* Indicamos que la próxima vez que se llame a esta función para activar el popUp
//         * será la primera vez del caso "show" para esa aparición */
//        isFirstTime = 1;
				
//        /* Si la gestión de zona de tratamiento esta en zoom tenemos un glitch de un refresco en
//         * el que el boton "Return" desaparece ya que el popUp lo deshabilita al quitarse pero
//         * el handle de la zona de tratamiento lo volvera a poner. Para evitar esto ponemos el estado
//         * del boton de return a visible y habilitado si la zona de tratamiento esta en zoom. Lo mas facil es
//         * forzar un update de la zona */
////		AppGUIhandleTrtZone();
//    }
//    AppGUIhandleCtrlPanel( 1, HPindex);
}

void AppGUIhandleTstVacSMALLPopUp( uint8 show, uint8 HPindex)
{
//    GUIstRect areaTS;
//    areaTS.h = APP_GUI_POPUP_VAC_SMALL_BUT_HEIGHT;
//    areaTS.w = APP_GUI_POPUP_VAC_SMALL_BUT_WIDTH;
//    areaTS.posx = 0;
//    areaTS.posy = 0;
		
//    if( show)
//    {
//        areaTS.posx = APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][App_GUI_VacLowLevel][Coordinate_X];
//        areaTS.posy = APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][App_GUI_VacLowLevel][Coordinate_Y];
//        GUIsetButonPosition( butPopUpTstVacSmallLowLvl,
//                            APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][App_GUI_VacLowLevel][Coordinate_X],
//                            APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][App_GUI_VacLowLevel][Coordinate_Y],
//                            APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][App_GUI_VacLowLevel][Coordinate_X],
//                            APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][App_GUI_VacLowLevel][Coordinate_Y],
//                            areaTS);
		
//        areaTS.posx = APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][App_GUI_VacMedLevel][Coordinate_X];
//        areaTS.posy = APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][App_GUI_VacMedLevel][Coordinate_Y];
//        GUIsetButonPosition( butPopUpTstVacSmallMedLvl,
//                            APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][App_GUI_VacMedLevel][Coordinate_X],
//                            APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][App_GUI_VacMedLevel][Coordinate_Y],
//                            APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][App_GUI_VacMedLevel][Coordinate_X],
//                            APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][App_GUI_VacMedLevel][Coordinate_Y],
//                            areaTS);
		
//        areaTS.posx = APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][AppGUI_VacHighLevel][Coordinate_X];
//        areaTS.posy = APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][AppGUI_VacHighLevel][Coordinate_Y];
//        GUIsetButonPosition( butPopUpTstVacSmallHighLvl,
//                            APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][AppGUI_VacHighLevel][Coordinate_X],
//                            APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][AppGUI_VacHighLevel][Coordinate_Y],
//                            APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][AppGUI_VacHighLevel][Coordinate_X],
//                            APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][AppGUI_VacHighLevel][Coordinate_Y],
//                            areaTS);
		
//        //Colocamos la imagen de fondo del selector en función del manipulo
//        GUIsetImgViewerImage( imgPopUpVacSelBck, APP_GUI_TRT_SCR_POPUP_VAC_SMALL_BCK_IMG[HPindex]);
//        //Asignamos las coordenadas al fondo del selector de vacuum
//        GUIsetImgViewerPosition( imgPopUpVacSelBck,
//                                APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][AppGUI_VacLevelSelector][Coordinate_X],
//                                APP_GUI_POPUP_TST_VAC_SMALL_COORDINATES_PER_HP[HPindex][AppGUI_VacLevelSelector][Coordinate_Y]);
		
//        /* Activar el popUp */
//        GUIactivePopUp( PopUpTstVacSmall);
		
//        GUIsetImgButton(butPopUpTstVacSmallLowLvl, APP_GUI_POPUP_TST_VAC_SMALL_BUT_IMAGES[HP_CRYO_VAC_LVL_0][AppGUIdata.tstVacHdlr.selVacLvl==HP_CRYO_VAC_LVL_0], 0);
//        GUIsetWidgetVisibility( butPopUpTstVacSmallLowLvl, 1);	//Se ponen los widgets visibles
//        GUIsetWidgetEnable( butPopUpTstVacSmallLowLvl, (AppGUIdata.tstVacHdlr.selVacLvl!=HP_CRYO_VAC_LVL_0));
//        GUIsetImgButton(butPopUpTstVacSmallMedLvl, APP_GUI_POPUP_TST_VAC_SMALL_BUT_IMAGES[HP_CRYO_VAC_LVL_1][AppGUIdata.tstVacHdlr.selVacLvl==HP_CRYO_VAC_LVL_1], 0);
//        GUIsetWidgetVisibility( butPopUpTstVacSmallMedLvl, 1);
//        GUIsetWidgetEnable( butPopUpTstVacSmallMedLvl, (AppGUIdata.tstVacHdlr.selVacLvl!=HP_CRYO_VAC_LVL_1));
//        GUIsetImgButton(butPopUpTstVacSmallHighLvl, APP_GUI_POPUP_TST_VAC_SMALL_BUT_IMAGES[HP_CRYO_VAC_LVL_2][AppGUIdata.tstVacHdlr.selVacLvl==HP_CRYO_VAC_LVL_2], 0);
//        GUIsetWidgetVisibility( butPopUpTstVacSmallHighLvl, 1);
//        GUIsetWidgetEnable( butPopUpTstVacSmallHighLvl, (AppGUIdata.tstVacHdlr.selVacLvl!=HP_CRYO_VAC_LVL_2));
		
//        GUIsetWidgetVisibility( imgPopUpVacSelBck, 1);
//    }
//    else
//    {
//        /* Desactivamos el popUp */
//        GUIdisablePopUp( PopUpTstVacSmall);
		
//        //Quitamos la visibilidad y deshabilitamos los widgets
//        GUIsetWidgetVisibility( butPopUpTstVacSmallLowLvl, 0);
//        GUIsetWidgetEnable( butPopUpTstVacSmallLowLvl, 0);
//        GUIsetWidgetVisibility( butPopUpTstVacSmallMedLvl, 0);
//        GUIsetWidgetEnable( butPopUpTstVacSmallMedLvl, 0);
//        GUIsetWidgetVisibility( butPopUpTstVacSmallHighLvl, 0);
//        GUIsetWidgetEnable( butPopUpTstVacSmallHighLvl, 0);
//        GUIsetWidgetVisibility( imgPopUpVacSelBck, 0);
//    }
//    AppGUIhandleCtrlPanel( 1, HPindex);
////	AppGUIhandleTrtZone();
}

void AppGUIhandleRFIDpopUp( uint8 show, uint8 HPindex)
{
//    tPRFdata *PRF;
//    tHPcryoData *HP;
//    uint8 i;	//auxiliar
	
//    /* Según si se quiere mostrar o no */
//    if( show)
//    {
//        /* Activar el popUp */
//        GUIactivePopUp( PopUpRFID);
		
//        /* Poner en la barra de color de HP la imagen adecuada */
//        GUIsetImgViewerImage( imgPopUpHPcolorBar, APP_GUI_TRT_SCR_POPUP_COLOR_BAR_IMAGES[HPindex]);
		
//        /* Poner la imagen de la etiqueta que requiere */
//        HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF);
		
//        for (i = HP_CRYO_LABEL_ZO; i<HP_CRYO_NUM_LABELS; i++) 	//Recorremos todas las etiquetas
//        {
//            if (HP_CYRO_LABEL_REQUESTED[i][HPcryoGetModel( HP, PRF)] == HP_CRYO_DEFAULT)		//Una vez encontramos la etiqueta predeterminada para el manipulo en cuestión, la guardamos como solicitada
//            {
//                GUIsetImgViewerImage( imgPopUpRFIDlabel, APP_GUI_TRT_SCR_POPUP_RFID_LABELS_IMGS[i]);
//            }
//        }
		
//        /* Poner si se ha leido si es Ok o no Ok la etiqueta leida */
//        GUIsetImgViewerImage( imgPopUpRFIDresult, APP_GUI_TRT_SCR_POPUP_RFID_STATUS_IMGS[HP->trt.RFID_read_label]);
		
//        if(AppGUIdata.RFIDhdlr.show_reuse_option)
//        {
//            GUIsetWidgetVisibility( NumVwrPopUpRFIDrestTime, EXP_UCreuseLabelAllow(PRF->IDperifHW));
//            GUIsetNumViewerNum( NumVwrPopUpRFIDrestTime, AppGUIsecondsToClock(EXP_UCreuseLabelTRTtime(PRF->IDperifHW)), 2);
//            GUIsetWidgetEnable( butPopUpRFIDreuseLabel, EXP_UCreuseLabelAllow(PRF->IDperifHW));
//        }
//        else
//        {
//            GUIsetWidgetVisibility( NumVwrPopUpRFIDrestTime, 0);
//            GUIsetWidgetEnable( butPopUpRFIDreuseLabel, 0);
//        }
			
//    }
//    else
//    {
//        /* Desactivamos el popUp */
//        GUIdisablePopUp( PopUpRFID);
//        if(HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF)){	HP->trt.RFID_read_label = RFID_NO_LABEL;	}
//        AppGUIdata.RFIDhdlr.show_reuse_option = 0;
//        GUIsetWidgetVisibility( NumVwrPopUpRFIDrestTime, 0);
//        GUIsetWidgetEnable( butPopUpRFIDreuseLabel, 0);
//        /* Si la gestión de zona de tratamiento esta en zoom tenemos un glitch de un refresco en
//         * el que el boton "Return" desaparece ya que el popUp lo deshabilita al quitarse pero
//         * el handle de la zona de tratamiento lo volvera a poner. Para evitar esto ponemos el estado
//         * del boton de return a visible y habilitado si la zona de tratamiento esta en zoom. Lo mas facil es
//         * forzar un update de la zona */
////		AppGUIhandleTrtZone();
//    }
}

void AppGUIhandleRecommendationpopUp( uint8 show, uint8 selTrtDot, cAppGUIfullBodyAreas selTrtArea)
{
    uint8 i;
	
    /* Según si se quiere mostrar o no */
    if( show)
    {
        /* Activar el popUp */
        wdgWpr.GUIactivePopUp( PopUpRecomm);
		
        for (i = 0; i < HP_CRYO_NUM_HP_MODELS; i++)	{	wdgWpr.GUIsetWidgetVisibility( APP_GUI_TRT_LIST_OF_IMG_HP_RECOMMENDED_PER_ZONE[i], APP_GUI_HP_RECOMMENDED_PER_ZONE[i][selTrtArea][selTrtDot]);	}
    }
    else
    {
        /* Desactivamos el popUp */
        wdgWpr.GUIdisablePopUp( PopUpRecomm);
		
        //for (i = HP_CRYO_MODEL_CURVED; i < HP_CRYO_NUM_HP_MODELS; i++){		GUIsetWidgetVisibility( APP_GUI_TRT_LIST_OF_IMG_HP_RECOMMENDED_PER_ZONE[i], 0 );	}
		
        /* Si la gestión de zona de tratamiento esta en zoom tenemos un glitch de un refresco en
         * el que el boton "Return" desaparece ya que el popUp lo deshabilita al quitarse pero
         * el handle de la zona de tratamiento lo volvera a poner. Para evitar esto ponemos el estado
         * del boton de return a visible y habilitado si la zona de tratamiento esta en zoom. Lo mas facil es
         * forzar un update de la zona */
//		AppGUIhandleTrtZone();
    }
}

void AppGUIhandleWarningPopUp( uint8 show)
{
    /* Según si se quiere mostrar o no */
    if( show)
    {
        ERR_erase_NewWarningFlag();
        wdgWpr.GUIactiveWarningsPopUp();

        wdgWpr.GUIWarningIconActivate( App_GUI_Wng_Nivel_Agua_Bajo, AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Nivel_Agua_Bajo);
        wdgWpr.GUIWarningIconActivate( App_GUI_Wng_Nivel_Agua_Medio, AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Nivel_Agua_Medio);
        wdgWpr.GUIWarningIconActivate( App_GUI_Wng_Temp_Amb, AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Temp_Amb);
        wdgWpr.GUIWarningIconActivate( App_GUI_Wng_RFID, AppGUIdata.AppGUI_WarningHandler.Flag_Wng_RFID);
        wdgWpr.GUIWarningIconActivate( App_GUI_Wng_RTC, AppGUIdata.AppGUI_WarningHandler.Flag_Wng_RTC);
        wdgWpr.GUIWarningIconActivate( App_GUI_Wng_Filtro_Aire, AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Filtro_Aire);
    }
    else
    {
        wdgWpr.GUIdisableWarningsPopUp();
//        /* Para bloquear el boton de idiomas*/
//        AppGUIhandleMainMenu(AppGUIdata.mainMenuHdlr.isUp, AppGUIdata.screen);
    }
	
//    if (AppGUIdata.mainMenuHdlr.isUp) GUIsetWidgetEnable( APP_GUI_AVISOS_SWITCH_WIDGET_SCREENS[AppGUIdata.screen], 1);
}

void AppGUIhandleMainMenu( uint8 show)
{
    uint8 i;
    uint8 isPopUp;
		
    /* Obtenemos si hay algún popUp activo para condicionar las habilitaciones pero no
     * las visibilidades. La parte gráfica no se ve afectada */
    isPopUp = AppGUIisPopUpActive();
		
    /* Habilitamos los widgets del main menu cuando esta desplegado */
    wdgWpr.mainMenuOpened(show);
    wdgWpr.mainMenuEnabled(!isPopUp);
	
    /* Indicamos el estado del menu principal */
    AppGUIdata.mainMenuHdlr.isUp = show;
	
// TODO    if(isPopUp && AppGUIisWarningPopUpActive())	GUIsetWidgetEnable( SwTrtScrAvisos, 1);
}

void AppGUIclearData( void)
{
    uint8 i;
	
    AppGUIdata.MachineErrorBeep = 0;
    AppGUIdata.RFIDhdlr.HPindex = 0;
    AppGUIdata.RFIDhdlr.show_reuse_option = 0;
    AppGUIdata.timeHdlr.HPindex = 0;
    AppGUIdata.timeHdlr.selTime = APP_GUI_NO_TIME_SELECTED;
    AppGUIdata.tstVacHdlr.HPindex = 0;
    AppGUIdata.tstVacHdlr.selVacLvl = APP_GUI_NO_VAC_LVL_SELECTED;
    AppGUIdata.tstVacHdlr.waitingUserStart = 0;
    AppGUIdata.tstVacHdlr.waitingUserEnd = 0;
    AppGUIdata.trtZoneHdlr.selTrtArea = AppGUIfullBodyNO_AREA;
    AppGUIdata.trtZoneHdlr.selTrtDot = APP_GUI_NO_TRT_DOT_SELECTED;
    AppGUIdata.mainMenuHdlr.isUp = 0;
    for ( i=0; i < MaxGrupoZonas; i++)	AppGUIdata.trtZoneHdlr.timeGroupZones[i] = HP_CRYO_TIME_NO_TIME;
    for ( i=0; i < APP_GUI_MAXNUM_HP; i++)
    {
        AppGUIdata.slot[i].TrtMode = HP_CRYO_TRT_MODE_MANUAL;
        AppGUIdata.slot[i].ErrorBeep = 0;
        AppGUIdata.slot[i].timeRefResuccionesBlink = 0;
        AppGUIdata.slot[i].numResucciones = 0;
    }
}

void AppGUIclearSlotData( uint8 HPindex)
{
    uint8 i;
	
    /*/////////////////DANGER///////////////////////////DANGER////////////////////////////DANGER/////////////////////////////*/
    cHPcryoTrtTimes time_not_used;
    tPRFdata *PRF;
    tHPcryoData *HP;
    uint8 GroupZoneRep;
	
    HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF);
	
    GroupZoneRep = 0;
    for( i = 0; i < APP_GUI_MAXNUM_HP; i++)
    {
        HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[i], &HP, &PRF);
		
        if (i == HPindex)	GroupZoneRep++;		//En caso de estar comparando el manipulo seleccionado consigo mismo (indicamos que se puede borrar el tiempo de grupo)
		
        if ((i != HPindex) && (					//En caso de que no tenga zona asignada el manipulo pasado por parametro con el que se quiere comparar
           ((AppGUIdata.slot[i].selTrtArea == AppGUIfullBodyNO_AREA) && (AppGUIdata.slot[i].selTrtDot == APP_GUI_NO_TRT_DOT_SELECTED)) ||
           ((AppGUIdata.slot[HPindex].selTrtArea == AppGUIfullBodyNO_AREA) && (AppGUIdata.slot[HPindex].selTrtDot == APP_GUI_NO_TRT_DOT_SELECTED))))
            GroupZoneRep++;
		
        if ((i != HPindex) &&					//En caso de que teniendo ambos manipulos zonas asignadas, estas no pertenezcan al mismo grupo o si pertenecen, pero uno está limitado por modelo
            (AppGUIdata.slot[i].selTrtArea != AppGUIfullBodyNO_AREA) && (AppGUIdata.slot[i].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED) &&
            (AppGUIdata.slot[HPindex].selTrtArea != AppGUIfullBodyNO_AREA) && (AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED) &&
            ((APP_GUI_TRT_ZONES_GROUP_ASSOCIATION[AppGUIdata.slot[i].selTrtArea][AppGUIdata.slot[i].selTrtDot] != APP_GUI_TRT_ZONES_GROUP_ASSOCIATION[AppGUIdata.slot[HPindex].selTrtArea][AppGUIdata.slot[HPindex].selTrtDot]) ||
            (HPcryoGetTimeRestriction (&time_not_used, HP, PRF))))
            GroupZoneRep++;
    }
    //Si se cumplen las premisas anteriores para los 4 manipulos, y la zona seleccionada no vale 0xFF
    if (( GroupZoneRep == 4) && (AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED))
    {
        //Si de los 4 manipulos no hay ninguno que pertenezca al mismo grupo, entonces borramos el tiempo de grupo
        AppGUIdata.trtZoneHdlr.timeGroupZones[APP_GUI_TRT_ZONES_GROUP_ASSOCIATION[AppGUIdata.slot[HPindex].selTrtArea][AppGUIdata.slot[HPindex].selTrtDot]] = HP_CRYO_TIME_NO_TIME;
    }
    /*/////////////////DANGER///////////////////////////DANGER////////////////////////////DANGER/////////////////////////////*/
	
    AppGUIdata.slot[HPindex].timeRefResuccionesBlink = 0;
    AppGUIdata.slot[HPindex].numResucciones = 0;
    AppGUIdata.slot[HPindex].CleanUPhdlr.HP_in_cleaning = 0;
    AppGUIdata.slot[HPindex].CleanUPhdlr.HP_clean_init_or_end = HP_CRYO_CLEAN_UP_NONE;
    AppGUIdata.slot[HPindex].CleanUPhdlr.Timer_count = 0.00;
    AppGUIdata.slot[HPindex].CleanUPhdlr.status = APP_GUI_CLEAN_UP_COUNTDOWN;
    AppGUIdata.slot[HPindex].TrtMode = HP_CRYO_TRT_MODE_AUTO;
    AppGUIdata.slot[HPindex].TstVacuumModeScss = HP_CRYO_TEST_VACUUM_AUTO_UNDONE;
    AppGUIdata.slot[HPindex].selTrtArea = AppGUIfullBodyNO_AREA;
    AppGUIdata.slot[HPindex].selTrtDot = APP_GUI_NO_TRT_DOT_SELECTED;
    AppGUIdata.slot[HPindex].selTime = APP_GUI_NO_TIME_SELECTED;
    AppGUIdata.slot[HPindex].selVacLvl = HP_CRYO_VAC_LVL_2;
    AppGUIdata.slot[HPindex].tmrBlink = 0;
    AppGUIdata.slot[HPindex].trtTime = 0.0;
    AppGUIdata.slot[HPindex].isTrtDone = 0;
    AppGUIdata.slot[HPindex].showAutoKO = 0;
    AppGUIdata.slot[HPindex].showVacumRetryRqstUsrToMoveHP = 0;
    AppGUIdata.slot[HPindex].alarmVacumRetryRqstUsrToMoveHP = 0;
    AppGUIdata.slot[HPindex].VwrTemperatureOrTime = 0;
    AppGUIdata.slot[HPindex].TempHP = 0.0;
    for( i = 0; i < APP_GUI_MAX_BLINK_INDICATORS; i++){ AppGUIdata.slot[HPindex].statusFlagsOnOff[i] = 0;}
    for( i = 0; i < HP_CRYO_VAC_LVL_NUM; i++){ AppGUIdata.slot[HPindex].testedVacLvls[i] = 0;}
}

void AppGUIhandleErrPopUps( void)
{
//    uint8 errMsg, wrnMsg;
//    uint32 errCode, wrnCode;
//    static uint8 isErrUp[Max_perifs];
//    uint8 dev, i;
//    uint32 widID;
//    uint8 HPindex;
//    tHPcryoData *HP;
//    tPRFdata *PRF;
	
//    /* Miramos si hay algún error activo para cada uno de los manipulos */
//    for( dev = Manip1; dev < Maq; dev++)
//    {
//        /* Obtenemso el error */
//        isErrUp[dev] = ERR_interface_msg( dev, &errCode, &errMsg, &wrnCode, &wrnMsg);
//        isErrUp[dev] = ( errCode != Error_ok);
		
//        /* Obtenemos el HPindex a partir del slot (dev) */
//        for( i = 0; i < APP_GUI_MAXNUM_HP; i++)
//        {
//            if( APP_GUI_SLOT_DISTRIBUTION[i] == dev){ HPindex = i;}
//        }
		
//        if (!AppGUIdata.slot[HPindex].ErrorBeep && isErrUp[dev]) { AppGUIdata.slot[HPindex].ErrorBeep = 1;	BUZZ_Configure(1, 100, PATRO_SO_ERROR );	}
//        if (!isErrUp[dev])	{	AppGUIdata.slot[HPindex].ErrorBeep = 0;	}
		
//        /* Habilitamos y hacemos visibles los widgets de error */
//        for( i = 0; i < APP_GUI_NUM_ERR_WIDGETS_WHEN_HP; i++)
//        {
//            widID = APP_GUI_TRT_SCR_HP_ERR_WIDGETS[HPindex][i];
//            GUIsetWidgetVisibility( widID, isErrUp[dev]);
//            GUIsetWidgetEnable( widID, isErrUp[dev]);
//        }
		
//        /* Deshabilitamos los widgets del panel de control solo si hay error */
//        for( i = 0; i < APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_SHOW_NUM; i++)
//        {
//            widID = APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_SHOW[HPindex][i];
//            if( isErrUp[dev]){ GUIsetWidgetEnable( widID, 0);}
//        }
//        for( i = 0; i < APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_HIDE_NUM; i++)
//        {
//            widID = APP_GUI_TRT_SCR_CTRL_PNL_WID_WHEN_HIDE[HPindex][i];
//            if( isErrUp[dev]){ GUIsetWidgetEnable( widID, 0);}
//        }
		
//        /* Ponemos el codigo de error */
//        GUIsetNumViewerNum( APP_GUI_TRT_SCR_HP_ERR_WIDGETS[HPindex][1], (float)errCode, 0);
		
//        /* Ponemos el tiempo de tratamiento */			//V7750
//        if(HPcryoGetFromSlot(APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
//        {
//            if (HPcryoGetStatus(HP, PRF) == HP_CRYO_TREATMENT)
//            {
//                GUIsetNumViewerNum( APP_GUI_TRT_SCR_HP_ERR_WIDGETS[HPindex][4], AppGUIdata.slot[HPindex].trtTime, 2);
//            }
//        }
				
//        /* Ponemos el mensaje de error */
//        GUIsetImgViewerImage( APP_GUI_TRT_SCR_HP_ERR_WIDGETS[HPindex][2],
//                              APP_GUI_TRT_SCR_HP_ERR_MSG_IMAGES[errMsg]);
//    }
	
//    /* Miramos para la maquina */
//    isErrUp[Maq] = ERR_interface_msg( Maq, &errCode, &errMsg, &wrnCode, &wrnMsg);
//    isErrUp[Maq] = ( errCode != Error_ok);
	
//    if (!AppGUIdata.MachineErrorBeep && isErrUp[Maq]) { AppGUIdata.MachineErrorBeep = 1;	BUZZ_Configure(1, 100, PATRO_SO_ERROR );	}
//    if (!isErrUp[Maq])	{	AppGUIdata.MachineErrorBeep = 0;	}
	
//    /* Habilitamos y hacemos visibles los widgets de error de la maquina */
//    for( i = 0; i < APP_GUI_NUM_ERR_WIDGETS_WHEN_UC; i++)
//    {
//        widID = APP_GUI_TRT_SCR_UC_ERR_WIDGETS[i];
//        GUIsetWidgetVisibility( widID, isErrUp[Maq]);
//        GUIsetWidgetEnable( widID, isErrUp[Maq]);
//    }
	
//    /* Para la maquina no deshabilitamos nada mas */
	
//    /* Ponemos el codigo de error */
//    GUIsetNumViewerNum( NumVwrPopUpErrUC, (float)errCode, 0);
	
//    /* Ponemos el mensaje de error */
//    GUIsetImgViewerImage( imgPopUpErrMsgUC, APP_GUI_TRT_SCR_HP_ERR_MSG_IMAGES[errMsg]);
}

void AppGUIhandleCleanUpPopUps( uint8 show, uint8 HPindex)
{
//    tPRFdata *PRF;
//    tHPcryoData *HP;
//    uint8 isWaitingUser, isCountDown;
			
//    isWaitingUser = ( AppGUIdata.slot[HPindex].CleanUPhdlr.status == APP_GUI_CLEAN_UP_WAIT_USER);
//    isCountDown = ( AppGUIdata.slot[HPindex].CleanUPhdlr.status == APP_GUI_CLEAN_UP_COUNTDOWN);
//    if( HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF)) {AppGUIdata.slot[HPindex].CleanUPhdlr.HP_clean_init_or_end = HPcryoCleanUpInitOrEnd( HP, PRF);}
	

//    if((AppGUIdata.slot[HPindex].CleanUPhdlr.HP_clean_init_or_end == HP_CRYO_CLEAN_UP_END_OF_TRT) || (show==0))
//    {
//        //Fondo
//        GUIsetWidgetVisibility( APP_GUI_TRT_SCR_CLEANUP_BCKGND_WIDGETS[HPindex], show);
//        GUIsetWidgetEnable( APP_GUI_TRT_SCR_CLEANUP_BCKGND_WIDGETS[HPindex], show);
		
//        //Imagen
//        GUIsetWidgetVisibility( APP_GUI_TRT_SCR_CLEANUP_IMAGES_WIDGETS[HPindex], show);
//        GUIsetWidgetEnable( APP_GUI_TRT_SCR_CLEANUP_IMAGES_WIDGETS[HPindex], show);
//        GUIsetImgViewerImage( APP_GUI_TRT_SCR_CLEANUP_IMAGES_WIDGETS[HPindex],
//                              APP_GUI_TRT_SCR_CLEANUP_STATUS_IMAGES[AppGUIdata.slot[HPindex].CleanUPhdlr.status]);
	
//        //Visor numerico
//        GUIsetWidgetVisibility( APP_GUI_TRT_SCR_CLEANUP_NUM_VIEWER_WIDGETS[HPindex], show);
//        GUIsetWidgetEnable( APP_GUI_TRT_SCR_CLEANUP_NUM_VIEWER_WIDGETS[HPindex], show);
//        GUIsetNumViewerNum(APP_GUI_TRT_SCR_CLEANUP_NUM_VIEWER_WIDGETS[HPindex],
//                           AppGUIdata.slot[HPindex].CleanUPhdlr.Timer_count, 2);
		
//        //Boton YES
//        GUIsetWidgetVisibility( APP_GUI_TRT_SCR_CLEANUP_BUTTON_YES_WIDGETS[HPindex], show);		//Solo si hay pregunta
//        GUIsetWidgetEnable( APP_GUI_TRT_SCR_CLEANUP_BUTTON_YES_WIDGETS[HPindex], show && isWaitingUser);
//        GUIsetImgButton( APP_GUI_TRT_SCR_CLEANUP_BUTTON_YES_WIDGETS[HPindex], APP_GUI_TRT_SCR_CLEANUP_BUTTON_YES_IMAGES[isWaitingUser], 0);
		
//        //Boton NO
//        GUIsetWidgetVisibility( APP_GUI_TRT_SCR_CLEANUP_BUTTON_NO_WIDGETS[HPindex], show);			//Solo si hay pregunta
//        GUIsetWidgetEnable( APP_GUI_TRT_SCR_CLEANUP_BUTTON_NO_WIDGETS[HPindex], show && isWaitingUser);
//        GUIsetImgButton( APP_GUI_TRT_SCR_CLEANUP_BUTTON_NO_WIDGETS[HPindex], APP_GUI_TRT_SCR_CLEANUP_BUTTON_NO_IMAGES[isWaitingUser], 0);
	
//        //Boton CLEAN
//        GUIsetWidgetVisibility( APP_GUI_TRT_SCR_CLEANUP_BUTTON_CLEAN_WIDGETS[HPindex], show);
//        GUIsetWidgetEnable( APP_GUI_TRT_SCR_CLEANUP_BUTTON_CLEAN_WIDGETS[HPindex], show && isCountDown);
//        GUIsetImgButton( APP_GUI_TRT_SCR_CLEANUP_BUTTON_CLEAN_WIDGETS[HPindex], APP_GUI_TRT_SCR_CLEANUP_BUTTON_CLEAN_IMAGES[isCountDown], 0);

//#ifdef APP_SW_VER_NEW_CLEANUP_MODE
//        //Boton CANCEL
//        GUIsetWidgetVisibility( APP_GUI_TRT_SCR_CLEANUP_BURTTON_CANCEL_WIDGETS[HPindex], show);
//        GUIsetWidgetEnable( APP_GUI_TRT_SCR_CLEANUP_BURTTON_CANCEL_WIDGETS[HPindex], (show && HPcryoCleanUpCancelAllowed(APP_GUI_SLOT_DISTRIBUTION[HPindex])));
		
//        //Visor numerico de cancelaciones
//        GUIsetWidgetVisibility( APP_GUI_TRT_SCR_CLEANUP_NUMVWR_CANCELLED_TIMES_WIDGET[HPindex], show);
//        GUIsetWidgetEnable( APP_GUI_TRT_SCR_CLEANUP_NUMVWR_CANCELLED_TIMES_WIDGET[HPindex], show);
//        GUIsetNumViewerNum(APP_GUI_TRT_SCR_CLEANUP_NUMVWR_CANCELLED_TIMES_WIDGET[HPindex],
//                            (HPcryoCleanUpNumberOfCancellations(APP_GUI_SLOT_DISTRIBUTION[HPindex]) + (HP_CRYO_CLEAN_UP_MAX_TIMES_CANCEL/10)), 1);
//        /* Para representar el número de cancelaciones referenciado a un total (3-5), se sustituye el caracter del punto por la barra, y se calcula para obtener de decimal
//         * el número máximo de cancelaciones (3.5) */
//#else
//        //Boton CANCEL
//        GUIsetWidgetVisibility( APP_GUI_TRT_SCR_CLEANUP_BURTTON_CANCEL_WIDGETS[HPindex], 0);
//        GUIsetWidgetEnable( APP_GUI_TRT_SCR_CLEANUP_BURTTON_CANCEL_WIDGETS[HPindex], 0);
		
//        //Visor numerico de cancelaciones
//        GUIsetWidgetVisibility( APP_GUI_TRT_SCR_CLEANUP_NUMVWR_CANCELLED_TIMES_WIDGET[HPindex], 0);
//        GUIsetWidgetEnable( APP_GUI_TRT_SCR_CLEANUP_NUMVWR_CANCELLED_TIMES_WIDGET[HPindex], 0);
//        GUIsetNumViewerNum(APP_GUI_TRT_SCR_CLEANUP_NUMVWR_CANCELLED_TIMES_WIDGET[HPindex],
//                            0.0, 1);
//#endif

//    }
//    else if(AppGUIdata.slot[HPindex].CleanUPhdlr.HP_clean_init_or_end == HP_CRYO_CLEAN_UP_INIT_OF_TRT)
//    {
//        //Imagen
//        GUIsetWidgetVisibility( APP_GUI_TRT_SCR_CLEANUP_IMAGES_WIDGETS[HPindex], show);
//        GUIsetWidgetEnable( APP_GUI_TRT_SCR_CLEANUP_IMAGES_WIDGETS[HPindex], show);
//        GUIsetImgViewerImage( APP_GUI_TRT_SCR_CLEANUP_IMAGES_WIDGETS[HPindex],
//                              APP_GUI_TRT_SCR_CLEANUP_STATUS_IMAGES[AppGUIdata.slot[HPindex].CleanUPhdlr.status]);
//    }
}

uint8 AppGUIisTrtRunning( uint8 HPindex, cHPcryoTreatmentStatus *status)
{
    tPRFdata *PRF;
    tHPcryoData *HP;
	
    /* Comprobamos si el HP indicado esta en tratamiento y si lo está devolvemos el status */
    if( HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
    {
        /* Hay HP, vamos a ver si esta en tratamiento */
        if( HPcryoGetStatus( HP, PRF) == HP_CRYO_TREATMENT)
        {
            /* Esta en tratamiento, devolvemos cierto y guardamos el estado de tratamiento si el
             * puntero pasado no es NULL */
            if( status != NULL){ ( *status) = HPcryoTrtStatus( HP, PRF);}
            return 1;
        }
    }
	
    /* Si llegamos aqui es que no esta en tratamiento */
    return 0;
}

uint8 AppGUIisTstVacRunning( uint8 HPindex, cHPcryoTestVacumStatus *status)
{
//    tPRFdata *PRF;
//    tHPcryoData *HP;
	
//    /* Comprobamos si el HP indicado esta en test vacum y si lo está devolvemos el status */
//    if( HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
//    {
//        /* Hay HP, vamos a ver si esta en test vacum */
//        if( HPcryoGetStatus( HP, PRF) == HP_CRYO_TEST_VACUM)
//        {
//            /* Esta en test vacum, devolvemos cierto y guardamos el estado de test si el
//             * puntero pasado no es NULL */
//            if( status != NULL){ ( *status) = HPcryoTestVacumStatus( HP, PRF);}
//            return 1;
//        }
//    }
	
    /* Si llegamos aqui es que no esta en test vacum */
    return 0;
}

uint8 AppGUIisHPconnected( uint8 HPindex, cHPcryoModels *model)
{
    tPRFdata *PRF;
    tHPcryoData *HP;
		
    /* Comprobamos si el slot indicado tiene un HP conectado */
    if( HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
    {
        /* Hay HP, asignamos el modelo */
        if( model != NULL){ 	( *model) = HPcryoGetModel( HP, PRF);	}
		
        /* Devolvemos cierto */
        return 1;
    }
	
    /* Si llegamos aqui es que no hay HP */
    return 0;
}

uint8 AppGUIisInitRunning( uint8 HPindex)
{
//    tPRFdata *PRF;
//    tHPcryoData *HP;
	
//    /* Comprobamos si el HP indicado esta en inicialización */
//    if( HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
//    {
//        /* Hay HP, vamos a ver si esta en tratamiento */
//        if(( HPcryoGetStatus( HP, PRF) == HP_CRYO_TEST_INIT)||(PRF->status == PRF_STATUS_INIT))		return 1;
//    }
	
    /* Si llegamos aqui es que no esta en inicialización */
    return 0;
}

/* Funciones privadas */
void AppGUIloadScrInit( void)
{
//    uint8 i;
	
//    /* Asignamos la pantalla actual */
//    AppGUIdata.screen = APP_GUI_LOAD_SCREEN;
		
//    /* Inicializamos las variables de la animación a ocultas para poder ejecutarla */
//    for( i = 0; i < APP_GUI_LOAD_SCR_ANIM_IMG_NUM; i++)
//    {
//        GUIsetWidgetVisibility( APP_GUI_LOAD_SCR_ANIM_IMG_LIST[i], APP_GUI_WIDGET_NOT_VISIBLE);
//    }
}

void AppGUIloadScrUpdate( void)
{
//    static uint8 loadScrIndex = 0;
//    static uint32 animTmr = 0;
	
//    /* Comprobamos si ha pasado un ciclo de animacion */
//    if( TICKS_DiffTicks( animTmr) > APP_GUI_LOAD_SCR_ANIM_TIME)
//    {
//        /* Ejecutamos un ciclo de animación */
//        animTmr = TICKS_GetTicks();
//        GUIsetWidgetVisibility( APP_GUI_LOAD_SCR_ANIM_IMG_LIST[loadScrIndex], 1);
		
//        /* Pasamos al siguiente ciclo para la siguiente vuelta */
//        loadScrIndex = ( loadScrIndex + 1) % APP_GUI_LOAD_SCR_ANIM_IMG_NUM;
		
//        /* Si ya hemos terminado pasamos a la pantalla de inicio y reseteamos el temporizador.
//         * Hacemos un update para que se vea el ultimo tramo de la barra */
//        if( loadScrIndex == 0){ AppGUIupdate(); AppGUIchangeScreen( APP_GUI_INIT_SCREEN);}
//    }
}

void AppGUIinitScrInit( void)
{
    /* Asignamos la pantalla actual */
    AppGUIdata.screen = APP_GUI_INIT_SCREEN;
    wdgWpr.changeScreen(APP_GUI_INIT_SCREEN);
	
    /* Inicializamos el menu principal a oculto */
    AppGUIhandleMainMenu( 0 );

    AppGUIhandleWarningPopUp( 0);
    AppGUIwarningNotification();
}

void AppGUIinitScrUpdate( void)
{
//    stWidget *popUp;
//    /* Nada que hacer */
//    //PDTE
//    //GUIsetNumViewerNum( numVwrSWversion, APP_SW_VERSION, 1);
	
//    AppGUIwarningNotification();
//    AppGUIupdateWarningFlags();
	
//    /* Actualizamos el popUp de Avisos según esté activado o no*/
//    popUp = GUIgetWidget( APP_GUI_AVISOS_POPUP_WIDGET_SCREENS[AppGUIdata.screen]);
//    AppGUIhandleWarningPopUp( popUp->enable != 0);
}


void AppGUItrtScrInit( void)
{
    uint8 i;

    /* Inicializamos las variables de control */
    AppGUIclearData();
		
    /* Asignamos la pantalla actual */
    AppGUIdata.screen = APP_GUI_TREATMENT_SCREEN;
	
    AppGUIhandleWarningPopUp( 0);
    AppGUIwarningNotification();
	
    /* Inicializaciones por HP */
    for( i = 0; i < APP_GUI_MAXNUM_HP; i++)
    {
        /* Reseteamos las variables de los slots */
        AppGUIclearSlotData( i);
				
        /* Ocultamos todos los popUps */
        AppGUIhandleTimePopUp( 0, i);
        AppGUIhandleTstVacPopUp( 0, i);
        AppGUIhandleRFIDpopUp( 0, i);
        AppGUIhandleTstVacSMALLPopUp( 0, i);
        AppGUIhandleRecommendationpopUp( 0, 0, AppGUIfullBodyNO_AREA);
        AppGUIhandleWarningPopUp( 0);
		
        AppGUIdata.slot[i].isCtrlPnlShow = 1;
    }
	
    /* Inicializamos el menu principal oculto */
    AppGUIhandleMainMenu( 0 );
	
    /* Forzamos un update de la pantalla para asegurar que se arranque
     * con el estado de los HP actual y no lo veamos en 2 refrescos */
    AppGUItrtScrUpdate();

    wdgWpr.changeScreen(APP_GUI_TREATMENT_SCREEN);
}

void AppGUItrtScrUpdate( void)
{
    uint8 i; //Variable auxiliar
    tHPcryoData *HP;
    tPRFdata *PRF;
    uint8 HPindex, isAutoOK;
//    stWidget *popUp;
    cHPcryoModels modelHP;
    uint8 autoIsOK;
	
    AppGUIwarningNotification();
    AppGUIupdateWarningFlags();
	
    AppGUIdata.EndTRTbeep = 0;
	
    /* Actualizamos el interface según el estado del HP */
    for( HPindex = 0; HPindex < APP_GUI_MAXNUM_HP; HPindex++)
    {
        /* Comprobamos si hay HP */
        if( HPcryoGetFromSlot((cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
        {
            /* Hay HP conectado, ponemos el color del LED */
            HPcryoSetLEDcolor( APP_GUI_LED_COLOR_FROM_SLOT[HPindex], HP, PRF);
			
            /* Indicamos para el popUp que no estamos esperando la acción del usuario. Solo en un caso
             * se pone a TRUE asi que para ahorrar código lo preasignamos a FALSE. Lo condicionamos
             * al HP que tiene activado el popUp */
            if( HPindex == AppGUIdata.tstVacHdlr.HPindex){ AppGUIdata.tstVacHdlr.waitingUserStart = 0;		AppGUIdata.tstVacHdlr.waitingUserEnd = 0;}
			
            if ( !AppGUIisInitRunning(HPindex) && (AppGUIdata.slot[HPindex].selTrtArea != APP_GUI_NUM_FULL_BODY_AREAS) && (AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED))
                    AppGUIapplyTimeRestriction( HPindex, HP, PRF);	//Si ya no está en inicialización y tenemos seleccionada una zona, comprobamos la restricción de tiempo para el modelo del manipulo
			
            /* Indicamos de inicio que el HP no esta en cleaning */
            AppGUIdata.slot[HPindex].CleanUPhdlr.HP_in_cleaning = 0;
            AppGUIdata.slot[HPindex].CleanUPhdlr.HP_clean_init_or_end = HP_CRYO_CLEAN_UP_NONE;
								
            /* Actualizamos el tiempo de tratamiento */
            AppGUIdata.slot[HPindex].trtTime = AppGUIcalcTrtTime( HPindex, HPcryoTrtGetTimeSeconds( HP, PRF),
                                                                  HPcryoTrtGetTreatmentTotalTimeSeconds( HP, PRF));
            /* Actualizamos la temperatura del tratamiento */
            AppGUIdata.slot[HPindex].TempHP = HPcryoHPtemperature ( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex]);
			
            /* Comprobamos si hay que mostrar el aviso de no es OK la plica en modo AUTO */
            if( HPcryoTrtIsInAutoAndOK( &isAutoOK, HP, PRF)){ AppGUIdata.slot[HPindex].showAutoKO = !isAutoOK;}
            else{ AppGUIdata.slot[HPindex].showAutoKO = 0;}
			
            /* Comprobamos si hay que mostrar el aviso de recolocar por resucciones */
            AppGUIdata.slot[HPindex].showVacumRetryRqstUsrToMoveHP = HPcryoTrtVacumRetryIsUserRqstToMoveHP( HP, PRF);	//Indica cuando se va a recomendar una recolocación
            if(AppGUIdata.slot[HPindex].showVacumRetryRqstUsrToMoveHP == 0){AppGUIdata.slot[HPindex].alarmVacumRetryRqstUsrToMoveHP = 0;} //V7750 - En caso de quitar la solicitud de recolocación, quitamos también la alarma de recolocación
            //GUIsetNumViewerNum(APP_GUI_TRT_SCR_NUM_VWE_RESUCCTIONS_NUM_WIDGETS[HPindex], HPcryoTrtResuctionsNum( HP, PRF), 0);
			
            /* Control de boton AUTO/MANUAL para limitar - Tiny y Tiny Curved solo en modo Manual*/
            if (!HPcryoIsAutoModeAvaible(HP, PRF))	AppGUIdata.slot[HPindex].TrtMode = HP_CRYO_TRT_MODE_MANUAL;
			
            /* Según el estado actual */
            switch( HPcryoGetStatus( HP, PRF))
            {
                case HP_CRYO_TEST_INIT: break;
                case HP_CRYO_IDLE:
                    /* Si hemos realizado un tratamiento reseteamos las variables de control
                     * del slot y indicamos que ya no hay tratamiento finalizado */
                    if( AppGUIdata.slot[HPindex].isTrtDone != 0)
                    {
                        AppGUIclearSlotData( HPindex);
                    }
					
                    switch( HPcryoIdleGetVacumStatus( HP, PRF))
                    {
                        case HP_CRYO_IDLE_VAC_STATUS_WITH_VAC:
                            /* Parpadeo de pulsar boton al haber vacum */
                            AppGUIsetHPstatusFlags( APP_GUI_FLG_OFF, APP_GUI_FLG_BLINK, APP_GUI_FLG_FIX, APP_GUI_FLG_OFF, HPindex);
                            break;
                        case HP_CRYO_IDLE_VAC_STATUS_WITHOUT_VAC:
                            /* Todos los indicadores apagados */
                            AppGUIsetHPstatusFlags( APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, HPindex);
                            break;
                        default: break;
                    }
                    break;
                case HP_CRYO_TEST_VACUM:
                    switch( HPcryoTestVacumStatus( HP, PRF))
                    {
                        case HP_CRYO_TEST_VAC_RUN_WAITING_USER_START:
                            /* Activamos indicadores */
                            AppGUIsetHPstatusFlags( APP_GUI_FLG_OFF, APP_GUI_FLG_BLINK, APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, HPindex);
							
                            /* Indicamos para el popUp que estamos esperando la acción del usuario */
                            if( HPindex == AppGUIdata.tstVacHdlr.HPindex){ AppGUIdata.tstVacHdlr.waitingUserStart = 1;}
                            break;
                        case HP_CRYO_TEST_VAC_RUN_VACUM:
                            /* Activamos indicadores */
                            AppGUIsetHPstatusFlags( APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, APP_GUI_FLG_BLINK, APP_GUI_FLG_OFF, HPindex);
                            break;
                        case HP_CRYO_TEST_VAC_RUN_WAITING_USER_END:
                            /* Activamos indicadores */
                            AppGUIsetHPstatusFlags( APP_GUI_FLG_OFF, APP_GUI_FLG_BLINK, APP_GUI_FLG_FIX, APP_GUI_FLG_OFF, HPindex);
							
                            /* Indicamos para el popUp que estamos esperando la acción del usuario */
                            if( HPindex == AppGUIdata.tstVacHdlr.HPindex){ AppGUIdata.tstVacHdlr.waitingUserEnd = 1;}
							
                            /* Indicamos que se ha realizado el test de vacum (No AUTO)*/
                            if(!HPcryoTestVacIsAuto(HP, PRF))
                            {
                                AppGUIdata.slot[HPindex].testedVacLvls[AppGUIdata.tstVacHdlr.Tst_vac_but] = 1;

                                if(AppGUIdata.slot[HPindex].TrtMode == HP_CRYO_TRT_MODE_MANUAL)
                                {
                                    for( i = HP_CRYO_VAC_LVL_0; i < HP_CRYO_VAC_LVL_NUM; i++){	wdgWpr.GUIsetSwitchStatus( APP_GUI_TRT_SCR_POPUP_TST_VAC_SW_LIST[i], 0);	}
                                    wdgWpr.GUIsetSwitchStatus( APP_GUI_TRT_SCR_POPUP_TST_VAC_SW_LIST[AppGUIdata.tstVacHdlr.Tst_vac_but], 1);
                                    AppGUIdata.tstVacHdlr.selVacLvl = (cHPcryoTrtVacLvls)AppGUIdata.tstVacHdlr.Tst_vac_but;
                                    AppGUIdata.slot[AppGUIdata.tstVacHdlr.HPindex].selVacLvl = AppGUIdata.tstVacHdlr.selVacLvl;
                                }
                            }
                            else		/* V7760 - Habra que indicar que se ha realizado un test de vacuum AUTO, indicar tambien si ha tenido exito */
                            {
                                HPcryoTestVacumIsInAutoAndOK( &autoIsOK, HP, PRF);
                                if(autoIsOK){	AppGUIdata.slot[HPindex].TstVacuumModeScss = HP_CRYO_TEST_VACUUM_AUTO_DONE_SUCCESS;}
                                else{	AppGUIdata.slot[HPindex].TstVacuumModeScss = HP_CRYO_TEST_VACUUM_AUTO_DONE_FAIL;}

                            }
							
                            break;
                        case HP_CRYO_TEST_VAC_DONE:
                        case HP_CRYO_TEST_VAC_FAIL:
                            /* Activamos indicadores */
                            AppGUIsetHPstatusFlags( APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, HPindex);
                            break;
                    }
                    break;
                case HP_CRYO_TREATMENT:
                    switch( HPcryoTrtStatus( HP, PRF))
                    {
                        case HP_CRYO_TREATMENT_RUN_WAITING_RFID:
                            /* Activamos indicadores */
                            AppGUIsetHPstatusFlags( APP_GUI_FLG_BLINK, APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, HPindex);
							
                            /* Levantamos el popUp si no esta ya activado */
                            if (AppGUIIsPopupDisplayed(PopUpRFID) != 0)
                            {
                                /* Guardamos el HP que ha activado el popUp */
                                AppGUIdata.RFIDhdlr.HPindex = HPindex;
								
                                /* Activamos el popUp */
                                AppGUIdata.RFIDhdlr.animLoadImg = 1;
                                AppGUIhandleRFIDpopUp( 1, HPindex);
                            }
                            break;
                        case HP_CRYO_TREATMENT_RUN_WAITING_USER_START:
                            /* Activamos indicadores */
                            AppGUIsetHPstatusFlags( APP_GUI_FLG_OFF, APP_GUI_FLG_BLINK, APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, HPindex);
							
                            /* Quitamos el popUp si esta activado por este HP */
                            if( AppGUIdata.RFIDhdlr.HPindex == HPindex)
                            {
                                if(TICKS_DiffTicks(HP->trt.RFIDpopupTimer)>APP_GUI_1SEC_MILISEC)	//V7760- -Espera de 1 segundo para quitar el popup
                                {
                                    AppGUIhandleRFIDpopUp( 0, AppGUIdata.RFIDhdlr.HPindex);
                                }
                                else
                                {
                                    AppGUIhandleRFIDpopUp( 1, AppGUIdata.RFIDhdlr.HPindex);
                                }
                            }
                            break;
                        case HP_CRYO_TREATMENT_RUN_VACUM:
                            /* Activamos indicadores */
                            AppGUIsetHPstatusFlags( APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, APP_GUI_FLG_BLINK, APP_GUI_FLG_OFF, HPindex);
							
                            /* Indicamos que se ha realizado un tratamiento para poder resetear las variables
                             * de control del slot cuando vayamos a IDLE ( es cuando el TRT ha finalizado) */
                            if (AppGUIdata.slot[HPindex].trtTime <= APP_GUI_TRT_TIME_TO_BEEP) AppGUIdata.EndTRTbeep = 1;
                            AppGUIdata.slot[HPindex].isTrtDone = 1;
                            break;
                        case HP_CRYO_TREATMENT_RUN_COOLING:
                            /* Activamos indicadores */
                            if (EXP_UCgetVacumRetrys( HPcryoGetSlot( HP, PRF)) > AppGUIdata.slot[HPindex].numResucciones)		//Control de si ha habido resucciones
                            {
                                AppGUIdata.slot[HPindex].timeRefResuccionesBlink = TICKS_GetTicks(); 							//Tomamos referencia de tiempo
                                AppGUIdata.slot[HPindex].numResucciones = EXP_UCgetVacumRetrys( HPcryoGetSlot( HP, PRF));		//Actualizamos contador de resucciones
                            }
                            if( TICKS_DiffTicks(AppGUIdata.slot[HPindex].timeRefResuccionesBlink) < APP_GUI_30SEC_MILISEC)						//Si la diferencia es menor de 30 sec
                            {
                                AppGUIsetHPstatusFlags( APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, APP_GUI_FLG_BLINK, APP_GUI_FLG_BLINK, HPindex);		//Parpadea el indicador de vacuum
                            }
                            else
                            {
                                AppGUIsetHPstatusFlags( APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, APP_GUI_FLG_FIX, APP_GUI_FLG_BLINK, HPindex);			//Si no, solo parpadea el indicador de frio
                            }
							
                            /* Indicamos que se ha realizado un tratamiento para poder resetear las variables
                             * de control del slot cuando vayamos a IDLE ( es cuando el TRT ha finalizado) */
                            if (AppGUIdata.slot[HPindex].trtTime <= APP_GUI_TRT_TIME_TO_BEEP) AppGUIdata.EndTRTbeep = 1;
                            AppGUIdata.slot[HPindex].isTrtDone = 1;
                            break;
                        case HP_CRYO_TREATMENT_RUN_WAITING_USER_END:
                            /* Activamos indicadores */
                            AppGUIsetHPstatusFlags( APP_GUI_FLG_OFF, APP_GUI_FLG_BLINK, APP_GUI_FLG_FIX, APP_GUI_FLG_OFF, HPindex);
							
                            /* Indicamos que se ha realizado un tratamiento para poder resetear las variables
                             * de control del slot cuando vayamos a IDLE ( es cuando el TRT ha finalizado) */
                            if (AppGUIdata.slot[HPindex].trtTime <= APP_GUI_TRT_TIME_TO_BEEP) AppGUIdata.EndTRTbeep = 1;
                            AppGUIdata.slot[HPindex].isTrtDone = 1;
                            break;
                        case HP_CRYO_TREATMENT_RUN_PAUSE:
                            break;
                        case HP_CRYO_TREATMENT_DONE:
                        case HP_CRYO_TREATMENT_FAIL:
                            /* Activamos indicadores */
                            AppGUIsetHPstatusFlags( APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, HPindex);
                            break;
                    }
                    break;
                case HP_CRYO_CLEAN_UP:
                    AppGUIdata.slot[HPindex].CleanUPhdlr.HP_in_cleaning = 1;
                    AppGUIdata.slot[HPindex].CleanUPhdlr.Timer_count = AppGUIsecondsToClock( HPcryoCleanUpGetCountDownSeconds( HP, PRF));
                    switch( HPcryoCleanUpStatus( HP, PRF))
                    {
                        case HP_CRYO_CLEAN_UP_COUNTDOWN:
                            AppGUIdata.slot[HPindex].CleanUPhdlr.status = APP_GUI_CLEAN_UP_COUNTDOWN;
                            break;
                        case HP_CRYO_CLEAN_UP_CHECK_PATIENT:
                            AppGUIdata.slot[HPindex].CleanUPhdlr.status = APP_GUI_CLEAN_UP_CLEANING;
                            break;
                        case HP_CRYO_CLEAN_UP_WAITING_USER:
                            AppGUIdata.slot[HPindex].CleanUPhdlr.status = APP_GUI_CLEAN_UP_WAIT_USER;
                            break;
                        case HP_CRYO_CLEAN_UP_CLEANING:
                            AppGUIdata.slot[HPindex].CleanUPhdlr.status = APP_GUI_CLEAN_UP_CLEANING;
                            break;
                        case HP_CRYO_CLEAN_UP_WAIT_VACUM:
                            AppGUIdata.slot[HPindex].CleanUPhdlr.status = APP_GUI_CLEAN_UP_WAIT_VACUM;
                            break;
                        case HP_CRYO_CLEAN_UP_DONE:
                        case HP_CRYO_CLEAN_UP_FAIL:
                        default:
                            break;
                    }
                    break;
                case HP_CRYO_FATIGUE_0: break;
                default: break;
            }
        }
        else
        {
            /* No hay HP conectado */
            /* Inicialización de variables del slot */
            AppGUIclearSlotData( HPindex);
			
            /* Apagamos todos los indicadores */
            AppGUIsetHPstatusFlags( APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, APP_GUI_FLG_OFF, HPindex);
			
            /* Actualizamos el tiempo de tratamiento */
            AppGUIdata.slot[HPindex].trtTime = AppGUIcalcTrtTime( HPindex, 0, 0);
        }

        /* Actualizamos el panel de control */
        //AppGUIhandleCtrlPanel(AppGUIdata.slot[HPindex].isCtrlPnlShow, HPindex);
    }

    //Realiza un pitido cuando el tiempo de TRT de algún manipulo está por debajo de un cierto tiempo
    if(AppGUIdata.EndTRTbeep && (TICKS_DiffTicks(AppGUIdata.EndTRTbeepTout)>APP_GUI_TRT_END_TRT_BEEP_TOUT))
    {
        BUZZ_Configure(1, 100, PATRO_SO_FINAL_TRT );
        AppGUIdata.EndTRTbeepTout = TICKS_GetTicks();
    }
	
    /* Actualizamos el popUp de tiempo segun este activado o no */
//	AppGUIhandleTimePopUp( (( AppGUIIsPopupDisplayed(PopUpTime) != 0) && (AppGUIisHPconnected( AppGUIdata.timeHdlr.HPindex, &modelHP))), AppGUIdata.timeHdlr.HPindex);

    /* Actualizamos el popUp de RFID segun este activado o no */
    HPcryoGetFromSlot((cPRFslot)APP_GUI_SLOT_DISTRIBUTION[AppGUIdata.RFIDhdlr.HPindex], &HP, &PRF);
    AppGUIhandleRFIDpopUp( (( AppGUIIsPopupDisplayed(PopUpRFID) != 0) && (AppGUIisHPconnected( AppGUIdata.RFIDhdlr.HPindex, &modelHP)) /*&& (HPcryoTrtStatus(HP, PRF) == HP_CRYO_TREATMENT_RUN_WAITING_RFID)*/), AppGUIdata.RFIDhdlr.HPindex); //V7760 comentado el waiting RFID

    /* Actualizamos el popUp de test vacum segun este activado o no */
    AppGUIhandleTstVacPopUp( (( AppGUIIsPopupDisplayed(PopUpTstVac) != 0) && (AppGUIisHPconnected( AppGUIdata.tstVacHdlr.HPindex, &modelHP))), AppGUIdata.tstVacHdlr.HPindex);

    AppGUIhandleTstVacSMALLPopUp( (( AppGUIIsPopupDisplayed(PopUpTstVacSmall) != 0) && (AppGUIisHPconnected( AppGUIdata.tstVacHdlr.HPindex, &modelHP))), AppGUIdata.tstVacHdlr.HPindex);

    /* Actualizamos el popUp de recomendaciónes según esté activado o no*/
    AppGUIhandleRecommendationpopUp( ( AppGUIIsPopupDisplayed(PopUpRecomm) != 0), AppGUIdata.trtZoneHdlr.selTrtDot, AppGUIdata.trtZoneHdlr.selTrtArea);
	
    /* Actualizamos el popUp de Avisos según esté activado o no*/
    AppGUIhandleWarningPopUp( AppGUIIsPopupDisplayed((cAppGUIwidgetIDlist)APP_GUI_AVISOS_POPUP_WIDGET_SCREENS[AppGUIdata.screen]) != 0);
		 
	
    /* Actualizamos la gestión de errores, tal y como esta tiene que ser lo ultimo en actualizarse
     * PDTE LIMPIAR Y MEJORAR */
    AppGUIhandleErrPopUps();
    //MAIN MENU

    /* Actualizamos el selector de zona de tratamiento */
    AppGUIhandleTrtZone();
	
    /* Actualizamos el panel de control */
    for( HPindex=0;HPindex<APP_GUI_MAXNUM_HP;HPindex++)
    {
        if((AppGUIdata.slot[HPindex].CleanUPhdlr.HP_in_cleaning)&(AppGUIisHPconnected( HPindex, &modelHP))){	AppGUIdata.slot[HPindex].isCtrlPnlShow = 1;	}
        if (HPcryoGetFromSlot((cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF)){	AppGUIdata.slot[HPindex].CleanUPhdlr.HP_clean_init_or_end = HP->cleanUpInitOrEnd;	}
        AppGUIhandleCleanUpPopUps( ((AppGUIdata.slot[HPindex].CleanUPhdlr.HP_in_cleaning)&(AppGUIisHPconnected( HPindex, &modelHP))&(AppGUIdata.slot[HPindex].isCtrlPnlShow)), HPindex);
        AppGUIhandleCtrlPanel(AppGUIdata.slot[HPindex].isCtrlPnlShow, HPindex);
    }
	
    /* Para bloquear el boton de idiomas*/
    AppGUIhandleMainMenu(AppGUIdata.mainMenuHdlr.isUp);
}


void AppGUIcalcScrInit( void)
{
    //LDD_RTC_TTime AppGUI_RTC_TIME_and_DATE;//DEBUG
	
    /* Inicializamos las variables de control */
    AppGUIclearData();
	
    AppGUIdata.CalcHandler.CalcCode = 0.0;
    AppGUIdata.CalcHandler.numDigitsIn = 0;
    AppGUIdata.CalcHandler.FillingWater_flag = 0;
    AppGUIdata.CalcHandler.MachineModeChngFlag = 0;		//V7790
	
    /* Asignamos la pantalla actual */
    AppGUIdata.screen = APP_GUI_CALCULATOR_SCREEN;
    wdgWpr.changeScreen(APP_GUI_CALCULATOR_SCREEN);

    // Initialize the calculator value
    wdgWpr.GUIsetNumViewerNum( NumVwrPantallaCalc, AppGUIdata.CalcHandler.CalcCode, 0);
    AppGUIwarningNotification();

    AppGUIhandleWarningPopUp( 0);
	
    /*DEBUG*/
//	AppGUI_RTC_TIME_and_DATE.Second = 54;
//	AppGUI_RTC_TIME_and_DATE.Minute = 32;
//	AppGUI_RTC_TIME_and_DATE.Hour = 13;
//	AppGUI_RTC_TIME_and_DATE.Day = 24;
//	AppGUI_RTC_TIME_and_DATE.Month = 7;
//	AppGUI_RTC_TIME_and_DATE.Year = 2019;
//	AppGUI_RTC_TIME_and_DATE.DayOfWeek = 3;
//
//	RTC_set_time (&AppGUI_RTC_TIME_and_DATE);
    /*DEBUG*/
	
    /* Inicializamos el menu principal a oculto */
    AppGUIhandleMainMenu( 0 );
}
void AppGUIcalcScrUpdate( void)
{
//    LDD_RTC_TTime AppGUI_RTC_TIME_and_DATE;
//    uint32 AppGUI_RTC_time;
//    uint32 AppGUI_RTC_date;
//    stWidget *popUp;
	
//    AppGUIwarningNotification();
//    AppGUIupdateWarningFlags();
	
//    /* Actualizamos el popUp de Avisos según esté activado o no*/
//    popUp = GUIgetWidget( APP_GUI_AVISOS_POPUP_WIDGET_SCREENS[AppGUIdata.screen]);
//    AppGUIhandleWarningPopUp( popUp->enable != 0);
	
	
	
//    if(AppGUIdata.CalcHandler.RTC_time_flag == 1)		//En caso de haberse introducido el código para la lectura del tiempo del RTD
//    {
//        RTC_get_time (&AppGUI_RTC_TIME_and_DATE);		//Se toma el tiempo registrado
		
//        AppGUI_RTC_time = AppGUI_RTC_TIME_and_DATE.Second;							//Se van concatenando los números del tiempo (segundos, minutos y horas) para su representación
//        AppGUI_RTC_time = AppGUI_RTC_time + (AppGUI_RTC_TIME_and_DATE.Minute*100);
//        AppGUI_RTC_time = AppGUI_RTC_time + (AppGUI_RTC_TIME_and_DATE.Hour*10000);
		
//        GUIsetNumViewerNum( NumVwrPantallaCalc, (float)AppGUI_RTC_time, 0);			//Se representa el tiempo en el visor numerico de la calculadora
//    }
//    if(AppGUIdata.CalcHandler.RTC_date_flag == 1)		//En caso de haberse introducido el código para la lectura de la fecha del RTD
//    {
//        RTC_get_time (&AppGUI_RTC_TIME_and_DATE);		//Se toma el tiempo registrado
		
//        AppGUI_RTC_date = AppGUI_RTC_TIME_and_DATE.Year % 100;						//Se van concatenando los números de la fecha (año, mes y día) para su representación
//        AppGUI_RTC_date = AppGUI_RTC_date + (AppGUI_RTC_TIME_and_DATE.Month*100);
//        AppGUI_RTC_date = AppGUI_RTC_date + (AppGUI_RTC_TIME_and_DATE.Day*10000);
		
//        GUIsetNumViewerNum( NumVwrPantallaCalc, (float)AppGUI_RTC_date, 0);			//Se representa la fecha en el visor numerico de la calculadora
//    }
//    if(AppGUIdata.CalcHandler.FillingWater_flag == 1)
//    {
//        /* Abrir electrovalvula */
//        /*if (!EXP_UCgetLevelHighWater()){*/ EXP_UChandleVentEV( 1);/*}*/
		
//        /* Pita cuando se ha llegado a detectar que se ha llenado el deposito hasta arriba */
//        if (EXP_UCgetLevelHighWater())
//        {
//            BUZZ_Configure(1, 100, PATRO_SO_FINAL_TRT);
//            //AppGUIdata.CalcHandler.FillingWater_flag = 0;
			
//            /* Cerrar electrovalvula */
//            /*if( EXP_UChandleVentEV( 0) == SUCCESS){ AppGUIdata.CalcHandler.FillingWater_flag = 0;}*/
//        }
//    }
}

void AppGUIcfgScrInit( void)
{
    /* Inicializamos las variables de control */
    AppGUIclearData();

    /* Asignamos la pantalla actual */
    AppGUIdata.screen = APP_GUI_CONFIGURATION_SCREEN;
    wdgWpr.changeScreen(APP_GUI_CONFIGURATION_SCREEN);

    AppGUIhandleWarningPopUp( 0);
    AppGUIwarningNotification();
	
    AppGUIdata.CfgHandler.FillingWater_flag = 0;
    wdgWpr.GUIsetNumViewerNum( NumVwrModeloMaqCfg, 1234567890.0, 0);
    wdgWpr.GUIsetNumViewerNum( NumVwrVersionSoftwareCfg, APP_SW_VERSION, 3);
    AppGUIdata.CfgHandler.BootAnimationImg = App_GUI_CfgScr_FW_loading_0;
    AppGUIdata.CfgHandler.Boot_animation_tout = 0;
	
    /* Inicializamos el menu principal a oculto */
    AppGUIhandleMainMenu( 0 );
	
    /* Identificamos como ha de estar el boton del visor de resucciones */
    //GUIsetSwitchStatus( SwCfgResuctionViewer, 0/*EXP_UCresuctionsViewer()*/);
	
    /* Identificamos como ha d estar el boton del visor de temperaturas */
#ifdef APP_SW_VER_SHOW_TEMPERATURES
    GUIsetSwitchStatus( SwCfgTemperatureViewer, EXP_UCtempViewer ());
#else
    //GUIsetWidgetEnable(SwCfgTemperatureViewer,0);
    //GUIsetWidgetVisibility(SwCfgTemperatureViewer,0);
#endif
}
void AppGUIcfgScrUpdate( void)
{
//    uint8 i;
//    stWidget *popUp;
		
//    AppGUIwarningNotification();
//    AppGUIupdateWarningFlags();
	
//    /* Actualizamos el popUp de Avisos según esté activado o no*/
//    popUp = GUIgetWidget( APP_GUI_AVISOS_POPUP_WIDGET_SCREENS[AppGUIdata.screen]);
//    AppGUIhandleWarningPopUp( popUp->enable != 0);
	
//    if(AppGUIdata.CfgHandler.BOOT_rqst)
//    {
//        for (i=0;i<APP_GUI_MAIN_MENU_WID_WHEN_SHOW_NUM;i++){		GUIsetWidgetEnable(APP_GUI_MAIN_MENU_WID_WHEN_SHOW[APP_GUI_CONFIGURATION_SCREEN][i],0); }
//        GUIsetWidgetEnable(butCfgScrShowMainMenu,0);
//        GUIsetWidgetEnable(butCfgScrHideMainMenu,0);
//        GUIsetWidgetEnable(butCfgActualizarSoftware,0);
//        GUIsetWidgetEnable(butCfgRecargaCoolant,0);
//        GUIsetWidgetEnable(butCfgCleanUpHP1,0);
//        GUIsetWidgetEnable(butCfgCleanUpHP2,0);
//        GUIsetWidgetEnable(butCfgCleanUpHP3,0);
//        GUIsetWidgetEnable(butCfgCleanUpHP4,0);
//        GUIsetWidgetEnable(butCfgCleanUpRoundHP,0);
		
////		GUIsetWidgetVisibility (imgSoftwareProgressionUpdateBar, 1);
////
////		if (TICKS_DiffTicks(AppGUIdata.CfgHandler.Boot_animation_tout) > 2000)
////		{
////			GUIsetImgViewerImage (imgSoftwareProgressionUpdateBar, APP_GUI_CFG_SCR_LOADING_NEW_FW_ANIMATION[AppGUIdata.CfgHandler.BootAnimationImg]);
////
////			AppGUIdata.CfgHandler.BootAnimationImg++;
////			if(AppGUIdata.CfgHandler.BootAnimationImg > App_GUI_CfgScr_FW_loading_100)		AppGUIdata.CfgHandler.BootAnimationImg = App_GUI_CfgScr_FW_loading_0;
////			AppGUIdata.CfgHandler.Boot_animation_tout = TICKS_GetTicks();
////		}
		
//        switch(BOOT_Motor())
//        {
//            case BootIDLE:
//            case BootERROR:
//            case NOTFOUNDFILE:
//            case BootSUCCESS:			Cpu_SystemReset();	break;
//            case BootRUNNING: 			break;
//            case BootCheckSectorNand:	break;
////				AppGUIdata.CfgHandler.BOOT_rqst = 0;
////				if(AppGUIdata.mainMenuHdlr.isUp)
////				{
////					for (i=0;i<APP_GUI_MAIN_MENU_WID_WHEN_SHOW_NUM;i++){		GUIsetWidgetEnable(APP_GUI_MAIN_MENU_WID_WHEN_SHOW[APP_GUI_CONFIGURATION_SCREEN][i],1); }
////					GUIsetWidgetEnable(butCfgScrHideMainMenu,1);
////				}
////				else {	GUIsetWidgetEnable(butCfgScrShowMainMenu,1);	}
////				GUIsetWidgetEnable(butCfgActualizarSoftware,1);
////				break;
//            default: break;
//        }
//    }
//    else
//    {
//        GUIsetWidgetVisibility (imgSoftwareProgressionUpdateBar, 0);
//    }
	
//    if(AppGUIdata.CfgHandler.FillingWater_flag == 1)
//    {
//        /* Abrir electrovalvula */
//        /*if (!EXP_UCgetLevelHighWater()){*/ EXP_UChandleVentEV( 1);/*}*/
		
//        /* Pita cuando se ha llegado a detectar que se ha llenado el deposito hasta arriba */
//        if (EXP_UCgetLevelHighWater())
//        {
//            BUZZ_Configure(1, 100, PATRO_SO_FINAL_TRT);
//            //AppGUIdata.CalcHandler.FillingWater_flag = 0;
			
//            /* Cerrar electrovalvula */
//            /*if( EXP_UChandleVentEV( 0) == SUCCESS){ AppGUIdata.CalcHandler.FillingWater_flag = 0;}*/
//        }
//    }

//    /* Ajustar el estado del interruptor al valor registrado en memoria */
//    //GUIsetSwitchStatus( SwCfgResuctionViewer, EXP_UCresuctionsViewer());

	
//    /*Incluir la gestión de la limpieza para los distintos aplicadores*/
	
//    /*Incluir la activación/desactivación de la limpieza automática*/
	
}

void AppGUIdataScrInit( void)
{
//    /* Inicializamos las variables de control */
//    AppGUIclearData();
	
//    /* Asignamos la pantalla actual */
//    AppGUIdata.screen = APP_GUI_LANGUAGES_SCREEN;
	
//    AppGUIhandleWarningPopUp( 0);
//    AppGUIwarningNotification();
	
//    /* Ponemos a ON el idioma que esté seleccionado y deshabilitamos el widget */
////	if(EXP_UC_get_Language() != App_GUI_Sin_idioma)
////	{
////		GUIsetSwitchStatus((EXP_UC_get_Language() + APP_GUI_LANG_SW_WIDGET_LANG_LIST[0]), 1);
////		GUIsetWidgetEnable((EXP_UC_get_Language() + APP_GUI_LANG_SW_WIDGET_LANG_LIST[0]), 0);
////	}
	
//    /* Inicializamos el menu principal a oculto */
//    AppGUIhandleMainMenu( 0, AppGUIdata.screen);
}
void AppGUIdataScrUpdate( void)
{
////	uint8 i;		//Variable auxiliar
//    stWidget *popUp;
	
//    AppGUIwarningNotification();
//    AppGUIupdateWarningFlags();
	
//    /* Actualizamos el popUp de Avisos según esté activado o no*/
//    popUp = GUIgetWidget( APP_GUI_AVISOS_POPUP_WIDGET_SCREENS[AppGUIdata.screen]);
//    AppGUIhandleWarningPopUp( popUp->enable != 0);
	
//    /* Todos los demas switches los pasamos a OFF y pasan a habilitados*/
////	for(i = 0; i < App_GUI_Sin_idioma; i++)
////	{
////		GUIsetSwitchStatus((i+APP_GUI_LANG_SW_WIDGET_LANG_LIST[0]), (EXP_UC_get_Language() == i));
////		GUIsetWidgetEnable((i+APP_GUI_LANG_SW_WIDGET_LANG_LIST[0]), (EXP_UC_get_Language() != i));
////	}
}

void AppGUIfat0ScrInit( void)
{
	
    /* Asignamos la pantalla actual */
    AppGUIdata.screen = APP_GUI_FATIGUE_SCREEN;
    wdgWpr.changeScreen(APP_GUI_FATIGUE_SCREEN);
	
// TODO    GUIsetNumViewerNum( NumVwrFatigaTime, 0.0, 2);
// TODO
// TODO    GUIsetNumViewerNum( NumVwrErrFatiga1, 0.0 , 0);
// TODO    GUIsetNumViewerNum( NumVwrErrFatiga2, 0.0 , 0);
// TODO    GUIsetNumViewerNum( NumVwrErrFatiga3, 0.0 , 0);
// TODO    GUIsetNumViewerNum( NumVwrErrFatiga4, 0.0 , 0);
// TODO    GUIsetNumViewerNum( NumVwrErrFatiga5, 0.0 , 0);
// TODO
// TODO    GUIsetImgViewerImage(imgStep1status,c149_ZonaAplicacionManipPuntoSelected);
// TODO    GUIsetImgViewerImage(imgStep2status,c149_ZonaAplicacionManipPuntoSelected);
// TODO    GUIsetImgViewerImage(imgStep3status,c149_ZonaAplicacionManipPuntoSelected);
// TODO    GUIsetImgViewerImage(imgStep4statusHP1,c149_ZonaAplicacionManipPuntoSelected);
// TODO    GUIsetImgViewerImage(imgStep4statusHP2,c149_ZonaAplicacionManipPuntoSelected);
// TODO    GUIsetImgViewerImage(imgStep4statusHP3,c149_ZonaAplicacionManipPuntoSelected);
// TODO    GUIsetImgViewerImage(imgStep4statusHP4,c149_ZonaAplicacionManipPuntoSelected);
// TODO    GUIsetImgViewerImage(imgStep5statusHP1,c149_ZonaAplicacionManipPuntoSelected);
// TODO    GUIsetImgViewerImage(imgStep5statusHP2,c149_ZonaAplicacionManipPuntoSelected);
// TODO    GUIsetImgViewerImage(imgStep5statusHP3,c149_ZonaAplicacionManipPuntoSelected);
// TODO    GUIsetImgViewerImage(imgStep5statusHP4,c149_ZonaAplicacionManipPuntoSelected);
// TODO
// TODO    ERR_clear(Manip1);	ERR_reset_perif(Manip1);
// TODO    ERR_clear(Manip2);	ERR_reset_perif(Manip2);
// TODO    ERR_clear(Manip3);	ERR_reset_perif(Manip3);
// TODO    ERR_clear(Manip4);	ERR_reset_perif(Manip4);
// TODO    ERR_clear(Maq);		ERR_reset_perif(Maq);
	
    AppGUIdata.fatigue_fail = 0;
// TODO    GUIsetSwitchImg( SwFatigueFailBeep, b028_BotonAvisosMarcaAgua, b028_BotonAvisosMarcaAgua, b028_BotonAvisosMarcaAgua, b028_BotonAvisosMarcaAgua);
// TODO    GUIsetWidgetEnable(SwFatigueFailBeep,AppGUIdata.fatigue_fail);
}

void AppGUIfat0ScrUpdate( void)
{
//	uint8 i;	//Vble auxiliar bucles
//	static uint8 err_code[Max_perifs];
//	float Rth, retTemp, retFlow, pumpTemp, envTemp, Vtob, CPI;
//	static float Rth_mem = 0, retTemp_mem = 0, retFlow_mem = 0, pumpTemp_mem = 0, envTemp_mem = 0, Vtob_mem = 0, CPI_mem = 0;
//	float CaudalRetornoHP1, CaudalRetornoHP2, CaudalRetornoHP3, CaudalRetornoHP4;
//	float PresionHP1, PresionHP2, PresionHP3, PresionHP4;
//	static float CaudalRetornoHP1_mem = 0, CaudalRetornoHP2_mem = 0, CaudalRetornoHP3_mem = 0, CaudalRetornoHP4_mem = 0;
//	static float PresionHP1_mem, PresionHP2_mem, PresionHP3_mem, PresionHP4_mem;
//	static cEXP_UCfatigueSteps prevStep = EXP_UC_FATIGUE_CHECK_FILTER;
//	uint32 Fatigue_time;
//	static uint32 time_to_beep = 0;
	
//	//Asignamos valores a las variables
//	EXP_UCfatigaDataUpdate (&Rth, &retTemp, &retFlow, &pumpTemp, &envTemp, &Vtob, &CPI,
//							&CaudalRetornoHP1, &CaudalRetornoHP2, &CaudalRetornoHP3, &CaudalRetornoHP4,
//							&Fatigue_time,
//							&PresionHP1, &PresionHP2, &PresionHP3, &PresionHP4);
	
//	//En el momento en el que cambiamos de paso en la Fatiga realizamos un pitido
//	if(prevStep != EXP_UCfatigaStatus())
//	{
//		prevStep = EXP_UCfatigaStatus();
//		BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
//	}
	
//	/*Gestion del boton de silencio para quitar el pitido tras fallar la fatiga*/
//	GUIsetWidgetEnable(SwFatigueFailBeep,AppGUIdata.fatigue_fail);
//	if(AppGUIdata.fatigue_fail){	GUIsetSwitchImg( SwFatigueFailBeep, b030_BotonAvisosRls, b030_BotonAvisosRls, b029_BotonAvisosPress, b029_BotonAvisosPress);	}
//	else{	GUIsetSwitchImg( SwFatigueFailBeep, b028_BotonAvisosMarcaAgua, b028_BotonAvisosMarcaAgua, b028_BotonAvisosMarcaAgua, b028_BotonAvisosMarcaAgua);	}
	
//	switch (EXP_UCfatigaStatus())
//	{
//		case EXP_UC_FATIGUE_CHECK_FILTER:
//			GUIsetImgViewerImage(imgStep1status,c152_ZonaAplicacionManipPuntoHP2);
//			break;
//		case EXP_UC_FATIGUE_CHECK_SETA:
//			GUIsetImgViewerImage(imgStep1status,c151_ZonaAplicacionManipPuntoHP1);
//			GUIsetImgViewerImage(imgStep2status,c152_ZonaAplicacionManipPuntoHP2);
//			break;
//		case EXP_UC_FATIGUE_CHECK_RFID:
//			GUIsetImgViewerImage(imgStep2status,c151_ZonaAplicacionManipPuntoHP1);
//			GUIsetImgViewerImage(imgStep3status,c152_ZonaAplicacionManipPuntoHP2);
//			break;
//		case EXP_UC_FATIGUE_CHECK_VAC_HP1:
//			GUIsetImgViewerImage(imgStep3status,c151_ZonaAplicacionManipPuntoHP1);
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_4_HP_WIDGETS[(PRF_HW_SLOT1-1)],c152_ZonaAplicacionManipPuntoHP2);
//			break;
//		case EXP_UC_FATIGUE_CHECK_VAC_HP2:
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_4_HP_WIDGETS[(PRF_HW_SLOT1-1)],c151_ZonaAplicacionManipPuntoHP1);
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_4_HP_WIDGETS[(PRF_HW_SLOT2-1)],c152_ZonaAplicacionManipPuntoHP2);
//			break;
//		case EXP_UC_FATIGUE_CHECK_VAC_HP3:
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_4_HP_WIDGETS[(PRF_HW_SLOT2-1)],c151_ZonaAplicacionManipPuntoHP1);
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_4_HP_WIDGETS[(PRF_HW_SLOT3-1)],c152_ZonaAplicacionManipPuntoHP2);
//			break;
//		case EXP_UC_FATIGUE_CHECK_VAC_HP4:
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_4_HP_WIDGETS[(PRF_HW_SLOT3-1)],c151_ZonaAplicacionManipPuntoHP1);
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_4_HP_WIDGETS[(PRF_HW_SLOT4-1)],c152_ZonaAplicacionManipPuntoHP2);
//			break;
//		case EXP_UC_FATIGUE_TRT_VAC_HP1:
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_4_HP_WIDGETS[(PRF_HW_SLOT4-1)],c151_ZonaAplicacionManipPuntoHP1);
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_5_HP_WIDGETS[(PRF_HW_SLOT1-1)],c152_ZonaAplicacionManipPuntoHP2);
//			break;
//		case EXP_UC_FATIGUE_TRT_VAC_HP2:
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_5_HP_WIDGETS[(PRF_HW_SLOT1-1)],c151_ZonaAplicacionManipPuntoHP1);
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_5_HP_WIDGETS[(PRF_HW_SLOT2-1)],c152_ZonaAplicacionManipPuntoHP2);
//			break;
//		case EXP_UC_FATIGUE_TRT_VAC_HP3:
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_5_HP_WIDGETS[(PRF_HW_SLOT2-1)],c151_ZonaAplicacionManipPuntoHP1);
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_5_HP_WIDGETS[(PRF_HW_SLOT3-1)],c152_ZonaAplicacionManipPuntoHP2);
//			break;
//		case EXP_UC_FATIGUE_TRT_VAC_HP4:
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_5_HP_WIDGETS[(PRF_HW_SLOT3-1)],c151_ZonaAplicacionManipPuntoHP1);
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_5_HP_WIDGETS[(PRF_HW_SLOT4-1)],c152_ZonaAplicacionManipPuntoHP2);
//			for(i=Manip1;i<Max_perifs;i++){	err_code[i] = 0;	}
//			break;
//		case EXP_UC_FATIGUE_TST_PELTIERS:
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_5_HP_WIDGETS[(PRF_HW_SLOT1-1)],c151_ZonaAplicacionManipPuntoHP1);
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_5_HP_WIDGETS[(PRF_HW_SLOT2-1)],c151_ZonaAplicacionManipPuntoHP1);
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_5_HP_WIDGETS[(PRF_HW_SLOT3-1)],c151_ZonaAplicacionManipPuntoHP1);
//			GUIsetImgViewerImage(APP_GUI_FAT_STATUS_5_HP_WIDGETS[(PRF_HW_SLOT4-1)],c151_ZonaAplicacionManipPuntoHP1);
			
//			GUIsetNumViewerNum( NumVwrFatigaTime, AppGUIsecondsToClock((EXPdata.UC.FatigaTime/1000)), 2);			//Tiempo que lleva el tratamiento de test
			
//			/*Recogemos los valores que tenemos entre el 85-90% del tratamiento de test*/		/*QUIZAS DEBA IR EN EL MODULO DE LA EXPANSORA TODO LO DE ALMACENAR LOS DATOS PARA PRESENTARLOS AL FINAL DE LA FATIGA*/
//			if((Fatigue_time > (0.85*EXP_UC_FATIGA_TRT_TEST_TIME)) && (Fatigue_time < (0.9*EXP_UC_FATIGA_TRT_TEST_TIME)))
//			{
//				retTemp_mem = retTemp; retFlow_mem = retFlow; pumpTemp_mem = pumpTemp; envTemp_mem = envTemp; Vtob_mem = Vtob; Rth_mem = Rth; CPI_mem = CPI;
//				CaudalRetornoHP1_mem = CaudalRetornoHP1; CaudalRetornoHP2_mem = CaudalRetornoHP2; CaudalRetornoHP3_mem = CaudalRetornoHP3; CaudalRetornoHP4_mem = CaudalRetornoHP4;
//				PresionHP1_mem = PresionHP1; PresionHP2_mem = PresionHP2; PresionHP3_mem = PresionHP3; PresionHP4_mem = PresionHP4;
//			}
//			break;
//		case EXP_UC_FATIGUE_DONE:
//			/*Una vez acabado el test del tratamiento devolvemos por pantalla los valores recogidos entre el 85-90% del tratamiento*/
//			retTemp = retTemp_mem;	retFlow = retFlow_mem;	pumpTemp = pumpTemp_mem;	envTemp = envTemp_mem;	Vtob = Vtob_mem;	CPI = CPI_mem;	Rth = Rth_mem;
//			CaudalRetornoHP1 = CaudalRetornoHP1_mem;	CaudalRetornoHP2 = CaudalRetornoHP2_mem;	CaudalRetornoHP3 = CaudalRetornoHP3_mem;	CaudalRetornoHP4 = CaudalRetornoHP4_mem;
//			PresionHP1 = PresionHP1_mem;	PresionHP2 = PresionHP2_mem;	PresionHP3 = PresionHP3_mem;	PresionHP4 = PresionHP4_mem;

//			/*Si se ha finalizado con fallo cada segundo se pita*/
//			if((AppGUIdata.fatigue_fail) && (TICKS_DiffTicks(time_to_beep)>APP_GUI_FATIGUE_5_SEC_MILISEC)){	BUZZ_Configure(1, 100, PATRO_SO_ERROR );	time_to_beep = TICKS_GetTicks();	}
//			break;
//		case EXP_UC_FATIGUE_FAIL:
//			/*Tomamos los valores que se tenían en el momento del fallo de la fatiga*/
//			retTemp_mem = EXP_UCfatigaGetErrorValues(FAT_VAL_retTemp); retFlow_mem = EXP_UCfatigaGetErrorValues(FAT_VAL_retFlow); pumpTemp_mem = EXP_UCfatigaGetErrorValues(FAT_VAL_pumpTemp);
//			envTemp_mem = EXP_UCfatigaGetErrorValues(FAT_VAL_envTemp); Vtob_mem = EXP_UCfatigaGetErrorValues(FAT_VAL_Vtob); Rth_mem = EXP_UCfatigaGetErrorValues(FAT_VAL_Rth);
//			CPI_mem = EXP_UCfatigaGetErrorValues(FAT_VAL_CPI);
//			CaudalRetornoHP1_mem = EXP_UCfatigaGetErrorValues(FAT_VAL_CaudalHP1); CaudalRetornoHP2_mem = EXP_UCfatigaGetErrorValues(FAT_VAL_CaudalHP2);
//			CaudalRetornoHP3_mem = EXP_UCfatigaGetErrorValues(FAT_VAL_CaudalHP3); CaudalRetornoHP4_mem = EXP_UCfatigaGetErrorValues(FAT_VAL_CaudalHP4);
//			PresionHP1_mem = EXP_UCfatigaGetErrorValues(FAT_VAL_PresionHP1); PresionHP2_mem = EXP_UCfatigaGetErrorValues(FAT_VAL_PresionHP2);
//			PresionHP3_mem = EXP_UCfatigaGetErrorValues(FAT_VAL_PresionHP3); PresionHP4_mem = EXP_UCfatigaGetErrorValues(FAT_VAL_PresionHP4);
			
//			/*Levantamos el flag que sirve para lanzar el pitido de fallo*/
//			AppGUIdata.fatigue_fail = 1;
//			break;
//		default: break;
//	}
	
//	//Valores ofrecidos por pantalla, gestión del valor y el color del fondo en caso de haber finalizado la fatiga
//	GUIsetNumViewerNum( NumVwrTempAmb, envTemp, 1);			GUIsetImgNumVwr(NumVwrTempAmb, APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_envTemp, envTemp)]);
//	GUIsetNumViewerNum( NumVwrTempBomba, pumpTemp, 1);		GUIsetImgNumVwr(NumVwrTempBomba, APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_pumpTemp, pumpTemp)]);
//	GUIsetNumViewerNum( NumVwrTempRetorno, retTemp, 1);		GUIsetImgNumVwr(NumVwrTempRetorno, APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_retTemp, retTemp)]);
//	GUIsetNumViewerNum( NumVwrCaudalRetorno, retFlow, 1);	GUIsetImgNumVwr(NumVwrCaudalRetorno, APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_retFlow, retFlow)]);
//	GUIsetNumViewerNum( NumVwrVtobera, Vtob, 0);			GUIsetImgNumVwr(NumVwrVtobera, APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_Vtob, Vtob)]);
//	GUIsetNumViewerNum( NumVwrRth, Rth, 3);					GUIsetImgNumVwr(NumVwrRth, APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_Rth, Rth)]);
//	GUIsetNumViewerNum( NumVwrCPI, CPI, 1);					GUIsetImgNumVwr(NumVwrCPI, APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_CPI, CPI)]);
//	GUIsetNumViewerNum( NumVwrCaudalRetornoHP1, CaudalRetornoHP1 , 2);		GUIsetImgNumVwr(NumVwrCaudalRetornoHP1, APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_CaudalHP1, CaudalRetornoHP1)]);
//	GUIsetNumViewerNum( NumVwrCaudalRetornoHP2, CaudalRetornoHP2 , 2);		GUIsetImgNumVwr(NumVwrCaudalRetornoHP2, APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_CaudalHP2, CaudalRetornoHP2)]);
//	GUIsetNumViewerNum( NumVwrCaudalRetornoHP3, CaudalRetornoHP3 , 2);		GUIsetImgNumVwr(NumVwrCaudalRetornoHP3, APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_CaudalHP3, CaudalRetornoHP3)]);
//	GUIsetNumViewerNum( NumVwrCaudalRetornoHP4, CaudalRetornoHP4 , 2);		GUIsetImgNumVwr(NumVwrCaudalRetornoHP4, APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_CaudalHP4, CaudalRetornoHP4)]);
//	GUIsetNumViewerNum( NumVwrVacuumHP1, PresionHP1, 1);		GUIsetImgNumVwr(NumVwrVacuumHP1, APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_PresionHP1, PresionHP1)]);
//	GUIsetNumViewerNum( NumVwrVacuumHP2, PresionHP2, 1);		GUIsetImgNumVwr(NumVwrVacuumHP2, APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_PresionHP2, PresionHP2)]);
//	GUIsetNumViewerNum( NumVwrVacuumHP3, PresionHP3, 1);		GUIsetImgNumVwr(NumVwrVacuumHP3, APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_PresionHP3, PresionHP3)]);
//	GUIsetNumViewerNum( NumVwrVacuumHP4, PresionHP4, 1);		GUIsetImgNumVwr(NumVwrVacuumHP4, APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_PresionHP4, PresionHP4)]);
	
//	/*Se revisan los fallos posibles en los distintos manipulos y en la maquina*/
//	for(i=Manip1;i<=Maq;i++)
//	{
//		if(err_code[i] == 0)
//		{
//			err_code[i] = EXP_UCfatigaErrUpdate(i);
//			if (err_code[i] != 0){	GUIsetNumViewerNum( NumVwrErrFatiga1+(i-1), err_code[i] , 0);	/*GUIsetImgNumVwr(NumVwrErrFatiga1+(i-1), c463_FondoNumVwrErrorRojo);*/	}
//		}
//		GUIsetImgNumVwr(NumVwrErrFatiga1+(i-1), APP_GUI_FAT_VALUE_STATUS[EXP_UCfatigaCheckValue(FAT_VAL_ErrorHP1+(i-1), (float)err_code[i])]);
//	}
}

void AppGUIsatScrInit( void)
{
    uint8 i; //Variable auxiliar para bucles
	
    /* Asignamos la pantalla actual */
    AppGUIdata.screen = APP_GUI_SAT_SCREEN;
    wdgWpr.changeScreen(APP_GUI_SAT_SCREEN);
	
    for (i=0;i<APP_GUI_MAXNUM_HP;i++)
    {
        AppGUIdata.SATHandler.FrioSwitch[i] = 0;
        AppGUIdata.SATHandler.VacuumSwitch[i] = 0;
        AppGUIdata.SATHandler.TestLedSwitch[i] = 0;
        AppGUIdata.SATHandler.TestLedRGBSwitch[i] = 0;
    }
	
    AppGUIdata.SATHandler.RFID_FWversion = RFID_GetFWversion();
	
// TODO    GUIdisablePopUp( PopupErrorSAT);
	
// TODO    GUIsetSwitchStatus(SwVacuum,0);
// TODO    GUIsetSwitchStatus(SwFrio,0);
// TODO    GUIsetSwitchStatus(SwTestLed,0);
// TODO    GUIsetSwitchStatus(SwTestLedRGB,0);
    AppGUIdata.SATHandler.RFIDSwitch = 0;
    AppGUIdata.SATHandler.Page = HP1_Page;
    AppGUIdata.SATHandler.PageNum = AppGUIdata.SATHandler.Page + APP_GUI_SAT_SCREEN_NUMVWR_MAX_PAGES;
// TODO    GUIsetWidgetEnable(butPrevPagSATscreen,0);
// TODO    GUIsetNumViewerNum( NumVwrPaginaSATscreen, AppGUIdata.SATHandler.PageNum, 1);
}

void AppGUIsatScrUpdate( void)
{
//	uint8 i;	//Variable auxiliar para bucles
	
//	/*Variables para gestion de los valores a mostrar*/
//	uint8 HPconnected =0;	//Flag de HP conectado
//	uint8 HPindex=0;		//Indice del manipulo de la página donde nos encontramos
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	/*Variables para RFID*/
//	static char Label_requested[2];
//	static char Label_Read[2];
//	K70_RFID_CPU_ERR_tt RFID_module_Err;
//	returnstatus_t rfid_read_status;
//	//uint32 err_code;
//	//stWidget *popUp;

//	//Pone el número correspondiente a la página de SAT donde nos encontramos
//	GUIsetNumViewerNum( NumVwrPaginaSATscreen, AppGUIdata.SATHandler.PageNum, 1);
	
//	//Habilita/deshabilita los botones de siguiente o anterior página
//	if(AppGUIdata.SATHandler.Page == HP1_Page)	GUIsetWidgetEnable(butPrevPagSATscreen,0);
//	else	GUIsetWidgetEnable(butPrevPagSATscreen,1);
	
//	if(AppGUIdata.SATHandler.Page == MachineDefPage)	GUIsetWidgetEnable(butNextPagSATscreen,0);
//	else	GUIsetWidgetEnable(butNextPagSATscreen,1);
	
//	//Gestion de la lectura RFID para la comprobación del correcto funcionamiento del modulo
//	if (AppGUIdata.SATHandler.RFIDSwitch)
//	{
//		Label_requested[0] = 'D';
//		Label_requested[1] = 'M';
//		rfid_read_status = RFID_read_label(Label_requested, Label_Read, RFID_NOT_ERASE_LABEL, &RFID_module_Err);
//		switch (rfid_read_status)		//Gestion de los estados del proceso de la lectura
//		{
//			case BLOCKING:
//			case IDLE:
//			case RUNNING:	break;
//			case ERROR:		if (RFID_module_Err == K70_RFID_CPU_ERR_LABEL_INVALID){BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );}	break;
//			case SUCCESS:	BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );	break;
//			default: break;
//		}
//	}
	
//	//Gestion de botones y datos a mostrar en función de la página donde nos encontremos
//	switch(AppGUIdata.SATHandler.Page)
//	{
//		case HP1_Page:
//			HPindex = APP_GUI_HP1_ID;
//			if (HPcryoGetFromSlot(APP_GUI_HP1_ID+1, &HP, &PRF)){	HPconnected = 1;	}
//			else{	HPconnected = 0;	}
//			break;
//		case HP2_Page:
//			HPindex = APP_GUI_HP2_ID;
//			if (HPcryoGetFromSlot(APP_GUI_HP2_ID+1, &HP, &PRF)){	HPconnected = 1;	}
//			else{	HPconnected = 0;	}
//			break;
//		case HP3_Page:
//			HPindex = APP_GUI_HP3_ID;
//			if (HPcryoGetFromSlot(APP_GUI_HP3_ID+1, &HP, &PRF)){	HPconnected = 1;	}
//			else{	HPconnected = 0;	}
//			break;
//		case HP4_Page:
//			HPindex = APP_GUI_HP4_ID;
//			if (HPcryoGetFromSlot(APP_GUI_HP4_ID+1, &HP, &PRF)){	HPconnected = 1;	}
//			else{	HPconnected = 0;	}
//			break;
//		case MachinePage:
//			GUIsetWidgetEnable(SwVacuum,0);		GUIsetSwitchStatus(SwVacuum,0);
//			GUIsetWidgetEnable(SwFrio,0);		GUIsetSwitchStatus(SwFrio,0);
//			GUIsetWidgetEnable(SwTestLed,0);	GUIsetSwitchStatus(SwTestLed,0);
//			GUIsetWidgetEnable(SwTestLedRGB,0);	GUIsetSwitchStatus(SwTestLedRGB,0);
			
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[0], EXPdata.UC.commonData1.fields.returnTemp, 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[1], EXPdata.UC.commonData1.fields.pumpOutTemp, 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[2], EXPdata.UC.commonData2.fields.consRadFan, 2);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[3], EXPdata.UC.commonData2.fields.consWaterPump, 2);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[4], EXPdata.UC.commonData1.fields.status.bits.alarma_gral, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[5], EXPdata.UC.commonData1.fields.status.bits.puerta_tobera, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[6], EXPdata.UC.commonData1.fields.envTemp, 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[7], EXPdata.UC.commonData1.fields.waterPressure, 2);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[8], EXPdata.UC.commonData1.fields.radOutTemp, 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[9], EXPdata.UC.commonData1.fields.returnFlow, 2);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[10], EXPdata.UC.commonData2.fields.enabled485devices, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[11], EXPdata.UC.commonData2.fields.temporaryEnabledPerif, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[12], EXPdata.UC.PCBlvlDetector.vars.fields.level.byte, 0);
//			//GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[13], EXPdata.UC.radFanVoltage, 1); //AppGPRS_get_GPRS_board_detected
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[13], AppGPRS_get_GPRS_board_detected(), 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[14], EXPdata.UC.CPI, 2);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[15], MemoryMap.var.var_flash.TreatmentCount, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[16], EXP_UCoscTempStatus(), 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[17], EXP_UCreuseLabelModeStatus(), 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[18], EXP_UCtempSlopeStatus(), 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[19], EXP_UCtempSecureStatus(), 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[20], EXP_UCerrSecureStatus(), 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[21], EXP_UCerrDeltaTempSecureStatus(), 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[22], EXP_UC_RecLOG_Status(), 0);		/*V7790 - LOGs*/
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[23], (MemoryMap.var.var_flash.FiFoNAND[0].u32NumBytes/2048), 0);		/*V7790 - LOGs*/
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[24], (MemoryMap.var.var_flash.FiFoNAND[1].u32NumBytes/2048), 0);		/*V7790 - LOGs*/
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[25], AppGPRS_GetMCCnum(0), 0);										/*V7790 - MOVILE COUNTRY CODE */
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[26], Label_Read[0], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[27], Label_Read[1], 0);
//			break;
//		case HP_Commands_Page:
//			GUIsetWidgetEnable(SwVacuum,0);		GUIsetSwitchStatus(SwVacuum,0);
//			GUIsetWidgetEnable(SwFrio,0);		GUIsetSwitchStatus(SwFrio,0);
//			GUIsetWidgetEnable(SwTestLed,0);	GUIsetSwitchStatus(SwTestLed,0);
//			GUIsetWidgetEnable(SwTestLedRGB,0);	GUIsetSwitchStatus(SwTestLedRGB,0);

//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[0], EXPdata.perif[1].data.fields.model, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[1], EXPdata.perif[1].data.fields.version, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[2], EXPdata.perif[1].data.fields.serialNum[0], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[3], EXPdata.perif[1].data.fields.serialNum[1], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[4], EXPdata.perif[1].data.fields.serialNum[2], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[5], 0, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[6], 0, 0);

//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[7], EXPdata.perif[2].data.fields.model, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[8], EXPdata.perif[2].data.fields.version, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[9], EXPdata.perif[2].data.fields.serialNum[0], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[10], EXPdata.perif[2].data.fields.serialNum[1], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[11], EXPdata.perif[2].data.fields.serialNum[2], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[12], 0, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[13], 0, 0);

//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[14], EXPdata.perif[3].data.fields.model, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[15], EXPdata.perif[3].data.fields.version, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[16], EXPdata.perif[3].data.fields.serialNum[0], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[17], EXPdata.perif[3].data.fields.serialNum[1], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[18], EXPdata.perif[3].data.fields.serialNum[2], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[19], 0, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[20], 0, 0);

//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[21], EXPdata.perif[4].data.fields.model, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[22], EXPdata.perif[4].data.fields.version, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[23], EXPdata.perif[4].data.fields.serialNum[0], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[24], EXPdata.perif[4].data.fields.serialNum[1], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[25], EXPdata.perif[4].data.fields.serialNum[2], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[26], 0, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[27], 0, 0);

//			break;
//		case MachineDefPage:
//			GUIsetWidgetEnable(SwVacuum,0);		GUIsetSwitchStatus(SwVacuum,0);
//			GUIsetWidgetEnable(SwFrio,0);		GUIsetSwitchStatus(SwFrio,0);
//			GUIsetWidgetEnable(SwTestLed,0);	GUIsetSwitchStatus(SwTestLed,0);
//			GUIsetWidgetEnable(SwTestLedRGB,0);	GUIsetSwitchStatus(SwTestLedRGB,0);
			
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[0], EXPdata.header.fields.board_definition.u8FWVers, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[1], EXPdata.UC.PCBlvlDetector.hdr.fields.board_definition.u8FWVers, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[2], EXPdata.UC.PCBpwrSupply[0].hdr.fields.board_definition.u8FWVers, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[3], EXPdata.UC.PCBpwrSupply[1].hdr.fields.board_definition.u8FWVers, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[4], EXPdata.UC.PCBcomplement[0].hdr.fields.board_definition.u8FWVers, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[5], EXPdata.UC.PCBcomplement[1].hdr.fields.board_definition.u8FWVers, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[6], EXPdata.UC.PCBcomplement[2].hdr.fields.board_definition.u8FWVers, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[7], EXPdata.UC.PCBcomplement[3].hdr.fields.board_definition.u8FWVers, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[8], EXPdata.UC.PCBcomplement[4].hdr.fields.board_definition.u8FWVers, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[9], EXPdata.UC.PCBcomplement[5].hdr.fields.board_definition.u8FWVers, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[10], EXPdata.UC.PCBcomplement[6].hdr.fields.board_definition.u8FWVers, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[11], EXPdata.UC.PCBcomplement[7].hdr.fields.board_definition.u8FWVers, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[12], EXPdata.UC.PCBcomplement[8].hdr.fields.board_definition.u8FWVers, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[13], EXPdata.UC.PCBcomplement[9].hdr.fields.board_definition.u8FWVers, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[14], AppGUIdata.SATHandler.RFID_FWversion, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[15], AppGUIdata.WiFiMac[0], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[16], AppGUIdata.WiFiMac[1], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[17], AppGUIdata.WiFiMac[2], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[18], AppGUIdata.WiFiMac[3], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[19], AppGUIdata.WiFiMac[4], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[20], AppGUIdata.WiFiMac[5], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[21], 0, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[22], 0, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[23], 0, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[24], 0, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[25], 0, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[26], 0, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[27], 0, 0);
//			break;
//		default:
//			break;
//	}
	
//	if ((AppGUIdata.SATHandler.Page == HP1_Page)||
//		(AppGUIdata.SATHandler.Page == HP2_Page)||
//		(AppGUIdata.SATHandler.Page == HP3_Page)||
//		(AppGUIdata.SATHandler.Page == HP4_Page))
//	{
//		if (HPconnected)
//		{
//			GUIsetWidgetEnable(SwVacuum,1);
//			GUIsetWidgetEnable(SwFrio,1);
//			GUIsetWidgetEnable(SwTestLed,1);
//			GUIsetWidgetEnable(SwTestLedRGB,1);
			
//			/* Test del LED de la plica */
//			if(HPcryoIsAutoModeAvaible(HP, PRF))
//			{
//				GUIsetWidgetEnable(SwTestLed,1);
//				if (AppGUIdata.SATHandler.TestLedSwitch[HPindex])
//				{
//					HP->frames.mainIn.data.enable_plica = 1;
//					HPcryoSATbodyFillSensorTestStart( HP, PRF);
//					GUIsetWidgetVisibility(imgTestLedStatus, 1);
//					if( HPcryoSATbodyFillSensorIsDetecting(HP, PRF)){	GUIsetImgViewerImage(imgTestLedStatus, c453_MenuAlarmaOK_MarcaAgua);	}
//					else{	GUIsetImgViewerImage(imgTestLedStatus, c455_MenuAlarmaNO_MarcaAgua);	}
//				}
//				else{	HP->frames.mainIn.data.enable_plica = 0;	GUIsetWidgetVisibility(imgTestLedStatus, 0);	HPcryoSATbodyFillSensorTestStop( HP, PRF);	}
//			}
//			else{	GUIsetWidgetEnable(SwTestLed,0);	GUIsetWidgetVisibility(imgTestLedStatus, 0);}
		
//			HPcryoGetBit51 (HP, PRF);
			
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[0], HP->frames.mainOut.data.estado, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[1], PRF->common->data.fields.model, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[2], PRF->IDperifHW, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[3], ((PRF->common->isEnabled<<2)+(PRF->common->isInit<<1)+(PRF->common->isSPIok)), 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[4], HP->frames.dbgOut.data.NivelPlica, 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[5], EXPdata.UC.commonData2.fields.vacumRetrysCnt[HPindex], 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[6], HP->frames.Define_Out.data.ptu8DatosVerificacion[0], 0);
			
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[7], HP->frames.mainIn.data.fConsignaVacum, 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[8], EXPdata.UC.handPieceData[HPindex].vars.fields.PS1voltagePerCent, 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[9], HP->frames.dbgOut.data.MedidasTemperatura[0], 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[10], HP->frames.dbgOut.data.MedidasTemperatura[1], 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[11], HP->frames.dbgOut.data.MedidasTemperatura[2], 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[12], HP->frames.dbgOut.data.MedidasTemperatura[3], 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[13], HP->frames.dbgOut.data.MedidasTemperatura[4], 1);
						
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[14], HP->frames.mainOut.data.presionVaccum, 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[15], EXPdata.UC.handPieceData[HPindex].vars.fields.PS2voltagePerCent, 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[16], HP->frames.dbgOut.data.MedidasTemperatura[5], 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[17], HP->frames.dbgOut.data.MedidasTemperatura[6], 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[18], HP->frames.dbgOut.data.MedidasTemperatura[7], 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[19], HP->frames.dbgOut.data.MedidasTemperatura[8], 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[20], EXPdata.UC.handPieceData[HPindex].sensors.fields.returnTemp, 1);
			
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[21], HP->frames.mainOut.data.avisos.u16Avisos, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[22], HP->frames.dbgOut.data.warnings.u16Warnings, 0);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[23], HP->frames.dbgOut.data.Calibraciones[0], 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[24], HP->frames.dbgOut.data.Calibraciones[1], 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[25], HP->frames.dbgOut.data.Calibraciones[2], 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[26], EXPdata.UC.handPieceData[HPindex].sensors.fields.returnFlow, 1);
//			GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[27], EXPdata.UC.handPieceData[HPindex].vars.fields.radPerformance, 1);
//		}
//		else
//		{
//			GUIsetWidgetEnable(SwVacuum,0);		GUIsetSwitchStatus(SwVacuum,0);
//			GUIsetWidgetEnable(SwFrio,0);		GUIsetSwitchStatus(SwFrio,0);
//			GUIsetWidgetEnable(SwTestLed,0);	GUIsetSwitchStatus(SwTestLed,0);
//			GUIsetWidgetEnable(SwTestLedRGB,0);	GUIsetSwitchStatus(SwTestLedRGB,0);
//			GUIsetWidgetVisibility(imgTestLedStatus, 0);
			
//			for (i=0;i<APP_GUI_SAT_MAX_NUMVWR;i++)	GUIsetNumViewerNum( APP_GUI_SAT_NUMVWR_WIDGET_LIST[i], 0, 0);
//		}
//	}

//	/*	Gestion de Popup de errores de la pantalla de SAT	*/
////	for(i= Manip1; i<Max_perifs; i++)
////	{
////		err_code = EXP_UCerroresSAT(i);
////		if(err_code!=0)
////		{
////			popUp = GUIgetWidget( PopupErrorSAT);
////			if( popUp->enable == 0){ BUZZ_Configure(1, 100, PATRO_SO_ERROR );	}
////			GUIactivePopUp( PopupErrorSAT);
////			GUIsetNumViewerNum(APP_GUI_SAT_ERRORES_NUMVWR_LIST[i-1], err_code, 0);
////		}
////	}
	
//	/*Activar estados de vacuum o frio de cada manipulo*/
//	for (i=0;i<APP_GUI_MAXNUM_HP;i++)
//	{
//		if(HPcryoGetFromSlot(i+1, &HP, &PRF))
//		{
//			if (AppGUIdata.SATHandler.VacuumSwitch[i]){ HPcryoSATvacumTestStart(HP, PRF);}else{ HPcryoSATvacumTestStop(HP, PRF);}
//			if (AppGUIdata.SATHandler.FrioSwitch[i]){ HPcryoSATcoolingTestStart(HP, PRF);}else{ HPcryoSATcoolingTestStop(HP, PRF);}
//			if (AppGUIdata.SATHandler.TestLedRGBSwitch[i]){ HPcryoSAT_RGBtestStart( HP, PRF);}else{ HPcryoSAT_RGBtestStop( HP, PRF);}
//		}
//	}
}

void AppGUIsetHPstatusFlags( cAppGUIstatusFlagshdlr RFID, cAppGUIstatusFlagshdlr button,
                             cAppGUIstatusFlagshdlr vacum, cAppGUIstatusFlagshdlr cooling,
                             uint8 HPindex)
{
//	uint8 i;
//	static uint8 blink = 0;
//	static uint32 timeBlink = 0;
//	cAppGUIstatusFlagshdlr flgs[APP_GUI_MAX_BLINK_INDICATORS] = { RFID, button, vacum, cooling};
	
//	/* Comprobamos el temporizado del parpadeo */
//	if( TICKS_DiffTicks( timeBlink) > APP_GUI_INDICATORTIME_REF)
//	{
//		timeBlink = TICKS_GetTicks(); blink = !blink;
//	}
	
//	/* Activación de flags */
//	for( i = 0; i < APP_GUI_MAX_BLINK_INDICATORS; i++)
//	{
//		if( ( blink && flgs[i] == APP_GUI_FLG_BLINK) || flgs[i] == APP_GUI_FLG_FIX)
//		{ AppGUIdata.slot[HPindex].statusFlagsOnOff[i] = 1;}
//		else
//		{ AppGUIdata.slot[HPindex].statusFlagsOnOff[i] = 0;}
//	}
}

uint8 AppGUIIsPopupDisplayed( const cAppGUIwidgetIDlist widgetId )
{
    // Look for the popup to get its state
    for ( int i=0; i < APP_GUI_POPUP_DISPLAYED_MAP_NUM; i++ )
    {
        if ( APP_GUI_POPUP_DISPLAYED_MAP[i].id == widgetId )
        {
            return APP_GUI_POPUP_DISPLAYED_MAP[i].displayed;
        }
    }

    return 0;
}

uint8 AppGUIisPopUpActive( void)
{
    uint8 i;
	
    /* Buscamos si algún popUp esta activo */
    for( i = 0; i < APP_GUI_TRT_SCR_NUM_POPUPS; i++)
    {
        if( AppGUIIsPopupDisplayed((cAppGUIwidgetIDlist)APP_GUI_TRT_SCR_POPUP_WIDGET_LIST[i]) != 0){ return 1;}
    }
	
    /* Si llegamos aqui no hay ningun popUp activo */
    return 0;
}

uint8 AppGUIisRecommPopUpActive (void)		//Comprueba si el PopUp de recomendaciones está activo
{
    return AppGUIIsPopupDisplayed(PopUpRecomm);
}

uint8 AppGUIisTimePopUpActive (void)		//Comprueba si el PopUp de tiempo está activo
{
    return AppGUIIsPopupDisplayed(PopUpTime);
}

uint8 AppGUIisVacPopUpActive (void)	//Comprueba si el PopUp de Vacc pequeño está activo
{
    return AppGUIIsPopupDisplayed(PopUpTstVac);
}

uint8 AppGUIisVacSmallPopUpActive (void)	//Comprueba si el PopUp de Vacc pequeño está activo
{
    return AppGUIIsPopupDisplayed(PopUpTstVacSmall);
}

uint8 AppGUIisRFIDPopUpActive (void)		//Comprueba si el PopUp de RFID está activo
{
    return AppGUIIsPopupDisplayed(PopUpRFID);
}

uint8 AppGUIisCleanUpPopUpActive( uint8 HPindex)
{
//	if (AppGUIdata.slot[HPindex].CleanUPhdlr.HP_in_cleaning)	return 1;
//	//Si llega hasta aquí sigifica que el manipulo no está limpiandose
    return 0;
}
uint8 AppGUIisErrorPopUpActive( uint8 HPindex)
{
    uint8 errMsg, wrnMsg;
    uint32 errCode, wrnCode;
    uint8 isErrUp, dev;
    dev = 1;
	
//	switch(HPindex)
//	{
//		case 0: dev = Manip1;	break;
//		case 1: dev = Manip3;	break;
//		case 2: dev = Manip2;	break;
//		case 3: dev = Manip4;	break;
//		default:	break;
//	}
	
//	if (ERR_interface_msg( Maq, &errCode, &errMsg, &wrnCode, &wrnMsg) == 1)
//	{
//		isErrUp = !(ERR_interface_msg( dev, &errCode, &errMsg, &wrnCode, &wrnMsg));
//	}
//	else{return 1;}
	
    return isErrUp; //PDTE
}

uint8 AppGUIisWarningPopUpActive (void)		//Comprueba si el PopUp de avisos está activo
{
//	stWidget *popUp;
	
//	popUp = GUIgetWidget( PopupTrtScrAvisos);
//	if( popUp->enable != 0){ return 1;}
	
    return 0;
}

void AppGUIpanelCtrlColourBlink(void)
{
    static uint8 ColourBlink = 0;
    static uint32 ColourBlinkTime = 0;
    uint8 HPindex, model;
	
    for(HPindex = 0; HPindex < APP_GUI_MAXNUM_HP; HPindex++)
    {
        if (TICKS_DiffTicks(ColourBlinkTime)>APP_GUI_MAX_TIME_BLINK_HP_CTRL_PANEL)
        {
            ColourBlink = !ColourBlink;
            ColourBlinkTime = TICKS_GetTicks();
        }
		
        if( AppGUIdata.slot[HPindex].selTrtArea == AppGUIfullBodyNO_AREA &&
            AppGUIdata.slot[HPindex].selTrtDot == APP_GUI_NO_TRT_DOT_SELECTED &&
            AppGUIdata.trtZoneHdlr.selTrtArea != AppGUIfullBodyNO_AREA &&
            AppGUIdata.trtZoneHdlr.selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED &&
            AppGUIisHPconnected( HPindex, (cHPcryoModels *)&model) &&
            !AppGUIisInitRunning(HPindex))
        {
            wdgWpr.GUIsetImgViewerImage(APP_GUI_TRT_SCR_CTRL_PNL_COLOUR_WIDGETS[HPindex], ColourBlink);
        }
        else
        {
            wdgWpr.GUIsetImgViewerImage(APP_GUI_TRT_SCR_CTRL_PNL_COLOUR_WIDGETS[HPindex], 1);
        }
    }
}

void AppGUIapplyTimeRestriction( uint8 HPindex, tHPcryoData *HP, tPRFdata *PRF)
{
//	cHPcryoTrtTimes TimeRestricted;
	
//	if ( HPcryoGetTimeRestriction (&TimeRestricted, HP, PRF))		//Consultamos al HPcryo si en tabla se muestra que para el tipo de manipulo conectado hay restricción de tiempo
//	{
//		AppGUIdata.slot[HPindex].selTime = TimeRestricted;			//Si la hay, se asigna el tiempo definido
//		GUIsetWidthNumVwr(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex],108);					//Al no tener elección de otro tiempo se centran los dígitos y se cambia la imagen para que no tenga la flecha que indica selección
//		GUIsetImgNumVwr(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex],c047_FondoNumVwrBlanco);
//	}
//	else if(AppGUIdata.slot[HPindex].selTrtArea != APP_GUI_NUM_FULL_BODY_AREAS && 		//En caso de tener una zona asignada con un tiempo aplicado para el grupo de zonas
//			AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED &&
//			AppGUIdata.trtZoneHdlr.timeGroupZones[APP_GUI_TRT_ZONES_GROUP_ASSOCIATION[AppGUIdata.slot[HPindex].selTrtArea][AppGUIdata.slot[HPindex].selTrtDot]] != HP_CRYO_TIME_NO_TIME)
//	{
//		//Asignamos al manipulo el tiempo establecido para el grupo zonas
//		AppGUIdata.slot[HPindex].selTime = AppGUIdata.trtZoneHdlr.timeGroupZones[APP_GUI_TRT_ZONES_GROUP_ASSOCIATION[AppGUIdata.slot[HPindex].selTrtArea][AppGUIdata.slot[HPindex].selTrtDot]];
//		if ( AppGUIopenTimePopupPermission( HPindex, HP, PRF))
//		{
//			GUIsetWidthNumVwr(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex],118);					//Al poder seleccionar otros tiempos se ponen los digitos desplazados a la derecha y se pone la imagen con la flecha que indica selección
//			GUIsetImgNumVwr(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex],c047_FondoTemporizador);
//		}
//		else
//		{
//			GUIsetWidthNumVwr(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex],108);					//Al no tener elección de otro tiempo se centran los dígitos y se cambia la imagen para que no tenga la flecha que indica selección
//			GUIsetImgNumVwr(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex],c047_FondoNumVwrBlanco);
//		}
//	}
//	//DAVID V765x
//	else if( AppGUIdata.slot[HPindex].selTime == APP_GUI_NO_TIME_SELECTED)
//	{
//		//Asignamos tiempo por defecto
//		AppGUIdata.slot[HPindex].selTime = HP_CRYO_TIME_LIST_PER_HP[HPcryoGetModel( HP, PRF)][0];
//		AppGUIdata.trtZoneHdlr.timeGroupZones[APP_GUI_TRT_ZONES_GROUP_ASSOCIATION[AppGUIdata.slot[HPindex].selTrtArea][AppGUIdata.slot[HPindex].selTrtDot]] = AppGUIdata.slot[HPindex].selTime;
//		GUIsetWidthNumVwr(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex],118);					//Al poder seleccionar otros tiempos se ponen los digitos desplazados a la derecha y se pone la imagen con la flecha que indica selección
//		GUIsetImgNumVwr(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex],c047_FondoTemporizador);
//	}
//	else
//	{
//		GUIsetWidthNumVwr(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex],118);					//Al poder seleccionar otros tiempos se ponen los digitos desplazados a la derecha y se pone la imagen con la flecha que indica selección
//		GUIsetImgNumVwr(APP_GUI_TRT_SCR_NUM_VWR_TIME_WIDGETS[HPindex],c047_FondoTemporizador);
//	}
}

uint8 AppGUIopenTimePopupPermission( uint8 HPindex, tHPcryoData *HP, tPRFdata *PRF)		//Devuelve si el manipulo conectado en la situación en la que se encuentre, si tiene o no permitido ir a la selección de tiempo
{
    uint8 i;
    uint8 zone_in_trt = 0;
    cHPcryoTrtTimes TimeRestricted;
	
//	if (HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))	//Si hay manipulo
//	{
//		for( i = 0; i < APP_GUI_MAXNUM_HP; i++)		//Recorremos los 4 comprobando si está conectado, si pertenecen al mismo grupo los puntos seleccionados como tratamiento, y si está en tratamiento
//		{
//			if ( (i != HPindex) &&
//				(APP_GUI_TRT_ZONES_GROUP_ASSOCIATION[AppGUIdata.slot[i].selTrtArea][AppGUIdata.slot[i].selTrtDot] == APP_GUI_TRT_ZONES_GROUP_ASSOCIATION[AppGUIdata.slot[HPindex].selTrtArea][AppGUIdata.slot[HPindex].selTrtDot]) &&
//				(AppGUIisTrtRunning( i, NULL)))	zone_in_trt++; 	//Si se cumple incrementamos la variable
//		}
//	}
	
    return ((!HPcryoGetTimeRestriction (&TimeRestricted, HP, PRF)) && (!zone_in_trt)); //Si se cumple que el HP tiene una restriccion por modelo o por grupo de zonas de tratamiento, entonces devuelve que no puede acceder al popup de tiempo
}


uint8 AppGUIisHPaDoubleDummy( tHPcryoData *HP, tPRFdata *PRF)		//Se comprueba si hay un manipulo double conectado, devolviendo cual es el primario y el secundario
{																	//Y devuelve si el manipulo que se ha pasado es el secundario o no
    uint8 DoubleMainSlot;
    uint8 DoubleOffSlot;
	
    if( HPcryoDoubleGetSlots( &DoubleMainSlot, &DoubleOffSlot, HP, PRF))
    {
        if( DoubleOffSlot == PRF->IDperifHW)	return 1;
    }
    return 0;
}

void AppGUIbuttonManagement (cAppGUIctrMenuBut button, uint8 butt_states, uint8 HPindex)
{
    tPRFdata *PRF;
    tHPcryoData *HP;
	
    HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF);
		
    switch ( button)		//En función del boton que me pasen como parametro
    {
        case App_GUI_but_Play:		//Se indexará a una tabla u otra, donde se selecciona en función del estado que pasen por parametro las imagenes de PRS, RLS y el estado de ENABLE/DISABLE
            if (butt_states == App_GUI_Play_but_disabled)	wdgWpr.GUIsetWidgetEnable ( APP_GUI_TRT_SCR_BUT_PLAY_WIDGETS[HPindex], 0);
            else
            {
                wdgWpr.GUIUpdatePlayButton((EAppGUI_HPsIDs)HPindex, (EAppGUIPlayButStates)butt_states);
//                GUIsetImgButton ( APP_GUI_TRT_SCR_BUT_PLAY_WIDGETS[HPindex], APP_GUI_TRT_SCR_BUT_PLAY_IMG[butt_states][App_GUI_widget_PRS_img], 1);
//                GUIsetImgButton ( APP_GUI_TRT_SCR_BUT_PLAY_WIDGETS[HPindex], APP_GUI_TRT_SCR_BUT_PLAY_IMG[butt_states][App_GUI_widget_RLS_img], 0);
                wdgWpr.GUIsetWidgetEnable ( APP_GUI_TRT_SCR_BUT_PLAY_WIDGETS[HPindex], APP_GUI_TRT_SCR_BUT_PLAY_IMG[butt_states][App_GUI_widget_ENABLE]);
            }
            break;
        case App_GUI_but_Vacc:
//            if (butt_states == App_GUI_Vac_but_disabled)	wdgWpr.GUIsetWidgetEnable ( APP_GUI_TRT_SCR_BUT_TSTVAC_WIDGETS[HPindex], 0);
//            else
//            {

                wdgWpr.GUIUpdateVacuumButton( (EAppGUI_HPsIDs)HPindex, (EAppGUIVacButStates)butt_states, AppGUIdata.slot[HPindex].selVacLvl );

//                GUIsetSwitchImg ( APP_GUI_TRT_SCR_BUT_TSTVAC_WIDGETS[HPindex],
//                                  APP_GUI_TRT_SCR_BUT_VAC_IMG[AppGUIdata.slot[HPindex].selVacLvl][butt_states][App_GUI_widget_PRS_img], APP_GUI_TRT_SCR_BUT_VAC_IMG[AppGUIdata.slot[HPindex].selVacLvl][butt_states][App_GUI_widget_RLS_img],
//                                  APP_GUI_TRT_SCR_BUT_VAC_IMG[AppGUIdata.slot[HPindex].selVacLvl][butt_states][App_GUI_widget_PRS_img], APP_GUI_TRT_SCR_BUT_VAC_IMG[AppGUIdata.slot[HPindex].selVacLvl][butt_states][App_GUI_widget_RLS_img]);
//                wdgWpr.GUIsetWidgetEnable ( APP_GUI_TRT_SCR_BUT_TSTVAC_WIDGETS[HPindex], APP_GUI_TRT_SCR_BUT_VAC_IMG[AppGUIdata.slot[HPindex].selVacLvl][butt_states][App_GUI_widget_ENABLE]);
//            }
            break;
        case App_GUI_but_Time:
            if (butt_states == App_GUI_Time_but_disabled)	wdgWpr.GUIsetWidgetEnable ( APP_GUI_TRT_SCR_BUT_SEL_TIME_WIDGETS[HPindex], 0);
            else
            {
                wdgWpr.GUIUpdateTimeButton((EAppGUI_HPsIDs)HPindex, (EAppGUITimeButStates)butt_states);
//                GUIsetImgButton ( APP_GUI_TRT_SCR_BUT_SEL_TIME_WIDGETS[HPindex], APP_GUI_TRT_SCR_BUT_TIME_IMG[butt_states][App_GUI_widget_PRS_img], 1);
//                GUIsetImgButton ( APP_GUI_TRT_SCR_BUT_SEL_TIME_WIDGETS[HPindex], APP_GUI_TRT_SCR_BUT_TIME_IMG[butt_states][App_GUI_widget_RLS_img], 0);
                wdgWpr.GUIsetWidgetEnable ( APP_GUI_TRT_SCR_BUT_SEL_TIME_WIDGETS[HPindex], APP_GUI_TRT_SCR_BUT_TIME_IMG[butt_states][App_GUI_widget_ENABLE]);
            }
            break;
        default:
            //ERROR
            break;
    }
}


void AppGUIconnectingHP (uint8 HPindex, uint32 *imgPrsID, uint32 *imgRlsID, uint32 *imgModelText)
{
//	static uint32 time_blink[APP_GUI_MAXNUM_HP] = {0,0,0,0};		//Variables de tiempo para el parpadeo del reloj que se muestra al conectar un HP
//	static uint8 img_count[APP_GUI_MAXNUM_HP] = {0,0,0,0};			//Contador empleado para identificar la imagen a mostrar en el "parpadeo"
	
//	*imgPrsID = APP_GUI_TRT_LOAD_NEW_HP_CONFIG[img_count[HPindex]];		//Asignación de la tabla de la imagen a representar
//	*imgRlsID = APP_GUI_TRT_LOAD_NEW_HP_CONFIG[img_count[HPindex]];		//Se emplea la misma para el PRS y el RLS (no se va a pòder pulsar en esta casualistica)
//	GUIsetWidgetEnable( APP_GUI_TRT_SCR_BUT_MODEL_IMG_WIDGETS[HPindex], 0);	//Se deshabilita el boton
//	*imgModelText = c233_ImgPixelBlanco;	//El texto del modelo de manipulo no se muestra
	
//	if (TICKS_DiffTicks(time_blink[HPindex]) >= APP_GUI_MAX_TIME_BLINK_LOAD_HP)		//Contabilización del tiempo para el parpadeo
//	{
//		time_blink[HPindex] = TICKS_GetTicks();		//Actualización del tiempo
//		img_count[HPindex]++;						//Incrementamos el contador de imagenes
//		if (img_count[HPindex]>=APP_GUI_TRT_LOAD_NEW_HP_IMG) img_count[HPindex]=0;		//Si llegamos al final de la lista de imagenes, comenzamos de nuevo desde la primera
//	}
}

float AppGUIcalcTrtTime( uint8 HPindex, uint32 trtElapsedTime_s, uint32 totalTrtTime_s)
{
    uint32 trtRemainingTime_s;
    float resultTime = 0.0;
	
//	/* Obtenemos los segundos restantes de tratamiento si hay tiempo seleccionado */
//	if( AppGUIdata.slot[HPindex].selTime != APP_GUI_NO_TIME_SELECTED)
//	{
//		if( totalTrtTime_s >= trtElapsedTime_s){ trtRemainingTime_s = totalTrtTime_s - trtElapsedTime_s;}
//		else { trtRemainingTime_s = 0;}
//		resultTime = AppGUIsecondsToClock( trtRemainingTime_s);
//	}
	
    /* Devolvemos el resultado */
    return resultTime;
}

float AppGUIsecondsToClock( uint32 seconds)
{
    uint32 min, sec;
    float resultTime = 0.0;
		
    /* Obtenemos los minutos restantes y segundos restantes dividiendo por 60 y cogiendo el resto */
    min = seconds / 60;
    sec = seconds % 60;
		
    /* Finalmente componemos el numero float como "min.sec" */
    resultTime = (( float)sec) / 100.0;
    resultTime = resultTime + ( float)min;
	
    /* Devolvemos el resultado */
    return resultTime;
}

void AppGUIupdateWarningFlags(void)
{
//	uint16 wng_flags;
	
//	wng_flags = ERR_get_WarningFlags();
	
//	AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Nivel_Agua_Bajo = ((wng_flags & Aviso_NivelAguaBajo) != 0);
//	AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Nivel_Agua_Medio = ((wng_flags & Aviso_NivelAguaMedio) != 0);
//	AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Temp_Amb = ((wng_flags & Aviso_TempAmbiente) != 0);
//	AppGUIdata.AppGUI_WarningHandler.Flag_Wng_RFID = ((wng_flags & Aviso_RFID) != 0);
//	AppGUIdata.AppGUI_WarningHandler.Flag_Wng_RTC = ((wng_flags & Aviso_RTC) != 0);
//	AppGUIdata.AppGUI_WarningHandler.Flag_Wng_Filtro_Aire = ((wng_flags & Aviso_FiltroAire) != 0);
}
void AppGUIwarningNotification (void)
{
    wdgWpr.GUIsetWidgetVisibility( APP_GUI_AVISOS_NOTIFICATIONS_WIDGETS_SCREENS[AppGUIdata.screen], ERR_get_NewWarningFlag());
//    if(AppGUIdata.mainMenuHdlr.isUp){	GUIsetImgViewerPosition( APP_GUI_AVISOS_NOTIFICATIONS_WIDGETS_SCREENS[AppGUIdata.screen],APP_GUI_IMG_AVISO_PENDIENTE_COORD);	}
//    else{	GUIsetImgViewerPosition( APP_GUI_AVISOS_NOTIFICATIONS_WIDGETS_SCREENS[AppGUIdata.screen],APP_GUI_IMG_AVISO_PENDIENTE2_COORD);	}
}

void AppGUIchangeMenuVwrTemperatureOrTime ( uint8 HPindex)
{
    if(AppGUIdata.slot[HPindex].VwrTemperatureOrTime == 0)
    {	AppGUIdata.slot[HPindex].VwrTemperatureOrTime = 1;	}
    else
    {	AppGUIdata.slot[HPindex].VwrTemperatureOrTime = 0;	}
}

void AppGUI_RFIDpopup_ReuseOption (uint8 option)
{
    AppGUIdata.RFIDhdlr.show_reuse_option = option;
}

void AppGUIsetWiFiMAC (uint8 *ptuMAC)
{
    AppGUIdata.WiFiMac[0] = ptuMAC[0];
    AppGUIdata.WiFiMac[1] = ptuMAC[1];
    AppGUIdata.WiFiMac[2] = ptuMAC[2];
    AppGUIdata.WiFiMac[3] = ptuMAC[3];
    AppGUIdata.WiFiMac[4] = ptuMAC[4];
    AppGUIdata.WiFiMac[5] = ptuMAC[5];
}

//V7790
void AppGUI_GPRScoverage( uint8 show, cAppGUIscreen screen)
{
    if( screen == APP_GUI_INIT_SCREEN || //screen == APP_GUI_TREATMENT_SCREEN ||
        screen == APP_GUI_CONFIGURATION_SCREEN)
    {
//		GUIsetWidgetVisibility( APP_GUI_GPRS_COVERAGE_WID_BY_SCREEN[screen], show);
    }
}
