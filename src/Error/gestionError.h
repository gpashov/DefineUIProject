/*
 * gestionErrores2.h
 *
 *  Created on: Nov 15, 2016
 *      Author: ingenieria1
 */

#ifndef GESTIONERRORES_H_
#define GESTIONERRORES_H_

//Librerías
#include "PE_Types.h"
#include "GeneralDefines.h"
#include "../Perifericos/Perifericos.h"
#include "../Perifericos/HPcryo.h"
#include "../Expansora/Expansora.h"
#include "../Ticks/Ticks.h"

//Constantes
#define NUMBER_ERRORS_LOG	10
#define NUMBER_AVISOS_LOG	10

#define ERROR_CODE_PERIF_1_OFFSET	1000
#define ERROR_CODE_PERIF_2_OFFSET	2000
#define ERROR_CODE_PERIF_3_OFFSET	3000
#define ERROR_CODE_PERIF_4_OFFSET	4000
#define ERROR_CODE_MACHINE_OFFSET	5000

#define ERR_FORCE_VACUUM_OFF		0
#define ERR_MANTAIN_VACUUM_STATE	1

#define ERR_LIST_ERR_STANDBY		5

#define ERR_LISR_PER_PERIFERIC		35

#define THREE_MIN_MILISEC			180000
#define ONE_MIN_MILISEC				60000
#define HALF_MIN_MILISEC			30000
#define FIVETEEN_SEC_MILISEC		15000
#define TEN_SEC_MILISEC				10000
#define FIVE_SEC_MILISEC			5000
#define ONE_MILISEC					1
#define ONE_SEC_MILISEC				1000
#define TWO_SEC_MILISEC				2000
#define REPS_MAX_TO_FILTR_ERR		200

#define TIME_2_CHANGE_ERR_POLICY	900000	/*15 min*/

static const uint8 REP_TO_FIND_THE_CORRECT_VACCUM = 4;



//Estructuras
typedef enum
{
	Aviso_NivelAguaBajo 	= 0x0001,
	Aviso_NivelAguaMedio 	= 0x0002,
	Aviso_TempAmbiente 		= 0x0004,
	Aviso_RFID				= 0x0008,
	Aviso_RTC				= 0x0010,
	Aviso_FiltroAire		= 0x0020,
	
	Aviso_All				= 0xFFFF
}Avisos;

