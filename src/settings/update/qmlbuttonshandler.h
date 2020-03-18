#ifndef QMLBUTTONSHANDLER_H
#define QMLBUTTONSHANDLER_H
#include <QObject>
///
/// \brief The QmlButtonsHandler class
/// Данный класс является обработчиком кнопок(OK/CANCEL) qml
class QmlButtonsHandler: public QObject
{
  Q_OBJECT
public:
  //Функции, вызываемые из QML
  Q_INVOKABLE void backButtonPressed()
  {
    emit back();
  }
  Q_INVOKABLE void loadButtonPressed()
  {
    emit load();
  }
signals:
  void load();
  void back();
  void selectedLevel(int buttonNumber);
};


#endif // QMLBUTTONSHANDLER_H
