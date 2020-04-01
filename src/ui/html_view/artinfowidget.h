#ifndef INFOART_H
#define INFOART_H
#include <QWidget>
#include "src/database/levelstructures.h"

class QGridLayout;
class ScrolledTextBrowser;
class StyledButton;

class ArtInfoWidget : public QWidget
{
  Q_OBJECT
public:
  ArtInfoWidget(QWidget* parent = nullptr);
  void load(Art art);
signals:
  void back();

protected:
  ScrolledTextBrowser *m_text;
};

#endif  // INFOART_H