typedef enum
{				//Lista de los distintos errores posibles
	Error_ok	=	0,

	// Error SPI
	Error_ComSPIMAN1			,//= 1,D
	Error_ComSPIMAN2			,//= 2,
	Error_ComSPIMAN3			,//= 3,
	Error_ComSPIMAN4			,//= 4,
                                
	// Error 485                
	Error_Com485_H201			,//= 5,D
	Error_Com485_H202			,//= 6,
	Error_Com485_H203			,//= 7,
	Error_Com485_H204			,//= 8,
	                            
	Error_Com485_VAC1			,//= 9,
	Error_Com485_VAC2			,//= 10,
	Error_Com485_VAC3			,//= 11,
	Error_Com485_VAC4			,//= 12,
                                
	Error_Com485_Perd			,//= 13,
                                
	Error_Com485_Rebos			,//= 14,
	                            
	Error_Com485_Fuente1		,//= 15,
	Error_Com485_Fuente2		,//= 16,
	                            
	// Error Resucciones        
    Error_NResuccionesMAN1		,//= 17,D		//Gestión especial del error
    Error_NResuccionesMAN2		,//= 18,		//Gestión especial del error
    Error_NResuccionesMAN3		,//= 19,		//Gestión especial del error
    Error_NResuccionesMAN4		,//= 20,		//Gestión especial del error
                                
    // Error Nivel H20          
    Error_NivelH2OBajo			,//= 21,
    Error_NivelH2OMedio			,//= 22,
                               
    // Error Sensor de temperatura
    Err_SnsTempAmbienteAltaAviso			,//= 23,D
    Err_SnsTempAmbienteAltaAlarma			,//= 24,D
                                
    // Error Caudal             
    Err_CaudalimetroMan1		,//= 25,D
	Err_CaudalimetroMan2		,//= 26,
	Err_CaudalimetroMan3		,//= 27,
	Err_CaudalimetroMan4		,//= 28,
	
	// Error Hidraulica             
	Err_HidraulicaMan1			,//= 29,D
	Err_HidraulicaMan2			,//= 30,
	Err_HidraulicaMan3			,//= 31,
	Err_HidraulicaMan4			,//= 32,
	
	// Varios
	Err_AcFail					,//= 33			//Aparece al apagar la maquina
	Err_TpuntFail				,//= 34
	Err_ButtStandby				,//= 35
	
	// Error Control Peltier    
	Err_ControlFApeltier1		,//= 36,		//Gestión especial del error
	Err_ControlFApeltier2		,//= 37,		//Gestión especial del error
	Err_ControlFApeltier3		,//= 38,		//Gestión especial del error
	Err_ControlFApeltier4		,//= 39,		//Gestión especial del error
	                            
	Err_ControlFApeltier1TRT	,//= 40,		//Gestión especial del error
	Err_ControlFApeltier2TRT	,//= 41,		//Gestión especial del error
	Err_ControlFApeltier3TRT	,//= 42,		//Gestión especial del error
	Err_ControlFApeltier4TRT	,//= 43,		//Gestión especial del error
	                            
	// Error Comunicación Expansora
	Err_ComExp					,//= 44,D
                                
	// Error Cominicación RFID  
	Err_ComRFID					,//= 45					
	Err_ComRFID1				,//= 46,
	Err_ComRFID2				,//= 47,
	Err_ComRFID3				,//= 48,
	Err_ComRFID4				,//= 49,
	                            
	// Error RTC                
	Err_RTC						,//= 50,
	                            
	//                          
	Err_NPltInsf1				,//= 51,D //#error alta prioridad
	Err_NPltInsf2				,//= 52,
	Err_NPltInsf3				,//= 53,
	Err_NPltInsf4				,//= 54,
	                            
	// Error Time Out           
	Err_TimeOutMan1				,//= 55,D
	Err_TimeOutMan2				,//= 56,
	Err_TimeOutMan3				,//= 57,
	Err_TimeOutMan4				,//= 58,
	                            
	Err_TimeOutVacm1			,//= 59,D
	Err_TimeOutVacm2			,//= 60,
	Err_TimeOutVacm3			,//= 61,
	Err_TimeOutVacm4			,//= 62,
		                       
	// Error Temperatura Entrada
	Err_TempEntradaAlta1		,//= 63,D
	Err_TempEntradaAlta2		,//= 64,
	Err_TempEntradaAlta3		,//= 65,
	Err_TempEntradaAlta4		,//= 66,
	                            
	// Error TOUT               
	Err_TimeOutVacEstable1		,//= 67,D
	Err_TimeOutVacEstable2		,//= 68,
	Err_TimeOutVacEstable3		,//= 69,
	Err_TimeOutVacEstable4		,//= 70,
	                            
	Err_ToutTempIniciTrart1		,//= 71,D
	Err_ToutTempIniciTrart2		,//= 72,
	Err_ToutTempIniciTrart3		,//= 73,
	Err_ToutTempIniciTrart4		,//= 74,
	                            
	Err_ToutTempFinalTrat1		,//= 75,D
	Err_ToutTempFinalTrat2		,//= 76,
	Err_ToutTempFinalTrat3		,//= 77,
	Err_ToutTempFinalTrat4		,//= 78,
	                           
	// Error Seguridad Frio     
	Err_SeguridadFrioMan1		,//= 79,D //#error alta prioridad
	Err_SeguridadFrioMan2		,//= 80,
	Err_SeguridadFrioMan3		,//= 81,
	Err_SeguridadFrioMan4		,//= 82,
                                
	// Error PID                
	Err_PIDoff1					,//= 83,D
	Err_PIDoff2					,//= 84,
	Err_PIDoff3					,//= 85,
	Err_PIDoff4					,//= 86,
	
	// Error comunicación manopulo-main
	Err_HPsinTramasMain1		,//= 87D
	Err_HPsinTramasMain2		,//= 88
	Err_HPsinTramasMain3		,//= 89
	Err_HPsinTramasMain4		,//= 90
	
	// GENERADOS POR LA MAIN
	Error_Com485_DetectorNivel	,//= 91,D
	Error_BusAlarma_Seta		,//= 92 //#error alta prioridad solo este
	Error_BusAlarma_no_identificado,//=93
	Error_FiltroAire			,//= 94D
	
	// David
	Error_TempPumpOutAlta		,//95
	Error_TempPumpOutBaja		,//96
	Error_TempRetornoAlta		,//97
	Error_TempRetornoBaja		,//98
	Err_SnsTempAmbienteBajaAlarma,//99
	Error_CaudalRetornoMaximo	,//100
	Error_MaxConsBombaH2O		,//101
	Error_MaxConsVentRad,//102
	Error_MaxCons24Vtotal,//103
	
	Error_SinMemoriaParaPerif,//104
	Error_ModeloDePerifDesconocido,//105
	
	Error_HPstatusAlarma1,//106 
	Error_HPstatusAlarma2,
	Error_HPstatusAlarma3,
	Error_HPstatusAlarma4,
	
	Error_HPstatusDescfg1,//110
	Error_HPstatusDescfg2,
	Error_HPstatusDescfg3,
	Error_HPstatusDescfg4, //113
	
	Error_HPstatusDeshab485com1,//114
	Error_HPstatusDeshab485com2,
	Error_HPstatusDeshab485com3,
	Error_HPstatusDeshab485com4,
	
	Error_HPprotFlagTempClavada1, //118
	Error_HPprotFlagTempClavada2,
	Error_HPprotFlagTempClavada3,
	Error_HPprotFlagTempClavada4,
	
	Error_CircTempDesc1, //122
	Error_CircTempDesc2,
	Error_CircTempDesc3,
	Error_CircTempDesc4,
	
	Error_TestSondasFallo1, //126	/* V7790 - TEMP SAFE - frostbite */
	Error_TestSondasFallo2,	//#error alta prioridad
	Error_TestSondasFallo3,
	Error_TestSondasFallo4,
	
	Error_HPctrlMinTemp1, //130
	Error_HPctrlMinTemp2,
	Error_HPctrlMinTemp3,
	Error_HPctrlMinTemp4,
	
	Error_HPctrlMaxTemp1, //134
	Error_HPctrlMaxTemp2,
	Error_HPctrlMaxTemp3,
	Error_HPctrlMaxTemp4,
	
	Error_HPctrlDifTempFreeze1, //138
	Error_HPctrlDifTempFreeze2,
	Error_HPctrlDifTempFreeze3,
	Error_HPctrlDifTempFreeze4,
	
	Error_HPctrlDeltaTempMax1, //142
	Error_HPctrlDeltaTempMax2,
	Error_HPctrlDeltaTempMax3,
	Error_HPctrlDeltaTempMax4,
	
	Error_HPcannotRemovePlug1,	//146
	Error_HPcannotRemovePlug2,
	Error_HPcannotRemovePlug3,
	Error_HPcannotRemovePlug4,
	
	Error_HPsecondWindowLowTemp1,	//150
	Error_HPsecondWindowLowTemp2,
	Error_HPsecondWindowLowTemp3,
	Error_HPsecondWindowLowTemp4,
	
	Error_HPcalibOutRange1,		//154 //#error alta prioridad
	Error_HPcalibOutRange2,
	Error_HPcalibOutRange3,
	Error_HPcalibOutRange4,
	
	Error_HPsondaStep1,		//158 //#error alta prioridad
	Error_HPsondaStep2,
	Error_HPsondaStep3,
	Error_HPsondaStep4,
	
	Error_HPsondaRotaHP1,	//162 //#error alta prioridad
	Error_HPsondaRotaHP2,
	Error_HPsondaRotaHP3,
	Error_HPsondaRotaHP4,
	
//	Error_HPtemp_frostbiteHP1,	//166	/* V7790 - TEMP SAFE */
//	Error_HPtemp_frostbiteHP2,
//	Error_HPtemp_frostbiteHP3,
//	Error_HPtemp_frostbiteHP4,
	
    Error_FinalCode
    //PDTE PASAR ERRORES NUEVOS A TABLA 
    //PDTE ELIMINAR X4 EN LOS ERRORES
}GestionErrors_t;

