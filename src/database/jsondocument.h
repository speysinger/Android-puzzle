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
#include "settings/update/pixmaploader.h"
#include <QDate>
#include <set>

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
  //<For update
  //std::vector<Author> getArtAuthors(const QString &authorName);
  std::vector<Author> getArtAuthors(const QJsonArray &artAuthorsNames);
  //maybe no need of this function
  Author &getAuthorByName(QString &authorName);
  //For update>

private:

  QJsonDocument jsonDoc;

  std::set<Era> m_erasArray;
  std::set<Art> m_artsArray;
  std::set<Author> m_authorsArray;

  std::multimap<Art,Author> m_artAuthors;

};

#endif // JSONDOCUMENT_H
