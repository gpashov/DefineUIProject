/*
 * ProtocolMaster.c
 *
 *  Created on: Nov 15, 2016
 *      Author: ingenieria1
 */

#include "ProtocolMaster.h"
#include "RS485/RS485.h"
#include "Ticks/Ticks.h"




#define PROTMST_TEMPS_SILENCI	15
#define PROTMST_TEMPS_REINTENT	20


protocol_status_t protocol_status;
esclau_control_t esclau_control[MAX_NUM_ESCLAUS];
protocol_frame_t protocol_framePregunta;
protocol_frame_t protocol_frameResposta;
uint8_t ptu8DataRebuda[64];

void PROTMST_GeneraHeader(esclau_control_t *esclau_actual);

returnstatus_t PROTMST_CheckHeader(header_t cab);

void PROTMST_CalculChecksum(esclau_control_t *esclau_actual);

returnstatus_t PROTMST_VerificaChecksum(esclau_control_t *esclau_actual, uint16_t u16Inicial);


void PROTMST_Init(void)
{
	uint8_t i;
	
	protocol_status.u8Enable = 1;

	protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_ORDRE;
	protocol_status.u8BytesRebuts = 0;
	protocol_status.u8EsclauActual = 0;
	protocol_status.u8CodiError = 0;
	
	for(i = 0; i < MAX_NUM_ESCLAUS; i++)
	{
		esclau_control[i].ordre.fields.u8AddrEsclau = i+1;
		esclau_control[i].ordre.fields.tipus_operacio = OPERACIO_IDLE;
		esclau_control[i].ordre_status.value = 0;
	}
	    
	protocol_status.Receive = RS485_Receive;
	protocol_status.QuantsBytesBufferRX = RS485_QuantsBytesBufferRX;
	protocol_status.ResetBuffers = RS485_ResetBuffers;
	protocol_status.Transmit = RS485_Transmit;
//	protocol_status.ResetBuffers(RS485_MST);
	
	//cr_sysMemoryMap.var.puerto485_mst.u32TramasOK = 0;
	//cr_sysMemoryMap.var.puerto485_mst.u32TramasKO = 0;
	
	RS485_Init(RS485_MST);
	
//	BUZZ_Configure(1, 100, PATRO_SO_MASTER_MODE);
//	HAL_GPIO_WritePin(DBG_LED_1_GPIO_Port, DBG_LED_1_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(DBG_LED_2_GPIO_Port, DBG_LED_2_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(DBG_LED_3_GPIO_Port, DBG_LED_3_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(DBG_LED_4_GPIO_Port, DBG_LED_4_Pin, GPIO_PIN_RESET);
}

