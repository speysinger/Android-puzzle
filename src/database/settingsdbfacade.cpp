#include "settingsdbfacade.h"

SettingsDBFacade::SettingsDBFacade(QObject *parent)
  : DBFacade(parent),
    DefaultSettings(
      {
        {
          "path",
          QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0]
        },
        {"sound", "none"},
        {"data","2019-03-07"}
      }
  ) {

  if (false == m_db.tables().contains("settings")) {
    exec("CREATE TABLE settings ("
             "property TEXT PRIMARY KEY, "
             "value TEXT NOT NULL"
         ");"
    );

    for (auto setting : DefaultSettings) {
      exec(tr("INSERT INTO settings (property, value) VALUES (") +
            qs(setting.first) + ", " +
            qs(setting.second) +
           ");");
    }
  }

  m_model = new QSqlTableModel(this, m_db);
  m_model->setTable("settings");
  m_model->setEditStrategy(QSqlTableModel::OnFieldChange);
}

void SettingsDBFacade::set(const Settings &setting) {
  try {
    exec(tr("UPDATE settings SET value = ") +
        qs(setting.value) + " WHERE property = " + qs(setting.property));
  }
  catch(...) { return; }
}

QString SettingsDBFacade::getValue(const QString &property) {
  try {
    exec(tr("select value FROM settings WHERE property = ") +
        qs(property));
    m_model->select();
    m_query->first();
    return m_query->value(0).toString();
  }
  catch(...) { return DefaultSettings[property]; }
}




