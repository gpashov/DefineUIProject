/*
 * Expansora.c
 *
 *  Created on: Mar 7, 2019
 *      Author: dbelmonte
 */

#include "Expansora.h"
#include "../ProtocolMaster/ProtocolMaster.h"
//#include "../Ticks/Ticks.h"
//#include "../Error/gestionError.h"
//#include "../App.h"
//#include "../BOOT/boot.h"
#include "../AppLOG/AppLOG.h"
//#include "../Test/test.h"
#include "../GPRS/AppGPRS.h"

#define EXP_ERR_ALARM_MAX_RAD_FAN_CONS		5.0
#define EXP_ERR_ALARM_MAX_WATER_PUMP_CONS	5.0
#define EXP_ERR_ALARM_MAX_RETURN_FLOW		5.0
#define EXP_ERR_ALARM_RETURN_TEMP_LOW		-1.0
#define EXP_ERR_ALARM_RETURN_TEMP_HIGH		50.0
#define EXP_ERR_ALARM_TEMP_PUMP_OUT_LOW		5.0
#define EXP_ERR_ALARM_TEMP_PUMP_OUT_HIGH	45.0
#define EXP_ERR_WARN_TEMP_ENV				30.0
#define EXP_ERR_WARN_FLAG_DOWN_TEMP_ENV		28.0
#define EXP_ERR_ALARM_TEMP_ENV_LOW			5.0
#define EXP_ERR_ALARM_TEMP_ENV_HIGH			35.0
#define EXP_ERR_ALARM_MAX_24V_TOTAL_CONS	5.0

#define	EXP_PROTMST_ADDR_SLAVE 			4
#define EXP_PROTMST_FRAME_TIMEOUT 		333
#define EXP_PROTMST_MAX_RETRYS 			3
#define	EXP_PROTMST_SLOT_POS 			0
#define	EXP_PROTMST_BLOCKING_TIMEOUT 	( ( EXP_PROTMST_FRAME_TIMEOUT * EXP_PROTMST_MAX_RETRYS) + 500)
#define	EXP_PROTMST_GPERIF_MEM_ID 		4
#define	EXP_PROTMST_DATA_MEM_ID 		0
#define EXP_PROTMST_OTHER_PCB_MEM_ID	5
#define EXP_PROTMST_MAX_BYTES 			64
#define EXP_PROTMST_WDOG_ENABLE_VALUE	1	//ACTIVAR WATCHDOG!!! PDTE
#define EXP_PROTMST_WDOG_ENABLE_DIR		42

#define EXP_REMAP_BUFF_DIR_INI 1264
#define EXP_PUENTE_PROTOCOLO_DIR_INIT	0x00000000
#define EXP_PERIFERICOS_HABILITADOS		0x00000000

//const uint8 EXP_GPERIF_GENERAL_DATA_SIZE = 52;
#define EXP_GPERIF_GENERAL_DATA_DIR_INI 4
#define EXP_GPERIF_INIT_PERIFS_DIR_INI 2
#define EXP_GPERIF_INIT_PERIFS_SIZE 2
#define EXP_GPERIF_ENABLED_PERIFS_DIR_INI 0
#define EXP_GPERIF_ENABLED_PERIFS_SIZE 2
#define EXP_GPERIF_STATUS_PERIFS_DIR_INI ( EXP_GPERIF_ENABLED_PERIFS_DIR_INI)
#define EXP_GPERIF_STATUS_PERIFS_SIZE ( EXP_GPERIF_ENABLED_PERIFS_SIZE + EXP_GPERIF_INIT_PERIFS_SIZE)

#define EXP_REMAP_STRUCTS_DIR_INI 368 
//const uint8 EXP_REMAP_STRUCTS_SIZE = 8;
#define EXP_REMAP_STRUCTS_MAX_DATA_FRAME_STRUCTS 8
#define EXP_REMAP_STRUCTS_FRAME_DIR_VECTOR_SIZE ( EXP_REMAP_STRUCTS_SIZE * EXP_REMAP_STRUCTS_MAX_DATA_FRAME_STRUCTS)
#define EXP_REMAP_STRUCTS_FULL_PERIF_SIZE ( EXP_REMAP_STRUCTS_FRAME_DIR_VECTOR_SIZE * 2)

#define EXP_DATA_HEADER_DIR_INI 0
//const uint8 EXP_DATA_HEADER_SIZE = 64;
#define EXP_UC_COMMON_VARS1_DIR_INI 64
//const uint8 EXP_UC_COMMON_VARS1_SIZE = 28;
#define EXP_UC_COMMON_VARS2_DIR_INI 284
//EXP_UC_COMMON_VARS2_SIZE 60
#define EXP_UC_HANDPIECE_SENSORS_DIR_INI 92
//EXP_UC_HANDPIECE_SENSORS_SIZE 12
#define EXP_UC_HANDPIECE_VARS_DIR_INI 140
//EXP_UC_HANDPIECE_VARS_SIZE 36
#define EXP_UC_PCB_LVL_DETECTOR_HDR_DIR_INI 1276
//EXP_UC_PCB_HEADER_SIZE
#define EXP_UC_LVL_DETECTOR_VARS_DIR_INI 1340
//EXP_UC_LVL_DETECTOR_VARS_SIZE
#define EXP_UC_PCB_PWR_SUPPLY_DIR_INI 36
//#define EXP_UC_PCB_PWR_SUPPLY_VARS_SIZE 36
#define EXP_UC_PCB_COMPLEMENT_DIR_INI 236
//#define EXP_UC_PCB_COMPLEMENT_VARS_SIZE 40
#define EXP_UC_RAD_FAN_VOLTAGE_DIR_INI 1368

#define EXP_UC_PROTOCOL_BRIDGE_DIR_INI		0
#define EXP_UC_PROTOCOL_BRIDGE_VARS_SIZE	12

#define EXP_UC_COMMON_VARS2_RETRY_FACTOR_OFFSET 16
#define EXP_UC_COMMON_VARS2_LUNG_FACTOR_OFFSET 32

/*** TIPOS DE DATOS ***/
typedef union
{
	struct
	{
		uint8 slaveAddr;
		uint8 opType;
		uint8 memID;
		uint8 nBytes;
		uint16 frameTout;
		uint16 frameMaxRetrys;
		uint32 dataAddr;
	}fields;
	uint8 vector[EXP_UC_PROTOCOL_BRIDGE_VARS_SIZE];
}tEXPprotocolBridge;

typedef enum
{
	EXP_PROTMST_COM_OP_READ = OPERACIO_LECTURA,
	EXP_PROTMST_COM_OP_WRITE = OPERACIO_ESCRIPTURA
}cEXPcomOp;

/*** VARIABLES GLOBALES ***/
tEXPdata EXPdata;

tEXP_UCreuseLabelData EXP_UCreuseLabelData[EXP_UC_NUM_HANDPIECES];

/*** DECLARACION DE FUNCIONES LOCALES ***/
returnstatus_t EXPcomOrder( cEXPcomOp operation, uint8 memID, uint32 addr, uint8 nBytes, uint8 *buffer);
returnstatus_t EXPgetData( uint8 memID, uint32 addr, uint8 nBytes, uint8 *buffer);
returnstatus_t EXPupdatePerifs( void);
returnstatus_t EXP_UCupdateHP( void);
returnstatus_t EXP_UCerror( void);
void EXP_UCerror485complBusPerif( uint8 perif, uint8 H2Oshift, uint8 vacShift, 
							   uint16 H2OerrCode, uint16 vacErrCode);
void EXPrefreshCPI( void);

void EXP_UC_MCCmanage (void);

/*** FUNCIONES ***/
/* FUNIONES PUBLICAS */
void EXPinit( void)
{
//	uint8 cnt0, cnt1;
	
//	/* Inicializamos la estructura de datos */
//	/* - DataToGet */
//	EXPdata.dataToGet.byte = 0;
//	EXPdata.dataToGet.bits.header = 1;
//	EXPdata.dataToGet.bits.perifs = 1;
//	EXPdata.dataToGet.bits.common1 = 1;
//	EXPdata.dataToGet.bits.common2 = 1;
//	EXPdata.dataToGet.bits.HP = 1;
//	EXPdata.dataToGet.bits.cfg = 1;
//	EXPdata.dataToGet.bits.err = 1;
//	EXPdata.dataToGet.bits.PCBs = 1;
	
	
//	/* - Perifericos */
//	for( cnt0 = 0; cnt0 < EXP_MAX_PERIF; cnt0++)
//	{
//		EXPdata.newPerif[cnt0] = 0;
//		EXPdata.perif[cnt0].isInit = 0;
//		EXPdata.perif[cnt0].isEnabled = 0;
//		EXPdata.perif[cnt0].isSPIok = 1;
//		for( cnt1 = 0; cnt1 < EXP_GPERIF_GENERAL_DATA_SIZE; cnt1++){ EXPdata.perif[cnt0].data.vector[cnt1] = 0;}
//	}
	
//	/* - Header */
//	for( cnt0 = 0; cnt0 < EXP_DATA_HEADER_SIZE; cnt0++){ EXPdata.header.vector[cnt0] = 0;}
	
//	/* - UC commonData1 */
//	for( cnt0 = 0; cnt0 < EXP_UC_COMMON_VARS1_SIZE; cnt0++){ EXPdata.UC.commonData1.vector[cnt0] = 0;}
	
//	/* - UC commonData2 */
//	for( cnt0 = 0; cnt0 < EXP_UC_COMMON_VARS2_SIZE; cnt0++){ EXPdata.UC.commonData2.vector[cnt0] = 0;}
	
//	/* - UC handPiece */
//	for( cnt0 = 0; cnt0 < EXP_UC_NUM_HANDPIECES; cnt0++)
//	{
//		/* Sensores de handpiece */
//		for( cnt1 = 0; cnt1 < EXP_UC_HANDPIECE_SENSORS_SIZE; cnt1++)
//		{ EXPdata.UC.handPieceData[cnt0].sensors.vector[cnt1] = 0;}
		
//		/* Variables de handpiece */
//		for( cnt1 = 0; cnt1 < EXP_UC_HANDPIECE_VARS_SIZE; cnt1++)
//		{ EXPdata.UC.handPieceData[cnt0].vars.vector[cnt1] = 0;}
//	}
	
//	/* - PCB detector de nivel */
//	for( cnt0 = 0; cnt0 < EXP_UC_PCB_HEADER_SIZE; cnt0++){ EXPdata.UC.PCBlvlDetector.hdr.vector[cnt0] = 0;}
//	for( cnt0 = 0; cnt0 < EXP_UC_LVL_DETECTOR_VARS_SIZE; cnt0++){ EXPdata.UC.PCBlvlDetector.vars.vector[cnt0] = 0;}
//	//Faltan las debug memoria 5. Los complementos. PDTE
	
//	EXPdata.UC.commonData2.fields.temporaryEnabledPerif = 0x1F;
	
////	while(BOOT_ConfigGetSerialFlash(TEMP_OSC_PROCESS_ENABLE_MEMORY_ADDRESS, 1, &EXPdata.UC.ModeTempOscIDLE)!=BOOT_SerialFlash_LecturaCorrecta);
////	if((EXPdata.UC.ModeTempOscIDLE!=0)&&(EXPdata.UC.ModeTempOscIDLE!=1)){	EXPdata.UC.ModeTempOscIDLE = 0;	}
////	while(BOOT_ConfigGetSerialFlash(RESUCTION_VIEWER_ENABLE_MEMORY_ADDRESS, 1, &EXPdata.UC.ModeResuctionsViewer)!=BOOT_SerialFlash_LecturaCorrecta);
////	if((EXPdata.UC.ModeResuctionsViewer!=0)&&(EXPdata.UC.ModeResuctionsViewer!=1)){	EXPdata.UC.ModeResuctionsViewer = 0;	}
//	while(BOOT_LoadConfigParamSerialFlash (EXPdata.UC.Config_Param.vector) != BOOT_SerialFlash_LecturaCorrecta);
}

#ifdef DEBUG_STANDALONE
uint8 EXPupdate( uint32 loopTime) {
	
	return(1);
}

