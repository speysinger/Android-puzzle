#ifndef SCROLLEDTEXTBROWSER_H
#define SCROLLEDTEXTBROWSER_H
#include <QTextBrowser>

//! QTextBrowser с удобным пролистыванием
class ScrolledTextBrowser : public QTextBrowser
{
  Q_OBJECT
public:
  ScrolledTextBrowser(QWidget* parent = nullptr);

protected:
  void mousePressEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent*);

private:
  int m_cursorPos_y;
  bool m_isMouseButtonPressed;
};

#endif  // SCROLLEDTEXTBROWSER_H
