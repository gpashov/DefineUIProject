/*
 * GeneralDefines.h
 *
 *  Created on: Nov 15, 2016
 *      Author: ingenieria1
 */

#ifndef GENERALDEFINES_H_
#define GENERALDEFINES_H_



#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
//cp#include "main.h"

/* Other basic data types */
typedef signed char             int8;
typedef signed short int        int16;
typedef signed long int         int32;

typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned long int       uint32;

/*Previes ini*/ //cris:modificat
#define WIFI_MAX_SSID_LENGHT	16
#define WIFI_MAX_PSWD_LENGHT	16

typedef enum
{
	
	RUNNING = -2,
	
	ERROR = -1,
	
	IDLE = 0,
	
	SUCCESS = 1,
	
	BLOCKING=3,
			
}returnstatus_t;



/*Previes fin*/

//typedef enum //cris:modificat
//{
//	RUNNING_HTP = -2,
//	ERROR_HTP = -1,
//	IDLE_HTP = 0,
//	SUCCESS_HTP = 1,
//	BLOCKING_HTP=3,
//}returnstatus_prot_t;

#define PROTSPI_MAX_BUFFER						512

#define ID_BROADCAST										0
#define FUENTE_ID_PRINCIPAL								1
#define FUENTE_ID_SECUNDARIA							2
#define COMPLEMENTO_ID_PERD_VAC1					3
#define COMPLEMENTO_ID_REBOSADERO					4
#define COMPLEMENTO_ID_AGUA_M1						5
#define COMPLEMENTO_ID_AGUA_M4						6
#define COMPLEMENTO_ID_AGUA_M2						7
#define COMPLEMENTO_ID_AGUA_M3						8
#define COMPLEMENTO_ID_VACUM_M1					9
#define COMPLEMENTO_ID_VACUM_M2					10
#define COMPLEMENTO_ID_VACUM_M3					11
#define COMPLEMENTO_ID_VACUM_M4					12
#define MAX_ESCLAVOS_PUERTO_SENSORICA			12

//#define COMPLEMENTO_ID_PERD_VAC2 					0xFF		/* NO APLICA */

#define MAX_PCB_EXP						1 //cris
#define MAX_PCB_GDISP					4 //cris: 1:RFID 2:RF1 3:RF2 4:EXP
#define MAX_PCB_FUENTES				2
#define MAX_PCB_COMPLEMENTOS	10  /* solo hay una valv de perdidas */

#define EXP_DEFAULT_ADDR            0x04 // Indice del tipo de comunicación. En este caso corresponde a la expansora.
#define EXP_BOARD_TYPE              0x01

#define EXP_MIN_SLOT				2
#define EXP_MAX_SLOT				2

#define EXP_FW_VERSION                  0x01

#define EXP_MAX_BUF_RX                  0xFF

#define EXP_INTERNAL_USED_RAM_SIZE      sizeof(memory_map_t) //falta: modificar nomes memory map expansora
#define EXP_INTERNAL_RAM_SIZE           	3896
#define EXP_INTERNAL_FLASH_SIZE    		65535
#define EXP_UNDEFINED_3_SIZE           		1024
#define EXP_GESTION_PERIF_SIZE				sizeof(gestion_perifericos_t)//cris: gestion perifericos falta: comprovar que sigui ok al finalitzar els periferics
#define EXP_DEBUG_RAM_SIZE      			sizeof(debug_map_expansora_t) //cris: puente protocolo + debug
#define EXP_UNDEFINED_6_SIZE            	123
#define EXP_UNDEFINED_7_SIZE        		0

#define EXP_MAX_BUFFER_DATA_MANIPULO	5120//256
#define EXP_MAX_REMAP_DATA_IN				8
#define EXP_MAX_REMAP_DATA_OUT				8
#define EXP_MAX_PERIFERICOS_DEFINIDOS		15

#define EXP_MAX_MANIPULOS				4

#define RFID_MAX_BOARDS 				1//2


#define GPERIF_MALLOC_SIZE				128

