#include "eralistmodel.h"
#include "updater.h"
#include "testing/testmanager.h"

EraListModel::EraListModel(QObject* parent) : QAbstractListModel(parent)
{
  clearList();
  connect(&UPDATER, SIGNAL(itemsLoaded(std::vector<EraListModelItem>, bool)), this,
          SLOT(fillEras(std::vector<EraListModelItem>, bool)));
  connect(&TESTMANAGER, SIGNAL(erasReady(std::vector<EraListModelItem>, bool)), this,
          SLOT(fillEras(std::vector<EraListModelItem>, bool)));
}

void EraListModel::fillEras(std::vector<EraListModelItem> vec, bool isTestingModule)
{
  clearList();

  if (isTestingModule)
    m_isTestingModule = true;
  else
    m_isTestingModule = false;

  emit listViewWindowOpened();
  m_allErasForLoading = vec;
  emit listModelReady();
}

QString EraListModel::BoolToString(bool b) const
{
  return b ? "true" : "false";
}

int EraListModel::getTotalEraFilesCount(const EraListModelItem& eraItem) const
{
  return eraItem.domesticFilesCount + eraItem.internationalFilesCount;
}

int EraListModel::rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent)
  return m_eraListModel.size();
}

bool EraListModel::isPositionValid(int rowIndex) const
{
  return rowIndex < m_eraListModel.size();
}

void EraListModel::getSelectedElements(bool isTestingRequest, int buttonNumber)
{
  std::vector<EraListModelItem> selectedEras;
  selectedEras.clear();
  for (auto& era : m_eraListModel)
  {
    //если эпоха выбрана пользователем
    if (era.checkValue)
    {
      if (m_domesticArtSwitchButton)
        era.domesticSelected = true;

      if (m_internationalArtSwitchButton)
        era.internationalSelected = true;

      selectedEras.push_back(era);
    }
  }

  //если ничего не было выбрано, но кнопка вызова следующего окна была нажата
  if (selectedEras.size() <= 0)
    emit nothingIsSelected();
  else
  {
    //что-то выбрано, значит можно открывать следующее окно
    emit somethingSelected();

    //если данные изначально получены из окна тестирования, то testmanager будет обрабатывать результат
    if (isTestingRequest)
      TESTMANAGER.startTesting(selectedEras, buttonNumber);
    else  //иначе данные присылал апдейтер и данные ему отослать
      UPDATER.UploadSelectedItems(selectedEras);
  }
}

void EraListModel::changeListOfTheSelectedEpoch(bool domesticArt, bool foreigntArt)
{
  m_domesticArtSwitchButton = domesticArt;
  m_internationalArtSwitchButton = foreigntArt;

  m_fillingList.clear();
  removeRows(0, m_eraListModel.size(), QModelIndex());

  for (auto era : m_allErasForLoading)
  {
    //если выбрано отображение 2-х типов искусства
    if (m_domesticArtSwitchButton && m_internationalArtSwitchButton &&
        (era.domesticFilesCount > 0 || era.internationalFilesCount > 0))
    {
      m_fillingList.push_back(era);
    }
    //если выбрано отображение только отечественных эпох
    else if (m_domesticArtSwitchButton && era.domesticFilesCount > 0)
      m_fillingList.push_back(era);

    //если выбрано отображение только зарубежных эпох
    else if (m_internationalArtSwitchButton && era.internationalFilesCount > 0)
      m_fillingList.push_back(era);
  }
  insertRows(0, m_fillingList.size(), QModelIndex());
}

void EraListModel::clearList()
{
  removeRows(0, m_eraListModel.size(), QModelIndex());
  m_eraListModel.clear();
  m_fillingList.clear();
}

bool EraListModel::isTestingModule()
{
  return m_isTestingModule;
}

QHash<int, QByteArray> EraListModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[nameRole] = "eraName";
  roles[countRole] = "filesCount";
  roles[checkRole] = "checkValue";
  return roles;
}

QVariant EraListModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid() || (role != nameRole && role != checkRole && role != countRole))
    return QVariant{};

  int rowIndex = index.row();
  EraListModelItem eraItemAtIndex = m_eraListModel[rowIndex];

  if (!isPositionValid(rowIndex))
    return QVariant{};

  if (role == countRole)
  {
    int addEraToNumber = 0;
    if (eraItemAtIndex.eraNeedToUpdate)
      addEraToNumber = 1;

    if (m_domesticArtSwitchButton && m_internationalArtSwitchButton)
    {
      if (eraItemAtIndex.eraNeedToUpdate)
        return QVariant::fromValue(QString::number(getTotalEraFilesCount(eraItemAtIndex) + addEraToNumber));
      else
        return QVariant::fromValue(QString::number(getTotalEraFilesCount(eraItemAtIndex)));
    }

    else if (m_domesticArtSwitchButton & (eraItemAtIndex.domesticFilesCount > 0))
      return QVariant::fromValue(QString::number(eraItemAtIndex.domesticFilesCount + addEraToNumber));

    else
      return QVariant::fromValue(QString::number(eraItemAtIndex.internationalFilesCount + addEraToNumber));
  }
  if (role == checkRole)
    return QVariant::fromValue(BoolToString(eraItemAtIndex.checkValue));
  return QVariant::fromValue(eraItemAtIndex.eraName);
}

bool EraListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  Q_UNUSED(value)

  if (index.isValid() && role == checkRole)
  {
    int rowIndex = index.row();
    if (!isPositionValid(rowIndex))
      return false;
    m_eraListModel[rowIndex].checkValue = !m_eraListModel[rowIndex].checkValue;
    emit dataChanged(index, index, { checkRole });
    return true;
  }
  return false;
}

bool EraListModel::removeRows(int row, int count, const QModelIndex& parent)
{
  Q_UNUSED(parent)
  if (count > 0)
  {
    beginRemoveRows(QModelIndex(), row, count - 1);
    m_eraListModel.erase(m_eraListModel.begin(), m_eraListModel.end());
    endRemoveRows();
  }
  return true;
}

bool EraListModel::insertRows(int row, int count, const QModelIndex& parent)
{
  Q_UNUSED(row)
  Q_UNUSED(parent)

  if (count > 0)
  {
    beginInsertRows(QModelIndex(), 0, count - 1);
    m_eraListModel = m_fillingList;
    m_fillingList.clear();
    endInsertRows();
  }
  return true;
}
