#include "loader.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtNetwork>

Loader::Loader() : QObject(){
}

QNetworkReply *Loader::load(QString url)
{
  QEventLoop loop;
  QNetworkReply *loadedFile;
  connect(&m_manager,SIGNAL(finished(QNetworkReply*)),&loop,SLOT(quit()));
  loadedFile = m_manager.get(QNetworkRequest(QUrl(url)));
  loop.exec();

  if(loadedFile->error() != QNetworkReply::NoError) {
    qDebug()<<"error";
    loadedFile->abort();
    loadedFile->deleteLater();
    m_manager.clearAccessCache();
    throw NetworkReplyException("in DataLoader: " + loadedFile->errorString().toStdString());
  }

  return loadedFile;
}

void Loader::loadPixmap(QString url, QString imagePath)
{
  QNetworkReply *reply;
  try {
    reply = load(url);
  } catch(NetworkReplyException error) {
    throw std::runtime_error("Network error");
  }

  QPixmap pixmap;
  pixmap.loadFromData(reply->readAll());
  pixmap.save(imagePath, "JPG");
  reply->deleteLater();
}

void Loader::loadJSON(QString url)
{
  qDebug()<<"STart json load";
  QNetworkReply *reply;
  try {
    reply = load(url);
  } catch(NetworkReplyException error) {
    throw std::runtime_error("Network error");
  }
  QByteArray JSONdoc = reply->readAll();

  emit loaded(JSONdoc);
  reply->deleteLater();
  qDebug()<<"EndJSONLOAD";
}
