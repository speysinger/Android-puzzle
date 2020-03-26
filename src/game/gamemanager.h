#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "puzzlegame.h"
#include "database/levelstructures.h"
#include <memory>

class PuzzleGame;
class Art;

///
/// \brief The GameManager class
/// Данный класс реализует: создание игры(PuzzleGame) по входящим данным
/// Сбор и запись в бд игровой статистики
class GameManager
{
public:
  GameManager();

  void createGame(PuzzleGame* puzzleGame, Mode mode);
  void createGame(PuzzleGame* puzzleGame, Author author, Mode mode);
  void createGame(PuzzleGame* puzzleGame, Era era, Mode mode);
  void createGame(PuzzleGame* puzzleGame, Art art, Mode mode);

  Art getArt();
  void addStatisticRecord(int puzzleCollectionTime);

private:
  void setGame(PuzzleGame* puzzleGame, Art art, Mode mode);

  std::unique_ptr<Art> m_currentArt;
  Mode m_artPuzzleMode;
};

#endif  // GAMEMANAGER_H
