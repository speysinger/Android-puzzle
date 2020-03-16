#include "statisticmodel.h"
#include "database/levelsdbfacade.h"
#include "database/levelstructures.h"

StatisticModel::StatisticModel(QObject *parent)
  :QAbstractTableModel(parent)
{
  loadData();
  tableItems.clear();

  fillItemsBuffer("3x3");
  insertRows(0, tableItemsBuffer.size(), QModelIndex());

}

void StatisticModel::modeChanged(QString mode)
{
  clearList();
  fillItemsBuffer(mode);
  insertRows(0, tableItemsBuffer.size(), QModelIndex());
}

int StatisticModel::count()
{
  return tableItems.size();
}

void StatisticModel::loadData()
{
  allItems = DB.getAllStatistic();
}

int StatisticModel::columnCount(const QModelIndex &parent) const
{
  return 4;
}

int StatisticModel::rowCount(const QModelIndex &parent) const
{
  return tableItems.size();
}

bool StatisticModel::isPositionValid(int rowIndex) const
{
  return rowIndex<tableItems.size();
}


void StatisticModel::clearList()
{
  removeRows(0,tableItems.size(),QModelIndex());
  tableItems.clear();
  tableItemsBuffer.clear();
}

void StatisticModel::fillItemsBuffer(QString mode)
{
  for(auto tableItem : allItems)
  {
    if(tableItem.mode == mode)
      tableItemsBuffer.push_back(tableItem);
  }
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
  if(role==EraName)
    return QVariant::fromValue(tableItems[rowIndex].eraName);
  if(role==AssembledPuzzleArts)
    return QVariant::fromValue(tableItems[rowIndex].assembledPuzzleArts);
  if(role == WorstTime)
    return QVariant::fromValue(tableItems[rowIndex].worstTime);
  if(role == BestTime)
    return QVariant::fromValue(tableItems[rowIndex].bestTime);
  if(!isPositionValid(rowIndex))
    return QVariant {};
}

bool StatisticModel::removeRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent)
  if(count>0)
  {
    beginRemoveRows(QModelIndex(), row, count);
    tableItems.erase(tableItems.begin(),tableItems.end());
    endRemoveRows();
  }
  return true;
}

bool StatisticModel::insertRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent)
  if(count > 0){
    beginInsertRows(QModelIndex(),0,count-1);
    tableItems=tableItemsBuffer;
    tableItemsBuffer.clear();
    endInsertRows();
  }
  return true;
}
