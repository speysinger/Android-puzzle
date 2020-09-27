#ifndef LEVELICON_H
#define LEVELICON_H

#include <QGraphicsPixmapItem>

#include "src/database/levelstructures.h"

class LevelGraphicsIcon : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
 public:
  explicit LevelGraphicsIcon(QGraphicsItem* parent = nullptr);
  void setLabelSize(const int w, const int h);
  void disableItem(const int w, const int h);
  virtual ~LevelGraphicsIcon() = default;

 protected:
  virtual QPixmap iconImage() = 0;
};

class AuthorIcon : public LevelGraphicsIcon {
  Q_OBJECT
 public:
  explicit AuthorIcon(Author&& author_, QGraphicsItem* parent = nullptr);
  Author getAuthor();

 protected:
  virtual QPixmap iconImage();

  Author author;
};

class EraIcon : public LevelGraphicsIcon {
  Q_OBJECT
 public:
  explicit EraIcon(Era&& era_, QGraphicsItem* parent = nullptr);
  Era getEra();

 protected:
  virtual QPixmap iconImage();

  Era era;
};

class ArtIcon : public LevelGraphicsIcon {
  Q_OBJECT
 public:
  explicit ArtIcon(Art&& art_, QGraphicsItem* parent = nullptr);
  Art getArt();

 protected:
  virtual QPixmap iconImage();

  Art art;
};

#endif  // LEVELICON_H
