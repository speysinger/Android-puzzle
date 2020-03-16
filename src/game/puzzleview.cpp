#include "puzzleview.h"
#include "game/puzzleitem/puzzlematrix.h"
#include "game/puzzleitem/settableitem.h"
#include "game/puzzleitem/selectableitem.h"
#include "game/puzzleitem/puzzleitem.h"
#include "game/puzzleitem/rotatableitem.h"

PuzzleView::PuzzleView(QGraphicsScene *scene)
  : QGraphicsView(scene) {
  grabGesture(Qt::PinchGesture);
  setAttribute(Qt::WA_AcceptTouchEvents);
  setTransformationAnchor(AnchorViewCenter);

  setViewportMargins(0, 0, 0, 0);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

bool PuzzleView::event(QEvent *event) {
  if (event->type() == QEvent::Gesture)
    return gestureEvent(static_cast<QGestureEvent*>(event));
  return QGraphicsView::event(event);
}

bool PuzzleView::gestureEvent(QGestureEvent *event) {
  qDebug() << "gestureEvent";
  if (QGesture *pinch = event->gesture(Qt::PinchGesture))
    pinchTriggered(static_cast<QPinchGesture *>(pinch));
  return true;
}

void PuzzleView::pinchTriggered(QPinchGesture* pinch) {
  if (pinch->state() == Qt::GestureUpdated) {
    auto scaleValue = pinch->scaleFactor();
    scale(scaleValue, scaleValue);
    emit change_scalefactor();
  }
}

void PuzzleView::mousePressEvent(QMouseEvent *event) {
  auto item = dynamic_cast<SettableItem*>(itemAt(event->pos()));
  if (item && false == item->is_setted()) {
    setInteractive(true);
    setDragMode(QGraphicsView::DragMode::NoDrag);
  }
  else {
    setInteractive(false);
    setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
  }
  QGraphicsView::mousePressEvent(event);
}
