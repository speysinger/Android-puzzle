#include "levelsdbfacade.h"
#include <QDate>
#include <QString>

LevelsDBFacade::LevelsDBFacade(QObject* parent) : DBFacade(parent)
{
  if (false == m_db.tables().contains("eras"))
  {
    exec("CREATE TABLE eras ("
         "id TEXT PRIMARY KEY, "
         "eraImagePath TEXT,"
         "lastUpdate DATE"
         ");");
  }

  if (false == m_db.tables().contains("authors"))
  {
    exec("CREATE TABLE authors ("
         "authorName TEXT PRIMARY KEY, "
         "authorImagePath TEXT,"
         "authorInfo TEXT,"
         "lastUpdate DATE"
         ");");
  }

  if (false == m_db.tables().contains("arts"))
  {
    exec("CREATE TABLE arts ("
         "era TEXT,"
         "path TEXT PRIMARY KEY,"
         "info TEXT,"
         "name TEXT,"
         "domestic INTEGER,"
         "lastUpdate DATE"
         ");");
  }
  if (false == m_db.tables().contains("artsAuthors"))
  {
    exec("CREATE TABLE artsAuthors ("
         "id INTEGER PRIMARY KEY AUTOINCREMENT,"
         "artName TEXT,"
         "artAuthor TEXT"
         ");");
  }

  if (false == m_db.tables().contains("statistic"))
  {
    exec("CREATE TABLE statistic ("
         "id INTEGER PRIMARY KEY AUTOINCREMENT,"
         "eraName TEXT,"
         "artName TEXT,"
         "worstTime TEXT,"
         "bestTime TEXT,"
         "mode TEXT"
         ");");
  }

  m_eras_model = new QSqlRelationalTableModel(this, m_db);
  m_eras_model->setTable("eras");
  m_eras_model->setEditStrategy(QSqlTableModel::OnFieldChange);

  m_authors_model = new QSqlRelationalTableModel(this, m_db);
  m_authors_model->setTable("authors");
  m_authors_model->setEditStrategy(QSqlTableModel::OnFieldChange);

  m_arts_model = new QSqlRelationalTableModel(this, m_db);
  m_arts_model->setTable("arts");
  m_arts_model->setRelation(0, QSqlRelation("eras", "id", "id"));
  m_arts_model->setRelation(3, QSqlRelation("authors", "authorName", "authorName"));
  m_arts_model->setEditStrategy(QSqlTableModel::OnFieldChange);

  m_artsAuthors_model = new QSqlRelationalTableModel(this, m_db);
  m_artsAuthors_model->setTable("artsAuthors");
  m_artsAuthors_model->setEditStrategy(QSqlTableModel::OnFieldChange);

  m_statistic_model = new QSqlRelationalTableModel(this, m_db);
  m_statistic_model->setTable("statistic");
  m_statistic_model->setEditStrategy(QSqlTableModel::OnFieldChange);
}

void LevelsDBFacade::clearDatabase()
{
  for (auto author : authors())
  {
    deleteFile(author.imgPath);
  }
  clearTable("authors");

  for (auto era : eras())
  {
    deleteFile(era.imgPath);
  }
  clearTable("eras");

  for (auto art : arts())
  {
    deleteFile(art.imgPath);
  }
  clearTable("arts");
  clearTable("artsAuthors");
  clearTable("statistic");
}

Art LevelsDBFacade::randomArt()
{
  exec(tr("SELECT era, path, info, name, domestic, lastUpdate FROM arts ORDER BY RANDOM() LIMIT 1;"));
  m_arts_model->select();
  m_query->first();

  QString era = m_query->value(0).toString(), path = m_query->value(1).toString(), info = m_query->value(2).toString(),
          name = m_query->value(3).toString();
  bool domestic = m_query->value(4).toBool();
  QDate lastUpdate = m_query->value(5).toDate();
  std::vector<Author> authors = getAuthorsOfArt(name);

  return Art(era, path, info, name, domestic, lastUpdate, authors);
}

