#ifndef UPDATER_H
#define UPDATER_H

#include <src/database/levelsdbfacade.h>
#include <src/database/levelstructures.h>
#include <src/database/jsonparser.h>
#include <vector>
#include <set>
#include "loader.h"

///
/// \brief The Updater class
/// Данный класс реализует обновление базы данных(Эпохи/Картины/Авторы)
/// Предоставляет интерфейс, позволяющий загрузить json и обновить указанный список эпох
class Updater : public QObject
{
  Q_OBJECT
public:
  Updater();
  void uploadSelectedItems(const std::vector<EraListModelItem>& selectedEras);
  void loadJson();
public slots:
  void fillUpdatableLists(const QByteArray& jsonData);

private:
  enum UpdateFileStatus
  {
    LOAD,
    UPDATE,
    NOTHING
  };

  template <class T>
  class UpdatableItemWrapper
  {
  public:
    UpdatableItemWrapper(T object_, UpdateFileStatus updateFiles_) : object(object_), updateFiles(updateFiles_)
    {
    }
    T object;
    mutable UpdateFileStatus updateFiles;

    bool operator<(const UpdatableItemWrapper<T>& other) const
    {
      return object < other.object;
    }

    bool operator==(const UpdatableItemWrapper<T>& other) const
    {
      return object == other.object;
    }
  };

  QString getUpdatableItemPath(QString url);

  template <class T>
  void prepareUpdatableItems(std::set<T> jsonClassObjectsList, std::set<T> dbClassObjectsList,
                             std::set<UpdatableItemWrapper<T>>&);
  void prepareUpdatableEras(const JsonParser& loadedJson);
  void prepareUpdatableArts(const JsonParser& loadedJson);
  void prepareUpdatableAuthors(const JsonParser& loadedJson);

  void sendUpdatableInfoToQml();
  int countSelectedForUpdateItems(const std::vector<EraListModelItem>& selectedEras);
  void countAuthors(UpdatableItemWrapper<Art> art, int& domesticFilesCount, int& internationalFilesCount,
                    std::set<UpdatableItemWrapper<Author>>& authorsList);

  template <class T>
  void downloadItem(UpdatableItemWrapper<T> item);
  void downloadEra(UpdatableItemWrapper<Era> era);
  void downloadArt(UpdatableItemWrapper<Art> art);
  void downloadAuthor(UpdatableItemWrapper<Author> author);

  std::set<UpdatableItemWrapper<Era>> m_updatableEras;
  std::set<UpdatableItemWrapper<Art>> m_updatableArts;
  std::set<UpdatableItemWrapper<Author>> m_updatableAuthors;

  Loader* pixmapLoader = new Loader();
  Loader* jsonLoader = new Loader();

  QString const jsonPath = "https://pro-prof.com/artists-puzzle/load_1/levels.json";

signals:
  void itemsLoaded(std::vector<EraListModelItem> vec, bool isTestingModule);
  void maxValueCalculated(int maxValue);
  void fileLoaded();
  void stopLoading();
};

#define UPDATER Singleton<Updater>::instance()

#endif  // UPDATER_H
