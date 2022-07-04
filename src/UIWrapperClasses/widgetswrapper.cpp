#include "widgetswrapper.h"

WidgetsWrapper::WidgetsWrapper(QObject *parent)
    : QObject{parent}
{

}

void WidgetsWrapper::changeScreen(EAppGUIscreen screenId)
{
    emit changeScreenSignal(screenId);
}

void WidgetsWrapper::bodyZoom(bool zoomed)
{
    emit bodyZoomed(zoomed);
}

void WidgetsWrapper::bodyGenderSelect(EAppGUIbodys gender)
{
    emit bodyGenderSelected(gender);
}

void WidgetsWrapper::bodyAreaSelect(EAppGUIfullBodyAreas area)
{
    emit bodyAreaSelected(area);
}

void WidgetsWrapper::dotZoneAssignHp(EAppGUIwidgetIDlist dot, EAppGUI_HPsIDs hpIndex)
{
    emit dotZoneHpAssigned(dot, hpIndex);
}

void WidgetsWrapper::dotZoneSelect(EAppGUIwidgetIDlist dot, bool isSelected)
{
    emit dotZoneSelected(dot, isSelected);
}

void WidgetsWrapper::GUIsetNumViewerNum(uint32 id, double num, uint8 dec)
{
    char prova[50];
    float_to_string(num, prova, dec);
    QString qstr(prova);

    switch(id)
    {
    case NumVwrTimeHP1: emit treatmentTimerSet(APP_GUI_HP1_ID, prova); break;
    case NumVwrTimeHP2: emit treatmentTimerSet(APP_GUI_HP2_ID, prova); break;
    case NumVwrTimeHP3: emit treatmentTimerSet(APP_GUI_HP3_ID, prova); break;
    case NumVwrTimeHP4: emit treatmentTimerSet(APP_GUI_HP4_ID, prova); break;
    case NumVwrResucctionCountHP1: emit resuctionCountChanged(APP_GUI_HP1_ID, num); break;
    case NumVwrResucctionCountHP2: emit resuctionCountChanged(APP_GUI_HP2_ID, num); break;
    case NumVwrResucctionCountHP3: emit resuctionCountChanged(APP_GUI_HP3_ID, num); break;
    case NumVwrResucctionCountHP4: emit resuctionCountChanged(APP_GUI_HP4_ID, num); break;
    case NumVwrPopUpRFIDrestTime: break;
    case NumVwrPopUpErrHP1: break;
    case NumVwrPopUpErrHP2: break;
    case NumVwrPopUpErrHP3: break;
    case NumVwrPopUpErrHP4: break;
    case NumVwrPopUpErrUC: break;
    case NumVwrPopUpErrTRTtimeHP1: break;
    case NumVwrPopUpErrTRTtimeHP2: break;
    case NumVwrPopUpErrTRTtimeHP3: break;
    case NumVwrPopUpErrTRTtimeHP4: break;
    case NumVwrPopUpCleanHP1: break;
    case NumVwrPopUpCleanHP2: break;
    case NumVwrPopUpCleanHP3: break;
    case NumVwrPopUpCleanHP4: break;
    case NumVwrPopUpCleanNumCancelHP1: break;
    case NumVwrPopUpCleanNumCancelHP2: break;
    case NumVwrPopUpCleanNumCancelHP3: break;
    case NumVwrPopUpCleanNumCancelHP4: break;
    case NumVwrPantallaCalc:        setCalcNumber(qstr); break;
    case NumVwrModeloMaqCfg:        setConfModel(qstr); break;
    case NumVwrVersionSoftwareCfg:  setConfVersion(qstr); break;
    case NumVwrPaginaSATscreen: break;
    case NumVwr1: break;
    case NumVwr2: break;
    case NumVwr3: break;
    case NumVwr4: break;
    case NumVwr5: break;
    case NumVwr6: break;
    case NumVwr7: break;
    case NumVwr8: break;
    case NumVwr9: break;
    case NumVwr10: break;
    case NumVwr11: break;
    case NumVwr12: break;
    case NumVwr13: break;
    case NumVwr14: break;
    case NumVwr15: break;
    case NumVwr16: break;
    case NumVwr17: break;
    case NumVwr18: break;
    case NumVwr19: break;
    case NumVwr20: break;
    case NumVwr21: break;
    case NumVwr22: break;
    case NumVwr23: break;
    case NumVwr24: break;
    case NumVwr25: break;
    case NumVwr26: break;
    case NumVwr27: break;
    case NumVwr28: break;
    case NumVwrError1: break;
    case NumVwrError2: break;
    case NumVwrError3: break;
    case NumVwrError4: break;
    case NumVwrError5: break;
    case NumVwrTempAmb: break;
    case NumVwrTempBomba: break;
    case NumVwrTempRetorno: break;
    case NumVwrCaudalRetorno: break;
    case NumVwrVtobera: break;
    case NumVwrRth: break;
    case NumVwrCPI: break;
    case NumVwrCaudalRetornoHP1: break;
    case NumVwrCaudalRetornoHP2: break;
    case NumVwrCaudalRetornoHP3: break;
    case NumVwrCaudalRetornoHP4: break;
    case NumVwrVacuumHP1: break;
    case NumVwrVacuumHP2: break;
    case NumVwrVacuumHP3: break;
    case NumVwrVacuumHP4: break;
    case NumVwrFatigaTime: break;
    case NumVwrErrFatiga1: break;
    case NumVwrErrFatiga2: break;
    case NumVwrErrFatiga3: break;
    case NumVwrErrFatiga4: break;
    case NumVwrErrFatiga5: break;
    default: /* Do nothing. */ break;
    }
}

void WidgetsWrapper::GUIsetSwitchStatus(uint32 id, uint8 OnOff)
{
    switch (id) {
    case SwInitScrAvisos: break;
    case SwCtrlPnlTstVacHP1: break;
    case SwCtrlPnlTstVacHP2: break;
    case SwCtrlPnlTstVacHP3: break;
    case SwCtrlPnlTstVacHP4: break;
    case SwDotZone0:
    case SwDotZone1:
    case SwDotZone2:
    case SwDotZone3:
    case SwDotZone4:
    case SwDotZone5:
    case SwDotZone6:
    case SwDotZone7:
    case SwDotZone8:
    case SwDotZone9:
    case SwDotZone10:
    case SwDotZone11:
    case SwDotZone12:
    case SwDotZone13:
    case SwDotZone14: dotZoneSelected((EAppGUIwidgetIDlist)id, (bool)OnOff); break;
    case SwPopUpTstVacLowLvl: break;
    case SwPopUpTstVacMidLvl: break;
    case SwPopUpTstVacHighLvl: break;
    case SwPopUpRecommInfo: break;
    case SwTrtScrAvisos: break;
    case SwCalcScrAvisos: break;
    case SwCfgResuctionViewer: break;
    case SwCfgTemperatureViewer: break;
    case SwCfgScrAvisos: break;
    case SwLanFrances: break;
    case SwLanCastellano: break;
    case SwLanIngles: break;
    case SwLanItaliano: break;
    case SwLanAleman: break;
    case SwLanPolaco: break;
    case SwLanRuso: break;
    case SwLanPortugues: break;
    case SwLanChino: break;
    case SwLanJapones: break;
    case SwLanCoreano: break;
    case SwLanScrAvisos: break;
    case SwVacuum: break;
    case SwFrio: break;
    case SwRFID: break;
    case SwTestLed: break;
    case SwTestLedRGB: break;
    case SwFatigueFailBeep: break;
    default: /* Do nothing */ break;
    }
}

