#ifndef PUZZLEMATRIX_H
#define PUZZLEMATRIX_H

#include "src/game/puzzlepath.h"

class SettableItem;

typedef std::vector<std::vector<SettableItem*> > PuzzleMatrix;

//! заполняет содержимым все элементы пазла
PuzzleMatrix createPuzzles(const QPixmap& source,
                           PuzzlePathMatrix& puzzlePathes);

#endif  // PUZZLEMATRIX_H
