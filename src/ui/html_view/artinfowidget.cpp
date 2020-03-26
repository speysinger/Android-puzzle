#include "artinfowidget.h"
#include <QGridLayout>
#include "ui/buttons/styledbutton.h"
#include "scrolledtextbrowser.h"
#include "database/levelsdbfacade.h"
#include <vector>

ArtInfoWidget::ArtInfoWidget(QWidget* parent) : QWidget(parent)
{
  m_layer = new QGridLayout(this);
  setLayout(m_layer);

  m_text = new ScrolledTextBrowser(this);
  m_backButton = new StyledButton("back", this);
  m_backButton->setIcon(QIcon(":/icon/back.ico"));

  m_layer->addWidget(m_text, 0, 0);
  m_layer->addWidget(m_backButton, 1, 0);

  connect(m_backButton, SIGNAL(clicked(bool)), SIGNAL(back()));
}

void ArtInfoWidget::load(Art art)
{
  QTextCursor c;
  m_text->setHtml(tr("<b>") + "Авторы:" + "</b><br>");
  std::vector<Author> authors = art.artAuthors;

  for (auto author : authors)
  {
    QImage authorImage(author.imgPath);

    m_text->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    c = m_text->textCursor();
    c.insertImage(authorImage.scaled(350, authorImage.height(), Qt::KeepAspectRatio));

    m_text->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    c = m_text->textCursor();
    c.insertHtml(tr("<br>") + author.authorInfo + "<br><br>");
  }
  c.insertHtml(tr("<b>") + art.imgName + "</b><br>");
  QImage artImage(art.imgPath);
  m_text->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
  c = m_text->textCursor();
  c.insertImage(artImage.scaled(350, artImage.height(), Qt::KeepAspectRatio));

  m_text->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
  c = m_text->textCursor();
  c.insertHtml(tr("<br>") + art.imgInfo + "<br><br>");
}
