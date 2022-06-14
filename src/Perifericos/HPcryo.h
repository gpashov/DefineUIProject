/*
 * HPcryo.h
 *
 *  Created on: Mar 6, 2019
 *      Author: dbelmonte
 */

/*
 * v - Tiempo trt
 * - Modo AUTO - ojo tiny's que no va. Ojo AppGUI cbk que tiene que bloquearse el boton una vez iniciado el trt. ojo funcion de return isOK que mire estar en estado result.
 * - Llenado / vaciado
 * v - Pitido final tratamiento
 * v - Resucciones
 * v - Vacum retry no resetea el tiempo pero no cuenta el tiempo entre quitar HP y volver a ponerlo
 * */
 
#ifndef HPCRYO_H_
#define HPCRYO_H_

/*** INCLUDES ***/
#include "../GeneralDefines.h"
#include "Perifericos.h"
#include "RFID/RFID.h"
#include "Buzzer/Buzzer.h"
//#include "../RTC/RTC.h"
//#include "../BusAlarma/BusAlarma.h"

/*** CONSTANTES ***/
#define HP_CRYO_MAX_TEMP_SNS 9
#define HP_CRYO_SAT_RGB_TEST_MAX_COLORS 3

/** REMAP FRAMES **/
#define HP_CRYO_N_REMAP_FRAMES 14//12

//#define HP_CRYO_MAX_NUM_EMULATED 2				/* como maximo se conectara un double de momento */
#define HP_CRYO_MAX_PID_PER_HP 4 					/* por defecto cada manipulo tiene 2 fuentes y cada fuente tiene PID de temperatura y PID de saturacion */
#define HP_CRYO_TOTAL_PID HP_CRYO_MAX_PID_PER_HP 	/* * HP_CRYO_MAX_NUM_EMULATED */

#define HP_CRYO_REMAP_FRAME_MAIN_IN_DIR 0
#define HP_CRYO_REMAP_FRAME_MAIN_IN_SIZE 43
#define HP_CRYO_REMAP_FRAME_MAIN_OUT_DIR ( HP_CRYO_REMAP_FRAME_MAIN_IN_DIR + HP_CRYO_REMAP_FRAME_MAIN_IN_SIZE)
#define HP_CRYO_REMAP_FRAME_MAIN_OUT_SIZE 23
#define HP_CRYO_REMAP_FRAME_CONFIG_IN_DIR ( HP_CRYO_REMAP_FRAME_MAIN_OUT_DIR + HP_CRYO_REMAP_FRAME_MAIN_OUT_SIZE)
#define HP_CRYO_REMAP_FRAME_CONFIG_IN_SIZE 35
#define HP_CRYO_REMAP_FRAME_CONFIG_OUT_DIR ( HP_CRYO_REMAP_FRAME_CONFIG_IN_DIR + HP_CRYO_REMAP_FRAME_CONFIG_IN_SIZE)
#define HP_CRYO_REMAP_FRAME_CONFIG_OUT_SIZE 35
#define HP_CRYO_REMAP_FRAME_DEBUG_IN_DIR ( HP_CRYO_REMAP_FRAME_CONFIG_OUT_DIR + HP_CRYO_REMAP_FRAME_CONFIG_OUT_SIZE)
#define HP_CRYO_REMAP_FRAME_DEBUG_IN_SIZE 1
#define HP_CRYO_REMAP_FRAME_DEBUG_OUT_DIR ( HP_CRYO_REMAP_FRAME_DEBUG_IN_DIR + HP_CRYO_REMAP_FRAME_DEBUG_IN_SIZE)
#define HP_CRYO_REMAP_FRAME_DEBUG_OUT_SIZE 71
#define HP_CRYO_REMAP_FRAME_PID_IN_DIR ( HP_CRYO_REMAP_FRAME_DEBUG_OUT_DIR + HP_CRYO_REMAP_FRAME_DEBUG_OUT_SIZE)
#define HP_CRYO_REMAP_FRAME_PID_IN_SIZE 113
#define HP_CRYO_REMAP_FRAME_PID_OUT_DIR ( HP_CRYO_REMAP_FRAME_PID_IN_DIR + HP_CRYO_REMAP_FRAME_PID_IN_SIZE)
#define HP_CRYO_REMAP_FRAME_PID_OUT_SIZE 80
#define HP_CRYO_REMAP_FRAME_DEFINITION_IN_DIR ( HP_CRYO_REMAP_FRAME_PID_OUT_DIR + HP_CRYO_REMAP_FRAME_PID_OUT_SIZE)
#define HP_CRYO_REMAP_FRAME_DEFINITION_IN_SIZE 11
#define HP_CRYO_REMAP_FRAME_DEFINITION_OUT_DIR ( HP_CRYO_REMAP_FRAME_DEFINITION_IN_DIR + HP_CRYO_REMAP_FRAME_DEFINITION_IN_SIZE)
#define HP_CRYO_REMAP_FRAME_DEFINITION_OUT_SIZE 11

#define HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_DIR		( HP_CRYO_REMAP_FRAME_DEFINITION_OUT_DIR + HP_CRYO_REMAP_FRAME_DEFINITION_OUT_SIZE)
#define HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_SIZE	71
#define HP_CRYO_REMAP_FRAME_FLASH_MEMORY_OUT_DIR	( HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_DIR + HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_SIZE)
#define HP_CRYO_REMAP_FRAME_FLASH_MEMORY_OUT_SIZE	71


//#define HP_CRYO_EXTERNAL_FLASH_MEMORY_SECTOR_SIZE	0x1000
//#define HP_CRYO_EXTERNAL_FLASH_MEMORY_SIZE			0x100000

#define HP_CRYO_MAX_SONDAS_GRUPO		4
#define HP_CRYO_MAX_GRUPOS_DE_SONDAS	4


#define HP_CRYO_TIME_LOOP_OSC_SET_POINT_TEMP	10000
#define HP_CRYO_DELTA_TEMP_OSC					(float)0.15
#define HP_CRYO_SW_HP_THRESSHOLD_CTRL_OSC_TEMP	20
#define HP_CRYO_SW_HP_THRESSHOLD_CTRL_MEM_FLASH_ACCESS	17

#define HP_CRYO_UP_THRSHOLD_WIN_TEMP_OSC_IDLE	3.0
#define HP_CRYO_LOW_THRSHOLD_WIN_TEMP_OSC_IDLE	8.0

#define HP_CRYO_RFID_LABEL_AND_HP_TABLE_ELEMENTS	11

#define HP_CRYO_CLEAN_UP_MAX_TIMES_CANCEL		5.0

#define HP_CRYP_MEMORY_FLASH_ADDR_TO_USE	0x40000

#define HP_CRYO_TRT_PERCENT_COMPLETE_2_CLEAN	0.85	//85% del tratamiento para solicitar limpieza - V7775

