#ifndef ERALISTMODEL_H
#define ERALISTMODEL_H

#include "src/database/levelstructures.h"

#include <QAbstractListModel>
#include <vector>
#include <QHash>

///
/// \brief The EraListModel class
/// Данный является моделью для qml listView
/// Реализует редактирование содержимого listView
class EraListModel : public QAbstractListModel
{
  Q_OBJECT
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
  EraListModel(QObject* parent = nullptr);

  enum listItemsType
  {
    nameRole = Qt::UserRole + 1,
    countRole,
    checkRole
  };

  int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex& index, const QVariant& value, int role) override;
  bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
  bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
  bool isPositionValid(int rowIndex) const;

  Q_INVOKABLE void getSelectedElements(bool isTestingRequest, int buttonNumber);
  Q_INVOKABLE void changeListOfTheSelectedEpoch(bool domesticArt, bool foreigntArt);
  Q_INVOKABLE void clearList();
  Q_INVOKABLE bool isTestingModule();

  QHash<int, QByteArray> roleNames() const override;
  QString BoolToString(bool b) const;

private:
  int getTotalEraFilesCount(const EraListModelItem& eraItem) const;
  std::vector<EraListModelItem> m_allErasForLoading;
  std::vector<EraListModelItem> m_eraListModel;
  std::vector<EraListModelItem> m_fillingList;

  bool m_isTestingModule = false;

  bool m_domesticArtSwitchButton = false;
  bool m_internationalArtSwitchButton = false;
};

#endif  // ERALISTMODEL_H
