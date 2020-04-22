import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.13

Item {
  id:_currentItem
  property string fontFamlily: "hAndy"
  Rectangle {
    id:_firstColumnId
    width: _currentItem.width*0.6
    height: _currentItem.height
    anchors.left: _currentItem.left
    Text {
      id: _firstText
      anchors.verticalCenter: _firstColumnId.verticalCenter
      text: eraName
      font {
          family: fontFamlily
        pointSize: Math.min(_currentItem.width===0?6:_currentItem.width,
                            _currentItem.height===0?6:_currentItem.height)/6.7
        bold:true
      }
      wrapMode: Text.WrapAnywhere
    }
  }
  Rectangle {
    id: _countColumnId
    width: _currentItem.width*0.3
    height: _currentItem.height
    anchors.right: _secondColumnItem.left
    Text {
      id: _countText
      anchors.verticalCenter: _countColumnId.verticalCenter
      text: _listModel.isTestingModule()?(""):(' Файлов '+ filesCount)
      font {
          family: fontFamlily
        pointSize: Math.min(_currentItem.width===0?6:_currentItem.width,
                            _currentItem.height===0?6:_currentItem.height)/6.7
        bold:true
      }
      wrapMode: Text.WrapAnywhere
    }

  }

  Rectangle
  {
    id:_secondColumnItem

    width: _currentItem.width*0.1
    height: _currentItem.height
    anchors.right: _currentItem.right
    CheckBox {
      id: control
      checked: checkValue==="false" ? false:true
      anchors.right: _secondColumnItem.right
      anchors.rightMargin: _secondColumnItem.width*0.03

      indicator: Rectangle {
        anchors.top: control.top
        anchors.topMargin: _secondColumnItem.height*0.05
        implicitWidth: _secondColumnItem.width>_secondColumnItem.height? _secondColumnItem.height*0.9:_secondColumnItem.width*0.9
        implicitHeight: _secondColumnItem.width>_secondColumnItem.height? _secondColumnItem.height*0.9:_secondColumnItem.width*0.9
        x: control.leftPadding
        y: _secondColumnItem.height / 2.3 - _secondColumnItem / 2.3
        border.color: "green"

        Rectangle {
          width: _secondColumnItem.width>_secondColumnItem.height? _secondColumnItem.height*0.9:_secondColumnItem.width*0.9
          height:_secondColumnItem.width>_secondColumnItem.height? _secondColumnItem.height*0.9:_secondColumnItem.width*0.9
          color: control.down ? "white" : "green"
          visible: control.checked
        }
      }
      onClicked:
          //259=UserRole+1
          _listModel.setData(_listModel.index(index,0),false,259)
    }
  }
}
