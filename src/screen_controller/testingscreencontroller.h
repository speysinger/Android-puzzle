#ifndef TESTINGSCREENCONTROLLER_H
#define TESTINGSCREENCONTROLLER_H


#include "screensstack.h"
#include "testing/testsettingswidget.h"
#include "testing/widgetoftesting.h"
#include "testing/testresultswindow.h"

class TestSettingsWidget;
class WidgetOfTesting;
class TestResultsWindow;

class TestingScreenController : public ScreensStack {
  Q_OBJECT
public:
  explicit TestingScreenController(QWidget *parent = nullptr);
  void pushTestingWindow();
signals:
  void back();
protected:
   TestSettingsWidget *m_testing;
   WidgetOfTesting *m_testWindow;
   TestResultsWindow *m_testResults;
};

#endif // TESTINGSCREENCONTROLLER_H
