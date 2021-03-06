#include "optionswidget.h"

#include <QFile>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>

#include "src/database/levelsdbfacade.h"
#include "src/ui/buttons/styledbutton.h"

OptionsWidget::OptionsWidget(QWidget* parent)
    : QWidget(parent),
      m_line_path(this) {
  QGridLayout* layer = new QGridLayout(this);
  setLayout(layer);
  QLabel* store = new QLabel("Сохранить в:", this);

  m_line_path.setText("path");
  m_line_path.setStyleSheet("QLineEdit { background: rgb(153, 255, 153);}");

  StyledButton* choose = new StyledButton("Выбрать путь", this);
  StyledButton* deleteImages = new StyledButton("Удалить изображения", this);

  StyledButton* load = new StyledButton("Обновить", this);
  StyledButton* back = new StyledButton("Назад", this);

  choose->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  deleteImages->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  load->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  back->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  back->setIcon(QIcon(":/icon/back.ico"));
  load->setIcon(QIcon(":/icon/loading.ico"));

  layer->addWidget(store, 0, 0, 1, 1);
  layer->addWidget(&m_line_path, 0, 1, 1, 1);
  layer->addWidget(choose, 1, 0, 1, 3);
  layer->addWidget(deleteImages, 2, 0, 1, 3);

  layer->addWidget(load, 3, 0, 1, 3);
  layer->addWidget(back, 4, 0, 1, 3);

  connect(deleteImages, SIGNAL(clicked(bool)), SLOT(clearDatabase()));
  connect(back, SIGNAL(clicked(bool)), SIGNAL(back()));
  connect(choose, SIGNAL(clicked(bool)), SLOT(createOpenDialog()));
  connect(load, SIGNAL(clicked(bool)), SIGNAL(loadSelected()));

  QString pathValue = DBSettings.getValue("path");

  if (pathValue.isEmpty()) {
    m_line_path.setText(QDir::currentPath());
    Settings mySetting("path", m_line_path.text());
    DBSettings.set(mySetting);
  }

  m_line_path.setText(pathValue);
}

void OptionsWidget::createOpenDialog() {
  QString path =
      QFileDialog::getExistingDirectory(nullptr, "Directory Dialog", "");
  if (!path.isEmpty()) {
    m_line_path.setText(path);
    Settings mySetting("path", m_line_path.text());
    DBSettings.set(mySetting);
  }
}

void OptionsWidget::clearDatabase() {
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(
      this, "Подтверждение", "Вы действительно хотите удалить все изображения?",
      QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    DB.clearDatabase();
  }
}
