#ifndef TESTRESULTSWIDGET_H
#define TESTRESULTSWIDGET_H

#include <QQmlContext>
#include "settings/update/qmlbuttonshandler.h"
#include "settings/update/qmlwidget.h"

///
/// \brief The TestResultsWidget class
/// Данный класс реализует создание окна вывода статистики тестирования
class TestResultsWidget: public QmlWidget
{
  Q_OBJECT
public:
  TestResultsWidget(QWidget *parent=nullptr);
signals:
  void backToMainMenuButtonPressed();
};

#endif // TESTRESULTSWIDGET_H
