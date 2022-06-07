/*
 * AppGPRS.c
 *
 *  Created on: Mar 30, 2021
 *      Author: sguerrero
 */

/* - Librerias - */

#include "AppGPRS.h"
#include "GPRS.h"

/* - Definiciones - */

#define APP_GPRS_DIFFERENT_COUNTRY_CODES	251		//Numero de Codigos registrados de los distintos paises
#define APP_GPRS_MCC_NUM_CODES_FORBIDDEN	31		//Numero de Codigos de los paises donde no se puede aplicar el SAFE por temperatura
#define MAX_INTENTOS_DE_CONEXION 3					//Numero maximop de intentos de conexion consecutivas que debe dar para saltar el error

/*Lista paises con MCC*/
//typedef enum
//{
//	Greece,								//0001
//	Netherlands,						//0002
//	Belgium,							//0003
//	France,								//0004
//	Monaco,								//0005
//	Andorra,							//0006
//	Spain,								//0007
//	Hungary,							//0008
//	Bosnia_and_Herzegovina,				//0009	
//	Croatia,							//0010
//	Serbia,								//0011
//	Kosovo,								//0012
//	Italy,								//0013
//	Romania,							//0014
//	Switzerland,						//0015
//	Czech_Republic,						//0016
//	Slovakia,							//0017
//	Austria,							//0018
//	Guernsey,//(United Kingdom)			//0019
//	Isle_of_Man,//(United Kingdom)		//0020
//	Jersey,//(United Kingdom)			//0021
//	United_Kingdom,						//0022
//	//United_Kingdom
//	Denmark,//(Kingdom of Denmark)		//0023
//	Sweden,								//0024
//	Norway,								//0025
//	Finland,							//0026
//	Lithuania,							//0027
//	Latvia,								//0028
//	Estonia,							//0029
//	Russian_Federation,					//0030
//	Ukraine,							//0031
//	Belarus,							//0032
//	Moldova,							//0033
//	Poland,								//0034
//	Germany,							//0035
//	Gibraltar,//(United Kingdom)		//0036
//	Portugal,							//0037
//	Luxembourg,							//0038
//	Ireland,							//0039
//	Iceland,							//0040
//	Albania,							//0041
//	Malta,								//0042
//	Cyprus,								//0043
//	Georgia,							//0044
//	Armenia,							//0045
//	Bulgaria,							//0046
//	Turkey,								//0047
//	Faroe_Islands,//(Kingdom of Denmark)//0048
//	Abkhazia,							//0049
//	Greenland,//(Kingdom of Denmark)	//0050
//	San_Marino,							//0051
//	Slovenia,							//0052
//	North_Macedonia,					//0053
//	Liechtenstein,						//0054
//	Montenegro,							//0055
//	Canada,								//0056
//	Saint_Pierre_and_Miquelon,			//0057
//	Guam,//(United States of America)	//0058
//	Northern_Mariana_Islands,//(United States of America)	//0059
//	United_States_of_America,			//0060
//	//Guam,//(United States of America)
//	//United States of America
//	//United States of America
//	//United States of America
//	//United States of America
//	//United States of America
//	//United States of America
//	Puerto_Rico,						//0061
//	United_States_Virgin_Islands,		//0062
//	Mexico,								//0063
//	Jamaica,							//0064
//	Guadeloupe,//(France)				//0065
//	Martinique,//(France)				//0066
//	Saint_Barthélemy,//(France)			//0067
//	Saint_Martin,//(France)				//0068
//	Barbados,							//0069
//	Antigua_and_Barbuda,				//0070
//	Cayman_Islands,//(United Kingdom)	//0071
//	British_Virgin_Islands,//(United Kingdom)	//0072
//	Bermuda,							//0073
//	Grenada,							//0074
//	Montserrat,//(United Kingdom)		//0075
//	Saint_Kitts_and_Nevis,				//0076
//	Saint_Lucia,						//0077
//	Saint_Vincent_and_the_Grenadines,	//0078
//	Sint_Eustatius_and_Saba_Bonaire, 	//0079
//	Curaçao,							//0080
//	Sint_Maarten,						//0081
//	Aruba,								//0082
//	Bahamas,							//0083
//	Anguilla,//(United Kingdom)			//0084
//	Dominica,							//0085
//	Cuba,								//0085
//	Dominican_Republic,					//0087
//	Haiti,								//0088
//	Trinidad_and_Tobago,				//0089
//	Turks_and_Caicos_Islands,			//0090
//	Azerbaijan,							//0091
//	Kazakhstan,							//0092
//	Bhutan,								//0093
//	India,								//0094
//	//Indi
//	//India
//	Pakistan,							//0095
//	Afghanistan,						//0096
//	Sri_Lanka,							//0097
//	Myanmar,							//0098
//	Lebanon,							//0099
//	Jordan,								//0100
//	Syria,								//0101
//	Iraq,								//0102
//	Kuwait,								//0103
//	Saudi_Arabia,						//0104
//	Yemen,								//0105
//	Oman,								//0106
//	United_Arab_Emirates,				//0107
//	Israel,								//0108
//	Palestine,							//0109
//	Bahrain,							//0110
//	Qatar,								//0111
//	Mongolia,							//0112
//	Nepal,								//0113
//	Abu_Dhabi,//United_Arab_Emirates	//0114
//	Dubai,//United Arab Emirates		//0115
//	Iran,								//0116
//	Uzbekistan,							//0117
//	Tajikistan,							//0118
//	Kyrgyzstan,							//0119
//	Turkmenistan,						//0120
//	Japan,								//0121
//	//Japan
//	South_Korea,						//0122
//	Vietnam,							//0123
//	Hong_Kong_SAR,// (People's Republic of China)	//0124
//	Macau_SAR,//(People's Republic of China)		//0125
//	Cambodia,							//0126
//	Laos,								//0127
//	China,								//0128
//	//China
//	Taiwan,								//0129
//	North_Korea,						//0130 
//	Bangladesh,							//0131
//	Maldives,							//0132
//	Malaysia,							//0133
//	Australia,							//0134
//	Norfolk_Island,						//0135
//	Indonesia,							//0136
//	East_Timor,							//0137
//	Philippines,						//0138
//	Thailand,							//0139
//	Singapore,							//0140
//	Brunei,								//0141
//	New_Zealand,						//0142
//	Nauru,								//0143
//	Papua_New_Guinea,					//0144
//	Tonga,								//0145
//	Solomon_Islands,					//0146
//	Vanuatu,							//0147
//	Fiji,								//0148
//	Wallis_and_Futuna,					//0149
//	American_Samoa,//(United States of America)		//0150
//	Kiribati,							//0151
//	New_Caledonia,						//0152
//	French_Polynesia,//(France)			//0153
//	Cook_Islands,//(Pacific Ocean)		//0154
//	Samoa,								//0155
//	Federated_States_of_Micronesia,		//0156 
//	Marshall_Islands,					//0157
//	Palau,								//0158
//	Tuvalu,								//0159
//	Tokelau,							//0160
//	Niue,								//0161
//	Egypt,								//0162
//	Algeria,							//0163
//	Morocco,							//0164
//	Tunisia,							//0165
//	Libya,								//0166
//	Gambia,								//0167
//	Senegal,							//0168
//	Mauritania,							//0169
//	Mali,								//0170
//	Guinea,								//0171
//	Ivory_Coast,						//0172
//	Burkina_Faso,						//0173
//	Niger,								//0174
//	Togo,								//0175
//	Benin,								//0176
//	Mauritius,							//0177
//	Liberia,							//0178
//	Sierra_Leone,						//0179
//	Ghana,								//0180
//	Nigeria,							//0181
//	Chad,								//0182
//	Central_African_Republic,			//0183
//	Cameroon,							//0184
//	Cape_Verde,							//0185
//	Sao_Tome_and_Principe,				//0186
//	Equatorial_Guinea,					//0187
//	Gabon,								//0188
//	Congo,								//0189
//	Democratic_Republic_of_the_Congo,	//0190
//	Angola,								//0191
//	Guinea_Bissau,						//0192
//	Seychelles,							//0193
//	Sudan,								//0194
//	Rwanda,								//0195
//	Ethiopia,							//0196
//	Somalia,							//0197
//	Djibouti,							//0198
//	Kenya,								//0199
//	Tanzania,							//0200
//	Uganda,								//0201
//	Burundi,							//0202
//	Mozambique,							//0203
//	Zambia,								//0204
//	Madagascar,							//0205
//	French_Indian_Ocean_Territories,//(France)	//0206
//	Zimbabwe,							//0207
//	Namibia,							//0208
//	Malawi,								//0209
//	Lesotho,							//0210
//	Botswana,							//0211
//	Swaziland,							//0212
//	Comoros,							//0213
//	South_Africa,						//0214
//	Eritrea,							//0215
//	Ascension_and_Tristan_da_Cunha_Saint_Helena,	//0216 
//	South_Sudan,						//0217
//	Belize,								//0218
//	Guatemala,							//0219
//	El_Salvador,						//0220
//	Honduras,							//0221
//	Nicaragua,							//0222
//	Costa_Rica,							//0223
//	Panama,								//0224
//	Peru,								//0225
//	Argentina,							//0226
//	Brazil,								//0227
//	Chile,								//0228
//	Colombia,							//0229
//	Venezuela,							//0230
//	Bolivia,							//0231
//	Guyana,								//0232
//	Ecuador,							//0233
//	French_Guiana,//(France)			//0234
//	Paraguay,							//0235
//	Suriname,							//0236
//	Uruguay,							//0237
//	Falkland_Islands,//(United Kingdom)	//0238
//	British_Indian_Ocean_Territory,//(United Kingdom)	//0239
//	
//	GPRS_MCC_max_countrues
//};

