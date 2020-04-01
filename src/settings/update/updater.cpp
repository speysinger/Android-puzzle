#include "updater.h"
#include "QDate"
#include <algorithm>
#include "progressbarwidget.h"

Updater::Updater()
{
  QThread* thread = new QThread;
  jsonLoader->moveToThread(thread);
  thread->start();

  connect(jsonLoader, SIGNAL(loaded(const QByteArray&)), this, SLOT(fillUpdatableLists(const QByteArray&)),
          Qt::AutoConnection);
}

void Updater::fillUpdatableLists(const QByteArray& jsonData)
{
  m_updatableEras.clear();
  m_updatableArts.clear();
  m_updatableAuthors.clear();

  JsonParser loadedJson;
  loadedJson.readJson(jsonData);

  fillListOfUpdatableEras(loadedJson);
  fillListOfUpdatableArts(loadedJson);
  fillListOfUpdatableAuthors(loadedJson);

  sendUpdatableInfoToQml();
}

QString Updater::getUpdatableItemPath(QString url)
{
  url = url.remove("https://pro-prof.com/artists-puzzle/load_1/");
  QString path_dir = DBSettings.getValue("path") + "/load_1/";
  QDir().mkdir(path_dir);

  QString path = path_dir + url;

  QDir().mkdir(path.left(path.lastIndexOf(QChar('/'))));
  return path;
}

void Updater::fillListOfUpdatableEras(const JsonParser& loadedJson)
{
  m_updatableEras.clear();
  std::set<Era> erasFromDB, erasFromLoadedFile;

  erasFromDB = DB.getEras();
  erasFromLoadedFile = loadedJson.getEras();

  for (auto& era : erasFromLoadedFile)
  {
    UpdateFileStatus updateFiles;

    auto foundedElement = erasFromDB.find(era);
    if (foundedElement != erasFromDB.end())
    {
      if (era.lastUpdate > foundedElement->lastUpdate)
        updateFiles = UPDATE;
      else
        updateFiles = NOTHING;
    }
    else
      updateFiles = LOAD;
    m_updatableEras.insert(UpdatableItemWrapper<Era>(era, updateFiles));
  }
}

void Updater::fillListOfUpdatableArts(const JsonParser& loadedJson)
{
  m_updatableArts.clear();
  std::set<Art> artsFromDB, artsFromLoadedFile;

  artsFromDB = DB.getArts();
  artsFromLoadedFile = loadedJson.getArts();

  for (auto& art : artsFromLoadedFile)
  {
    UpdateFileStatus updateFiles;
    auto foundedElement = artsFromDB.find(art);
    if (foundedElement != artsFromDB.end())
    {
      if (art.lastUpdate > foundedElement->lastUpdate)
        updateFiles = UPDATE;
      else
        updateFiles = NOTHING;
    }
    else
      updateFiles = LOAD;
    m_updatableArts.insert(UpdatableItemWrapper<Art>(art, updateFiles));
  }
}

void Updater::fillListOfUpdatableAuthors(const JsonParser& loadedJson)
{
  m_updatableAuthors.clear();
  std::set<Author> authorsFromDB, authorsFromLoadedFile;

  authorsFromDB = DB.getAllAuthors();
  authorsFromLoadedFile = loadedJson.getAuthors();

  for (auto& author : authorsFromLoadedFile)
  {
    UpdateFileStatus updateFiles;
    auto foundedElement = authorsFromDB.find(author);
    if (foundedElement != authorsFromDB.end())
    {
      if (author.lastUpdate > foundedElement->lastUpdate)
        updateFiles = UPDATE;
      else
        updateFiles = NOTHING;
    }
    else
      updateFiles = LOAD;
    if (updateFiles != NOTHING)
      m_updatableAuthors.insert(UpdatableItemWrapper<Author>(author, updateFiles));
  }
}

void Updater::sendUpdatableInfoToQml()
{
  std::vector<EraListModelItem> eraListModelItems;

  for (auto& era : m_updatableEras)
  {
    bool eraNeedToUpdate = false;
    int domesticFilesCount = 0;
    int internationalFilesCount = 0;

    if (era.updateFiles != NOTHING)
      eraNeedToUpdate = true;
    for (auto& art : m_updatableArts)
    {
      if (art.object.eraName == era.object.name)
      {
        if (art.updateFiles != NOTHING)
        {
          if (art.object.domestic)
            domesticFilesCount++;
          else
            internationalFilesCount++;
        }

        for (auto& artAuthor : art.object.artAuthors)
        {
          UpdatableItemWrapper<Author> test(artAuthor, NOTHING);

          auto foundedAuthor = m_updatableAuthors.find(test);
          if (foundedAuthor != m_updatableAuthors.end())
          {
            if (foundedAuthor->updateFiles != NOTHING)
            {
              if (art.object.domestic)
                domesticFilesCount++;
              else
                internationalFilesCount++;
            }
          }
        }
      }
    }
    EraListModelItem eraListModelItem(era.object.name, domesticFilesCount, internationalFilesCount, eraNeedToUpdate,
                                      false, false, false);
    eraListModelItems.push_back(eraListModelItem);
  }

  emit itemsLoaded(eraListModelItems, false);
}