#else 
uint8 EXPupdate( uint32 loopTime)
{
	returnstatus_t ret, retAux;
	uint8 buffer[1];
	uint8 errRfrshVars;
	static uint32 time = 0;
	uint8 loopDone = 0;
	uint8 cnt;
	uint32 address;
	
//	/* Comprobamos so ha pasado el tiempo suficiente */
//	if( TICKS_DiffTicks( time) > loopTime)
//	{
//		/* Ha pasado el tiempo suficiente para hacer el loop, reseteamos el contador de tiempo e indicamos
//		 * que ejecutamos loop */
//		time = TICKS_GetTicks();
//		loopDone = 1;
		
//		/* Indicamos que no ha habido error de refresco de variables */
//		errRfrshVars = 0;
		
//		/* Refrescamos todas las variables necesarias de la expansora y las procesamos segun convenga */
//		/* - Enviar configuración */
//		if( EXPdata.dataToGet.bits.cfg)
//		{
//			/* Watch Dog */
//			buffer[0] = EXP_PROTMST_WDOG_ENABLE_VALUE;
//			ret = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_DATA_MEM_ID,
//							   EXP_PROTMST_WDOG_ENABLE_DIR, 1, buffer);
			
//			/* Como no cambia reseteamos el flag para no estar escribiendolo continuamente */
//			if( ret == SUCCESS){ EXPdata.dataToGet.bits.cfg = 0;}
			
//			/* Si hay error indicamos que no se han refrescado las variables para no mirar la
//			 * gestión de errores */
//			if( ret == ERROR) { errRfrshVars = 1;}
//		}
		
//		/* - Headers */
//		if( EXPdata.dataToGet.bits.header)
//		{
//			/* Inicializamos la variable de retorno */
//			ret = SUCCESS;
			
//			/* Obtenemos el header de la PCB expansora*/
//			retAux = EXPgetData( EXP_PROTMST_DATA_MEM_ID, EXP_DATA_HEADER_DIR_INI,
//							  	 EXP_DATA_HEADER_SIZE, EXPdata.header.vector);
//			if( retAux == ERROR) { ret = ERROR;}
						
//			/* Obtenemos el header de la PCB detector de nivel */
//			retAux = EXPgetData( EXP_PROTMST_OTHER_PCB_MEM_ID, EXP_UC_PCB_LVL_DETECTOR_HDR_DIR_INI,
//							  	 EXP_UC_PCB_HEADER_SIZE, EXPdata.UC.PCBlvlDetector.hdr.vector);
//			if( retAux == ERROR) { ret = ERROR;}
						
//			/* Obtenemos los header de las PCB's de fuentes */
//			for( cnt = 0; cnt < EXP_UC_NUM_PCB_PWR_SUPPLY; cnt++)
//			{
//				address = EXP_UC_PCB_PWR_SUPPLY_DIR_INI + ( EXP_UC_PCB_HEADER_SIZE + EXP_UC_PCB_PWR_SUPPLY_VARS_SIZE) * cnt;
//				retAux = EXPgetData( EXP_PROTMST_OTHER_PCB_MEM_ID, address,
//									 EXP_UC_PCB_HEADER_SIZE, EXPdata.UC.PCBpwrSupply[cnt].hdr.vector);
//				if( retAux == ERROR) { ret = ERROR;}
//			}
			
//			/* Obtenemos los headers de las PCB's de complementos */
//			for( cnt = 0; cnt < EXP_UC_NUM_PCB_COMPLEMENT; cnt++)
//			{
//				address = EXP_UC_PCB_COMPLEMENT_DIR_INI + ( EXP_UC_PCB_HEADER_SIZE + EXP_UC_PCB_COMPLEMENT_VARS_SIZE) * cnt;
//				retAux = EXPgetData( EXP_PROTMST_OTHER_PCB_MEM_ID, address,
//									 EXP_UC_PCB_HEADER_SIZE, EXPdata.UC.PCBcomplement[cnt].hdr.vector);
//				if( retAux == ERROR) { ret = ERROR;}
//			}
			
//			/* Como el header no cambia reseteamos el flag para no estar pidiendolo continuamente */
//			if( ret == SUCCESS){ EXPdata.dataToGet.bits.header = 0;}
			
//			/* Si hay error indicamos que no se han refrescado las variables para no mirar la
//			 * gestión de errores */
//			if( ret == ERROR) { errRfrshVars = 1;}
//		}
		
//		/* - Perifericos */
//		if( EXPdata.dataToGet.bits.perifs)
//		{
//			ret = EXPupdatePerifs();
			
//			/* Si hay error indicamos que no se han refrescado las variables para no mirar la
//			 * gestión de errores */
//			if( ret == ERROR) { errRfrshVars = 1;}
//		}
		
//		/* - Common data 1 */
//		if( EXPdata.dataToGet.bits.common1)
//		{
//			ret = EXPgetData( EXP_PROTMST_DATA_MEM_ID, EXP_UC_COMMON_VARS1_DIR_INI,
//							  EXP_UC_COMMON_VARS1_SIZE, EXPdata.UC.commonData1.vector);
//			//PDTE - pasar a subrutina y gestionar bien la obtencion de datos. No tan hardcoded
//			ret = EXPgetData( EXP_PROTMST_OTHER_PCB_MEM_ID, EXP_UC_RAD_FAN_VOLTAGE_DIR_INI,
//							  4, ( uint8 *)( &( EXPdata.UC.radFanVoltage)));
//			EXPdata.UC.radFanVoltage = EXPdata.UC.radFanVoltage / 10.0;
//			EXPrefreshCPI();
			
//			/* Si hay error indicamos que no se han refrescado las variables para no mirar la
//			 * gestión de errores */
//			if( ret == ERROR) { errRfrshVars = 1;}
//		}
		
//		/* - Common data 2 */
//		if( EXPdata.dataToGet.bits.common2)
//		{
//			ret = EXPgetData( EXP_PROTMST_DATA_MEM_ID, EXP_UC_COMMON_VARS2_DIR_INI,
//							  EXP_UC_COMMON_VARS2_SIZE, EXPdata.UC.commonData2.vector);
			
//			/* Si hay error indicamos que no se han refrescado las variables para no mirar la
//			 * gestión de errores */
//			if( ret == ERROR) { errRfrshVars = 1;}
//		}
							  
//		/* - HandPiece data */
//		if( EXPdata.dataToGet.bits.HP)
//		{
//			ret = EXP_UCupdateHP();
			
//			/* Si hay error indicamos que no se han refrescado las variables para no mirar la
//			 * gestión de errores */
//			if( ret == ERROR) { errRfrshVars = 1;}
//		}
		
//		/* - PCB's data */
//		if( EXPdata.dataToGet.bits.PCBs)
//		{
//			/* Inicializamos la variable de retorno */
//			ret = SUCCESS;
			
//			/* Leemos las variables de la PCB detectora de nivel de agua */
//			retAux = EXPgetData( EXP_PROTMST_OTHER_PCB_MEM_ID, EXP_UC_LVL_DETECTOR_VARS_DIR_INI,
//							     EXP_UC_LVL_DETECTOR_VARS_SIZE, EXPdata.UC.PCBlvlDetector.vars.vector);
//			if( retAux == ERROR) { ret = ERROR;}
			
//			/* Leemos las variables de las PCB's de fuentes */
			
//			/* Leemos las variables de las PCB's de complementos */
			
//			/* Si hay error indicamos que no se han refrescado las variables para no mirar la
//			 * gestión de errores */
//			if( ret == ERROR) { errRfrshVars = 1;}
//		}
				
//		/* - Generación de errores */
//		if( EXPdata.dataToGet.bits.err && !errRfrshVars)
//		{
//			ret = EXP_UCerror();
//		}
		
//		if( EXPdata.UC.FatigaStartStop)
//		{
//			EXP_UCfatiga();
//		}
		
//		/* Gestion de otras acciones que requieren motor PDTE */
//		/* - Llenado / vaciado */
//		/* - ON/OFF Hidraulica */
//		/* - ... */
	
//		/*V7790 - GPRS get MCC*/
//		EXP_UC_MCCmanage();
//	}
	
	/* Devolvemos si se ha ejecutado el loop o no */
	return loopDone;
}
#endif


uint8 EXP_UCgetStdBy( void)
{
	return EXPdata.header.fields.board_status.bit_field.exp_st.stdby;
}

returnstatus_t EXP_UCexitStandby (void)
{
	uint8 buffer[12];
	returnstatus_t retorno;
	
	buffer[0] = 0x01;
	buffer[1] = 0x81;
	buffer[2] = 0x00;
	buffer[3] = 0x01;
	buffer[4] = 0x64;
	buffer[5] = 0x00;
	buffer[6] = 0x03;
	buffer[7] = 0x00;
	buffer[8] = 0x40;
	buffer[9] = 0x00;
	buffer[10] = 0x00;
	buffer[11] = 0x00;
	
	retorno = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_OTHER_PCB_MEM_ID, 
					EXP_PUENTE_PROTOCOLO_DIR_INIT, 12, buffer);
	
	buffer[0] = 0x02;
	
	retorno = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_OTHER_PCB_MEM_ID, 
				EXP_PUENTE_PROTOCOLO_DIR_INIT+20, 1, buffer);
	
	buffer[0] = 0x03;
	buffer[1] = 0x00;
		
	retorno = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_DATA_MEM_ID, 
				44, 2, buffer);
	
	retorno = RUNNING;
	while((retorno != SUCCESS) && (retorno != ERROR))
	{
		EXPcomOrder( EXP_PROTMST_COM_OP_READ, EXP_PROTMST_OTHER_PCB_MEM_ID,
				19, 1, (uint8 *)(&retorno));
	}
	
	//if(retorno == SUCCESS){	EXPdata.header.fields.board_status.bit_field.exp_st.stdby = 1;	}
	
	return retorno;
}

uint8 EXPfoundNewPerif( uint8 *indexNewPerif)
{
	uint8 cnt;
	
	/* Comprobamos si hay algún periferico nuevo detectado que aun no se haya
	 * comunicado */
	cnt = 0;
	while( cnt < EXP_MAX_PERIF && EXPdata.newPerif[cnt] == 0){ cnt++;}
	if( cnt < EXP_MAX_PERIF)
	{
		/* Hemos encontrado un periferico nuevo, lo comunicamos y reseteamos */
		EXPdata.newPerif[cnt] = 0;
		( *indexNewPerif) = cnt;
		return 1;
	}
	
	/* Si llegamos aqui es que no hemos encontrado periferico nuevo */
	return 0;
}

returnstatus_t EXPsendRemap( tEXPremap *remap, uint8 IDperifHW, uint8 slot, cEXPremapFramDir frameDir)
{
	returnstatus_t ret;
	uint32 addr;
	
	/* Calculamos la dirección donde se tiene que ubicar la estructura de remap */
	addr = EXP_REMAP_STRUCTS_DIR_INI + 
		   EXP_REMAP_STRUCTS_FULL_PERIF_SIZE * IDperifHW +
		   EXP_REMAP_STRUCTS_FRAME_DIR_VECTOR_SIZE * frameDir + EXP_REMAP_STRUCTS_SIZE * slot;
		
	/* Enviamos la estructura de remapeo */
	ret = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_GPERIF_MEM_ID, 
				       addr, EXP_REMAP_STRUCTS_SIZE, remap->vector);
		
	/* Devolvemos el resultado */
	return ret;
}

returnstatus_t EXPremapFrameGetData( uint32 dirRelToBuff, uint8 nBytes, uint8 *buffer)
{
	returnstatus_t ret;
	
	/* Obtenemos los datos de la expansora. Devolvemos el resultado de la orden */
	ret = EXPcomOrder( EXP_PROTMST_COM_OP_READ, EXP_PROTMST_GPERIF_MEM_ID, 
			           dirRelToBuff + EXP_REMAP_BUFF_DIR_INI, nBytes, buffer);
	
	/* Devolvemos el resultado */
	return ret;
}

returnstatus_t EXPremapFrameSetData( uint32 dirRelToBuff, uint8 nBytes, uint8 *buffer)
{
	returnstatus_t ret;
	
	/* Obtenemos los datos de la expansora. Devolvemos el resultado de la orden */
	ret = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_GPERIF_MEM_ID, 
			           dirRelToBuff + EXP_REMAP_BUFF_DIR_INI, nBytes, buffer);
	
	/* Devolvemos el resultado */
	return ret;
}

returnstatus_t EXPenableDisablePerif( uint8 indexPerif, uint8 enableDisable)
{
	uint8 i;
	uint16 enabledPerifs;
	returnstatus_t ret;

	/* Modificamos el estado del periferico indicado */
	EXPdata.perif[indexPerif].isEnabled = !(enableDisable == 0);
	
	/* Construimos el word con los perifericos habilitados */
	enabledPerifs = 0;
	for( i = 0; i < EXP_MAX_PERIF; i++)
	{
		enabledPerifs = enabledPerifs | ( ( ( uint16)EXPdata.perif[i].isEnabled) << i);
	}
	
	/* Enviamos el word con los perifericos habilitados */
	ret = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_GPERIF_MEM_ID, EXP_GPERIF_ENABLED_PERIFS_DIR_INI, 
				       EXP_GPERIF_ENABLED_PERIFS_SIZE, ( uint8 *)( &enabledPerifs));
	
	/* Devolvemos el resultado de la operación */
	return ret;
}

/* V7790 */
returnstatus_t EXPwriteDebugData( uint8 *buffer, uint8 num_bytes, uint32 addr, uint8 mem_id)
{
	returnstatus_t ret;
	
	ret = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, mem_id, addr, num_bytes, buffer);
	
	// Devolvemos el resultado de la operación 
	return ret;
}

returnstatus_t EXPreadDebugData( uint8 *buffer, uint8 num_bytes, uint32 addr, uint8 mem_id)
{
	returnstatus_t ret;
	
	ret = EXPcomOrder( EXP_PROTMST_COM_OP_READ, mem_id, addr, num_bytes, buffer);
	
	// Devolvemos el resultado de la operación 
	return ret;
}
/* V7790 */

returnstatus_t EXP_UCconfigVacumPumpBehaviour( uint32 TonEV, uint16 pumpDuty)
{
	returnstatus_t ret;
	uint32 addr;
	uint8 buffer[6];
	uint8 i;
		
	/* Primero escribimos el TonEV y PumpDuty, ambos son consecutivos en la memoria de la Expansora de modo
	 * que optimizamos las transmisiones */
	for( i = 0; i < 4; i++){ buffer[i] = ( ( uint8 *)( &TonEV))[i];}
	for( i = 0; i < 2; i++){ buffer[i + 4] = ( ( uint8 *)( &pumpDuty))[i];}
	addr = EXP_UC_COMMON_VARS2_DIR_INI + 0;
	ret = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_DATA_MEM_ID, addr, 6, buffer);
	if( ret == ERROR){ return ret;}
	
	/* Asignamos los valores escritos */
	EXPdata.UC.commonData2.fields.vacumConfigTonEV = TonEV;
	EXPdata.UC.commonData2.fields.vacumConfigPumpDuty = pumpDuty;
	
	/* Fin, todo OK */
	return SUCCESS;
}

