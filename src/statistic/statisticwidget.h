#ifndef STATISTICWIDGET_H
#define STATISTICWIDGET_H

#include <QQmlContext>
#include "settings/update/qmlbuttonshandler.h"
#include "settings/update/qmlwidget.h"
///
/// \brief The StatisticWidget class
/// Данный класс реализует создание qml окна, отображающего игровую статистику
class StatisticWidget: public QmlWidget
{
  Q_OBJECT
public:
  StatisticWidget(QWidget *parent = nullptr);
  void loadStatistic();
signals:
  void back();
  void loadData();
};

#endif // STATISTICWIDGET_H
