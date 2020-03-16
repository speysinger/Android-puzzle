#include "universalmodebutton.h"
#include <QStyle>

UniversalModeButton::UniversalModeButton(const QString& text, QWidget* parent) :
  QPushButton (parent) {
  setText(text);
  connect(this, SIGNAL(pressed()), this, SLOT(pick()));

  setStyleSheet(
    "QPushButton { "
      "  border-style: outset;"
      "  border-width: 2px;"
      "  border-radius: 8px;"
      " padding: 6px; "
    "}"
    " QPushButton[picked=true] { background-color: rgba(255, 0, 0, 200);}"
    " QPushButton[picked=false] { background-color: rgba(0, 255, 0, 200);}"
  );
}

bool UniversalModeButton::picked() {
  return m_picked;
}

void UniversalModeButton::pick(bool picked) {
  if (m_picked == picked)
    return;

  m_picked = picked;
  style()->unpolish(this);
  style()->polish(this);
}

void UniversalModeButton::pick() {
  pick(true);
  emit picked_true();
}

void UniversalModeButton::unpick() {
  pick(false);
}

