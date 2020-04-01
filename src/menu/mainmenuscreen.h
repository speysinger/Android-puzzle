#ifndef MAINMENUSCREEN_H
#define MAINMENUSCREEN_H

#include "src/mode.h"
#include "level_icons_view/iconsview.h"
#include "src/ui/buttons/levelmodewidget.h"

class MainMenuScreen : public QWidget
{
  Q_OBJECT
public:
  MainMenuScreen(QWidget* parent = nullptr);
  Mode mode();
signals:
  void settingsSelected();
  void testingSelected();
  void updateSelected();
  void erasSelected();
  void authorsSelected();
  void randomSelected();
  void statisticSelected();
  void exit();
  void aboutProgramSelected();

protected:
  LevelModeWidget* m_modeWidget;
};

#endif  // MAINMENUSCREEN_H
