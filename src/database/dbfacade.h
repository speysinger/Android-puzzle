#ifndef DBFACADE_H
# define DBFACADE_H

#include <QtSql/QtSql>
#include <QObject>

class DBFacade : public QObject {
  Q_OBJECT
public:
  DBFacade(QObject *parent = nullptr);
protected:
  void exec(QString);
  QString qs(QString);

  QSqlDatabase m_db;
  QSqlQuery *m_query;
  QSqlRecord m_record;
};
#endif // DBFACADE_H
