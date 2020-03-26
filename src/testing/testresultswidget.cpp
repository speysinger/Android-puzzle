#include "testresultswidget.h"
#include "testmanager.h"

TestResultsWidget::TestResultsWidget(QWidget* parent) : QmlWidget(parent)
{
  m_pathToQmlFile = "qrc:/qmlWindows/DragAndDropWindow/TestResults.qml";
  this->setSource(QUrl(m_pathToQmlFile));
  connect(m_buttonsHandler, &QmlButtonsHandler::back, [=] { emit backToMainMenuButtonPressed(); });
}
