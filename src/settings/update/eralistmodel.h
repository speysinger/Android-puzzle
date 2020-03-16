#ifndef ERALISTMODEL_H
#define ERALISTMODEL_H
#include <QAbstractListModel>
#include <vector>
#include <QObject>
#include <QHash>
#include <QList>
#include "database/levelstructures.h"


class EraListModel: public QAbstractListModel
{
  Q_OBJECT
  Q_PROPERTY(bool isTestingModule_ READ isTestingModule CONSTANT)
public slots:
  void fillEras(std::vector<EraListModelItem> vec, bool isTestingModule);
signals:
  void itTestingModule();
  void notTestingModule();
  void listModelReady();
  void listViewWindowOpened();
  void nothingIsSelected();
  void somethingSelected();
public:
  EraListModel(QObject*parent=nullptr);

  bool isTestingModule()
  {
    return isTestingModule_;
  }


  enum listItemsType{
    NameRole=Qt::UserRole+1,
    CountRole,
    CheckRole
  };

  int rowCount(const QModelIndex& parent=QModelIndex{}) const override;
  QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  bool isPositionValid(int rowIndex) const;

  Q_INVOKABLE void getSelectedElements(bool isTestingRequest, int buttonNumber);
  Q_INVOKABLE void changeListOfTheSelectedEpoch(bool domesticArt,bool foreigntArt);
  Q_INVOKABLE void clearList();

  QHash<int,QByteArray> roleNames() const override;
  QString BoolToString(bool b) const;

private:

  bool isTestingModule_ = false;
  int getTotalEraFilesCount(const EraListModelItem &eraItem) const;
  std::vector<EraListModelItem> allErasForLoading;
  std::vector<EraListModelItem> m_eraListModel;
  std::vector<EraListModelItem> m_fillingList;

  bool domesticArtSwitchButton=false;
  bool internationalArtSwitchButton=false;
};

#endif // ERALISTMODEL_H