const uint16 APP_GPRS_different_MCC [APP_GPRS_DIFFERENT_COUNTRY_CODES] = 
{
	202,	204,	206,	208,	212,	213,	214,	216,	218,	219,
	220,	221,	222,	226,	228,	230,	231,	232,	234,	234,
	234,	234,	235,	238,	240,	242,	244,	246,	247,	248,
	250,	255,	257,	259,	260,	262,	266,	268,	270,	272,
	274,	276,	278,	280,	282,	283,	284,	286,	288,	289,
	290,	292,	293,	294,	295,	297,	302,	308,	310,	310,
	310,	311,	311,	312,	313,	314,	315,	316,	330,	332,
	334,	338,	340,	340,	340,	340,	342,	344,	346,	348,
	350,	352,	354,	356,	358,	360,	362,	362,	362,	363,
	364,	365,	366,	368,	370,	372,	374,	376,	400,	401,
	402,	404,	405,	406,	410,	412,	413,	414,	415,	416,
	417,	418,	419,	420,	421,	422,	424,	425,	425,	426,
	427,	428,	429,	430,	431,	432,	434,	436,	437,	438,
	440,	441,	450,	452,	454,	455,	456,	457,	460,	461,
	466,	467,	470,	472,	502,	505,	505,	510,	514,	515,
	520,	525,	528,	530,	536,	537,	539,	540,	541,	542,
	543,	544,	545,	546,	547,	548,	549,	550,	551,	552,
	553,	554,	555,	602,	603,	604,	605,	606,	607,	608,
	609,	610,	611,	612,	613,	614,	615,	616,	617,	618,
	619,	620,	621,	622,	623,	624,	625,	626,	627,	628,
	629,	630,	631,	632,	633,	634,	635,	636,	637,	638,
	639,	640,	641,	642,	643,	645,	646,	647,	648,	649,
	650,	651,	652,	653,	654,	655,	657,	658,	659,	702,
	704,	706,	708,	710,	712,	714,	716,	722,	724,	730,
	732,	734,	736,	738,	740,	742,	744,	746,	748,	750,
	995
};

