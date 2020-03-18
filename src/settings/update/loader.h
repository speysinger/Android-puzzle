#ifndef LOADER_H
#define LOADER_H

#include <QNetworkAccessManager>
#include <QPixmap>
#include <QEventLoop>

///
/// \brief The Loader class
/// Класс реализует загрузку Pixmap и Json файлов
class Loader : public QObject {
  Q_OBJECT
public:
  Loader();
  struct NetworkReplyException : public std::invalid_argument {
    NetworkReplyException(std::string what) : std::invalid_argument(what) {
    }
  };
public slots:
  QNetworkReply* load(QString url);
  void loadPixmap(QString url, QString imagePath);
  void loadJSON(QString url);
signals:
  void loaded(const QByteArray &JSONdoc);
private:
  QNetworkAccessManager m_manager;
};

#endif // LOADER_H
