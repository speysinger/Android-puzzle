#include "dropgridmodel.h"

#include "src/testing/testmanager.h"

DropGridModel::DropGridModel(QObject* parent) : QAbstractListModel(parent) {
  m_dropItemsList.clear();
  m_fillingList.clear();

  connect(&TESTMANAGER, &TestManager::dropModelListReady,
          [=](std::vector<DropGridItem> dropItems) {
            m_fillingList = dropItems;
            fillDropGrid();
          });
  connect(&TESTMANAGER, &TestManager::questionsIsOver, [=] { clearGrid(); });
}

void DropGridModel::fillDropGrid() {
  clearGrid();
  insertRows(0, 4, QModelIndex());
}

void DropGridModel::clearGrid() {
  removeRows(0, m_dropItemsList.size(), QModelIndex());
}

void DropGridModel::setNextDropQuad() {
  TESTMANAGER.takeResultsFromDropModel(m_dropItemsList);
}

int DropGridModel::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent)
  return m_dropItemsList.size();
}

QHash<int, QByteArray> DropGridModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[itemType] = "itemType";
  roles[dropItemName] = "dropItemName";
  roles[dropItemImageSource] = "dropItemImageSource";
  roles[answerObjectName] = "answerObjectName";
  return roles;
}

QVariant DropGridModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid() ||
      (role != itemType && role != dropItemName && role != dropItemImageSource))
    return QVariant{};
  int rowIndex = index.row();
  DropGridItem dropItemAtIndex = m_dropItemsList[rowIndex];

  switch (role) {
    case itemType: {
      return QVariant::fromValue(dropItemAtIndex.itemType);
    }
    case dropItemName: {
      return QVariant::fromValue(dropItemAtIndex.dropItemName);
    }
    case answerObjectName: {
      return QVariant::fromValue(dropItemAtIndex.answerObjectName);
    }
    case dropItemImageSource: {
      return QVariant::fromValue(dropItemAtIndex.dropItemImageSource);
    }
    default: {
      return QVariant{};
    }
  }
}

bool DropGridModel::setData(const QModelIndex& index, const QVariant& value,
                            int role) {
  Q_UNUSED(value)

  if (index.isValid() && role == answerObjectName) {
    int rowIndex = index.row();
    m_dropItemsList[rowIndex].answerObjectName = value.toString();
    emit dataChanged(index, index, {answerObjectName});
    return true;
  }
  return false;
}

bool DropGridModel::insertRows(int row, int count, const QModelIndex& parent) {
  Q_UNUSED(row)
  Q_UNUSED(parent)

  if (count > 0) {
    beginInsertRows(QModelIndex(), 0, 3);
    if (m_fillingList.size() == 0) return false;

    for (auto dropItem : m_fillingList) m_dropItemsList.push_back(dropItem);

    m_fillingList.clear();
    endInsertRows();
  }
  return true;
}

bool DropGridModel::removeRows(int row, int count, const QModelIndex& parent) {
  Q_UNUSED(parent)
  if (count > 0) {
    beginRemoveRows(QModelIndex(), row, count - 1);
    m_dropItemsList.clear();
    endRemoveRows();
  }
  return true;
}