/* V7778 - TEMP SEC */
////#define HP_CRYO_CALIB_LIMIT_PT1000 	200
//#define HP_CRYO_CALIB_LIMIT_NTC		50
/* V7778 - TEMP SEC */
/* V7780 */
//#define HP_CRYO_CALIB_SECURE_LIMIT	50
/* V7780 */

#define HP_CRYO_RFID_LABELS_CODE_NUM_CHAR			2

//#define HP_CRYO_MAX_VACUM_RETRYS_IN_THIRD_TIME	50		//V7790 - TempSAFE (pasado del .c al .h)

//#define HP_CRYO_DFLT_ENABLE_PLICA 0
//#define HP_CRYO_DFLT_COLOR_LED HP_CRYO_CTLLED_COLOR_APAGADO
//#define HP_CRYO_DFLT_CAMBIO_ESTADO HP_CRYO_MAN_IDLE
//#define HP_CRYO_DFLT_TIEMPO_TRT_S 0
//#define HP_CRYO_DFLT_CONSIGNA_VACUM 0.0
//#define
/*
 * Modelos de HPcryo posibles
 */
typedef enum
{
    HP_CRYO_FAT_DONE_NONE,
    HP_CRYO_FAT_DONE_1,
    HP_CRYO_FAT_DONE_2,
	
    HP_CRYO_FAT_DONE_MAX
}cHPcrypFatigueComplete;

typedef enum
{
    HP_CRYO_FAT_STOP,
    HP_CRYO_FAT_1,
    HP_CRYO_FAT_2,
    HP_CRTYO_FAT_LAST_TEST,
	
    HP_CRYO_FAT_MAX
}cHPcrypFatigueRqst;

typedef enum
{
    HP_CRYO_FAT_Running,
    HP_CRYO_FAT_HP1done = PRF_HW_SLOT1,
    HP_CRYO_FAT_HP2done = PRF_HW_SLOT2,
    HP_CRYO_FAT_HP3done = PRF_HW_SLOT3,
    HP_CRYO_FAT_HP4done = PRF_HW_SLOT4,
}cHPcryoFatigueStatus;

typedef enum
{
    HP_CRYO_MODEL_UNDEFINED,
    HP_CRYO_MODEL_CURVED,
    HP_CRYO_MODEL_TIGHT,
    HP_CRYO_MODEL_STRIGHT,
    HP_CRYO_MODEL_TINY,
    HP_CRYO_MODEL_TINY_CURVED,
    HP_CRYO_MODEL_DOUBLE,
    HP_CRYO_MODEL_OVAL,
    HP_CRYO_MODEL_OVAL_CURVED,
    HP_CRYO_MODEL_ANGLED,
    HP_CRYO_NUM_HP_MODELS
}cHPcryoModels;

typedef enum
{
    HP_CRYO_LABEL_UNDEFINED,
    HP_CRYO_LABEL_ZO,			//Curved, Oval, Oval Curved, Stright, Tight
    HP_CRYO_LABEL_Z1,			//Tiny y Tiny Curved
    HP_CRYO_LABEL_Z2,			//Double
    HP_CRYO_LABEL_Z3,			//Delta
    HP_CRYO_LABEL_DM,			//Todos, tratamiento de DEMO
    HP_CRYO_PROD_LABEL_PD,		//Todos, tratamiento libre para pruebas de produccion
    HP_CRYO_LABEL_ERASED,		//Etiqueta borrada por una maquina Define
    HP_CRYO_NUM_LABELS
}cHPcryoLabels;

typedef enum
{
    HP_CRYO_LABEL_REQ_CLEANUP,
    HP_CRYO_LABEL_NOT_REQ_CLEANUP,
	
    HP_CRYO_LABEL_CLEANUP_OPTIONS
}cHPcryoLabelsCleanUpOptions;

typedef enum
{
    HP_CRYO_NOT_VALID,
    HP_CRYO_VALID,
    HP_CRYO_DEFAULT
}cHPcryoLabel_HPstatus;

typedef enum
{
    HP_CRYO_RFID_not_reserved,
    HP_CRYO_RFID_reserved
}cHPcryoRFID_HP_status_resource;

typedef enum
{
    HP_CRYO_RFID_OK,
    HP_CRYO_RFID_FAILURE,
    HP_CRYO_RFID_LABEL_INVALID,
	
    HP_CRYO_RFID_LABEL_READ_STATUS_MAX
}cHPcryoRFID_err;

typedef enum
{
    HP_CRYO_TIME_45_MIN,
    HP_CRYO_TIME_50_MIN,
    HP_CRYO_TIME_70_MIN,
    HP_CRYO_MAX_TIME_LIST,
    HP_CRYO_TIME_NO_TIME
}cHPcryoTrtTimes;

typedef enum
{
    HP_CRYO_TRT_MODE_MANUAL,
    HP_CRYO_TRT_MODE_AUTO,
	
    HP_CRYO_TRT_MODES
}cHPcryoTrtModes;

typedef enum
{
    HP_CRYO_TEST_VACUUM_AUTO_DONE_SUCCESS,
    HP_CRYO_TEST_VACUUM_AUTO_DONE_FAIL,
    HP_CRYO_TEST_VACUUM_AUTO_UNDONE,
	
    HP_CRYO_TEST_VACUUM_AUTO_MAZ_STATES
}cHPcryoTstVaccAutoStates;

typedef enum
{
    HP_CRYO_TRT_AUTO_WAIT_TIME,
    HP_CRYO_TRT_AUTO_DETECTING,
    HP_CRYO_TRT_AUTO_RESULT,
    HP_CRYO_TRT_AUTO_IDLE
}cHPcryoTrtAutoStatus;

typedef enum
{
    HP_CRYO_VAC_LVL_0,
    HP_CRYO_VAC_LVL_1,
    HP_CRYO_VAC_LVL_2,
    HP_CRYO_VAC_LVL_NUM
}cHPcryoTrtVacLvls;

typedef enum
{
    HP_CRYO_TEST_INIT,
    HP_CRYO_IDLE,
    HP_CRYO_TEST_VACUM,
    HP_CRYO_TREATMENT,
    HP_CRYO_CLEAN_UP,
    HP_CRYO_TEST_PELTIERS_OSC_TEMP,
    HP_CRYO_SAT,		//SAT
    HP_CRYO_FATIGUE_0,
}cHPcryoStatus;

typedef enum
{
    HP_CRYO_ADJUST_VACUM_IDLE,
    HP_CRYO_ADJUST_VACUM_SET,
    HP_CRYO_ADJUST_VACUM_WAIT
}cHPcryoAdjustVacumStatus;

typedef enum
{
    HP_CRYO_IDLE_VAC_STATUS_WITH_VAC,
    HP_CRYO_IDLE_VAC_STATUS_WITHOUT_VAC
}cHPcryoIdleVacumStatus;

