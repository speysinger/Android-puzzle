#ifndef PICKEDBUTTON_H
#define PICKEDBUTTON_H
#include <QPushButton>

//! кнопка-переключатель
//! находится в двух состояниях - выбрано-невыбрано
//! вырабатывает сигналы при переключении
class PickedButton : public QPushButton
{
  Q_OBJECT
  Q_PROPERTY(bool picked READ picked WRITE pick NOTIFY picked)
public:
  PickedButton(const QString& text, QWidget* parent = nullptr);
public slots:
  void pick(bool);
  bool picked();
protected slots:
  void invert();
protected:
  void resizeEvent(QResizeEvent *event) override;
signals:
  void picked(bool);

private:
  bool m_picked;
};

#endif  // PICKEDBUTTON_H
