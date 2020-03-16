#include "testingresultsmodel.h"
#include "testing/testmanager.h"


TestingResultsModel::TestingResultsModel(QObject *parent)
  :QAbstractListModel(parent)
{

  connect(&TESTMANAGER, &TestManager::testResultsReady, [=](std::vector<TestResultsItem> testResultsVec)
  {
    fillResults(testResultsVec);
  });
}

void TestingResultsModel::fillResults(std::vector<TestResultsItem> vec)
{
  removeRows(0,testingResults.size(), QModelIndex());
  testResultsBuffer=vec;
  insertRows(0,testResultsBuffer.size(), QModelIndex());
}


int TestingResultsModel::rowCount(const QModelIndex &parent) const
{
  return testingResults.size();
}

QHash<int, QByteArray> TestingResultsModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[Question] = "question";
  roles[UserAnswer] = "userAnswer";
  roles[CorrectAnswer] = "correctAnswer";
  return roles;
}

QVariant TestingResultsModel::data(const QModelIndex &index, int role) const
{
  if(!index.isValid() || (role!=Question && role!=UserAnswer && role!=CorrectAnswer))
    return QVariant {};
  int rowIndex=index.row();

  if(role == Question)
    return QVariant::fromValue(testingResults[rowIndex].question);

  if(role == UserAnswer)
    return QVariant::fromValue(testingResults[rowIndex].userAnswer);

  if(role == CorrectAnswer)
    return QVariant::fromValue(testingResults[rowIndex].correctAnswer);

  return QVariant {};
}

bool TestingResultsModel::insertRows(int column, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent)
  if(count>0){
    beginInsertRows(QModelIndex(), 0, count-1);
    testingResults = testResultsBuffer;
    endInsertRows();
  }
  return true;
}

bool TestingResultsModel::removeRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent)
  if(count>0)
  {
    beginRemoveRows(QModelIndex(), row, count-1);
    testingResults.clear();
    endRemoveRows();
  }
  return true;
}
