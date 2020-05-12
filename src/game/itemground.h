#ifndef ITEMGROUND_H
#define ITEMGROUND_H

#include <QGraphicsRectItem>
#include <QObject>

class ItemGround : public QObject, public QGraphicsRectItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
 public:
  ItemGround(QRectF rect, QObject* parent = nullptr);
};

#endif  // ITEMGROUND_H
