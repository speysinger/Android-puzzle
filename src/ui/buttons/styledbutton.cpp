#include "styledbutton.h"
#include <QStyle>
#include <QFont>
#include <QDebug>

StyledButton::StyledButton(const QString& text, QWidget* parent) : QPushButton(text, parent)
{
  setStyleSheet(" QPushButton {border-radius: 8px; padding: 6px;}"
                " QPushButton { background-color: #ccdd39;}"
                " QPushButton:pressed {"
                " background-color: #4baf4f;"
                "}");
  QFont font("hAndy");
  setFont(font);
}

void StyledButton::resizeEvent(QResizeEvent* event)
{
  QFont resizedFont = font();
  float fontSize = std::min(this->width() / 18, this->height() / 3);
  if (this->fontMetrics().elidedText(this->text(), Qt::ElideMiddle, this->geometry().width()) != this->text())
  {
  }
  if (fontSize <= 1)
    resizedFont.setPointSizeF(1);
  else
    resizedFont.setPointSizeF(fontSize);

  setFont(resizedFont);
  QPushButton::resizeEvent(event);
}
