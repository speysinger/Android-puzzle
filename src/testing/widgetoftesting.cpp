#include "widgetoftesting.h"
#include "testmanager.h"

WidgetOfTesting::WidgetOfTesting(QWidget *parent):
  QmlWidget(parent)
{
  pathToQmlFile = "qrc:/qmlWindows/DragAndDropWindow/TestingWindow.qml";

  this->rootContext()->setContextProperty("titles", testingTitles);
  this->setSource(QUrl(pathToQmlFile));
  connect(&TESTMANAGER,&TestManager::newQuestionsHaveEraType, [=]{emit testingTitles->newQuestionsHaveEraType();});
  connect(&TESTMANAGER,&TestManager::newQuestionsHaveAuthorType, [=]{emit testingTitles->newQuestionsHaveAuthorType();});
}
