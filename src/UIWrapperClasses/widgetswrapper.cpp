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

void WidgetsWrapper::dotZoneAssignHp(uint8 dot, EAppGUI_HPsIDs hpIndex)
{
    emit dotZoneHpAssigned(dot, hpIndex);
}

void WidgetsWrapper::dotZoneSelect(uint8 dot, bool isSelected)
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
    case numVwrTimeHP1: emit treatmentTimerSet(APP_GUI_HP1_ID, prova); break;
    case numVwrTimeHP2: emit treatmentTimerSet(APP_GUI_HP2_ID, prova); break;
    case numVwrTimeHP3: emit treatmentTimerSet(APP_GUI_HP3_ID, prova); break;
    case numVwrTimeHP4: emit treatmentTimerSet(APP_GUI_HP4_ID, prova); break;
    case numVwrResucctionCountHP1: emit resuctionCountChanged(APP_GUI_HP1_ID, num); break;
    case numVwrResucctionCountHP2: emit resuctionCountChanged(APP_GUI_HP2_ID, num); break;
    case numVwrResucctionCountHP3: emit resuctionCountChanged(APP_GUI_HP3_ID, num); break;
    case numVwrResucctionCountHP4: emit resuctionCountChanged(APP_GUI_HP4_ID, num); break;
    case numVwrPopUpRFIDrestTime: break;
    case numVwrPopUpErrHP1: break;
    case numVwrPopUpErrHP2: break;
    case numVwrPopUpErrHP3: break;
    case numVwrPopUpErrHP4: break;
    case numVwrPopUpErrUC: break;
    case numVwrPopUpErrTRTtimeHP1: break;
    case numVwrPopUpErrTRTtimeHP2: break;
    case numVwrPopUpErrTRTtimeHP3: break;
    case numVwrPopUpErrTRTtimeHP4: break;
    case numVwrPopUpCleanHP1: break;
    case numVwrPopUpCleanHP2: break;
    case numVwrPopUpCleanHP3: break;
    case numVwrPopUpCleanHP4: break;
    case numVwrPopUpCleanNumCancelHP1: break;
    case numVwrPopUpCleanNumCancelHP2: break;
    case numVwrPopUpCleanNumCancelHP3: break;
    case numVwrPopUpCleanNumCancelHP4: break;
    case numVwrPantallaCalc:        setCalcNumber(qstr); break;
    case numVwrModeloMaqCfg:        setConfModel(qstr); break;
    case numVwrVersionSoftwareCfg:  setConfVersion(qstr); break;
    case numVwrPaginaSATscreen: break;
    case numVwr1: break;
    case numVwr2: break;
    case numVwr3: break;
    case numVwr4: break;
    case numVwr5: break;
    case numVwr6: break;
    case numVwr7: break;
    case numVwr8: break;
    case numVwr9: break;
    case numVwr10: break;
    case numVwr11: break;
    case numVwr12: break;
    case numVwr13: break;
    case numVwr14: break;
    case numVwr15: break;
    case numVwr16: break;
    case numVwr17: break;
    case numVwr18: break;
    case numVwr19: break;
    case numVwr20: break;
    case numVwr21: break;
    case numVwr22: break;
    case numVwr23: break;
    case numVwr24: break;
    case numVwr25: break;
    case numVwr26: break;
    case numVwr27: break;
    case numVwr28: break;
    case numVwrError1: break;
    case numVwrError2: break;
    case numVwrError3: break;
    case numVwrError4: break;
    case numVwrError5: break;
    case numVwrTempAmb: break;
    case numVwrTempBomba: break;
    case numVwrTempRetorno: break;
    case numVwrCaudalRetorno: break;
    case numVwrVtobera: break;
    case numVwrRth: break;
    case numVwrCPI: break;
    case numVwrCaudalRetornoHP1: break;
    case numVwrCaudalRetornoHP2: break;
    case numVwrCaudalRetornoHP3: break;
    case numVwrCaudalRetornoHP4: break;
    case numVwrVacuumHP1: break;
    case numVwrVacuumHP2: break;
    case numVwrVacuumHP3: break;
    case numVwrVacuumHP4: break;
    case numVwrFatigaTime: break;
    case numVwrErrFatiga1: break;
    case numVwrErrFatiga2: break;
    case numVwrErrFatiga3: break;
    case numVwrErrFatiga4: break;
    case numVwrErrFatiga5: break;
    default: /* Do nothing. */ break;
    }
}