uint16 WidgetsWrapper::GUIsetWidgetVisibility(uint32 id, uint8 vis)
{
    switch(id) {
    //PANTALLA DE CARGA
//    case ImgLoadScrBckGnd,
//    case ImgLoadAnim1,
//    case imgLoadAnim2,
//    case imgLoadAnim3,
//    case imgLoadAnim4,
//    case imgLoadAnim5,
//    case imgLoadAnim6,
//    case imgLoadAnim7,
//    case imgLoadAnim8,

//    //PANTALLA DE INICIO
//    case imgInitScrBckGnd,
//    case ButSelectWoman,
//    case ButSelectMan,
//    case imgInitGPRScoverage,		//V7790

//    //Menu principal
//    case butInitScrShowMainMenu,
//    case butInitScrHideMainMenu,
//    case imgInitScrHome,
//    case butInitScrCfg,
//    case butInitScrCalc,
//    case butInitScrData,

//    case SwInitScrAvisos,
//    case ImgInitScrNotificacion,
//    case PopupInitScrAvisos,
//    case imgPopUpInitScrAvisoBckGND,
//    case imgPopUpInitScrAvisoNivelAguaBajo,
//    case imgPopUpInitScrAvisoNivelAguaMedio,
//    case imgPopUpInitScrAvisoTempAmb,
//    case imgPopUpInitScrAvisoRFID,
//    case imgPopUpInitScrAvisoRTC,
//    case imgPopUpInitScrAvisoFiltroAire,

//    //PANTALLA DE TRATAMIENTO
//    case imgTrtScrBckGnd,
//    case imgFullBodyAndZoom,
//    case imgTrtGPRScoverage,				//V7790

//    //Fondos de los paneles de control
//    case imgCtrlPnlBckGndHP1,
//    case imgCtrlPnlBckGndHP2,
//    case imgCtrlPnlBckGndHP3,
//    case imgCtrlPnlBckGndHP4,

//    //Colores fondos de los paneles de control
//    case ImgColourCtrlPnlBckGndHP1,
//    case ImgColourCtrlPnlBckGndHP2,
//    case ImgColourCtrlPnlBckGndHP3,
//    case ImgColourCtrlPnlBckGndHP4,

    //Indicadores de accion del HP cuando activos, los inactivos forman parte del fondo
    case ImgCtrlPnlRFIDblinkHP1: emit indicatorRfidVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case ImgCtrlPnlRFIDblinkHP2: emit indicatorRfidVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case ImgCtrlPnlRFIDblinkHP3: emit indicatorRfidVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case ImgCtrlPnlRFIDblinkHP4: emit indicatorRfidVisibilityChanged(APP_GUI_HP4_ID, vis); break;
    case ImgCtrlPnlPulBlinkHP1: emit indicatorButtonVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case ImgCtrlPnlPulBlinkHP2: emit indicatorButtonVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case ImgCtrlPnlPulBlinkHP3: emit indicatorButtonVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case ImgCtrlPnlPulBlinkHP4: emit indicatorButtonVisibilityChanged(APP_GUI_HP4_ID, vis); break;
    case ImgCtrlPnlVacBlinkHP1: emit indicatorVacuumVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case ImgCtrlPnlVacBlinkHP2: emit indicatorVacuumVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case ImgCtrlPnlVacBlinkHP3: emit indicatorVacuumVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case ImgCtrlPnlVacBlinkHP4: emit indicatorVacuumVisibilityChanged(APP_GUI_HP4_ID, vis); break;
    case ImgCtrlPnlCoolingBlinkHP1: emit indicatorCoolingVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case ImgCtrlPnlCoolingBlinkHP2: emit indicatorCoolingVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case ImgCtrlPnlCoolingBlinkHP3: emit indicatorCoolingVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case ImgCtrlPnlCoolingBlinkHP4: emit indicatorCoolingVisibilityChanged(APP_GUI_HP4_ID, vis); break;

//    //Botones del panel de control de PLAY y Test Vacum
//    case ButCtrlPnlPlayHP1,
//    case ButCtrlPnlPlayHP2,
//    case ButCtrlPnlPlayHP3,
//    case ButCtrlPnlPlayHP4,
//    case SwCtrlPnlTstVacHP1,
//    case SwCtrlPnlTstVacHP2,
//    case SwCtrlPnlTstVacHP3,
//    case SwCtrlPnlTstVacHP4,

//    //Botones (switch) que permite seleccionar modo de tratamiento AUTO o MANUAL
//    case ButSwtchModeAutoManualHP1,
//    case ButSwtchModeAutoManualHP2,
//    case ButSwtchModeAutoManualHP3,
//    case ButSwtchModeAutoManualHP4,

    //Visores de tiempo restante de trt y boton de seleccion de tiempo
    case NumVwrTimeHP1: emit timeRemainingVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case NumVwrTimeHP2: emit timeRemainingVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case NumVwrTimeHP3: emit timeRemainingVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case NumVwrTimeHP4: emit timeRemainingVisibilityChanged(APP_GUI_HP4_ID, vis); break;
    case ButSelectTimeHP1: emit timeSelectButtonVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case ButSelectTimeHP2: emit timeSelectButtonVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case ButSelectTimeHP3: emit timeSelectButtonVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case ButSelectTimeHP4: emit timeSelectButtonVisibilityChanged(APP_GUI_HP4_ID, vis); break;
//    case ButVwrTemperatureHP1,
//    case ButVwrTemperatureHP2,
//    case ButVwrTemperatureHP3,
//    case ButVwrTemperatureHP4,

    //Visor numerico para contabilizar resucciones
    case NumVwrResucctionCountHP1: emit resuctionCountVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case NumVwrResucctionCountHP2: emit resuctionCountVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case NumVwrResucctionCountHP3: emit resuctionCountVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case NumVwrResucctionCountHP4: emit resuctionCountVisibilityChanged(APP_GUI_HP4_ID, vis); break;

//    //Boton con la imagen e imagen con el texto del modelo
//    case ImgModelTextHP1,
//    case ImgModelTextHP2,
//    case ImgModelTextHP3,
//    case ImgModelTextHP4,
//    case ButModelImageHP1,
//    case ButModelImageHP2,
//    case ButModelImageHP3,
//    case ButModelImageHP4,

//    //Botonoes de recogida y despliegue del panel de control
//    case ButHideControlPanelHP1,
//    case ButHideControlPanelHP2,
//    case ButHideControlPanelHP3,
//    case ButHideControlPanelHP4,
//    case butShowControlPanelHP1,
//    case butShowControlPanelHP2,
//    case butShowControlPanelHP3,
//    case butShowControlPanelHP4,

//    //Botones de selección de Full body
//    case ButFullBodyTorso,
//    case ButFullBodyPiernas,
//    case ButFullBodyBrazos,
//    case ButFullBodyEspalda,
//    case ButFullBodyPiernaMuslo,
//    case ButFullBodyCuello,

//    //Puntos seleccion de zona de tratamiento cuando zoom
//    case SwDotZone0,
//    case SwDotZone1,
//    case SwDotZone2,
//    case SwDotZone3,
//    case SwDotZone4,
//    case SwDotZone5,
//    case SwDotZone6,
//    case SwDotZone7,
//    case SwDotZone8,
//    case SwDotZone9,
//    case SwDotZone10,
//    case SwDotZone11,
//    case SwDotZone12,
//    case SwDotZone13,
//    case SwDotZone14,

    //Punto seleccionado para tratamiento con ese HP a mostrar en full body
    case ImgSelectedTrtZoneHP1: trtDotFullBodyVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case ImgSelectedTrtZoneHP2: trtDotFullBodyVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case ImgSelectedTrtZoneHP3: trtDotFullBodyVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case ImgSelectedTrtZoneHP4: trtDotFullBodyVisibilityChanged(APP_GUI_HP4_ID, vis); break;

//    //POPUP's
//    //Common
    case ButPopUpReturn: emit returnButtonVisibilityChanged(vis); break;
//    case imgPopUpHPcolorBar,

//    //PopUp Time widgets
//    case PopUpTime,
//    case butPopUpTime50min,
//    case butPopUpTime70min,
//    case imgPopUpTime1sel,
//    case imgPopUpTime2sel,

//    //PopUp Test Vacum widgets
//    case PopUpTstVac,
//    case imgPopUpTstVacBckGnd,
//    case imgPopUpTstVacLowLvl,
//    case imgPopUpTstVacMidLvl,
//    case imgPopUpTstVacHighLvl,
//    case imgPopUpTstVacPulHand,
//    case imgPopUpTstVacPulHandx2,
//    case butPopUpTstVacManualLowLvl,
//    case butPopUpTstVacManualMidLvl,
//    case butPopUpTstVacManualHighLvl,
//    case butPopUpTstVacAuto,
//    case SwPopUpTstVacLowLvl,
//    case SwPopUpTstVacMidLvl,
//    case SwPopUpTstVacHighLvl,
//    case imgPopUpTstVacAUTOstatus,

//    //PopUp Test Vacuum 2 widgets
//    case PopUpTstVacSmall,
//    case imgPopUpVacSelBck,
//    case butPopUpTstVacSmallLowLvl,
//    case butPopUpTstVacSmallMedLvl,
//    case butPopUpTstVacSmallHighLvl,

//    //PopUp RFID widgets
//    case PopUpRFID,
//    case imgPopUpRFIDbckGnd,
//    case imgPopUpRFIDlabel,
//    case imgPopUpRFIDresult,
//    case butPopUpRFIDreuseLabel,
//    case NumVwrPopUpRFIDrestTime,

//    //PopUp Recommendation widgets
    case SwPopUpRecommInfo: emit infoSwitchVisibilityChanged(vis); break;
//    case PopUpRecomm,
//    case imgPopUpRecommbckGnd,
    case ImgPopUpRecommCurved:
    case ImgPopUpRecommTight:
    case ImgPopUpRecommStright:
    case ImgPopUpRecommTiny:
    case ImgPopUpRecommTinyCurved:
    case ImgPopUpRecommDouble:
    case ImgPopUpRecommOval:
    case ImgPopUpRecommOvalCurved:
    case ImgPopUpRecommAngled: emit suggestedHpWatermarkDisplayed((EAppGUIwidgetIDlist)id, vis); break;

//    //Menu Principal
//    case butTrtScrShowMainMenu,
//    case butTrtScrHideMainMenu,
//    case ButTrtScrHome,
//    case ButTrtScrCfg,
//    case ButTrtScrCalc,
//    case butTrtScrData,

//    case SwTrtScrAvisos,
//    case ImgTrtScrNotificacion,
//    case PopupTrtScrAvisos,
//    case imgPopUpTrtScrAvisoBckGND,
//    case imgPopUpTrtScrAvisoNivelAguaBajo,
//    case imgPopUpTrtScrAvisoNivelAguaMedio,
//    case imgPopUpTrtScrAvisoTempAmb,
//    case imgPopUpTrtScrAvisoRFID,
//    case imgPopUpTrtScrAvisoRTC,
//    case imgPopUpTrtScrAvisoFiltroAire,

//    //popUp's Error
//    case imgPopUpErrBckGndHP1,
//    case imgPopUpErrBckGndHP2,
//    case imgPopUpErrBckGndHP3,
//    case imgPopUpErrBckGndHP4,
//    case imgPopUpErrBckGndUC,
//    case NumVwrPopUpErrHP1,
//    case NumVwrPopUpErrHP2,
//    case NumVwrPopUpErrHP3,
//    case NumVwrPopUpErrHP4,
//    case NumVwrPopUpErrUC,
//    case imgPopUpErrMsgHP1,
//    case imgPopUpErrMsgHP2,
//    case imgPopUpErrMsgHP3,
//    case imgPopUpErrMsgHP4,
//    case imgPopUpErrMsgUC,
//    case butPopUpErrOkHP1,
//    case butPopUpErrOkHP2,
//    case butPopUpErrOkHP3,
//    case butPopUpErrOkHP4,
//    case butPopUpErrOkUC,
//    case NumVwrPopUpErrTRTtimeHP1,
//    case NumVwrPopUpErrTRTtimeHP2,
//    case NumVwrPopUpErrTRTtimeHP3,
//    case NumVwrPopUpErrTRTtimeHP4,

//    //PopUp's CleanUp
//    case imgPopUpCleanBckGndHP1,
//    case imgPopUpCleanBckGndHP2,
//    case imgPopUpCleanBckGndHP3,
//    case imgPopUpCleanBckGndHP4,
//    case NumVwrPopUpCleanHP1,
//    case NumVwrPopUpCleanHP2,
//    case NumVwrPopUpCleanHP3,
//    case NumVwrPopUpCleanHP4,
//    case butPopUpCleanHP1,
//    case butPopUpCleanHP2,
//    case butPopUpCleanHP3,
//    case butPopUpCleanHP4,
//    case butPopUpCleanYESHP1,
//    case butPopUpCleanYESHP2,
//    case butPopUpCleanYESHP3,
//    case butPopUpCleanYESHP4,
//    case butPopUpCleanNOHP1,
//    case butPopUpCleanNOHP2,
//    case butPopUpCleanNOHP3,
//    case butPopUpCleanNOHP4,
//    case imgPopUpCleanHP1,
//    case imgPopUpCleanHP2,
//    case imgPopUpCleanHP3,
//    case imgPopUpCleanHP4,
//    case butPopUpCleanCancelHP1,
//    case butPopUpCleanCancelHP2,
//    case butPopUpCleanCancelHP3,
//    case butPopUpCleanCancelHP4,
//    case NumVwrPopUpCleanNumCancelHP1,
//    case NumVwrPopUpCleanNumCancelHP2,
//    case NumVwrPopUpCleanNumCancelHP3,
//    case NumVwrPopUpCleanNumCancelHP4,


//    //Pantalla de la calculadora
//    case imgFondoCalcScreen,
//    case imgCuerpoCalc,
//    case NumVwrPantallaCalc,
//    case ButNum0Calc,
//    case ButNum1Calc,
//    case ButNum2Calc,
//    case ButNum3Calc,
//    case ButNum4Calc,
//    case ButNum5Calc,
//    case ButNum6Calc,
//    case ButNum7Calc,
//    case ButNum8Calc,
//    case ButNum9Calc,
//    case butMasCalc,
//    case butMenosCalc,
//    case ButEnterCalc,
//    case ButCECalc,
//    case butComaCalc,

//    //Menu principal - calculadora
//    case butCalcScrShowMainMenu,
//    case butCalcScrHideMainMenu,
//    case butCalcScrHome,
//    case butCalcScrCfg,
//    case imgCalcScrCalc,
//    case butCalcScrData,

//    case SwCalcScrAvisos,
//    case ImgCalcScrNotificacion,
//    case PopupCalcScrAvisos,
//    case imgPopUpCalcScrAvisoBckGND,
//    case imgPopUpCalcScrAvisoNivelAguaBajo,
//    case imgPopUpCalcScrAvisoNivelAguaMedio,
//    case imgPopUpCalcScrAvisoTempAmb,
//    case imgPopUpCalcScrAvisoRFID,
//    case imgPopUpCalcScrAvisoRTC,
//    case imgPopUpCalcScrAvisoFiltroAire,

//    //Pantalla de configuración
//    case imgFondoCfgScreen,
//    case imgVentanaCfgCastellano,
//    case butCfgActualizarSoftware,
//    case imgSoftwareProgressionUpdateBar,
//    case NumVwrModeloMaqCfg,
//    case NumVwrVersionSoftwareCfg,
//    case butCfgRecargaCoolant,
//    case SwCfgResuctionViewer,
//    case SwCfgTemperatureViewer,
//    case butCfgCleanUpHP1,
//    case butCfgCleanUpHP2,
//    case butCfgCleanUpHP3,
//    case butCfgCleanUpHP4,
//    case butCfgCleanUpRoundHP,
//    case imgCfgGPRScoverage,		//V7790

//    //Menu principal - configuracion
//    case butCfgScrShowMainMenu,
//    case butCfgScrHideMainMenu,
//    case butCfgScrHome,
//    case imgCfgScrCfg,
//    case butCfgScrCalc,
//    case butCfgScrData,

//    case SwCfgScrAvisos,
//    case ImgCfgScrNotificacion,
//    case PopupCfgScrAvisos,
//    case imgPopUpCfgScrAvisoBckGND,
//    case imgPopUpCfgScrAvisoNivelAguaBajo,
//    case imgPopUpCfgScrAvisoNivelAguaMedio,
//    case imgPopUpCfgScrAvisoTempAmb,
//    case imgPopUpCfgScrAvisoRFID,
//    case imgPopUpCfgScrAvisoRTC,
//    case imgPopUpCfgScrAvisoFiltroAire,

//    //Pantalla de idiomas
//    case imgFondoLanScreen,

//    case SwLanFrances,
//    case SwLanCastellano,
//    case SwLanIngles,
//    case SwLanItaliano,
//    case SwLanAleman,
//    case SwLanPolaco,
//    case SwLanRuso,
//    case SwLanPortugues,
//    case SwLanChino,
//    case SwLanJapones,
//    case SwLanCoreano,

//    //Menu principal - idiomas
//    case butLanScrShowMainMenu,
//    case butLanScrHideMainMenu,
//    case butLanScrHome,
//    case butLanScrCfg,
//    case butLanScrCalc,
//    case imgLanScrData,

//    case SwLanScrAvisos,
//    case ImgLanScrNotificacion,
//    case PopupLanScrAvisos,
//    case imgPopUpLanScrAvisoBckGND,
//    case imgPopUpLanScrAvisoNivelAguaBajo,
//    case imgPopUpLanScrAvisoNivelAguaMedio,
//    case imgPopUpLanScrAvisoTempAmb,
//    case imgPopUpLanScrAvisoRFID,
//    case imgPopUpLanScrAvisoRTC,
//    case imgPopUpLanScrAvisoFiltroAire,

//    //Pantalla de SAT
//    case imgFondoSATscreen,
//    case butHomeSATscreen,

//    case NumVwrPaginaSATscreen,
//    case butNextPagSATscreen,
//    case butPrevPagSATscreen,

//    case imgVwr1,
//    case imgVwr2,
//    case imgVwr3,
//    case imgVwr4,
//    case imgVwr5,
//    case imgVwr6,
//    case imgVwr7,
//    case imgVwr8,
//    case imgVwr9,
//    case imgVwr10_1,
//    case imgVwr10_2,
//    case imgVwr11_1,
//    case imgVwr11_2,
//    case imgVwr12_1,
//    case imgVwr12_2,
//    case imgVwr13_1,
//    case imgVwr13_2,
//    case imgVwr14_1,
//    case imgVwr14_2,
//    case imgVwr15_1,
//    case imgVwr15_2,
//    case imgVwr16_1,
//    case imgVwr16_2,
//    case imgVwr17_1,
//    case imgVwr17_2,
//    case imgVwr18_1,
//    case imgVwr18_2,
//    case imgVwr19_1,
//    case imgVwr19_2,
//    case imgVwr20_1,
//    case imgVwr20_2,
//    case imgVwr21_1,
//    case imgVwr21_2,
//    case imgVwr22_1,
//    case imgVwr22_2,
//    case imgVwr23_1,
//    case imgVwr23_2,
//    case imgVwr24_1,
//    case imgVwr24_2,
//    case imgVwr25_1,
//    case imgVwr25_2,
//    case imgVwr26_1,
//    case imgVwr26_2,
//    case imgVwr27_1,
//    case imgVwr27_2,
//    case imgVwr28_1,
//    case imgVwr28_2,

//    case NumVwr1,
//    case NumVwr2,
//    case NumVwr3,
//    case NumVwr4,
//    case NumVwr5,
//    case NumVwr6,
//    case NumVwr7,
//    case NumVwr8,
//    case NumVwr9,
//    case NumVwr10,
//    case NumVwr11,
//    case NumVwr12,
//    case NumVwr13,
//    case NumVwr14,
//    case NumVwr15,
//    case NumVwr16,
//    case NumVwr17,
//    case NumVwr18,
//    case NumVwr19,
//    case NumVwr20,
//    case NumVwr21,
//    case NumVwr22,
//    case NumVwr23,
//    case NumVwr24,
//    case NumVwr25,
//    case NumVwr26,
//    case NumVwr27,
//    case NumVwr28,

//    case imgVacuum,
//    case imgFrio,
//    case imgRFID,
//    case imgTestLed,
//    case imgTestLedStatus,
//    case imgTestLedRGD,
//    case SwVacuum,
//    case SwFrio,
//    case SwRFID,
//    case SwTestLed,
//    case SwTestLedRGB,

//    case PopupErrorSAT,
//    case imgVwrFondoErrorSAT,
//    case NumVwrError1,
//    case NumVwrError2,
//    case NumVwrError3,
//    case NumVwrError4,
//    case NumVwrError5,
//    case butOkerr,

//    //Pantalla de FATIGA
//    case imgFondoFATIGAscreen,
//    case butHomeFATIGAscreen,

//    case imgStep1,
//    case imgStep1status,
//    case imgStep2,
//    case imgStep2status,
//    case imgStep3,
//    case imgStep3status,
//    case imgStep4,
//    case imgStep4statusHP1,
//    case imgStep4statusHP2,
//    case imgStep4statusHP3,
//    case imgStep4statusHP4,
//    case imgStep5,
//    case imgStep5statusHP1,
//    case imgStep5statusHP2,
//    case imgStep5statusHP3,
//    case imgStep5statusHP4,
//    case imgStep6,
//    case imgStep6status,
//    case imgStep7,
//    case imgStep7status,

//    case NumVwrTempAmb,
//    case NumVwrTempBomba,
//    case NumVwrTempRetorno,
//    case NumVwrCaudalRetorno,
//    case NumVwrVtobera,
//    case NumVwrRth,
//    case NumVwrCPI,
//    case NumVwrCaudalRetornoHP1,
//    case NumVwrCaudalRetornoHP2,
//    case NumVwrCaudalRetornoHP3,
//    case NumVwrCaudalRetornoHP4,
//    case NumVwrVacuumHP1,
//    case NumVwrVacuumHP2,
//    case NumVwrVacuumHP3,
//    case NumVwrVacuumHP4,
//    case NumVwrFatigaTime,
//    case NumVwrErrFatiga1,
//    case NumVwrErrFatiga2,
//    case NumVwrErrFatiga3,
//    case NumVwrErrFatiga4,
//    case NumVwrErrFatiga5,

//    case imgVwrVAC1,
//    case imgVwrVAC2,
//    case imgVwrVAC3,
//    case imgVwrVAC4,
//    case imgVwrCaudal1,
//    case imgVwrCaudal2,
//    case imgVwrCaudal3,
//    case imgVwrCaudal4,
//    case imgVwrTempAmb,
//    case imgVwrTempBomba,
//    case imgVwrTempRetorno,
//    case imgVwrCaudalRetorno,
//    case imgVwrVtobera,
//    case imgVwrRth,
//    case imgVwrCPI,				//447

//    case SwFatigueFailBeep,

    case ImgInitScrNotificacion:
    case ImgTrtScrNotificacion:
    case ImgCalcScrNotificacion:
    case ImgCfgScrNotificacion:
    case ImgLanScrNotificacion: emit mainMenuWarningNotificationDisplayed(vis); break;

    default: /* Do nothing */ break;
    }

    return 0;
}

