#include "statisticwidget.h"

#include <QQuickItem>

#include "statisticmodel.h"
#include "sortfilterproxymodel.h"

StatisticWidget::StatisticWidget(QWidget* parent) : QmlWidget(parent)
{
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
