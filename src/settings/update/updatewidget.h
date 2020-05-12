#ifndef UPDATEWIDGET_H
#define UPDATEWIDGET_H

#include <QQmlContext>

#include "qmlbuttonshandler.h"
#include "qmlwidget.h"

///
/// \brief The UpdateWidget class
/// Данный класс реализует создание qml окна обновления базы данных
class UpdateWidget : public QmlWidget {
  Q_OBJECT
 public:
  UpdateWidget(QWidget* parent = nullptr);
 signals:
  void backButtonPressed();
  void loadButtonPressed();
};

#endif  // UPDATEWIDGET_H