uint16 WidgetsWrapper::GUIsetWidgetEnable(uint32 id, uint8 enable)
{
    switch(id) {
    //PANTALLA DE CARGA
//    case ImgLoadScrBckGnd,
//    case ImgLoadAnim1,
//    case imgLoadAnim2,
//    case imgLoadAnim3,
//    case imgLoadAnim4,
//    case imgLoadAnim5,
//    case imgLoadAnim6,
//    case imgLoadAnim7,
//    case imgLoadAnim8,

//    //PANTALLA DE INICIO
//    case imgInitScrBckGnd,
//    case ButSelectWoman,
//    case ButSelectMan,
//    case imgInitGPRScoverage,		//V7790

//    //Menu principal
//    case butInitScrShowMainMenu,
//    case butInitScrHideMainMenu,
//    case imgInitScrHome,
//    case butInitScrCfg,
//    case butInitScrCalc,
//    case butInitScrData,

//    case SwInitScrAvisos,
//    case ImgInitScrNotificacion,
//    case PopupInitScrAvisos,
//    case imgPopUpInitScrAvisoBckGND,
//    case imgPopUpInitScrAvisoNivelAguaBajo,
//    case imgPopUpInitScrAvisoNivelAguaMedio,
//    case imgPopUpInitScrAvisoTempAmb,
//    case imgPopUpInitScrAvisoRFID,
//    case imgPopUpInitScrAvisoRTC,
//    case imgPopUpInitScrAvisoFiltroAire,

//    //PANTALLA DE TRATAMIENTO
//    case imgTrtScrBckGnd,
//    case imgFullBodyAndZoom,
//    case imgTrtGPRScoverage,				//V7790

//    //Fondos de los paneles de control
//    case imgCtrlPnlBckGndHP1,
//    case imgCtrlPnlBckGndHP2,
//    case imgCtrlPnlBckGndHP3,
//    case imgCtrlPnlBckGndHP4,

//    //Colores fondos de los paneles de control
//    case ImgColourCtrlPnlBckGndHP1,
//    case ImgColourCtrlPnlBckGndHP2,
//    case ImgColourCtrlPnlBckGndHP3,
//    case ImgColourCtrlPnlBckGndHP4,

//    //Indicadores de accion del HP cuando activos, los inactivos forman parte del fondo
//    case ImgCtrlPnlRFIDblinkHP1,
//    case ImgCtrlPnlRFIDblinkHP2,
//    case ImgCtrlPnlRFIDblinkHP3,
//    case ImgCtrlPnlRFIDblinkHP4,
//    case ImgCtrlPnlPulBlinkHP1,
//    case ImgCtrlPnlPulBlinkHP2,
//    case ImgCtrlPnlPulBlinkHP3,
//    case ImgCtrlPnlPulBlinkHP4,
//    case ImgCtrlPnlVacBlinkHP1,
//    case ImgCtrlPnlVacBlinkHP2,
//    case ImgCtrlPnlVacBlinkHP3,
//    case ImgCtrlPnlVacBlinkHP4,
//    case ImgCtrlPnlCoolingBlinkHP1,
//    case ImgCtrlPnlCoolingBlinkHP2,
//    case ImgCtrlPnlCoolingBlinkHP3,
//    case ImgCtrlPnlCoolingBlinkHP4,

    //Botones del panel de control de PLAY y Test Vacum
    case ButCtrlPnlPlayHP1: emit controlPanelPlayButtonEnabled(APP_GUI_HP1_ID, enable); break;
    case ButCtrlPnlPlayHP2: emit controlPanelPlayButtonEnabled(APP_GUI_HP2_ID, enable); break;
    case ButCtrlPnlPlayHP3: emit controlPanelPlayButtonEnabled(APP_GUI_HP3_ID, enable); break;
    case ButCtrlPnlPlayHP4: emit controlPanelPlayButtonEnabled(APP_GUI_HP4_ID, enable); break;
    case SwCtrlPnlTstVacHP1: emit controlPanelVacuumButtonEnabled(APP_GUI_HP1_ID, enable); break;
    case SwCtrlPnlTstVacHP2: emit controlPanelVacuumButtonEnabled(APP_GUI_HP2_ID, enable); break;
    case SwCtrlPnlTstVacHP3: emit controlPanelVacuumButtonEnabled(APP_GUI_HP3_ID, enable); break;
    case SwCtrlPnlTstVacHP4: emit controlPanelVacuumButtonEnabled(APP_GUI_HP4_ID, enable); break;

//    //Botones (switch) que permite seleccionar modo de tratamiento AUTO o MANUAL
//    case ButSwtchModeAutoManualHP1,
//    case ButSwtchModeAutoManualHP2,
//    case ButSwtchModeAutoManualHP3,
//    case ButSwtchModeAutoManualHP4,

//    //Visores de tiempo restante de trt y boton de seleccion de tiempo
//    case NumVwrTimeHP1
//    case NumVwrTimeHP2
//    case NumVwrTimeHP3
//    case NumVwrTimeHP4
    case ButSelectTimeHP1: emit controlPanelTimeButtonEnabled(APP_GUI_HP1_ID, enable); break;
    case ButSelectTimeHP2: emit controlPanelTimeButtonEnabled(APP_GUI_HP2_ID, enable); break;
    case ButSelectTimeHP3: emit controlPanelTimeButtonEnabled(APP_GUI_HP3_ID, enable); break;
    case ButSelectTimeHP4: emit controlPanelTimeButtonEnabled(APP_GUI_HP4_ID, enable); break;
    case ButVwrTemperatureHP1: emit temperatureButtonEnabled(APP_GUI_HP1_ID, enable); break;
    case ButVwrTemperatureHP2: emit temperatureButtonEnabled(APP_GUI_HP2_ID, enable); break;
    case ButVwrTemperatureHP3: emit temperatureButtonEnabled(APP_GUI_HP3_ID, enable); break;
    case ButVwrTemperatureHP4: emit temperatureButtonEnabled(APP_GUI_HP4_ID, enable); break;

//    //Visor numerico para contabilizar resucciones
//    case NumVwrResucctionCountHP1,
//    case NumVwrResucctionCountHP2,
//    case NumVwrResucctionCountHP3,
//    case NumVwrResucctionCountHP4,

//    //Boton con la imagen e imagen con el texto del modelo
//    case ImgModelTextHP1,
//    case ImgModelTextHP2,
//    case ImgModelTextHP3,
//    case ImgModelTextHP4,
    case ButModelImageHP1: emit hpImageButtonEnabled(APP_GUI_HP1_ID, enable); break;
    case ButModelImageHP2: emit hpImageButtonEnabled(APP_GUI_HP2_ID, enable); break;
    case ButModelImageHP3: emit hpImageButtonEnabled(APP_GUI_HP3_ID, enable); break;
    case ButModelImageHP4: emit hpImageButtonEnabled(APP_GUI_HP4_ID, enable); break;

    //Botonoes de recogida y despliegue del panel de control
    case ButHideControlPanelHP1: emit controlPanelHideButtonEnabled(APP_GUI_HP1_ID, enable); break;
    case ButHideControlPanelHP2: emit controlPanelHideButtonEnabled(APP_GUI_HP2_ID, enable); break;
    case ButHideControlPanelHP3: emit controlPanelHideButtonEnabled(APP_GUI_HP3_ID, enable); break;
    case ButHideControlPanelHP4: emit controlPanelHideButtonEnabled(APP_GUI_HP4_ID, enable); break;
//    case butShowControlPanelHP1,
//    case butShowControlPanelHP2,
//    case butShowControlPanelHP3,
//    case butShowControlPanelHP4,

//    //Botones de selección de Full body
//    case ButFullBodyTorso,
//    case ButFullBodyPiernas,
//    case ButFullBodyBrazos,
//    case ButFullBodyEspalda,
//    case ButFullBodyPiernaMuslo,
//    case ButFullBodyCuello,

    //Puntos seleccion de zona de tratamiento cuando zoom
    case SwDotZone0:
    case SwDotZone1:
    case SwDotZone2:
    case SwDotZone3:
    case SwDotZone4:
    case SwDotZone5:
    case SwDotZone6:
    case SwDotZone7:
    case SwDotZone8:
    case SwDotZone9:
    case SwDotZone10:
    case SwDotZone11:
    case SwDotZone12:
    case SwDotZone13:
    case SwDotZone14: emit dotZoneEnabled((EAppGUIwidgetIDlist)id, enable); break;

//    //Punto seleccionado para tratamiento con ese HP a mostrar en full body
//    case ImgSelectedTrtZoneHP1,
//    case ImgSelectedTrtZoneHP2,
//    case ImgSelectedTrtZoneHP3,
//    case ImgSelectedTrtZoneHP4,

//    //POPUP's
//    //Common
    case ButPopUpReturn: emit returnButtonEnabled(enable); break;
//    case imgPopUpHPcolorBar,

//    //PopUp Time widgets
//    case PopUpTime,
//    case butPopUpTime50min,
//    case butPopUpTime70min,
//    case imgPopUpTime1sel,
//    case imgPopUpTime2sel,

//    //PopUp Test Vacum widgets
//    case PopUpTstVac,
//    case imgPopUpTstVacBckGnd,
//    case imgPopUpTstVacLowLvl,
//    case imgPopUpTstVacMidLvl,
//    case imgPopUpTstVacHighLvl,
//    case imgPopUpTstVacPulHand,
//    case imgPopUpTstVacPulHandx2,
//    case butPopUpTstVacManualLowLvl,
//    case butPopUpTstVacManualMidLvl,
//    case butPopUpTstVacManualHighLvl,
//    case butPopUpTstVacAuto,
//    case SwPopUpTstVacLowLvl,
//    case SwPopUpTstVacMidLvl,
//    case SwPopUpTstVacHighLvl,
//    case imgPopUpTstVacAUTOstatus,

//    //PopUp Test Vacuum 2 widgets
//    case PopUpTstVacSmall,
//    case imgPopUpVacSelBck,
//    case butPopUpTstVacSmallLowLvl,
//    case butPopUpTstVacSmallMedLvl,
//    case butPopUpTstVacSmallHighLvl,

//    //PopUp RFID widgets
//    case PopUpRFID,
//    case imgPopUpRFIDbckGnd,
//    case imgPopUpRFIDlabel,
//    case imgPopUpRFIDresult,
//    case butPopUpRFIDreuseLabel,
//    case NumVwrPopUpRFIDrestTime,

//    //PopUp Recommendation widgets
    case SwPopUpRecommInfo: emit infoSwitchEnabled(enable); break;
//    case PopUpRecomm,
//    case imgPopUpRecommbckGnd,
//    case ImgPopUpRecommCurved,
//    case ImgPopUpRecommTight,
//    case ImgPopUpRecommStright,
//    case ImgPopUpRecommTiny,
//    case ImgPopUpRecommTinyCurved,
//    case ImgPopUpRecommDouble,
//    case ImgPopUpRecommOval,
//    case ImgPopUpRecommOvalCurved,
//    case ImgPopUpRecommAngled,

//    //Menu Principal
//    case butTrtScrShowMainMenu,
//    case butTrtScrHideMainMenu,
//    case ButTrtScrHome,
//    case ButTrtScrCfg,
//    case ButTrtScrCalc,
//    case butTrtScrData,

//    case SwTrtScrAvisos,
//    case ImgTrtScrNotificacion,
//    case PopupTrtScrAvisos,
//    case imgPopUpTrtScrAvisoBckGND,
//    case imgPopUpTrtScrAvisoNivelAguaBajo,
//    case imgPopUpTrtScrAvisoNivelAguaMedio,
//    case imgPopUpTrtScrAvisoTempAmb,
//    case imgPopUpTrtScrAvisoRFID,
//    case imgPopUpTrtScrAvisoRTC,
//    case imgPopUpTrtScrAvisoFiltroAire,

//    //popUp's Error
//    case imgPopUpErrBckGndHP1,
//    case imgPopUpErrBckGndHP2,
//    case imgPopUpErrBckGndHP3,
//    case imgPopUpErrBckGndHP4,
//    case imgPopUpErrBckGndUC,
//    case NumVwrPopUpErrHP1,
//    case NumVwrPopUpErrHP2,
//    case NumVwrPopUpErrHP3,
//    case NumVwrPopUpErrHP4,
//    case NumVwrPopUpErrUC,
//    case imgPopUpErrMsgHP1,
//    case imgPopUpErrMsgHP2,
//    case imgPopUpErrMsgHP3,
//    case imgPopUpErrMsgHP4,
//    case imgPopUpErrMsgUC,
//    case butPopUpErrOkHP1,
//    case butPopUpErrOkHP2,
//    case butPopUpErrOkHP3,
//    case butPopUpErrOkHP4,
//    case butPopUpErrOkUC,
//    case NumVwrPopUpErrTRTtimeHP1,
//    case NumVwrPopUpErrTRTtimeHP2,
//    case NumVwrPopUpErrTRTtimeHP3,
//    case NumVwrPopUpErrTRTtimeHP4,

//    //PopUp's CleanUp
//    case imgPopUpCleanBckGndHP1,
//    case imgPopUpCleanBckGndHP2,
//    case imgPopUpCleanBckGndHP3,
//    case imgPopUpCleanBckGndHP4,
//    case NumVwrPopUpCleanHP1,
//    case NumVwrPopUpCleanHP2,
//    case NumVwrPopUpCleanHP3,
//    case NumVwrPopUpCleanHP4,
//    case butPopUpCleanHP1,
//    case butPopUpCleanHP2,
//    case butPopUpCleanHP3,
//    case butPopUpCleanHP4,
//    case butPopUpCleanYESHP1,
//    case butPopUpCleanYESHP2,
//    case butPopUpCleanYESHP3,
//    case butPopUpCleanYESHP4,
//    case butPopUpCleanNOHP1,
//    case butPopUpCleanNOHP2,
//    case butPopUpCleanNOHP3,
//    case butPopUpCleanNOHP4,
//    case imgPopUpCleanHP1,
//    case imgPopUpCleanHP2,
//    case imgPopUpCleanHP3,
//    case imgPopUpCleanHP4,
//    case butPopUpCleanCancelHP1,
//    case butPopUpCleanCancelHP2,
//    case butPopUpCleanCancelHP3,
//    case butPopUpCleanCancelHP4,
//    case NumVwrPopUpCleanNumCancelHP1,
//    case NumVwrPopUpCleanNumCancelHP2,
//    case NumVwrPopUpCleanNumCancelHP3,
//    case NumVwrPopUpCleanNumCancelHP4,


//    //Pantalla de la calculadora
//    case imgFondoCalcScreen,
//    case imgCuerpoCalc,
//    case NumVwrPantallaCalc,
//    case ButNum0Calc,
//    case ButNum1Calc,
//    case ButNum2Calc,
//    case ButNum3Calc,
//    case ButNum4Calc,
//    case ButNum5Calc,
//    case ButNum6Calc,
//    case ButNum7Calc,
//    case ButNum8Calc,
//    case ButNum9Calc,
//    case butMasCalc,
//    case butMenosCalc,
//    case ButEnterCalc,
//    case ButCECalc,
//    case butComaCalc,

//    //Menu principal - calculadora
//    case butCalcScrShowMainMenu,
//    case butCalcScrHideMainMenu,
//    case butCalcScrHome,
//    case butCalcScrCfg,
//    case imgCalcScrCalc,
//    case butCalcScrData,

//    case SwCalcScrAvisos,
//    case ImgCalcScrNotificacion,
//    case PopupCalcScrAvisos,
//    case imgPopUpCalcScrAvisoBckGND,
//    case imgPopUpCalcScrAvisoNivelAguaBajo,
//    case imgPopUpCalcScrAvisoNivelAguaMedio,
//    case imgPopUpCalcScrAvisoTempAmb,
//    case imgPopUpCalcScrAvisoRFID,
//    case imgPopUpCalcScrAvisoRTC,
//    case imgPopUpCalcScrAvisoFiltroAire,

//    //Pantalla de configuración
//    case imgFondoCfgScreen,
//    case imgVentanaCfgCastellano,
//    case butCfgActualizarSoftware,
//    case imgSoftwareProgressionUpdateBar,
//    case NumVwrModeloMaqCfg,
//    case NumVwrVersionSoftwareCfg,
//    case butCfgRecargaCoolant,
//    case SwCfgResuctionViewer,
//    case SwCfgTemperatureViewer,
//    case butCfgCleanUpHP1,
//    case butCfgCleanUpHP2,
//    case butCfgCleanUpHP3,
//    case butCfgCleanUpHP4,
//    case butCfgCleanUpRoundHP,
//    case imgCfgGPRScoverage,		//V7790

//    //Menu principal - configuracion
//    case butCfgScrShowMainMenu,
//    case butCfgScrHideMainMenu,
//    case butCfgScrHome,
//    case imgCfgScrCfg,
//    case butCfgScrCalc,
//    case butCfgScrData,

//    case SwCfgScrAvisos,
//    case ImgCfgScrNotificacion,
//    case PopupCfgScrAvisos,
//    case imgPopUpCfgScrAvisoBckGND,
//    case imgPopUpCfgScrAvisoNivelAguaBajo,
//    case imgPopUpCfgScrAvisoNivelAguaMedio,
//    case imgPopUpCfgScrAvisoTempAmb,
//    case imgPopUpCfgScrAvisoRFID,
//    case imgPopUpCfgScrAvisoRTC,
//    case imgPopUpCfgScrAvisoFiltroAire,

//    //Pantalla de idiomas
//    case imgFondoLanScreen,

//    case SwLanFrances,
//    case SwLanCastellano,
//    case SwLanIngles,
//    case SwLanItaliano,
//    case SwLanAleman,
//    case SwLanPolaco,
//    case SwLanRuso,
//    case SwLanPortugues,
//    case SwLanChino,
//    case SwLanJapones,
//    case SwLanCoreano,

//    //Menu principal - idiomas
//    case butLanScrShowMainMenu,
//    case butLanScrHideMainMenu,
//    case butLanScrHome,
//    case butLanScrCfg,
//    case butLanScrCalc,
//    case imgLanScrData,

//    case SwLanScrAvisos,
//    case ImgLanScrNotificacion,
//    case PopupLanScrAvisos,
//    case imgPopUpLanScrAvisoBckGND,
//    case imgPopUpLanScrAvisoNivelAguaBajo,
//    case imgPopUpLanScrAvisoNivelAguaMedio,
//    case imgPopUpLanScrAvisoTempAmb,
//    case imgPopUpLanScrAvisoRFID,
//    case imgPopUpLanScrAvisoRTC,
//    case imgPopUpLanScrAvisoFiltroAire,

//    //Pantalla de SAT
//    case imgFondoSATscreen,
//    case butHomeSATscreen,

//    case NumVwrPaginaSATscreen,
//    case butNextPagSATscreen,
//    case butPrevPagSATscreen,

//    case imgVwr1,
//    case imgVwr2,
//    case imgVwr3,
//    case imgVwr4,
//    case imgVwr5,
//    case imgVwr6,
//    case imgVwr7,
//    case imgVwr8,
//    case imgVwr9,
//    case imgVwr10_1,
//    case imgVwr10_2,
//    case imgVwr11_1,
//    case imgVwr11_2,
//    case imgVwr12_1,
//    case imgVwr12_2,
//    case imgVwr13_1,
//    case imgVwr13_2,
//    case imgVwr14_1,
//    case imgVwr14_2,
//    case imgVwr15_1,
//    case imgVwr15_2,
//    case imgVwr16_1,
//    case imgVwr16_2,
//    case imgVwr17_1,
//    case imgVwr17_2,
//    case imgVwr18_1,
//    case imgVwr18_2,
//    case imgVwr19_1,
//    case imgVwr19_2,
//    case imgVwr20_1,
//    case imgVwr20_2,
//    case imgVwr21_1,
//    case imgVwr21_2,
//    case imgVwr22_1,
//    case imgVwr22_2,
//    case imgVwr23_1,
//    case imgVwr23_2,
//    case imgVwr24_1,
//    case imgVwr24_2,
//    case imgVwr25_1,
//    case imgVwr25_2,
//    case imgVwr26_1,
//    case imgVwr26_2,
//    case imgVwr27_1,
//    case imgVwr27_2,
//    case imgVwr28_1,
//    case imgVwr28_2,

//    case NumVwr1,
//    case NumVwr2,
//    case NumVwr3,
//    case NumVwr4,
//    case NumVwr5,
//    case NumVwr6,
//    case NumVwr7,
//    case NumVwr8,
//    case NumVwr9,
//    case NumVwr10,
//    case NumVwr11,
//    case NumVwr12,
//    case NumVwr13,
//    case NumVwr14,
//    case NumVwr15,
//    case NumVwr16,
//    case NumVwr17,
//    case NumVwr18,
//    case NumVwr19,
//    case NumVwr20,
//    case NumVwr21,
//    case NumVwr22,
//    case NumVwr23,
//    case NumVwr24,
//    case NumVwr25,
//    case NumVwr26,
//    case NumVwr27,
//    case NumVwr28,

//    case imgVacuum,
//    case imgFrio,
//    case imgRFID,
//    case imgTestLed,
//    case imgTestLedStatus,
//    case imgTestLedRGD,
//    case SwVacuum,
//    case SwFrio,
//    case SwRFID,
//    case SwTestLed,
//    case SwTestLedRGB,

//    case PopupErrorSAT,
//    case imgVwrFondoErrorSAT,
//    case NumVwrError1,
//    case NumVwrError2,
//    case NumVwrError3,
//    case NumVwrError4,
//    case NumVwrError5,
//    case butOkerr,

//    //Pantalla de FATIGA
//    case imgFondoFATIGAscreen,
//    case butHomeFATIGAscreen,

//    case imgStep1,
//    case imgStep1status,
//    case imgStep2,
//    case imgStep2status,
//    case imgStep3,
//    case imgStep3status,
//    case imgStep4,
//    case imgStep4statusHP1,
//    case imgStep4statusHP2,
//    case imgStep4statusHP3,
//    case imgStep4statusHP4,
//    case imgStep5,
//    case imgStep5statusHP1,
//    case imgStep5statusHP2,
//    case imgStep5statusHP3,
//    case imgStep5statusHP4,
//    case imgStep6,
//    case imgStep6status,
//    case imgStep7,
//    case imgStep7status,

//    case NumVwrTempAmb,
//    case NumVwrTempBomba,
//    case NumVwrTempRetorno,
//    case NumVwrCaudalRetorno,
//    case NumVwrVtobera,
//    case NumVwrRth,
//    case NumVwrCPI,
//    case NumVwrCaudalRetornoHP1,
//    case NumVwrCaudalRetornoHP2,
//    case NumVwrCaudalRetornoHP3,
//    case NumVwrCaudalRetornoHP4,
//    case NumVwrVacuumHP1,
//    case NumVwrVacuumHP2,
//    case NumVwrVacuumHP3,
//    case NumVwrVacuumHP4,
//    case NumVwrFatigaTime,
//    case NumVwrErrFatiga1,
//    case NumVwrErrFatiga2,
//    case NumVwrErrFatiga3,
//    case NumVwrErrFatiga4,
//    case NumVwrErrFatiga5,

//    case imgVwrVAC1,
//    case imgVwrVAC2,
//    case imgVwrVAC3,
//    case imgVwrVAC4,
//    case imgVwrCaudal1,
//    case imgVwrCaudal2,
//    case imgVwrCaudal3,
//    case imgVwrCaudal4,
//    case imgVwrTempAmb,
//    case imgVwrTempBomba,
//    case imgVwrTempRetorno,
//    case imgVwrCaudalRetorno,
//    case imgVwrVtobera,
//    case imgVwrRth,
//    case imgVwrCPI,				//447

//    case SwFatigueFailBeep,
    default: /* Do nothing */ break;
    }

    return 0;
}

