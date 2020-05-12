#include "jsonparser.h"

#include <QJsonArray>
#include <QJsonObject>
#include <set>
#include <vector>

const std::set<Era>& JsonParser::getEras() const
{
  return m_erasArray;
}

const std::set<Art>& JsonParser::getArts() const
{
  return m_artsArray;
}

const std::set<Art> JsonParser::getArts(const Era& era) const
{
  std::set<Art> arts;

  auto it = m_artsArray.begin();

  while (it != m_artsArray.end())
  {
    if (it->eraName == era.eraName)
      arts.insert(*it);
    ++it;
  }
  return arts;
}

const std::set<Author>& JsonParser::getAuthors() const
{
  return m_authorsArray;
}

void JsonParser::prepareErasArray()
{
  QJsonArray erasArray;
  erasArray = QJsonValue(m_jsonDoc.object().value("eras")).toArray();
  for (auto eraObj : erasArray)
  {
    Era era(eraObj.toObject().value("eraName").toString(), eraObj.toObject().value("eraImagePath").toString(),
            QDate::fromString(eraObj.toObject().value("lastUpdate").toString(), "yyyy-MM-dd"));
    m_erasArray.insert(era);
  }
}

void JsonParser::prepareArtsArray()
{
  QJsonArray artsArray;
  artsArray = QJsonValue(m_jsonDoc.object().value("arts")).toArray();

  for (auto artObj : artsArray)
  {
    QJsonArray m_artAuthorsNames = artObj.toObject().value("artAuthors").toArray();
    std::vector<Author> artAuthors = getArtAuthors(m_artAuthorsNames);

    Art art(artObj.toObject().value("artEra").toString(), artObj.toObject().value("artPath").toString(),
            artObj.toObject().value("artInfo").toString(), artObj.toObject().value("artName").toString(),
            artObj.toObject().value("isDomestic").toBool(),
            QDate::fromString(artObj.toObject().value("lastUpdate").toString(), "yyyy-MM-dd"), artAuthors);

    m_artsArray.insert(art);
  }
}

void JsonParser::prepareAuthorsArray()
{
  QJsonArray authorsArray;
  authorsArray = QJsonValue(m_jsonDoc.object().value("authors")).toArray();
  for (auto authorObj : authorsArray)
  {
    Author author(authorObj.toObject().value("authorName").toString(),
                  authorObj.toObject().value("authorImagePath").toString(),
                  authorObj.toObject().value("authorInfo").toString(),
                  QDate::fromString(authorObj.toObject().value("lastUpdate").toString(), "yyyy-MM-dd"));
    m_authorsArray.insert(author);
  }
}

void JsonParser::readJson(const QByteArray& jsonData)
{
  QJsonParseError docError;

  m_jsonDoc = QJsonDocument::fromJson(jsonData, &docError);
  if (docError.error != QJsonParseError::NoError)
  {
    throw docError.errorString();
  }

  prepareErasArray();
  prepareAuthorsArray();
  prepareArtsArray();
}

std::vector<Author> JsonParser::getArtAuthors(const QJsonArray& artAuthorsNames)
{
  std::vector<Author> authors;

  for (auto artAuthorsObj : artAuthorsNames)
  {
    std::set<Author>::iterator author = m_authorsArray.find(Author(artAuthorsObj.toString(), "", "", QDate()));

    if (author != m_authorsArray.end())
      authors.push_back(*author);
  }
  return authors;
}
