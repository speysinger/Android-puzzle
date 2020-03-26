#include "media.h"
namespace media
{
void play(const std::string& path)
{
  Media.setMedia(QUrl(QString::fromStdString(path)));
  Media.play();
}

}  // namespace media
