#include "gamemanager.h"
#include "database/levelsdbfacade.h"

GameManager::GameManager():artPuzzleMode()
{}

void GameManager::createGame(PuzzleGame *puzzleGame, Mode mode)
{
  Art art = DB.randomArt();
  getGame(puzzleGame, art, mode);
}

void GameManager::createGame(PuzzleGame *puzzleGame, Author author, Mode mode)
{
  Art art = DB.randomArt(author);
  getGame(puzzleGame, art, mode);
}

void GameManager::createGame(PuzzleGame *puzzleGame, Era era, Mode mode)
{
  Art art = DB.randomArt(era);
  getGame(puzzleGame, art, mode);
}

void GameManager::createGame(PuzzleGame *puzzleGame, Art art, Mode mode)
{
  getGame(puzzleGame, art, mode);
}

Art GameManager::getArt()
{
  return *m_currentArt;
}

void GameManager::addStatisticRecord(int puzzleCollectionTime)
{
  QString time = QString("%1:%2").arg( puzzleCollectionTime / 60000        , 2, 10, QChar('0'))
                                .arg((puzzleCollectionTime % 60000) / 1000, 2, 10, QChar('0'));

  QString mode = QString::number(artPuzzleMode.vertically) + "x" + QString::number(artPuzzleMode.horizontally);

  StatisticRecord statisticRecord(m_currentArt->eraName,
                                  m_currentArt->imgName,
                                  time,
                                  time,
                                  mode
                                  );
  DB.checkStatistic(statisticRecord);
}

void GameManager::getGame(PuzzleGame *puzzleGame, Art art, Mode mode)
{
  m_currentArt = make_unique<Art>(art);
  artPuzzleMode = mode;

  QPixmap pixmap(m_currentArt->imgPath);
  puzzleGame->setLabel(m_currentArt->imgPath);
  puzzleGame->load(pixmap, artPuzzleMode);

}
