#ifndef QMLWIDGET_H
#define QMLWIDGET_H

#include <QQuickWidget>
#include <QQmlContext>
#include "qmlbuttonshandler.h"

class QmlWidget: public QQuickWidget
{
  Q_OBJECT
public:
  QmlWidget(QWidget *parent):QQuickWidget(parent)
  {
    setStyleSheet("background-color: 'gray';");
    this->rootContext()->setContextProperty("buttonsHandler",buttonsHandler);
    this->setResizeMode(QQuickWidget::SizeRootObjectToView);
    this->setAttribute(Qt::WA_AlwaysStackOnTop);
    this->setClearColor(Qt::transparent);
  }
protected:
  QmlButtonsHandler *buttonsHandler=new QmlButtonsHandler();
  QString pathToQmlFile;
};

#endif // QMLWIDGET_H
