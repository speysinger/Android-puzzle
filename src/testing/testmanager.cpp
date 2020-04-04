#include "testmanager.h"
#include "src/database/levelsdbfacade.h"
#include "src/database/levelstructures.h"
#include <time.h>
#include "src/game/random_points.h"

int TestManager::convertButtonNumberToNumberQuestions(int buttonNumber)
{
  int countOfQuestions = 0;

  if (buttonNumber == 0)
    countOfQuestions = 5;
  else if (buttonNumber == 1)
    countOfQuestions = 10;
  else
    countOfQuestions = 15;
  return countOfQuestions;
}

void TestManager::loadAvailableEras()
{
  m_eraModule.clear();
  m_testResults.clear();
  m_eraForTestQuestions.clear();
  m_authorForTestQuestions.clear();

  std::vector<EraListModelItem> availableForTestingEras;
  std::vector<Era> allEras;

  allEras = DB.eras();

  for (auto& era : allEras)
  {
    std::vector<Art> eraArts = DB.arts(era);
    if (eraArts.size() > 0)
    {
      bool hasDomesticArts = false;
      bool hasInternationalArts = false;

      std::vector<QuestionWrapper> questionsAndAnswers;

      for (auto& eraArt : eraArts)
      {
        DragGridItem dragItem = createDragItem(eraArt);
        DropGridItem eraDropItem = createDropItem(era);

        bool isDomestic = eraArt.domestic;
        questionsAndAnswers.push_back(QuestionWrapper(dragItem, eraDropItem, true, isDomestic));

        if (eraArt.domestic && !hasDomesticArts)
          hasDomesticArts = true;
        else if (!eraArt.domestic && !hasInternationalArts)
          hasInternationalArts = true;

        for (auto& artAuthor : eraArt.artAuthors)
        {
          DropGridItem authorDropItem = createDropItem(artAuthor);
          questionsAndAnswers.push_back(QuestionWrapper(dragItem, authorDropItem, false, isDomestic));
        }
      }
      //У эпохи, при их наличии, указывается любое ненулевое количество отечественных и заруб. файлов.
      int domesticFilesCount = 0, internationalFilesCount = 0;
      if (hasDomesticArts)
        domesticFilesCount = 2;
      if (hasInternationalArts)
        internationalFilesCount = 2;

      availableForTestingEras.push_back(EraListModelItem(era.name, domesticFilesCount, internationalFilesCount, false,
                                                         false, hasDomesticArts, hasInternationalArts));
      m_eraModule.push_back(eraModuleQuestionsWrapper(era, questionsAndAnswers));
    }
  }
  emit erasReady(availableForTestingEras, true);
}

/// \brief Подсчёт количества отечественных и зарубежных вопросов для выбранного количества эпох
void TestManager::getNumberOfEraQuestions(int& eraQuestions, int& authorQuestions,
                                          std::vector<EraListModelItem>& selectedEras)
{
  for (auto& selectedEra : selectedEras)
  {
    auto foundedEra = std::find(m_eraModule.begin(), m_eraModule.end(), selectedEra.eraName);
    for (auto& question : foundedEra->questionsAndAnswers)
    {
      if (selectedEra.domesticSelected && question.isDomestic)
        increaseQuestionCounter(question.isEraQuestion, eraQuestions, authorQuestions);
      if (selectedEra.internationalSelected && !question.isDomestic)
        increaseQuestionCounter(question.isEraQuestion, eraQuestions, authorQuestions);
    }
  }
  qDebug() << QString::number(eraQuestions) + " " + QString::number(authorQuestions);
}

