/*
 * Expansora.h
 *
 *  Created on: Mar 7, 2019
 *      Author: dbelmonte
 */


/*** NOTAS ***/
/*
 * Todo lo que lleva el tag "UC" hace referencia a la construcción de la maquina Define y no a la PCB
 * expansora. Esto es para distinguir aquello que en futuras maquinas con expansora tendrá que cambiar.
 * Es aconsejble pasar todo a un modulo UC especifico para facilitar la comprension y el mantenimiento.
 */

#ifndef EXPANSORA_H_
#define EXPANSORA_H_

/*** INCLUDES ***/
#include "../GeneralDefines.h"
//#include "../App.h"

/*** CONSTANTES ***/
/*
 * Constanes generales de tamaños de las estructuras de datos de la expansora, estan en el header
 * para poder declarar los vectores.
 */
#define EXP_MAX_PERIF 7 						//Numero máximo de perifericos admitidos, son a nivel HW

#define EXP_GPERIF_GENERAL_DATA_SIZE 52			//Tamaño de los datos generales de un periferico
#define EXP_REMAP_STRUCTS_SIZE 8				//Tamaño de las estructuras de remapeo
#define EXP_DATA_HEADER_SIZE 64					//Tamaño de la cabecera del protocolo, esto deberia estar en PROTOCOLMASER
#define EXP_UC_PCB_HEADER_SIZE 64				//Tamaño de la cabecera del protocolo, esto deberia estar en PROTOCOLMASTER

/*
 * Estas constantes ya no son propias de la expansora sino que son de la construcción de la UC. Es decir,
 * deberían ir en un modulo UC a parte de este para conservar la abstracción del modulo expansora.
 * Aqui se tendrán en cuenta cosas como que la maquina tiene 4 "ramas" para los 4 manipulos.
 */
#define EXP_UC_COMMON_VARS1_SIZE 28				//Tamaño de las variables comunes1 de la UC
#define EXP_UC_COMMON_VARS2_SIZE 84				//Tamaño de las variables comunes2 de la UC
#define EXP_UC_NUM_HANDPIECES 4					//Número de manípulos aceptado por la UC
#define EXP_UC_HANDPIECE_SENSORS_SIZE 12		//Tamaño de los datos de sensor de la UC vinculados al HP
#define EXP_UC_HANDPIECE_VARS_SIZE 36			//Tamaño de las variables de la UC vinculadas al HP
#define EXP_UC_LVL_DETECTOR_VARS_SIZE 16		//Tamaño de las variables leidas del detector de nivel
#define EXP_UC_NUM_PCB_PWR_SUPPLY 2				//Número de PCBs de fuentes en la UC		
#define EXP_UC_NUM_PCB_COMPLEMENT 10			//Número de PCBs de complementos en la UC
#define EXP_UC_PCB_PWR_SUPPLY_VARS_SIZE 36		//Tamaño de las variables leidas de la PCB de fuentes
#define EXP_UC_PCB_COMPLEMENT_VARS_SIZE 40		//Tamaño de las variables leidas de la PCB complementos

#define EXP_UC_FATIGA_WAIT_SKIP_CLEANUP_STOP	30000
#define EXP_UC_FATIGA_TRT_TEST_TIME				4200000

#define EXP_UC_FATIGA_LIM_MIN_VACC			270
#define EXP_UC_FATIGA_VAC_LOSS_LIM			21.0	/*3mbar * 10min de TRT (70min -> 21mbar)*/
#define EXP_UC_FATIGA_LIM_MIN_CAUDAL		0.5
#define EXP_UC_FATIGA_LIM_MAX_CAUDAL		1.1
#define EXP_UC_FATIGA_DELAY_CHECK_VALUES	90000	/*Tiempo de espera para que se estabilicen los valores antes de comprobar sus límites*/

#define EXP_UC_CONFIG_PARAMETERS_NUM		30 // #JM_GPRS previamente 9 +  los 21 de los parametros V7790

#define EXP_UC_REUSE_LABEL_STOP_LIMIT		1200000	/* 20 minutos */	//V7775
#define EXP_UC_REUSE_LABEL_TIME_LIMIT		7200000	/* 120 minutos */	//V7775

#define EXP_UC_ONE_SEC				1	//V7775