const uint16 APP_GPRS_Country_SAFE_temp_disable [APP_GPRS_MCC_NUM_CODES_FORBIDDEN] = 
 {
	214,											//SPAIN
	234, 235, 365, 995, 348, 346, 750, 266,		 	//UNITED KINGDOM
	272,											//IRELAND
	204,											//NETHERLAND
	262,											//GERMANY
	222,											//ITALY
	208, 742, 647, 547, 340,						//FRANCE
	460, 461, 										//CHINA
	440, 441,										//JAPAN
	310, 311, 312, 313, 314, 315, 316, 544			//USA
 };

/* - Estructuras - */

typedef struct
{
	uint16 MCC485[10];				//Valor almacenado del MCC
	uint16 MCCFlash[10];			//Valor de la flash
	uint8 TempSAFEpermissionFLASH;		//Permiso que tiene el equipo para aplicar o no el SAFE de temperatura
	uint8 TempSAFEpermission485;
	returnstatus_t GetMCCstatusFLASH;	//Estado del proceso de obtencion del MCC
	returnstatus_t GetMCCstatus485;
}sAppGPRSdata;

/* - Variables - */

sAppGPRSdata AppGPRSdata;
uint8 saveEnable;
uint16 reintentos_de_conexion;
uint8 placa_detectada;
uint8 senyal_detectada;

