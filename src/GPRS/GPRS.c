/*
 * GPRS.c
 *
 *  Created on: Mar 25, 2021
 *      Author: sguerrero
 */

/* - Librerias - */

#include "GPRS.h"
//#include "../ExternalNANDFlash/ExternalNANDFlash.h"
#include "../Expansora/Expansora.h"
#include "../BOOT/boot.h"

/* - Definiciones - */
typedef union
{
	uint8 bufferIn[20];
	uint16 mccs[10];
}bufferUnion_t;

//union
//{
//	struct
//	{
//		uint8 status;
//		uint8 dummy;
//		uint16 MCC[10];
//	}GPRS_config;
//	uint8 buffer[22];
//}buffer_GPRS;
uint16 MCC_local[10];	//valor MCC obtenido (variable local)

#define GPRS_PROTMST_ADDR_SLAVE			0x68
#define GPRS_PROTMST_MAX_BYTES			64
#define GPRS_PROTMST_FRAME_TIMEOUT		333
#define GPRS_PROTMST_MAX_RETRYS			1//3
#define GPRS_PROTMST_SLOT_POS			0
#define	GPRS_PROTMST_BLOCKING_TIMEOUT 	( ( GPRS_PROTMST_FRAME_TIMEOUT * GPRS_PROTMST_MAX_RETRYS) + 500)
#define	GPRS_PROTMST_DATA_MEM_ID 		0
#define GPRS_PROTMST_MCC_ADDR			96	
#define GPRS_PROTMST_ACCIONS_ADDR		44

typedef enum
{
	GPRS_IDLE,
	GPRS_RESET,
	GPRS_ACCION_GUARDAR_CONFIG,
	GPRS_GET_COUNTRY,
	
	GPRS_MAX_ACCIONES
}eGPRScommands;


/* - Estrcuturas - */

/* - Variables - */

uint8 GetMCC_motor;
uint8 BoardConn;

/* - Declaracion funciones locales - */

returnstatus_t GPRScomOrder( eGPRScomOp operation, uint8 memID, uint32 addr, uint8 nBytes, uint8 *buffer);

/* - Funciones globales - */

void GPRS_init (void)
{
	GetMCC_motor = 0;
	BoardConn = 0;
	//returnstatus_t retorno; //V7790 #JM_GPRS
	if(EXPdata.UC.Config_Param.data.GPRS_iniciado == 1) // posibles valores 0,1 o 2. 0 Sin datos. 1 con datos. 2 Con placa pero sin datos. Excepto con 1, se ponen ceros en el valor
	{
		MCC_local[0] = EXPdata.UC.Config_Param.data.MCC[0];
		MCC_local[1] = EXPdata.UC.Config_Param.data.MCC[1];
		MCC_local[2] = EXPdata.UC.Config_Param.data.MCC[2];
		MCC_local[3] = EXPdata.UC.Config_Param.data.MCC[3];
		MCC_local[4] = EXPdata.UC.Config_Param.data.MCC[4];
		MCC_local[5] = EXPdata.UC.Config_Param.data.MCC[5];
		MCC_local[6] = EXPdata.UC.Config_Param.data.MCC[6];
		MCC_local[7] = EXPdata.UC.Config_Param.data.MCC[7];
		MCC_local[8] = EXPdata.UC.Config_Param.data.MCC[8];
		MCC_local[9] = EXPdata.UC.Config_Param.data.MCC[9];
	}
	else
	{
		MCC_local[0] = 0;
		MCC_local[1] = 0;
		MCC_local[2] = 0;
		MCC_local[3] = 0;
		MCC_local[4] = 0;
		MCC_local[5] = 0;
		MCC_local[6] = 0;
		MCC_local[7] = 0;
		MCC_local[8] = 0;
		MCC_local[9] = 0;
	}
//	do
//	{
//		retorno = EXTNAND_ReadBytes(EXTERNAL_NAND_FLASH_GPRS_INIT_ADDR, buffer_GPRS.buffer, 22);
//		switch(retorno)
//		{
//		case RUNNING: break;
//		case SUCCESS:
//			if(buffer_GPRS.GPRS_config.status == 1)
//			{
//				MCC_local[0] = EXPdata.UC.Config_Param.data.MCC[0];
//				MCC_local[1] = buffer_GPRS.GPRS_config.MCC[1];
//				MCC_local[2] = buffer_GPRS.GPRS_config.MCC[2];
//				MCC_local[3] = buffer_GPRS.GPRS_config.MCC[3];
//				MCC_local[4] = buffer_GPRS.GPRS_config.MCC[4];
//				MCC_local[5] = buffer_GPRS.GPRS_config.MCC[5];
//				MCC_local[6] = buffer_GPRS.GPRS_config.MCC[6];
//				MCC_local[7] = buffer_GPRS.GPRS_config.MCC[7];
//				MCC_local[8] = buffer_GPRS.GPRS_config.MCC[8];
//				MCC_local[9] = buffer_GPRS.GPRS_config.MCC[9];
//			}
//			else
//			{
//				MCC_local[0] = 0;
//				MCC_local[1] = 0;
//				MCC_local[2] = 0;
//				MCC_local[3] = 0;
//				MCC_local[4] = 0;
//				MCC_local[5] = 0;
//				MCC_local[6] = 0;
//				MCC_local[7] = 0;
//				MCC_local[8] = 0;
//				MCC_local[9] = 0;
//			}
//			break;
//		case ERROR:
//		default:
//			//TEST_PrintInfo("Read error\r\n");
//			break;
//		}
//	}while(retorno == RUNNING);
	
}

