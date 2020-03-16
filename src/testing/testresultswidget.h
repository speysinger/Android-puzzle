#ifndef TESTRESULTSWIDGET_H
#define TESTRESULTSWIDGET_H

#include <QQmlContext>
#include "settings/update/qmlbuttonshandler.h"
#include "settings/update/qmlwidget.h"

class TestResultsWidget: public QmlWidget
{
  Q_OBJECT
public:
  TestResultsWidget(QWidget *parent=nullptr);
signals:
  void backToMainMenuButtonPressed();
};

#endif // TESTRESULTSWIDGET_H