returnstatus_t EXP_UCconfigHPvacumFactors( float retryFactor, float lungFactor, uint8 slot)
{
	returnstatus_t ret;
	uint32 addr;
	uint8 buffer[4];
	uint8 i;
	uint8 HPindex = slot - 1;
		
	/* Comprobamos que el indice sea correcto */
	if( HPindex > 3){ return ERROR;}
		
	/* Primero enviamos el factor de resuccion */
	for( i = 0; i < 4; i++){ buffer[i] = ( ( uint8 *)( &retryFactor))[i];}	
	addr = EXP_UC_COMMON_VARS2_DIR_INI + EXP_UC_COMMON_VARS2_RETRY_FACTOR_OFFSET + 4 * HPindex;
	ret = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_DATA_MEM_ID, addr, 4, buffer);
	if( ret == ERROR){ return ret;}
	
	/* Asignamos los valores escritos */	
	EXPdata.UC.commonData2.fields.vacumRetryFactor[HPindex] = retryFactor;
	
	/* Segundo enviamos el factor de pulmon */
	for( i = 0; i < 4; i++){ buffer[i] = ( ( uint8 *)( &lungFactor))[i];}
	addr = EXP_UC_COMMON_VARS2_DIR_INI + EXP_UC_COMMON_VARS2_LUNG_FACTOR_OFFSET + 4 * HPindex;
	ret = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_DATA_MEM_ID, addr, 4, buffer);
	if( ret == ERROR){ return ret;}
	
	/* Asignamos los valores escritos */	
	EXPdata.UC.commonData2.fields.vacumLungFactor[HPindex] = lungFactor;
	
	/* Fin, todo OK */
	return SUCCESS;
}

returnstatus_t EXP_UCconfigHPoverHeat( uint8 OnOff, float performanceFactor, uint8 slot)
{
	returnstatus_t ret;
	uint32 addr;
	uint8 boolOnOff;
	uint8 HPindex = slot - 1;
	
	/* Comprobamos que el indice sea correcto */
	if( HPindex > 3){ return ERROR;}
	
	/* El OnOff y el factor de rendimiento no estan consecutivos, tenemos que enviarlos en dos tramas.
	 * Primero enviamos el factor de rendimiento nuevo. */
	addr = EXP_UC_HANDPIECE_VARS_DIR_INI + 32 + EXP_UC_HANDPIECE_VARS_SIZE * HPindex;
	ret = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_DATA_MEM_ID, addr, 4, ( uint8 *)( &performanceFactor));
	if( ret == ERROR){ return ret;}
	
	/* Asignamos el valor escrito */
	EXPdata.UC.handPieceData[HPindex].vars.fields.radPerformanceFactor = performanceFactor;
	
	/* Enviamos el OnOff, convertimos el dato pasado a valor 0 o 1 tipo bool */
	boolOnOff = ( OnOff != 0);
	addr = EXP_UC_HANDPIECE_VARS_DIR_INI + EXP_UC_HANDPIECE_VARS_SIZE * HPindex + 3;
	ret = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_DATA_MEM_ID, addr, 1, &boolOnOff);
	if( ret == ERROR){ return ret;}
	
	/* Asignamos el valor escrito */
	EXPdata.UC.handPieceData[HPindex].vars.fields.performanceCalcOnOff = boolOnOff;
	
	/* Fin, todo OK */
	return SUCCESS;
}

uint8 EXP_UCgetVacumRetrys( uint8 slot)
{
	uint8 HPindex = slot - 1;
	if( HPindex > 3){ return 0xFF;}
	return EXPdata.UC.commonData2.fields.vacumRetrysCnt[HPindex];
}

returnstatus_t EXP_UChandleVentEV( uint8 openClose)
{
	returnstatus_t ret;
	tEXPprotocolBridge bridge;
	uint8 data;
	uint32 addr;
	
	/* Utilizamos el puente protocolo para comunicar con la PCB de complementos */
	/* - Preparamos la trama de orden para el puente protocolo */
	bridge.fields.slaveAddr = 4;
	bridge.fields.opType = 0x81;
	bridge.fields.memID = 0;
	bridge.fields.nBytes = 1;
	bridge.fields.frameTout = 100;
	bridge.fields.frameMaxRetrys = 3;
	bridge.fields.dataAddr = 44;
	
	/* - Enviamos la orden de comunicacion a traves del puente protocolo de la EXP al complemento */
	ret = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_OTHER_PCB_MEM_ID, EXP_UC_PROTOCOL_BRIDGE_DIR_INI, 
					   EXP_UC_PROTOCOL_BRIDGE_VARS_SIZE, bridge.vector);
	if( ret == ERROR){ return ret;}
	
	/* - Enviamos los datos que queremos que se envien en la trama de la EXP al complemento, en
	 * este caso es la orden de apertura o cierre de la EV */
	if( openClose != 0){ data = 4;}else{ data = 3;}
	addr = 20;
	ret = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_OTHER_PCB_MEM_ID, addr, 1, &data);
	if( ret == ERROR){ return ret;}
	
	/* Enviamos la orden de ejecutar la acción */
	addr = 44;
	data = 3;
	ret = EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_DATA_MEM_ID, addr, 1, &data);
	if( ret == ERROR){ return ret;}
	
	/* Todo OK */
	return SUCCESS;
}

//PDTE
uint32 EXP_UCgetPS0alarmFlags( void){ return 0;}
uint32 EXP_UCgetPS1alarmFlags( void){ return 0;}
uint32 EXP_UCgetEXPalarmFlags( void){ return 0;}

/* FUNCIONES PRIVADAS */
returnstatus_t EXPcomOrder( cEXPcomOp operation, uint8 memID, uint32 addr, uint8 nBytes, uint8 *buffer)
{
	nova_ordre_t order;
	ordre_status_t orderStatus;
	prot_mems_status_t memoryStatus;
	uint8 *slaveStatus;
	uint8 slaveStatus1, slaveStatus2;
	uint32 time;
	uint8 nBytesToSend;
	uint8 *dirRel;	
	
//	/* El status de la placa lo recibimos al llamar a "PROTMST_EstatOrdre" en el "ptuEstatEsclau". Aprovechamos
//	 * para refrescarlo cada vez que hagamos una trama buena. */
//	slaveStatus = &( EXPdata.header.fields.board_status.status);
	
//	/* El buffer interno del PROTOCOL MASTER tiene un límite de bytes, tenemos que dividir el
//	 * buffer del usuario en trozos de como máximo dicho tamaño */
//	nBytesToSend = nBytes;
//	dirRel = buffer;
	
//	while( nBytesToSend > 0)
//	{
//		/* Inicializamos la estructura de ordern para el protocolo con los datos que recibidos */
//		order.fields.u8AddrEsclau = EXP_PROTMST_ADDR_SLAVE;
//		order.fields.tipus_operacio = operation;
//		order.fields.u8Memoria = memID;
//		if( nBytesToSend > EXP_PROTMST_MAX_BYTES){ order.fields.u8NumBytes = EXP_PROTMST_MAX_BYTES;}
//		else{ order.fields.u8NumBytes = nBytesToSend;}
//		order.fields.u16TimeoutTrama = EXP_PROTMST_FRAME_TIMEOUT;
//		order.fields.u16MaxReintents = EXP_PROTMST_MAX_RETRYS;
//		order.fields.u32Addr = addr;
		
//		/* Esta función hace un uso bloqueante de la librería protocol master.
//		 * Primero intentamos encolar la orden de comunicaciones durante un tiempo máximo */
//		time = TICKS_GetTicks();
//		while( PROTMST_EncuaOrdre( EXP_PROTMST_SLOT_POS, order, dirRel) != SUCCESS &&
//			   TICKS_DiffTicks( time) < EXP_PROTMST_BLOCKING_TIMEOUT)
//		{
//			/* No conseguimos encolar la orden de comunicaciones, llamamos al motor para liberar el esclavo */
//			PROTMST_Motor();
//		}
		
//		/* Esperamos a que la orden se haya completado o salgamos por timeout. Si en el anterior hemos salido
//		 * por timeout el while nunca entrará.
//		 * Forzamos a 0 el orderStatus para que siempre entre la primera vez al while, no nos fiamos de que
//		 * la funcion "PROTMST_EstatOrdre" no de problemas si no se ha podido encolar la orden en el anterior
//		 * while por el timeout. (Si miramos su coigo fuente no parece que tenga que dar ningun problema de
//		 * todos modos) */
//		orderStatus.value = 0;
//		while( ( orderStatus.value & 0xF0) == 0 && TICKS_DiffTicks( time) < EXP_PROTMST_BLOCKING_TIMEOUT)
//		{
//			/* La comunicación esta en curso, llamamos al motor */
//			PROTMST_Motor();
			
//			/* Siguiente comprobación de status */
//			orderStatus = PROTMST_EstatOrdre( EXP_PROTMST_SLOT_POS, &memoryStatus,
//											  slaveStatus, &slaveStatus1, &slaveStatus2);
//		}
			
//		/* Comprobamos si hemos salido por timeout */
//		if( TICKS_DiffTicks( time) >= EXP_PROTMST_BLOCKING_TIMEOUT)
//		{
//			/* Timeout de bloqueo agotado, error de comunicaciones */
//			ERR_add( Err_ComExp);
//			return ERROR;
//			//OJO ESTO TENEMOS QUE LLAMAR AL MOTOR CON EL ESTATORDRE HASTA QUE DE FINALIZADO PDTE
//		}
		
//		/* Si llegamos aqui no hemos salido por timeout, comprobamos el resultado de la comunicación */
//		if( orderStatus.bit_field.u8OrdreFinalitzada)
//		{
//			/* La comunicación ha ido bien, actualizamos para el envio del siguiente trozo del buffer */
//			nBytesToSend = nBytesToSend - order.fields.u8NumBytes;
//			dirRel = dirRel + order.fields.u8NumBytes;
//			addr += order.fields.u8NumBytes;
//			ERR_delete(Err_ComExp);
//		}
//		else
//		{
//			/* La comunicación ha fallado. Indicamos eror general de comunicaciones */
//			ERR_add( Err_ComExp);
//			return ERROR;
//		}
//	}
	
	if( nBytesToSend == 0){ return SUCCESS;}else{ return ERROR;}
}

returnstatus_t EXPgetData( uint8 memID, uint32 addr, uint8 nBytes, uint8 *buffer)
{
	returnstatus_t ret;
	
	/* Petición de datos */
	ret = EXPcomOrder( EXP_PROTMST_COM_OP_READ, memID, addr, nBytes, buffer);
	
	/* Devolvemos el resultado */
	return ret;
}

returnstatus_t EXPupdatePerifs( void)
{
	returnstatus_t ret;
	uint16 myBuff[2];
	uint16 initPerifs, enabledPerifs;
	uint8 i, isInit;
	uint32 addr;
	
	/* Pedimos los perifericos iniciados y los habilitados */
	ret = EXPgetData( EXP_PROTMST_GPERIF_MEM_ID, EXP_GPERIF_STATUS_PERIFS_DIR_INI, 
					  EXP_GPERIF_STATUS_PERIFS_SIZE, ( uint8 *)myBuff);
	if( ret == ERROR){ return ret;}
	initPerifs = myBuff[1];
	enabledPerifs = myBuff[0];
	
	/* Actualizamos el valor del campo isInit de los perifericos y comprobamos si ha habido
	 * flanco de detección de periferico */
	for( i = 0; i < EXP_MAX_PERIF; i++)
	{
		/* Asignamos si el periferico esta habilitado o no */
		EXPdata.perif[i].isEnabled = ( enabledPerifs & (0x0001 << i)) != 0;
		
		/* Vemos si el periferico esta inicializado */
		isInit = ( initPerifs & (0x0001 << i)) != 0;
		
		/* Comprobamos si hay flanco de detección */
		if( ( EXPdata.perif[i].isInit == 0) && isInit){ EXPdata.newPerif[i] = 1;}
		
		/* Si el periferico no esta init reseteamos la variable de flanco de detección */
		if( !isInit){ EXPdata.newPerif[i] = 0;}
		
		/* Indicamos si el periferico esta inicializado */
		EXPdata.perif[i].isInit = isInit;		
		
		/* Comprobamos si hay error de comunicaciones de SPI con el periferico. Si no esta habilitado
		 * damos el SPI como OK */
		if( EXPdata.perif[i].isEnabled)
		{
			EXPdata.perif[i].isSPIok = ( ( EXPdata.UC.commonData2.fields.temporaryEnabledPerif & ( 0x0001 << i)) != 0); 
		}
		else
		{
			EXPdata.perif[i].isSPIok = 1;
		}
		
		/* Obtenemos la información de versiones general del periferico si hay flanco de deteccion,
		 * esto es para hacerlo solo cuando se conecte el periferico y no de forma continuada */
		if( EXPdata.newPerif[i])
		{
			/* Calculamos la dirección inicial para el periferico deseado */
			addr = i * EXP_GPERIF_GENERAL_DATA_SIZE + EXP_GPERIF_GENERAL_DATA_DIR_INI;
					
			/* Pedimos la información general de un periferico */
			ret = EXPgetData( EXP_PROTMST_GPERIF_MEM_ID, addr, EXP_GPERIF_GENERAL_DATA_SIZE, 
							  EXPdata.perif[i].data.vector);
			if( ret == ERROR){ return ret;}
		}
	}
	
	/* Devolvemos el resultado */
	return ret;
}

returnstatus_t EXP_UCupdateHP( void)
{
	returnstatus_t ret;
	uint32 addr;
	uint8 i;
	
	/* Bucle de lectura para todos los slots de manipulos*/
	for( i = 0; i < EXP_UC_NUM_HANDPIECES; i++)
	{
		/* Leemos los datos de sensores internos de la maquina de cada manípulo aunque no este conectado */
		/* Calculamos la dirección inicial para el HP deseado */
		addr = i * EXP_UC_HANDPIECE_SENSORS_SIZE + EXP_UC_HANDPIECE_SENSORS_DIR_INI;
		
		/* Pedimos la información */
		ret = EXPgetData( EXP_PROTMST_DATA_MEM_ID, addr, EXP_UC_HANDPIECE_SENSORS_SIZE, 
						  EXPdata.UC.handPieceData[i].sensors.vector);
		if( ret == ERROR){ return ret;}
		
		/* Leemos las variables que el manipulo indica a la expansora solo si el manipulo esta conectado.
		 * En caso de no estar conectado su valor no tendría sentido */
		if( EXPdata.perif[EXP_UC_HANDPIECE_HW_PERIF_POS[i]].isInit)
		{
			/* Calculamos la direccion segun el HP deseado */
			addr = i * EXP_UC_HANDPIECE_VARS_SIZE + EXP_UC_HANDPIECE_VARS_DIR_INI;
			
			/* Pedimos la información */
			ret = EXPgetData( EXP_PROTMST_DATA_MEM_ID, addr, EXP_UC_HANDPIECE_VARS_SIZE, 
							  EXPdata.UC.handPieceData[i].vars.vector);
			if( ret == ERROR){ return ret;}
		}		
	}
	
	/* Devolvemos el resultado */
	return ret;
}