//V7790 #JM_GPRS // obtener las posición de la flash
returnstatus_t GPRS_get_FLASH_MCC(uint16* MCC)
{
	returnstatus_t ret;
	if(EXPdata.UC.Config_Param.data.GPRS_iniciado == 1)
	{
		MCC[0] = EXPdata.UC.Config_Param.data.MCC[0];
		MCC[1] = EXPdata.UC.Config_Param.data.MCC[1];
		MCC[2] = EXPdata.UC.Config_Param.data.MCC[2];
		MCC[3] = EXPdata.UC.Config_Param.data.MCC[3];
		MCC[4] = EXPdata.UC.Config_Param.data.MCC[4];
		MCC[5] = EXPdata.UC.Config_Param.data.MCC[5];
		MCC[6] = EXPdata.UC.Config_Param.data.MCC[6];
		MCC[7] = EXPdata.UC.Config_Param.data.MCC[7];
		MCC[8] = EXPdata.UC.Config_Param.data.MCC[8];
		MCC[9] = EXPdata.UC.Config_Param.data.MCC[9];
		ret = SUCCESS;
	}
	else if(EXPdata.UC.Config_Param.data.GPRS_iniciado == 2)
	{
		ret = BLOCKING;
	}
	else
	{
		ret = ERROR;
	}
	return ret;
}

