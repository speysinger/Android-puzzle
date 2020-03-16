#include "dbfacade.h"
#include "levelsdbfacade.h"

DBFacade::DBFacade(QObject *parent)
  : QObject(parent) {

  if(QSqlDatabase::contains(QSqlDatabase::defaultConnection)) {
    m_db = QSqlDatabase::database();
  }
  else {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("puzzleDB.db1");
  }

  if (false == m_db.open())
    throw "can't open/create DB";
  m_query = new QSqlQuery(m_db);
}

QString DBFacade::qs(QString str) {
  return "'" + str + "'";
}

void DBFacade::exec(QString str) {
  m_query->clear();
  if (false == m_query->exec(str))
    throw tr("DBFacade Error: can't exec : ") + str;
  m_record = m_query->record();
}
