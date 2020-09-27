#include "updatewidget.h"

#include "src/settings/update/eralistmodel.h"

UpdateWidget::UpdateWidget(QWidget* parent) : QmlWidget(parent) {
  qmlRegisterType<EraListModel>("EraListModel", 1, 0, "EraListModel");

  m_pathToQmlFile = "qrc:/qmlWindows/UpdateWindow/UpdateWindow.qml";
  this->setSource(QUrl(m_pathToQmlFile));
  connect(m_buttonsHandler, &QmlButtonsHandler::back,
          [=] { emit backButtonPressed(); });
  connect(m_buttonsHandler, &QmlButtonsHandler::load,
          [=] { emit loadButtonPressed(); });
}
