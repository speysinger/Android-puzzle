#ifndef LEVELSDBFACADE_H
#define LEVELSDBFACADE_H

#include "dbfacade.h"
#include "src/singleton.h"
#include "levelstructures.h"
#include "settingsdbfacade.h"
#include "jsonparser.h"

#include <QSqlRelationalTableModel>
#include <vector>

class LevelsDBFacade : public DBFacade
{
  Q_OBJECT
public:
  LevelsDBFacade(QObject* parent = nullptr);

  void clearDatabase();

  Art randomArt();
  Art randomArt(Era& era);
  Art randomArt(Author& author);

  std::set<Author> getAllAuthors();
  std::vector<Author> getAuthorsOfArt(const QString& artName);

  std::vector<Author> authors();
  std::vector<Era> eras();
  std::set<Era> getEras();
  std::set<Art> getArts();

  std::vector<Art> arts();
  std::vector<Art> arts(Era& era);
  std::vector<Art> arts(Author& author);

  void fillArtsAuthors(std::vector<Art>& arts);
  void fillArtsAuthors(std::set<Art>& arts);

  void loadLevels(const QByteArray& jsonData);

  /// for update
  void update(const Era& era);
  /// for update
  void update(const Art& art);
  /// for update
  void update(const Author& author);

  void save(const Art& Art);
  void save(const Era& era);
  void save(const Author& author);
  void addArtAuthor(const QString authorName, const QString artName);

  void checkStatistic(StatisticRecord& statisticRecord);
  std::vector<StatisticsTableItem> getAllStatistic();

private:
  void addStatistic(const StatisticRecord& statisticRecord);
  void updateStatistic(const StatisticRecord& statisticRecord);

  void deleteFile(QString path);
  void clearTable(QString tableName);

protected:
  QSqlRelationalTableModel* m_arts_model;
  QSqlRelationalTableModel* m_eras_model;
  QSqlRelationalTableModel* m_authors_model;
  QSqlRelationalTableModel* m_artsAuthors_model;
  QSqlRelationalTableModel* m_statistic_model;

  friend class Singleton<LevelsDBFacade>;
};

#define DB Singleton<LevelsDBFacade>::instance()

#endif  // LEVELSDBFACADE_H