void WidgetsWrapper::GUIsetImgViewerImage(uint32 id, uint32 idImg)
{
    switch (id) {
    case ImgModelTextHP1: emit hpControlPanelModelTextSet( AppEnumsNs::APP_GUI_HP1_ID, (EAppGUIimageIDlist)idImg ); break;
    case ImgModelTextHP2: emit hpControlPanelModelTextSet( AppEnumsNs::APP_GUI_HP2_ID, (EAppGUIimageIDlist)idImg ); break;
    case ImgModelTextHP3: emit hpControlPanelModelTextSet( AppEnumsNs::APP_GUI_HP3_ID, (EAppGUIimageIDlist)idImg ); break;
    case ImgModelTextHP4: emit hpControlPanelModelTextSet( AppEnumsNs::APP_GUI_HP4_ID, (EAppGUIimageIDlist)idImg ); break;
    case ImgColourCtrlPnlBckGndHP1: emit hpControlPanelColorSet(AppEnumsNs::APP_GUI_HP1_ID, (uint8)idImg); break;
    case ImgColourCtrlPnlBckGndHP2: emit hpControlPanelColorSet(AppEnumsNs::APP_GUI_HP2_ID, (uint8)idImg); break;
    case ImgColourCtrlPnlBckGndHP3: emit hpControlPanelColorSet(AppEnumsNs::APP_GUI_HP3_ID, (uint8)idImg); break;
    case ImgColourCtrlPnlBckGndHP4: emit hpControlPanelColorSet(AppEnumsNs::APP_GUI_HP4_ID, (uint8)idImg); break;
    default: break;
    }
}