typedef enum		/* PERIFERICOS PROT SPI */
{
	EXP_PERIFERICO_MAIN,				/* no se enviaran tramas SPI, pero sirve para reservar una zona para la main */
	EXP_PERIFERICO_APL1,
	EXP_PERIFERICO_APL2,
	EXP_PERIFERICO_APL3,
	EXP_PERIFERICO_APL4,
	EXP_PERIFERICO_RF1,
	EXP_PERIFERICO_RF2,
	EXP_MAX_PERIFERICOS
	
}perif_t;

#define GPERIF_PERIF_PROV_FREE_OUT 0xFB
#define GPERIF_PERIF_PROV_FREE_IN 0xFC
#define GPERIF_PERIF_PROV_ALLOC_OUT 0xFD
#define GPERIF_PERIF_PROV_ALLOC_IN 0xFE


enum		/* DEFINICION MEMORIAS PROTOCOLO ESCLAVO EXPANSORA */
{
	EXP_INTERNAL_USED_RAM = 0,
	EXP_INTERNAL_RAM,
	EXP_INTERNAL_FLASH,
	EXP_UNDEFINED_3,
	EXP_GESTION_PERIF,
	EXP_DEBUG_RAM,
	EXP_UNDEFINED_6,
	EXP_UNDEFINED_7,

	EXP_MAX_MEMORIES
};


enum		/* DEFINICION ACCIONES MAIN */
{
	MAIN_ACCION_IDLE,
	
	MAIN_RFID_ACCION_RESET,
	MAIN_RFID_ACCION_GUARDAR_CONFIG,
	MAIN_RFID_ACTUALIZA_MAPA,
	MAIN_RFID_ACCION_LEER_TARJETA,

//	MAIN_EXP_ACCION_IDLE,
	MAIN_EXP_ACCION_RESET,
	MAIN_EXP_ACCION_GUARDAR_CONFIG,
	MAIN_EXP_ACCION_PUENTE_PROTOCOLO,			/* hace la transmision entre la expansora y el esclavo de sensorica segun la estructura puente_protocolo_t */

	MAIN_MAX_ACCIONES
};

//cris: Memories RFID 
enum
{
	RFID_INTERNAL_USED_RAM = 0,
	RFID_INTERNAL_RAM,
	RFID_INTERNAL_FLASH,
	RFID_INTERNAL_E2PROM,
	RFID_EXTERNAL_EEPROM,
	RFID_CARD_TRAILER_SECTOR,
	RFID_CARD_DATA_SECTOR,
	RFID_CARD_SELECT_SECTOR,

	RFID_MAX_MEMORIES
};

//cris: Memories expansora (GDISP) //gen
enum
{
	GDISP_INTERNAL_USED_RAM = 0,
	GDISP_INTERNAL_RAM,
	GDISP_INTERNAL_FLASH,
	GDISP_INTERNAL_E2PROM,
	GDISP_GESTION_PERIF,
	GDISP_PUENTE_PROTOCOLO,
	GDISP_CARD_DATA_SECTOR,
	GDISP_CARD_SELECT_SECTOR,
	
	GDISP_MAX_MEMORIES
};


typedef union		/* doublereg_t */
{
	uint16_t u16value;
	struct
	{
		uint8_t u8LO;
		uint8_t u8HI;
	}byteacces;
	struct
	{
		uint16_t bit0   : 1;
		uint16_t bit1   : 1;
		uint16_t bit2   : 1;
		uint16_t bit3   : 1;
		uint16_t bit4   : 1;
		uint16_t bit5   : 1;
		uint16_t bit6   : 1;
		uint16_t bit7   : 1;
		uint16_t bit8   : 1;
		uint16_t bit9   : 1;
		uint16_t bit10  : 1;
		uint16_t bit11  : 1;
		uint16_t bit12  : 1;
		uint16_t bit13  : 1;
		uint16_t bit14  : 1;
		uint16_t bit15  : 1;
	}bitacces;
}doublereg_t;

typedef union		/* tetrareg_t */
{
	float fvalue;
	uint32_t u32value;
	struct
	{
		doublereg_t u16LO;
		doublereg_t u16HI;
	}intacces;
}tetrareg_t;

typedef struct	/* boarddef_t */
{
	uint8_t u8BoardAddres;
	uint8_t u8BoardType;
	uint8_t u8MaxBuffRx;
	uint8_t u8BootVers;
	uint8_t u8FWVers;
	uint8_t u8ProtVers;
	uint8_t u8MinSlot;
	uint8_t u8MaxSlot;
	tetrareg_t SizeMemories[EXP_MAX_MEMORIES];
}boarddef_t;

