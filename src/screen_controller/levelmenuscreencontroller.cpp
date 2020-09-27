#include "levelmenuscreencontroller.h"

#include <memory>

#include "gamescreencontroller.h"
#include "src/database/levelsdbfacade.h"
#include "src/database/levelstructures.h"
#include "src/menu/levelmenuscreen.h"

LevelMenuScreenController::LevelMenuScreenController(QWidget* parent)
    : ScreensStack(parent), m_selectedAuthor(nullptr), m_selectedEra(nullptr) {
  m_game = new GameScreenController(this);
  m_menu = new LevelMenuScreen(this);

  m_game->hide();
  m_menu->hide();

  connect(m_game, &GameScreenController::back, [=] { pop(); });
  connect(m_menu, &LevelMenuScreen::back, [=] {
    if (m_selectedEra) {
      m_selectedEra = nullptr;
      m_selectedAuthor = nullptr;
      m_menu->loadEras();
    } else if (m_selectedAuthor) {
      m_selectedEra = nullptr;
      m_selectedAuthor = nullptr;
      m_menu->loadAuthors();
    } else {
      emit back();
    }
  });

  connect(m_menu, &LevelMenuScreen::randomSelected, [=] {
     if (m_selectedEra) {
      m_game->startRandomGame(*m_selectedEra, m_menu->mode());
    } else if (m_selectedAuthor) {
      m_game->startRandomGame(*m_selectedAuthor, m_menu->mode());
    } else {
      m_game->startRandomGame(m_menu->mode());
    }
    push(m_game);
  });

  connect(m_menu, &LevelMenuScreen::authorSelected, [=](Author author) {
    m_selectedAuthor = std::make_unique<Author>(author);
    m_menu->loadArts(author);
  });

  connect(m_menu, &LevelMenuScreen::eraSelected, [=](Era era) {
    m_selectedEra = std::make_unique<Era>(era);
    m_menu->loadArts(era);
  });

  connect(m_menu, &LevelMenuScreen::artSelected, [=](Art art) {
    push(m_game);
    m_game->startSelectedGame(art, m_menu->mode());
  });
}

void LevelMenuScreenController::showEras() {
  m_selectedEra = nullptr;
  m_selectedAuthor = nullptr;
  m_menu->loadEras();
  push(m_menu);
}

void LevelMenuScreenController::showAuthors() {
  m_selectedEra = nullptr;
  m_selectedAuthor = nullptr;
  m_menu->loadAuthors();
  push(m_menu);
}
