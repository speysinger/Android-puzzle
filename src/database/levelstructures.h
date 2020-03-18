#ifndef LEVELSTRUCTURES_H
#define LEVELSTRUCTURES_H
#include <QString>
#include <QVariant>
#include <QDate>
#include <vector>


struct Era {
  mutable QString name, imgPath;
  QDate lastUpdate;

  Era(QString name_, QString imgPath_, QDate lastUpdate_)
    : name(name_), imgPath(imgPath_), lastUpdate(lastUpdate_) {
  }

  friend uint qHash(const Era &era){
    return qHash(era.name);
  }

  bool operator<(const Era &other) const
  {
    return other.name<name;
  }

};

struct Author {
  QString authorName, imgPath, authorInfo; QDate lastUpdate;

  Author(QString authorName_, QString imgPath_, QString authorInfo_, QDate lastUpdate_)
    : authorName(authorName_), imgPath(imgPath_), authorInfo(authorInfo_), lastUpdate(lastUpdate_){}

  friend uint qHash(const Author &author) {
    return qHash(author.authorName);
  }

  bool operator==(const Author &other) const {
    return other.authorName==authorName;
  }

  friend bool operator<(const Author& x, const Author& y)
  {
    return x.authorName>y.authorName;
  }
};


struct Art {

  QString eraName, imgPath, imgInfo, imgName;bool domestic; QDate lastUpdate;
  mutable std::vector<Author> artAuthors;

  Art (){}
  Art(QString eraName_, QString imgPath_,  QString imgInfo_, QString name_, bool domestic_, QDate lastUpdate_,
      std::vector<Author> artAuthors_)
    : eraName(eraName_), imgPath(imgPath_), imgInfo(imgInfo_), imgName(name_), domestic(domestic_), lastUpdate(lastUpdate_),
      artAuthors(artAuthors_) {}

  friend uint qHash(const Art &art){
    return qHash(art.imgName);
  }

  bool operator==(const Art &other) const {
    return other.eraName==eraName;
  }

  Art operator=(const Art &other) {
    eraName = other.eraName;
    imgPath = other.imgPath;
    imgName = other.imgName;
    domestic = other.domestic;
    lastUpdate = other.lastUpdate;
    return *this;
  }

  friend bool operator<(const Art& x, const Art& y)
  {
    return x.imgName<y.imgName;
  }
};

struct EraListModelItem{
  QString eraName;
  int domesticFilesCount;
  int internationalFilesCount;
  bool eraNeedToUpdate;
  bool domesticSelected;
  bool internationalSelected;
  bool checkValue;

  EraListModelItem(QString eraName_,int domesticFilesCount_, int internationalFilesCount_,
                   bool eraNeedToUpdate_, bool checkValue_, bool domesticSelected_, bool internationalSelected_):
    eraName(eraName_), domesticFilesCount(domesticFilesCount_), internationalFilesCount(internationalFilesCount_),
    eraNeedToUpdate(eraNeedToUpdate_), domesticSelected(domesticSelected_), internationalSelected(internationalSelected_), checkValue(checkValue_){
  }
  EraListModelItem& operator=(const QVariant newValue){
    this->checkValue=newValue.toBool();
    return *this;
  }
  bool operator==(const QString &findEraName) const{
    return eraName==findEraName;
  }
};

struct TestResultsItem {
  QString question;
  QString userAnswer;
  QString correctAnswer;
  TestResultsItem(QString question_, QString userAnswer_, QString correctAnswer_):
    question(question_), userAnswer(userAnswer_), correctAnswer(correctAnswer_){}
};

struct StatisticRecord
{
  QString eraName;
  QString artName;
  QString worstTime;
  QString bestTime;
  QString mode;

  StatisticRecord(QString eraName_, QString artName_, QString worstTime_, QString bestTime_,
                  QString mode_):
    eraName(eraName_), artName(artName_), worstTime(worstTime_), bestTime(bestTime_),
    mode(mode_){}
};

struct StatisticsTableItem
{
  QString eraName;
  QString assembledPuzzleArts;
  QString worstTime;
  QString bestTime;
  QString mode;

  StatisticsTableItem(QString eraName_, QString assembledPuzzleArts_, QString worstTime_, QString bestTime_,
                      QString mode_):
    eraName(eraName_), assembledPuzzleArts(assembledPuzzleArts_), worstTime(worstTime_), bestTime(bestTime_),
  mode(mode_){}
};


struct DropGridItem {
  QString itemType;
  QString dropItemName;
  QString dropItemImageSource;
  QString answerObjectName;

  DropGridItem(QString itemType_, QString dropItemName_, QString dropItemImageSource_, QString answerObjectName_):
    itemType(itemType_), dropItemName(dropItemName_), dropItemImageSource(dropItemImageSource_), answerObjectName(answerObjectName_){}

  DropGridItem& operator=(const QString newValue) {
    this->answerObjectName = newValue;
    return *this;
  }
};

struct DragGridItem{
  QString itemType;
  QString dragItemName;
  QString dragItemImageSource;

  DragGridItem(QString itemType_, QString dragItemName_, QString dragItemImageSource_):
    itemType(itemType_),dragItemName(dragItemName_), dragItemImageSource(dragItemImageSource_){}

};

#endif // LEVELSTRUCTURES_H