#define EXP_UC_COMMON_VARS1_ADDR_TEMP_SAFE_FROST	147	/* V7790 */
#define EXP_UC_COMMON_VARS1_SIZE_TEMP_SAFE_FROST	36	/* V7790 */

#define EXP_UC_LOOP_TIME_GETTING_MCC	300000 // #JM_GPRS bajamos de 15 a 5 minutos 900000	// V7790 - GPRS get MCC - Loop = 15minutos = 15*60*1000 = 900000

/*
 * Vector que relaciona el indice de manipulo (0 a 3) con su posicion HW real (1 a 4) 
 * en el array de perifericos. Usado para el refresco de las variables internas de la maquina 
 * relativas a los HP.
 */
static const uint8 EXP_UC_HANDPIECE_HW_PERIF_POS[EXP_UC_NUM_HANDPIECES] =
{
		1, 	// Indice de periferico HW del HP1
		2, 	// Indice de periferico HW del HP2
		3, 	// Indice de periferico HW del HP3
		4  	// Indice de periferico HW del HP4
};

/*
 * Sentido de las tramas de remapeo de los perifericos, se usa en el modulo HPcryo en su array de tramas
 */
typedef enum
{
	FAT_VAL_PresionHP1,
	FAT_VAL_PresionHP2,
	FAT_VAL_PresionHP3,
	FAT_VAL_PresionHP4,
	FAT_VAL_CaudalHP1,
	FAT_VAL_CaudalHP2,
	FAT_VAL_CaudalHP3,
	FAT_VAL_CaudalHP4,
	FAT_VAL_Rth,
	FAT_VAL_retTemp,
	FAT_VAL_retFlow,
	FAT_VAL_pumpTemp,
	FAT_VAL_envTemp,
	FAT_VAL_Vtob,
	FAT_VAL_CPI,
	FAT_VAL_ErrorHP1,
	FAT_VAL_ErrorHP2,
	FAT_VAL_ErrorHP3,
	FAT_VAL_ErrorHP4,
	FAT_VAL_ErrorMaq,
	
	FatMaxValues
}cEXP_UCfatigueValues;

typedef enum
{
	EXP_UC_FATIGUE_VALUE_UNCHECKED,
	EXP_UC_FATIGUE_VALUE_OK,
	EXP_UC_FATIGUE_VALUE_WRONG,
	EXP_UC_FATIGUE_VALUE_VAC_RESUCTION,
	
	EXP_UC_FATIGUE_MAX_VALUE_STATUS
}cEXP_UCfatigueValuesStatus;

typedef enum
{
	EXP_REMAP_FRAME_DIR_IN = 0,
	EXP_REMAP_FRAME_DIR_OUT = 1
}cEXPremapFramDir;

typedef enum
{
	EXP_UC_FATIGUE_CHECK_FILTER,
	EXP_UC_FATIGUE_CHECK_SETA,
	EXP_UC_FATIGUE_CHECK_RFID,
	EXP_UC_FATIGUE_CHECK_VAC_HP1,
	EXP_UC_FATIGUE_CHECK_VAC_HP2,
	EXP_UC_FATIGUE_CHECK_VAC_HP3,
	EXP_UC_FATIGUE_CHECK_VAC_HP4,
	EXP_UC_FATIGUE_TRT_VAC_HP1,
	EXP_UC_FATIGUE_TRT_VAC_HP2,
	EXP_UC_FATIGUE_TRT_VAC_HP3,
	EXP_UC_FATIGUE_TRT_VAC_HP4,
	EXP_UC_FATIGUE_TST_PELTIERS,
	EXP_UC_FATIGUE_DONE,
	EXP_UC_FATIGUE_FAIL,
	
	EXP_UC_FATIGUE_MAX_STEPS
}cEXP_UCfatigueSteps;

typedef enum
{
	EXP_UC_FATIGUE_STEP_TO_DO,
	EXP_UC_FATIGUE_STEP_DOING,
	EXP_UC_FATIGUE_STEP_DONE,
	EXP_UC_FATIGUE_STEP_ERROR,
	
	EXP_UC_FATIGUE_MAX_STATUS
}cEXP_UCfatigueStatus;

/*
 * Estructura de datos de configuración que se graban en la memoria FLASH externa
 * */
