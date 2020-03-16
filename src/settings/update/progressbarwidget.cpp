#include "progressBarWidget.h"
#include <QQuickView>
#include <QQuickWidget>
#include <QStackedLayout>
#include "updater.h"

ProgressBarWidget::ProgressBarWidget(QWidget *parent):QQuickWidget(parent)
{
  //QVBoxLayout *mainLayout = new QVBoxLayout;
  setStyleSheet("background-color: 'grey';");
  this->rootContext()->setContextProperty("progressInd",loadHandler);
  this->setSource(QUrl(QStringLiteral("qrc:/qmlWindows/UpdateWindow/ProgressBarWindow.qml")));
  this->setResizeMode(QQuickWidget::SizeRootObjectToView);
  this->setAttribute(Qt::WA_AlwaysStackOnTop);
  this->setClearColor(Qt::transparent);
  connect(loadHandler,&LoadHandler::back,[=] {emit backButtonPressed();});

  connect(&UPDATER,&Updater::maxValueCalculated,[=](int maxValue){
    loadHandler->setMaxValue(maxValue);
  });

  connect(&UPDATER,&Updater::fileLoaded,[=]{
    loadHandler->incValue();
  });

//  QQuickView *view = new QQuickView();
//  view->rootContext()->setContextProperty("progressInd",loadHandler);
//  view->setSource(QUrl(QStringLiteral("qrc:/qmlWindows/UpdateWindow/ProgressBarWindow.qml")));
//  view->setResizeMode(QQuickView::SizeRootObjectToView);
//  view->setColor("#FFFFE0");
//  QWidget *container=QWidget::createWindowContainer(view);

//  QLayout *layer = new QStackedLayout(this);
//  setLayout(layer);
//  layer->addWidget(container);

  //connect(loadHandler,&LoadHandler::back,[=] {emit backButtonPressed();});
  //connect(loadHandler,&LoadHandler::loaded,[=]{emit loadButtonPressed();});
}

