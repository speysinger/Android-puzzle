#include "optionswidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QFile>
#include <QFileDialog>
#include "ui/buttons/styledbutton.h"

OptionsWidget::OptionsWidget(QWidget* parent): QWidget(parent),
  m_line_path(this),
  m_combo_sound(this), m_sounds({"Cat", "Cow", "Frog", "Mouse", "none"}) {
  QGridLayout *layer = new QGridLayout(this);
  setLayout(layer);
  QLabel *store = new QLabel("Сохранить в:", this);


  m_line_path.setText("path");
  m_line_path.setStyleSheet("QLineEdit { background: rgb(153, 255, 153);}");
  StyledButton *choose = new StyledButton("Choose", this);
  QLabel *sound = new QLabel("Sound:", this);

  StyledButton *load = new StyledButton("Обновить", this);
  StyledButton *back = new StyledButton("Назад", this);

  choose->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  m_combo_sound.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  load->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  back->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  back->setIcon(QIcon(":/icon/back.ico"));
  load->setIcon(QIcon(":/icon/loading.ico"));

  for (auto soundValue : m_sounds) {
    m_combo_sound.addItem(soundValue);
  }

  layer->addWidget(store, 0, 0, 1, 1);
  layer->addWidget(&m_line_path, 0, 1, 1, 1);
  layer->addWidget(choose, 1, 0, 1, 3);

  layer->addWidget(sound, 2, 0, 1, 1);
  layer->addWidget(&m_combo_sound, 2, 1, 1, 3);

  layer->addWidget(load, 3, 0, 1, 3);
  layer->addWidget(back, 4, 0, 1, 3);

  connect(back, SIGNAL(clicked(bool)), SIGNAL(back()));
  connect(choose, SIGNAL(clicked(bool)), SLOT(createOpenDialog()));
  connect(&m_combo_sound, SIGNAL(currentIndexChanged(QString)), SLOT(setSound()));
  connect(load, SIGNAL(clicked(bool)), SIGNAL(loadSelected()));

  m_combo_sound.setStyleSheet(" border-radius: 8px; padding: 6px; "
                              " background-color: #ccdd39;"
                              " selection-background-color: #f26665;" );
  QString soundValue = DBSettings.getValue("sound");
  QString pathValue = DBSettings.getValue("path");

  m_combo_sound.setCurrentText(soundValue);
  m_line_path.setText(pathValue);
}

void OptionsWidget::createOpenDialog() {
  QString path = QFileDialog::getExistingDirectory(nullptr, "Directory Dialog", "");
  m_line_path.setText(path);
  Settings mySetting("path", m_line_path.text());
  DBSettings.set(mySetting);
}

void OptionsWidget::setSound() {
  Settings mySetting("sound", m_combo_sound.currentText());
  DBSettings.set(mySetting);
}
