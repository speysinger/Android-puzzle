#include "settingwidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QFile>
#include <QFileDialog>
#include <QDebug>

#include "buttons/styledbutton.h"
#include "update/indexloader.h"

SettingWidget::SettingWidget(QWidget* parent): QWidget(parent),
  m_line_path(this),
  m_combo_sound(this), m_sounds({"Cat", "Cow", "Frog", "Mouse", "none"}) {
  QGridLayout *layer = new QGridLayout(this);
  setLayout(layer);
  QLabel *store = new QLabel("Сохранить в", this);

  m_line_path.setText("path");
  StyledButton *choose = new StyledButton("Choose", this);
  QLabel *sound = new QLabel("Sound:", this);

  StyledButton *load = new StyledButton("Обновить", this);
  StyledButton *back = new StyledButton("Назад", this);

  load->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  back->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  back->setIcon(QIcon(":/icon/back.ico"));
  load->setIcon(QIcon(":/icon/loading.ico"));

  for (auto soundValue : m_sounds) {
    m_combo_sound.addItem(soundValue);
  }

  layer->addWidget(store, 0, 0, 1, 1);
  layer->addWidget(&m_line_path, 0, 1, 1, 1);
  layer->addWidget(choose, 0, 2, 1, 1);

  layer->addWidget(sound, 1, 0, 1, 1);
  layer->addWidget(&m_combo_sound, 1, 1, 1, 2);

  layer->addWidget(load, 2, 0, 1, 3);
  layer->addWidget(back, 3, 0, 1, 3);

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

void SettingWidget::createOpenDialog() {
  QString path = QFileDialog::getExistingDirectory(0, "Directory Dialog", "");
  m_line_path.setText(path);
  Settings mySetting("path", m_line_path.text());
  DBSettings.set(mySetting);
}

void SettingWidget::setSound() {
  Settings mySetting("sound", m_combo_sound.currentText());
  DBSettings.set(mySetting);
}

/*void SettingWidget::loadSelected() {
  //push(m_update);
  //QQmlApplicationEngine engine("qrc:/qmlWindows/UpdateWindow/UpdateWindow.qml");
}*/
