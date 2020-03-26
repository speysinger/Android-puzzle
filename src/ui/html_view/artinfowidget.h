#ifndef INFOART_H
#define INFOART_H
#include <QWidget>
#include "database/levelstructures.h"

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
  QGridLayout* m_layer;
  ScrolledTextBrowser* m_text;
  StyledButton* m_backButton;
};

#endif  // INFOART_H