typedef enum
{
    HP_CRYO_TEST_VAC_RUN_WAITING_USER_START,
    HP_CRYO_TEST_VAC_RUN_VACUM,
    HP_CRYO_TEST_VAC_RUN_WAITING_USER_END,
    HP_CRYO_TEST_VAC_DONE,
    HP_CRYO_TEST_VAC_FAIL
}cHPcryoTestVacumStatus;

typedef enum
{
    HP_CRYO_TEST_VAC_MODE_MANUAL,
    HP_CRYO_TEST_VAC_MODE_AUTO
}cHPcryoTestVacumMode;

typedef enum
{
    HP_CRYO_TREATMENT_RUN_WAITING_RFID,
    HP_CRYO_TREATMENT_RUN_WAITING_USER_START,
    HP_CRYO_TREATMENT_RUN_VACUM,
    HP_CRYO_TREATMENT_RUN_COOLING,
    HP_CRYO_TREATMENT_RUN_WAITING_USER_END,
    HP_CRYO_TREATMENT_RUN_PAUSE,
    HP_CRYO_TREATMENT_DONE,
    HP_CRYO_TREATMENT_FAIL
}cHPcryoTreatmentStatus;

typedef enum
{
    HP_CRYO_INIT_RQST_CONFIG,
    HP_CRYO_INIT_GET_CONFIG_DATA
}cHPcryoInitStatus;

typedef enum
{
    HP_CRYO_FINISH_CLEAR
}cHPcryoFinishStatus;

typedef enum
{
    HP_CRYO_CLEAN_UP_COUNTDOWN,
    HP_CRYO_CLEAN_UP_CHECK_PATIENT,
    HP_CRYO_CLEAN_UP_WAITING_USER,
    HP_CRYO_CLEAN_UP_CLEANING,
    HP_CRYO_CLEAN_UP_WAIT_VACUM,
    HP_CRYO_CLEAN_UP_DONE,
    HP_CRYO_CLEAN_UP_FAIL,
    HP_CRYO_CLEAN_UP_PAUSE
}cHPcryoCleanUpStatus;

typedef enum
{
    HP_CRYO_CLEAN_UP_RQST_NONE,
    HP_CRYO_CLEAN_UP_RQST_WITH_CHECK,
    HP_CRYO_CLEAN_UP_RQST_FORCED
}cHPcryoCleanUpRqst;

typedef enum
{
    HP_CRYO_CLEAN_UP_NONE,
    HP_CRYO_CLEAN_UP_INIT_OF_TRT,
    HP_CRYO_CLEAN_UP_END_OF_TRT,
    HP_CRYO_CLEAN_UP_MOMENTS_TO_CLEAN
}cHPcryoCleanUpMoments;

typedef enum
{
    HP_CRYO_CTLLED_COLOR_APAGADO,
    HP_CRYO_CTLLED_COLOR_ROJO,
    HP_CRYO_CTLLED_COLOR_CELESTE,
    HP_CRYO_CTLLED_COLOR_LILA,
    HP_CRYO_CTLLED_COLOR_LIMON,
    HP_CRYO_CTLLED_COLOR_NARANJA,
    HP_CRYO_CTLLED_COLOR_AZUL,
    HP_CRYO_CTLLED_COLOR_VERDE,
		
    HP_CRYO_NUM_MAX_COLORS
}cHPcryoLEDcolors;

typedef	enum
{
    HP_CRYO_MAN_INIT,						/* inicializacion de las comunicaciones con la expansora, secuencia del color del led */
    HP_CRYO_MAN_IDLE,						/* estado de reposo, tiene todo apagado, el boton no tiene accion y el led se enciende solido como dice main */
    HP_CRYO_MAN_READY,						/* estado con configuracion de tratamiento ok y a la espera que se apriete el boton. el led se enciende solido como dice main */
    HP_CRYO_MAN_ENABLEH2O,					/* el boton no tiene accion, el led se enciende solido como dice main y solo esta activa la hidraulica */
    HP_CRYO_MAN_WAITINGSETPOINTS,			/* tratamiento inciado, se espera a que tanto el vac como la temperatura lleguen a los valores indicados. El led parpadea en intensidad con color indicado desde main y velocidad lenta */
    HP_CRYO_MAN_INPROGRESS,					/* se ha llegado/sobrepasado los valores minimos indicados. El led parpadea en intensidad con color indicado desde main y velocidad media (segun se aproxima el final del tratamiento velocidad sube) */
    HP_CRYO_MAN_PAUSE,						/* se ha agotado el tiempo de tratamiento, las peltiers se apagan, pero se mantiene el vac. El led parpadea en intensidad con color indicado desde main y velocidad rapida */
    HP_CRYO_MAN_FINISHING,					/* se deshabilitan el vac y las peltiers. El led parpadea ON/OFF con color indicado desde main, X parpadeos rapidos con silencio entre ellos */
    HP_CRYO_MAN_ALARM,						/* se apaga todo sin rampa. El led parpadea ON/OFF con color indicado desde main, X parpadeos rapidos con silencio entre ellos */
    HP_CRYO_MAN_DESCONFIGURADO,				/* el manipulo no esta configurado, no tiene modelo ni numero fuentes en uso. El led repite la secuencia: ROJO, AZUL, VERDE, OFF */
    HP_CRYO_MAN_ENABLEVAC,					/* el boton no tiene accion, el led se enciende solido como dice main y solo esta activo el VAC */
    HP_CRYO_MAN_TESTSONDAS,					/* el boton no tiene accion, el led se enciende .... y hace el test de las sondas que se hace en la inicializacion */
    HP_CRYO_MAN_TESTPELTIERS,				/* el boton no tiene accion, el led se enciende .... y pone en la fuente1 de peltiers el valor de la cons temp, en la fuente2 la temp de inicio y, en caso de double, la fuente3 la ventana y la fuente 4 temp maxima entrada. se podra hacer vac */
    HP_CRYO_MAN_STANDBY,					/* el equipo esta en standby */
    HP_CRYO_MAN_MANIPULO_DESHAB_ERROR_COMS,	/* hay algun problema con las comunicaciones con las placas de las que depende el manipulo y no puede trabajar */
    //HP_CRYO_MAN_TEMP_SENOIDAL,			/* modo debug que envia una sinusoide como temperatura total. No activa vac ni peltiers */
    //HP_CRYO_MAN_PROTECCION,					/* ha saltado alguna proteccion */
	
    HP_CRYO_MAN_MAX_STATUS
}cHPcryoHWstatus;

