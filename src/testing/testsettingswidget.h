#ifndef TESTSETTINGSWIDGET_H
#define TESTSETTINGSWIDGET_H

#include <QQmlContext>
#include "settings/update/qmlbuttonshandler.h"
#include "settings/update/qmlwidget.h"

///
/// \brief The TestSettingsWidget class
/// Данный класс реализует создание окна настроек тестирования
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
