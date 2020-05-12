#include "levelicon.h"

#include <QColor>
#include <QDebug>
#include <QtGlobal>

//------------- ILevelIcon:

ILevelIcon::ILevelIcon(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {}

//------------- LevelGraphicsIcon:

LevelGraphicsIcon::LevelGraphicsIcon(QGraphicsItem* parent)
    : ILevelIcon(parent) {}

void LevelGraphicsIcon::setLabelSize(const int w, const int h) {
  QPixmap image = iconImage();

  auto pixmapSize = image.size();

  auto minSize = qMin(pixmapSize.height(), pixmapSize.width());
  auto maxSize = qMax(pixmapSize.height(), pixmapSize.width());

  auto shift = (maxSize - minSize) / 2;

  QPixmap icon;
  if (pixmapSize.height() < pixmapSize.width()) {
    icon = image.copy(shift, 0, minSize + shift, minSize);
  } else {
    icon = image.copy(0, shift, minSize, minSize + shift);
  }

  setPixmap(icon.scaled(w, h));
}

void LevelGraphicsIcon::disableItem(const int w, const int h) {
  QPixmap icon(w, h);
  icon.fill(QColor("white"));
  setPixmap(icon);
}

//------------- AuthorIcon:

AuthorIcon::AuthorIcon(Author&& author_, QGraphicsItem* parent)
    : LevelGraphicsIcon(parent), author(author_) {}

QPixmap AuthorIcon::iconImage() { return QPixmap(author.imgPath); }

Author AuthorIcon::getAuthor() { return author; }

//------------- EraIcon:

EraIcon::EraIcon(Era&& era_, QGraphicsItem* parent)
    : LevelGraphicsIcon(parent), era(era_) {}

QPixmap EraIcon::iconImage() { return QPixmap(era.imgPath); }

Era EraIcon::getEra() { return era; }

//------------- ArtIcon:

ArtIcon::ArtIcon(Art&& art_, QGraphicsItem* parent)
    : LevelGraphicsIcon(parent), art(art_) {}

QPixmap ArtIcon::iconImage() { return QPixmap(art.imgPath); }

Art ArtIcon::getArt() { return art; }
