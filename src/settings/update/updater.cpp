#include "updater.h"
#include "QDate"
#include <set>
#include <algorithm>
#include "progressBarWidget.h"
#include <settings/update/indexloader.h>

Updater::Updater()
{
  connect(&LOADER, SIGNAL(loaded(const QByteArray &)), this, SLOT(fillUpdatableLists(const QByteArray&)), Qt::AutoConnection);
}

void Updater::fillUpdatableLists(const QByteArray &jsonData)
{
  timer.start();
  JsonDocument loadedJson;
  loadedJson.readJson(jsonData);

  fillListOfUpdatableEras(loadedJson);
  fillListOfUpdatableArts(loadedJson);
  fillListOfUpdatableAuthors(loadedJson);

  sendUpdatableInfoToQml();
}

void Updater::fillListOfUpdatableEras(JsonDocument &loadedJson)
{
  updatableEras.clear();
  std::set<Era> erasFromDB,erasFromLoadedFile;

  erasFromDB=DB.getEras();
  erasFromLoadedFile=loadedJson.getEras();

  for(auto& era : erasFromLoadedFile)
  {
    UpdateFileStatus updateFiles;

    auto foundedElement=erasFromDB.find(era);
    if(foundedElement!=erasFromDB.end())
    {
      if(era.lastUpdate > foundedElement->lastUpdate)
        updateFiles = UPDATE;
      else
        updateFiles = NOTHING;
    }
    else
      updateFiles = LOAD;
    updatableEras.insert(UpdatableItemWrapper<Era>(era,updateFiles));
  }
}

void Updater::fillListOfUpdatableArts(JsonDocument &loadedJson)
{
  updatableArts.clear();
  std::set<Art> artsFromDB,artsFromLoadedFile;

  artsFromDB=DB.getArts();
  artsFromLoadedFile=loadedJson.getArts();

  for(auto& art : artsFromLoadedFile)
  {
    UpdateFileStatus updateFiles;
    auto foundedElement = artsFromDB.find(art);
    if(foundedElement!=artsFromDB.end())
    {
      if(art.lastUpdate>foundedElement->lastUpdate)
        updateFiles = UPDATE;
      else
        updateFiles = NOTHING;
    }
    else
      updateFiles = LOAD;
    updatableArts.insert(UpdatableItemWrapper<Art>(art,updateFiles));
  }
}

void Updater::fillListOfUpdatableAuthors(JsonDocument &loadedJson)
{
  updatableAuthors.clear();
  std::set<Author> authorsFromDB, authorsFromLoadedFile;

  authorsFromDB=DB.getAllAuthors();
  authorsFromLoadedFile=loadedJson.getAuthors();

  for(auto& author : authorsFromLoadedFile)
  {
    UpdateFileStatus updateFiles;
    auto foundedElement = authorsFromDB.find(author);
    if(foundedElement!=authorsFromDB.end())
    {
      if(author.lastUpdate>foundedElement->lastUpdate)
        updateFiles = UPDATE;
      else
        updateFiles = NOTHING;
    }
    else
      updateFiles = LOAD;
    if(updateFiles != NOTHING)
      updatableAuthors.insert(UpdatableItemWrapper<Author>(author,updateFiles));
  }
}

void Updater::sendUpdatableInfoToQml()
{
  std::vector<EraListModelItem> eraListModelItems;

  for(auto& era : updatableEras)
  {
    bool eraNeedToUpdate = false;
    int domesticFilesCount = 0;
    int internationalFilesCount = 0;

    if(era.updateFiles != NOTHING)
      eraNeedToUpdate = true;
    for(auto& art : updatableArts)
    {
      if(art.object.eraName == era.object.name)
      {
        if(art.updateFiles != NOTHING)
        {
          if(art.object.domestic)
            domesticFilesCount++;
          else
            internationalFilesCount++;
        }

        for(auto& artAuthor : art.object.artAuthors)
        {
          UpdatableItemWrapper<Author> test(artAuthor, NOTHING);

          auto foundedAuthor = updatableAuthors.find(test);
          if(foundedAuthor != updatableAuthors.end())
          {
            if(foundedAuthor->updateFiles != NOTHING)
            {
              if(art.object.domestic)
                domesticFilesCount++;
              else
                internationalFilesCount++;
            }
          }
        }
      }
    }
    EraListModelItem eraListModelItem(era.object.name, domesticFilesCount, internationalFilesCount, eraNeedToUpdate, false,
                                      false, false);
    eraListModelItems.push_back(eraListModelItem);
  }

  emit itemsLoaded(eraListModelItems, false);

  int ms=timer.elapsed();
  qDebug()<<"MS"+QString::number(ms);
}