/* - Declaracion funciones locales - */

uint8 AppGPRSevaluateMCC (uint16 *MCC);
uint8 AppGPRSisValidCode(uint16 toCheck);

/* - Funciones globales - */

void AppGPRS_init (void)
{
	AppGPRSdata.MCC485[0] = 0;
	AppGPRSdata.MCC485[1] = 0;
	AppGPRSdata.MCC485[2] = 0;
	AppGPRSdata.MCC485[3] = 0;
	AppGPRSdata.MCC485[4] = 0;
	AppGPRSdata.MCC485[5] = 0;
	AppGPRSdata.MCC485[6] = 0;
	AppGPRSdata.MCC485[7] = 0;
	AppGPRSdata.MCC485[8] = 0;
	AppGPRSdata.MCC485[9] = 0;
	AppGPRSdata.MCCFlash[0] = 0;
	AppGPRSdata.MCCFlash[1] = 0;
	AppGPRSdata.MCCFlash[2] = 0;
	AppGPRSdata.MCCFlash[3] = 0;
	AppGPRSdata.MCCFlash[4] = 0;
	AppGPRSdata.MCCFlash[5] = 0;
	AppGPRSdata.MCCFlash[6] = 0;
	AppGPRSdata.MCCFlash[7] = 0;
	AppGPRSdata.MCCFlash[8] = 0;
	AppGPRSdata.MCCFlash[9] = 0;
	AppGPRSdata.TempSAFEpermissionFLASH = 0;
	AppGPRSdata.TempSAFEpermission485 = 0;
	AppGPRSdata.GetMCCstatusFLASH = IDLE;
	AppGPRSdata.GetMCCstatus485 = IDLE;
	saveEnable = 1;
	reintentos_de_conexion = 0;
	placa_detectada = 0;
	senyal_detectada = 2;
}

