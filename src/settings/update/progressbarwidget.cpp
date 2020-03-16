#include "progressBarWidget.h"
#include "updater.h"

ProgressBarWidget::ProgressBarWidget(QWidget *parent):
  QmlWidget(parent)
{
  pathToQmlFile = "qrc:/qmlWindows/UpdateWindow/ProgressBarWindow.qml";
  this->rootContext()->setContextProperty("progressInd",loadHandler);

  this->setSource(QUrl(pathToQmlFile));
  connect(loadHandler,&LoadHandler::back,[=] {emit backButtonPressed();});

  connect(&UPDATER,&Updater::maxValueCalculated, [=](int maxValue)
  {
    loadHandler->setMaxValue(maxValue);
  });

  connect(&UPDATER,&Updater::fileLoaded,[=]
  {
    loadHandler->incValue();
  });
}

