#include "loader.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtNetwork>
#include "database/levelsdbfacade.h"
#include "database/settingsdbfacade.h"

Loader::Loader() : QObject(){
}

QNetworkReply *Loader::load(QString url) {

  QEventLoop loop;
  QNetworkReply *loadedFile;
  connect(&m_manager,SIGNAL(finished(QNetworkReply*)),&loop,SLOT(quit()));
  loadedFile = m_manager.get(QNetworkRequest(QUrl(url)));
  loop.exec();

  if(loadedFile->error() != QNetworkReply::NoError) {
    throw NetworkReplyException("in DataLoader: " + loadedFile->errorString().toStdString());
  }

  return loadedFile;
}

void Loader::loadPixmap(QString url, QString imagePath)
{
  QNetworkReply *reply = load(url);
  QPixmap pixmap;
  pixmap.loadFromData(reply->readAll());
  pixmap.save(imagePath, "JPG");
  reply->deleteLater();
}

void Loader::loadJSON(QString url)
{
  QNetworkReply *reply = load(url);
  QByteArray JSONdoc = reply->readAll();

  emit loaded(JSONdoc);
  reply->deleteLater();
}
