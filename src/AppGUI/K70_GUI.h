/*
 * Libreria             -       Graphic User Interface (GUI)
 * PCB                  -       CoreK70
 * Versión              -       1.00
 * Fecha compilación    -       xx/xx/2016
 * 
 * Descripción:
 *      El objetivo de esta librería es aportar las herramientas necesarias para la creación de interfaces gráficas que 
 *      permiten la comunicación entre el usuario y el equipo. 
 *      La interfaz se divide en diferentes pantallas y estas en diferentes capas que permiten crear transparencias 
 *      entre imágenes. Los elementos que permiten crear las diferentes pantallas son los widgets y pueden ser de los 
 *      siguientes tipos: Botón, interruptor, visor de imagen, visor numérico, ventana emergente y timer (falta programar).
 *      Esta libreria requiere que el archivo que contiene todas las imágenes necesarias para crear la interfaz en 
 *      formato CCN (pack.ccn), el archivo del índice de estas imágenes (pack.lut) y el archivo con la definición de la 
 *      interfaz (interface.csv) estén grabados en la nandFlash. Por ahora para poder grabar las imágenes en la nandFlash 
 *      hay que copiarlas previamente desde un USB.
 *      A través de esta librería también se puede controlar el back light de la pantalla, ya que esta enmascara la llamada a 
 *      la función de control del back light de la librería GFX.
 *      También es posible crear interfaces con un fondo de color sólido sin necesidad de añadir una imagen de ese color.
 *      Es posible cambiar las características de los widgets mediante las funciones apropiadas y que los widgets botón, 
 *      pulsador y ventana emergente realicen funciones al ser pulsadas o soltadas (callbacks). 
 *      Para usar esta libreria es necesario compilar también la librería K70_GFX.h y la librería K70_CCN.h.
 *      Esta librería no está pensada para entornos multitarea ni protegida con mutex.
 *      
 * Compilacion:
 *      Para utilizar esta librería en una aplicación hay que configurar las propiedades del proyecto de la aplicación 
 *      tal como se describe a continuación:
 *      - En:           "C/C++ Build - Settings - ARM Ltd Windows GCC C Compiler - Directories"
 *        Añadir:       "${SystemDrive}\libK70\libCoreK70\Headers"
 *      - En:           "C/C++ Build - Settings - ARM Ltd Windows GCC C Linker - Miscellaneous - Other objects"
 *        Añadir:       "${SystemDrive}/libK70/libCoreK70/Debug/libCoreK70_GFX.a"
 *      - En:           "C/C++ Build - Settings - ARM Ltd Windows GCC C Linker - Miscellaneous - Linker flags"
 *        Añadir:       "--start-group "${SystemDrive}/libK70/libCoreK70/Debug/libCoreK70_GFX.a" -Xlinker --end-group"
 *      - En:           "C/C++ Build - Settings - ARM Ltd Windows GCC C Linker - Linker Order"
 *        Subir "${SystemDrive}/libK70/libCoreK70/Debug/libCoreK70_GFX.a" a la primera posición 
 *      
 * Uso:
 * 		FALTAAAA!!
 * 		
 * 		
 * 		1) LLamar a la función GFXinit() para inicializar la librería. A esta función también hay que pasarle el tipo de
 * 		compresión que se va a utilizar y los punteros a los archivos .LUT (archivo con el índice de las imágenes) y al 
 * 		.CCN (archivo con las imágenes comprimidas).
 * 		2) LLamar a la función GFXconfigScreen() para configurar si se quiere pintar el fondo de un color sólido si no se
 * 		dispone de una imagen que ocupe toda la pantalla.
 * 		3) Si se quiere modificar el back light se debe llamar a la función GFXbackL().
 * 		4) Para crear una escena, hay que llamar a la función GFXinitScene() e indicar el número de capas que va a tener
 * 		la escena.
 * 		5) Luego ya podemos añadir las capas que queremos usar con la función GFXaddLayer() y añadir los iconos en la capa
 * 		con la función GFXaddIcon().
 * 		6) Para configurar las diferentes características de los iconos hay que usar las funciones: GFXconfigVisibility(),
 * 		GFXconfigPosition() y GFXconfigImage().
 * 		7) Para eliminar los iconos, las capas y la escena, hay que llamar a las funciones GFXremoveIcon(), GFXremoveLayer()
 * 		y GFXremoveScene() respectivamente.
 * 		8) Si se quiere refrescar la pantalla hay que llamar a la función GFXrefresh().
 * 		9) Por último llamar a la función GFXfinish() para finalizar la librería.
 *      
 * Ejemplo:
 *      Hay una demostración de todas las funciones de la librería en el proyecto: Demo_CoreK70_GUI.       
 *      
 */  

