#include "pixmaploader.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QDir>
#include <QNetworkReply>
#include "database/settingsdbfacade.h"
#include "database/levelsdbfacade.h"

PixmapLoader::PixmapLoader(QObject *parent) :
    QObject(parent) {
  connect(&m_manager, SIGNAL(finished(QNetworkReply*)), SLOT(on_load(QNetworkReply*)));
}

QString PixmapLoader::getPicPath()
{
  return picFilePath;
}

void PixmapLoader::load(QString imageUrl) {
  QEventLoop loop;
  connect(&m_manager,SIGNAL(finished(QNetworkReply*)),&loop,SLOT(quit()));
  m_manager.get(QNetworkRequest(QUrl(imageUrl)));
  m_pic_path = imageUrl.remove("https://pro-prof.com/artists-puzzle/load_1/");
  loop.exec();
}

void PixmapLoader::on_load(QNetworkReply *reply) {
  picFilePath="";
  if(reply->error() != QNetworkReply::NoError)
      throw NetworReplyException("in PixmapLoader: " + reply->errorString().toStdString());
  QPixmap pixmap;

  pixmap.loadFromData(reply->readAll());
  QString path_dir = DBSettings.getValue("path") + "/load_1/";
  QDir().mkdir(path_dir);

  QString path = DBSettings.getValue("path") + "/" + m_pic_path;

  QDir().mkdir(path.left(path.lastIndexOf(QChar('/'))));
  pixmap. save(path, "JPG");
  picFilePath=path;
  reply->deleteLater();
}
