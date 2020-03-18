#include <QApplication>
#include <QFontDatabase>
#include "screen_controller/mainmenuscreencontroller.h"
#include <QFile>
#include "database/levelsdbfacade.h"

#include <map>
#include <iostream>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  /*QFile levels(":/pictures_db/levels.json");
  if (levels.open(QIODevice::ReadOnly | QFile::Text)) {
    DB.loadLevels(levels.readAll());
  }*/

  QFontDatabase::addApplicationFont(":/fonts/menu_font.ttf");

  MainMenuScreenController controller;
  controller.show();

  controller.setStyleSheet(
        "QWidget { background-color:#FFFFE0; border: 0px; width: 40; height:30}"
  );
  return a.exec();
}
