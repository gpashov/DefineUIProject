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
//Parametros de configuraci�n para la comunicaci�n con el m�dulo RFID
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
	K70_RFID_CPU_ERR_LABEL_INVALID,		//Tarjeta con c�digo que no es el que buscamos
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
	uint8_t ptu8BufferDataRFID[180];			//Buffer de comunicaci�n
	RFID_block_or_free_t RFID_resource_stat;	//Distintos estados del recurso (RFID)
	
	uint32 RFID_polling_time_aux;				//Variable auxiliar de tiempo que sirve para hacer polling una vez cada segundo
	returnstatus_t RFID_Error;					//Parametro que devuelve el estado de la lectura del RFID (RFID_read_label)
	
	uint32 RFID_tout_w8_info;					//Time out empleado para evitar cuelgues del m�dulo si hay una perdida de comunicaci�n mientras se espera una respuesta (Leyenfo 'o' o 'k')
	uint8 RFID_tout_rep;						//Contador de repeticiones para la gestion de la perdida de comunicaci�n

	cRFID_labelStatus RFID_label_detected;					//Flag que indica cuando se detecta la presencia de una etiqueta

	uint8 Err_loop_count;
}RFID_control_t;


// Variables Globales 


// Delaraci�n de funciones
/*
 * Funci�n RFID_init
 * Descripci�n:
 *      Se encarga de la inicializaci�n de las variables
 * Par�metros:
 * 		- No pide ning�n dato de entrada
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void RFID_init (void);

/*
 * Funci�n RFID_read_label
 * Descripci�n:
 *      Se le pasa dos parametros, el modelo de la tarjeta que se espera leer y un flag indicando si se desea o no borrar la etiqueta.
 *      Este proceso no es bloqueante, por lo que se realiza en varias vueltas del bucle principal, por lo que devuelve cada vez que se llama a esta funci�n el estado del proceso.
 *      Una vez finalizado devuelve "RFID_CARD_VALID" , si el flag de borrado estaba activa se habr� borrado la etiqueta, si no, no, pero en cualquier caso
 *      la etiqueta leida ha coincidido con la esperada.
 *      En caso de devolver "RFID_CARD_NO_VALID" indica que la etiqueta leida no coincide con la esperada.
 *      
 *      Para emplear este modulo correctamente se ha de hacer previamente un lock para reservar el recurso, de esta forma ning�n otro elemento intentar� acceder, ya que esta funci�n les indicar� que ya est� reservada.
 *      A continuaci�n se puede ir llamando a esta funci�n hasta que nos d� un resultado, y finalmente realizaremos un free para dejar libre el recurso y pueda ocuparlo otro elemento.
 * Par�metros:
 * 		- uint8 *modelo : Modelo que se busca leer
 * 		
 * 		- uint8 *model_read : Modelo que se ha leido con el RFID
 * 		
 * 		- RFID_EraseAction EraseTarjetRFID : Flag que indica si se quiere o no borrar la etiqueta
 * 		
 * 		- K70_RFID_CPU_ERR_tt *RFID_Error_code : C�digo de error que indica el resultado de la gestion de la lectura RFID
 * Retorno:
 *      - returnstatus_t : Estado del proceso, indica si se ha finalziado con exito, con error, si se puede abortar el proceso (RUNNING) o si est� bloqueado sin posibilidad de aborta (BLOCKING).
 * Errores:
 * 
 */
returnstatus_t RFID_read_label (char *modelo, char *model_read, RFID_EraseAction EraseTarjetRFID, K70_RFID_CPU_ERR_tt *RFID_Error_code);

/*
 * Funci�n RFID_lock
 * Descripci�n:
 *      Bloquea el recurso para que no lo puedan llamar mientras est� trabajando. Los mensajes que devuelve son 2: "RFID_NOW_IN_USE" cuando el que ha llamado a la funci�n
 *      ha reservado el recurso del RFID para �l. Y "RFID_ALREADY_IN_USE" cuando el recurso ya est� reservado por alguien.
 *      El control de si "alguien" tiene reservado el recurso para �l se gestiona fuera.
 *      En el parametro de devoluci�n tambi�n se indica si el proceso ha fallado, de forma que desde fuera se gestiona el avisar de a�adir un error al modulo de errores.
 * Par�metros:
 * 		- No pide ning�n dato de entrada
 * Retorno:
 *      - Devuelve el estado en el que se encuentra el modulo RFID
 * Errores:
 * 
 */
RFID_block_or_free_t RFID_lock (void);

/*
 * Funci�n RFID_free
 * Descripci�n:
 *      En caso de que no est� un proceso de lectura llevandose a cabo, se encarga de liberar el recurso del RFID.
 *      Hay que tener en cuenta lo que devuelve, "RFID_ALREADY_IN_USE" significa que no puede liberarse el recurso por que a�n hay un proceso de lectura realizandose
 *      y "RFID_FREE_TO_USE" indicar� que el recurso ha sido liberado y podr� se bloqueado para su uso de nuevo.
 * Par�metros:
 * 		- No pide ning�n dato de entrada
 * Retorno:
 *      - Devuelve el estado en el que se encuentra el modulo RFID
 * Errores:
 * 
 */ 
RFID_block_or_free_t RFID_free (void);

/*
 * Funci�n RFID_motor
 * Descripci�n:
 *      Si el recurso del RFID est� libre (no reservado, no se est� usando, por nadie) y adem�s desde la �ltima vez que se realiz� un POLLING
 *      ha pasado al menos 1 segundo, se realiza de nuevo un POLLING.
 *      Devuelve un codigo de error que indica SUCCESS si todo ha ido sin problemas, y ERROR si no ha funcionado bien y ha de activarse desde fuera un AVISO DE ERROR.
 * Par�metros:
 * 		- No pide ning�n dato de entrada
 * Retorno:
 *      - returnstatus_t : Indica si ha finalizado el polling de forma exitosa o con error
 * Errores:
 * 		Devuelve una variable que se emplear� para generar un aviso de error durante el polling
 */ 
returnstatus_t RFID_motor (void);

/*
 * Funci�n RFID_label_detection
 * Descripci�n:
 *      Si se detecta la presencia de una etiqueta (elemento para la lectura con el RFID) devuelve un 1, en caso contrario un 0.
 * Par�metros:
 * 		- No pide ning�n dato de entrada
 * Retorno:
 *      - uint8 : Indica si se ha detectado la presencia de una etiqueta o no
 * Errores:
 * 		
 */ 
uint8 RFID_label_detection(void);

/*
 * Funci�n RFID_getStatus
 * Descripci�n:
 *      
 * Par�metros:
 * 		
 * Retorno:
 *      
 * Errores:
 * 		
 */
RFID_estats_t RFID_getStatus( void);

/*
 * Funci�n RFID_GetFWversion
 * Descripci�n:
 *      Realiza la lectura de la versi�n de FW que tiene la PCB del RFID.
 * Par�metros:
 * 		- No pide ning�n dato de entrada.
 * Retorno:
 *      - uint8 : Devuelve la versi�n de FW.
 * Errores:
 * 		
 */
uint8 RFID_GetFWversion (void);

#endif /* RFID_H_ */
