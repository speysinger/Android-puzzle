import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

Rectangle {
  id:_testResultsWindow
  color: "transparent"
  property bool isTestResultsWindow: true


  Row {
    id: _tablesTitles
    anchors.top: parent.top
    anchors.topMargin: parent.height*0.01
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.leftMargin: parent.width*0.01
    anchors.bottomMargin: parent.height*0.2
    anchors.rightMargin: parent.width*0.01
    width: parent.width*0.98
    height: parent.height*0.07
    Rectangle {
      id:_questionTitle
      height: _tablesTitles.height
      width: _tablesTitles.width*0.45
      border.width: _questionTitle.height*0.03
      color:"khaki"
      Text{
        id: _questionText
        anchors.centerIn: _questionTitle
        anchors.verticalCenter: _questionTitle.verticalCenter
        text: "Вопрос"
        font {
          pointSize: Math.min(_questionTitle.width===0?3:_questionTitle.width,
                              _questionTitle.height===0?3:_questionTitle.height)/3
          bold:true
        }
      }
    }
    Rectangle{
      id:_answersTitle
      height: _tablesTitles.height
      width: _tablesTitles.width*0.55
      border.width: _answersTitle.height*0.03
      color:"khaki"
      Text{
        id: _answersText
        anchors.centerIn: _answersTitle
        anchors.verticalCenter: _answersTitle.verticalCenter
        text: "Ответ"
        font{
          pointSize: Math.min((_answersTitle.width===0?3:_answersTitle.width),
                              (_answersTitle.height===0?3:_answersTitle.height))/3
          bold:true
        }
      }
    }
  }


  EraListView {
    id: _eraListView
    anchors.top: _tablesTitles.bottom
    anchors.left: parent.left
    anchors.leftMargin: _testResultsWindow.width*0.01
    anchors.bottomMargin: _testResultsWindow.height*0.2
    anchors.rightMargin: _testResultsWindow.width*0.01
    width: _testResultsWindow.width*0.98
    height: _testResultsWindow.height*0.82
  }

  Button {
    id:_backToTestSettingsWindow
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.leftMargin: _testResultsWindow.width*0.05
    anchors.rightMargin: _testResultsWindow.width*0.05
    anchors.top: _eraListView.bottom
    anchors.topMargin: parent.height*0.005
    height: _testResultsWindow.height*0.09
    width: _testResultsWindow.width*0.9
    Text{
      anchors.centerIn: _backToTestSettingsWindow
      text: "Главное меню"
      font{
        pointSize: Math.min((_backToTestSettingsWindow.height===0?2:_backToTestSettingsWindow.height)
                            ,(_backToTestSettingsWindow.width===0?2:_backToTestSettingsWindow.width))/2
      }
    }

    background: Rectangle
    {
      color:_backToTestSettingsWindow.down? "lawngreen":"greenyellow"
      radius:_backToTestSettingsWindow.height
    }
    onClicked:{
      buttonsHandler.backButtonPressed()
    }
  }
}
