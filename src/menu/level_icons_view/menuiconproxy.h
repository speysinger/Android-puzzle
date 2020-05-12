#ifndef MENUICONPROXY_H
#define MENUICONPROXY_H

#include "levelicon.h"

class MenuIconProxy {
 public:
  MenuIconProxy(LevelGraphicsIcon* icon_);
  LevelGraphicsIcon* getItem();
  void setLabelSize(const int w, const int h);
  void setPos(qreal ax, qreal ay);
  void disableItem(const int w, const int h);

 private:
  bool pixmapCreated = false;
  LevelGraphicsIcon* m_icon;
};

#endif  // MENUICONPROXY_H