returnstatus_t GPRS_getMCC(uint16* MCC, uint8 saveEnable)
{
	static uint8 flag = 0;
	uint8 bufferOut[1];			//Buffer donde se incluye la orden a transmitir
	bufferUnion_t bufferUnion;
				//Buffer de recepcion del MCC a obtener
	returnstatus_t ret;			//Retorno de la funcion (el estado del proceso)
	//uint8 bufferPointer = 0;
	ret = RUNNING;
	
	switch(GetMCC_motor)
	{
	case 0:
		bufferOut[0] = GPRS_GET_COUNTRY;
		switch(GPRScomOrder( GPRS_PROTMST_COM_OP_WRITE, GPRS_PROTMST_DATA_MEM_ID, GPRS_PROTMST_ACCIONS_ADDR, 1, bufferOut))	//Se envia el comando
		{
		case SUCCESS:	GetMCC_motor = 1;	flag = 0; break;
		case RUNNING:		
			break;
		case ERROR:
		default:
			GetMCC_motor = 0xF0;
			break;
		}
		break;
	case 1:
		switch(GPRScomOrder( GPRS_PROTMST_COM_OP_READ, GPRS_PROTMST_DATA_MEM_ID, GPRS_PROTMST_MCC_ADDR, 20, bufferUnion.bufferIn))	//Lectura del memory map (MCC)
		{
		case SUCCESS:	
			//MCC_local = (((uint16)bufferIn[1]<<8) + ((uint16)bufferIn[0]));
			//V7790 #JM_GPRS
			if(bufferUnion.mccs[0] > 99 && bufferUnion.mccs[0] < 1000)
			{
				if(saveEnable)
				{
					EXPdata.UC.Config_Param.data.MCC[0] = bufferUnion.mccs[0];
					EXPdata.UC.Config_Param.data.MCC[1] = bufferUnion.mccs[1];
					EXPdata.UC.Config_Param.data.MCC[2] = bufferUnion.mccs[2];
					EXPdata.UC.Config_Param.data.MCC[3] = bufferUnion.mccs[3];
					EXPdata.UC.Config_Param.data.MCC[4] = bufferUnion.mccs[4];
					EXPdata.UC.Config_Param.data.MCC[5] = bufferUnion.mccs[5];
					EXPdata.UC.Config_Param.data.MCC[6] = bufferUnion.mccs[6];
					EXPdata.UC.Config_Param.data.MCC[7] = bufferUnion.mccs[7];
					EXPdata.UC.Config_Param.data.MCC[8] = bufferUnion.mccs[8];
					EXPdata.UC.Config_Param.data.MCC[9] = bufferUnion.mccs[9];
					EXPdata.UC.Config_Param.data.GPRS_iniciado = 1;
					//while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
					saveMMC(1,bufferUnion.mccs);
				}
			}
			MCC_local[0] = bufferUnion.mccs[0];
			MCC_local[1] = bufferUnion.mccs[1];
			MCC_local[2] = bufferUnion.mccs[2];
			MCC_local[3] = bufferUnion.mccs[3];
			MCC_local[4] = bufferUnion.mccs[4];
			MCC_local[5] = bufferUnion.mccs[5];
			MCC_local[6] = bufferUnion.mccs[6];
			MCC_local[7] = bufferUnion.mccs[7];
			MCC_local[8] = bufferUnion.mccs[8];
			MCC_local[9] = bufferUnion.mccs[9];
			
			GetMCC_motor = 2;
			BoardConn = 1;
			break;
		case RUNNING:		//No debe de verse este estado por que la transmision es bloqueante
			break;
		case ERROR:
		default:
			GetMCC_motor = 0xF0;
			break;
		}
		break;
	case 2:
		switch(MCC_local[0])
		{
		case 0:					//Inicializado el valor de MCC
			if(flag == 1)
			{
				GetMCC_motor = 0x80;
			}
			else
				GetMCC_motor = 1;	
			break;
		case 10:				//RUNNING el proceso de obtener el MCC
			flag = 1;
			GetMCC_motor = 1;
			break;
		case 20:				//ERROR en el proceso de obtener el MCC
		case 30:				//ERROR por time out en el proceso de obtener el MCC
			GetMCC_motor = 0x80;
			break;
		default:				//En cualquier otro caso, obtenemos un valor para el MCC que no son los que nos indican algún detalle del proceso
			GetMCC_motor = 0x80;
			break;
		}
		break;
	case 0x80:
		GetMCC_motor = 0;
		MCC[0] = MCC_local[0];			//Devuelvo el MCC obtenido
		MCC[1] = MCC_local[1];
		MCC[2] = MCC_local[2];
		MCC[3] = MCC_local[3];
		MCC[4] = MCC_local[4];
		MCC[5] = MCC_local[5];
		MCC[6] = MCC_local[6];
		MCC[7] = MCC_local[7];
		MCC[8] = MCC_local[8];
		MCC[9] = MCC_local[9];
		ret = SUCCESS;
		break;
	case 0xF0:
	default:
		GetMCC_motor = 0;
		MCC[0] = 0;		//En caso de erro entrego el ultimo MCC obtenido (0 si no se ha obtenido previamente)
		ret = ERROR;
		break;
	}
	
	return ret;
}

returnstatus_t GPRS_reset(void)
{
	returnstatus_t ret;
	
	uint8 bufferOut[1];
	
	bufferOut[0] = GPRS_RESET;
	
	ret = GPRScomOrder( GPRS_PROTMST_COM_OP_WRITE, GPRS_PROTMST_DATA_MEM_ID, GPRS_PROTMST_ACCIONS_ADDR, 1, bufferOut);		//Se envia la orden de reset

	return ret;
}

/* - Funciones locales - */

/*
 * memID = 0 -> para escribir las acciones y para leer del Memory Map MCC
 * */