#ifndef GUI_H_
#define GUI_H_

#include "GeneralDefines.h"
//#include  "../DDR/DDR.h"

/*Esta constante está delante de la definición de tipos porque se necesita para la estructura del visor de imagen*/
#define GUInumVimg 12/*Número de imagenes diferentes a mostrar en el visor numérico(set de números del 0-9, 
 *el signo menos(-) y el signo de separación decimal( . ó ,)*/


//#define NUM_MANIPULOS 4 // Número de manipulos.


/* - Definicion de tipos */
/*- 	Estructura rectangulo*/
typedef struct { 
	
	uint16	posx;
	uint16	posy;
	uint16	w;
	uint16 	h;
	
}GUIstRect;

typedef struct{
	
	uint32	idImg;
	void 	*ptrImg;
	
}GUIstImagen;


typedef struct{
	
	GUIstRect areaTS;
	GUIstImagen imgTS;
	
}stTS;






/*-		Estructura pulsación pantalla táctil*/

/*-		Estructura común para todos los widgets*/
typedef struct{
	uint32 	id; 			//Id del widget, no se debe repetir
	uint8	screen; 		//Pantalla en la que está situado el widget, el valor de la pantalla tiene que empezar por 0 y seguir en orden
	uint8 	widgetType; 	/*Tipo de widget: 1=botón, 2=interruptor, 3=visor de imagen, 4=visor numérico, 5=ventana emergente y 
							timer=falta por programar*/
	void* 	stWidgetType; 	//Estructura especifica de cada tipo de widget
	uint8	exist; 			//Indica si tenemos que tener en cuenta el widget
	uint8	existAnt; 		//Variable auxiliar para controlar la existencia del icono.
	uint8 	enable; 		//Variable que indica si el widget está tipo marca de agua (idle) pero se muestra por pantalla
	uint8 	visible; 		//Indica si el widget es visible
	uint8	posLayer; 		//Indica en que capa del GFX está situado el widget (para hacer correctamente las transparencias)
	uint8 	needRefresh;	/*Indica si es necesario refrescar la imagen que se muestra en pantalla.
							0:No hay que refrescar 1:Hay que refrescar*/
	uint8	visAnt; 		//Variable auxiliar para controlar la visibilidad del icono en pantalla.
	void (*cbkUpdate)();	//Puntero a la función de actualización del widget
	void (*cbkRefresh)(); 	//Puntero a la función de refresco del widget
}stWidget;

/*-		Estructura del widget botón*/
typedef struct{
	
	uint8	prsRls; 			//Botón pulsado o no pulsado: 0=released, 1=press
	uint8	state; 			//Estado en la máquina de estados del update del botón
	uint32 	idIco; 		//Id interno del icono del botón
	uint32	idImgPrs; 	//Id para el archivo LUT de la imagen pulsada
	uint32	idImgRls; 	//Id para el archivo LUT de la imagen no pulsada
	uint32	timer; 		//Falta definir como será este timer para la pulsación continuada
	stTS	TS; 				//Imagen y area táctil del botón
	/*Callbbacks del botón*/
	void (*cbkPrs)(void*); 	//Callback para el botón pulsado
	void (*cbkRls)(void*); 	//Callback para el botón no pulsado
	void (*cbkCon)(void*); 	//Callback para la pulsación continuada
	/*Posiciones de las imagenes*/
	uint16	posxImgPrs;	
	uint16	posyImgPrs;
	uint16	posxImgRls;
	uint16	posyImgRls;
	
}stButton;	

/*-		Estructura del widget interruptor*/
typedef struct{
	uint8	prsRls; 		//Interrutor pulsado o no pulsado: 0=released, 1=press
	uint8	onOff; 			//Interruptor on o off: 0=off, 1=on
	uint8	state; 			//Estado en la máquina de estados del update del interruptor
	uint32 	idIco; 			//Id interno del icono del interruptor
	uint32	idImgOn; 		//Id para el archivo LUT del interruptor on
	uint32	idImgOff; 		//Id para el archivo LUT del interruptor off
	uint32	idImgPrsOn; 	//Id para el archivo LUT al pulsar el interruptor para on
	uint32	idImgPrsOff;	//Id para el archivo LUT al pulsar el interruptor para off
	stTS	TS; 				//Imagen y area táctil del interruptor
	/*Callbacks del interruptor*/
	void (*cbkOn)(void*); 		//Callback para el interruptor on
	void (*cbkOff)(void*); 		//Callback para el interruptor off
	/*Posiciones de las imagenes*/
	uint16	posxImgOn;
	uint16	posyImgOn;
	uint16	posxImgOff;
	uint16	posyImgOff;
	uint16	posxImgPrsOn;
	uint16	posyImgPrsOn;
	uint16	posxImgPrsOff;
	uint16	posyImgPrsOff;
}stSwitch;

