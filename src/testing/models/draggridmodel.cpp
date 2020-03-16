#include "draggridmodel.h"
#include "testing/testmanager.h"

DragGridModel::DragGridModel(QObject*parent)
  :QAbstractListModel(parent)
{
  m_DragItemsList.clear();
  m_fillingList.clear();

  connect(&TESTMANAGER,&TestManager::dragModelListReady,[=](std::vector<DragGridItem> dragItems){
    m_fillingList=dragItems;
    fillDragGrid();
  });
  connect(&TESTMANAGER, &TestManager::questionsIsOver, [=] {
    clearGrid();
  });
}

void DragGridModel::fillDragGrid()
{
  clearGrid();
  insertRows(0,4,QModelIndex());
}

void DragGridModel::clearGrid()
{
  removeRows(0,m_DragItemsList.size(),QModelIndex());
}


int DragGridModel::rowCount(const QModelIndex &parent) const
{
  return m_DragItemsList.size();
}

QHash<int, QByteArray> DragGridModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[itemType] = "itemType";
  roles[dragItemName] = "dragItemName";
  roles[dragItemImageSource] = "dragItemImageSource";
  roles[answerIndex] = "answerIndex";
  return roles;
}

QVariant DragGridModel::data(const QModelIndex &index, int role) const
{
  if(!index.isValid() || (role!=itemType && role!=dragItemName && role!=dragItemImageSource))
    return QVariant {};
  int rowIndex=index.row();
  if(role==itemType)
    return QVariant::fromValue(m_DragItemsList[rowIndex].itemType);

  if(role==dragItemName)
    return QVariant::fromValue(m_DragItemsList[rowIndex].dragItemName);

  if(role==dragItemImageSource)
    return QVariant::fromValue(m_DragItemsList[rowIndex].dragItemImageSource);

  return QVariant::fromValue(m_DragItemsList[rowIndex].answerIndex);
}

bool DragGridModel::insertRows(int column, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent)
  /// Сюда вызов функции, которая запишет во временный вектор нужные значения
  /// После чего в beginInsertRows нужно передать количество созданных элементов
  /// следом в вектор-модель записать значения временного вектора
  /// подать вызвать функцию endInsertRows
  if(count>0){
    //вставка 4 элементов с 0 по 3
    beginInsertRows(QModelIndex(),0,3);
    std::vector<DragGridItem>::iterator it=m_fillingList.begin();
    if(it==m_fillingList.end())
    {
      //TESTMANAGER
    }
    for(int i=0;i<4;i++)
    {
      m_DragItemsList.push_back(*it);
      it=m_fillingList.erase(it);
    }
    endInsertRows();
  }
  return true;
}

bool DragGridModel::removeRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent)
  if(count>0)
  {
    beginRemoveRows(QModelIndex(), row, count);
    m_DragItemsList.clear();
    endRemoveRows();
  }
}
