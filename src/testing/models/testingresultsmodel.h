#ifndef TESTINGRESULTSMODEL_H
#define TESTINGRESULTSMODEL_H

#include <QAbstractListModel>

#include "src/database/levelstructures.h"

///
/// \brief The TestingResultsModel class
/// Данный класс является моделью для ListView, отображающего результаты
/// тестирования
class TestingResultsModel : public QAbstractListModel {
  Q_OBJECT
 public:
  TestingResultsModel(QObject* parent = nullptr);
  void fillResults(std::vector<TestResultsItem> vec);

  enum listItemsType { question = Qt::UserRole + 1, userAnswer, correctAnswer };

  int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  bool removeRows(int row, int count,
                  const QModelIndex& parent = QModelIndex()) override;
  bool insertRows(int row, int count,
                  const QModelIndex& parent = QModelIndex()) override;
  bool isPositionValid(int rowIndex) const;

  QHash<int, QByteArray> roleNames() const override;
  QString BoolToString(bool b) const;

 private:
  std::vector<TestResultsItem> m_testingResults;
  std::vector<TestResultsItem> m_testResultsBuffer;
};

#endif  // TESTINGRESULTSMODEL_H
