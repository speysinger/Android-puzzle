#include "pathpoints.h"

#include <QGraphicsPathItem>
#include <functional>
#include <vector>

#include "QPainter"
#include "QPen"
#include "QTime"
#include "qmath.h"
#include "random_points.h"

void randomizePoints(std::vector<QPoint>::iterator from,
                     std::vector<QPoint>::iterator to, const QPoint range) {
  for (auto it = from; it != to; ++it) {
    *it = getNear(*it, range);
  }
}

void randCurvePath(PathPoints& path) {
  if (rand() % 2) return;

  if (path.type == PathPoints::Type::HorizontalZigZag) {
    for (auto& point : path.points) point.setY(-point.y());
  }
  if (path.type == PathPoints::Type::VerticalZigZag) {
    for (auto& point : path.points) point.setX(-point.x());
  }
}

PathPoints verticalPath(int w, int h) {
  w = h / 5;
  QPoint middle(w / 2, h / 2);

  QPoint zigzagSize(w / 10, h / 10);
  QPoint zigzagSize1(w / 6, h / 6);
  QPoint zigzagSize2(w / 4, h / 3);

  const QPoint range(w / 20, h / 20);

  PathPoints path;
  path.type = PathPoints::Type::VerticalZigZag;

  path.points = {QPoint(0, 0),
                 QPoint(0, middle.y() - zigzagSize.y()),

                 QPoint(-w + zigzagSize2.x(), middle.y() - zigzagSize2.y()),
                 QPoint(-w + zigzagSize1.x(), middle.y() - zigzagSize1.y()),
                 QPoint(-w + zigzagSize.x(), middle.y() - zigzagSize.y()),
                 QPoint(-w, middle.y()),
                 QPoint(-w + zigzagSize.x(), middle.y() + zigzagSize.y()),
                 QPoint(-w + zigzagSize1.x(), middle.y() + zigzagSize1.y()),
                 QPoint(-w + zigzagSize2.x(), middle.y() + zigzagSize2.y()),

                 QPoint(0, middle.y() + zigzagSize.y()),

                 QPoint(0, h)};

  randomizePoints(path.points.begin() + 2, path.points.end() - 2, range);
  randCurvePath(path);

  return path;
}

PathPoints horizontalPath(int w, int h) {
  h = h / 5;

  QPoint middle(w / 2, h / 2);

  QPoint zigzagSize(w / 10, h / 10);
  QPoint zigzagSize1(w / 6, h / 6);
  QPoint zigzagSize2(w / 4, h / 4);

  const QPoint range(w / 20, h / 20);

  PathPoints path;
  path.type = PathPoints::Type::HorizontalZigZag;

  path.points = {QPoint(0, 0),
                 QPoint(middle.x() - zigzagSize.x(), 0),
                 QPoint(middle.x() - zigzagSize2.x(), zigzagSize2.y() - h),
                 QPoint(middle.x() - zigzagSize1.x(), zigzagSize1.y() - h),
                 QPoint(middle.x() - zigzagSize.x(), zigzagSize.y() - h),
                 QPoint(middle.x(), -h),

                 QPoint(middle.x() + zigzagSize.x(), zigzagSize.y() - h),
                 QPoint(middle.x() + zigzagSize1.x(), zigzagSize1.y() - h),
                 QPoint(middle.x() + zigzagSize2.x(), zigzagSize2.y() - h),
                 QPoint(middle.x() + zigzagSize.x(), 0),
                 QPoint(w, 0)};

  randomizePoints(path.points.begin() + 2, path.points.end() - 2, range);
  randCurvePath(path);

  return path;
}

PathPoints horizLinePath(int w) {
  PathPoints path;
  path.type = PathPoints::Type::HorizontalLine;

  path.points = {QPoint(0, 0), QPoint(w, 0)};

  return path;
}

PathPoints vertLinePath(int h) {
  PathPoints path;
  path.type = PathPoints::Type::VerticalLine;

  path.points = {QPoint(0, 0), QPoint(0, h)};

  return path;
}

QSize pathSize(PathPoints& path) {
  auto sign = [](int value) -> int { return value < 0 ? -1 : 1; };

  auto xCompare = [](QPoint a, QPoint b) -> bool { return a.x() < b.x(); };
  auto yCompare = [](QPoint a, QPoint b) -> bool { return a.y() < b.y(); };

  auto minMaxX =
      std::minmax_element(path.points.begin(), path.points.end(), xCompare);
  auto minMaxY =
      std::minmax_element(path.points.begin(), path.points.end(), yCompare);

  return QSize(
      (minMaxX.second->x() - minMaxX.first->x()) * sign(minMaxX.first->x()),
      (minMaxY.second->y() - minMaxY.first->y()) * sign(minMaxY.first->y()));
}

PathPointsMatrix getVerPoints(QPixmap& source, size_t n_rows, size_t n_column) {
  const size_t colVert_m = n_column + 1;
  const size_t colVert_n = n_rows;

  std::vector<std::vector<PathPoints> > pathes;
  pathes.resize(n_rows);

  auto w = source.width() / n_column;
  auto h = source.height() / n_rows;

  for (size_t i = 0; i < colVert_n; i++) {
    pathes[i].resize(colVert_m);
    for (size_t j = 0; j < colVert_m; j++)
      if (j == 0 || (j == colVert_m - 1))
        pathes[i][j] = vertLinePath(h);
      else
        pathes[i][j] = verticalPath(w, h);
  }
  return pathes;
}

PathPointsMatrix getHorizPoints(QPixmap& source, size_t n_rows,
                                size_t n_columns) {
  auto colHoriz_n = n_rows + 1;
  auto colHoriz_m = n_columns + 1;

  std::vector<std::vector<PathPoints> > pathes;
  pathes.resize(colHoriz_n);

  auto w = source.width() / n_columns;
  auto h = source.height() / n_rows;

  for (size_t i = 0; i < colHoriz_n; i++) {
    pathes[i].resize(colHoriz_m);
    for (size_t j = 0; j < colHoriz_m; j++)
      if (i == 0 || i == colHoriz_n - 1)
        pathes[i][j] = horizLinePath(w);
      else
        pathes[i][j] = horizontalPath(w, h);
  }

  return pathes;
}