typedef enum
{				//Lista con las distintas procedencias de los errores (asociado a los manipulos o a la máquina completa)
	 No_perif,
	 
	 Manip1,
	 Manip2,
	 Manip3,
	 Manip4,
	 Maq,
	 Max_perifs
}perif_to_manage;

typedef enum
{					//Lista de imagenes de errores
	Err_msg_standard,
	
	No_msg,
	Err_msg_release_HP,
	Err_msg_obstruction,
	Err_msg_seta,
	Err_msg_temperatura,
	Err_msg_resucciones,
	
	Err_msg_SPIcom,
	Err_msg_485,
	Err_msg_Caudal,
	Err_msg_Power,
	Err_msg_RFID,
	Err_msg_InsfNTC,
	Err_msg_ToutVacc,
	Err_msg_NoMainThread,
	Err_msg_Unknown,
	Err_msg_InternalTemp,
	Err_msg_InternalSensors,
	Err_msg_HPdesconfeigured,
	Err_msg_HPalarm,
	Err_msg_PCBdamaged,
	Err_msg_InitialTest,
	
	Err_msg_max,
}errors_messages;

typedef enum
{
	No_msg_standard,
	
	No_warning_msg,
	Warning_msg_2,
	Warning_msg_3,
	Warning_msg_4,
	Warning_msg_5,
	Warning_msg_max,
}warning_messages;