void WidgetsWrapper::GUIsetImgViewerPosition(uint32 id, uint16 posx, uint16 posy)
{
    EAppGUI_HPsIDs hpIndex = APP_GUI_MAXNUM_HP;

    switch(id) {
    case ImgSelectedTrtZoneHP1: hpIndex = AppEnumsNs::APP_GUI_HP1_ID; break;
    case ImgSelectedTrtZoneHP2: hpIndex = AppEnumsNs::APP_GUI_HP2_ID; break;
    case ImgSelectedTrtZoneHP3: hpIndex = AppEnumsNs::APP_GUI_HP3_ID; break;
    case ImgSelectedTrtZoneHP4: hpIndex = AppEnumsNs::APP_GUI_HP4_ID; break;
    default: break;
    }

    emit trtDotFullBodyPositionChanged(hpIndex, posx, posy);
}

void WidgetsWrapper::GUIsetHpControlPanelImgButton(uint32 id, EAppGUIimageIDlist idImg)
{
    EAppGUI_HPsIDs hpIndex = APP_GUI_MAXNUM_HP;

    switch (id) {
    case ButModelImageHP1:
        hpIndex = AppEnumsNs::APP_GUI_HP1_ID;
        break;
    case ButModelImageHP2:
        hpIndex = AppEnumsNs::APP_GUI_HP2_ID;
        break;
    case ButModelImageHP3:
        hpIndex = AppEnumsNs::APP_GUI_HP3_ID;
        break;
    case ButModelImageHP4:
        hpIndex = AppEnumsNs::APP_GUI_HP4_ID;
        break;
    default: break;
    }

    emit hpControlPanelButtonImagesSet(hpIndex, idImg);
}

