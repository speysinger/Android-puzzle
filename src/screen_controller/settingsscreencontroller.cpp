#include "settingsscreencontroller.h"
#include "settings/update/eralistmodel.h"
#include "settings/update/updater.h"

SettingsScreenController::SettingsScreenController(QWidget *parent)
  :ScreensStack(parent)
{
  qmlRegisterType<EraListModel>("EraListModel",1,0,"EraListModel");

  m_update=new UpdateWidget(this);
  m_options=new OptionsWidget(this);
  m_progressBar=new ProgressBarWidget(this);

  m_update->hide();
  m_options->hide();
  m_progressBar->hide();

  connect(m_update,&UpdateWidget::backButtonPressed,[=] { pop(); });

  connect(m_update,&UpdateWidget::loadButtonPressed,[=]{  push(m_progressBar);});

  connect(m_options,&OptionsWidget::loadSelected,[=]{
    UPDATER.loadJson();
    push(m_update);
  });

  connect(m_options, SIGNAL(back()), SIGNAL(back()));
  connect(m_progressBar,&ProgressBarWidget::backButtonPressed,[=]{
    UPDATER.loadJson();
    qDebug()<<"POP";
    pop();
    qDebug()<<"ZDAROVA";

   });

  push(m_options);
}
