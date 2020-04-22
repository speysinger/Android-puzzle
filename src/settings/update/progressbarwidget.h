#ifndef PROGRESSBARWIDGET_H
#define PROGRESSBARWIDGET_H

#include <QQmlContext>
#include "qmlwidget.h"
#include <cmath>

///
/// \brief The LoadHandler class
/// Данный класс реализует взаимодействие с прогресс баром QML
/// Класс устанавливает пиковое значение, изменяет прогресс загрузки и уведомляет об этом
class LoadHandler : public QObject
{
  Q_OBJECT
  Q_PROPERTY(float progress READ progress NOTIFY progressChanged)
public:
  void setMaxValue(int value)
  {
    m_numberOfUpdatedItems = value;
  }
  void incValue()
  {
    if(m_numberOfUpdatedItems!=0)
    {
    m_currentProgress++;;
    emit progressChanged(ceil((float(m_currentProgress) / float(m_numberOfUpdatedItems)) * 100));

    if (m_currentProgress == m_numberOfUpdatedItems)
    {
      resetValues();
    }
    }
  }

  float progress()
  {
    return m_currentProgress;
  }

  Q_INVOKABLE void stopLoad()
  {
    resetValues();
    emit back();
  }
  void resetValues()
  {
      m_currentProgress = 0;
      m_numberOfUpdatedItems = 0;
      emit progressChanged(0);
  }

signals:
  void progressChanged(float progress);
  void back();
  void loaded();

private:

  int m_currentProgress = 0;
  int m_numberOfUpdatedItems = 0;
};

///
/// \brief The ProgressBarWidget class
/// Данный класс реализует создание qml окна progressBar
class ProgressBarWidget : public QmlWidget
{
  Q_OBJECT
public:
  ProgressBarWidget(QWidget* parent = nullptr);
signals:
  void backButtonPressed();

private:
  LoadHandler* m_loadHandler = new LoadHandler();
};

#define PROGRESSBAR Singleton<LoadHandler>::instance()
#endif  // PROGRESSBARWIDGET_H