returnstatus_t PROTMST_Motor(void)
{
	returnstatus_t temp;
	uint8_t i;
	uint16_t StatusMemoria;
	
	temp = RUNNING;
	
	switch(protocol_status.u8ProtocolMotor)
	{
	case PROT_STAT_ESPERANT_ORDRE:
		i = protocol_status.u8EsclauActual;
		StatusMemoria = esclau_control[protocol_status.u8EsclauActual].ordre_status.value;
		if(
				(esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio != OPERACIO_IDLE) && 
				((esclau_control[protocol_status.u8EsclauActual].ordre_status.value&0xF0) == 0)
		)
		{
			/* hi ha ordre per aquest esclau */
			protocol_status.u8CodiError = 0;
			protocol_status.u8ProtocolMotor = PROT_STAT_CALCULANT_HEADER;
			esclau_control[protocol_status.u8EsclauActual].u16Reintents = 0;
			esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8OrdreEnCurs = 1;
			if(esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio == OPERACIO_POOLING)
			{
				esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8PoolingEnCurs = 1;
			}
			else if(esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio == OPERACIO_RESET)
			{
				esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8ResetEnCurs = 1;
			}
			else	//OPERACIO_ESCRIPTURA i OPERACIO_LECTURA
			{
				esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8LecturaEnCurs = 1;
			}
		}
		else
		{
			protocol_status.u8EsclauActual++;
			if(protocol_status.u8EsclauActual >= MAX_NUM_ESCLAUS) protocol_status.u8EsclauActual = 0;
		}
		break;
	case PROT_STAT_CALCULANT_HEADER:
//		HAL_GPIO_TogglePin(DBG_LED_4_GPIO_Port, DBG_LED_4_Pin);
		temp = BLOCKING;
		protocol_status.ResetBuffers(RS485_MST);
		PROTMST_GeneraHeader(&esclau_control[protocol_status.u8EsclauActual]);
		esclau_control[protocol_status.u8EsclauActual].u8BytesRebuts = 0;
		protocol_status.u32TicksProtocol = TICKS_GetTicks();
		protocol_status.u8ProtocolMotor = PROT_STAT_ENVIANT_HEADER;
		break;
	case PROT_STAT_ENVIANT_HEADER:
		temp = BLOCKING;
		if(protocol_status.Transmit(RS485_MST, protocol_framePregunta.ptucBytes, sizeof(header_t), 0) == SUCCESS)
		{
			protocol_status.u8ProtocolMotor = PROT_STAT_CALCULANT_DADES;
		}
		else if(TICKS_DiffTicks(protocol_status.u32TicksProtocol) > 50)
		{
			protocol_status.u8CodiError = 6;
			protocol_status.u8ProtocolMotor = PROT_STAT_ERROR1;
		}
		break;
	case PROT_STAT_CALCULANT_DADES:
		temp = BLOCKING;
		protocol_status.u32TicksProtocol = TICKS_GetTicks();
		if(esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio == OPERACIO_ESCRIPTURA)
		{
			protocol_framePregunta.field.ptu8Data = esclau_control[protocol_status.u8EsclauActual].ptu8Data;
			protocol_status.u8ProtocolMotor = PROT_STAT_ENVIANT_DADES;
		}
		else
		{
			protocol_status.u8ProtocolMotor = PROT_STAT_CALCULANT_CHEKSUM;
		}
		break;
	case PROT_STAT_ENVIANT_DADES:
		temp = BLOCKING;
		if(protocol_status.Transmit(RS485_MST, esclau_control[protocol_status.u8EsclauActual].ptu8Data, protocol_framePregunta.field.header.u8NumData, 0) == SUCCESS)
		{
			protocol_status.u8ProtocolMotor = PROT_STAT_CALCULANT_CHEKSUM;
		}
		else if(TICKS_DiffTicks(protocol_status.u32TicksProtocol) > 100)
		{
			protocol_status.u8CodiError = 7;
			protocol_status.u8ProtocolMotor = PROT_STAT_ERROR1;
		}
		break;
	case PROT_STAT_CALCULANT_CHEKSUM:
		temp = BLOCKING;
		PROTMST_CalculChecksum(&esclau_control[protocol_status.u8EsclauActual]);
		protocol_status.u32TicksProtocol = TICKS_GetTicks();
		protocol_status.u8ProtocolMotor = PROT_STAT_ENVIANT_CHEKSUM;
		break;
	case PROT_STAT_ENVIANT_CHEKSUM:
		temp = BLOCKING;
		if(protocol_status.Transmit(RS485_MST, (uint8_t *)(&protocol_framePregunta.field.u16FrameChecksum), 2, 1) == SUCCESS)
		{
			protocol_status.u32TicksProtocol = TICKS_GetTicks();
			//protocol_status.ResetBuffers();
			if(esclau_control[protocol_status.u8EsclauActual].ordre.fields.u8AddrEsclau != 0)
			{
				/* no es trama broadcast, espero recibir respuesta */
				protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_HEADER;
			}
			else
			{
				/* es trama broadcast, no espero recibir respuesta */
				/* solo tiene sentido si es una memoria que ejecute al momento porque no se puede hacer pooling */
				protocol_status.u8ProtocolMotor = PROT_STAT_REPETICIONS_BROADCAST;
			}
		}
		else if(TICKS_DiffTicks(protocol_status.u32TicksProtocol) > 5)
		{
			protocol_status.u8CodiError = 8;
			protocol_status.u8ProtocolMotor = PROT_STAT_ERROR1;
		}
		break;
	case PROT_STAT_ESPERANT_HEADER:
		temp = BLOCKING;
		if(protocol_status.Receive(RS485_MST, protocol_frameResposta.ptucBytes, sizeof(header_t)) == SUCCESS)
		{
			protocol_status.u32TicksProtocol = TICKS_GetTicks();
			if(protocol_frameResposta.field.header.u8NumData > 0)
			{
				if(esclau_control[protocol_status.u8EsclauActual].ptu8Data == NULL)
				{
					/* no hi ha buffer definit per les dades i m'indiquen que hi han dades */
					protocol_status.u8CodiError = 9;
					protocol_status.u8ProtocolMotor = PROT_STAT_ERROR1;
				}
				else
				{
					protocol_frameResposta.field.ptu8Data = ptu8DataRebuda;
					protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_DADES1;
					protocol_status.u8BytesRebuts = 0;
				}
			}
			else
			{
				protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_CHECKSUM;
			}
		}
		else if(TICKS_DiffTicks(protocol_status.u32TicksProtocol) > (esclau_control[protocol_status.u8EsclauActual].ordre.fields.u16TimeoutTrama+100))
		{
			protocol_status.u8CodiError = 1;
			protocol_status.u8ProtocolMotor = PROT_STAT_ERROR1;
		}
		break;
	case PROT_STAT_ESPERANT_DADES1:
		temp = BLOCKING;
		protocol_status.u32TicksProtocol = TICKS_GetTicks();
		if(protocol_status.u8BytesRebuts < protocol_frameResposta.field.header.u8NumData)
		{
			/* queden bytes per rebre */
			protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_DADES2;
		}
		else
		{
			protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_CHECKSUM;
		}
		break;
	case PROT_STAT_ESPERANT_DADES2:
		temp = BLOCKING;
		i = protocol_status.QuantsBytesBufferRX(RS485_MST);
		if((protocol_status.u8BytesRebuts+i) > protocol_frameResposta.field.header.u8NumData)
		{
			/* hi han mes bytes que les dades que em queden, nomes agafo les que falten */
			/* potser el checksum de la trama ja m'ha arribat, pero s'agafa en un altre estat */
			i = protocol_frameResposta.field.header.u8NumData - protocol_status.u8BytesRebuts;
		}
		if(i > 0)
		{
			protocol_status.Receive(RS485_MST, protocol_frameResposta.field.ptu8Data+protocol_status.u8BytesRebuts, i);
			protocol_status.u8BytesRebuts+=i;
			protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_DADES1;
		}
		else if(TICKS_DiffTicks(protocol_status.u32TicksProtocol) > 5)
		{
			protocol_status.u8CodiError = 2;
			protocol_status.u8ProtocolMotor = PROT_STAT_ERROR1;
		}
		break;
	case PROT_STAT_ESPERANT_CHECKSUM:
		temp = BLOCKING;
		if(protocol_status.Receive(RS485_MST, (uint8_t *)(&protocol_frameResposta.field.u16FrameChecksum), 2) == SUCCESS)
		{
			protocol_status.u8ProtocolMotor = PROT_STAT_VERIFICAR_HEADER;
		}
		else if(TICKS_DiffTicks(protocol_status.u32TicksProtocol) > 5)
		{
			protocol_status.u8CodiError = 3;
			protocol_status.u8ProtocolMotor = PROT_STAT_ERROR1;
		}
		break;
	case PROT_STAT_VERIFICAR_HEADER:
		if(PROTMST_CheckHeader(protocol_frameResposta.field.header) == SUCCESS)
		{
			protocol_status.u8ProtocolMotor = PROT_STAT_VERIFICAR_CHECKSUM;
		}
		else
		{
			protocol_status.u8CodiError = 4;
			protocol_status.u8ProtocolMotor = PROT_STAT_ERROR1;
		}
		break;
	case PROT_STAT_VERIFICAR_CHECKSUM:
		if(PROTMST_VerificaChecksum(&esclau_control[protocol_status.u8EsclauActual], protocol_frameResposta.field.u16FrameChecksum) == SUCCESS)
		{
			/* la resposta es bona, vaig a actualitzar l'estat de la placa i l'estat de les memories */
			esclau_control[protocol_status.u8EsclauActual].mems_status.status = protocol_frameResposta.field.header.memoria.status;
			esclau_control[protocol_status.u8EsclauActual].u8esclau_status = protocol_frameResposta.field.header.u8ProtocolVers;
			esclau_control[protocol_status.u8EsclauActual].u8esclau_comodin1 = protocol_frameResposta.field.header.u8ChecksumSlaveAddr;
			esclau_control[protocol_status.u8EsclauActual].u8esclau_comodin2 = protocol_frameResposta.field.header.u8ChecksumMemAddr;
			protocol_status.u32TicksProtocol = TICKS_GetTicks();
		//cr_sys	MemoryMap.var.puerto485_mst.u32TramasOK++;
			protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_SILENCI;
		}
		else
		{
			protocol_status.u8CodiError = 5;
			protocol_status.u8ProtocolMotor = PROT_STAT_ERROR1;
		}
		break;
	case PROT_STAT_ESPERANT_SILENCI:
		if(TICKS_DiffTicks(protocol_status.u32TicksProtocol) > PROTMST_TEMPS_SILENCI)
		{
//			HAL_GPIO_TogglePin(DBG_LED_3_GPIO_Port, DBG_LED_3_Pin);
			StatusMemoria = (protocol_frameResposta.field.header.memoria.status)>>(uint16_t)(((uint16_t)2*(uint16_t)protocol_frameResposta.field.header.tipooperacion.fields.u8acces_mem));
			StatusMemoria &= 0x03; 
			if(esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8ResetEnCurs == 1)
			{
				/* s'esta cancelant l'ordre actual */
				switch(StatusMemoria)
				{
				case PROT_MEM_STAT_IDLE:
					/* no pot retornar mai aquest valor, vaig a error */
					esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio = OPERACIO_IDLE;
					esclau_control[protocol_status.u8EsclauActual].ordre_status.value = 0;
					/* he perdut la trama de pooling que deia que la memoria ha acabat */
					esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8OrdreFinalitzada = 1;
					esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8ErrorComs = 1;
					protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_ORDRE;
					break;
				case PROT_MEM_STAT_RUNNING:
					/* el reset de l'ordre esta en curs, vaig a enviar el pooling */
					esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio = OPERACIO_POOLING;
					protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_ORDRE;
					break;
				case PROT_MEM_STAT_FINISHED:
				case PROT_MEM_STAT_ABORTED:
					/* tant si dona ordre abortada o acabada, informo com que ha acabat l'ordre de reset */
					esclau_control[protocol_status.u8EsclauActual].ordre_status.value = 0;
					esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8OrdreAbortadaPerMaster = 1;
					esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio = OPERACIO_IDLE;
					protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_ORDRE;
					break;
				}
			}
			else if(esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio == OPERACIO_RESET)
			{
				/* es vol cancelar l'ordre actual */
				switch(StatusMemoria)
				{
				case PROT_MEM_STAT_IDLE:
					/* no pot retornar mai aquest valor, vaig a error */
					esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio = OPERACIO_IDLE;
					esclau_control[protocol_status.u8EsclauActual].ordre_status.value = 0;
					/* he perdut la trama de pooling que deia que la memoria ha acabat */
					esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8OrdreFinalitzada = 1;
					esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8ErrorComs = 1;
					protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_ORDRE;
					break;
				case PROT_MEM_STAT_RUNNING:
					/* el reset de l'ordre esta en curs, vaig a enviar el pooling */
//					esclau_control[protocol_status.u8EsclauActual].ordre.tipus_operacio = OPERACIO_POOLING;
					protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_ORDRE;
					break;
				case PROT_MEM_STAT_FINISHED:
				case PROT_MEM_STAT_ABORTED:
					/* tant si dona ordre abortada o acabada, informo com que ha acabat l'ordre de reset */
					esclau_control[protocol_status.u8EsclauActual].ordre_status.value = 0;
					esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8OrdreAbortadaPerMaster = 1;
					esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio = OPERACIO_IDLE;
					protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_ORDRE;
					break;
				}
			}
			else if(esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8LecturaEnCurs == 1)
			{
				/* hi ha una operacio de lectura/escriptura en marxa, gestio del pooling */
				/* mirar si l'estat de la memoria es finalitzat. Si ho es, ha acabat l'ordre, sino s'ha d'encuar un pooling */
				switch(StatusMemoria)
				{
				case PROT_MEM_STAT_IDLE:
					/* no pot retornar mai aquest valor, vaig a error */
					esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio = OPERACIO_IDLE;
					esclau_control[protocol_status.u8EsclauActual].ordre_status.value = 0;
					/* he perdut la trama de pooling que deia que la memoria ha acabat */
					esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8OrdreFinalitzada = 1;
					esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8ErrorComs = 1;
					protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_ORDRE;
					break;
				case PROT_MEM_STAT_RUNNING:
					/* l'ordre necessita mes cicles per finalitzar, vaig a fer pooling */
					esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio = OPERACIO_POOLING;
					//esclau_control[protocol_status.u8EsclauActual].ordre_status.value = 0;
					protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_ORDRE;
					break;
				case PROT_MEM_STAT_FINISHED:
					/* l'ordre ha acabat, sense haver de fer pooling o despres de fer poolings */
					esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio = OPERACIO_IDLE;
					protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_ORDRE;
					esclau_control[protocol_status.u8EsclauActual].ordre_status.value = 0;
					esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8OrdreFinalitzada = 1;
					for(i = 0; i < protocol_frameResposta.field.header.u8NumData; i++)
					{
						esclau_control[protocol_status.u8EsclauActual].ptu8Data[i] = protocol_frameResposta.field.ptu8Data[i];
					}
					break;
				case PROT_MEM_STAT_ABORTED:
					/* l'esclau no em deixa fer l'ordre */
					esclau_control[protocol_status.u8EsclauActual].ordre_status.value = 0;
					esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8OrdreAbortadaPerEsclau = 1;
					esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio = OPERACIO_IDLE;
					protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_ORDRE;
					break;
				}
			}
			else
			{
				/* es ordre de pooling */
				switch(StatusMemoria)
				{
				case PROT_MEM_STAT_IDLE:
				case PROT_MEM_STAT_RUNNING:
				case PROT_MEM_STAT_FINISHED:
					/* l'ordre ha acabat */
					esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio = OPERACIO_IDLE;
					protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_ORDRE;
					esclau_control[protocol_status.u8EsclauActual].ordre_status.value = 0;
					esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8OrdreFinalitzada = 1;
					for(i = 0; i < protocol_frameResposta.field.header.u8NumData; i++)
					{
						esclau_control[protocol_status.u8EsclauActual].ptu8Data[i] = protocol_frameResposta.field.ptu8Data[i];
					}
					break;
				case PROT_MEM_STAT_ABORTED:
					/* l'esclau no em deixa fer l'ordre */
					esclau_control[protocol_status.u8EsclauActual].ordre_status.value = 0;
					esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8OrdreAbortadaPerEsclau = 1;
					esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio = OPERACIO_IDLE;
					protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_ORDRE;
					break;
				}
			}
			temp = SUCCESS;
			protocol_status.u8EsclauActual++;
			if(protocol_status.u8EsclauActual >= MAX_NUM_ESCLAUS) protocol_status.u8EsclauActual = 0;
		}
		break;
	case PROT_STAT_REPETICIONS_BROADCAST:
		if(TICKS_DiffTicks(protocol_status.u32TicksProtocol) > (esclau_control[protocol_status.u8EsclauActual].ordre.fields.u16TimeoutTrama))
		{
			esclau_control[protocol_status.u8EsclauActual].u16Reintents++;
			if(esclau_control[protocol_status.u8EsclauActual].u16Reintents >= esclau_control[protocol_status.u8EsclauActual].ordre.fields.u16MaxReintents)
			{
				/* ya he hecho los reenvios de la trama broadcast, doy por acabado */
				protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_SILENCI;
				protocol_status.u32TicksProtocol = TICKS_GetTicks();
				/* tengo que poner que ha terminado la orden */
				protocol_frameResposta.field.header.memoria.status = ((uint16_t)PROT_MEM_STAT_FINISHED)<<(uint16_t)(((uint16_t)2*(uint16_t)protocol_frameResposta.field.header.tipooperacion.fields.u8acces_mem));
			}
			else
			{
				protocol_status.u8ProtocolMotor = PROT_STAT_CALCULANT_HEADER;
			}
		}
		break;

	case PROT_STAT_ERROR1:
//cp		if(ATPARSER_AddFrameError(protocol_status.u8EsclauActual+1, protocol_status.u8CodiError+ATPARSER_MST_INIT_ERRORS) == SUCCESS_HTP)
		{
//			BUZZ_Configure(1, 80, PATRO_SO_RFID_KO);
			protocol_status.u32TicksProtocol = TICKS_GetTicks();
			protocol_status.u8ProtocolMotor = PROT_STAT_ERROR2;
//			HAL_GPIO_WritePin(DBG_LED_1_GPIO_Port, DBG_LED_1_Pin, GPIO_PIN_SET);
		}
		break;
	case PROT_STAT_ERROR2:
		if(protocol_status.QuantsBytesBufferRX(RS485_MST) != 0)
		{
			protocol_status.u32TicksProtocol = TICKS_GetTicks();
			protocol_status.ResetBuffers(RS485_MST);
		}
		else if(TICKS_DiffTicks(protocol_status.u32TicksProtocol) > 5)
		{
			protocol_status.u8ProtocolMotor = PROT_STAT_ERROR3;
		}
		break;
	case PROT_STAT_ERROR3:
		if(TICKS_DiffTicks(protocol_status.u32TicksProtocol) > PROTMST_TEMPS_REINTENT)
		{
//			HAL_GPIO_WritePin(DBG_LED_1_GPIO_Port, DBG_LED_1_Pin, GPIO_PIN_RESET);
			//cr_sysMemoryMap.var.puerto485_mst.u32TramasKO++;
			esclau_control[protocol_status.u8EsclauActual].u16Reintents++;
			if(esclau_control[protocol_status.u8EsclauActual].u16Reintents >= esclau_control[protocol_status.u8EsclauActual].ordre.fields.u16MaxReintents)
			{
				/* masa reintents, aborto l'ordre */
				protocol_status.u8ProtocolMotor = PROT_STAT_ESPERANT_ORDRE;
				esclau_control[protocol_status.u8EsclauActual].ordre_status.bit_field.u8ErrorComs = 1;
				esclau_control[protocol_status.u8EsclauActual].ordre.fields.tipus_operacio = OPERACIO_IDLE;
				protocol_status.u8EsclauActual++;
				if(protocol_status.u8EsclauActual >= MAX_NUM_ESCLAUS) protocol_status.u8EsclauActual = 0;
				temp = ERROR;
			}
			else
			{
				protocol_status.u8ProtocolMotor = PROT_STAT_CALCULANT_HEADER;
			}
		}
		break;
	}
	
	return temp;
}

