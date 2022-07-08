#ifndef RTC_H_
#define RTC_H_

//Librer�as
#include "PE_Types.h"
//#include "HAL_RTC.h"
#include "GeneralDefines.h"
#include "../Ticks/Ticks.h"

//Constantes
#define RTC_MAX_TIME_TO_CHECK	55000		//55 segundos	-	Tiempo m�ximo para realizar la comprobaci�n de que el RTC funciona correctamente
#define RTC_MIN_TIME_TO_CHECK	5000		//5 segundos	-	Tiempo minimo para realizar la comprobaci�n de que el RTC funciona correctamente

//Variables

//Estructuras

//Funciones
/*
 * Funci�n RTC_init
 * Descripci�n:
 *      Realiza la inicializaci�n de todas las variables.
 * Par�metros:
 * 		- No solicita ning�n dato
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
returnstatus_t RTC_init (void);

/*
 * Funci�n RTC_start
 * Descripci�n:
 *      Realiza la inicializaci�n de todas las variables cuando el RTC nunca ha sido inicializado antes.
 * Par�metros:
 * 		- No solicita ning�n dato
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
returnstatus_t RTC_start (void);

/*
 * Funci�n RTC_get_time
 * Descripci�n:
 *      Toma el tiempo del RTC
 * Par�metros:
 * 		- Puntero a la variable donde queremos guardar el tiempo del RTC
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
returnstatus_t RTC_get_time (LDD_RTC_TTime *Time);

/*
 * Funci�n RTC_set_time
 * Descripci�n:
 *      Establece el tiempo del RTC
 * Par�metros:
 * 		- Puntero a la variable donde se encuentra el valor de tiempo a establecer
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
returnstatus_t RTC_set_time (LDD_RTC_TTime *Time);

/*
 * Funci�n RTC_running
 * Descripci�n:
 *      Realiza la comprobaci�n de que el RTC continua funcionando correctamente
 * Par�metros:
 * 		- No solicita ning�n dato
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
returnstatus_t RTC_running (void);

#endif /* RTC_H_ */
