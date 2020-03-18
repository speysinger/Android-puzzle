#ifndef DROPGRIDMODEL_H
#define DROPGRIDMODEL_H

#include <QAbstractListModel>
#include "database/levelstructures.h"

///
/// \brief The DropGridModel class
/// Данный класс является моделью для DropGridModel
/// Реализует редактирование содержимого DropGridModel
class DropGridModel:public QAbstractListModel
{
  Q_OBJECT
public:
  DropGridModel(QObject*parent=nullptr);
  enum listItemsType{
    itemType=Qt::UserRole+1,
    dropItemName,
    dropItemImageSource,
    answerObjectName
  };

  void fillDropGrid();
  void clearGrid();

  Q_INVOKABLE void setNextDropQuad();

  int rowCount(const QModelIndex& parent=QModelIndex{}) const override;
  QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  QHash<int,QByteArray> roleNames() const override;

private:
  std::vector<DropGridItem> m_dropItemsList ;
  std::vector<DropGridItem> m_fillingList;

};

#endif // DROPGRIDMODEL_H