/*-		Estructura del widget visor de imagen*/
typedef struct{
	uint32	idIco;	//Id interno del icono del visor numérico
	uint32	idImg;	//Id para el archivo LUT de la imagen a mostrar
	/*Posición de la imagen*/
	uint16	posx;
	uint16	posy;
}stImgViewer;



/*-		Estructura del widget visor numérico*/
typedef struct{
	/*Características de la imagen de fondo del visor numérico*/
	
	float  numAnter;
	
	uint32	idIcoImgVwr;	//Id interno del icono de la imagen de fondo
	uint8	imgVwrOn;		//Indica si el visor numérico tiene imagen de fondo: 0=No tiene fondo, 1=Tiene fondo
	uint16	posxImgVwr;		
	uint16	posyImgVwr;
	uint16	wImgVwr;
	uint16	hImgVwr;
	
	uint32	idImgVwr;		//Id para el archivo LUT de la imagen a mostrar en el fondo
	/*Características de los dígitos del visor numérico*/
	uint8	posLayerDig;	//Indica en que capa del GFX estan situados los dígitos (para hacer correctamente las transparencias)
	uint8	iDigit; 		//Número de dígitos del visor
	uint16	sepDig; 		//Distancia entre dígitos en píxels
	uint16	wDig;
	uint16	hDig;	
	uint32	idImg[GUInumVimg];	/*Array con los Ids para el archivo LUT de todas las posibles caracteres a mostrar en el visor
								numérico(set de números del 0-9, el signo menos(-) y el signo de separación decimal( . ó ,)*/
	uint32	*idIcoDig;		//Vector con los ids internos de los dígitos
	uint16	*posxDig;		//Vector con las posiciones x de cada dígito
	uint16	*posyDig;		//Vector con las posiciones y de cada dígito
	uint32	*idImgDig;		/*Vector con los ids para el archivo LUT de la imagen que corresponderá a cada dígito
							para mostrar por pantalla*/
	uint8	*visDig;		//Vector con la visibilidad de cada dígito
	char	*bufNum;		//Array auxiliar de caracteres para colocar correctamente el dígito en pantalla
}stNumViewer;

typedef int (*fCallback)(void);


/*-		Estructura del widget ventana emergente*/
typedef struct{
	
	uint8	prsState;		/*Estado de la pulsación: 0=no pulsado, 1=pulsado fuera del pop-up, 2=pulsado en el botón que abre la
	 	 	 	 	 	 	 ventana, 3=pulsado dentro del pop-up pero no de una opción y 4=pulsado en una opción*/
	uint8	prsOption;		//Opción pulsada de la ventana emergente
	
	uint8	state; 			//Estado en la máquina de estados del update de la ventana emergente

	/*Vector con la lista de widgets*/
	
	uint32 numWidgets;
	
	uint32 numWidgetsDisable;
	
	uint8 PopUpListEnbaleOrDisable; //0 - Disable all 1-Disable list

	uint32 *listaWidgets;   // Puntero con la lista de widgets Pop Up
	
	uint32 *listWidgetsDisable;  // Puntero con la lista de widgets que deshabilita el Pop Up. 
		
	uint32 idWidgetPopUpAnt;   //Variable para guardar si hay algun popUp activo anterior
	
	uint8 enableAnt; //Variable para controlar el estado de habilitación anterior del popUp
	
	uint8 popUpSup; //Variable que indica que hay un popUp por encima de este

}stPopUp;


// Definicion de varialbes CallBacks



/*-		Estructura de las diferentes pantallas de la interfaz*/

typedef struct{
	uint32	iWidget;	//Número de widgets de la pantallaGUIconfigInterface
	uint8	iLayers;	//Número de capas de la pantalla
	stWidget *pWidget;	//Vector a todos los widgets de la pantalla
}stScreen;

/*-		Estructura de toda la interfaz*/
typedef struct{
	uint8	iScreen;	//Número de pantallas de la interfaz
	stScreen *pScreen;	//Vector a las pantallas de la interfaz
}stInterface;


/* - Constantes */
//#define GUIfields 30	//Número de todos los campos del vector de widgets
//#define GUIpixColorTscr 0xFF000000

