#ifndef STATISTICMODEL_H
#define STATISTICMODEL_H

#include <QAbstractTableModel>
#include "database/levelstructures.h"
#include <vector>
#include <QObject>
#include <QHash>

///
/// \brief The StatisticModel class
/// Данный класс является моделью для qml StatisticTable
/// Реализует редактирование содержимого TableView
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

  std::vector<StatisticsTableItem> m_tableItems;
  std::vector<StatisticsTableItem> m_tableItemsBuffer;
  std::vector<StatisticsTableItem> m_allItems;
  const int m_columnCount = 4;

};

#endif // STATISTICMODEL_H