returnstatus_t GPRScomOrder( eGPRScomOp operation, uint8 memID, uint32 addr, uint8 nBytes, uint8 *buffer)
{
	nova_ordre_t order;
	ordre_status_t orderStatus;
	prot_mems_status_t memoryStatus;
	uint8 slaveStatus;
	uint8 slaveStatus1, slaveStatus2;
	uint32 time;
	uint8 nBytesToSend;
	uint8 *dirRel;	
	
	/* El status de la placa lo recibimos al llamar a "PROTMST_EstatOrdre" en el "ptuEstatEsclau". Aprovechamos
	 * para refrescarlo cada vez que hagamos una trama buena. */
	//slaveStatus = &( EXPdata.header.fields.board_status.status);
	
	/* El buffer interno del PROTOCOL MASTER tiene un límite de bytes, tenemos que dividir el 
	 * buffer del usuario en trozos de como máximo dicho tamaño */
	nBytesToSend = nBytes;
	dirRel = buffer;
	
	while( nBytesToSend > 0)
	{
		/* Inicializamos la estructura de ordern para el protocolo con los datos que recibidos */
		order.fields.u8AddrEsclau = GPRS_PROTMST_ADDR_SLAVE;
		order.fields.tipus_operacio = operation;
		order.fields.u8Memoria = memID;
		if( nBytesToSend > GPRS_PROTMST_MAX_BYTES){ order.fields.u8NumBytes = GPRS_PROTMST_MAX_BYTES;}
		else{ order.fields.u8NumBytes = nBytesToSend;}				
		order.fields.u16TimeoutTrama = GPRS_PROTMST_FRAME_TIMEOUT;
		order.fields.u16MaxReintents = GPRS_PROTMST_MAX_RETRYS;
		order.fields.u32Addr = addr;
		
		/* Esta función hace un uso bloqueante de la librería protocol master. 
		 * Primero intentamos encolar la orden de comunicaciones durante un tiempo máximo */
		time = TICKS_GetTicks();
		while( PROTMST_EncuaOrdre( GPRS_PROTMST_SLOT_POS, order, dirRel) != SUCCESS &&
			   TICKS_DiffTicks( time) < GPRS_PROTMST_BLOCKING_TIMEOUT)
		{
			/* No conseguimos encolar la orden de comunicaciones, llamamos al motor para liberar el esclavo */
			PROTMST_Motor();		
		}
		
		/* Esperamos a que la orden se haya completado o salgamos por timeout. Si en el anterior hemos salido
		 * por timeout el while nunca entrará.
		 * Forzamos a 0 el orderStatus para que siempre entre la primera vez al while, no nos fiamos de que
		 * la funcion "PROTMST_EstatOrdre" no de problemas si no se ha podido encolar la orden en el anterior
		 * while por el timeout. (Si miramos su coigo fuente no parece que tenga que dar ningun problema de 
		 * todos modos) */
		orderStatus.value = 0;
		while( ( orderStatus.value & 0xF0) == 0 && TICKS_DiffTicks( time) < GPRS_PROTMST_BLOCKING_TIMEOUT)
		{			
			/* La comunicación esta en curso, llamamos al motor */
			PROTMST_Motor();
			
			/* Siguiente comprobación de status */
			orderStatus = PROTMST_EstatOrdre( GPRS_PROTMST_SLOT_POS, &memoryStatus, 
											  &slaveStatus, &slaveStatus1, &slaveStatus2);
		}
			
		/* Comprobamos si hemos salido por timeout */
		if( TICKS_DiffTicks( time) >= GPRS_PROTMST_BLOCKING_TIMEOUT)
		{
			/* Timeout de bloqueo agotado, error de comunicaciones */
			return ERROR; 
			//OJO ESTO TENEMOS QUE LLAMAR AL MOTOR CON EL ESTATORDRE HASTA QUE DE FINALIZADO PDTE
		}
		
		/* Si llegamos aqui no hemos salido por timeout, comprobamos el resultado de la comunicación */
		if( orderStatus.bit_field.u8OrdreFinalitzada)
		{
			/* La comunicación ha ido bien, actualizamos para el envio del siguiente trozo del buffer */
			nBytesToSend = nBytesToSend - order.fields.u8NumBytes;
			dirRel = dirRel + order.fields.u8NumBytes;
			addr += order.fields.u8NumBytes;
		}
		else
		{
			/* La comunicación ha fallado. Indicamos eror general de comunicaciones */
			return ERROR;
		}	
	}
	
	if( nBytesToSend == 0){ return SUCCESS;}else{ return ERROR;}
}

void GPRS_Clear_FLASH(uint8* conf, uint16* flashMCC, uint8 val) //#JM_GPRS
{
	/*returnstatus_t ret;
	//borrar las 10 posiciones de mcc
	buffer_GPRS.GPRS_config.MCC[0] = 0; 
	buffer_GPRS.GPRS_config.MCC[1] = 0;
	buffer_GPRS.GPRS_config.MCC[2] = 0;
	buffer_GPRS.GPRS_config.MCC[3] = 0;
	buffer_GPRS.GPRS_config.MCC[4] = 0;
	buffer_GPRS.GPRS_config.MCC[5] = 0;
	buffer_GPRS.GPRS_config.MCC[6] = 0;
	buffer_GPRS.GPRS_config.MCC[7] = 0;
	buffer_GPRS.GPRS_config.MCC[8] = 0;
	buffer_GPRS.GPRS_config.MCC[9] = 0;
	buffer_GPRS.GPRS_config.status = 0;
	do
	{
		ret = EXTNAND_WriteBytes(EXTERNAL_NAND_FLASH_GPRS_INIT_ADDR, buffer_GPRS.buffer, EXTERNAL_NAND_FLASH_PAGE_SIZE);
	}while(ret == RUNNING);*/
	*conf = val;
	flashMCC[0] = 0;
	flashMCC[1] = 0;
	flashMCC[2] = 0;
	flashMCC[3] = 0;
	flashMCC[4] = 0;
	flashMCC[5] = 0;
	flashMCC[6] = 0;
	flashMCC[7] = 0;
	flashMCC[8] = 0;
	flashMCC[9] = 0;
}

uint8 GPRS_board_Answer()
{
	return BoardConn;
}
