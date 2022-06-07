/*
 * AppLOG.c
 *
 *  Created on: Jan 21, 2021
 *      Author: sguerrero
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include "AppLOG.h"
#include "../GeneralDefines.h"
//#include "UART/UART.h"
//#include "Logs/Logs.h"
//#include "../MSD/MSD.h"
//#include "../Buzzer/Buzzer.h"
//#include "../WATCH_DOG/watchdog.h"
//#include "../Perifericos/Temp_SAFE.h"
//#include "../GPRS/AppGPRS.h"

/* --- Constantes --- */
#define APP_LOG_MAX_INT16_VALUE	(int16)32767
#define APP_LOG_MIN_INT16_VALUE	(int16)-32768
#define APP_LOG_MAX_UINT8_VALUE 255
#define APP_LOG_MIN_UINT8_VALUE 0

#define APP_LOG_MIN_RAM_DATA_2_SAVE 		512			/* Minimos datos en RAM para almacenarlos */
#define APP_LOG_TIME_WITHOUT_SAVING_2_SAVE 	30000		/* Tiempo que ha de pasar sim guardar LOGs para almacenar los datos en RAM */

#define APP_LOG_TIME_STAMP_VECTOR_SIZE			6		/* Marca de tiempo para todos los datos del LOG */

#define APP_LOG_HP_DATA_VECTOR_SIZE				3		/* Estructura de características del aplicador */

#define APP_LOG_TRT_VECTOR_SIZE					43		/* Almacenado cada minuto dureante tratamiento */
#define APP_LOG_ERROR_VECTOR_SIZE				10		/* Almacenado cada vez que salta un error */
#define APP_LOG_WARNING_VECTOR_SIZE				6		/* Almacenado cada vez que salta un warning */
#define APP_LOG_MACHINE_VECTOR_SIZE				10		/* Almacenado cada 5 minutos */
#define APP_LOG_MODES_VECTOR_SIZE				7		/* Almacenado al arrancar el equipo y al cambiar los modos */

#define APP_LOG_TRT_ASCII_VECTOR_SIZE			199		/* Almacenado cada minuto dureante tratamiento en ASCII */
#define APP_LOG_ERROR_ASCII_VECTOR_SIZE			37		/* Almacenado cada vez que salta un error en ASCII */
#define APP_LOG_WARNING_ASCII_VECTOR_SIZE		31		/* Almacenado cada vez que salta un warning en ASCII */
#define APP_LOG_MACHINE_ASCII_VECTOR_SIZE		62		/* Almacenado cada 5 minutos en ASCII */
#define APP_LOG_MODES_ASCII_VECTOR_SIZE			87		/* Almacenado al arrancar el equipo y al cambiar los modos en ASCII */

#define APP_LOG_TRT_ASCII_DEFINITION			169		/* Cabecera de definiciones de tramas de tratamiento */
#define APP_LOG_MACHINE_ASCII_DEFINITION		73		/* Cabecera de definiciones de tramas de machine */

#define APP_LOG_RECENT_LOGS_2_SEND				3*5		/* 3 bloques x 5 tratamientos*/

/* --- Listas --- */
typedef enum
{
		AppLOG_TRT,					//0: Datos del aplicador del tratamiento
		AppLOG_Error,				//1: Errores
		AppLOG_Warning,				//2: Avisos
		AppLOG_Machine,				//3: Datos generales del equipo
		AppLOG_Modes,				//4: Modos de funcionamiento del equipo
		
		AppLOG_MaxLOGtypes
}lAppLOG_DataLogTypes;

/* --- Constantes ---*/

const char APP_LOG_HP_MODELS_ASCII [HP_CRYO_NUM_HP_MODELS][13] =
{
	{"           ;"},	//0
	{"     CURVED;"},	//1
	{"      TIGHT;"},	//2
	{"   STRAIGHT;"},	//3
	{"       TINY;"},	//4
	{"TINY CURVED;"},	//5
	{"     DOUBLE;"},	//6
	{"       OVAL;"},	//7
	{"OVAL CURVED;"},	//8
	{"      DELTA;"}	//9
};

/* --- Estructuras --- */
/* LOG EN MEMORIA */
typedef union
{
	struct
	{
		uint8 year;		//Anyo
		uint8 month;	//Mes
		uint8 day;		//Dia
		uint8 hour;		//Hora
		uint8 minute;	//Minutos
		uint8 seccond;	//Segundos
		
	}data;
	uint8 vector[APP_LOG_TIME_STAMP_VECTOR_SIZE];
}sApp_LOG_time_stamp;

typedef union
{
	struct
	{
		uint8 HPindex;		//Puerto de conexion del aplicador
		uint8 model;		//Modelo del aplicador
		uint8 fw_version;	//Version del FW del aplicador
	}data;
	uint8 vector[APP_LOG_HP_DATA_VECTOR_SIZE];
}sAppLOG_HPdata;

typedef union
{
	struct
	{
		uint8 LOG_data_type;				//Tipo de dato del LOG
		sApp_LOG_time_stamp time_stamp;		//Marca de tiempo
		sAppLOG_HPdata HP_data;				//Datos del aplicador
		uint8 Frostbite;					//Congelacion detectada
		uint8 label;						//Etiqueta empleada para el tratamineto
		uint8 return_flow;					//Flujo de retorno
		uint8 vac_rtry;						//Resucciones
		uint8 PW_pelt_1;					//Potencia peltier 1
		uint8 PW_pelt_2;					//Potencia peltier 2
		uint16 vac_set_point;				//Consigna de vacuum
		uint16 vac_level;					//Nivel de vacuum
		int16 temp_return;					//Temperatura de retorno
		int16 cal1;							//Calibracion 1
		int16 cal2;							//Calibracion 2
		int16 cal3;							//Calibracion 3
		int16 sns[HP_CRYO_MAX_TEMP_SNS];	//Sensors
		uint16 MCC;							//Mobile Country Code
		uint32 trt_num;						//Indice de tratamiento
	}data;
	uint8 vector[APP_LOG_TRT_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE + APP_LOG_HP_DATA_VECTOR_SIZE];
}sAppLOG_trt;

typedef union
{
	struct
	{
		uint8 LOG_data_type;		//Tipo de dato del LOG
		
		sApp_LOG_time_stamp time_stamp;			//Marca de tiempo

		uint8 dummy;							//Cumplir boundary
		uint16 err_code;						//Codigo del error
		uint16 dummy2;							//Cumplir boundary
		uint32 trt_num;							//Indice de tratamiento
	}data;
	uint8 vector[APP_LOG_ERROR_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE];
}sAppLOG_error;

typedef union
{
	struct
	{
		uint8 LOG_data_type;		//Tipo de dato del LOG
		
		sApp_LOG_time_stamp time_stamp;			//Marca de tiempo
		
		uint8 dummy;							//Cumplir boundary
		uint16 wng_code;						//Codigo del aviso
		uint16 dummy2;							//Cumplir boundary
	}data;
	uint8 vector[APP_LOG_WARNING_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE];
}sAppLOG_warning;

typedef union
{
	struct
	{
		uint8 LOG_data_type;		//Tipo de dato del LOG
		
		sApp_LOG_time_stamp time_stamp;			//Marca de tiempo
		
		uint8 total_flow;						//flujo total
		uint8 emergency_but;					//Boton de emergencia
		uint8 cool_tank_lvl;					//nivel del tanque de anticongelante
		int16 rad_in_temp;						//temperatura de entrada del radiador
		int16 rad_out_temp;						//Temperatura de salida del radiador
		int16 env_temp;							//Temperatura ambiente
	}data;
	uint8 vector[APP_LOG_MACHINE_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE];
}sAppLOG_machine;

typedef union
{
	struct
	{
		uint8 LOG_data_type;		//Tipo de dato del LOG
		
		sApp_LOG_time_stamp time_stamp;			//Marca de tiempo
		
		uint8 Oscillations;						//Oscilaciones en estado IDLE del aplicador
		uint8 Label_reuse;						//Reuso de etiquetas
		uint8 Temp_slope;						//Rampa de bajada de temperatura
		uint8 Temp_secure;						//Consigna de temperatura -5ºC
		uint8 Err_secure;						//Modo estricto de parametros de seguridad
		uint8 Err_delta_secure;					//Modo estricto del error del delta de temperatura
	}data;
	uint8 vector[APP_LOG_MODES_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE];
}sAppLOG_modes;

/* LOG A TRANSMITIR */

typedef union
{
	struct
	{
		char LOG_data_type[5];			//Tipo de dato del LOG	//TEMP;
		
		char LOG_time_stamp[20];		//Marca de tiempo		//29/01/2021;08:30:17;
		
		char trt_num[6];				//Indice de tratamiento	//15000;
		
		char MCC[4];					//MCC		//214;
		
		char HP_index[4];				//Datos del aplicador		//HP1;
		char HP_model[12];				//Datos del aplicador		//OVAL CURVE;
		char HP_fw_version[3];			//Datos del aplicador		//99;

		char label[4];					//Etiqueta empleada para el tratamineto	//Z0;
		
		char sns_1[8];					//Sensor 1				//-050.00;
		char sns_2[8];					//Sensor 2				// 100.00;
		char sns_3[8];					//Sensor 3				//-150.00;
		char sns_4[8];					//Sensor 4				// 200.00;
		char sns_5[8];					//Sensor 5				//-50.00;
		char sns_6[8];					//Sensor 6				//-50.00;
		char sns_7[8];					//Sensor 7				//-50.00;
		char sns_8[8];					//Sensor 8				//-50.00;
		char sns_9[8];					//Sensor 9				//-50.00;
		
		char Frostbite[4];				//255;

		char vac_rty[4];				//Resucciones				//255;
		char vac_set_point[7];			//Consigna de vacuum		//655,35;
		char vac_level[7];				//Nivel de vacuum			//655,35;
		char PW_pelt_1[4];				//Potencia peltier 1		//100;
		char PW_pelt_2[4];				//Potencia peltier 2		//100;
		char temp_return[8];			//Temperatura de retorno	//-150,00;
		char cal1[8];					//Calibracion 1				//-3276,7;
		char cal2[8];					//Calibracion 2				//-3276,7;
		char cal3[8];					//Calibracion 3				//-3276,7;
		char return_flow[5];			//Flujo de retorno			//25,5;
		
		char END[2];					//\r\n
	}data;
	uint8 vector[APP_LOG_TRT_ASCII_VECTOR_SIZE];
}sAppLOG_trt_ASCII;