Art LevelsDBFacade::randomArt(Era& era_)
{
  exec(tr("SELECT era, path, info, name, domestic, lastUpdate FROM arts WHERE era=") + qs(era_.name) +
       tr("ORDER BY RANDOM() LIMIT 1;"));
  m_arts_model->select();
  m_query->first();

  QString era = m_query->value(0).toString(), path = m_query->value(1).toString(), info = m_query->value(2).toString(),
          name = m_query->value(3).toString();
  bool domestic = m_query->value(4).toBool();
  QDate lastUpdate = m_query->value(5).toDate();
  std::vector<Author> authors = getAuthorsOfArt(name);

  return Art(era, path, info, name, domestic, lastUpdate, authors);
}

Art LevelsDBFacade::randomArt(Author& author_)
{
  exec(tr("SELECT era, path, info, name, domestic, lastUpdate FROM arts WHERE author=") + qs(author_.authorName) +
       tr("ORDER BY RANDOM() LIMIT 1;"));
  m_arts_model->select();
  m_query->first();

  QString era = m_query->value(0).toString(), path = m_query->value(1).toString(), info = m_query->value(2).toString(),
          name = m_query->value(3).toString();
  bool domestic = m_query->value(4).toBool();
  QDate lastUpdate = m_query->value(5).toDate();
  std::vector<Author> authors = getAuthorsOfArt(name);

  return Art(era, path, info, name, domestic, lastUpdate, authors);
}

std::set<Author> LevelsDBFacade::getAllAuthors()
{
  std::set<Author> authors;
  exec(tr("SELECT authorName, authorImagePath, authorInfo, lastUpdate from authors;"));
  m_authors_model->select();
  while (m_query->next())
  {
    authors.insert(Author(m_query->value(0).toString(), m_query->value(1).toString(), m_query->value(2).toString(),
                          m_query->value(3).toDate()));
  }

  return authors;
}

std::vector<Art> LevelsDBFacade::arts()
{
  std::vector<Art> arts;
  exec(tr("SELECT era, path, info, name, domestic, lastUpdate from arts;"));
  m_arts_model->select();
  m_query->first();

  while (m_query->next())
  {
    QString era = m_query->value(0).toString(), path = m_query->value(1).toString(),
            info = m_query->value(2).toString(), name = m_query->value(3).toString();
    bool domestic = m_query->value(4).toBool();
    QDate lastUpdate = m_query->value(5).toDate();

    arts.push_back(Art(era, path, info, name, domestic, lastUpdate, std::vector<Author>()));
  }
  fillArtsAuthors(arts);

  return arts;
}

std::vector<Art> LevelsDBFacade::arts(Era& era_)
{
  std::vector<Art> arts;

  exec(tr("SELECT era, path, info, name, domestic, lastUpdate FROM arts WHERE era=") + qs(era_.name) + tr(";"));
  m_arts_model->select();

  while (m_query->next())
  {
    QString era = m_query->value(0).toString(), path = m_query->value(1).toString(),
            info = m_query->value(2).toString(), name = m_query->value(3).toString();
    bool domestic = m_query->value(4).toBool();
    QDate lastUpdate = m_query->value(5).toDate();

    arts.push_back(Art(era, path, info, name, domestic, lastUpdate, std::vector<Author>()));
  }
  fillArtsAuthors(arts);

  return arts;
}

std::vector<Art> LevelsDBFacade::arts(Author& author_)
{
  std::vector<Art> arts;
  exec(tr("SELECT era, path, info, name, domestic, lastUpdate FROM arts JOIN artsAuthors ON artsAuthors.artName=name "
          "WHERE artsAuthors.artAuthor=") +
       qs(author_.authorName) + tr(";"));
  m_arts_model->select();

  while (m_query->next())
  {
    QString era = m_query->value(0).toString(), path = m_query->value(1).toString(),
            info = m_query->value(2).toString(), name = m_query->value(3).toString();
    bool domestic = m_query->value(4).toBool();
    QDate lastUpdate = m_query->value(5).toDate();

    arts.push_back(Art(era, path, info, name, domestic, lastUpdate, std::vector<Author>()));
  }
  fillArtsAuthors(arts);

  return arts;
}

