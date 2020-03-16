#ifndef UPDATER_H
#define UPDATER_H

#include <database/levelsdbfacade.h>
#include <database/levelstructures.h>
#include <database/jsondocument.h>
#include <QObject>
#include <vector>
#include <set>
#include <QTime>

class Updater:public QObject
{
  Q_OBJECT
public:
  Updater();
  void UploadSelectedItems(std::vector<EraListModelItem> &selectedEras);
public slots:
  void fillUpdatableLists(const QByteArray &jsonData);

private:
  enum UpdateFileStatus { LOAD, UPDATE, NOTHING };

  template<class T>
  class UpdatableItemWrapper
  {
  public:
    UpdatableItemWrapper(T object_, UpdateFileStatus updateFiles_):
      object(object_), updateFiles(updateFiles_){}
    T object;
    mutable UpdateFileStatus updateFiles;

    bool operator<(const UpdatableItemWrapper<T>& other) const
    {
     return object<other.object;
    }

    bool operator==(const UpdatableItemWrapper<T>& other) const{
      return object == other.object;
    }
  };

  void fillListOfUpdatableEras(JsonDocument &loadedJson);
  void fillListOfUpdatableArts(JsonDocument &loadedJson);
  void fillListOfUpdatableAuthors(JsonDocument &loadedJson);

  void sendUpdatableInfoToQml();
  int countSelectedForUpdateItems(std::vector<EraListModelItem> &selectedEras);

  void downloadEra(UpdatableItemWrapper<Era> era);
  void downloadArt(UpdatableItemWrapper<Art> art);
  void downloadAuthor(UpdatableItemWrapper<Author> author);

  std::set<UpdatableItemWrapper<Era>> updatableEras;
  std::set<UpdatableItemWrapper<Art>> updatableArts;
  std::set<UpdatableItemWrapper<Author>> updatableAuthors;

  QTime timer;

signals:
  void itemsLoaded(std::vector<EraListModelItem> vec, bool isTestingModule);
  void maxValueCalculated(int maxValue);
  void fileLoaded();
};

#define UPDATER Singleton<Updater>::instance()

#endif // UPDATER_H
