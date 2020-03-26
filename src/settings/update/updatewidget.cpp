#include "updatewidget.h"

UpdateWidget::UpdateWidget(QWidget* parent) : QmlWidget(parent)
{
  m_pathToQmlFile = "qrc:/qmlWindows/UpdateWindow/UpdateWindow.qml";
  this->setSource(QUrl(m_pathToQmlFile));
  connect(m_buttonsHandler, &QmlButtonsHandler::back, [=] { emit backButtonPressed(); });
  connect(m_buttonsHandler, &QmlButtonsHandler::load, [=] { emit loadButtonPressed(); });
}
