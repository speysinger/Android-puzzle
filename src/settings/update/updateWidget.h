#ifndef UPDATEWIDGET_H
#define UPDATEWIDGET_H

#include <QtWidgets>
#include <QQmlContext>
#include <QQuickView>
#include "qmlbuttonshandler.h"

class UpdateWidget : public QWidget
{
    Q_OBJECT
public:
    UpdateWidget(QWidget* parent = nullptr);
signals:
    void backButtonPressed();
    void loadButtonPressed();
private:
    QmlButtonsHandler *buttonsHandler=new QmlButtonsHandler();
};

#endif // UPDATEWIDGET_H