typedef union
{
	struct
	{
		uint8 ModeResuctionsViewer;
		uint8 ModeTemperatureViewer;
		uint8 ModeTempOscIDLE;
		uint8 ModeRecicleLabel;
		uint8 ModeTempSlope;
		uint8 ModeTempSecure;
		uint8 ModeErrSec;
		uint8 ModeErrDeltaTempSec;
		uint8 ModeRecLOG;
		//uint8 Language;
		//uint8 Country;		//V7790 - DISCLAIMER
		//uint8 Month_ref;	//V7790 - DISCLAIMER
		uint8 GPRS_iniciado;
		uint16 MCC[10];
	}data;
	uint8 vector[EXP_UC_CONFIG_PARAMETERS_NUM];
}EXP_UC_Config_Param;


/*
 * Cabecera del protocolo para todas las PCB que lo usen, esto debería estar en PROTOCOLMASTER
 */
typedef union
{
	cabecera_fw_t fields;
	uint8 vector[EXP_DATA_HEADER_SIZE];
}tEXPheader;

/*
 * Estructura de remapeo de las tramas de periferico.
 */
typedef union
{
	struct
	{
		uint8 id[4];						//ID de la trama, normalmente el ultimo byte se usa de version
		uint16 dirRelToBuff;				//Dirección inicial de la trama en el buffer de remapeo relativa a este
		uint8 nBytes;						//Numero de bytes de la trama
		uint8 dummy;						//Ajuste de boundary a 32
	}fields;
	uint8 vector[EXP_REMAP_STRUCTS_SIZE];	//Para las transmisiones poder hacerlas directamente
}tEXPremap;

/*
 * Estructura general de periferico de expansora. Datos comunes a todo periferico
 */
typedef struct
{
	uint8 isEnabled;						//Indica si el periferico esta habilitado
	uint8 isInit;							//Indica si el periferico esta listo para trabajar con él (Esta presente y la expansora ya comunica)
	uint8 isSPIok;							//Indica si hay error de comunicaciones de SPI. Se resetea automaticamente 
	
	/* Common data */
	union
	{
		struct
		{
			uint32 serialNum[3];						//Numero de serie del periferico			
			uint32 model;								//Modelo del periferico
			uint16 nPowerSuppliesUsed;					//Numero de F.A. que utiliza	
			uint16 version;								//Versión del periferico
			uint32 Maxbuffer;							//???
			uint8 versionDataBlock[30];					//???
		}fields;
		uint8 vector[EXP_GPERIF_GENERAL_DATA_SIZE];		//Para las transmisiones poder hacerlas directamente
	}data;		
}tEXPperif;

/*
 * Estructura de "inputs" en la placa expansora
 */
typedef union
{
	struct
	{
		uint16 slot0:1;			//RAC	
		uint16 slot1:1;				
		uint16 slot2:1;				
		uint16 detectM1:1;				
		uint16 detectM2:1;				
		uint16 detectM3:1;				
		uint16 detectM4:1;				
		uint16 pedal_a:1;		//Dos posiciones del pedal		
		uint16 pedal_c:1;				
		uint16 alarma_gral:1;	//SETA			
		uint16 puerta_vac:1;				
		uint16 puerta_iza:1;				
		uint16 puerta_dcha:1;				
		uint16 puerta_elec:1;				
		uint16 puerta_tobera:1;		
	}bits;
	uint16 word;
}tUCinputs;

/*
 * Estructura de datos comunes 1. Estan separados por el agrupamiento en la memoria de la expansora.
 * De este modo es mas facil enviarlos por el protocolo. Por eso hay el comunes 2.
 */
typedef union
{
	struct
	{
		tUCinputs status;  			//Estado de las entradas (filtradas)
		tUCinputs actions; 			//no se usa
		float envTemp;				//Temperatura ambiente
		float radOutTemp;			//Temperatura de salida del radiador
		float pumpOutTemp;			//Temperatura de salida de la bomba
		float waterPressure;		//Presión hidráulica
		float returnFlow;			//Caudal total de retorno
		float returnTemp;			//Temperatura media de retorno
	}fields;
	uint8 vector[EXP_UC_COMMON_VARS1_SIZE];		//Para las transmisiones poder hacerlas directamente
}tUCcommonData1;

/*
 * Estructura de datos comunes 2.
 */
