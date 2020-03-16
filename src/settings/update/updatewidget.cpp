#include "updateWidget.h"

UpdateWidget::UpdateWidget(QWidget *parent):
  QmlWidget(parent)
{
  pathToQmlFile = "qrc:/qmlWindows/UpdateWindow/UpdateWindow.qml";
  this->setSource(QUrl(pathToQmlFile));
  connect(buttonsHandler,&QmlButtonsHandler::back,[=] {emit backButtonPressed();});
  connect(buttonsHandler,&QmlButtonsHandler::load,[=]{emit loadButtonPressed();});

}

