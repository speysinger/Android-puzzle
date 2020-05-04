#include "testresultswidget.h"
#include "testmanager.h"
#include "src/testing/models/testingresultsmodel.h"

TestResultsWidget::TestResultsWidget(QWidget* parent) : QmlWidget(parent)
{
      qmlRegisterType<TestingResultsModel>("TestingResultsModel", 1, 0, "TestingResultsModel");

  m_pathToQmlFile = "qrc:/qmlWindows/DragAndDropWindow/TestResults.qml";
  this->setSource(QUrl(m_pathToQmlFile));
  connect(m_buttonsHandler, &QmlButtonsHandler::back, [=] { emit backToMainMenuButtonPressed(); });
}
