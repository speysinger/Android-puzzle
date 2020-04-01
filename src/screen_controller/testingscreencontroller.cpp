#include "testingscreencontroller.h"
#include "src/testing/testmanager.h"
#include "src/settings/update/eralistmodel.h"
#include "src/testing/models/testingresultsmodel.h"
#include "src/testing/models/draggridmodel.h"
#include "src/testing/models/dropgridmodel.h"

TestingScreenController::TestingScreenController(QWidget* parent) : ScreensStack(parent)
{
  qmlRegisterType<EraListModel>("EraListModel", 1, 0, "EraListModel");
  qmlRegisterType<TestingResultsModel>("TestingResultsModel", 1, 0, "TestingResultsModel");
  qmlRegisterType<DropGridModel>("dropgridmodel", 1, 0, "DropGridModel");
  qmlRegisterType<DragGridModel>("draggridmodel", 1, 0, "DragGridModel");

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

  connect(m_testing, &TestSettingsWidget::startTestingButtonPressed, [=] { push(m_testWindow); });

  connect(&TESTMANAGER, &TestManager::questionsIsOver, [=] {
    pop();
    push(m_testResults);
  });
}

void TestingScreenController::pushTestingWindow()
{
  TESTMANAGER.loadAvailableEras();
  push(m_testing);
}
