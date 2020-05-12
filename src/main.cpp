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

  QFontDatabase::addApplicationFont(":/fonts/menu_font.ttf");

  MainMenuScreenController controller;
  controller.showFullScreen();

  controller.setStyleSheet("QWidget { background-color:#FFFFE0; border: 0px;}");
  return a.exec();
}
