/*
 * cbk.c
 *
 *  Created on: Jul 6, 2016
 *      Author: ingenieria9
 */

#include "cbk.h"
//#include "PE_Types.h"
#include "../AppGUI/AppGuiInterfaceStructure.h"
#include "../AppGUI/AppGUI.h"
#include "UIWrapperClasses/widgetswrapper.h"
#include "../AppGUI/K70_GUI.h"
#include "BOOT/boot.h"
#include "Perifericos/HPcryo.h"
//#include "../../Perifericos/Perifericos.h"
//#include "../../Expansora/Expansora.h"
//#include "../../Error/gestionError.h"
//#include "../../App.h"
#include "AppLOG/AppLOG.h"
#include "GPRS/AppGPRS.h"

/* Variables globales */
extern WidgetsWrapper wdgWpr;

/* Declaración de funciones locales */

/* Funciones publicas */
//void *cbkIndex(uint32 cbk)
//{
//	switch(cbk)
//	{
//		default:
				
//		case CBKdummy: 					return CBKdummyF;
//		case CBKbutGenderSelect: 		return CBKbutGenderSelectF;
//        case CBKbutMainMenuShow: 		return CBKbutMainMenuShowF;
//        case CBKbutMainMenuHide: 		return CBKbutMainMenuHideF;
//        case CBKbutHome: 				return CBKbutHomeF;
//		case CBKbutConfig: 				return CBKbutConfigF;
//		case CBKbutCalc: 				return CBKbutCalcF;
//		case CBKbutData: 				return CBKbutDataF;
//		case CBKbutWarningOn:			return CBKbutWarningOnF;
//		case CBKbutWarningOff:			return CBKbutWarningOffF;
//		case CBKbutCtrlPnlPlay:			return CBKbutCtrlPnlPlayF;
//		case CBKswCtrlPnlTstVacOn:		return CBKswCtrlPnlTstVacOnF;
//		case CBKswCtrlPnlTstVacOff:		return CBKswCtrlPnlTstVacOffF;
//		case CBKbutSelectTime:			return CBKbutSelectTimeF;
//		case CBKbutTemperatureVwr:		return CBKbutTemperatureVwrF;
//		case CBKbutTRTmodeAutoManual:	return CBKbutTRTmodeAutoManualF;
//		case CBKbutInfoZoneSelectedOn:	return CBKbutInfoZoneSelectedOnF;
//		case CBKbutInfoZoneSelectedOff:	return CBKbutInfoZoneSelectedOffF;
//		case CBKbutModelImage:			return CBKbutModelImageF;
//		case CBKbutHideCtrlPnl:			return CBKbutHideCtrlPnlF;
//		case CBKbutShowCtrlPnl:			return CBKbutShowCtrlPnlF;
//		case CBKbutFullBodyArea:		return CBKbutFullBodyAreaF;
//		case CBKswDotZoneOn:			return CBKswDotZoneOnF;
//		case CBKswDotZoneOff:			return CBKswDotZoneOffF;
//		//case CBKbutPopUpOK:				return CBKbutPopUpOKF;
//		case CBKbutPopUpReturn:			return CBKbutPopUpReturnF;
//		case CBKbutReuseRFIDlabel:		return CBKbutReuseRFIDlabelF;
//		case CBKbutPopUpTimeValue:		return CBKbutPopUpTimeValueF;
//		case CBKbutPopUpTstVacManual:	return CBKbutPopUpTstVacManualF;
//		case CBKbutPopUpTstVacAuto:		return CBKbutPopUpTstVacAutoF;
//		case CBKbutPopUpVacSmallLvl:	return CBKbutPopUpVacSmallLvlF;
//		case CBKswPopUpTstVacLvlOn:		return CBKswPopUpTstVacLvlOnF;
//		case CBKswPopUpTstVacLvlOff:	return CBKswPopUpTstVacLvlOffF;
//		case CBKbutPopUpErrOk:			return CBKbutPopUpErrOkF;
//		case CBKbutNumCalc:				return CBKbutNumCalcF;
//		case CBKbutEnterCalc:			return CBKbutEnterCalcF;
//		case CBKbutCECalc:				return CBKbutCECalcF;
//		case CBKbutSoftUpdateCfg:		return CBKbutSoftUpdateCfgF;
//		case CBKbutRecargaCoolant:		return CBKbutRecargaCoolantF;
//		case CBKswResuctionsVierew:		return CBKswResuctionsVierewF;
//		case CBKswCfgTemperatureViewer:	return CBKswCfgTemperatureViewerF;
//		case CBKbutCleanUpHP:			return CBKbutCleanUpHPF;
//		case CBKbutCleanUpHPround:		return CBKbutCleanUpHProundF;
//		case CBKswLanguage:				return CBKswLanguageF;
//		case CBKswCountry:				return CBKswCountryF;
//		case CBKbutPopUpCleanUp:		return CBKbutPopUpCleanUpF;
//		case CBKbutPopUpCleanUpYES:		return CBKbutPopUpCleanUpYESF;
//		case CBKbutPopUpCleanUpNO:		return CBKbutPopUpCleanUpNOF;
//		case CBKbutPopUpCleanUpCancel:	return CBKbutPopUpCleanUpCancelF;
//		case CBKbutSATnextPage:			return CBKbutSATnextPageF;
//		case CBKbutSATprevPage:			return CBKbutSATprevPageF;
//		case CBKswSATVacOn:				return CBKswSATVacOnF;
//		case CBKswSATVacOff:			return CBKswSATVacOffF;
//		case CBKswSATFrioOn:			return CBKswSATFrioOnF;
//		case CBKswSATFrioOff:			return CBKswSATFrioOffF;
//		case CBKswSATrfidOn:			return CBKswSATrfidOnF;
//		case CBKswSATrfidOff:			return CBKswSATrfidOffF;
//		case CBKswSATtestLedOn:			return CBKswSATtestLedOnF;
//		case CBKswSATtestLedOff:		return CBKswSATtestLedOffF;
//		case CBKswSATtestLedRGBOn:		return CBKswSATtestLedRGBOnF;
//		case CBKswSATtestLedRGBOff:		return CBKswSATtestLedRGBOffF;
//		case CBKswFATIGUEfailBelloff:	return CBKswFATIGUEfailBelloffF;
//		case CBKbutOkSATerr:			return CBKbutOkSATerrF;
//	}
//}

/* Funciones privadas */
void CBKdummyF( void *widget)
{
	/* No hacemos nada, dummy */
}

void CBKbutGenderSelectF( void *widget)
{
    /* Casteamos al tipo widget */
    stWidget *w = ( stWidget *)widget;
	
    /* Puede ser el boton de hombre o de mujer. Averiguamos quien es y asignamos a la variable body */
    if( w->id == ButSelectWoman){ AppGUIdata.trtZoneHdlr.body = AppGUIbodyFemale;}
    else if( w->id == ButSelectMan){ AppGUIdata.trtZoneHdlr.body = AppGUIbodyMale;}

    /* Pasamos a la pantalla de tratamiento */
//	if((EXP_UC_get_Country() != App_GUI_Sin_pais) || (AppGUIdata.CalcHandler.FlagSkipLangSelection))
//	{	AppGUIchangeScreen( APP_GUI_TREATMENT_SCREEN);	}
//	else
//	{	AppGUIchangeScreen( APP_GUI_LANGUAGES_SCREEN);	}
	
    AppGUIchangeScreen( APP_GUI_TREATMENT_SCREEN);
}

void CBKbutMainMenuShowF()
{
    /* Mostramos el menu principal */
    AppGUIhandleMainMenu( 1 );
    AppGUIwarningNotification();
}

void CBKbutMainMenuHideF()
{
    /* Ocultamos el menu principal */
    AppGUIhandleMainMenu( 0 );
    AppGUIwarningNotification();
}

void CBKbutHomeF( void *widget)
{
    uint8 perif;
    tHPcryoData *HP;
    tPRFdata *PRF;
    uint8 HPindex;
    uint8 isOk = 0;
	
    /* Si venimos de la pantalla del SAT apagamos todos los tests*/
    if (AppGUIdata.screen == APP_GUI_SAT_SCREEN)
    {
        for(perif=(APP_GUI_HP1_ID+1); perif<=APP_GUI_MAXNUM_HP; perif++)
        {
            if(HPcryoGetFromSlot((cPRFslot)perif, &HP, &PRF))
            {
                HPcryoSATallTestStop(HP, PRF);
                HP->frames.mainIn.data.enable_plica = 0;
                HPcryoSATbodyFillSensorTestStop( HP, PRF);
				
                /* Reseteamos variables */
                HP->SAT.testRun.bits.RGB = 0;
                HP->SAT.testRun.bits.bodyFillSensor = 0;
                HP->SAT.testRun.bits.cooling = 0;
                HP->SAT.testRun.bits.dummy = 0;
                HP->SAT.testRun.bits.vacum = 0;
                HP->SAT.RGB.tmr = 0;
                HP->SAT.RGB.curColor = 0;
                HP->SAT.RGB.colors[0] = HP_CRYO_CTLLED_COLOR_ROJO;
                HP->SAT.RGB.colors[1] = HP_CRYO_CTLLED_COLOR_VERDE;
                HP->SAT.RGB.colors[2] = HP_CRYO_CTLLED_COLOR_AZUL;
            }
        }
    }
	
    /* Si venimos de la pantalla de FATIGA */
    if (AppGUIdata.screen == APP_GUI_FATIGUE_SCREEN)
    {
        EXP_UCfatigaStop();
        if(HPcryoGetFromSlot((cPRFslot)(APP_GUI_HP1_ID+1), &HP, &PRF)){	HPcryoIdle( 0, HP, PRF);	}
        if(HPcryoGetFromSlot((cPRFslot)(APP_GUI_HP2_ID+1), &HP, &PRF)){	HPcryoIdle( 0, HP, PRF);	}
        if(HPcryoGetFromSlot((cPRFslot)(APP_GUI_HP3_ID+1), &HP, &PRF)){	HPcryoIdle( 0, HP, PRF);	}
        if(HPcryoGetFromSlot((cPRFslot)(APP_GUI_HP4_ID+1), &HP, &PRF)){	HPcryoIdle( 0, HP, PRF);	}
    }
	
    /* Pasamos a la pantalla de inicio si no hay HP en tratamiento o test de vacum */
    for( HPindex = 0; HPindex < APP_GUI_MAXNUM_HP; HPindex++)
    {
        isOk = isOk + AppGUIisTrtRunning( HPindex, NULL);
        isOk = isOk + AppGUIisTstVacRunning( HPindex, NULL);
    }
    if( isOk == 0){ AppGUIchangeScreen( APP_GUI_INIT_SCREEN);}
}