typedef union
{
	struct
	{
		char LOG_data_type[4];			//Tipo de dato del LOG		//ERR;
		
		char LOG_time_stamp[20];		//Marca de tiempo			//29/01/2021;08:30:17;
		
		char trt_num[6];				//Indice de tratamiento		//15000;
		
		char err_code[5];				//Codigo del error			//4004;
		
		char END[2];					//\r\n
	}data;
	uint8 vector[APP_LOG_ERROR_ASCII_VECTOR_SIZE];
}sAppLOG_error_ASCII;

typedef union
{
	struct
	{
		char LOG_data_type[4];			//Tipo de dato del LOG		//WNG;
		
		char LOG_time_stamp[20];		//Marca de tiempo			//29/01/2021;08:30:17;
		
		char wng_code[5];				//Codigo del aviso			//4004;
		
		char END[2];					//\r\n
	}data;
	uint8 vector[APP_LOG_WARNING_ASCII_VECTOR_SIZE];
}sAppLOG_warning_ASCII;

typedef union
{
	struct
	{
		char LOG_data_type[5];			//Tipo de dato del LOG		//MCHN;
		
		char LOG_time_stamp[20];		//Marca de tiempo			//29/01/2021;08:30:17;
		
		char rad_in_temp[8];			//temperatura de entrada del radiador	//-150,00;		TMP_RAD_IN;-150,00;
		char rad_out_temp[8];			//Temperatura de salida del radiador	//-150,00;		TMP_RAD_OUT;-150,00;
		char env_temp[8];				//Temperatura ambiente					//-150,00;		TMP_ENV;-150,00;
		char total_flow[5];				//flujo total							//25,5;			TTL_FLW;25,5;
		char emergency_but[2];			//Boton de emergencia					//0;			EMG_BUT;0;
		char cool_tank_lvl[4];			//nivel del tanque de anticongelante	//255;			COOL_LVL;255;
		
		char END[2];					//\r\n
	}data;
	uint8 vector[APP_LOG_MACHINE_ASCII_VECTOR_SIZE];
}sAppLOG_machine_ASCII;

typedef union
{
	struct
	{
		char LOG_data_type[4];			//Tipo de dato del LOG		//MOD;
		
		char LOG_time_stamp[20];		//Marca de tiempo			//29/01/2021;08:30:17;
		
		char Oscillations[6];		//Oscilaciones en estado IDLE del aplicador			//OSC;0;
		char Label_reuse[9];		//Reuso de etiquetas								//LBL_RE;0;
		char Temp_slope[11];		//Rampa de bajada de temperatura					//TEMP_SLP;0;
		char Temp_secure[11];		//Consigna de temperatura -5ºC						//TEMP_SCR;0;
		char Err_secure[10];		//Modo estricto de parametros de seguridad			//ERR_SCR;0;
		char Err_delta_secure[14];	//Modo estricto del error del delta de temperatura	//ERR_DLT_SCR;0;
		
		char END[2];				//\r\n
	}data;
	uint8 vector[APP_LOG_MODES_ASCII_VECTOR_SIZE];
}sAppLOG_modes_ASCII;

typedef union
{
	struct
	{
		char LOG_data_type[4];			//Tipo de dato del LOG	//TRT;
		
		char LOG_time_stamp[10];		//Marca de tiempo		//DATE;HOUR;		29/01/2021;08:30:17;
		
		char trt_num[7];				//Indice de tratamiento	//TRTnum;			15000;
		
		char MCC[4];					//MCC	//MCC;	//214;
		
		char HP_index[5];				//Datos del aplicador		//PORT;			HP1;
		char HP_model[9];				//Datos del aplicador		//MODEL HP;		OVAL CURVE;
		char HP_fw_version[3];			//Datos del aplicador		//FW;			FW:99;

		char label[6];					//Etiqueta empleada para el tratamineto		//Label;	LBL:Z0;
		
		char sns_1[5];					//Sensor 1					//SNS1;			-050.00;
		char sns_2[5];					//Sensor 2					//SNS2;			 100.00;
		char sns_3[5];					//Sensor 3					//SNS3;			-150.00;
		char sns_4[5];					//Sensor 4					//SNS4;			 200.00;
		char sns_5[5];					//Sensor 5					//SNS5;			-50.00;
		char sns_6[5];					//Sensor 6					//SNS6;			-50.00;
		char sns_7[5];					//Sensor 7					//SNS7;			-50.00;
		char sns_8[5];					//Sensor 8					//SNS8;			-50.00;
		char sns_9[5];					//Sensor 9					//SNS9;			-50.00;
		
		char Frostbite[10];				//Frostbite;				FRST;255;

		char vac_rty[8];				//Resucciones				//VAC_RTY;			VAC_RTY;255;
		char vac_set_point[8];			//Consigna de vacuum		//VAC_SET;			VAC_SET;655,35;
		char vac_level[8];				//Nivel de vacuum			//VAC_LVL;			VAC_LVL;655,35;
		char PW_pelt_1[4];				//Potencia peltier 1		//PW1;				PW1;100;
		char PW_pelt_2[4];				//Potencia peltier 2		//PW2;				PW2;100;
		char temp_return[8];			//Temperatura de retorno	//TMP_RTN;			TMP_RTN;-150,00;
		char cal1[5];					//Calibracion 1				//CAL1;				CAL1;-3276,7;
		char cal2[5];					//Calibracion 2				//CAL2;				CAL2;-3276,7;
		char cal3[5];					//Calibracion 3				//CAL3;				CAL3;-3276,7;
		char return_flow[8];			//Flujo de retorno			//RTN_FLW;			RTN_FLW;25,5;
		
		char END[2];					//\r\n
	}data;
	uint8 vector[APP_LOG_TRT_ASCII_DEFINITION];
}sAppLOG_trt_definition_ASCII;

typedef union
{
	struct
	{
		char LOG_data_type[5];			//Tipo de dato del LOG					//MCHN;
		
		char LOG_time_stamp[10];		//Marca de tiempo						//DATE;HOUR;		29/01/2021;08:30:17;
		
		char rad_in_temp[11];			//temperatura de entrada del radiador	//TMP_RAD_IN;		TMP_RAD_IN;-150,00;
		char rad_out_temp[12];			//Temperatura de salida del radiador	//TMP_RAD_OUT;		TMP_RAD_OUT;-150,00;
		char env_temp[8];				//Temperatura ambiente					//TMP_ENV;			TMP_ENV;-150,00;
		char total_flow[8];				//flujo total							//TTL_FLW;			TTL_FLW;25,5;
		char emergency_but[8];			//Boton de emergencia					//EMG_BUT;			EMG_BUT;0;
		char cool_tank_lvl[9];			//nivel del tanque de anticongelante	//COOL_LVL;			COOL_LVL;255;
		
		char END[2];					//\r\n
	}data;
	uint8 vector[APP_LOG_MACHINE_ASCII_DEFINITION];
}sAppLOG_machine_definition_ASCII;

typedef struct
{
	eAppLOGcommands Commands;
	uint8 TaskMotor;
//	FIL OutputFile;
	uint8 WiFiMac[6];
	uint8 TRTstarted;
	uint32 saveRAM_t_ref;
}sAppLOGdata;

/* --- Declaracion de estructuras --- */
sAppLOG_trt AppLOG_trt;				//Estructura datos tratamiento
sAppLOG_error AppLOG_error;			//Estructura errores
sAppLOG_warning AppLOG_warning;		//Estructura avisos
sAppLOG_machine AppLOG_machine;		//Estructura datos equipo
sAppLOG_modes AppLOG_modes;			//Estructuras modos del equipo

sAppLOG_trt_ASCII AppLOG_trt_ASCII;				//Estructura datos tratamiento - ASCII
sAppLOG_error_ASCII AppLOG_error_ASCII;			//Estructura errores - ASCII
sAppLOG_warning_ASCII AppLOG_warning_ASCII;		//Estructura avisos - ASCII
sAppLOG_machine_ASCII AppLOG_machine_ASCII;		//Estructura datos equipo - ASCII
sAppLOG_modes_ASCII AppLOG_modes_ASCII;			//Estructuras modos del equipo - ASCII

sAppLOG_trt_definition_ASCII AppLOG_trt_definition_ASCII;
sAppLOG_machine_definition_ASCII AppLOG_machine_definition_ASCII;

sAppLOGdata AppLOGdata;

/* --- Asignar valores a las definiciones de las tramas de trt y machine --- */



/* --- Declaracion de funciones locales --- */
void AppLOG_getTimeStamp (sApp_LOG_time_stamp* time_stamp);
void AppLOG_getHPdata (sAppLOG_HPdata* HPdata, tHPcryoData *HP, tPRFdata *PRF);

void AppLOG_TRT2ASCII (uint8 *TrtAscii);
void AppLOG_Error2ASCII (uint8 *ErrorAscii);
void AppLOG_Warning2ASCII (uint8 *WarningAscii);
void AppLOG_Machine2ASCII (uint8 *MachineAscii);
void AppLOG_Mode2ASCII (uint8 *ModeAscii);

void AppLOG_TRT_Definition_2_ASCII (void);
void AppLOG_MACHINE_Definition_2_ASCII (void);

returnstatus_t AppLOG_send_ASCII_LOG (uint8 Mode);
returnstatus_t AppLOG_send_RAW_LOG (uint8 Mode);

int AppLOG_ABSval(int y);
int16 AppLOG_FLOAT_2_INT16(float value);
uint8 AppLOG_FLOAT_2_UINT8(float value);

/* --- Funciones Publicas --- */
void AppLOG_init(void)
{
//	AppLOGdata.Commands = AppLOG_No_Command;
	
//	AppLOGdata.TRTstarted = 0;
	
//	AppLOGdata.saveRAM_t_ref = TICKS_GetTicks();
	
//	AppLOG_TRT_Definition_2_ASCII();
//	AppLOG_MACHINE_Definition_2_ASCII();
}

