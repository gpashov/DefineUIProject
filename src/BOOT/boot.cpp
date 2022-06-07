/*
 * LoadData.c
 *
 *  Created on: Oct 18, 2018
 *      Author: ingenieria9
 */

#include <stdio.h>
#include <string.h>
#include "PE_Types.h"
#include "boot.h"
//#include "Cpu.h"
//#include "Utils.h"

//#include "../UART/UART.H"
//#include "../Generated_Code/HAL_UART_2.h"

//#include "../ExternalNANDFlash/ExternalNANDFlash.h"

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

#ifndef NFC_GetPageAddressFromBlockAddressAndPageOffset
#define NFC_GetPageAddress(_BlockAddress_, _PageOffset_)   ((_BlockAddress_)*64 + _PageOffset_)
#endif


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

/*Variables Globales*/

const uint32 pageNumberCNNN = 25600; //400*64
const uint32 pageNumberLUT = 64;//= 2;	/* MODIFICADO SERGIO */
const uint32 blockEraseCCN = 400;
const uint32 blockEraseLUT = 1;//= 1;	/* MODIFICADO SERGIO */
uint32 ReadOrWrite;

//variable de bloque de inicio de LUT y CCN
//Estos valores se modifican en caso de bloques erroneos
uint32 NandBlockWriteCCN = NandBlockWriteCCN_ORG;
uint32 NandBlockWriteLUT = NandBlockWriteLUT_ORG;
uint32 NandBlockWriteCCN_CPY = NandBlockWriteCCN_ORG;	//Variables copia, se utiliza a la hora de Guardar la nueva Zona de grabacion de CCN 
uint32 NandBlockWriteLUT_CPY = NandBlockWriteLUT_ORG;

enum
{
	BOOT_MOTOR_WRITE,
	BOOT_MOTOR_READ,
};

enum
{
	BOOT_CCN_Init,
	BOOT_CCN_Erase,
	BOOT_CCN_OpenFile,
	BOOT_CCN_WriteFromUSB,
	BOOT_CCN_Close,
	BOOT_CCN_ErrorNotFoundFile,
	BOOT_CCN_ErrorWrite,
};

enum
{
	BOOT_LUT_Init,
	BOOT_LUT_Erase,
	BOOT_LUT_OpenFile,
	BOOT_LUT_WriteFromUSB,
	BOOT_LUT_Close,
	BOOT_LUT_ErrorNotFoundFile,
	BOOT_LUT_ErrorWrite,
};

enum
{
	BOOT_BOOTLOADER_Init,
	BOOT_BOOTLOADER_ExistFile,
	BOOT_BOOTLOADER_OpenFile,
	BOOT_BOOTLOADER_CheckSerialFlash,
	BOOT_BOOTLOADER_EraseSerialFlash,
	BOOT_BOOTLOADER_Write,
	BOOT_BOOTLOADER_CheckWriteAndRead,
	BOOT_BOOTLOADER_SetNewFir,
	BOOT_BOOTLOADER_Close,
	BOOT_BOOTLOADER_ErrorNotFoundFile,
	BOOT_BOOTLOADER_ErrorUpdate,
};

/*Funciones Privadas*/

BOOTreturnstatus_t BOOTbootloaderUpdate();
void BOOT_SaveDataLTU(uint32 blockErase, uint32 blockWrite, uint32 pageNumber);
BOOTreturnstatus_t BOOT_SaveDataCNN(uint32 blockWrite, uint32 pageNumber);
BOOTreturnstatus_t BOOTreadLUT(uint32 NandBlockLUT );
BOOTreturnstatus_t BOOTReadCCN(uint32 NandBlockCCN);
void CNNandLUTCopySecurity(uint32 blockToReadCCN, uint32 pageNumberToReadCCN, uint32 blockCopySecurityWriteCNN,uint32 blockToReadLUT, uint32 pageNumberToReadLUT,  uint32 blockCopySecurityWriteLUT );
BOOTreturnstatus_t BOOTWriteLUT(void );
BOOTreturnstatus_t BOOTWriteCCN(void);

/* Variables globales*/

Boot_status_t BootStatus;
int DataCompare(uint8_t  s1[], uint8_t s2[] );
static uint32 SectorToRead=0;
static uint32 SectorToWrite=0;
static uint32 SectorToRead2=0;
static uint32 SectorToWrite2=0;
uint32 motorGetConfigSerialFlash=0;
uint8 motorSetConfigSerialFlash=0;
uint8* BuffDataSeriaFlash=0; 
extern uint8 flagInitCopyFilesFromNand;
//uint8_t  WritePageBufferCNN[2048] __attribute__ ((aligned (4)));
//uint8_t  ReadPageBufferCNN[2048] __attribute__ ((aligned (4)));
//uint8_t  WritePageBufferLTU[2048]   __attribute__ ((aligned (4)));
//uint8_t  ReadPageBufferLTU[2048]   __attribute__ ((aligned (4)));
uint8_t  WritePageBuffer[2048] __attribute__ ((aligned (8)));
uint8_t  ReadPageBuffer[2048] __attribute__ ((aligned (8)));
//uint8_t  WritePageBufferINT[81] __attribute__ ((aligned (4)));
//uint8_t  ReadPageBufferINT[81]  __attribute__ ((aligned (4)));
//uint32 pageNumberCNN=0;

//#define BOOT_USE_NFC_DRIVER
#ifdef BOOT_USE_NFC_DRIVER
//extern MyNfcInfo_Struct  NfcInfo;
#else
#endif
#define BOOT_CONVERT_NAND_BLOCK_2_ADDR(x)	(x*EXTERNAL_NAND_FLASH_PAGES_BLOCK*EXTERNAL_NAND_FLASH_PAGE_SIZE)
#define BOOT_CONVERT_NAND_PAGE_2_ADDR(x)	(x*EXTERNAL_NAND_FLASH_PAGE_SIZE)


uint8 AppMotorCNN=0;
uint32 l;
tK70_DDRdataPtr DDRdataBoot;

void BOOT_Init(tK70_DDRdataPtr DDRdata)
{
	DDRdataBoot= DDRdata;
	//NfcInfo.hNfc = NFC1_Init(&NfcInfo);
	//EXTFLASH_Init();
	BootStatus= BOOT_STATUS_CHEKSectorsNand;
}

void BOOT_Enable(void)
{	
	BootStatus= BOOT_STATUS_INIT;	
}

void BOOT_Read(void) //OT
{
	ReadOrWrite = BOOT_MOTOR_READ;
}

void BOOT_Write(void) //OT
{
	ReadOrWrite = BOOT_MOTOR_WRITE;
}

void BOOT_Disable()
{		
	BootStatus= BOOT_STATUS_DISABLE;	
}


returnstatus_t BOOT_WriteFlashZone_CCNLUT ( uint32 block_ccn, uint32 block_lut  )   {
	
	uint8* ptr;
	uint32 code  = NandCodeZone_CCNLUT;
	returnstatus_t ret = SUCCESS;
	uint32_t aux;

//#ifdef BOOT_USE_NFC_DRIVER
//	LDD_TError  result;
//#endif
	
//	ptr = ReadPageBuffer;
	
//	memset(ReadPageBuffer, 0xFF, sizeof(ReadPageBuffer));

//	ptr[0] = code & 0xFF;
//	ptr[1] = (code>>8)&0xFF;
//	ptr[2] = (code>>16)&0xFF;
//	ptr[3] = (code>>24)&0xFF;
	
//	ptr[4] = block_ccn & 0xFF;
//	ptr[5] = (block_ccn>>8)&0xFF;
//	ptr[6] = (block_ccn>>16)&0xFF;
//	ptr[7] = (block_ccn>>24)&0xFF;
	
//	ptr[8] = block_lut & 0xFF;
//	ptr[9] = (block_lut>>8)&0xFF;
//	ptr[10] = (block_lut>>16)&0xFF;
//	ptr[11] = (block_lut>>24)&0xFF;
	
//#ifdef BOOT_USE_NFC_DRIVER
//	NfcInfo.CmdPending = TRUE;
//	result = NFC1_EraseBlocks(NfcInfo.hNfc, 0, NandBlockWriteINDEX, 1);  //
//	while(NfcInfo.CmdPending){}; // Esperamos hasta  que el dispositivo este operativo.
//#else
//	aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(NandBlockWriteINDEX);
//	do
//	{
//		ret = EXTNAND_EraseBlocks(aux ,1);
//	}while(ret == RUNNING);
//#endif
	
//#ifdef BOOT_USE_NFC_DRIVER
//	NfcInfo.CmdPending = TRUE;
//	result = NFC1_WritePages(NfcInfo.hNfc, 0, NFC_GetPageAddress(NandBlockWriteINDEX, NandPageWriteINDEX), 1 , ReadPageBuffer);
//	while(NfcInfo.CmdPending){}; // Esperamos hasta  que el dispositivo este operativo.
//#else
//	aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(NandBlockWriteINDEX);
//	aux+= BOOT_CONVERT_NAND_PAGE_2_ADDR(NandPageWriteINDEX);
//	do
//	{
//		ret = EXTNAND_WriteBytes(aux, ReadPageBuffer, EXTERNAL_NAND_FLASH_PAGE_SIZE);
//	}while(ret == RUNNING);
//#endif
	
//	memset(WritePageBuffer, 0xFF, sizeof(WritePageBuffer));
	
//#ifdef BOOT_USE_NFC_DRIVER
//	NfcInfo.CmdPending = TRUE;
//	result = NFC1_ReadPages(NfcInfo.hNfc, 0, NFC_GetPageAddress(NandBlockWriteINDEX, NandPageWriteINDEX), 1 , WritePageBuffer);
//	while(NfcInfo.CmdPending){}; // Esperamos hasta  que el dispositivo este operativo.
//#else
//	aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(NandBlockWriteINDEX);
//	aux += BOOT_CONVERT_NAND_PAGE_2_ADDR(NandPageWriteINDEX);
//	do
//	{
//		ret = EXTNAND_ReadBytes(aux, WritePageBuffer, EXTERNAL_NAND_FLASH_PAGE_SIZE);
//	}while(ret == RUNNING);
//#endif
	
//	if ( memcmp( ReadPageBuffer, WritePageBuffer, 12 )==0 ) {   //comparamos si se ha copiado bien
//		TEST_PrintInfo("SAVE CCN_LUT ZONE OK\r\n");
//	}
//	else {
//		TEST_PrintInfo("ERROR CCN_LUT ZONE\r\n");
//	}
	
	return(ret);
}


