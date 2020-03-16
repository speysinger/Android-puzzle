#include "settingsscreencontroller.h"
#include "settings/update/eralistmodel.h"
#include <QQmlEngine>
#include "settings/update/indexloader.h"
#include <QtConcurrent/qtconcurrentrun.h>

SettingsScreenController::SettingsScreenController(QWidget *parent)
  :ScreensStack(parent)
{
  qmlRegisterType<EraListModel>("EraListModel",1,0,"EraListModel");

  m_update=new UpdateWidget(this);
  m_settings=new SettingWidget(this);
  m_progressBar=new ProgressBarWidget(this);

  m_update->hide();
  m_settings->hide();
  m_progressBar->hide();

  connect(m_update,&UpdateWidget::backButtonPressed,[=] { pop(); });

  connect(m_update,&UpdateWidget::loadButtonPressed,[=]{  push(m_progressBar);});

  connect(m_settings,&SettingWidget::loadSelected,[=]{
    push(m_update);
    LOADER.load("https://pro-prof.com/artists-puzzle/load_1/levels.json");
  });

  connect(m_settings, SIGNAL(back()), SIGNAL(back()));

  connect(m_progressBar,&ProgressBarWidget::backButtonPressed,[=]{
    LOADER.load("https://pro-prof.com/artists-puzzle/load_1/levels.json");
    pop();});

  push(m_settings);
}