void WidgetsWrapper::GUIsetSwitchStatus(uint32 id, uint8 OnOff)
{
    switch (id) {
    case swInitScrAvisos: break;
    case swCtrlPnlTstVacHP1: break;
    case swCtrlPnlTstVacHP2: break;
    case swCtrlPnlTstVacHP3: break;
    case swCtrlPnlTstVacHP4: break;
    case swDotZone0: break;
    case swDotZone1: break;
    case swDotZone2: break;
    case swDotZone3: break;
    case swDotZone4: break;
    case swDotZone5: break;
    case swDotZone6: break;
    case swDotZone7: break;
    case swDotZone8: break;
    case swDotZone9: break;
    case swDotZone10: break;
    case swDotZone11: break;
    case swDotZone12: break;
    case swDotZone13: break;
    case swDotZone14: break;
    case swPopUpTstVacLowLvl: break;
    case swPopUpTstVacMidLvl: break;
    case swPopUpTstVacHighLvl: break;
    case swPopUpRecommInfo: break;
    case swTrtScrAvisos: break;
    case swCalcScrAvisos: break;
    case swCfgResuctionViewer: break;
    case swCfgTemperatureViewer: break;
    case swCfgScrAvisos: break;
    case swLanFrances: break;
    case swLanCastellano: break;
    case swLanIngles: break;
    case swLanItaliano: break;
    case swLanAleman: break;
    case swLanPolaco: break;
    case swLanRuso: break;
    case swLanPortugues: break;
    case swLanChino: break;
    case swLanJapones: break;
    case swLanCoreano: break;
    case swLanScrAvisos: break;
    case swVacuum: break;
    case swFrio: break;
    case swRFID: break;
    case swTestLed: break;
    case swTestLedRGB: break;
    case swFatigueFailBeep: break;
    default: /* Do nothing */ break;
    }
}

