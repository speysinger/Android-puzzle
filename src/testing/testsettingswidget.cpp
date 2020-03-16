#include "testsettingswidget.h"
#include "testmanager.h"

#include <QtQuick>
#include <QQuickItem>
#include <QQuickView>


TestSettingsWidget::TestSettingsWidget(QWidget *parent):QQuickWidget(parent)
{
  setStyleSheet("background-color: 'grey';");
  this->rootContext()->setContextProperty("buttonsHandler",buttonsHandler);
  this->setSource(QUrl(QStringLiteral("qrc:/qmlWindows/DragAndDropWindow/TestSettingsWindow.qml")));
  this->setResizeMode(QQuickWidget::SizeRootObjectToView);
  this->setAttribute(Qt::WA_AlwaysStackOnTop);
  this->setClearColor(Qt::transparent);

  connect(buttonsHandler,&QmlButtonsHandler::back,[=] { emit backButtonPressed();});

  connect(&TESTMANAGER,&TestManager::possibleToStartTesting, [=] {emit startTestingButtonPressed();});

  auto root = this->rootObject();

  connect(&TESTMANAGER,SIGNAL(notEnoughFilesToStartTesting()), root, SIGNAL(notEnoughFilesToStartTesting()));

}