returnstatus_t BOOT_ReadFlashZone_CCNLUT ( void )  {
	
	uint32 code  = 0;
	uint32 ccn_block = 0;
	uint32 lut_block = 0;
	returnstatus_t ret = SUCCESS;
	uint32_t aux;
	
//#ifdef BOOT_USE_NFC_DRIVER
//	LDD_TError  result;
//#endif
	
//	memset(ReadPageBuffer, 0x00, sizeof(ReadPageBuffer));
	
//#ifdef BOOT_USE_NFC_DRIVER
//	NfcInfo.CmdPending= TRUE;
//	result = NFC1_ReadPages(NfcInfo.hNfc, 0, NFC_GetPageAddress(NandBlockWriteINDEX, NandPageWriteINDEX), 1 , ReadPageBuffer);
//	while(NfcInfo.CmdPending){};
//#else
//	aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(NandBlockWriteINDEX);
//	aux+= BOOT_CONVERT_NAND_PAGE_2_ADDR(NandPageWriteINDEX);
//	do
//	{
//		ret = EXTNAND_ReadBytes(aux,ReadPageBuffer, EXTERNAL_NAND_FLASH_PAGE_SIZE);
//	}while(ret == RUNNING);
//#endif

//	code = ( (uint32)ReadPageBuffer[0] | ( ((uint32)ReadPageBuffer[1])<<8) | (((uint32)ReadPageBuffer[2])<<16) | (((uint32)ReadPageBuffer[3])<<24) );
	
//	if (code == NandCodeZone_CCNLUT ) {   //comprobamos si la flash esta iniciada
//		ccn_block = ( (uint32)ReadPageBuffer[4] | ( ((uint32)ReadPageBuffer[5])<<8) | (((uint32)ReadPageBuffer[6])<<16) | (((uint32)ReadPageBuffer[7])<<24) );
//		lut_block = ( (uint32)ReadPageBuffer[8] | ( ((uint32)ReadPageBuffer[9])<<8) | (((uint32)ReadPageBuffer[10])<<16) | (((uint32)ReadPageBuffer[11])<<24) );
		
		
//		if ( ((ccn_block == NandBlockWriteCCN_Z0)&&(lut_block == NandBlockWriteLUT_Z0) ) ||    //comprobamos si la zona es correcta
//			 ((ccn_block == NandBlockWriteCCN_Z1)&&(lut_block == NandBlockWriteLUT_Z1) ) ||
//			 ((ccn_block == NandBlockWriteCCN_Z2)&&(lut_block == NandBlockWriteLUT_Z2) ) ||
//			 ((ccn_block == NandBlockWriteCCN_Z3)&&(lut_block == NandBlockWriteLUT_Z3) ) )
//		{
//			NandBlockWriteCCN = ccn_block;
//			NandBlockWriteLUT = lut_block;
//			NandBlockWriteCCN_CPY = ccn_block;
//			NandBlockWriteLUT_CPY = lut_block;
//			TEST_PrintInfo("LOAD CCN_LUT ZONE OK\r\n");
//			//if ( ( NandBlockWriteCCN != NandBlockWriteCCN_CPY)||( NandBlockWriteLUT != NandBlockWriteLUT_CPY) ) {
//			//	BOOT_WriteFlashZone_CCNLUT(NandBlockWriteCCN, NandBlockWriteLUT);
//			//}
			
//		}
//		else {
//			ret = ERROR;
//			NandBlockWriteCCN = NandBlockWriteCCN_ORG;  //Valores por defecto
//			NandBlockWriteLUT = NandBlockWriteLUT_ORG;
//			TEST_PrintInfo("ERROR CCN_LUT ZONE CORRUCT\r\n");
//			//BOOT_WriteFlashZone_CCNLUT(NandBlockWriteCCN, NandBlockWriteLUT);  //Grabamos valores por defecto
//		}
//	}
//	else {  //Flash no iniciada
//		ret = ERROR;
//		NandBlockWriteCCN = NandBlockWriteCCN_ORG;  //valores por defecto
//		NandBlockWriteLUT = NandBlockWriteLUT_ORG;
//		TEST_PrintInfo("INITIALIZE CCN_LUT ZONE\r\n");
//		//BOOT_WriteFlashZone_CCNLUT(NandBlockWriteCCN, NandBlockWriteLUT);  //Grabamos valores por defecto
//	}
	
	return(ret);
}

void BOOT_LoadZone_CCNLUT ( void ) {

//	switch ( BOOT_ReadFlashZone_CCNLUT() ) {
//	case SUCCESS:
//		break;
		
//	case ERROR:
//		BOOT_WriteFlashZone_CCNLUT(NandBlockWriteCCN, NandBlockWriteLUT);  //Grabamos valores por defecto
//		break;
//	}
}

void BOOT_SaveZone_CCNLUT ( )
{
//   if ( ( NandBlockWriteCCN != NandBlockWriteCCN_CPY)||( NandBlockWriteLUT != NandBlockWriteLUT_CPY) ) {
//	   BOOT_WriteFlashZone_CCNLUT(NandBlockWriteCCN, NandBlockWriteLUT);
//	   NandBlockWriteCCN_CPY = NandBlockWriteCCN;
//	   NandBlockWriteLUT_CPY = NandBlockWriteLUT;
//   }
//   else {
//	   TEST_PrintInfo("ZONE CCN_LUT NOT CHANGE\r\n");
//   }
}


returnstatus_t BOOT_CCNandLUTfromNandToDDR(uint8 **srcCCN , uint8  **srcLUT )
{
//#ifdef BOOT_USE_NFC_DRIVER
//	LDD_TError  Result;
//#endif
//	uint32_t aux;
//	uint32_t temp;
//	uint32 blockNumberLTU= NandBlockWriteLUT;
//	uint32 blockNumberCNN= NandBlockWriteCCN;
//	uint8 ptu8BOOT_dataSet[60];
//	returnstatus_t StatusCCNandLUTFromNand=IDLE;
//	returnstatus_t ret;
		
//	WDOG_disable();
	
//	while(BOOT_ConfigGetSerialFlash(BOOT_SIZE_DATAPARAMETERS,  5, ptu8BOOT_dataSet) != BOOT_SerialFlash_LecturaCorrecta);
			
//	if(!strncmp( "LCOk", (char *)ptu8BOOT_dataSet, 4))
//	{
//		DDRmalloc(DDRdataBoot, srcCCN, SizeDDRdataCCN);
//		DDRmalloc(DDRdataBoot, srcLUT, SizeDDRdataLUT);
				
//#ifdef BOOT_USE_NFC_DRIVER
//		NfcInfo.CmdPending= TRUE;
//		Result = NFC1_ReadPages(NfcInfo.hNfc, 0, NFC_GetPageAddress(blockNumberCNN,0), pageNumberCNNN , *srcCCN);
//		while(NfcInfo.CmdPending){};
		
//		NfcInfo.CmdPending= TRUE;
//		Result = NFC1_ReadPages(NfcInfo.hNfc, 0, NFC_GetPageAddress(blockNumberLTU,0), pageNumberLUT , *srcLUT);
//		while(NfcInfo.CmdPending){};
//#else
//		aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(blockNumberCNN);
//		temp = 0;
//		do
//		{
//			do
//			{
//				ret=EXTNAND_ReadBytes(aux,(uint8_t *)(*(srcCCN)+BOOT_CONVERT_NAND_PAGE_2_ADDR(temp)), EXTERNAL_NAND_FLASH_PAGE_SIZE);
//			}while(ret == RUNNING);
//			temp++;
//			aux+=EXTERNAL_NAND_FLASH_PAGE_SIZE;
//		}while(temp < pageNumberCNNN);

//		aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(blockNumberLTU);
//		temp = 0;
//		do
//		{
//			do
//			{
//				ret=EXTNAND_ReadBytes(aux,(uint8_t *)(*(srcLUT)+BOOT_CONVERT_NAND_PAGE_2_ADDR(temp)), EXTERNAL_NAND_FLASH_PAGE_SIZE);
//			}while(ret == RUNNING);
//			temp++;
//			aux+=EXTERNAL_NAND_FLASH_PAGE_SIZE;
//		}while(temp < pageNumberLUT);
//#endif

//		StatusCCNandLUTFromNand = SUCCESS;
//	}
//	else
//	{
//		StatusCCNandLUTFromNand= ERROR;
//	}
//	WDOG_enable();
    return (returnstatus_t)0;//StatusCCNandLUTFromNand;
}

