#ifndef ICONSVIEW_H
#define ICONSVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMap>
#include "menuitemproxy.h"

class IconsView : public QGraphicsView {
  Q_OBJECT
public:
  IconsView(QWidget *parent = nullptr);

  void loadAuthors();
  void loadEras();
  void loadArts(Author author);
  void loadArts(Era era);
protected:
  void resizeEvent(QResizeEvent *event) override;
  void disposeIcons();

  void scrollContentsBy(int dx, int dy) override;

  void setProxyItems();

  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
signals:
  void authorSelected(Author data);
  void eraSelected(Era data);
  void artSelected(Art data);
protected:
  QGraphicsScene m_scene;
  QPoint m_clickPos;
  std::vector<MenuItemProxy*> m_icons;

  const int IconSize = 150;
  const int NColumn = 2;

  size_t firstLoadableItemIndex = 0;
  size_t lastLoadableItemIndex = 0;
};

#endif // ICONSVIEW_H
