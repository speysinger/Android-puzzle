#include "indexloader.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtNetwork>
#include "database/levelsdbfacade.h"
#include "database/settingsdbfacade.h"

IndexLoader::IndexLoader(QObject *parent) :
  QObject(parent){
  connect(&m_manager, SIGNAL(finished(QNetworkReply*)),
          SLOT(on_loaded(QNetworkReply*)));
}

//singleton?



//передавать булевский параметр-костыль, enum
//Абстрактный метод лоадер и две реализации indexloader и pixmaploader
//Базовый класс лоадер с основными методами и переменными(protected) и виртуальным методом on_loaded
//

//в одной из реализаций

void IndexLoader::load(QString url) {
  m_manager.get(QNetworkRequest(QUrl(url)));
}

void IndexLoader::on_loaded(QNetworkReply *reply) {
  if(reply->error() != QNetworkReply::NoError) {
    throw NetworkReplyException("in DataLoader: " + reply->errorString().toStdString());
  }
  QByteArray JSONdoc = reply->readAll();
  emit loaded(JSONdoc);
  reply->deleteLater();
}