void AppLOG_motor(void)
{
//	uint8 i;	//Variable auxiliar bucles
//	returnstatus_t ret = RUNNING;
//	static uint32 USB_TimerDetected;
//	static uint32 tmrWaitInit;
//	char FileName[16];
//	uint16 MSD_return;
//	char WiFiMac_ASCII[26];
	
//	for(i=0;i<6;i++)
//	{
//		sprintf(WiFiMac_ASCII+4*i, "%03d:", AppLOGdata.WiFiMac[i]);
//	}
//	WiFiMac_ASCII[24] = '\r';
//	WiFiMac_ASCII[25] = '\n';
	
//	if((AppLOGdata.Commands == AppLOG_No_Command) &&
//	   (TICKS_DiffTicks(AppLOGdata.saveRAM_t_ref) > APP_LOG_TIME_WITHOUT_SAVING_2_SAVE) &&
//	   (AppLOGdata.TRTstarted == 1))
//	{
//		AppLOGdata.Commands = AppLOG_saveRAM;
//		AppLOGdata.TRTstarted = 0;
//	}
	
//	switch(AppLOGdata.Commands)
//	{
//	case AppLOG_No_Command:
//		AppLOGdata.TaskMotor = 0;
//		ret = IDLE;
//		break;
//	case AppLOG_SendASCII_LOG:
//		switch(AppLOGdata.TaskMotor)
//		{
//		case 0:
//			AppLOGdata.TaskMotor = 1;
//			LOGS_RestorationPointFiFoPointers(0);
//			//tmrWaitInit = TICKS_GetTicks();
//			//UART_Transmit(INDEX_UART_2, (uint8*)WiFiMac_ASCII, sizeof(WiFiMac_ASCII)); //V7790 Debug out
//			//while( (UART_TransmitNOTFinished(INDEX_UART_2))&&(TICKS_DiffTicks(tmrWaitInit)<50) );
//			//tmrWaitInit = TICKS_GetTicks();
//			//UART_Transmit(INDEX_UART_2, (uint8*)AppLOG_trt_definition_ASCII.vector, sizeof(AppLOG_trt_definition_ASCII));
//			//while( (UART_TransmitNOTFinished(INDEX_UART_2))&&(TICKS_DiffTicks(tmrWaitInit)<50) );
//			//tmrWaitInit = TICKS_GetTicks();
//			//UART_Transmit(INDEX_UART_2, (uint8*)AppLOG_machine_definition_ASCII.vector, sizeof(AppLOG_machine_definition_ASCII));
//			//while( (UART_TransmitNOTFinished(INDEX_UART_2))&&(TICKS_DiffTicks(tmrWaitInit)<50) );
//			break;
//		case 1:
//			ret = AppLOG_send_ASCII_LOG (0);
//			if(ret == IDLE){	AppLOGdata.TaskMotor = 0x80;	}
//			else if(ret == ERROR){	AppLOGdata.TaskMotor = 0xF0;	}
//			break;
//		case 0x80:
//			LOGS_RestoreFiFoPointers(0);
//			AppLOGdata.Commands = AppLOG_No_Command;
//			BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
//			break;
//		case 0xF0:
//		default:
//			LOGS_RestoreFiFoPointers(0);
//			AppLOGdata.Commands = AppLOG_No_Command;
//			BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
//			break;
//		}
//		break;
//	case AppLOG_SendRAW_LOG:
//		switch(AppLOGdata.TaskMotor)
//		{
//		case 0:
//			AppLOGdata.TaskMotor = 1;
//			LOGS_RestorationPointFiFoPointers(0);
//			//tmrWaitInit = TICKS_GetTicks(); //V7790 Debug out
//			//UART_Transmit(INDEX_UART_2, (uint8*)WiFiMac_ASCII, sizeof(WiFiMac_ASCII));
//			//while( (UART_TransmitNOTFinished(INDEX_UART_2))&&(TICKS_DiffTicks(tmrWaitInit)<50) );
//			break;
//		case 1:
//			ret = AppLOG_send_RAW_LOG (0);
//			if(ret == IDLE){	AppLOGdata.TaskMotor = 0x80;	}
//			else if(ret == ERROR){	AppLOGdata.TaskMotor = 0xF0;	}
//			break;
//		case 0x80:
//			LOGS_RestoreFiFoPointers(0);
//			AppLOGdata.Commands = AppLOG_No_Command;
//			BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
//			break;
//		case 0xF0:
//		default:
//			LOGS_RestoreFiFoPointers(0);
//			AppLOGdata.Commands = AppLOG_No_Command;
//			BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
//			break;
//		}
//		break;
//	case AppLOG_Erase_LOG:
//		switch(AppLOGdata.TaskMotor)
//		{
//		case 0:
//			LOGS_ResetFiFoPointers(0);
//			AppLOGdata.TaskMotor++;
//			break;
//		case 1:
//			switch(LOGS_SaveFiFoPointers(0))
//			{
//			case RUNNING: break;
//			case SUCCESS:
//				AppLOGdata.TaskMotor = 0x80;
//				break;
//			case ERROR:
//			default:
//				AppLOGdata.TaskMotor = 0xF0;
//				break;
//			}
//			break;
//		case 0x80:
//			AppLOGdata.Commands = AppLOG_No_Command;
//			BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
//			break;
//		case 0xF0:
//		default:
//			AppLOGdata.Commands = AppLOG_No_Command;
//			BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
//			break;
//		}
//		break;
//	case AppLOG_Send_USB_ASCII_LOG:
//		while(1)
//		{
//			WDOG_clear();
//			switch(AppLOGdata.TaskMotor)
//			{
//			case 0:
//				AppLOGdata.TaskMotor++;
//				LOGS_RestorationPointFiFoPointers(0);
//				break;
//			case 1:
//				MSDinit();								/* Inicializa la librería del USB */
//				MSDdetection(MSD_ON);					/* Alimenta el USB y realiza su detección */
//				USB_TimerDetected = TICKS_GetTicks();
//				AppLOGdata.TaskMotor++;
//				break;
//			case 2:
//				MSD_Task();
//				Poll();
//				if(MSDstatus() == MSD_DEVICE_READY)
//				{
//					AppLOGdata.TaskMotor++;
//					USB_TimerDetected = TICKS_GetTicks();
//				}
//				else if(TICKS_DiffTicks(USB_TimerDetected)> 5000)
//				{	AppLOGdata.TaskMotor = 0xF0;	}
//				break;
//			case 3:
//				MSD_Task();
//				Poll();
//				if(MSDinstallMFS() == K70_MSD_ERR_OK)
//				{	AppLOGdata.TaskMotor++;	}
//				else if(TICKS_DiffTicks(USB_TimerDetected)> 5000)
//				{	AppLOGdata.TaskMotor = 0xF0;	}
//				break;
//			case 4:
//				MSD_Task();
//				Poll();
//				for(i=0;i<100;i++)
//				{
//					sprintf(FileName, "AsciiLOG%d.csv", i);
					
//					MSD_return = MSDopenFile(&AppLOGdata.OutputFile, (uint8 *)FileName,FA_READ);
//					if(MSD_return == K70_MSD_ERR_OK)
//					{	MSDcloseFile(&AppLOGdata.OutputFile);	}
//					else if(MSD_return == K70_MSD_ERR_NO_FILE)
//					{
//						USB_TimerDetected = 0;
//						if(MSDopenFile(&AppLOGdata.OutputFile, (uint8 *)FileName, FA_CREATE_ALWAYS | FA_WRITE) == K70_MSD_ERR_OK)
//						{	AppLOGdata.TaskMotor++;	}
//						else
//						{	AppLOGdata.TaskMotor = 0xF0;	}
//						break;
//					}
//					else
//					{	AppLOGdata.TaskMotor = 0xF0;
//						break;
//					}
//				}
//				break;
//			case 5:
//				MSD_Task();
//				Poll();
//				/* Grabar al USB las cabeceras de la trama TRT*/
//				ret = MSDwriteFile(&AppLOGdata.OutputFile, (uint8*)WiFiMac_ASCII, sizeof(WiFiMac_ASCII), &tmrWaitInit);
//				if(ret != K70_MSD_ERR_OK)
//				{
//					ret = ERROR;
//					AppLOGdata.TaskMotor = 0xF0;
//				}
//				else
//				{	AppLOGdata.TaskMotor++;	}
//				break;
//			case 6:
//				MSD_Task();
//				Poll();
//				/* Grabar al USB las cabeceras de la trama TRT*/
//				ret = MSDwriteFile(&AppLOGdata.OutputFile, (uint8*)AppLOG_trt_definition_ASCII.vector, sizeof(AppLOG_trt_definition_ASCII), &tmrWaitInit);
//				if(ret != K70_MSD_ERR_OK)
//				{
//					ret = ERROR;
//					AppLOGdata.TaskMotor = 0xF0;
//				}
//				else
//				{	AppLOGdata.TaskMotor++;	}
//				break;
//			case 7:
//				MSD_Task();
//				Poll();
//				/* Grabar al USB las cabeceras de la trama MACHINE*/
//				ret = MSDwriteFile(&AppLOGdata.OutputFile, (uint8*)AppLOG_machine_definition_ASCII.vector, sizeof(AppLOG_machine_definition_ASCII), &tmrWaitInit);
//				if(ret != K70_MSD_ERR_OK)
//				{
//					ret = ERROR;
//					AppLOGdata.TaskMotor = 0xF0;
//				}
//				else
//				{	AppLOGdata.TaskMotor++;	}
//				break;
//			case 8:
//				MSD_Task();
//				Poll();
//				ret = AppLOG_send_ASCII_LOG (1);
//				if(ret == IDLE){	AppLOGdata.TaskMotor = 0x80;	}
//				else if(ret == ERROR){	AppLOGdata.TaskMotor = 0xF0;	}
//				break;
//			case 0x80:
//				MSDcloseFile(&AppLOGdata.OutputFile);
//				MSDdetection(MSD_OFF);
//				MSDuninstallMFS();
//				LOGS_RestoreFiFoPointers(0);
//				AppLOGdata.Commands = AppLOG_No_Command;
//				BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
//				AppLOGdata.TaskMotor = 0xFF;
//				USB_TimerDetected = TICKS_GetTicks();
//				break;
//			case 0xF0:
//			default:
//				MSDcloseFile(&AppLOGdata.OutputFile);
//				MSDdetection(MSD_OFF);
//				MSDuninstallMFS();
//				LOGS_RestoreFiFoPointers(0);
//				AppLOGdata.Commands = AppLOG_No_Command;
//				BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
//				AppLOGdata.TaskMotor = 0xFF;
//				USB_TimerDetected = TICKS_GetTicks();
//				break;
//			case 0xFF:
//				if(TICKS_DiffTicks(USB_TimerDetected) > 5000){	Cpu_SystemReset();	}
//				break;
//			}
//		}
//		break;
//	case AppLOG_Send_USB_RAW_LOG:
//		while(1)
//		{
//			WDOG_clear();
//			switch(AppLOGdata.TaskMotor)
//			{
//			case 0:
//				AppLOGdata.TaskMotor++;
//				LOGS_RestorationPointFiFoPointers(0);
//				break;
//			case 1:
//				MSDinit();								/* Inicializa la librería del USB */
//				MSDdetection(MSD_ON);					/* Alimenta el USB y realiza su detección */
//				USB_TimerDetected = TICKS_GetTicks();
//				AppLOGdata.TaskMotor++;
//				break;
//			case 2:
//				MSD_Task();
//				Poll();
//				if(MSDstatus() == MSD_DEVICE_READY)
//				{
//					AppLOGdata.TaskMotor++;
//					USB_TimerDetected = TICKS_GetTicks();
//				}
//				else if(TICKS_DiffTicks(USB_TimerDetected)> 5000)
//				{	AppLOGdata.TaskMotor = 0xF0;	}
//				break;
//			case 3:
//				MSD_Task();
//				Poll();
//				if(MSDinstallMFS() == K70_MSD_ERR_OK)
//				{	AppLOGdata.TaskMotor++;	}
//				else if(TICKS_DiffTicks(USB_TimerDetected)> 5000)
//				{	AppLOGdata.TaskMotor = 0xF0;	}
//				break;
//			case 4:
//				MSD_Task();
//				Poll();
//				for(i=0;i<100;i++)
//				{
//					sprintf(FileName, "RawLOG%d.bin", i);
					
//					MSD_return = MSDopenFile(&AppLOGdata.OutputFile, (uint8 *)FileName,FA_READ);
//					if(MSD_return == K70_MSD_ERR_OK)
//					{	MSDcloseFile(&AppLOGdata.OutputFile);	}
//					else if(MSD_return == K70_MSD_ERR_NO_FILE)
//					{
//						USB_TimerDetected = 0;
//						if(MSDopenFile(&AppLOGdata.OutputFile, (uint8 *)FileName, FA_CREATE_ALWAYS | FA_WRITE) == K70_MSD_ERR_OK)
//						{	AppLOGdata.TaskMotor++;	}
//						else
//						{	AppLOGdata.TaskMotor = 0xF0;	}
//						break;
//					}
//					else
//					{	AppLOGdata.TaskMotor = 0xF0;
//						break;
//					}
//				}
//				break;
//			case 5:
//				MSD_Task();
//				Poll();
//				/* Grabar al USB las cabeceras de la trama TRT*/
//				ret = MSDwriteFile(&AppLOGdata.OutputFile, (uint8*)WiFiMac_ASCII, sizeof(WiFiMac_ASCII), &tmrWaitInit);
//				if(ret != K70_MSD_ERR_OK)
//				{
//					ret = ERROR;
//					AppLOGdata.TaskMotor = 0xF0;
//				}
//				else
//				{	AppLOGdata.TaskMotor++;	}
//				break;
//			case 6:
//				MSD_Task();
//				Poll();
//				ret = AppLOG_send_RAW_LOG (1);
//				if(ret == IDLE){	AppLOGdata.TaskMotor = 0x80;	}
//				else if(ret == ERROR){	AppLOGdata.TaskMotor = 0xF0;	}
//				break;
//			case 0x80:
//				MSDcloseFile(&AppLOGdata.OutputFile);
//				MSDdetection(MSD_OFF);
//				MSDuninstallMFS();
//				LOGS_RestoreFiFoPointers(0);
//				AppLOGdata.Commands = AppLOG_No_Command;
//				BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
//				AppLOGdata.TaskMotor = 0xFF;
//				USB_TimerDetected = TICKS_GetTicks();
//				break;
//			case 0xF0:
//			default:
//				MSDcloseFile(&AppLOGdata.OutputFile);
//				MSDdetection(MSD_OFF);
//				MSDuninstallMFS();
//				LOGS_RestoreFiFoPointers(0);
//				AppLOGdata.Commands = AppLOG_No_Command;
//				BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
//				AppLOGdata.TaskMotor = 0xFF;
//				USB_TimerDetected = TICKS_GetTicks();
//				break;
//			case 0xFF:
//				if(TICKS_DiffTicks(USB_TimerDetected) > 5000){	Cpu_SystemReset();	}
//				break;
//			}
//		}
//		break;
//	case AppLOG_Send_RecentLOG_ASCII_USB:
//		while(1)
//		{
//			WDOG_clear();
//			switch(AppLOGdata.TaskMotor)
//			{
//			case 0:
//				AppLOGdata.TaskMotor++;
//				LOGS_RestorationPointFiFoPointers(0);
//				LOGS_SeekFiFoPointers(0, APP_LOG_RECENT_LOGS_2_SEND);		//descargar lo ultimos 15 bloques el equivalente a 5 tratamientos
//				break;
//			case 1:
//				MSDinit();								/* Inicializa la librería del USB */
//				MSDdetection(MSD_ON);					/* Alimenta el USB y realiza su detección */
//				USB_TimerDetected = TICKS_GetTicks();
//				AppLOGdata.TaskMotor++;
//				break;
//			case 2:
//				MSD_Task();
//				Poll();
//				if(MSDstatus() == MSD_DEVICE_READY)
//				{
//					AppLOGdata.TaskMotor++;
//					USB_TimerDetected = TICKS_GetTicks();
//				}
//				else if(TICKS_DiffTicks(USB_TimerDetected)> 5000)
//				{	AppLOGdata.TaskMotor = 0xF0;	}
//				break;
//			case 3:
//				MSD_Task();
//				Poll();
//				if(MSDinstallMFS() == K70_MSD_ERR_OK)
//				{	AppLOGdata.TaskMotor++;	}
//				else if(TICKS_DiffTicks(USB_TimerDetected)> 5000)
//				{	AppLOGdata.TaskMotor = 0xF0;	}
//				break;
//			case 4:
//				MSD_Task();
//				Poll();
//				for(i=0;i<100;i++)
//				{
//					sprintf(FileName, "RecentLOG%d.csv", i);
					
//					MSD_return = MSDopenFile(&AppLOGdata.OutputFile, (uint8 *)FileName,FA_READ);
//					if(MSD_return == K70_MSD_ERR_OK)
//					{	MSDcloseFile(&AppLOGdata.OutputFile);	}
//					else if(MSD_return == K70_MSD_ERR_NO_FILE)
//					{
//						USB_TimerDetected = 0;
//						if(MSDopenFile(&AppLOGdata.OutputFile, (uint8 *)FileName, FA_CREATE_ALWAYS | FA_WRITE) == K70_MSD_ERR_OK)
//						{	AppLOGdata.TaskMotor++;	}
//						else
//						{	AppLOGdata.TaskMotor = 0xF0;	}
//						break;
//					}
//					else
//					{	AppLOGdata.TaskMotor = 0xF0;
//						break;
//					}
//				}
//				break;
//			case 5:
//				MSD_Task();
//				Poll();
//				/* Grabar al USB las cabeceras de la trama TRT*/
//				ret = MSDwriteFile(&AppLOGdata.OutputFile, (uint8*)WiFiMac_ASCII, sizeof(WiFiMac_ASCII), &tmrWaitInit);
//				if(ret != K70_MSD_ERR_OK)
//				{
//					ret = ERROR;
//					AppLOGdata.TaskMotor = 0xF0;
//				}
//				else
//				{	AppLOGdata.TaskMotor++;	}
//				break;
//			case 6:
//				MSD_Task();
//				Poll();
//				/* Grabar al USB las cabeceras de la trama TRT*/
//				ret = MSDwriteFile(&AppLOGdata.OutputFile, (uint8*)AppLOG_trt_definition_ASCII.vector, sizeof(AppLOG_trt_definition_ASCII), &tmrWaitInit);
//				if(ret != K70_MSD_ERR_OK)
//				{
//					ret = ERROR;
//					AppLOGdata.TaskMotor = 0xF0;
//				}
//				else
//				{	AppLOGdata.TaskMotor++;	}
//				break;
//			case 7:
//				MSD_Task();
//				Poll();
//				/* Grabar al USB las cabeceras de la trama MACHINE*/
//				ret = MSDwriteFile(&AppLOGdata.OutputFile, (uint8*)AppLOG_machine_definition_ASCII.vector, sizeof(AppLOG_machine_definition_ASCII), &tmrWaitInit);
//				if(ret != K70_MSD_ERR_OK)
//				{
//					ret = ERROR;
//					AppLOGdata.TaskMotor = 0xF0;
//				}
//				else
//				{	AppLOGdata.TaskMotor++;	}
//				break;
//			case 8:
//				MSD_Task();
//				Poll();
//				ret = AppLOG_send_ASCII_LOG (1);
//				if(ret == IDLE){	AppLOGdata.TaskMotor = 0x80;	}
//				else if(ret == ERROR){	AppLOGdata.TaskMotor = 0xF0;	}
//				break;
//			case 0x80:
//				MSDcloseFile(&AppLOGdata.OutputFile);
//				MSDdetection(MSD_OFF);
//				MSDuninstallMFS();
//				LOGS_RestoreFiFoPointers(0);
//				AppLOGdata.Commands = AppLOG_No_Command;
//				BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
//				AppLOGdata.TaskMotor = 0xFF;
//				USB_TimerDetected = TICKS_GetTicks();
//				break;
//			case 0xF0:
//			default:
//				MSDcloseFile(&AppLOGdata.OutputFile);
//				MSDdetection(MSD_OFF);
//				MSDuninstallMFS();
//				LOGS_RestoreFiFoPointers(0);
//				AppLOGdata.Commands = AppLOG_No_Command;
//				BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
//				AppLOGdata.TaskMotor = 0xFF;
//				USB_TimerDetected = TICKS_GetTicks();
//				break;
//			case 0xFF:
//				if(TICKS_DiffTicks(USB_TimerDetected) > 5000){	Cpu_SystemReset();	}
//				break;
//			}
//		}
//		break;
//	case AppLOG_Send_RecentLOG_ASCII:
//		switch(AppLOGdata.TaskMotor)
//		{
//		case 0:
//			AppLOGdata.TaskMotor = 1;
//			LOGS_RestorationPointFiFoPointers(0);
//			LOGS_SeekFiFoPointers(0, APP_LOG_RECENT_LOGS_2_SEND);		//descargar lo ultimos 15 bloques el equivalente a 5 tratamientos
//			//tmrWaitInit = TICKS_GetTicks(); //V7790 Debug out
//			//while( (UART_TransmitNOTFinished(INDEX_UART_2))&&(TICKS_DiffTicks(tmrWaitInit)<50) );
//			//tmrWaitInit = TICKS_GetTicks();
//			//UART_Transmit(INDEX_UART_2, (uint8*)WiFiMac_ASCII, sizeof(WiFiMac_ASCII));
//			//while( (UART_TransmitNOTFinished(INDEX_UART_2))&&(TICKS_DiffTicks(tmrWaitInit)<50) );
//			//tmrWaitInit = TICKS_GetTicks();
//			//while( (UART_TransmitNOTFinished(INDEX_UART_2))&&(TICKS_DiffTicks(tmrWaitInit)<50) );
//			//tmrWaitInit = TICKS_GetTicks();
//			//UART_Transmit(INDEX_UART_2, (uint8*)AppLOG_trt_definition_ASCII.vector, sizeof(AppLOG_trt_definition_ASCII));
//			//while( (UART_TransmitNOTFinished(INDEX_UART_2))&&(TICKS_DiffTicks(tmrWaitInit)<50) );
//			//tmrWaitInit = TICKS_GetTicks();
//			//UART_Transmit(INDEX_UART_2, (uint8*)AppLOG_machine_definition_ASCII.vector, sizeof(AppLOG_machine_definition_ASCII));
//			//while( (UART_TransmitNOTFinished(INDEX_UART_2))&&(TICKS_DiffTicks(tmrWaitInit)<50) );
//			break;
//		case 1:
//			ret = AppLOG_send_ASCII_LOG (0);
//			if(ret == IDLE){	AppLOGdata.TaskMotor = 0x80;	}
//			else if(ret == ERROR){	AppLOGdata.TaskMotor = 0xF0;	}
//			break;
//		case 0x80:
//			LOGS_RestoreFiFoPointers(0);
//			AppLOGdata.Commands = AppLOG_No_Command;
//			BUZZ_Configure(1, 100, PATRO_SO_RFID_OK );
//			break;
//		case 0xF0:
//		default:
//			LOGS_RestoreFiFoPointers(0);
//			AppLOGdata.Commands = AppLOG_No_Command;
//			BUZZ_Configure(1, 100, PATRO_SO_RFID_KO );
//			break;
//		}
//		break;
//	case AppLOG_saveRAM:
//		LOGS_FlushRAM(0);
//		AppLOGdata.Commands = AppLOG_No_Command;
//		break;
//	default:
//		break;
//	}
}

