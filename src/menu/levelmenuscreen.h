#ifndef CATEGORYWIDGET_H
#define CATEGORYWIDGET_H

#include "mode.h"
#include "level_icons_view/iconsview.h"

class LevelModeWidget;

class LevelMenuScreen : public QWidget {
  Q_OBJECT
public:
  LevelMenuScreen(QWidget* parent = nullptr);
  Mode mode();

  void loadAuthors();
  void loadEras();

  void loadArts(Author author);
  void loadArts(Era era);
signals:
  void randomSelected();
  void back();

  void authorSelected(Author data);
  void eraSelected(Era data);
  void artSelected(Art data);

protected:
   LevelModeWidget* m_modeWidget;
   IconsView *m_iconView;
};

#endif // CATEGORYWIDGET_H
