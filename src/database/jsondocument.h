#ifndef JSONDOCUMENT_H
#define JSONDOCUMENT_H

#include <QByteArray>
#include <QJsonDocument>
#include <QDate>
#include <QObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <database/levelstructures.h>
#include <QDate>
#include <set>


///
/// \brief The JsonDocument class
/// Данный класс реализует парсер Json документа под структуры(Era, Art, Author)
class JsonDocument:public QObject
{
  Q_OBJECT
public:
  JsonDocument();

  std::set<Era> &getEras();
  std::set<Art> getArts();
  std::set<Art> getArts(const Era &era);
  std::set<Author> getAuthors();

  void prepareErasArray();
  void prepareArtsArray();
  void prepareAuthorsArray();

  void readJson(const QByteArray &jsonData);


  Author getAuthor(QString authorName);
  std::vector<Author> getArtAuthors(const QJsonArray &artAuthorsNames);
  Author &getAuthorByName(QString &authorName);

private:

  QJsonDocument m_jsonDoc;

  std::set<Era> m_erasArray;
  std::set<Art> m_artsArray;
  std::set<Author> m_authorsArray;

  std::multimap<Art,Author> m_artAuthors;

};

#endif // JSONDOCUMENT_H
