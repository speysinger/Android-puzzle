import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4
Rectangle {
    id:_progressBarWindow
    width: Screen.width/4
    height: Screen.height/4
    color:"lemonchiffon"
    Connections {
        target: progressInd
        onProgressChanged: _progressBar.value = progress
    }

    Connections
    {
        target: progressInd
        onBack: _progressBar.value=0
    }

    ProgressBarImagesFromServer
    {
        id:_progressBar
        maximumValue: 100
        minimumValue: 0
        value: 0
        Text {
            id: name
            text: _progressBar.value+"/100%"
            font{
                pointSize: Math.min(_progressBarWindow.width===0?1:_progressBarWindow.width,
                                    _progressBarWindow.height===0?1:_progressBarWindow.height)/15
            }

            anchors.centerIn: _progressBar
        }
        x:(_progressBarWindow.width / 2 - width / 2);
        y:(_progressBarWindow.height / 2 - height / 1.2);
        width: _progressBarWindow.width*0.9
        height: _progressBarWindow.height*0.2
        anchors.left: parent.left
        anchors.leftMargin: _progressBarWindow.width*0.05
        anchors.rightMargin: _progressBarWindow.width*0.05
    }
    Button {
        id:_cancelButton
        anchors.top: _progressBar.bottom
        anchors.left: parent.left
        width: _progressBarWindow.width*0.9
        height: _progressBarWindow.height*0.15
        anchors.topMargin: _progressBarWindow.height*0.02
        anchors.leftMargin: _progressBarWindow.width*0.05
        anchors.rightMargin: _progressBarWindow.width*0.05
        Text {
            anchors.centerIn: _cancelButton
            text: qsTr("Отмена")
            font {
                pointSize: Math.min(_progressBarWindow.width===0?1:_progressBarWindow.width,
                                    _progressBarWindow.height===0?1:_progressBarWindow.width)/15
            }
        }
        style: ButtonStyle{ background: Rectangle
            {
                color:_cancelButton.down? "red":"orangered"
                radius:_cancelButton.height
            }
        }
        onClicked: progressInd.stopLoad()
    }
}
