/*
 * App.h
 *
 *  Created on: Jan 25, 2017
 *      Author: ingenieria1
 */

#ifndef APP_H_
#define APP_H_

#include "PE_Types.h"

//#define DEBUG_STANDALONE		//define para utilizar la placa Main fuera del equipo. En solitario.
#define DEBUG_INFO				//imprime valores de información del equipo
#define DEBUG_CONSOLE_MENU		//activamos consola

/* PDTE version de software provisional */
//#define APP_SW_VER_DM_NO_LIMIT				//Comentar esto para hacer la limitada V Y.XX0 y descomentarlo para hacer la no limitada Y.XX1
#ifdef APP_SW_VER_DM_NO_LIMIT
#define APP_SW_VER_DM_MODE 0.001
#else
#define APP_SW_VER_DM_MODE 0.000
#endif

//#define APP_SW_VER_SKIP_LANG_SELECTION			//Comentar esto para que por defecto se salte la seleccion de idiomas
#define APP_SW_VER_TEMP_SAFE_PD_LABEL			//Comentar para que la etiqueta de producción evalue las congelaciones
//#define APP_SW_VER_AUTO_ENABLE				//Comentar para hacer que la versión no cuente con modo AUTO
#define APP_SW_VER_CLEANUP_ENABLE				//Comentar para que la versión no cuente con la limpieza
#define APP_SW_VER_NEW_CLEANUP_MODE				//Comentar para deshabilitar el nuevo modo de limpieza (y volver al antiguo)
//#define APP_SW_VER_SHOW_TEMPERATURES			//Comentar para deshabilitar el visor de las temperaturas

#define APP_SW_VERSION ( 7.791 + APP_SW_VER_DM_MODE)
//#define APP_SW_VERSION ( 9.995 + APP_SW_VER_DM_MODE)

#define APP_INIT_TIME_RESET_ERROR	20000		//Los pirmeros 20 segundos al encender el equipo no se tienen en cuenta los errores

/* SERIAL FLASH - ADDRESS */
#define CALIBRATION_MEMORY_ADDRESS  			0x200
#define TEMP_OSC_PROCESS_ENABLE_MEMORY_ADDRESS  0x20c	/*CALIBRATION_MEMORY_ADDRESS(0x200) + MEMORY_CAL_LENGTH(11B)*/
#define RESUCTION_VIEWER_ENABLE_MEMORY_ADDRESS  0x20e	/*CALIBRATION_MEMORY_ADDRESS(0x200) + MEMORY_CAL_LENGTH(11B) + TEMP_OSC_MEMORY_LENGTH (1B)*/

extern uint8 StateDebug;
extern uint32 Debug_j;
extern uint32 Debug_k;

//void APP_Main(void);

#endif /* APP_H_ */