BOOTreturnstatus_t BOOT_Motor()
{	
//	MSD_status BOOT_MSDerror;
//	BOOTreturnstatus_t BOOT_errorStatus = BootRUNNING;
//	uint8 BootflagCorrectLoad =  0;
//	uint8 ptu8BOOT_data[60];
//	uint8 ptu8BOOT_dataSec[60];
//	uint8 ptu8BOOT_dataSet[60];
//	uint32 BOOT_TimerDetected;
	
//	WDOG_disable();		/* Se desactiva el Watchdog */
	
//	while((BootStatus != BOOT_STATUS_FINISH)  && ( BootStatus != BOOT_STATUS_IDLE ))	/* Proceso bloqueante */
//	{
//		MSD_Task();
//		Poll();   //MEDIR TIEMPO DE ESTO
		
//		switch(BootStatus)
//		{
//		case  BOOT_STATUS_CHEKSectorsNand:		/* Estado inicial */
			
//			while(EXTFLASH_ReadBytes(0, ptu8BOOT_data, 30)!= SUCCESS);
//			while(BOOT_ConfigGetSerialFlash(BOOT_SIZE_DATAPARAMETERSSecurity,  5, ptu8BOOT_dataSec) != BOOT_SerialFlash_LecturaCorrecta);
//			while(BOOT_ConfigGetSerialFlash(BOOT_SIZE_DATAPARAMETERS,  5, ptu8BOOT_dataSet) != BOOT_SerialFlash_LecturaCorrecta);
						
//			/* Si el BOOT de Albert ya ha finalizado */
//			if((!strncmp( "UPDATEEND", (char *)ptu8BOOT_data, 9))  &&  (!strncmp( "PEND", (char *)ptu8BOOT_dataSec, 4)))
//			{
//				/* Copia de seguridad de LUT y CCN en la NAND (Espacio de seguridad) */
//				CNNandLUTCopySecurity(NandBlockWriteCCN, pageNumberCNNN, NandBlockSecurityCNN,NandBlockWriteLUT, pageNumberLUT, NandBlockSecurityLUT);
				
//				/* Escribimos en dataSec 'LCOk' */
//				sprintf((char *)ptu8BOOT_dataSec,"LCOk");
				
//				/* Almacena en la NAND en el espacio de parametros de seguridad el dataSec (LCOk) */
//				while( BOOT_ConfigSetSerialFlash(BOOT_SIZE_DATAPARAMETERSSecurity, 5, ptu8BOOT_dataSec) != BOOT_SerialFlash_EscrituraCorrecta);
//			}
//			/* Si el BOOT de Albert no ha finalizado */
//			else if((strncmp( "UPDATEEND", (char *)ptu8BOOT_data, 9))  &&  (!strncmp( "PEND", (char *)ptu8BOOT_dataSec, 4)))
//			{
//				/* Copia de seguridad del LUT y el CCN en la NAND (Espacio de LUT y CCN) */
//				CNNandLUTCopySecurity(NandBlockSecurityCNN, pageNumberCNNN, NandBlockWriteCCN,NandBlockSecurityLUT, pageNumberLUT, NandBlockWriteLUT  );
				
//				/* Escribimos en dataSec 'LCOk' */
//				sprintf((char *)ptu8BOOT_dataSec,"LCOk");
				
//				/* Almacena en la NAND en el espacio de parametros de seguridad el dataSec (LCOk) */
//				while(BOOT_ConfigSetSerialFlash(BOOT_SIZE_DATAPARAMETERSSecurity, 5, ptu8BOOT_dataSec)!= BOOT_SerialFlash_EscrituraCorrecta);
				
//				/* Almacena en la NAND en el espacio de parametros el dataSec (LCOk) */
//				while(BOOT_ConfigSetSerialFlash(BOOT_SIZE_DATAPARAMETERS, 5, ptu8BOOT_dataSec)!= BOOT_SerialFlash_EscrituraCorrecta);
//			}
//			/* Si dataSec y dataSet valen ambas distinto de 'LCOk' */
//			else if( (!strncmp( "LCOk", (char *)ptu8BOOT_dataSec, 5))   &&  (strncmp( "LCOk", (char *)ptu8BOOT_dataSet, 5)) )
//			{
//				/* Copia de seguridad del LUT y el CCN en la NAND (Espacio de seguridad) */
//				CNNandLUTCopySecurity(NandBlockSecurityCNN, pageNumberCNNN, NandBlockWriteCCN, NandBlockSecurityLUT, pageNumberLUT,  NandBlockWriteLUT );
				
//				/* Escribimos en dataSec 'LCOk' */
//				sprintf((char *)ptu8BOOT_dataSec,"LCOk");
				
//				/* Almacena en la NAND en el espacio de parametros el dataSec (LCOk) */
//				while(BOOT_ConfigSetSerialFlash(BOOT_SIZE_DATAPARAMETERS, 5, ptu8BOOT_dataSec)!= BOOT_SerialFlash_EscrituraCorrecta);
//			}
//			/* Si dataSec vale LCOk y dataSet es distinto de LCOk */
//			else if( (!strncmp( "LCOk", (char *)ptu8BOOT_dataSet, 5))   &&  (strncmp( "LCOk", (char *)ptu8BOOT_dataSec, 5)) )
//			{
//				/* Copia de seguridad de LUT y CCN en la NAND (Espacio de seguridad) */
//				CNNandLUTCopySecurity(NandBlockWriteCCN, pageNumberCNNN, NandBlockSecurityCNN,NandBlockWriteLUT, pageNumberLUT, NandBlockSecurityLUT );
				
//				/* Escribimos en dataSec 'LCOk' */
//				sprintf((char *)ptu8BOOT_dataSec,"LCOk");
				
//				/* Almacena en la NAND en el espacio de parametros de seguridad el dataSec (LCOk) */
//				while(BOOT_ConfigSetSerialFlash(BOOT_SIZE_DATAPARAMETERSSecurity, 5, ptu8BOOT_dataSec)!= BOOT_SerialFlash_EscrituraCorrecta );
//			}
			
//			/* RUNNING -> Check Sector Nand*/
//			BOOT_errorStatus = BootCheckSectorNand;
			
//			/* Sale del proceso bloqueante*/
//			BootStatus= BOOT_STATUS_IDLE; //OT
// 			break;
			
//		case  BOOT_STATUS_IDLE:		BOOT_errorStatus = BootIDLE;	break;		/* No entra por que el bucle while excluye este caso */

//		case  BOOT_STATUS_INIT:
			
//			MSDinit();								/* Inicializa la librería del USB */
//			MSDdetection(MSD_ON);					/* Alimenta el USB y realiza su detección */
//			BootStatus= BOOT_STATUS_ENABLE;			/* Actualiza el status para pasar al siguiente paso */
//			BOOT_TimerDetected= TICKS_GetTicks();	/* Toma referencia de tiempo para evaluar cuando dejar de buscar un USB */
//			break;

//		case  BOOT_STATUS_ENABLE:

//			BOOT_MSDerror =  MSDstatus();	/* Devuelve el estado del USB */
//			if(BOOT_MSDerror == MSD_DEVICE_READY)	BootStatus = BOOT_STATUS_DETECTING;					/* En caso de detectar un USB en estado READY pasamos al siguiente paso */
//			if(TICKS_DiffTicks(BOOT_TimerDetected)> TIME_DETECTED_USB) 	BootStatus= BOOT_STATUS_NO_USB;	/* Si se exceden de 5 segundos buscando un dispositivo USB se determina que no hay ningún USB conectado */
//			break;

//		case  BOOT_STATUS_DETECTING:
				
//			BOOT_MSDerror = MSDinstallMFS();	/* Se instalan en el USB el sistema de archivos MSF para poder realizar la lectura/escritura */
//			if(BOOT_MSDerror == K70_MSD_ERR_OK)	/* Si la instalación finaliza con exito */
//			{
//				/* Las funciones BOOT_Read y BOOT_Write le dan valor a la variable global ReadOrWrite */
//				if( ReadOrWrite== BOOT_MOTOR_WRITE ) BootStatus = BOOT_STATUS_LOADLUT;	/* Si se quiere escribir pasamos a LOAD LUT */
//				else BootStatus= BOOT_STATUS_READLUT;									/* Si se quiere leer pasamos a READ LUT */
//			}
//			break;

//		case BOOT_STATUS_CHANGE_INDEX_LUT:
//			if 		( NandBlockWriteLUT == NandBlockWriteLUT_Z0 ) { NandBlockWriteLUT = NandBlockWriteLUT_Z1; NandBlockWriteCCN = NandBlockWriteCCN_Z1;  BootStatus = BOOT_STATUS_LOADLUT;}
//			else if ( NandBlockWriteLUT == NandBlockWriteLUT_Z1 ) { NandBlockWriteLUT = NandBlockWriteLUT_Z2; NandBlockWriteCCN = NandBlockWriteCCN_Z2;  BootStatus = BOOT_STATUS_LOADLUT; }
//			else if ( NandBlockWriteLUT == NandBlockWriteLUT_Z2 ) { NandBlockWriteLUT = NandBlockWriteLUT_Z3; NandBlockWriteCCN = NandBlockWriteCCN_Z3;  BootStatus = BOOT_STATUS_LOADLUT;}
//			else {
//				//error.. Probamos en la zona 0
//				NandBlockWriteLUT = NandBlockWriteLUT_Z0; NandBlockWriteCCN = NandBlockWriteCCN_Z0;  BootStatus = BOOT_STATUS_LOADLUT;
//			}
//		break;
			
//		case  BOOT_STATUS_LOADLUT:	/* Para escribir */
						
//			switch( BOOTreadLUT(NandBlockWriteLUT))	/* Se lee el bloque de memoria NAND donde se encuentra al LUT */
//			{
//				case BootSUCCESS:	BootStatus = BOOT_STATUS_LOADCCN;			break;	/* Si se lee correctamente se salta a la lectura del CCN */
//				case NOTFOUNDFILE:	BootStatus = BOOT_STATUS_LOADBOOTLOADER;	break;	/* En caso de no encontrar nada se salta al BOOT loader */
//				case BootERROR:
//					BootStatus = BOOT_STATUS_LOADCCNANDLUTSecuity;						/* Si devuelve error se pasa al proceso de carga del LUT y CCN de seguridad */
//					BootflagCorrectLoad=4;							/* LUT, CCN y FW -ERROR- */
//					break;
//				case BootIDLE: break;
//				case BootErrorLUTCCN: BootStatus = BOOT_STATUS_CHANGE_INDEX_LUT;  break;  //no se ha podido grabar, cambiamos de indice (Flash con Bloque malo)
//				default: break;				/* AÑADIDO SERGIO */
//			}
//			break;
			
//		case  BOOT_STATUS_LOADCCN:	/* Si se ha tenido exito al cargar el LUT */
//			switch(BOOTReadCCN(NandBlockWriteCCN))	/* Se lee el bloque de memoria NAND donde se encuentra el CCN */
//			{
//				case BootSUCCESS:								/* En caso de tener exito se salta al BOOT loader */
//					BOOT_SaveZone_CCNLUT();  //grabamos zona donde se almacena el CCN y el LUT
					
//					BootStatus = BOOT_STATUS_LOADBOOTLOADER;
//					BootflagCorrectLoad=1;			/* LUT y CCN -OK- FW -ERROR- */
//					break;
	
//				case NOTFOUNDFILE:								/* En caso de no encontrar archivos se salta al proceso de carga del LUT y CCN de seguridad */
//					BootStatus = BOOT_STATUS_LOADCCNANDLUTSecuity;
//					BootflagCorrectLoad=4;			/* LUT, CCN y FW -ERROR- */
//					break;
	
//				case BootERROR:									/* En caso de error se realiza lo mismo que en el paso anterior */
//					BootStatus = BOOT_STATUS_LOADCCNANDLUTSecuity;
//					BootflagCorrectLoad=4;			/* LUT, CCN y FW -ERROR- */
//					break;
	
//				case BootIDLE:	break;
//				default: break;				/* AÑADIDO SERGIO */
				
//				case BootErrorLUTCCN:   //no se ha podido grabar, cambiamos de indice (Flash con Bloque malo)
//					BootStatus = BOOT_STATUS_CHANGE_INDEX_LUT;
//					break;  //no se ha podido grabar, cambiamos de indice
//				}
//			break;
							
//		case  BOOT_STATUS_LOADBOOTLOADER:
//			switch(BOOTbootloaderUpdate())		/* Proceso de Almacenado de nuevo FW */
//			{
//			case BootSUCCESS:
//				BootStatus= BOOT_STATUS_LOADCCNANDLUTSecuity;			/* En caso de haberse completado con exito */
//				if(BootflagCorrectLoad==1) BootflagCorrectLoad=3;		/* LUT, CCN y FW -OK- */
//				else	BootflagCorrectLoad=2;							/* FW -OK- LUY y CCN -ERROR- */
//				break;
//			case NOTFOUNDFILE: BootStatus= BOOT_STATUS_LOADCCNANDLUTSecuity; break;		/* Si no se ha encontrado ficheros */
//			case BootERROR: BootStatus = BOOT_STATUS_LOADCCNANDLUTSecuity; break;		/* Si ha tenido algún error en la carga */
//			case BootRUNNING:
//			case BootIDLE: break;
//			default: break;		/* AÑADIDO SERGIO */
//			}
//			break;
			
//		case BOOT_STATUS_LOADCCNANDLUTSecuity:
//			switch(BootflagCorrectLoad)
//			{
//			/* Se ha copiado correctamente LUT y CCN pero el FW ha dado error o no había archivos */
//			case 1:  // Copia de seguridad
//				CNNandLUTCopySecurity(NandBlockWriteCCN, pageNumberCNNN, NandBlockSecurityCNN,NandBlockWriteLUT, pageNumberLUT, NandBlockSecurityLUT  );
//				sprintf((char *)ptu8BOOT_data,"LCOk");
//				while(BOOT_ConfigSetSerialFlash(BOOT_SIZE_DATAPARAMETERS, 5, ptu8BOOT_data)!= BOOT_SerialFlash_EscrituraCorrecta);
//				sprintf((char *)ptu8BOOT_data,"LCOk");
//				while(BOOT_ConfigSetSerialFlash(BOOT_SIZE_DATAPARAMETERSSecurity, 5, ptu8BOOT_data)!=BOOT_SerialFlash_EscrituraCorrecta);
//				break;
				
//			case 2:	break;		/* Se ha cargado el FW correctamente, pero el LUT y el CCN ha tenido un problema */
									
//			case 3:				/* Se ha cargado el FW, el LUT y el CCN correctamente */
//				sprintf((char *)ptu8BOOT_data,"LCOk");
//				while(BOOT_ConfigSetSerialFlash(BOOT_SIZE_DATAPARAMETERS, 6, ptu8BOOT_data)!=BOOT_SerialFlash_EscrituraCorrecta);
//				sprintf((char *)ptu8BOOT_data,"PEND");
//				while(BOOT_ConfigSetSerialFlash(BOOT_SIZE_DATAPARAMETERSSecurity, 5, ptu8BOOT_data)!=BOOT_SerialFlash_EscrituraCorrecta);
//				break;
//				// No se ha realizado correctamente la copia de los archivos o los archivos no son los correctos.
				
//			case 4:		/* Ha fallado la carga del FW, del LUT y del CCN */
//				sprintf((char *)ptu8BOOT_data,"LCkO");
//				while(BOOT_ConfigSetSerialFlash(BOOT_SIZE_DATAPARAMETERS, 5, ptu8BOOT_data)!=BOOT_SerialFlash_EscrituraCorrecta);
//				break;
				
//			default: break;
//			}
//			BootStatus= BOOT_STATUS_DISABLE;
//			break;
			
//		case BOOT_STATUS_READLUT:
//			switch(BOOTWriteLUT())
//			{
//				case BootSUCCESS:	BootStatus = BOOT_STATUS_READCCN;	break;
//				case NOTFOUNDFILE:	BootStatus = BOOT_STATUS_DISABLE;	break;
//				case BootERROR:		BootStatus = BOOT_STATUS_DISABLE;	break;
//			}
//			break;
			
//		case BOOT_STATUS_READCCN:
//			switch(BOOTWriteCCN())
//			{
//				case BootSUCCESS:	BootStatus = BOOT_STATUS_DISABLE;	break;
//				case NOTFOUNDFILE:	BootStatus = BOOT_STATUS_DISABLE;	break;
//				case BootERROR:		BootStatus = BOOT_STATUS_DISABLE;	break;
//			}
//		break;
			
//		case  BOOT_STATUS_DISABLE:
//			MSDdetection(MSD_OFF);
//			MSDuninstallMFS();
//			BootStatus= BOOT_STATUS_FINISH;
//			BOOT_errorStatus = BootSUCCESS;
//			break;
						
//		case BOOT_STATUS_NO_USB:
//			MSDdetection(MSD_OFF);
//			MSDuninstallMFS();
//			BootStatus= BOOT_STATUS_FINISH;
//			BOOT_errorStatus = BootIDLE;
//			break;
					
//		case  BOOT_STATUS_FINISH:	break;
		
//		}
//	}
//	WDOG_enable();
    return  BootSUCCESS;//BOOT_errorStatus;
}