uint16 WidgetsWrapper::GUIsetWidgetVisibility(uint32 id, uint8 vis)
{
    switch(id) {
    //PANTALLA DE CARGA
//    case imgLoadScrBckGnd,
//    case imgLoadAnim1,
//    case imgLoadAnim2,
//    case imgLoadAnim3,
//    case imgLoadAnim4,
//    case imgLoadAnim5,
//    case imgLoadAnim6,
//    case imgLoadAnim7,
//    case imgLoadAnim8,

//    //PANTALLA DE INICIO
//    case imgInitScrBckGnd,
//    case butSelectWoman,
//    case butSelectMan,
//    case imgInitGPRScoverage,		//V7790

//    //Menu principal
//    case butInitScrShowMainMenu,
//    case butInitScrHideMainMenu,
//    case imgInitScrHome,
//    case butInitScrCfg,
//    case butInitScrCalc,
//    case butInitScrData,

//    case swInitScrAvisos,
//    case imgInitScrNotificacion,
//    case popupInitScrAvisos,
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
//    case imgColourCtrlPnlBckGndHP1,
//    case imgColourCtrlPnlBckGndHP2,
//    case imgColourCtrlPnlBckGndHP3,
//    case imgColourCtrlPnlBckGndHP4,

    //Indicadores de accion del HP cuando activos, los inactivos forman parte del fondo
    case imgCtrlPnlRFIDblinkHP1: emit indicatorRfidVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case imgCtrlPnlRFIDblinkHP2: emit indicatorRfidVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case imgCtrlPnlRFIDblinkHP3: emit indicatorRfidVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case imgCtrlPnlRFIDblinkHP4: emit indicatorRfidVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case imgCtrlPnlPulBlinkHP1: emit indicatorButtonVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case imgCtrlPnlPulBlinkHP2: emit indicatorButtonVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case imgCtrlPnlPulBlinkHP3: emit indicatorButtonVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case imgCtrlPnlPulBlinkHP4: emit indicatorButtonVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case imgCtrlPnlVacBlinkHP1: emit indicatorVacuumVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case imgCtrlPnlVacBlinkHP2: emit indicatorVacuumVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case imgCtrlPnlVacBlinkHP3: emit indicatorVacuumVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case imgCtrlPnlVacBlinkHP4: emit indicatorVacuumVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case imgCtrlPnlCoolingBlinkHP1: emit indicatorCoolingVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case imgCtrlPnlCoolingBlinkHP2: emit indicatorCoolingVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case imgCtrlPnlCoolingBlinkHP3: emit indicatorCoolingVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case imgCtrlPnlCoolingBlinkHP4: emit indicatorCoolingVisibilityChanged(APP_GUI_HP1_ID, vis); break;

//    //Botones del panel de control de PLAY y Test Vacum
//    case butCtrlPnlPlayHP1,
//    case butCtrlPnlPlayHP2,
//    case butCtrlPnlPlayHP3,
//    case butCtrlPnlPlayHP4,
//    case swCtrlPnlTstVacHP1,
//    case swCtrlPnlTstVacHP2,
//    case swCtrlPnlTstVacHP3,
//    case swCtrlPnlTstVacHP4,

//    //Botones (switch) que permite seleccionar modo de tratamiento AUTO o MANUAL
//    case butSwtchModeAutoManualHP1,
//    case butSwtchModeAutoManualHP2,
//    case butSwtchModeAutoManualHP3,
//    case butSwtchModeAutoManualHP4,

    //Visores de tiempo restante de trt y boton de seleccion de tiempo
    case numVwrTimeHP1: emit timeRemainingVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case numVwrTimeHP2: emit timeRemainingVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case numVwrTimeHP3: emit timeRemainingVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case numVwrTimeHP4: emit timeRemainingVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case butSelectTimeHP1: emit timeSelectButtonVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case butSelectTimeHP2: emit timeSelectButtonVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case butSelectTimeHP3: emit timeSelectButtonVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case butSelectTimeHP4: emit timeSelectButtonVisibilityChanged(APP_GUI_HP4_ID, vis); break;
//    case butVwrTemperatureHP1,
//    case butVwrTemperatureHP2,
//    case butVwrTemperatureHP3,
//    case butVwrTemperatureHP4,

    //Visor numerico para contabilizar resucciones
    case numVwrResucctionCountHP1: emit resuctionCountVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case numVwrResucctionCountHP2: emit resuctionCountVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case numVwrResucctionCountHP3: emit resuctionCountVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case numVwrResucctionCountHP4: emit resuctionCountVisibilityChanged(APP_GUI_HP4_ID, vis); break;

//    //Boton con la imagen e imagen con el texto del modelo
//    case imgModelTextHP1,
//    case imgModelTextHP2,
//    case imgModelTextHP3,
//    case imgModelTextHP4,
//    case butModelImageHP1,
//    case butModelImageHP2,
//    case butModelImageHP3,
//    case butModelImageHP4,

//    //Botonoes de recogida y despliegue del panel de control
//    case butHideControlPanelHP1,
//    case butHideControlPanelHP2,
//    case butHideControlPanelHP3,
//    case butHideControlPanelHP4,
//    case butShowControlPanelHP1,
//    case butShowControlPanelHP2,
//    case butShowControlPanelHP3,
//    case butShowControlPanelHP4,

//    //Botones de selección de Full body
//    case butFullBodyTorso,
//    case butFullBodyPiernas,
//    case butFullBodyBrazos,
//    case butFullBodyEspalda,
//    case butFullBodyPiernaMuslo,
//    case butFullBodyCuello,

//    //Puntos seleccion de zona de tratamiento cuando zoom
//    case swDotZone0,
//    case swDotZone1,
//    case swDotZone2,
//    case swDotZone3,
//    case swDotZone4,
//    case swDotZone5,
//    case swDotZone6,
//    case swDotZone7,
//    case swDotZone8,
//    case swDotZone9,
//    case swDotZone10,
//    case swDotZone11,
//    case swDotZone12,
//    case swDotZone13,
//    case swDotZone14,

    //Punto seleccionado para tratamiento con ese HP a mostrar en full body
    case imgSelectedTrtZoneHP1: trtDotFullBodyVisibilityChanged(APP_GUI_HP1_ID, vis); break;
    case imgSelectedTrtZoneHP2: trtDotFullBodyVisibilityChanged(APP_GUI_HP2_ID, vis); break;
    case imgSelectedTrtZoneHP3: trtDotFullBodyVisibilityChanged(APP_GUI_HP3_ID, vis); break;
    case imgSelectedTrtZoneHP4: trtDotFullBodyVisibilityChanged(APP_GUI_HP4_ID, vis); break;

//    //POPUP's
//    //Common
    case butPopUpReturn: emit returnButtonVisibilityChanged(vis); break;
//    case imgPopUpHPcolorBar,

//    //PopUp Time widgets
//    case popUpTime,
//    case butPopUpTime50min,
//    case butPopUpTime70min,
//    case imgPopUpTime1sel,
//    case imgPopUpTime2sel,

//    //PopUp Test Vacum widgets
//    case popUpTstVac,
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
//    case swPopUpTstVacLowLvl,
//    case swPopUpTstVacMidLvl,
//    case swPopUpTstVacHighLvl,
//    case imgPopUpTstVacAUTOstatus,

//    //PopUp Test Vacuum 2 widgets
//    case popUpTstVacSmall,
//    case imgPopUpVacSelBck,
//    case butPopUpTstVacSmallLowLvl,
//    case butPopUpTstVacSmallMedLvl,
//    case butPopUpTstVacSmallHighLvl,

//    //PopUp RFID widgets
//    case popUpRFID,
//    case imgPopUpRFIDbckGnd,
//    case imgPopUpRFIDlabel,
//    case imgPopUpRFIDresult,
//    case butPopUpRFIDreuseLabel,
//    case numVwrPopUpRFIDrestTime,

//    //PopUp Recommendation widgets
    case swPopUpRecommInfo: emit infoSwitchVisibilityChanged(vis); break;
//    case popUpRecomm,
//    case imgPopUpRecommbckGnd,
//    case imgPopUpRecommCurved,
//    case imgPopUpRecommTight,
//    case imgPopUpRecommStright,
//    case imgPopUpRecommTiny,
//    case imgPopUpRecommTinyCurved,
//    case imgPopUpRecommDouble,
//    case imgPopUpRecommOval,
//    case imgPopUpRecommOvalCurved,
//    case imgPopUpRecommAngled,

//    //Menu Principal
//    case butTrtScrShowMainMenu,
//    case butTrtScrHideMainMenu,
//    case butTrtScrHome,
//    case butTrtScrCfg,
//    case butTrtScrCalc,
//    case butTrtScrData,

//    case swTrtScrAvisos,
//    case imgTrtScrNotificacion,
//    case popupTrtScrAvisos,
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
//    case numVwrPopUpErrHP1,
//    case numVwrPopUpErrHP2,
//    case numVwrPopUpErrHP3,
//    case numVwrPopUpErrHP4,
//    case numVwrPopUpErrUC,
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
//    case numVwrPopUpErrTRTtimeHP1,
//    case numVwrPopUpErrTRTtimeHP2,
//    case numVwrPopUpErrTRTtimeHP3,
//    case numVwrPopUpErrTRTtimeHP4,

//    //PopUp's CleanUp
//    case imgPopUpCleanBckGndHP1,
//    case imgPopUpCleanBckGndHP2,
//    case imgPopUpCleanBckGndHP3,
//    case imgPopUpCleanBckGndHP4,
//    case numVwrPopUpCleanHP1,
//    case numVwrPopUpCleanHP2,
//    case numVwrPopUpCleanHP3,
//    case numVwrPopUpCleanHP4,
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
//    case numVwrPopUpCleanNumCancelHP1,
//    case numVwrPopUpCleanNumCancelHP2,
//    case numVwrPopUpCleanNumCancelHP3,
//    case numVwrPopUpCleanNumCancelHP4,


//    //Pantalla de la calculadora
//    case imgFondoCalcScreen,
//    case imgCuerpoCalc,
//    case numVwrPantallaCalc,
//    case butNum0Calc,
//    case butNum1Calc,
//    case butNum2Calc,
//    case butNum3Calc,
//    case butNum4Calc,
//    case butNum5Calc,
//    case butNum6Calc,
//    case butNum7Calc,
//    case butNum8Calc,
//    case butNum9Calc,
//    case butMasCalc,
//    case butMenosCalc,
//    case butEnterCalc,
//    case butCECalc,
//    case butComaCalc,

//    //Menu principal - calculadora
//    case butCalcScrShowMainMenu,
//    case butCalcScrHideMainMenu,
//    case butCalcScrHome,
//    case butCalcScrCfg,
//    case imgCalcScrCalc,
//    case butCalcScrData,

//    case swCalcScrAvisos,
//    case imgCalcScrNotificacion,
//    case popupCalcScrAvisos,
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
//    case numVwrModeloMaqCfg,
//    case numVwrVersionSoftwareCfg,
//    case butCfgRecargaCoolant,
//    case swCfgResuctionViewer,
//    case swCfgTemperatureViewer,
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

//    case swCfgScrAvisos,
//    case imgCfgScrNotificacion,
//    case popupCfgScrAvisos,
//    case imgPopUpCfgScrAvisoBckGND,
//    case imgPopUpCfgScrAvisoNivelAguaBajo,
//    case imgPopUpCfgScrAvisoNivelAguaMedio,
//    case imgPopUpCfgScrAvisoTempAmb,
//    case imgPopUpCfgScrAvisoRFID,
//    case imgPopUpCfgScrAvisoRTC,
//    case imgPopUpCfgScrAvisoFiltroAire,

//    //Pantalla de idiomas
//    case imgFondoLanScreen,

//    case swLanFrances,
//    case swLanCastellano,
//    case swLanIngles,
//    case swLanItaliano,
//    case swLanAleman,
//    case swLanPolaco,
//    case swLanRuso,
//    case swLanPortugues,
//    case swLanChino,
//    case swLanJapones,
//    case swLanCoreano,

//    //Menu principal - idiomas
//    case butLanScrShowMainMenu,
//    case butLanScrHideMainMenu,
//    case butLanScrHome,
//    case butLanScrCfg,
//    case butLanScrCalc,
//    case imgLanScrData,

//    case swLanScrAvisos,
//    case imgLanScrNotificacion,
//    case popupLanScrAvisos,
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

//    case numVwrPaginaSATscreen,
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

//    case numVwr1,
//    case numVwr2,
//    case numVwr3,
//    case numVwr4,
//    case numVwr5,
//    case numVwr6,
//    case numVwr7,
//    case numVwr8,
//    case numVwr9,
//    case numVwr10,
//    case numVwr11,
//    case numVwr12,
//    case numVwr13,
//    case numVwr14,
//    case numVwr15,
//    case numVwr16,
//    case numVwr17,
//    case numVwr18,
//    case numVwr19,
//    case numVwr20,
//    case numVwr21,
//    case numVwr22,
//    case numVwr23,
//    case numVwr24,
//    case numVwr25,
//    case numVwr26,
//    case numVwr27,
//    case numVwr28,

//    case imgVacuum,
//    case imgFrio,
//    case imgRFID,
//    case imgTestLed,
//    case imgTestLedStatus,
//    case imgTestLedRGD,
//    case swVacuum,
//    case swFrio,
//    case swRFID,
//    case swTestLed,
//    case swTestLedRGB,

//    case PopupErrorSAT,
//    case imgVwrFondoErrorSAT,
//    case numVwrError1,
//    case numVwrError2,
//    case numVwrError3,
//    case numVwrError4,
//    case numVwrError5,
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

//    case numVwrTempAmb,
//    case numVwrTempBomba,
//    case numVwrTempRetorno,
//    case numVwrCaudalRetorno,
//    case numVwrVtobera,
//    case numVwrRth,
//    case numVwrCPI,
//    case numVwrCaudalRetornoHP1,
//    case numVwrCaudalRetornoHP2,
//    case numVwrCaudalRetornoHP3,
//    case numVwrCaudalRetornoHP4,
//    case numVwrVacuumHP1,
//    case numVwrVacuumHP2,
//    case numVwrVacuumHP3,
//    case numVwrVacuumHP4,
//    case numVwrFatigaTime,
//    case numVwrErrFatiga1,
//    case numVwrErrFatiga2,
//    case numVwrErrFatiga3,
//    case numVwrErrFatiga4,
//    case numVwrErrFatiga5,

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

//    case swFatigueFailBeep,

    case imgInitScrNotificacion:
    case imgTrtScrNotificacion:
    case imgCalcScrNotificacion:
    case imgCfgScrNotificacion:
    case imgLanScrNotificacion: emit mainMenuWarningNotificationDisplayed(vis); break;

    default: /* Do nothing */ break;
    }

    return 0;
}

