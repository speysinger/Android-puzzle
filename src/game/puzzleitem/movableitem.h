#ifndef MOVABLEITEM_H
#define MOVABLEITEM_H

#include "rotatableitem.h"

//! перемещение Фрагментов пазла
class MovableItem : public RotatableItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
 public:
  MovableItem(PuzzlePath *path, const QPixmap &source, const QRect &rect,
              QObject *parent = nullptr)
      : RotatableItem(path, source, rect, parent), m_is_moved(false) {}

  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

  bool is_moved() { return m_is_moved; }

 private:
  bool m_is_moved;
  QPointF m_movePos;
};

#endif  // MOVABLEITEM_H
