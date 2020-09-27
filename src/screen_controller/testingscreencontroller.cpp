#include "testingscreencontroller.h"

#include "src/settings/update/eralistmodel.h"
#include "src/testing/models/testingresultsmodel.h"
#include "src/testing/testmanager.h"

TestingScreenController::TestingScreenController(QWidget* parent)
    : ScreensStack(parent) {
  m_testing = new TestSettingsWidget(this);
  m_testWindow = new WidgetOfTesting(this);
  m_testResults = new TestResultsWidget(this);

  connect(m_testing, &TestSettingsWidget::backButtonPressed, [=] {
    emit back();
    pop();
  });
  connect(m_testResults, &TestResultsWidget::backToMainMenuButtonPressed, [=] {
    pop();
    emit back();
  });

  connect(m_testing, &TestSettingsWidget::startTestingButtonPressed,
          [=] { push(m_testWindow); });

  connect(&TESTMANAGER, &TestManager::questionsIsOver, [=] {
    pop();
    push(m_testResults);
  });
}

void TestingScreenController::pushTestingWindow() {
  TESTMANAGER.loadAvailableEras();
  push(m_testing);
}
