#include "statisticwidget.h"

#include <QtQuick>
#include <QQuickItem>
#include <QQuickView>

#include "statisticmodel.h"
#include "sortfilterproxymodel.h"


StatisticWidget::StatisticWidget(QWidget *parent):QQuickWidget(parent)
{
  qmlRegisterType<StatisticModel>("StatisticModel",1,0,"StatisticModel");
  qmlRegisterType<SortFilterProxyModel>("SortFilter", 1, 0, "SortFilterProxyModel");

  setStyleSheet("background-color: 'grey';");
  this->rootContext()->setContextProperty("buttonsHandler",buttonsHandler);
  this->setSource(QUrl(QStringLiteral("qrc:/qmlWindows/Statistic/StatisticWindow.qml")));
  this->setResizeMode(QQuickWidget::SizeRootObjectToView);
  this->setAttribute(Qt::WA_AlwaysStackOnTop);
  this->setClearColor(Qt::transparent);


  connect(buttonsHandler,&QmlButtonsHandler::back,[=] { emit back();});
}

void StatisticWidget::loadStatistic()
{

}

