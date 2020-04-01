#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <random>
#include "src/database/levelstructures.h"
#include "src/singleton.h"

///
/// \brief The TestManager class
/// Данный класс реализует:
/// созданием вопросов для тестирования
/// отправкой их в модели GridView
/// обработкой результата теста
///
/// Предоставляет интерфейс, позволяющий:
/// составить список, доступных для тестирования, эпох и вопросов по ним
/// начинать тестирование по указанному списку эпох
/// получить результаты тестирования и обработать их
class TestManager : public QObject
{
  Q_OBJECT
public:
  void loadAvailableEras();

  void startTesting(std::vector<EraListModelItem>, int requiredCountOfQuestions);
  void takeResultsFromDropModel(std::vector<DropGridItem> results);
signals:
  void erasReady(std::vector<EraListModelItem> vec, bool isTestingModule);

  void notEnoughFilesToStartTesting();
  void possibleToStartTesting();

  void dragModelListReady(std::vector<DragGridItem>);
  void dropModelListReady(std::vector<DropGridItem>);

  void newQuestionsHaveEraType();
  void newQuestionsHaveAuthorType();

  void questionsIsOver();

  void testResultsReady(std::vector<TestResultsItem>& m_testResults);

private:
  struct QuestionWrapper;

  int convertButtonNumberToNumberQuestions(int buttonNumber);

  void getNumberOfEraQuestions(int& eraQuestions, int& artQuestions, std::vector<EraListModelItem>& selectedEras);

  void findCorrectAnswers(std::vector<DropGridItem>& results, int& quadResidue);
  void findWrongAnswers(std::vector<DropGridItem>& results, int& quadResidue);

  void sendQuadToDndModels();

  DragGridItem createDragItem(Art art);
  DropGridItem createDropItem(Era era);
  DropGridItem createDropItem(Author author);

  void increaseQuestionCounter(bool isEraQuestion, int& eraQuestionsCount, int& authorQuestionsCount);

  void pointToRightVector(std::vector<QuestionWrapper>::iterator& it);
  void deleteItemFromRightVector(std::vector<QuestionWrapper>::iterator& it);

  int getQuestionType();

  /// \brief
  ///  Обёртка над вопросом
  /// Содержит dragItem(вопрос), dropGridItem(ответ), принадлежность к типу вопроса
  struct QuestionWrapper
  {
    DragGridItem dragGridItem;
    DropGridItem dropGridItem;
    bool isEraQuestion;
    bool isDomestic;

    QuestionWrapper(DragGridItem dragGridItem_, DropGridItem dropGridItem_, bool isEraQuestion_, bool isDomestic_)
      : dragGridItem(dragGridItem_), dropGridItem(dropGridItem_), isEraQuestion(isEraQuestion_), isDomestic(isDomestic_)
    {
    }
  };

  /// \brief
  /// Обёртка над эпохой и вопросами по ней
  struct eraModuleQuestionsWrapper
  {
    Era era;
    std::vector<QuestionWrapper> questionsAndAnswers;

    eraModuleQuestionsWrapper(Era era_, std::vector<QuestionWrapper> questionsAndAnswers_)
      : era(era_), questionsAndAnswers(questionsAndAnswers_)
    {
    }

    bool operator==(const QString& findEraName) const
    {
      return era.name == findEraName;
    }
  };

  std::vector<eraModuleQuestionsWrapper> m_eraModule;

  std::vector<QuestionWrapper> m_eraForTestQuestions;
  std::vector<QuestionWrapper> m_authorForTestQuestions;

  std::vector<TestResultsItem> m_testResults;

  bool m_currentTypeOfQuestionIsEra = false;
  const int questionItems = 4;
};

#define TESTMANAGER Singleton<TestManager>::instance()

#endif  // TESTMANAGER_H
