/*
 * RFID.c
 *
 *  Created on: Nov 20, 2018
 *      Author: ingenieria9
 */

#include "RFID.h"
#include "Buzzer/Buzzer.h"
//#include "Ticks/Ticks.h"

/*		DEBUG	-	Variables de contador de tiempo y veces que se entra en condicionantes
uint32 t_ref[10];
uint32 t_dif[10];
uint16 count = 0;
uint16 count3 = 0;
uint16 count4 = 0;
*/
//Variables
RFID_control_t  RFID_control;		//Estructura que engloba todas las variables de control del modulo RFID

//Funciones locales
/*
 * Función RFID_EnvioTramas
 * Descripción:
 *      Comunicación con el tag RFID
 * Parámetros:
 * 		- Nueva orden	-	nova_ordre_t nueva_orden
 * 		
 * 		- Puntero a los datos	-	uint8_t *ptu8Data
 * 		
 * 		- Tipo de manipulo	-	uint8 TypeHP
 * Retorno:
 *      - Estado del proceso	-	returnstatus_t
 * Errores:
 * 
 */
returnstatus_t RFID_EnvioTramas(nova_ordre_t nueva_orden, uint8_t *ptu8Data);

/*
 * Función calcpwd
 * Descripción:
 *      Realiza el calculo de los parametros necesarios para calcular la contraseña empleada para desencriptar los datos
 * Parámetros:
 * 		- Puntero a los datros recibidos para desencriptar	-	uint8_t ptudata[]
 * 		
 * 		- Puntero a cadena de caracteres con el modelo de la etiqueta RFID  que se desea leer	-	char modelo[]
 * Retorno:
 *      - Estado del proceso	-	returnstatus_t
 * Errores:
 * 
 */
returnstatus_t calcpwd(uint8_t ptudata[],  char *modelo, char *model_read);


//Funciones
void RFID_init (void)
{
	//Inicialización de Variables
	RFID_control.MotorRFIDSendFrame = 0;	
	RFID_control.RFID_resource_stat = RFID_FREE_TO_USE;
//	RFID_control.RFID_polling_time_aux = TICKS_GetTicks();		//Variable auxiliar de tiempo para la realización del polling
	RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
	memset(RFID_control.ptu8BufferDataRFID,0,sizeof(uint8_t)*180);//RFID_control.ptu8BufferDataRFID[180];
	RFID_control.RFID_label_detected = RFID_DETECTING_LABEL;
	
	RFID_free();
}

returnstatus_t RFID_motor (void)
{
	//Variables locales de la función
	returnstatus_t return_status;
	nova_ordre_t nueva_orden;
//	ordre_status_t estatordre_aux;
//	prot_mems_status_t MemsStatus;
	uint8_t u8EstatEsclau;
	uint8_t u8EsclauComdin1;
	uint8_t u8EsclauComdin2;
	
	return_status = IDLE;

//	//Comprobamos que el recurso (RFID) se encuentra disponible, y que desde la ultima vez que se hizo POLLING ha pasado más de 1 segundo
//	if((RFID_control.RFID_resource_stat == RFID_FREE_TO_USE) && (TICKS_DiffTicks(RFID_control.RFID_polling_time_aux) > RFID_TIME_POLLING_1SEG))		//En caso de que no esté siendo usado el RFID y desde la ultima vez que se entró en esta función (referencia de tiempo) ha pasado más de un segundo
//	{
//		RFID_control.RFID_polling_time_aux = TICKS_GetTicks();				//Actualizamos la referencia de tiempo
		
//		//Activo el polling
//		nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//		nueva_orden.fields.u8Memoria = RFID_MEMORY_SELECTION;
//		nueva_orden.fields.u32Addr = NULL;
//		nueva_orden.fields.u8NumBytes = NULL;
//		nueva_orden.fields.tipus_operacio = OPERACIO_POOLING;
//		nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_THREAD_100;
//		nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_RETRY_3;
		
//		RFID_control.ptu8BufferDataRFID[0] = 0x2;	//Dato a escribir (orden Lectura)
		
//		//Realizo la solicitud para comunicarme con la placa RFID, me quedo esperando hasta que me dan permiso
//		while(PROTMST_EncuaOrdre(RFID_SLOT_POS, nueva_orden, RFID_control.ptu8BufferDataRFID) != SUCCESS)	{	PROTMST_Motor();	}
		
		
//		estatordre_aux.value = 0;					//Variable de estado de la comunicación
		
//		while((estatordre_aux.value & 0xF0)==0)		//Mientras no haya nada en curso
//		{
//			PROTMST_Motor();
//			estatordre_aux = PROTMST_EstatOrdre(RFID_SLOT_POS, &MemsStatus, &u8EstatEsclau, &u8EsclauComdin1, &u8EsclauComdin2);
//		}

//		// Nota: Si hay errores de comunicación con la RFID. Hay que indicar un error. Realizar un AddError();
//		// Nota2: Se indica finalmente con el "return" si ha habido error o no, y ya desde fuera se procederá a indicar el aviso de error
//		if (estatordre_aux.bit_field.u8OrdreFinalitzada)
//		{
//			return_status = SUCCESS;
//		}
//		else
//		{
//			return_status = ERROR;
//		}
//	}
	return return_status;		//Devuelvo el estado final de la comunicación
}

