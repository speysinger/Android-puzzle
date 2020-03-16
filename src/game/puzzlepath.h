#ifndef PUZZLEPATH_H
#define PUZZLEPATH_H

#include <QPainterPath>
#include "pathpoints.h"

struct  PuzzlePath {
  QPainterPath path;
  int upleft_dx, upleft_dy,
      downright_dx, downright_dy;

  PuzzlePath() {}

  PuzzlePath(QPainterPath _path, int _upleft_dx, int _upleft_dy,
             int _downright_dx, int _downright_dy)
    : path (_path), upleft_dx(_upleft_dx), upleft_dy(_upleft_dy),
                    downright_dx(_downright_dx), downright_dy (_downright_dy) {
  }
};

typedef std::vector<std::vector<PuzzlePath*> > PuzzlePathMatrix;

//! преобразует массив точек в QPainterPath
//! @param points - исходный массив точек
//! @param need_reverse - необходимость "отражения" линии относительно оси
//! при передаче путь копируется, т.к. путь является общим для нескольких фигур
QPainterPath points2path(PathPoints path, bool need_reverse);

//! строит элемент пазла из четырех зигзагов
PuzzlePath* createPuzzlePathItem(PathPoints& up, PathPoints& right,
                       PathPoints& down, PathPoints& left);

//! создает пазлы для заданной картинки и количества фигур
PuzzlePathMatrix getPuzzlePathes(QPixmap& source, size_t n_rows, size_t n_columns);

#endif // PUZZLEPATH_H
