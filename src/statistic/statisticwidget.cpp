#include "statisticwidget.h"

#include <QQuickItem>

#include "statisticmodel.h"
#include "sortfilterproxymodel.h"

StatisticWidget::StatisticWidget(QWidget* parent) : QmlWidget(parent)
{
    qmlRegisterType<StatisticModel>("StatisticModel", 1, 0, "StatisticModel");
    qmlRegisterType<SortFilterProxyModel>("SortFilter", 1, 0, "SortFilterProxyModel");

  m_pathToQmlFile = "qrc:/qmlWindows/Statistic/StatisticWindow.qml";

  this->setSource(QUrl(m_pathToQmlFile));

  auto root = this->rootObject();

  connect(this, SIGNAL(loadData()), root, SIGNAL(loadData()));
  connect(m_buttonsHandler, &QmlButtonsHandler::back, [=] { emit back(); });
}

void StatisticWidget::loadStatistic()
{
  emit loadData();
}
