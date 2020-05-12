#include "levelmenuscreen.h"

#include <QGridLayout>

#include "src/menu/level_icons_view/iconsview.h"
#include "src/ui/buttons/levelmodewidget.h"
#include "src/ui/buttons/styledbutton.h"
#include "src/ui/html_view/helpviewer.h"

LevelMenuScreen::LevelMenuScreen(QWidget* parent)
    : QWidget(parent),
      m_modeWidget(new LevelModeWidget(this)),
      m_iconView(new IconsView(this)) {
  QGridLayout* layer = new QGridLayout(this);
  setLayout(layer);

  QSizePolicy buttonSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  buttonSizePolicy.setVerticalStretch(1);

  StyledButton* randomButton = new StyledButton("Случайный старт", this);
  StyledButton* backButton = new StyledButton("Назад", this);

  randomButton->setIcon(QIcon(":/icon/play.ico"));
  randomButton->setSizePolicy(buttonSizePolicy);
  backButton->setIcon(QIcon(":/icon/back.ico"));
  backButton->setSizePolicy(buttonSizePolicy);

  m_modeWidget->setSizePolicy(buttonSizePolicy);

  buttonSizePolicy.setVerticalStretch(8);
  m_iconView->setSizePolicy(buttonSizePolicy);

  layer->addWidget(m_iconView, 1, 0, 1, 4);
  layer->addWidget(m_modeWidget, 2, 0, 1, 4);

  layer->addWidget(randomButton, 3, 0, 1, 2);
  layer->addWidget(backButton, 3, 2, 1, 2);

  connect(m_iconView, SIGNAL(authorSelected(Author)),
          SIGNAL(authorSelected(Author)));
  connect(m_iconView, SIGNAL(eraSelected(Era)), SIGNAL(eraSelected(Era)));
  connect(m_iconView, SIGNAL(artSelected(Art)), SIGNAL(artSelected(Art)));

  connect(backButton, SIGNAL(clicked()), this, SIGNAL(back()));
  connect(randomButton, SIGNAL(clicked()), this, SIGNAL(randomSelected()));
}

Mode LevelMenuScreen::mode() { return m_modeWidget->mode(); }

void LevelMenuScreen::loadAuthors() { m_iconView->loadAuthors(); }

void LevelMenuScreen::loadEras() { m_iconView->loadEras(); }

void LevelMenuScreen::loadArts(Author author) { m_iconView->loadArts(author); };

void LevelMenuScreen::loadArts(Era era) { m_iconView->loadArts(era); }
