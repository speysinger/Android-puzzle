import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

import "../UpdateWindow"
import "../SupportingFiles"

Rectangle {
    id:_testSettingsWindow
    color: "transparent"

    signal notEnoughFilesToStartTesting();

    Connections {
        target: _testSettingsWindow
        onNotEnoughFilesToStartTesting:{
            _popUpNotification.visible=true;
            _popUpNotification.text = qsTr("Недостаточное количество\n файлов для тестирования")
        }
    }

    ChooseEpochType{
        id:_switchPanel
        width: _testSettingsWindow.width
    }

    EraList {
        id: _epochList
        anchors.top: _switchPanel.bottom
        anchors.topMargin: _testSettingsWindow.height*0.01
        anchors.left: parent.left
        anchors.leftMargin: _testSettingsWindow.width*0.05
        anchors.rightMargin: _testSettingsWindow.width*0.05
        width: _testSettingsWindow.width*0.9
        height: _testSettingsWindow.height*0.68
    }

    TabBar {
        id: _chooseNumberOfQuestions
        anchors.top: _epochList.bottom
        anchors.left: parent.left
        width: _testSettingsWindow.width*0.9
        height: _testSettingsWindow.height*0.04
        anchors.topMargin: _testSettingsWindow.height*0.02
        anchors.leftMargin: _testSettingsWindow.width*0.05
        anchors.rightMargin: _testSettingsWindow.width*0.05
        background: Rectangle{
            color:"lemonchiffon"
        }

        TabButton {
            id:_firstTabButton
            height: _testSettingsWindow.height*0.07
            Text{
                anchors.centerIn: _firstTabButton
                text: qsTr("5")
                font{
                    pointSize: Math.min(_firstTabButton.height===0?1:_firstTabButton.height
                                        ,_firstTabButton.width===0?1:_firstTabButton.height)/2.7
                }
            }

            background: Rectangle {
                color: _chooseNumberOfQuestions.currentIndex === 0? "orange":"lightgreen"
                border.color: "#26282a"
                border.width: _testSettingsWindow.height*0.003
                radius: _testSettingsWindow.height*0.04
            }
        }
        TabButton {
            id:_secondTabButton
            height: _testSettingsWindow.height*0.07
            Text{
                anchors.centerIn: _secondTabButton
                text: qsTr("10")
                font{
                    pointSize: Math.min(_secondTabButton.height===0?1:_secondTabButton.height
                                        ,_secondTabButton.width===0?1:_secondTabButton.height)/2.7
                }
            }
            background: Rectangle {
                color: _chooseNumberOfQuestions.currentIndex === 1? "orange":"lightgreen"
                border.color: "#26282a"
                border.width: _testSettingsWindow.height*0.003
                radius: _testSettingsWindow.height*0.04
            }
        }

        TabButton {
            id:_thirdTabButton
            height: _testSettingsWindow.height*0.07
            Text{
                anchors.centerIn: _thirdTabButton
                text: qsTr("15")
                font{
                    pointSize: Math.min(_thirdTabButton.height===0?1:_thirdTabButton.height
                                        ,_thirdTabButton.width===0?1:_thirdTabButton.height)/2.7
                }
            }
            background: Rectangle {
                color: _chooseNumberOfQuestions.currentIndex === 2? "orange":"lightgreen"
                border.color: "#26282a"
                border.width: _testSettingsWindow.height*0.003
                radius: _testSettingsWindow.height*0.04
            }
        }
    }

    Rectangle{
        id:_rowLayout
        color: "transparent"
        anchors.top: _chooseNumberOfQuestions.bottom
        anchors.topMargin: _testSettingsWindow.height*0.02
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: _testSettingsWindow.width*0.05
        anchors.rightMargin: _testSettingsWindow.width*0.05
        height: _testSettingsWindow.height*0.11
        width: _testSettingsWindow.width*0.90
        Button{
            id:_backButton
            anchors.left: _rowLayout.left
            width: _rowLayout.width*0.45
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.2
            anchors.bottom: parent.bottom
            height: _rowLayout.height*0.2
            Text{
                anchors.centerIn: _backButton
                text: qsTr("Назад")
                font{
                    pointSize: Math.min((_backButton.height===0?1:_backButton.height)
                                        ,(_backButton.width===0?1:_backButton.width))/2
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
            id:_loadImagesButton
            anchors.right: _rowLayout.right
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.2
            anchors.bottom: parent.bottom
            width: _rowLayout.width*0.45
            height: _rowLayout.height*0.2
            Text{
                anchors.centerIn: _loadImagesButton
                text: qsTr("Начать")
                font{
                    pointSize: Math.min((_loadImagesButton.height===0?1:_loadImagesButton.height),
                                        (_loadImagesButton.width===0?1:_loadImagesButton.width))/2
                }
            }
            background: Rectangle
            {
                color:_loadImagesButton.down? "lawngreen":"greenyellow"
                radius:_loadImagesButton.height
            }
            onClicked:{
                _epochList.chooseCorrectModelData("testSettings")
            }
        }
    }
    PopUpNotification{
        id:_popUpNotification

        Connections{
            target: _epochList
            onNothingIsSelected:
            {
                _popUpNotification.visible=true;
                _popUpNotification.text = qsTr("Недостаточное количество файлов\n для тестирования")
            }
        }
    }
}
