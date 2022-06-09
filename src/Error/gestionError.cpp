/*
 * GestionErrores2.c
 *
 *  Created on: Nov 15, 2016
 *      Author: ingenieria1
 */

//FALTA REVISAR LA FUNCIÓN REFRESH() PARA LA DETECCIÓN DE CIERTOS ERRORAS QUE TIENEN UNA GESTIÓN ESPECIAL (VACUUM). TAMBIÉN FALTA AÑADIR DICHA GESTIÓN DE ERRORES ESPECIAL.

//Librerías
#include "gestionError.h"
#include "../AppLOG/AppLOG.h"

//Definición de estructuras
 typedef struct
 {
	 GestionErrors_t Error_code;
	 uint32 manage_type;
     uint32 message_type;
     perif_to_manage perif;
	 uint32	error_set_rep;
     uint32 time_out_set_error;
	 void (*ptr_function_add)(void *);
	 void (*ptr_function_set)(void *);
	 void (*ptr_function_clear)(void *);
	 uint8_t err_user_msg;
	 uint8_t wrng_user_msg;
	 
 }tErrors_configuration;

 typedef struct
 {
	 uint16 error_set_count;			//NO SE USA UINT16 * 169 errores = 338B
	 uint32	timer_error_count;
	 //uint8 aux_count;
 }tErrors_count;
 
enum
{				//Lista de tipos de gestión de errores
	Noerror, 
	ConVacSeguir,
	ConVacParar,
	SinVac,
};

enum
{	
	ok,
	Alarma,
	Aviso,
};

//Estructura de errores de los perifericos
ERR_Device_periferics ERR_data;
//tEXPdata EXPdata;

tHPcryoData *HPcryoData_HP1;
tHPcryoData *HPcryoData_HP2;
tHPcryoData *HPcryoData_HP3;
tHPcryoData *HPcryoData_HP4;

tPRFdata *PRFdata_HP1;
tPRFdata *PRFdata_HP2;
tPRFdata *PRFdata_HP3;
tPRFdata *PRFdata_HP4;

//Referencia de tiempo para el bucle del refresco de los errores
uint32_t time_update;

uint32_t initTimeErrorEnable;

tErrors_count Errors_count[Error_FinalCode];

uint32 time_change_policy[Max_perifs];

//Declaración de funciones locales

void ErrorSet_StartCount(perif_to_manage Perif);
void ErrorClear_ProcessCount(perif_to_manage Perif);

/*
 * Función cbk_ErrorReset485Coms
 * Descripción:
 *      Limpia los buffers de comunicaciones por 485
 * Parámetros:
 * 		- Puntero a un parametro de tipo variable
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
//void cbk_ErrorEXPReset485Coms (perif_to_manage Manip);

/*
 * Función cbk_ErrorResetPerif
 * Descripción:
 *      Resetea el periferico con error de SPI
 * Parámetros:
 * 		- Puntero a un parametro de tipo variable
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
//void cbk_ErrorResetPerif(perif_to_manage Manip);

/*
 * Función cbk_ErrorAddVoid
 * Descripción:
 *      Función (CallBack) que se llama al realizar la acción Add de un error (detectarlo por primera vez
 * Parámetros:
 * 		- Puntero a un parametro de tipo variable
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void cbk_ErrorAddVoid(void * estructura);

/*
 * Función cbk_ErrorSetVoid
 * Descripción:
 *      Función (CallBack) que se llama al activar un error nuevo (Lanzar el error)
 * Parámetros:
 * 		- Puntero a un parametro de tipo variable
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void cbk_ErrorSetVoid(void * estructura);

/*
 * Función cbk_ErrorClearVoid
 * Descripción:
 *      Función (CallBack) que se llama al desactivar un error nuevo
 * Parámetros:
 * 		- Puntero a un parametro de tipo variable
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void cbk_ErrorClearVoid(void * estructura);

/*
 * Función cbk_ErrorSetVoid_RESUCCION
 * Descripción:
 *      Función (CallBack) que se llama al activar un error de las resucciones
 * Parámetros:
 * 		- Puntero a un parametro de tipo variable
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void cbk_ErrorSetVoid_RESUCCION(void * estructura);

/*
 * Función cbk_ErrorClearVoid_RESUCCION
 * Descripción:
 *      Función (CallBack) que se llama al desactivar un error de las resucciones
 * Parámetros:
 * 		- Puntero a un parametro de tipo variable
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void cbk_ErrorClearVoid_RESUCCION(void * estructura);

/*
 * Función cbk_ErrorSetVoid_FAPELTIER
 * Descripción:
 *      Función (CallBack) que se llama al activar un error de la fuente de alimentación de la peltier
 * Parámetros:
 * 		- Puntero a un parametro de tipo variable
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void cbk_ErrorSetVoid_FAPELTIER(void * estructura);

/*
 * Función cbk_ErrorClearVoid_FAPELTIER
 * Descripción:
 *      Función (CallBack) que se llama al desactivar un error de la fuente de alimentación de la peltier
 * Parámetros:
 * 		- Puntero a un parametro de tipo variable
 * Retorno:
 *      - No devuelve nada
 * Errores:
 * 
 */
void cbk_ErrorClearVoid_FAPELTIER(void * estructura);

/*
 * Función ERR_HP_disconected_mng
 * Descripción:
 *      Realiza un cribado de las casualisticas determinando cuando realizar un clear de los errores cuando un HP se encuentra desconectado
 * Parámetros:
 * 		- No se le pasa ningún parámetro
 * Retorno:
 *      - No se devuelve ningún parámetro de retorno
 * Errores:
 * 
 */
void ERR_HP_disconected_mng (void);

/*
 * Función ERR_WarningCode_to_Flags
 * Descripción:
 *      Actualiza el array de flags de avisos en función de los avisos que vayan saltando
 * Parámetros:
 * 		- WarningCode: Código del warning que ha saltado
 * Retorno:
 *      - No se devuelve ningún parámetro de retorno
 * Errores:
 * 
 */
void ERR_WarningCode_to_Flags (uint32 WarningCode);

//Constantes
const GestionErrors_t Errors_list_per_Perif[Max_perifs][ERR_LISR_PER_PERIFERIC] = 
{
        {Error_ok,Error_ok,Error_ok,Error_ok,Error_ok,
         Error_ok,Error_ok,Error_ok,Error_ok,Error_ok,
         Error_ok,Error_ok,Error_ok,Error_ok,Error_ok,
         Error_ok,Error_ok,Error_ok,Error_ok,Error_ok,
         Error_ok,Error_ok,Error_ok,Error_ok,Error_ok,
         Error_ok,Error_ok,Error_ok,Error_ok,Error_ok,Error_ok},
		
		//Lista de errores asociados al HP1
		{Error_ComSPIMAN1, Error_Com485_H201, Error_Com485_VAC1, Error_NResuccionesMAN1, Err_CaudalimetroMan1, 
		Err_HidraulicaMan1, Err_ControlFApeltier1, Err_ControlFApeltier1TRT, Err_ComRFID1, Err_NPltInsf1, 
		Err_TimeOutMan1, Err_TimeOutVacm1, Err_TempEntradaAlta1, Err_TimeOutVacEstable1, Err_ToutTempIniciTrart1, Err_ToutTempFinalTrat1,
		Err_SeguridadFrioMan1, Err_PIDoff1, Err_HPsinTramasMain1, Error_HPstatusAlarma1, Error_HPstatusDescfg1, 
		Error_HPstatusDeshab485com1, Error_HPprotFlagTempClavada1, Error_CircTempDesc1, Error_TestSondasFallo1, Error_HPctrlMinTemp1, 
		Error_HPctrlMaxTemp1, Error_HPctrlDifTempFreeze1, Error_HPctrlDeltaTempMax1, Error_HPcannotRemovePlug1, Error_HPsecondWindowLowTemp1,
		Error_HPcalibOutRange1, Error_HPsondaStep1, Error_HPsondaRotaHP1, /*Error_HPtemp_frostbiteHP1*/},
		
		//Lista de errores asociados al HP2
		{Error_ComSPIMAN2, Error_Com485_H202, Error_Com485_VAC2, Error_NResuccionesMAN2, Err_CaudalimetroMan2, 
		Err_HidraulicaMan2, Err_ControlFApeltier2, Err_ControlFApeltier2TRT, Err_ComRFID2, Err_NPltInsf2, 
		Err_TimeOutMan2, Err_TimeOutVacm2, Err_TempEntradaAlta2, Err_TimeOutVacEstable2, Err_ToutTempIniciTrart2, Err_ToutTempFinalTrat2,
		Err_SeguridadFrioMan2, Err_PIDoff2, Err_HPsinTramasMain2, Error_HPstatusAlarma2, Error_HPstatusDescfg2, 
		Error_HPstatusDeshab485com2, Error_HPprotFlagTempClavada2, Error_CircTempDesc2, Error_TestSondasFallo2, Error_HPctrlMinTemp2, 
		Error_HPctrlMaxTemp2, Error_HPctrlDifTempFreeze2, Error_HPctrlDeltaTempMax2, Error_HPcannotRemovePlug2, Error_HPsecondWindowLowTemp2,
		Error_HPcalibOutRange2, Error_HPsondaStep2, Error_HPsondaRotaHP2, /*Error_HPtemp_frostbiteHP2*/},
		
		//Lista de errores asociados al HP3
		{Error_ComSPIMAN3, Error_Com485_H203, Error_Com485_VAC3, Error_NResuccionesMAN3, Err_CaudalimetroMan3, 
		Err_HidraulicaMan3, Err_ControlFApeltier3, Err_ControlFApeltier3TRT, Err_ComRFID3, Err_NPltInsf3, 
		Err_TimeOutMan3, Err_TimeOutVacm3, Err_TempEntradaAlta3, Err_TimeOutVacEstable3, Err_ToutTempIniciTrart3, Err_ToutTempFinalTrat3,
		Err_SeguridadFrioMan3, Err_PIDoff3, Err_HPsinTramasMain3, Error_HPstatusAlarma3, Error_HPstatusDescfg3, 
		Error_HPstatusDeshab485com3, Error_HPprotFlagTempClavada3, Error_CircTempDesc3, Error_TestSondasFallo3, Error_HPctrlMinTemp3, 
		Error_HPctrlMaxTemp3, Error_HPctrlDifTempFreeze3, Error_HPctrlDeltaTempMax3, Error_HPcannotRemovePlug3, Error_HPsecondWindowLowTemp3,
		Error_HPcalibOutRange3, Error_HPsondaStep3, Error_HPsondaRotaHP3, /*Error_HPtemp_frostbiteHP3*/},
		
		//Lista de errores asociados al HP4
		{Error_ComSPIMAN4, Error_Com485_H204, Error_Com485_VAC4, Error_NResuccionesMAN4, Err_CaudalimetroMan4, 
		Err_HidraulicaMan4, Err_ControlFApeltier4, Err_ControlFApeltier4TRT, Err_ComRFID4, Err_NPltInsf4, 
		Err_TimeOutMan4, Err_TimeOutVacm4, Err_TempEntradaAlta4, Err_TimeOutVacEstable4, Err_ToutTempIniciTrart4, Err_ToutTempFinalTrat4,
		Err_SeguridadFrioMan4, Err_PIDoff4, Err_HPsinTramasMain4, Error_HPstatusAlarma4, Error_HPstatusDescfg4, 
		Error_HPstatusDeshab485com4, Error_HPprotFlagTempClavada4, Error_CircTempDesc4, Error_TestSondasFallo4, Error_HPctrlMinTemp4, 
		Error_HPctrlMaxTemp4, Error_HPctrlDifTempFreeze4, Error_HPctrlDeltaTempMax4, Error_HPcannotRemovePlug4, Error_HPsecondWindowLowTemp4,
		Error_HPcalibOutRange4, Error_HPsondaStep4, Error_HPsondaRotaHP4, /*Error_HPtemp_frostbiteHP4*/},
		
		//Lista de errores asociados a la Maquina
		{Error_Com485_Perd, Error_Com485_Rebos, Error_Com485_Fuente1, Error_Com485_Fuente2, Error_NivelH2OBajo, Error_NivelH2OMedio, 
		Err_SnsTempAmbienteAltaAviso, Err_SnsTempAmbienteAltaAlarma, Err_AcFail, Err_TpuntFail, Err_ButtStandby, Err_ComExp, 
		Err_ComRFID, Err_RTC, Error_Com485_DetectorNivel, Error_BusAlarma_Seta, Error_BusAlarma_no_identificado, Error_FiltroAire, 
		Error_TempPumpOutAlta, Error_TempPumpOutBaja, Error_TempRetornoAlta, Error_TempRetornoBaja, Err_SnsTempAmbienteBajaAlarma, Error_CaudalRetornoMaximo, 
		Error_MaxConsBombaH2O, Error_MaxConsVentRad, Error_MaxCons24Vtotal, Error_SinMemoriaParaPerif, Error_ModeloDePerifDesconocido, }
};
const uint32 Standby_Err_List [ERR_LIST_ERR_STANDBY] = 			//Lista de errores para mostrar en el estado de Standby
{
		(Err_ControlFApeltier1 + ERROR_CODE_PERIF_1_OFFSET),
		(Err_ControlFApeltier2 + ERROR_CODE_PERIF_2_OFFSET),
		(Err_ControlFApeltier3 + ERROR_CODE_PERIF_3_OFFSET),
		(Err_ControlFApeltier4 + ERROR_CODE_PERIF_4_OFFSET),
		(Err_ComExp + ERROR_CODE_MACHINE_OFFSET),
};