//PDTE CONTROLES DE TEMPERATURA CON TIMEOUTS
returnstatus_t EXP_UCerror( void)
{
	returnstatus_t ret = IDLE;
	uint8 cnt;
	float sum;
		
//	//PDTE algunos errores a gestionar
//	/* Errores de los datos obtenidos por el modulo EXP */
//	/* - Control de versiones de periferico */
//	//EXPdata.perif[0].data.fields.version;				//HPcryo
//	//EXPdata.perif[0].data.fields.Maxbuffer;				//EXP o PRF
//	//EXPdata.perif[0].data.fields.versionDataBlock[cnt]; //HPcryo
	
//	/* - Numero F.A. usadas por periferico */
//	//EXPdata.perif[0].data.fields.nPowerSuppliesUsed;
	
//	/* - Detección de alarma general SETA */
//	//EXPdata.UC.commonData1.fields.status.bits.alarma_gral; //Es para saber si ha sido la expansora?
	
//	/* - Puertas UC */
//	//EXPdata.UC.commonData1.fields.status.bits.puerta_vac; //No montado
//	//EXPdata.UC.commonData1.fields.status.bits.puerta_iza; //No montado
//	//EXPdata.UC.commonData1.fields.status.bits.puerta_dcha; //No montado
//	//EXPdata.UC.commonData1.fields.status.bits.puerta_elec; //No montado
//	if( EXPdata.UC.commonData1.fields.status.bits.puerta_tobera){ ERR_add( Error_FiltroAire);}
//	else
//	{
//		ERR_delete( Error_FiltroAire);
//		ERR_warning_clear(Maq, Aviso_FiltroAire);
//	}
	
//	/* - Temperatura ambiente */
////	if( EXPdata.UC.commonData1.fields.envTemp > EXP_ERR_ALARM_TEMP_ENV_HIGH){ ERR_add( Err_SnsTempAmbienteAltaAlarma);}
////	else{ ERR_delete( Err_SnsTempAmbienteAltaAlarma);}
////	if( EXPdata.UC.commonData1.fields.envTemp < EXP_ERR_ALARM_TEMP_ENV_LOW){ ERR_add( Err_SnsTempAmbienteBajaAlarma);}
////	else{ ERR_delete( Err_SnsTempAmbienteBajaAlarma);}
//	if( EXPdata.UC.commonData1.fields.envTemp > EXP_ERR_WARN_TEMP_ENV){ ERR_add( Err_SnsTempAmbienteAltaAviso);}
//	else{ERR_delete( Err_SnsTempAmbienteAltaAviso);}
//	if( EXPdata.UC.commonData1.fields.envTemp < EXP_ERR_WARN_FLAG_DOWN_TEMP_ENV)	{ERR_warning_clear(Maq, Aviso_TempAmbiente);}
	
//	/* - Temperaturas H2O */
//	//EXPdata.UC.commonData1.fields.radOutTemp;  //No montada
//	if( EXPdata.UC.commonData1.fields.pumpOutTemp > EXP_ERR_ALARM_TEMP_PUMP_OUT_HIGH){ ERR_add( Error_TempPumpOutAlta);}
//	else{ ERR_delete( Error_TempPumpOutAlta);}
//	if( EXPdata.UC.commonData1.fields.pumpOutTemp < EXP_ERR_ALARM_TEMP_PUMP_OUT_LOW){ ERR_add( Error_TempPumpOutBaja);}
//	else{ ERR_delete( Error_TempPumpOutBaja);}
//	if( EXPdata.UC.commonData1.fields.returnTemp > EXP_ERR_ALARM_RETURN_TEMP_HIGH){ ERR_add( Error_TempRetornoAlta);}
//	else{ ERR_delete( Error_TempRetornoAlta);}
//	if( EXPdata.UC.commonData1.fields.returnTemp < EXP_ERR_ALARM_RETURN_TEMP_LOW){ ERR_add( Error_TempRetornoBaja);}
//	else{ ERR_delete( Error_TempRetornoBaja);}
	
//	/* - Caudales */
//	if( EXPdata.UC.commonData1.fields.returnFlow > EXP_ERR_ALARM_MAX_RETURN_FLOW){ ERR_add( Error_CaudalRetornoMaximo);}
//	else{ ERR_delete( Error_CaudalRetornoMaximo);}
	
//	/* - Presion del H2O */
//	//EXPdata.UC.commonData1.fields.waterPressure; //No montado
	
//	/* - Habilitación temporal de perifericos, esto es el error de comunicaciones SPI */
//	//EXPdata.UC.commonData2.fields.temporaryEnabledPerif; //QUE LO MIRE PRF PARA NO TENER QUE PONER MASCARA DE PRF POSIBLES
	
//	/* - Resucciones */
//	//EXPdata.UC.commonData2.fields.vacumRetrysCnt[cnt];	//HPcryo
	
//	/* - Comunicaciones con los complementos. Sistema de mascara para poder trabajar con los otros
//	 * HP si falla el complementos de uno en concreto, es decir, no damos error si no hay HP */
//	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 0) & 1)){	ERR_add(Error_Com485_Fuente1);}
//	else{ ERR_delete(Error_Com485_Fuente1);}
//	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 1) & 1)){	ERR_add(Error_Com485_Fuente2);}
//	else{ ERR_delete(Error_Com485_Fuente2);}
//	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 2) & 1)){	ERR_add(Error_Com485_Perd);}
//	else{ ERR_delete(Error_Com485_Perd);}
//	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 3) & 1)){ ERR_add(Error_Com485_Rebos);}
//	else{ ERR_delete(Error_Com485_Rebos);}
//	if(!(EXPdata.UC.commonData2.fields.enabled485devices >> 12) & 1){ ERR_add(Error_Com485_DetectorNivel);}
//	else{ ERR_delete(Error_Com485_DetectorNivel);}
	
//	EXP_UCerror485complBusPerif( 1, 4, 8, Error_Com485_H201, Error_Com485_VAC1);
//	EXP_UCerror485complBusPerif( 2, 5, 10, Error_Com485_H202, Error_Com485_VAC2);
//	EXP_UCerror485complBusPerif( 3, 6, 11, Error_Com485_H203, Error_Com485_VAC3);
//	EXP_UCerror485complBusPerif( 4, 7, 9, Error_Com485_H204, Error_Com485_VAC4);
	
//	/* - Consumos de bomba y radiador */
//	if( EXPdata.UC.commonData2.fields.consWaterPump > EXP_ERR_ALARM_MAX_WATER_PUMP_CONS){ ERR_add( Error_MaxConsBombaH2O);}
//	else{ ERR_delete( Error_MaxConsBombaH2O);}
//	if( EXPdata.UC.commonData2.fields.consRadFan > EXP_ERR_ALARM_MAX_RAD_FAN_CONS){ ERR_add( Error_MaxConsVentRad);}
//	else{ ERR_delete( Error_MaxConsVentRad);}
	
//	/* - Consumos de los 24V a los HP. La suma no puede superar un máximo ya que cada HP podria
//	 * consumir diferente. */
//	sum = 0.0;
//	for( cnt = 0; cnt < EXP_UC_NUM_HANDPIECES; cnt++)
//	{ sum = sum + EXPdata.UC.commonData2.fields.cons24V_HP[cnt];}
////	if( sum > EXP_ERR_ALARM_MAX_24V_TOTAL_CONS){ ERR_add( Error_MaxCons24Vtotal);}
////	else{ ERR_delete( Error_MaxCons24Vtotal);}
	
//	/* - Consumos individuales de cada HP */
//	//EXPdata.UC.commonData2.fields.cons24V_HP[cnt]; //HPcryo
	
//	/* - Caudales de retorno de los HP */
//	//EXPdata.UC.handPieceData[cnt].sensors.fields.returnFlow; //HPcryo
	
//	/* - Temperatura de retorno */
//	//EXPdata.UC.handPieceData[cnt].sensors.fields.returnTemp; //HPcryo
	
//	/* - Nivel de vacum máximo */
//	//EXPdata.UC.handPieceData[cnt].sensors.fields.vacum; //HPcryo
	
//	/* - Detector de nivel */
////	if( !EXPdata.UC.PCBlvlDetector.vars.fields.level.bits.lvl1){ ERR_add( Error_NivelH2OBajo);}
////	else{ ERR_delete( Error_NivelH2OBajo);}
////	if( !EXPdata.UC.PCBlvlDetector.vars.fields.level.bits.lvl2){ ERR_add( Error_NivelH2OMedio);}
////	else{ ERR_delete( Error_NivelH2OMedio);}
	
//	/* - Detector de nivel */
//	if( !EXPdata.UC.PCBlvlDetector.vars.fields.level.bits.lvl0 && !EXPdata.UC.PCBlvlDetector.vars.fields.level.bits.lvl1 && !EXPdata.UC.PCBlvlDetector.vars.fields.level.bits.lvl2){ ERR_add( Error_NivelH2OBajo);}
//	else{ 		ERR_delete( Error_NivelH2OBajo);	}
	
//	if( EXPdata.UC.PCBlvlDetector.vars.fields.level.bits.lvl1){	ERR_warning_clear(Maq, Aviso_NivelAguaBajo);}
	
//	if( !EXPdata.UC.PCBlvlDetector.vars.fields.level.bits.lvl1 && !EXPdata.UC.PCBlvlDetector.vars.fields.level.bits.lvl2){ ERR_add( Error_NivelH2OMedio);}
//	else{ 	ERR_delete( Error_NivelH2OMedio);	}
	
//	if(EXPdata.UC.PCBlvlDetector.vars.fields.level.bits.lvl2){		ERR_warning_clear(Maq, Aviso_NivelAguaBajo|Aviso_NivelAguaMedio);	}
	
	return ret;
}

void EXP_UCerror485complBusPerif( uint8 perif, uint8 H2Oshift, uint8 vacShift, 
							   uint16 H2OerrCode, uint16 vacErrCode)
{
//	/* Solo en el periferico que este inicializado comprobamos los complementos que necesita */
//	if( EXPdata.perif[perif].isInit)
//	{
//		/* Comprobamos si falla el de vacum o el de la H2O */
//		if(!((EXPdata.UC.commonData2.fields.enabled485devices >> H2Oshift) & 1)){ ERR_add(H2OerrCode);}
//		else{ ERR_delete(H2OerrCode);}
//		if(!((EXPdata.UC.commonData2.fields.enabled485devices >> vacShift) & 1)){ ERR_add(vacErrCode);}
//		else{ ERR_delete(vacErrCode);}
//	}
//	else
//	{
//		/* Si no falla ninguno descontamos del filtrado del error */
//		ERR_delete(H2OerrCode); ERR_delete(vacErrCode);
//	}
}

void EXPrefreshCPI( void)
{
	float retTemp;
	float retFlow;
	float pumpTemp;
	float envTemp;
	float Vtob;
	retTemp = EXPdata.UC.commonData1.fields.returnTemp;
	retFlow = EXPdata.UC.commonData1.fields.returnFlow;
	pumpTemp = EXPdata.UC.commonData1.fields.pumpOutTemp;
	envTemp = EXPdata.UC.commonData1.fields.envTemp;
	Vtob = EXPdata.UC.radFanVoltage;
	
	/* Calculo del CPI a partir de las lecturas del equipo. Primero comprobamos que no vamos
	 * a dividir por 0.0 */
	if( retFlow > 0.0 && retTemp > pumpTemp)
	{
		/* Calculamos el CPI */
		EXPdata.UC.CPI = ( ( ( ( retTemp + pumpTemp) / 2.0) - envTemp) * Vtob) / ( ( retTemp - pumpTemp) * retFlow); 
	}
	else
	{
		EXPdata.UC.CPI = 0.0;
	}	
}

uint8 EXP_UCgetLevelHighWater( void)
{
	return EXPdata.UC.PCBlvlDetector.vars.fields.level.bits.lvl2;
}

float EXP_UCgetEnvTemp ( void)
{
	return EXPdata.UC.commonData1.fields.envTemp;
}

uint8 EXP_UCoscTempStatus (void)
{
	return EXPdata.UC.Config_Param.data.ModeTempOscIDLE;
}

uint8 EXP_UCresuctionsViewer (void)
{
	return EXPdata.UC.Config_Param.data.ModeResuctionsViewer;
}

uint8 EXP_UCtempViewer (void)
{
	return EXPdata.UC.Config_Param.data.ModeTemperatureViewer;
}

uint8 EXP_UCtempSlopeStatus (void)
{
	return !EXPdata.UC.Config_Param.data.ModeTempSlope;
}

uint8 EXP_UCtempSecureStatus (void)
{
	return EXPdata.UC.Config_Param.data.ModeTempSecure;
}

uint8 EXP_UCerrSecureStatus (void)
{
	return !EXPdata.UC.Config_Param.data.ModeErrSec;
}

uint8 EXP_UCerrDeltaTempSecureStatus (void)
{
	return !EXPdata.UC.Config_Param.data.ModeErrDeltaTempSec;
}

uint8 EXP_UCreuseLabelModeStatus (void)
{
	return EXPdata.UC.Config_Param.data.ModeRecicleLabel;
}

