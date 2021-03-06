#include "styledbutton.h"

#include <QDebug>
#include <QFont>
#include <QStyle>

StyledButton::StyledButton(const QString& text, QWidget* parent)
    : QPushButton(text, parent) {
  setStyleSheet(
      " QPushButton {border-radius: 8px; padding: 6px;}"
      " QPushButton { background-color: #ccdd39;}"
      " QPushButton:pressed {"
      " background-color: #4baf4f;"
      "}");
  QFont font("hAndy");
  setFont(font);
}

void StyledButton::resizeEvent(QResizeEvent* event) {
  QFont resizedFont = font();
  float fontSize = std::min(this->width() / 28, this->height() / 6);
  if (this->fontMetrics().elidedText(this->text(), Qt::ElideMiddle,
                                     this->geometry().width()) !=
      this->text()) {
  }
  if (fontSize <= 1)
    resizedFont.setPointSizeF(1);
  else
    resizedFont.setPointSizeF(fontSize);

  setIconSize(QSize(this->width() / 8, this->height() / 3));
  setFont(resizedFont);
  QPushButton::resizeEvent(event);
}
