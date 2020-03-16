#ifndef PUZZLEVIEW_H
#define PUZZLEVIEW_H

#include <QGraphicsView>
#include <QPinchGesture>
#include <QGraphicsScene>
#include <QPinchGesture>
#include <QDebug>

class PuzzleView : public QGraphicsView {
  Q_OBJECT
public:
  PuzzleView(QGraphicsScene* scene);
signals:
  void gesture_started();
  void change_scalefactor();
protected:
  virtual bool event(QEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
private:
  bool gestureEvent(QGestureEvent *event);
  void pinchTriggered(QPinchGesture* pinch);
};

#endif // PUZZLEVIEW_H