/* -    Listado de errores */
//#define K70_GUI_ERR_BASE	0x0400
//extern const uint16 K70_GUI_ERR_OK;
//extern const uint16 K70_GUI_ERR_ALLOC_SCREENS;
//extern const uint16 K70_GUI_ERR_ALLOC_WIDGETS;
//extern const uint16 K70_GUI_ERR_ALLOC_BUTTON;
//extern const uint16 K70_GUI_ERR_ALLOC_SWITCH;
//extern const uint16 K70_GUI_ERR_ALLOC_IMG_VIEWER;
//extern const uint16 K70_GUI_ERR_ALLOC_NUM_VIEWER;
//extern const uint16 K70_GUI_ERR_ALLOC_DIGITS;
//extern const uint16 K70_GUI_ERR_ALLOC_DIGITS_IMG;
//extern const uint16 K70_GUI_ERR_ALLOC_DIGITS_VIS;
//extern const uint16 K70_GUI_ERR_ALLOC_NUM_BUFFER;
//extern const uint16 K70_GUI_ERR_ALLOC_DIGITS_POS_X;
//extern const uint16 K70_GUI_ERR_ALLOC_DIGITS_POS_Y;
//extern const uint16 K70_GUI_ERR_ALLOC_POP_UP;
//extern const uint16 K70_GUI_ERR_ALLOC_OPTIONS;
//extern const uint16 K70_GUI_ERR_ALLOC_OPTIONS_IMG;
//extern const uint16 K70_GUI_ERR_ALLOC_OPTIONS_POS_X;
//extern const uint16 K70_GUI_ERR_ALLOC_OPTIONS_POS_Y;
//extern const uint16 K70_GUI_ERR_ALLOC_OPTIONS_CBKS;
//extern const uint16 K70_GUI_ERR_CANNOT_FIND_WIDGET;


/* - Variables globales (NUNCA) */
//debug
//uint8 GUIerrors; //Variable que nos permite mostrar por el hyperterminal los posibles errores de la libreria
//double GUInumVnum; //debug


/* - Funciones */
/*
 * Función GUIinit
 * Descripción:
 *      Inicializa la librería para su uso. Debe ser la primera función en ser llamada antes de ninguna otra. 
 *      Esta función inicializa las variables internas, inicializa la librería del driver gráfico K70_GFX.h e inicializa el
 *      touch screen con el bus spi pasado por el usuario.
 *      En el caso de la inicialización de la libreria GFX es necesario:
 *      1) Pasarle los punteros a los archivos de imagenes. 
 *      2) Seleccionar si se quiere pintar el fondo con un color sólido y que se repinte el fondo de este color cada vez que 
 *      se borra una imagen de la pantalla. Esta opción está pensada para el caso que no se disponga de una imagen de fondo
 *      que ocupe toda la pantalla. Si seleccionamos un color de fondo, pero no ponemos la variable de selección a 1, no se 
 *      actualizara el color de fondo de pantalla aunque le pasemos un color.
 *      3)  Configurar la intensidad del back light del LCD mediante PWM.
 * Parámetros:
 * 		1)imgType - uint8:
 * 				Tipo de la compresión de las imagenes: por ahora solo hay un tipo de compresión de imagen: CCN.
 * 				0:Ningún tipo
 * 				1:CCN
 * 		2)ptrPackCCN - uint8*:
 * 				Puntero al pack CCN, donde están todas las imágenes comprimidas.
 * 		3)ptrPackLUT - uint8*:
 * 				Puntero al pack LUT, donde está el índice de las imagenes.
 * 		4)bBottomRef uint8:
 * 				Variable que define si se quiere poner un color de fondo:
 * 					0: No se quiere pintar el fondo.
 * 					1: Se quiere pintar el fondo de un color sólido.
 * 		5)colorBottomRef uint32:
 * 				Color del fondo. Formato: 0xAARRGGBB.
 * 		6)bright - uint32:
 * 		 		Intensidad del back light. Formato: de 0x00(min) a 0xFF(max).
 * 		7)spifd - MQX_FILE_PTR*:
 * 				Bus spi creado por el usuario para la comunicación con la touch screen. Hay un ejemplo de la creación de 
 * 				este bus en la función DemoGUIspi() del programa de demo DemoCoreK70_GUI
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 *      K70_GFX_ERR_ALLOC_SCREEN: Libreria GFX: No es posible alojar la pantalla.
 *      K70_GFX_ERR_IMG_TYPE: Libreria GFX: Tipo de imagenes incorrecto.
 */


//uint16 GUIinit(uint8 imgType,uint8 *ptrPackCCN,uint8 *ptrPackLUT,uint8 bBottomRef, uint32 colorBottomRef,uint8 bright, tK70_DDRdataPtr DDRdata);//TSPIMQX_FILE_PTR *spifd);


//void TSPIGUItscrUpdate(stPosTS posTS);


//uint16 GUIconfigSPI(void);






//uint16 GUIconfigSPI(uint32 prphBaseAddr,void **tscrSPIfun,uint8 cs, uint8 attribSet);

