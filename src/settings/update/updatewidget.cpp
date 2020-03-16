#include "updateWidget.h"
#include <QQuickView>



UpdateWidget::UpdateWidget(QWidget *parent):QWidget(parent) {

  //  setStyleSheet("background-color: 'grey';");
  //  this->setSource(QUrl(QStringLiteral("qrc:/qmlWindows/UpdateWindow/UpdateWindow.qml")));
  //  this->setResizeMode(QQuickWidget::SizeRootObjectToView);
  //  this->setAttribute(Qt::WA_AlwaysStackOnTop);
  //  this->setClearColor(Qt::transparent);
  //  this->rootContext()->setContextProperty("buttonsHandler",buttonsHandler);
  //  connect(buttonsHandler,&ControlButtons::back,[=] {emit backButtonPressed();});
  //  connect(buttonsHandler,&ControlButtons::load,[=]{emit loadButtonPressed();});

  //оставить QQuickWidget
  QQuickView *view = new QQuickView();
  view->rootContext()->setContextProperty("buttonsHandler",buttonsHandler);
  view->setSource(QUrl(QStringLiteral("qrc:/qmlWindows/UpdateWindow/UpdateWindow.qml")));
  view->setResizeMode(QQuickView::SizeRootObjectToView);
  view->setColor("#FFFFE0");
  QWidget *container=QWidget::createWindowContainer(view);

  //this->QWidget::createWindowContainer(view);
  //this->createWindowContainer(view,parent);
  //container->setAttribute(Qt::WA_AlwaysStackOnTop);

  //this->createWindowContainer(view,this)->setAttribute(Qt::WA_AlwaysStackOnTop);
  //container->setAttribute(Qt::WA_AlwaysStackOnTop);
  QLayout *layer = new QStackedLayout(this);
  setLayout(layer);
  layer->addWidget(container);

  connect(buttonsHandler,&QmlButtonsHandler::back,[=] {emit backButtonPressed();});
  connect(buttonsHandler,&QmlButtonsHandler::load,[=]{emit loadButtonPressed();});


}

///QQuickView *view = new QQuickView();
//view->setSource(QUrl(QStringLiteral("qrc:/qmlWindows/UpdateWindow/UpdateWindow.qml")));
//view->setResizeMode(QQuickView::SizeRootObjectToView);
////view->setColor("#FFFFE0");
//view->resize(100,100);
//view->rootContext()->setContextProperty("buttonsHandler",buttonsHandler);
//this->createWindowContainer(view);
////this(QWidget::createWindowContainer(view));
////container->setAttribute(Qt::WA_AlwaysStackOnTop);
//QLayout *layer = new QStackedLayout(this);
//setLayout(layer);
//layer->addWidget(this);
////widgetLayout->addWidget(container);
////setStyleSheet("background-color: 'grey';");
////this->setSource(QUrl(QStringLiteral("qrc:/qmlWindows/UpdateWindow/UpdateWindow.qml")));
////this->setResizeMode(QQuickWidget::SizeRootObjectToView);
////this->setAttribute(Qt::WA_AlwaysStackOnTop);
////this->setClearColor(Qt::transparent);
////this->rootContext()->setContextProperty("buttonsHandler",buttonsHandler);
//connect(buttonsHandler,&ControlButtons::back,[=] {emit backButtonPressed();});
//connect(buttonsHandler,&ControlButtons::load,[=]{emit loadButtonPressed();});
