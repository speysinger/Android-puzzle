#include "selectableitem.h"

SelectableItem::~SelectableItem() {
  delete m_border;
}

void SelectableItem::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option,
           QWidget *widget) {
  PuzzleItem::paint(painter, option, widget);
  if (m_border)
    m_border->paint(painter, option, widget);
}

void SelectableItem::mousePressEvent(QGraphicsSceneMouseEvent *) {
  emit clicked();
  set_selected(true, true);
}

void SelectableItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *) {
  set_selected(false, true);
}

void SelectableItem::set_selected(bool selection, bool need_update = false) {
  m_selection = selection;
  if (selection) {
    m_border->setPen(SelectionPen);
  }
  else {
    m_border->setPen(DefaultPen);
  }

  if (need_update)
    update();
}