/* V7778 - TEMP SEC */
typedef enum
{
    HP_CRYO_TEMPERATURE_SET_POINT_EARLY_TRT,	//Consigna de temperatura gran parte del trt
    HP_CRYO_TEMPERATURE_SET_POINT_END_TRT,		//Consigna de temperatura final del trt
    HP_CRYO_STANDARD_TEMPERATURE_SET_POINT_TRT,	//Consigna de temperatura estandard del aplicador
    HP_CRYO_TEMPERATURE_TIME_STEP_RANGE_2,		//Salto de consigna en el rango 1 cada X tiempo
    HP_CRYO_TEMPERATURE_TIME_STEP_RANGE_3,		//Salto de consigna en el rango 2 cada X tiempo
    HP_CRYO_TEMPERATURE_RANGE_LIMIT_1,			//Limite del rango 1 de bajada
    HP_CRYO_TEMPERATURE_RANGE_LIMIT_2,			//Limite de rando 2 de bajada
    HP_CRYO_TEMPERATURE_STEP_2,					//Salto de consigna en el rango 1
    HP_CRYO_TEMPERATURE_STEP_3,					//Salto de consigna en el rango 2
    HP_CRYO_PERCENT_TRT_TIME_EARLY_TEMP,		//Porcentaje de tiempo con la consigna inicial (menos fría)
	
    HP_CRYO_TEMPERATURE_FEATURES				//Numero de caracteristicas de temperatura del aplicador
}cHPcryoTRTtempParam;
/* V7778 - TEMP SEC */

///* Tabla con los valores de tiempo por defecto según el indice de seleccion */
//extern const uint16 HP_CRYO_DFLT_TRT_TEMP_FAIL_LIST_TIME[HP_CRYO_NUM_HP_MODELS];
//extern const uint8 HP_CRYO_CTRL_DELTA_MAX_SNS_TEMP_LIST_VALUE[HP_CRYO_NUM_HP_MODELS];
//extern const float HP_CRYO_CTRL_MIN_SNS_TEMP_LIST_VALUE[HP_CRYO_NUM_HP_MODELS];
//extern const float HP_CRYO_DFLT_LIST_TRT_TEMP_WINDOW[HP_CRYO_NUM_HP_MODELS];
//extern const float HP_CRYO_TRT_TEMP_SET_POINT_FEATURES[HP_CRYO_NUM_HP_MODELS][HP_CRYO_TEMPERATURE_FEATURES];
extern const uint32 HP_CRYO_TIME_LIST[HP_CRYO_MAX_TIME_LIST];
//extern const cHPcryoTrtTimes HP_CRYO_TIME_LIST_PER_HP[HP_CRYO_NUM_HP_MODELS][HP_CRYO_MAX_TIME_LIST];
//extern const uint8 HP_CYRO_LABEL_REQUESTED[HP_CRYO_NUM_LABELS][HP_CRYO_RFID_LABEL_AND_HP_TABLE_ELEMENTS];

//extern const char HP_CRYO_LABEL_CODE [HP_CRYO_NUM_LABELS][HP_CRYO_RFID_LABELS_CODE_NUM_CHAR];	//V7790 - LOG

/*** TIPOS DE DATOS ***/
/*
 * Estructuras auxiliares
 */
typedef union		/* estado_entradas_t */
{
    uint8_t value;
    struct
    {
        uint8_t pulsador			: 1;
        uint8_t detec_plica_iza		: 1;				/* 1 - es detectada chicha => no veo luz */
        uint8_t detec_plica_dcha	: 1;
        uint8_t dummy				: 5;
    }bit_field;
}tHPcryoInputStatus;

typedef union	/* alarmas_manipulo_t	*/
{
    uint16_t u16Avisos;
    struct
    {
        uint16_t timeout					: 1;		/* se ha agotado el tiempo de tratamiento */
        uint16_t espera_vac					: 1;		/* ha pasado el tiempo de espera del vac */
        uint16_t vac						: 1;		/* no se consigue la presion necesaria */
        uint16_t hidraulica					: 1;		/* no arranca hidraulica */
        uint16_t temp_entrada				: 1;		/* agua de entrada demasiado alta. No se que temperatura hay de entrada */
        uint16_t caudal_entrada				: 1;		/* caudal de entrada demasiado bajo */
        uint16_t espera_temp				: 1;		/* ha pasado el tiempo de espera temp */
        uint16_t temperatura				: 1;		/* no se consigue la temperatura necesaria, no se esta dentro de la ventana/2. Antes de empezar a mirar ventana/2 se espera a estar dentro de ventana */
        uint16_t sonda_error				: 1;		/* error medida de sonda y no es posible hacer tratamiento */
        uint16_t seguridad_frio				: 1;		/* alguna sonda por debajo de la temperatura minima del manipulo */
        uint16_t pid_off_calor				: 1;		/* algun pid de temperaturas ha llegado a pararse por saturacion del calor que sobra */
        uint16_t sin_tramas_main			: 1;		/* hace tiempo que no se reciben tramas de la main */
        uint16_t sin_tramas_secundario		: 1;		/*  */
        uint16_t circuito_temp_desconocido	: 1;		/* se han probado las combinaciones de circuito de temperatura y no sirve ninguno */
        uint16_t test_sondas_fallido		: 1;		/* no se ha superado el test de sondas */
        uint16_t protecciones				: 1;		/* se ha activado alguna proteccion del manipulo */
    }bit_field;
}tHPcryoWarnings;

typedef union
{
    uint32_t u32color;
    uint8_t ptu8componentes[4];
    struct
    {
        uint8_t u8rojo;
        uint8_t u8verde;
        uint8_t u8azul;
        uint8_t u8dummy;
    }componentes;
}tHPcryoColorDefinition;

typedef struct
{
//	uint8_t num_pulsaciones;
//	uint8_t dummy[3];
//	uint32_t tiempo_entre_pulsaciones;
//	uint32_t max_tiempo;
    uint8_t num_pulsaciones;
    uint8_t dummy;
    uint16_t min_tiempo;
}tHPcryoPulConfig;

typedef struct	/* contador_coms_t	*/
{
    uint32_t u32TramasOK;
    uint32_t u32TramasKO;
}tHPcryoComCounter;

typedef union	/* warnings_manipulo_t	*/
{
    uint16_t u16Warnings;
    struct
    {
        uint16_t temp_clavada	: 1;		/* temperaturas con el mismo valor hace mas de 5seg */
        uint16_t dummy2			: 1;		/*  */
        uint16_t dummy3			: 1;		/*  */
        uint16_t dummy4			: 1;		/*  */
        uint16_t dummy5			: 1;		/*  */
        uint16_t dummy6			: 1;		/*  */
        uint16_t dummy7			: 1;		/*  */
        uint16_t dummy8			: 1;		/*  */
        uint16_t dummy9			: 1;		/*  */
        uint16_t dummy10		: 1;		/*  */
        uint16_t dummy11		: 1;		/*  */
        uint16_t dummy12		: 1;		/*  */
        uint16_t dummy13		: 1;		/*  */
        uint16_t dummy14		: 1;		/*  */
        uint16_t dummy15		: 1;		/*  */
        uint16_t dummy16		: 1;		/*  */
    }bit_field;
}tHPcryoProtections;

