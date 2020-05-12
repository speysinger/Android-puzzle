#ifndef PUZZLEVIEW_H
#define PUZZLEVIEW_H

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPinchGesture>

class PuzzleView : public QGraphicsView {
  Q_OBJECT
 public:
  PuzzleView(QGraphicsScene *scene);
 signals:
  void gesture_started();
  void change_scalefactor();

 protected:
  virtual bool event(QEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

 private:
  bool gestureEvent(QGestureEvent *event);
  void pinchTriggered(QPinchGesture *pinch);
};

#endif  // PUZZLEVIEW_H