//PDTE esto tendria que ser un "const" para no gastar memoria RAM
const tErrors_configuration ConfiguracionGestionErrores[Error_FinalCode] =
 {
	 {
         .Error_code = Error_ok, .manage_type = Noerror, .message_type = ok, .perif = Maq,
         .error_set_rep = 0, .time_out_set_error = 0,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 // Error SPI
	 {
		 .Error_code = Error_ComSPIMAN1, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVETEEN_SEC_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid/*cbk_ErrorResetPerif*/, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_SPIcom, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_ComSPIMAN2, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVETEEN_SEC_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid/*cbk_ErrorResetPerif*/, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_SPIcom, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_ComSPIMAN3, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVETEEN_SEC_MILISEC, 
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid/*cbk_ErrorResetPerif*/, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_SPIcom, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_ComSPIMAN4, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVETEEN_SEC_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid/*cbk_ErrorResetPerif*/, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_SPIcom, .wrng_user_msg = No_warning_msg
	 },
	 // Error 485 
	 {
		 .Error_code = Error_Com485_H201, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_Com485_H202, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_Com485_H203, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_Com485_H204, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 
	 {
		 .Error_code = Error_Com485_VAC1, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_Com485_VAC2, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_Com485_VAC3, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_Com485_VAC4, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 
	 {
		 .Error_code = Error_Com485_Perd, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 
	 {
		 .Error_code = Error_Com485_Rebos, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 
	 {
		 .Error_code = Error_Com485_Fuente1, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_Com485_Fuente2, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 // Error Resucciones
	 {
		 .Error_code = Error_NResuccionesMAN1, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip1, 		//Gestión especial del error
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid_RESUCCION, .ptr_function_clear = cbk_ErrorClearVoid_RESUCCION,
		 .err_user_msg = Err_msg_resucciones, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_NResuccionesMAN2, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip2, 		//Gestión especial del error
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid_RESUCCION, .ptr_function_clear = cbk_ErrorClearVoid_RESUCCION,
		 .err_user_msg = Err_msg_resucciones, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_NResuccionesMAN3, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip3, 		//Gestión especial del error
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid_RESUCCION, .ptr_function_clear = cbk_ErrorClearVoid_RESUCCION,
		 .err_user_msg = Err_msg_resucciones, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_NResuccionesMAN4, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip4, 		//Gestión especial del error
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid_RESUCCION, .ptr_function_clear = cbk_ErrorClearVoid_RESUCCION,
		 .err_user_msg = Err_msg_resucciones, .wrng_user_msg = No_warning_msg
	 },
	 // Error Nivel H20 
	 {
		 .Error_code = Error_NivelH2OBajo, .manage_type = Noerror, .message_type = Aviso, .perif = Maq,			//AVISO
		 .error_set_rep = 1, .time_out_set_error = TEN_SEC_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_NivelH2OMedio, .manage_type = Noerror, .message_type = Aviso, .perif = Maq,		//AVISO
		 .error_set_rep = 1, .time_out_set_error = TEN_SEC_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 // Error Sensor de temperatura
	 {
		 .Error_code = Err_SnsTempAmbienteAltaAviso, .manage_type = Noerror, .message_type = Aviso, .perif = Maq,		//AVISO
		 .error_set_rep = 50, .time_out_set_error = FIVETEEN_SEC_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_temperatura, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_SnsTempAmbienteAltaAlarma, .manage_type = ConVacParar, .message_type = Alarma, .perif = Maq,
		 .error_set_rep = 600, .time_out_set_error = THREE_MIN_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_temperatura, .wrng_user_msg = No_warning_msg
	 },
	 // Error Caudal 
	 {
		 .Error_code = Err_CaudalimetroMan1, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip1,
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = TEN_SEC_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_Caudal, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_CaudalimetroMan2, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip2,
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = TEN_SEC_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_Caudal, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_CaudalimetroMan3, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip3,
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = TEN_SEC_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_Caudal, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_CaudalimetroMan4, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip4,
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = TEN_SEC_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_Caudal, .wrng_user_msg = No_warning_msg
	 },
	 // Error Hidraulica 
	 {
		 .Error_code = Err_HidraulicaMan1, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip1,
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVE_SEC_MILISEC/*ONE_MILISEC*/,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_Caudal, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_HidraulicaMan2, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip2,
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVE_SEC_MILISEC/*ONE_MILISEC*/,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_Caudal, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_HidraulicaMan3, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip3,
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVE_SEC_MILISEC/*ONE_MILISEC*/,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_Caudal, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_HidraulicaMan4, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip4,
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVE_SEC_MILISEC/*ONE_MILISEC*/,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_Caudal, .wrng_user_msg = No_warning_msg
	 },
	 // Varios
	 {
		 .Error_code = Err_AcFail, .manage_type = ConVacParar, .message_type = Alarma, .perif = Maq,
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVE_SEC_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_Power, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_TpuntFail, .manage_type = ConVacParar, .message_type = Alarma, .perif = Maq,
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVE_SEC_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_Power, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ButtStandby, .manage_type = Noerror, .message_type = Aviso, .perif = Maq,		//AVISO
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 // Error Control Peltier
	 {
		 .Error_code = Err_ControlFApeltier1, .manage_type = SinVac, .message_type = Alarma, .perif = Manip1, 		//Gestión especial del error
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid_FAPELTIER, .ptr_function_clear = cbk_ErrorClearVoid_FAPELTIER,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ControlFApeltier2, .manage_type = SinVac, .message_type = Alarma, .perif = Manip2, 		//Gestión especial del error
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid_FAPELTIER, .ptr_function_clear = cbk_ErrorClearVoid_FAPELTIER,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ControlFApeltier3, .manage_type = SinVac, .message_type = Alarma, .perif = Manip3, 		//Gestión especial del error
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid_FAPELTIER, .ptr_function_clear = cbk_ErrorClearVoid_FAPELTIER,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ControlFApeltier4, .manage_type = SinVac, .message_type = Alarma, .perif = Manip4, 		//Gestión especial del error
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid_FAPELTIER, .ptr_function_clear = cbk_ErrorClearVoid_FAPELTIER,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 
	 {
		 .Error_code = Err_ControlFApeltier1TRT, .manage_type = SinVac, .message_type = Alarma, .perif = Manip1, 		//Gestión especial del error
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid_FAPELTIER, .ptr_function_clear = cbk_ErrorClearVoid_FAPELTIER,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ControlFApeltier2TRT, .manage_type = SinVac, .message_type = Alarma, .perif = Manip2, 		//Gestión especial del error
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		 .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid_FAPELTIER, .ptr_function_clear = cbk_ErrorClearVoid_FAPELTIER,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ControlFApeltier3TRT, .manage_type = SinVac, .message_type = Alarma, .perif = Manip3, 		//Gestión especial del error
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid_FAPELTIER, .ptr_function_clear = cbk_ErrorClearVoid_FAPELTIER,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ControlFApeltier4TRT, .manage_type = SinVac, .message_type = Alarma, .perif = Manip4, 		//Gestión especial del error
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid_FAPELTIER, .ptr_function_clear = cbk_ErrorClearVoid_FAPELTIER,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 // Error Comunicación Expansora
	 {
		 .Error_code = Err_ComExp, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVE_SEC_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 // Error Cominicación RFID  
	 {
		 .Error_code = Err_ComRFID, .manage_type = Noerror, .message_type = Aviso, .perif = Maq, 			//AVISO
		 .error_set_rep = 1, .time_out_set_error = FIVE_SEC_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_RFID, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ComRFID1, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_RFID, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ComRFID2, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_RFID, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ComRFID3, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_RFID, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ComRFID4, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_RFID, .wrng_user_msg = No_warning_msg
	 },
	 // Error RTC  
	 {
		 .Error_code = Err_RTC, .manage_type = Noerror, .message_type = Aviso, .perif = Maq, 		//Aviso
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 //
	 {
		 .Error_code = Err_NPltInsf1, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InsfNTC, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_NPltInsf2, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InsfNTC, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_NPltInsf3, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InsfNTC, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_NPltInsf4, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InsfNTC, .wrng_user_msg = No_warning_msg
	 },
	 // Error Time Out
	 {
		 .Error_code = Err_TimeOutMan1, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_TimeOutMan2, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_TimeOutMan3, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_TimeOutMan4, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 
	 {
		 .Error_code = Err_TimeOutVacm1, .manage_type = SinVac, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_ToutVacc, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_TimeOutVacm2, .manage_type = SinVac, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_ToutVacc, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_TimeOutVacm3, .manage_type = SinVac, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_ToutVacc, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_TimeOutVacm4, .manage_type = SinVac, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_ToutVacc, .wrng_user_msg = No_warning_msg
	 },
	 // Error Temperatura Entrada
	 {
		 .Error_code = Err_TempEntradaAlta1, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_TempEntradaAlta2, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_TempEntradaAlta3, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_TempEntradaAlta4, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 // Error TOUT 
	 {
		 .Error_code = Err_TimeOutVacEstable1, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_ToutVacc, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_TimeOutVacEstable2, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_ToutVacc, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_TimeOutVacEstable3, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_ToutVacc, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_TimeOutVacEstable4, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_ToutVacc, .wrng_user_msg = No_warning_msg
	 },
	 
	 {
		 .Error_code = Err_ToutTempIniciTrart1, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ToutTempIniciTrart2, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ToutTempIniciTrart3, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ToutTempIniciTrart4, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 
	 {
		 .Error_code = Err_ToutTempFinalTrat1, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ToutTempFinalTrat2, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ToutTempFinalTrat3, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_ToutTempFinalTrat4, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 // Error Seguridad Frio  
	 {
		 .Error_code = Err_SeguridadFrioMan1, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_SeguridadFrioMan2, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_SeguridadFrioMan3, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_SeguridadFrioMan4, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 // Error PID
	 {
		 .Error_code = Err_PIDoff1, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_PIDoff2, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_PIDoff3, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_PIDoff4, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 // Error comunicación manopulo-main
	 {
		 .Error_code = Err_HPsinTramasMain1, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_NoMainThread, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_HPsinTramasMain2, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_NoMainThread, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_HPsinTramasMain3, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_NoMainThread, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Err_HPsinTramasMain4, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_NoMainThread, .wrng_user_msg = No_warning_msg
	 },
	 // GENERADOS POR LA MAIN
	 {
		 .Error_code = Error_Com485_DetectorNivel, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_BusAlarma_Seta, .manage_type = SinVac, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_seta, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_BusAlarma_no_identificado, .manage_type = SinVac, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_Unknown, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_FiltroAire, .manage_type = Noerror, .message_type = Aviso, .perif = Maq, 		//AVISO
		 .error_set_rep = 1, .time_out_set_error = FIVE_SEC_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_TempPumpOutAlta, .manage_type = ConVacParar, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = HALF_MIN_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InternalTemp, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_TempPumpOutBaja, .manage_type = ConVacParar, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = HALF_MIN_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InternalTemp, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_TempRetornoAlta, .manage_type = ConVacParar, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = HALF_MIN_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InternalTemp, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_TempRetornoBaja, .manage_type = ConVacParar, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = HALF_MIN_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InternalTemp, .wrng_user_msg = No_warning_msg
	 },	 
	 {
		 .Error_code = Err_SnsTempAmbienteBajaAlarma, .manage_type = ConVacParar, .message_type = Alarma, .perif = Maq,
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = THREE_MIN_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InternalTemp, .wrng_user_msg = No_warning_msg
	 },	
	 {
		 .Error_code = Error_CaudalRetornoMaximo, .manage_type = ConVacParar, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = TEN_SEC_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InternalSensors, .wrng_user_msg = No_warning_msg
	 },	
	 {
		 .Error_code = Error_MaxConsBombaH2O, .manage_type = ConVacParar, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVE_SEC_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InternalSensors, .wrng_user_msg = No_warning_msg
	 },	 
	 {
		 .Error_code = Error_MaxConsVentRad, .manage_type = ConVacParar, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVE_SEC_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InternalSensors, .wrng_user_msg = No_warning_msg
	 },	
	 {
		 .Error_code = Error_MaxCons24Vtotal, .manage_type = ConVacParar, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVE_SEC_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InternalSensors, .wrng_user_msg = No_warning_msg
	 },	
	 /*{
		 .Error_code = Error_SinMemoriaParaPerif, .manage_type = ConVacParar, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },	*/
	 { //#JM_GPRS V7790 cambiado para saltar en caso de fallo de cobertura 
		 .Error_code = Error_SinMemoriaParaPerif, .manage_type = ConVacParar, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_standard, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_ModeloDePerifDesconocido, .manage_type = ConVacParar, .message_type = Alarma, .perif = Maq, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_HPdesconfeigured, .wrng_user_msg = No_warning_msg
	 },		 
	 {
		 .Error_code = Error_HPstatusAlarma1, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = TEN_SEC_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_HPalarm, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPstatusAlarma2, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = TEN_SEC_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_HPalarm, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPstatusAlarma3, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = TEN_SEC_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_HPalarm, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPstatusAlarma4, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = TEN_SEC_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_HPalarm, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPstatusDescfg1, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_HPdesconfeigured, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPstatusDescfg2, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_HPdesconfeigured, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPstatusDescfg3, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_HPdesconfeigured, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPstatusDescfg4, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_HPdesconfeigured, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPstatusDeshab485com1, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPstatusDeshab485com2, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPstatusDeshab485com3, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPstatusDeshab485com4, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_485, .wrng_user_msg = No_warning_msg
	 },	
	 {
		 .Error_code = Error_HPprotFlagTempClavada1, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPprotFlagTempClavada2, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPprotFlagTempClavada3, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPprotFlagTempClavada4, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },	
	 {
		 .Error_code = Error_CircTempDesc1, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_PCBdamaged, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_CircTempDesc2, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_PCBdamaged, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_CircTempDesc3, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_PCBdamaged, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_CircTempDesc4, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_PCBdamaged, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_TestSondasFallo1, .manage_type = SinVac, .message_type = Alarma, .perif = Manip1, 		/* - V7790 cambio a sin_vac por frostbite - */
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InitialTest, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_TestSondasFallo2, .manage_type = SinVac, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InitialTest, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_TestSondasFallo3, .manage_type = SinVac, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InitialTest, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_TestSondasFallo4, .manage_type = SinVac, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_InitialTest, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPctrlMinTemp1, .manage_type = SinVac, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPctrlMinTemp2, .manage_type = SinVac, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPctrlMinTemp3, .manage_type = SinVac, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPctrlMinTemp4, .manage_type = SinVac, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPctrlMaxTemp1, .manage_type = SinVac, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPctrlMaxTemp2, .manage_type = SinVac, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPctrlMaxTemp3, .manage_type = SinVac, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPctrlMaxTemp4, .manage_type = SinVac, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = 1, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPctrlDifTempFreeze1, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPctrlDifTempFreeze2, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPctrlDifTempFreeze3, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPctrlDifTempFreeze4, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },	
	 {
		 .Error_code = Error_HPctrlDeltaTempMax1, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPctrlDeltaTempMax2, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPctrlDeltaTempMax3, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPctrlDeltaTempMax4, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPcannotRemovePlug1, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_obstruction, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPcannotRemovePlug2, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_obstruction, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPcannotRemovePlug3, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_obstruction, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPcannotRemovePlug4, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_obstruction, .wrng_user_msg = No_warning_msg															
	 },
	 {
		 .Error_code = Error_HPsecondWindowLowTemp1, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVE_SEC_MILISEC,		/* V7780 */
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPsecondWindowLowTemp2, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVE_SEC_MILISEC,		/* V7780 */
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPsecondWindowLowTemp3, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVE_SEC_MILISEC,		/* V7780 */
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg
	 },
	 {
		 .Error_code = Error_HPsecondWindowLowTemp4, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = FIVE_SEC_MILISEC,		/* V7780 */
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 },
	 {
		 .Error_code = Error_HPcalibOutRange1, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 },
	 {
		 .Error_code = Error_HPcalibOutRange2, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 },
	 {
		 .Error_code = Error_HPcalibOutRange3, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 },
	 {
		 .Error_code = Error_HPcalibOutRange4, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 },
	 {
		 .Error_code = Error_HPsondaStep1, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 },
	 {
		 .Error_code = Error_HPsondaStep2, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 },
	 {
		 .Error_code = Error_HPsondaStep3, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 },
	 {
		 .Error_code = Error_HPsondaStep4, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 },
	{
		 .Error_code = Error_HPsondaRotaHP1, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 },
	{
		 .Error_code = Error_HPsondaRotaHP2, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 },
	{
		 .Error_code = Error_HPsondaRotaHP3, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 },
	{
		 .Error_code = Error_HPsondaRotaHP4, .manage_type = ConVacSeguir, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 }/*,
	 // V7790 - TEMP SAFE 
	 {
		 .Error_code = Error_HPtemp_frostbiteHP1, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip1, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 },
	{
		 .Error_code = Error_HPtemp_frostbiteHP2, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip2, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 },
	{
		 .Error_code = Error_HPtemp_frostbiteHP3, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip3, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 },
	{
		 .Error_code = Error_HPtemp_frostbiteHP4, .manage_type = ConVacParar, .message_type = Alarma, .perif = Manip4, 
		 .error_set_rep = REPS_MAX_TO_FILTR_ERR, .time_out_set_error = ONE_MILISEC,
		  .ptr_function_add = cbk_ErrorAddVoid, .ptr_function_set = cbk_ErrorSetVoid, .ptr_function_clear = cbk_ErrorClearVoid,
		 .err_user_msg = Err_msg_release_HP, .wrng_user_msg = No_warning_msg															
	 }
	 // V7790 - TEMP SAFE */
 };


//Funciones
void ERR_init()
{
	uint8 i = 0;	//Variable auxiliar para recorrer bucle "for" 
	
	time_update = 0;
	
	//Inicialización Manipulo 1
	ERR_data.HP1.Perif_id = Manip1;
    ERR_data.HP1.Perif_error = Error_ok;
	ERR_data.HP1.Perif_err_management = 0;
	ERR_data.HP1.log_index = 0;
	ERR_data.HP1.error_code = Noerror;
	ERR_data.HP1.avisos_log_index = 0;
	ERR_data.HP1.user_msg_error = Err_msg_standard;
	ERR_data.HP1.Perif_warning = Noerror;
	ERR_data.HP1.Warning_code = Noerror;
	ERR_data.HP1.user_msg_warning = No_warning_msg;
	
	//Inicialización Manipulo 2
	ERR_data.HP2.Perif_id = Manip2;
    ERR_data.HP2.Perif_error = Error_ok;
	ERR_data.HP2.Perif_err_management = 0;
	ERR_data.HP2.log_index = 0;
	ERR_data.HP2.error_code = Noerror;
	ERR_data.HP2.avisos_log_index = 0;
	ERR_data.HP2.user_msg_error = Err_msg_standard;
	ERR_data.HP2.Perif_warning = Noerror;
	ERR_data.HP2.Warning_code = Noerror;
	ERR_data.HP2.user_msg_warning = No_warning_msg;
	
	//Inicialización Manipulo 3
	ERR_data.HP3.Perif_id = Manip3;
    ERR_data.HP3.Perif_error = Error_ok;
	ERR_data.HP3.Perif_err_management = 0;
	ERR_data.HP3.log_index = 0;
	ERR_data.HP3.error_code = Noerror;
	ERR_data.HP3.avisos_log_index = 0;
	ERR_data.HP3.user_msg_error = Err_msg_standard;
	ERR_data.HP3.Perif_warning = Noerror;
	ERR_data.HP3.Warning_code = Noerror;
	ERR_data.HP3.user_msg_warning = No_warning_msg;
	
	//Inicialización Manipulo 4
	ERR_data.HP4.Perif_id = Manip4;
    ERR_data.HP4.Perif_error = Error_ok;
	ERR_data.HP4.Perif_err_management = 0;
	ERR_data.HP4.log_index = 0;
	ERR_data.HP4.error_code = Noerror;
	ERR_data.HP4.avisos_log_index = 0;
	ERR_data.HP4.user_msg_error = Err_msg_standard;
	ERR_data.HP4.Perif_warning = Noerror;
	ERR_data.HP4.Warning_code = Noerror;
	ERR_data.HP4.user_msg_warning = No_warning_msg;
	
	//Inicialización Maquina
	ERR_data.Machine.Perif_id = Maq;
    ERR_data.Machine.Perif_error = Error_ok;
	ERR_data.Machine.Perif_err_management = 0;
	ERR_data.Machine.log_index = 0;
	ERR_data.Machine.error_code = Noerror;
	ERR_data.Machine.avisos_log_index = 0;
	ERR_data.Machine.user_msg_error = Err_msg_standard;
	ERR_data.Machine.Perif_warning = Noerror;
	ERR_data.Machine.Warning_code = Noerror;
	ERR_data.Machine.user_msg_warning = No_warning_msg;
	
	//ERR_data.Warning_Flags = 0x0000;
	
	for (i=0; i<Error_FinalCode; i++)
	{
		Errors_count[i].timer_error_count = 0;
		Errors_count[i].error_set_count = 0;
		//Errors_count[i].aux_count = 0;
	}
	
	initTimeErrorEnable = TICKS_GetTicks();
}


void ERR_update(uint32_t time_loop)
{
    uint8 i;	//Variable auxiliar
	
	if (TICKS_DiffTicks(time_update) > time_loop)		//Condicionante para realizar esta función cada "time_loop" tiempo
	{
		ERR_HP_disconected_mng();
		
		time_update = TICKS_GetTicks();		//Se actualiza la referencia de tiempo
		
		for (i = Error_ok; i < Error_FinalCode; i++)		//Bucle encargado de recorrer toda la lista de errores
		{
			if ((TICKS_DiffTicks(Errors_count[i].timer_error_count) >= ConfiguracionGestionErrores[i].time_out_set_error) && Errors_count[i].timer_error_count != 0)		//Se comprueba si algún error activo ha superado su consigna de tiempo para activarlo
			{
				switch ( ConfiguracionGestionErrores[i].perif)					//En función del manipulo del que proceda el error
				{
					case Manip1:
						if (ConfiguracionGestionErrores[i].message_type == Alarma)						//Si el tipo de error es una Alarma
						{
							ERR_data.HP1.Error_Log[ERR_data.HP1.log_index] = i;							//Añadimos el error al log
							ERR_data.HP1.log_index++;													//Incrementamos el puntero del log
							if(ERR_data.HP1.log_index >= NUMBER_ERRORS_LOG)	ERR_data.HP1.log_index=0;	//Si llegamos al final del log, volvemos a la posición inicial (buffer circular)
						}
						else if (ConfiguracionGestionErrores[i].message_type == Aviso)								//Si el tipo de error es un Aviso
						{
							ERR_data.HP1.Avisos_log[ERR_data.HP1.avisos_log_index] = i;								//Añadimos el aviso al log
							ERR_data.HP1.avisos_log_index++;														//Incrementamos el puntero del log de avisos
							if(ERR_data.HP1.avisos_log_index >= NUMBER_AVISOS_LOG)	ERR_data.HP1.avisos_log_index=0;//Si llegamos al final del log de avisos, volvemos a la posición inicial (buffer circular)
							ERR_data.HP1.Perif_warning = i;															//Código de Warning
							ERR_data.HP1.Warning_code = i + ERROR_CODE_PERIF_1_OFFSET;								//Código de warning (con indicador de periferico)
							ERR_data.HP1.user_msg_warning = ConfiguracionGestionErrores[i].wrng_user_msg;			//Mensaje que ha de mostrarse para el usuario
						}
						
						if (ConfiguracionGestionErrores[i].manage_type > ERR_data.HP1.Perif_err_management)		//Si el error que me añaden tiene una prioridad mayor (asociado a la gestión del error)
						{
							ERR_data.HP1.Perif_err_management = ConfiguracionGestionErrores[i].manage_type;		//Actualizo la gestión del error
                            ERR_data.HP1.Perif_error = (GestionErrors_t)i;														//Actualizo el indice del error que se está gestionando
							
							ERR_data.HP1.error_code = ERR_data.HP1.Perif_error + ERROR_CODE_PERIF_1_OFFSET;		//Codigo de error para mostrar por pantalla
                            ERR_data.HP1.user_msg_error = (errors_messages)ConfiguracionGestionErrores[i].err_user_msg;			//Mensaje que ha de mostrarse para el usuario
							
							if(ConfiguracionGestionErrores[i].manage_type == ConVacSeguir)	{	ErrorSet_StartCount(Manip1);	}
							
							ConfiguracionGestionErrores[i].ptr_function_set((void*)ConfiguracionGestionErrores[i].perif);	//Callback de activación de error Main
							
							ERR_delete(i);				//Reseteo la consigna de tiempo
							
							/* V7790 - LOG error */
                            if (HPcryoGetFromSlot(PRF_HW_SLOT1, &HPcryoData_HP1, &PRFdata_HP1))
							{	
								AppLOG_saveERROR(ERR_data.HP1.error_code, HPcryoData_HP1, PRFdata_HP1);	
								AppLOG_saveTRT(HPcryoData_HP1, PRFdata_HP1);
							}
						}
						break;
					case Manip2:
						if (ConfiguracionGestionErrores[i].message_type == Alarma)
						{
							ERR_data.HP2.Error_Log[ERR_data.HP2.log_index] = i;							//Añadimos el error al log
							ERR_data.HP2.log_index++;													//Incrementamos el puntero del log
							if(ERR_data.HP2.log_index >= NUMBER_ERRORS_LOG)	ERR_data.HP2.log_index=0;	//Si llegamos al final del log, volvemos a la posición inicial (buffer circular)
						}
						else if (ConfiguracionGestionErrores[i].message_type == Aviso)
						{
							ERR_data.HP2.Avisos_log[ERR_data.HP2.avisos_log_index] = i;								//Añadimos el aviso al log
							ERR_data.HP2.avisos_log_index++;														//Incrementamos el puntero del log de avisos
							if(ERR_data.HP2.avisos_log_index >= NUMBER_AVISOS_LOG)	ERR_data.HP2.avisos_log_index=0;//Si llegamos al final del log de avisos, volvemos a la posición inicial (buffer circular)
							ERR_data.HP2.Perif_warning = i;
							ERR_data.HP2.Warning_code = i + ERROR_CODE_PERIF_2_OFFSET;
							ERR_data.HP2.user_msg_warning = ConfiguracionGestionErrores[i].wrng_user_msg;			//Mensaje que ha de mostrarse para el usuario
						}
						
						if (ConfiguracionGestionErrores[i].manage_type > ERR_data.HP2.Perif_err_management)
						{
							ERR_data.HP2.Perif_err_management = ConfiguracionGestionErrores[i].manage_type;
                            ERR_data.HP2.Perif_error = (GestionErrors_t)i;
							
							ERR_data.HP2.error_code = ERR_data.HP2.Perif_error + ERROR_CODE_PERIF_2_OFFSET;		//Codigo de error para mostrar por pantalla
                            ERR_data.HP2.user_msg_error = (errors_messages)ConfiguracionGestionErrores[i].err_user_msg;			//Mensaje que ha de mostrarse para el usuario
							
							if(ConfiguracionGestionErrores[i].manage_type == ConVacSeguir)	{	ErrorSet_StartCount(Manip2);	}
							
							ConfiguracionGestionErrores[i].ptr_function_set((void*)ConfiguracionGestionErrores[i].perif);	//Callback de activación de error Main
							
							ERR_delete(i);				//Reseteo la consigna de tiempo
							
							/* V7790 - LOG error */
                            if (HPcryoGetFromSlot(PRF_HW_SLOT2, &HPcryoData_HP2, &PRFdata_HP2))
							{	
								AppLOG_saveERROR(ERR_data.HP2.error_code, HPcryoData_HP2, PRFdata_HP2);	
								AppLOG_saveTRT(HPcryoData_HP2, PRFdata_HP2);
							}
						}
						break;
					case Manip3:
						if (ConfiguracionGestionErrores[i].message_type == Alarma)
						{
							ERR_data.HP3.Error_Log[ERR_data.HP3.log_index] = i;							//Añadimos el error al log
							ERR_data.HP3.log_index++;													//Incrementamos el puntero del log
							if(ERR_data.HP3.log_index >= NUMBER_ERRORS_LOG)	ERR_data.HP3.log_index=0;	//Si llegamos al final del log, volvemos a la posición inicial (buffer circular)
						}
						else if (ConfiguracionGestionErrores[i].message_type == Aviso)
						{
							ERR_data.HP3.Avisos_log[ERR_data.HP3.avisos_log_index] = i;								//Añadimos el aviso al log
							ERR_data.HP3.avisos_log_index++;														//Incrementamos el puntero del log de avisos
							if(ERR_data.HP3.avisos_log_index >= NUMBER_AVISOS_LOG)	ERR_data.HP3.avisos_log_index=0;//Si llegamos al final del log de avisos, volvemos a la posición inicial (buffer circular)
							ERR_data.HP3.Perif_warning = i;
							ERR_data.HP3.Warning_code = i + ERROR_CODE_PERIF_3_OFFSET;
							ERR_data.HP3.user_msg_warning = ConfiguracionGestionErrores[i].wrng_user_msg;
						}
						
						if (ConfiguracionGestionErrores[i].manage_type > ERR_data.HP3.Perif_err_management)
						{
							ERR_data.HP3.Perif_err_management = ConfiguracionGestionErrores[i].manage_type;
                            ERR_data.HP3.Perif_error = (GestionErrors_t)i;
							
							ERR_data.HP3.error_code = ERR_data.HP3.Perif_error + ERROR_CODE_PERIF_3_OFFSET;	//Codigo de error para mostrar por pantalla
                            ERR_data.HP3.user_msg_error = (errors_messages)ConfiguracionGestionErrores[i].err_user_msg;		//Mensaje que ha de mostrarse para el usuario
							
							if(ConfiguracionGestionErrores[i].manage_type == ConVacSeguir)	{	ErrorSet_StartCount(Manip3);	}
							
							ConfiguracionGestionErrores[i].ptr_function_set((void *)ConfiguracionGestionErrores[i].perif);	//Callback de activación de error Main
							
							ERR_delete(i);				//Reseteo la consigna de tiempo
							
							/* V7790 - LOG error */
                            if (HPcryoGetFromSlot(PRF_HW_SLOT3, &HPcryoData_HP3, &PRFdata_HP3))
							{	
								AppLOG_saveERROR(ERR_data.HP3.error_code, HPcryoData_HP3, PRFdata_HP3);	
								AppLOG_saveTRT(HPcryoData_HP3, PRFdata_HP3);
							}
						}
						break;
					case Manip4:
						//if (!HPcryoGetFromSlot(Manip4, &HPcryoData_HP4, &PRFdata_HP4)) break;
						
						if (ConfiguracionGestionErrores[i].message_type == Alarma)
						{
							ERR_data.HP4.Error_Log[ERR_data.HP4.log_index] = i;							//Añadimos el error al log
							ERR_data.HP4.log_index++;													//Incrementamos el puntero del log
							if(ERR_data.HP4.log_index >= NUMBER_ERRORS_LOG)	ERR_data.HP4.log_index=0;	//Si llegamos al final del log, volvemos a la posición inicial (buffer circular)
						}
						else if (ConfiguracionGestionErrores[i].message_type == Aviso)
						{
							ERR_data.HP4.Avisos_log[ERR_data.HP4.avisos_log_index] = i;								//Añadimos el aviso al log
							ERR_data.HP4.avisos_log_index++;														//Incrementamos el puntero del log de avisos
							if(ERR_data.HP4.avisos_log_index >= NUMBER_AVISOS_LOG)	ERR_data.HP4.avisos_log_index=0;//Si llegamos al final del log de avisos, volvemos a la posición inicial (buffer circular)
							ERR_data.HP4.Perif_warning = i;
							ERR_data.HP4.Warning_code = i + ERROR_CODE_PERIF_4_OFFSET;
							ERR_data.HP4.user_msg_warning = ConfiguracionGestionErrores[i].wrng_user_msg;
						}
						
						if (ConfiguracionGestionErrores[i].manage_type > ERR_data.HP4.Perif_err_management)
						{
							ERR_data.HP4.Perif_err_management = ConfiguracionGestionErrores[i].manage_type;
                            ERR_data.HP4.Perif_error = (GestionErrors_t)i;
							
							ERR_data.HP4.error_code = ERR_data.HP4.Perif_error + ERROR_CODE_PERIF_4_OFFSET;	//Codigo de error para mostrar por pantalla
                            ERR_data.HP4.user_msg_error = (errors_messages)ConfiguracionGestionErrores[i].err_user_msg;		//Mensaje que ha de mostrarse para el usuario
							
							if(ConfiguracionGestionErrores[i].manage_type == ConVacSeguir)	{	ErrorSet_StartCount(Manip4);	}
							
							ConfiguracionGestionErrores[i].ptr_function_set((void*)ConfiguracionGestionErrores[i].perif);	//Callback de activación de error Main
							
							ERR_delete(i);				//Reseteo la consigna de tiempo
							
							/* V7790 - LOG error */
                            if (HPcryoGetFromSlot(PRF_HW_SLOT4, &HPcryoData_HP4, &PRFdata_HP4))
							{	
								AppLOG_saveERROR(ERR_data.HP4.error_code, HPcryoData_HP4, PRFdata_HP4);	
								AppLOG_saveTRT(HPcryoData_HP4, PRFdata_HP4);
							}
						}
						break;
					case Maq:
						if (ConfiguracionGestionErrores[i].message_type == Alarma)
						{
							ERR_data.Machine.Error_Log[ERR_data.Machine.log_index] = i;							//Añadimos el error al log
							ERR_data.Machine.log_index++;														//Incrementamos el puntero del log
							if(ERR_data.Machine.log_index >= NUMBER_ERRORS_LOG)	ERR_data.Machine.log_index=0;	//Si llegamos al final del log, volvemos a la posición inicial (buffer circular)
						}
						else if (ConfiguracionGestionErrores[i].message_type == Aviso)
						{
							ERR_data.Machine.Avisos_log[ERR_data.Machine.avisos_log_index] = i;								//Añadimos el aviso al log
							ERR_data.Machine.avisos_log_index++;															//Incrementamos el puntero del log de avisos
							if(ERR_data.Machine.avisos_log_index >= NUMBER_AVISOS_LOG)	ERR_data.Machine.avisos_log_index=0;//Si llegamos al final del log de avisos, volvemos a la posición inicial (buffer circular)
							ERR_data.Machine.Perif_warning = i;
							ERR_WarningCode_to_Flags (i);
							ERR_data.Machine.Warning_code = i + ERROR_CODE_MACHINE_OFFSET;
							ERR_data.Machine.user_msg_warning = ConfiguracionGestionErrores[i].wrng_user_msg;
						}
						
						if (ConfiguracionGestionErrores[i].manage_type > ERR_data.Machine.Perif_err_management)
						{
							ERR_data.Machine.Perif_err_management = ConfiguracionGestionErrores[i].manage_type;
                            ERR_data.Machine.Perif_error = (GestionErrors_t)i;
							
							ERR_data.Machine.error_code = ERR_data.Machine.Perif_error + ERROR_CODE_MACHINE_OFFSET;	//Codigo de error para mostrar por pantalla
                            ERR_data.Machine.user_msg_error = (errors_messages)ConfiguracionGestionErrores[i].err_user_msg;			//Mensaje que ha de mostrarse para el usuario
							
							if(ConfiguracionGestionErrores[i].manage_type == ConVacSeguir)	{	ErrorSet_StartCount(Maq);	}
							
							ConfiguracionGestionErrores[i].ptr_function_set((void*)ConfiguracionGestionErrores[i].perif);	//Callback de activación de error Main
							
							ERR_delete(i);				//Reseteo la consigna de tiempo
							
							/* V7790 - LOG error */
							AppLOG_saveERROR(ERR_data.Machine.error_code, NULL, NULL);
							AppLOG_saveMachine();
						}
						break;
					default:
						//ERROR
						break;
				}
			}
		}
		
		switch (ERR_data.HP1.Perif_err_management)
		{
			case Noerror:
				break;
			case ConVacParar:
                if ((ERR_data.HP1.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT1, &HPcryoData_HP1, &PRFdata_HP1))	HPcryoTrtPause(HPcryoData_HP1, PRFdata_HP1);
				break;
			case ConVacSeguir:
                if ((ERR_data.HP1.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT1, &HPcryoData_HP1, &PRFdata_HP1))	HPcryoTrtPause(HPcryoData_HP1, PRFdata_HP1);
				break;
			case SinVac:
                if ((ERR_data.HP1.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT1, &HPcryoData_HP1, &PRFdata_HP1))	HPcryoStop(ERR_FORCE_VACUUM_OFF ,HPcryoData_HP1, PRFdata_HP1);
				break;
		}
		switch (ERR_data.HP2.Perif_err_management)
		{
			case Noerror:
				break;
			case ConVacParar:
                if ((ERR_data.HP2.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT2, &HPcryoData_HP2, &PRFdata_HP2))	HPcryoTrtPause(HPcryoData_HP2, PRFdata_HP2);
				break;
			case ConVacSeguir:
                if ((ERR_data.HP2.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT2, &HPcryoData_HP1, &PRFdata_HP1))	HPcryoTrtPause(HPcryoData_HP2, PRFdata_HP2);
				break;
			case SinVac:
                if ((ERR_data.HP2.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT2, &HPcryoData_HP2, &PRFdata_HP2))	HPcryoStop(ERR_FORCE_VACUUM_OFF ,HPcryoData_HP2, PRFdata_HP2);
				break;
		}
		switch (ERR_data.HP3.Perif_err_management)
		{
			case Noerror:
				break;
			case ConVacParar:
                if ((ERR_data.HP3.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT3, &HPcryoData_HP3, &PRFdata_HP3))	HPcryoTrtPause(HPcryoData_HP3, PRFdata_HP3);
				break;
			case ConVacSeguir:
                if ((ERR_data.HP3.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT3, &HPcryoData_HP1, &PRFdata_HP3))	HPcryoTrtPause(HPcryoData_HP3, PRFdata_HP3);
				break;
			case SinVac:
                if ((ERR_data.HP3.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT3, &HPcryoData_HP3, &PRFdata_HP3))	HPcryoStop(ERR_FORCE_VACUUM_OFF ,HPcryoData_HP3, PRFdata_HP3);
				break;
		}
		switch (ERR_data.HP4.Perif_err_management)
		{
			case Noerror:
				break;
			case ConVacParar:
                if ((ERR_data.HP4.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT4, &HPcryoData_HP4, &PRFdata_HP4))	HPcryoTrtPause(HPcryoData_HP4, PRFdata_HP4);
				break;
			case ConVacSeguir:
                if ((ERR_data.HP4.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT4, &HPcryoData_HP4, &PRFdata_HP4))	HPcryoTrtPause(HPcryoData_HP4, PRFdata_HP4);
				break;
			case SinVac:
                if ((ERR_data.HP4.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT4, &HPcryoData_HP4, &PRFdata_HP4))	HPcryoStop(ERR_FORCE_VACUUM_OFF ,HPcryoData_HP4, PRFdata_HP4);
				break;
		}
		switch (ERR_data.Machine.Perif_err_management)
		{
			case Noerror:
				break;
			case ConVacParar:
				//Se comprueba si hay manipulo conectado, si el error de la maquina es superior al propio del manipulo, y por ultimo se manda el manipulo al estado deseado para gestionar el error
                if (HPcryoGetFromSlot(PRF_HW_SLOT1, &HPcryoData_HP1, &PRFdata_HP1))	if(ERR_data.HP1.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoTrtPause(HPcryoData_HP1, PRFdata_HP1);
                if (HPcryoGetFromSlot(PRF_HW_SLOT2, &HPcryoData_HP2, &PRFdata_HP2))	if(ERR_data.HP2.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoTrtPause(HPcryoData_HP2, PRFdata_HP2);
                if (HPcryoGetFromSlot(PRF_HW_SLOT3, &HPcryoData_HP3, &PRFdata_HP3))	if(ERR_data.HP3.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoTrtPause(HPcryoData_HP3, PRFdata_HP3);
                if (HPcryoGetFromSlot(PRF_HW_SLOT4, &HPcryoData_HP4, &PRFdata_HP4))	if(ERR_data.HP4.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoTrtPause(HPcryoData_HP4, PRFdata_HP4);
				break;
			case ConVacSeguir:
				//Se comprueba si hay manipulo conectado, si el error de la maquina es superior al propio del manipulo, y por ultimo se manda el manipulo al estado deseado para gestionar el error
                if (HPcryoGetFromSlot(PRF_HW_SLOT1, &HPcryoData_HP1, &PRFdata_HP1))	if(ERR_data.HP1.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoTrtPause(HPcryoData_HP1, PRFdata_HP1);
                if (HPcryoGetFromSlot(PRF_HW_SLOT2, &HPcryoData_HP2, &PRFdata_HP2))	if(ERR_data.HP2.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoTrtPause(HPcryoData_HP2, PRFdata_HP2);
                if (HPcryoGetFromSlot(PRF_HW_SLOT3, &HPcryoData_HP3, &PRFdata_HP3))	if(ERR_data.HP3.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoTrtPause(HPcryoData_HP3, PRFdata_HP3);
                if (HPcryoGetFromSlot(PRF_HW_SLOT4, &HPcryoData_HP4, &PRFdata_HP4))	if(ERR_data.HP4.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoTrtPause(HPcryoData_HP4, PRFdata_HP4);
				break;
			case SinVac:
				//Se comprueba si hay manipulo conectado, si el error de la maquina es superior al propio del manipulo, y por ultimo se manda el manipulo al estado deseado para gestionar el error
                if (HPcryoGetFromSlot(PRF_HW_SLOT1, &HPcryoData_HP1, &PRFdata_HP1))	if(ERR_data.HP1.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoStop(ERR_FORCE_VACUUM_OFF ,HPcryoData_HP1, PRFdata_HP1);
                if (HPcryoGetFromSlot(PRF_HW_SLOT2, &HPcryoData_HP2, &PRFdata_HP2))	if(ERR_data.HP2.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoStop(ERR_FORCE_VACUUM_OFF ,HPcryoData_HP2, PRFdata_HP2);
                if (HPcryoGetFromSlot(PRF_HW_SLOT3, &HPcryoData_HP3, &PRFdata_HP3))	if(ERR_data.HP3.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoStop(ERR_FORCE_VACUUM_OFF ,HPcryoData_HP3, PRFdata_HP3);
                if (HPcryoGetFromSlot(PRF_HW_SLOT4, &HPcryoData_HP4, &PRFdata_HP4))	if(ERR_data.HP4.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoStop(ERR_FORCE_VACUUM_OFF ,HPcryoData_HP4, PRFdata_HP4);
				break;
		}
	}
}


void ERR_add(uint16 newError)
{
	static uint8 errorEnable = 0;
	//Control de errores al inicio
	if(errorEnable == 0)
	{
		if(TICKS_DiffTicks(initTimeErrorEnable) > ONE_MIN_MILISEC) //inicializado en el error init
		{
			errorEnable = 1;
		}
		else
		{
			return;
		}
	}
	Errors_count[newError].error_set_count++;							//Incrementamos la variable donde se suman el número de veces que ha saltado el mismo error
	
	if (Errors_count[newError].timer_error_count == 0)					//Si la referencia de tiempo referente al error actual (newError) está a cero
	{
		Errors_count[newError].timer_error_count = TICKS_GetTicks();	//Se toma la referencia de tiempo
		ConfiguracionGestionErrores[newError].ptr_function_add((void*)ConfiguracionGestionErrores[newError].perif);	//Función (CallBack para cuando activan el error) para realizar acciones propias de un error con gestión personalizada
	} 	 				
}


void ERR_clear(perif_to_manage HP)
{	
	switch (HP)
	{
	case No_perif:
		break;
	case Manip1:
		if(ERR_data.HP1.Perif_err_management == ConVacSeguir)	{	ErrorClear_ProcessCount(HP);	}
		
		ConfiguracionGestionErrores[ERR_data.HP1.Perif_error].ptr_function_clear((void*)ConfiguracionGestionErrores[ERR_data.HP1.Perif_error].perif);			//Función (CallBack al quitar el error) para realizar acciones propias de un error con gestión personalizada
		
		if(ERR_data.HP1.Perif_err_management > Noerror)
		{
			Errors_count[ERR_data.HP1.Perif_error].error_set_count = 0;		//Resetear contador del error gestionado
			Errors_count[ERR_data.HP1.Perif_error].timer_error_count = 0;	//Resetear referencia de tiempo del error gestionado
			//Errors_count[ERR_data.HP1.Perif_error].aux_count = 0;
			
			switch(ERR_data.HP1.Perif_err_management)
			{
				case ConVacParar:
                    if ((ERR_data.HP1.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT1, &HPcryoData_HP1, &PRFdata_HP1))	HPcryoStop(ERR_MANTAIN_VACUUM_STATE ,HPcryoData_HP1, PRFdata_HP1);		//Manda al periferico a FINAL DE TRATAMIENTO
					break;
				case ConVacSeguir:
                    if ((ERR_data.HP1.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT1, &HPcryoData_HP1, &PRFdata_HP1))	HPcryoTrtResume(HPcryoData_HP1, PRFdata_HP1);		//Manda al periferico a FINAL DE TRATAMIENTO
					break;
				case SinVac:
					//Ya se mandó a IDLE en el update
					break;
				default:
					//ERROR
					break;
			}
		}
		//Inicialización Manipulo 1
		ERR_data.HP1.Perif_id = Manip1;
        ERR_data.HP1.Perif_error = Error_ok;
		ERR_data.HP1.Perif_err_management = 0;
		ERR_data.HP1.error_code = Noerror;
		break;
	case Manip2:
		if(ERR_data.HP2.Perif_err_management == ConVacSeguir)	{	ErrorClear_ProcessCount(HP);	}
		
		ConfiguracionGestionErrores[ERR_data.HP2.Perif_error].ptr_function_clear((void*)ConfiguracionGestionErrores[ERR_data.HP2.Perif_error].perif);			//Función (CallBack) para realizar acciones propias de un error con gestión personalizada
			
		if(ERR_data.HP2.Perif_err_management > Noerror)
		{
			Errors_count[ERR_data.HP2.Perif_error].error_set_count = 0;		//Resetear contador del error gestionado
			Errors_count[ERR_data.HP2.Perif_error].timer_error_count = 0;	//Resetear referencia de tiempo del error gestionado
			//Errors_count[ERR_data.HP1.Perif_error].aux_count = 0;
			
			switch(ERR_data.HP2.Perif_err_management)
			{
				case ConVacParar:
                    if ((ERR_data.HP2.Perif_err_management >= ERR_data.Machine.Perif_err_management) && (HPcryoGetFromSlot(PRF_HW_SLOT2, &HPcryoData_HP2, &PRFdata_HP2)))	HPcryoStop(ERR_MANTAIN_VACUUM_STATE ,HPcryoData_HP2, PRFdata_HP2);		//Manda al periferico a FINAL DE TRATAMIENTO
					break;
				case ConVacSeguir:
                    if ((ERR_data.HP2.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT2, &HPcryoData_HP2, &PRFdata_HP2))	HPcryoTrtResume(HPcryoData_HP2, PRFdata_HP2);		//Manda al periferico a FINAL DE TRATAMIENTO
					break;
				case SinVac:
					//Ya se mandó a IDLE en el update
					break;
				default:
					//ERROR
					break;
			}
		}
		//Inicialización Manipulo 2
		ERR_data.HP2.Perif_id = Manip2;
        ERR_data.HP2.Perif_error = Error_ok;
		ERR_data.HP2.Perif_err_management = 0;
		ERR_data.HP2.error_code = Noerror;
		break;
	case Manip3:
		if(ERR_data.HP3.Perif_err_management == ConVacSeguir)	{	ErrorClear_ProcessCount(HP);	}
		
		ConfiguracionGestionErrores[ERR_data.HP3.Perif_error].ptr_function_clear((void*)ConfiguracionGestionErrores[ERR_data.HP3.Perif_error].perif);			//Función (CallBack) para realizar acciones propias de un error con gestión personalizada
			
		if(ERR_data.HP3.Perif_err_management > Noerror)
		{
			Errors_count[ERR_data.HP3.Perif_error].error_set_count = 0;		//Resetear contador del error gestionado
			Errors_count[ERR_data.HP3.Perif_error].timer_error_count = 0;	//Resetear referencia de tiempo del error gestionado
			//Errors_count[ERR_data.HP1.Perif_error].aux_count = 0;
			
			switch(ERR_data.HP3.Perif_err_management)
			{
				case ConVacParar:
                    if ((ERR_data.HP3.Perif_err_management >= ERR_data.Machine.Perif_err_management) && (HPcryoGetFromSlot(PRF_HW_SLOT3, &HPcryoData_HP3, &PRFdata_HP3)))	HPcryoStop(ERR_MANTAIN_VACUUM_STATE ,HPcryoData_HP3, PRFdata_HP3);		//Manda al periferico a FINAL DE TRATAMIENTO
					break;
				case ConVacSeguir:
                    if ((ERR_data.HP3.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT3, &HPcryoData_HP3, &PRFdata_HP3))	HPcryoTrtResume(HPcryoData_HP3, PRFdata_HP3);		//Manda al periferico a FINAL DE TRATAMIENTO
					break;
				case SinVac:
					//Ya se mandó a IDLE en el update
					break;
				default:
					//ERROR
					break;
			}
		}
		//Inicialización Manipulo 3
		ERR_data.HP3.Perif_id = Manip3;
        ERR_data.HP3.Perif_error = Error_ok;
		ERR_data.HP3.Perif_err_management = 0;
		ERR_data.HP3.error_code = Noerror;
		break;
	case Manip4:
		if(ERR_data.HP4.Perif_err_management == ConVacSeguir)	{	ErrorClear_ProcessCount(HP);	}
		
		ConfiguracionGestionErrores[ERR_data.HP4.Perif_error].ptr_function_clear((void*)ConfiguracionGestionErrores[ERR_data.HP4.Perif_error].perif);			//Función (CallBack) para realizar acciones propias de un error con gestión personalizada
			
		if(ERR_data.HP4.Perif_err_management > Noerror)
		{
			Errors_count[ERR_data.HP4.Perif_error].error_set_count = 0;		//Resetear contador del error gestionado
			Errors_count[ERR_data.HP4.Perif_error].timer_error_count = 0;	//Resetear referencia de tiempo del error gestionado
			//Errors_count[ERR_data.HP1.Perif_error].aux_count = 0;
			
			switch(ERR_data.HP4.Perif_err_management)
			{
				case ConVacParar:
                    if ((ERR_data.HP4.Perif_err_management >= ERR_data.Machine.Perif_err_management) && (HPcryoGetFromSlot(PRF_HW_SLOT4, &HPcryoData_HP4, &PRFdata_HP4)))	HPcryoStop(ERR_MANTAIN_VACUUM_STATE ,HPcryoData_HP4, PRFdata_HP4);		//Manda al periferico a FINAL DE TRATAMIENTO
					break;
				case ConVacSeguir:
                    if ((ERR_data.HP4.Perif_err_management >= ERR_data.Machine.Perif_err_management) && HPcryoGetFromSlot(PRF_HW_SLOT4, &HPcryoData_HP4, &PRFdata_HP4))	HPcryoTrtResume(HPcryoData_HP4, PRFdata_HP4);		//Manda al periferico a FINAL DE TRATAMIENTO
					break;
				case SinVac:
					//Ya se mandó a IDLE en el update
					break;
				default:
					//ERROR
					break;
			}
		}
		//Inicialización Manipulo 4
		ERR_data.HP4.Perif_id = Manip4;
        ERR_data.HP4.Perif_error = Error_ok;
		ERR_data.HP4.Perif_err_management = 0;
		ERR_data.HP4.error_code = Noerror;
		break;
	case Maq:
		if(ERR_data.Machine.Perif_err_management == ConVacSeguir)	{	ErrorClear_ProcessCount(HP);	}
		
		ConfiguracionGestionErrores[ERR_data.Machine.Perif_error].ptr_function_clear((void*)ConfiguracionGestionErrores[ERR_data.Machine.Perif_error].perif);			//Función (CallBack) para realizar acciones propias de un error con gestión personalizada
			
		if(ERR_data.Machine.Perif_err_management > Noerror)
		{
			Errors_count[ERR_data.Machine.Perif_error].error_set_count = 0;		//Resetear contador del error gestionado
			Errors_count[ERR_data.Machine.Perif_error].timer_error_count = 0;	//Resetear referencia de tiempo del error gestionado
			
			switch(ERR_data.Machine.Perif_err_management)
			{
				case ConVacParar:
                    if (HPcryoGetFromSlot(PRF_HW_SLOT1, &HPcryoData_HP1, &PRFdata_HP1))	if(ERR_data.HP1.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoStop(ERR_MANTAIN_VACUUM_STATE ,HPcryoData_HP1, PRFdata_HP1);		//Manda a la maquina a FINAL DE TRATAMIENTO
                    if (HPcryoGetFromSlot(PRF_HW_SLOT2, &HPcryoData_HP2, &PRFdata_HP2))	if(ERR_data.HP2.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoStop(ERR_MANTAIN_VACUUM_STATE ,HPcryoData_HP2, PRFdata_HP2);		//Manda a la maquina a FINAL DE TRATAMIENTO
                    if (HPcryoGetFromSlot(PRF_HW_SLOT3, &HPcryoData_HP3, &PRFdata_HP3))	if(ERR_data.HP3.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoStop(ERR_MANTAIN_VACUUM_STATE ,HPcryoData_HP3, PRFdata_HP3);		//Manda a la maquina a FINAL DE TRATAMIENTO
                    if (HPcryoGetFromSlot(PRF_HW_SLOT4, &HPcryoData_HP4, &PRFdata_HP4))	if(ERR_data.HP4.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoStop(ERR_MANTAIN_VACUUM_STATE ,HPcryoData_HP4, PRFdata_HP4);		//Manda a la maquina a FINAL DE TRATAMIENTO
					break;
				case ConVacSeguir:
                    if (HPcryoGetFromSlot(PRF_HW_SLOT1, &HPcryoData_HP1, &PRFdata_HP1))	if(ERR_data.HP1.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoTrtResume(HPcryoData_HP1, PRFdata_HP1);		//Manda a la maquina a FINAL DE TRATAMIENTO
                    if (HPcryoGetFromSlot(PRF_HW_SLOT2, &HPcryoData_HP2, &PRFdata_HP2))	if(ERR_data.HP2.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoTrtResume(HPcryoData_HP2, PRFdata_HP2);		//Manda a la maquina a FINAL DE TRATAMIENTO
                    if (HPcryoGetFromSlot(PRF_HW_SLOT3, &HPcryoData_HP3, &PRFdata_HP3))	if(ERR_data.HP3.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoTrtResume(HPcryoData_HP3, PRFdata_HP3);		//Manda a la maquina a FINAL DE TRATAMIENTO
                    if (HPcryoGetFromSlot(PRF_HW_SLOT4, &HPcryoData_HP4, &PRFdata_HP4))	if(ERR_data.HP4.Perif_err_management <= ERR_data.Machine.Perif_err_management)	HPcryoTrtResume(HPcryoData_HP4, PRFdata_HP4);		//Manda a la maquina a FINAL DE TRATAMIENTO
					break;
				case SinVac:
					//Ya se mandó a IDLE en el update
					break;
				default:
					//ERROR
					break;
			}
		}
		//Inicialización Maquina
		ERR_data.Machine.Perif_id = Maq;
        ERR_data.Machine.Perif_error = Error_ok;
		ERR_data.Machine.Perif_err_management = 0;
		ERR_data.Machine.error_code = Noerror;
		break;
	default:
		break;
	}
}


void ERR_warning_clear(perif_to_manage HP, uint16 Flags_Erase_Mask)
{
	ERR_data.Warning_Flags = ERR_data.Warning_Flags&(~Flags_Erase_Mask);
	switch (HP)
	{
		case Manip1:
			ERR_data.HP1.Perif_warning = Noerror;
			ERR_data.HP1.Warning_code = Noerror;
			break;
		case Manip2:
			ERR_data.HP2.Perif_warning = Noerror;
			ERR_data.HP2.Warning_code = Noerror;
			break;
		case Manip3:
			ERR_data.HP3.Perif_warning = Noerror;
			ERR_data.HP3.Warning_code = Noerror;
			break;
		case Manip4:
			ERR_data.HP4.Perif_warning = Noerror;
			ERR_data.HP4.Warning_code = Noerror;
			break;
		case Maq:
			ERR_data.Machine.Perif_warning = Noerror;
			ERR_data.Machine.Warning_code = Noerror;
			break;
		default:
			//ERROR
			break;
	}
}


void ERR_delete(uint16 newError)		//Va reduciendo las repeticiones que se acumulan para saltar la alarma con un contador de vueltas 
{
	Errors_count[newError].timer_error_count = 0;	//Se reinicia la referencia de tiempo para saltar el error
}


uint8 ERR_interface_msg(perif_to_manage HP, uint32 *err_code_HP, errors_messages *err_msg_HP, uint32 *warning_code_HP, warning_messages *warning_msg_HP)
{
	switch (HP)
	{
	case Manip1:
		( *err_code_HP) = ERR_data.HP1.error_code;
		( *err_msg_HP) = ERR_data.HP1.user_msg_error;
		( *warning_code_HP) = ERR_data.HP1.Warning_code;
        ( *warning_msg_HP) = (warning_messages)ERR_data.HP1.user_msg_warning;
		
		if(!ERR_data.HP1.Perif_error)	return 1;
		else	return 0;
		break;
	case Manip2:
		( *err_code_HP) = ERR_data.HP2.error_code;
		( *err_msg_HP) = ERR_data.HP2.user_msg_error;
		( *warning_code_HP) = ERR_data.HP2.Warning_code;
        ( *warning_msg_HP) = (warning_messages)ERR_data.HP2.user_msg_warning;
		
		if(!ERR_data.HP2.Perif_error)	return 1;
		else	return 0;
		break;
	case Manip3:
		( *err_code_HP) = ERR_data.HP3.error_code;
		( *err_msg_HP) = ERR_data.HP3.user_msg_error;
		( *warning_code_HP) = ERR_data.HP3.Warning_code;
        ( *warning_msg_HP) = (warning_messages)ERR_data.HP3.user_msg_warning;
		
		if(!ERR_data.HP3.Perif_error)	return 1;
		else	return 0;
		break;
	case Manip4:
		( *err_code_HP) = ERR_data.HP4.error_code;
		( *err_msg_HP) = ERR_data.HP4.user_msg_error;
		( *warning_code_HP) = ERR_data.HP4.Warning_code;
        ( *warning_msg_HP) = (warning_messages)ERR_data.HP4.user_msg_warning;
		
		if(!ERR_data.HP4.Perif_error)	return 1;
		else	return 0;
		break;
	case Maq:
		( *err_code_HP) = ERR_data.Machine.error_code;
		( *err_msg_HP) = ERR_data.Machine.user_msg_error;
		( *warning_code_HP) = ERR_data.Machine.Warning_code;
        ( *warning_msg_HP) = (warning_messages)ERR_data.Machine.user_msg_warning;
		
		if(!ERR_data.Machine.Perif_error)	return 1;
		else	return 0;
		break;
	default:
		//En cualquier otro caso
		return 0;
		break;
	}
}


void ERR_reset_perif(perif_to_manage HP)
{
	uint8 i;		//Variable auxiliar
	for (i = 0; i < ERR_LISR_PER_PERIFERIC; i++)		//Recorro el vector que almacena los errores asociados a cada periferico
	{
		Errors_count[Errors_list_per_Perif[HP][i]].error_set_count = 0;		//Reinicio el contador del error
		Errors_count[Errors_list_per_Perif[HP][i]].timer_error_count = 0;	//Se resetea la referencia de tiempo del error
		//Errors_count[Errors_list_per_Perif[HP][i]].aux_count = 0;
	}
}


uint8 ERR_standby_err(uint32 err_code_HP)
{
	uint8 aux;		//Variable auxiliar
	
	for (aux = 0; aux < ERR_LIST_ERR_STANDBY; aux++)
	{
		if (Standby_Err_List[aux] == err_code_HP)	return TRUE;
	}
	return FALSE;
}

void cbk_ErrorAddVoid(void *estructura){}
void cbk_ErrorSetVoid(void *estructura){}
void cbk_ErrorClearVoid(void *estructura){}

/*V7775*/
void ErrorSet_StartCount(perif_to_manage Perif)
{
	if(time_change_policy[Perif] == 0)	{time_change_policy[Perif] = TICKS_GetTicks();}
}

void ErrorClear_ProcessCount(perif_to_manage Perif)
{
	if(TICKS_DiffTicks(time_change_policy[Perif])>TIME_2_CHANGE_ERR_POLICY)	/*15 minutos*/
	{
		switch(Perif)
		{
		case Manip1:	ERR_data.HP1.Perif_err_management = ConVacParar;	break;
		case Manip2:	ERR_data.HP2.Perif_err_management = ConVacParar;	break;
		case Manip3:	ERR_data.HP3.Perif_err_management = ConVacParar;	break;
		case Manip4:	ERR_data.HP4.Perif_err_management = ConVacParar;	break;
		case Maq:	ERR_data.Machine.Perif_err_management = ConVacParar;	break;
		default: break;
		}
		time_change_policy[Perif] = 0;
	}
}

//void cbk_ErrorEXPReset485Coms (perif_to_manage Manip)
//{
////	uint8 PerifID;
////	GestionErrors_t Error;
//	
//	uint8 motor;
//	nova_ordre_t nueva_orden;
//	ordre_status_t estat_ordre;
//	uint8 temp1, temp2;
//	
//	motor = 0;
//	
////	switch(Manip)
////	{
////	case Manip1:
////		PerifID = PRF_HW_SLOT1;
////		Error = ERR_data.HP1.Perif_error;
////		break;
////	case Manip2:
////		PerifID = PRF_HW_SLOT2;
////		Error = ERR_data.HP2.Perif_error;
////		break;
////	case Manip3:
////		PerifID = PRF_HW_SLOT3;
////		Error = ERR_data.HP3.Perif_error;
////		break;
////	case Manip4:
////		PerifID = PRF_HW_SLOT4;
////		Error = ERR_data.HP4.Perif_error;
////		break;
////	case Maq:
////		PerifID = NULL;
////		Error = ERR_data.Machine.Perif_error;
////		break;
////	default: 
////		PerifID = NULL;
////		Error = NULL;
////		break;
////	}
//	
//	switch(motor)
//	{
//	case 0:	//INITIALIZE 1
//		nueva_orden.fields.tipus_operacio = OPERACIO_POOLING;
//		nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_1_RETRY;
//		nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_5_THREAD;
//		nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//		nueva_orden.fields.u8Memoria = RFID_MEMORY_SELECTION;
//		nueva_orden.fields.u8NumBytes = 0;
//		nueva_orden.fields.u32Addr = 0;
//		if(PROTMST_EncuaOrdre(EXP_PROTMST_SLOT_POS, nueva_orden, (void *)NULL) == SUCCESS)
//		{
//			motor = 1;	//Cambiamos a Initialize 2
//		}
//		else
//		{
//			PROTMST_Motor();
//			PROTMST_EstatOrdre
//			(
//					EXP_PROTMST_SLOT_POS, 
//					&(RFID_control.esclau.prot_mems_status),
//					&(RFID_control.esclau.u8esclau_comodin1), 
//					&(RFID_control.esclau.u8esclau_comodin1), 	/* comodin 1 */
//					&(RFID_control.esclau.u8esclau_comodin2)	/* comodin 2 */
//			);
//		}
//		break;
//	case 1: //INITIALIZE 2
//		PROTMST_Motor();
//		estat_ordre = PROTMST_EstatOrdre
//		(
//				EXP_PROTMST_SLOT_POS,
//				&(RFID_control.esclau.prot_mems_status),
//				&(RFID_control.esclau.u8esclau_comodin1), 
//				&(RFID_control.esclau.u8esclau_comodin1), 	/* comodin 1 */
//				&(RFID_control.esclau.u8esclau_comodin2)	/* comodin 2 */
//		);
//
//		if((estat_ordre.bit_field.u8OrdreFinalitzada == 1) && (estat_ordre.bit_field.u8ErrorComs == 0))
//		{
//			if(RFID_control.esclau.prot_mems_status.status == 0)
//			{
//				/* totes les memories estan en idle */
//				Motor = 3;
//			}
//			else
//			{
//				/* hi ha alguna memoria ocupada */
//				Motor = 2;
//			}
//		}
//		else if((estat_ordre.value&0xF0) != 0)
//		{
//			/* ha cancelat la placa o hi ha error coms */
//			Motor = 0;
//		}
//		break;
//	case 2: //INITIALIZE 3
//		for(temp1 = 0; temp1 < 8; temp1++)
//		{
//			temp2 = (RFID_control.esclau.prot_mems_status.status)>>(2*temp1);
//			temp2 &= 0x03;
//			if(temp2 != 0)
//			{
//				break;
//			}
//		}
//		if(temp1 >= 8)
//		{
//			/* no hi ha cap memo ocupada */
//			Motor = 3;
//		}
//		else
//		{
//			if(temp2 == PROT_MEM_STAT_FINISHED || temp2 == PROT_MEM_STAT_ABORTED)
//			{
//				/* s'havia acabat/cancelat l'ordre, es pot continuar */
//				nueva_orden.fields.tipus_operacio = OPERACIO_POOLING;
//				nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_1_RETRY;
//				nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_5_THREAD;
//				nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//				nueva_orden.fields.u8Memoria = temp1;
//				nueva_orden.fields.u8NumBytes = 0;
//				nueva_orden.fields.u32Addr = 0;
//				if(PROTMST_EncuaOrdre(EXP_PROTMST_SLOT_POS, nueva_orden, (void *)NULL) == SUCCESS)
//				{
//					Motor = 1;
//				}
//			}
//			else
//			{
//				/* ordre en curs, vaig a cancelar */
//				nueva_orden.fields.tipus_operacio = OPERACIO_RESET;
//				nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_1_RETRY;
//				nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_5_THREAD;
//				nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//				nueva_orden.fields.u8Memoria = RFID_MEMORY_SELECTION;
//				nueva_orden.fields.u8NumBytes = 0;
//				nueva_orden.fields.u32Addr = 0;
//				if(PROTMST_EncuaOrdre(EXP_PROTMST_SLOT_POS, nueva_orden, (void *)NULL) == SUCCESS)
//				{
//					Motor = 1;
//				}
//			}
//		}
//		break;
//	default: break;
//	}
//}

//void cbk_ErrorResetPerif(perif_to_manage Manip)
//{
//	uint32 time2wait;
//	uint8 PerifID;
//	GestionErrors_t Error;
//	
//	switch(Manip)
//	{
//	case Manip1:
//		PerifID = PRF_HW_SLOT1;
//		Error = ERR_data.HP1.Perif_error;
//		break;
//	case Manip2:
//		PerifID = PRF_HW_SLOT2;
//		Error = ERR_data.HP2.Perif_error;
//		break;
//	case Manip3:
//		PerifID = PRF_HW_SLOT3;
//		Error = ERR_data.HP3.Perif_error;
//		break;
//	case Manip4:
//		PerifID = PRF_HW_SLOT4;
//		Error = ERR_data.HP4.Perif_error;
//		break;
//	case Maq:
//	default: 
//		PerifID = NULL;
//		break;
//	}
//	
//	if(Errors_count[Error].aux_count<3)
//	{
//		/*Deshabilitar Periferico*/
//		EXPdeshabilitarPeriferico(PerifID);
//		
//		/*Espera de 100ms*/
//		time2wait = TICKS_GetTicks();
//		while(TICKS_DiffTicks(time2wait)<100);
//		
//		/*Habilitar Periferico*/
//		EXPhabilitarPeriferico(PerifID);
//		
//		Errors_count[Error].aux_count++;
//		
//		switch(Manip)
//		{
//		case Manip1:
//			ERR_data.HP1.Perif_id = Manip1;
//			ERR_data.HP1.Perif_error = Noerror;
//			ERR_data.HP1.Perif_err_management = 0;
//			ERR_data.HP1.error_code = Noerror;
//			break;
//		case Manip2:
//			ERR_data.HP2.Perif_id = Manip1;
//			ERR_data.HP2.Perif_error = Noerror;
//			ERR_data.HP2.Perif_err_management = 0;
//			ERR_data.HP2.error_code = Noerror;
//			break;
//		case Manip3:
//			ERR_data.HP3.Perif_id = Manip1;
//			ERR_data.HP3.Perif_error = Noerror;
//			ERR_data.HP3.Perif_err_management = 0;
//			ERR_data.HP3.error_code = Noerror;
//			break;
//		case Manip4:
//			ERR_data.HP4.Perif_id = Manip1;
//			ERR_data.HP4.Perif_error = Noerror;
//			ERR_data.HP4.Perif_err_management = 0;
//			ERR_data.HP4.error_code = Noerror;
//			break;
//		case Maq:
//		default: 
//			break;
//		}
//	}
//	else
//	{
//		Errors_count[Error].aux_count = 0;
//	}
//}

void cbk_ErrorSetVoid_RESUCCION(void * estructura){}
void cbk_ErrorClearVoid_RESUCCION(void * estructura){}

void cbk_ErrorSetVoid_FAPELTIER(void * estructura){}
void cbk_ErrorClearVoid_FAPELTIER(void * estructura){}

void ERR_HP_disconected_mng (void)
{
    if (!HPcryoGetFromSlot(PRF_HW_SLOT1, &HPcryoData_HP1, &PRFdata_HP1))
	{ 
		if (ERR_data.HP1.Perif_error != Error_ComSPIMAN1)
		{	
			ERR_clear(Manip1);	//Se comprueba si cada manipulo está conectado, en caso de estar desconectado se borra el error actual activado del manipulo
		}
	}
    if (!HPcryoGetFromSlot(PRF_HW_SLOT2, &HPcryoData_HP2, &PRFdata_HP2))
	{ 
		if (ERR_data.HP2.Perif_error != Error_ComSPIMAN2)
		{
			ERR_clear(Manip2);
		}
	}
    if (!HPcryoGetFromSlot(PRF_HW_SLOT3, &HPcryoData_HP3, &PRFdata_HP3))
	{ 
		if (ERR_data.HP3.Perif_error != Error_ComSPIMAN3)
		{
			ERR_clear(Manip3);
		}
	}
    if (!HPcryoGetFromSlot(PRF_HW_SLOT4, &HPcryoData_HP4, &PRFdata_HP4))
	{ 
		if (ERR_data.HP4.Perif_error != Error_ComSPIMAN4)
		{
			ERR_clear(Manip4);	
		}
	}
}

void ERR_WarningCode_to_Flags (uint32 WarningCode)
{
	switch(WarningCode)
	{
		case Error_NivelH2OBajo: 			if((ERR_data.Warning_Flags&Aviso_NivelAguaBajo) == 0){ERR_data.New_Warning_Flag = 1;	AppLOG_saveWARNING(ERR_data.Machine.Warning_code);}		/* V7790 - LOGs */
											ERR_data.Warning_Flags = ERR_data.Warning_Flags | Aviso_NivelAguaBajo;	break;
		case Error_NivelH2OMedio:			if((ERR_data.Warning_Flags&Aviso_NivelAguaMedio) == 0){ERR_data.New_Warning_Flag = 1;	AppLOG_saveWARNING(ERR_data.Machine.Warning_code);}
											ERR_data.Warning_Flags = ERR_data.Warning_Flags | Aviso_NivelAguaMedio;	break;
		case Err_SnsTempAmbienteAltaAviso: 	if((ERR_data.Warning_Flags&Aviso_TempAmbiente) == 0){ERR_data.New_Warning_Flag = 1;		AppLOG_saveWARNING(ERR_data.Machine.Warning_code);}	
											ERR_data.Warning_Flags = ERR_data.Warning_Flags | Aviso_TempAmbiente;	break;
		case Err_ComRFID: 					if((ERR_data.Warning_Flags&Aviso_RFID) == 0){ERR_data.New_Warning_Flag = 1;				AppLOG_saveWARNING(ERR_data.Machine.Warning_code);}			
											ERR_data.Warning_Flags = ERR_data.Warning_Flags | Aviso_RFID;			break;
		case Err_RTC: 						if((ERR_data.Warning_Flags&Aviso_RTC) == 0){ERR_data.New_Warning_Flag = 1;				AppLOG_saveWARNING(ERR_data.Machine.Warning_code);}			
											ERR_data.Warning_Flags = ERR_data.Warning_Flags | Aviso_RTC;			break;
		case Error_FiltroAire: 				if((ERR_data.Warning_Flags&Aviso_FiltroAire) == 0){ERR_data.New_Warning_Flag = 1;		AppLOG_saveWARNING(ERR_data.Machine.Warning_code);}	
											ERR_data.Warning_Flags = ERR_data.Warning_Flags | Aviso_FiltroAire;		break;
		default: break;
	}
}

uint16 ERR_get_WarningFlags (void)
{
	return ERR_data.Warning_Flags;
}

uint8 ERR_get_NewWarningFlag(void)
{
	return ERR_data.New_Warning_Flag;
}

void ERR_erase_NewWarningFlag(void)
{
	ERR_data.New_Warning_Flag = 0;
}

//void ERR_refresh(void)
//{
//	// Error SPI	
////	if(!((EXPdata.UC.commonData2.fields.temporaryEnabledPerif >> 3) & 1))	{	ERR_add(Error_ComSPIMAN1INI);	}	else	{	ERR_delete(Error_ComSPIMAN1INI);	}
////	if(!((EXPdata.UC.commonData2.fields.temporaryEnabledPerif >> 2) & 1))	{	ERR_add(Error_ComSPIMAN2INI);	}	else	{	ERR_delete(Error_ComSPIMAN2INI);	}
////	if(!((EXPdata.UC.commonData2.fields.temporaryEnabledPerif >> 1) & 1))	{	ERR_add(Error_ComSPIMAN3INI);	}	else	{	ERR_delete(Error_ComSPIMAN3INI);	}
////	if(!(EXPdata.UC.commonData2.fields.temporaryEnabledPerif & 1))			{	ERR_add(Error_ComSPIMAN4INI);	}	else	{	ERR_delete(Error_ComSPIMAN4INI);	}
////	
////	// Resucciones
//////	if(GestionError.Resucciones[2] > 3)	{	ERR_add(Error_NResuccionesMAN1);	}	else	{	ERR_delete(Error_NResuccionesMAN1);	}		//Gestión especial del error
//////	if(GestionError.Resucciones[3] > 3)	{	ERR_add(Error_NResuccionesMAN2);	}	else	{	ERR_delete(Error_NResuccionesMAN2);	}		//Gestión especial del error
//////	if(GestionError.Resucciones[0] > 3)	{	ERR_add(Error_NResuccionesMAN3);	}	else	{	ERR_delete(Error_NResuccionesMAN3);	}		//Gestión especial del error
//////	if(GestionError.Resucciones[1] > 3)	{	ERR_add(Error_NResuccionesMAN4);	}	else	{	ERR_delete(Error_NResuccionesMAN4);	}		//Gestión especial del error
////	
////	// Errores 485
////	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 12) & 1))	{	ERR_add(Error_Com485_Fuente1);	}	else	{	ERR_delete(Error_Com485_Fuente1);}
////	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 11) & 1))	{	ERR_add(Error_Com485_Fuente2);	}	else	{	ERR_delete(Error_Com485_Fuente2);}
////	
////	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 10) & 1))	{	ERR_add(Error_Com485_Perd);		}	else	{	ERR_delete(Error_Com485_Perd);	}
////	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 9) & 1))	{	ERR_add(Error_Com485_Rebos);	}	else	{	ERR_delete(Error_Com485_Rebos);	}
////	
////	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 8) & 1))	{	ERR_add(Error_Com485_H201);		}	else	{	ERR_delete(Error_Com485_H201);	}
////	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 7) & 1))	{	ERR_add(Error_Com485_H202);		}	else	{	ERR_delete(Error_Com485_H202);	}
////	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 6) & 1))	{	ERR_add(Error_Com485_H203);		}	else	{	ERR_delete(Error_Com485_H203);	}	
////	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 5) & 1))	{	ERR_add(Error_Com485_H204);		}	else	{	ERR_delete(Error_Com485_H204);	}
////	
////	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 4) & 1))	{	ERR_add(Error_Com485_VAC1);		}	else	{	ERR_delete(Error_Com485_VAC1);	}
////	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 3) & 1))	{	ERR_add(Error_Com485_VAC2);		}	else	{	ERR_delete(Error_Com485_VAC2);	}
////	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 2) & 1))	{	ERR_add(Error_Com485_VAC3);		}	else	{	ERR_delete(Error_Com485_VAC3);	}
////	if(!((EXPdata.UC.commonData2.fields.enabled485devices >> 1) & 1))	{	ERR_add(Error_Com485_VAC4);		}	else	{	ERR_delete(Error_Com485_VAC4);	}
////	
////	if(!(EXPdata.UC.commonData2.fields.enabled485devices & 1))			{	ERR_add(Error_Com485_DetectorNivel);}	else	{	ERR_delete(Error_Com485_DetectorNivel);	}
////		
////	// Nivel del Agua	-	Falta por implementar en el modulo expansora
////	//EXPdata.UC.commonData2.fields.consWaterPump
////	if(!((GestionError.NivelAgua >> 1) & 1))	{	ERR_add(Error_NivelH2OMedio);	}	else	{	ERR_delete(Error_NivelH2OMedio);	}
////	if(!(GestionError.NivelAgua & 1))			{	ERR_add(Error_NivelH2OBajo);	}	else	{	ERR_delete(Error_NivelH2OBajo);		}
//	
//	// Variables Generales	
//	//if(EXPdata.UC.commonData1.fields.envTemp > 36) 	{	ERR_add(Err_SnsTempAmbienteAlarma);	}	else	{	ERR_delete(Err_SnsTempAmbienteAlarma);	}
//		
//	// RFID A determinar  	-	lo gestiona el HPCryo
////	if(RFIDGestionErrores[0] >= 3)	{	ERR_add(Err_ComRFID1);	RFIDGestionErrores[0] = 0;	}	else	{	ERR_delete(Err_ComRFID1);	}
////	if(RFIDGestionErrores[0] >= 3)	{	ERR_add(Err_ComRFID2);	RFIDGestionErrores[1] = 0;	}	else	{	ERR_delete(Err_ComRFID2);	}
////	if(RFIDGestionErrores[0] >= 3)	{	ERR_add(Err_ComRFID3);	RFIDGestionErrores[2] = 0;	}	else	{	ERR_delete(Err_ComRFID3);	}
////	if(RFIDGestionErrores[0] >= 3)	{	ERR_add(Err_ComRFID4);	RFIDGestionErrores[3] = 0;	}	else	{	ERR_delete(Err_ComRFID4);	}
//	
//	// TIMER	-	gestionarlo en el modulo (APP) que llama al rtc
////	if(Time2.Second == Time.Second)	{	ERR_add(Err_RTC);	}	else	{	ERR_delete(Err_RTC);	}
//
//	//Recorre los flags de los manipulos que indican los errores
////	uint8 i;
////	uint8 j;
////	tHPcryoData *HPptr;
////	tPRFdata *PRFptr;
////	for(i = PRF_HW_SLOT1; i <= PRF_HW_SLOT4; i++)
////	{
////		j = i-1;	//Factor de resta para el indexado de los errores, se sumará 0, 1, 2 ó 3 al error "inicial" para indexar al deseado en función del slot del manipulo.
////		if(HPcryoGetFromSlot(i, &HPptr, &PRFptr))
////		{
////			if(HPptr->frames.mainOut.data.avisos.bit_field.espera_vac == 1)			{	ERR_add(Err_TimeOutVacm1 + j);			}	else	{	ERR_delete(Err_TimeOutVacm1 - j);		}	// Espera del Vac
////			if(HPptr->frames.mainOut.data.avisos.bit_field.timeout == 1)			{	ERR_add(Err_ToutTempFinalTrat1 - j);	}	else	{	ERR_delete(Err_ToutTempFinalTrat1 - j);	}	// TimeOut Tiempo Tratamiento
////			if(HPptr->frames.mainOut.data.avisos.bit_field.seguridad_frio == 1)		{	ERR_add(Err_SeguridadFrioMan1 - j);		}	else	{	ERR_delete(Err_SeguridadFrioMan1 - j);	}	// Seguridad Frio
////			if(HPptr->frames.mainOut.data.avisos.bit_field.seguridad_frio == 1)		{	ERR_add(Err_PIDoff1 - j);				}	else	{	ERR_delete(Err_PIDoff1 - j);			}	// PID Off	
////			if(HPptr->frames.mainOut.data.avisos.bit_field.espera_temp == 1)		{	ERR_add(Err_ToutTempIniciTrart1 - j);	}	else	{	ERR_delete(Err_ToutTempIniciTrart1 - j);}	// Tiempo espera de temperatura	
////			if(HPptr->frames.mainOut.data.avisos.bit_field.temp_entrada == 1)		{	ERR_add(Err_TempEntradaAlta1 - j);		}	else	{	ERR_delete(Err_TempEntradaAlta1 - j);	}	// Temperatua de entrada alta
////			if(HPptr->frames.mainOut.data.avisos.bit_field.sonda_error == 1)		{	ERR_add(Err_NPltInsf1 - j);				}	else	{	ERR_delete(Err_NPltInsf1 - j);			}	// Sonda error	
////			if(HPptr->frames.mainOut.data.avisos.bit_field.vac == 1)				{	ERR_add(Err_TimeOutVacEstable1 - j);	}	else	{	ERR_delete(Err_TimeOutVacEstable1 - j);	}	// TimeOutEstable
////			if(HPptr->frames.mainOut.data.avisos.bit_field.temperatura == 1)		{	ERR_add(Err_ToutTempFinalTrat1 - j);	}	else	{	ERR_delete(Err_ToutTempFinalTrat1 - j);	}	// TempOutTempFinal
////			if(HPptr->frames.mainOut.data.avisos.bit_field.caudal_entrada == 1)		{	ERR_add(Err_CaudalimetroMan1 - j);		}	else	{	ERR_delete(Err_CaudalimetroMan1 - j);	}	// Error Caudalimetro
////		}
////	}
//}

void ERR_log_err_code(uint8 **Error_Log, uint8 *Log_index, uint8 Periferico)
{
	switch(Periferico)
	{
		case Manip1:	*Error_Log = ERR_data.HP1.Error_Log;			*Log_index = ERR_data.HP1.log_index;		break;
		case Manip2:	*Error_Log = ERR_data.HP2.Error_Log;			*Log_index = ERR_data.HP2.log_index;		break;
		case Manip3:	*Error_Log = ERR_data.HP3.Error_Log;			*Log_index = ERR_data.HP3.log_index;		break;
		case Manip4:	*Error_Log = ERR_data.HP4.Error_Log;			*Log_index = ERR_data.HP4.log_index;		break;
		case Maq:		*Error_Log = ERR_data.Machine.Error_Log;		*Log_index = ERR_data.Machine.log_index;	break;
		default: break;
	}
}

void ERR_set_secure_TRT (perif_to_manage HP)
{
	
}

//void ERR_logadd(uint32 error_code)
//{
//	uint8 i;	//Vble auxiliar contador
//	for(i=0;i<20;i++)
//	{
//		if(ERR_data.ErrorFired.ErrorFired_code[i] == error_code){	ERR_data.ErrorFired.Count[i]++;	}
//		else if(ERR_data.ErrorFired.ErrorFired_code[i] == 0){	ERR_data.ErrorFired.ErrorFired_code[i] = error_code;	ERR_data.ErrorFired.Count[i] = 1;	}
//	}
//}
