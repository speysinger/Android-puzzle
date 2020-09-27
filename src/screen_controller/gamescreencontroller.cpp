#include "gamescreencontroller.h"

#include <memory>

#include "src/database/levelstructures.h"
#include "src/game/puzzlegame.h"
#include "src/ui/html_view/artinfowidget.h"

GameScreenController::GameScreenController(QWidget* parent)
    : ScreensStack(parent) {
  m_gameManager = new GameManager();
  m_game = new PuzzleGame(this);
  m_artInfo = new ArtInfoWidget(this);

  m_game->hide();
  m_artInfo->hide();

  connect(m_game, &PuzzleGame::back, [=] { pop(); });
  connect(m_artInfo, &ArtInfoWidget::back, [=] {
    pop();
    pop();
  });

  connect(m_game, &PuzzleGame::finished, [=] {
    m_artInfo->load(m_gameManager->getArt());

    int ms = timer.elapsed();
    m_gameManager->addStatisticRecord(ms);

    push(m_artInfo);
  });
}

void GameScreenController::startRandomGame(Mode mode) {
  m_gameManager->createGame(m_game, mode);
  start();
}

void GameScreenController::startRandomGame(Author author, Mode mode) {
  m_gameManager->createGame(m_game, author, mode);
  start();
}

void GameScreenController::startRandomGame(Era era, Mode mode) {
  m_gameManager->createGame(m_game, era, mode);
  start();
}

void GameScreenController::startSelectedGame(Art art, Mode mode) {
  m_gameManager->createGame(m_game, art, mode);
  start();
}

void GameScreenController::start() {
  timer.start();
  push(m_game);
}