typedef struct	/* pid_struct_conf */
{
    uint8_t u8Habilitado;
    uint8_t ID_PID;
    uint8_t dummy[2];
    uint32_t tiempo_calculo;
    float kp;
    float kd;
    float ki;
    int32_t saturacion_max;
    int32_t saturacion_min;
}tHPcryoConfigPID;

typedef struct	/* pid_struct_salida */
{
    float kp;
    float ki;
    float salida;
    float error_actual;
    float integral;
}tHPcryoOutputsPID;

/* TRAMAS DE REMAP */
/*
 * Trama MAIN
 */
typedef union
{
    struct
    {
        uint8_t block_size;
        /* buffer entrada de datos main */
        uint8_t dummy;
        uint8_t enable_plica;					/* habilitacion de la deteccion plica */
        uint8_t color_led;						/* color del led a encender */
        uint16 cambio_estado;					/* estado al que se quiere cambiar (cHPcryoHWstatus) */
        uint16_t u16SegundosTratamiento;		/* segundos maximos del tratamiento, la main contara su tiempo y este solo sirve como timeout */
        float fConsignaVacum;					/* indica consigna para el vacum */
        float fConsignaTemperatura;				/* indica consigna para la temperatura */
        float fTemperaturaInicio;				/* temperatura a la cual empieza a contar tiempo de tratamiento */
        float fVentanaTemperaturaTratamiento;	/* ventana de temepratura que se permite durante el tratamiento */
        uint16_t u16MaxTiempoEsperandoVac;		/* tiempo en seg para tener el vac y para que al menos la expansora me de que tiene la hidraulica encendida */
        uint16_t u16MaxTiempoEsperandoTemp;		/* tiempo en seg para tener la temperatura minima de tratamiento */
        uint16_t u16MaxTiempoFalloVac;			/* tiempo en seg para dar error de vac durante el tratamiento */
        uint16_t u16MaxTiempoFalloTemp;			/* tiempo en seg para dar error de vac durante el tratamiento */
        float fTemperaturaMaximaEntrada;		/* temperatura maxima a la entrada que permite el manipulo */
        float fTemperaturaMinimaSensores;		/* temperatura mas baja de los sensores para alarma de temperatura baja */
        uint16_t u16TiempoTempBaja;				/* tiempo en seg con temperatura baja para alarma */
        uint16_t u16dummy;
    }data;
    uint8 vector[HP_CRYO_REMAP_FRAME_MAIN_IN_SIZE + 1]; //Sumamos 1 por el block_size. Éste no esta incluido en la trama pero para que cuadre el boundary.
}tHPcryoRemapFrameMAIN_IN;

typedef union
{
    struct
    {
        uint8_t block_size;
        /* buffer salida de datos main */
        tHPcryoInputStatus estado_entradas;	/* estado del boton y la deteccion de plica */
        uint8_t id_manipulo_asociado;
        uint8_t id_manipulo_principal;
        tHPcryoWarnings avisos;
        uint16 estado;						/* estado actual del manipulo (cHPcryoHWstatus) */
        float fTempManipulo;				/* temperatura que calcula el manipulo, la mas baja de todas */
        float fTempIzquierda;				/* temperatura del lado izquierdo, la mas baja de las sondas que intervienen en el calculo */
        float fTempDerecha;					/* temperatura del lado derecho, la mas baja de las sondas que intervienen en el calculo */
        float presionVaccum;				/* presion de vac actual */
    }data;
    uint8 vector[HP_CRYO_REMAP_FRAME_MAIN_OUT_SIZE + 1]; //Sumamos 1 por el block_size. Éste no esta incluido en la trama pero para que cuadre el boundary.
}tHPcryoRemapFrameMAIN_OUT;

/*
 * Trama CONFIG
 */
typedef union
{
    struct
    {
        uint8_t block_size;						//No va con protocolo pero boundary de 32bits => dummy
        /* buffer entrada de datos config */
        uint8_t u8BloqueHabilitado;				//Para que se envie el OUT == IN NO ACTIVO POR DEFECTO
        uint8_t dummy[2];
        tHPcryoPulConfig pulsaciones_encendido;
        tHPcryoPulConfig pulsaciones_apagado;
        float fPendienteConversionTemperatura[2];
        float fOffsetConversionTemperatura[2];
        float fCuentasCalibracionTemperatura[2];
        tHPcryoColorDefinition prmtrs_color[HP_CRYO_NUM_MAX_COLORS];	//ESTO NO LO ESTAMOS ENVIANDO NI RECIBIENDO
    }data;
    uint8 vector[HP_CRYO_REMAP_FRAME_CONFIG_IN_SIZE + 1]; //Sumamos 1 por el block_size. Éste no esta incluido en la trama pero para que cuadre el boundary.
}tHPcryoRemapFrameCONFIG_IN_OUT;

/*
 * Trama DEBUG
 */
typedef union
{
    struct
    {
        uint8_t block_size;
        /* buffer entrada de datos debug */
        uint8_t u8BloqueHabilitado;						//ACTIVO POR DEFECTO
    }data;
    uint8 vector[HP_CRYO_REMAP_FRAME_DEBUG_IN_SIZE + 1]; //Sumamos 1 por el block_size. Éste no esta incluido en la trama pero para que cuadre el boundary.
}tHPcryoRemapFrameDEBUG_IN;

typedef union
{
    struct
    {
        uint8_t block_size;
        /* buffer salida de datos debug */
        //uint8_t dummy[3];
        uint8_t circuito_utilizado;
        tHPcryoProtections warnings;
        float MedidasTemperatura[HP_CRYO_MAX_TEMP_SNS];
        float Calibraciones[3];
        tHPcryoComCounter puertoSPI;
        float temp_interna;						/* temperatura interna del micro */
        float vdda;								/* tension analogica */
        float NivelPlica;
    }data;
    uint8 vector[HP_CRYO_REMAP_FRAME_DEBUG_OUT_SIZE + 1]; //Sumamos 1 por el block_size. Éste no esta incluido en la trama pero para que cuadre el boundary.
}tHPcryoRemapFrameDEBUG_OUT;

/*
 * Trama PID
 */
typedef union
{
    struct
    {
        uint8_t block_size;
        /* buffer entrada de datos config */
        uint8_t u8BloqueHabilitado;						//ACTIVADO DEFAULT
        tHPcryoConfigPID conf_pid[HP_CRYO_TOTAL_PID];
    }data;
    uint8 vector[HP_CRYO_REMAP_FRAME_PID_IN_SIZE + 1]; //Sumamos 1 por el block_size. Éste no esta incluido en la trama pero para que cuadre el boundary.
}tHPcryoRemapFramePID_IN;

