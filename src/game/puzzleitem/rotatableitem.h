#ifndef ROTATABLEITEM_H
#define ROTATABLEITEM_H

#include "selectableitem.h"

//! вращение Фрагментов пазла
class RotatableItem : public SelectableItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
public:
  RotatableItem(PuzzlePath *path, const QPixmap& source, const QRect &rect,
              QObject *parent = nullptr) :
    SelectableItem(path, source, rect, parent),
    m_rotateAngle(0), m_is_rotatable(false)  {
  }

  void set_randomRotate();
  void set_center_rotation(int angle);
  int angle() { return m_rotateAngle; }
signals:
  void changed();
protected:
  int m_rotateAngle;
  bool m_is_rotatable;
};

#endif // ROTATABLEITEM_H
