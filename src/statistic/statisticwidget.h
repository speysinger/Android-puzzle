#ifndef STATISTICWIDGET_H
#define STATISTICWIDGET_H

#include <QQuickWidget>
#include <QQmlContext>
#include "settings/update/qmlbuttonshandler.h"

class StatisticWidget: public QQuickWidget
{
  Q_OBJECT
public:
  StatisticWidget(QWidget *parent = nullptr);
  void loadStatistic();
signals:
  void back();

private:
  QmlButtonsHandler *buttonsHandler=new QmlButtonsHandler();
};

#endif // STATISTICWIDGET_H