typedef union
{
    struct
    {
        uint8_t block_size;
        /* buffer entrada de datos config */
        tHPcryoOutputsPID data_pid[HP_CRYO_TOTAL_PID];
    }data;
    uint8 vector[HP_CRYO_REMAP_FRAME_PID_OUT_SIZE + 1]; //Sumamos 1 por el block_size. Éste no esta incluido en la trama pero para que cuadre el boundary.
}tHPcryoRemapFramePID_OUT;

typedef union
{
    struct
    {
        uint8_t block_size;
        uint8_t u8TAG;
        uint16_t u16NumeroFuentesUso;
        uint32_t u32Modelo;
        uint8_t ptu8DatosVerificacion[4];
    }data;
    uint8 vector[HP_CRYO_REMAP_FRAME_DEFINITION_IN_SIZE+1];
}tHPcryoRemapFrameDEFINE_IN;

typedef union
{
    struct
    {
        uint8_t block_size;
        uint8_t u8TAG;
        uint16_t u16NumeroFuentesUso;
        uint32_t u32Modelo;
        uint8_t ptu8DatosVerificacion[4];
    }data;
    uint8 vector[HP_CRYO_REMAP_FRAME_DEFINITION_OUT_SIZE+1];
}tHPcryoRemapFrameDEFINE_OUT;

/* Memoria FLASH HP */
typedef union
{
    struct
    {
        uint8_t erase			: 1;
        uint8_t write			: 1;
        uint8_t read			: 1;
        uint8_t clear_flags		: 1;
        uint8_t dummy			: 4;
    }bit_field;
    uint8_t u8Actions;
}flash_actions_t;

typedef union
{
    struct
    {
        uint8_t op_in_progress		: 1;
        uint8_t erase_completed		: 1;
        uint8_t write_completed		: 1;
        uint8_t read_completed		: 1;
        uint8_t config_error		: 1;
        uint8_t dummy				: 3;
    }bit_field;
    uint8_t u8Status;
}flash_status_t;

typedef union
{
    struct
    {
        uint8 block_size;
        uint8 BloqueHabilitado;
        flash_actions_t action;
        uint8 num_bytes;
        uint32 addr;
        uint8 ptu8data[64];
    }data;
    uint8 vector[HP_CRYO_REMAP_FRAME_FLASH_MEMORY_IN_SIZE+1];
}tHPcryoRemapFrameFLASH_IN;

typedef union
{
    struct
    {
        uint8 block_size;
        uint8 Dummy;
        flash_status_t status;
        uint8 num_bytes;
        uint32 addr;
        uint8 ptu8data[64];
    }data;
    uint8 vector[HP_CRYO_REMAP_FRAME_FLASH_MEMORY_OUT_SIZE+1];
}tHPcryoRemapFrameFLASH_OUT;

typedef struct
{
    tHPcryoRemapFrameMAIN_IN mainIn;
    tHPcryoRemapFrameMAIN_OUT mainOut;
    tHPcryoRemapFrameCONFIG_IN_OUT cfgIn;
    tHPcryoRemapFrameCONFIG_IN_OUT cfgOut;
    tHPcryoRemapFrameDEBUG_IN dbgIn;
    tHPcryoRemapFrameDEBUG_OUT dbgOut;
    tHPcryoRemapFramePID_IN PIDin;
    tHPcryoRemapFramePID_OUT PIDout;
    tHPcryoRemapFrameDEFINE_IN Define_In;
    tHPcryoRemapFrameDEFINE_OUT Define_Out;
    tHPcryoRemapFrameFLASH_IN Flash_In;
    tHPcryoRemapFrameFLASH_OUT Flash_Out;
	
}tHPcryoRemapFrames;

typedef struct		//Errores asociados a los manipulos, indicados por cada manipulo por nivel. Con esta estructura se detectará el flanco
{
    uint8 espera_vac;						/* Fallo de tiempo de espera para alcanzar el vacum de consigna */
    uint8 vac_lvl;							/* Fallo de no alcanzar la presion de vacio necesaria */
    uint8 hidraulica;						/* Fallo al no tener la hidraulica activada o arrancada cuando se ha requerido */
    uint8 temp_entrada;						/* Fallo al llegar el H2O demasiado caliente al HP */
    uint8 caudal_entrada;					/* Fallo de caudal de entrada al HP */
    uint8 espera_temp;						/* Fallo de timeout de espera para alcanzar la temperatura de consigna, llegar a la ventana */
    uint8 temperatura_window;				/* Fallo al no mantener la temperatura dentro de la ventana/2 */
    uint8 sonda_error;						/* Fallo al no tener sondas de temperatura suficientes para el control */
    uint8 seguridad_frio;					/* Fallo al detectar alguna medida de temperatura por debajo de la minima */
    uint8 sin_tramas_main;					/* Fallo al no recibir tramas de MAIN en el HP */
    uint8 circuito_temp_desconocido;		/* Fallo al no reconocer el circuito de sensado de temperaturas (NTC o PT1K) */
    uint8 test_sondas_fallido;				/* Fallo al no superar el test de las sondas inicial hecho durante la inicializacion */
    uint8 temp_clavada;						/* Fallo por quedarse las temepraturas clavadas */
}tHPcryoWarningFlags;

typedef struct
{
    cHPcryoTestVacumStatus status;
    uint32 timeOut;
    cHPcryoTestVacumMode mode;
    uint8 autoIsOK;
}tHPcryoTestVacData;

typedef struct
{
    cHPcryoTrtAutoStatus status;
    uint32 tmr;
    uint32 waitTime;
    uint32 detectionTime;
    uint32 detectionFilterAcum;
    uint32 detectionFilterInc;
    uint32 detectionFilterDec;
    uint32 detectionFilterIsOKlvl;
    uint8 isOK;
}tHPcryoTrtAutoData;

typedef struct
{
    uint8 ProdTRT;
    uint8 DemoTRT;
    cHPcryoTrtModes mode;
    cHPcryoTrtTimes time;
    cHPcryoTrtVacLvls vacLvl;
    uint8 reqLabel;
    uint8 useDfltAlarmCfg;
}tHPcryoTrtParameters;