//typedef union		/* board_status_t */
//{
//	uint8_t status;
//	struct
//	{
//		uint8_t coms_error      : 1;
//		uint8_t dummy           : 7;
//	}bit_field;
//}board_status_t;


typedef union		/* board_status_t */ //cris:modificat
{
	uint8_t status;
	union
	{
		struct
		{
			uint8_t card_detection  	: 1;
			uint8_t card_operation  	: 1;
			uint8_t dummy       		: 6;
		}rfid_st;
		struct
		{
			uint8_t coms_error      : 1;
			uint8_t stdby			: 1;
			uint8_t dummy           : 6;
		}exp_st;
	}bit_field;
}board_status_t;

typedef union		/* board_alarms_t */ //cris:modificat
{
	uint8_t alarms;
	union
	{
		struct
		{
			uint8_t dummy       : 8;
		}rfid_st;
		struct
		{
			uint8_t RS485slave_error	: 1;
			uint8_t spi_error			: 1;
			uint8_t dummy       		: 6;
		}exp_st;
	}bit_field;
}board_alarms_t;

typedef union		/* mems_status_t */
{
	uint8_t status;
	struct
	{
		uint8_t stat        : 2;    /* control si hi ha tasques pendents per protocol */
		uint8_t abort       : 1;    /* desde protocol es vol abortar operacio (nomes pot abortar operacions fetes per ell mateix) */
		uint8_t op_protocol : 1;    /* funcio lectura/escriptura per protocol */
		uint8_t func_prot   : 1;    /* modul ocupat per ordre de protocol */
		uint8_t write       : 1;    /* modul fent escriptura */
		uint8_t read        : 1;    /* modul fent lectura */
		uint8_t scan        : 1;    /* modul fent scan de tarjetes */
	}bit_field;
}mems_status_t;

typedef union		/* mems_alarms_t */
{
	uint8_t alarms;
	struct
	{
		uint8_t u8AccesForaRang         : 1;
		uint8_t u7code                  : 7;
	}bit_field;
}mems_alarms_t;

typedef struct	/* cabecera_fw_t */
{
	boarddef_t board_definition;
	board_status_t board_status;
	board_alarms_t board_alarms;
	uint8_t dummy[2];
	uint16_t u16accions;
	uint16_t u16accioactual;
	mems_status_t mems_status[EXP_MAX_MEMORIES];
	mems_alarms_t mems_alarms[EXP_MAX_MEMORIES];
}cabecera_fw_t;



//cris: afegit
typedef struct
{
	uint8_t u8BoardAddres; //BoardID
	uint8_t u8BoardType;
	uint8_t u8MaxBuffRx;
	uint8_t u8BootVers;
	uint8_t u8FWVers;
	uint8_t u8ProtVers;
	uint8_t u8MinSlot;
	uint8_t u8MaxSlot;
	uint32_t SizeMemories[RFID_MAX_MEMORIES];
	uint8_t board_status;
	uint8_t board_alarms;
	uint16_t dummy;
	uint16_t u16accions;
	uint16_t u16accioactual;
	uint8_t mems_status[RFID_MAX_MEMORIES];
	uint8_t mems_alarms[RFID_MAX_MEMORIES];

	uint8_t ptu8UID_mifare[5];
	uint8_t ptu8Pswd[6];
	uint8_t u8Key;
	uint8_t u8MaxReintentsMIFARE;
	uint8_t u8TipoCalculoPswd;
}RFID_CPU_t;



typedef union	/* estado_manipulos_t	*/
{
	uint8_t u8Estado;
	struct
	{
		uint8_t conectado			: 1;		/* si se ha conectado manipulo */
		uint8_t inicializado	: 1;		/* si se ha inicializado el manipulo */
		uint8_t dummy					: 6;
	}bit_field;
}estado_manipulos_t;


typedef struct	/* sensores_manipulos */
{
	float caudalRetorno;
	float temperaturaRetorno;
	float presionVaccum;
}sensores_manipulos;


