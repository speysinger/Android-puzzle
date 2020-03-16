#ifndef MEDIA_H
#define MEDIA_H
#include "singleton.h"
#include <QMediaPlayer>

namespace media {
  #define Media Singleton<QMediaPlayer>::instance()

  void play(const std::string &path);
}

#endif // MEDIA_H
