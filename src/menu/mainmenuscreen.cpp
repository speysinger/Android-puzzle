#include "mainmenuscreen.h"

#include <QGridLayout>
#include <QPushButton>

#include "src/ui/buttons/styledbutton.h"

MainMenuScreen::MainMenuScreen(QWidget* parent)
    : QWidget(parent), m_modeWidget(new LevelModeWidget(this)) {
  QGridLayout* layer = new QGridLayout(this);
  setLayout(layer);

  StyledButton* randomPictures = new StyledButton("Случайная картинка", this);
  StyledButton* authors = new StyledButton("Выбрать автора", this);
  StyledButton* eras = new StyledButton("Выбрать эпоху", this);
  StyledButton* testing = new StyledButton("Тестирование", this);
  StyledButton* statictic = new StyledButton("Статистика", this);
  StyledButton* settings = new StyledButton("Настройки", this);
  StyledButton* aboutProgram = new StyledButton("О программе", this);
  StyledButton* exit = new StyledButton("Выход", this);

  settings->setIcon(QIcon(":/icon/settings.ico"));

  m_modeWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  m_modeWidget->sizePolicy().setHorizontalStretch(1);
  m_modeWidget->sizePolicy().setVerticalStretch(2);

  randomPictures->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  authors->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  eras->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  testing->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  statictic->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  settings->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  aboutProgram->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  exit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  layer->addWidget(m_modeWidget, 0, 0, 1, 2);
  layer->addWidget(randomPictures, 1, 0, 1, 2);
  layer->addWidget(authors, 2, 1);
  layer->addWidget(eras, 2, 0);
  layer->addWidget(testing, 3, 0, 1, 2);
  layer->addWidget(statictic, 4, 0, 1, 2);
  layer->addWidget(settings, 5, 0, 1, 2);
  layer->addWidget(aboutProgram, 6, 0);
  layer->addWidget(exit, 6, 1);

  layer->setSpacing(10);

  connect(testing, SIGNAL(clicked()), this, SIGNAL(testingSelected()));
  connect(settings, SIGNAL(clicked()), this, SIGNAL(settingsSelected()));
  connect(eras, SIGNAL(clicked()), this, SIGNAL(erasSelected()));
  connect(authors, SIGNAL(clicked()), this, SIGNAL(authorsSelected()));
  connect(randomPictures, SIGNAL(clicked()), this, SIGNAL(randomSelected()));
  connect(statictic, SIGNAL(clicked()), this, SIGNAL(statisticSelected()));
  connect(aboutProgram, SIGNAL(clicked()), this,
          SIGNAL(aboutProgramSelected()));
  connect(exit, SIGNAL(clicked()), this, SIGNAL(exit()));
}

Mode MainMenuScreen::mode() { return m_modeWidget->mode(); }
