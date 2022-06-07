/*
 * App.c
 *
 *  Created on: Jan 25, 2017
 *      Author: ingenieria1
 */

#include "Cpu.h"
#include "Ventilador_PIO.h"
#include "Events.h"
#include "HAL_LEDS.h"
#include "HAL_TICKS.h"
#include "TX_ENABLE_PIO.h"
#include "HAL_UART_5.h"
#include "Shtdn.h"
#include "tscrSPI.h"
#include "tscrIrq.h"
#include "HAL_PWM_1.h"
#include "HAL_RTC.h"
#include "HAL_UART_2.h"
#include "HAL_UART_4.h"
#include "HAL_WIFI_RESET_PIO.h"
#include "AD1.h"
#include "Ticks/Ticks.h"
#include "ProtocolMaster/ProtocolMaster.h"
#include "Buzzer/Buzzer.h"
#include "LED/LED.h" 
#include "string.h"
#include "stdio.h"
#include "GeneralDefines.h"
#include "UART/UART.h"
#include "stdlib.h"
#include "SPI_alr/SPI_alr.h"
#include "ExternalFlash/ExternalFlash.h"
#include "WiFi_WGM110/WiFi_WGM110.h"
#include "LEDsExterns/LEDsExterns.h"
#include "GUI/K70_GUI.h"
#include "System.h"
#include <math.h>
#include "ProtocolMaster/RS485/RS485.h" //debug proves
#include "BusAlarma/BusAlarma.h"
#include "TouchScreen/tscrPEX.h"
#include "DDR/DDR.h"
#include "poll.h"
#include "MSD/MSD.h"
#include "BOOT/boot.h"
#include "RFID/RFID.h"
#include "RTC/RTC.h"

#include "AppGUI/AppGUI.h"
#include "Expansora/Expansora.h"
#include "Perifericos/HPCryo.h"
#include "Perifericos/Perifericos.h"
#include "Error/gestionError.h"
#include "gestionMalloc/gestionMallocDynamic.h"
#include "WATCH_DOG/watchdog.h"

#include "AppLOG/AppLOG.h"
#include "ExternalNANDFlash/ExternalNANDFlash.h"
#include "VarFlash/VarFlash.h"
#include "Logs/Logs.h"
#include "test/test.h"
#include "Perifericos/Temp_SAFE.h"

#include "GPRS/GPRS.h"
#include "GPRS/AppGPRS.h"

/**VARIABLES GLOBALES**/
tK70_DDRdataPtr DDRdata;
uint8_t estado_standby;
uint8 APP_motorRFID=0;
LDD_TDeviceData *ptrFanMain;

extern const uint8 ptu8Bootloader[];

/* Descomentar si se quiere hacer debug */
//#define DEBUG

typedef enum
{
	APP_FAN_MAIN_OFF,
	APP_FAN_MAIN_ON
}cAPPfanMainOnOff;

typedef enum{
	
	APP_STATUS_IDLE=  0,
	
	APP_STATUS_INIT=  1,
	
	APP_STATUS_RUN=  2,
	
	APP_STATUS_BOOT=  3,
	
	APP_STATUS_CALIBRATION=  4,
	
	APP_STATUS_STANDBY=  5,

	APP_STATUS_ALARMBUS=  6,
			
	APP_STATUS_RESET=  7,

	APP_STATUS_INIT_REPAIRLUTANDCCN=8,
	
}AppStatus;

enum
{
	APP_BOOTWrite,
	APP_BOOTRead,
};

/**SoftwareVersion**/

typedef struct
{
	union
	{
		struct
		{
			uint8 version;
			uint8 model;
			uint8 week;	/* BCD */
			uint8 year;	/* BCD, decenas */
			
		}field;
		
		uint32 id; 
	}fileID;
	
	uint8 ptu8Description[0x3C];
	
}SoftVersion_t;

__attribute__ ((section(".versionsoft"))) const SoftVersion_t SoftVersion = 
{
		.fileID.field.version = 0x01,
		.fileID.field.model = 0x01,
		.fileID.field.week = 0xB,
		.fileID.field.year = 0x15
		,
		#ifdef DEBUG_STANDALONE
		.ptu8Description = {"\r\n2020-11-25 SW Main Version 7.790 DEBUG STANDALONE\r\n\0"}, 
		#else 
		.ptu8Description = {"\r\n2021-09-20 SW Main Version 7.791\r\n\0"},
		#endif
		
};	/* inicio es el FileID: anyo(2cifras), mes, dia, codigoFW(2cifras), version(2cifras) */

