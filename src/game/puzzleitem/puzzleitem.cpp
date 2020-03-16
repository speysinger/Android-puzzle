#include "puzzleitem.h"

#include <QPainter>
#include <QBitmap>

PuzzleItem::~PuzzleItem() {
  delete m_pixmap_item;
  delete m_path;
}

PuzzleItem::PuzzleItem(PuzzlePath *path, const QPixmap& source,
                       const QRect &rect, QObject *parent)  :
  QObject(parent), QGraphicsItem(), m_path(path) {

  QColor maskColor(122, 163, 39);

  // смещаем элемент пазла т.к. его часть в отрицательных координатах,
  // при отрисовке на QPainter эта часть обрезается
  m_path->path.translate(-m_path->upleft_dx, -m_path->upleft_dy);

  QPixmap pieceImage(source.copy(rect));

  QImage imgMask(pieceImage.size(), QImage::Format_ARGB32);
  imgMask.fill(Qt::GlobalColor::transparent);

  QPainter painter;
  painter.begin(&imgMask);
  painter.setBrush(maskColor);
  painter.drawPath(m_path->path);
  painter.end();

  QPixmap mask;
  mask.convertFromImage(imgMask);
  pieceImage.setMask(mask.mask());

  m_pixmap_item = new QGraphicsPixmapItem(pieceImage);
}

QRectF PuzzleItem::boundingRect() const {
  if (m_pixmap_item) {
    auto rect = m_pixmap_item->boundingRect();
    return rect;
  }
  return QRectF(0,0,0,0);
}

void PuzzleItem::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option,
           QWidget *widget) {
  if (m_pixmap_item)
    m_pixmap_item->paint(painter, option, widget);
}
