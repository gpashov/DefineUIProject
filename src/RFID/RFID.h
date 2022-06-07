/*
< * RFID.h
 *
 *  Created on: Nov 20, 2018
 *      Author: ingenieria9
 */

#ifndef RFID_H_
#define RFID_H_

//Librerias
//#include "PE_Types.h"
#include "../GeneralDefines.h"
//#include "../ProtocolMaster/ProtocolMaster.h"
//#include "../Ticks/Ticks.h"

//Constantes
//Parametros de configuración para la comunicación con el módulo RFID
#define RFID_MAX_NUM_ESCLAUS 			1
#define EXPANSORA_DEFAULT_ADDR_RFID		101

#define RFID_SLAVE_ADDRESS			101
#define	RFID_MEMORY_SELECTION		0
#define RFID_TIME_OUT_THREAD_100	100
#define RFID_TIME_OUT_THREAD_200	200
#define RFID_TIME_OUT_5_THREAD		5
#define RFID_1_NUM_BYTES			1
#define RFID_178_NUM_BYTES			178
#define RFID_NUM_MAX_1_RETRY		1
#define RFID_NUM_MAX_RETRY_3		3
#define RFID_NUM_MAX_RETRY_5		5
#define RFID_NUM_MAX_RETRY_10		10

#define RFID_NUM_MAX_LOOPS_ERR		10

#define RFID_PAYLOAD_MAX_DATA_TRANSMISSION		64
#define RFID_PAYLOAD_DATA_TAIL_TRANSMISSION		50

//Indicador de un segundo en milisegundos para esperar entre "pollings"
#define RFID_TIME_POLLING_1SEG		1000
#define RFID_TOUT_50MS_ERR_COM		50		//En el bucle de consulta por la lectura de la tarjeta (busqueda de la 'o'), tiempo de referencia para la lectura, para no preguntar constantemente.
#define RFID_TOUT_MAX_REP			20		//50ms+100ms = 150ms+20 = 3segundos para salir con error de reintentos de lectura RFID
#define RFID_SLOT_POS				1

typedef enum
{
	RFID_DETECTING_LABEL,
	RFID_LABEL_DETECTED,
	RFID_NO_LABEL_DETECTED
	
}cRFID_labelStatus;

typedef enum
{
	K70_RFID_CPU_ERR_OK						= 0,
	
	K70_RFID_CPU_ERR_BASE,
	K70_RFID_CPU_ERR_LABEL_INVALID,		//Tarjeta con código que no es el que buscamos
	K70_RFID_CPU_ERR_CANNOT_ERASE,		//No se ha podido realziar el borrado de la tarjeta
	K70_RFID_CPU_ERR_CANNOT_READ,		//No se ha podido leer la tarjeta
	K70_RFID_CPU_ERR_CANNOT_READ_ERASED,//No se ha podido leer la tarjeta tras el borrado

}K70_RFID_CPU_ERR_tt;

typedef enum
{
	RFID_LABEL_OK,
	RFID_LABEL_ERASED,
	RFID_LABEL_UNKNOWN,
	RFID_WRONG_LABEL,
	
	RFID_NO_LABEL,
	
	RFID_MAX_LABEL_OPTIONS
}K70_RFID_Read_result;

typedef enum
{
	RFID_STAT_INITIALIZE1,
	RFID_STAT_INITIALIZE2,
	RFID_STAT_INITIALIZE3,
	RFID_STAT_READING,
	RFID_STAT_WAIT_READING,
	RFID_STAT_START_READING,
	RFID_STAT_START_READING1,
	RFID_STAT_START_READING2,
	RFID_STAT_CHECK_PASSWORD,
	RFID_STAT_CHECK_MODELERASE,
	RFID_STAT_WRITE_RESULT,
	RFID_STAT_WAIT_READING_RESULT,
	RFID_STAT_VALIDATE,
	
}RFID_estats_t;


typedef enum
{
	
	RFID_FREE_TO_USE,
	RFID_NOW_IN_USE,
	RFID_ALREADY_IN_USE,
	
}RFID_block_or_free_t;


