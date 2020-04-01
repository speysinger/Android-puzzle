#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QByteArray>
#include <QJsonDocument>
#include <src/database/levelstructures.h>
#include <set>

///
/// \brief The JsonDocument class
/// Данный класс реализует парсер Json документа под структуры(Era, Art, Author)
class JsonParser
{
public:
  const std::set<Era>& getEras() const;
  const std::set<Art>& getArts() const;
  const std::set<Art> getArts(const Era& era) const;
  const std::set<Author>& getAuthors() const;

  void readJson(const QByteArray& jsonData);

private:
  void prepareErasArray();
  void prepareArtsArray();
  void prepareAuthorsArray();

  std::vector<Author> getArtAuthors(const QJsonArray& artAuthorsNames);

  QJsonDocument m_jsonDoc;

  std::set<Era> m_erasArray;
  std::set<Art> m_artsArray;
  std::set<Author> m_authorsArray;
};

#endif  // JSONPARSER_H
