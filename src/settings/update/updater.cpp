#include "updater.h"

#include <algorithm>

#include "QDate"
#include "progressbarwidget.h"

Updater::Updater() {
  QThread* thread = new QThread;
  jsonLoader->moveToThread(thread);
  thread->start();

  connect(jsonLoader, SIGNAL(loaded(const QByteArray&)), this,
          SLOT(fillUpdatableLists(const QByteArray&)), Qt::AutoConnection);
}

void Updater::fillUpdatableLists(const QByteArray& jsonData) {
  m_updatableEras.clear();
  m_updatableArts.clear();
  m_updatableAuthors.clear();

  JsonParser loadedJson;
  loadedJson.readJson(jsonData);

  prepareUpdatableEras(loadedJson);
  prepareUpdatableArts(loadedJson);
  prepareUpdatableAuthors(loadedJson);

  sendUpdatableInfoToQml();
}

QString Updater::getUpdatableItemPath(QString url) {
  url = url.remove("https://pro-prof.com/artists-puzzle/load/");
  QString path_dir = DBSettings.getValue("path") + "/load/";
  QDir().mkdir(path_dir);

  QString path = path_dir + url;

  QDir().mkdir(path.left(path.lastIndexOf(QChar('/'))));
  return path;
}

void Updater::prepareUpdatableEras(const JsonParser& loadedJson) {
  m_updatableEras.clear();
  std::set<Era> erasFromDB, erasFromLoadedFile;

  erasFromDB = DB.getEras();
  erasFromLoadedFile = loadedJson.getEras();

  prepareUpdatableItems(erasFromLoadedFile, erasFromDB, m_updatableEras);
}

void Updater::prepareUpdatableArts(const JsonParser& loadedJson) {
  m_updatableArts.clear();
  std::set<Art> artsFromDB, artsFromLoadedFile;

  artsFromDB = DB.getArts();
  artsFromLoadedFile = loadedJson.getArts();

  prepareUpdatableItems(artsFromLoadedFile, artsFromDB, m_updatableArts);
}

void Updater::prepareUpdatableAuthors(const JsonParser& loadedJson) {
  m_updatableAuthors.clear();
  std::set<Author> authorsFromDB, authorsFromLoadedFile;

  authorsFromDB = DB.getAllAuthors();
  authorsFromLoadedFile = loadedJson.getAuthors();

  prepareUpdatableItems(authorsFromLoadedFile, authorsFromDB,
                        m_updatableAuthors);

  auto begin = m_updatableAuthors.begin();
  auto end = m_updatableAuthors.end();

  for (auto authorIt = begin; authorIt != end; ++authorIt)
    if (authorIt->updateFiles == NOTHING)
        m_updatableAuthors.erase(authorIt);
}

void Updater::sendUpdatableInfoToQml() {
  std::vector<EraListModelItem> eraListModelItems;
  std::set<UpdatableItemWrapper<Author>> authorsList = m_updatableAuthors;

  for (auto& era : m_updatableEras) {
    bool eraNeedToUpdate = false;
    int domesticFilesCount = 0;
    int internationalFilesCount = 0;

    if (era.updateFiles != NOTHING) eraNeedToUpdate = true;
    for (auto& art : m_updatableArts) {
      if (art.object.eraName == era.object.eraName) {
        if (art.updateFiles != NOTHING) {
          if (art.object.domestic)
            domesticFilesCount++;
          else
            internationalFilesCount++;
        }

        countAuthors(art, domesticFilesCount, internationalFilesCount,
                     authorsList);
        authorsList = m_updatableAuthors;
      }
    }
    EraListModelItem eraListModelItem(era.object.eraName, domesticFilesCount,
                                      internationalFilesCount, eraNeedToUpdate,
                                      false, false, false);
    eraListModelItems.push_back(eraListModelItem);
  }

  emit itemsLoaded(eraListModelItems, false);
}

int Updater::countSelectedForUpdateItems(
    const std::vector<EraListModelItem>& selectedEras) {
  int itemsForUpdate = 0;
  std::set<UpdatableItemWrapper<Author>> authorsList = m_updatableAuthors;

  for (auto& era : selectedEras) {
    UpdatableItemWrapper<Era> desiredEra(Era(era.eraName, "", QDate()),
                                         UpdateFileStatus(NOTHING));

    auto foundedEra = m_updatableEras.find(desiredEra);
    if (foundedEra->updateFiles != NOTHING) itemsForUpdate++;

    for (auto& art : m_updatableArts) {
      if (art.object.eraName == foundedEra->object.eraName) {
        if (art.updateFiles != NOTHING) {
          if (era.domesticSelected && art.object.domestic)
            itemsForUpdate++;
          else if (era.internationalSelected && !art.object.domestic)
            itemsForUpdate++;
          else {
            continue;
          }
        }

        countAuthors(art, itemsForUpdate, itemsForUpdate, authorsList);
      }
    }
  }
  return itemsForUpdate;
}