void CBKbutConfigF( void *widget)
{
    uint8 HPindex;
    uint8 isOk = 0;
	
    /* Pasamos a la pantalla de inicio si no hay HP en tratamiento o test de vacum */
    for( HPindex = 0; HPindex < APP_GUI_MAXNUM_HP; HPindex++)
    {
        isOk = isOk + AppGUIisTrtRunning( HPindex, NULL);
        isOk = isOk + AppGUIisTstVacRunning( HPindex, NULL);
    }
    if( isOk == 0){ AppGUIchangeScreen( APP_GUI_CONFIGURATION_SCREEN);}
}

void CBKbutCalcF( void *widget)
{
    uint8 HPindex;
    uint8 isOk = 0;
	
    /* Pasamos a la pantalla de inicio si no hay HP en tratamiento o test de vacum */
    for( HPindex = 0; HPindex < APP_GUI_MAXNUM_HP; HPindex++)
    {
        isOk = isOk + AppGUIisTrtRunning( HPindex, NULL);
        isOk = isOk + AppGUIisTstVacRunning( HPindex, NULL);
    }
    if( isOk == 0){ AppGUIchangeScreen( APP_GUI_CALCULATOR_SCREEN);}
}

void CBKbutDataF( void *widget)
{
//	uint8 HPindex;
//	uint8 isOk = 0;
	
//	/* Pasamos a la pantalla de inicio si no hay HP en tratamiento o test de vacum */
//	for( HPindex = 0; HPindex < APP_GUI_MAXNUM_HP; HPindex++)
//	{
//		isOk = isOk + AppGUIisTrtRunning( HPindex, NULL);
//		isOk = isOk + AppGUIisTstVacRunning( HPindex, NULL);
//	}
//	if( isOk == 0){ AppGUIchangeScreen( APP_GUI_LANGUAGES_SCREEN);}
}

void CBKbutWarningOnF ()
{
// TODO Check if the popup is hidden
//    stWidget *popUp;

//    popUp = GUIgetWidget( APP_GUI_AVISOS_POPUP_WIDGET_SCREENS[AppGUIdata.screen]);
//    if( popUp->enable == 0)
        AppGUIhandleWarningPopUp( 1);
}

void CBKbutWarningOffF ()
{
// TODO Check if the popup is shown
//    stWidget *popUp;

//    popUp = GUIgetWidget( APP_GUI_AVISOS_POPUP_WIDGET_SCREENS[AppGUIdata.screen]);
//    if ( popUp->enable != 0)
        AppGUIhandleWarningPopUp( 0);
}

void CBKbutCtrlPnlPlayF( void *widget)
{
    //RFID_time_ref[0] = TICKS_GetTicks();	//DEBUG	-	Tiempo de referencia desde el inicio de pulsar para RFID hasta el final del procedimiento
    //RFID_time_ref[1] = TICKS_GetTicks();	//DEBUG	-	Tiempo de referencia desde l inicio de pulsar para RFID hasta comienzo del proceso en el modulo RFID
	
    uint8 HPindex;
    tHPcryoData *HP;
    tPRFdata *PRF;
	
    /* Casteamos al tipo widget */
    stWidget *w = ( stWidget *)widget;
	
    /* Obtenemos el indice del HP en función del widget */
    switch( w->id)
    {
        case ButCtrlPnlPlayHP1: HPindex = 0; break;
        case ButCtrlPnlPlayHP2: HPindex = 1; break;
        case ButCtrlPnlPlayHP3: HPindex = 2; break;
        case ButCtrlPnlPlayHP4: HPindex = 3; break;
        default: return;
    }
	
    if (HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
    {
        if ((AppGUIisTrtRunning( HPindex, NULL)) && (HPcryoTrtVacumRetryAvailable( HP, PRF)))
        {
            HPcryoStop(1, HP, PRF);
            AppGUIdata.slot[HPindex].VwrTemperatureOrTime = 0;
            return;
        }
    }
	
    /* Lanzamos tratamiento si esta todo seleccionado correctamente y hay HP */
    if( HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF) &&
        AppGUIdata.slot[HPindex].selTime != APP_GUI_NO_TIME_SELECTED &&
        AppGUIdata.slot[HPindex].selVacLvl != APP_GUI_NO_VAC_LVL_SELECTED &&
        AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED &&
        AppGUIdata.slot[HPindex].selTrtArea != AppGUIfullBodyNO_AREA)
    {
        /* Hay manípulo y tiene tratamiento configurado */
		
        HP->trt.TrtParameters.mode = AppGUIdata.slot[HPindex].TrtMode;
        HP->trt.TrtParameters.reqLabel = 1;
        HP->trt.TrtParameters.time = AppGUIdata.slot[HPindex].selTime;
        HP->trt.TrtParameters.useDfltAlarmCfg = 1;
        HP->trt.TrtParameters.vacLvl = AppGUIdata.slot[HPindex].selVacLvl;
		
        HP->trt.TrtRequested = 1;
		
//		HPcryoTrtStartDflt(	AppGUIdata.slot[HPindex].TrtMode,
//							AppGUIdata.slot[HPindex].selTime,
//							AppGUIdata.slot[HPindex].selVacLvl, 1, 1, HP, PRF);
    }
    else
    {
        /* Posible pitido indicando que no se ha podido iniciar */
    }
}

void CBKswCtrlPnlTstVacOnF( void *widget)
{
//	uint8 HPindex;
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	stWidget *popUp;
	
//	/* Casteamos al tipo widget */
//	stWidget *w = ( stWidget *)widget;
	
//	/* Obtenemos el indice del HP en función del widget */
//	switch( w->id)
//	{
//		case SwCtrlPnlTstVacHP1: HPindex = 0; break;
//		case SwCtrlPnlTstVacHP2: HPindex = 1; break;
//		case SwCtrlPnlTstVacHP3: HPindex = 2; break;
//		case SwCtrlPnlTstVacHP4: HPindex = 3; break;
//		default: return;
//	}
	
//	HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF);
	
//	if (( AppGUIisTrtRunning( HPindex, NULL)) &&  (HPcryoTrtAdjustVacumAvailable( HP, PRF)))
//	{
//		popUp = GUIgetWidget( PopUpTstVacSmall);
//		if( HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF) &&
//			popUp->enable == 0 &&
//			AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED &&
//			AppGUIdata.slot[HPindex].selTrtArea != AppGUIfullBodyNO_AREA)
//		{
//			/* Guardamos el HP que ha activado el popUp */
//			AppGUIdata.tstVacHdlr.HPindex = HPindex;
			
//			/* Asignamos el nivel de vacum actualmente asignado a este HP - Solo si el modo de TRT es MANUAL */
//			if(HP->trt.TrtParameters.mode == HP_CRYO_TRT_MODE_MANUAL)
//			{
//				AppGUIdata.tstVacHdlr.selVacLvl = AppGUIdata.slot[HPindex].selVacLvl;
//			}
			
//			/* Activamos el PopUp del test de vacum */
//			AppGUIhandleTstVacSMALLPopUp( 1, HPindex);
//		}
//		else
//		{
//			/* Posible pitido indicando que no se ha podido iniciar */
//		}
//	}
//	else
//	{
//		/* Comprobamos que hay HP y tiene trt configurado para activar el popUp y que el
//		 * PopUp no esta ya activo */
//		popUp = GUIgetWidget( PopUpTstVac);
//		if( HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF) &&
//			popUp->enable == 0 &&
//			AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED &&
//			AppGUIdata.slot[HPindex].selTrtArea != AppGUIfullBodyNO_AREA)
//		{
//			/* Guardamos el HP que ha activado el popUp */
//			AppGUIdata.tstVacHdlr.HPindex = HPindex;
			
//			/* Asignamos el nivel de vacum actualmente asignado a este HP - Solo si el modo de TRT es MANUAL */
//			if(HP->trt.TrtParameters.mode == HP_CRYO_TRT_MODE_MANUAL)
//			{
//				AppGUIdata.tstVacHdlr.selVacLvl = AppGUIdata.slot[HPindex].selVacLvl;
//			}
			
//			/* Activamos el PopUp del test de vacum */
//			AppGUIhandleTstVacPopUp( 1, HPindex);
//		}
//		else
//		{
//			/* Posible pitido indicando que no se ha podido iniciar */
//		}
//	}
	
//	for( HPindex=0;HPindex<APP_GUI_MAXNUM_HP;HPindex++)	AppGUIhandleCtrlPanel(AppGUIdata.slot[HPindex].isCtrlPnlShow, HPindex);
//	//Se revisan las zonas de tratamiento ya que también gestiona el botón de info (para que se quite al activar otro popup
//	AppGUIhandleTrtZone();
}