void AppLOG_saveTRT(tHPcryoData *HP, tPRFdata *PRF)
{
//	uint8 i;
//	uint8 HPindex;
//	HPindex = PRF->IDperifHW - 1;
	
//	if((AppLOGdata.Commands == AppLOG_No_Command) && (EXP_UC_RecLOG_Status()))
//	{
//		AppLOGdata.saveRAM_t_ref = TICKS_GetTicks();
//		AppLOGdata.TRTstarted = 1;
		
//		AppLOG_trt.data.LOG_data_type = AppLOG_TRT;
		
//		AppLOG_getTimeStamp (&AppLOG_trt.data.time_stamp);
		
//		AppLOG_getHPdata (&AppLOG_trt.data.HP_data, HP, PRF);
		
//		AppLOG_trt.data.trt_num = HP->trt.HPtreatment_Num;
		
//		AppLOG_trt.data.MCC = AppGPRS_GetMCCnum(0);
		
//		AppLOG_trt.data.label = HP->trt.Label_accepted;
		
//		AppLOG_trt.data.Frostbite = Temp_SAFE_Frostbite(HP, PRF);
				
//		for(i=0;i<HP_CRYO_MAX_TEMP_SNS;i++)		//Se recorren todos los sensores de temperatura
//		{	AppLOG_trt.data.sns[i] = AppLOG_FLOAT_2_INT16((HP->frames.dbgOut.data.MedidasTemperatura[i]*100));	}
		
//		AppLOG_trt.data.vac_rtry = EXPdata.UC.commonData2.fields.vacumRetrysCnt[HPindex];
		
//		AppLOG_trt.data.vac_set_point = AppLOG_FLOAT_2_INT16(HP->frames.mainIn.data.fConsignaVacum*100);
//		AppLOG_trt.data.vac_level = AppLOG_FLOAT_2_INT16(HP->frames.mainOut.data.presionVaccum*100);
//		AppLOG_trt.data.PW_pelt_1 = AppLOG_FLOAT_2_UINT8(EXPdata.UC.handPieceData[HPindex].vars.fields.PS1voltagePerCent);
//		AppLOG_trt.data.PW_pelt_2 = AppLOG_FLOAT_2_UINT8(EXPdata.UC.handPieceData[HPindex].vars.fields.PS2voltagePerCent);
//		AppLOG_trt.data.temp_return = AppLOG_FLOAT_2_INT16(EXPdata.UC.handPieceData[HPindex].sensors.fields.returnTemp*100);
//		AppLOG_trt.data.cal1 = AppLOG_FLOAT_2_INT16(HP->frames.dbgOut.data.Calibraciones[0]*10);
//		AppLOG_trt.data.cal2 = AppLOG_FLOAT_2_INT16(HP->frames.dbgOut.data.Calibraciones[1]*10);
//		AppLOG_trt.data.cal3 = AppLOG_FLOAT_2_INT16(HP->frames.dbgOut.data.Calibraciones[2]*10);
//		AppLOG_trt.data.return_flow = AppLOG_FLOAT_2_UINT8(EXPdata.UC.handPieceData[HPindex].sensors.fields.returnFlow*10);
		
//		// Llamar a la funcion de guardado de datos en el LOG
//		LOGS_CueMessage(0, AppLOG_trt.vector, sizeof(AppLOG_trt));
//	}
}