/*
 * Función GUIconfigInterface
 * Descripción:
 *      Función que configura toda la interfaz. Primero reserva el espacio para todas las pantallas y los widgets de la interfaz,
 *      seguidamente rellena la estructura de los widgets ordenados por capas y reserva espacio para la estructura especifica de
 *      cada widget segun el tipo de widget (boton: stButton, interruptor: stSwitch,...) y también la rellena con los widgets
 *      pasados en el parámetro del vector de la interfaz.
 *      Esta función configura toda la interfaz pero no muestra aún nada por pantalla, hay que llamar a la función GUIinitScreen()
 *      para empezar a mostrar los widgets por pantalla.   
 * Parámetros:
 * 		1)interface - uint32[][GUIfields]:
 * 				Array de 2 dimensiones con todos los datos de la interfaz. El array tiene tantas filas como widgets tiene la 
 * 				interfaz y tantas columnas como el número máximo de campos del widget con más campos, este parametro está definido
 * 				como constante en los defines de esta libreria con el nombre de GUIfields.
 * 		2)screens - uint8:
 * 				Número de pantallas diferentes de la interfaz.
 * 		3)widgets - uint32:
 * 				Número de widgets totales de la interfaz.
 * 		4)numLayers - uint8[]:
 * 				Número de capas en cada pantalla, por orden de pantallas.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 *      K70_GUI_ERR_ALLOC_SCREENS: No es posible alojar las pantallas.
 *      K70_GUI_ERR_ALLOC_WIDGETS: No es posible alojar los widgets.
 *      K70_GUI_ERR_ALLOC_BUTTON: No es posible alojar la estructura del boton.
 *      K70_GUI_ERR_ALLOC_SWITCH: No es posible alojar la estructura del interruptor.
 *      K70_GUI_ERR_ALLOC_IMG_VIEWER: No es posible alojar la estructura del visor de imagen.
 *      K70_GUI_ERR_ALLOC_NUM_VIEWER: No es posible alojar la estructura del visor numerico.
 *      K70_GUI_ERR_ALLOC_POP_UP: No es posible alojar la estructura de la ventana emergente.
 *      K70_GUI_ERR_ALLOC_DIGITS: No es posible alojar los digitos del visor.
 *      K70_GUI_ERR_ALLOC_DIGITS_IMG: No es posible alojar las imagenes de los digitos del visor.
 *      K70_GUI_ERR_ALLOC_DIGITS_VIS: No es posible alojar la visibilidad de los digitos del visor.
 *      K70_GUI_ERR_ALLOC_NUM_BUFFER: No es posible alojar el buffer para el numero del visor.
 *      K70_GUI_ERR_ALLOC_DIGITS_POS_X: No es posible alojar las posiciones x de los digitos del visor.
 *      K70_GUI_ERR_ALLOC_DIGITS_POS_Y: No es posible alojar las posiciones y de los digitos del visor.
 *      K70_GUI_ERR_ALLOC_OPTIONS: No es posible alojar las opciones de la ventana emergente.
 *      K70_GUI_ERR_ALLOC_OPTIONS_POS_X: No es posible alojar las posiciones x de las opciones de la pantalla emergente.
 *      K70_GUI_ERR_ALLOC_OPTIONS_POS_Y: No es posible alojar las posiciones y de las opciones de la pantalla emergente.
 *      K70_GUI_ERR_ALLOC_OPTIONS_CBKS: No es posible alojar los callbacks de las opciones de la ventana emergente.
 *      
 */

//uint16 GUIconfigInterface(const uint32 interface[][GUIfields],uint8 screens,uint32 widgets,uint8 *numLayers);

/*
 * Función GUIinitScreen
 * Descripción:
 *      Función que inicia la pantalla indicada por el usuario mostrandola por pantalla. Los pasos que sigue esta función son los
 *      siguientes:
 *      1) Si hay alguna pantalla no finalizada mostrandose, la finaliza.
 *      2) Inicia la escena del GFX con las capas que tiene la pantalla.
 *      3) Cuenta los widgets que hay en cada capa y añade la capa a la escena del GFX.
 *      4) Una vez ha añadido las capas, añade los widgets de todas las capas.
 *      5) Refresca la pantalla con toda la información ya configurada.   
 * Parámetros:
 * 		1)screen - uint8:
 * 				Pantalla que se quiere mostrar.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 *      
 *      
 */
//uint16 GUIinitScreen(uint8 screen);

