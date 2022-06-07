/*
 * GPRS.h
 *
 *  Created on: Mar 25, 2021
 *      Author: sguerrero
 */

#ifndef GPRS_H_
#define GPRS_H_

/* - Librerias - */
#include "GeneralDefines.h"
#include "../ProtocolMaster/ProtocolMaster.h"
//#include "../Ticks/Ticks.h"

/* - Estructuras - */
typedef enum
{
	GPRS_PROTMST_COM_OP_READ = OPERACIO_LECTURA,
	GPRS_PROTMST_COM_OP_WRITE = OPERACIO_ESCRIPTURA
}eGPRScomOp;

/* - Variables - */


/* - Declaracion funciones globales - */
void GPRS_init (void);						//Inicializacion del modulo que se comunica con el GPRS
returnstatus_t GPRS_getMCC(uint16* MCC, uint8 saveEnable);	//Obtener MCC solicitandolo al modulo GPRS
returnstatus_t GPRS_get_FLASH_MCC(uint16* MCC);
returnstatus_t GPRS_reset(void);			//Reset del modulo GPRS
returnstatus_t GPRScomOrder( eGPRScomOp operation, uint8 memID, uint32 addr, uint8 nBytes, uint8 *buffer);
void GPRS_Clear_FLASH(uint8* conf, uint16* flashMCC, uint8 val);
uint8 GPRS_board_Answer();

#endif /* GPRS_H_ */