typedef union
{
	struct
	{
		uint32 vacumConfigTonEV; 						//Tiempo de la "aceleración" al hacer el vacum
		uint16 vacumConfigPumpDuty; 					//Duty cycle de la bomba de vacum cuando no acelera
		uint16 temporaryEnabledPerif;					//Cuando vale 0 tenemos problemas de COM con ese periferico. 
		uint8 vacumRetrysCnt[EXP_UC_NUM_HANDPIECES];	//Numero de resucciones por manipulo
		uint32 enabled485devices;						//Cuando vale 0 tenemos problemas de COM con ese complemento
		float vacumRetryFactor[EXP_UC_NUM_HANDPIECES];	//Tanto por uno al que volverá a resuccionar respecto a la consigna (0.1)
		float vacumLungFactor[EXP_UC_NUM_HANDPIECES]; 	//Tanto por uno que pasamos la consigna de vacum para compensar el efecto pulmon (1.1)
		float consWaterPump;							//Consumo de la bomba de agua
		float consRadFan;								//Consumo del ventilador del radiador
		float cons24V_HP[EXP_UC_NUM_HANDPIECES];		//Consumo de los 24V de cada manípulo
		uint32 serialNum[3];							//Numero de serie ???
	}fields;
	uint8 vector[EXP_UC_COMMON_VARS2_SIZE];				//Para las transmisiones poder hacerlas directamente
}tUCcommonData2;

/*
 * Requerimientos de los manipulos a la expansora
 */
typedef union
{
	struct
	{
		uint8 cooling:1;		//Hidraulica
		uint8 vacum:1;			//Vacum
		uint8 src_adj:1;		//???
		uint8 rf:1;				//???
		uint8 power:1;			//???
		uint8 dummy:3;
	}bits;
	uint8 byte;
}tUChandPieceControls;

/*
 * Estructura con los datos de sensores y variables de la epansora referentes a los manipulos o
 * a las 4 "ramas" internas de la maquina. Habra una por cada manipulo o rama
 */
typedef struct
{
	union
	{
		struct
		{
			float returnFlow;								//Caudal de retorno 
			float returnTemp;								//Temperatura de retorno
			float vacum;									//Presión de vacum
		}fields;
		uint8 vector[EXP_UC_HANDPIECE_SENSORS_SIZE];		//Para las transmisiones poder hacerlas directamente
	}sensors;
	
	union
	{
		struct
		{
			uint8 status;								//???
			uint8 boardStatus;							//???
			uint8 boardAlarm;							//???
			uint8 performanceCalcOnOff; 				//ON/OFF del calculo del Qsobra
			tUChandPieceControls requestedCtrls; 		//Peticion de HP
			tUChandPieceControls inUseCtrls; 			//EXP esta trabajando
			tUChandPieceControls readyCtrls; 			//Ha terminado
			uint8 dummy;								//Alineación 32 bits
			float maxInWaterTemp;						//Temperatura máxima de entrada del agua al manipulo
			float minFlow;								//Mínimo caudal aceptado
			float vacumSetPoint;						//Consigna de vacum puesta por el manípulos
			float PS1voltagePerCent;					//Potencia en la F.A 1 de las peltiers
			float PS2voltagePerCent;					//Potencia en la F.A 2 de las peltiers
			float radPerformance;						//???
			float radPerformanceFactor; 				//Factor al calculo del Qsobra
		}fields;
		uint8 vector[EXP_UC_HANDPIECE_VARS_SIZE];		//Para las transmisiones poder hacerlas directamente
	}vars;
}tUChandPieceData;

/* Cabecera generica de PCB de complementos y fuentes */
typedef union
{
	cabecera_fw_t fields;
	uint8 vector[EXP_UC_PCB_HEADER_SIZE];
}tUC_PCBheader;

/* Estructura de datos de la PCB detectora de nivel de H2O */
typedef struct
{	
	tUC_PCBheader hdr;
	
	union
	{
		struct
		{
			union
			{
				struct
				{
					uint8 lvl0:1;
					uint8 lvl1:1;
					uint8 lvl2:1;
					uint8 dummy:5;
				}bits;
				uint8 byte;
			}level;
			
			uint8 dummy[3];
			float lvlRaw[3];
		}fields;
		uint8 vector[EXP_UC_LVL_DETECTOR_VARS_SIZE];
	}vars;
}tUC_PCBlevelDetector;