uint16 WidgetsWrapper::GUIsetWidgetEnable(uint32 id, uint8 enable)
{
    switch(id) {
    //PANTALLA DE CARGA
//    case imgLoadScrBckGnd,
//    case imgLoadAnim1,
//    case imgLoadAnim2,
//    case imgLoadAnim3,
//    case imgLoadAnim4,
//    case imgLoadAnim5,
//    case imgLoadAnim6,
//    case imgLoadAnim7,
//    case imgLoadAnim8,

//    //PANTALLA DE INICIO
//    case imgInitScrBckGnd,
//    case butSelectWoman,
//    case butSelectMan,
//    case imgInitGPRScoverage,		//V7790

//    //Menu principal
//    case butInitScrShowMainMenu,
//    case butInitScrHideMainMenu,
//    case imgInitScrHome,
//    case butInitScrCfg,
//    case butInitScrCalc,
//    case butInitScrData,

//    case swInitScrAvisos,
//    case imgInitScrNotificacion,
//    case popupInitScrAvisos,
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
//    case imgColourCtrlPnlBckGndHP1,
//    case imgColourCtrlPnlBckGndHP2,
//    case imgColourCtrlPnlBckGndHP3,
//    case imgColourCtrlPnlBckGndHP4,

//    //Indicadores de accion del HP cuando activos, los inactivos forman parte del fondo
//    case imgCtrlPnlRFIDblinkHP1,
//    case imgCtrlPnlRFIDblinkHP2,
//    case imgCtrlPnlRFIDblinkHP3,
//    case imgCtrlPnlRFIDblinkHP4,
//    case imgCtrlPnlPulBlinkHP1,
//    case imgCtrlPnlPulBlinkHP2,
//    case imgCtrlPnlPulBlinkHP3,
//    case imgCtrlPnlPulBlinkHP4,
//    case imgCtrlPnlVacBlinkHP1,
//    case imgCtrlPnlVacBlinkHP2,
//    case imgCtrlPnlVacBlinkHP3,
//    case imgCtrlPnlVacBlinkHP4,
//    case imgCtrlPnlCoolingBlinkHP1,
//    case imgCtrlPnlCoolingBlinkHP2,
//    case imgCtrlPnlCoolingBlinkHP3,
//    case imgCtrlPnlCoolingBlinkHP4,

//    //Botones del panel de control de PLAY y Test Vacum
//    case butCtrlPnlPlayHP1,
//    case butCtrlPnlPlayHP2,
//    case butCtrlPnlPlayHP3,
//    case butCtrlPnlPlayHP4,
//    case swCtrlPnlTstVacHP1,
//    case swCtrlPnlTstVacHP2,
//    case swCtrlPnlTstVacHP3,
//    case swCtrlPnlTstVacHP4,

//    //Botones (switch) que permite seleccionar modo de tratamiento AUTO o MANUAL
//    case butSwtchModeAutoManualHP1,
//    case butSwtchModeAutoManualHP2,
//    case butSwtchModeAutoManualHP3,
//    case butSwtchModeAutoManualHP4,

//    //Visores de tiempo restante de trt y boton de seleccion de tiempo
//    case numVwrTimeHP1
//    case numVwrTimeHP2
//    case numVwrTimeHP3
//    case numVwrTimeHP4
//    case butSelectTimeHP1,
//    case butSelectTimeHP2,
//    case butSelectTimeHP3,
//    case butSelectTimeHP4,
    case butVwrTemperatureHP1: emit temperatureButtonEnabled(APP_GUI_HP1_ID, enable); break;
    case butVwrTemperatureHP2: emit temperatureButtonEnabled(APP_GUI_HP2_ID, enable); break;
    case butVwrTemperatureHP3: emit temperatureButtonEnabled(APP_GUI_HP3_ID, enable); break;
    case butVwrTemperatureHP4: emit temperatureButtonEnabled(APP_GUI_HP1_ID, enable); break;

//    //Visor numerico para contabilizar resucciones
//    case numVwrResucctionCountHP1,
//    case numVwrResucctionCountHP2,
//    case numVwrResucctionCountHP3,
//    case numVwrResucctionCountHP4,

//    //Boton con la imagen e imagen con el texto del modelo
//    case imgModelTextHP1,
//    case imgModelTextHP2,
//    case imgModelTextHP3,
//    case imgModelTextHP4,
    case butModelImageHP1: emit hpImageButtonEnabled(APP_GUI_HP1_ID, enable); break;
    case butModelImageHP2: emit hpImageButtonEnabled(APP_GUI_HP2_ID, enable); break;
    case butModelImageHP3: emit hpImageButtonEnabled(APP_GUI_HP3_ID, enable); break;
    case butModelImageHP4: emit hpImageButtonEnabled(APP_GUI_HP1_ID, enable); break;

    //Botonoes de recogida y despliegue del panel de control
    case butHideControlPanelHP1: emit controlPanelHideButtonEnabled(APP_GUI_HP1_ID, enable); break;
    case butHideControlPanelHP2: emit controlPanelHideButtonEnabled(APP_GUI_HP2_ID, enable); break;
    case butHideControlPanelHP3: emit controlPanelHideButtonEnabled(APP_GUI_HP3_ID, enable); break;
    case butHideControlPanelHP4: emit controlPanelHideButtonEnabled(APP_GUI_HP1_ID, enable); break;
//    case butShowControlPanelHP1,
//    case butShowControlPanelHP2,
//    case butShowControlPanelHP3,
//    case butShowControlPanelHP4,

//    //Botones de selección de Full body
//    case butFullBodyTorso,
//    case butFullBodyPiernas,
//    case butFullBodyBrazos,
//    case butFullBodyEspalda,
//    case butFullBodyPiernaMuslo,
//    case butFullBodyCuello,

    //Puntos seleccion de zona de tratamiento cuando zoom
    case swDotZone0:
    case swDotZone1:
    case swDotZone2:
    case swDotZone3:
    case swDotZone4:
    case swDotZone5:
    case swDotZone6:
    case swDotZone7:
    case swDotZone8:
    case swDotZone9:
    case swDotZone10:
    case swDotZone11:
    case swDotZone12:
    case swDotZone13:
    case swDotZone14: emit dotZoneEnabled((EAppGUIwidgetIDlist)id, enable); break;

//    //Punto seleccionado para tratamiento con ese HP a mostrar en full body
//    case imgSelectedTrtZoneHP1,
//    case imgSelectedTrtZoneHP2,
//    case imgSelectedTrtZoneHP3,
//    case imgSelectedTrtZoneHP4,

//    //POPUP's
//    //Common
    case butPopUpReturn: emit returnButtonEnabled(enable); break;
//    case imgPopUpHPcolorBar,

//    //PopUp Time widgets
//    case popUpTime,
//    case butPopUpTime50min,
//    case butPopUpTime70min,
//    case imgPopUpTime1sel,
//    case imgPopUpTime2sel,

//    //PopUp Test Vacum widgets
//    case popUpTstVac,
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
//    case swPopUpTstVacLowLvl,
//    case swPopUpTstVacMidLvl,
//    case swPopUpTstVacHighLvl,
//    case imgPopUpTstVacAUTOstatus,

//    //PopUp Test Vacuum 2 widgets
//    case popUpTstVacSmall,
//    case imgPopUpVacSelBck,
//    case butPopUpTstVacSmallLowLvl,
//    case butPopUpTstVacSmallMedLvl,
//    case butPopUpTstVacSmallHighLvl,

//    //PopUp RFID widgets
//    case popUpRFID,
//    case imgPopUpRFIDbckGnd,
//    case imgPopUpRFIDlabel,
//    case imgPopUpRFIDresult,
//    case butPopUpRFIDreuseLabel,
//    case numVwrPopUpRFIDrestTime,

//    //PopUp Recommendation widgets
    case swPopUpRecommInfo: emit infoSwitchEnabled(enable); break;
//    case popUpRecomm,
//    case imgPopUpRecommbckGnd,
//    case imgPopUpRecommCurved,
//    case imgPopUpRecommTight,
//    case imgPopUpRecommStright,
//    case imgPopUpRecommTiny,
//    case imgPopUpRecommTinyCurved,
//    case imgPopUpRecommDouble,
//    case imgPopUpRecommOval,
//    case imgPopUpRecommOvalCurved,
//    case imgPopUpRecommAngled,

//    //Menu Principal
//    case butTrtScrShowMainMenu,
//    case butTrtScrHideMainMenu,
//    case butTrtScrHome,
//    case butTrtScrCfg,
//    case butTrtScrCalc,
//    case butTrtScrData,

//    case swTrtScrAvisos,
//    case imgTrtScrNotificacion,
//    case popupTrtScrAvisos,
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
//    case numVwrPopUpErrHP1,
//    case numVwrPopUpErrHP2,
//    case numVwrPopUpErrHP3,
//    case numVwrPopUpErrHP4,
//    case numVwrPopUpErrUC,
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
//    case numVwrPopUpErrTRTtimeHP1,
//    case numVwrPopUpErrTRTtimeHP2,
//    case numVwrPopUpErrTRTtimeHP3,
//    case numVwrPopUpErrTRTtimeHP4,

//    //PopUp's CleanUp
//    case imgPopUpCleanBckGndHP1,
//    case imgPopUpCleanBckGndHP2,
//    case imgPopUpCleanBckGndHP3,
//    case imgPopUpCleanBckGndHP4,
//    case numVwrPopUpCleanHP1,
//    case numVwrPopUpCleanHP2,
//    case numVwrPopUpCleanHP3,
//    case numVwrPopUpCleanHP4,
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
//    case numVwrPopUpCleanNumCancelHP1,
//    case numVwrPopUpCleanNumCancelHP2,
//    case numVwrPopUpCleanNumCancelHP3,
//    case numVwrPopUpCleanNumCancelHP4,


//    //Pantalla de la calculadora
//    case imgFondoCalcScreen,
//    case imgCuerpoCalc,
//    case numVwrPantallaCalc,
//    case butNum0Calc,
//    case butNum1Calc,
//    case butNum2Calc,
//    case butNum3Calc,
//    case butNum4Calc,
//    case butNum5Calc,
//    case butNum6Calc,
//    case butNum7Calc,
//    case butNum8Calc,
//    case butNum9Calc,
//    case butMasCalc,
//    case butMenosCalc,
//    case butEnterCalc,
//    case butCECalc,
//    case butComaCalc,

//    //Menu principal - calculadora
//    case butCalcScrShowMainMenu,
//    case butCalcScrHideMainMenu,
//    case butCalcScrHome,
//    case butCalcScrCfg,
//    case imgCalcScrCalc,
//    case butCalcScrData,

//    case swCalcScrAvisos,
//    case imgCalcScrNotificacion,
//    case popupCalcScrAvisos,
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
//    case numVwrModeloMaqCfg,
//    case numVwrVersionSoftwareCfg,
//    case butCfgRecargaCoolant,
//    case swCfgResuctionViewer,
//    case swCfgTemperatureViewer,
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

//    case swCfgScrAvisos,
//    case imgCfgScrNotificacion,
//    case popupCfgScrAvisos,
//    case imgPopUpCfgScrAvisoBckGND,
//    case imgPopUpCfgScrAvisoNivelAguaBajo,
//    case imgPopUpCfgScrAvisoNivelAguaMedio,
//    case imgPopUpCfgScrAvisoTempAmb,
//    case imgPopUpCfgScrAvisoRFID,
//    case imgPopUpCfgScrAvisoRTC,
//    case imgPopUpCfgScrAvisoFiltroAire,

//    //Pantalla de idiomas
//    case imgFondoLanScreen,

//    case swLanFrances,
//    case swLanCastellano,
//    case swLanIngles,
//    case swLanItaliano,
//    case swLanAleman,
//    case swLanPolaco,
//    case swLanRuso,
//    case swLanPortugues,
//    case swLanChino,
//    case swLanJapones,
//    case swLanCoreano,

//    //Menu principal - idiomas
//    case butLanScrShowMainMenu,
//    case butLanScrHideMainMenu,
//    case butLanScrHome,
//    case butLanScrCfg,
//    case butLanScrCalc,
//    case imgLanScrData,

//    case swLanScrAvisos,
//    case imgLanScrNotificacion,
//    case popupLanScrAvisos,
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

//    case numVwrPaginaSATscreen,
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

//    case numVwr1,
//    case numVwr2,
//    case numVwr3,
//    case numVwr4,
//    case numVwr5,
//    case numVwr6,
//    case numVwr7,
//    case numVwr8,
//    case numVwr9,
//    case numVwr10,
//    case numVwr11,
//    case numVwr12,
//    case numVwr13,
//    case numVwr14,
//    case numVwr15,
//    case numVwr16,
//    case numVwr17,
//    case numVwr18,
//    case numVwr19,
//    case numVwr20,
//    case numVwr21,
//    case numVwr22,
//    case numVwr23,
//    case numVwr24,
//    case numVwr25,
//    case numVwr26,
//    case numVwr27,
//    case numVwr28,

//    case imgVacuum,
//    case imgFrio,
//    case imgRFID,
//    case imgTestLed,
//    case imgTestLedStatus,
//    case imgTestLedRGD,
//    case swVacuum,
//    case swFrio,
//    case swRFID,
//    case swTestLed,
//    case swTestLedRGB,

//    case PopupErrorSAT,
//    case imgVwrFondoErrorSAT,
//    case numVwrError1,
//    case numVwrError2,
//    case numVwrError3,
//    case numVwrError4,
//    case numVwrError5,
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

//    case numVwrTempAmb,
//    case numVwrTempBomba,
//    case numVwrTempRetorno,
//    case numVwrCaudalRetorno,
//    case numVwrVtobera,
//    case numVwrRth,
//    case numVwrCPI,
//    case numVwrCaudalRetornoHP1,
//    case numVwrCaudalRetornoHP2,
//    case numVwrCaudalRetornoHP3,
//    case numVwrCaudalRetornoHP4,
//    case numVwrVacuumHP1,
//    case numVwrVacuumHP2,
//    case numVwrVacuumHP3,
//    case numVwrVacuumHP4,
//    case numVwrFatigaTime,
//    case numVwrErrFatiga1,
//    case numVwrErrFatiga2,
//    case numVwrErrFatiga3,
//    case numVwrErrFatiga4,
//    case numVwrErrFatiga5,

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

//    case swFatigueFailBeep,
    default: /* Do nothing */ break;
    }

    return 0;
}

