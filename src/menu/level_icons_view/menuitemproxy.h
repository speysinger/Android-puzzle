#ifndef MENUITEMPROXY_H
#define MENUITEMPROXY_H

#include "levelicon.h"

class MenuItemProxy
{
public:
  MenuItemProxy(LevelGraphicsIcon* icon_);
  LevelGraphicsIcon* getItem();
  void setLabelSize(const int w, const int h);
  void setPos(qreal ax, qreal ay);
  void disableItem(const int w, const int h);

private:
  bool pixmapCreated = false;
  LevelGraphicsIcon* m_icon;
};

#endif  // MENUITEMPROXY_H
