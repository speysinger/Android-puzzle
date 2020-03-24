#include "pickedbutton.h"
#include <QStyle>

PickedButton::PickedButton(const QString& text, QWidget *parent):
  QPushButton(text, parent), m_picked(false) {

  connect(this, SIGNAL(clicked()), SLOT(invert()));
  setStyleSheet(
    " QPushButton {border-radius: 8px; padding: 6px;}"
    " QPushButton[picked=true] { background-color: #f26665;}"
    " QPushButton[picked=false] { background-color: #f6d70a;}"
    " QPushButton { font-family: hAndy;}"
  );
}

bool PickedButton::picked() {
  return m_picked;
}

void PickedButton::pick(bool is_picked) {
  if (m_picked == is_picked)
    return;

  m_picked = is_picked;
  style()->unpolish(this);
  style()->polish(this);

  emit picked(m_picked);
}

void PickedButton::invert() {
  pick(!m_picked);
}