typedef union		/* controles_t */
{
	uint8_t u8Controles;
	struct
	{
		uint8_t hidraulica		: 1;
		uint8_t vacum			: 1;
		uint8_t fuente1			: 1;
		uint8_t fuente2			: 1;
		uint8_t rf				: 1;
		uint8_t potencia		: 1;
		uint8_t dummy			: 2;
	}bif_field;
}controles_t;


typedef struct	/* variables_manipulos_t */
{
	estado_manipulos_t estado;						/* estado del manipulo */
	uint8_t estado_placa;
	uint8_t alarmas_placa;
	uint8_t calculoRendimiento;						/* si es 1, la expansora calcula el rendimiento de la tobera, si es 0 no calcula nada (se podra escribir por coms) */
	controles_t ctl_pedidos;							/* controles que requiere */
	controles_t ctl_listos;								/* indica que el control esta funcionando */
	float fTemperaturaAguaEntradaMaximo;	/* indica con que temperatura maxima a la entrada puede trabajar */
	float fCaudalMinimo;									/* indica el caudal minimo con el que puede trabajar */
	float	fConsignaVacum;									/* indica consigna para el vacum */
	float fTensionV1;											/* indica % tension a aplicar para la fuente 1 */
	float fTensionV2;											/* indica % tension a aplicar para la fuente 2 */
	float fRendimientoTobera;							/* factor para indicar el rendimiento de la tobera */
	float fFactorRendimientoMain;					/* factor a usar por la main para afectar al calculo del rendimiento (por defecto a 1.0), solo se aplica si expansora hace el calculo */
	
}variables_manipulos_t;



typedef struct	/* variables_complementos_t */
{
	//	uint8_t led_status;
	//	uint8_t ev_status;
	//	uint8_t boton;
	//	uint8_t dummy;
	float temperatura;
	float presionAire;
	float presionAgua;
	float caudal;
	uint32_t u32TimeEV_ON;
	float presionMaximaAire;
}variables_complementos_t;

typedef struct	/* debug_complementos_t */
{
	uint8_t u8NumRepeticionesLed;
	uint32_t u33TiempoONLed;
	uint32_t u33TiempoOFFLed;
}debug_complementos_t;

typedef struct	/* mapa_memoria_comp_t */
{
	cabecera_fw_t cabecera_fw;
	/* anyadir variables propias de la placa */
	variables_complementos_t var;
	debug_complementos_t debug;
}mapa_memoria_comp_t;

typedef struct	/* variables_fuente_t */
{
	uint8_t status;
	uint8_t estadoModulos;
	uint8_t alarma;
	uint8_t powerGoods;
	uint8_t onoffModulos[4];
	float PorcentajeVolt[4];

}variables_fuente_t;

typedef struct	/* debug_fuente_t */
{
	uint8_t led_status;
}debug_fuente_t;

typedef struct	/* mapa_memoria_fuentes_t */
{
	cabecera_fw_t cabecera_fw;
	/* anyadir variables propias de la placa */
	variables_fuente_t var;
	debug_fuente_t debug;
}mapa_memoria_fuentes_t;


//cris:afegit
typedef struct	/* variables_expansora_t */
{
	//falta: modificar cuando las definamos
	uint8_t status;
	uint8_t estadoModulos;
	uint8_t alarma;
	uint8_t powerGoods;
	uint8_t onoffModulos[4];
	float PorcentajeVolt[4];

}variables_expansora_t;


typedef union		/* estado_entradas_t */
{
	uint16_t value;
	struct
	{
		uint16_t slot0				: 1;
		uint16_t slot1				: 1;
		uint16_t slot2				: 1;
		uint16_t detect_M1		: 1;
		uint16_t detect_M2		: 1;
		uint16_t detect_M3		: 1;
		uint16_t detect_M4		: 1;
		uint16_t pedal_A			: 1;
		uint16_t pedal_C			: 1;
		uint16_t alarma_gral	: 1;
		uint16_t puerta_vacum	: 1;
		uint16_t puerta_iza		: 1;
		uint16_t puerta_dch		: 1;
		uint16_t puerta_elec	: 1;
		uint16_t puerta_tobera: 1;
		
		uint16_t dummy				: 1;
	}bit_field;
	
}estado_entradas_t;




//cris:afegit
typedef struct	/* debug_expansora_t */
{
	//falta: modificar cuando las definamos
	uint8_t led_status;
}debug_expansora_t;