void CBKswCtrlPnlTstVacOffF( void *widget)
{
//	uint8 HPindex;
//	stWidget *popUp;
//	tPRFdata *PRF;
//	tHPcryoData *HP;
	
//	/* -- PopUp de test de vacum */
//	popUp = GUIgetWidget( PopUpTstVac);
//	if( popUp->enable)
//	{
//		/* Es el popUp de test de vacum, tenemos que asignar el nivel seleccionado si esta testeado */
////		if( AppGUIdata.slot[AppGUIdata.tstVacHdlr.HPindex].testedVacLvls[AppGUIdata.tstVacHdlr.selVacLvl] != 0)
////		{
//		/* Asignamos el vacum seleccionado */
////		AppGUIdata.slot[AppGUIdata.tstVacHdlr.HPindex].selVacLvl = AppGUIdata.tstVacHdlr.selVacLvl;
////		}
////		else
////		{
////			AppGUIdata.slot[AppGUIdata.tstVacHdlr.HPindex].selVacLvl = APP_GUI_NO_VAC_LVL_SELECTED;
////		}
				
//		/* Si el HP esta en test de vacum lo paramos y si esta en tratamiento ajustamos el vacum */
//		if( HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[AppGUIdata.tstVacHdlr.HPindex], &HP, &PRF))
//		{
//			/* Según el status del HP */
//			switch( HPcryoGetStatus( HP, PRF))
//			{
//				case HP_CRYO_TREATMENT:
					
//					/* Ajustamos al nuevo nivel de vacum si es un valor válido */
//					if( AppGUIdata.slot[AppGUIdata.tstVacHdlr.HPindex].selVacLvl != APP_GUI_NO_VAC_LVL_SELECTED)
//					{
//						if( HPcryoTrtAdjustVacumDflt( AppGUIdata.tstVacHdlr.selVacLvl, HP, PRF))
//						{
//							/* Se ha ajustado correctamente el vacum */
//							AppGUIdata.slot[AppGUIdata.tstVacHdlr.HPindex].selVacLvl = AppGUIdata.tstVacHdlr.selVacLvl;
//						}
//						else
//						{
//							/* No se puede cambiar el nivel de vacum */
//						}
//					}
//					break;
//				case HP_CRYO_TEST_VACUM:
//					/* Paramos el test de vacum */
//					HPcryoStop( 1, HP, PRF);
					
//					/* Asignamos el nuevo nivel */
//					AppGUIdata.slot[AppGUIdata.tstVacHdlr.HPindex].selVacLvl = AppGUIdata.tstVacHdlr.selVacLvl;
//					break;
//				default:
//					AppGUIdata.slot[AppGUIdata.tstVacHdlr.HPindex].selVacLvl = AppGUIdata.tstVacHdlr.selVacLvl;
//					break;
//			}
//		}
		
//		/* Desactivamos el popUp de test de vacum */
//		AppGUIhandleTstVacPopUp( 0, AppGUIdata.tstVacHdlr.HPindex);
//	}
	
//	popUp = GUIgetWidget( PopUpTstVacSmall);
//	if(popUp->enable)
//	{
//		AppGUIhandleTstVacSMALLPopUp( 0, AppGUIdata.tstVacHdlr.HPindex);
//	}
	
	
//	for( HPindex = 0; HPindex < APP_GUI_MAXNUM_HP; HPindex++)
//	{
//		if (HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF) && (AppGUIdata.slot[HPindex].selTrtArea != APP_GUI_NUM_FULL_BODY_AREAS) && (AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED))
//		{
//			AppGUIapplyTimeRestriction(HPindex, HP, PRF);
//			//AppGUIdata.slot[HPindex].trtTime = AppGUIcalcTrtTime( HPindex, HPcryoTrtGetTimeSeconds( HP, PRF));
//			AppGUIdata.slot[HPindex].trtTime = AppGUIcalcTrtTime( HPindex, HPcryoTrtGetTimeSeconds( HP, PRF),
//																  HPcryoTrtGetTreatmentTotalTimeSeconds( HP, PRF));
//		}
//		AppGUIhandleCtrlPanel(AppGUIdata.slot[HPindex].isCtrlPnlShow, HPindex);
//	}
//	//Se revisan las zonas de tratamiento ya que también gestiona el botón de info (para que se quite al activar otro popup
//	AppGUIhandleTrtZone();
}

void CBKbutSelectTimeF( void *widget)
{
    uint8 HPindex;
    tHPcryoData *HP;
    tPRFdata *PRF;
    stWidget *popUp;
	
    /* Casteamos al tipo widget */
    stWidget *w = ( stWidget *)widget;
	
    /* Obtenemos el indice del HP en función del widget */
    switch( w->id)
    {
        case ButSelectTimeHP1: HPindex = 0; break;
        case ButSelectTimeHP2: HPindex = 1; break;
        case ButSelectTimeHP3: HPindex = 2; break;
        case ButSelectTimeHP4: HPindex = 3; break;
        default: return;
    }
    if( HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
    {
        if ( AppGUIopenTimePopupPermission( HPindex, HP, PRF))
        {
            /* Comprobamos que hay HP y tiene trt configurado para activar el popUp y que el
             * PopUp no esta ya activo */
//            popUp = GUIgetWidget( PopUpTime);
            if( AppGUIIsPopupDisplayed(PopUpTime) == 0 &&
                AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED &&
                AppGUIdata.slot[HPindex].selTrtArea != AppGUIfullBodyNO_AREA)
            {
                /* Guardamos el HP que ha activado el popUp */
                AppGUIdata.timeHdlr.HPindex = HPindex;
				
                /* Asignamos el tiempo actualmente asignado a este HP */
                AppGUIdata.timeHdlr.selTime = AppGUIdata.slot[HPindex].selTime;
				
                /* Activamos el PopUp del tiempo */
                AppGUIhandleTimePopUp( 1, HPindex);
            }
            else
            {
                AppGUIhandleTimePopUp( 0, HPindex);
                /* Posible pitido indicando que no se ha podido iniciar */
            }
        }
    }

    //Se revisan los 4 paneles de control de los manipulos
    for( HPindex=0;HPindex<APP_GUI_MAXNUM_HP;HPindex++)	AppGUIhandleCtrlPanel(AppGUIdata.slot[HPindex].isCtrlPnlShow, HPindex);
	
    //Se revisan las zonas de tratamiento ya que también gestiona el botón de info (para que se quite al activar otro popup
    AppGUIhandleTrtZone();
}

void CBKbutTemperatureVwrF ( void *widget)
{
    uint8 HPindex;
	
    /* Casteamos al tipo widget */
    stWidget *w = ( stWidget *)widget;
	
    /* Obtenemos el indice del HP en función del widget */
    switch( w->id)
    {
        case ButVwrTemperatureHP1: HPindex = 0; break;
        case ButVwrTemperatureHP2: HPindex = 1; break;
        case ButVwrTemperatureHP3: HPindex = 2; break;
        case ButVwrTemperatureHP4: HPindex = 3; break;
        default: return;
    }
	
    AppGUIchangeMenuVwrTemperatureOrTime ( HPindex);
}

void CBKbutTRTmodeAutoManualF ( void *widget)
{
//	uint8 HPindex;
//	tHPcryoData *HP;
//	tPRFdata *PRF;
	
//	/* Casteamos al tipo widget */
//	stWidget *w = ( stWidget *)widget;
	
//	/* Obtenemos el indice del HP en función del widget */
//	switch( w->id)
//	{
//		case ButSwtchModeAutoManualHP1: HPindex = 0; break;
//		case ButSwtchModeAutoManualHP2: HPindex = 1; break;
//		case ButSwtchModeAutoManualHP3: HPindex = 2; break;
//		case ButSwtchModeAutoManualHP4: HPindex = 3; break;
//		default: return;
//	}
//	if (HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
//	{
//		if (HPcryoIsAutoModeAvaible(HP, PRF))
//		{
//			if (AppGUIdata.slot[HPindex].TrtMode == HP_CRYO_TRT_MODE_MANUAL)
//			{
//				AppGUIdata.slot[HPindex].TrtMode = HP_CRYO_TRT_MODE_AUTO;
//				AppGUIdata.slot[AppGUIdata.tstVacHdlr.HPindex].selVacLvl = HP_CRYO_VAC_LVL_2;
//			}
//			else if (AppGUIdata.slot[HPindex].TrtMode == HP_CRYO_TRT_MODE_AUTO){	AppGUIdata.slot[HPindex].TrtMode = HP_CRYO_TRT_MODE_MANUAL;	}
//		}
//	}
	
//	//Se revisan los 4 paneles de control de los manipulos
//	for( HPindex=0;HPindex<APP_GUI_MAXNUM_HP;HPindex++)	AppGUIhandleCtrlPanel(AppGUIdata.slot[HPindex].isCtrlPnlShow, HPindex);
}

void CBKbutInfoZoneSelectedOnF()
{
    uint8 HPindex;
    stWidget *popUp;

    if( AppGUIIsPopupDisplayed(PopUpRecomm) == 0)		AppGUIhandleRecommendationpopUp( 1, AppGUIdata.trtZoneHdlr.selTrtDot, AppGUIdata.trtZoneHdlr.selTrtArea);
	
    for( HPindex=0;HPindex<APP_GUI_MAXNUM_HP;HPindex++)	AppGUIhandleCtrlPanel(AppGUIdata.slot[HPindex].isCtrlPnlShow, HPindex);
    AppGUIhandleTrtZone();
}

void CBKbutInfoZoneSelectedOffF()
{
    uint8 HPindex;

    if ( AppGUIIsPopupDisplayed(PopUpRecomm) != 0)		AppGUIhandleRecommendationpopUp( 0, AppGUIdata.trtZoneHdlr.selTrtDot, AppGUIdata.trtZoneHdlr.selTrtArea);
	
    for( HPindex=0;HPindex<APP_GUI_MAXNUM_HP;HPindex++)	AppGUIhandleCtrlPanel(AppGUIdata.slot[HPindex].isCtrlPnlShow, HPindex);
    AppGUIhandleTrtZone();
}

void CBKbutModelImageF( void *widget)
{
    uint8 HPindex;
    uint8 otherHPindex, isOtherHPworking, found;
    tHPcryoData *HP;
    tPRFdata *PRF;
	
    /* Casteamos al tipo widget */
    stWidget *w = ( stWidget *)widget;
	
    /* Obtenemos el indice del HP en función del widget */
    switch( w->id)
    {
        case ButModelImageHP1: HPindex = 0; break;
        case ButModelImageHP2: HPindex = 1; break;
        case ButModelImageHP3: HPindex = 2; break;
        case ButModelImageHP4: HPindex = 3; break;
        default: return;
    }
	
    /* Comprobamos si algun HP tiene esta zona */
    otherHPindex = 0;
    found = 0;
    isOtherHPworking = 0;
    while( otherHPindex < APP_GUI_MAXNUM_HP && !found)
    {
        /* Comprobamos si tiene la zona seleccionada y no es el mismo HP que
         * ha llamado a la función  */
        if( AppGUIdata.slot[otherHPindex].selTrtDot == AppGUIdata.trtZoneHdlr.selTrtDot &&
            AppGUIdata.slot[otherHPindex].selTrtArea == AppGUIdata.trtZoneHdlr.selTrtArea &&
            HPindex != otherHPindex)
        {
            /* Hemos encontrado un HP que ya tiene seleccionada esta zona de tratamiento */
            found = 1;
			
            /* comprobamos si esta en tratamiento */
            isOtherHPworking = AppGUIisTrtRunning( otherHPindex, NULL);
        }
        else
        {
            otherHPindex++;
        }
    }
	
    /* Comprobamos que hay HP conectado y que tenemos un DOT de tratamiento seleccionado
     * asi como una area de full body seleccionada y que no hay otro HP en tratamiento
     * con esta zona ya seleccionada y que el propio HP no esta en tratamiento */
    if( HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF) &&
        AppGUIdata.trtZoneHdlr.selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED &&
        AppGUIdata.trtZoneHdlr.selTrtArea != AppGUIfullBodyNO_AREA &&
        !isOtherHPworking && !AppGUIisTrtRunning( HPindex, NULL))
    {
        /* Guardamos configuracion en el slot adecuado */
        if( AppGUIdata.slot[HPindex].selTrtDot != AppGUIdata.trtZoneHdlr.selTrtDot ||
            AppGUIdata.slot[HPindex].selTrtArea != AppGUIdata.trtZoneHdlr.selTrtArea)
        {
            /* Hay manípulo y tenemos area y zona seleccionados en el interface. Reseteamos y
             * luego asignamos la nueva zona */
            AppGUIclearSlotData( HPindex);
					
            /* No es la misma zona de tratamiento, la asignamos */
            AppGUIdata.slot[HPindex].selTrtDot = AppGUIdata.trtZoneHdlr.selTrtDot;
            AppGUIdata.slot[HPindex].selTrtArea = AppGUIdata.trtZoneHdlr.selTrtArea;
			
            /* Si hay otro HP con la zona seleccionada reseteamos sus
             * variables de control de slot */
            if( found){ AppGUIclearSlotData( otherHPindex);}
        }
        else
        {
            /* Es la misma zona de tratamiento, reseteamos */
            AppGUIclearSlotData( HPindex);
        }
		
        /* Refrescamos la zona de seleccion de tratamiento */
        AppGUIhandleTrtZone();
        /* Se llama a la funcion que actualiza la configuración del panel de control personal de cada manipulo, de esta forma el glitch de los 45 min del Tiny y Tiny Curved se soluciona */
//		AppGUIhandleCtrlPanel(AppGUIdata.slot[HPindex].isCtrlPnlShow, HPindex);
//		if( found) AppGUIhandleCtrlPanel(AppGUIdata.slot[otherHPindex].isCtrlPnlShow, otherHPindex);
    }
    else
    {
        /* Posible pitido indicando que no se ha podido iniciar */
    }
}

