#include <QPushButton>
#include <QGridLayout>
#include "buttons/styledbutton.h"
#include "scrolledtextbrowser.h"
#include "helpviewer.h"

HelpViewer::HelpViewer(QWidget *parent)
  : QWidget(parent) {

  QGridLayout *layer = new QGridLayout(this);
  setLayout(layer);

  ScrolledTextBrowser *helpViewer = new ScrolledTextBrowser;
  StyledButton *backButton = new StyledButton("back", this);

  helpViewer->setSource(QUrl("qrc:/help.html"));
  backButton->setIcon(QIcon(":/icon/back.ico"));

  layer->addWidget(backButton, 1, 1);
  layer->addWidget(helpViewer, 0, 0, 1, 3);

  connect(backButton, SIGNAL(clicked(bool)), SIGNAL(back()));
}