//typedef struct
//{
//	uint8 ErrorFired_code[20];
//	uint8 Count[20];
//}ERR_errorFired_structure;

typedef struct
{
	//Estructura para cada Periferico
	perif_to_manage Perif_id;				//Identificador del Periferico
	GestionErrors_t Perif_error;			//Error del periferico
	uint8_t Perif_err_management;			//Forma de gestionar el error - Criterio identificador de prioridad del error
	uint8 Error_Log [NUMBER_ERRORS_LOG];	//Error_Log [NUMBER_ERRORS_LOG];												//No sirve con los nuevos LOGS	5 * 10 = 50B
	uint8 log_index;																										//No sirve con los nuevos LOGS	5 * 1  = 5B
	uint32 error_code;						//Codigo de error que se muestra por pantalla
	uint8 Avisos_log [NUMBER_AVISOS_LOG];																					//No sirve con los nuevos LOGS	5 * 10 = 50B
	uint8 avisos_log_index;																									//No sirve con los nuevos LOGS	5 * 1  = 5B
	errors_messages user_msg_error;
	uint8 user_msg_warning;
	uint8 Perif_warning;
	uint16 Warning_code;
}ERR_Perif_structure;

typedef struct
{
	//Lista de manipulos/perifericos conectados en la máquina
	ERR_Perif_structure HP1;			//Manipulo 1
	ERR_Perif_structure HP2;			//Manipulo 2
	ERR_Perif_structure HP3;			//Manipulo 3
	ERR_Perif_structure HP4;			//Manipulo 4
	ERR_Perif_structure Machine;		//General de la máquina
	
	uint16 Warning_Flags;
	uint8 New_Warning_Flag;
//	ERR_errorFired_structure ErrorFired;
}ERR_Device_periferics;

//Variables
extern ERR_Device_periferics ERR_data;

//Funciones

/*
 * Función ERR_init
 * Descripción:
 *      Realiza la inicialización de todas las variables.
 * Parámetros:
 * 		- No solicita ningún dato
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void ERR_init (void);

/*
 * Función ERR_add
 * Descripción:
 *      Incrementa las repeticiones que el error ha aparecido, si se supera el número máximo de veces establecidos en un corto periodo de tiempo,
 *      se indica con una alarma el error que ha saltado
 *       Se encarga de la gestión de añadir errores, priorizando aquellos cuya gestión sea más prioritaria.
 * Parámetros:
 * 		- newError	uint8:
 * 			
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void ERR_add(uint16 newError);

///*
// * Función ERR_refresh
// * Descripción:
// *      Comprueba los flags del módulo de comunicación con la expansora, añadiendo los errores asociados a dichos flags.
// * Parámetros:
// * 		- No solicita ningún dato
// * Retorno:
// *      - No devuelve nada
// * Errores:
// * 
// */
//void ERR_refresh(void);

