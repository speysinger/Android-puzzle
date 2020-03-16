#ifndef STATISTICMODEL_H
#define STATISTICMODEL_H

#include <QAbstractTableModel>
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

  struct statisticsTableItem
  {
    QString eraName;
    QString assembledPuzzleArts;
    QString worstTime;
    QString bestTime;
    QString mode;

    statisticsTableItem(QString eraName_, QString assembledPuzzleArts_, QString worstTime_, QString bestTime_,
                        QString mode_):
      eraName(eraName_), assembledPuzzleArts(assembledPuzzleArts_), worstTime(worstTime_), bestTime(bestTime_),
    mode(mode_){}
  };


  Q_INVOKABLE void modeChanged(QString mode);
  Q_INVOKABLE int count();
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  int rowCount(const QModelIndex& parent=QModelIndex{}) const override;
  QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override;
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  bool isPositionValid(int rowIndex) const;
  QHash<int,QByteArray> roleNames() const override;

private:
  void clearList();

  //было бы лучше использовать multimap. сначала вектор затестить
  std::vector<statisticsTableItem> tableItems;
  std::vector<statisticsTableItem> tableItemsBuffer;
  std::vector<statisticsTableItem> allItems;

};

#endif // STATISTICMODEL_H
