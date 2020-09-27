#include "levelmodewidget.h"

#include <QGridLayout>
#include <QLabel>

LevelModeWidget::LevelModeWidget(QWidget* parent) : QWidget(parent) {
  QGridLayout* layer = new QGridLayout(this);
  setLayout(layer);

  std::vector<ModeButton*> buttons = {
      new ModeButton("3x3", Mode(3, 3, true), this),
      new ModeButton("5x5", Mode(5, 5, true), this),
      new ModeButton("7x7", Mode(7, 7, true), this),
      new ModeButton("9x9", Mode(9, 9, true), this)};

  QSizePolicy buttonSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  buttonSizePolicy.setHorizontalStretch(5);

  for (size_t i = 0; i < buttons.size(); ++i) {
    layer->addWidget(buttons[i], 1, i);

    for (size_t j = 0; j < buttons.size(); ++j) {
      if (i == j) continue;
      connect(buttons[i], SIGNAL(picked_true()), buttons[j], SLOT(unpick()));
    }
    buttons[i]->setSizePolicy(buttonSizePolicy);
    connect(buttons[i], SIGNAL(picked_true()), this, SLOT(onPick()));
  }

  buttonSizePolicy.setHorizontalStretch(6);

  m_pickedButton = buttons[0];
  m_pickedButton->pick(true);

  m_rotatedButton = new PickedButton("rotated?", this);
  m_rotatedButton->setIcon(QIcon(":/icon/rotate.ico"));
  m_rotatedButton->setSizePolicy(buttonSizePolicy);

  layer->addWidget(m_rotatedButton, 1, buttons.size(), 1, 1);
}

void LevelModeWidget::onPick() {
  m_pickedButton = static_cast<ModeButton*>(sender());
}

Mode LevelModeWidget::mode() {
  Mode mode = m_pickedButton->mode();
  mode.rotated = m_rotatedButton->picked();
  return mode;
}