/*
 * El proceso de lectura RFID es bloqueante desde fuera, el unico estado donde se puede salir del bucle es en el estado RFID_STAT_WAIT_READING
 * donde al realizar la lectura del modulo RFID nos indica que no hay presencia de ninguna tarjeta, por lo que se sale del bucle.
 * Para ello se emplea la variable RFID_control.RFID_label_detected, que puede tener 3 estados, en el estado de RFID_NO_LABEL_DETECTED
 * salimos y en la próxima vez que se gestione el update del manipulo con el recurso reservado, se volverá a intentar la lectura.
 */

uint32 T_erase_ref, T_erase_total, T_read2_ref, T_read2_total;		//DEBUG
uint32 T_erase_read2_total;											//DEBUG
returnstatus_t RFID_read_label (char *modelo, char *model_read, RFID_EraseAction EraseTarjetRFID, K70_RFID_CPU_ERR_tt *RFID_Error_code)
{
	//uint8 i; //DEBUG	-	variable auxiliar para bucles
//	ordre_status_t estat_ordre;
	nova_ordre_t nueva_orden;
	uint8 temp1, temp2;
	RFID_control.RFID_Error = RUNNING;
	*RFID_Error_code = K70_RFID_CPU_ERR_OK;
	
//	switch(RFID_control.esclau.u8Motor)
//	{
//		case RFID_STAT_INITIALIZE1:										//La inicialización se encarga de la liberación de cualquier trama que estuviera procesandose, se realiza esto previo a comenzar nuestra comunicación
//			//for (i = 0;i<10;i++) t_ref[i] = 0;		-	Referencia de tiempos e inicialización de los mismos para el control de tiempos de la lectura RFID
//			//for (i = 0;i<10;i++) t_dif[i] = 0;
//			//t_ref[0] = TICKS_GetTicks();
//			//t_ref[1] = TICKS_GetTicks();
			
//			RFID_control.RFID_Error = BLOCKING;
			
//			RFID_control.RFID_label_detected = RFID_DETECTING_LABEL;
			
//			nueva_orden.fields.tipus_operacio = OPERACIO_POOLING;
//			nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_1_RETRY;
//			nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_5_THREAD;
//			nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//			nueva_orden.fields.u8Memoria = RFID_MEMORY_SELECTION;
//			nueva_orden.fields.u8NumBytes = 0;
//			nueva_orden.fields.u32Addr = 0;
//			if(PROTMST_EncuaOrdre(RFID_SLOT_POS, nueva_orden, (void *)NULL) == SUCCESS)
//			{
//				RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE2;
//			}
//			else
//			{
//				PROTMST_Motor();
//				PROTMST_EstatOrdre
//				(
//						RFID_SLOT_POS,
//						&(RFID_control.esclau.prot_mems_status),
//						&(RFID_control.esclau.u8esclau_comodin1),
//						&(RFID_control.esclau.u8esclau_comodin1), 	/* comodin 1 */
//						&(RFID_control.esclau.u8esclau_comodin2)	/* comodin 2 */
//				);
//			}
//			break;
//		case RFID_STAT_INITIALIZE2:
//			if (RFID_control.Err_loop_count > RFID_NUM_MAX_LOOPS_ERR)
//			{
//				RFID_control.RFID_Error = ERROR;
//				*RFID_Error_code = K70_RFID_CPU_ERR_CANNOT_READ;
//			}
//			else{	RFID_control.RFID_Error = BLOCKING;	}
//			PROTMST_Motor();
//			estat_ordre = PROTMST_EstatOrdre
//			(
//					RFID_SLOT_POS,
//					&(RFID_control.esclau.prot_mems_status),
//					&(RFID_control.esclau.u8esclau_comodin1),
//					&(RFID_control.esclau.u8esclau_comodin1), 	/* comodin 1 */
//					&(RFID_control.esclau.u8esclau_comodin2)	/* comodin 2 */
//			);

//			if((estat_ordre.bit_field.u8OrdreFinalitzada == 1) && (estat_ordre.bit_field.u8ErrorComs == 0))
//			{
//				if(RFID_control.esclau.prot_mems_status.status == 0)
//				{
//					/* totes les memories estan en idle */
//					RFID_control.esclau.u8Motor = RFID_STAT_READING;
//					RFID_control.Err_loop_count = 0;
//				}
//				else
//				{
//					/* hi ha alguna memoria ocupada */
//					RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE3;
//				}
//			}
//			else if((estat_ordre.value&0xF0) != 0)
//			{
//				/* ha cancelat la placa o hi ha error coms */
//				RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//				RFID_control.Err_loop_count++;
//			}
//			break;
//		case RFID_STAT_INITIALIZE3:
//			RFID_control.RFID_Error = BLOCKING;
			
//			for(temp1 = 0; temp1 < 8; temp1++)
//			{
//				temp2 = (RFID_control.esclau.prot_mems_status.status)>>(2*temp1);
//				temp2 &= 0x03;
//				if(temp2 != 0)
//				{
//					break;
//				}
//			}
//			if(temp1 >= 8)
//			{
//				/* no hi ha cap memo ocupada */
//				RFID_control.esclau.u8Motor = RFID_STAT_READING;
//			}
//			else
//			{
//				if(temp2 == PROT_MEM_STAT_FINISHED || temp2 == PROT_MEM_STAT_ABORTED)
//				{
//					/* s'havia acabat/cancelat l'ordre, es pot continuar */
//					nueva_orden.fields.tipus_operacio = OPERACIO_POOLING;
//					nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_1_RETRY;
//					nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_5_THREAD;
//					nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//					nueva_orden.fields.u8Memoria = temp1;
//					nueva_orden.fields.u8NumBytes = 0;
//					nueva_orden.fields.u32Addr = 0;
//					if(PROTMST_EncuaOrdre(RFID_SLOT_POS, nueva_orden, (void *)NULL) == SUCCESS)
//					{
//						RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE2;
//					}
//				}
//				else
//				{
//					/* ordre en curs, vaig a cancelar */
//					nueva_orden.fields.tipus_operacio = OPERACIO_RESET;
//					nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_1_RETRY;
//					nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_5_THREAD;
//					nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//					nueva_orden.fields.u8Memoria = RFID_MEMORY_SELECTION;
//					nueva_orden.fields.u8NumBytes = 0;
//					nueva_orden.fields.u32Addr = 0;
//					if(PROTMST_EncuaOrdre(RFID_SLOT_POS, nueva_orden, (void *)NULL) == SUCCESS)
//					{
//						RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE2;
//					}
//				}
//			}
//			break;
	
//		case RFID_STAT_READING:														//ESCRIBIMOS LA SOLICITUD PARA LA COMUNICACIÓN CON EL "SLAVE"
//			//DEBUG
//			//if ( t_dif[1] == 0)
//			//{
//			//	t_dif[1] = TICKS_DiffTicks(t_ref[1]);		//Referencias de tiempos del proceso de lectura RFID
//			//	t_ref[2] = TICKS_GetTicks();
//			//}
//			//DEBUG
//			RFID_control.RFID_Error = BLOCKING;
			
//			nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//			nueva_orden.fields.u8Memoria = RFID_MEMORY_SELECTION;
//			nueva_orden.fields.u32Addr = 44;									//registro de acciones (escribo para realizar una lectura de la RFID)
//			nueva_orden.fields.tipus_operacio = OPERACIO_ESCRIPTURA;
//			nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_THREAD_100;
//			nueva_orden.fields.u8NumBytes = RFID_1_NUM_BYTES;
//			nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_1_RETRY;
	
//			RFID_control.ptu8BufferDataRFID[0] = 0x2;		//Dato a escribir	-	(orden de lectura)
	
//			switch(RFID_EnvioTramas(nueva_orden, RFID_control.ptu8BufferDataRFID))
//			{
//				case SUCCESS:
//					RFID_control.esclau.u8Motor = RFID_STAT_WAIT_READING;
//					RFID_control.RFID_tout_rep = 0;
//					break;
		
//				case ERROR:
//					RFID_control.esclau.accions.u16CodiError = K70_RFID_CPU_ERR_BASE;
//					RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//					RFID_control.RFID_Error = ERROR;
//					break;
		
//				case RUNNING:
//					RFID_control.RFID_Error = BLOCKING;
//					break;
					
//				default:		//ERROR
//					RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//					RFID_control.RFID_Error = ERROR;
//					*RFID_Error_code = K70_RFID_CPU_ERR_BASE;
//					break;
//			}
//			break;

//		case RFID_STAT_WAIT_READING:												//LEEMOS EL PERMISO PARA EL EMPLEO DEL "SLAVE"
//			//DEBUG
//			//if ( t_dif[2] == 0)
//			//{
//			//	t_dif[2] = TICKS_DiffTicks(t_ref[2]);		//Referencia de tiempos de los distintos procesos de la lectura RFID
//			//	t_ref[3] = TICKS_GetTicks();
//			//}
//			//DEBUG
//			RFID_control.RFID_Error = BLOCKING;

//			nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//			nueva_orden.fields.u8Memoria = RFID_MEMORY_SELECTION;
//			nueva_orden.fields.u32Addr = 65;
//			nueva_orden.fields.u8NumBytes = RFID_1_NUM_BYTES;
//			nueva_orden.fields.tipus_operacio = OPERACIO_LECTURA;
//			nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_THREAD_100;
//			nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_1_RETRY;
			
//			if (TICKS_DiffTicks(RFID_control.RFID_tout_w8_info) > RFID_TOUT_50MS_ERR_COM)
//			{
//				/*	DEBUG	-	Referencias de tiempospara calcular el tiempo desde que se comienza a preguntar por la lectura de una tarjeta hasta que indica error o hasta que lee
//				if (t_dif[9] == 0)
//				{
//					t_ref[9] = TICKS_GetTicks();
//					t_ref[8] = TICKS_GetTicks();
//				}
//				 */
//				switch(RFID_EnvioTramas(nueva_orden, RFID_control.ptu8BufferDataRFID))
//				{
//					case SUCCESS:
//						// Valor ok
//						if( RFID_control.ptu8BufferDataRFID[0] == 'o' )					//Se ha leido una tarjeta
//						{
//							//t_dif[8] = TICKS_DiffTicks(t_ref[8]);	//_DEBUG	-	Tiempo tardado desde la busqueda de una tarjetahatsa la lectura de una 'o'
//							RFID_control.esclau.u8Motor = RFID_STAT_START_READING;
//							RFID_control.RFID_label_detected = RFID_LABEL_DETECTED;
//						}
//						else															//No se detecta presencia de una tarjeta
//						{
//							RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//							RFID_control.RFID_label_detected = RFID_NO_LABEL_DETECTED;		//No se ha detectado la presencia de nada, por lo que salimos del bucle y ya se volverá a intentar de nuevo más adelante.
//							RFID_control.RFID_Error = IDLE;
//							//count3 ++;	//DEBUG	-	Contabiliza las veces que se sale por no haber detectado nada
//						}
//						break;
		
//					case ERROR:
//						//DEBUG
//						//t_dif[9] = TICKS_DiffTicks(t_ref[9]);	//DEBUG	-	tiempo desde que busca tarjeta hasta que da error
//						//count ++;								//DEBUG	-	Contabiliza el numero de veces que salta el error
//						//DEBUG
//						/* la RFID cuando esta leyendo de la tarjeta no contesta!!! */
//						RFID_control.RFID_label_detected = RFID_DETECTING_LABEL;			//Se indica que se ha detectado una tarjeta, se está leyendo, así que permanecemos en el bucle para completar la lectura
//						RFID_control.RFID_Error = BLOCKING;
//						RFID_control.RFID_tout_w8_info = TICKS_GetTicks();
//						RFID_control.RFID_tout_rep ++;
//						if (RFID_control.RFID_tout_rep > RFID_TOUT_MAX_REP)
//						{
//							RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//							RFID_control.RFID_Error = ERROR;
//							*RFID_Error_code = K70_RFID_CPU_ERR_CANNOT_READ;
//						}
//						break;
		
//					case RUNNING:
//						//count4++;	//DEBUG	-	Contador de veces que pasa por este estado
//						RFID_control.RFID_Error = BLOCKING;
//						break;
//					default:			//ERROR
//						RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//						RFID_control.RFID_Error = ERROR;
//						*RFID_Error_code = K70_RFID_CPU_ERR_BASE;
//						break;
//				}
//			}
//			break;

//		case RFID_STAT_START_READING:												//LEEMOS LOS DATOS RECOGIDOS POR EL MÓDULO RFID
//			//DEBUG
//			//if ( t_dif[3] == 0)
//			//{
//			//	t_dif[3] = TICKS_DiffTicks(t_ref[3]);
//			//	t_ref[4] = TICKS_GetTicks();
//			//}
//			//DEBUG
//			nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//			nueva_orden.fields.u8Memoria = RFID_MEMORY_SELECTION;
//			nueva_orden.fields.u32Addr = 66;
//			nueva_orden.fields.u8NumBytes = RFID_PAYLOAD_MAX_DATA_TRANSMISSION;	//64 de 178
//			nueva_orden.fields.tipus_operacio = OPERACIO_LECTURA;
//			nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_THREAD_200;
//			nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_1_RETRY;

//			//ptu8BufferDataRFID[0] = 0x2;

//			switch(RFID_EnvioTramas(nueva_orden, RFID_control.ptu8BufferDataRFID))
//			{
//				case SUCCESS:
//					RFID_control.esclau.u8Motor = RFID_STAT_START_READING1;
//					break;
	
//				case ERROR:
//					RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//					RFID_control.RFID_Error = ERROR;
//					*RFID_Error_code = K70_RFID_CPU_ERR_CANNOT_READ;
//					break;
	
//				case RUNNING:
//					RFID_control.RFID_Error = BLOCKING;
//					break;
//				default:			//ERROR
//					RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//					RFID_control.RFID_Error = ERROR;
//					*RFID_Error_code = K70_RFID_CPU_ERR_BASE;
//					break;
//			}
//			break;
//		case RFID_STAT_START_READING1:												//LEEMOS LOS DATOS RECOGIDOS POR EL MÓDULO RFID
//				nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//				nueva_orden.fields.u8Memoria = RFID_MEMORY_SELECTION;
//				nueva_orden.fields.u32Addr = 130;
//				nueva_orden.fields.u8NumBytes = RFID_PAYLOAD_MAX_DATA_TRANSMISSION;	//64 de 178 (2º paquete)
//				nueva_orden.fields.tipus_operacio = OPERACIO_LECTURA;
//				nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_THREAD_200;
//				nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_1_RETRY;

//				switch(RFID_EnvioTramas(nueva_orden, (uint8 *)(RFID_control.ptu8BufferDataRFID+RFID_PAYLOAD_MAX_DATA_TRANSMISSION)))	//Dirección en el buffer + 64 (primer paquete de información)
//				{
//					case SUCCESS:
//						RFID_control.esclau.u8Motor = RFID_STAT_START_READING2;
//						break;
		
//					case ERROR:
//						RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//						RFID_control.RFID_Error = ERROR;
//						*RFID_Error_code = K70_RFID_CPU_ERR_CANNOT_READ;
//						break;
		
//					case RUNNING:
//						RFID_control.RFID_Error = BLOCKING;
//						break;
//					default:			//ERROR
//						RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//						RFID_control.RFID_Error = ERROR;
//						*RFID_Error_code = K70_RFID_CPU_ERR_BASE;
//						break;
//				}
//				break;
//		case RFID_STAT_START_READING2:												//LEEMOS LOS DATOS RECOGIDOS POR EL MÓDULO RFID
//					nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//					nueva_orden.fields.u8Memoria = RFID_MEMORY_SELECTION;
//					nueva_orden.fields.u32Addr = 194;
//					nueva_orden.fields.u8NumBytes = RFID_PAYLOAD_DATA_TAIL_TRANSMISSION;		//50 de 178 (paquete de transmisión final)
//					nueva_orden.fields.tipus_operacio = OPERACIO_LECTURA;
//					nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_THREAD_200;
//					nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_1_RETRY;

//					//ptu8BufferDataRFID[0] = 0x2;

//					switch(RFID_EnvioTramas(nueva_orden, (uint8 *)(RFID_control.ptu8BufferDataRFID + (RFID_PAYLOAD_MAX_DATA_TRANSMISSION * 2))))		//Dirección en el buffer + 128 (64 + 64 (primer y segundo paquetes de información))
//					{
//						case SUCCESS:
//							RFID_control.esclau.u32TempsEntrePooling = TICKS_GetTicks();
//							RFID_control.esclau.u8Motor = RFID_STAT_CHECK_PASSWORD;
//							break;
			
//						case ERROR:
//							RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//							RFID_control.RFID_Error = ERROR;
//							*RFID_Error_code = K70_RFID_CPU_ERR_CANNOT_READ;
//							break;
			
//						case RUNNING:
//							RFID_control.RFID_Error = BLOCKING;
//							break;
//						default:			//ERROR
//							RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//							RFID_control.RFID_Error = ERROR;
//							*RFID_Error_code = K70_RFID_CPU_ERR_BASE;
//							break;
//					}
//					break;

//		case RFID_STAT_CHECK_PASSWORD:												//SE REALIZA EL DESENCRIPTADO DE LOS DATOS RECOGIDOS
//			//DEBUG
//			//if ( t_dif[4] == 0)
//			//{
//			//	t_dif[4] = TICKS_DiffTicks(t_ref[4]);
//			//	t_ref[5] = TICKS_GetTicks();
//			//}
//			//DEBUG
//			switch(calcpwd(RFID_control.ptu8BufferDataRFID, modelo, model_read))
//			{
//				case SUCCESS:
//					RFID_control.esclau.u8Motor = RFID_STAT_CHECK_MODELERASE;
//					break;
	
//				case ERROR:
//					RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//					RFID_control.RFID_Error = ERROR;					//En caso de que la etiqueta no fuera igual a la esperada se indica y se sale del proceso
//					*RFID_Error_code = K70_RFID_CPU_ERR_LABEL_INVALID;
//					RFID_control.RFID_label_detected = RFID_NO_LABEL_DETECTED;
//					break;
	
//				case RUNNING:
//					break;
//				default:			//ERROR
//					RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//					RFID_control.RFID_Error = ERROR;
//					*RFID_Error_code = K70_RFID_CPU_ERR_BASE;
//					break;
//			}

//			break;

//		case RFID_STAT_CHECK_MODELERASE:											//SE DECIDE SI BORRAR O NO LA ETIQUETA ACEPTADA
//			if( EraseTarjetRFID == RFID_ERASE_LABEL )
//			{
//				RFID_control.esclau.u8Motor = RFID_STAT_WRITE_RESULT;
//				T_erase_ref = TICKS_GetTicks();		//DEBUG
//			}
//			else	RFID_control.esclau.u8Motor = RFID_STAT_VALIDATE;				//en caso de no querer borrarla se valida y se sale del proceso
//			break;

//		case RFID_STAT_WRITE_RESULT:												//PARA BORRAR LA ETIQUETA SE SOBREESCRIBE
//			nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//			nueva_orden.fields.u8Memoria = RFID_MEMORY_SELECTION;
//			nueva_orden.fields.u32Addr = 44;
//			nueva_orden.fields.u8NumBytes = RFID_1_NUM_BYTES;
//			nueva_orden.fields.tipus_operacio = OPERACIO_ESCRIPTURA;
//			nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_THREAD_100;
//			nueva_orden.fields.u16MaxReintents = /*RFID_NUM_MAX_RETRY_3*/RFID_NUM_MAX_1_RETRY;

//			RFID_control.ptu8BufferDataRFID[0] = 0x3;

//			switch(RFID_EnvioTramas(nueva_orden, RFID_control.ptu8BufferDataRFID))
//			{
//				case SUCCESS:
//					RFID_control.esclau.u8Motor = RFID_STAT_WAIT_READING_RESULT;
//					RFID_control.RFID_tout_rep = 0;
//					T_erase_total = TICKS_DiffTicks(T_erase_ref);	//DEBUG
//					T_read2_ref = TICKS_GetTicks();					//DEBUG
//					break;
	
//				case ERROR:
//					RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//					RFID_control.RFID_Error = ERROR;
//					*RFID_Error_code = K70_RFID_CPU_ERR_CANNOT_ERASE;
//					break;
	
//				case RUNNING:
//					RFID_control.RFID_Error = BLOCKING;
//					break;
//				default:			//ERROR
//					RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//					RFID_control.RFID_Error = ERROR;
//					//*RFID_Error_code = K70_RFID_CPU_ERR_BASE;				//V7790 - RFID todos los errores a partir de validar la etiquta te permiten acceder a tratamiento
//					*RFID_Error_code = K70_RFID_CPU_ERR_CANNOT_ERASE;
//					break;
//			}
//			break;

//		case RFID_STAT_WAIT_READING_RESULT:											//SE VUELVE A LEER LA ETIQUETA PARA CONFIRMAR QUE SE HA BORRADO DE FORMA EXITOSA

//			nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//			nueva_orden.fields.u8Memoria = RFID_MEMORY_SELECTION;
//			nueva_orden.fields.u32Addr = 64;
//			nueva_orden.fields.u8NumBytes = RFID_1_NUM_BYTES;
//			nueva_orden.fields.tipus_operacio = OPERACIO_LECTURA;
//			nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_THREAD_100;  // Tout=  1.5 seg.
//			nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_1_RETRY;

//			if (TICKS_DiffTicks(RFID_control.RFID_tout_w8_info) > RFID_TOUT_50MS_ERR_COM)
//			{
//				switch(RFID_EnvioTramas(nueva_orden, RFID_control.ptu8BufferDataRFID))
//				{
//					case SUCCESS:
//						// Check comprobar
//						if(RFID_control.ptu8BufferDataRFID[0] == 'k')					//si se ha sobreescrito bien se continúa, si no se vuelve a repetir el proceso de borrado
//						{
//							RFID_control.esclau.u8Motor = RFID_STAT_VALIDATE;
//							T_read2_total = TICKS_DiffTicks(T_read2_ref);
//						}
//						else
//						{
//							RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//							RFID_control.RFID_Error = ERROR;
//							*RFID_Error_code = K70_RFID_CPU_ERR_CANNOT_ERASE;
//						}
//						break;
		
//					case ERROR:
//						RFID_control.RFID_Error = BLOCKING;
//						RFID_control.RFID_tout_w8_info = TICKS_GetTicks();
//						RFID_control.RFID_tout_rep ++;
//						if (RFID_control.RFID_tout_rep > RFID_TOUT_MAX_REP)
//						{
//							RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//							RFID_control.RFID_Error = ERROR;
//							*RFID_Error_code = K70_RFID_CPU_ERR_CANNOT_READ_ERASED;
//						}
//						break;
		
//					case RUNNING:
//						RFID_control.RFID_Error = BLOCKING;
//						break;
//					default:			//ERROR
//						RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//						RFID_control.RFID_Error = ERROR;
//						//*RFID_Error_code = K70_RFID_CPU_ERR_BASE;				//V7790 - RFID todos los errores a partir de validar la etiquta te permiten acceder a tratamiento
//						*RFID_Error_code = K70_RFID_CPU_ERR_CANNOT_READ_ERASED;
//						break;
//				}
//			}
//			break;

//		case RFID_STAT_VALIDATE :														//FINALMENTE SE VALIDA EL PROCESO INDICANDO QUE YA SE HA TERMINADO DE FORMA EXITOSA
//			//DEBUG
//			//if ( t_dif[5] == 0){	t_dif[5] = TICKS_DiffTicks(t_ref[5]);	}
//			//DEBUG
//			RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//			RFID_control.RFID_Error= SUCCESS;
//			*RFID_Error_code = K70_RFID_CPU_ERR_OK;
//			RFID_control.RFID_label_detected = RFID_LABEL_DETECTED;
//			T_erase_read2_total = TICKS_DiffTicks(T_erase_ref);		//DEBUG
//			//t_dif[0] = TICKS_DiffTicks(t_ref[0]);		//DEBUG	-	Contador de tiempo de todo el proceso
//			break;

//		default:
//			//ERROR
//			RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
//			RFID_control.RFID_Error = ERROR;
//			*RFID_Error_code = K70_RFID_CPU_ERR_BASE;
//			RFID_control.RFID_label_detected = RFID_NO_LABEL_DETECTED;
//			break;
//	}
	return RFID_control.RFID_Error;
}


