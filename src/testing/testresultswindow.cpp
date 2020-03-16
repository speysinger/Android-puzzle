#include "testresultswindow.h"
#include "testmanager.h"

TestResultsWindow::TestResultsWindow(QWidget *parent):QQuickWidget(parent)
{
  setStyleSheet("background-color: 'grey';");
  this->rootContext()->setContextProperty("buttonsHandler",buttonsHandler);
  this->setSource(QUrl(QStringLiteral("qrc:/qmlWindows/DragAndDropWindow/TestResults.qml")));
  this->setResizeMode(QQuickWidget::SizeRootObjectToView);
  this->setAttribute(Qt::WA_AlwaysStackOnTop);
  this->setClearColor(Qt::transparent);

  connect(buttonsHandler,&QmlButtonsHandler::back,[=] {emit backToMainMenuButtonPressed();});
}
