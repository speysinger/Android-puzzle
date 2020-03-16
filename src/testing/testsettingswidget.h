#ifndef TESTSETTINGSWIDGET_H
#define TESTSETTINGSWIDGET_H

#include <QQmlContext>
#include "settings/update/qmlbuttonshandler.h"
#include "settings/update/qmlwidget.h"

class TestSettingsWidget: public QmlWidget
{
  Q_OBJECT
public:
  TestSettingsWidget(QWidget *parent = nullptr);
signals:
  void backButtonPressed();
  void startTestingButtonPressed();
};

#endif // TESTSETTINGSWIDGET_H
