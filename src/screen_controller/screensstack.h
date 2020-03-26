#ifndef SCREENSSTACK_H
#define SCREENSSTACK_H

#include <QWidget>
#include <QGridLayout>
#include <QStack>
#include <memory>

//! стек окон приложения
class ScreensStack : public QWidget
{
  Q_OBJECT
public:
  explicit ScreensStack(QWidget* parent = nullptr);
public slots:
  void push(QWidget* widget);
  void pop();
  int lenght();

protected:
  bool check_empty();
signals:
  void back();

private:
  QStack<QWidget*> m_widgets;
  QGridLayout m_layout;
};

#endif  // SCREENSSTACK_H
