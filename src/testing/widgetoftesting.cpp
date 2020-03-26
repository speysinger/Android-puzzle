#include "widgetoftesting.h"
#include "testmanager.h"

WidgetOfTesting::WidgetOfTesting(QWidget* parent) : QmlWidget(parent)
{
  m_pathToQmlFile = "qrc:/qmlWindows/DragAndDropWindow/TestingWindow.qml";

  this->rootContext()->setContextProperty("titles", m_testingTitles);
  this->setSource(QUrl(m_pathToQmlFile));
  connect(&TESTMANAGER, &TestManager::newQuestionsHaveEraType,
          [=] { emit m_testingTitles->newQuestionsHaveEraType(); });
  connect(&TESTMANAGER, &TestManager::newQuestionsHaveAuthorType,
          [=] { emit m_testingTitles->newQuestionsHaveAuthorType(); });
}
