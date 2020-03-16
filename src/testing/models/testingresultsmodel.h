#ifndef TESTINGRESULTSMODEL_H
#define TESTINGRESULTSMODEL_H

#include <QAbstractListModel>
#include "database/levelstructures.h"

class TestingResultsModel: public QAbstractListModel
{
  Q_OBJECT
public:
  TestingResultsModel(QObject*parent = nullptr);
  void fillResults(std::vector<TestResultsItem> vec);

  enum listItemsType{
    Question=Qt::UserRole+1,
    UserAnswer,
    CorrectAnswer
  };

  int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  bool isPositionValid(int rowIndex) const;

  QHash<int,QByteArray> roleNames() const override;
  QString BoolToString(bool b) const;

private:
  std::vector<TestResultsItem> testingResults;
  std::vector<TestResultsItem> testResultsBuffer;

};

#endif // TESTINGRESULTSMODEL_H