void WidgetsWrapper::GUISetTreatmentTimerBackground(EAppGUI_HPsIDs hpIndex, bool isSelectable)
{
    emit treatmentTimerBackgroundSet(hpIndex, isSelectable);
}

void WidgetsWrapper::GUIactiveWarningsPopUp()
{
    emit warningsPopupDisplayed(true);
}

void WidgetsWrapper::GUIdisableWarningsPopUp()
{
    emit warningsPopupDisplayed(false);
}

void WidgetsWrapper::GUIWarningIconActivate(EAppGUImachineWarnings warningId, bool isActive)
{
    emit warningActivated(warningId, isActive);
}

void WidgetsWrapper::GUIUpdateVacuumButton( EAppGUI_HPsIDs HPindex, EAppGUIVacButStates butt_states, int vacuumLevel )
{
    emit vacuumButtonUpdated(HPindex, butt_states, vacuumLevel);
}

void WidgetsWrapper::GUIUpdatePlayButton(EAppGUI_HPsIDs HPindex, EAppGUIPlayButStates butt_states)
{
    emit playButtonUpdated(HPindex, butt_states);
}

void WidgetsWrapper::GUIUpdateTimeButton(EAppGUI_HPsIDs HPindex, EAppGUITimeButStates butt_states)
{
    emit timeButtonUpdated(HPindex, butt_states);
}

