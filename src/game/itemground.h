#ifndef ITEMGROUND_H
#define ITEMGROUND_H

#include <QObject>
#include <QGraphicsRectItem>

class ItemGround : public QObject, public QGraphicsRectItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
public:
  ItemGround(QRectF rect, QObject* parent = nullptr);
};

#endif // ITEMGROUND_H
