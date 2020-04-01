#ifndef TESTINGSCREENCONTROLLER_H
#define TESTINGSCREENCONTROLLER_H

#include "screensstack.h"
#include "src/testing/testsettingswidget.h"
#include "src/testing/widgetoftesting.h"
#include "src/testing/testresultswidget.h"

class TestSettingsWidget;
class WidgetOfTesting;
class TestResultsWidget;

///
/// \brief The TestingScreenController class
/// Данный класс реализует управление показом окон, связанных с тестированием
class TestingScreenController : public ScreensStack
{
  Q_OBJECT
public:
  explicit TestingScreenController(QWidget* parent = nullptr);
  void pushTestingWindow();
signals:
  void back();

protected:
  TestSettingsWidget* m_testing;
  WidgetOfTesting* m_testWindow;
  TestResultsWidget* m_testResults;
};

#endif  // TESTINGSCREENCONTROLLER_H
