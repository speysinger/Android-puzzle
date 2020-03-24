#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QByteArray>
#include <QJsonDocument>
#include <database/levelstructures.h>
#include <set>


///
/// \brief The JsonDocument class
/// Данный класс реализует парсер Json документа под структуры(Era, Art, Author)
class JsonParser:public QObject
{
  Q_OBJECT
public:
  JsonParser();

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

#endif // JSONPARSER_H