RFID_block_or_free_t RFID_lock (void)
{
	if (RFID_control.RFID_resource_stat == RFID_FREE_TO_USE)		RFID_control.RFID_resource_stat = RFID_NOW_IN_USE;		//Si el recurso está libre y me solicitan bloquearlo, devuelvo un "RFID_NOW_IN_USE"
	else	RFID_control.RFID_resource_stat = RFID_ALREADY_IN_USE;															//En caso de que me soliciten bloquearlo y ya esté siendo usado, devolveré "RFID_ALREADY_IN_USE"
	
	return RFID_control.RFID_resource_stat;
}

RFID_block_or_free_t RFID_free (void)
{
	RFID_control.RFID_resource_stat = RFID_FREE_TO_USE;		//Si ya no está en proceso ninguna comunicación, se libera el recurso
	RFID_control.esclau.u8Motor = RFID_STAT_INITIALIZE1;
	RFID_control.Err_loop_count = 0;
	return RFID_control.RFID_resource_stat;
}

uint8 RFID_label_detection(void)
{
	return RFID_control.RFID_label_detected;
}

RFID_estats_t RFID_getStatus( void)
{
	return RFID_control.esclau.u8Motor;
}

returnstatus_t RFID_EnvioTramas(nova_ordre_t nueva_orden, uint8_t *ptu8Data)
{
    returnstatus_t valor_retorno;
//    static ordre_status_t estatordre;
//    prot_mems_status_t MemsStatus;
    uint8_t u8EstatEsclau;
    uint8_t u8EsclauComdin1;
    uint8_t u8EsclauComdin2;
    valor_retorno = RUNNING;

//    while (valor_retorno == RUNNING)
//    {
//		switch (RFID_control.MotorRFIDSendFrame)
//		{
//			case 0:
//				if( PROTMST_EncuaOrdre(RFID_SLOT_POS, nueva_orden, ptu8Data) == SUCCESS)		RFID_control.MotorRFIDSendFrame++;					//El motor del envio tramas no avanza hasta que no acepten la solicitud de comunicación
//				break;
				
//			case 1:
//				estatordre = PROTMST_EstatOrdre(RFID_SLOT_POS, &MemsStatus, &u8EstatEsclau, &u8EsclauComdin1, &u8EsclauComdin2);		//Se procede a realizar la comunicación hasta que se finalice
//				if((estatordre.value & 0xF0) != 0)		//Si se ha finalizado por cualquier motivo (cancelación, exito, etc.)
//				{
//					if(estatordre.bit_field.u8OrdreFinalitzada && !estatordre.bit_field.u8ErrorComs)			valor_retorno = SUCCESS;				//Si nos indica que se ha finalizado con exito, devolvemos un mensaje de SUCCESS
//					else																						valor_retorno = ERROR;					//En caso contrario uno de ERROR
					
//					RFID_control.MotorRFIDSendFrame = 0;
//				}
//				break;
	
//			default:
//				RFID_control.MotorRFIDSendFrame = 0;
//				valor_retorno = ERROR;	//ERROR
//				break;
//		}
//		PROTMST_Motor();
//    }
    
    return valor_retorno;    
}