const uint8 ptu8DiesSetmana[7][10] =
{
		"Diumenge\0",
		"Dilluns\0",
		"Dimarts\0",
		"Dimecres\0",
		"Dijous\0",
		"Divendres\0",
		"Dissabte\0"
};

typedef union
{
    struct
    {
        uint32_t TAG;
        uint32_t CCN_pos;
        uint32_t LUT_pos;
    }values;
    uint8_t bytes[12];
}images_position_t;

/**VARIABLES LOCALES**/
void APP_Init(void);

returnstatus_t APP_Calibration(void);


/* MAIN*/
void APP_Main(void){
	
	/* DEBUG */
/* Variables Locales  */
	uint32 timeInitResetErrors;
	uint32 timerCalibration;
	AppStatus motorAppPrincipal=APP_STATUS_INIT;
	uint8 *srcCCN;
	uint8 *srcLUT;
	uint32 tmrWaitInit;
	returnstatus_t RFID_status;
	returnstatus_t RTC_status;
//	uint8_t data[9];
	uint8 exitStandbyTouch_flag;
	uint32 exitStandbyTouch_time = TICKS_GetTicks();
	uint32_t recoverImages;
	images_position_t posImages;
	uint8_t WiFiMAC[6];

	APP_Init();
		
	
	/* De inicio dejamos que las PCB's de la maquina se inicialicen correctamente, para ello
	 * esperamos 0,5 segundos */
	tmrWaitInit = TICKS_GetTicks();
	while( TICKS_DiffTicks( tmrWaitInit) < 500){}
	
	/* Forzamos un primer update de todos los modulos para iniciar variables correctamente */
	EXPupdate( 0);
	PRFupdate( 0);
	/* V7790 - TEMP SAFE */
	Temp_SAFE_Clear_all();
	/* V7790 - TEMP SAFE */
	
//	data[0] = 'U';
//	data[1] = 'P';
//	data[2] = 'D';
//	data[3] = 'A';
//	data[4] = 'T';
//	data[5] = 'E';
//	data[6] = 'E';
//	data[7] = 'N';
//	data[8] = 'D';
//	
//	while(EXTFLASH_EraseSector(0, 1)!=SUCCESS);
//	tmrWaitInit = TICKS_GetTicks();
//	while( TICKS_DiffTicks( tmrWaitInit) < 500){}
//	while(EXTFLASH_WriteBytes(0,data,9)!=SUCCESS);
	
	/* De inicio pueden haber saltado errores en la expansora al forzar un
	 * refresco justo arranca la maquina. Los reseteamos */
	ERR_clear( Manip1);
	ERR_clear( Manip2);
	ERR_clear( Manip3);
	ERR_clear( Manip4);
	ERR_clear( Maq);
	
	LED_Configure(0,255,1,1);
	
	tmrWaitInit = TICKS_GetTicks();
	UART_Transmit(INDEX_UART_2, (uint8*)SoftVersion.ptu8Description, strlen((char *)SoftVersion.ptu8Description));
	while( (UART_TransmitNOTFinished(INDEX_UART_2))&&(TICKS_DiffTicks(tmrWaitInit)<50) );
	
	
	VARFLASH_Init();
	WIFI_Init();
	recoverImages = 0;
	while(recoverImages < 0x8000)
	{
		WIFI_Motor();
		switch(recoverImages)
		{
		case 0:
			if(WIFI_TurnOnModule() == SUCCESS)
			{
				tmrWaitInit = TICKS_GetTicks();
				recoverImages++;
			}
			else if(TICKS_DiffTicks(tmrWaitInit) > 1000)
			{
				recoverImages = 2;
			}
			break;
		case 1:
			if(WIFI_GetMACaddress(WiFiMAC) == SUCCESS)
			{
				recoverImages+=2;
			}
			else if(TICKS_DiffTicks(tmrWaitInit) > 1000)
			{
				recoverImages = 2;
			}
			break;
		case 2:
			TEST_PrintInfo("WiFi err\r\n");
			WiFiMAC[0] = 1;
			WiFiMAC[1] = 2;
			WiFiMAC[2] = 3;
			WiFiMAC[3] = 4;
			WiFiMAC[4] = 5;
			WiFiMAC[5] = 6;
			recoverImages++;
			break;
		case 3:
			if(WIFI_TurnOffModule() == SUCCESS)
			{
				TEST_PrintValue ( "WiFiMAC %03d:", WiFiMAC[0]);
				TEST_PrintValue ( "%03d:", WiFiMAC[1]);
				TEST_PrintValue ( "%03d:", WiFiMAC[2]);
				TEST_PrintValue ( "%03d:", WiFiMAC[3]);
				TEST_PrintValue ( "%03d:", WiFiMAC[4]);
				TEST_PrintValue ( "%03d\r\n", WiFiMAC[5]);
				AppLOGsetWiFiMAC (WiFiMAC);
				AppGUIsetWiFiMAC (WiFiMAC);
				recoverImages++;
			}
			break;
		case 4:
			if(VARFLASH_SetBusy() == SUCCESS)
			{
				EXTNAND_Init();
				recoverImages++;
			}
			break;
		case 5:
			switch(EXTNAND_Initialize(1))	//con 0 buscaria bloques malos,deberia estar la nand de fabrica
			{
			case RUNNING: break;
			case SUCCESS:
				recoverImages++;
				break;
			case ERROR:
			default:
				TEST_PrintInfo("EXTNAND initialize err\r\n");
				recoverImages = 0xF0;
				break;
			}
			break;
		case 6:
			switch(VARFLASH_GetVars())
			{
			case RUNNING: break;
			case SUCCESS: //ha encontrado config
				TEST_PrintInfo("Config ok\r\n");
				recoverImages = 0x81;
				break;
			case IDLE:	//no ha encontrado config
				MemoryMap.var.var_flash.NANDBadBlockCount = 0;
				MemoryMap.var.var_flash.TreatmentCount = 0;
				MemoryMap.var.var_flash.FiFoNAND[0].ReadIndex = 0;
				MemoryMap.var.var_flash.FiFoNAND[0].WriteIndex = 0;
				MemoryMap.var.var_flash.FiFoNAND[0].u32NumBytes = 0;
				MemoryMap.var.var_flash.FiFoNAND[1].ReadIndex = 0;
				MemoryMap.var.var_flash.FiFoNAND[1].WriteIndex = 0;
				MemoryMap.var.var_flash.FiFoNAND[1].u32NumBytes = 0;
				TEST_PrintInfo("Config NO ok\r\n");
				recoverImages++;
				break;
			case ERROR:
			default:
				//no deberia entrar aqui nunca
				TEST_PrintInfo("Get conf err\r\n");
				recoverImages = 0xF0;
				break;
			}
			break;
		case 7:
			/* voy a borrar la parte alta de la serial flash */
			tmrWaitInit = EXTERNAL_FLASH_NAND_BAD_BLOCK;
			recoverImages++;
			break;
		case 8:
			switch(EXTFLASH_EraseSector(tmrWaitInit, 1))
			{
			case RUNNING: break;
			case SUCCESS:
				recoverImages++;
				break;
			case ERROR:
			default:
				TEST_PrintInfo("Erase flash err\r\n");
				recoverImages = 0xF0;
				break;
			}
			break;
		case 9:
			tmrWaitInit+=EXTERNAL_FLASH_ERASE_SECTOR_SIZE;
			if(tmrWaitInit >= EXTERNAL_FLASH_MEMORY_SIZE)
			{
				recoverImages++;
			}
			else
			{
				recoverImages--;
			}
			break;
		case 10:
			/* no hay config buena, venia de un FW antiguo. Hay que recolocar cosas */
			switch(EXTNAND_ReadBytes(0, posImages.bytes, 12))
			{
			case RUNNING: break;
			case SUCCESS:
				if(posImages.values.TAG == NandCodeZone_CCNLUT)
				{
					/* encontrada configuracion de posicion de imagenes, voy a copiarlas a la posicion 1 y 401 */
					if((posImages.values.CCN_pos == NandBlockWriteCCN_ORG) && (posImages.values.LUT_pos == NandBlockWriteLUT_ORG))
					{
						/* no hay que hacer nada */
						recoverImages = 0x80;
					}
					else
					{
						recoverImages = 0x10;
					}
				}
				else
				{
					/* no se donde estan las imagenes */
					TEST_PrintInfo("wtf!images?\r\n");
					recoverImages = 0xF0;
				}
				break;
			case ERROR:
			default:
				TEST_PrintInfo("NAND conf err\r\n");
				recoverImages = 0xF0;
				break;
			}
			break;
		case 0x10:
			/* copia del CCN y LUT del bloque 1 al 401 */
			tmrWaitInit = 0;
			recoverImages++;
			break;
		case 0x11:
			switch(EXTNAND_DataBlockMove((posImages.values.CCN_pos+tmrWaitInit)<<17, (NandBlockWriteCCN_ORG+tmrWaitInit)<<17, EXTERNAL_NAND_FLASH_PAGES_BLOCK))
			{
			case RUNNING: break;
			case SUCCESS:
				recoverImages++;
				TEST_PrintValue ( "Blk cp %04X\r\n", tmrWaitInit);
				break;
			case ERROR:
			default:
				TEST_PrintValue ( "BMV err %04X\r\n", tmrWaitInit);
				recoverImages = 0xF0;
				break;
			}
			break;
		case 0x12:
			switch(EXTNAND_EraseBlocks((posImages.values.CCN_pos+tmrWaitInit)<<17, 1))
			{
			case RUNNING: break;
			case SUCCESS:
				recoverImages++;
				TEST_PrintValue ( "Blk re %04X\r\n", tmrWaitInit);
				break;
			case ERROR:
			default:
				TEST_PrintInfo("Blk re err\r\n");
				recoverImages = 0xF0;
				break;
			}
			break;
		case 0x13:
			tmrWaitInit++;
			if(tmrWaitInit >= NandBlockWriteLUT_ORG+1)
			{
				/* he acabado de hacer copia */
				recoverImages++;
			}
			else
			{
				recoverImages = 0x11;
			}
			break;
		case 0x14:
			/* actualizar bloque 0 con la pos del lut y ccn */
			switch(EXTNAND_EraseBlocks(0, 1))
			{
			case RUNNING: break;
			case SUCCESS:
				recoverImages++;
				TEST_PrintInfo ( "Blk 0 erase\r\n");
				break;
			case ERROR:
			default:
				TEST_PrintInfo("NAND er 0 err\r\n");
				recoverImages = 0xF0;
				break;
			}
			break;
		case 0x15:
			switch(EXTNAND_WriteBytes(0,posImages.bytes,2048))
			{
			case RUNNING: break;
			case SUCCESS:
				recoverImages = 0x80;
				TEST_PrintInfo ( "Blk 0 updated\r\n");
				break;
			case ERROR:
			default:
				TEST_PrintInfo("Set conf err\r\n");
				recoverImages = 0xF0;
				break;
			}
			break;
//		case 0x50:
//			switch(VARFLASH_SetVars())
//			{
//			case RUNNING: break;
//			case SUCCESS:
//				recoverImages++;
//				break;
//			case ERROR:
//			default:
//				TEST_PrintInfo("Set vars err\r\n");
//				recoverImages = 0xF0;
//				break;
//			}
//			break;
//		case 0x51:
//			VARFLASH_SetFree();
//			recoverImages = 0xF0;
//			break;
		case 0x80:
			switch(VARFLASH_SetVars())
			{
			case RUNNING: break;
			case SUCCESS:
				recoverImages++;
				break;
			case ERROR:
			default:
				TEST_PrintInfo("Set vars err\r\n");
				recoverImages = 0xF0;
				break;
			}
			break;
		case 0x81:
			VARFLASH_SetFree();
			recoverImages = 0x8000;
			break;
		case 0xF0:
			WDOG_clear();
			motorAppPrincipal= APP_STATUS_CALIBRATION;
			recoverImages = 0x8000;
//            tmrWaitInit = TICKS_GetTicks();
//            while(TICKS_DiffTicks(tmrWaitInit) < 3000)    WDOG_clear();
//            recoverImages = 0;
			break;
		}
	}
	tmrWaitInit = TICKS_GetTicks();
	
	//cargamos zona CCN_LUT
	BOOT_LoadZone_CCNLUT ();
	tmrWaitInit = TICKS_GetTicks();	
	while( (UART_TransmitNOTFinished(INDEX_UART_2))&&(TICKS_DiffTicks(tmrWaitInit)<50) );
	
	#ifdef DEBUG_CONSOLE_MENU
		TEST_MenuTestRUN();
	#endif	
	
	timeInitResetErrors = TICKS_GetTicks();
	
	AppLOG_saveModes();	/* V7790 - LOG modes */
	GPRScomOrder( OPERACIO_LECTURA, 0, 0, 2, (uint8 *)(&tmrWaitInit));
	#ifdef DEBUG
		uint32 tPRF = TICKS_GetTicks(); //DEBUG
		uint32 tTotal = tPRF;
	#endif
	while(1)
	{
		WDOG_clear();
		
		#ifdef DEBUG
			tTotal = TICKS_DiffTicks( tTotal); 		//DEBUG
			tTotal = TICKS_GetTicks();				//DEBUG
		#endif
		
		/* Motores independientes del estado */	
		#ifdef DEBUG
			tEXP = TICKS_GetTicks();				//DEBUG
		#endif
		if( !EXPupdate( 1500))
		{	
			#ifdef DEBUG
				tPRF = TICKS_DiffTicks( tPRF); //DEBUG
				tPRF = TICKS_GetTicks(); //DEBUG
			#endif
			PRFupdate( 250);
		}
		else
		{
			#ifdef DEBUG
				tEXP = TICKS_DiffTicks( tEXP); //DEBUG
			#endif
		}
		#ifdef DEBUG
			tUPD = TICKS_GetTicks(); //DEBUG
		#endif
		ERR_update( 0);
		
		AppLOG_motor();
		
		if(TICKS_DiffTicks(timeInitResetErrors) < APP_INIT_TIME_RESET_ERROR)
		{
			ERR_clear(Manip1);
			ERR_clear(Manip2);
			ERR_clear(Manip3);
			ERR_clear(Manip4);
			ERR_clear(Maq);
		}
			
		LOGS_Motor();
		
		BusAlarm_Motor();		
		PROTMST_Motor();
		LEDsExternsMotor( 50);
		#ifdef DEBUG
			tUPD = TICKS_DiffTicks( tUPD); //DEBUG
		#endif
		
		/*Polling para reconfiguración del chip del touch*/
		TSCRN_polling (1000);	/*Cada segundo*/
		
		/* Comprobamos si el RTC esta funcionando */
		RTC_status = RTC_running();
		if( RTC_status == ERROR)
		{ 
			ERR_add( Err_RTC);
			RTC_start();
		} //DEBUG!!!
		else if ( RTC_status == SUCCESS)
		{	
			ERR_delete( Err_RTC);	
			ERR_warning_clear(Maq, Aviso_RTC);	
		}
				
		/* Activamos el ventilador de la cabina de la PCB MAIN */
		Ventilador_PIO_PutVal( ptrFanMain, APP_FAN_MAIN_ON);
		
		/*POLLING dle RFID para que no salte el Watchdog*/
		RFID_status = RFID_motor();
		if (RFID_status == ERROR)
		{
			ERR_add(Err_ComRFID);			//Aviso de error del RFID durante Polling
		}			
		else if(RFID_status == SUCCESS)
		{
			ERR_delete(Err_ComRFID);
			ERR_warning_clear(Maq, Aviso_RFID);
		}
		
		LED_Motor(0);
		
		
		switch(motorAppPrincipal )
		{  
			case APP_STATUS_IDLE:
				motorAppPrincipal= APP_STATUS_INIT;
				//GUIbackL(0x20);
				break;
			
			case APP_STATUS_INIT:
				timeInitResetErrors = TICKS_GetTicks();
				exitStandbyTouch_flag = 0;
				timerCalibration = TICKS_GetTicks();
				while( ((TICKS_GetTicks()-timerCalibration) < 5000) && (TSCRN_pulsed()));
				if(TSCRN_pulsed())
				{
					motorAppPrincipal= APP_STATUS_CALIBRATION;
				} 
				else
				{ 
					if(BOOT_CCNandLUTfromNandToDDR(&srcCCN, &srcLUT)== SUCCESS)
					{
						AppGUIinit(DDRdata, srcCCN, srcLUT);
						
						/* PDTE!! Esto hacerlo bien y en cada HP al iniciarse */
						EXP_UCconfigVacumPumpBehaviour( 12000, 600);
//						EXP_UCconfigHPvacumFactors( 0.30, 1.1, PRF_HW_SLOT1);
//						EXP_UCconfigHPvacumFactors( 0.30, 1.1, PRF_HW_SLOT2);
//						EXP_UCconfigHPvacumFactors( 0.30, 1.1, PRF_HW_SLOT3);
//						EXP_UCconfigHPvacumFactors( 0.30, 1.1, PRF_HW_SLOT4);
//						EXP_UCconfigHPoverHeat( 1, 1.0, PRF_HW_SLOT1);
//						EXP_UCconfigHPoverHeat( 1, 1.0, PRF_HW_SLOT2);
//						EXP_UCconfigHPoverHeat( 1, 1.0, PRF_HW_SLOT3);
//						EXP_UCconfigHPoverHeat( 1, 1.0, PRF_HW_SLOT4);
										
						if( EXP_UCgetStdBy())
						{ 
							motorAppPrincipal = APP_STATUS_STANDBY;
							exitStandbyTouch_time = TICKS_GetTicks();
						}
						else
						{ 
							motorAppPrincipal= APP_STATUS_RUN;
						}
									
					} 
					else{ motorAppPrincipal = APP_STATUS_INIT_REPAIRLUTANDCCN; }								
				} 	
				break;
										
			case APP_STATUS_INIT_REPAIRLUTANDCCN:		
				timeInitResetErrors = TICKS_GetTicks();
				BOOT_REPARELUTandCCN();	
				BOOT_Motor();
				motorAppPrincipal = APP_STATUS_INIT;
				break;
									 
			case APP_STATUS_RUN:
				#ifdef DEBUG
				 	 tGUI = TICKS_GetTicks(); //DEBUG
				#endif
				AppGUIupdate();
				#ifdef DEBUG
				tGUI = TICKS_DiffTicks( tGUI); //DEBUG
				#endif
				if( EXP_UCgetStdBy())
					{ 
						motorAppPrincipal = APP_STATUS_STANDBY;
						exitStandbyTouch_time = TICKS_GetTicks();
					}
				//BUZZ_Motor();
				GUIbackL(0x60);	
				//PROTMST_Motor();									
				break;
				
			case APP_STATUS_BOOT:				
				switch(BOOT_Motor())
				{	
					case BootCheckSectorNand:	
					case BootSUCCESS:			
					case BootIDLE:	
						Cpu_SystemReset();
						break;
					default: break;
				}
				break;
						
			case APP_STATUS_CALIBRATION: 	
				WDOG_disable();
				if(APP_Calibration() == SUCCESS)
				{
					motorAppPrincipal  =  APP_STATUS_BOOT;
					BOOT_Enable();
					BOOT_Write();	
				}
				GUIbackL(0x60);
				break;
						
			case APP_STATUS_STANDBY:
				if( !EXP_UCgetStdBy())
				{ 
					motorAppPrincipal = APP_STATUS_RUN;
					AppGUIchangeScreen( APP_GUI_LOAD_SCREEN);
					AppGUIinit_reconfig();
					//AppGUIinit(DDRdata, srcCCN, srcLUT);			//Se vuelven a hacer mallocs, pero no se han hecho frees
				}
				if(TSCRN_pulsed())
				{	
					exitStandbyTouch_flag = 1;	
				}
				else
				{	
					exitStandbyTouch_flag = 0;	exitStandbyTouch_time = TICKS_GetTicks();	
				}
				if((exitStandbyTouch_flag) && (TICKS_DiffTicks(exitStandbyTouch_time)>1000))
				{	
					EXP_UCexitStandby();
				}
				GUIbackL(0x00);
				break;
							
			case APP_STATUS_ALARMBUS:
					      
				break;
											
			case APP_STATUS_RESET:
				motorAppPrincipal= APP_STATUS_IDLE;
				Cpu_SystemReset();
				//  HAL_NVIC_SystemReset();
				break;
		}
	}
}

