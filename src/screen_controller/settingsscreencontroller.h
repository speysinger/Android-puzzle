#ifndef SETTINGSSCREENCONTROLLER_H
#define SETTINGSSCREENCONTROLLER_H

#include "screensstack.h"
#include "src/settings/optionswidget.h"
#include "src/settings/update/updatewidget.h"
#include "src/settings/update/progressbarwidget.h"

class OptionsWidget;
class UpdateWidget;
class UpdateProgressBar;

///
/// \brief The SettingsScreenController class
/// Данный класс реализует управление показом окон, связанных с тестированием и настройками(путь до файла, звук)
class SettingsScreenController : public ScreensStack
{
  Q_OBJECT
public:
  explicit SettingsScreenController(QWidget* parent = nullptr);

protected:
  OptionsWidget* m_options;
  UpdateWidget* m_update;
  ProgressBarWidget* m_progressBar;
};

#endif  // SETTINGSSCREENCONTROLLER_H