typedef struct
{
    /*V7790 - LOGs*/
    uint32 HPtreatment_Num;
	
    uint8 TrtRequested;
	
    tHPcryoTrtParameters TrtParameters;
	
    cHPcryoTreatmentStatus status;
    cHPcryoTreatmentStatus beforePause;
    uint32 timeOut;
    uint8 rqLbl;
    cHPcryoLabels Label_accepted;
    uint8 Label_reuse;
    uint8 RFID_reserved;
    returnstatus_t RFIDstatus;
    uint32 RFIDpopupTimer;
//    K70_RFID_Read_result RFID_read_label;
    uint32 startTime;
    uint32 pauseTime;
    uint32 trtTime_s;
	
    cHPcryoTrtModes mode; //inicializar
	
    tHPcryoTrtAutoData autoMode;
	
    uint8 trt_secure_plus_three;
    uint32 trt_secure_plus_three_time_ref;
	
	
    uint8 adjustVacumCnt;
    cHPcryoAdjustVacumStatus adjustVacumStatus;
    float adjustVacumValue;
    uint32 adjustVacumTimeOut;
    uint32 adjustVacumResetTime;
	
    uint8 vacumRetryCnt;
    uint32 vacumRetryTimeOut;
    uint32 vacumRetryRlsTime;
    uint8 vacumRetryRqstUserToMoveHP;
	
    /* V7778 - TEMP SEC */
    uint8 set_temp_reached;
    float trt_temp_set;
    uint32 time_ref_range2, time_ref_range3;
    /* V7778 - TEMP SEC */
}tHPcryoTrtData;

typedef struct
{
    cHPcryoInitStatus status;
}tHPcryoInitData;

typedef struct
{
    cHPcryoFinishStatus status;
}tHPcryoFinishData;

typedef struct
{
    uint32 updatePeriod_ms;
    uint32 updateTime_ms;
    uint32 remapPeriod_ms;
    uint32 remapTime_ms;
    uint32 ctrlPeriod_ms;
    uint32 ctrlTime_ms;
    uint32 refreshPeriod_ms;
    uint32 refreshTime_ms;
}tHPcryoUpdateTimes;

typedef struct
{
    uint32 minTempTimeOut;
    uint32 maxTempTimeOut;
    uint32 difTempTimeOut;
    uint32 deltaTempTimeOut;
    float difTempLastSnsValue[HP_CRYO_MAX_TEMP_SNS];
}tHPcryoCtrlData;

typedef struct
{
    cHPcryoIdleVacumStatus vacStatus;
}tHPcryoIdleData;

typedef struct
{
    uint32 tmrIsClean_ms;
    uint32 tmrCannotClean_ms;
    uint32 timeIsClean;
    uint32 timeCannotClean;
    uint32 timeCleanPaused;	/*Contabiliza el tiempo que se ha llevado el proceso de limpieza pausado para continuar con el tiempo restante del proceso de limpieza*/
    uint32 timeRefCleanPaused;
    float cleanVacum;
    uint8 NoUmbralVacResetFilter;
}tHPcryoCleanUpCycleData;

typedef struct
{
    cHPcryoCleanUpStatus status;
    uint32 time_ms;
    uint32 countDown_ms;
    uint32 checkPatientTime_ms;
    uint8 forceClean;
    tHPcryoCleanUpCycleData cycle;
    cHPcryoLabelsCleanUpOptions LabelRQcleanup;
    uint8 cancelled_times;
	
}tHPcryoClenUpData;

typedef struct
{
    uint32 tmr;
    uint32 switchTime;
    uint8 curColor;
    cHPcryoLEDcolors colors[HP_CRYO_SAT_RGB_TEST_MAX_COLORS];
}tHPcryoSAT_RGBtestData;
		
//SAT
typedef struct
{
    union
    {
        struct
        {
            uint8 cooling:1;
            uint8 vacum:1;
            uint8 bodyFillSensor:1;
            uint8 RGB:1;
            uint8 dummy:4;	//ponía 5
        }bits;
        uint8 byte;
    }testRun;
	
    tHPcryoSAT_RGBtestData RGB;
}tHPcryoSATdata;
//SAT

/*
 * Estructura de datos global del modulo
 */
typedef struct
{
    uint8 isUsed;
    cHPcryoCleanUpMoments cleanUpInitOrEnd;
    cHPcryoCleanUpRqst cleanUpRqst;
    cHPcryoStatus status;
    tHPcryoUpdateTimes time;
    tHPcryoIdleData idle;
    tHPcryoTestVacData tstVac;
    tHPcryoTrtData trt;
    tHPcryoCtrlData ctrl;
    tHPcryoClenUpData cleanUp;
    tHPcryoSATdata SAT; //SAT
    tHPcryoInitData init;
    tHPcryoFinishData finish;
    tHPcryoRemapFrames frames;
    tHPcryoWarningFlags warningFlags;
	
    uint8 SnsGroupKO[HP_CRYO_MAX_GRUPOS_DE_SONDAS];
	
    uint32 trt_OscTemp_timer;
	
    cHPcrypFatigueRqst fatigue_requested;
    cHPcrypFatigueComplete fatigue_done;
    uint8 fatigue_substep;
	
    uint8 PrevStatusSAT;
	
}tHPcryoData;

///*** VARIABLES GLOBALES PUBLICAS ***/
//extern tHPcryoData HPcryoData[HPCRYO_MAX_N_PERIFS];

///*** FUNCIONES PUBLICAS PARA PERIFERICOS ***/
///* INICIALIZACION DE DATOS */
//void HPcryoInit( void);

///* CALLBACKS */
//returnstatus_t HPcryoInitCbk( tPRFdata *PRF);
//returnstatus_t HPcryoUpdateCbk( tPRFdata *PRF);
//returnstatus_t HPcryoFinishCbk( tPRFdata *PRF);

///* DETECCION DE MODELO */
//uint8 HPcryoIsThisModelYours( uint32 model);

/*** FUNCIONES PUBLICAS PARA APP ***/
/* OBTENCION DE ESTRUCTURAS DE DATOS */
uint8 HPcryoGetFromSlot( cPRFslot slot, tHPcryoData **HPptr, tPRFdata **PRFptr);

