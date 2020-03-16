#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "puzzlegame.h"
#include "database/levelstructures.h"
#include <memory>

class PuzzleGame;
class Art;

class GameManager: public QObject
{
  Q_OBJECT
public:
  GameManager();

  void createGame(PuzzleGame *puzzleGame, Mode mode);
  void createGame(PuzzleGame *puzzleGame, Author author, Mode mode);
  void createGame(PuzzleGame *puzzleGame, Era era, Mode mode);
  void createGame(PuzzleGame *puzzleGame, Art art, Mode mode);

  Art getArt();


  void addStatisticRecord(int puzzleCollectionTime);

  private:
  void getGame(PuzzleGame *puzzleGame, Art art, Mode mode);

  template<typename T, typename... Args>
  std::unique_ptr<T> make_unique(Args&&... args) {
      return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }

   std::unique_ptr<Art> m_currentArt;
   Mode artPuzzleMode;
};

#endif // GAMEMANAGER_H