/* Estructura de datos de la PCB de fuentes */
typedef struct
{
	tUC_PCBheader hdr;
	
	//la union de turno
}tUC_PCBpwrSupply;

/* Estructura de datos de la PCB de complementos */
typedef struct
{
	tUC_PCBheader hdr;
	
	//la union de turno
}tUC_PCBcomplement;

typedef struct
{
	float Rth;
	float retTemp;
	float retFlow;
	float pumpTemp;
	float envTemp;
	float Vtob;
	float CPI;
	float Caudal1;
	float Caudal2;
	float Caudal3;
	float Caudal4;
	float Presion1;
	float Presion2;
	float Presion3;
	float Presion4;
	
}cEXP_UCfatigueERROR;

typedef struct
{
	cEXP_UCfatigueStatus status[EXP_UC_FATIGUE_MAX_STEPS];
	cEXP_UCfatigueSteps step;
	uint8 substeps;
	
	cEXP_UCfatigueERROR FatigueError;
}tUC_FatigueData;

typedef struct
{
	uint8 label_type;
	uint32 time_ref_read;
	uint32 time_trt_remain;
	uint32 time_trt_stop;
	
	uint8 allowReuseLabel;
	
}tEXP_UCreuseLabelData;

/*
 * Estructura general de datos de la expansora. Incluye la mayoria de estructuras anteriores
 */
typedef struct
{	
	union
	{
		struct
		{
			uint8 header:1;				//Cabecera de la PCB expansora
			uint8 perifs:1;				//Datos de perifericos en general
			uint8 common1:1;			//Datos comunes 1 de UC
			uint8 common2:1;			//Datos comunes 2 de UC
			uint8 HP:1;					//Datos de los manípulos
			uint8 cfg:1;				//Configuraciones iniciales
			uint8 err:1;				//Generación de errores
			uint8 PCBs:1;				//Lecturas de variables del resto de las PCBs (Nivel, fuentes, complementos)
		}bits;
		uint8 byte;
	}dataToGet;							//Flags para indicar que se refresca en el bucle principal
	
	uint8 newPerif[EXP_MAX_PERIF];
	tEXPperif perif[EXP_MAX_PERIF];
	
	
	tEXPheader header;					//Cabecera de la PCB expansora
	struct
	{
		tUCcommonData1 commonData1;								//Estructura con los datos comunes 1 de UC
		tUCcommonData2 commonData2;								//Estructura con los datos comunes 2 de UC
		tUChandPieceData handPieceData[EXP_UC_NUM_HANDPIECES];	//Vector con las estructuras de datos de los 4 HP
		tUC_PCBlevelDetector PCBlvlDetector;
		tUC_PCBpwrSupply PCBpwrSupply[EXP_UC_NUM_PCB_PWR_SUPPLY];
		tUC_PCBcomplement PCBcomplement[EXP_UC_NUM_PCB_COMPLEMENT];
		float radFanVoltage;									//Provisional, hay que montarlo bien PDTE
		float CPI;												//Provisional, hay que montarlo bien PDTE
		
		EXP_UC_Config_Param Config_Param;
		
		tUC_FatigueData FatigueProcess;
		uint8 FatigaStartStop;
		uint32 FatigaTime;
		float FatigaPresion_ref[EXP_UC_NUM_HANDPIECES];
		uint8 FatigaCountResuc[EXP_UC_NUM_HANDPIECES];
	}UC;
}tEXPdata;

/*** VARIABLES GLOBALES PUBLICAS ***/
extern tEXPdata EXPdata;

/*** FUNCIONES PUBLICAS ***/
void EXPinit( void);
uint8 EXPupdate( uint32 loopTime);
uint8 EXP_UCgetStdBy( void);
returnstatus_t EXP_UCexitStandby (void);

