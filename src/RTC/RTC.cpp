
//Librerías
#include "RTC.h"

//Constantes
returnstatus_t status;

//Variables
LDD_TDeviceData *RTC_Structure;
LDD_TDeviceData *MyRTCPtr;

uint32 check_time_aux;
LDD_RTC_TTime previous_Time;

//Estructuras

//Funciones locales

//Funciones
returnstatus_t RTC_init (void)
{
//	RTC_Structure = HAL_RTC_Init((LDD_TUserData *)NULL, TRUE);		//Inicialización del DRIVER
//	check_time_aux = TICKS_GetTicks();								//Inicializar el tiempo auxiliar para la comprobación del funcionamiento del RTC
    status = SUCCESS;
    return status;
}

returnstatus_t RTC_start (void)
{
//	RTC_Structure = HAL_RTC_Init((LDD_TUserData *)NULL, FALSE);		//Inicialización del DRIVER
//	check_time_aux = TICKS_GetTicks();								//Inicializar el tiempo auxiliar para la comprobación del funcionamiento del RTC
	status = SUCCESS;
	return status;
}
	
returnstatus_t RTC_get_time (LDD_RTC_TTime *Time)
{
//	HAL_RTC_GetTime(MyRTCPtr, Time);				//Obtención del tiempo del RTC
	status = SUCCESS;
	return status;
}

returnstatus_t RTC_set_time (LDD_RTC_TTime *Time)
{
//	if (HAL_RTC_SetTime(MyRTCPtr, Time) == 0x00) status = SUCCESS;		//Establecer el tiempo del RTC
//	else status = ERROR;
	
    return SUCCESS; //status;
}

returnstatus_t RTC_running (void)
{
	LDD_RTC_TTime new_Time;			//Variable auxiliar para la comprobación del funcionamiento del RTC (el tiempo actual que me indica)
	
	status = RUNNING;								//El RTC se indica como que funciona correctamente hasta que se demuestre lo contrario
	
//	if((TICKS_DiffTicks(check_time_aux) < RTC_MAX_TIME_TO_CHECK)&&(TICKS_DiffTicks(check_time_aux) > RTC_MIN_TIME_TO_CHECK))		//Si ha pasado al menos 5 segundos desde la ultima vez que se entró en la comprobación del funcionamiento dle RTC, y menos de 55 segundos
//	{
//		HAL_RTC_GetTime(MyRTCPtr, &new_Time);						//Tomamos el tiempo actual que indica el RTC
//		if(previous_Time.Second == new_Time.Second)		status = ERROR;		//Comparamos el tiempo tomado previamente y el actual, si son iguales indica que hay un error con el RTC
//		else status = SUCCESS;
		
//		previous_Time.Second = new_Time.Second;						//Actualizamos el tiempo de referencia para la proxima comprobación
		
//		check_time_aux = TICKS_GetTicks();								//Actualizamos el tiempo auxiliar que cuenta tiempo entre veces que se entra en la comprobación
//	}
	return status;
}
