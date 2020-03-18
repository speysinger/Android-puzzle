#ifndef QMLWIDGET_H
#define QMLWIDGET_H

#include <QQuickWidget>
#include <QQmlContext>
#include "qmlbuttonshandler.h"

///
/// \brief The QmlWidget class
/// Данный класс реализует создание qQuickWidget
class QmlWidget: public QQuickWidget
{
  Q_OBJECT
public:
  QmlWidget(QWidget *parent):QQuickWidget(parent)
  {
    setStyleSheet("background-color: 'gray';");
    this->rootContext()->setContextProperty("buttonsHandler",m_buttonsHandler);
    this->setResizeMode(QQuickWidget::SizeRootObjectToView);
    this->setAttribute(Qt::WA_AlwaysStackOnTop);
    this->setClearColor(Qt::transparent);
  }
protected:
  QmlButtonsHandler *m_buttonsHandler=new QmlButtonsHandler();
  QString m_pathToQmlFile;
};

#endif // QMLWIDGET_H