typedef enum
{	
	RFID_ERASE_LABEL,	
	RFID_NOT_ERASE_LABEL,
	
}RFID_EraseAction;


//Estructuras

typedef struct
{
	uint8 u8MotorAccio;
	uint8 u8Memoria;
	uint8 u8TipusOp;
	uint16 u16NumBytes;
	K70_RFID_CPU_ERR_tt u16CodiError;
	uint8 *ptu8Data;
	uint32 u32Addr;
	
}RFID_accions_t;

typedef struct
{
	uint8 u8IdCPU;

	uint8 u8TipusClauLectura;
	uint8 u8TipusClauEscriptura;
	uint8_t u8esclau_comodin1;
	uint8_t u8esclau_comodin2;
	RFID_estats_t u8Motor;
	RFID_estats_t u8MotorErase;
		
//	prot_mems_status_t prot_mems_status;
	uint32 u32TempsEntrePooling;
	uint32 u32TempsEntreActualitzacioMapa;
	RFID_accions_t accions;
	
}RFID_esclau_t;

typedef struct
{
	uint8 u8NumeroCPU;
	RFID_esclau_t esclau;

	uint32 MotorRFIDSendFrame;					//Motor empleado en el envio de tramas
	uint8_t ptu8BufferDataRFID[180];			//Buffer de comunicación
	RFID_block_or_free_t RFID_resource_stat;	//Distintos estados del recurso (RFID)
	
	uint32 RFID_polling_time_aux;				//Variable auxiliar de tiempo que sirve para hacer polling una vez cada segundo
	returnstatus_t RFID_Error;					//Parametro que devuelve el estado de la lectura del RFID (RFID_read_label)
	
	uint32 RFID_tout_w8_info;					//Time out empleado para evitar cuelgues del módulo si hay una perdida de comunicación mientras se espera una respuesta (Leyenfo 'o' o 'k')
	uint8 RFID_tout_rep;						//Contador de repeticiones para la gestion de la perdida de comunicación

	cRFID_labelStatus RFID_label_detected;					//Flag que indica cuando se detecta la presencia de una etiqueta

	uint8 Err_loop_count;
}RFID_control_t;


// Variables Globales 


// Delaración de funciones
/*
 * Función RFID_init
 * Descripción:
 *      Se encarga de la inicialización de las variables
 * Parámetros:
 * 		- No pide ningún dato de entrada
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void RFID_init (void);

/*
 * Función RFID_read_label
 * Descripción:
 *      Se le pasa dos parametros, el modelo de la tarjeta que se espera leer y un flag indicando si se desea o no borrar la etiqueta.
 *      Este proceso no es bloqueante, por lo que se realiza en varias vueltas del bucle principal, por lo que devuelve cada vez que se llama a esta función el estado del proceso.
 *      Una vez finalizado devuelve "RFID_CARD_VALID" , si el flag de borrado estaba activa se habrá borrado la etiqueta, si no, no, pero en cualquier caso
 *      la etiqueta leida ha coincidido con la esperada.
 *      En caso de devolver "RFID_CARD_NO_VALID" indica que la etiqueta leida no coincide con la esperada.
 *      
 *      Para emplear este modulo correctamente se ha de hacer previamente un lock para reservar el recurso, de esta forma ningún otro elemento intentará acceder, ya que esta función les indicará que ya está reservada.
 *      A continuación se puede ir llamando a esta función hasta que nos dé un resultado, y finalmente realizaremos un free para dejar libre el recurso y pueda ocuparlo otro elemento.
 * Parámetros:
 * 		- uint8 *modelo : Modelo que se busca leer
 * 		
 * 		- uint8 *model_read : Modelo que se ha leido con el RFID
 * 		
 * 		- RFID_EraseAction EraseTarjetRFID : Flag que indica si se quiere o no borrar la etiqueta
 * 		
 * 		- K70_RFID_CPU_ERR_tt *RFID_Error_code : Código de error que indica el resultado de la gestion de la lectura RFID
 * Retorno:
 *      - returnstatus_t : Estado del proceso, indica si se ha finalziado con exito, con error, si se puede abortar el proceso (RUNNING) o si está bloqueado sin posibilidad de aborta (BLOCKING).
 * Errores:
 * 
 */
