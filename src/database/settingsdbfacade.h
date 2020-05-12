#ifndef SETTINGSDBFACADE_H
#define SETTINGSDBFACADE_H

#include <exception>

#include "dbfacade.h"
#include "src/singleton.h"

struct Settings {
  QString value;
  QString property;
  Settings(QString property_, QString value_) {
    value = value_;
    property = property_;
  }
};

class SettingsDBFacade : public DBFacade {
  Q_OBJECT
 public:
  SettingsDBFacade(QObject* parent = nullptr);
  void set(const Settings& setting);
  QString getValue(const QString& property);

 protected:
  std::map<QString, QString> DefaultSettings;
  QSqlTableModel* m_model;

  friend class Singleton<SettingsDBFacade>;
};

#define DBSettings Singleton<SettingsDBFacade>::instance()

#endif  // SETTINGSDBFACADE_H
