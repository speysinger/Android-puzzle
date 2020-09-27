#ifndef VOLUMECONTROLLER_H
#define VOLUMECONTROLLER_H

#include <QWidget>
#include <vector>

#include "universalmodebutton.h"

struct Animal {
  std::string picture_path, sound_path;
  Animal(std::string _picture_path, std::string _sound_path)
      : picture_path(_picture_path), sound_path(_sound_path) {}
};

class AnimalButton : public UniversalModeButton {
  Q_OBJECT
 public:
  AnimalButton(const Animal &animal, QWidget *parent = nullptr);
  Animal selectedAnimal();

 private:
  Animal m_selectedAnimal;
};

class SoundController : public QWidget {
  Q_OBJECT
 public:
  explicit SoundController(std::vector<Animal> &&animals,
                           QWidget *parent = nullptr);
 private slots:
  void onPick();
 public slots:
  void play();

 protected:
  AnimalButton *m_pickedButton;
};

#endif  // VOLUMECONTROLLER_H