/*
 * Función GUIfinishScreen
 * Descripción:
 * 		Finaliza la pantalla actual borrando todos los widgets que se muestran por pantalla, finalizando la escena en el GFX.
 * 		Así deja la pantalla sin nada preparada para iniciar otra pantalla o para finalizar la libreria GUI.  
 * Parámetros:
 * 		1)screen - uint8:
 * 				Pantalla que se quiere finalizar.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 *      K70_GFX_ERR_ICON_NOT_FOUND: Icono no encontrado.
 *      K70_GFX_ERR_IMG_TYPE: Tipo de imagenes incorrecto.
 *      K70_GFX_ERR_ICO_POSITION: Posición del icono fuera de los márgenes de la pantalla.
 *      K70_GFX_ERR_LAYER_NOT_FOUND: Capa no encontrada.
 *      K70_GFX_ERR_ICO_POSITION: Posición del icono fuera de los márgenes de la pantalla.
 */
//uint16 GUIfinishScreen(uint8 screen);

/*
 * Función GUIupdate
 * Descripción:
 * 		Actualiza el estado de los widgets que están en la pantalla actual (no tienen porque estar mostrandose
 * 		en la pantalla fisicamente).
 * Parámetros:
 * 		No requiere parámetros.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */
//uint16 GUIupdate(void);

/*
 * Función GUIrefresh
 * Descripción:
 * 		Función que permite refrescar la pantalla, si el parámetro de entrada forceRfsh está a 0 sólo refresca los widgets 
 * 		que estan en la pantalla actual que necesiten refresco, si está a 1 se fuerza el refresco de toda la pantalla aunque
 * 		no haya ningún cambio.
 * Parámetros:
 * 		1)forceRfsh - uint8:
 * 				Indica si se quiere forzar el refresco de toda la pantalla: 
 * 					0:Refresco de los widgets que necesitan refresco. 
 * 					1:Refresco de toda la pantalla.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */
//uint16 GUIrefresh(uint8 forceRfsh);

/*
 * Función GUIbackL
 * Descripción:
 *      Configura la intensidad del back light del LCD mediante PWM.
 * Parámetros:
 * 		 1)bright - uint32:
 * 		 		Intensidad del back light. Formato: de 0x00(min) a 0xFF(max).
 * Retorno:
 *        Error - uint16:
 *				Devuelve el código de error.
 * Errores:
 *      K70_GFX_ERR_OK: No se ha producido ningún error.
 */
//uint16 GUIbackL(uint8 bright);

/*
 * Función GUIfinish
 * Descripción:
 * 		Se debe llamar a esta función para finalizar la librería. Debe ser la última función del programa.
 * 		Si no habiamos finalizado anteriormente la pantalla actual, la finalizamos para borrar los widgets de la pantalla.
 * 		Finalizamos tambien la libreria GFX: En el caso de que no se haya finalizado la escena, se finaliza, se
 * 		apaga el backlight y el LCD, se libera la memoria de los buffers de la pantalla y finaliza la libreria CCN.
 * 		Por útimo se liberan las memorias reservadas de toda la interfaz.
 * Parámetros:
 *      No requiere parámetros.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */
//uint16 GUIfinish(tK70_DDRdataPtr DDRdata);

/*
 * Función GUIsetWidgetExistance
 * Descripción:
 * 		Permite configurar la existencia de un widget. Si el widget no existe no se tendrá en cuenta ni en la actualización de
 * 		estado (GUIupdate) ni en el refresco de pantalla (GUIrefresh).
 * Parámetros:
 *      1)id - uint8:
 * 		 		Id del widget del que se quiere cambiar la existencia.
 * 		2)exist - uint8:
 * 				Parámetro que controla la existencia.
 * 					0: El widget pasa a no existir.
 * 					1: El widgtet pasa a existir.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */
//uint16 GUIsetWidgetExistance(uint32 id,uint8 exist);

/*
 * Función GUIsetWidgetVisibility
 * Descripción:
 * 		Permite configurar la visibilidad de un widget. Si el widget no está visible se tendrá en cuenta en la actualización de
 * 		estado (GUIupdate) pero no se tendrá en cuenta en el refresco de pantalla (GUIrefresh).
 * Parámetros:
 *      1)id - uint8:
 * 		 		Id del widget del que se quiere cambiar la existencia.
 * 		2)vis - uint8:
 * 				Parámetro que controla la visibilidad.
 * 					0: Widget no visible.
 * 					1: Widget visible.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */
//uint16 GUIsetWidgetVisibility(uint32 id,uint8 vis);


