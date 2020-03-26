#include "soundcontroller.h"
#include "media.h"
#include <QGridLayout>

AnimalButton::AnimalButton(const Animal& animal, QWidget* parent)
  : UniversalModeButton(" ", parent), m_selectedAnimal(animal)
{
  QIcon icon(QString::fromStdString(animal.picture_path));
  setIcon(icon);
}

Animal AnimalButton::selectedAnimal()
{
  return m_selectedAnimal;
}

SoundController::SoundController(std::vector<Animal>&& animals, QWidget* parent) : QWidget(parent)
{
  QGridLayout* layout = new QGridLayout(this);
  setLayout(layout);

  // create buttons
  std::vector<AnimalButton*> buttons(animals.size());
  for (size_t i = 0; i < animals.size(); ++i)
  {
    buttons[i] = new AnimalButton(animals[i], this);
    buttons[i]->setMinimumSize(60, 60);
    buttons[i]->unpick();

    layout->addWidget(buttons[i], 0, i);
  }

  // connect buttons
  for (size_t i = 0; i < animals.size(); ++i)
  {
    for (size_t j = 0; j < buttons.size(); ++j)
    {
      if (i == j)
        continue;
      connect(buttons[i], SIGNAL(picked_true()), buttons[j], SLOT(unpick()));
    }
    connect(buttons[i], SIGNAL(picked_true()), this, SLOT(onPick()));
  }

  m_pickedButton = buttons[0];
  m_pickedButton->pick();
}

void SoundController::onPick()
{
  m_pickedButton = static_cast<AnimalButton*>(sender());
}

void SoundController::play()
{
  std::string path = m_pickedButton->selectedAnimal().sound_path;

  media::play(path);
}
