#ifndef SETTABLEITEM_H
#define SETTABLEITEM_H

#include "movableitem.h"

//! установка Фрагмента в ячейки
class SettableItem : public MovableItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
public:
  SettableItem(PuzzlePath *path, const QPixmap& source, const QRect &rect,
               QPointF correctCornerPos,
               QObject *parent = nullptr) :
    MovableItem(path, source, rect, parent),
    m_correctCornerPos(correctCornerPos),
    StableDist(std::min(rect.height(), rect.width()) / 4.f),
    m_setted(false) {
    connect(this, SIGNAL(changed()), this, SLOT(onChanged()));
  }

  void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
    if (m_setted)
      return;
    MovableItem::mousePressEvent(event);
  }
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
    if (m_setted)
      return;
    MovableItem::mouseMoveEvent(event);
  }
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
    if (m_setted)
      return;
    MovableItem::mouseReleaseEvent(event);
  }

  bool is_setted() { return m_setted; }

  void setRotatable(bool rotatable) {
    m_is_rotatable = rotatable;
  }
private slots:
  void onChanged();
signals:
  void setted();
private:
  QPointF m_correctCornerPos;
  const float StableDist;
  bool m_setted;
};

#endif // SETTABLEITEM_H
