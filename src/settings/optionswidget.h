#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QComboBox>
#include <QLineEdit>
#include <QWidget>

#include "src/database/settingsdbfacade.h"
#include "src/screen_controller/screensstack.h"
#include "update/updatewidget.h"

class OptionsWidget : public QWidget {
  Q_OBJECT
 public:
  OptionsWidget(QWidget* parent = nullptr);
 signals:
  void back();
  void loadSelected();
 private slots:
  void createOpenDialog();
  void clearDatabase();

 private:
  QLineEdit m_line_path;
};

#endif  // SETTINGWIDGET_H
