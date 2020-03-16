import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4

Item {
    id:_currentItem
    Rectangle {
        id:_firstColumnId
        width: _currentItem.width*0.8
        height: _currentItem.height
        anchors.left: _currentItem.left
        Text {
            id: _firstText
            anchors.verticalCenter: _firstColumnId.verticalCenter
            text: _listModel.isTestingModule_?(eraName):(eraName + ' Файлов '+ filesCount)
            font{
                pointSize: Math.min(_currentItem.width===0?6:_currentItem.width,
                                    _currentItem.height===0?6:_currentItem.height)/6
                bold:true
            }
        }
    }
    Rectangle
    {
        id:_secondColumnItem

        width: _currentItem.width*0.2
        height: _currentItem.height
        anchors.right: _currentItem.right
        CheckBox {
            id: control
            checked: checkValue==="false" ? false:true
            anchors.right: _secondColumnItem.right
            anchors.rightMargin: _secondColumnItem.width*0.05

            indicator: Rectangle {
                anchors.top: control.top
                anchors.topMargin: _secondColumnItem.height*0.05
                implicitWidth: _secondColumnItem.width>_secondColumnItem.height? _secondColumnItem.height*0.8:_secondColumnItem.width*0.8
                implicitHeight: _secondColumnItem.width>_secondColumnItem.height? _secondColumnItem.height*0.8:_secondColumnItem.width*0.8
                x: control.leftPadding
                y: _secondColumnItem.height / 2.3 - _secondColumnItem / 2.3
                border.color: "green"

                Rectangle {
                    width: _secondColumnItem.width>_secondColumnItem.height? _secondColumnItem.height*0.8:_secondColumnItem.width*0.8
                    height:_secondColumnItem.width>_secondColumnItem.height? _secondColumnItem.height*0.8:_secondColumnItem.width*0.8
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