void Updater::countAuthors(
    UpdatableItemWrapper<Art> art, int& domesticFilesCount,
    int& internationalFilesCount,
    std::set<UpdatableItemWrapper<Author>>& authorsList) {
  for (auto& artAuthor : art.object.artAuthors) {
    UpdatableItemWrapper<Author> desiredAuthor(artAuthor, NOTHING);

    auto foundedAuthor = authorsList.find(desiredAuthor);
    if (foundedAuthor != authorsList.end()) {
      if (foundedAuthor->updateFiles != NOTHING) {
        if (art.object.domestic)
          domesticFilesCount++;
        else
          internationalFilesCount++;
        foundedAuthor->updateFiles = NOTHING;
      }
    }
  }
}

void Updater::downloadEra(UpdatableItemWrapper<Era> era) { downloadItem(era); }

void Updater::downloadArt(UpdatableItemWrapper<Art> art) {
  downloadItem(art);
  if (art.updateFiles == LOAD) {
    for (auto artAuthor : art.object.artAuthors)
      DB.addArtAuthor(artAuthor.authorName, art.object.imgName);
  }
}

void Updater::downloadAuthor(UpdatableItemWrapper<Author> author) {
  downloadItem(author);
}

/// \details Сперва производится подсчёт объектов, которые необходимо скачать,
/// для выбранного списка эпох Следом производится обход по списку всех картин
/// Для каждой картины проверяется наличие её эпохи в списке эпох на закачку
/// Для каждой картины проверяется необходимость закачать авторов
void Updater::uploadSelectedItems(
    const std::vector<EraListModelItem>& selectedEras) {
  int itemsForUpdateCount = countSelectedForUpdateItems(selectedEras);
  emit maxValueCalculated(itemsForUpdateCount);

  for (auto& art : m_updatableArts) {
    auto eraInSelectedList =
        std::find(selectedEras.begin(), selectedEras.end(), art.object.eraName);

    if (breaker) {
      breaker = false;
      emit stopLoading();
      return;
    }

    if (eraInSelectedList != selectedEras.end()) {
      UpdatableItemWrapper<Era> desiredEra(Era(art.object.eraName, "", QDate()),
                                           UpdateFileStatus(NOTHING));

      auto foundedEra = m_updatableEras.find(desiredEra);
      if (foundedEra->updateFiles != NOTHING) {
        downloadEra(*foundedEra);
        foundedEra->updateFiles = NOTHING;
      }

      if (art.object.eraName == foundedEra->object.eraName) {
        if (art.updateFiles != NOTHING) {
          if (eraInSelectedList->domesticSelected && art.object.domestic) {
            downloadArt(art);
          } else if (eraInSelectedList->internationalSelected &&
                     !art.object.domestic) {
            downloadArt(art);
          } else {
            continue;
          }
          art.updateFiles = NOTHING;
        }

        for (auto& artAuthor : art.object.artAuthors) {
          UpdatableItemWrapper<Author> desiredAuthor(artAuthor, NOTHING);
          auto foundedAuthor = m_updatableAuthors.find(desiredAuthor);
          if (foundedAuthor != m_updatableAuthors.end()) {
            if (foundedAuthor->updateFiles != NOTHING) {
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

void Updater::loadJson() {
  try {
    jsonLoader->loadJSON(jsonPath);
  } catch (const std::runtime_error& error) {
    qDebug() << error.what();
  }
}

void Updater::setBreakFlag(bool breakLoading) { breaker = breakLoading; }

template <class T>
void Updater::prepareUpdatableItems(
    std::set<T> jsonClassObjectsList, std::set<T> dbClassObjectsList,
    std::set<UpdatableItemWrapper<T>>& m_updatableItems) {
  for (auto& classObj : jsonClassObjectsList) {
    UpdateFileStatus updateFiles;

    auto foundedElement = dbClassObjectsList.find(classObj);
    if (foundedElement != dbClassObjectsList.end()) {
      if (classObj.lastUpdate > foundedElement->lastUpdate)
        updateFiles = UPDATE;
      else
        updateFiles = NOTHING;
    } else
      updateFiles = LOAD;
    m_updatableItems.insert(UpdatableItemWrapper<T>(classObj, updateFiles));
  }
}

template <class T>
void Updater::downloadItem(UpdatableItemWrapper<T> item) {
  QString pixmapPath = getUpdatableItemPath(item.object.imgPath);
  try {
    pixmapLoader->loadPixmap(item.object.imgPath, pixmapPath);
  } catch (const std::runtime_error& error) {
    qDebug() << error.what();
    return;
  }

  item.object.imgPath = pixmapPath;
  if (item.updateFiles == LOAD)
    DB.save(item.object);
  else
    DB.update(item.object);
  emit fileLoaded();
}