void AppLOG_saveERROR(uint16 error_code, tHPcryoData *HP, tPRFdata *PRF)
{
//	if((AppLOGdata.Commands == AppLOG_No_Command) && (EXP_UC_RecLOG_Status()))
//	{
//		AppLOGdata.saveRAM_t_ref = TICKS_GetTicks();
		
//		AppLOG_error.data.LOG_data_type = AppLOG_Error;
		
//		AppLOG_getTimeStamp(&AppLOG_error.data.time_stamp);
		
//		if((HP != NULL) && (PRF != NULL))
//		{	AppLOG_error.data.trt_num = HP->trt.HPtreatment_Num;	}
//		else
//		{	AppLOG_error.data.trt_num = 0;	}
		
//		AppLOG_error.data.err_code = error_code;
		
//		// Llamar a la funcion de guardado de datos en el LOG
//		LOGS_CueMessage(0, AppLOG_error.vector, sizeof(AppLOG_error));
//	}
}

void AppLOG_saveWARNING(uint16 warning_code)
{
//	if((AppLOGdata.Commands == AppLOG_No_Command) && (EXP_UC_RecLOG_Status()))
//	{
//		AppLOGdata.saveRAM_t_ref = TICKS_GetTicks();
		
//		AppLOG_warning.data.LOG_data_type = AppLOG_Warning;
		
//		AppLOG_getTimeStamp(&AppLOG_warning.data.time_stamp);
		
//		AppLOG_warning.data.wng_code = warning_code;
		
//		// Llamar a la funcion de guardado de datos en el LOG
//		LOGS_CueMessage(0, AppLOG_warning.vector, sizeof(AppLOG_warning));
//	}
}

void AppLOG_saveMachine(void)
{
//	if((AppLOGdata.Commands == AppLOG_No_Command) && (EXP_UC_RecLOG_Status()))
//	{
//		AppLOGdata.saveRAM_t_ref = TICKS_GetTicks();
		
//		AppLOG_machine.data.LOG_data_type = AppLOG_Machine;
		
//		AppLOG_getTimeStamp(&AppLOG_machine.data.time_stamp);
		
//		AppLOG_machine.data.rad_in_temp = AppLOG_FLOAT_2_INT16(EXPdata.UC.commonData1.fields.returnTemp*100);
//		AppLOG_machine.data.rad_out_temp = AppLOG_FLOAT_2_INT16(EXPdata.UC.commonData1.fields.pumpOutTemp*100);
//		AppLOG_machine.data.env_temp = AppLOG_FLOAT_2_INT16(EXPdata.UC.commonData1.fields.envTemp*100);
//		AppLOG_machine.data.total_flow = AppLOG_FLOAT_2_UINT8(EXPdata.UC.commonData1.fields.returnFlow*10);
//		AppLOG_machine.data.emergency_but = (uint8)EXPdata.UC.commonData1.fields.status.bits.alarma_gral;
//		AppLOG_machine.data.cool_tank_lvl = EXPdata.UC.PCBlvlDetector.vars.fields.level.byte;
		
//		// Llamar a la funcion de guardado de datos en el LOG
//		LOGS_CueMessage(0, AppLOG_machine.vector, sizeof(AppLOG_machine));
//	}
}

void AppLOG_saveModes(void)
{
//	if((AppLOGdata.Commands == AppLOG_No_Command) && (EXP_UC_RecLOG_Status()))
//	{
//		AppLOGdata.saveRAM_t_ref = TICKS_GetTicks();
		
//		AppLOG_modes.data.LOG_data_type = AppLOG_Modes;
		
//		AppLOG_getTimeStamp(&AppLOG_modes.data.time_stamp);
		
//		AppLOG_modes.data.Oscillations = EXP_UCoscTempStatus();
//		AppLOG_modes.data.Label_reuse = EXP_UCreuseLabelModeStatus();
//		AppLOG_modes.data.Temp_slope = EXP_UCtempSlopeStatus();
//		AppLOG_modes.data.Temp_secure = EXP_UCtempSecureStatus();
//		AppLOG_modes.data.Err_secure = EXP_UCerrSecureStatus();
//		AppLOG_modes.data.Err_delta_secure = EXP_UCerrDeltaTempSecureStatus();
		
//		// Llamar a la funcion de guardado de datos en el LOG
//		LOGS_CueMessage(0, AppLOG_modes.vector, sizeof(AppLOG_modes));
//	}
}

