#include "statisticmodel.h"
#include "database/levelsdbfacade.h"
#include "database/levelstructures.h"

StatisticModel::StatisticModel(QObject *parent)
  :QAbstractTableModel(parent)
{
  loadData();
}

void StatisticModel::modeChanged(QString mode)
{
  clearList();
  fillItemsBuffer(mode);
}

int StatisticModel::count()
{
  return m_tableItems.size();
}

void StatisticModel::loadData()
{
  clearList();
  m_allItems.clear();
  m_allItems = DB.getAllStatistic();
  fillItemsBuffer("3x3");
}

int StatisticModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return m_columnCount;
}

int StatisticModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return m_tableItems.size();
}

bool StatisticModel::isPositionValid(int rowIndex) const
{
  return rowIndex < m_tableItems.size();
}

void StatisticModel::clearList()
{
  removeRows(0,m_tableItems.size(), QModelIndex());
  m_tableItems.clear();
  m_tableItemsBuffer.clear();
}

void StatisticModel::fillItemsBuffer(QString mode)
{
  for(auto tableItem : m_allItems)
  {
    if(tableItem.mode == mode)
      m_tableItemsBuffer.push_back(tableItem);
  }
  insertRows(0, m_tableItemsBuffer.size(), QModelIndex());
}

QHash<int, QByteArray> StatisticModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[EraName] = "eraName";
  roles[AssembledPuzzleArts] = "assembledPuzzleArts";
  roles[WorstTime] = "worstTime";
  roles[BestTime] = "bestTime";
  return roles;
}

QVariant StatisticModel::data(const QModelIndex &index, int role) const
{
  if(!index.isValid() || (role!=EraName && role!=AssembledPuzzleArts && role!=WorstTime && role!=BestTime))
    return QVariant {};
  int rowIndex=index.row();
  StatisticsTableItem tableItem = m_tableItems[rowIndex];

  if(role == EraName)
    return QVariant::fromValue(tableItem.eraName);

  if(role == AssembledPuzzleArts)
    return QVariant::fromValue(tableItem.assembledPuzzleArts);

  if(role == WorstTime)
    return QVariant::fromValue(tableItem.worstTime);

  if(role == BestTime)
    return QVariant::fromValue(tableItem.bestTime);

  if(!isPositionValid(rowIndex))
    return QVariant {};
  return QVariant::fromValue(tableItem.eraName);
}

bool StatisticModel::removeRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent)
  if(count > 0)
  {
    beginRemoveRows(QModelIndex(), row, count-1);
    m_tableItems.erase(m_tableItems.begin(), m_tableItems.end());
    endRemoveRows();
  }
  return true;
}

bool StatisticModel::insertRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(row)
  Q_UNUSED(parent)

  if(count > 0){
    beginInsertRows(QModelIndex(),0,count-1);
    m_tableItems = m_tableItemsBuffer;
    m_tableItemsBuffer.clear();
    endInsertRows();
  }
  return true;
}