returnstatus_t PROTMST_EncuaOrdre(uint8_t u8Posicio, nova_ordre_t nova_ordre, uint8_t *ptu8Dades)
{
	returnstatus_t temp;
	uint16_t i;
	
	if(nova_ordre.fields.tipus_operacio == OPERACIO_RESET && esclau_control[u8Posicio].ordre.fields.tipus_operacio != OPERACIO_IDLE)
	{
		/* es vol fer reset de l'operacio en curs, vaig a veure si es pot */
		if((protocol_status.u8EsclauActual != u8Posicio) ||
				((protocol_status.u8EsclauActual == u8Posicio) && ((protocol_status.u8ProtocolMotor > PROT_STAT_ENVIANT_CHEKSUM) || (protocol_status.u8ProtocolMotor < PROT_STAT_CALCULANT_HEADER))))
		{
			/* el reset no es per la tarjeta que es vol encuar el reset o la trama en curs ja s'ha construit 
			 * en el segon cas, primer s'enviara la trama que esta construida i el seguent cop la de reset, pero si aquesta trama
			 * finalitza el proces actual donara directament trama abortada */
			esclau_control[u8Posicio].ordre.fields.tipus_operacio = OPERACIO_RESET;
			temp = SUCCESS;
		}
		else
		{
			/* hi havia una trama en construccio
			 * per no enviar trames erronees, dono error d'encuar */
			temp = ERROR;
		}
	}
	else if(esclau_control[u8Posicio].ordre.fields.tipus_operacio != OPERACIO_IDLE)
	{
		temp = ERROR;
	}
	else
	{
		for(i = 0; i < sizeof(nova_ordre_t); i++)
		{
			esclau_control[u8Posicio].ordre.ptu8Bytes[i] = nova_ordre.ptu8Bytes[i]; 
		}
		esclau_control[u8Posicio].ptu8Data = ptu8Dades;

		temp = SUCCESS;
	}
	return temp;
}