/*** ***/
uint8 EXPfoundNewPerif( uint8 *indexNewPerif);
returnstatus_t EXPsendRemap( tEXPremap *remap, uint8 IDperifHW, uint8 slot, cEXPremapFramDir frameDir);
returnstatus_t EXPremapFrameGetData( uint32 dirRelToBuff, uint8 nBytes, uint8 *buffer);
returnstatus_t EXPremapFrameSetData( uint32 dirRelToBuff, uint8 nBytes, uint8 *buffer);
returnstatus_t EXPenableDisablePerif( uint8 indexPerif, uint8 enableDisable);
returnstatus_t EXP_UCconfigVacumPumpBehaviour( uint32 TonEV, uint16 pumpDuty);
returnstatus_t EXP_UCconfigHPvacumFactors( float retryFactor, float lungFactor, uint8 slot);
returnstatus_t EXP_UCconfigHPoverHeat( uint8 OnOff, float performanceFactor, uint8 slot);
uint8 EXP_UCgetVacumRetrys( uint8 slot);
returnstatus_t EXP_UChandleVentEV( uint8 openClose);

uint32 EXP_UCgetPS0alarmFlags( void);
uint32 EXP_UCgetPS1alarmFlags( void);
uint32 EXP_UCgetEXPalarmFlags( void);

uint8 EXP_UCgetLevelHighWater( void);

float EXP_UCgetEnvTemp ( void);
uint8 EXP_UCoscTempStatus (void);
uint8 EXP_UCresuctionsViewer (void);
uint8 EXP_UCtempViewer (void);
uint8 EXP_UCtempSlopeStatus (void);
uint8 EXP_UCtempSecureStatus (void);
uint8 EXP_UCerrSecureStatus (void);
uint8 EXP_UCerrDeltaTempSecureStatus (void);
uint8 EXP_UCreuseLabelModeStatus (void);
uint8 EXP_UC_RecLOG_Status (void);
//uint8 EXP_UC_get_Language (void);
//void EXP_UC_set_Language (uint8 Language);
/*
uint8 EXP_UC_get_Country (void);			//V7790 - DISCLAIMER
void EXP_UC_set_Country (uint8 Country);	//V7790 - DISCLAIMER
uint8 EXP_UC_get_Month_REF (void);			//V7790 - DISCLAIMER
void EXP_UC_set_Month_REF (uint8 Month);	//V7790 - DISCLAIMER
void EXP_UC_Check_Month (void);				//V7790 - DISCLAIMER
*/
float EXP_UCfatigaGetErrorValues(cEXP_UCfatigueValues val);
void EXP_UCfatigaSetErrorValues (void);
void EXP_UCfatigaStart( void);
void EXP_UCfatigaStop( void);
cEXP_UCfatigueSteps EXP_UCfatigaStatus ( void);
uint8 EXP_UCfatigaVerif( void);
void EXP_UCfatiga_init ( void);
void EXP_UCfatigaDataUpdate(float *Rth, float *retTemp, float *retFlow, float *pumpTemp, float *envTemp, float *Vtob, float *CPI, float *CaudalRetornoHP1, float *CaudalRetornoHP2, float *CaudalRetornoHP3, float *CaudalRetornoHP4, uint32 *Fatigue_time, float *PresionHP1, float *PresionHP2, float *PresionHP3, float *PresionHP4);
uint8 EXP_UCfatigaErrUpdate(uint8 Perif);
cEXP_UCfatigueValuesStatus EXP_UCfatigaCheckValue(cEXP_UCfatigueValues value_type, float value);
uint8 EXP_UCfatigaVerif( void);
void EXP_UCfatiga ( void);

uint32 EXP_UCerroresSAT(uint8 Perif);

void EXPhabilitarPeriferico(uint8 Periferico);
void EXPdeshabilitarPeriferico(uint8 Periferico);

/*REUSE label functions*/
void EXP_UCperifNEWlabel (uint8 periferico, uint8 label, uint32 TRTtime);
void EXP_UCupdateTRTtimeReuseLabel (uint8 periferico, uint32 TRTtime);
uint8 EXP_UCreuseLabel (uint8 periferico, uint8 labelRq);
uint8 EXP_UCreuseLabelAllow(uint8 periferico);
uint32 EXP_UCreuseLabelTRTtime(uint8 periferico);
uint8 EXP_UCreuseLabelType (uint8 periferico);

returnstatus_t EXPwriteDebugData( uint8 *buffer, uint8 num_bytes, uint32 addr, uint8 mem_id);
returnstatus_t EXPreadDebugData( uint8 *buffer, uint8 num_bytes, uint32 addr, uint8 mem_id);

void saveMMC(uint8 conf, uint16 *toSaveMCC);

#endif /* EXPANSORA_H_ */
