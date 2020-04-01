#include "artinfowidget.h"
#include <QGridLayout>
#include "src/ui/buttons/styledbutton.h"
#include "scrolledtextbrowser.h"
#include "src/database/levelsdbfacade.h"
#include <vector>

ArtInfoWidget::ArtInfoWidget(QWidget* parent) : QWidget(parent)
{
  QGridLayout *m_layer = new QGridLayout(this);
  setLayout(m_layer);

  m_text = new ScrolledTextBrowser(this);
  StyledButton *m_backButton = new StyledButton("back", this);
  m_backButton->setIcon(QIcon(":/icon/back.ico"));

  QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  sizePolicy.setVerticalStretch(1);

  m_backButton->setSizePolicy(sizePolicy);

  sizePolicy.setVerticalStretch(8);
  m_text->setSizePolicy(sizePolicy);

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