void CBKbutHideCtrlPnlF( void *widget)
{
//	uint8 HPindex;
	
//	/* Casteamos al tipo widget */
//	stWidget *w = ( stWidget *)widget;
	
//	/* Obtenemos el indice del HP en función del widget */
//	switch( w->id)
//	{
//		case ButHideControlPanelHP1: HPindex = 0; break;
//		case ButHideControlPanelHP2: HPindex = 1; break;
//		case ButHideControlPanelHP3: HPindex = 2; break;
//		case ButHideControlPanelHP4: HPindex = 3; break;
//		default: return;
//	}
	
//	/* Indicamos que el panel de control se esta ocultando */
//	AppGUIdata.slot[HPindex].isCtrlPnlShow = 0;
			
//	/* Ocultamos el panel de control */
//	AppGUIhandleCtrlPanel( 0, HPindex);
}

void CBKbutShowCtrlPnlF( void *widget)
{
//	uint8 HPindex;
	
//	/* Casteamos al tipo widget */
//	stWidget *w = ( stWidget *)widget;
	
//	/* Obtenemos el indice del HP en función del widget */
//	switch( w->id)
//	{
//		case butShowControlPanelHP1: HPindex = 0; break;
//		case butShowControlPanelHP2: HPindex = 1; break;
//		case butShowControlPanelHP3: HPindex = 2; break;
//		case butShowControlPanelHP4: HPindex = 3; break;
//		default: return;
//	}
	
//	/* Indicamos que el panel de control se esta mostrando */
//	AppGUIdata.slot[HPindex].isCtrlPnlShow = 1;
	
//	/* Mostramos el panel de control */
//	AppGUIhandleCtrlPanel( 1, HPindex);
}

void CBKbutFullBodyAreaF( void *widget)
{
    uint8 i;
	
    /* Casteamos al tipo widget */
    stWidget *w = ( stWidget *)widget;
	
    /* Guardamos el área de tratamiento seleccionada */
    i = AppGUIfullBodyTorso;
    while( i < APP_GUI_NUM_FULL_BODY_AREAS && APP_GUI_TRT_SCR_FULL_BODY_AREAS_WIDGETS[i] != w->id){ i++;}
    if( i >= APP_GUI_NUM_FULL_BODY_AREAS){ AppGUIdata.trtZoneHdlr.selTrtArea = AppGUIfullBodyNO_AREA;}
    else{ AppGUIdata.trtZoneHdlr.selTrtArea = (cAppGUIfullBodyAreas)i;}
		
    /* Refrescamos la zona de selección de tratamiento */
    AppGUIhandleTrtZone();
}

void CBKswDotZoneOnF( void *widget)
{
    uint8 i;
	
    /* Casteamos al tipo widget */
    stWidget *w = ( stWidget *)widget;
	
    /* Guardamos el área de tratamiento seleccionada */
    i = 0;
    while( i < APP_GUI_MAX_DOTS_PER_AREA && APP_GUI_TRT_SCR_DOT_ZONES_WIDGETS[i] != w->id){ i++;}
    if( i >= APP_GUI_MAX_DOTS_PER_AREA){ AppGUIdata.trtZoneHdlr.selTrtDot = APP_GUI_NO_TRT_DOT_SELECTED;}
    else{ AppGUIdata.trtZoneHdlr.selTrtDot = i;}
	
    for( i = 0; i < APP_GUI_MAX_DOTS_PER_AREA; i++)
    {
        /* Todos los switches que no sean el que ha llamado a estado OFF */
        if( APP_GUI_TRT_SCR_DOT_ZONES_WIDGETS[i] != w->id)
        {
            wdgWpr.GUIsetSwitchStatus( APP_GUI_TRT_SCR_DOT_ZONES_WIDGETS[i], 0);
        }
    }
	
    /* Refrescamos la zona de selección de tratamiento */
    AppGUIhandleTrtZone();
}

void CBKswDotZoneOffF( void *widget)
{
    /* Casteamos al tipo widget */
    stWidget *w = ( stWidget *)widget;
	
    /* Si es el "dot" actualmente seleccionado lo descartamos */
    if( APP_GUI_TRT_SCR_DOT_ZONES_WIDGETS[AppGUIdata.trtZoneHdlr.selTrtDot] == w->id)
    {
        AppGUIdata.trtZoneHdlr.selTrtDot = APP_GUI_NO_TRT_DOT_SELECTED;
    }

    /* Refrescamos la zona de selección de tratamiento */
    AppGUIhandleTrtZone();
}

void CBKpopUpDisplayedF( void *widget, bool visible )
{
    stWidget *w = ( stWidget *)widget;

    // Look for the popup visible state
    for ( int i = 0; i < APP_GUI_POPUP_DISPLAYED_MAP_NUM; i++ )
    {
        // Popup found
        if( w->id == APP_GUI_POPUP_DISPLAYED_MAP[i].id )
        {
            // Set the new popup state
            APP_GUI_POPUP_DISPLAYED_MAP[i].displayed = visible;
        }
    }
}

void CBKbutPopUpReturnF()
{
    uint8 HPindex;
    stWidget *popUp;
    uint8 isPopUp = 0;
    tHPcryoData *HP;
    tPRFdata *PRF;
	
    /* El comportamiento depende de que popUp esta activo o si ninguno lo esta entender que es el zoom de la
     * zona de tratamiento */
    /* -- PopUp's tiempo, test vacum y RFID se desactivan */
//    popUp = GUIgetWidget( PopUpRFID);
    if( AppGUIisRFIDPopUpActive() )
    {
        /* Paramos el tratamiento en curso */
        if( HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[AppGUIdata.RFIDhdlr.HPindex], &HP, &PRF))
        { HPcryoStop( 1, HP, PRF);}
		
        /* Quitamos el popUp */
        AppGUIhandleRFIDpopUp( 0, AppGUIdata.RFIDhdlr.HPindex); isPopUp = 1;
        RFID_free();
    }
//	popUp = GUIgetWidget( PopUpTime);
//	if( popUp->enable){ AppGUIhandleTimePopUp( 0, AppGUIdata.timeHdlr.HPindex); isPopUp = 1;}
//	popUp = GUIgetWidget( PopUpTstVac);
//	if( popUp->enable)
//	{
//		/* Si hay test de vacum en marcha lo paramos, si es tratamiento lo mantenemos */
//		if( HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[AppGUIdata.tstVacHdlr.HPindex], &HP, &PRF))
//		{
//			if( HPcryoGetStatus( HP, PRF) == HP_CRYO_TEST_VACUM){ HPcryoStop( 1, HP, PRF);}
//		}
//
//		/* Quitamos el PopUp */
//		AppGUIhandleTstVacPopUp( 0, AppGUIdata.tstVacHdlr.HPindex); isPopUp = 1;
//	}
	
    /* Si no era ningun popUp entonces es la gestión de zonas de tratamiento para quitar el zoom */
    if( !isPopUp)
    {
        /* Indicamos que no hay nada seleccionado en la gestión de areas */
        AppGUIdata.trtZoneHdlr.selTrtDot = APP_GUI_NO_TRT_DOT_SELECTED;
        AppGUIdata.trtZoneHdlr.selTrtArea = AppGUIfullBodyNO_AREA;
		
        /* Refrescamos la zona de selección de tratamiento */
        AppGUIhandleTrtZone();
    }
	
    for( HPindex=0;HPindex<APP_GUI_MAXNUM_HP;HPindex++)
    {
        if (HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
        {
            if ( (!AppGUIisInitRunning(HPindex)) && (AppGUIdata.slot[HPindex].selTrtArea != APP_GUI_NUM_FULL_BODY_AREAS) && (AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED))
            {AppGUIapplyTimeRestriction(HPindex, HP, PRF);}
        }
        AppGUIhandleCtrlPanel(AppGUIdata.slot[HPindex].isCtrlPnlShow, HPindex);
    }
    //Se revisan las zonas de tratamiento ya que también gestiona el botón de info (para que se quite al activar otro popup
    AppGUIhandleTrtZone();
}

