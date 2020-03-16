#ifndef LEVELMENUSCREENCONTROLLER_H
#define LEVELMENUSCREENCONTROLLER_H

#include "screensstack.h"
#include "mode.h"
#include "database/levelstructures.h"
#include "game/gamemanager.h"
#include <memory>

class GameScreenController;
class LevelMenuScreen;

class LevelMenuScreenController : public ScreensStack {
  Q_OBJECT
public:
  explicit LevelMenuScreenController(QWidget *parent = nullptr);
  void showEras();
  void showAuthors();
signals:
  void back();
protected:
   GameScreenController *m_game;
   LevelMenuScreen *m_menu;

   std::unique_ptr<Author> m_selectedAuthor;
   std::unique_ptr<Era> m_selectedEra;
};

#endif // LEVELMENUSCREENCONTROLLER_H