returnstatus_t calcpwd(uint8_t ptudata[], char *modelo, char *model_read)
{      
	returnstatus_t valor_retorno= RUNNING;
	
	//Se realiza la conversión de los datos leidos por RFID para poder obtener el código de la etiqueta leida
	
	char a=0x55, b=0xAA, c=0xA5, d=0x5A;     
	char PSWD[4]; 
	char PACK[2];
	
	char modelo2[2];
			  
	PSWD[0] = ptudata[16 + ((ptudata[4] ^ a) & 0x7f)] ^ a;
	PSWD[1] = ptudata[16 + ((ptudata[5] ^ b) & 0x7f)] ^ b;
	PSWD[2] = ptudata[16 + ((ptudata[6] ^ c) & 0x7f)] ^ c;
	PSWD[3] = ptudata[16 + ((ptudata[7] ^ d) & 0x7f)] ^ d;
	
	PACK[0] = ptudata[176];
	PACK[1] = ptudata[177];
	
	modelo2[0] = PACK[0]^PSWD[2];
	modelo2[1] = PACK[1]^PSWD[3];

	//Si el modelo leido coincide con el modelo que nos han pasado como el que se busca, devolvemos SUCCESS, en caso contrario devolvemos ERROR
	if((modelo2[0] == modelo[0]) && (modelo2[1] == modelo[1])) valor_retorno = SUCCESS;
	else valor_retorno = ERROR;
	
	model_read[0] = modelo2[0];	//El modelo que se lee se devuelve también
	model_read[1] = modelo2[1];
			 
	return valor_retorno;
}