void LevelsDBFacade::fillArtsAuthors(std::vector<Art>& arts)
{
  for (auto& art : arts)
    art.artAuthors = getAuthorsOfArt(art.imgName);
}

void LevelsDBFacade::fillArtsAuthors(std::set<Art>& arts)
{
  for (auto& art : arts)
    art.artAuthors = getAuthorsOfArt(art.imgName);
}

std::vector<Author> LevelsDBFacade::getAuthorsOfArt(const QString& artName)
{
  std::vector<Author> authors;
  exec(tr("SELECT authorName, authorImagePath, authorInfo, lastUpdate from authors JOIN artsAuthors ON "
          "authors.authorName=artsAuthors.artAuthor WHERE artname=") +
       qs(artName) + ";");
  m_authors_model->select();
  while (m_query->next())
  {
    Author author(m_query->value(0).toString(), m_query->value(1).toString(), m_query->value(2).toString(),
                  m_query->value(3).toDate());
    authors.push_back(author);
  }
  return authors;
}

std::vector<Author> LevelsDBFacade::authors()
{
  std::vector<Author> authors;
  exec(tr("SELECT authorName, authorImagePath, authorInfo, lastUpdate from authors;"));
  m_authors_model->select();
  while (m_query->next())
  {
    authors.push_back(Author(m_query->value(0).toString(), m_query->value(1).toString(), m_query->value(2).toString(),
                             m_query->value(3).toDate()));
  }

  return authors;
}

std::vector<Era> LevelsDBFacade::eras()
{
  std::vector<Era> eras;
  exec(tr("SELECT id, eraImagePath, lastUpdate from eras;"));
  m_eras_model->select();
  while (m_query->next())
  {
    eras.push_back(Era(m_query->value(0).toString(), m_query->value(1).toString(), m_query->value(2).toDate()));
  }

  return eras;
}

std::set<Era> LevelsDBFacade::getEras()
{
  std::set<Era> eras;
  exec(tr("SELECT id, eraImagePath, lastUpdate from eras;"));
  m_eras_model->select();
  while (m_query->next())
  {
    Era era(m_query->value(0).toString(), m_query->value(1).toString(), m_query->value(2).toDate());

    eras.insert(era);
  }

  return eras;
}

std::set<Art> LevelsDBFacade::getArts()
{
  std::set<Art> arts;
  exec(tr("SELECT era, path, info, name, domestic, lastUpdate from arts;"));
  m_arts_model->select();

  while (m_query->next())
  {
    QString era = m_query->value(0).toString(), path = m_query->value(1).toString(),
            info = m_query->value(2).toString(), name = m_query->value(3).toString();
    bool domestic = m_query->value(4).toBool();
    QDate lastUpdate = m_query->value(5).toDate();

    arts.insert(Art(era, path, info, name, domestic, lastUpdate, std::vector<Author>()));
  }
  fillArtsAuthors(arts);

  return arts;
}

void LevelsDBFacade::addEra(const Era& era)
{
  try
  {
    exec(tr("INSERT INTO eras (id, eraImagePath,lastUpdate) VALUES (") + qs(era.name) + ", " + qs(era.imgPath) + ", " +
         qs(era.lastUpdate.toString("yyyy-MM-dd")) + ");");
  }
  catch (...)
  {
    return;
  }
}

