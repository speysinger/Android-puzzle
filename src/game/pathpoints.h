#ifndef QTITEM_H
#define QTITEM_H

#include <vector>
#include <QPoint>
#include <QSize>
#include <QPixmap>

struct PathPoints {
  enum class Type {
    HorizontalLine,
    VerticalLine,
    HorizontalZigZag,
    VerticalZigZag,
  };

  std::vector<QPoint> points;
  Type type;
};

typedef std::vector<std::vector<PathPoints> > PathPointsMatrix;

//! формирует точки горизонтального зигзага
PathPoints horizontalPath(int w, int h);

//! формирует точки вертикального зигзага
PathPoints verticalPath(int w, int h);

//! формирует точки горизонтальной прямой (граница пазла)
PathPoints horizLinePath(int w);

//! формирует точки горизонтальной вертикальной (граница пазла)
PathPoints vertLinePath(int h);

//! случайным образом отражает выгнутный путь в вогнутый
void randCurvePath(PathPoints& path);

//! возвращает размеры зигзага или линии
QSize pathSize(PathPoints &path);

//! формирует матрицу из горизонтальных крючков
//! для заданного изображения и количества фигур
PathPointsMatrix getHorizPoints (QPixmap& source, size_t n_rows, size_t n_columns);

//! формирует матрицу из вертикальных крючков
//! для заданного изображения и количества фигур
PathPointsMatrix getVerPoints (QPixmap& source, size_t n_rows, size_t n_column);
#endif // QTITEM_H