ordre_status_t PROTMST_EstatOrdre(uint8_t u8Posicio, prot_mems_status_t *ptMemsStatus, uint8_t *ptu8EstatEsclau, uint8_t *ptu8EsclauComdin1, uint8_t *ptu8EsclauComdin2)
{
	ordre_status_t temp;
	temp.value = esclau_control[u8Posicio].ordre_status.value;
	
	if((temp.value&0xF0) != 0)
	{
		esclau_control[u8Posicio].ordre_status.value = 0;
		ptMemsStatus->status = esclau_control[u8Posicio].mems_status.status;
		*ptu8EstatEsclau = (esclau_control[u8Posicio].u8esclau_status | 0x01);
		*ptu8EsclauComdin1 = esclau_control[u8Posicio].u8esclau_comodin1;
		*ptu8EsclauComdin2 = esclau_control[u8Posicio].u8esclau_comodin2;
	}
	return temp;
}

void PROTMST_ChangeIDSlave(uint8_t u8Posicio, uint8_t u8NouID)
{
	esclau_control[u8Posicio].ordre.fields.u8AddrEsclau = u8NouID;
}

void PROTMST_ResetIDSlave(uint8_t u8Posicio)
{
	esclau_control[u8Posicio].ordre.fields.u8AddrEsclau = u8Posicio+1;
}

