#ifndef LEVELSDBFACADE_H
# define LEVELSDBFACADE_H

#include "dbfacade.h"
#include <QSqlRelationalTableModel>
#include <map>
#include "singleton.h"
#include "levelstructures.h"
#include "settingsdbfacade.h"
#include "jsondocument.h"
#include <vector>

class LevelsDBFacade : public DBFacade {
  Q_OBJECT
public:
  LevelsDBFacade(QObject *parent = nullptr);

  Art randomArt();
  Art randomArt(Era& era);
  Art randomArt(Author& author);

  std::set<Author> getAllAuthors();
  std::vector<Author> authorsByNameArt(const QString& artName);
  std::set<Author> getAuthorsByNameArt(const QString& artName);
  std::vector<Author> getAuthorsOfArt(const QString& artName);

  std::vector<Author> authors();
  std::vector<Era> eras();
  std::set<Era> getEras();
  std::set<Art> getArts();


  std::vector<Art> arts();
  std::vector<Art> arts(Era& era);
  std::set<Art> getArts(const Era& era);
  std::vector<Art> arts(Author& author);

  void fillArtsAuthors(std::vector<Art> &arts);
  void fillArtsAuthors(std::set<Art> &arts);

  void loadLevels(const QByteArray &jsonData);

  ///for update
  void updateEra(const Era &era);
  ///for update
  void updateArt(Art &art);
  ///for update
  void updateAuthor(Author &author);

  void addArt(const Art& Art);
  void addEra(const Era& era);
  void addAuthor(const Author& author);
  void addArtAuthor(const QString authorName, const QString artName);


  void checkStatistic(StatisticRecord &statisticRecord);

  void addStatistic(const StatisticRecord &statisticRecord);
  void updateStatistic(const StatisticRecord &statisticRecord);

  StatisticRecord getStatisticRecord(const QString artName, const QString mode);

protected:
  QSqlRelationalTableModel *m_arts_model;
  QSqlRelationalTableModel *m_eras_model;
  QSqlRelationalTableModel *m_authors_model;
  QSqlRelationalTableModel *m_artsAuthors_model;
  QSqlRelationalTableModel *m_statistic_model;

  friend class Singleton<LevelsDBFacade>;
};

#define DB Singleton<LevelsDBFacade>::instance()

#endif // LEVELSDBFACADE_H
