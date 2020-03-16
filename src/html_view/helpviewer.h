#ifndef HELP_H
#define HELP_H

#include <QWidget>
#include "scrolledtextbrowser.h"

class HelpViewer : public QWidget {
  Q_OBJECT
public:
  HelpViewer(QWidget* parent = nullptr);
signals:
  void back();
};

#endif // HELP_H