/*
 * Función GUIsetWidgetEnable
 * Descripción:
 * 		Permite configurar la habilitacion  de un widget. Si el widget no está visible se tendrá en cuenta en la actualización de
 * 		estado (GUIupdate) pero no se tendrá en cuenta en el refresco de pantalla (GUIrefresh).
 * Parámetros:
 *      1)id - uint8:
 * 		 		Id del widget del que se quiere cambiar la existencia.
 * 		2)vis - uint8:
 * 				Parámetro que controla la visibilidad.
 * 					0: Widget no habilitado
 * 					1: Widget habiltiado.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */

//uint16 GUIsetWidgetEnable(uint32 id,uint8 enable);


/* - 	Funciones públicas del widget botón*/
/*
 * Función GUIsetButonPosition
 * Descripción:
 * 		Permite configurar la posición del botón. Se puede cambiar la posición de la imagen pulsada, la de la imagen no pulsada y
 * 		el area táctil.
 * Parámetros:
 *      1)id - uint8:
 * 		 		Id del widget botón del que se quiere cambiar la posición.
 * 		2)posxImgPrs - uint16
 * 				Posición x de la imagen pulsada.
 * 		3)posyImgPrs - uint16
 * 				Posición y de la imagen pulsada.
 * 		4)posxImgRls - uint16
 * 				Posición x de la imagen no pulsada.
 * 		5)posyImgRls - uint16
 * 				Posición y de la imagen no pulsada.
 * 		6)areaTS - GUIstRect:
 * 				Estructura rectangulo con la posición x, posición y, el ancho y el alto.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 *      
 *      
 *      
 */




//uint16 GUIsetButonPosition(uint8 id,uint16 posxImgPrs,uint16 posyImgPrs,uint16 posxImgRls,uint16 posyImgRls,GUIstRect areaTS);

/*
 * Función GUIsetImgButton
 * Descripción:
 * 		Permite configurar la imagen del visor de imagen.
 * Parámetros:
 *      1)id - uint8:
 * 		 		Id del widget visor de imagen del que se quiere cambiar la posición.
 * 		2)idImg - uint32
 * 				Id de la imagen que queremos mostrar.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */
//uint16 GUIsetImgButton(uint32 id,uint32 idImg, uint8 presOrRel);

//uint16 GUIsetTscImgButton(uint32 id,uint32 idImg);
/* - 	Funciones públicas del widget interruptor*/
/*
 * Función GUIsetSwitchPosition
 * Descripción:
 * 		Permite configurar la posición del botón. Se puede cambiar la posición de la imagen on, la de la imagen off,
 * 		la de la imagen pulsada on, la de la imagen pulsada off y el area táctil.
 * Parámetros:
 *      1)id - uint8:
 * 		 		Id del widget interruptor del que se quiere cambiar la posición.
 * 		2)posxImgOn - uint16
 * 				Posición x de la imagen on
 * 		3)posyImgOn - uint16
 * 				Posición y de la imagen on
 * 		4)posxImgOff - uint16
 * 				Posición x de la imagen off
 * 		5)posyImgOff - uint16
 * 				Posición y de la imagen off
 * 		6)posxImgPrsOn - uint16
 * 				Posición x de la imagen pulsada on
 * 		7)posyImgPrsOn - uint16
 * 				Posición y de la imagen pulsada on
 * 		8)posxImgPrsOff - uint16
 * 				Posición x de la imagen pulsada off
 * 		9)posyImgPrsOff - uint16
 * 				Posición y de la imagen pulsada off	
 * 		10)areaTS - GUIstRect:
 * 				Estructura rectangulo con la posición x, posición y, el ancho y el alto.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */
//uint16 GUIsetSwitchPosition(uint32 id,uint16 posxImgOn,uint16 posyImgOn,uint16 posxImgOff,uint16 posyImgOff,
//		uint16 posxImgPrsOn,uint16 posyImgPrsOn,uint16 posxImgPrsOff,uint16 posyImgPrsOff, GUIstRect areaTS);
//uint16 GUIsetSwitchImg( uint32 id, uint32 imgOnPrs, uint32 imgOffPrs, uint32 imgOnRls, uint32 imgOffRls);
//uint16 GUIsetSwitchTscImg( uint32 id, uint32 imgTSCR);
//uint16 GUIsetSwitchStatus( uint32 id, uint8 OnOff);

/* - 	Funciones públicas del widget visor de imagen*/
/*
 * Función GUIsetImgViewerPosition
 * Descripción:
 * 		Permite configurar la posición del visor de imagen.
 * Parámetros:
 *      1)id - uint8:
 * 		 		Id del widget visor de imagen del que se quiere cambiar la posición.
 * 		2)posx - uint16
 * 				Posición x del visor de imagen
 * 		3)posy - uint16
 * 				Posición y del visor de imagen
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */
//uint16 GUIsetImgViewerPosition(uint32 id,uint16 posx,uint16 posy);