int Updater::countSelectedForUpdateItems(const std::vector<EraListModelItem>& selectedEras)
{
  int itemsForUpdate = 0;
  std::set<UpdatableItemWrapper<Author>> authorsList = m_updatableAuthors;

  for (auto& era : selectedEras)
  {
    UpdatableItemWrapper<Era> fakeItemWrapper(Era(era.eraName, "", QDate()), UpdateFileStatus(NOTHING));

    auto foundedEra = m_updatableEras.find(fakeItemWrapper);
    if (foundedEra->updateFiles != NOTHING)
      itemsForUpdate++;

    for (auto& art : m_updatableArts)
    {
      if (art.object.eraName == foundedEra->object.name)
      {
        if (art.updateFiles != NOTHING)
        {
          if (era.domesticSelected && art.object.domestic)
            itemsForUpdate++;
          if (era.internationalSelected && !art.object.domestic)
            itemsForUpdate++;
        }

        for (auto& artAuthor : art.object.artAuthors)
        {
          UpdatableItemWrapper<Author> test(artAuthor, NOTHING);
          auto foundedAuthor = authorsList.find(test);
          if (foundedAuthor != authorsList.end())
          {
            if (foundedAuthor->updateFiles != NOTHING)
            {
              itemsForUpdate++;
              foundedAuthor->updateFiles = NOTHING;
            }
          }
        }
      }
    }
  }
  return itemsForUpdate;
}

void Updater::downloadEra(UpdatableItemWrapper<Era> era)
{
  QString pixmapPath = getUpdatableItemPath(era.object.imgPath);
  try
  {
    pixmapLoader->loadPixmap(era.object.imgPath, pixmapPath);
  }
  catch (const std::runtime_error& error)
  {
    qDebug() << error.what();
    return;
  }

  era.object.imgPath = pixmapPath;
  if (era.updateFiles == LOAD)
    DB.addEra(era.object);
  else
    DB.updateEra(era.object);
  emit fileLoaded();
}

void Updater::downloadArt(UpdatableItemWrapper<Art> art)
{
  QString pixmapPath = getUpdatableItemPath(art.object.imgPath);
  try
  {
    pixmapLoader->loadPixmap(art.object.imgPath, pixmapPath);
  }
  catch (const std::runtime_error& error)
  {
    qDebug() << error.what();
    return;
  }
  art.object.imgPath = pixmapPath;
  if (art.updateFiles == LOAD)
  {
    DB.addArt(art.object);
    for (auto artAuthor : art.object.artAuthors)
      DB.addArtAuthor(artAuthor.authorName, art.object.imgName);
  }
  else
    DB.updateArt(art.object);
  emit fileLoaded();
}

void Updater::downloadAuthor(UpdatableItemWrapper<Author> author)
{
  QString pixmapPath = getUpdatableItemPath(author.object.imgPath);
  try
  {
    pixmapLoader->loadPixmap(author.object.imgPath, pixmapPath);
  }
  catch (const std::runtime_error& error)
  {
    qDebug() << error.what();
    return;
  }
  author.object.imgPath = pixmapPath;
  if (author.updateFiles == LOAD)
    DB.addAuthor(author.object);
  else
    DB.updateAuthor(author.object);
  emit fileLoaded();
}

/// \details Сперва производится подсчёт объектов, которые необходимо скачать, для выбранного списка эпох
/// Следом производится обход по списке всех картин
/// Для каждой картины проверяется наличие её эпохи в списке эпох на закачку
/// Для каждой картины проверяется необходимость закачать авторов
void Updater::UploadSelectedItems(const std::vector<EraListModelItem>& selectedEras)
{
  int itemsForUpdateCount = countSelectedForUpdateItems(selectedEras);
  emit maxValueCalculated(itemsForUpdateCount);

  for (auto& art : m_updatableArts)
  {
    auto eraInSelectedList = std::find(selectedEras.begin(), selectedEras.end(), art.object.eraName);

    if (eraInSelectedList != selectedEras.end())
    {
      UpdatableItemWrapper<Era> fakeItemWrapper(Era(art.object.eraName, "", QDate()), UpdateFileStatus(NOTHING));

      auto foundedEra = m_updatableEras.find(fakeItemWrapper);
      if (foundedEra->updateFiles != NOTHING)
      {
        downloadEra(*foundedEra);
        foundedEra->updateFiles = NOTHING;
      }

      if (art.object.eraName == foundedEra->object.name)
      {
        if (art.updateFiles != NOTHING)
        {
          if (eraInSelectedList->domesticSelected && art.object.domestic)
          {
            downloadArt(art);
          }
          if (eraInSelectedList->internationalSelected && !art.object.domestic)
          {
            downloadArt(art);
          }
          art.updateFiles = NOTHING;
        }

        for (auto& artAuthor : art.object.artAuthors)
        {
          UpdatableItemWrapper<Author> test(artAuthor, NOTHING);
          auto foundedAuthor = m_updatableAuthors.find(test);
          if (foundedAuthor != m_updatableAuthors.end())
          {
            if (foundedAuthor->updateFiles != NOTHING)
            {
              downloadAuthor(*foundedAuthor);
              m_updatableAuthors.erase(foundedAuthor);
            }
          }
        }
      }
    }
  }
  emit stopLoading();
}

void Updater::loadJson()
{
  try
  {
    jsonLoader->loadJSON(jsonPath);
  }
  catch (const std::runtime_error& error)
  {
    qDebug() << error.what();
  }
}
