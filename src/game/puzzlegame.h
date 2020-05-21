#ifndef PUZZLEGAME_H
#define PUZZLEGAME_H

#include <QLabel>

#include "pathpoints.h"
#include "puzzlepath.h"
#include "puzzleview.h"
#include "src/game/puzzleitem/puzzleitem.h"
#include "src/mode.h"
#include "src/sound_controller/soundcontroller.h"

class SettableItem;

class PuzzleGame : public QWidget {
  Q_OBJECT
 public:
  PuzzleGame(QWidget* parent = nullptr);
  void load(QPixmap source, Mode mode);
 protected slots:
  void onItemClicked();
  void onItemSetted();
  void rotate90();
 signals:
  void finished();
  void back();

 protected:
  const int GroundLayer = 0;
  int m_selectionLayer;
  int m_unsetted;
  bool m_image_orientation;

  QGraphicsScene m_scene;
  PuzzleView m_view;
  SoundController m_sound;
};

#endif  // PUZZLEGAME_H