BOOTreturnstatus_t BOOT_SaveDataCNN(uint32 blockWrite, uint32 pageNumber)
{
	uint8_t   *WritePageBufferPtr = WritePageBuffer;
	uint8_t   *ReadPageBufferPtr =  ReadPageBuffer;
	uint32 blockWrt = blockWrite;
	uint8_t flag_err = 0;
	uint8_t ret = BootSUCCESS;
	uint32_t aux;
	returnstatus_t extnand_ret;
	
//	do {  //reintentamos copia
//#ifdef BOOT_USE_NFC_DRIVER
//		NfcInfo.CmdPending = TRUE;  // Indicamos que el dispositivo se encuentra en proceso de ejecución.
//		NFC1_WritePages(NfcInfo.hNfc, 0, NFC_GetPageAddress(blockWrt, pageNumber ) ,1, WritePageBufferPtr);
		
//		while(NfcInfo.CmdPending){};   // Esperamos hasta  que el dispositivo este operativo.
	
//		NfcInfo.CmdPending  = TRUE;
//		NFC1_ReadPages(NfcInfo.hNfc, 0,  NFC_GetPageAddress(blockWrt, pageNumber ), 1 , ReadPageBufferPtr);
//		//verificamos grabacion
//		while(NfcInfo.CmdPending){};
//#else
//		aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(blockWrt);
//		aux+= BOOT_CONVERT_NAND_PAGE_2_ADDR(pageNumber);
//		do
//		{
//			extnand_ret = EXTNAND_WriteBytes(aux, WritePageBufferPtr, EXTERNAL_NAND_FLASH_PAGE_SIZE);
//		}while(extnand_ret == RUNNING);
//		do
//		{
//			extnand_ret = EXTNAND_ReadBytes(aux, ReadPageBufferPtr, EXTERNAL_NAND_FLASH_PAGE_SIZE);
//		}while(extnand_ret == RUNNING);
//#endif
		
//		if ( memcmp(WritePageBufferPtr, ReadPageBufferPtr, sizeof (WritePageBuffer))== 0 ) { TEST_PrintInfo( "." ); flag_err=10; }  //copia correcta
//		else { //copia erronea
//			TEST_PrintInfo( "!");
//			flag_err++;
//			if (flag_err==4) {ret = BootErrorLUTCCN;}  //no se copia en las repeticiones
//		}
						
//	}
//	while ( flag_err<4 ); //reintentamos copia

    return (BOOTreturnstatus_t)(ret);
}

void BOOT_SaveDataLTU(uint32 blockErase, uint32 blockWrite, uint32 pageNumber)
{
	uint8_t    *WritePageBufferPtrLTU = WritePageBuffer;
	uint8_t    *ReadPageBufferPtrLTU = ReadPageBuffer;
	uint32 bckErase=blockErase;
	uint32 blockWrt= blockWrite;
	uint8_t flag_err = 0;
	returnstatus_t ret;
	uint32_t aux;
	
//	do {
//#ifdef BOOT_USE_NFC_DRIVER
//		NfcInfo.CmdPending = TRUE;
//		NFC1_EraseBlocks(NfcInfo.hNfc, 0,blockWrt , bckErase);
//		while(NfcInfo.CmdPending){}; // Esperamos hasta  que el dispositivo este operativo.
	
//		NfcInfo.CmdPending= TRUE;  // Indicamos que el dispositivo se encuentra en proceso de ejecución.
//		NFC1_WritePages(NfcInfo.hNfc, 0 , NFC_GetPageAddress(blockWrt, pageNumber ) ,1, WritePageBufferPtrLTU);
//		while(NfcInfo.CmdPending){};   // Esperamos hasta  que el dispositivo este operativo.
	
//		NfcInfo.CmdPending = TRUE;
//		NFC1_ReadPages(NfcInfo.hNfc, 0,   NFC_GetPageAddress(blockWrt, pageNumber ), 1 , ReadPageBufferPtrLTU);
//		while(NfcInfo.CmdPending){};
//#else
//		aux=BOOT_CONVERT_NAND_BLOCK_2_ADDR(blockWrt);
//		do
//		{
//			ret = EXTNAND_EraseBlocks(aux, bckErase);
//		}while(ret == RUNNING);
		
//		aux += BOOT_CONVERT_NAND_PAGE_2_ADDR(pageNumber);
//		do
//		{
//			ret = EXTNAND_WriteBytes(aux, WritePageBufferPtrLTU, EXTERNAL_NAND_FLASH_PAGE_SIZE);
//		}while(ret == RUNNING);
		
//		do
//		{
//			ret = EXTNAND_ReadBytes(aux, ReadPageBufferPtrLTU, EXTERNAL_NAND_FLASH_PAGE_SIZE);
//		}while(ret = RUNNING);
//#endif
		
//		if ( memcmp(WritePageBufferPtrLTU, ReadPageBufferPtrLTU, sizeof (WritePageBuffer))== 0 ) { TEST_PrintInfo( "." ); flag_err=5; }
//		else {TEST_PrintInfo( "!"); flag_err++; }
		
//	}while (flag_err<4);
}

BOOTreturnstatus_t BOOTreadLUT(uint32 NandBlockLUT )
{
	uint32 i;
	uint32 cont;
	uint32 contAux=2048;
	uint32 lenghtLTU;
	uint8 AppMotorLTU=0;
//	FIL inputFile;
	uint8 ptu8FileName[60];
	uint32 u32BytesWritten;
	uint32 USB_error;
	BOOTreturnstatus_t ErrorWriteLTu= BootIDLE;
//	char *MFSfileNameLTU= "LUT.lut";
//	uint8 ptu8BOOT_data[60];
//	char*  MFSdirectoryNameLTU= "";
	uint32 blockNumberLTU= NandBlockLUT;
	uint32 blockEraseLUT=1;//1; /* MODIFICADO SERGIO */
	uint32 pageNumberLTU=0;			/*  !!!! hay una variable global que se llama LUT casi igual !!!!  */
	returnstatus_t ret;
	uint32_t aux;
	
	/* AÑADIDO SERGIO */
	uint8_t    *WritePageBufferPtrLTU = WritePageBuffer;
	uint8_t    *ReadPageBufferPtrLTU = ReadPageBuffer;
	uint8_t flag_err = 0;
	uint8_t flag_err_end = 0;
	
//	MSD_Task();

//	Poll();
	
//	while(((ErrorWriteLTu != NOTFOUNDFILE ) && (ErrorWriteLTu != BootERROR)) &&  (ErrorWriteLTu != BootSUCCESS) && (ErrorWriteLTu != BootErrorLUTCCN) ) 	/* Mientras que no acabe con exito o de algún error BLOQUEANTE */
//	{
//		switch(AppMotorLTU)
//		{
//		case BOOT_LUT_Init: //OT

//			USB_error = MSDdirExist("LUTCCN");
//			if (USB_error == K70_MSD_ERR_OK) USB_error = MSDchangeDir("LUTCCN");

//			USB_error = MSDfileExist("LUT.lut", "", &i);	/* Comprueba que el archivo del LUT existe */

//			if(USB_error == K70_MSD_ERR_OK) AppMotorLTU = BOOT_LUT_Erase;	/* En caso de haber encontrado el archivo se salta al siguiente paso */

//			else AppMotorLTU = BOOT_LUT_ErrorNotFoundFile;	/*Se ha producido un problema, indicamos que se tiene que desconectar el USB y volverlo a conectar*/

//			break;
			
//		case BOOT_LUT_Erase:
			
//			/* AÑADIDO SERGIO */
//#ifdef BOOT_USE_NFC_DRIVER
//			NfcInfo.CmdPending = TRUE;
//			NFC1_EraseBlocks(NfcInfo.hNfc, 0,blockNumberLTU , blockEraseLUT);
//			while(NfcInfo.CmdPending){}; // Esperamos hasta  que el dispositivo este operativo.
//#else
//			aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(blockNumberLTU);
//			do
//			{
//				ret = EXTNAND_EraseBlocks(aux, blockEraseLUT);
//			}while(ret == RUNNING);
//#endif
//			/* AÑADIDO SERGIO */
			
//			sprintf((char *)ptu8BOOT_data,"Err");
									
//			while(BOOT_ConfigSetSerialFlash(BOOT_SIZE_DATAPARAMETERS, 5, ptu8BOOT_data)!= BOOT_SerialFlash_EscrituraCorrecta);	/* Escribir "Err" en los parametros en la memoria FLASH */

//			strcpy(ptu8FileName, MFSdirectoryNameLTU);
//			strcat(ptu8FileName, MFSfileNameLTU);

//			USB_error = MSDopenFile(&inputFile, ptu8FileName, FA_READ);		/* Se abre el fichero con la intención de realizar la lectura */

//			if(USB_error == K70_MSD_ERR_OK) AppMotorLTU= BOOT_LUT_OpenFile;	/* Si no hay problema se continua */
//			else AppMotorLTU = BOOT_LUT_ErrorNotFoundFile;
			
//			break;
			
//		case BOOT_LUT_OpenFile:

////			lenghtLTU = inputFile.fsize;	/* Se toma la longitud del LUT */
////
////			cont = lenghtLTU;
////
////			USB_error = MSDreadFile(&inputFile, WritePageBuffer, cont , &u32BytesWritten);
////
////			BOOT_SaveDataLTU(blockEraseLUT, blockNumberLTU, pageNumberLTU);	/* Realiza la escritura */
			
//			/* AÑADIDO SERGIO */
//			cont=0;
//			lenghtLTU = inputFile.fsize;

//			//TEST_PrintInfo("Copy LUT:");
//			TEST_PrintValue("Copy LUT %u: ",NandBlockLUT);
			
//			do
//			{
//				flag_err = 0;
//				if(lenghtLTU-cont < 2048 )	 contAux = lenghtLTU-cont;
				
//				USB_error = MSDreadFile(&inputFile, WritePageBuffer, contAux , &u32BytesWritten);

//				if(USB_error != K70_MSD_ERR_OK)
//				{
//					AppMotorLTU = BOOT_LUT_ErrorWrite;
//					break;
//				}

//				//BOOT_SaveDataLTU(blockEraseLUT, blockNumberLTU, pageNumberLTU);	/* Realiza la escritura */
//				do {
//#ifdef BOOT_USE_NFC_DRIVER
//					NfcInfo.CmdPending= TRUE;  	// Indicamos que el dispositivo se encuentra en proceso de ejecución.
//					NFC1_WritePages(NfcInfo.hNfc, 0 , NFC_GetPageAddress(blockNumberLTU, pageNumberLTU ) ,1, WritePageBufferPtrLTU);
//					while(NfcInfo.CmdPending){};   // Esperamos hasta  que el dispositivo este operativo.
	
//					NfcInfo.CmdPending = TRUE;
//					NFC1_ReadPages(NfcInfo.hNfc, 0,   NFC_GetPageAddress(blockNumberLTU, pageNumberLTU ), 1 , ReadPageBufferPtrLTU);
//					while(NfcInfo.CmdPending){};
//#else
//					aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(blockNumberLTU);
//					aux += BOOT_CONVERT_NAND_PAGE_2_ADDR(pageNumberLTU);
//					do
//					{
//						ret = EXTNAND_WriteBytes(aux, WritePageBufferPtrLTU, EXTERNAL_NAND_FLASH_PAGE_SIZE);
//					}while(ret == RUNNING);
//					do
//					{
//						ret = EXTNAND_ReadBytes(aux, ReadPageBufferPtrLTU, EXTERNAL_NAND_FLASH_PAGE_SIZE);
//					}while(ret == RUNNING);
//#endif
					
//					if ( memcmp(WritePageBufferPtrLTU, ReadPageBufferPtrLTU,contAux)== 0) {TEST_PrintInfo("."); flag_err=10;} //siguiente pagina
//					else { TEST_PrintInfo("!"); flag_err++; if (flag_err == 4) flag_err_end = 1; }
//				}while (flag_err<4);  //repetimos la copia de la pagina. A veces la copia de la primera pagina falla despues del borrado.. con esto reintentamos
				
//				pageNumberLTU++;

//				cont = cont + 2048;

//			}while( (cont<lenghtLTU)&&(flag_err_end ==0) );
						
//			AppMotorLTU= BOOT_LUT_WriteFromUSB;
//			break;
			
//		case BOOT_LUT_WriteFromUSB:

//			USB_error=MSDcloseFile(&inputFile);	/* Cierra el archivo */

//			AppMotorLTU=BOOT_LUT_Init;	/* Se vuelve al inicio */

//			if (flag_err_end == 0)	{ TEST_PrintInfo("SAVE LUT OK\r\n");     ErrorWriteLTu = BootSUCCESS; }	/* Se indica que tiene exito el proceso */
//			else 					{ TEST_PrintInfo("SAVE LUT ERROR\r\n");  ErrorWriteLTu = BootErrorLUTCCN; }
//			break;
			
//		case BOOT_LUT_Close:				/* No se contempla este caso */
//			ErrorWriteLTu=   NOTFOUNDFILE;
//			break;
			
//		case BOOT_LUT_ErrorWrite:			/* No se contempla este caso */
//			// Falta indicar que devuleva algún tipo de error.
//			TEST_PrintInfo("USB ERROR\r\n");
//			ErrorWriteLTu= BootERROR;
//			break;
			
//		case BOOT_LUT_ErrorNotFoundFile:	/* Si no encuentra el archivo en el USB salta aquí */
//			ErrorWriteLTu=   NOTFOUNDFILE;
//			break;
			
//		default: break;		/* AÑADIDO SERGIO */
//		}
//	}
	return ErrorWriteLTu;
}

