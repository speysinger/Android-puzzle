#ifndef WIDGETOFTESTING_H
#define WIDGETOFTESTING_H

#include <QQmlContext>
#include "settings/update/qmlbuttonshandler.h"
#include "settings/update/qmlwidget.h"

class Titles: public QObject
{
  Q_OBJECT
public:
  bool IsEraQuestions=false;
  Q_INVOKABLE QString getEraTitle(){return eraTitle;}
  Q_INVOKABLE QString getArtTitle(){return artTitle;}
  Q_INVOKABLE QString getErasWord(){return eras;}
  Q_INVOKABLE QString getArtsWord(){return arts;}
  Q_INVOKABLE QString getAuthorsWord(){return authors;}
signals:
  void newQuestionsHaveEraType();
  void newQuestionsHaveAuthorType();
 private:
  QString eraTitle = "Соотнесите картины с эпохами";
  QString artTitle = "Соотнесите картины с авторами";
  QString eras = "Эпохи";
  QString arts = "Картины";
  QString authors = "Авторы";
};

class WidgetOfTesting: public QmlWidget
{
  Q_OBJECT
public:
  WidgetOfTesting(QWidget *parent=nullptr);
signals:
  void nextQuestionsButtonPressed();

private:
  Titles *testingTitles=new Titles();
};


#endif // WIDGETOFTESTING_H
