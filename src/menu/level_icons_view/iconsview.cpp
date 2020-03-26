#include "iconsview.h"
#include "database/levelsdbfacade.h"
#include "menuitemproxy.h"

#include <QVBoxLayout>
#include <QScrollBar>
#include <QResizeEvent>

IconsView::IconsView(QWidget* parent) : QGraphicsView(parent), m_scene(this)
{
  setInteractive(false);
  setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
  setViewportMargins(0, 0, 0, 0);

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  setScene(&m_scene);
}

void IconsView::disposeIcons()
{
  const int n = m_icons.size();

  const int NRow = n / NColumn + (n % NColumn ? 1 : 0);

  int i = 0;
  for (auto icon : m_icons)
  {
    int iRow = i / NColumn;
    int iColumn = i % NColumn;

    if (height() > width())
    {
      std::swap(iRow, iColumn);
    }

    icon->setPos(iRow * IconSize, iColumn * IconSize);
    icon->disableItem(IconSize, IconSize);
    ++i;
  }

  if (height() > width())
  {
    m_scene.setSceneRect(0, 0, IconSize * NColumn, IconSize * NRow);
  }
  else
  {
    m_scene.setSceneRect(0, 0, IconSize * NRow, IconSize * NColumn);
  }
  scrollContentsBy(0, 0);
  fitInView(0, 0, IconSize * NColumn, IconSize * NColumn, Qt::KeepAspectRatio);
}

void IconsView::scrollContentsBy(int dx, int dy)
{
  qreal axis, size;

  QRectF visibleSceneRect = mapToScene(viewport()->rect()).boundingRect();

  if (width() > height())
  {
    axis = visibleSceneRect.x();
    size = visibleSceneRect.width();
  }
  else
  {
    axis = visibleSceneRect.y();
    size = visibleSceneRect.height();
  }

  if (axis <= 0)
    axis = 0;

  firstLoadableItemIndex = size_t(axis / IconSize) * NColumn;
  lastLoadableItemIndex = firstLoadableItemIndex + (size / IconSize + NColumn) * NColumn;
  lastLoadableItemIndex = qMin(lastLoadableItemIndex, m_icons.size());

  setProxyItems();

  QGraphicsView::scrollContentsBy(dx, dy);
}

void IconsView::setProxyItems()
{
  for (size_t index = firstLoadableItemIndex; index < lastLoadableItemIndex; index++)
  {
    auto* iconProxy = m_icons[index];
    iconProxy->setLabelSize(IconSize, IconSize);
  }

  if (firstLoadableItemIndex >= 1)
  {
    m_icons[firstLoadableItemIndex - 1]->disableItem(IconSize, IconSize);
    m_icons[firstLoadableItemIndex - 2]->disableItem(IconSize, IconSize);
  }

  if (lastLoadableItemIndex + (NColumn + 1) <= m_icons.size())
  {
    m_icons[lastLoadableItemIndex + 1]->disableItem(IconSize, IconSize);
    m_icons[lastLoadableItemIndex + 2]->disableItem(IconSize, IconSize);
  }
}

void IconsView::resizeEvent(QResizeEvent* event)
{
  if (event->size() != event->oldSize())
  {
    disposeIcons();
  }
}

void IconsView::mousePressEvent(QMouseEvent* event)
{
  m_clickPos = event->pos();
  QGraphicsView::mousePressEvent(event);
}

void IconsView::mouseReleaseEvent(QMouseEvent* event)
{
  auto object = itemAt(event->pos());
  do
  {
    if (nullptr == object)
      break;

    if ((m_clickPos - event->pos()).manhattanLength() > 10)
      break;

    auto proxy = dynamic_cast<QGraphicsItem*>(object);
    if (nullptr == proxy)
      break;

    auto authorIcon = dynamic_cast<AuthorIcon*>(proxy);
    auto eraIcon = dynamic_cast<EraIcon*>(proxy);
    auto artIcon = dynamic_cast<ArtIcon*>(proxy);

    if (authorIcon)
    {
      emit authorSelected(authorIcon->getAuthor());
    }
    if (eraIcon)
    {
      emit eraSelected(eraIcon->getEra());
    }
    if (artIcon)
    {
      emit artSelected(artIcon->getArt());
    }
  } while (false);

  QGraphicsView::mouseReleaseEvent(event);
}

void IconsView::loadAuthors()
{
  m_scene.clear();
  m_icons.clear();

  for (auto author : DB.authors())
  {
    AuthorIcon* authorIcon = new AuthorIcon(std::move(author));

    MenuItemProxy* proxy = new MenuItemProxy(authorIcon);

    m_icons.push_back(proxy);
    m_scene.addItem(proxy->getItem());
  }

  disposeIcons();
}

void IconsView::loadEras()
{
  m_scene.clear();
  m_icons.clear();

  for (auto era : DB.eras())
  {
    EraIcon* eraIcon = new EraIcon(std::move(era));

    MenuItemProxy* proxy = new MenuItemProxy(eraIcon);

    m_icons.push_back(proxy);

    m_scene.addItem(proxy->getItem());
  }
  disposeIcons();
}

void IconsView::loadArts(Author author)
{
  m_scene.clear();
  m_icons.clear();

  for (auto art : DB.arts(author))
  {
    ArtIcon* artIcon = new ArtIcon(std::move(art));

    MenuItemProxy* proxy = new MenuItemProxy(artIcon);

    m_icons.push_back(proxy);
    m_scene.addItem(proxy->getItem());
  }
  disposeIcons();
}

void IconsView::loadArts(Era era)
{
  m_scene.clear();
  m_icons.clear();

  auto test = DB.arts(era);
  for (int i = 0; i < 100; i++)
    test.push_back(test[0]);

  for (auto art : test)
  {
    ArtIcon* artIcon = new ArtIcon(std::move(art));

    MenuItemProxy* proxy = new MenuItemProxy(artIcon);

    m_icons.push_back(proxy);
    m_scene.addItem(proxy->getItem());
  }
  disposeIcons();
}
