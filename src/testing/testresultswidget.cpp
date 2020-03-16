#include "testresultswidget.h"
#include "testmanager.h"

TestResultsWidget::TestResultsWidget(QWidget *parent):
  QmlWidget(parent)
{
  pathToQmlFile = "qrc:/qmlWindows/DragAndDropWindow/TestResults.qml";
  this->setSource(QUrl(pathToQmlFile));
  connect(buttonsHandler,&QmlButtonsHandler::back,[=] {emit backToMainMenuButtonPressed();});
}
