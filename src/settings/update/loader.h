#ifndef LOADER_H
#define LOADER_H

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QPixmap>

///
/// \brief The Loader class
/// Класс реализует загрузку Pixmap и Json файлов
class Loader : public QObject {
  Q_OBJECT
 public:
  struct NetworkReplyException : public std::invalid_argument {
    NetworkReplyException(std::string what) : std::invalid_argument(what) {}
  };
  void loadPixmap(QString url, QString imagePath);
  void loadJSON(QString url);

 private:
  QNetworkReply* load(QString url);
 signals:
  void loaded(const QByteArray& JSONdoc);

 private:
  QNetworkAccessManager m_manager;
};

#endif  // LOADER_H
