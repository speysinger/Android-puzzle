import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import SortFilter 1.0
import StatisticModel 1.0

Rectangle {
    id: window
    color: "lemonchiffon"
    signal loadData()

    ToolBar {
        id:_toolBar
        anchors.top: parent.top
        style: ToolBarStyle {
            background:Rectangle {
                color: "lemonchiffon"
            }
        }
        height: parent.height*0.08

        TabBar {
            id: _chooseNumberOfQuestions
            anchors.top: parent.top
            anchors.left: parent.left
            width: window.width*0.6
            height: _toolBar.height*0.92
            background: Rectangle {
                color:"lemonchiffon"
            }
            signal anyButtonPressed(string buttonText)

            TabButton {
                id:_firstTabButton
                height: _chooseNumberOfQuestions.height
                onClicked: _chooseNumberOfQuestions.anyButtonPressed(_firstTabButtonText.text)
                Text {
                    id:_firstTabButtonText
                    anchors.centerIn: _firstTabButton
                    text: qsTr("3x3")
                    font{
                        pointSize: Math.min(_firstTabButton.height===0?1:_firstTabButton.height
                                            ,_firstTabButton.width===0?1:_firstTabButton.height)/2.7
                    }
                }

                background: Rectangle {
                    color: _chooseNumberOfQuestions.currentIndex === 0? "orange":"lightgreen"
                    border.color: "#26282a"
                    border.width: window.height*0.003
                    radius: window.height*0.04
                }
            }
            TabButton {
                id:_secondTabButton
                height: _chooseNumberOfQuestions.height
                onClicked: _chooseNumberOfQuestions.anyButtonPressed(_secondTabButtonText.text)
                Text {
                    id:_secondTabButtonText
                    anchors.centerIn: _secondTabButton
                    text: qsTr("5x5")
                    font{
                        pointSize: Math.min(_secondTabButton.height===0?1:_secondTabButton.height
                                            ,_secondTabButton.width===0?1:_secondTabButton.height)/2.7
                    }
                }
                background: Rectangle {
                    color: _chooseNumberOfQuestions.currentIndex === 1? "orange":"lightgreen"
                    border.color: "#26282a"
                    border.width: window.height*0.003
                    radius: window.height*0.04
                }
            }

            TabButton {
                id:_thirdTabButton
                height: _chooseNumberOfQuestions.height
                onClicked: _chooseNumberOfQuestions.anyButtonPressed(_thirdTabButtonText.text)
                Text{
                    id:_thirdTabButtonText
                    anchors.centerIn: _thirdTabButton
                    text: qsTr("7x7")
                    font{
                        pointSize: Math.min(_thirdTabButton.height===0?1:_thirdTabButton.height
                                            ,_thirdTabButton.width===0?1:_thirdTabButton.height)/2.7
                    }

                }
                background: Rectangle {
                    color: _chooseNumberOfQuestions.currentIndex === 2? "orange":"lightgreen"
                    border.color: "#26282a"
                    border.width: window.height*0.003
                    radius: window.height*0.04
                }
            }

            TabButton {
                id:_fourthTabButton
                height: _chooseNumberOfQuestions.height
                onClicked: _chooseNumberOfQuestions.anyButtonPressed(_fourthTabButtonText.text)
                Text {
                    id:_fourthTabButtonText
                    anchors.centerIn: _fourthTabButton
                    text: qsTr("9x9")
                    font{
                        pointSize: Math.min(_fourthTabButton.height===0?1:_fourthTabButton.height,
                                            _fourthTabButton.width===0?1:_fourthTabButton.height)/2.7
                    }
                }
                background: Rectangle {
                    color: _chooseNumberOfQuestions.currentIndex === 3? "orange":"lightgreen"
                    border.color: "#26282a"
                    border.width: window.height*0.003
                    radius: window.height*0.04
                }
            }
        }

        TextField {
            id: searchBox
            height: _chooseNumberOfQuestions.height
            placeholderText: "Поиск..."
            font.pointSize: _toolBar.height*0.7

            inputMethodHints: Qt.ImhNoPredictiveText

            width: window.width / 5 * 1.5
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    StatisticTable {
        id:_statisticTable
        anchors.top: _toolBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height*0.8
    }

    Button {
        id:_backButton
        anchors.left: parent.left
        anchors.right: parent.right
        width: parent.width*0.45
        anchors.top: _statisticTable.bottom
        anchors.topMargin: parent.height*0.02
        anchors.leftMargin: parent.width*0.05
        anchors.rightMargin: parent.width*0.05
        height: parent.height*0.08
        Text {
            anchors.centerIn: _backButton
            text: qsTr("Назад")
            font{
                pointSize: Math.min((_backButton.height===0?1:_backButton.height)
                                    ,(_backButton.width===0?1:_backButton.width))/2
            }
        }
        style: ButtonStyle {
            background: Rectangle {
                color:_backButton.down? "red":"orangered"
                radius:_backButton.height
            }
        }
        onClicked: buttonsHandler.backButtonPressed()

    }
}
