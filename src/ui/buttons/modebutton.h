#ifndef MODEBUTTON_H
#define MODEBUTTON_H

#include "pickedbutton.h"
#include "mode.h"

class ModeButton : public PickedButton
{
  Q_OBJECT
public:
  ModeButton(const QString& text, const Mode& mode, QWidget* parent = nullptr);
public slots:
  void unpick();
  Mode mode();
  void onPicked();
signals:
  void picked_true();

private:
  Mode m_mode;
};

#endif  // MODEBUTTON_H
