#include "testsettingswidget.h"
#include "testmanager.h"

#include <QQuickItem>

TestSettingsWidget::TestSettingsWidget(QWidget* parent) : QmlWidget(parent)
{
  m_pathToQmlFile = "qrc:/qmlWindows/DragAndDropWindow/TestSettingsWindow.qml";
  this->setSource(QUrl(m_pathToQmlFile));

  connect(m_buttonsHandler, &QmlButtonsHandler::back, [=] { emit backButtonPressed(); });
  connect(&TESTMANAGER, &TestManager::possibleToStartTesting, [=] { emit startTestingButtonPressed(); });

  auto root = this->rootObject();

  connect(&TESTMANAGER, SIGNAL(notEnoughFilesToStartTesting()), root, SIGNAL(notEnoughFilesToStartTesting()));
}
