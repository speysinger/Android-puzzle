#ifndef STATISTICMODEL_H
#define STATISTICMODEL_H

#include <QAbstractTableModel>
#include "database/levelstructures.h"
#include <vector>
#include <QObject>
#include <QHash>


class StatisticModel: public QAbstractTableModel
{
  Q_OBJECT
public:
  StatisticModel(QObject*parent=nullptr);

  enum listItemsType{
    EraName=Qt::UserRole+1,
    AssembledPuzzleArts,
    WorstTime,
    BestTime
  };

  Q_INVOKABLE void modeChanged(QString mode);
  Q_INVOKABLE int count();
  Q_INVOKABLE void loadData();
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  int rowCount(const QModelIndex& parent=QModelIndex{}) const override;
  QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override;
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  bool isPositionValid(int rowIndex) const;
  QHash<int,QByteArray> roleNames() const override;

private:
  void clearList();
  void fillItemsBuffer(QString mode);

  //было бы лучше использовать multimap. сначала вектор затестить
  std::vector<StatisticsTableItem> tableItems;
  std::vector<StatisticsTableItem> tableItemsBuffer;
  std::vector<StatisticsTableItem> allItems;

};

#endif // STATISTICMODEL_H