void CBKbutPopUpTimeValueF( void *widget)
{
    uint8 HPindex;
    tHPcryoData *HP;
    tPRFdata *PRF;
    uint8 i;
	
    /* Casteamos al tipo widget */
    stWidget *w = ( stWidget *)widget;
	
    /* Seleccionamos el tiempo según el id del widget */
    i = HP_CRYO_TIME_45_MIN;
    while( i < HP_CRYO_MAX_TIME_LIST && APP_GUI_TRT_SCR_POPUP_TIME_SW_LIST[i] != w->id){ i++;}
    if( i >= HP_CRYO_MAX_TIME_LIST){ AppGUIdata.timeHdlr.selTime = APP_GUI_NO_TIME_SELECTED;}
    else
    {
        AppGUIdata.timeHdlr.selTime = (cHPcryoTrtTimes)i;
        /* Es el popUp de tiempo, tenemos que asignar el tiempo seleccionado */
        AppGUIdata.slot[AppGUIdata.timeHdlr.HPindex].selTime = AppGUIdata.timeHdlr.selTime;
        AppGUIdata.trtZoneHdlr.timeGroupZones[APP_GUI_TRT_ZONES_GROUP_ASSOCIATION[AppGUIdata.slot[AppGUIdata.timeHdlr.HPindex].selTrtArea][AppGUIdata.slot[AppGUIdata.timeHdlr.HPindex].selTrtDot]] = AppGUIdata.timeHdlr.selTime;
    }

    /* Desactivamos el popUp de tiempo */
    AppGUIhandleTimePopUp( 0, AppGUIdata.timeHdlr.HPindex);
	
	
    //Actualizamos el panel de control
    for( HPindex=0;HPindex<APP_GUI_MAXNUM_HP;HPindex++)
    {
        AppGUIhandleCtrlPanel(AppGUIdata.slot[HPindex].isCtrlPnlShow, HPindex);
		
        /* Actualizamos el tiempo de tratamiento */
        if( HPcryoGetFromSlot( (cPRFslot)APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
        {
            AppGUIdata.slot[HPindex].trtTime = AppGUIcalcTrtTime( HPindex, HPcryoTrtGetTimeSeconds( HP, PRF),
                                                                  HPcryoTrtGetTreatmentTotalTimeSeconds( HP, PRF));
        }
			
    }
}

void CBKbutPopUpTstVacManualF( void *widget)
{
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	uint8 HPindex = AppGUIdata.tstVacHdlr.HPindex;
	
//	/* Casteamos al tipo widget */
//	stWidget *w = ( stWidget *)widget;
	
//	/* Obtenemos el indice del HP en función del widget */
//	switch( w->id)
//	{
//		case butPopUpTstVacManualLowLvl: AppGUIdata.tstVacHdlr.Tst_vac_but = HP_CRYO_VAC_LVL_0; break;
//		case butPopUpTstVacManualMidLvl: AppGUIdata.tstVacHdlr.Tst_vac_but = HP_CRYO_VAC_LVL_1; break;
//		case butPopUpTstVacManualHighLvl: AppGUIdata.tstVacHdlr.Tst_vac_but = HP_CRYO_VAC_LVL_2; break;
//		default: return;
//	}
	
	
//	/* Lanzamos test de vacum si esta todo seleccionado correctamente y hay HP */
//	if( HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF) &&
//		AppGUIdata.tstVacHdlr.selVacLvl != APP_GUI_NO_VAC_LVL_SELECTED &&
//		AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED &&
//		AppGUIdata.slot[HPindex].selTrtArea != AppGUIfullBodyNO_AREA)
//	{
//		/* Hay manípulo y tiene test configurado */
//		HPcryoTestVacumStartDflt( HP_CRYO_TEST_VAC_MODE_MANUAL, AppGUIdata.tstVacHdlr.Tst_vac_but, 1, HP, PRF);
//	}
//	else
//	{
//		/* Posible pitido indicando que no se ha podido iniciar */
//	}
	
//	//Actualizamos el panel de control
//	for( HPindex=0;HPindex<APP_GUI_MAXNUM_HP;HPindex++)	AppGUIhandleCtrlPanel(AppGUIdata.slot[HPindex].isCtrlPnlShow, HPindex);
}

void CBKbutPopUpTstVacAutoF( void *widget)
{
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	uint8 HPindex = AppGUIdata.tstVacHdlr.HPindex;
	
//	/* Lanzamos test de vacum si esta todo seleccionado correctamente y hay HP */
//	if( HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF) &&
//		AppGUIdata.tstVacHdlr.selVacLvl != APP_GUI_NO_VAC_LVL_SELECTED &&
//		AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED &&
//		AppGUIdata.slot[HPindex].selTrtArea != AppGUIfullBodyNO_AREA)
//	{
//		/* Hay manípulo y tiene test configurado */
//		if (HPcryoIsAutoModeAvaible(HP, PRF))	{HPcryoTestVacumStartDflt( HP_CRYO_TEST_VAC_MODE_AUTO, AppGUIdata.tstVacHdlr.selVacLvl, 1, HP, PRF);}
//	}
//	else
//	{
//		/* Posible pitido indicando que no se ha podido iniciar */
//	}
}

void CBKbutPopUpVacSmallLvlF( void *widget)
{
//	cHPcryoTrtVacLvls vac_level;
//	//uint8 HPindex;
//	tHPcryoData *HP;
//	tPRFdata *PRF;
	
//	HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[AppGUIdata.tstVacHdlr.HPindex], &HP, &PRF);
	
//	/* Casteamos al tipo widget */
//	stWidget *w = ( stWidget *)widget;
	
//	/* Obtenemos el indice del HP en función del widget */
//	switch( w->id)
//	{
//		case butPopUpTstVacSmallLowLvl: vac_level = HP_CRYO_VAC_LVL_0; break;
//		case butPopUpTstVacSmallMedLvl: vac_level = HP_CRYO_VAC_LVL_1; break;
//		case butPopUpTstVacSmallHighLvl: vac_level = HP_CRYO_VAC_LVL_2; break;
//		default: return;
//	}
	
//	AppGUIdata.tstVacHdlr.selVacLvl = vac_level;
	
//	/* Ajustamos al nuevo nivel de vacum si es un valor válido */
//	if( AppGUIdata.slot[AppGUIdata.tstVacHdlr.HPindex].selVacLvl != APP_GUI_NO_VAC_LVL_SELECTED)
//	{
//		if( HPcryoTrtAdjustVacumDflt( AppGUIdata.tstVacHdlr.selVacLvl, HP, PRF))
//		{
//			AppGUIdata.slot[AppGUIdata.tstVacHdlr.HPindex].selVacLvl = vac_level;
//		}
//	}
	
//	/* Desactivamos el popUp de test de vacum */
//	AppGUIhandleTstVacSMALLPopUp( 0, AppGUIdata.tstVacHdlr.HPindex);
//	GUIsetSwitchStatus( APP_GUI_TRT_SCR_BUT_TSTVAC_WIDGETS[AppGUIdata.tstVacHdlr.HPindex], 0);
	
////	for( HPindex = 0; HPindex < APP_GUI_MAXNUM_HP; HPindex++)
////	{
////		if (HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF)  && (AppGUIdata.slot[HPindex].selTrtArea != APP_GUI_NUM_FULL_BODY_AREAS) && (AppGUIdata.slot[HPindex].selTrtDot != APP_GUI_NO_TRT_DOT_SELECTED))
////		{
////			AppGUIapplyTimeRestriction(HPindex, HP, PRF);
////			AppGUIdata.slot[HPindex].trtTime = AppGUIcalcTrtTime( HPindex, HPcryoTrtGetTimeSeconds( HP, PRF),
////																  HPcryoTrtGetTreatmentTotalTimeSeconds( HP, PRF));
////		}
////		AppGUIhandleCtrlPanel( 1, HPindex);		//Se usaba cuando se ponian todos los botones en marca de agua al activar un popup
////	}
//	//Se revisan las zonas de tratamiento ya que también gestiona el botón de info (para que se quite al activar otro popup
//	AppGUIhandleTrtZone();
}

void CBKswPopUpTstVacLvlOnF( void *widget)
{
//	uint8 i;
		
//	/* Casteamos al tipo widget */
//	stWidget *w = ( stWidget *)widget;
	
//	/* Seleccionamos el nivel de vacum según el id del widget */
//	i = HP_CRYO_VAC_LVL_0;
//	while( i < HP_CRYO_VAC_LVL_NUM && APP_GUI_TRT_SCR_POPUP_TST_VAC_SW_LIST[i] != w->id){ i++;}
//	if( i >= HP_CRYO_VAC_LVL_NUM){ AppGUIdata.tstVacHdlr.selVacLvl = APP_GUI_NO_VAC_LVL_SELECTED;}
//	else{ AppGUIdata.tstVacHdlr.selVacLvl = i;}
	
//	AppGUIdata.slot[AppGUIdata.tstVacHdlr.HPindex].selVacLvl = AppGUIdata.tstVacHdlr.selVacLvl;
	
//	/* Hacemos los switches excluyentes */
//	for( i = HP_CRYO_VAC_LVL_0; i < HP_CRYO_VAC_LVL_NUM; i++)
//	{
//		/* Todos los switches que no sean el que ha llamado a estado OFF */
//		if( APP_GUI_TRT_SCR_POPUP_TST_VAC_SW_LIST[i] != w->id)
//		{
//			GUIsetSwitchStatus( APP_GUI_TRT_SCR_POPUP_TST_VAC_SW_LIST[i], 0);
//		}
//	}
		
//	/* Refrescamos el popUp */
//	AppGUIhandleTstVacPopUp( 1, AppGUIdata.tstVacHdlr.HPindex);
}

void CBKswPopUpTstVacLvlOffF( void *widget)
{
//	/* Casteamos al tipo widget */
//	stWidget *w = ( stWidget *)widget;
	
//	/* Si es el tiempo actualmente seleccionado lo mantenemos seleccionado */
//	if( APP_GUI_TRT_SCR_POPUP_TST_VAC_SW_LIST[AppGUIdata.tstVacHdlr.selVacLvl] == w->id)
//	{
//		GUIsetSwitchStatus( w->id, 1);
//		//AppGUIdata.tstVacHdlr.selVacLvl = APP_GUI_NO_VAC_LVL_SELECTED;
//	}
	
//	/* Refrescamos el popUp */
//	AppGUIhandleTstVacPopUp( 1, AppGUIdata.tstVacHdlr.HPindex);
}

void CBKbutPopUpErrOkF( void *widget)
{
//	uint8 HPindex = 0;
	
//	/* Casteamos al tipo widget */
//	stWidget *w = ( stWidget *)widget;
	
//	/* En función del widget que sea hacemos clear del error */
//	if( w->id == butPopUpErrOkUC){ ERR_clear( Maq);}
//	else
//	{
//		switch( w->id)
//		{
//			case butPopUpErrOkHP1: HPindex = APP_GUI_HP1_ID; break;
//			case butPopUpErrOkHP2: HPindex = APP_GUI_HP2_ID; break;
//			case butPopUpErrOkHP3: HPindex = APP_GUI_HP3_ID; break;
//			case butPopUpErrOkHP4: HPindex = APP_GUI_HP4_ID; break;
//		}
	
//		/* Error clear según la distribución de slots */
//		ERR_clear( APP_GUI_SLOT_DISTRIBUTION[HPindex]);
//	}
	
//	//Actualizamos el panel de control
//	for( HPindex=0;HPindex<APP_GUI_MAXNUM_HP;HPindex++)	AppGUIhandleCtrlPanel(AppGUIdata.slot[HPindex].isCtrlPnlShow, HPindex);
	
//	/* Actualizamos el estado grafico de los popUp de error */
//	AppGUIhandleErrPopUps();
}

void CBKbutNumCalcF( void *widget)
{
    uint8 numIn;
	
    /* Casteamos al tipo widget */
    stWidget *w = ( stWidget *)widget;
	
    switch(w->id)
    {
        case ButNum0Calc:	numIn = 0; if(AppGUIdata.CalcHandler.numDigitsIn==0){return;} break;
        case ButNum1Calc:	numIn = 1; break;
        case ButNum2Calc:	numIn = 2; break;
        case ButNum3Calc:	numIn = 3; break;
        case ButNum4Calc:	numIn = 4; break;
        case ButNum5Calc:	numIn = 5; break;
        case ButNum6Calc:	numIn = 6; break;
        case ButNum7Calc:	numIn = 7; break;
        case ButNum8Calc:	numIn = 8; break;
        case ButNum9Calc:	numIn = 9; break;
        default: return;
    }
	
    if (AppGUIdata.CalcHandler.numDigitsIn < APP_GUI_MAX_DIGITS_CALC_SCREEN)
    {
        AppGUIdata.CalcHandler.numDigitsIn++;
        AppGUIdata.CalcHandler.CalcCode = (AppGUIdata.CalcHandler.CalcCode*10)+(float)(numIn);
    }
	
    wdgWpr.GUIsetNumViewerNum( NumVwrPantallaCalc, AppGUIdata.CalcHandler.CalcCode, 0);
}

void CBKbutEnterCalcF( void *widget)
{
    uint8_t buff_Osc_Temp[1];
    uint32 special_action_code;
    uint32 execution_code;
    tHPcryoData *HP;
    tPRFdata *PRF;
    uint8 bufGPRS[22]; //#JM_GPRS V7790
	
//	if (AppGUIdata.CalcHandler.CalcCode == 1.0){BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );}
//	if (AppGUIdata.CalcHandler.CalcCode == 2.0){BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );}
//	if (AppGUIdata.CalcHandler.CalcCode == 3.0){BUZZ_Configure(1, 100, PATRO_SO_WARNING );}
//	if (AppGUIdata.CalcHandler.CalcCode == 4.0){BUZZ_Configure(1, 100, PATRO_SO_CALIBRATION );}
//	if (AppGUIdata.CalcHandler.CalcCode == 5.0){BUZZ_Configure(1, 100, PATRO_SO_FINAL_TRT );}
//	if (AppGUIdata.CalcHandler.CalcCode == 6.0){BUZZ_Configure(1, 100, PATRO_SO_ERROR );}
//	if (AppGUIdata.CalcHandler.CalcCode == 7.0){BUZZ_Configure(1, 100, PATRO_SO_FINAL_TRT_CONFIG );}
//	if (AppGUIdata.CalcHandler.CalcCode == 8.0){BUZZ_Configure(1, 100, PATRO_SO_BUT_SW_PULSED );}
	
    if (AppGUIdata.CalcHandler.numDigitsIn == APP_GUI_MAX_DIGITS_CALC_SCREEN)
    {
        special_action_code = (uint32)AppGUIdata.CalcHandler.CalcCode / APP_GUI_CALC_DECODIFICATION_FACTOR;
        if (special_action_code == APP_GUI_CALC_SPECIAL_ACTION_CODE)
        {
            execution_code = (uint32)AppGUIdata.CalcHandler.CalcCode % APP_GUI_CALC_DECODIFICATION_FACTOR;
            switch (execution_code)
            {
                case AppGUIcalc_RTC_time:
                    AppGUIdata.CalcHandler.RTC_time_flag = 1;
                    break;
                case AppGUIcalc_RTC_date:
                    AppGUIdata.CalcHandler.RTC_date_flag = 1;
                    break;
                case AppGUIcalc_Vaciado:
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
                    break;
                case AppGUIcalc_Llenado:
                    AppGUIdata.CalcHandler.FillingWater_flag = 1;
                    break;
                case AppGUIcalc_SATscreen:
                    AppGUIchangeScreen( APP_GUI_SAT_SCREEN);
                    break;
                case AppGUIcalc_FATIGAscreen:
                    AppGUIchangeScreen( APP_GUI_FATIGUE_SCREEN);
                    EXP_UCfatigaStart();
                    break;
					
                case AppGUIcalc_ProgCurved:
                    if(HPcryoGetFromSlot(PRF_HW_SLOT1, &HP, &PRF)){	if(HPcryoReconfigHP( HP_CRYO_MODEL_CURVED, HP, PRF)){		BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );	}	}	break;
                case AppGUIcalc_ProgTight:
                    if(HPcryoGetFromSlot(PRF_HW_SLOT1, &HP, &PRF)){	if(HPcryoReconfigHP( HP_CRYO_MODEL_TIGHT, HP, PRF)){		BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );	}	}	break;
                case AppGUIcalc_ProgStright:
                    if(HPcryoGetFromSlot(PRF_HW_SLOT1, &HP, &PRF)){	if(HPcryoReconfigHP( HP_CRYO_MODEL_STRIGHT, HP, PRF)){		BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );	}	}	break;
                case AppGUIcalc_ProgTiny:
                    if(HPcryoGetFromSlot(PRF_HW_SLOT1, &HP, &PRF)){	if(HPcryoReconfigHP( HP_CRYO_MODEL_TINY, HP, PRF)){			BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );	}	}	break;
                case AppGUIcalc_ProgTinyCurved:
                    if(HPcryoGetFromSlot(PRF_HW_SLOT1, &HP, &PRF)){	if(HPcryoReconfigHP( HP_CRYO_MODEL_TINY_CURVED, HP, PRF)){	BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );	}	}	break;
                case AppGUIcalc_ProgDouble:
                    if(HPcryoGetFromSlot(PRF_HW_SLOT1, &HP, &PRF)){	if(HPcryoReconfigHP( HP_CRYO_MODEL_DOUBLE, HP, PRF)){		BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );	}	}	break;
                case AppGUIcalc_ProgOval:
                    if(HPcryoGetFromSlot(PRF_HW_SLOT1, &HP, &PRF)){	if(HPcryoReconfigHP( HP_CRYO_MODEL_OVAL, HP, PRF)){			BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );	}	}	break;
                case AppGUIcalc_ProgOvalCurved:
                    if(HPcryoGetFromSlot(PRF_HW_SLOT1, &HP, &PRF)){	if(HPcryoReconfigHP( HP_CRYO_MODEL_OVAL_CURVED, HP, PRF)){	BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );	}	}	break;
                case AppGUIcalc_ProgAngled:
                    if(HPcryoGetFromSlot(PRF_HW_SLOT1, &HP, &PRF)){	if(HPcryoReconfigHP( HP_CRYO_MODEL_ANGLED, HP, PRF)){		BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );	}	}	break;
				
                case AppGUIcalc_OscTempIDLEenable:
                    EXPdata.UC.Config_Param.data.ModeTempOscIDLE = 1;
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;
                case AppGUIcalc_OscTempIDLEdisable:
                    EXPdata.UC.Config_Param.data.ModeTempOscIDLE = 0;
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;
					
                case AppGUIcalc_ReuseLabelEnable:
                    EXPdata.UC.Config_Param.data.ModeRecicleLabel = 1;
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;
					
                case AppGUIcalc_ReuseLabelDisable:
                    EXPdata.UC.Config_Param.data.ModeRecicleLabel = 0;
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;

                case AppGUIcalc_TempSlopeEnable:
                    EXPdata.UC.Config_Param.data.ModeTempSlope = 0;
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;

                case AppGUIcalc_TempSlopeDisable:
                    EXPdata.UC.Config_Param.data.ModeTempSlope = 1;
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;

                case AppGUIcalc_TempSecureEnable:
                    EXPdata.UC.Config_Param.data.ModeTempSecure = 1;
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;

                case AppGUIcalc_TempSecureDisable:
                    EXPdata.UC.Config_Param.data.ModeTempSecure = 0;
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;
					
                case AppGUIcalc_ErrSecureEnable:
                    EXPdata.UC.Config_Param.data.ModeErrSec = 0;
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;

                case AppGUIcalc_ErrSecureDisable:
                    EXPdata.UC.Config_Param.data.ModeErrSec = 1;
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;
					
					
                case AppGUIcalc_ErrSecureDeltaTempEnable:
                    EXPdata.UC.Config_Param.data.ModeErrDeltaTempSec = 0;
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;

                case AppGUIcalc_ErrSecureDeltaTempDisable:
                    EXPdata.UC.Config_Param.data.ModeErrDeltaTempSec = 1;
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;
                    /*
                case AppGUIcalc_LangSelectionEnable:
                    AppGUIdata.CalcHandler.FlagSkipLangSelection = 0;
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
                    break;
					
                case AppGUIcalc_LangSelectionDisable:
                    AppGUIdata.CalcHandler.FlagSkipLangSelection = 1;
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
                    break;
                    */
                case AppGUIcalc_SendASCII_LOG:
                    if(AppLOG_GetCommand() == AppLOG_No_Command)
                    {	AppLOG_SetCommand(AppLOG_SendASCII_LOG);	}
                    else
                    {	BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );	}
                    break;
                case AppGUIcalc_SendRAW_LOG:
                    if(AppLOG_GetCommand() == AppLOG_No_Command)
                    {	AppLOG_SetCommand(AppLOG_SendRAW_LOG);	}
                    else
                    {	BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );	}
                    break;
                case AppGUIcalc_EraseLOG:
                    if(AppLOG_GetCommand() == AppLOG_No_Command)
                    {	AppLOG_SetCommand(AppLOG_Erase_LOG);		}
                    else
                    {	BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );	}
                    break;
                case AppGUIcalc_Send_USB_ASCII_LOG:
                    if(AppLOG_GetCommand() == AppLOG_No_Command)
                    {	AppLOG_SetCommand(AppLOG_Send_USB_ASCII_LOG);	}
                    else
                    {	BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );	}
                    break;
                case AppGUIcalc_Send_USB_RAW_LOG:
                    if(AppLOG_GetCommand() == AppLOG_No_Command)
                    {	AppLOG_SetCommand(AppLOG_Send_USB_RAW_LOG);	}
                    else
                    {	BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );	}
                    break;
                case AppGUIcalc_SendRecent_LOG:
                    if(AppLOG_GetCommand() == AppLOG_No_Command)
                    {	AppLOG_SetCommand(AppLOG_Send_RecentLOG_ASCII);	}
                    else
                    {	BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );	}
                    break;
                case AppGUIcalc_Send_USB_Recent_LOG:
                    if(AppLOG_GetCommand() == AppLOG_No_Command)
                    {	AppLOG_SetCommand(AppLOG_Send_RecentLOG_ASCII_USB);	}
                    else
                    {	BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );	}
                    break;
                case AppGUIcalc_RecordLOG_enable:
                    EXPdata.UC.Config_Param.data.ModeRecLOG = 0;
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;
                case AppGUIcalc_RecordLOG_disable:
                    EXPdata.UC.Config_Param.data.ModeRecLOG = 1;
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;
                case AppGUIcalc_GPRS_Del_country: //#JM_GPRS V7790 borrar paises pero conservar que la máquina tiene placa
                    AppGPRSClear(&EXPdata.UC.Config_Param.data.GPRS_iniciado,EXPdata.UC.Config_Param.data.MCC,2);
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;
                case AppGUIcalc_GPRS_Clear: //#JM_GPRS V7790
                    AppGPRSClear(&EXPdata.UC.Config_Param.data.GPRS_iniciado,EXPdata.UC.Config_Param.data.MCC,0);
                    while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
                    BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
                    AppGUIdata.CalcHandler.MachineModeChngFlag = 1;		/* V7790 - LOG modes */
                    break;
                default: break;
            }
        }
    }
}