returnstatus_t APP_Calibration()
{
	returnstatus_t AppErrorCalibration=RUNNING;
	BUZZ_Configure(1, 100, PATRO_SO_CALIBRATION );
	if(TSCRN_calibration(DDRdata)==SUCCESS)
	{
		AppErrorCalibration= SUCCESS;
	}
	return AppErrorCalibration;
}

void APP_Init()
{
		GESMALLOC_Init();
		TICKS_Init();
		BUZZ_Init();
		LED_Init();
		LEDsExternsInit();
		SPI_Init(INDEX_SPI_2);
		UART_Init(INDEX_UART_2);
		PROTMST_Init();
		EXTFLASH_Init();
		DDRinit(&DDRdata, 0x70000000, 0x07E00000, K70_DDR_MODE_FAST, 0);	//0x07F00000
		BOOT_Init(DDRdata);
		TSCRN_init();
		LEDsExternsConfigure(LED_DL2, LEDsExterns_Intermitencias, LEDsExterns_Forever, LEDsExterns_LED_ON, 0, 600, 600,0);
		SYS_Init();
		ptrFanMain = Ventilador_PIO_Init( (LDD_TUserData *)NULL);
		RTC_init();
		ERR_init();
		PRFinit();				
		EXPinit();
		BusAlarm_Init();
		RFID_init();
		WDOG_init();
		AppLOG_init();
		LOGS_Init();
		GPRS_init();
		AppGPRS_init();
}
