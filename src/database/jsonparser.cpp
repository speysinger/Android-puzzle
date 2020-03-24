#include "jsonparser.h"

#include <QJsonObject>
#include <QJsonArray>
#include <vector>
#include <set>

JsonParser::JsonParser()
{
}

std::set<Era> &JsonParser::getEras()
{
  return m_erasArray;
}

std::set<Art> JsonParser::getArts()
{
 return m_artsArray;
}

std::set<Art> JsonParser::getArts(const Era &era)
{
  //Art tmp(era.name, "", "", "",false, QDate(),std::vector<A);

  std::set<Art> arts;

  auto it=m_artsArray.begin();
  //auto it = m_artAuthors.find(tmp);
  //auto it2=m_artAuthors.equal_range(tmp);

  while(it!=m_artsArray.end())
  {
    if(it->eraName == era.name)
    arts.insert(*it);
    ++it;
  }
  ///Можно equal_range, но медленее
  /// Сперва проверка на конец списка, потом на совпадение, иначе исключение
  /*while (it!=m_artAuthors.end() && it->first.eraName == era.name) {
    arts.insert(it->first);
    ++it;
  }*/

  return arts;
}

std::set<Author> JsonParser::getAuthors()
{
  return m_authorsArray;
}

void JsonParser::prepareErasArray()
{
  QJsonArray erasArray;
  erasArray=QJsonValue(m_jsonDoc.object().value("eras")).toArray();
  for(int index=0;index<erasArray.size();index++)
  {
    Era era(erasArray.at(index).toObject().value("eraName").toString(),
            erasArray.at(index).toObject().value("eraImagePath").toString(),
            QDate::fromString(erasArray.at(index).toObject().value("lastUpdate").toString(), "yyyy-MM-dd"));
    m_erasArray.insert(era);
  }
}

void JsonParser::prepareArtsArray()
{
  QJsonArray artsArray;
  artsArray=QJsonValue(m_jsonDoc.object().value("arts")).toArray();
  for(int index=0;index<artsArray.size();index++)
  {
    QJsonArray m_artAuthorsNames = artsArray.at(index).toObject().value("artAuthors").toArray();
    std::vector<Author> artAuthors = getArtAuthors(m_artAuthorsNames);

    Art art(artsArray.at(index).toObject().value("artEra").toString(),
            artsArray.at(index).toObject().value("artPath").toString(),
            artsArray.at(index).toObject().value("artInfo").toString(),
            artsArray.at(index).toObject().value("artName").toString(),
            artsArray.at(index).toObject().value("isDomestic").toBool(),
            QDate::fromString(artsArray.at(index).toObject().value("lastUpdate").toString(), "yyyy-MM-dd"),
            artAuthors);
    m_artsArray.insert(art);
  }
}

void JsonParser::prepareAuthorsArray()
{
  QJsonArray authorsArray;
  authorsArray=QJsonValue(m_jsonDoc.object().value("authors")).toArray();
  for(int index=0;index<authorsArray.size();index++)
  {
      Author author(authorsArray.at(index).toObject().value("authorName").toString(),
                    authorsArray.at(index).toObject().value("authorImagePath").toString(),
                    authorsArray.at(index).toObject().value("authorInfo").toString(),
                    QDate::fromString(authorsArray.at(index).toObject().value("lastUpdate").toString(), "yyyy-MM-dd"));
      m_authorsArray.insert(author);
    }
}


void JsonParser::readJson(const QByteArray &jsonData)
{
  QJsonParseError docError;
  m_jsonDoc = QJsonDocument::fromJson(jsonData, &docError);
  if (docError.error != QJsonParseError::NoError) {
    throw docError.errorString();
  }
  //catch вызывающей стороной?

  prepareErasArray();
  prepareAuthorsArray();
  prepareArtsArray();
}

Author JsonParser::getAuthor(QString authorName)
{
  QJsonArray authorsArray;
  authorsArray=QJsonValue(m_jsonDoc.object().value("authors")).toArray();
  for(int index=0;index<authorsArray.size();index++)
  {
    if(authorsArray.at(index).toObject().value("authorName").toString() == authorName)
    {
      Author author(authorsArray.at(index).toObject().value("authorName").toString(),
                    authorsArray.at(index).toObject().value("authorImagePath").toString(),
                    authorsArray.at(index).toObject().value("authorInfo").toString(),
                    QDate::fromString(authorsArray.at(index).toObject().value("lastUpdate").toString(), "yyyy-MM-dd"));
      return author;
    }
  }
  return Author("", "", "",QDate());
}

std::vector<Author> JsonParser::getArtAuthors(const QJsonArray &artAuthorsNames)
{
  std::vector<Author> authors;

  for(int i=0;i<artAuthorsNames.size();i++)
  {
    std::set<Author>::iterator author = m_authorsArray.find(
          Author(artAuthorsNames[i].toString(),"","",QDate()));

    if(author != m_authorsArray.end())
      authors.push_back(*author);

  }
  return authors;
}

