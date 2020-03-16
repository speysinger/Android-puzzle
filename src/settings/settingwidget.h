#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include "database/settingsdbfacade.h"
#include "update/updatewidget.h"
#include "screen_controller/screensstack.h"

class SettingWidget : public QWidget{
  Q_OBJECT
public:
  SettingWidget(QWidget* parent = nullptr);
signals:
  void back();
  void loadSelected();
private slots:
  void createOpenDialog();
  void setSound();
  //void onLoad();
private:

  QLineEdit m_line_path;
  QComboBox m_combo_sound;
  std::vector<QString> m_sounds;
};

#endif // SETTINGWIDGET_H
