#ifndef SCREENSSTACK_H
#define SCREENSSTACK_H

#include <QWidget>
#include <QGridLayout>
#include <QStack>
#include <memory>

//! стек окон приложения
class ScreensStack : public QWidget {
  Q_OBJECT
public:
  explicit ScreensStack(QWidget *parent = nullptr);
public slots:
  void push(QWidget* widget);
  void pop();
  int lenght();
protected:
  bool check_empty();
  template<typename T, typename... Args>
  std::unique_ptr<T> make_unique(Args&&... args) {//added
      return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
signals:
  void back();
private:
  QStack<QWidget*> m_widgets;
  QGridLayout m_layout;
};

#endif // SCREENSSTACK_H
