#include "puzzlegame.h"
#include "itemground.h"
#include "random_points.h"
#include "src/ui/buttons/styledbutton.h"
#include "src/game/puzzleitem/puzzlematrix.h"
#include "src/game/puzzleitem/settableitem.h"
#include <QGridLayout>
#include <QPushButton>
#include <QSpacerItem>

PuzzleGame::PuzzleGame(QWidget* parent)
  : QWidget(parent),
    m_scene(), m_view(&m_scene),
    m_selectionLayer(1),
    m_sound({
      Animal(":/icon/pets/cat.png", "qrc:/sounds/pets/cat.ogg"),
      Animal(":/icon/pets/dog.png", "qrc:/sounds/pets/dog.ogg"),
      Animal(":/icon/pets/fish.png", ""),
      Animal(":/icon/pets/hen.png", "qrc:/sounds/pets/hen.ogg"),
      Animal(":/icon/pets/mouse.png", "qrc:/sounds/pets/mouse.ogg")
    }, this) {


    QSizePolicy buttonSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    buttonSizePolicy.setVerticalStretch(1);

  StyledButton *rotate = new StyledButton("rotate", this);
  rotate->setSizePolicy(buttonSizePolicy);
  StyledButton *back = new StyledButton("back", this);
  back->setIcon(QIcon(":/icons/back.ico"));
  back->setSizePolicy(buttonSizePolicy);

  QGridLayout *grid = new QGridLayout(this);
  setLayout(grid);


  buttonSizePolicy.setVerticalStretch(9);
  m_view.setSizePolicy(buttonSizePolicy);

  grid->addWidget(&m_view,1,0,1,2);
  grid->addWidget(&m_label,2,0,1,2);
  grid->addWidget(&m_sound,3,0,1,2);

  grid->addWidget(rotate,4,0);
  grid->addWidget(back,4,1);

  connect(back, SIGNAL(clicked()), this, SIGNAL(back()));
  connect(rotate, SIGNAL(clicked()), this, SLOT(rotate90()));
}

void PuzzleGame::load(QPixmap source, Mode mode) {
  m_scene.clear();
  m_view.viewport()->update();

  auto background = new QGraphicsPixmapItem(source);

  m_scene.addItem(background);
  background->setPos(0,0);
  background->setOpacity(0.2);

  m_unsetted = mode.horizontally * mode.vertically;

  auto puzzlePathes = getPuzzlePathes(source, mode.horizontally, mode.vertically);

  const size_t
      ImageH = source.height(),
      ImageW = source.width(),
      h = ImageH / mode.horizontally,
      w = ImageW / mode.vertically;

  auto puzzleMatrix = createPuzzles(source, puzzlePathes);

  QPoint upperBound(-w, -h), lowerBound(ImageW + w, ImageH + h);

  for (size_t i = 0; i < puzzleMatrix.size(); ++i) {
    auto& row = puzzleMatrix[i];
    for (size_t j = 0; j < row.size(); ++j) {
      auto& puzzleItem = row[j];
      auto itemGround = new ItemGround(QRectF(j*w, i*h, w, h));

      puzzleItem->setRotatable(mode.rotated);

      m_scene.addItem(puzzleItem);
      m_scene.addItem(itemGround);

      itemGround->setZValue(GroundLayer);
      puzzleItem->setZValue(m_selectionLayer);

      puzzleItem->setPos(getBetween(upperBound, lowerBound));
      puzzleItem->set_randomRotate();

      connect(puzzleItem, SIGNAL(clicked()), SLOT(onItemClicked()));
      connect(puzzleItem, SIGNAL(setted()), SLOT(onItemSetted()));
      connect(&m_view, SIGNAL(change_scalefactor()),
              puzzleItem, SLOT(clear_selection()));
    }
  }

  m_view.fitInView(QRectF(-w, -h, 2*w+ImageW, 2*h+ImageH), Qt::KeepAspectRatio);
  m_view.centerOn(0,0);
  m_view.show();
  m_view.update();
}

void PuzzleGame::rotate90() {
  m_view.rotate(90);
}

void PuzzleGame::onItemClicked() {
  ++m_selectionLayer;

  static_cast<SettableItem*>(sender())->setZValue(m_selectionLayer);
}

void PuzzleGame::onItemSetted() {
  m_sound.play();
  --m_unsetted;
  if (0 == m_unsetted) {
    emit finished();
  }
}