returnstatus_t AppGPRS_Connect_Get_MCC (void)
{
	//static uint32 ref_time = 0;
	AppGPRSdata.GetMCCstatusFLASH = IDLE;
	AppGPRSdata.GetMCCstatus485 = IDLE;
	
//	//#JM_GPRS
//	//de forma temporal, para no esperar los 5 minutos, obtenemos la info de la flash
//	AppGPRSdata.GetMCCstatusFLASH = GPRS_get_FLASH_MCC(AppGPRSdata.MCCFlash);		//Se lanza el proceso de obtencion del MCC
//	if(AppGPRSdata.GetMCCstatusFLASH == SUCCESS)
//	{
//		AppGPRSdata.TempSAFEpermissionFLASH = AppGPRSevaluateMCC (AppGPRSdata.MCCFlash);		//Una vez acabe y obtenga el MCC se procesa este mismo
//		if(AppGPRSdata.TempSAFEpermissionFLASH == 1)
//		{
//			AppGPRSdata.MCCFlash[0] += 1000;
//		}
//		else if(AppGPRSdata.TempSAFEpermissionFLASH == 0)
//		{
//			AppGPRSdata.MCCFlash[0] += 2000;
//		}
//		else
//		{
//			AppGPRSdata.TempSAFEpermissionFLASH = 0;
//			AppGPRSdata.MCCFlash[0] += 3000;
//		}
//		//Si tenemos datos en flash, el equipo debe tener placa
//		placa_detectada = 1;
//	}
//	else if(AppGPRSdata.GetMCCstatusFLASH == BLOCKING)
//	{
//		AppGPRSdata.TempSAFEpermissionFLASH = 0;
//		placa_detectada = 2;
//	}
//	//Si GPRS_get_FLASH_MCC devuelve error, significa que no tenemos datos válidos en flash
//	//end #JM_GPRS
	
//	AppGPRSdata.GetMCCstatus485 = GPRS_getMCC(AppGPRSdata.MCC485,saveEnable);		//Se lanza el proceso de obtencion del MCC
	
//	if(AppGPRSdata.GetMCCstatus485 == SUCCESS)
//	{
//		AppGPRSdata.TempSAFEpermission485 = AppGPRSevaluateMCC (AppGPRSdata.MCC485);		//Una vez acabe y obtenga el MCC se procesa este mismo
//		if(AppGPRSdata.TempSAFEpermission485 == 1)
//		{
//			AppGPRSdata.MCC485[0] += 1000;
//			senyal_detectada = 1;
//		}
//		else if(AppGPRSdata.TempSAFEpermission485 == 0)
//		{
//			AppGPRSdata.MCC485[0] += 2000;
//			senyal_detectada = 1;
//		}
//		else
//		{
//			AppGPRSdata.TempSAFEpermission485 = 0;
//			AppGPRSdata.MCC485[0] += 3000;
//			senyal_detectada = 0;
//		}
//		//Si la placa ha enviado datos, asumimos que está
//		placa_detectada = 1;
//		//La comunicacion ha ido bien. Ponemos a 0 el contador de reintentos
//		AppGPRS_clear_retry();
//	}
//	if(AppGPRSdata.GetMCCstatus485 == ERROR)
//	{
//		if(placa_detectada == 1 || placa_detectada == 2) //si tenemos datos o la maquina está configurada como con placa
//		{
//			AppGPRS_inc_retry();
//		}
//	}
	
	return AppGPRSdata.GetMCCstatus485;
}

returnstatus_t AppGPRS_GetMCCstatus (void)
{
	return AppGPRSdata.GetMCCstatus485;		//Devuelve el estado del proceso de obtencion del MCC
}

uint16 AppGPRS_GetMCCnum (uint8 sel) //0 = flash .. 1 = 485 
{
	if(sel == 0)
		return AppGPRSdata.MCCFlash[0];					//Devuelve el valor almacenado del MCC
	else
		return AppGPRSdata.MCC485[0];					//Devuelve el valor almacenado del MCC
}

uint8 AppGPRS_SAFE_permission (void)
{
//	if(AppGPRSdata.TempSAFEpermission485 != AppGPRSdata.TempSAFEpermissionFLASH)
//	{
//		GPRS_get_FLASH_MCC(AppGPRSdata.MCCFlash);
//		AppGPRSdata.TempSAFEpermission485 = AppGPRSevaluateMCC (AppGPRSdata.MCC485);
//		AppGPRSdata.TempSAFEpermissionFLASH = AppGPRSevaluateMCC (AppGPRSdata.MCCFlash);
//	}
//	if(AppGPRSdata.TempSAFEpermissionFLASH == 1 || AppGPRSdata.TempSAFEpermission485 == 1)
        return 1;	//Devuelve el flag que indica el permiso que se tiene para aplicar el SAFE de temperatura
//	else
//		return 0;
}

void AppGPRS_reset (void)
{
//	returnstatus_t ret;
//	uint8 count;
	
//	ret = IDLE;
//	count = 0;
	
//	while((ret != SUCCESS) && (count < 3))
//	{
//		ret = GPRS_reset();			//3 intentos para resetear el modulo
//		if(ret == SUCCESS)
//		{
//			AppGPRSdata.GetMCCstatus485 = IDLE;
//			AppGPRSdata.GetMCCstatusFLASH = IDLE;
//		}
// 		count++;
//	}
}