BOOTreturnstatus_t BOOTReadCCN(uint32 NandBlockCCN)
{	
	uint32 cont=0;		
	uint32 contAux=2048;
	uint32 lenghtCNN;
	uint32 rt=0;
//	FIL inputFile;
	uint8 ptu8FileName[60];
	uint32 u32BytesWritten;
	uint32 USB_error;
	BOOTreturnstatus_t ErrorWriteCNN=  BootIDLE;
	uint32 blockNandCCN = NandBlockCCN;
	LDD_TError  Result;
	uint8 ptu8BOOT_data[60];
//	char *MFSfileNameCNN= "CCN.ccn";
//	char  *MFSdirectoryNameCNN= "";
	uint32 blockNumberCNN= NandBlockCCN;  //Bloque inicial de grabacion de CCN
	uint32 pagenumberccn = 0;			  //indice de pagina para copiar
	//uint8_t flag_err = 0;
	uint8_t flag_err_end = 0;
	uint32_t aux;
	returnstatus_t ret;
	
//	MSD_Task();

//	Poll();
	
//	while( (ErrorWriteCNN != NOTFOUNDFILE) && (ErrorWriteCNN != BootERROR) &&  (ErrorWriteCNN != BootSUCCESS) && (ErrorWriteCNN != BootErrorLUTCCN) )	/* Mientras no acabe con éxito o de algún tipo de error BLOQUEANTE */
//	{
//		switch(AppMotorCNN)
//		{
//		case BOOT_CCN_Init: //OT
			
//			USB_error = MSDdirExist("LUTCCN");
//			if (USB_error == K70_MSD_ERR_OK) USB_error = MSDchangeDir("LUTCCN");
		
//			USB_error = MSDfileExist("CCN.ccn", "", &rt);		/* Comprueba si existe el archivo en el USB */

//			if(USB_error == K70_MSD_ERR_OK) 	AppMotorCNN =BOOT_CCN_Erase;	/* En caso de existir se continua con el sifuiente paso */
//			else	AppMotorCNN=BOOT_CCN_ErrorNotFoundFile;	/*Se ha producido un problema, indicamos que se tiene que desconectar el USB y volverlo a conectar*/
//			break;
			
//		case BOOT_CCN_Erase:
//#ifdef BOOT_USE_NFC_DRIVER
//			NfcInfo.CmdPending = TRUE;
//			Result = NFC1_EraseBlocks(NfcInfo.hNfc, 0, blockNandCCN, blockEraseCCN);	/* Borra el CCN de la memoria NAND */
//			while(NfcInfo.CmdPending){}; 	/* Espera hasta que acabe el proceso */
//#else
//			aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(blockNandCCN);
//			do
//			{
//				ret = EXTNAND_EraseBlocks(aux, blockEraseCCN);
//			}while(ret == RUNNING);
//#endif
							
//			AppMotorCNN= BOOT_CCN_OpenFile;	/* Se salta al siguiente paso */
//			break;
			
//		case BOOT_CCN_OpenFile:

//			sprintf((char *)ptu8BOOT_data,"Err");
													
//			while(BOOT_ConfigSetSerialFlash(BOOT_SIZE_DATAPARAMETERS, 5, ptu8BOOT_data)!= BOOT_SerialFlash_EscrituraCorrecta);
									
//			strcpy(ptu8FileName, MFSdirectoryNameCNN);
//			strcat(ptu8FileName, MFSfileNameCNN);

//			USB_error = MSDopenFile(&inputFile, ptu8FileName, FA_READ);

//			if(USB_error == K70_MSD_ERR_OK)		AppMotorCNN= BOOT_CCN_WriteFromUSB;
//			break;
			
//		case BOOT_CCN_WriteFromUSB:

//			cont=0;
//			lenghtCNN=inputFile.fsize;
//			pagenumberccn = 0;

//			//TEST_PrintInfo("Copy CCN:");
//			TEST_PrintValue("Copy CCN %u: ",NandBlockCCN);

//			do
//			{
//				if(lenghtCNN-cont < 2048 )	 contAux= lenghtCNN-cont;
				
//				USB_error = MSDreadFile(&inputFile, WritePageBuffer, contAux , &u32BytesWritten);

//				if(USB_error != K70_MSD_ERR_OK)
//				{
//					AppMotorCNN = BOOT_CCN_ErrorWrite;
//					break;
//				}

//				switch ( BOOT_SaveDataCNN(blockNumberCNN, pagenumberccn) ) {
//					case BootSUCCESS:
//						pagenumberccn++;
//						cont= cont + 2048;
//						flag_err_end = 0;
//						break;
//					case BootErrorLUTCCN:
//						flag_err_end = BootErrorLUTCCN;
//						break;
//				}

//			}while( (cont<lenghtCNN)&&(flag_err_end == 0) );
			
//			AppMotorCNN = BOOT_CCN_Close ;
//			break;

//		case BOOT_CCN_Close:
//			USB_error=MSDcloseFile(&inputFile);

//			if ( flag_err_end == BootErrorLUTCCN) {
//				AppMotorCNN= BOOT_CCN_Init;
//				ErrorWriteCNN = BootErrorLUTCCN; //error en la copia a Flash
//				TEST_PrintInfo("SAVE CCN ERROR\r\n");
//			}
//			else { //copia correcta
//				AppMotorCNN= BOOT_CCN_Init;
//				ErrorWriteCNN = BootSUCCESS;
//				TEST_PrintInfo("SAVE CCN OK\r\n");
//			}
//			break;

//		case BOOT_CCN_ErrorNotFoundFile:
//			ErrorWriteCNN =   NOTFOUNDFILE;
//			break;
			
//		case BOOT_CCN_ErrorWrite:
//			// Falta indicar que devuleva algún tipo de error.
//			ErrorWriteCNN= BootERROR;
//			break;
//		}
//	}
    return BootSUCCESS;//ErrorWriteCNN;
}