void LevelsDBFacade::addArt(const Art& art)
{
  try
  {
    exec(tr("INSERT INTO arts (era, path, info, name, domestic, lastUpdate) VALUES (") + qs(art.eraName) + ", " +
         qs(art.imgPath) + ", " + qs(art.imgInfo) + ", " + qs(art.imgName) + ", " + qs(art.domestic ? "1" : "0") +
         ", " + qs(art.lastUpdate.toString("yyyy-MM-dd")) + ");");
  }
  catch (...)
  {
    return;
  }
}

void LevelsDBFacade::addAuthor(const Author& author)
{
  try
  {
    exec(tr("INSERT INTO authors (authorName, authorImagePath, authorInfo, lastUpdate) VALUES (") +
         qs(author.authorName) + ", " + qs(author.imgPath) + ", " + qs(author.authorInfo) + ", " +
         qs(author.lastUpdate.toString("yyyy-MM-dd")) + ");");
  }
  catch (...)
  {
    return;
  }
}

void LevelsDBFacade::addArtAuthor(const QString authorName, const QString artName)
{
  try
  {
    exec(tr("INSERT INTO artsAuthors (artName, artAuthor) VALUES (") + qs(artName) + ", " + qs(authorName) + ");");
  }
  catch (...)
  {
    return;
  }
}

/// Сперва проверяется наличие записи статистики в базе
/// При её отсутствии, поступившая запись заносится в базу
/// При её наличии, сравниваются худшее и лучшее времена между двумя записями
/// При разнице во временах запись в базе обновляется
void LevelsDBFacade::checkStatistic(StatisticRecord& statisticRecord)
{
  exec(tr("SELECT eraName, artName, worstTime, bestTime, mode FROM statistic WHERE artName =") +
       qs(statisticRecord.artName) + tr("AND mode =") + qs(statisticRecord.mode) + ";");
  m_statistic_model->select();

  QString worstTime, bestTime;

  if (m_query->next())
  {
    worstTime = m_query->value(2).toString();
    bestTime = m_query->value(3).toString();
    if (worstTime < statisticRecord.worstTime)
    {
      statisticRecord.bestTime = bestTime;
      updateStatistic(statisticRecord);
    }
    if (bestTime > statisticRecord.bestTime)
    {
      statisticRecord.worstTime = bestTime;
      updateStatistic(statisticRecord);
    }
  }
  else
    addStatistic(statisticRecord);
}

void LevelsDBFacade::addStatistic(const StatisticRecord& statisticRecord)
{
  try
  {
    exec(tr("INSERT INTO statistic (eraName, artName, worstTime, bestTime, mode) VALUES (") +
         qs(statisticRecord.eraName) + ", " + qs(statisticRecord.artName) + ", " + qs(statisticRecord.worstTime) +
         ", " + qs(statisticRecord.bestTime) + ", " + qs(statisticRecord.mode) + ");");
  }
  catch (...)
  {
    return;
  }
}

void LevelsDBFacade::updateStatistic(const StatisticRecord& statisticRecord)
{
  try
  {
    exec("UPDATE statistic SET worstTime=" + qs(statisticRecord.worstTime) +
         ", bestTime= " + qs(statisticRecord.bestTime) + +" WHERE artName=" + qs(statisticRecord.artName) +
         "AND mode=" + qs(statisticRecord.mode) + ";");
  }
  catch (...)
  {
    return;
  }
}

void LevelsDBFacade::deleteFile(QString path)
{
  QFile file(path);
  file.remove();
}

void LevelsDBFacade::clearTable(QString tableName)
{
  exec(tr("DELETE FROM ") + tableName + ";");
  // exec(tr("VACUUM;"));
}

std::vector<StatisticsTableItem> LevelsDBFacade::getAllStatistic()
{
  std::vector<StatisticsTableItem> records;

  exec(tr("SELECT eraname, MAX(worsttime), MIN(besttime), COUNT(eraname), "
          "mode FROM statistic GROUP by eraname, mode;"));
  m_statistic_model->select();

  while (m_query->next())
  {
    QString eraName_ = m_query->value(0).toString(), worstTime_ = m_query->value(1).toString(),
            bestTime_ = m_query->value(2).toString(), count_ = m_query->value(3).toString(),
            mode_ = m_query->value(4).toString();

    StatisticsTableItem record(eraName_, count_, worstTime_, bestTime_, mode_);
    records.push_back(record);
  }
  return records;
}

