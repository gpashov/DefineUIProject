#ifndef WIDGETSWRAPPER_H
#define WIDGETSWRAPPER_H

#include <QObject>
#include "AppGUI/AppGuiInterfaceStructure.h"

class WidgetsWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString calcNumber READ calcNumber NOTIFY calcNumberChanged)
    Q_PROPERTY(QString confModel READ confModel NOTIFY confModelChanged)
    Q_PROPERTY(QString confVersion READ confVersion NOTIFY confVersionChanged)

public:
    explicit WidgetsWrapper(QObject *parent = nullptr);

    // Widgets data getters and setters
    QString calcNumber();
    QString confModel();
    QString confVersion();
    void setCalcNumber(QString txt);
    void setConfModel(QString txt);
    void setConfVersion(QString txt);

    void changeScreen(EAppGUIscreen screenId);

    // Treatment area selection functions
    void bodyZoom(bool zoomed);
    void bodyGenderSelect(EAppGUIbodys gender);
    void bodyAreaSelect(EAppGUIfullBodyAreas area);
    void dotZoneAssignHp(EAppGUIwidgetIDlist dot, EAppGUI_HPsIDs hpIndex);
    void dotZoneSelect(EAppGUIwidgetIDlist dot, bool isSelected);

    // Widgets update functions. Used by the application
    void GUIsetNumViewerNum(uint32 id, double num, uint8 dec);
    void GUIsetSwitchStatus( uint32 id, uint8 OnOff);
    uint16 GUIsetWidgetVisibility(uint32 id,uint8 vis);
    uint16 GUIsetWidgetEnable(uint32 id,uint8 enable);
    void GUIsetImgViewerImage(uint32 id,uint32 idImg);
    void GUIsetImgViewerPosition(uint32 id,uint16 posx,uint16 posy);
    void GUIsetHpControlPanelImgButton(uint32 id,EAppGUIimageIDlist idImg);
    void GUISetTreatmentTimerBackground(EAppGUI_HPsIDs hpIndex, bool isSelectable);
    void GUIactiveWarningsPopUp();
    void GUIdeactivateWarningsPopUp();
    void GUIWarningIconActivate(EAppGUImachineWarnings warningId, bool isActive);
    void GUIUpdateVacuumButton(EAppGUI_HPsIDs HPindex, EAppGUIVacButStates butt_states, int vacuumLevel);
    void GUIUpdatePlayButton(EAppGUI_HPsIDs HPindex, EAppGUIPlayButStates butt_states);
    void GUIUpdateTimeButton(EAppGUI_HPsIDs HPindex, EAppGUITimeButStates butt_states);
    void GUIactivePopUp(EAppGUIwidgetIDlist popupWidgetId);
    void GUIdisablePopUp(EAppGUIwidgetIDlist popupWidgetId);
    void GUIcontrolPanelActivatePopUp(EAppGUI_HPsIDs HPindex, EAppGUIwidgetIDlist popupWidgetId);
    void GUIcontrolPanelDisablePopUp(EAppGUI_HPsIDs HPindex, EAppGUIwidgetIDlist popupWidgetId);
    void GUIsetTimePopUp(EAppGUI_HPsIDs HPindex, EAppGUITimePopUpState popupState);
    void GUIshowControlPanel(EAppGUI_HPsIDs HPindex, bool show);
    void GUIenableControlPanels(bool isEnabled);
    void GUItestVacuumPopupSetLevelImage(EAppGUIwidgetIDlist imageWidgetId, EAppGUItstVacDone status);
    void GUItestVacuumPopupChangeColorBar(EAppGUI_HPsIDs hpIndex);
    void GUIrfidPopupChangeColorBar(EAppGUI_HPsIDs hpIndex);
    void GUIShowErrorPopup(uint8 hpIndex, bool isErrorActive);