void WidgetsWrapper::GUIsetImgViewerImage(uint32 id, uint32 idImg)
{
    switch (id) {
    case imgModelTextHP1: emit hpControlPanelModelTextSet( AppEnumsNs::APP_GUI_HP1_ID, (EAppGUIimageIDlist)idImg ); break;
    case imgModelTextHP2: emit hpControlPanelModelTextSet( AppEnumsNs::APP_GUI_HP2_ID, (EAppGUIimageIDlist)idImg ); break;
    case imgModelTextHP3: emit hpControlPanelModelTextSet( AppEnumsNs::APP_GUI_HP3_ID, (EAppGUIimageIDlist)idImg ); break;
    case imgModelTextHP4: emit hpControlPanelModelTextSet( AppEnumsNs::APP_GUI_HP4_ID, (EAppGUIimageIDlist)idImg ); break;
    case imgColourCtrlPnlBckGndHP2: emit hpControlPanelColorSet(AppEnumsNs::APP_GUI_HP2_ID, (uint8)idImg); break;
    case imgColourCtrlPnlBckGndHP1: emit hpControlPanelColorSet(AppEnumsNs::APP_GUI_HP1_ID, (uint8)idImg); break;
    case imgColourCtrlPnlBckGndHP3: emit hpControlPanelColorSet(AppEnumsNs::APP_GUI_HP3_ID, (uint8)idImg); break;
    case imgColourCtrlPnlBckGndHP4: emit hpControlPanelColorSet(AppEnumsNs::APP_GUI_HP4_ID, (uint8)idImg); break;
    default: break;
    }
}