/// \details Сперва проверяется количество доступных вопросов
/// Следом случайным образом выбирается эпоха
/// Из эпохи случайным образом выбирается вопрос и записывается  во временный вектор
/// Как только временный вектор достигает размера = количеству вопросов на одном экране, он записывается в итог. вектор
void TestManager::startTesting(std::vector<EraListModelItem> selectedEras, int buttonNumber)
{
  ///псевдо-генератор для std::shuffle
  std::random_device rd;
  std::mt19937 g(rd());

  int eraQuestions = 0, artQuestions = 0, countOfQuestions = 0;
  getNumberOfEraQuestions(eraQuestions, artQuestions, selectedEras);

  countOfQuestions = convertButtonNumberToNumberQuestions(buttonNumber);

  if ((eraQuestions / questionItems + artQuestions / questionItems) < countOfQuestions)
  {
    emit notEnoughFilesToStartTesting();
    return;
  }
  else
    emit possibleToStartTesting();

  ///Приведение счётчика вопросов к модулю размерностью в 4 вопроса
  countOfQuestions *= questionItems;

  std::vector<QuestionWrapper> eraQuestionsQuad_;
  std::vector<QuestionWrapper> authorQuestionsQuad_;

  while (countOfQuestions != 0)
  {
    size_t randomEra = getBetween(0, selectedEras.size() - 1);

    auto it = find(m_eraModule.begin(), m_eraModule.end(), selectedEras[randomEra].eraName);
    auto& eraQuestions = *it;

    int eraQuestionsSize = eraQuestions.questionsAndAnswers.size();

    if (eraQuestionsSize == 0)
    {
      m_eraModule.erase(it);
      selectedEras.erase(selectedEras.begin() + randomEra);
      continue;
    }

    size_t questionsRandomShift = getBetween(0, (eraQuestionsSize - 1));

    auto randomItemIterator = (it->questionsAndAnswers.begin() + questionsRandomShift);
    QuestionWrapper& randomItemForInsert = *randomItemIterator;

    if (randomItemForInsert.isEraQuestion)
      eraQuestionsQuad_.push_back(randomItemForInsert);
    else
      authorQuestionsQuad_.push_back(randomItemForInsert);

    it->questionsAndAnswers.erase(randomItemIterator);

    if (eraQuestionsQuad_.size() == questionItems)
    {
      m_eraForTestQuestions.insert(m_eraForTestQuestions.end(), eraQuestionsQuad_.begin(), eraQuestionsQuad_.end());
      eraQuestionsQuad_.clear();
      countOfQuestions -= questionItems;
    }

    if (authorQuestionsQuad_.size() == questionItems)
    {
      m_authorForTestQuestions.insert(m_authorForTestQuestions.end(), authorQuestionsQuad_.begin(),
                                      authorQuestionsQuad_.end());
      authorQuestionsQuad_.clear();
      countOfQuestions -= questionItems;
    }
  }
  sendQuadToDndModels();
}

void TestManager::takeResultsFromDropModel(std::vector<DropGridItem> results)
{
  std::vector<DropGridItem> locResults = results;
  int residueCount = questionItems;

  findCorrectAnswers(locResults, residueCount);
  findWrongAnswers(locResults, residueCount);

  sendQuadToDndModels();
}

/// \details Для каждого элемента из списка результатов проверяется тип вопроса(автор или эпоха)
/// Следом происходит его поиск в первых элементах общего списка вопросов, равных residueCount
/// При нахождении вопроса в общем списке, результаты заносятся в список и вопрос удаляется как из общего списка,
/// так и из списка результатов
void TestManager::findCorrectAnswers(std::vector<DropGridItem>& results, int& residueCount)
{
  std::vector<DropGridItem>::iterator dropIt = results.begin();
  for (int dropItemsIndex = 0; dropItemsIndex < residueCount; dropItemsIndex++, dropIt++)
  {
    std::vector<QuestionWrapper>::iterator questionsIt;

    pointToRightVector(questionsIt);

    for (int quadQuestionsIndex = 0; quadQuestionsIndex < residueCount; quadQuestionsIndex++, questionsIt++)
    {
      //если найдена пара вопрос+ответ как дал пользователь
      if ((dropIt->answerObjectName == questionsIt->dragGridItem.dragItemName) &&
          dropIt->dropItemName == questionsIt->dropGridItem.dropItemName)
      {
        m_testResults.push_back(TestResultsItem(questionsIt->dropGridItem.dropItemName, dropIt->answerObjectName,
                                                questionsIt->dragGridItem.dragItemName));
        dropIt = results.erase(dropIt--);
        residueCount--;
        deleteItemFromRightVector(questionsIt);
        break;
      }
    }
  }
}

