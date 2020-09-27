#include "testingresultsmodel.h"

#include "src/testing/testmanager.h"

TestingResultsModel::TestingResultsModel(QObject* parent)
    : QAbstractListModel(parent) {
  connect(&TESTMANAGER, &TestManager::testResultsReady,
          [=](std::vector<TestResultsItem> testResultsVec) {
            fillResults(testResultsVec);
          });
}

void TestingResultsModel::fillResults(std::vector<TestResultsItem> vec) {
  removeRows(0, m_testingResults.size(), QModelIndex());
  m_testResultsBuffer = vec;
  insertRows(0, m_testResultsBuffer.size(), QModelIndex());
}

int TestingResultsModel::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent)
  return m_testingResults.size();
}

QHash<int, QByteArray> TestingResultsModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[question] = "question";
  roles[userAnswer] = "userAnswer";
  roles[correctAnswer] = "correctAnswer";
  return roles;
}

QVariant TestingResultsModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid() ||
      (role != question && role != userAnswer && role != correctAnswer))
    return QVariant{};
  int rowIndex = index.row();
  TestResultsItem testResultsItem = m_testingResults[rowIndex];

  switch (role) {
    case question: {
      return QVariant::fromValue(testResultsItem.question);
    }
    case userAnswer: {
      return QVariant::fromValue(testResultsItem.userAnswer);
    }
    case correctAnswer: {
      return QVariant::fromValue(testResultsItem.correctAnswer);
    }
    default: {
      return QVariant{};
    }
  }
}

bool TestingResultsModel::insertRows(int column, int count,
                                     const QModelIndex& parent) {
  Q_UNUSED(column)
  Q_UNUSED(parent)
  if (count > 0) {
    beginInsertRows(QModelIndex(), 0, count - 1);
    m_testingResults = m_testResultsBuffer;
    endInsertRows();
  }
  return true;
}

bool TestingResultsModel::removeRows(int row, int count,
                                     const QModelIndex& parent) {
  Q_UNUSED(parent)
  if (count > 0) {
    beginRemoveRows(QModelIndex(), row, count - 1);
    m_testingResults.clear();
    endRemoveRows();
  }
  return true;
}
