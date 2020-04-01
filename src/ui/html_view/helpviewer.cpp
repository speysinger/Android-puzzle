#include <QPushButton>
#include <QGridLayout>
#include "src/ui/buttons/styledbutton.h"
#include "scrolledtextbrowser.h"
#include "helpviewer.h"

HelpViewer::HelpViewer(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout *layer = new QVBoxLayout(this);
    setLayout(layer);

  ScrolledTextBrowser* helpViewer = new ScrolledTextBrowser;
  StyledButton* backButton = new StyledButton("back", this);

  QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  sizePolicy.setVerticalStretch(1);

  backButton->setSizePolicy(sizePolicy);

  sizePolicy.setVerticalStretch(10);
  helpViewer->setSizePolicy(sizePolicy);

  helpViewer->setSource(QUrl("qrc:/help.html"));
  backButton->setIcon(QIcon(":/icon/back.ico"));

  layer->addWidget(helpViewer);
    layer->addWidget(backButton);

  connect(backButton, SIGNAL(clicked(bool)), SIGNAL(back()));
}