/// \details Для каждого элемента из списка результатов проверяется тип вопроса(автор или эпоха)
/// Следом происходит его поиск в первых элементах общего списка вопросов, равных residueCount
/// При нахождении вопроса в общем списке, результаты заносятся в список и вопрос удаляется как из общего списка,
/// так и из списка результатов
void TestManager::findWrongAnswers(std::vector<DropGridItem>& results, int& residueCount)
{
  std::vector<DropGridItem>::iterator dropIt = results.begin();
  while (residueCount != 0)
  {
    std::vector<QuestionWrapper>::iterator questionsIt;
    pointToRightVector(questionsIt);

    for (int quadQuestionsIndex = 0; quadQuestionsIndex < residueCount; quadQuestionsIndex++, questionsIt++)
    {
      //если найден вопрос пользователя
      if (dropIt->dropItemName == questionsIt->dropGridItem.dropItemName)
      {
        m_testResults.push_back(TestResultsItem(questionsIt->dropGridItem.dropItemName, dropIt->answerObjectName,
                                                questionsIt->dragGridItem.dragItemName));
        dropIt = results.erase(dropIt);
        residueCount--;
        deleteItemFromRightVector(questionsIt);
        break;
      }
    }
  }
}

void TestManager::sendQuadToDndModels()
{
  int questionType;

  std::vector<DragGridItem> dragGridItems;
  std::vector<DropGridItem> dropGridItems;

  if (m_eraForTestQuestions.size() == 0 && m_authorForTestQuestions.size() == 0)
  {
    emit questionsIsOver();
    emit testResultsReady(m_testResults);
    return;
  }

  questionType = getQuestionType();

  for (size_t index = 0; index < questionItems; index++)
  {
    QuestionWrapper questionWrapper = questionType ? m_eraForTestQuestions[index] : m_authorForTestQuestions[index];
    m_currentTypeOfQuestionIsEra = questionType;

    dragGridItems.push_back(questionWrapper.dragGridItem);
    dropGridItems.push_back(questionWrapper.dropGridItem);
  }

  ///псевдо-генератор для std::shuffle
  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(dragGridItems.begin(), dragGridItems.end(), g);
  std::shuffle(dropGridItems.begin(), dropGridItems.end(), g);

  if (m_currentTypeOfQuestionIsEra)
    emit newQuestionsHaveEraType();
  else
    emit newQuestionsHaveAuthorType();

  dragModelListReady(dragGridItems);
  dropModelListReady(dropGridItems);
}

DragGridItem TestManager::createDragItem(Art art)
{
  DragGridItem dragItem("Picture", art.imgName, art.imgPath);
  return dragItem;
}

DropGridItem TestManager::createDropItem(Era era)
{
  DropGridItem dropItem("Picture", era.name, era.imgPath, "");
  return dropItem;
}

DropGridItem TestManager::createDropItem(Author author)
{
  DropGridItem dropItem("Picture", author.authorName, author.imgPath, "");
  return dropItem;
}

void TestManager::increaseQuestionCounter(bool isEraQuestion, int& eraQuestionsCount, int& authorQuestionsCount)
{
  if (isEraQuestion)
    eraQuestionsCount++;
  else
    authorQuestionsCount++;
}

void TestManager::pointToRightVector(std::vector<QuestionWrapper>::iterator& it)
{
  if (m_currentTypeOfQuestionIsEra)
    it = m_eraForTestQuestions.begin();
  else
    it = m_authorForTestQuestions.begin();
}

void TestManager::deleteItemFromRightVector(std::vector<QuestionWrapper>::iterator& it)
{
  if (m_currentTypeOfQuestionIsEra)
    m_eraForTestQuestions.erase(it);
  else
    m_authorForTestQuestions.erase(it);
}

int TestManager::getQuestionType()
{
  if (m_eraForTestQuestions.size() == 0)
    return 0;  //вопрос из authorQuadQuestions
  else if (m_authorForTestQuestions.size() == 0)
    return 1;  //вопрос из eraQuadQuestions
  else
    return getBetween(0, 1);  //рандом между 0 и 1
}
