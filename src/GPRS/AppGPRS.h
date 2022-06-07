/*
 * AppGPRS.h
 *
 *  Created on: Mar 30, 2021
 *      Author: sguerrero
 */

#ifndef APPGPRS_H_
#define APPGPRS_H_

/* - Librerias - */
#include "GeneralDefines.h"
//#include "../Error/gestionError.h"
/* - Estrcuturas - */

/* - Variables - */


/* - Declaracion funciones globales - */

void AppGPRS_init (void);							//Inicializacion
returnstatus_t AppGPRS_Connect_Get_MCC (void);		//Conectar y obtener el MCC
returnstatus_t AppGPRS_GetMCCstatus (void);			//Estado del proceso de obtencion del MCC
uint16 AppGPRS_GetMCCnum (uint8 sel);				//Obtener MCC almacenado
uint8 AppGPRS_SAFE_permission (void);				//Obtener permiso para aplicar el SAFE
void AppGPRS_reset (void);							//Resetear modulo
void AppGPRSClear(uint8* conf, uint16* flashMCC, uint8 val);	//Borra el registro del GPRS en flash e impide regrabar hasta reiniciar
void AppGPRS_inc_retry(void);						//Incrementar numero de reintentos
void AppGPRS_clear_retry(void);						//set a 0 el numero de reintetos
uint8 AppGPRS_get_GPRS_board_detected(void);		//devuelve 0 si no ha detectado placa ni indicios de haberla tenido, 1 en caso de detectarla o 2 si el equipo se ha configurado con placa
uint8 appGPRS_get_signal(void);						//0 -> sin cobertura; 1 -> con cobertura; 2 -> buscando 3-> no consigue conectar con la placa

#endif /* APPGPRS_H_ */