signals:
    void changeScreenSignal(AppEnumsNs::EAppGUIscreen screenId);

    // Widgets visibility signals

    void infoSwitchVisibilityChanged(bool newVisibility);
    void returnButtonVisibilityChanged(bool newVisibility);
    void timeSelectButtonVisibilityChanged(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool newVisibility);
    void timeRemainingVisibilityChanged(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool newVisibility);

    // Widgets enabled signals
    void infoSwitchEnabled(bool enable);
    void returnButtonEnabled(bool enable);
    void hpImageButtonEnabled(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool enable);
    void controlPanelShowButtonEnabled(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool isEnabled);
    void controlPanelHideButtonEnabled(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool isEnabled);
    void controlPanelVacuumButtonEnabled(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool isEnabled);
    void controlPanelPlayButtonEnabled(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool isEnabled);
    void controlPanelTimeButtonEnabled(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool isEnabled);


    // Calculator
    void calcNumberChanged(QString text);

    // Configuration
    void confModelChanged(QString text);
    void confVersionChanged(QString text);

    // SAT screen
    void satScreenSwVacuumSet(bool OnOff);
    void satScreenSwFrioSet(bool OnOff);
    void satScreenSwTestLedSet(bool OnOff);
    void satScreenSwTestLedRGBSet(bool OnOff);

    // Main menu
    void mainMenuOpened(bool menuOpened);
    void mainMenuEnabled(bool menuEnabled);
    void mainMenuWarningNotificationDisplayed(bool isDisplayed);

    // Body areas
    void bodyZoomed(bool zoomed);
    void bodyGenderSelected(AppEnumsNs::EAppGUIbodys gender);
    void bodyAreaSelected(AppEnumsNs::EAppGUIfullBodyAreas area);

    // Dot zones full body
    void trtDotFullBodyVisibilityChanged(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool newVisibility);
    void trtDotFullBodyPositionChanged(AppEnumsNs::EAppGUI_HPsIDs hpIndex, uint32 posX, uint32 posY);

    // Zoomed body dots
    void dotZoneEnabled(uint32 id, bool enable);
    void dotZoneHpAssigned(AppEnumsNs::EAppGUIwidgetIDlist dot, AppEnumsNs::EAppGUI_HPsIDs hpIndex);
    void dotZoneSelected(AppEnumsNs::EAppGUIwidgetIDlist dot, bool isSelected);

    // Control panels widgets
    void hpControlPanelShown(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool isShown);
    void hpControlPanelsEnabled(bool isEnabled);
    void treatmentTimerSet(AppEnumsNs::EAppGUI_HPsIDs hpIndex, QString newTime);
    void treatmentTimerBackgroundSet(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool isSelectable);
    void temperatureButtonEnabled(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool isEnabled);
    void resuctionCountVisibilityChanged(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool newVisibility);
    void resuctionCountChanged(AppEnumsNs::EAppGUI_HPsIDs hpIndex, uint8 resuctionCount);
    void indicatorRfidVisibilityChanged(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool newVisibility);
    void indicatorButtonVisibilityChanged(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool newVisibility);
    void indicatorVacuumVisibilityChanged(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool newVisibility);
    void indicatorCoolingVisibilityChanged(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool newVisibility);
    void hpControlPanelButtonImagesSet(AppEnumsNs::EAppGUI_HPsIDs hpIndex, AppEnumsNs::EAppGUIimageIDlist idImg);
    void hpControlPanelModelTextSet(AppEnumsNs::EAppGUI_HPsIDs hpIndex, AppEnumsNs::EAppGUIimageIDlist idImg);
    void hpControlPanelColorSet(AppEnumsNs::EAppGUI_HPsIDs hpIndex, uint8 colorState);
    void vacuumButtonUpdated(AppEnumsNs::EAppGUI_HPsIDs HPindex, AppEnumsNs::EAppGUIVacButStates butt_state, int vacuumLevel);
    void vacuumButtonSwitchStateChanged(AppEnumsNs::EAppGUI_HPsIDs HPindex, bool switchState);
    void playButtonUpdated(AppEnumsNs::EAppGUI_HPsIDs HPindex, AppEnumsNs::EAppGUIPlayButStates butt_state);
    void timeButtonUpdated(AppEnumsNs::EAppGUI_HPsIDs HPindex, AppEnumsNs::EAppGUITimeButStates butt_state);

    // Control panel popups
    void testVacuumPopupSmallActivated(AppEnumsNs::EAppGUI_HPsIDs HPindex, bool isActivated);
    void testVacuumPopupSmallButtonEnabled(AppEnumsNs::EAppGUIwidgetIDlist typeWidgetId, bool isEnabled);

    // Popups
    void warningsPopupDisplayed(bool isDisplayed);
    void warningActivated(AppEnumsNs::EAppGUImachineWarnings warningId, bool isActivated);
    void recommendedHpsPopupActivated(bool isActivated);
    void suggestedHpWatermarkDisplayed(AppEnumsNs::EAppGUIwidgetIDlist typeWidgetId, bool isDispalyed);
    void rfidPopupActivated(bool isActivated);
    void rfidPopupLabelChanged(AppEnumsNs::EAppGUIimageIDlist idImg);
    void rfidPopupStatusChanged(AppEnumsNs::EAppGUIimageIDlist idImg);
    void rfidPopupColorBarChanged(AppEnumsNs::EAppGUI_HPsIDs hpIndex);
    void rfidPopupRestTimeVisibilityChanged(bool newVisibility);
    void rfidPopupRestTimeUpdated(QString newTime);
    void rfidPopupReuseLabelEnabled(bool isEnabled);
    void testVacuumPopupActivated(bool isActivated);
    void testVacuumPopupSwitchStateChanged(AppEnumsNs::EAppGUIwidgetIDlist widgetId, bool OnOff);
    void testVacuumPopupSwitchEnabled(AppEnumsNs::EAppGUIwidgetIDlist widgetId, bool isEnabled);
    void testVacuumPopupManualTestButtonEnabled(AppEnumsNs::EAppGUIwidgetIDlist widgetId, bool isEnabled);
    void testVacuumPopupAutoTestButtonEnabled(bool isEnabled);
    void testVacuumPopupPressHandVisibilityChanged(bool newVisibility);
    void testVacuumPopupPressHandX2VisibilityChanged(bool newVisibility);
    void testVacuumPopupAutoStatusVisibilityChanged(bool newVisibility);
    void testVacuumPopupAutoButtonVisibilityChanged(bool newVisibility);
    void testVacuumPopupAutoStatusImageChanged(AppEnumsNs::EAppGUIimageIDlist idImg);
    void testVacuumPopupLevelImageSet(AppEnumsNs::EAppGUIwidgetIDlist imageWidgetId, AppEnumsNs::EAppGUItstVacDone status);
    void testVacuumPopupColorBarChanged(AppEnumsNs::EAppGUI_HPsIDs hpIndex);
    void timePopUpSet(AppEnumsNs::EAppGUI_HPsIDs HPindex, AppEnumsNs::EAppGUITimePopUpState popupState);

    // Error popups
    void errorPopupActivated(AppEnumsNs::EAppGUI_HPsIDs hpIndex, bool isErrorActive);    // We use APP_GUI_MAXNUM_HP for the central error popup
    void errorPopupErrorCodeSet(AppEnumsNs::EAppGUI_HPsIDs hpIndex, QString errorCode);
    void errorPopupTreatmentTimeSet(AppEnumsNs::EAppGUI_HPsIDs hpIndex, QString time);
    void errorPopupErrorMessageImageSet(AppEnumsNs::EAppGUI_HPsIDs hpIndex, AppEnumsNs::EAppGUIimageIDlist idImg);

private:
    void float_to_string(double f, char r[], uint8 dec);
    int n_tu(int number, int count);


    // TEXT WIDGETS DATA

    // Calculator screen
    QString calcNumberStr;

    // Configuration screen
    QString confModelStr;
    QString confVersionStr;
};

#endif // WIDGETSWRAPPER_H