returnstatus_t AppLOG_send_ASCII_LOG (uint8 Mode)
{
	uint16 i;					//Variable auxiliar para bucles
	returnstatus_t ret = IDLE;
//	returnstatus_t LOGret = IDLE;
//	uint16 MSD_return;
	
//	static uint32 NumBytes;
//	static uint8 Buffer[50];
//	uint32 NumBytes2Send;
//	uint8 Buffer2send[200];
	
//	uint32 tmrWaitInit;
	
//	LOGret = LOG_GetNextMessage(0, Buffer, &NumBytes);
	
//	/* DEBUG 1 */
////	*Buffer = *AppLOG_modes.vector;
////	NumBytes = APP_LOG_MODES_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE;
//	/* DEBUG 1 */
//	/* DEBUG 2 */
////	static uint8 count = 0;
////
////	switch(count)
////	{
////	case 0:
////		*Buffer = *AppLOG_temp_sns.vector;
////		NumBytes = APP_LOG_TEMP_SNS_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE;
////		count++;
////		LOGret = SUCCESS;
////		break;
////	case 1:
////		*Buffer = *AppLOG_trt.vector;
////		NumBytes = APP_LOG_TRT_VECTOR_SIZE + APP_LOG_HP_DATA_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE;
////		count++;
////		LOGret = SUCCESS;
////		break;
////	case 2:
////		*Buffer = *AppLOG_error.vector;
////		NumBytes = APP_LOG_ERROR_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE;
////		count++;
////		LOGret = SUCCESS;
////		break;
////	case 3:
////		*Buffer = *AppLOG_warning.vector;
////		NumBytes = APP_LOG_WARNING_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE;
////		count++;
////		LOGret = SUCCESS;
////		break;
////	case 4:
////		*Buffer = *AppLOG_machine.vector;
////		NumBytes = APP_LOG_MACHINE_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE;
////		count++;
////		LOGret = SUCCESS;
////		break;
////	case 5:
////		*Buffer = *AppLOG_modes.vector;
////		NumBytes = APP_LOG_MODES_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE;
////		count++;
////		LOGret = IDLE;
////		break;
////	default:
////		break;
////	}
//	/* DEBUG 2 */
//	if(LOGret != SUCCESS)
//	{	ret = LOGret;	}
//	else
//	{
//		switch(Buffer[0])
//		{
//		case AppLOG_TRT:
//			if(NumBytes == APP_LOG_TRT_VECTOR_SIZE + APP_LOG_HP_DATA_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE)
//			{
//				for(i=0;i<NumBytes;i++){	AppLOG_trt.vector[i] = Buffer[i];	}
//				AppLOG_TRT2ASCII (Buffer2send);
//				NumBytes2Send = APP_LOG_TRT_ASCII_VECTOR_SIZE;
//				ret = SUCCESS;
//			}
//			else{	ret = ERROR;	}
//			break;
//		case AppLOG_Error:
//			if(NumBytes == APP_LOG_ERROR_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE)
//			{
//				for(i=0;i<NumBytes;i++){	AppLOG_error.vector[i] = Buffer[i];	}
//				AppLOG_Error2ASCII (Buffer2send);
//				NumBytes2Send = APP_LOG_ERROR_ASCII_VECTOR_SIZE;
//				ret = SUCCESS;
//			}
//			else{	ret = ERROR;	}
//			break;
//		case AppLOG_Warning:
//			if(NumBytes == APP_LOG_WARNING_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE)
//			{
//				for(i=0;i<NumBytes;i++){	AppLOG_warning.vector[i] = Buffer[i];	}
//				AppLOG_Warning2ASCII (Buffer2send);
//				NumBytes2Send = APP_LOG_WARNING_ASCII_VECTOR_SIZE;
//				ret = SUCCESS;
//			}
//			else{	ret = ERROR;	}
//			break;
//		case AppLOG_Machine:
//			if(NumBytes == APP_LOG_MACHINE_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE)
//			{
//				for(i=0;i<NumBytes;i++){	AppLOG_machine.vector[i] = Buffer[i];	}
//				AppLOG_Machine2ASCII (Buffer2send);
//				NumBytes2Send = APP_LOG_MACHINE_ASCII_VECTOR_SIZE;
//				ret = SUCCESS;
//			}
//			else{	ret = ERROR;	}
//			break;
//		case AppLOG_Modes:
//			if(NumBytes == APP_LOG_MODES_VECTOR_SIZE + APP_LOG_TIME_STAMP_VECTOR_SIZE)
//			{
//				for(i=0;i<NumBytes;i++){	AppLOG_modes.vector[i] = Buffer[i];	}
//				AppLOG_Mode2ASCII (Buffer2send);
//				NumBytes2Send = APP_LOG_MODES_ASCII_VECTOR_SIZE;
//				ret = SUCCESS;
//			}
//			else{	ret = ERROR;	}
//			break;
//		default:
//			ret = ERROR;
//			break;
//		}
//	}
	
//	/* Mandar el buffer Buffer2send */
//	if((ret == SUCCESS) && (NumBytes2Send > 0))
//	{
//		if(Mode == 0)
//		{
//			/* Mandar por Puerto Serie */
//			//tmrWaitInit = TICKS_GetTicks();//V7790 Debug out
//			//UART_Transmit(INDEX_UART_2, (uint8*)Buffer2send, NumBytes2Send);
//			//while( (UART_TransmitNOTFinished(INDEX_UART_2))&&(TICKS_DiffTicks(tmrWaitInit)<50) );
//		}
//		else if(Mode == 1)
//		{
//			/* Grabar al USB */
//			MSD_return = MSDwriteFile(&AppLOGdata.OutputFile, (uint8*)Buffer2send, NumBytes2Send, &tmrWaitInit);
//			if(MSD_return != K70_MSD_ERR_OK)
//			{	ret = ERROR;	}
//			else
//			{	/*TEST_PrintInfo("|");*/	}
//		}
//	}
	
	return ret;
}

returnstatus_t AppLOG_send_RAW_LOG (uint8 Mode)
{
	returnstatus_t ret = IDLE;
//	uint16 MSD_return;
//	uint32 NumBytes = 0;
//	static uint8 Buffer[2048];
	
//	uint32 tmrWaitInit;
	
//	NumBytes = sizeof(Buffer);

//	ret = LOG_GetLOGValues(0, Buffer, NumBytes);
	
//	/* Mandar el buffer */
//	if((ret == SUCCESS) && (NumBytes > 0))
//	{
//		if(Mode == 0)
//		{
//			/* Mandar por Puerto Serie */
//			//tmrWaitInit = TICKS_GetTicks();//V7790 Debug out
//			//UART_Transmit(INDEX_UART_2, (uint8*)Buffer, NumBytes);
//			//while( (UART_TransmitNOTFinished(INDEX_UART_2))&&(TICKS_DiffTicks(tmrWaitInit)<50) );
//		}
//		else if(Mode == 1)
//		{
//			/* Grabar al USB */
//			MSD_return = MSDwriteFile(&AppLOGdata.OutputFile, (uint8*)Buffer, NumBytes, &tmrWaitInit);
//			if(MSD_return != K70_MSD_ERR_OK)
//			{	ret = ERROR;	}
//			else
//			{	/*TEST_PrintInfo("/");*/	}
//		}
		
//	}
	
	return ret;
}

eAppLOGcommands AppLOG_GetCommand (void)
{
	return AppLOGdata.Commands;
}

void AppLOG_SetCommand (eAppLOGcommands Command)
{
	AppLOGdata.Commands = Command;
}

void AppLOGsetWiFiMAC (uint8 *ptuMAC)
{
	AppLOGdata.WiFiMac[0] = ptuMAC[0];
	AppLOGdata.WiFiMac[1] = ptuMAC[1];
	AppLOGdata.WiFiMac[2] = ptuMAC[2];
	AppLOGdata.WiFiMac[3] = ptuMAC[3];
	AppLOGdata.WiFiMac[4] = ptuMAC[4];
	AppLOGdata.WiFiMac[5] = ptuMAC[5];
}

/* --- Funciones Locales --- */
void AppLOG_getTimeStamp (sApp_LOG_time_stamp* time_stamp)
{
//	LDD_RTC_TTime Time;		//Variable para recoger el time stamp
	
//	RTC_get_time (&Time);	//Se toma el valor del time stamp del RTC
	
//	time_stamp->data.year = (uint8)(Time.Year%100);
//	time_stamp->data.month = (uint8)Time.Month;
//	time_stamp->data.day = (uint8)Time.Day;
//	time_stamp->data.hour = (uint8)Time.Hour;
//	time_stamp->data.minute = (uint8)Time.Minute;
//	time_stamp->data.seccond = (uint8)Time.Second;
}

void AppLOG_getHPdata (sAppLOG_HPdata* HPdata, tHPcryoData *HP, tPRFdata *PRF)
{
	HPdata->data.HPindex = PRF->IDperifHW; //1-4 -> HP1:1 - HP2:2 - HP3:3 - HP4:4
	HPdata->data.fw_version = (uint8)EXPdata.perif[PRF->IDperifHW].data.fields.version;
	HPdata->data.model = (uint8)PRF->common->data.fields.model;
}

