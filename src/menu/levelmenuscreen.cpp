#include "levelmenuscreen.h"
#include <QGridLayout>
#include "ui/buttons/levelmodewidget.h"
#include "ui/buttons/styledbutton.h"
#include "ui/html_view/helpviewer.h"
#include "menu/level_icons_view/iconsview.h"

LevelMenuScreen::LevelMenuScreen(QWidget* parent):
  QWidget(parent),
  m_modeWidget(new LevelModeWidget(this)),
  m_iconView(new IconsView(this)) {

  QGridLayout *layer = new QGridLayout(this);
  setLayout(layer);

  StyledButton *randomButton = new StyledButton("Случайный старт", this);
  StyledButton *backButton = new StyledButton("Назад", this);

  randomButton->setIcon(QIcon(":/icon/play.ico"));
  backButton->setIcon(QIcon(":/icon/back.ico"));

  layer->addWidget(m_iconView, 1, 0, 1, 4);
  layer->addWidget(m_modeWidget, 2, 0, 1, 4);

  layer->addWidget(randomButton, 3, 0, 1, 2);
  layer->addWidget(backButton, 3, 2, 1, 2);

  connect(m_iconView, SIGNAL(authorSelected(Author)), SIGNAL(authorSelected(Author)));
  connect(m_iconView, SIGNAL(eraSelected(Era)), SIGNAL(eraSelected(Era)));
  connect(m_iconView, SIGNAL(artSelected(Art)), SIGNAL(artSelected(Art)));

  connect(backButton, SIGNAL(clicked()), this, SIGNAL(back()));
  connect(randomButton, SIGNAL(clicked()), this, SIGNAL(randomSelected()));
}

Mode LevelMenuScreen::mode() {
  return m_modeWidget->mode();
}

void LevelMenuScreen::loadAuthors() {
  m_iconView->loadAuthors();
}

void LevelMenuScreen::loadEras() {
  m_iconView->loadEras();
}

void LevelMenuScreen::loadArts(Author author) {
  m_iconView->loadArts(author);
};

void LevelMenuScreen::loadArts(Era era) {
  m_iconView->loadArts(era);
}


