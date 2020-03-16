#include "statisticmodel.h"
#include <QDebug>

StatisticModel::StatisticModel(QObject *parent)
  :QAbstractTableModel(parent)
{
  statisticsTableItem item("абстракционизм","4/85", "0:40", "12:32", "3x3");
  tableItems.push_back(item);
  statisticsTableItem item2("абстракционизм2","4/85", "0:40", "12:32", "5x5");
  tableItems.push_back(item2);
  statisticsTableItem item3("абстракционизм","4/85", "0:40", "12:32", "7x7");
  tableItems.push_back(item3);
  statisticsTableItem item4("абстракционизм3","4/85", "0:40", "12:32", "3x3");
  tableItems.push_back(item4);
  statisticsTableItem item5("абстракционизм","4/85", "0:40", "12:32", "5x5");
  tableItems.push_back(item5);
  statisticsTableItem item6("абстракционизм","4/85", "0:40", "12:32", "7x7");
  tableItems.push_back(item6);
  statisticsTableItem item7("абстракционизм4","4/85", "0:40", "12:32", "3x3");
  tableItems.push_back(item7);
  statisticsTableItem item8("абстракционизм","4/85", "0:40", "12:32", "5x5");
  tableItems.push_back(item8);
  statisticsTableItem item9("абстракционизм","4/85", "0:40", "12:32", "3x3");
  tableItems.push_back(item9);
  statisticsTableItem item10("абстракционизм","4/85", "0:40", "12:32", "9x9");
  tableItems.push_back(item10);
  statisticsTableItem item11("абстракционизм","4/85", "0:40", "12:32", "5x5");
  tableItems.push_back(item11);

  allItems=tableItems;

  tableItems.clear();

  for(int i=0; i<allItems.size(); i++)
  {
    if(allItems[i].mode=="3x3")
      tableItemsBuffer.push_back(allItems[i]);
  }
  insertRows(0,tableItemsBuffer.size(),QModelIndex());

}

void StatisticModel::modeChanged(QString mode)
{
  clearList();
  if(mode == "3x3")
  {
    for(int i=0; i<allItems.size(); i++)
    {
      if(allItems[i].mode=="3x3")
        tableItemsBuffer.push_back(allItems[i]);
    }
  }
  else if(mode == "5x5")
  {
    for(int i=0; i<allItems.size(); i++)
    {
      if(allItems[i].mode=="5x5")
        tableItemsBuffer.push_back(allItems[i]);
    }
  }
  else if(mode == "7x7")
  {
    for(int i=0; i<allItems.size(); i++)
    {
      if(allItems[i].mode=="7x7")
        tableItemsBuffer.push_back(allItems[i]);
    }
  }
  else
  {
    for(int i=0; i<allItems.size(); i++)
    {
      if(allItems[i].mode=="9x9")
        tableItemsBuffer.push_back(allItems[i]);
    }
  }
  insertRows(0,tableItemsBuffer.size(),QModelIndex());
}

int StatisticModel::count()
{
  qDebug()<<"TABLESIZE="+QString::number(tableItems.size());
  return tableItems.size();
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
  //m_fillingList.clear();
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
    return QVariant::fromValue(tableItems[rowIndex].assembledPuzzleArts);
  if(role == BestTime)
    return QVariant::fromValue(tableItems[rowIndex].assembledPuzzleArts);
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

bool StatisticModel::insertRows(int row, int count, const QModelIndex &parent2)
{
  Q_UNUSED(parent2)
  /// Сюда вызов функции, которая запишет во временный вектор нужные значения
  /// После чего в beginInsertRows нужно передать количество созданных элементов
  /// следом в вектор-модель записать значения временного вектора
  /// подать вызвать функцию endInsertRows
  if(count>0){
    beginInsertRows(QModelIndex(),0,count-1);
    tableItems=tableItemsBuffer;
    tableItemsBuffer.clear();
    endInsertRows();
  }
  return true;
}
