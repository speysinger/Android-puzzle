#ifndef TESTRESULTSWINDOW_H
#define TESTRESULTSWINDOW_H

#include <QQuickWidget>
#include <QQmlContext>
#include "settings/update/qmlbuttonshandler.h"

class TestResultsWindow: public QQuickWidget
{
  Q_OBJECT
public:
  TestResultsWindow(QWidget *parent=nullptr);
signals:
  void backToMainMenuButtonPressed();
private:
  QmlButtonsHandler *buttonsHandler=new QmlButtonsHandler();
};

#endif // TESTRESULTSWINDOW_H