void AppLOG_TRT2ASCII (uint8 *TrtAscii)
{
//	uint16 i;		//auxiliar para bucle
//	/*DEBUG*/
////	AppLOG_trt.data.trt_num = 245;
////
////	AppLOG_trt.data.time_stamp.data.year = 2021;
////	AppLOG_trt.data.time_stamp.data.month = 2;
////	AppLOG_trt.data.time_stamp.data.day = 5;
////	AppLOG_trt.data.time_stamp.data.hour = 13;
////	AppLOG_trt.data.time_stamp.data.minute = 23;
////	AppLOG_trt.data.time_stamp.data.seccond = 12;
////
////	AppLOG_trt.data.HP_data.data.HPindex = 2;
////	AppLOG_trt.data.HP_data.data.fw_version = 21;
////	AppLOG_trt.data.HP_data.data.model = 3;
////
////	AppLOG_trt.data.PW_pelt_1 = 45;
////	AppLOG_trt.data.PW_pelt_2 = 73;
////	AppLOG_trt.data.cal1 = 23;
////	AppLOG_trt.data.cal2 = -45;
////	AppLOG_trt.data.cal3 = 64860;
////	AppLOG_trt.data.label = 3;
////	AppLOG_trt.data.return_flow = 11;
////	AppLOG_trt.data.temp_return = 2812;
////	AppLOG_trt.data.vac_level = 23482;
////	AppLOG_trt.data.vac_rtry = 12;
////	AppLOG_trt.data.vac_set_point = 22000;
//	/*DEBUG*/
	
//	sprintf(AppLOG_trt_ASCII.data.LOG_data_type, "TRT;");
//	sprintf(AppLOG_trt_ASCII.data.LOG_time_stamp, "%02u/%02u/20%02u;%02u:%02u:%02u;",
//			AppLOG_trt.data.time_stamp.data.day,
//			AppLOG_trt.data.time_stamp.data.month,
//			AppLOG_trt.data.time_stamp.data.year,
//			AppLOG_trt.data.time_stamp.data.hour,
//			AppLOG_trt.data.time_stamp.data.minute,
//			AppLOG_trt.data.time_stamp.data.seccond);
//	sprintf(AppLOG_trt_ASCII.data.trt_num, "%05lu;", AppLOG_trt.data.trt_num);
//	sprintf(AppLOG_trt_ASCII.data.MCC, "%03d;", AppLOG_trt.data.MCC);
//	sprintf(AppLOG_trt_ASCII.data.HP_index, "HP%01u;", AppLOG_trt.data.HP_data.data.HPindex);
//	sprintf(AppLOG_trt_ASCII.data.HP_model, "%s", APP_LOG_HP_MODELS_ASCII[AppLOG_trt.data.HP_data.data.model]);
//	sprintf(AppLOG_trt_ASCII.data.HP_fw_version, "%02u;", AppLOG_trt.data.HP_data.data.fw_version);
//	sprintf(AppLOG_trt_ASCII.data.label, "%c%02d;",
//			HP_CRYO_LABEL_CODE[AppLOG_trt.data.label][0], HP_CRYO_LABEL_CODE[AppLOG_trt.data.label][1]);
//	sprintf(AppLOG_trt_ASCII.data.Frostbite, "%03d;", AppLOG_trt.data.Frostbite);
//	sprintf(AppLOG_trt_ASCII.data.sns_1, "%03i,%02i;", ((AppLOG_trt.data.sns[0]%100000)/100), AppLOG_ABSval(AppLOG_trt.data.sns[0]%100));
//	sprintf(AppLOG_trt_ASCII.data.sns_2, "%03i,%02i;", ((AppLOG_trt.data.sns[1]%100000)/100), AppLOG_ABSval(AppLOG_trt.data.sns[1]%100));
//	sprintf(AppLOG_trt_ASCII.data.sns_3, "%03i,%02i;", ((AppLOG_trt.data.sns[2]%100000)/100), AppLOG_ABSval(AppLOG_trt.data.sns[2]%100));
//	sprintf(AppLOG_trt_ASCII.data.sns_4, "%03i,%02i;", ((AppLOG_trt.data.sns[3]%100000)/100), AppLOG_ABSval(AppLOG_trt.data.sns[3]%100));
//	sprintf(AppLOG_trt_ASCII.data.sns_5, "%03i,%02i;", ((AppLOG_trt.data.sns[4]%100000)/100), AppLOG_ABSval(AppLOG_trt.data.sns[4]%100));
//	sprintf(AppLOG_trt_ASCII.data.sns_6, "%03i,%02i;", ((AppLOG_trt.data.sns[5]%100000)/100), AppLOG_ABSval(AppLOG_trt.data.sns[5]%100));
//	sprintf(AppLOG_trt_ASCII.data.sns_7, "%03i,%02i;", ((AppLOG_trt.data.sns[6]%100000)/100), AppLOG_ABSval(AppLOG_trt.data.sns[6]%100));
//	sprintf(AppLOG_trt_ASCII.data.sns_8, "%03i,%02i;", ((AppLOG_trt.data.sns[7]%100000)/100), AppLOG_ABSval(AppLOG_trt.data.sns[7]%100));
//	sprintf(AppLOG_trt_ASCII.data.sns_9, "%03i,%02i;", ((AppLOG_trt.data.sns[8]%100000)/100), AppLOG_ABSval(AppLOG_trt.data.sns[8]%100));
//	sprintf(AppLOG_trt_ASCII.data.vac_rty, "%03u;", AppLOG_trt.data.vac_rtry);
//	sprintf(AppLOG_trt_ASCII.data.vac_set_point, "%03u,%02u;", ((AppLOG_trt.data.vac_set_point%100000)/100), (AppLOG_trt.data.vac_set_point%100));
//	sprintf(AppLOG_trt_ASCII.data.vac_level, "%03u,%02u;", ((AppLOG_trt.data.vac_level%100000)/100), (AppLOG_trt.data.vac_level%100));
//	sprintf(AppLOG_trt_ASCII.data.PW_pelt_1, "%03u;", AppLOG_trt.data.PW_pelt_1);
//	sprintf(AppLOG_trt_ASCII.data.PW_pelt_2, "%03u;", AppLOG_trt.data.PW_pelt_2);
//	sprintf(AppLOG_trt_ASCII.data.temp_return, "%03i,%02i;", ((AppLOG_trt.data.temp_return%100000)/100), AppLOG_ABSval(AppLOG_trt.data.temp_return%100));
//	sprintf(AppLOG_trt_ASCII.data.cal1, "%04i,%01i;", ((AppLOG_trt.data.cal1%100000)/10), AppLOG_ABSval(AppLOG_trt.data.cal1%10));
//	sprintf(AppLOG_trt_ASCII.data.cal2, "%04i,%01i;", ((AppLOG_trt.data.cal2%100000)/10), AppLOG_ABSval(AppLOG_trt.data.cal2%10));
//	sprintf(AppLOG_trt_ASCII.data.cal3, "%04i,%01i;", ((AppLOG_trt.data.cal3%100000)/10), AppLOG_ABSval(AppLOG_trt.data.cal3%10));
//	sprintf(AppLOG_trt_ASCII.data.return_flow, "%02u,%01u;", ((AppLOG_trt.data.return_flow%1000)/10), (AppLOG_trt.data.return_flow%10));
//	sprintf(AppLOG_trt_ASCII.data.END, "\r\n");
	
//	for(i=0;i<(APP_LOG_TRT_ASCII_VECTOR_SIZE);i++)
//	{	TrtAscii[i] = AppLOG_trt_ASCII.vector[i];	}
}

void AppLOG_Error2ASCII (uint8 *ErrorAscii)
{
//	uint16 i;		//auxiliar para bucle
//	/*DEBUG*/
////	AppLOG_error.data.trt_num = 256;
////
////	AppLOG_error.data.time_stamp.data.year = 2021;
////	AppLOG_error.data.time_stamp.data.month = 2;
////	AppLOG_error.data.time_stamp.data.day = 5;
////	AppLOG_error.data.time_stamp.data.hour = 13;
////	AppLOG_error.data.time_stamp.data.minute = 23;
////	AppLOG_error.data.time_stamp.data.seccond = 12;
////
////	AppLOG_error.data.err_code = 4004;
//	/*DEBBUG*/
	
//	sprintf(AppLOG_error_ASCII.data.LOG_data_type, "ERR;");
	
//	sprintf(AppLOG_error_ASCII.data.LOG_time_stamp, "%02u/%02u/20%02u;%02u:%02u:%02u;",
//			AppLOG_error.data.time_stamp.data.day,
//			AppLOG_error.data.time_stamp.data.month,
//			AppLOG_error.data.time_stamp.data.year,
//			AppLOG_error.data.time_stamp.data.hour,
//			AppLOG_error.data.time_stamp.data.minute,
//			AppLOG_error.data.time_stamp.data.seccond);
	
//	sprintf(AppLOG_error_ASCII.data.trt_num, "%05lu;", AppLOG_error.data.trt_num);
	
//	sprintf(AppLOG_error_ASCII.data.err_code, "%04u;", AppLOG_error.data.err_code);
	
//	sprintf(AppLOG_error_ASCII.data.END, "\r\n");
	
//	for(i=0;i<(APP_LOG_ERROR_ASCII_VECTOR_SIZE);i++)
//	{	ErrorAscii[i] = AppLOG_error_ASCII.vector[i];	}
}

void AppLOG_Warning2ASCII (uint8 *WarningAscii)
{
//	uint16 i;		//auxiliar para bucle
//	/*DEBUG*/
////	AppLOG_warning.data.time_stamp.data.year = 2021;
////	AppLOG_warning.data.time_stamp.data.month = 2;
////	AppLOG_warning.data.time_stamp.data.day = 5;
////	AppLOG_warning.data.time_stamp.data.hour = 13;
////	AppLOG_warning.data.time_stamp.data.minute = 23;
////	AppLOG_warning.data.time_stamp.data.seccond = 12;
////
////	AppLOG_warning.data.wng_code = 3123;
//	/*DEBUG*/
	
//	sprintf(AppLOG_warning_ASCII.data.LOG_data_type, "WNG;");
	
//	sprintf(AppLOG_warning_ASCII.data.LOG_time_stamp, "%02u/%02u/20%02u;%02u:%02u:%02u;",
//			AppLOG_warning.data.time_stamp.data.day,
//			AppLOG_warning.data.time_stamp.data.month,
//			AppLOG_warning.data.time_stamp.data.year,
//			AppLOG_warning.data.time_stamp.data.hour,
//			AppLOG_warning.data.time_stamp.data.minute,
//			AppLOG_warning.data.time_stamp.data.seccond);
	
//	sprintf(AppLOG_warning_ASCII.data.wng_code, "%04u;", AppLOG_warning.data.wng_code);
	
//	sprintf(AppLOG_warning_ASCII.data.END, "\r\n");
	
//	for(i=0;i<(APP_LOG_WARNING_ASCII_VECTOR_SIZE);i++)
//	{	WarningAscii[i] = AppLOG_warning_ASCII.vector[i];	}
}

