#ifndef INDEXLOADER_H
#define INDEXLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include "singleton.h"

class IndexLoader : public QObject {
  Q_OBJECT
public:
  IndexLoader(QObject *parent = nullptr);
  struct NetworkReplyException : public std::invalid_argument {
    NetworkReplyException(std::string what) : std::invalid_argument(what) {
    }
  };
signals:
  void loaded(const QByteArray &JSONdoc);
public slots:
  void load(QString url);
private slots:
  void on_loaded(QNetworkReply* reply);
private:
  QNetworkAccessManager m_manager;
};

#define LOADER Singleton<IndexLoader>::instance()

#endif // INDEXLOADER_H
