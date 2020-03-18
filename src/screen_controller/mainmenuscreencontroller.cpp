#include "mainmenuscreencontroller.h"
#include "menu/mainmenuscreen.h"
#include "gamescreencontroller.h"
#include "html_view/helpviewer.h"
#include "levelmenuscreencontroller.h"
#include "settingsscreencontroller.h"
#include "testingscreencontroller.h"
#include "statistic/statisticwidget.h"

MainMenuScreenController::  MainMenuScreenController(QWidget* parent)
  : ScreensStack(parent) {

  m_menu = new MainMenuScreen(this);
  m_settings = new SettingsScreenController(this);
  m_game = new GameScreenController(this);
  m_aboutProgram = new HelpViewer(this);
  m_level_menu = new LevelMenuScreenController(this);
  m_testing = new TestingScreenController(this);
  m_statistic = new StatisticWidget(this);

  m_menu->hide();
  m_settings->hide();
  m_game->hide();
  m_aboutProgram->hide();
  m_level_menu->hide();
  m_testing->hide();
  m_statistic->hide();

  connect(m_menu, &MainMenuScreen::settingsSelected, [=] {
    push(m_settings);
  });
  connect(m_menu, &MainMenuScreen::testingSelected, [=] {
    push(m_testing);
    m_testing->pushTestingWindow();
  });
  connect(m_menu, &MainMenuScreen::exit, [=] { this->close(); });
  connect(m_menu, &MainMenuScreen::aboutProgramSelected, [=] { push(m_aboutProgram); });
  connect(m_menu, &MainMenuScreen::erasSelected, [=] {
    m_level_menu->showEras();
    push(m_level_menu);
  });
  connect(m_menu, &MainMenuScreen::authorsSelected, [=] {
    m_level_menu->showAuthors();
    push(m_level_menu);
  });
  connect(m_menu, &MainMenuScreen::randomSelected, [=] {
    m_game->startRandomGame(m_menu->mode());
    push(m_game);
  });
  connect(m_menu,&MainMenuScreen::statisticSelected, [=]{
    push(m_statistic);
    m_statistic->loadStatistic();
  });


  connect(m_game, &GameScreenController::back, [=] { pop(); });
  connect(m_settings, SIGNAL(back()), SLOT(pop()));
  connect(m_testing,&TestingScreenController::back, [=] {pop();});
  connect(m_aboutProgram, SIGNAL(back()), SLOT(pop()));
  connect(m_level_menu, &LevelMenuScreenController::back, [=] { pop(); });
  connect(m_statistic, &StatisticWidget::back, [=] {pop();});

  push(m_menu);
}
