#ifndef RTC_H_
#define RTC_H_

//Librerías
#include "PE_Types.h"
//#include "HAL_RTC.h"
#include "GeneralDefines.h"
#include "../Ticks/Ticks.h"

//Constantes
#define RTC_MAX_TIME_TO_CHECK	55000		//55 segundos	-	Tiempo máximo para realizar la comprobación de que el RTC funciona correctamente
#define RTC_MIN_TIME_TO_CHECK	5000		//5 segundos	-	Tiempo minimo para realizar la comprobación de que el RTC funciona correctamente

//Variables

//Estructuras

//Funciones
/*
 * Función RTC_init
 * Descripción:
 *      Realiza la inicialización de todas las variables.
 * Parámetros:
 * 		- No solicita ningún dato
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
returnstatus_t RTC_init (void);

/*
 * Función RTC_start
 * Descripción:
 *      Realiza la inicialización de todas las variables cuando el RTC nunca ha sido inicializado antes.
 * Parámetros:
 * 		- No solicita ningún dato
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
returnstatus_t RTC_start (void);

/*
 * Función RTC_get_time
 * Descripción:
 *      Toma el tiempo del RTC
 * Parámetros:
 * 		- Puntero a la variable donde queremos guardar el tiempo del RTC
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
returnstatus_t RTC_get_time (LDD_RTC_TTime *Time);

/*
 * Función RTC_set_time
 * Descripción:
 *      Establece el tiempo del RTC
 * Parámetros:
 * 		- Puntero a la variable donde se encuentra el valor de tiempo a establecer
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
returnstatus_t RTC_set_time (LDD_RTC_TTime *Time);

/*
 * Función RTC_running
 * Descripción:
 *      Realiza la comprobación de que el RTC continua funcionando correctamente
 * Parámetros:
 * 		- No solicita ningún dato
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
returnstatus_t RTC_running (void);

#endif /* RTC_H_ */
