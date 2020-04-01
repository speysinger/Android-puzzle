import QtQuick 2.0

Item {
    id:_listViewResultsItem
    Rectangle {
        id:_firstColumnId
        width: _listViewResultsItem.width*0.45
        height: _listViewResultsItem.height
        anchors.left: _listViewResultsItem.left
        color: "palegoldenrod"
        border.width: _firstColumnId.height*0.01
        Text {
            id: _firstText
            anchors.fill: _firstColumnId
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            width: _firstColumnId.width
            text: question
            font {
                pointSize: Math.min(_listViewResultsItem.width===0?1:_listViewResultsItem.width,
                                    _listViewResultsItem.height===0?1:_listViewResultsItem.height)/9
                bold:true
            }
            wrapMode: Text.WrapAnywhere
        }
    }
    Rectangle {
        id:_secondColumnItem
        width: _listViewResultsItem.width*0.55
        height: _listViewResultsItem.height
        anchors.top: parent.top
        anchors.right: _listViewResultsItem.right
        anchors.left: _firstColumnId.right
        color: userAnswer===correctAnswer?"lightgreen":"crimson"
        border.width: _secondColumnItem.height*0.015

        Rectangle {
            id:_userAnswerTextWrapper
            width: _secondColumnItem.width
            height: _secondColumnItem.height/2
            anchors.top: _secondColumnItem.top
            anchors.left: _secondColumnItem.left
            border.width: _userAnswerTextWrapper.height*0.01
            border.color: "black"
            color: _secondColumnItem.color

            Text {
                id:_userAnswerText
                width: _userAnswerTextWrapper.width*0.9
                anchors.verticalCenter: _userAnswerTextWrapper.verticalCenter
                //leftPadding: _userAnswerTextWrapper.width*0.01
                text: "Ваш ответ: "+userAnswer
                font{
                    pointSize: Math.min(_userAnswerTextWrapper.width===0?1:_userAnswerTextWrapper.width,
                                        _userAnswerTextWrapper.height===0?1:_userAnswerTextWrapper.height)/5
                    bold:true
                }
                wrapMode: Text.WrapAnywhere
            }
        }

        Rectangle {
            id:_correctAnswerTextWrapper
            width: _secondColumnItem.width
            anchors.top: _userAnswerTextWrapper.bottom
            anchors.bottom:_secondColumnItem.bottom
            anchors.left: _secondColumnItem.left

            border.width: _correctAnswerTextWrapper.height*0.015
            border.color: "black"
            color: _secondColumnItem.color
            Text {
                id:_correctAnswerText
                width: _correctAnswerTextWrapper.width
                anchors.verticalCenter: _correctAnswerTextWrapper.verticalCenter
                text:"Правильный ответ: "+correctAnswer
                font {
                    pointSize: Math.min(_correctAnswerTextWrapper.width===0?1:_correctAnswerTextWrapper.width,
                                        _correctAnswerTextWrapper.height===0?1:_correctAnswerTextWrapper.height)/5
                    bold:true
                }
                wrapMode: Text.WrapAnywhere
            }
        }
    }
}
