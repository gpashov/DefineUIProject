/*
 * ProtocolMaster.h
 *
 *  Created on: Nov 15, 2016
 *      Author: ingenieria1
 */

#ifndef PROTOCOLMASTER_H_
#define PROTOCOLMASTER_H_

#include "PE_Types.h"
#include "GeneralDefines.h"


#define PROTOCOL_VERSION        0x01

#define MAX_NUM_ESCLAUS		5//MAX_PCB_FUENTES+MAX_PCB_COMPLEMENTOS
#define BROADCAST_ID		0


typedef enum
{
    PROT_STAT_ESPERANT_ORDRE,
    PROT_STAT_CALCULANT_HEADER,		/*****************************************************************************************/
    PROT_STAT_ENVIANT_HEADER,		/* no possar estats entremig de PROT_STAT_CALCULANT_HEADER i PROT_STAT_ENVIANT_CHEKSUM   */
    PROT_STAT_CALCULANT_DADES,		/* per poder gestionar l'enviament de l'ordre de reset es necessari que no estigui entre */
    PROT_STAT_ENVIANT_DADES,		/* aquests 2 estats per a que l'ordre estigui ben construida                             */
    PROT_STAT_CALCULANT_CHEKSUM,	/*                                                                                       */
    PROT_STAT_ENVIANT_CHEKSUM,		/*****************************************************************************************/
    PROT_STAT_ESPERANT_HEADER,
    PROT_STAT_ESPERANT_DADES1,
    PROT_STAT_ESPERANT_DADES2,
    PROT_STAT_ESPERANT_CHECKSUM,
    PROT_STAT_VERIFICAR_HEADER,
    PROT_STAT_VERIFICAR_CHECKSUM,
    PROT_STAT_ESPERANT_SILENCI,
	PROT_STAT_REPETICIONS_BROADCAST,
            
    PROT_STAT_ERROR1,
    PROT_STAT_ERROR2,
    PROT_STAT_ERROR3
}prot_estats_t;

typedef union
{
    uint16_t status;
    struct
    {
        uint16_t UsedInternalRAM    : 2;
        uint16_t InternalRAM        : 2;
        uint16_t InternalFLASH      : 2;
        uint16_t InternalE2PROM     : 2;
        uint16_t ExternalMem1       : 2;
        uint16_t ExternalMem2       : 2;
        uint16_t ExternalMem3       : 2;
        uint16_t ExternalMem4       : 2;
    }mem;
}prot_mems_status_t;

typedef enum
{
    PROT_ORDER_IDLE,
    PROT_ORDER_ORDER,
    PROT_ORDER_POOLING,
    PROT_ORDER_RESET_ORDER
}prot_order_t;

typedef enum
{
    PROT_MEM_STAT_IDLE,
    PROT_MEM_STAT_RUNNING,
    PROT_MEM_STAT_FINISHED,
    PROT_MEM_STAT_ABORTED
}prot_mem_status_t;

typedef union
{
    uint8_t value;
    struct
    {
        uint8_t u8MemNoDefinida             :1;
        uint8_t u8NovaOrdreAmbOrdreActiva   :1;
        uint8_t u8OrdreResetAmbMemRepos     :1;
        uint8_t u8Unused                    :5;
    }bit_field;
}prot_error_t;

typedef enum
{
	OPERACIO_IDLE = 0,
	OPERACIO_POOLING = 2,
	OPERACIO_RESET = 3,
	OPERACIO_ESCRIPTURA = 0x81,
	OPERACIO_LECTURA = 1
	
}tipus_operacio_t;

typedef enum
{
	PROMST_ORDRE_ABORTADA_MASTER 	= 0x10,
	PROMST_ORDRE_ABORTADA_ESCLAU 	= 0x20,
	PROMST_ORDRE_FINALITZADA_OK 	= 0x40,
	PROMST_ORDRE_ERROR_COMS		 	= 0x80,
}ordre_status_valor_t;

typedef union
{
	uint8_t value;
	struct
	{
		uint8_t u8OrdreEnCurs				: 1;
		uint8_t u8LecturaEnCurs			: 1;
		uint8_t u8PoolingEnCurs			: 1;
		uint8_t u8ResetEnCurs				: 1;
		uint8_t u8OrdreAbortadaPerMaster	: 1;
		uint8_t u8OrdreAbortadaPerEsclau	: 1;
		uint8_t u8OrdreFinalitzada		: 1;
		uint8_t u8ErrorComs				: 1;
	}bit_field;
}ordre_status_t;

typedef struct
{
	nova_ordre_t ordre;
	uint8_t u8BytesRebuts;
	uint8_t u8esclau_status;
	uint8_t u8esclau_comodin1;
	uint8_t u8esclau_comodin2;
	prot_mems_status_t mems_status;
	uint16_t u16Reintents;
	ordre_status_t ordre_status;
	uint32_t u32Timer;
	uint8_t *ptu8Data;
}esclau_control_t;

typedef union
{
    uint8_t value;
    struct
    {
        uint8_t u8RFU		  : 3;
        uint8_t u8Direccion   : 1;	/* 0, dirección master a esclavo; 1, esclavo a master */
        uint8_t u8acces_mem   : 3;
        uint8_t u8operation   : 1;
    }fields;
}tipo_op_field_t;

typedef struct
{
    uint8_t u8AddrSlave;
    tipo_op_field_t tipooperacion;
    uint8_t u8ProtocolVers;
    uint8_t u8NumData;
    uint8_t ptu32addres[4];
    prot_mems_status_t memoria;
    uint8_t u8ChecksumSlaveAddr;
    uint8_t u8ChecksumMemAddr;
}header_t;

typedef union
{
    struct
    {
        header_t header;
        uint8_t *ptu8Data;
        uint16_t u16FrameChecksum;
    }field;
    uint8_t ptucBytes[64/*sizeof(header_t)+6*/];
}protocol_frame_t;

typedef struct
{
    uint8_t u8Enable;
    // Variables d'estat
    uint8_t u8BytesRebuts;
    uint8_t u8EsclauActual;
		uint8_t u8CodiError;
    prot_estats_t u8ProtocolMotor;
    // Variable pel timer
    uint32_t u32TicksProtocol;
	        
    returnstatus_t (*Receive)(uint8_t u8Channel, uint8_t* ptu8Dades, uint16_t u16NumDades);
    
    uint32_t (*QuantsBytesBufferRX)(uint8_t u8Channel);
    void (*ResetBuffers)(uint8_t u8Channel);

    returnstatus_t (*Transmit)(uint8_t u8Channel, uint8_t* ptu8Dades, uint16_t u16NumDades, uint8_t u8LastPacket);

}protocol_status_t;

void PROTMST_Init(void);

returnstatus_t PROTMST_Motor(void);

//cris: u8Posicio = numEsclau-1 (es index de array)
returnstatus_t PROTMST_EncuaOrdre(uint8_t u8Posicio, nova_ordre_t nova_ordre, uint8_t *ptu8Dades);

//cris: u8Posicio = numEsclau-1 (es index de array)
ordre_status_t PROTMST_EstatOrdre(uint8_t u8Posicio, prot_mems_status_t *ptMemsStatus, uint8_t *ptu8EstatEsclau, uint8_t *ptu8EsclauComdin1, uint8_t *ptu8EsclauComdin2);

void PROTMST_ChangeIDSlave(uint8_t u8Posicio, uint8_t u8NouID);

void PROTMST_ResetIDSlave(uint8_t u8Posicio);

#endif /* PROTOCOLMASTER_H_ */