BOOTreturnstatus_t BOOTbootloaderUpdate(){ //OT
		
	uint8 bootMotor=BOOT_BOOTLOADER_Init;
	uint32 u32BytesWritten;
	uint32 i=0; 	
	uint8 ptu8Flash_data[260];	
	uint8 ptu8USB_data[256];	
	uint8 LoadUSB_data[1];	
	uint8  *ptu8Flash;		
	static uint32 lenghtBoot=0;
	static uint32  checksum=0;
	uint16 USB_errorBoot;  // Gestión errores USB.
//	char *MFSfileNameIndex= "fwmain.bin";
//	char  *MFSdirectoryNameIndex= "";
	uint8 ptu8FileName[60];	
//	static FIL inputFileBoot;
	uint32 rt=0;	
	uint32 cnt=0;	
	BOOTreturnstatus_t ErrorBoot   =   BootIDLE;	
	uint8 ErrorIgual=0;
	/* UNUSED */
	uint8 ptu8File[22]; 	 
	uint8 *ptu8FileBoot;
	uint32 LoadUSB[1];	
	uint8 ptuData8;
//	FIL inputFile;
	SoftVersion_t  file_softvers;
	
//	while((ErrorBoot  != NOTFOUNDFILE  ) && (ErrorBoot  != BootERROR )  &&  (ErrorBoot  != BootSUCCESS )  )
//	{
//		MSD_Task();
	
//		Poll();
			 
//		switch(bootMotor)
//		{
//		case BOOT_BOOTLOADER_Init:
	
//			while(EXTFLASH_ReadBytes(0, ptu8Flash_data, 30)!= SUCCESS);
	
//			if(!strncmp("NEWFIR", (char *)ptu8Flash_data, 6))
//			{
//				file_softvers.fileID.field.year =  ptu8Flash_data[10];
//				file_softvers.fileID.field.week = ptu8Flash_data[9];
//				file_softvers.fileID.field.model = ptu8Flash_data[8];
//				file_softvers.fileID.field.version = ptu8Flash_data[7];
//				bootMotor= BOOT_BOOTLOADER_ExistFile;
//			}
//			else
//			{
//				file_softvers.fileID.field.year = ptu8Flash_data[12];
//				file_softvers.fileID.field.week = ptu8Flash_data[11];
//				file_softvers.fileID.field.model = ptu8Flash_data[10];
//				file_softvers.fileID.field.version = ptu8Flash_data[9];
				
//				if(!strncmp("SIZEERROR", (char *)ptu8Flash_data, 9))  		bootMotor= BOOT_BOOTLOADER_ExistFile;
//				else if(!strncmp("CRC_ERROR", (char *)ptu8Flash_data, 9))	bootMotor= BOOT_BOOTLOADER_ExistFile;
//				else if(!strncmp("UPDATEEND",(char *) ptu8Flash_data, 9))	bootMotor = BOOT_BOOTLOADER_ExistFile;
//				else	bootMotor = BOOT_BOOTLOADER_ExistFile;		//Eliminar en la definitiva, solo para cuando aún no se ha pasado la verificación
//			}
//			break;
			
//		case BOOT_BOOTLOADER_ExistFile:
	
//			USB_errorBoot  =  MSDchangeDir("..");  //volvemos al directorio raiz por si estamos en "LUTCCN"
//			USB_errorBoot  =  MSDfileExist("fwmain.bin", "", &rt);	/* Busqueda del archivo en el USB para cargar nuevo FW */
	
//			if(USB_errorBoot ==   K70_MSD_ERR_OK) { bootMotor = BOOT_BOOTLOADER_OpenFile ; }
//			else { bootMotor= BOOT_BOOTLOADER_ErrorNotFoundFile;  TEST_PrintInfo("fwmain.bin NOT FOUND\r\n"); }
//			break;
			
//		case BOOT_BOOTLOADER_OpenFile:
	
//			strcpy(ptu8FileName, MFSdirectoryNameIndex);	/* Almacena el directorio del fichero */
//			strcat(ptu8FileName, MFSfileNameIndex);			/* Almacena a continuación el nombre del fichero */
	
//			USB_errorBoot = MSDopenFile(&inputFileBoot, ptu8FileName, FA_READ);		/* Realiza la lectura del contenido del fichero */
	
//			lenghtBoot= inputFileBoot.fsize;	/* Se toma el tamaño del fichero */
							
//			if(USB_errorBoot == K70_MSD_ERR_OK) { 		/* Si no hay error, se salta al siguiente paso */
//				bootMotor= BOOT_BOOTLOADER_CheckSerialFlash;
//				TEST_PrintInfo("Open fwmain.bin\r\n");
//			}
//			break;
	
//		case BOOT_BOOTLOADER_CheckSerialFlash:
	
//			//Compruebo que la direccion 0x0000 a la 0x3000  es exactamente igual.
//			cnt = 0;	/* Contador de paquetes de 256B */
//			ptu8Flash = (uint8 *) 0x0000000;
//			while(cnt < BOOT_POSICIO_FW_EXT_MEMO)	/* Máxima capacidad de memoria reservada para el firmware 0x3000 */
//			{
//				USB_errorBoot = MSDreadFile( &inputFileBoot, ptu8USB_data, 256, &u32BytesWritten);	/* Tomar paquetes de 256B del archivo de origen */
	
//				if(USB_errorBoot != K70_MSD_ERR_OK)					/* En caso de error */
//				{ bootMotor= BOOT_BOOTLOADER_ErrorNotFoundFile;	}
//				else												/* Si todo va bien */
//				{
//					for(i=0; i < 256 ; i++)		/* Se recorren los 256B */
//					{
//						ptuData8= ptu8USB_data[i];
//						/* si es diferente y es un area que no se utiliza */ /* las areas que no se utilizan el grabador las deja a 0xFF, pero el fichero binario tiene 0x00 */
//						if((ptu8USB_data[i] != *ptu8Flash) && (ptu8USB_data[i] != 0) && (*ptu8Flash != 0xFF)) {	ErrorIgual=1;	}
//						ptu8Flash ++;
//					}
//				}
				
//				if(ErrorIgual==1)	/* En caso de haberse encontrado un error en la copia */
//				{
//					ErrorBoot= BootERROR;
//					break;
//				}
//				cnt += 256;		/* Se incrementa el contador 256B */
//			}

//			bootMotor = BOOT_BOOTLOADER_EraseSerialFlash;	/* Si no ha habido ningún error saltamos al siguiente paso */
		
//			break;
	
//		case BOOT_BOOTLOADER_EraseSerialFlash:		/* Se borra el resto de la memoria a partir de la dirección 0x3000 hasta la 0x10000 */
//			TEST_PrintInfo("Erase SFLASH Sectors\r\n");
//			cnt = BOOT_POSICIO_FW_EXT_MEMO;
			
//			// Borrado de la flash externa
//			while(cnt < EXTERNAL_FLASH_NAND_BAD_BLOCK)//BOOT_MAX_TAMANY_EXT_MEMO)
//			{
//				while(EXTFLASH_EraseSector(cnt, 1 )!= SUCCESS);
//				TEST_PrintInfo(".");
//				cnt+=0x1000;
//			}
	
//			bootMotor= BOOT_BOOTLOADER_Write;
	
//			break;
	
//		//Copia de USB a Flash externa
//		case BOOT_BOOTLOADER_Write:
	
//			cnt = BOOT_POSICIO_FW_EXT_MEMO;
//			checksum = 0;
//			ErrorIgual=0;
			
//			if(lenghtBoot > EXTERNAL_FLASH_NAND_BAD_BLOCK)
//			{
//				bootMotor=BOOT_BOOTLOADER_ErrorUpdate;
//				break;
//			}
			
//			TEST_PrintInfo("Copy FW to SFLASH\r\n");
//			while(cnt < lenghtBoot)	/* Partiendo desde la posición 0x3000 (la máxima para el FW) se escribe en la FLASH los datos del USB */
//			{
//				USB_errorBoot = MSDreadFile( &inputFileBoot, LoadUSB_data, 1, &u32BytesWritten);	/* Lectura de los datos */
	
//				if( USB_errorBoot == K70_MSD_ERR_OK)	/* Si no hay problema con la lectura */
//				{
//					checksum = checksum+ ((uint32)LoadUSB_data[0]);		/* Preparar CHECKSUM */
//					while( EXTFLASH_WriteBytes(cnt, LoadUSB_data, 1 )!= SUCCESS);		/* Se escribe en la FLASH */
//					cnt++;
//				}
//				else	/* En caso de problema */
//				{
//					bootMotor=BOOT_BOOTLOADER_ErrorNotFoundFile;
//					break;
//				}
//				if ( (cnt%2048)==0) TEST_PrintInfo(".");
//			}
	
//			bootMotor = BOOT_BOOTLOADER_CheckWriteAndRead;	/* Si no hay problema saltamos al siguiente paso */
//			break;
		
//		// Comprobacion de lectura y ecritura correcto.
//		case BOOT_BOOTLOADER_CheckWriteAndRead:
			
//			TEST_PrintInfo("\r\nCALC CheckSum");
//			checksum = 0;
//			cnt = BOOT_POSICIO_FW_EXT_MEMO;
			
//			while(cnt < lenghtBoot)		/* Se realiza la lectura completa de lo grabado en la FLASH y se comprueba el CHECKSUM */
//			{
//				while(EXTFLASH_ReadBytes(cnt , ptu8Flash_data, 1)!= SUCCESS);
//				checksum = checksum+ ((uint32)ptu8Flash_data[0]);
//				cnt++;
//				if ( (cnt%2048)==0) TEST_PrintInfo(".");
//			}
//			TEST_PrintValue("CSum = %u\r\n", checksum);
//			cnt=0;
			
//			while(EXTFLASH_ReadBytes(cnt, ptu8Flash_data, 30 )!=SUCCESS){};		/* Se leen los primeros 30B */
				
//			bootMotor= BOOT_BOOTLOADER_SetNewFir;
//			break;
				
//		// Set tag new FW.
//		case BOOT_BOOTLOADER_SetNewFir:
//			TEST_PrintInfo("SET NEWFIR\r\n");
//			cnt = 0;
	
//			while(EXTFLASH_EraseSector(cnt,1)!=SUCCESS){};		/* Borra un sector */
						
//			while(EXTFLASH_ReadBytes(cnt, ptu8Flash_data, 30 )!=SUCCESS){};		/* Se leen los primeros 30B */
	
//			sprintf((char *)ptu8USB_data,"NEWFIR");		/* Se actualiza la dirección del nuevo FW */
							
//			ptu8USB_data[6] = 0x01;
//			ptu8USB_data[7] = 0x01;
//			ptu8USB_data[8] = 0xB;
//			ptu8USB_data[9] = 0xB;
//			lenghtBoot = lenghtBoot-BOOT_POSICIO_FW_EXT_MEMO;
			
//			ptu8USB_data[10] = (lenghtBoot&0xFF);
//			ptu8USB_data[11] = ((lenghtBoot>>8));
//			ptu8USB_data[12] = ((lenghtBoot>>16));
//			ptu8USB_data[13] = ((lenghtBoot>>24));
//			ptu8USB_data[14] = (checksum&0xFF);
//			ptu8USB_data[15] = ((checksum>>8));
//			ptu8USB_data[16] = ((checksum>>16));
//			ptu8USB_data[17] = ((checksum>>24));
							  
//			while(EXTFLASH_WriteBytes(cnt  , ptu8USB_data, 18 ) != SUCCESS){};	/* Se escriben los primeros 18B */
	
//			while(EXTFLASH_ReadBytes(cnt, ptu8Flash_data, 18 )!=SUCCESS){};		/* Se leen los primeros 18B */
					
//			bootMotor= BOOT_BOOTLOADER_Close;
//			break;
			
//		// Cerramos el USB.
//		case BOOT_BOOTLOADER_Close:
//			TEST_PrintInfo("Close File\r\n");
//			USB_errorBoot = MSDcloseFile(&inputFileBoot);
//			ErrorBoot= BootSUCCESS;
//			break;
				
//		//No se ha encontrado el fichero
//		case BOOT_BOOTLOADER_ErrorNotFoundFile:
//			TEST_PrintInfo("File Not Found\r\n");
//			USB_errorBoot = MSDcloseFile(&inputFileBoot);
//			ErrorBoot= NOTFOUNDFILE;
//			break;
	
//		// Error de actualizacion del boot.
//		case BOOT_BOOTLOADER_ErrorUpdate:
//			TEST_PrintInfo("Update Error\r\n");
//			ErrorBoot = BootERROR;
//			break;
			
//		default: break;		/* AÑADIDO SERGIO */
//		}
//	}
    return BootSUCCESS;//ErrorBoot;
}

Boot_SerialFlashConfig_t BOOT_ConfigSetSerialFlash(uint32 Address, uint8 nBytes, uint8 *BuffSerialFlash)
{
	uint32 i=0;
	uint32 j=0;
	Boot_SerialFlashConfig_t bootErrSaveSerial = BOOT_SerialFlash_Running;
	uint8 flagBootSaveSerialFlash=0;
	uint32 ptu8SaveSerial_data[4];
	
//	switch(motorSetConfigSerialFlash)
//	{
//	case 0:
//		BuffDataSeriaFlash = (uint8*)calloc(0x1000,sizeof(uint8));

//		if((Address + (nBytes-1)) > 0x1000)	/*Si el espacio a escribir supera el espacio reservado - ERROR*/
//		{
//			motorSetConfigSerialFlash= 8;
//			bootErrSaveSerial= BOOT_SerialFlash_ErrorSize;
//		}
//		else								/*En caso contrario continuamos*/
//		{
//			motorSetConfigSerialFlash++;
//		}
//		break;
		
//	case 1:
//		switch(EXTFLASH_ReadBytes( 0x1000, ptu8SaveSerial_data, 4 ))	/*Realizamos la lectura de 4 bytes a partir de la dirección 0x1000*/
//		{
//		case RUNNING:
//			break;

//		case SUCCESS:
//			if(strncmp(" BtOK ", (char *)ptu8SaveSerial_data , 4))	/*Si leemos que el boot está OK*/
//			{
//				SectorToRead= SectorSaveSerialFlash;				/*Identificamos los sectores para escribir o leer respecto al BOOT*/
//				SectorToWrite= SectorSaveSerialFlashSecurity;
//			}
//			else
//			{
//				SectorToRead= SectorSaveSerialFlashSecurity;		/*Identificamos los sectores para escribir o leer respecto al BOOT*/
//				SectorToWrite= SectorSaveSerialFlash;
//			}
//			motorSetConfigSerialFlash++;
//			break;

//		case ERROR:
//			motorSetConfigSerialFlash = 8;
//			bootErrSaveSerial= BOOT_SerialFlash_ErrorEscritura;
//			break;
			
//		default: break;
//		}
//		break;
			
//	case 2:
		
//		switch(EXTFLASH_ReadBytes(SectorToRead , BuffDataSeriaFlash , 0x1000))	/*Leemos el sector completo definido como de lectura (del BOOT)*/
//		{
//		case RUNNING:
//			break;

//		case SUCCESS:
//			motorSetConfigSerialFlash++;			/*Si se ha realizado la lectura con exito continuamos*/
//			break;
	
//		case ERROR:
//			motorSetConfigSerialFlash= 8;
//			bootErrSaveSerial= BOOT_SerialFlash_ErrorEscritura;
//			break;
			
//		default: break;
//		}
//		break;

//	case 3:
//		switch(EXTFLASH_EraseSector(SectorToWrite, 1 ))		/*Borramos el sector completo que se ha definido como de escritura (del BOOT)*/
//		{
//		case RUNNING:
//			break;

//		case SUCCESS:
//			motorSetConfigSerialFlash++;			/*Si se ha realizado la lectura con exito continuamos*/
//			break;

//		case ERROR:
//			motorSetConfigSerialFlash= 8;
//			bootErrSaveSerial= BOOT_SerialFlash_ErrorEscritura;
//			break;
			
//		default: break;
//		}
//		break;
					
//	case 4:
//		switch(EXTFLASH_WriteBytes(SectorToWrite , BuffDataSeriaFlash , 0x1000))	/*El buffer de entrada a la función lo escribimos en el sector seleccionado de escritura del BOOT*/
//		{
//		case RUNNING:
//			break;

//		case SUCCESS:
//			motorSetConfigSerialFlash++;			/*Si se ha realizado la lectura con exito continuamos*/
//			break;

//		case ERROR:
//			motorSetConfigSerialFlash= 8;
//			bootErrSaveSerial= BOOT_SerialFlash_ErrorEscritura;
//			break;
			
//		default: break;
//		}
//		break;
			
//	case 5:
//		switch(EXTFLASH_EraseSector(SectorToRead, 1 ))		/*Se borra el sector definico de lectura del BOOT*/
//		{
//		case RUNNING:
//			break;

//		case SUCCESS:
//			motorSetConfigSerialFlash++;			/*Si se ha realizado la lectura con exito continuamos*/
//			break;

//		case ERROR:
//			motorSetConfigSerialFlash= 8;
//			bootErrSaveSerial= BOOT_SerialFlash_ErrorEscritura;
//			break;
			
//		default: break;
//		}
//		break;

//	case 6:
//		// Los primeros 4 bytes se reservan para las firmas de la flash
//		sprintf((char *)BuffDataSeriaFlash,"BtOK");
											
//		for(i =   Address ; i < Address + nBytes; i++)		/*El buffer que se emplea para escritura/lectura, en la dirección dentro del propio sector se guarda la firma del BOOT OK*/
//		{
//			BuffDataSeriaFlash[i] = BuffSerialFlash[j];
//			j++;
//		}

//		switch(EXTFLASH_WriteBytes( SectorToRead, BuffDataSeriaFlash, 0x1000))	/*En el sector de lectura se escribe el mismo buffer que se ha empleado para escribir el de lectura pero con la firma de BOOT OK*/
//		{
//		case RUNNING:
//			break;

//		case SUCCESS:						/*En caso de tener exito se devuelve SUCCESS, y se continúa hacia el ultimo paso*/
//			bootErrSaveSerial= SUCCESS;
//			flagBootSaveSerialFlash=2;		/*??? - No se usa*/
//			motorSetConfigSerialFlash=9;
//			break;

//		case ERROR:
//			motorSetConfigSerialFlash= 8;
//			bootErrSaveSerial= BOOT_SerialFlash_ErrorEscritura;
//			break;
			
//		default: break;
//		}
//		break;
											
//	case 8:								/*En caso de error salta a este paso*/
//		free( BuffDataSeriaFlash );
//		motorSetConfigSerialFlash=0;
//		break;
								
//	case 9:
//		bootErrSaveSerial = BOOT_SerialFlash_EscrituraCorrecta;		/*Devuelve finalización de escritura correcta*/
//		free( BuffDataSeriaFlash );									/*Se libera la memoria Flash*/
//		motorSetConfigSerialFlash=0;								/*Se reinicia el motor del proceso*/
//		break;
		
//	default: break;
//	}
	return bootErrSaveSerial;
}

