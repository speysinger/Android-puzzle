  #include "movableitem.h"
#include <QApplication>
#include <QGraphicsSceneMouseEvent>

void MovableItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  RotatableItem::mousePressEvent(event);

  m_movePos = event->scenePos();
  m_is_moved = false;
  setCursor(Qt::ClosedHandCursor);
}

void MovableItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  RotatableItem::mouseMoveEvent(event);

  if (false == m_selection)
    return;

  if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
    .length() < QApplication::startDragDistance()) {
    return;
  }

  m_is_moved = true;

  QPointF delta = event->scenePos() - m_movePos;
  m_movePos = event->scenePos();

  moveBy(delta.x(), delta.y());
}

void MovableItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  RotatableItem::mouseReleaseEvent(event);

  unsetCursor();
  if (false == m_is_moved) {
    set_center_rotation(90);
    return;
  }

  m_is_moved = false;
  emit changed();
}
