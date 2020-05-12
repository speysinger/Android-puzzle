#include "progressbarwidget.h"

#include "updater.h"

ProgressBarWidget::ProgressBarWidget(QWidget* parent) : QmlWidget(parent) {
  m_pathToQmlFile = "qrc:/qmlWindows/UpdateWindow/ProgressBarWindow.qml";
  this->rootContext()->setContextProperty("progressInd", m_loadHandler);

  this->setSource(QUrl(m_pathToQmlFile));
  connect(m_loadHandler, &LoadHandler::back, [=] {
    m_loadHandler->resetValues();
    emit backButtonPressed();
  });

  connect(&UPDATER, &Updater::maxValueCalculated,
          [=](int maxValue) { m_loadHandler->setMaxValue(maxValue); });

  connect(&UPDATER, &Updater::fileLoaded, [=] { m_loadHandler->incValue(); });
}
