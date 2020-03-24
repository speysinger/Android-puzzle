#ifndef LEVELMODE_H
#define LEVELMODE_H

#include <QWidget>
#include "mode.h"
#include "ui/buttons/modebutton.h"

//! кнопки для выбора уровня (количества разбиений)
class LevelModeWidget: public QWidget {
  Q_OBJECT
public:
  LevelModeWidget(QWidget* parent = nullptr);
  Mode mode();
public slots:
  void onPick();
protected:
  ModeButton *m_pickedButton;
  PickedButton *m_rotatedButton;
};

#endif // LEVELMODE_H
