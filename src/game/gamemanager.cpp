#include "gamemanager.h"
#include "database/levelsdbfacade.h"

GameManager::GameManager():m_artPuzzleMode()
{}

void GameManager::createGame(PuzzleGame *puzzleGame, Mode mode)
{
  Art art = DB.randomArt();
  setGame(puzzleGame, art, mode);
}

void GameManager::createGame(PuzzleGame *puzzleGame, Author author, Mode mode)
{
  Art art = DB.randomArt(author);
  setGame(puzzleGame, art, mode);
}

void GameManager::createGame(PuzzleGame *puzzleGame, Era era, Mode mode)
{
  Art art = DB.randomArt(era);
  setGame(puzzleGame, art, mode);
}

void GameManager::createGame(PuzzleGame *puzzleGame, Art art, Mode mode)
{
  setGame(puzzleGame, art, mode);
}

Art GameManager::getArt()
{
  return *m_currentArt;
}

void GameManager::addStatisticRecord(int puzzleCollectionTime)
{
  QString time = QString("%1:%2").arg( puzzleCollectionTime / 60000        , 2, 10, QChar('0'))
                                .arg((puzzleCollectionTime % 60000) / 1000, 2, 10, QChar('0'));

  QString mode = QString::number(m_artPuzzleMode.vertically) + "x" + QString::number(m_artPuzzleMode.horizontally);

  StatisticRecord statisticRecord(m_currentArt->eraName,
                                  m_currentArt->imgName,
                                  time,
                                  time,
                                  mode
                                  );
  DB.checkStatistic(statisticRecord);
}

void GameManager::setGame(PuzzleGame *puzzleGame, Art art, Mode mode)
{
  m_currentArt = make_unique<Art>(art);
  m_artPuzzleMode = mode;

  QPixmap pixmap(m_currentArt->imgPath);
  puzzleGame->setLabel(m_currentArt->imgPath);
  puzzleGame->load(pixmap, m_artPuzzleMode);

}