returnstatus_t RFID_read_label (char *modelo, char *model_read, RFID_EraseAction EraseTarjetRFID, K70_RFID_CPU_ERR_tt *RFID_Error_code);

/*
 * Función RFID_lock
 * Descripción:
 *      Bloquea el recurso para que no lo puedan llamar mientras está trabajando. Los mensajes que devuelve son 2: "RFID_NOW_IN_USE" cuando el que ha llamado a la función
 *      ha reservado el recurso del RFID para él. Y "RFID_ALREADY_IN_USE" cuando el recurso ya está reservado por alguien.
 *      El control de si "alguien" tiene reservado el recurso para él se gestiona fuera.
 *      En el parametro de devolución también se indica si el proceso ha fallado, de forma que desde fuera se gestiona el avisar de añadir un error al modulo de errores.
 * Parámetros:
 * 		- No pide ningún dato de entrada
 * Retorno:
 *      - Devuelve el estado en el que se encuentra el modulo RFID
 * Errores:
 * 
 */
RFID_block_or_free_t RFID_lock (void);

/*
 * Función RFID_free
 * Descripción:
 *      En caso de que no esté un proceso de lectura llevandose a cabo, se encarga de liberar el recurso del RFID.
 *      Hay que tener en cuenta lo que devuelve, "RFID_ALREADY_IN_USE" significa que no puede liberarse el recurso por que aún hay un proceso de lectura realizandose
 *      y "RFID_FREE_TO_USE" indicará que el recurso ha sido liberado y podrá se bloqueado para su uso de nuevo.
 * Parámetros:
 * 		- No pide ningún dato de entrada
 * Retorno:
 *      - Devuelve el estado en el que se encuentra el modulo RFID
 * Errores:
 * 
 */ 
RFID_block_or_free_t RFID_free (void);

/*
 * Función RFID_motor
 * Descripción:
 *      Si el recurso del RFID está libre (no reservado, no se está usando, por nadie) y además desde la última vez que se realizó un POLLING
 *      ha pasado al menos 1 segundo, se realiza de nuevo un POLLING.
 *      Devuelve un codigo de error que indica SUCCESS si todo ha ido sin problemas, y ERROR si no ha funcionado bien y ha de activarse desde fuera un AVISO DE ERROR.
 * Parámetros:
 * 		- No pide ningún dato de entrada
 * Retorno:
 *      - returnstatus_t : Indica si ha finalizado el polling de forma exitosa o con error
 * Errores:
 * 		Devuelve una variable que se empleará para generar un aviso de error durante el polling
 */ 
returnstatus_t RFID_motor (void);

/*
 * Función RFID_label_detection
 * Descripción:
 *      Si se detecta la presencia de una etiqueta (elemento para la lectura con el RFID) devuelve un 1, en caso contrario un 0.
 * Parámetros:
 * 		- No pide ningún dato de entrada
 * Retorno:
 *      - uint8 : Indica si se ha detectado la presencia de una etiqueta o no
 * Errores:
 * 		
 */ 
uint8 RFID_label_detection(void);

/*
 * Función RFID_getStatus
 * Descripción:
 *      
 * Parámetros:
 * 		
 * Retorno:
 *      
 * Errores:
 * 		
 */
RFID_estats_t RFID_getStatus( void);

/*
 * Función RFID_GetFWversion
 * Descripción:
 *      Realiza la lectura de la versión de FW que tiene la PCB del RFID.
 * Parámetros:
 * 		- No pide ningún dato de entrada.
 * Retorno:
 *      - uint8 : Devuelve la versión de FW.
 * Errores:
 * 		
 */
uint8 RFID_GetFWversion (void);

#endif /* RFID_H_ */
