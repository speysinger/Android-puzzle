#ifndef MAINMENUSCREENCONTROLLER_H
#define MAINMENUSCREENCONTROLLER_H

#include "screensstack.h"

class MainMenuScreen;
class SettingsScreenController;
class GameScreenController;
class HelpViewer;
class LevelMenuScreenController;
class TestingScreenController;
class StatisticWidget;

class MainMenuScreenController : public ScreensStack {
  Q_OBJECT
 public:
  explicit MainMenuScreenController(QWidget* parent = nullptr);

 protected:
  MainMenuScreen* m_menu;
  SettingsScreenController* m_settings;
  GameScreenController* m_game;
  HelpViewer* m_aboutProgram;
  LevelMenuScreenController* m_level_menu;
  TestingScreenController* m_testing;
  StatisticWidget* m_statistic;
};

#endif  // MAINMENUSCREENCONTROLLER_H