Boot_SerialFlashConfig_t BOOT_SaveConfigParamSerialFlash (uint8 *Buff)
{
	/* Declaración */
	Boot_SerialFlashConfig_t status_return;				/*Variable de retorno que indica el estado del proceso*/
	static BOOT_ConfigData_motor_SerialFlash Motor = Check_Size;		/*Variable de control para el motor del proceso*/
	uint8 Buff2write[CONFIG_PARAM_SERIAL_FLASH_SIZE+1];	/*Buffer que recogerá todos los datos más el Checksum*/
	uint16 i;											/*Variable auxiliar para bucles*/
	static uint8 Checksum;								/*Variable que recoge el Checksum*/
	
	uint8 a; /*DEBUG*/
	uint8 size;
	
	/* Inicialización */
	status_return = BOOT_SerialFlash_Running;
	
//	switch(Motor)
//	{
//	case Check_Size:
//		size = sizeof(Buff);
//		/*Evaluamos que el buffer de datos que nos pasa no supere el máximo reservado para almacenar la configuración*/
//		if(sizeof(Buff) > CONFIG_PARAM_SERIAL_FLASH_SIZE)
//		{
//			status_return = BOOT_SerialFlash_ErrorSize;
//		}	/*En caso de superarlo salimos dando un error*/
//		else
//		{
//			Motor = CalculateChecksum;
//		}						/*En caso de estar todo correcto pasamos al cálculo del CHECKSUM*/
//		break;
//	case CalculateChecksum:
//		for(i=0;i<CONFIG_PARAM_SERIAL_FLASH_SIZE;i++)			/*Se recorre todo el buffer para calcular el CHECKSUM*/
//		{
//			Checksum += Buff[i];
//		}
//		Checksum = !Checksum;
//		Motor = PrepareBuffer;									/*Una vez tenemos el Checlsu, pasamos al siguiente paso. preparar el buffer*/
//		break;
//	case PrepareBuffer:
//		for(i=0;i<CONFIG_PARAM_SERIAL_FLASH_SIZE;i++)			/*Se prepara el buffer con la misma información que el buffer de entrada más el CHECKSUM al final*/
//		{
//			Buff2write[i] = Buff[i];
//		}
//		Buff2write[CONFIG_PARAM_SERIAL_FLASH_SIZE] = Checksum;
//		Motor = EraseBlock;										/*Pasamos a borrar un bloque de memoria para guardar los parametros deseados*/
//		break;
//	case EraseBlock:
//		while(EXTFLASH_EraseSector(CONFIG_PARAM_SERIAL_FLASH_ADDR, 1 )== RUNNING);	/*Se borra un bloque de memoria*/
//		Motor = WriteSerialFlash;
//		break;
//	case WriteSerialFlash:
//		while(EXTFLASH_WriteBytes(CONFIG_PARAM_SERIAL_FLASH_ADDR , Buff2write , (CONFIG_PARAM_SERIAL_FLASH_SIZE+1)) == RUNNING);	/*Escribimos el contenido del buffer*/
//		status_return = BOOT_SerialFlash_EscrituraCorrecta;		/*Salimos indicando que el proceso ha finalizado con éxito*/
//		Checksum = 0;
//		Motor = Check_Size;										/*Reiniciamos el motor*/
//		break;
//	default: Motor = Check_Size; break;
//	}
	return status_return;
}

Boot_SerialFlashConfig_t BOOT_LoadConfigParamSerialFlash (uint8 *Buff)
{
	/* Declaración */
	Boot_SerialFlashConfig_t status_return;				/*Variable de retorno que indica el estado del proceso*/
	static BOOT_ConfigData_motor_SerialFlash Motor = ReadSerialFlash;		/*Variable de control para el motor del proceso*/
	uint8 Buff2read[CONFIG_PARAM_SERIAL_FLASH_SIZE+1];	/*Buffer que recogerá todos los datos más el Checksum*/
	uint16 i;											/*Variable auxiliar para bucles*/
	uint8 Checksum;										/*Variable que recoge el Checksum*/
	
	/* Inicialización */
	status_return = BOOT_SerialFlash_Running;
	
//	switch(Motor)
//	{
//	case ReadSerialFlash:
//		while(EXTFLASH_ReadBytes(CONFIG_PARAM_SERIAL_FLASH_ADDR , Buff2read , (CONFIG_PARAM_SERIAL_FLASH_SIZE+1)) == RUNNING);
//		Motor = EvaluateChecksum;
//		break;
//	case EvaluateChecksum:
//		for(i=0;i<CONFIG_PARAM_SERIAL_FLASH_SIZE;i++)
//		{
//			Checksum += Buff2read[i];
//		}
//		Checksum = !Checksum;
//		if(Checksum == Buff2read[CONFIG_PARAM_SERIAL_FLASH_SIZE])
//		{
//			for(i=0;i<CONFIG_PARAM_SERIAL_FLASH_SIZE;i++)
//			{
//				Buff[i] = Buff2read[i];
//			}
//			status_return = BOOT_SerialFlash_LecturaCorrecta;
//			Motor = ReadSerialFlash;
//		}
//		else
//		{	Motor = InicializeConfig;	}
//		break;
//	case InicializeConfig:
//		for(i=0;i<CONFIG_PARAM_SERIAL_FLASH_SIZE;i++)
//		{	Buff[i] = 0;	}
//		while(EXTFLASH_EraseSector(CONFIG_PARAM_SERIAL_FLASH_ADDR, 1 )== RUNNING);	/*Se borra un bloque de memoria*/
//		Motor = ReadSerialFlash;
//		status_return = BOOT_SerialFlash_LecturaCorrecta;
//		break;
//	default: Motor = ReadSerialFlash;	break;
//	}
	return status_return;
}

Boot_SerialFlashConfig_t BOOT_ConfigGetSerialFlash(uint32 Address, uint8 nBytes, uint8 *BuffSerialFlash)
{
	Boot_SerialFlashConfig_t bootErrReadSerial = BOOT_SerialFlash_Running;
	
	static uint8 ptu8GetSerial_data[20];
	
//	switch(motorGetConfigSerialFlash)
//	{
//	case 0:
//		if((Address+ nBytes-1) > 0x1000)
//		{
//			bootErrReadSerial = BOOT_SerialFlash_ErrorSize;
//		}
//		else
//		{
//			motorGetConfigSerialFlash++;
//		}
//		break;

//		case 1:
			
//			switch(EXTFLASH_ReadBytes( 0x1000, ptu8GetSerial_data, 4 ))
//			{
//			case RUNNING:
//				break;

//			case SUCCESS:
//				if(strncmp("BtOK", (char *)ptu8GetSerial_data , 4)==0)
//				{
//					SectorToRead2= SectorSaveSerialFlash;
//					SectorToWrite2= SectorSaveSerialFlashSecurity;
//				}
//				else
//				{
//					SectorToRead2 = SectorSaveSerialFlashSecurity;
//					SectorToWrite2 = SectorSaveSerialFlash;
//				}
//				motorGetConfigSerialFlash++;
//				break;

//			case ERROR:
//				motorGetConfigSerialFlash= 0;
//				bootErrReadSerial= BOOT_SerialFlash_ErrorLectura;
//				break;
				
//			default: break;	/* AÑADIDO SERGIO */
//			}
			
//			break;
				
//		case 2:
//			switch(EXTFLASH_ReadBytes(SectorToRead2+Address,BuffSerialFlash,nBytes))
//			{
//				case RUNNING:
//					break;
		
//				case SUCCESS:
//					bootErrReadSerial = BOOT_SerialFlash_LecturaCorrecta;
//					motorGetConfigSerialFlash= 0;
//					break;
		
//				case ERROR:
//					bootErrReadSerial= BOOT_SerialFlash_ErrorLectura;
//					motorGetConfigSerialFlash= 0;
//					break;
					
//				default: break;	/* AÑADIDO SERGIO */
//			}
			
//			break;
//		default: break;	/* AÑADIDO SERGIO */
//	}
	return bootErrReadSerial; 
}