void CBKbutCECalcF( void *widget)
{
    AppGUIdata.CalcHandler.numDigitsIn = 0;
    AppGUIdata.CalcHandler.CalcCode = 0.0;
    AppGUIdata.CalcHandler.RTC_time_flag = 0;
    AppGUIdata.CalcHandler.RTC_date_flag = 0;
    AppGUIdata.CalcHandler.FillingWater_flag = 0;
	
    /* Cerrar electrovalvula */
    EXP_UChandleVentEV( 0);
	
    wdgWpr.GUIsetNumViewerNum( NumVwrPantallaCalc, AppGUIdata.CalcHandler.CalcCode, 0);
}

void CBKbutSoftUpdateCfgF ( void *widget)
{
//	BUZZ_Configure(1, 100, PATRO_SO_BUT_SW_PULSED );
//	AppGUIdata.CfgHandler.BOOT_rqst = 1;
//	BOOT_Enable();
//	BOOT_Write();
}

void CBKbutRecargaCoolantF ( void *widget)
{
//	if(AppGUIdata.CfgHandler.FillingWater_flag == 0)
//	{	AppGUIdata.CfgHandler.FillingWater_flag = 1;	}
//	else
//	{	AppGUIdata.CfgHandler.FillingWater_flag = 0;	}
}