/*
 * Función ERR_update
 * Descripción:
 *      Se encarga de la gestión de los errores en una primera etapa, decidiendo en que modo poner los manipulos.
 * Parámetros:
 * 		- time_loop		uint32:
 * 			Parametro que emplea como periodo para no actuar cada llamada a la función
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void ERR_update (uint32_t time_loop);

/*
 * Función ERR_clear
 * Descripción:
 *      Limpia el indicador de alarma además de realizar la segunda estapa de la gestión de los mismos.
 * Parámetros:
 * 		- Periferico al que limpiar los parametros de la gestión de errores
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void ERR_clear(perif_to_manage HP);

/*
 * Función ERR_warning_clear
 * Descripción:
 *      Limpia el indicador de avisos.
 * Parámetros:
 * 		- Periferico al que limpiar los parametros de avisos de la gestión de errores
 * 		- Mascara con los flags de los warnings que se quieren limpiar
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void ERR_warning_clear(perif_to_manage HP, uint16 Flags_Erase_Mask);

/*
 * Función ERR_delete
 * Descripción:
 *      Descuenta del contador de las alarmas en caso de no haberse incrementado dicho contador
 * Parámetros:
 * 		- uint16 newError
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void ERR_delete (uint16 newError);

/*
 * Función ERR_interface_msg
 * Descripción:
 *      Responde a la interfaz con la información asociada a un manipulo. Indica si hay o no error asociado a dicho manipulo, su código de error y el mensaje que ha de mostrarse al usuario
 * Parámetros:
 * 		- uint8 HP : Manipulo por el que se pregunta
 * 		
 * 		-uint32 *err_code_HP : Puntero para rellenar con el codigo de error
 * 		
 * 		-uint8 *err_msg_HP : Puntero con el mensaje a entregar al usuario
 * 		
 * 		-uint32 *warning_code_HP : Puntero a rellenar con el código del aviso
 * 		
 * 		-uint8 *warning_msg_HP : Puntero con el mensaje del aviso para el usuario
 * Retorno:
 *      - uint8 : Devuelve un flag indicando si dicho manipulo tiene un error o no
 * Errores:
 * 
 */
uint8 ERR_interface_msg(perif_to_manage HP, uint32 *err_code_HP, errors_messages *err_msg_HP, uint32 *warning_code_HP, warning_messages *warning_msg_HP);

/*
 * Función ERR_standby_err
 * Descripción:
 *      Responde si el codigo de error que se le ha pasado por parametro está presente en la lista de errores especiales que han de mostrarse en el estado de standby.
 *      Responde "TRUE" si el error pasado coincide con alguno de la lista, o "FALSE" si no coincide con ninguno.
 * Parámetros:
 * 		-uint32 err_code_HP : Codigo de error que se quiere consultar
 * 		
 * Retorno:
 *      - uint8 : Devuelve un flag indicando si el codigo de error está dentro de la lista o no
 * Errores:
 * 
 */
uint8 ERR_standby_err(uint32 err_code_HP);

/*
 * Función ERR_reset_perif
 * Descripción:
 *      Se encarga de recorrer los errores asociados a un manipulo y resetear los contadores y referencias de tiempos de dichos errores.
 *      Esta función está pensada para emplearse al desconctar un manipulo.
 * Parámetros:
 * 		-perif_to_manage HP : Periferico del que se quiere realizar un reseteado completo de errores asociados
 * 		
 * Retorno:
 *      No devuelve nada
 * Errores:
 * 
 */
void ERR_reset_perif(perif_to_manage HP);

/*
 * Función ERR_get_WarningFlags
 * Descripción:
 *      Devuelve el array con todos los flags de avisos que han saltado
 * Parámetros:
 * 		No pide parametros de entrada
 * Retorno:
 *      Devuelve el array con los flags de avisos
 * Errores:
 * 
 */
uint16 ERR_get_WarningFlags (void);

/*
 * Función ERR_get_NewWarningFlag
 * Descripción:
 *      Devuelve el flag de si hay un nuevo aviso 
 * Parámetros:
 * 		No pide parametros de entrada
 * Retorno:
 *      Devuelve el el flag de nuevos avisos
 * Errores:
 * 
 */
uint8 ERR_get_NewWarningFlag(void);

/*
 * Función ERR_erase_NewWarningFlag
 * Descripción:
 *      Borra el flag de nuevos avisos por revisar
 * Parámetros:
 * 		No pide parametros de entrada
 * Retorno:
 *      No devuelve nada
 * Errores:
 * 
 */
void ERR_erase_NewWarningFlag(void);

void ERR_log_err_code(uint8 **Error_Log, uint8 *Log_index, uint8 Periferico);

//void ERR_logadd(uint32 error_code);

#endif /* GESTIONERRORES_H_ */