/* - Funciones locales - */

uint8 AppGPRSevaluateMCC(uint16 *MCC)
{
//	uint8 j,k,l,f;
//	//uint16 = flag;
//	f = 0;
//	l = 100;
	
//	for(j = 0; j < 10; j++)//recorremos los 10 códigos que nos puede enviar
//	{
//		if(MCC[j] > 99 && MCC[j] < 1000)//el código cumple el formato de un pais (tres dígitos)
//		{
//			//para ahorrar recorrer los vectores varias veces
//			if(j > 0) // el primero se tiene que hacer por fuerza
//			{
//				for(l = 0; l < j; l++)
//				{
//					if(MCC[j] == MCC[l])
//					{
//						//el MCC ya ha sido procesado
//						l = 100;
//					}
//				}
//			}
//			else
//			{
//				l = 0;
//			}
//			/**
//			 * J no puede valer nunca 100. Si vale 100 es que ha encontrado el código que hay que analizar, no es necesario volver a hacerlo
//			 * si vale menos, es que ha recorrido los ya existentes y no han coincidido. Se debe analizar el núevo código
//			 */
//			if(l != 100)
//			{
//				l = 100;
//				//for(i = 0; i < APP_GPRS_DIFFERENT_COUNTRY_CODES; i++)//recorrer los paises válidos
//				//{
//					//if(MCC[j] == APP_GPRS_different_MCC [i])//el codigo coincide con el de algun pais
//				switch(AppGPRSisValidCode(MCC[j]))
//					//if(AppGPRSisValidCode(MCC[j]) == 1) //si el código coincide con el de algún pais (versión burbuja)
//				{
//				case 0:
//					//el código no es valido
//					break;
//				case 1:
//					f = 1;
//					for(k=0; k<APP_GPRS_MCC_NUM_CODES_FORBIDDEN; k++)		//Al coincidir con algun valor valido, se comprueba si coincide con un valor de los paises donde no se puede aplicar
//					{
//						if(MCC[j] == APP_GPRS_Country_SAFE_temp_disable[k]) //Un pais detectado no acepta safe
//						{
//							MCC[0] = MCC[j];
//							return 0;
//						}
//					}
//					break;
//				case 2:
//					break;
//				case 3:
//					break;
//				}
////					{
////						f = 1;
////						for(k=0; k<APP_GPRS_MCC_NUM_CODES_FORBIDDEN; k++)		//Al coincidir con algun valor valido, se comprueba si coincide con un valor de los paises donde no se puede aplicar
////						{
////							if(MCC[j] == APP_GPRS_Country_SAFE_temp_disable[k]) //Un pais detectado no acepta safe
////							{
////								MCC[0] = MCC[j];
////								return 0;
////							}
////						}
////					}
//				//}
//			}
//		}
//	}
//	//flag == 1 => se ha encontrado al menos un pais válido. De todos los paises, ninguno impide SAFE
//	//flag == 0 => no había códigos de pais válidos. No se puede aplicar safe
//	//flag >1 => se ha encontrado al menos un pais válido. Uno de los paises no permite aplicar SAFE. El valor se guarda en MCC[0]
//	if(f == 1)
        return 1;
//	else
//		return 2;
	
	
//	/*if((MCC > 99) && (MCC < 1000))		//Los codigos MCC siempre 3 digitos
//	{
//		for(i=0; i<APP_GPRS_DIFFERENT_COUNTRY_CODES; i++)		//Se recorren todos los codigos validos y se comprueba que coincide con alguno
//		{
//			if(MCC == APP_GPRS_different_MCC [i])
//			{
//				flag = 1;
//				break;
//			}
//		}
		
//		if(flag == 0)	//Si no coincide con ninguno, lo ponemos a 0 (dandolo por invalido) (no permitimos que se aplique el SAFE de temperatura)
//		{
//			AppGPRSdata.MCC = 0;
//			ret = 0;
//		}
//		else
//		{
//			for(i=0; i<APP_GPRS_MCC_NUM_CODES_FORBIDDEN; i++)		//Al coincidir con algun valor valido, se comprueba si coincide con un valor de los paises donde no se puede aplicar
//			{
//				if(MCC == APP_GPRS_Country_SAFE_temp_disable[i])
//				{
//					ret = 0;
//					break;
//				}
//				else{ret = 1;}
//			}
//		}
//	}
//	else{ret = 0;}*/
	
//	//return ret;
}

