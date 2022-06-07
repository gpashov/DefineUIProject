/*
 * AppLOG.h
 *
 *  Created on: Jan 21, 2021
 *      Author: sguerrero
 */

#ifndef APPLOG_H_
#define APPLOG_H_

#include "../Perifericos/HPcryo.h"

#define APP_LOG_TIME_TO_REC_TRT		1000//60000	/* 1 minuto (min aprox 1seg)*/
#define APP_LOG_TIME_TO_REC_MACHINE	1000//300000	/* 5 minutos (min 1.5seg)*/

/*  */
typedef enum
{
	AppLOG_No_Command,
	
	AppLOG_SendASCII_LOG,
	AppLOG_SendRAW_LOG,
	AppLOG_Send_USB_ASCII_LOG,
	AppLOG_Send_USB_RAW_LOG,
	AppLOG_Send_RecentLOG_ASCII_USB,
	AppLOG_Send_RecentLOG_ASCII,
	AppLOG_Erase_LOG,
	AppLOG_saveRAM,
}eAppLOGcommands;

/* FUNCIONES GLOBALES */
/* Inicializacion del AppLOG */
void AppLOG_init(void);

/* Motor del AppLOG */
void AppLOG_motor(void);

/* Almacena en el LOG la variables de un aplicador relacionadas con un tratamiento (excluyendo las sondas de temperatura */
void AppLOG_saveTRT(tHPcryoData *HP, tPRFdata *PRF);

/* Almacena en el LOG las variables relacionadas con un error producido */
void AppLOG_saveERROR(uint16 error_code, tHPcryoData *HP, tPRFdata *PRF);

/* Almacena en el LOG las variables relacionadas con los avisos que se producen */
void AppLOG_saveWARNING(uint16 warning_code);

/* Almacena en el LOG las variables relacionadas con el estado del equipo */
void AppLOG_saveMachine(void);

/* Almacena en el LOG los modos de funcionamiento del equipo que estan programados */
void AppLOG_saveModes(void);

/* Devuelve el comando que se encuentra ejecutando */
eAppLOGcommands AppLOG_GetCommand (void);

/* Establece un comando para ejecutar */
void AppLOG_SetCommand (eAppLOGcommands Command);

/* Recoge la MAC de la WiFi */
void AppLOGsetWiFiMAC (uint8 *ptuMAC);

#endif /* APPLOG_H_ */
