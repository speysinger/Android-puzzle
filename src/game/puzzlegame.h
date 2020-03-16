#ifndef PUZZLEGAME_H
#define PUZZLEGAME_H

#include "mode.h"
#include "puzzleview.h"
#include "pathpoints.h"
#include "puzzlepath.h"
#include "game/puzzleitem/puzzleitem.h"
#include "sound_controller/soundcontroller.h"
#include <QLabel>

class SettableItem;

class PuzzleGame : public QWidget {
  Q_OBJECT
public:
  PuzzleGame(QWidget* parent = nullptr);
  void load(QPixmap source, Mode mode);
  void setLabel(QString str) { // TODO: remove
    m_label.setText(str);
  }
protected slots:
  void onItemClicked();
  void onItemSetted();
  void rotate90();
signals:
  void finished();
  void back();

protected:
  QGraphicsScene m_scene;
  PuzzleView m_view;
  SoundController m_sound;
  QLabel m_label;

  const int GroundLayer = 0;
  int m_selectionLayer;
  int m_unsetted;
  bool m_image_orientation;
};

#endif // PUZZLEGAME_H
