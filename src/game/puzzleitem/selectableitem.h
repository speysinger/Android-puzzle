#ifndef SELECTABLEITEM_H
#define SELECTABLEITEM_H

#include "game/puzzlepath.h"
#include "puzzleitem.h"
#include <QPainter>

//! выделение Фрагментов пазла
class SelectableItem : public PuzzleItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
public:
  SelectableItem(PuzzlePath *path, const QPixmap& source, const QRect &rect,
               QObject *parent = nullptr) :
    PuzzleItem(path, source, rect, parent) {

    m_border = new QGraphicsPathItem(m_path->path);
    set_selected(false, false);
  }

  ~SelectableItem() override;

  void paint(QPainter *painter,
             const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;

  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

  void set_selected(bool selection, bool need_update);
signals:
  void clicked();

public slots:
  void clear_selection() {
      set_selected(false, true);
  }
protected:
  bool m_selection;

  QGraphicsPathItem* m_border;

  const QPen
    SelectionPen = {QColor(255, 117, 56), 2},
    DefaultPen = {QColor(0, 0, 0), 1};
};

#endif // SELECTABLEITEM_H
