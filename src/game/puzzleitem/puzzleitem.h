#ifndef PUZZLEITEM_H
#define PUZZLEITEM_H

#include <QGraphicsPixmapItem>

#include "src/game/puzzlepath.h"

//! базовый класс пазла
class PuzzleItem : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
 public:
  PuzzleItem(PuzzlePath *path, const QPixmap &source, const QRect &rect,
             QObject *parent = nullptr);
  ~PuzzleItem() override;

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;

 private:
  QGraphicsPixmapItem *m_pixmap_item;

 protected:
  PuzzlePath *m_path;
};

#endif  // PUZZLEITEM_H
