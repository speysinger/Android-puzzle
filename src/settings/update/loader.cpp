#include "loader.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QtNetwork>

QNetworkReply* Loader::load(QString url) {
  QEventLoop loop;
  QNetworkReply* loadedFile;
  connect(&m_manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
  loadedFile = m_manager.get(QNetworkRequest(QUrl(url)));
  loop.exec();

  if (loadedFile->error() != QNetworkReply::NoError) {
    loadedFile->abort();
    loadedFile->deleteLater();
    m_manager.clearAccessCache();
    throw NetworkReplyException("in DataLoader: " +
                                loadedFile->errorString().toStdString());
  }

  return loadedFile;
}

void Loader::loadPixmap(QString url, QString imagePath) {
  QNetworkReply* reply;
  try {
    reply = load(url);
  } catch (NetworkReplyException error) {
    throw std::runtime_error("Network error");
  }

  QPixmap pixmap;
  pixmap.loadFromData(reply->readAll());
  reply->deleteLater();
  pixmap.save(imagePath, "JPG");
}

void Loader::loadJSON(QString url) {
  QNetworkReply* reply;
  try {
    reply = load(url);
  } catch (NetworkReplyException error) {
    throw std::runtime_error("Network error");
  }
  QByteArray JSONdoc = reply->readAll();

  reply->deleteLater();
  emit loaded(JSONdoc);
}
