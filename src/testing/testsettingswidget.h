#ifndef TESTSETTINGSWIDGET_H
#define TESTSETTINGSWIDGET_H

#include <QQuickWidget>
#include <QQmlContext>
#include "settings/update/qmlbuttonshandler.h"

class TestSettingsWidget: public QQuickWidget
{
  Q_OBJECT
public:
  TestSettingsWidget(QWidget *parent = nullptr);
signals:
  void backButtonPressed();
  void startTestingButtonPressed();

private:
  QmlButtonsHandler *buttonsHandler=new QmlButtonsHandler();
};

#endif // TESTSETTINGSWIDGET_H