/**********************************************************************************************
//Copia del CCN y LUT de una zona de la Flash a la Otra.
	//blockToReadCCN   				->origen
	//pageNumberToReadCCN 			->origen y destino. Numero de paginas a copiar	
	//blockCopySecurityWriteCNN   	->destino
	//blockToReadLUT				->origen
	//blockCopySecurityWriteLUT		->destino
	//pageNumberToReadLUT			->origen y destino. Numero de paginas copiar
************************************************************************************************/
void CNNandLUTCopySecurity(uint32 blockToReadCCN, uint32 pageNumberToReadCCN, uint32 blockCopySecurityWriteCNN,uint32 blockToReadLUT, uint32 pageNumberToReadLUT,  uint32 blockCopySecurityWriteLUT  )
{
	uint8_t    *WritePageBufferPtr = WritePageBuffer;
	uint8_t    *ReadPageBufferPtr =  ReadPageBuffer;
#ifdef BOOT_USE_NFC_DRIVER
	NfcInfo.CmdPending = TRUE;  // Indicamos que el dispositivo se encuentra en proceso de ejecución.
#endif
	uint32 i=0;
	uint32 pageNumberToReadLocal=0;
	LDD_TError ErrorCopySecurity=0;
	uint32_t aux;
	returnstatus_t ret;
	
//	// Copia  CCN
//#ifdef BOOT_USE_NFC_DRIVER
//	NfcInfo.hNfc = NFC1_Init(&NfcInfo);
//	NfcInfo.CmdPending = TRUE;
//	NFC1_EraseBlocks(NfcInfo.hNfc, 0,blockCopySecurityWriteCNN , blockEraseCCN);
//#else
//	aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(blockCopySecurityWriteCNN);
//	do
//	{
//		ret = EXTNAND_EraseBlocks(aux, blockEraseCCN);
//	}while(ret == RUNNING);
//#endif
	
//	if (ErrorCopySecurity != ERR_OK) {	return;	}
	
//	for( i=0; i< pageNumberToReadCCN; i++)
//	{
//#ifdef BOOT_USE_NFC_DRIVER
//		//NfcInfo.CmdPending  = TRUE;
		
//		while(NfcInfo.CmdPending){};
		
//		ErrorCopySecurity=NFC1_ReadPages(NfcInfo.hNfc, 0,  NFC_GetPageAddress(blockToReadCCN, pageNumberToReadLocal ), 1 , ReadPageBufferPtr);

//		if (ErrorCopySecurity != ERR_OK){	return;	}
		
//		//NfcInfo.CmdPending  = TRUE;
		
//		while(NfcInfo.CmdPending){};
		
//		ErrorCopySecurity=NFC1_WritePages(NfcInfo.hNfc, 0, NFC_GetPageAddress(blockCopySecurityWriteCNN, pageNumberToReadLocal ) ,1, ReadPageBufferPtr);
				
//		if (ErrorCopySecurity != ERR_OK) {	return;	}
//#else
//		aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(blockToReadCCN);
//		aux+=BOOT_CONVERT_NAND_PAGE_2_ADDR(pageNumberToReadLocal);
//		do
//		{
//			ret = EXTNAND_ReadBytes(aux, ReadPageBufferPtr, EXTERNAL_NAND_FLASH_PAGE_SIZE);
//		}while(ret == RUNNING);
//		if(ret == ERROR) {	return; }
		
//		aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(blockCopySecurityWriteCNN);
//		aux+=BOOT_CONVERT_NAND_PAGE_2_ADDR(pageNumberToReadLocal);
//		do
//		{
//			ret = EXTNAND_WriteBytes(aux, ReadPageBufferPtr, EXTERNAL_NAND_FLASH_PAGE_SIZE);
//		}while(ret == RUNNING);
//		if(ret == ERROR) {	return; }
//#endif
		
//		pageNumberToReadLocal++;
//	}
	
//	// Copia  LUT
//	pageNumberToReadLocal=0;
			
//#ifdef BOOT_USE_NFC_DRIVER
//	NFC1_EraseBlocks(NfcInfo.hNfc, 0,blockCopySecurityWriteLUT , blockEraseLUT);
//#else
//	aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(blockCopySecurityWriteLUT);
//	do
//	{
//		ret = EXTNAND_EraseBlocks(aux, blockEraseLUT);
//	}while(ret == RUNNING);
//#endif
	
//	pageNumberToReadLocal=0;
	
//	//NfcInfo.CmdPending  = TRUE;
	
	
//	/* AÑADIDO SERGIO */
	
	
	
//	for( i=0; i< pageNumberToReadLUT; i++)
//	{
//#ifdef BOOT_USE_NFC_DRIVER
//		//NfcInfo.CmdPending  = TRUE;
		
//		while(NfcInfo.CmdPending){};
		
//		ErrorCopySecurity=NFC1_ReadPages(NfcInfo.hNfc, 0,  NFC_GetPageAddress(blockToReadLUT, pageNumberToReadLocal ), 1 , ReadPageBufferPtr);

//		if (ErrorCopySecurity != ERR_OK){	return;	}
		
//		//NfcInfo.CmdPending  = TRUE;
		
//		while(NfcInfo.CmdPending){};
		
//		ErrorCopySecurity=NFC1_WritePages(NfcInfo.hNfc, 0, NFC_GetPageAddress(blockCopySecurityWriteLUT, pageNumberToReadLocal ) ,1, ReadPageBufferPtr);
				
//		if (ErrorCopySecurity != ERR_OK) {	return;	}
//#else
//		aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(blockToReadLUT);
//		aux+=BOOT_CONVERT_NAND_PAGE_2_ADDR(pageNumberToReadLocal);
//		do
//		{
//			ret = EXTNAND_ReadBytes(aux, ReadPageBufferPtr, EXTERNAL_NAND_FLASH_PAGE_SIZE);
//		}while(ret == RUNNING);
//		if(ret == ERROR) {	return; }
		
//		aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(blockCopySecurityWriteLUT);
//		aux+=BOOT_CONVERT_NAND_PAGE_2_ADDR(pageNumberToReadLocal);
//		do
//		{
//			ret = EXTNAND_WriteBytes(aux, ReadPageBufferPtr, EXTERNAL_NAND_FLASH_PAGE_SIZE);
//		}while(ret == RUNNING);
//		if(ret == ERROR) {	return; }
//#endif
		
//		pageNumberToReadLocal++;
//	}
	
	
	
//	/* AÑADIDO SERGIO */
	
//	/*
//	while(NfcInfo.CmdPending){};
	
//	ErrorCopySecurity= NFC1_ReadPages(NfcInfo.hNfc, 0,  NFC_GetPageAddress(blockToReadLUT, pageNumberToReadLocal ), 1 , ReadPageBufferPtr);
	
	
//	if (ErrorCopySecurity != ERR_OK) {	return;	}
	
//	//NfcInfo.CmdPending  = TRUE;
	
//	while(NfcInfo.CmdPending){};
		
//	ErrorCopySecurity= NFC1_WritePages(NfcInfo.hNfc, 0, NFC_GetPageAddress(blockCopySecurityWriteLUT, pageNumberToReadLocal ) ,1, ReadPageBuffer);
	
//	if (ErrorCopySecurity != ERR_OK){	return;	}
//	*/
}

int  DataCompare(uint8_t  s1[], uint8_t s2[] )
{		
	uint32 i=0;
	int aux=0;
//	size_t  n = NELEMS(s1);
						
//	for (i=0; i < n; i++)
//	{
//		if(s1[i] != s2[i])
//		{
//			aux=i;
//		}
//	}
	return aux;
}

void BOOT_REPARELUTandCCN()
{
	BootStatus= BOOT_STATUS_CHEKSectorsNand;
}

BOOTreturnstatus_t BOOTWriteLUT(void )
{
	uint32 i;
	uint8 AppMotorLTU=0;
//	FIL inputFile;
	uint8 ptu8FileName[60];
	uint32 USB_error;
	uint32 u32BytesWritten;
	BOOTreturnstatus_t ErrorWriteLTu= BootIDLE;
//	char *MFSfileNameLTU= "LUT.txt";
//	char*  MFSdirectoryNameLTU= "";
	uint8_t    *ReadPageBufferPtrLTU = ReadPageBuffer;
	uint32_t aux;
	returnstatus_t ret;
	/* UNUSED */
	uint8 ptu8File[1];
	uint8 ptu8BOOT_data[60];
	
//	MSD_Task();

//	Poll();
	
//	while((ErrorWriteLTu != NOTFOUNDFILE ) && (ErrorWriteLTu != BootERROR) &&  (ErrorWriteLTu != BootSUCCESS))
//	{
//		switch(AppMotorLTU)
//		{
//		case 0:
//			USB_error = MSDfileExist("LUT.txt", "", &i);

//			if(USB_error == K70_MSD_ERR_OK)
//			{
//#ifdef BOOT_USE_NFC_DRIVER
//				NfcInfo.hNfc = NFC1_Init(&NfcInfo);
//#endif
//				AppMotorLTU ++;
//			}
//			else{	AppMotorLTU = 0x80;	}/*Se ha producido un problema, indicamos que se tiene que desconectar el USB y volverlo a conectar*/
//			break;
			
//		case 1:
//			strcpy(ptu8FileName, MFSdirectoryNameLTU);
//			strcat(ptu8FileName, MFSfileNameLTU);

//			USB_error = MSDopenFile(&inputFile, ptu8FileName, FA_WRITE);

//			if(USB_error == K70_MSD_ERR_OK){	AppMotorLTU++;	}
//			break;

//		case 2:
//			/* MODIFICADO SERGIO */
			
//			for( i=0; i< pageNumberLUT; i++)
//			{
//#ifdef BOOT_USE_NFC_DRIVER
//				NfcInfo.CmdPending  = TRUE;
				
//				NFC1_ReadPages(NfcInfo.hNfc, 0,  NFC_GetPageAddress(NandBlockWriteLUT, i ), 1 , ReadPageBufferPtrLTU);
				
//				while(NfcInfo.CmdPending){};
//#else
//				aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(NandBlockWriteLUT);
//				aux += BOOT_CONVERT_NAND_PAGE_2_ADDR(i);
//				do
//				{
//					ret = EXTNAND_ReadBytes(aux, ReadPageBufferPtrLTU, EXTERNAL_NAND_FLASH_PAGE_SIZE);
//				}while(ret == RUNNING);
//#endif
				
//				USB_error = MSDwriteFile(&inputFile, ReadPageBufferPtrLTU, 2048 , &u32BytesWritten);
//			}
			
//			/* MODIFICADO SERGIO */
			
////			NfcInfo.CmdPending = TRUE;
////
////			NFC1_ReadPages(NfcInfo.hNfc, 0,  NFC_GetPageAddress(NandBlockWriteLUT, 0 ), 1 , ReadPageBufferPtrLTU);
////
////			while(NfcInfo.CmdPending){};
////			USB_error = MSDwriteFile(&inputFile, ReadPageBufferPtrLTU , 2048 , &u32BytesWritten);
								
//			AppMotorLTU++;
//			break;

//		case 3:
//			USB_error = MSDcloseFile(&inputFile);

//			AppMotorLTU = 0;

//			ErrorWriteLTu= BootSUCCESS;
//			break;

//		// No esta el archivo
//		case 0x80:
//			ErrorWriteLTu=   NOTFOUNDFILE;
//			break;
			
//		case 0x90:
//			// Falta indicar que devuleva algún tipo de error.
//			ErrorWriteLTu= BootERROR;
//			break;
			
//		default: break;
//		}
//	}
	return ErrorWriteLTu;
}

BOOTreturnstatus_t BOOTWriteCCN(void)
{	
	uint32 i;
	uint8 AppMotorLTU=0;
//	FIL inputFile;
	uint8 ptu8FileName[60];
	uint32 u32BytesWritten;
	uint32 USB_error;
	BOOTreturnstatus_t ErrorWriteLTu= BootIDLE;
//	char *MFSfileNameCNN= "CCN.txt";
//	char*  MFSdirectoryNameCCN= "";
	uint8_t    *ReadPageBufferPtrCCN = ReadPageBuffer;
	uint32_t aux;
	returnstatus_t ret;
	/* UNUSED */
	uint8 ptu8File[1];
	uint8 ptu8BOOT_data[60];
	
//	MSD_Task();

//	Poll();
	
//	while(((ErrorWriteLTu != NOTFOUNDFILE ) && (ErrorWriteLTu != BootERROR)) &&  (ErrorWriteLTu != BootSUCCESS))
//	{
//		switch(AppMotorLTU)
//		{
//		case 0:
//			USB_error = MSDfileExist("CCN.txt", "", &i);

//			if(USB_error == K70_MSD_ERR_OK){	AppMotorLTU ++;	}
//			else{	AppMotorLTU = 0x80;	}/*Se ha producido un problema, indicamos que se tiene que desconectar el USB y volverlo a conectar*/
//			break;
			
//		case 1:
//			strcpy(ptu8FileName, MFSdirectoryNameCCN);
//			strcat(ptu8FileName, MFSfileNameCNN);

//			USB_error = MSDopenFile(&inputFile, ptu8FileName, FA_WRITE);

//			if(USB_error == K70_MSD_ERR_OK){	AppMotorLTU++;	}
//			break;

//		case 2:
//			for( i=0; i< pageNumberCNNN; i++)
//			{
//#ifdef BOOT_USE_NFC_DRIVER
//				NfcInfo.CmdPending  = TRUE;
				
//				NFC1_ReadPages(NfcInfo.hNfc, 0,  NFC_GetPageAddress(NandBlockWriteCCN, i ), 1 , ReadPageBufferPtrCCN);
				
//				while(NfcInfo.CmdPending){};
//#else
//				aux = BOOT_CONVERT_NAND_BLOCK_2_ADDR(NandBlockWriteCCN);
//				aux += BOOT_CONVERT_NAND_PAGE_2_ADDR(i);
//				do
//				{
//					ret = EXTNAND_ReadBytes(aux, ReadPageBufferPtrCCN, EXTERNAL_NAND_FLASH_PAGE_SIZE);
//				}while(ret == RUNNING);
//#endif
				
//				USB_error = MSDwriteFile(&inputFile, ReadPageBufferPtrCCN, 2048 , &u32BytesWritten);
//			}
//			AppMotorLTU++;

//		case 3:
//			USB_error=MSDcloseFile(&inputFile);

//			AppMotorLTU=0;

//			ErrorWriteLTu= BootSUCCESS;
//			break;

//		// No esta el archivo
//		case 0x80:
//			ErrorWriteLTu=   NOTFOUNDFILE;
//			break;
			
//		case 0x90:
//			// Falta indicar que devuleva algún tipo de error.
//			ErrorWriteLTu= BootERROR;
//			break;
		
//		default: break;
//		}
//	}
	return ErrorWriteLTu;
}