/* OBTENCION DE DATOS */
cHPcryoModels HPcryoGetModel( tHPcryoData *HP, tPRFdata *PRF);
cPRFslot HPcryoGetSlot( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoDoubleGetSlots( uint8 *mainSlot, uint8 *offSlot, tHPcryoData *HP, tPRFdata *PRF);
cHPcryoStatus HPcryoGetStatus( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoIsAutoModeAvaible( tHPcryoData *HP, tPRFdata *PRF);

/* CONFIGURACIONES DEL HP */
uint8 HPcryoSetLEDcolor( cHPcryoLEDcolors colorID, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoSetAlarmCfg( float tempWindow, uint16 vacWaitTime_s, uint16 tempWaitTime_s,
                        uint16 vacFailTime_s, uint16 tempFailTime_s, float maxInTemp,
                        float minSensorTemp, uint16 lowTempTime_s, tHPcryoData *HP);
uint8 HPcryoSetTriggerONcfg( uint8 nPress, uint16 minTime_ms, tHPcryoData *HP);
uint8 HPcryoSetTriggerOFFcfg( uint8 nPress, uint16 minTime_ms, tHPcryoData *HP);
uint8 HPcryoSetOverHeat( uint8 OnOff, float performanceFactor, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoGetTimeRestriction (cHPcryoTrtTimes *TimeRestricted, tHPcryoData *HP, tPRFdata *PRF);

/* ESTADO IDLE */
uint8 HPcryoIdle( uint8 holdVacum, tHPcryoData *HP, tPRFdata *PRF);
cHPcryoIdleVacumStatus HPcryoIdleGetVacumStatus( tHPcryoData *HP, tPRFdata *PRF);

/* COMUN A LOS ESTADOS TRT Y TST VAC */
uint8 HPcryoStop( uint8 holdVacum, tHPcryoData *HP, tPRFdata *PRF);

/* ESTADO TEST DE VACUM */
uint8 HPcryoTestVacumStartDflt( cHPcryoTestVacumMode mode, cHPcryoTrtVacLvls vacLvl, uint8 useDfltAlarmCfg, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTestVacumStartFree( cHPcryoTestVacumMode mode, float vacum, uint8 useDfltAlarmCfg, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTestVacumStop( uint8 holdVacum, tHPcryoData *HP, tPRFdata *PRF);
cHPcryoTestVacumStatus HPcryoTestVacumStatus( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTestVacumIsInAutoAndOK( uint8 *isOK, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTestVacIsAuto( tHPcryoData *HP, tPRFdata *PRF);

/* ESTADO DE TRATAMIENTO */
uint8 HPcryoTrtStartDflt( cHPcryoTrtModes mode, cHPcryoTrtTimes time, cHPcryoTrtVacLvls vacLvl,
                          uint8 reqLabel, uint8 useDfltAlarmCfg, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTrtStartFree( cHPcryoTrtModes mode, uint16 time_s, float vacum, float temp,
                          float trtIniTemp, uint8 reqLabel, uint8 useDfltAlarmCfg, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTrtStop( uint8 holdVacum, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTrtPause( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTrtResume( tHPcryoData *HP, tPRFdata *PRF);
uint32 HPcryoTrtGetTimeSeconds( tHPcryoData *HP, tPRFdata *PRF);
uint32 HPcryoTrtGetTreatmentTotalTimeSeconds( tHPcryoData *HP, tPRFdata *PRF);
cHPcryoTreatmentStatus HPcryoTrtStatus( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTrtAdjustVacumDflt( cHPcryoTrtVacLvls vacLvl, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTrtAdjustVacumFree( float vacum, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTrtAdjustVacumAvailable( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTrtVacumRetryAvailable( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTrtVacumRetryIsUserRqstToMoveHP( tHPcryoData *HP, tPRFdata *PRF); 						//PDTE - Usar en AppGUI
uint8 HPcryoTrtResuctionsNum( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTrtIsInAutoAndOK( uint8 *isOK, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoTrtIsAuto( tHPcryoData *HP, tPRFdata *PRF);

/* ESTADO DE LIMPIEZA */
uint8 HPcryoCleanUpStartDflt( uint8 forceClean, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoCleanUpStartFree( uint8 forceClean, uint32 countDown_ms, uint32 timeIsClean, uint32 timeCannotClean,
                              float cleanVacum, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoCleanUpReset( uint8 forceClean, uint32 countDown_ms, uint32 timeIsClean, uint32 timeCannotClean,
              float cleanVacum, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoCleanUpStop( tHPcryoData *HP, tPRFdata *PRF);
cHPcryoCleanUpStatus HPcryoCleanUpStatus( tHPcryoData *HP, tPRFdata *PRF);
cHPcryoCleanUpMoments HPcryoCleanUpInitOrEnd( tHPcryoData *HP, tPRFdata *PRF);
uint32 HPcryoCleanUpGetCountDownSeconds( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoCleanUpAllowClean( uint8 go, tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoCleanUpFinishCountDown( tHPcryoData *HP, tPRFdata *PRF);

//SAT
/* ESTADO DE SAT */
uint8 HPcryoSATcoolingTestStart( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoSATcoolingTestStop( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoSATvacumTestStart( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoSATvacumTestStop( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoSATbodyFillSensorTestStart( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoSATbodyFillSensorTestStop( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoSATbodyFillSensorIsDetecting( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoSAT_RGBtestStart( tHPcryoData *HP, tPRFdata *PRF);
uint8 HPcryoSAT_RGBtestStop( tHPcryoData *HP, tPRFdata *PRF);
void HPcryoSATallTestStop( tHPcryoData *HP, tPRFdata *PRF);
//SAT

////FATIGA
//uint8 HPcryoFatiga ( tHPcryoData *HP, tPRFdata *PRF);
//uint8 HPcryoFatigaStart ( cHPcrypFatigueRqst fatiga, tHPcryoData *HP, tPRFdata *PRF);
//uint8 HPcryoFatigaStop ( tHPcryoData *HP, tPRFdata *PRF);
//uint8 HPcryoFatigaComplete ( cHPcrypFatigueComplete fatigaDone, tHPcryoData *HP, tPRFdata *PRF);
//cHPcrypFatigueComplete HPcryoFatigaState ( tHPcryoData *HP, tPRFdata *PRF);

//cHPcryoFatigueStatus HPcryoFtg1Update( cPRFslot perif);
//cHPcryoFatigueStatus HPcryoFtg2Update( cPRFslot perif);
//void HPcryoFtg3Update( tHPcryoData *HP, tPRFdata *PRF);
//void HPcryoFtg4Update( tHPcryoData *HP, tPRFdata *PRF);
//void HPcryoFtg5Update( tHPcryoData *HP, tPRFdata *PRF);
////FATIGA

//RECONFIG HP
uint8 HPcryoReconfigHP( cHPcryoModels model2cfg, tHPcryoData *HP, tPRFdata *PRF);
//RECONFIG HP

////CleanUp Cancellation
//void HPcryoCleanUpCancelledTimesSentToHP ( uint8 cancelled_times, tHPcryoData *HP, tPRFdata *PRF);
//uint8 HPcryoCleanUpCancelledTimesReceiveFromHP ( tHPcryoData *HP, tPRFdata *PRF);
//uint8 HPcryoCleanUpCancelAllowed ( uint8 slot);
//uint8 HPcryoCleanUpNumberOfCancellations ( cPRFslot slot);
////CleanUp Cancellation

//Show Temperature
float HPcryoHPtemperature ( cPRFslot slot);
//Show Temperature

//void HPcryoGetBit51 ( tHPcryoData *HP, tPRFdata *PRF);

uint8 HPcryoGetTRTplusThree ( tHPcryoData *HP, tPRFdata *PRF);
uint32 HPcryoGetTRTplusThreeTime ( tHPcryoData *HP, tPRFdata *PRF);

//extern uint32 RFID_time_ref[4];	//DEBUG	-	Control de tiempos modulo RFID
//extern uint32 RFID_time_diff[4];	//DEBUG	-	Control de tiempos modulo RFID

#endif