uint8 EXP_UC_RecLOG_Status (void)					/* V7790 - LOGs */
{
	return !EXPdata.UC.Config_Param.data.ModeRecLOG;
}

//uint8 EXP_UC_get_Language (void)
//{
//	return EXPdata.UC.Config_Param.data.Language;
//}

//void EXP_UC_set_Language (uint8 Language)
//{
//	EXPdata.UC.Config_Param.data.Language = Language;
//}
/*
//V7790 - DISCLAIMER
uint8 EXP_UC_get_Country (void)
{
	return EXPdata.UC.Config_Param.data.Country;
}

void EXP_UC_set_Country (uint8 Country)
{
	EXPdata.UC.Config_Param.data.Country = Country;
}

uint8 EXP_UC_get_Month_REF (void)
{
	return EXPdata.UC.Config_Param.data.Month_ref;
}

void EXP_UC_set_Month_REF (uint8 Month)
{
	EXPdata.UC.Config_Param.data.Month_ref = Month;
}

void EXP_UC_Check_Month (void)
{
	LDD_RTC_TTime Time;
	
	RTC_get_time (&Time);
	
	if(((uint8)Time.Month != EXP_UC_get_Month_REF()) && (EXP_UC_get_Month_REF() != 0) )
	{
		TEST_PrintInfo("Reset Pais seleccionado\r\n");
		
		EXP_UC_set_Country (0);		//App_GUI_Sin_pais = 0
		while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
	}
}
*/
/* - Fatiga - */

float EXP_UCfatigaGetErrorValues(cEXP_UCfatigueValues val)
{
	switch(val)
	{
		case FAT_VAL_PresionHP1:	return EXPdata.UC.FatigueProcess.FatigueError.Presion1;	break;
		case FAT_VAL_PresionHP2:	return EXPdata.UC.FatigueProcess.FatigueError.Presion2;	break;
		case FAT_VAL_PresionHP3:	return EXPdata.UC.FatigueProcess.FatigueError.Presion3;	break;
		case FAT_VAL_PresionHP4:	return EXPdata.UC.FatigueProcess.FatigueError.Presion4;	break;
		case FAT_VAL_CaudalHP1:	return EXPdata.UC.FatigueProcess.FatigueError.Caudal1; 	break;
		case FAT_VAL_CaudalHP2:	return EXPdata.UC.FatigueProcess.FatigueError.Caudal2;	break;
		case FAT_VAL_CaudalHP3:	return EXPdata.UC.FatigueProcess.FatigueError.Caudal3;	break;
		case FAT_VAL_CaudalHP4:	return EXPdata.UC.FatigueProcess.FatigueError.Caudal4;	break;
		case FAT_VAL_Rth:	return EXPdata.UC.FatigueProcess.FatigueError.Rth;	break;
		case FAT_VAL_retTemp:	return EXPdata.UC.FatigueProcess.FatigueError.retTemp;	break;
		case FAT_VAL_retFlow:	return EXPdata.UC.FatigueProcess.FatigueError.retFlow;	break;
		case FAT_VAL_pumpTemp:	return EXPdata.UC.FatigueProcess.FatigueError.pumpTemp;	break;
		case FAT_VAL_envTemp:	return EXPdata.UC.FatigueProcess.FatigueError.envTemp;	break;
		case FAT_VAL_Vtob:	return EXPdata.UC.FatigueProcess.FatigueError.Vtob;	break;
		case FAT_VAL_CPI:	return EXPdata.UC.FatigueProcess.FatigueError.CPI;	break;
		default: break;
	}
	return 0;
}

void EXP_UCfatigaSetErrorValues (void)
{
	uint32 time;
	EXP_UCfatigaDataUpdate(&EXPdata.UC.FatigueProcess.FatigueError.Rth, &EXPdata.UC.FatigueProcess.FatigueError.retTemp, &EXPdata.UC.FatigueProcess.FatigueError.retFlow,
						   &EXPdata.UC.FatigueProcess.FatigueError.pumpTemp, &EXPdata.UC.FatigueProcess.FatigueError.envTemp, &EXPdata.UC.FatigueProcess.FatigueError.Vtob,
						   &EXPdata.UC.FatigueProcess.FatigueError.CPI,
						   &EXPdata.UC.FatigueProcess.FatigueError.Caudal1, &EXPdata.UC.FatigueProcess.FatigueError.Caudal2, &EXPdata.UC.FatigueProcess.FatigueError.Caudal3,
						   &EXPdata.UC.FatigueProcess.FatigueError.Caudal4,
						   &time,
						   &EXPdata.UC.FatigueProcess.FatigueError.Presion1, &EXPdata.UC.FatigueProcess.FatigueError.Presion2, &EXPdata.UC.FatigueProcess.FatigueError.Presion3,
						   &EXPdata.UC.FatigueProcess.FatigueError.Presion4);
}

void EXP_UCfatigaStart( void)
{
	EXP_UCfatiga_init();
	EXPdata.UC.FatigaStartStop = 1;
}

void EXP_UCfatigaStop( void)
{
	EXPdata.UC.FatigaStartStop = 0;
}

cEXP_UCfatigueSteps EXP_UCfatigaStatus ( void)
{
	return EXPdata.UC.FatigueProcess.step;
}

void EXP_UCfatigaDataUpdate(float *Rth, float *retTemp, float *retFlow, float *pumpTemp, float *envTemp, float *Vtob, float *CPI, float *CaudalRetornoHP1, float *CaudalRetornoHP2, float *CaudalRetornoHP3, float *CaudalRetornoHP4, uint32 *Fatigue_time, float *PresionHP1, float *PresionHP2, float *PresionHP3, float *PresionHP4)
{	
	tHPcryoData *HP;
	tPRFdata *PRF;
		
	//Valores requeridos de la Expansora
	*retTemp = EXPdata.UC.commonData1.fields.returnTemp;
	*retFlow = EXPdata.UC.commonData1.fields.returnFlow;
	*pumpTemp = EXPdata.UC.commonData1.fields.pumpOutTemp;
	*envTemp = EXPdata.UC.commonData1.fields.envTemp;
	*Vtob = EXPdata.UC.radFanVoltage;
	*CPI = EXPdata.UC.CPI;
	if ((*retFlow*(*retTemp-*pumpTemp)!=0))	*Rth = (((*retTemp + *pumpTemp)/2.0)-*envTemp)/(*retFlow*(*retTemp-*pumpTemp));
	else	*Rth=0.0;
	
	if(HPcryoGetFromSlot( PRF_HW_SLOT1, &HP, &PRF)){	*CaudalRetornoHP1 = EXPdata.UC.handPieceData[PRF_HW_SLOT1-1].sensors.fields.returnFlow;	*PresionHP1 = HP->frames.mainOut.data.presionVaccum;	}
	else{	*CaudalRetornoHP1 = 0.0;	*PresionHP1 = 0.0;	}
	if(HPcryoGetFromSlot( PRF_HW_SLOT2, &HP, &PRF)){	*CaudalRetornoHP2 = EXPdata.UC.handPieceData[PRF_HW_SLOT2-1].sensors.fields.returnFlow;	*PresionHP2 = HP->frames.mainOut.data.presionVaccum;	}
	else{	*CaudalRetornoHP2 = 0.0;	*PresionHP2 = 0.0;	}
	if(HPcryoGetFromSlot( PRF_HW_SLOT3, &HP, &PRF)){	*CaudalRetornoHP3 = EXPdata.UC.handPieceData[PRF_HW_SLOT3-1].sensors.fields.returnFlow;	*PresionHP3 = HP->frames.mainOut.data.presionVaccum;	}
	else{	*CaudalRetornoHP3 = 0.0;	*PresionHP3 = 0.0;	}
	if(HPcryoGetFromSlot( PRF_HW_SLOT4, &HP, &PRF)){	*CaudalRetornoHP4 = EXPdata.UC.handPieceData[PRF_HW_SLOT4-1].sensors.fields.returnFlow;	*PresionHP4 = HP->frames.mainOut.data.presionVaccum;	}
	else{	*CaudalRetornoHP4 = 0.0;	*PresionHP4 = 0.0;	}
	
	*Fatigue_time = EXPdata.UC.FatigaTime;
}

uint8 EXP_UCfatigaErrUpdate(uint8 Perif)
{
	uint8 logIndex;
	uint8 *errorLog;
	uint8 i, j;	//Vble auxiliar bucles
		
//	if(Perif != Maq)
//	{
//		ERR_log_err_code(&errorLog, &logIndex, Perif);
//		if(logIndex <=0){	logIndex = NUMBER_ERRORS_LOG-1;	}
//		else{	logIndex--;	}
//		for(j=0;j<NUMBER_ERRORS_LOG;j++)
//		{
//			if(logIndex <=0){	logIndex = NUMBER_ERRORS_LOG-1;	}
//			else{	logIndex--;	}
			
//			if((errorLog[logIndex]!=Err_NPltInsf1+(Perif-1))&&
//			   (errorLog[logIndex]!=Error_HPctrlMaxTemp1+(Perif-1))&&
//			   (errorLog[logIndex]!=Error_HPctrlDifTempFreeze1+(Perif-1))&&
//			   (errorLog[logIndex]!=Error_HPctrlDeltaTempMax1+(Perif-1))&&
//			   /*V7787 fatiga*/
//			   (errorLog[logIndex]!=Error_HPsondaStep1+(Perif-1))&&
//			   (errorLog[logIndex]!=Error_HPcalibOutRange1+(Perif-1))&&
//			   (errorLog[logIndex]!=Error_HPsondaRotaHP1+(Perif-1))&&
//			   /*V7787 fatiga*/
//			   (errorLog[logIndex]!=0))
//			{	return errorLog[logIndex];	}
//		}
//	}
//	else
//	{
//		ERR_log_err_code(&errorLog, &logIndex, Maq);
//		if(logIndex <=0){	logIndex = NUMBER_ERRORS_LOG-1;	}
//		else{	logIndex--;	}
//		for(i=0;i<NUMBER_ERRORS_LOG;i++)
//		{
//			if(logIndex <=0){	logIndex = NUMBER_ERRORS_LOG-1;	}
//			else{	logIndex--;	}
			
//			if((errorLog[logIndex]!=Error_BusAlarma_Seta)&&(errorLog[logIndex]!=0)){	return errorLog[logIndex];	}
//		}
//	}
	return 0;
}

cEXP_UCfatigueValuesStatus EXP_UCfatigaCheckValue(cEXP_UCfatigueValues value_type, float value)
{
	tHPcryoData *HP;
	tPRFdata *PRF;
	
	if(EXPdata.UC.FatigueProcess.step!=EXP_UC_FATIGUE_DONE){	return EXP_UC_FATIGUE_VALUE_UNCHECKED;	}
	
	switch(value_type)
	{
		case FAT_VAL_PresionHP1:if(HPcryoGetFromSlot( PRF_HW_SLOT1, &HP, &PRF))
						{	if(value<(EXPdata.UC.FatigaPresion_ref[0]-EXP_UC_FATIGA_VAC_LOSS_LIM)){return EXP_UC_FATIGUE_VALUE_WRONG;}	
							else if(EXPdata.UC.FatigaCountResuc[0]){return EXP_UC_FATIGUE_VALUE_VAC_RESUCTION;}
							else{return EXP_UC_FATIGUE_VALUE_OK;}}
			break;
		case FAT_VAL_PresionHP2:if(HPcryoGetFromSlot( PRF_HW_SLOT2, &HP, &PRF))
						{	if(value<(EXPdata.UC.FatigaPresion_ref[1]-EXP_UC_FATIGA_VAC_LOSS_LIM)){return EXP_UC_FATIGUE_VALUE_WRONG;}
							else if(EXPdata.UC.FatigaCountResuc[1]){return EXP_UC_FATIGUE_VALUE_VAC_RESUCTION;}
							else{return EXP_UC_FATIGUE_VALUE_OK;}	}
			break;
		case FAT_VAL_PresionHP3:if(HPcryoGetFromSlot( PRF_HW_SLOT3, &HP, &PRF))
						{	if(value<(EXPdata.UC.FatigaPresion_ref[2]-EXP_UC_FATIGA_VAC_LOSS_LIM)){return EXP_UC_FATIGUE_VALUE_WRONG;}
							else if(EXPdata.UC.FatigaCountResuc[2]){return EXP_UC_FATIGUE_VALUE_VAC_RESUCTION;}
							else{return EXP_UC_FATIGUE_VALUE_OK;}	}
			break;
		case FAT_VAL_PresionHP4:if(HPcryoGetFromSlot( PRF_HW_SLOT4, &HP, &PRF))
						{	if(value<(EXPdata.UC.FatigaPresion_ref[3]-EXP_UC_FATIGA_VAC_LOSS_LIM)){return EXP_UC_FATIGUE_VALUE_WRONG;}
							else if(EXPdata.UC.FatigaCountResuc[3]){return EXP_UC_FATIGUE_VALUE_VAC_RESUCTION;}
							else{return EXP_UC_FATIGUE_VALUE_OK;}	}
			break;
		case FAT_VAL_CaudalHP1:if(HPcryoGetFromSlot( PRF_HW_SLOT1, &HP, &PRF))
						{	if((value<EXP_UC_FATIGA_LIM_MIN_CAUDAL)||(value>EXP_UC_FATIGA_LIM_MAX_CAUDAL))
							{return EXP_UC_FATIGUE_VALUE_WRONG;}else{return EXP_UC_FATIGUE_VALUE_OK;}	}
			break;
		case FAT_VAL_CaudalHP2:if(HPcryoGetFromSlot( PRF_HW_SLOT2, &HP, &PRF))
						{	if((value<EXP_UC_FATIGA_LIM_MIN_CAUDAL)||(value>EXP_UC_FATIGA_LIM_MAX_CAUDAL))
							{return EXP_UC_FATIGUE_VALUE_WRONG;}else{return EXP_UC_FATIGUE_VALUE_OK;}	}
			break;
		case FAT_VAL_CaudalHP3:if(HPcryoGetFromSlot( PRF_HW_SLOT3, &HP, &PRF))
						{	if((value<EXP_UC_FATIGA_LIM_MIN_CAUDAL)||(value>EXP_UC_FATIGA_LIM_MAX_CAUDAL))
							{return EXP_UC_FATIGUE_VALUE_WRONG;}else{return EXP_UC_FATIGUE_VALUE_OK;}	}
			break;
		case FAT_VAL_CaudalHP4:if(HPcryoGetFromSlot( PRF_HW_SLOT4, &HP, &PRF))
						{	if((value<EXP_UC_FATIGA_LIM_MIN_CAUDAL)||(value>EXP_UC_FATIGA_LIM_MAX_CAUDAL))
							{return EXP_UC_FATIGUE_VALUE_WRONG;}else{return EXP_UC_FATIGUE_VALUE_OK;}	}
			break;
		case FAT_VAL_Rth:		return EXP_UC_FATIGUE_VALUE_UNCHECKED;//if(){}
			break;
		case FAT_VAL_retTemp:	return EXP_UC_FATIGUE_VALUE_UNCHECKED;//if(){}
			break;
		case FAT_VAL_retFlow:	return EXP_UC_FATIGUE_VALUE_UNCHECKED;//if(){}
			break;
		case FAT_VAL_pumpTemp:	return EXP_UC_FATIGUE_VALUE_UNCHECKED;//if(){}
			break;
		case FAT_VAL_envTemp:	return EXP_UC_FATIGUE_VALUE_UNCHECKED;//if(){}
			break;
		case FAT_VAL_Vtob:		return EXP_UC_FATIGUE_VALUE_UNCHECKED;//if(){}
			break;
		case FAT_VAL_CPI:		if((value<7)||(value>12)){return EXP_UC_FATIGUE_VALUE_WRONG;}else{return EXP_UC_FATIGUE_VALUE_OK;}
			break;
		case FAT_VAL_ErrorHP1:	if((uint8)value!=0){return EXP_UC_FATIGUE_VALUE_WRONG;}else{return EXP_UC_FATIGUE_VALUE_OK;}	break;
		case FAT_VAL_ErrorHP2:	if((uint8)value!=0){return EXP_UC_FATIGUE_VALUE_WRONG;}else{return EXP_UC_FATIGUE_VALUE_OK;}	break;
		case FAT_VAL_ErrorHP3:	if((uint8)value!=0){return EXP_UC_FATIGUE_VALUE_WRONG;}else{return EXP_UC_FATIGUE_VALUE_OK;}	break;
		case FAT_VAL_ErrorHP4:	if((uint8)value!=0){return EXP_UC_FATIGUE_VALUE_WRONG;}else{return EXP_UC_FATIGUE_VALUE_OK;}	break;
		case FAT_VAL_ErrorMaq:	if((uint8)value!=0){return EXP_UC_FATIGUE_VALUE_WRONG;}else{return EXP_UC_FATIGUE_VALUE_OK;}	break;
		default: return EXP_UC_FATIGUE_VALUE_UNCHECKED; break;
	}
	return EXP_UC_FATIGUE_VALUE_UNCHECKED;
}