void LevelsDBFacade::loadLevels(const QByteArray& jsonData)
{
  JsonParser jsonDoc;

  std::set<Era> eras;
  std::set<Art> arts;

  std::set<Author> allAuthors;
  std::set<Author> artAuthors;

  jsonDoc.readJson(jsonData);  ///Заполнение списков эпох, авторов, картин
  eras = jsonDoc.getEras();

  std::set<Era>::iterator erasIt = eras.begin();
  for (; erasIt != eras.end(); ++erasIt)
    addEra(*erasIt);

  arts = jsonDoc.getArts();
  std::set<Art>::iterator artsIt = arts.begin();

  ///Добавление картины в БД
  /// Получение и добавление в бд авторов картины
  /// Добавление авторов картины в таблицу соответствия картины и её авторов
  for (; artsIt != arts.end(); ++artsIt)
  {
    addArt(*artsIt);

    std::vector<Author>::const_iterator authorsIt = artsIt->artAuthors.begin();
    for (; authorsIt != artsIt->artAuthors.end(); ++authorsIt)
    {
      addAuthor(*authorsIt);
      addArtAuthor(authorsIt->authorName, artsIt->imgName);
    }
  }
}

void LevelsDBFacade::updateEra(const Era& era)
{
  exec(tr("SELECT path FROM eras WHERE id=") + qs(era.name) + tr(";"));
  m_eras_model->select();
  m_query->first();

  QString previousFilePath = m_query->value(0).toString();
  if (era.imgPath != previousFilePath)
    deleteFile(previousFilePath);

  try
  {
    exec("UPDATE eras SET id=" + qs(era.name) + ", eraImagePath= " + qs(era.imgPath) +
         ", lastUpdate=" + qs(era.lastUpdate.toString("yyyy-MM-dd")) + " WHERE id=" + qs(era.name) + ";");
  }
  catch (...)
  {
    return;
  }
}

void LevelsDBFacade::updateArt(Art& art)
{
  exec(tr("SELECT path FROM arts WHERE name=") + qs(art.imgName) + tr(";"));
  m_arts_model->select();
  m_query->first();

  QString previousFilePath = m_query->value(0).toString();
  if (art.imgPath != previousFilePath)
    deleteFile(previousFilePath);

  try
  {
    exec("UPDATE arts SET era=" + qs(art.eraName) + ", path= " + qs(art.imgPath) + ", info=" + qs(art.imgInfo) +
         ", name=" + qs(art.imgName) + ", domestic=" + qs(art.domestic ? "1" : "0") +
         ", lastUpdate=" + qs(art.lastUpdate.toString("yyyy-MM-dd")) + " WHERE name=" + qs(art.imgName) + ";");
  }
  catch (...)
  {
    return;
  }
}

void LevelsDBFacade::updateAuthor(Author& author)
{
  exec(tr("SELECT authorImagePath FROM authors WHERE authorName=") + qs(author.authorName) + tr(";"));
  m_authors_model->select();
  m_query->first();

  QString previousFilePath = m_query->value(0).toString();
  if (author.imgPath != previousFilePath)
    deleteFile(previousFilePath);

  try
  {
    exec("UPDATE authors SET authorName=" + qs(author.authorName) + ", authorImagePath= " + qs(author.imgPath) +
         ", authorInfo=" + qs(author.authorInfo) + ", lastUpdate=" + qs(author.lastUpdate.toString("yyyy-MM-dd")) +
         " WHERE authorName=" + qs(author.authorName) + ";");
  }
  catch (...)
  {
    return;
  }
}