//cris:afegit
typedef struct	/* mapa_memoria_expansora_t */
{
	cabecera_fw_t cabecera_fw;
	/* anyadir variables propias de la placa */
	estado_entradas_t estado_entradas;
	estado_entradas_t accion_entradas;
	
	float temperaturaAmb;
	float temperaturaOutRadiador;
	float temperaturaOutBomba;
	float presionAgua;
	float caudalRetorno;
	float temperaturaRetorno;
	sensores_manipulos sens_man[EXP_MAX_MANIPULOS];
	variables_manipulos_t manipulo[EXP_MAX_MANIPULOS];
	

}mapa_memoria_expansora_t;

typedef struct	/* struct_remap_t */
{
	/* definicion de 1bloque de datos del protocolo SPI */
	uint8_t ptu8DescripcionBloque[4];	/* cabecera a enviar con el nombre del bloque, da sentido a los bytes que se enviaran despues */
	uint16_t addr_init;					/* direccion inicial dentro de ptu8Buffer_DataPerif */
	uint8_t num_bytes;					/* numero de bytes que tiene el bloque */
	uint8_t dummy;						/* para cumplir con el boundary */
}struct_remap_t;

typedef struct	/* perif_remap_t */
{
	/* definicion de los bloques de datos para un periferico */
	struct_remap_t data_in[EXP_MAX_REMAP_DATA_IN];			/* bloques de datos para hacer los bytes de entrada al periferico */
	
	struct_remap_t data_out[EXP_MAX_REMAP_DATA_OUT];		/* bloques de datos para hacer los bytes de salida del periferico */
	
}perif_remap_t;

typedef enum					/* identificadores de cada placa en el array de versiones */
{
	PROTSPI_UNDEF_COMS,		
	PROTSPI_DEBUG_COMS,			//Referencia en main
	PROTSPI_CONFIG_COMS,		//Referencia en main
	PROTSPI_MAIN_COMS,			//Referencia en main
	PROTSPI_EXPANSORA_COMS,	//Referencia en el MemMap de la expansora
	//cris: falta RF
	PROTSPI_DEF_PERIF,
	PROTSPI_PID,

	PROTSPI_MAX_COMS_DEFINIDAS
	
}protSPI_t;


typedef struct	/* version_data_t */
{
	/* definicion de la version del protocolo que utiliza para el resto de perifericos */
	uint32_t modelo;										/* modelo de periferico */
	uint16_t u16NumFuentesUso;						/*numero de fuentes para peltiers que utiliza el manipulo*/
	uint16_t version_perif;								/* version del codigo */
	uint16_t max_buffer;									/* tamanyo maximo del buffer reservado para el SPI */
	uint8_t version[2*EXP_MAX_PERIFERICOS_DEFINIDOS];		/* versiones de protocolo para el resto de perifericos. Primer byte identificador (valores del enum PROTSPI_XXXX_COMS) 2º version */
}version_data_t;

typedef struct	/* gestion_perifericos_t	*/ //cris: reordeno version, remapeo y data
{
	uint16_t perif_habilitados;																/* a nivel de bit los perifericos que estan habilitados */
	uint16_t perif_inicializados;															/* a nivel de bit los perifericos con los que puedo hablar en este momento (ya estan inicializados) */
	version_data_t version_data[EXP_MAX_PERIFERICOS];							/* definicion de la version del protocolo soportado */
	perif_remap_t remapeo_periferico[EXP_MAX_PERIFERICOS];					/* definicion de los bloques de datos para cada periferico */
	uint8_t ptu8Buffer_DataPerif[EXP_MAX_BUFFER_DATA_MANIPULO];		/* buffer de intercambio de datos entre perifericos, la expansora no sabe que significa nada */
	
}gestion_perifericos_t;

typedef struct	/* contador_coms_t	*/
{
	uint32_t u32TramasOK;
	
	uint32_t u32TramasKO;
	
}contador_coms_t;




#define PID_MAX			1
typedef struct	/* pid_struct_t */
{
	uint8_t u8Habilitado;
	uint8_t ID_PID;
	float consigna;
	float entrada;
	float salida;
	float error_actual;
	float error_anterior;
	uint32_t tiempo_calculo;			/* periodo de calculo en ms */
	float integral;
	float derivada;
	float kp;
	float kd;
	float ki;
	int32_t saturacion_max;
	int32_t saturacion_min;
	
}pid_struct_t;


