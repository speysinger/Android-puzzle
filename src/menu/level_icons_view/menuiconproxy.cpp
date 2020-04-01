#include "menuiconproxy.h"

MenuIconProxy::MenuIconProxy(LevelGraphicsIcon* icon_) : m_icon(icon_)
{
}

LevelGraphicsIcon* MenuIconProxy::getItem()
{
  return m_icon;
}

void MenuIconProxy::setPos(qreal ax, qreal ay)
{
  m_icon->setPos(ax, ay);
}

void MenuIconProxy::setLabelSize(const int w, const int h)
{
  if (!pixmapCreated)
  {
    pixmapCreated = true;
    m_icon->setLabelSize(w, h);
  }
}

void MenuIconProxy::disableItem(const int w, const int h)
{
  if (pixmapCreated)
  {
    pixmapCreated = false;
    m_icon->disableItem(w, h);
  }
}
