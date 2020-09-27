#include "rotatableitem.h"

void RotatableItem::set_center_rotation(int angle) {
  if (false == m_is_rotatable) return;
  m_rotateAngle += angle;

  QRectF rect = mapToScene(this->boundingRect()).boundingRect();
  QPointF center = rect.center();

  QTransform t;
  t.translate(center.x(), center.y());
  t.rotate(angle);
  t.translate(-center.x(), -center.y());
  setPos(t.map(pos()));

  setRotation(rotation() + angle);
  m_rotateAngle %= 360;

  emit changed();
}

void RotatableItem::set_randomRotate() {
  if (false == m_is_rotatable) return;
  int angle = (rand() % 4) * 90;

  if (angle) {
    set_center_rotation(angle);
  }
}
