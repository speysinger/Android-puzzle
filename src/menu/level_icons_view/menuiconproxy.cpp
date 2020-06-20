#include "menuiconproxy.h"

MenuIconProxy::MenuIconProxy(Art art) {
  ArtIcon* artIcon = new ArtIcon(std::move(art));
  m_icon = artIcon;
}

MenuIconProxy::MenuIconProxy(Era era) {
  EraIcon* eraIcon = new EraIcon(std::move(era));
  m_icon = eraIcon;
}

MenuIconProxy::MenuIconProxy(Author author) {
  AuthorIcon* authorIcon = new AuthorIcon(std::move(author));
  m_icon = authorIcon;
}

LevelGraphicsIcon* MenuIconProxy::getItem() { return m_icon; }

void MenuIconProxy::setPos(qreal ax, qreal ay) { m_icon->setPos(ax, ay); }

void MenuIconProxy::setLabelSize(const int w, const int h) {
  if (!pixmapCreated) {
    pixmapCreated = true;
    m_icon->setLabelSize(w, h);
  }
}

void MenuIconProxy::disableItem(const int w, const int h) {
  if (pixmapCreated) {
    pixmapCreated = false;
    m_icon->disableItem(w, h);
  }
}
