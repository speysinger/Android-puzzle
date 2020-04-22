import QtQuick 2.13
import QtQuick.Controls 2.5

import "../SupportingFiles"

Rectangle {
  id:_updateWindow
  color: "transparent"
  property string fontFamlily: "hAndy"
  signal updateModuleLoadButtonPressed()

  ChooseEpochType {
    id:_switchPanel
    width: _updateWindow.width
  }

  EraList {
    id: _epochList
    anchors.top: _switchPanel.bottom
    anchors.topMargin: _updateWindow.width*0.03
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.leftMargin: _updateWindow.width*0.05
    anchors.bottomMargin: _updateWindow.height*0.15
    anchors.rightMargin: _updateWindow.width*0.05
    width: _updateWindow.width*0.9
    height: _updateWindow.height*0.88
  }

  Rectangle {
    id:_rowLayout
    color: "transparent"
    anchors.top: _epochList.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.leftMargin: _updateWindow.width*0.05
    anchors.rightMargin: _updateWindow.width*0.05
    height: _updateWindow.height*0.11
    width: _updateWindow.width*0.90
    Button {
      id:_backButton
      anchors.right: _rowLayout.right
      width: _rowLayout.width*0.45
      anchors.top: parent.top
      anchors.topMargin: parent.height*0.2
      anchors.bottom: parent.bottom
      height: _rowLayout.height*0.2
      Text {
        anchors.centerIn: _backButton
        text: qsTr("Назад")
        font{
            family: fontFamlily
          pointSize: Math.min((_backButton.height===0?1:_backButton.height/4.3)
                              ,(_backButton.width===0?1:_backButton.width/2))
        }
      }
      background: Rectangle
      {
        color:_backButton.down? "red":"orangered"
        radius:_backButton.height
      }
      onClicked: buttonsHandler.backButtonPressed()

    }

    Button {
      id: _loadImagesButton
      anchors.left: _rowLayout.left
      anchors.top: parent.top
      anchors.topMargin: parent.height*0.2
      anchors.bottom: parent.bottom
      width: _rowLayout.width*0.45
      height: _rowLayout.height*0.2
      Text {
        anchors.centerIn: _loadImagesButton
        text: qsTr("Загрузить")
        font{
            family: fontFamlily
          pointSize: Math.min((_loadImagesButton.height===0?1:_loadImagesButton.height/4.3)
                              ,(_loadImagesButton.width===0?1:_loadImagesButton.width/2))
        }
      }
      background: Rectangle
      {
        color: _loadImagesButton.down? "lawngreen":"greenyellow"
        radius: _loadImagesButton.height
      }
      onClicked: {
        _epochList.chooseCorrectModelData("updateWindow");
      }

      Connections {
        target: _epochList
        onSomethingSelected: buttonsHandler.loadButtonPressed()
      }
    }
  }
  PopUpNotification {
    id: _popUpNotification

    Connections {
      target: _epochList
      onNothingIsSelected:
      {
        _popUpNotification.visible = true;
        _popUpNotification.text = qsTr("Список обновления пуст")
      }
    }
  }
}