uint8 EXP_UCfatigaVerif( void)
{
//	//Declaración de variables
//	uint8 i;
//	float PresionHP1, PresionHP2, PresionHP3, PresionHP4;
//	float CaudalRetornoHP1, CaudalRetornoHP2, CaudalRetornoHP3, CaudalRetornoHP4;
//	float Rth, retTemp, retFlow, pumpTemp, envTemp, Vtob, CPI;
//	uint32 Fatigue_time;
//	//uint8 ResuccionHP1, ResuccionHP2, ResuccionHP3, ResuccionHP4;
	
//	//Asignamos valores a las variables
//	EXPdata.UC.FatigaCountResuc[0] = EXPdata.UC.commonData2.fields.vacumRetrysCnt[0];
//	EXPdata.UC.FatigaCountResuc[1] = EXPdata.UC.commonData2.fields.vacumRetrysCnt[1];
//	EXPdata.UC.FatigaCountResuc[2] = EXPdata.UC.commonData2.fields.vacumRetrysCnt[2];
//	EXPdata.UC.FatigaCountResuc[3] = EXPdata.UC.commonData2.fields.vacumRetrysCnt[3];
	
//	EXP_UCfatigaDataUpdate (&Rth, &retTemp, &retFlow, &pumpTemp, &envTemp, &Vtob, &CPI,
//							&CaudalRetornoHP1, &CaudalRetornoHP2, &CaudalRetornoHP3, &CaudalRetornoHP4,
//							&Fatigue_time,
//							&PresionHP1, &PresionHP2, &PresionHP3, &PresionHP4);
	
//	//Comprobamos que ni haya ningún error en algún manipulo o en la maquina
//	for(i=Manip1;i<=Maq;i++)
//	{
//		if(EXP_UCfatigaErrUpdate(i)!=0)
//		{	return 1;	}
//	}

//	//Tomamos la referencia del nivel de vacuum alcanzado una vez todos los valores han de ser estables
//	if((Fatigue_time>60000) && (Fatigue_time<65000))
//	{	EXPdata.UC.FatigaPresion_ref[0] = PresionHP1;	EXPdata.UC.FatigaPresion_ref[1] = PresionHP2;	EXPdata.UC.FatigaPresion_ref[2] = PresionHP3;	EXPdata.UC.FatigaPresion_ref[3] = PresionHP4;	}
	
//	//Comprobamos que los valores que se están tomando no se salen de los límites establecidos
//	if(Fatigue_time>EXP_UC_FATIGA_DELAY_CHECK_VALUES)
//	{
//		if((CaudalRetornoHP1<EXP_UC_FATIGA_LIM_MIN_CAUDAL)||(CaudalRetornoHP2<EXP_UC_FATIGA_LIM_MIN_CAUDAL)||(CaudalRetornoHP3<EXP_UC_FATIGA_LIM_MIN_CAUDAL)||(CaudalRetornoHP4<EXP_UC_FATIGA_LIM_MIN_CAUDAL)||
//		   (CaudalRetornoHP1>EXP_UC_FATIGA_LIM_MAX_CAUDAL)||(CaudalRetornoHP2>EXP_UC_FATIGA_LIM_MAX_CAUDAL)||(CaudalRetornoHP3>EXP_UC_FATIGA_LIM_MAX_CAUDAL)||(CaudalRetornoHP4>EXP_UC_FATIGA_LIM_MAX_CAUDAL)||
//		   (PresionHP1<(EXPdata.UC.FatigaPresion_ref[0]-EXP_UC_FATIGA_VAC_LOSS_LIM))	||(PresionHP2<(EXPdata.UC.FatigaPresion_ref[1]-EXP_UC_FATIGA_VAC_LOSS_LIM))||
//		   (PresionHP3<(EXPdata.UC.FatigaPresion_ref[2]-EXP_UC_FATIGA_VAC_LOSS_LIM))	||(PresionHP4<(EXPdata.UC.FatigaPresion_ref[3]-EXP_UC_FATIGA_VAC_LOSS_LIM))||
//		   (EXPdata.UC.FatigaCountResuc[0]!=0)||(EXPdata.UC.FatigaCountResuc[1]!=0)||(EXPdata.UC.FatigaCountResuc[2]!=0)||(EXPdata.UC.FatigaCountResuc[3]!=0))
//		{
//			return 1;
//		}
//	}
	
	//Si llegamos aquí todo está funcionando correctamente
	return 0;
}

void EXP_UCfatiga_init ( void)
{
//	uint8 i;
//	tHPcryoData *HP;
//	tPRFdata *PRF;
	
//	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_CHECK_FILTER;/*/EXP_UC_FATIGUE_CHECK_RFID;*/
//	EXPdata.UC.FatigueProcess.substeps = 0;
//	for(i=0;i<EXP_UC_FATIGUE_MAX_STEPS;i++){	EXPdata.UC.FatigueProcess.status[i] = EXP_UC_FATIGUE_STEP_TO_DO;	}
//	for(i=PRF_HW_SLOT1;i<=PRF_HW_SLOT4;i++){	if(HPcryoGetFromSlot( i, &HP, &PRF)){	HPcryoFatigaStop ( HP, PRF);	HPcryoFatigaComplete ( HP_CRYO_FAT_DONE_NONE, HP, PRF);	}	}
}