void WidgetsWrapper::GUIactivePopUp(EAppGUIwidgetIDlist popupWidgetId)
{
    switch (popupWidgetId) {
    case PopUpRecomm: emit recommendedHpsPopupActivated(true); break;
    case PopUpRFID: emit rfidPopupActivated(true); break;
    case PopUpTstVac: emit testVacuumPopupActivated(true); break;
    default: break;
    }
}

void WidgetsWrapper::GUIdisablePopUp(EAppGUIwidgetIDlist popupWidgetId)
{
    switch (popupWidgetId) {
    case PopUpRecomm: emit recommendedHpsPopupActivated(false); break;
    case PopUpRFID: emit rfidPopupActivated(false); break;
    case PopUpTstVac: emit testVacuumPopupActivated(false); break;
    default: break;
    }
}

void WidgetsWrapper::GUIsetTimePopUp(EAppGUI_HPsIDs HPindex, EAppGUITimePopUpState popupState)
{
    emit timePopUpSet(HPindex, popupState);
}

QString WidgetsWrapper::calcNumber()
{
    return calcNumberStr;
}

QString WidgetsWrapper::confModel()
{
    return confModelStr;
}

QString WidgetsWrapper::confVersion()
{
    return confVersionStr;
}

void WidgetsWrapper::setCalcNumber(QString txt)
{
    if (txt == calcNumberStr)
    {
        return;
    }
    else
    {
        calcNumberStr = txt;
        emit calcNumberChanged(calcNumberStr);
    }
}