void CBKswResuctionsVierewF ( void *widget)
{
//	if(EXPdata.UC.Config_Param.data.ModeResuctionsViewer == 1)
//	{
//		EXPdata.UC.Config_Param.data.ModeResuctionsViewer = 0;
//		while(BOOT_SaveConfigParamSerialFlash (EXPdata.UC.Config_Param.vector) != BOOT_SerialFlash_EscrituraCorrecta);
//		BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
//	}
//	else
//	{
//		EXPdata.UC.Config_Param.data.ModeResuctionsViewer = 1;
//		while(BOOT_SaveConfigParamSerialFlash (EXPdata.UC.Config_Param.vector) != BOOT_SerialFlash_EscrituraCorrecta);
//		BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
//	}
}

void CBKswCfgTemperatureViewerF ( void *widget)
{
//	if(EXPdata.UC.Config_Param.data.ModeTemperatureViewer == 1)
//	{
//		EXPdata.UC.Config_Param.data.ModeTemperatureViewer = 0;
//		while(BOOT_SaveConfigParamSerialFlash (EXPdata.UC.Config_Param.vector) != BOOT_SerialFlash_EscrituraCorrecta);
//		BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
//	}
//	else
//	{
//		EXPdata.UC.Config_Param.data.ModeTemperatureViewer = 1;
//		while(BOOT_SaveConfigParamSerialFlash (EXPdata.UC.Config_Param.vector) != BOOT_SerialFlash_EscrituraCorrecta);
//		BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
//	}
}

void CBKbutCleanUpHPF ( void *widget)
{
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	uint8 HPindex;
	
//	/* Casteamos al tipo widget */
//	stWidget *w = ( stWidget *)widget;
	
//	/* Obtenemos el indice del HP en función del widget */
//	switch( w->id)
//	{
//		case butCfgCleanUpHP1: HPindex = 0; break;
//		case butCfgCleanUpHP2: HPindex = 1; break;
//		case butCfgCleanUpHP3: HPindex = 2; break;
//		case butCfgCleanUpHP4: HPindex = 3; break;
//		default: return;
//	}
	
//	if( HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
//	{
//		if(HP->cleanUp.status == HP_CRYO_CLEAN_UP_DONE)
//		{
//			HP->cleanUpRqst = HP_CRYO_CLEAN_UP_RQST_FORCED;
//			HP->cleanUpInitOrEnd = HP_CRYO_CLEAN_UP_INIT_OF_TRT;
//		}
//	}
}

void CBKbutCleanUpHProundF ( void *widget)
{
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	uint8 HPindex;
	
//	for (HPindex=0;HPindex<APP_GUI_MAXNUM_HP;HPindex++)
//	{
//		if( HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
//		{
//			if((HP->cleanUp.cancelled_times>0) && (HP->cleanUp.status == HP_CRYO_CLEAN_UP_DONE))
//			{
//				HP->cleanUpRqst = HP_CRYO_CLEAN_UP_RQST_FORCED;
//				HP->cleanUpInitOrEnd = HP_CRYO_CLEAN_UP_INIT_OF_TRT;
//			}
//		}
//	}
}

void CBKswLanguageF ( void *widget)
{		
//	//	/* Casteamos al tipo widget */
//	//	stWidget *w = ( stWidget *)widget;
//	//
//	//	/* Se almacena el lenguaje seleccionado */
//	//	EXP_UC_set_Language (w->id - APP_GUI_LANG_SW_WIDGET_LANG_LIST[App_GUI_Frances] + 1);
//	//	while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
}

void CBKswCountryF ( void *widget)		//V7790 - DISCLAIMER
{		
//	LDD_RTC_TTime Time;
//	/* Casteamos al tipo widget */
//	stWidget *w = ( stWidget *)widget;
	
//	RTC_get_time (&Time);
	
//	/* Se almacena el lenguaje seleccionado */
//	/*
//	EXP_UC_set_Country (w->id - APP_GUI_LANG_SW_WIDGET_COUNTRY_LIST[App_GUI_USA] + 1);
//	EXP_UC_set_Month_REF((uint8)Time.Month);
//	while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
//	*/
}

void CBKbutPopUpCleanUpF ( void *widget)
{
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	uint8 HPindex;
	
//	/* Casteamos al tipo widget */
//	stWidget *w = ( stWidget *)widget;
	
//	/* Obtenemos el indice del HP en función del widget */
//	switch( w->id)
//	{
//		case butPopUpCleanHP1: HPindex = 0; break;
//		case butPopUpCleanHP2: HPindex = 1; break;
//		case butPopUpCleanHP3: HPindex = 2; break;
//		case butPopUpCleanHP4: HPindex = 3; break;
//		default: return;
//	}
	
//	if( HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
//	{
//		HPcryoCleanUpFinishCountDown( HP, PRF);
//	}
}

void CBKbutPopUpCleanUpYESF ( void *widget)
{
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	uint8 HPindex;
	
//	/* Casteamos al tipo widget */
//	stWidget *w = ( stWidget *)widget;
	
//	/* Obtenemos el indice del HP en función del widget */
//	switch( w->id)
//	{
//		case butPopUpCleanYESHP1: HPindex = 0; break;
//		case butPopUpCleanYESHP2: HPindex = 1; break;
//		case butPopUpCleanYESHP3: HPindex = 2; break;
//		case butPopUpCleanYESHP4: HPindex = 3; break;
//		default: return;
//	}
	
//	if( HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
//	{
//		HPcryoCleanUpAllowClean( 1, HP, PRF);
//	}
}

void CBKbutPopUpCleanUpNOF ( void *widget)
{
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	uint8 HPindex;
	
//	/* Casteamos al tipo widget */
//	stWidget *w = ( stWidget *)widget;
	
//	/* Obtenemos el indice del HP en función del widget */
//	switch( w->id)
//	{
//		case butPopUpCleanNOHP1: HPindex = 0; break;
//		case butPopUpCleanNOHP2: HPindex = 1; break;
//		case butPopUpCleanNOHP3: HPindex = 2; break;
//		case butPopUpCleanNOHP4: HPindex = 3; break;
//		default: return;
//	}
	
//	if( HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
//	{
//		HPcryoCleanUpAllowClean( 0, HP, PRF);
//	}
}