void WidgetsWrapper::GUIsetImgViewerPosition(uint32 id, uint16 posx, uint16 posy)
{
    EAppGUI_HPsIDs hpIndex = APP_GUI_MAXNUM_HP;

    switch(id) {
    case imgSelectedTrtZoneHP1: hpIndex = AppEnumsNs::APP_GUI_HP1_ID; break;
    case imgSelectedTrtZoneHP2: hpIndex = AppEnumsNs::APP_GUI_HP2_ID; break;
    case imgSelectedTrtZoneHP3: hpIndex = AppEnumsNs::APP_GUI_HP3_ID; break;
    case imgSelectedTrtZoneHP4: hpIndex = AppEnumsNs::APP_GUI_HP4_ID; break;
    default: break;
    }

    emit trtDotFullBodyPositionChanged(hpIndex, posx, posy);
}

void WidgetsWrapper::GUIsetHpControlPanelImgButton(uint32 id, EAppGUIimageIDlist idImg)
{
    EAppGUI_HPsIDs hpIndex = APP_GUI_MAXNUM_HP;

    switch (id) {
    case butModelImageHP1:
        hpIndex = AppEnumsNs::APP_GUI_HP1_ID;
        break;
    case butModelImageHP2:
        hpIndex = AppEnumsNs::APP_GUI_HP2_ID;
        break;
    case butModelImageHP3:
        hpIndex = AppEnumsNs::APP_GUI_HP3_ID;
        break;
    case butModelImageHP4:
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