uint8 RFID_GetFWversion (void)
{
//	ordre_status_t estat_ordre;			//PROTMST vble
	nova_ordre_t nueva_orden;			//PROTMST & Envio tramas vble
	uint8_t *ptu8Data;					//Envio tramas vble
	returnstatus_t envio_estat;			//Envio tramas vble
	uint8_t RFID_Motor_GetFWversion;	//Motor para initialize
	uint8 temp1, temp2;					//Initialize vble
	
	uint8 return_value;		//Valor de retorno de la función
	
	uint8 Err_loop_count = 0;							//Contador de error para initialize
	RFID_Motor_GetFWversion = RFID_STAT_INITIALIZE1;	//Primer estado para initialize
	uint8 RFID_init = 0;								//Initialize no completada
	
//	while(!RFID_init)	//Mientras no se haya completado el initialize
//	{
//		switch(RFID_Motor_GetFWversion)
//		{
//		case RFID_STAT_INITIALIZE1:										//La inicialización se encarga de la liberación de cualquier trama que estuviera procesandose, se realiza esto previo a comenzar nuestra comunicación
	
//			nueva_orden.fields.tipus_operacio = OPERACIO_POOLING;
//			nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_1_RETRY;
//			nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_5_THREAD;
//			nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//			nueva_orden.fields.u8Memoria = RFID_MEMORY_SELECTION;
//			nueva_orden.fields.u8NumBytes = 0;
//			nueva_orden.fields.u32Addr = 0;
//			if(PROTMST_EncuaOrdre(RFID_SLOT_POS, nueva_orden, (void *)NULL) == SUCCESS)
//			{
//				RFID_Motor_GetFWversion = RFID_STAT_INITIALIZE2;
//			}
//			else
//			{
//				PROTMST_Motor();
//				PROTMST_EstatOrdre
//				(
//						RFID_SLOT_POS,
//						&(RFID_control.esclau.prot_mems_status),
//						&(RFID_control.esclau.u8esclau_comodin1),
//						&(RFID_control.esclau.u8esclau_comodin1), 	/* comodin 1 */
//						&(RFID_control.esclau.u8esclau_comodin2)	/* comodin 2 */
//				);
//			}
//			break;
//		case RFID_STAT_INITIALIZE2:
//			if (Err_loop_count > RFID_NUM_MAX_LOOPS_ERR)
//			{
//				return_value = 0;	//Error de initialize, salimos devolviendo 0
//				return 0;
//			}
			
//			PROTMST_Motor();
//			estat_ordre = PROTMST_EstatOrdre
//			(
//					RFID_SLOT_POS,
//					&(RFID_control.esclau.prot_mems_status),
//					&(RFID_control.esclau.u8esclau_comodin1),
//					&(RFID_control.esclau.u8esclau_comodin1), 	/* comodin 1 */
//					&(RFID_control.esclau.u8esclau_comodin2)	/* comodin 2 */
//			);
	
//			if((estat_ordre.bit_field.u8OrdreFinalitzada == 1) && (estat_ordre.bit_field.u8ErrorComs == 0))
//			{
//				if(RFID_control.esclau.prot_mems_status.status == 0)
//				{
//					/* totes les memories estan en idle */
//					RFID_init = 1;			//Initialize completado
//					Err_loop_count = 0;
//				}
//				else
//				{
//					/* hi ha alguna memoria ocupada */
//					RFID_Motor_GetFWversion = RFID_STAT_INITIALIZE3;
//				}
//			}
//			else if((estat_ordre.value&0xF0) != 0)
//			{
//				/* ha cancelat la placa o hi ha error coms */
//				RFID_Motor_GetFWversion = RFID_STAT_INITIALIZE1;
//				Err_loop_count++;
//			}
//			break;
//		case RFID_STAT_INITIALIZE3:
			
//			for(temp1 = 0; temp1 < 8; temp1++)
//			{
//				temp2 = (RFID_control.esclau.prot_mems_status.status)>>(2*temp1);
//				temp2 &= 0x03;
//				if(temp2 != 0)
//				{
//					break;
//				}
//			}
//			if(temp1 >= 8)
//			{
//				/* no hi ha cap memo ocupada */
//				RFID_init = 1;		//Initialize completado
//				Err_loop_count = 0;
//			}
//			else
//			{
//				if(temp2 == PROT_MEM_STAT_FINISHED || temp2 == PROT_MEM_STAT_ABORTED)
//				{
//					/* s'havia acabat/cancelat l'ordre, es pot continuar */
//					nueva_orden.fields.tipus_operacio = OPERACIO_POOLING;
//					nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_1_RETRY;
//					nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_5_THREAD;
//					nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//					nueva_orden.fields.u8Memoria = temp1;
//					nueva_orden.fields.u8NumBytes = 0;
//					nueva_orden.fields.u32Addr = 0;
//					if(PROTMST_EncuaOrdre(RFID_SLOT_POS, nueva_orden, (void *)NULL) == SUCCESS)
//					{
//						RFID_Motor_GetFWversion = RFID_STAT_INITIALIZE2;
//					}
//				}
//				else
//				{
//					/* ordre en curs, vaig a cancelar */
//					nueva_orden.fields.tipus_operacio = OPERACIO_RESET;
//					nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_1_RETRY;
//					nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_5_THREAD;
//					nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;
//					nueva_orden.fields.u8Memoria = RFID_MEMORY_SELECTION;
//					nueva_orden.fields.u8NumBytes = 0;
//					nueva_orden.fields.u32Addr = 0;
//					if(PROTMST_EncuaOrdre(RFID_SLOT_POS, nueva_orden, (void *)NULL) == SUCCESS)
//					{
//						RFID_Motor_GetFWversion = RFID_STAT_INITIALIZE2;
//					}
//				}
//			}
//			break;
			
//		default: break;
//		}
//	}
	
//	nueva_orden.fields.u8AddrEsclau = RFID_SLAVE_ADDRESS;			//101
//	nueva_orden.fields.u8Memoria = RFID_MEMORY_SELECTION;			//0
//	nueva_orden.fields.u32Addr = 4;
//	nueva_orden.fields.tipus_operacio = OPERACIO_LECTURA;			//1
//	nueva_orden.fields.u16TimeoutTrama = RFID_TIME_OUT_THREAD_100;	//100
//	nueva_orden.fields.u8NumBytes = RFID_1_NUM_BYTES;				//1
//	nueva_orden.fields.u16MaxReintents = RFID_NUM_MAX_RETRY_5;		//5
	
//	envio_estat = RFID_EnvioTramas(nueva_orden, ptu8Data);		//Enviamos la solicitud de lectura del byte que contiene la versión FW
	
	if(envio_estat == SUCCESS)
	{
		return_value = ptu8Data[0];		//Si se lee correctamente se devuelve
	}
	else
	{
		return_value = 0;				//Si ha habido algún problema se devuelve 0
	}
		
	return return_value;
}
