#include "testsettingswidget.h"
#include "testmanager.h"

#include <QtQuick>
#include <QQuickItem>


TestSettingsWidget::TestSettingsWidget(QWidget *parent):
  QmlWidget(parent)
{
  pathToQmlFile = "qrc:/qmlWindows/DragAndDropWindow/TestSettingsWindow.qml";
  this->setSource(QUrl(pathToQmlFile));

  connect(buttonsHandler,&QmlButtonsHandler::back,[=] { emit backButtonPressed();});
  connect(&TESTMANAGER,&TestManager::possibleToStartTesting, [=] {emit startTestingButtonPressed();});

  auto root = this->rootObject();

  connect(&TESTMANAGER,SIGNAL(notEnoughFilesToStartTesting()), root, SIGNAL(notEnoughFilesToStartTesting()));

}

