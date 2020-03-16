#ifndef PROGRESSBARWIDGET_H
#define PROGRESSBARWIDGET_H

#include <QQmlContext>
#include "qmlwidget.h"


class LoadHandler:public QObject
{
  Q_OBJECT
  Q_PROPERTY(float progress READ progress NOTIFY progressChanged)
public:
  void setMaxValue(int value){
    numberOfUpdatedItems=value;
  }
  void incValue()
  {
    currentProgress++;
    emit progressChanged(ceil((float(currentProgress)/float(numberOfUpdatedItems))*100));

    if(currentProgress >= numberOfUpdatedItems)
    {
      stopLoad();
    }
  }

  float progress()
  {
    return currentProgress;
  }

  Q_INVOKABLE void stopLoad()
  {
    currentProgress=0;
    numberOfUpdatedItems=0;
    emit back();
  }
signals:
  void progressChanged(float progress);
  void back();
  void loaded();
private:
  int currentProgress=0;
  int numberOfUpdatedItems=0;

};

class ProgressBarWidget:public QmlWidget
{
  Q_OBJECT
public:
  ProgressBarWidget(QWidget *parent=nullptr);
  void startUp();
signals:
    void backButtonPressed();
private:
    LoadHandler *loadHandler = new LoadHandler();
};


#define PROGRESSBAR Singleton<LoadHandler>::instance()
#endif // PROGRESSBARWIDGET_H
