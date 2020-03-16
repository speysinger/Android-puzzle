#ifndef GAMESCREENCONTROLLER_H
#define GAMESCREENCONTROLLER_H

#include "screensstack.h"
#include "mode.h"
#include "database/levelstructures.h"

#include "game/gamemanager.h"
#include <memory>
#include <QTime>

class PuzzleGame;
class HelpViewer;
class ArtInfoWidget;

class GameScreenController : public ScreensStack {
  Q_OBJECT
public:
  explicit GameScreenController(QWidget *parent = nullptr);
  void startRandomGame(Mode mode);
  void startRandomGame(Author author, Mode mode);
  void startRandomGame(Era era, Mode mode);

  void startSelectedGame(Art art, Mode mode);

  void start();
protected:
   PuzzleGame *m_game;
   GameManager *m_gameManager;
   ArtInfoWidget *m_artInfo;
   QTime timer;
};

#endif // GAMESCREENCONTROLLER_H