/*
 * Función GUIsetImgViewerImage
 * Descripción:
 * 		Permite configurar la imagen del visor de imagen.
 * Parámetros:
 *      1)id - uint8:
 * 		 		Id del widget visor de imagen del que se quiere cambiar la posición.
 * 		2)idImg - uint32
 * 				Id de la imagen que queremos mostrar.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */
//uint16 GUIsetImgViewerImage(uint32 id,uint32 idImg);

/* - 	Funciones públicas del widget visor numérico*/
/*
 * Función GUIsetNumViewerPosition
 * Descripción:
 * 		Permite configurar la posición del visor numérico.
 * Parámetros:
 *      1)id - uint8:
 * 		 		Id del widget visor numérico del que se quiere cambiar la posición.
 * 		2)posxImgVwr - uint16
 * 				Posición x del visor numérico.
 * 		3)posyImgVwr - uint16
 * 				Posición y del visor numérico.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */
//uint16 GUIsetNumViewerPosition(uint32 id,uint16 posxImgVwr,uint16 posyImgVwr);

/*
 * Función GUIsetNumViewerNum
 * Descripción:
 * 		Permite configurar el número del visor numérico.
 * Parámetros:
 *      1)id - uint8:
 * 		 		Id del widget visor numérico del que se quiere cambiar el número.
 * 		2)num - double
 * 				Número que queremos mostrar.
 * 		3)dec - uint8
 * 				Número de decimales que tiene el número a mostrar.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */
//uint16 GUIsetNumViewerNum(uint32 id,float num,uint8 dec);


//uint16 GUIsetNumViewerNum2(uint32 id, float num,uint8 dec,uint8 visb);

//void float_to_string(float f, char r[], uint8 dec);

//int n_tu(int number, int count);


/* - 	Funciones públicas del widget ventana emergente*/
/*
 * Función GUIsetPopUpOptionsImages
 * Descripción:
 * 		Permite configurar las imágenes de las opciones de la ventana emergente.
 * Parámetros:
 *      1)id - uint8:
 * 		 		Id del widget ventana emergente del que se quiere cambiar la imagen de las opciones.
 * 		2)idImg - uint32*:
 * 				Vector a los ids de las imágenes de las opciones.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */





/*
 * Función GUIsetPopUpCallbacks
 * Descripción:
 * 		Permite configurar los callbacks de las opciones de la ventana emergente.
 * Parámetros:
 *      1)id - uint8:
 * 		 		Id del widget ventana emergente del que se quiere cambiar los callbacks.
 * 		2)cbk - uint32*:
 * 				Vector a los ids de los callbacks de las opciones.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */


/*
 * Función GUIsetPopUpButtonPosition
 * Descripción:
 * 		Permite configurar la posición del botón que despliega la ventana emergente.
 * Parámetros:
 *      1)id - uint8:
 * 		 		Id del widget ventana emergente del que se quiere cambiar la posición del botón.
 * 		2)posxBut - uint16:
 * 				Posición x del botón.
 * 		3)posyBut - uint16:
 * 				Posición y del botón.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */


/*
 * Función GUIsetPopUpWindowPosition
 * Descripción:
 * 		Permite configurar la posición de la ventana emergente.
 * Parámetros:
 *      1)id - uint8:
 * 		 		Id del widget ventana emergente del que se quiere cambiar la posición.
 * 		2)posxBut - uint16:
 * 				Posición x de la ventana emergente.
 * 		3)posyBut - uint16:
 * 				Posición y de la ventana emergente.
 * Retorno:
 *      Error - uint16:
 *              Devuelve el código de error.
 * Errores:
 *      K70_GUI_ERR_OK: No se ha producido ningún error.
 */


// Otman : Falta descripcion de cada funcion.

//uint16 GUIsetPopUpWidgets(uint32 id, const uint32 *idWidgets,  uint32 *idWidgetsDisable);

//uint16 GUIsetPopUpWidgets2(uint8 id, uint32 *idWidgets);

//uint16 GUIactivePopUp(uint32 id);

//uint16 GUIdisablePopUp(uint32 id);

//uint16 GUIgetPopUpStatus( uint32 id, uint8 *status);

/* - 	Funcion privada para los demás programas de widgets*/
/*
 * Función GUIgetInterface
 * Descripción:
 * 		Devuelve la interfaz con la que se está trabajando.
 * Parámetros:
 *      No requiere parámetros.
 * Retorno:
 *      GUIinterf - stInterface:
 *      		Interfaz con la que se está trabajando.
 * Errores:
 *      No genera errores.
 */

//stInterface* GUIgetInterface(void);

//stWidget *GUIgetWidget( uint32 id);

#endif /* GUI_H_ */