void CBKbutPopUpCleanUpCancelF ( void *widget)
{
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	uint8 HPindex;
	
//	/* Casteamos al tipo widget */
//	stWidget *w = ( stWidget *)widget;
	
//	/* Obtenemos el indice del HP en función del widget */
//	switch( w->id)
//	{
//		case butPopUpCleanCancelHP1: HPindex = 0; break;
//		case butPopUpCleanCancelHP2: HPindex = 1; break;
//		case butPopUpCleanCancelHP3: HPindex = 2; break;
//		case butPopUpCleanCancelHP4: HPindex = 3; break;
//		default: return;
//	}
	
//	if(HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[HPindex], &HP, &PRF))
//	{
//		/* Cancelar el tratamiento e incrementar el contador y guardarlo en la memoria del aplicador */
//		HP->cleanUp.cancelled_times++;
//		HPcryoCleanUpCancelledTimesSentToHP(HP->cleanUp.cancelled_times, HP, PRF);
//		HPcryoCleanUpStop(HP, PRF);
//	}
}

void CBKbutSATnextPageF ( void *widget)
{
//	uint8 HPindex = 0;
	
//	AppGUIdata.SATHandler.Page++;
//	AppGUIdata.SATHandler.PageNum++;
	
//	switch(AppGUIdata.SATHandler.Page)
//	{
//		case HP1_Page:	HPindex = APP_GUI_HP1_ID;	break;
//		case HP2_Page:	HPindex = APP_GUI_HP2_ID;	break;
//		case HP3_Page:	HPindex = APP_GUI_HP3_ID;	break;
//		case HP4_Page:	HPindex = APP_GUI_HP4_ID;	break;
//		default:	break;
//	}
	
//	GUIsetSwitchStatus(SwVacuum, AppGUIdata.SATHandler.VacuumSwitch[HPindex]);
//	GUIsetSwitchStatus(SwFrio, AppGUIdata.SATHandler.FrioSwitch[HPindex]);
//	GUIsetSwitchStatus(SwTestLed, AppGUIdata.SATHandler.TestLedSwitch[HPindex]);
//	GUIsetSwitchStatus(SwTestLedRGB, AppGUIdata.SATHandler.TestLedRGBSwitch[HPindex]);
}

void CBKbutSATprevPageF ( void *widget)
{
//	uint8 HPindex = 0;
	
//	AppGUIdata.SATHandler.Page--;
//	AppGUIdata.SATHandler.PageNum--;
	
//	switch(AppGUIdata.SATHandler.Page)
//	{
//		case HP1_Page:	HPindex = APP_GUI_HP1_ID;	break;
//		case HP2_Page:	HPindex = APP_GUI_HP2_ID;	break;
//		case HP3_Page:	HPindex = APP_GUI_HP3_ID;	break;
//		case HP4_Page:	HPindex = APP_GUI_HP4_ID;	break;
//		default:	break;
//	}
	
//	GUIsetSwitchStatus(SwVacuum, AppGUIdata.SATHandler.VacuumSwitch[HPindex]);
//	GUIsetSwitchStatus(SwFrio, AppGUIdata.SATHandler.FrioSwitch[HPindex]);
//	GUIsetSwitchStatus(SwTestLed, AppGUIdata.SATHandler.TestLedSwitch[HPindex]);
//	GUIsetSwitchStatus(SwTestLedRGB, AppGUIdata.SATHandler.TestLedRGBSwitch[HPindex]);
}

void CBKswSATVacOnF ( void *widget)
{
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	uint8 HPindex = 0;
//	switch(AppGUIdata.SATHandler.Page)
//	{
//		case HP1_Page:	HPindex = APP_GUI_HP1_ID;	break;
//		case HP2_Page:	HPindex = APP_GUI_HP2_ID;	break;
//		case HP3_Page:	HPindex = APP_GUI_HP3_ID;	break;
//		case HP4_Page:	HPindex = APP_GUI_HP4_ID;	break;
//		default:	break;
//	}
//	AppGUIdata.SATHandler.VacuumSwitch[HPindex] = 1;
//	AppGUIdata.SATHandler.FrioSwitch[HPindex] = 0;
//	GUIsetSwitchStatus(SwFrio, AppGUIdata.SATHandler.FrioSwitch[HPindex]);
	
//	if(HPcryoGetFromSlot(HPindex+1, &HP, &PRF)){	HPcryoSATcoolingTestStop(HP, PRF);	}
}
void CBKswSATVacOffF ( void *widget)
{
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	uint8 HPindex = 0;
//	switch(AppGUIdata.SATHandler.Page)
//	{
//		case HP1_Page:	HPindex = APP_GUI_HP1_ID;	break;
//		case HP2_Page:	HPindex = APP_GUI_HP2_ID;	break;
//		case HP3_Page:	HPindex = APP_GUI_HP3_ID;	break;
//		case HP4_Page:	HPindex = APP_GUI_HP4_ID;	break;
//		default:	break;
//	}
//	AppGUIdata.SATHandler.VacuumSwitch[HPindex] = 0;
	
//	if(HPcryoGetFromSlot(HPindex+1, &HP, &PRF)){	HPcryoSATvacumTestStop(HP, PRF);	}
}
void CBKswSATFrioOnF ( void *widget)
{
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	uint8 HPindex = 0;
//	switch(AppGUIdata.SATHandler.Page)
//	{
//		case HP1_Page:	HPindex = APP_GUI_HP1_ID;	break;
//		case HP2_Page:	HPindex = APP_GUI_HP2_ID;	break;
//		case HP3_Page:	HPindex = APP_GUI_HP3_ID;	break;
//		case HP4_Page:	HPindex = APP_GUI_HP4_ID;	break;
//		default:	break;
//	}
//	AppGUIdata.SATHandler.VacuumSwitch[HPindex] = 0;
//	AppGUIdata.SATHandler.FrioSwitch[HPindex] = 1;
//	GUIsetSwitchStatus(SwVacuum, AppGUIdata.SATHandler.VacuumSwitch[HPindex]);
	
//	if(HPcryoGetFromSlot(HPindex+1, &HP, &PRF)){	HPcryoSATvacumTestStop(HP, PRF);	}
}
void CBKswSATFrioOffF ( void *widget)
{
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	uint8 HPindex = 0;
//	switch(AppGUIdata.SATHandler.Page)
//	{
//		case HP1_Page:	HPindex = APP_GUI_HP1_ID;	break;
//		case HP2_Page:	HPindex = APP_GUI_HP2_ID;	break;
//		case HP3_Page:	HPindex = APP_GUI_HP3_ID;	break;
//		case HP4_Page:	HPindex = APP_GUI_HP4_ID;	break;
//		default:	break;
//	}
//	AppGUIdata.SATHandler.FrioSwitch[HPindex] = 0;
	
//	if(HPcryoGetFromSlot(HPindex+1, &HP, &PRF)){	HPcryoSATcoolingTestStop(HP, PRF);	}
}
void CBKswSATrfidOnF ( void *widget)
{
//	AppGUIdata.SATHandler.RFIDSwitch = 1;
}
void CBKswSATrfidOffF ( void *widget)
{
//	AppGUIdata.SATHandler.RFIDSwitch = 0;
}

void CBKswSATtestLedOnF ( void *widget)
{
//	uint8 HPindex = 0;
//	switch(AppGUIdata.SATHandler.Page)
//	{
//		case HP1_Page:	HPindex = APP_GUI_HP1_ID;	break;
//		case HP2_Page:	HPindex = APP_GUI_HP2_ID;	break;
//		case HP3_Page:	HPindex = APP_GUI_HP3_ID;	break;
//		case HP4_Page:	HPindex = APP_GUI_HP4_ID;	break;
//		default:	break;
//	}
	
//	AppGUIdata.SATHandler.TestLedSwitch[HPindex] = 1;
}

void CBKswSATtestLedOffF ( void *widget)
{
//	uint8 HPindex = 0;
//	switch(AppGUIdata.SATHandler.Page)
//	{
//		case HP1_Page:	HPindex = APP_GUI_HP1_ID;	break;
//		case HP2_Page:	HPindex = APP_GUI_HP2_ID;	break;
//		case HP3_Page:	HPindex = APP_GUI_HP3_ID;	break;
//		case HP4_Page:	HPindex = APP_GUI_HP4_ID;	break;
//		default:	break;
//	}
	
//	AppGUIdata.SATHandler.TestLedSwitch[HPindex] = 0;
}

void CBKswSATtestLedRGBOnF ( void *widget)
{
//	uint8 HPindex = 0;
//	switch(AppGUIdata.SATHandler.Page)
//	{
//		case HP1_Page:	HPindex = APP_GUI_HP1_ID;	break;
//		case HP2_Page:	HPindex = APP_GUI_HP2_ID;	break;
//		case HP3_Page:	HPindex = APP_GUI_HP3_ID;	break;
//		case HP4_Page:	HPindex = APP_GUI_HP4_ID;	break;
//		default:	break;
//	}
	
//	AppGUIdata.SATHandler.TestLedRGBSwitch[HPindex] = 1;
}
void CBKswSATtestLedRGBOffF ( void *widget)
{
    uint8 HPindex = 0;
    switch(AppGUIdata.SATHandler.Page)
    {
        case HP1_Page:	HPindex = APP_GUI_HP1_ID;	break;
        case HP2_Page:	HPindex = APP_GUI_HP2_ID;	break;
        case HP3_Page:	HPindex = APP_GUI_HP3_ID;	break;
        case HP4_Page:	HPindex = APP_GUI_HP4_ID;	break;
        default:	break;
    }
	
    AppGUIdata.SATHandler.TestLedRGBSwitch[HPindex] = 0;
}

void CBKswFATIGUEfailBelloffF ( void *widget)
{
//	if(AppGUIdata.fatigue_fail){	AppGUIdata.fatigue_fail = 0;	}
}

void CBKbutOkSATerrF ( void *widget)
{
//	uint8 i;
	
//	GUIdisablePopUp( PopupErrorSAT);
//	for(i=Manip1;i<Max_perifs;i++)	ERR_clear(i);
}

void CBKbutReuseRFIDlabelF ( void *widget)
{
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	if(HPcryoGetFromSlot( APP_GUI_SLOT_DISTRIBUTION[AppGUIdata.RFIDhdlr.HPindex], &HP, &PRF))
//	{
//		HP->trt.Label_reuse = 1;
//	}
}
