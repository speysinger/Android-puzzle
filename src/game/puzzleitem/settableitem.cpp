#include "settableitem.h"

void SettableItem::onChanged() {
  if (angle())
    return;
  if (QLineF(this->scenePos(), m_correctCornerPos).length() < StableDist) {
    setPos(m_correctCornerPos);
    m_setted = true;
    emit setted();
    setZValue(0);
  }
}