void AppLOG_Machine2ASCII (uint8 *MachineAscii)
{
//	uint16 i;		//auxiliar para bucle
//	/*DEBUG*/
////	AppLOG_machine.data.time_stamp.data.year = 2021;
////	AppLOG_machine.data.time_stamp.data.month = 2;
////	AppLOG_machine.data.time_stamp.data.day = 5;
////	AppLOG_machine.data.time_stamp.data.hour = 13;
////	AppLOG_machine.data.time_stamp.data.minute = 23;
////	AppLOG_machine.data.time_stamp.data.seccond = 12;
////
////	AppLOG_machine.data.CPI = 116;
////	AppLOG_machine.data.cool_tank_lvl = 2;
////	AppLOG_machine.data.emergency_but = 0;
////	AppLOG_machine.data.env_temp = 2654;
////	AppLOG_machine.data.fan_rad_volt = 120;
////	AppLOG_machine.data.rad_in_temp = 2863;
////	AppLOG_machine.data.rad_out_temp = 2463;
////	AppLOG_machine.data.total_flow = 27;
//	/*DEBUG*/
	
//	sprintf(AppLOG_machine_ASCII.data.LOG_data_type, "MCHN;");
//	sprintf(AppLOG_machine_ASCII.data.LOG_time_stamp, "%02u/%02u/20%02u;%02u:%02u:%02u;",
//			AppLOG_machine.data.time_stamp.data.day,
//			AppLOG_machine.data.time_stamp.data.month,
//			AppLOG_machine.data.time_stamp.data.year,
//			AppLOG_machine.data.time_stamp.data.hour,
//			AppLOG_machine.data.time_stamp.data.minute,
//			AppLOG_machine.data.time_stamp.data.seccond);
//	sprintf(AppLOG_machine_ASCII.data.rad_in_temp, "%03i,%02i;", ((AppLOG_machine.data.rad_in_temp%100000)/100), AppLOG_ABSval(AppLOG_machine.data.rad_in_temp%100));
//	sprintf(AppLOG_machine_ASCII.data.rad_out_temp, "%03i,%02i;", ((AppLOG_machine.data.rad_out_temp%100000)/100), AppLOG_ABSval(AppLOG_machine.data.rad_out_temp%100));
//	sprintf(AppLOG_machine_ASCII.data.env_temp, "%03i,%02i;", ((AppLOG_machine.data.env_temp%100000)/100), AppLOG_ABSval(AppLOG_machine.data.env_temp%100));
//	sprintf(AppLOG_machine_ASCII.data.total_flow, "%02u,%01u;", ((AppLOG_machine.data.total_flow%1000)/10), (AppLOG_machine.data.total_flow%10));
//	sprintf(AppLOG_machine_ASCII.data.emergency_but, "%01u;", AppLOG_machine.data.emergency_but);
//	sprintf(AppLOG_machine_ASCII.data.cool_tank_lvl, "%03u;", AppLOG_machine.data.cool_tank_lvl);
//	sprintf(AppLOG_machine_ASCII.data.END, "\r\n");
	
//	for(i=0;i<(APP_LOG_MACHINE_ASCII_VECTOR_SIZE);i++)
//	{	MachineAscii[i] = AppLOG_machine_ASCII.vector[i];	}
}

void AppLOG_Mode2ASCII (uint8 *ModeAscii)
{
//	uint16 i;		//auxiliar para bucle
//	/*DEBUG*/
////	AppLOG_modes.data.time_stamp.data.year = 2021;
////	AppLOG_modes.data.time_stamp.data.month = 2;
////	AppLOG_modes.data.time_stamp.data.day = 5;
////	AppLOG_modes.data.time_stamp.data.hour = 13;
////	AppLOG_modes.data.time_stamp.data.minute = 23;
////	AppLOG_modes.data.time_stamp.data.seccond = 12;
////
////	AppLOG_modes.data.Err_delta_secure = 1;
////	AppLOG_modes.data.Err_secure = 1;
////	AppLOG_modes.data.Label_reuse = 0;
////	AppLOG_modes.data.Oscillations = 0;
////	AppLOG_modes.data.Temp_secure = 0;
////	AppLOG_modes.data.Temp_slope = 1;
//	/*DEBUG*/
	
//	sprintf(AppLOG_modes_ASCII.data.LOG_data_type, "MOD;");
	
//	sprintf(AppLOG_modes_ASCII.data.LOG_time_stamp, "%02u/%02u/20%02u;%02u:%02u:%02u;",
//			AppLOG_modes.data.time_stamp.data.day,
//			AppLOG_modes.data.time_stamp.data.month,
//			AppLOG_modes.data.time_stamp.data.year,
//			AppLOG_modes.data.time_stamp.data.hour,
//			AppLOG_modes.data.time_stamp.data.minute,
//			AppLOG_modes.data.time_stamp.data.seccond);
	
//	sprintf(AppLOG_modes_ASCII.data.Oscillations, "OSC;%01u;", AppLOG_modes.data.Oscillations);
//	sprintf(AppLOG_modes_ASCII.data.Label_reuse, "LBL_RE;%01u;", AppLOG_modes.data.Label_reuse);
//	sprintf(AppLOG_modes_ASCII.data.Temp_slope, "TEMP_SLP;%01u;", AppLOG_modes.data.Temp_slope);
//	sprintf(AppLOG_modes_ASCII.data.Temp_secure, "TEMP_SCR;%01u;", AppLOG_modes.data.Temp_secure);
//	sprintf(AppLOG_modes_ASCII.data.Err_secure, "ERR_SCR;%01u;", AppLOG_modes.data.Err_secure);
//	sprintf(AppLOG_modes_ASCII.data.Err_delta_secure, "ERR_DLT_SCR;%01u;", AppLOG_modes.data.Err_delta_secure);
	
//	sprintf(AppLOG_modes_ASCII.data.END, "\r\n");
	
//	for(i=0;i<(APP_LOG_MODES_ASCII_VECTOR_SIZE);i++)
//	{	ModeAscii[i] = AppLOG_modes_ASCII.vector[i];	}
}

void AppLOG_TRT_Definition_2_ASCII (void)
{
	sprintf(AppLOG_trt_definition_ASCII.data.LOG_data_type, "TRT;");
	sprintf(AppLOG_trt_definition_ASCII.data.LOG_time_stamp, "DATE;HOUR;");
	sprintf(AppLOG_trt_definition_ASCII.data.trt_num, "TRTnum;");
	sprintf(AppLOG_trt_definition_ASCII.data.MCC, "MCC;");
	sprintf(AppLOG_trt_definition_ASCII.data.HP_index, "PORT;");
	sprintf(AppLOG_trt_definition_ASCII.data.HP_model, "MODEL HP;");
	sprintf(AppLOG_trt_definition_ASCII.data.HP_fw_version, "FW;");
	sprintf(AppLOG_trt_definition_ASCII.data.label, "Label;");
	sprintf(AppLOG_trt_definition_ASCII.data.sns_1, "SNS1;");
	sprintf(AppLOG_trt_definition_ASCII.data.sns_2, "SNS2;");
	sprintf(AppLOG_trt_definition_ASCII.data.sns_3, "SNS3;");
	sprintf(AppLOG_trt_definition_ASCII.data.sns_4, "SNS4;");
	sprintf(AppLOG_trt_definition_ASCII.data.sns_5, "SNS5;");
	sprintf(AppLOG_trt_definition_ASCII.data.sns_6, "SNS6;");
	sprintf(AppLOG_trt_definition_ASCII.data.sns_7, "SNS7;");
	sprintf(AppLOG_trt_definition_ASCII.data.sns_8, "SNS8;");
	sprintf(AppLOG_trt_definition_ASCII.data.sns_9, "SNS9;");
	sprintf(AppLOG_trt_definition_ASCII.data.Frostbite, "FROSTBITE;");
	sprintf(AppLOG_trt_definition_ASCII.data.vac_rty, "VAC_RTY;");
	sprintf(AppLOG_trt_definition_ASCII.data.vac_set_point, "VAC_SET;");
	sprintf(AppLOG_trt_definition_ASCII.data.vac_level, "VAC_LVL;");
	sprintf(AppLOG_trt_definition_ASCII.data.PW_pelt_1, "PW1;");
	sprintf(AppLOG_trt_definition_ASCII.data.PW_pelt_2, "PW2;");
	sprintf(AppLOG_trt_definition_ASCII.data.temp_return, "TMP_RTN;");
	sprintf(AppLOG_trt_definition_ASCII.data.cal1, "CAL1;");
	sprintf(AppLOG_trt_definition_ASCII.data.cal2, "CAL2;");
	sprintf(AppLOG_trt_definition_ASCII.data.cal3, "CAL3;");
	sprintf(AppLOG_trt_definition_ASCII.data.return_flow, "RTN_FLW;");
	sprintf(AppLOG_trt_definition_ASCII.data.END, "\r\n");
}

void AppLOG_MACHINE_Definition_2_ASCII (void)
{	
	sprintf(AppLOG_machine_definition_ASCII.data.LOG_data_type, "MCHN;");
	sprintf(AppLOG_machine_definition_ASCII.data.LOG_time_stamp, "DATE;HOUR;");
	sprintf(AppLOG_machine_definition_ASCII.data.rad_in_temp, "TMP_RAD_IN;");
	sprintf(AppLOG_machine_definition_ASCII.data.rad_out_temp, "TMP_RAD_OUT;");
	sprintf(AppLOG_machine_definition_ASCII.data.env_temp, "TMP_ENV;");
	sprintf(AppLOG_machine_definition_ASCII.data.total_flow, "TTL_FLW;");
	sprintf(AppLOG_machine_definition_ASCII.data.emergency_but, "EMG_BUT;");
	sprintf(AppLOG_machine_definition_ASCII.data.cool_tank_lvl, "COOL_LVL;");
	sprintf(AppLOG_machine_definition_ASCII.data.END, "\r\n");
}

int AppLOG_ABSval(int y)	//Devuelve el valor absoluto sin signo de un int
{
	if(y<0){return(y*-1);}
	else{return(y);}
}

int16 AppLOG_FLOAT_2_INT16(float value)
{
	int16 return_val;
	if(value > APP_LOG_MAX_INT16_VALUE)				//Se mira que el valor no supere el maximo de un int16
	{	return_val = APP_LOG_MAX_INT16_VALUE;	}	//Se le da el valor maximo
	else if(value < APP_LOG_MIN_INT16_VALUE)		//Se mira que el valor no sea inferior que el minimo de un int16
	{	return_val = APP_LOG_MIN_INT16_VALUE;	}	//Se le da el valor minimo
	else											//Si entra dentro del rango
	{	return_val = (int16)value;	}				//Se castea y se devuelve el valor
	
	return return_val;
}

uint8 AppLOG_FLOAT_2_UINT8(float value)
{
	uint8 return_val;
	if(value > APP_LOG_MAX_UINT8_VALUE)				//Se mira que el valor no supere el maximo de un uint8
	{	return_val = APP_LOG_MAX_UINT8_VALUE;	}	//Se le da el valor maximo
	else if(value < APP_LOG_MIN_UINT8_VALUE)		//Se mira que el valor no sea inferior que el minimo de un uint8
	{	return_val = APP_LOG_MIN_UINT8_VALUE;	}	//Se le da el valor minimo
	else											//Si entra dentro del rango
	{	return_val = (uint8)value;	}				//Se castea y se devuelve el valor
	
	return return_val;
}

