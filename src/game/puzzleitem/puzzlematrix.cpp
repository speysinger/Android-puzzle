#include "src/game/puzzleitem/puzzlematrix.h"
#include "src/game/puzzleitem/settableitem.h"
#include <assert.h>

PuzzleMatrix createPuzzles(const QPixmap &source, PuzzlePathMatrix &puzzlePathes) {
  assert(puzzlePathes.size() > 0);

  const QColor maskColor(122, 163, 39);

  const auto n_rows = puzzlePathes.size();
  const auto n_colums = puzzlePathes[0].size();

  const auto item_h = source.size().height() / n_rows;
  const auto item_w = source.size().width() / n_colums;

  PuzzleMatrix puzzleMatrix;
  puzzleMatrix.resize(n_rows);

  for (size_t i = 0; i < n_rows; i++) {
    puzzleMatrix[i].resize(n_colums);
    for (size_t j = 0; j < n_colums; j++) {
      auto& path = *puzzlePathes[i][j];
      auto x = item_w * j + path.upleft_dx;
      auto y = item_h * i + path.upleft_dy;
      auto conrete_item_w = item_w - path.upleft_dx + path.downright_dx;
      auto conrete_item_h = item_h - path.upleft_dy + path.downright_dy;
      puzzleMatrix[i][j] = new SettableItem(puzzlePathes[i][j], source,
                                            QRect(x, y, conrete_item_w, conrete_item_h),
                                            QPointF(x, y));
    }
  }
  return puzzleMatrix;
}
