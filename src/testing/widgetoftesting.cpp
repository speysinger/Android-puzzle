#include "widgetoftesting.h"
#include "testmanager.h"

WidgetOfTesting::WidgetOfTesting(QWidget *parent):QQuickWidget(parent)
{
  setStyleSheet("background-color: 'grey';");
  this->rootContext()->setContextProperty("buttonsHandler",buttonsHandler);
  this->rootContext()->setContextProperty("titles",testingTitles);
  this->setSource(QUrl(QStringLiteral("qrc:/qmlWindows/DragAndDropWindow/TestingWindow.qml")));
  this->setResizeMode(QQuickWidget::SizeRootObjectToView);
  this->setAttribute(Qt::WA_AlwaysStackOnTop);
  this->setClearColor(Qt::transparent);

  connect(&TESTMANAGER,&TestManager::newQuestionsHaveEraType, [=]{emit testingTitles->newQuestionsHaveEraType();});
  connect(&TESTMANAGER,&TestManager::newQuestionsHaveAuthorType, [=]{emit testingTitles->newQuestionsHaveAuthorType();});

}
