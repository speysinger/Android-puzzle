import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4

Row{
  id: root
  anchors.top: parent.top
  anchors.topMargin: parent.height*0.01
  anchors.left: parent.left
  anchors.right: parent.right
  leftPadding: parent.width*0.07
  width: parent.width
  height: parent.height*0.1
  spacing: parent.width*0.01
  signal activated(bool firstSwitchChecked,bool secondSwitchChecked)

  Connections{
    target:_backButton
    onClicked:
    {
      _firstSwitch.checked=false;
      _secondSwitch.checked=false;
    }
  }

  Connections{
    target: _epochList
    onListLoading:
    {
      _firstSwitch.checked=false;
      _secondSwitch.checked=false;
    }
  }

  Rectangle{
    id:_firstSwitchTextWrapper
    width: root.width*0.3
    height: root.height
    color:"transparent"
    Text {
      anchors.centerIn: _firstSwitchTextWrapper
      text: qsTr("Отечественное")
      font{
        pointSize: Math.min((_firstSwitchTextWrapper.height===0?1:_firstSwitchTextWrapper.height*0.4),
                            (_firstSwitchTextWrapper.width===0?1:_firstSwitchTextWrapper.width*0.1))
      }
      verticalAlignment: Text.AlignVCenter
    }
  }

  Rectangle{
    id:_firstSwitchWrapper
    width: root.width*0.1
    height: root.height
    color:"transparent"

    Switch {
      id: _firstSwitch
      //text: qsTr("Switch")
      anchors.centerIn: _firstSwitchWrapper
      width: _firstSwitchWrapper.width*0.95
      height: _firstSwitchTextWrapper.height/2

      Connections{
        target: _firstSwitch
        onClicked: root.activated(_firstSwitch.checked,_secondSwitch.checked)
      }

      indicator: Rectangle {
        width: _firstSwitch.width
        height: _firstSwitch.height
        radius: Math.pow(_firstSwitchWrapper.height*0.1376,2)
        color: _firstSwitch.checked ? "#17a81a" : "#ffffff"
        border.color: _firstSwitch.checked ? "#17a81a" : "#cccccc"

        Rectangle {
          x: _firstSwitch.checked ? parent.width - width : 0
          width: _firstSwitch.width*0.3
          height: _firstSwitch.height
          radius: Math.pow(_firstSwitch.height*0.1376,2)
          color: _firstSwitch.down ? "#cccccc" : "#ffffff"
          border.color: _firstSwitch.checked ? (_firstSwitch.down ? "#17a81a" : "#21be2b") : "#999999"
        }
      }
    }


  }
  Rectangle{
    id:_secondSwitchWrapper
    width: root.width*0.1
    height: root.height
    color:"transparent"

    Switch {
      id: _secondSwitch
      //text: qsTr("Switch")
      anchors.centerIn: _secondSwitchWrapper
      width: _secondSwitchWrapper.width*0.95
      height:_secondSwitchWrapper.height/2

      Connections{
        target: _secondSwitch
        onClicked: root.activated(_firstSwitch.checked,_secondSwitch.checked)
      }

      indicator: Rectangle {
        width: _secondSwitch.width
        height: _secondSwitch.height
        radius: Math.pow(_secondSwitchWrapper.height*0.1376,2)
        color: _secondSwitch.checked ? "#17a81a" : "#ffffff"
        border.color: _secondSwitch.checked ? "#17a81a" : "#cccccc"

        Rectangle {
          x: _secondSwitch.checked ? parent.width - width : 0
          width: _secondSwitch.width*0.3
          height: _secondSwitch.height
          radius: Math.pow(_secondSwitch.height*0.1376,2)
          color: _secondSwitch.down ? "#cccccc" : "#ffffff"
          border.color: _secondSwitch.checked ? (_secondSwitch.down ? "#17a81a" : "#21be2b") : "#999999"
        }
      }
    }
  }

  Rectangle{
    id:_secondSwitchTextWrapper
    width: root.width*0.3
    height: root.height
    color:"transparent"

    Text {
      anchors.centerIn: _secondSwitchTextWrapper
      text: qsTr("Зарубежное")
      font{
        pointSize: Math.min((_secondSwitchTextWrapper.height===0?1:_secondSwitchTextWrapper.height*0.4),
                            (_secondSwitchTextWrapper.width===0?1:_secondSwitchTextWrapper.width*0.1))
      }
      verticalAlignment: Text.AlignVCenter
    }
  }
}
