#ifndef MEDIA_H
#define MEDIA_H
#include <QMediaPlayer>

#include "src/singleton.h"

namespace media {
#define Media Singleton<QMediaPlayer>::instance()

void play(const std::string &path);
}  // namespace media

#endif  // MEDIA_H
