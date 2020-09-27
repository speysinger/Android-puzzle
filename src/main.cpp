 #include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QSslSocket>
#include <iostream>
#include <map>

#include "database/levelsdbfacade.h"
#include "screen_controller/mainmenuscreencontroller.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  QFile levels(":/pictures_db/levels.json");
  QFileInfo check_db("puzzleDB.db1");

    if (levels.open(QIODevice::ReadOnly | QFile::Text) && !check_db.exists()) {
      DB.loadLevels(levels.readAll());
    }

  QFontDatabase::addApplicationFont(":/fonts/menu_font.ttf");

  MainMenuScreenController controller;
  controller.showFullScreen();

  controller.setStyleSheet("QWidget { background-color:#FFFFE0; border: 0px;}");
  return a.exec();
}
