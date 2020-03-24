#include "modebutton.h"

ModeButton::ModeButton(const QString& text, const Mode& mode, QWidget* parent) :
  PickedButton (text, parent), m_mode(mode) {
  connect(this, SIGNAL(picked(bool)), this, SLOT(onPicked()));
}

void ModeButton::unpick() {
  pick(false);
}

Mode ModeButton::mode() {
  return m_mode;
}

void ModeButton::onPicked() {
  if (picked())
    emit picked_true();
}

