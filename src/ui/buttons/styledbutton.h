#ifndef STYLEDBUTTON_H
#define STYLEDBUTTON_H
#include <QPushButton>
#include <QWidget>

//! базовая кнопка с установленными стилями приложения
class StyledButton : public QPushButton {
  Q_OBJECT
 public:
  explicit StyledButton(const QString& text, QWidget* parent = nullptr);

 protected:
  void resizeEvent(QResizeEvent*) override;
};

#endif  // STYLEDBUTTON_H