void EXP_UCfatiga ( void)
{
//	uint8 i;
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	uint16 wng_flags;	//Variable de gestión de los flags de los avisos
//	static char Label_requested[2];
//	static char Label_Read[2];
//	K70_RFID_CPU_ERR_tt RFID_module_Err;
//	returnstatus_t rfid_read_status;
//	static uint32 t_ref;
//	static uint32 diff_t;
//	static uint32 time_accum = 0;
	
	
//	EXPdata.UC.FatigueProcess.status[EXPdata.UC.FatigueProcess.step] = EXP_UC_FATIGUE_STEP_DOING;
//	switch(EXPdata.UC.FatigueProcess.step)
//	{
//		case EXP_UC_FATIGUE_CHECK_FILTER:
//			switch (EXPdata.UC.FatigueProcess.substeps)
//			{
//			case 0:
//				wng_flags = ERR_get_WarningFlags();
//				if ((wng_flags & Aviso_FiltroAire) == 0) EXPdata.UC.FatigueProcess.substeps = 1;
//				break;
//			case 1:
//				wng_flags = ERR_get_WarningFlags();
//				if ((wng_flags & Aviso_FiltroAire) != 0) EXPdata.UC.FatigueProcess.substeps = 2;
//				break;
//			case 2:
//				wng_flags = ERR_get_WarningFlags();
//				if ((wng_flags & Aviso_FiltroAire) == 0)
//				{
//					EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_CHECK_SETA;
//					EXPdata.UC.FatigueProcess.substeps = 0;
//					EXPdata.UC.FatigueProcess.status[EXPdata.UC.FatigueProcess.step] = EXP_UC_FATIGUE_STEP_DONE;
//				}
//				break;
//			default: break;
//			}
//			break;
//		case EXP_UC_FATIGUE_CHECK_SETA:
//			switch (EXPdata.UC.FatigueProcess.substeps)
//			{
//			case 0:	if(BusAlarm_IsAlarmOn())	EXPdata.UC.FatigueProcess.substeps = 1;
//				break;
//			case 1:	if(!BusAlarm_IsAlarmOn())	EXPdata.UC.FatigueProcess.substeps = 2;
//				break;
//			case 2:
//				if(BusAlarm_IsAlarmOn())
//				{
//					EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_CHECK_RFID;
//					EXPdata.UC.FatigueProcess.substeps = 0;
//					EXPdata.UC.FatigueProcess.status[EXPdata.UC.FatigueProcess.step] = EXP_UC_FATIGUE_STEP_DONE;
//				}
//				break;
//			default: break;
//			}
//			break;
//		case EXP_UC_FATIGUE_CHECK_RFID:
//			Label_requested[0] = 'D';
//			Label_requested[1] = 'M';
//			do
//			{
//				rfid_read_status = RFID_read_label(Label_requested, Label_Read, RFID_NOT_ERASE_LABEL, &RFID_module_Err);
//				switch (rfid_read_status)		//Gestion de los estados del proceso de la lectura
//				{
//					case IDLE:
//					case BLOCKING:
//					case RUNNING:	break;
//					case ERROR:		if(RFID_module_Err == K70_RFID_CPU_ERR_LABEL_INVALID)
//									{
//										EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_CHECK_VAC_HP1;
//										EXPdata.UC.FatigueProcess.status[EXPdata.UC.FatigueProcess.step] = EXP_UC_FATIGUE_STEP_DONE;
//										ERR_clear(Maq);
//										time_accum = 0;
//									}
//									break;
//					case SUCCESS:	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_CHECK_VAC_HP1;
//									EXPdata.UC.FatigueProcess.status[EXPdata.UC.FatigueProcess.step] = EXP_UC_FATIGUE_STEP_DONE;
//									ERR_clear(Maq);
//									time_accum = 0;
//									break;
//					default: break;
//				}
//			}while(rfid_read_status == BLOCKING);
//			break;
//		case EXP_UC_FATIGUE_CHECK_VAC_HP1:
//			switch (EXPdata.UC.FatigueProcess.substeps)
//			{
//				case 0:
//					if((HPcryoGetFromSlot( PRF_HW_SLOT1, &HP, &PRF) == 0) &&
//					   (HPcryoGetFromSlot( PRF_HW_SLOT2, &HP, &PRF) == 0) &&
//				       (HPcryoGetFromSlot( PRF_HW_SLOT3, &HP, &PRF) == 0) &&
//				       (HPcryoGetFromSlot( PRF_HW_SLOT4, &HP, &PRF) == 0))
//					{	EXPdata.UC.FatigueProcess.substeps = 1;	}
//					break;
//				case 1:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT1, &HP, &PRF))
//					{
//						if(HP->status == HP_CRYO_CLEAN_UP)
//						{	if(HPcryoCleanUpStop(HP, PRF)){		EXPdata.UC.FatigueProcess.substeps = 2;	HPcryoIdle( 0, HP, PRF);	}}
//						if((TICKS_DiffTicks(t_ref) > EXP_UC_FATIGA_WAIT_SKIP_CLEANUP_STOP) && (HP->status == HP_CRYO_IDLE)){	EXPdata.UC.FatigueProcess.substeps = 2;	}
//					}
//					else{	t_ref = TICKS_GetTicks();	}
//					break;
//				case 2:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT1, &HP, &PRF))
//					{
//						if((HP->status != HP_CRYO_IDLE) && (HP->status != HP_CRYO_FATIGUE_0)){	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_CLEAN_UP){	HPcryoCleanUpStop(HP, PRF);	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status != HP_CRYO_FATIGUE_0){	HPcryoFatiga(HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_FATIGUE_0){	HPcryoFatigaStart ( HP_CRYO_FAT_1, HP, PRF);	EXPdata.UC.FatigueProcess.substeps = 3;	}
//					}
//					break;
//				case 3:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT1, &HP, &PRF))
//					{
//						if(HPcryoFatigaState ( HP, PRF) == HP_CRYO_FAT_DONE_1){	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_CHECK_VAC_HP2;	EXPdata.UC.FatigueProcess.substeps = 0;	}
//					}
//					else	EXPdata.UC.FatigueProcess.substeps = 1;
//					break;
//				default: break;
//			}
//			break;
//		case EXP_UC_FATIGUE_CHECK_VAC_HP2:
//			switch (EXPdata.UC.FatigueProcess.substeps)
//			{
//				case 0:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT2, &HP, &PRF))
//					{
//						if(HP->status == HP_CRYO_CLEAN_UP)
//						{	if(HPcryoCleanUpStop(HP, PRF)){		EXPdata.UC.FatigueProcess.substeps = 1;	HPcryoIdle( 0, HP, PRF);	}}
//						if((TICKS_DiffTicks(t_ref) > EXP_UC_FATIGA_WAIT_SKIP_CLEANUP_STOP) && (HP->status == HP_CRYO_IDLE)){	EXPdata.UC.FatigueProcess.substeps = 1;	}
//					}
//					else{	t_ref = TICKS_GetTicks();	}
//					break;
//				case 1:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT2, &HP, &PRF))
//					{
//						if((HP->status != HP_CRYO_IDLE) && (HP->status != HP_CRYO_FATIGUE_0)){	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_CLEAN_UP){	HPcryoCleanUpStop(HP, PRF);	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status != HP_CRYO_FATIGUE_0){	HPcryoFatiga(HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_FATIGUE_0){	HPcryoFatigaStart ( HP_CRYO_FAT_1, HP, PRF);	EXPdata.UC.FatigueProcess.substeps = 2;	}
//					}
//					else	EXPdata.UC.FatigueProcess.substeps = 0;
//					break;
//				case 2:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT2, &HP, &PRF))
//					{
//						if(HPcryoFatigaState ( HP, PRF) == HP_CRYO_FAT_DONE_1){	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_CHECK_VAC_HP3;	EXPdata.UC.FatigueProcess.substeps = 0;	}
//					}
//					else	EXPdata.UC.FatigueProcess.substeps = 0;
//					break;
//				default: break;
//			}
//			break;
//		case EXP_UC_FATIGUE_CHECK_VAC_HP3:
//			switch (EXPdata.UC.FatigueProcess.substeps)
//			{
//				case 0:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT3, &HP, &PRF))
//					{
//						if(HP->status == HP_CRYO_CLEAN_UP)
//						{	if(HPcryoCleanUpStop(HP, PRF)){		EXPdata.UC.FatigueProcess.substeps = 1;	HPcryoIdle( 0, HP, PRF);	}}
//						if((TICKS_DiffTicks(t_ref) > EXP_UC_FATIGA_WAIT_SKIP_CLEANUP_STOP) && (HP->status == HP_CRYO_IDLE)){	EXPdata.UC.FatigueProcess.substeps = 1;	}
//					}
//					else{	t_ref = TICKS_GetTicks();	}
//					break;
//				case 1:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT3, &HP, &PRF))
//					{
//						if((HP->status != HP_CRYO_IDLE) && (HP->status != HP_CRYO_FATIGUE_0)){	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_CLEAN_UP){	HPcryoCleanUpStop(HP, PRF);	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status != HP_CRYO_FATIGUE_0){	HPcryoFatiga(HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_FATIGUE_0){	HPcryoFatigaStart ( HP_CRYO_FAT_1, HP, PRF);	EXPdata.UC.FatigueProcess.substeps = 2;	}
//					}
//					else	EXPdata.UC.FatigueProcess.substeps = 0;
//					break;
//				case 2:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT3, &HP, &PRF))
//					{
//						if(HPcryoFatigaState ( HP, PRF) == HP_CRYO_FAT_DONE_1)
//						{	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_CHECK_VAC_HP4;	EXPdata.UC.FatigueProcess.substeps = 0;	}
//					}
//					else	EXPdata.UC.FatigueProcess.substeps = 0;
//					break;
//				default: break;
//			}
//			break;
//		case EXP_UC_FATIGUE_CHECK_VAC_HP4:
//			switch (EXPdata.UC.FatigueProcess.substeps)
//			{
//				case 0:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT4, &HP, &PRF))
//					{
//						if(HP->status == HP_CRYO_CLEAN_UP)
//						{	if(HPcryoCleanUpStop(HP, PRF)){		EXPdata.UC.FatigueProcess.substeps = 1;	HPcryoIdle( 0, HP, PRF);	}}
//						if((TICKS_DiffTicks(t_ref) > EXP_UC_FATIGA_WAIT_SKIP_CLEANUP_STOP) && (HP->status == HP_CRYO_IDLE)){	EXPdata.UC.FatigueProcess.substeps = 1;	}
//					}
//					else{	t_ref = TICKS_GetTicks();	}
//					break;
//				case 1:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT4, &HP, &PRF))
//					{
//						if((HP->status != HP_CRYO_IDLE) && (HP->status != HP_CRYO_FATIGUE_0)){	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_CLEAN_UP){	HPcryoCleanUpStop(HP, PRF);	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status != HP_CRYO_FATIGUE_0){	HPcryoFatiga(HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_FATIGUE_0){	HPcryoFatigaStart ( HP_CRYO_FAT_1, HP, PRF);	EXPdata.UC.FatigueProcess.substeps = 2;	}
//					}
//					else	EXPdata.UC.FatigueProcess.substeps = 0;
//					break;
//				case 2:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT4, &HP, &PRF))
//					{
//						if(HPcryoFatigaState ( HP, PRF) == HP_CRYO_FAT_DONE_1)
//						{	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_TRT_VAC_HP1;	EXPdata.UC.FatigueProcess.substeps = 0;	}
//					}
//					else	EXPdata.UC.FatigueProcess.substeps = 0;
//					break;
//				default: break;
//			}
//			break;
//		case EXP_UC_FATIGUE_TRT_VAC_HP1:
//			switch (EXPdata.UC.FatigueProcess.substeps)
//			{
//				case 0:
//					if((HPcryoGetFromSlot( PRF_HW_SLOT1, &HP, &PRF) == 1) &&
//					   (HPcryoGetFromSlot( PRF_HW_SLOT2, &HP, &PRF) == 1) &&
//					   (HPcryoGetFromSlot( PRF_HW_SLOT3, &HP, &PRF) == 1) &&
//					   (HPcryoGetFromSlot( PRF_HW_SLOT4, &HP, &PRF) == 1))
//					{	EXPdata.UC.FatigueProcess.substeps = 1;	}
//					break;
//				case 1:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT1, &HP, &PRF))
//					{
//						if((HP->status != HP_CRYO_IDLE) && (HP->status != HP_CRYO_FATIGUE_0)){	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_CLEAN_UP){	HPcryoCleanUpStop(HP, PRF);	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status != HP_CRYO_FATIGUE_0){	HPcryoFatiga(HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_FATIGUE_0){	HPcryoFatigaStart ( HP_CRYO_FAT_2, HP, PRF);	EXPdata.UC.FatigueProcess.substeps = 2;	}
//					}
//					else	EXPdata.UC.FatigueProcess.substeps = 3;
//					break;
//				case 2:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT1, &HP, &PRF))
//					{
//						if(HPcryoFatigaState ( HP, PRF) == HP_CRYO_FAT_DONE_2)
//						{
//							HPcryoFatigaStart ( HP_CRTYO_FAT_LAST_TEST, HP, PRF);
//							EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_TRT_VAC_HP2;
//							EXPdata.UC.FatigueProcess.substeps = 0;
//							if (time_accum != 0){	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_TST_PELTIERS;	t_ref = TICKS_GetTicks();	}
//						}
//					}
//					else	EXPdata.UC.FatigueProcess.substeps = 3;
//					break;
//				case 3:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT1, &HP, &PRF))
//					{
//						if(HP->status == HP_CRYO_CLEAN_UP)
//						{	if(HPcryoCleanUpStop(HP, PRF)){		EXPdata.UC.FatigueProcess.substeps = 1;	HPcryoIdle( 0, HP, PRF);	}}
//						if((TICKS_DiffTicks(t_ref) > EXP_UC_FATIGA_WAIT_SKIP_CLEANUP_STOP) && (HP->status == HP_CRYO_IDLE)){	EXPdata.UC.FatigueProcess.substeps = 1;	}
//					}
//					else{	t_ref = TICKS_GetTicks();	}
//					break;
//				default: break;
//			}
//			break;
//			break;
//		case EXP_UC_FATIGUE_TRT_VAC_HP2:
//			switch (EXPdata.UC.FatigueProcess.substeps)
//			{
//				case 0:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT2, &HP, &PRF))
//					{
//						if((HP->status != HP_CRYO_IDLE) && (HP->status != HP_CRYO_FATIGUE_0)){	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_CLEAN_UP){	HPcryoCleanUpStop(HP, PRF);	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status != HP_CRYO_FATIGUE_0){	HPcryoFatiga(HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_FATIGUE_0){	HPcryoFatigaStart ( HP_CRYO_FAT_2, HP, PRF);	EXPdata.UC.FatigueProcess.substeps = 1;	}
//					}
//					else	EXPdata.UC.FatigueProcess.substeps = 2;
//				case 1:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT2, &HP, &PRF))
//					{
//						if(HPcryoFatigaState ( HP, PRF) == HP_CRYO_FAT_DONE_2)
//						{
//							HPcryoFatigaStart ( HP_CRTYO_FAT_LAST_TEST, HP, PRF);
//							EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_TRT_VAC_HP3;
//							EXPdata.UC.FatigueProcess.substeps = 0;
//							if (time_accum != 0){	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_TST_PELTIERS;	t_ref = TICKS_GetTicks();	}
//						}
//					}
//					else	EXPdata.UC.FatigueProcess.substeps = 2;
//					break;
//				case 2:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT2, &HP, &PRF))
//					{
//						if(HP->status == HP_CRYO_CLEAN_UP)
//						{	if(HPcryoCleanUpStop(HP, PRF)){		EXPdata.UC.FatigueProcess.substeps = 0;	HPcryoIdle( 0, HP, PRF);	}}
//						if((TICKS_DiffTicks(t_ref) > EXP_UC_FATIGA_WAIT_SKIP_CLEANUP_STOP) && (HP->status == HP_CRYO_IDLE)){	EXPdata.UC.FatigueProcess.substeps = 0;	}
//					}
//					else{	t_ref = TICKS_GetTicks();	}
//					break;
//				default:break;
//			}
//			break;
//		case EXP_UC_FATIGUE_TRT_VAC_HP3:
//			switch (EXPdata.UC.FatigueProcess.substeps)
//			{
//				case 0:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT3, &HP, &PRF))
//					{
//						if((HP->status != HP_CRYO_IDLE) && (HP->status != HP_CRYO_FATIGUE_0)){	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_CLEAN_UP){	HPcryoCleanUpStop(HP, PRF);	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status != HP_CRYO_FATIGUE_0){	HPcryoFatiga(HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_FATIGUE_0){	HPcryoFatigaStart ( HP_CRYO_FAT_2, HP, PRF);	EXPdata.UC.FatigueProcess.substeps = 1;	}
//					}
//					else 	EXPdata.UC.FatigueProcess.substeps = 2;
//					break;
//				case 1:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT3, &HP, &PRF))
//					{
//						if(HPcryoFatigaState ( HP, PRF) == HP_CRYO_FAT_DONE_2)
//						{
//							HPcryoFatigaStart ( HP_CRTYO_FAT_LAST_TEST, HP, PRF);
//							EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_TRT_VAC_HP4;
//							EXPdata.UC.FatigueProcess.substeps = 0;
//							if (time_accum != 0){	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_TST_PELTIERS;	t_ref = TICKS_GetTicks();	}
//						}
//					}
//					else 	EXPdata.UC.FatigueProcess.substeps = 2;
//					break;
//				case 2:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT3, &HP, &PRF))
//					{
//						if(HP->status == HP_CRYO_CLEAN_UP)
//						{	if(HPcryoCleanUpStop(HP, PRF)){		EXPdata.UC.FatigueProcess.substeps = 0;	HPcryoIdle( 0, HP, PRF);	}}
//						if((TICKS_DiffTicks(t_ref) > EXP_UC_FATIGA_WAIT_SKIP_CLEANUP_STOP) && (HP->status == HP_CRYO_IDLE)){	EXPdata.UC.FatigueProcess.substeps = 0;	}
//					}
//					else{	t_ref = TICKS_GetTicks();	}
//					break;
//				default: break;
//			}
//			break;
//		case EXP_UC_FATIGUE_TRT_VAC_HP4:
//			switch (EXPdata.UC.FatigueProcess.substeps)
//			{
//				case 0:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT4, &HP, &PRF))
//					{
//						if((HP->status != HP_CRYO_IDLE) && (HP->status != HP_CRYO_FATIGUE_0)){	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_CLEAN_UP){	HPcryoCleanUpStop(HP, PRF);	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status != HP_CRYO_FATIGUE_0){	HPcryoFatiga(HP, PRF);	HPcryoFatigaStop ( HP, PRF);	}
//						else if(HP->status == HP_CRYO_FATIGUE_0){	HPcryoFatigaStart ( HP_CRYO_FAT_2, HP, PRF);	EXPdata.UC.FatigueProcess.substeps = 1;	}
//					}
//					else 	EXPdata.UC.FatigueProcess.substeps = 2;
//					break;
//				case 1:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT4, &HP, &PRF))
//					{
//						if(HPcryoFatigaState ( HP, PRF) == HP_CRYO_FAT_DONE_2)
//						{
//							HPcryoFatigaStart ( HP_CRTYO_FAT_LAST_TEST, HP, PRF);
//							EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_TST_PELTIERS;
//							EXPdata.UC.FatigueProcess.substeps = 0;
//							t_ref = TICKS_GetTicks();
//							if (time_accum != 0){	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_TST_PELTIERS;	}
//						}
//					}
//					else 	EXPdata.UC.FatigueProcess.substeps = 2;
//					break;
//				case 2:
//					if(HPcryoGetFromSlot( PRF_HW_SLOT4, &HP, &PRF))
//					{
//						if(HP->status == HP_CRYO_CLEAN_UP)
//						{	if(HPcryoCleanUpStop(HP, PRF)){		EXPdata.UC.FatigueProcess.substeps = 0;	HPcryoIdle( 0, HP, PRF);	}}
//						if((TICKS_DiffTicks(t_ref) > EXP_UC_FATIGA_WAIT_SKIP_CLEANUP_STOP) && (HP->status == HP_CRYO_IDLE)){	EXPdata.UC.FatigueProcess.substeps = 0;	}
//					}
//					else{	t_ref = TICKS_GetTicks();	}
//					break;
//				default: break;
//			}
//			break;
//		case EXP_UC_FATIGUE_TST_PELTIERS:
//			if((HPcryoGetFromSlot( PRF_HW_SLOT1, &HP, &PRF) == 1) &&
//			   (HPcryoGetFromSlot( PRF_HW_SLOT2, &HP, &PRF) == 1) &&
//			   (HPcryoGetFromSlot( PRF_HW_SLOT3, &HP, &PRF) == 1) &&
//			   (HPcryoGetFromSlot( PRF_HW_SLOT4, &HP, &PRF) == 1))
//			{
				
//				diff_t = TICKS_DiffTicks(t_ref);
//				EXPdata.UC.FatigaTime = diff_t + time_accum;
				
//				if(EXP_UCfatigaVerif()){	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_FAIL;	EXP_UCfatigaSetErrorValues();	}
//				if(EXPdata.UC.FatigaTime>EXP_UC_FATIGA_TRT_TEST_TIME){	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_DONE;	}
//			}
//			else
//			{
//				time_accum += diff_t;
//				if(HPcryoGetFromSlot( PRF_HW_SLOT1, &HP, &PRF) == 0){	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_TRT_VAC_HP1;	EXPdata.UC.FatigueProcess.substeps = 1;	}
//				if(HPcryoGetFromSlot( PRF_HW_SLOT2, &HP, &PRF) == 0){	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_TRT_VAC_HP2;	EXPdata.UC.FatigueProcess.substeps = 0;	}
//				if(HPcryoGetFromSlot( PRF_HW_SLOT3, &HP, &PRF) == 0){	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_TRT_VAC_HP3;	EXPdata.UC.FatigueProcess.substeps = 0;	}
//				if(HPcryoGetFromSlot( PRF_HW_SLOT4, &HP, &PRF) == 0){	EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_TRT_VAC_HP4;	EXPdata.UC.FatigueProcess.substeps = 0;	}
//			}
//			break;
//		case EXP_UC_FATIGUE_DONE:
//			for(i=PRF_HW_SLOT1;i<=PRF_HW_SLOT4;i++){	if(HPcryoGetFromSlot( i, &HP, &PRF)){	HPcryoIdle( 0, HP, PRF);	HPcryoFatigaStop ( HP, PRF);}	}
//			break;
//		case EXP_UC_FATIGUE_FAIL:
//			EXPdata.UC.FatigueProcess.step = EXP_UC_FATIGUE_DONE;
//			break;
//		default: break;
//	}
}