#define PUENTE_PROTOCOLO_MAX_DATA			16
#define GDISP_ADDR_PUENTE_PROTOCOLO			0
typedef union		/* nova_ordre_t */
{
	struct
	{
		uint8_t u8AddrEsclau;
		uint8_t tipus_operacio;
		uint8_t u8Memoria;
		uint8_t u8NumBytes;
		uint16_t u16TimeoutTrama;
		uint16_t u16MaxReintents;
		uint32_t u32Addr;
	}fields;

	uint8_t ptu8Bytes[12];

}nova_ordre_t;

typedef struct	/* puente_protocolo_t */
{
	nova_ordre_t orden;
	uint16_t mem_status;
	uint8_t esclavo_status;
	uint8_t comodin1;
	uint8_t comodin2;
	uint8_t resultado;
	uint8_t ptu8Data[PUENTE_PROTOCOLO_MAX_DATA];	
}puente_protocolo_t;


typedef struct
{
	/* envio tramas de la main a esclavos del bus sensores */
	puente_protocolo_t puenteprotocolo;
	
	/* mapa memoria de los esclavos RS485 */
	mapa_memoria_fuentes_t fuente_alim[MAX_PCB_FUENTES];
	mapa_memoria_comp_t complementos[MAX_PCB_COMPLEMENTOS];
	
	pid_struct_t pid[PID_MAX];
	
	/* contadores de errores de protocolos */
	contador_coms_t puerto485_slv;
	contador_coms_t puerto485_mst;
	contador_coms_t puertoSPI;

}debug_map_expansora_t;

typedef struct
{
	uint32_t ReadIndex;
	uint32_t WriteIndex;
	uint32_t u32NumBytes;
}fifo_counter_t;

typedef struct
{
	uint8_t TAG[2];
	uint16_t NANDBadBlockCount;
	uint32_t TreatmentCount;
	fifo_counter_t FiFoNAND[2];
}var_flash_t;

typedef struct
{
	cabecera_fw_t cabecera_fw;
	
	/* anyadir variables propias de la placa */
	
	/*variables main*/ //cris
	returnstatus_t rfidResult;
	
	
//cris: son propias de expansora, podria ponerlo en la variable mapa_memoria_expansora_t
/* estado_entradas_t estado_entradas;
	estado_entradas_t accion_entradas;

	float temperaturaAmb;
	float temperaturaOutRadiador;
	float temperaturaOutBomba;
	float presionAgua;
	float caudalRetorno;
	float temperaturaRetorno;
	sensores_manipulos sens_man[EXP_MAX_MANIPULOS];
	variables_manipulos_t manipulo[EXP_MAX_MANIPULOS];*/

	/* mapa memoria de los esclavos RS485 */
	
//	/*mapa memoria RFID*///cris
//	RFID_CPU_t RFID_CPU[RFID_MAX_BOARDS];
//		
//	//cris: afegeixo
//	mapa_memoria_expansora_t expansora[MAX_PCB_EXP]; 
//	
//	/* gestion perifericos */
//	gestion_perifericos_t gestion_perifericos;
//
//	/* cris: puente protocolo + variables debug */
//	debug_map_expansora_t exp_debug;
//	
//	//cris: son propias de expansora, posar dins de expansora?
//	mapa_memoria_fuentes_t fuente_alim[MAX_PCB_FUENTES];
//	mapa_memoria_comp_t complementos[MAX_PCB_COMPLEMENTOS];
	
	/* contadores de errores de protocolos */
	pid_struct_t pid[PID_MAX];
	contador_coms_t puerto485_slv;
	contador_coms_t puerto485_mst;
	contador_coms_t puertoSPI;
	
	var_flash_t var_flash;
	uint16_t u16Errores;
	uint16_t u16Warnings;
	
	uint8_t borrame;

}memory_map_def_t;

typedef union
{
	memory_map_def_t var;
	uint8_t ptucBytes[sizeof(memory_map_def_t)];
}memory_map_t;


extern memory_map_t MemoryMap;




#endif /* GENERALDEFINES_H_ */

