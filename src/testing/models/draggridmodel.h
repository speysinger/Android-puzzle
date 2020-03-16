#ifndef DRAGGRIDMODEL_H
#define DRAGGRIDMODEL_H
#include <QAbstractListModel>
#include "database/levelstructures.h"

class DragGridModel: public QAbstractListModel
{
  Q_OBJECT
public:
  DragGridModel(QObject*parent=nullptr);
  enum listItemsType{
    itemType=Qt::UserRole+1,
    dragItemName,
    dragItemImageSource,
    answerIndex
  };

  void fillDragGrid();
  Q_INVOKABLE void clearGrid();

  int rowCount(const QModelIndex& parent=QModelIndex{}) const override;
  QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override;
  bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  QHash<int,QByteArray> roleNames() const override;

private:
  std::vector<DragGridItem> m_DragItemsList ;
  std::vector<DragGridItem> m_fillingList;

};

#endif // DRAGGRIDMODEL_H