uint32 EXP_UCerroresSAT(uint8 Perif)
{
//	uint32 err_code_HP;
//	errors_messages err_msg_HP;
//	uint32 warning_code_HP;
//	warning_messages warning_msg_HP;
	
//	if((Perif<Manip1)||(Perif>Maq)) return 0;
	
//	if (ERR_interface_msg(Perif, &err_code_HP, &err_msg_HP, &warning_code_HP, &warning_msg_HP) == 0)
//	{
//		if((err_code_HP == ((Error_HPctrlMaxTemp1+(Perif-1))+(1000*Perif)))  	|| 		/*Filtramos los errores que queremos que se muestren en la pantalla de SAT*/
//		   (err_code_HP == ((Error_HPctrlMinTemp1+(Perif-1))+(1000*Perif)))  	||
//		   (err_code_HP == ((Err_SeguridadFrioMan1+(Perif-1))+(1000*Perif))) 	||
//		   (err_code_HP == ((Error_HPctrlDeltaTempMax1+(Perif-1))+(1000*Perif)))||
//		   (err_code_HP == ((Error_BusAlarma_Seta)+(1000*Perif))))
//		{
//			return err_code_HP;
//		}
//	}
	return 0;
}

void EXPdeshabilitarPeriferico(uint8 Periferico)	/*Periferico va de 1 a 4*/
{
	uint16 buffer;
	uint16 mask;
	
	mask = 1<<Periferico;
	mask = ~mask;

	EXPcomOrder( EXP_PROTMST_COM_OP_READ, EXP_PROTMST_GPERIF_MEM_ID, 
				 EXP_PERIFERICOS_HABILITADOS, 2, (uint8*)&buffer);
	
	buffer = buffer&mask;
	EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_GPERIF_MEM_ID, 
				 EXP_PERIFERICOS_HABILITADOS, 2, (uint8*)&buffer);
}

void EXPhabilitarPeriferico(uint8 Periferico)		/*Periferico va de 1 a 4*/
{
	uint16 buffer;
	uint16 mask;
	
	mask = 1<<Periferico;

	EXPcomOrder( EXP_PROTMST_COM_OP_READ, EXP_PROTMST_GPERIF_MEM_ID, 
				 EXP_PERIFERICOS_HABILITADOS, 2, (uint8*)&buffer);
	
	buffer = buffer|mask;
	EXPcomOrder( EXP_PROTMST_COM_OP_WRITE, EXP_PROTMST_GPERIF_MEM_ID, 
				 EXP_PERIFERICOS_HABILITADOS, 2, (uint8*)&buffer);
}

void EXP_UCperifNEWlabel (uint8 periferico, uint8 label, uint32 TRTtime)	/*Periferico va de 1 a 4 (Restamos uno al periferico para ajustar su dirección en el vector de datos)*/
{
//	EXP_UCreuseLabelData[periferico-1].label_type = label;
//	EXP_UCreuseLabelData[periferico-1].time_ref_read = TICKS_GetTicks();
//	EXP_UCreuseLabelData[periferico-1].time_trt_stop = TICKS_GetTicks();
//	EXP_UCreuseLabelData[periferico-1].time_trt_remain = TRTtime;
//	EXP_UCreuseLabelData[periferico-1].allowReuseLabel = 0;
}

void EXP_UCupdateTRTtimeReuseLabel (uint8 periferico, uint32 TRTtime)	/*Periferico va de 1 a 4 (Restamos uno al periferico para ajustar su dirección en el vector de datos)*/
{
//	EXP_UCreuseLabelData[periferico-1].time_trt_remain = TRTtime;
//	EXP_UCreuseLabelData[periferico-1].time_trt_stop = TICKS_GetTicks();
}

uint8 EXP_UCreuseLabel (uint8 periferico, uint8 labelRq)	/*Periferico va de 1 a 4 (Restamos uno al periferico para ajustar su dirección en el vector de datos)*/
{
//	if((TICKS_DiffTicks(EXP_UCreuseLabelData[periferico-1].time_trt_stop) > EXP_UC_REUSE_LABEL_STOP_LIMIT) ||
//	   (TICKS_DiffTicks(EXP_UCreuseLabelData[periferico-1].time_ref_read) > EXP_UC_REUSE_LABEL_TIME_LIMIT) ||
//	   (EXP_UCreuseLabelData[periferico-1].time_trt_remain < EXP_UC_ONE_SEC))
//	{
//		EXP_UCreuseLabelData[periferico-1].label_type = HP_CRYO_LABEL_UNDEFINED;
//		EXP_UCreuseLabelData[periferico-1].time_trt_remain = 0;
//		EXP_UCreuseLabelData[periferico-1].allowReuseLabel = 0;
//		return 0;
//	}
	
//	if(((EXP_UCreuseLabelData[periferico-1].label_type == labelRq) ||
//		(EXP_UCreuseLabelData[periferico-1].label_type == HP_CRYO_LABEL_DM)) &&
//	   (EXP_UCreuseLabelData[periferico-1].time_trt_remain > 0))
//	{
//		EXP_UCreuseLabelData[periferico-1].allowReuseLabel = 1;
//		return 1;
//	}
	
//	EXP_UCreuseLabelData[periferico-1].allowReuseLabel = 0;
	return 0;
}

uint8 EXP_UCreuseLabelAllow(uint8 periferico)	/*Periferico va de 1 a 4 (Restamos uno al periferico para ajustar su dirección en el vector de datos)*/
{
	return (EXP_UCreuseLabelData[periferico-1].allowReuseLabel & EXPdata.UC.Config_Param.data.ModeRecicleLabel);
}

uint32 EXP_UCreuseLabelTRTtime(uint8 periferico)	/*Periferico va de 1 a 4 (Restamos uno al periferico para ajustar su dirección en el vector de datos)*/
{
	return EXP_UCreuseLabelData[periferico-1].time_trt_remain;
}

uint8 EXP_UCreuseLabelType (uint8 periferico)	/*Periferico va de 1 a 4 (Restamos uno al periferico para ajustar su dirección en el vector de datos)*/
{
	return EXP_UCreuseLabelData[periferico-1].label_type;
}

/*V7790 - GPRS get MCC*/
void EXP_UC_MCCmanage (void)
{
//	static uint8 first_time_flag = 0;
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	//cHPcryoStatus HPstatus;
//	//cHPcryoTreatmentStatus HP_TRTstatus;
//	uint8 HPindex;
//	uint8 CountNoTRT;
//	returnstatus_t retAux;
	
//	static uint32 refTime = 0;
//	CountNoTRT = 0;
	
//	//if(((AppGPRS_GetMCCnum(1) == 0) && (TICKS_DiffTicks(refTime) > EXP_UC_LOOP_TIME_GETTING_MCC)) || (first_time_flag == 0))		//Si ya se tiene un valor valido del MCC o no han pasado 15 minutos desde la ultima medida, no se ejecuta
//	if(((appGPRS_get_signal() != 1) && (TICKS_DiffTicks(refTime) > EXP_UC_LOOP_TIME_GETTING_MCC)) || (first_time_flag == 0))		//Si ya se tiene un valor valido del MCC o no han pasado 15 minutos desde la ultima medida, no se ejecuta
//	{
//		/*for(HPindex = 1; HPindex <= EXP_UC_NUM_HANDPIECES; HPindex++)	//Se recorren los 4 aplicadores
//		{
//			if(HPcryoGetFromSlot( HPindex, &HP, &PRF))					//Se comprueban si estan conectados
//			{
//				//HPstatus = HPcryoGetStatus(&HP, &PRF);
//				//HP_TRTstatus = HPcryoTrtStatus(&HP, &PRF);					//Se mira si el estado es fuera de tratamiento
//				if(HPcryoGetStatus(HP, PRF) != HP_CRYO_TREATMENT){CountNoTRT++;}
//				//if((HP_TRTstatus == HP_CRYO_TREATMENT_DONE) || (HP_TRTstatus == HP_CRYO_TREATMENT_FAIL)){CountNoTRT++;}
//			}
//			else{CountNoTRT++;}
//		}
		
//		if(CountNoTRT == EXP_UC_NUM_HANDPIECES)		//Si ningun aplicador esta en tratamiento
//		{
//			retAux = AppGPRS_Connect_Get_MCC();		//Se ejecuta el proceso de obtencion del MCC
//			if((retAux == SUCCESS) || (retAux == ERROR))		//Cuando se consigue de forma exitosa o por error se resetea la referencia de tiempo
//			{
//				refTime = TICKS_GetTicks();
//				first_time_flag = 1;
//			}
//		}*/
//		//#JM_GPRS Durante el tratamiento, se siguen solicitando intentos de lectura
//		retAux = AppGPRS_Connect_Get_MCC();		//Se ejecuta el proceso de obtencion del MCC
//		if((retAux == SUCCESS) || (retAux == ERROR))		//Cuando se consigue de forma exitosa o por error se resetea la referencia de tiempo
//		{
//			refTime = TICKS_GetTicks();
//			first_time_flag = 1;
//		}
//	}
}

void saveMMC(uint8 conf, uint16 *toSaveMCC)
{
//	EXPdata.UC.Config_Param.data.GPRS_iniciado = conf;
//	EXPdata.UC.Config_Param.data.MCC[0] = toSaveMCC[0];
//	EXPdata.UC.Config_Param.data.MCC[1] = toSaveMCC[1];
//	EXPdata.UC.Config_Param.data.MCC[2] = toSaveMCC[2];
//	EXPdata.UC.Config_Param.data.MCC[3] = toSaveMCC[3];
//	EXPdata.UC.Config_Param.data.MCC[4] = toSaveMCC[4];
//	EXPdata.UC.Config_Param.data.MCC[5] = toSaveMCC[5];
//	EXPdata.UC.Config_Param.data.MCC[6] = toSaveMCC[6];
//	EXPdata.UC.Config_Param.data.MCC[7] = toSaveMCC[7];
//	EXPdata.UC.Config_Param.data.MCC[8] = toSaveMCC[8];
//	EXPdata.UC.Config_Param.data.MCC[9] = toSaveMCC[9];
//	while(BOOT_SaveConfigParamSerialFlash(EXPdata.UC.Config_Param.vector)!= BOOT_SerialFlash_EscrituraCorrecta );
}

