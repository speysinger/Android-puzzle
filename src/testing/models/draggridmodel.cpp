#include "draggridmodel.h"
#include "src/testing/testmanager.h"

DragGridModel::DragGridModel(QObject* parent) : QAbstractListModel(parent)
{
  m_dragItemsList.clear();
  m_fillingList.clear();

  connect(&TESTMANAGER, &TestManager::dragModelListReady, [=](std::vector<DragGridItem> dragItems) {
    m_fillingList = dragItems;
    fillDragGrid();
  });

  connect(&TESTMANAGER, &TestManager::questionsIsOver, [=] { clearGrid(); });
}

void DragGridModel::fillDragGrid()
{
  clearGrid();
  insertRows(0, 4, QModelIndex());
}

void DragGridModel::clearGrid()
{
  removeRows(0, m_dragItemsList.size(), QModelIndex());
}

int DragGridModel::rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent)
  return m_dragItemsList.size();
}

QHash<int, QByteArray> DragGridModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[itemType] = "itemType";
  roles[dragItemName] = "dragItemName";
  roles[dragItemImageSource] = "dragItemImageSource";
  return roles;
}

QVariant DragGridModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid() || (role != itemType && role != dragItemName && role != dragItemImageSource))
    return QVariant{};
  int rowIndex = index.row();
  DragGridItem dragItemAtIndex = m_dragItemsList[rowIndex];

  switch (role)
  {
    case itemType: {
      return QVariant::fromValue(dragItemAtIndex.itemType);
    }
    case dragItemName: {
      return QVariant::fromValue(dragItemAtIndex.dragItemName);
    }
    case dragItemImageSource: {
      return QVariant::fromValue(dragItemAtIndex.dragItemImageSource);
    }
    default: {
      return QVariant{};
    }
  }
}

bool DragGridModel::insertRows(int column, int count, const QModelIndex& parent)
{
  Q_UNUSED(parent)
  Q_UNUSED(column)

  if (count > 0)
  {
    beginInsertRows(QModelIndex(), 0, 3);

    if (m_fillingList.size() == 0)
      return false;

    for (auto dragItem : m_fillingList)
      m_dragItemsList.push_back(dragItem);

    m_fillingList.clear();
    endInsertRows();
  }
  return true;
}

bool DragGridModel::removeRows(int row, int count, const QModelIndex& parent)
{
  Q_UNUSED(parent)
  if (count > 0)
  {
    beginRemoveRows(QModelIndex(), row, count - 1);
    m_dragItemsList.clear();
    endRemoveRows();
  }
  return true;
}
