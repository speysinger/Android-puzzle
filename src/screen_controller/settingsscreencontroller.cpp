#include "settingsscreencontroller.h"

#include "src/settings/update/updater.h"

SettingsScreenController::SettingsScreenController(QWidget* parent)
    : ScreensStack(parent) {
  m_update = new UpdateWidget(this);
  m_options = new OptionsWidget(this);
  m_progressBar = new ProgressBarWidget(this);

  m_update->hide();
  m_options->hide();
  m_progressBar->hide();

  connect(m_update, &UpdateWidget::backButtonPressed, [=] { pop(); });

  connect(m_update, &UpdateWidget::loadButtonPressed,
          [=] { push(m_progressBar); });

  connect(m_options, &OptionsWidget::loadSelected, [=] {
    UPDATER.loadJson();
    push(m_update);
  });

  connect(m_progressBar, &ProgressBarWidget::backButtonPressed,
          [=] { UPDATER.setBreakFlag(true); });

  connect(m_options, SIGNAL(back()), SIGNAL(back()));

  connect(&UPDATER, &Updater::stopLoading, [=] {
    pop();
    UPDATER.loadJson();
  });

  push(m_options);
}