void WidgetsWrapper::setConfModel(QString txt)
{
    if (txt == confModelStr)
    {
        return;
    }
    else
    {
        confModelStr = txt;
        emit confModelChanged(confModelStr);
    }
}

void WidgetsWrapper::setConfVersion(QString txt)
{
    if (txt == confVersionStr)
    {
        return;
    }
    else
    {
        confVersionStr = txt;
        emit confVersionChanged(confVersionStr);
    }
}

void WidgetsWrapper::float_to_string(double f, char r[], uint8 dec)
{
    long long int length, length2, i, iNumber, coma_position, sign, coma_space;
    double fNumber2, fNumber_in;

    coma_space = 1;		//espacio reservado para la coma
    sign = -1;   		//inicialización de la variable?
    if (f < 0)			//Si el valor es negativo
    {
        sign = '-';		//asignamos al signo el número del caracter menos
        f *= -1;		//ponemos positivo el número
    }

    fNumber_in = f;		//Numero introducido
    fNumber2 = f;		//guardamos el valor como float
    iNumber = f;			//casteamos el valor como long long int, eliminando los decimales
    length = 0;  		//inicialización de la variable de la longitud del número previo a la coma
    length2 = 0;		//inicialización de la variable de la lontitud del número posterior a la coma


    while( (fNumber2 - (float)iNumber) != 0.0 && !((fNumber2 - (float)iNumber) < 0.0) )		//le restamos al númeor con decimales la parte entera y se comprueba si vale 0 y si es mayor que 0.0
    {
        fNumber2 = f * (n_tu(10.0, length2 + 1));		//desplazamos a la izquierda de la coma el número (28.47 --> 284.7) multipicandolo por 10.
        iNumber = fNumber2;								//actualizamos los valores para volver a comprobar en la condición del while si el número se ha quedado sin decimales

        length2++;										//control del número de decimales
    }

    /* Calculate length decimal part */
    for (length = (f >= 1) ? 0 : 1; f >= 1; length++)	//Bucle empleado para el calculo de la longitud de la parte entera del número
        f /= 10;

    coma_position = length;						//asignamos la posición a la coma
    if (length2 > 0) length += coma_space;      // If there are digits in the decimal part, add the comma length.
    length = length + dec;			//calculamos la longitud total con la parte entera, la decimal
    iNumber = fNumber_in * (n_tu(10.0, dec));		//calculamos el número completo tomando la parte decimal como entera (24.95 --> 2495)
    if (sign == '-')							//En caso de que tengamos signo negativo
    {
        length++;								//incrementamos la longitud de caracteres
        coma_position++;						//y desplazamos la posición de la coma
    }

    for (i = length; i >= 0 ; i--)						//Recorremos el vector de caracteres desde el valor superior (la longitud completa del número)
    {
        if (i == (length))				r[i] = '\0';	//Para indicar el final del número
        else if(i == (coma_position))	r[i] = '.';		//colocar la coma
        else if(sign == '-' && i == 0)	r[i] = '-';		//colocar el signo
        else
        {
            r[i] = (iNumber % 10) + '0';					//sacar el número a representar en la posicion indicada
            iNumber /=10;								//actualizando el número quitando el ya guardado para representar
        }
    }
}

int WidgetsWrapper::n_tu(int number, int count)
{
    int result = 1;				//Si el contador directamente es 0 el resultado devuelto será 1
    while(count-- > 0)			//mientras que el contador sea superior a 0. Además se va reduciendo la cuenta a cada vuelta
        result *= number;		//se acumula el número pasado por parametro

    return result;				//se devuelve el acumulado
}
