#include "widgetoftesting.h"
#include "testmanager.h"
#include "src/testing/models/draggridmodel.h"
#include "src/testing/models/dropgridmodel.h"

WidgetOfTesting::WidgetOfTesting(QWidget* parent) : QmlWidget(parent)
{

    qmlRegisterType<DropGridModel>("dropgridmodel", 1, 0, "DropGridModel");
    qmlRegisterType<DragGridModel>("draggridmodel", 1, 0, "DragGridModel");

  m_pathToQmlFile = "qrc:/qmlWindows/DragAndDropWindow/TestingWindow.qml";

  this->rootContext()->setContextProperty("titles", m_testingTitles);
  this->setSource(QUrl(m_pathToQmlFile));
  connect(&TESTMANAGER, &TestManager::newQuestionsHaveEraType,
          [=] { emit m_testingTitles->newQuestionsHaveEraType(); });
  connect(&TESTMANAGER, &TestManager::newQuestionsHaveAuthorType,
          [=] { emit m_testingTitles->newQuestionsHaveAuthorType(); });
}
