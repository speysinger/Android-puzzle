#include "menuitemproxy.h"

MenuItemProxy::MenuItemProxy(LevelGraphicsIcon *icon_):
  m_icon(icon_)
{
}

LevelGraphicsIcon *MenuItemProxy::getItem()
{
  return m_icon;
}

void MenuItemProxy::setPos(qreal ax, qreal ay)
{
  m_icon->setPos(ax, ay);
}

void MenuItemProxy::setLabelSize(const int w, const int h)
{
  if(!pixmapCreated)
  {
    pixmapCreated = true;
    m_icon->setLabelSize(w, h);
  }
}

void MenuItemProxy::disableItem(const int w, const int h)
{
  if(pixmapCreated)
  {
    pixmapCreated = false;
    m_icon->disableItem(w, h);
  }
}
