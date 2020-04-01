#ifndef WIDGETOFTESTING_H
#define WIDGETOFTESTING_H

#include <QQmlContext>
#include "src/settings/update/qmlbuttonshandler.h"
#include "src/settings/update/qmlwidget.h"

///
/// \brief The Titles class
/// Данный класс содержит текст на вставку в окно тестирования, в зависимости от типа вопроса
class Titles : public QObject
{
  Q_OBJECT
public:
  bool IsEraQuestions = false;
  Q_INVOKABLE QString getEraTitle()
  {
    return m_eraTitle;
  }
  Q_INVOKABLE QString getArtTitle()
  {
    return m_artTitle;
  }
  Q_INVOKABLE QString getErasWord()
  {
    return m_eras;
  }
  Q_INVOKABLE QString getArtsWord()
  {
    return m_arts;
  }
  Q_INVOKABLE QString getAuthorsWord()
  {
    return m_authors;
  }
signals:
  void newQuestionsHaveEraType();
  void newQuestionsHaveAuthorType();

private:
  const QString m_eraTitle = "Соотнесите картины с эпохами";
  const QString m_artTitle = "Соотнесите картины с авторами";
  const QString m_eras = "Эпохи";
  const QString m_arts = "Картины";
  const QString m_authors = "Авторы";
};

///
/// \brief The WidgetOfTesting class
/// Данный класс реализует создание окна тестирования
class WidgetOfTesting : public QmlWidget
{
  Q_OBJECT
public:
  WidgetOfTesting(QWidget* parent = nullptr);
signals:
  void nextQuestionsButtonPressed();

private:
  Titles* m_testingTitles = new Titles();
};

#endif  // WIDGETOFTESTING_H
