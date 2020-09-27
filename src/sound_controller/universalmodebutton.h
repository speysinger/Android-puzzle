#ifndef UNIVERSALMODEBUTTON_H
#define UNIVERSALMODEBUTTON_H

#include <QPushButton>

class UniversalModeButton : public QPushButton {
  Q_OBJECT
  Q_PROPERTY(bool picked READ picked)
 public:
  UniversalModeButton(const QString& text, QWidget* parent = nullptr);
 public slots:
  bool picked();
  void pick();
  void unpick();

 private:
  void pick(bool);
 signals:
  void picked_true();

 private:
  bool m_picked;
};

#endif  // UNIVERSALMODEBUTTON_H
