#ifndef LEVELICON_H
#define LEVELICON_H

#include <QLabel>
#include <QGraphicsPixmapItem>
#include "database/levelstructures.h"

class ILevelIcon : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
public:
  explicit ILevelIcon(QGraphicsItem *parent = nullptr);
  virtual void setLabelSize(const int w, const int h) = 0;
  virtual void disableItem(const int w, const int h) = 0;
  virtual ~ILevelIcon() = default;
};

class LevelGraphicsIcon : public ILevelIcon {
  Q_OBJECT
public:
  explicit LevelGraphicsIcon(QGraphicsItem *parent = nullptr);
  virtual void setLabelSize(const int w, const int h);
  virtual void disableItem(const int w, const int h);
protected:
  virtual QPixmap iconImage() = 0;
};

class AuthorIcon : public LevelGraphicsIcon {
  Q_OBJECT
public:
  explicit AuthorIcon(Author&& author_, QGraphicsItem *parent = nullptr);
  Author getAuthor();
protected:
  virtual QPixmap iconImage();

  Author author;
};

class EraIcon : public LevelGraphicsIcon {
  Q_OBJECT
public:
  explicit EraIcon(Era&& era_, QGraphicsItem *parent = nullptr);
  Era getEra();
protected:
  virtual QPixmap iconImage();

  Era era;
};

class ArtIcon : public LevelGraphicsIcon {
  Q_OBJECT
public:
  explicit ArtIcon(Art&& art_, QGraphicsItem *parent = nullptr);
  Art getArt();
protected:
  virtual QPixmap iconImage();

  Art  art;
};

#endif // LEVELICON_H