void PROTMST_GeneraHeader(esclau_control_t *esclau_actual)
{
	uint16_t i;
//	uint32_t *ptu32Addr;
	
	protocol_framePregunta.field.header.u8AddrSlave = esclau_actual->ordre.fields.u8AddrEsclau;
	protocol_framePregunta.field.header.tipooperacion.fields.u8Direccion = 0;
	protocol_framePregunta.field.header.tipooperacion.fields.u8acces_mem = esclau_actual->ordre.fields.u8Memoria;
	protocol_framePregunta.field.header.tipooperacion.fields.u8operation = (esclau_actual->ordre.fields.tipus_operacio>>7)&0x01;
	
	if((esclau_actual->ordre.fields.tipus_operacio&0x03) == OPERACIO_LECTURA)
	{
		protocol_framePregunta.field.header.u8NumData = esclau_actual->ordre.fields.u8NumBytes;
	}
	else
	{
		protocol_framePregunta.field.header.u8NumData = 0;
	}
	
//	ptu32Addr = (uint32_t *)protocol_framePregunta.field.header.ptu32addres;
//	*ptu32Addr = esclau_actual->ordre.fields.u32Addr;
//	ptu32Addr = (uint32_t *)(&esclau_actual->ordre.fields.u32Addr);
	protocol_framePregunta.field.header.ptu32addres[0] = (esclau_actual->ordre.fields.u32Addr)&0xFF;//ptu32Addr[0];
	protocol_framePregunta.field.header.ptu32addres[1] = (esclau_actual->ordre.fields.u32Addr>>8)&0xFF;//ptu32Addr[1];
	protocol_framePregunta.field.header.ptu32addres[2] = (esclau_actual->ordre.fields.u32Addr>>16)&0xFF;//ptu32Addr[2];
	protocol_framePregunta.field.header.ptu32addres[3] = (esclau_actual->ordre.fields.u32Addr>>24)&0xFF;//ptu32Addr[3];
	protocol_framePregunta.field.header.memoria.status = esclau_actual->ordre.fields.tipus_operacio&0x03;
	protocol_framePregunta.field.header.memoria.status = (protocol_framePregunta.field.header.memoria.status)<<(2*esclau_actual->ordre.fields.u8Memoria);
	
	protocol_framePregunta.field.header.u8ProtocolVers = PROTOCOL_VERSION;
	
	protocol_framePregunta.field.header.u8ChecksumSlaveAddr = protocol_framePregunta.field.header.u8AddrSlave + protocol_framePregunta.field.header.tipooperacion.value;
	protocol_framePregunta.field.header.u8ChecksumSlaveAddr ^= 0xFF;
	protocol_framePregunta.field.header.u8ChecksumSlaveAddr++;
	
	protocol_framePregunta.field.header.u8ChecksumMemAddr = 0;
	for(i = 0; i < 4; i++)
	{
		protocol_framePregunta.field.header.u8ChecksumMemAddr += protocol_framePregunta.field.header.ptu32addres[i];
	}
	protocol_framePregunta.field.header.u8ChecksumMemAddr ^= 0xFF;
	protocol_framePregunta.field.header.u8ChecksumMemAddr++;
	
	
}

