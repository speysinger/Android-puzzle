#include "dropgridmodel.h"
#include "testing/testmanager.h"
#include <QDebug>

DropGridModel::DropGridModel(QObject*parent)
  :QAbstractListModel(parent)
{
  m_dropItemsList.clear();
  m_fillingList.clear();

  connect(&TESTMANAGER,&TestManager::dropModelListReady,[=](std::vector<DropGridItem> dropItems){
    m_fillingList = dropItems;
    fillDropGrid();
  });
  connect(&TESTMANAGER, &TestManager::questionsIsOver, [=] {
    clearGrid();
  });

}

void DropGridModel::fillDropGrid()
{
  clearGrid();
  insertRows(0,4,QModelIndex());
}

void DropGridModel::clearGrid()
{
  removeRows(0,m_dropItemsList.size(),QModelIndex());
}

void DropGridModel::setNextDropQuad()
{
  TESTMANAGER.takeResultsFromDropModel(m_dropItemsList);
}


int DropGridModel::rowCount(const QModelIndex &parent) const
{
  return m_dropItemsList.size();
}

QHash<int, QByteArray> DropGridModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[itemType] = "itemType";
  roles[dropItemName] = "dropItemName";
  roles[dropItemImageSource] = "dropItemImageSource";
  roles[answerObjectName] = "answerObjectName";
  return roles;
}

QVariant DropGridModel::data(const QModelIndex &index, int role) const
{
  if(!index.isValid() || (role!=itemType && role!=dropItemName && role!=dropItemImageSource))
    return QVariant {};
  int rowIndex=index.row();
  if(role==itemType)
    return QVariant::fromValue(m_dropItemsList[rowIndex].itemType);
  if(role==dropItemName)
    return QVariant::fromValue(m_dropItemsList[rowIndex].dropItemName);
  if(role==answerObjectName)
    return QVariant::fromValue(m_dropItemsList[rowIndex].answerObjectName);
  return QVariant::fromValue(m_dropItemsList[rowIndex].dropItemImageSource);
}

bool DropGridModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  Q_UNUSED(value)

  if (index.isValid() && role == answerObjectName) {
    int rowIndex=index.row();
    m_dropItemsList[rowIndex].answerObjectName = value.toString();
    emit dataChanged(index,index,{answerObjectName});
    return true;
  }
  return false;
}

bool DropGridModel::insertRows(int row, int count, const QModelIndex &parent)
{
  if(count>0){
    beginInsertRows(QModelIndex(),0,3);
    std::vector<DropGridItem>::iterator it=m_fillingList.begin();
    if(it == m_fillingList.end())
    {
      return false;
    }
    for(int i=0;i<4;i++)
    {
      m_dropItemsList.push_back(*it);
      it=m_fillingList.erase(it);
    }
    endInsertRows();
  }
  return true;
}

bool DropGridModel::removeRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent)
  if(count>0)
  {
    beginRemoveRows(QModelIndex(), row, count);
    m_dropItemsList.clear();
    endRemoveRows();
  }
  return true;
}