uint8 AppGPRSisValidCode(uint16 toCheck)
{
	uint16 indice,min,max,i;
	min = 0;
	max = APP_GPRS_DIFFERENT_COUNTRY_CODES-1;
	indice = max / 2;
	
	if(toCheck < APP_GPRS_different_MCC[0] || toCheck > APP_GPRS_different_MCC[APP_GPRS_DIFFERENT_COUNTRY_CODES-1])
	{
		return 0;
	}
	while(min < max)
	{
		if(toCheck < APP_GPRS_different_MCC[indice])
		{
			max = indice -1;
			indice = min + (max - min)/2;
		}
		else if(toCheck > APP_GPRS_different_MCC[indice])
		{
			min = indice + 1;
			indice = min + (max - min)/2;
		}
		else if(toCheck == APP_GPRS_different_MCC[indice])
		{
			return 1;
		}
		if((max - min) <= 5)
		{
			for(i = min; i <= max; i++)
			{
				if(toCheck == APP_GPRS_different_MCC[i])
					return 1;
			}
			return 2;
		}
	}
	return 3;
}

void AppGPRSClear(uint8* conf, uint16* flashMCC, uint8 val)
{
//	GPRS_Clear_FLASH(conf,flashMCC,val);
//	saveEnable = 0;
}

void AppGPRS_inc_retry(void)
{
//	uint8 HPindex;
//	uint8 CountNoTRT;
//	CountNoTRT = 0;
//	tHPcryoData *HP;
//	tPRFdata *PRF;
//	if(reintentos_de_conexion < MAX_INTENTOS_DE_CONEXION)
//		reintentos_de_conexion++;
//	if(reintentos_de_conexion == MAX_INTENTOS_DE_CONEXION)
//	{
//		for(HPindex = 1; HPindex <= EXP_UC_NUM_HANDPIECES; HPindex++)	//Se recorren los 4 aplicadores
//		{
//			if(HPcryoGetFromSlot( HPindex, &HP, &PRF))					//Se comprueban si estan conectados
//			{
//				//HPstatus = HPcryoGetStatus(&HP, &PRF);
//				//HP_TRTstatus = HPcryoTrtStatus(&HP, &PRF);					//Se mira si el estado es fuera de tratamiento
//				if(HPcryoGetStatus(HP, PRF) != HP_CRYO_TREATMENT){CountNoTRT++;}
//				//if((HP_TRTstatus == HP_CRYO_TREATMENT_DONE) || (HP_TRTstatus == HP_CRYO_TREATMENT_FAIL)){CountNoTRT++;}
//			}
//			else{CountNoTRT++;}
//		}
		
//		if(CountNoTRT == EXP_UC_NUM_HANDPIECES)		//Si ningun aplicador esta en tratamiento
//		{
//			//Hacer saltar el error
//			//Hacer visible el icono
//			reintentos_de_conexion++;
//			ERR_add(Error_SinMemoriaParaPerif);
//		}
//	}
}

void AppGPRS_clear_retry(void)
{
	reintentos_de_conexion = 0;
}

uint8 AppGPRS_get_GPRS_board_detected(void)
{
//	if(placa_detectada == 0)
//		placa_detectada = GPRS_board_Answer();
	return placa_detectada;
}

uint8 appGPRS_get_signal(void)
{
	return senyal_detectada;
	//if(AppGPRSdata.GetMCCstatus485 == SUCCESS)
//	if(senyal_detectada < 2)
//	{
//		return senyal_detectada; //0 sin señal, 1 con señal
//	}
//	else
//	{
//		if(placa_detectada == 1 && reintentos_de_conexion < MAX_INTENTOS_DE_CONEXION)
//			return 2;
//		else
//			return 3;
//	}
}
