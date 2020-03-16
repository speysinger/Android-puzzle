#include "eralistmodel.h"
#include "indexloader.h"
#include "updater.h"
#include "testing/testmanager.h"
#include <QDebug>

EraListModel::EraListModel(QObject *parent)
  :QAbstractListModel(parent)
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
  //cигнал, уведомляющий о том, что лист вью используются в модуле тестирования
  // и количество файлов выводить нет необходимости
  if(isTestingModule)
    isTestingModule_=true;
    //emit itTestingModule();
  else
    isTestingModule_=false;
    //emit notTestingModule();

  emit listViewWindowOpened();
  allErasForLoading = vec;
  emit listModelReady();
}

QString EraListModel::BoolToString(bool b) const
{
  return b ? "true" : "false";
}

int EraListModel::getTotalEraFilesCount(const EraListModelItem &eraItem) const
{
  return eraItem.domesticFilesCount+eraItem.internationalFilesCount;
}

int EraListModel::rowCount(const QModelIndex &parent) const
{
  return m_eraListModel.size();
}

bool EraListModel::isPositionValid(int rowIndex) const
{
  return rowIndex<m_eraListModel.size();
}

void EraListModel::getSelectedElements(bool isTestingRequest,int buttonNumber)
{
  std::vector<EraListModelItem> selectedEras;
  selectedEras.clear();
  for(std::vector<EraListModelItem>::iterator it = m_eraListModel.begin();it!=m_eraListModel.end();++it)
  {
    //если эпоха выбрана пользователем
    if(it->checkValue)
    {
      if(domesticArtSwitchButton)
        it->domesticSelected=true;
      if(internationalArtSwitchButton)
        it->internationalSelected=true;
      selectedEras.push_back(*it);
    }
  }

  //если ничего не было выбрано, но кнопка вызова следующего окна была нажата
  if(selectedEras.size()<=0)
    emit nothingIsSelected();
  else
  {
    //что-то выбрано, значит можно открывать следующее окно
    emit somethingSelected();

    //если данные изначально получены из окна тестирования, то testmanager будет обрабатывать результат
    if(isTestingRequest)
      TESTMANAGER.startTesting(selectedEras, buttonNumber);
    else //иначе данные присылал апдейтер и данные ему отослать
      UPDATER.UploadSelectedItems(selectedEras);
  }
}

void EraListModel::changeListOfTheSelectedEpoch(bool domesticArt, bool foreigntArt)
{
  domesticArtSwitchButton=domesticArt;
  internationalArtSwitchButton=foreigntArt;

  m_fillingList.clear();
  removeRows(0,m_eraListModel.size(),QModelIndex());//если удаление всех строк удачно

  for(size_t index=0;index<allErasForLoading.size();index++)
  {
    //если выбрано отображение 2-х типов искусства
    if(domesticArtSwitchButton && internationalArtSwitchButton && (allErasForLoading[index].domesticFilesCount>0
                                                                   || allErasForLoading[index].internationalFilesCount>0))
    {
      EraListModelItem newItem(allErasForLoading[index]);
      m_fillingList.push_back(newItem);
    }
    //если выбрано отображение только отечественных эпох
    else if(domesticArtSwitchButton && allErasForLoading[index].domesticFilesCount>0)
    {
      EraListModelItem newItem(allErasForLoading[index]);
      m_fillingList.push_back(newItem);
    }
    //если выбрано отображение только зарубежных эпох
    else if(internationalArtSwitchButton &&  allErasForLoading[index].internationalFilesCount>0)
    {
      EraListModelItem newItem(allErasForLoading[index]);
      m_fillingList.push_back(newItem);
    }
  }
  insertRows(0,m_fillingList.size(),QModelIndex());///Что выводить в случае, если не вставил
}

void EraListModel::clearList()
{
  removeRows(0,m_eraListModel.size(),QModelIndex());
  m_eraListModel.clear();
  m_fillingList.clear();
}

QHash<int, QByteArray> EraListModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[NameRole] = "eraName";
  roles[CountRole] = "filesCount";
  roles[CheckRole] = "checkValue";
  return roles;
}

QVariant EraListModel::data(const QModelIndex &index, int role) const
{
  if(!index.isValid() || (role!=NameRole && role!=CheckRole && role!=CountRole))
    return QVariant {};

  int rowIndex=index.row();

  if(role==CountRole)
  {
    int addEraToNumber=0;
    if(m_eraListModel[rowIndex].eraNeedToUpdate)
      addEraToNumber=1;
    //эпоха уже оказалась в списке для отображения
    //здесь лишь запрашивается информация о ней
    if(domesticArtSwitchButton && internationalArtSwitchButton)
    {
      if(m_eraListModel[rowIndex].eraNeedToUpdate)
        return QVariant::fromValue(QString::number(getTotalEraFilesCount(m_eraListModel[rowIndex])+
                                                   addEraToNumber));
      else
        return QVariant::fromValue(QString::number(getTotalEraFilesCount(m_eraListModel[rowIndex])));
    }

    else if(domesticArtSwitchButton & m_eraListModel[rowIndex].domesticFilesCount>0)
      return QVariant::fromValue(QString::number(m_eraListModel[rowIndex].domesticFilesCount+addEraToNumber));

    else
      return QVariant::fromValue(QString::number(m_eraListModel[rowIndex].internationalFilesCount+addEraToNumber));
  }
  if(role == CheckRole)
    return QVariant::fromValue(BoolToString(m_eraListModel[rowIndex].checkValue));
  if(!isPositionValid(rowIndex))
    return QVariant {};
  return QVariant::fromValue(m_eraListModel[rowIndex].eraName);
}

bool EraListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  Q_UNUSED(value)
  /*
   * Cannot assign to return value because function 'operator[]' returns a const value
   * m_EraListModel[rowIndex].checkValue=false;

   * */
  if (index.isValid() && role == CheckRole) {
    int rowIndex=index.row();
    if(!isPositionValid(rowIndex))
      return false;
    m_eraListModel[rowIndex].checkValue=!m_eraListModel[rowIndex].checkValue;
    emit dataChanged(index,index,{CheckRole});
    return true;
  }
  return false;
}

bool EraListModel::removeRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent)
  if(count>0)
  {
    beginRemoveRows(QModelIndex(), row, count);
    m_eraListModel.erase(m_eraListModel.begin(),m_eraListModel.end());
    endRemoveRows();
  }
  return true;
}

bool EraListModel::insertRows(int row, int count, const QModelIndex &parent2)
{
  Q_UNUSED(parent2)

  if(count>0){
    beginInsertRows(QModelIndex(),0,count-1);
    m_eraListModel=m_fillingList;
    m_fillingList.clear();
    endInsertRows();
  }
  return true;
}