returnstatus_t PROTMST_CheckHeader(header_t cab)
{
	uint16_t Aux;
	
	if(cab.tipooperacion.fields.u8Direccion != 1) return ERROR;
	
	Aux = ((uint16_t)0x0003)<<(2*(uint16_t)cab.tipooperacion.fields.u8acces_mem);
	if((cab.memoria.status&(~Aux)) != 0x0000)
	{
		/* el camp de validacio del 1er byte de la trama no es igual que la composicio dels bytes 7 i 8 de la trama */
		/* la trama es per accedir a un sol periferic */
		return ERROR;
	}
	
	return SUCCESS; 
}

void PROTMST_CalculChecksum(esclau_control_t *esclau_actual)
{
	uint16_t i, temp;
	
	temp = 0;
	for(i = 0; i < sizeof(header_t); i++)
	{
		temp += protocol_framePregunta.ptucBytes[i];
	}
	if(esclau_actual->ordre.fields.tipus_operacio == OPERACIO_ESCRIPTURA)
	{
		for(i = 0; i < esclau_actual->ordre.fields.u8NumBytes; i++)
		{
			temp += esclau_actual->ptu8Data[i];
		}
	}

	protocol_framePregunta.field.u16FrameChecksum = temp^0xFFFF;
	protocol_framePregunta.field.u16FrameChecksum++;
}

returnstatus_t PROTMST_VerificaChecksum(esclau_control_t *esclau_actual, uint16_t u16Inicial)
{
	uint16_t i, temp;
	returnstatus_t retorn;
		
	temp = u16Inicial;
	for(i = 0; i < sizeof(header_t); i++)
	{
		temp += protocol_frameResposta.ptucBytes[i];
	}
	
	for(i = 0; i < protocol_frameResposta.field.header.u8NumData; i++)
	{
		temp += protocol_frameResposta.field.ptu8Data[i];
	}
	
	if(temp == 0)
	{
		retorn = SUCCESS;
	}
	else
	{
		retorn = ERROR;
	}
	return retorn;
}