int Updater::countSelectedForUpdateItems(std::vector<EraListModelItem> &selectedEras)
{
  int itemsForUpdate = 0;
  std::set<UpdatableItemWrapper<Author>> authorsList = updatableAuthors;

  for(auto& era : selectedEras)
  {
    UpdatableItemWrapper<Era> fakeItemWrapper(Era(era.eraName, "", QDate()), UpdateFileStatus(NOTHING));

    auto foundedEra = updatableEras.find(fakeItemWrapper);
    if(foundedEra->updateFiles != NOTHING)
      itemsForUpdate++;

    for(auto& art : updatableArts)
    {
      if(art.object.eraName == foundedEra->object.name)
      {
        if(art.updateFiles != NOTHING)
        {
          if(era.domesticSelected && art.object.domestic)
            itemsForUpdate++;
          if(era.internationalSelected && !art.object.domestic)
            itemsForUpdate++;
        }

        for(auto& artAuthor : art.object.artAuthors)
        {
          UpdatableItemWrapper<Author> test(artAuthor, NOTHING);
          auto foundedAuthor = authorsList.find(test);
          if(foundedAuthor != authorsList.end())
          {
            if(foundedAuthor->updateFiles != NOTHING)
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
  LOADERPIXMAP.load(era.object.imgPath);
  era.object.imgPath=LOADERPIXMAP.getPicPath();
  if(era.updateFiles == LOAD)
    DB.addEra(era.object);
  else
    DB.updateEra(era.object);
  emit fileLoaded();
}

void Updater::downloadArt(UpdatableItemWrapper<Art> art)
{
  LOADERPIXMAP.load(art.object.imgPath);
  art.object.imgPath=LOADERPIXMAP.getPicPath();
  if(art.updateFiles == LOAD)
    DB.addArt(art.object);
  else
    DB.updateArt(art.object);
  emit fileLoaded();
}

void Updater::downloadAuthor(UpdatableItemWrapper<Author> author)
{
  LOADERPIXMAP.load(author.object.imgPath);
  author.object.imgPath=LOADERPIXMAP.getPicPath();
  if(author.updateFiles == LOAD)
    DB.addAuthor(author.object);
  else
    DB.updateAuthor(author.object);
  emit fileLoaded();
}


/// \details Сперва производится подсчёт объектов, которые необходимо скачать, для выбранного списка эпох
/// Следом производится обход по списке всех картин
/// Для каждой картины проверяется наличие её эпохи в списке эпох на закачку
/// Для каждой картины проверяется необходимость закачать авторов
void Updater::UploadSelectedItems(std::vector<EraListModelItem> &selectedEras)
{
  int itemsForUpdateCount = countSelectedForUpdateItems(selectedEras);

  qDebug()<<"COUNT"+QString::number(itemsForUpdateCount);
  //Количество файлов на загрузку в прогресс бар
  emit maxValueCalculated(itemsForUpdateCount);
  std::vector<EraListModelItem> eraListModelItems;

  //может обход по картинам с проверкой наличия эпохи картины в списке закачиваемых картин

  for(auto& art : updatableArts)
  {
    auto eraInSelectedList = std::find(selectedEras.begin(), selectedEras.end(), art.object.eraName);

    if(eraInSelectedList != selectedEras.end())
    {
      UpdatableItemWrapper<Era> fakeItemWrapper(Era(art.object.eraName, "", QDate()), UpdateFileStatus(NOTHING));

      auto foundedEra = updatableEras.find(fakeItemWrapper);
      if(foundedEra->updateFiles != NOTHING)
      {
        downloadEra(*foundedEra);
        foundedEra->updateFiles = NOTHING;
      }

      if(art.object.eraName == foundedEra->object.name)
      {
        if(art.updateFiles != NOTHING)
        {
          if(eraInSelectedList->domesticSelected && art.object.domestic)
            downloadArt(art);
          if(eraInSelectedList->internationalSelected && !art.object.domestic)
            downloadArt(art);
        }

        for(auto& artAuthor : art.object.artAuthors)
        {
          UpdatableItemWrapper<Author> test(artAuthor, NOTHING);
          auto foundedAuthor = updatableAuthors.find(test);
          if(foundedAuthor != updatableAuthors.end())
          {
            if(foundedAuthor->updateFiles != NOTHING)
            {
              downloadAuthor(*foundedAuthor);
              foundedAuthor->updateFiles = NOTHING;
              updatableAuthors.erase(foundedAuthor);

              if(art.updateFiles == LOAD)
                DB.addArtAuthor(foundedAuthor->object.authorName, art.object.imgName);
            }
          }
        }
        //updatableArts.erase(art);
      }
    }
  }
}
























/*for(auto& era : selectedEras)
{
  UpdatableItemWrapper<Era> fakeItemWrapper(Era(era.eraName, "", QDate()), UpdateFileStatus(NOTHING));

  auto foundedEra = updatableEras.find(fakeItemWrapper);
  if(foundedEra->updateFiles != NOTHING)
    downloadEra(*foundedEra);

  for(auto& art : updatableArts)
  {
    if(art.object.eraName == foundedEra->object.name)
    {
      if(art.updateFiles != NOTHING)
      {
        if(era.domesticSelected && art.object.domestic)
        {
          downloadArt(art);
        }
        if(era.internationalSelected && !art.object.domestic)
          downloadArt(art);
      }

      for(auto& artAuthor : art.object.artAuthors)
      {
        UpdatableItemWrapper<Author> test(artAuthor, NOTHING);
        auto foundedAuthor = updatableAuthors.find(test);
        if(foundedAuthor != updatableAuthors.end())
        {
          if(foundedAuthor->updateFiles != NOTHING)
          {
            downloadAuthor(*foundedAuthor);
            foundedAuthor->updateFiles = NOTHING;
            //updatableAuthors.erase(foundedAuthor);

            if(art.updateFiles == LOAD)
              DB.addArtAuthor(foundedAuthor->object.authorName, art.object.imgName);
          }
        }
      }
      art.updateFiles = NOTHING;
    }
  }
}*/
//}


