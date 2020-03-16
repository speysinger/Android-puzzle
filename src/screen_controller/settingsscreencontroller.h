#ifndef SETTINGSSCREENCONTROLLER_H
#define SETTINGSSCREENCONTROLLER_H


#include "screensstack.h"
#include "settings/settingwidget.h"
#include "settings/update/updatewidget.h"
#include "settings/update/progressbarwidget.h"

class SettingWidget;
class UpdateWidget;
class UpdateProgressBar;

class SettingsScreenController : public ScreensStack {
  Q_OBJECT
public:
  explicit SettingsScreenController(QWidget *parent = nullptr);
protected:
   SettingWidget *m_settings;
   UpdateWidget *m_update;
   ProgressBarWidget *m_progressBar;
};

#endif // SETTINGSSCREENCONTROLLER_H
