/*
 * boot.h
 *
 *  Created on: Oct 18, 2018
 *      Author: ingenieria9
 */

#ifndef LOADDATA_H_

#define LOADDATA_H_


/*** DEFINE ***/
#ifdef VERIFMAIN_H_
	#define CONFIG_PARAM_SERIAL_FLASH_ADDR		0x4000		//se utiliza para almacenar configuracion en Modo Verificacion. FW (VerifMain)
#else
	#define CONFIG_PARAM_SERIAL_FLASH_ADDR		0x3000		//direccion de configuracion en modo normal. FW (Main)
#endif
#define CONFIG_PARAM_SERIAL_FLASH_SIZE		0x20 // 9 originales + 21 = 30; 0x20 = 32. Aun queda dos bytes libres //0x35 //#JM_GPRS V7790 previamente 0x20 + 21 Bytes (0x15) para las posiciones del MCC 

#define BOOT_POSICIO_FW_EXT_MEMO 0x3000
#define BOOT_MAX_TAMANY_EXT_MEMO 0x100000

#define BOOT_SIZE_DATAPARAMETERS 			0x5
#define BOOT_SIZE_DATAPARAMETERSSecurity	11

//Hasta Version V770
//#define NandBlockWriteCCN  1200//0
//#define NandBlockWriteLUT  1600//400

//#define NandBlockSecurityCNN  1601//401	//401	// MODIFICADO SERGIO
//#define NandBlockSecurityLUT  2001//801	//801	// MODIFICADO SERGIO

//Posterior a Version V770
#define	NandBlockWriteINDEX	    ( 0 )
#define NandPageWriteINDEX		( 0 )
#define NandCodeZone_CCNLUT		( 0x00FFAA55 )

#define NandBlockWriteCCN_ORG  ( 1   )
#define NandBlockWriteLUT_ORG  ( 401 )

#define NandBlockWriteCCN_Z0  ( NandBlockWriteCCN_ORG )
#define NandBlockWriteLUT_Z0  ( NandBlockWriteLUT_ORG )
#define NandBlockWriteCCN_Z1  ( 402 )
#define NandBlockWriteLUT_Z1  ( 802 )
#define NandBlockWriteCCN_Z2  ( 803 )
#define NandBlockWriteLUT_Z2  (1203 )
#define NandBlockWriteCCN_Z3  (1204 )
#define NandBlockWriteLUT_Z3  (1604 )

#define NandBlockSecurityCNN   (1605)
#define NandBlockSecurityLUT   (2005)

#define SectorSaveSerialFlash  			0x1000
#define SectorSaveSerialFlashSecurity	0x2000

#define SizeDDRdataCCN  0x3200000
#define SizeDDRdataLUT  4096//2048

#define TIME_DETECTED_USB  5000

/*** INCLUDES ***/

//#include "GUI/K70_GUI.h"

#include "stddef.h"
#include "GeneralDefines.h"
//#include "../../Generated_Code/NFC1.h"

//#include "Events.h"

typedef uint8 *tK70_DDRdataPtr; //#include "DDR/DDR.h"

#include "../../Generated_Code/poll.h"

//#include "../MSD/MSD.h"

#include <math.h>

//#include "../Ticks/Ticks.h"

//#include "../ExternalFlash/ExternalFlash.h"

//#include "../WATCH_DOG/watchdog.h"

typedef enum
{
	BOOT_STATUS_CHEKSectorsNand,
	BOOT_STATUS_IDLE ,
	BOOT_STATUS_INIT ,
	BOOT_STATUS_READY ,
	BOOT_STATUS_ENABLE,
	BOOT_STATUS_DISABLE ,
	BOOT_STATUS_DETECTING,
	BOOT_STATUS_LOADLUT,
	BOOT_STATUS_LOADCCN,
	BOOT_STATUS_READLUT,
	BOOT_STATUS_READCCN,
	BOOT_STATUS_LOADBOOTLOADER,
	BOOT_STATUS_LOADCCNANDLUTSecuity,
	BOOT_STATUS_FINISH ,
	BOOT_STATUS_NO_USB,
	BOOT_STATUS_CHANGE_INDEX_LUT,
	
}Boot_status_t;

typedef enum
{
	BOOT_SerialFlash_Running,
	BOOT_SerialFlash_ErrorEscritura,
	BOOT_SerialFlash_EscrituraCorrecta,
	BOOT_SerialFlash_ErrorSize,
	BOOT_SerialFlash_ErrorLectura,
	BOOT_SerialFlash_LecturaCorrecta,
	
}Boot_SerialFlashConfig_t;

typedef enum
{
	BootIDLE ,
	BootRUNNING,
	BootERROR,
	BootSUCCESS,
	NOTFOUNDFILE,
	BootCheckSectorNand,
	BootErrorLUTCCN,
	
}BOOTreturnstatus_t;

typedef enum
{
	Check_Size,
	CalculateChecksum,
	PrepareBuffer,
	EraseBlock,
	WriteSerialFlash,
	
	EvaluateChecksum,
	ReadSerialFlash,
	InicializeConfig,
	
}BOOT_ConfigData_motor_SerialFlash;

//*** Funciones Públicas ***//

// Inicialización BOOT. Inicializa la external flash y la nand

void BOOT_Init(tK70_DDRdataPtr DDRdata);

// Copia de la Nand A la DDR
/* Inpt: srcCNN: Puntero con los valores de las imágenes
 * 			srcLUT: Puntero con los valores de las imágenes

	Outp: Resultado de la copia
*/
returnstatus_t BOOT_CCNandLUTfromNandToDDR(uint8 **srcCCN , uint8  **srcLUT);

// Habilitar la copia o lectura de los archivos.

void BOOT_Enable(void);

// Desabilitar la copia o lectura de los archivos.

void BOOT_Disable(void);

// Copia de los archivos CCN y LUT de la memoria correcta

void BOOT_REPARELUTandCCN();

// Motor Principal del motor . Outp: Estado del motor.
BOOTreturnstatus_t BOOT_Motor();

// Escritura en la Serial Flash de los valores indicado:
/*	Inpt: Adress: Dirreción a escribir en la serial
 * 			nBytes: número de bytes que se quieren escribir
 * 			Buffer:	Buffer con los datos a escribir
 * Outpt: Resultado de la escritura.
 * */
Boot_SerialFlashConfig_t BOOT_ConfigSetSerialFlash(uint32 Address, uint8 nBytes, uint8 *BuffSerialFlash);

// Lectura en la Serial Flash de los valores indicado:
/*	Inpt: Adress: Dirreción a escribir en la serial
 * 			nBytes: número de bytes que se quieren escribir
 * 			Buffer:	Buffer con los datos a escribir
 * Outpt: Lectura de la escritura.
 * */

Boot_SerialFlashConfig_t BOOT_ConfigGetSerialFlash(uint32 Address, uint8 nBytes, uint8 *BuffSerialFlash);

/*Boot modo escritura*/
void BOOT_Write(void);


/*Boot modo lectura*/
void BOOT_Read(void);

//Lectura de la zona de CCN y LUT
extern void BOOT_LoadZone_CCNLUT ( void );

Boot_SerialFlashConfig_t BOOT_SaveConfigParamSerialFlash (uint8 *Buff);
Boot_SerialFlashConfig_t BOOT_LoadConfigParamSerialFlash (uint8 *Buff);


#endif /* LOADDATA_H_ */
