import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.1

Rectangle {
    id:_testWindow
    color:"lemonchiffon"
    Connections{
        target: titles
        onNewQuestionsHaveEraType:{
            _taskText.text="Соотнесите картины с эпохами";
        }
    }

    Connections{
        target: titles
        onNewQuestionsHaveAuthorType:{
            _taskText.text="Соотнесите картины с авторами";
        }
    }

    Rectangle{
        id:_taskTextContainer
        height: _testWindow.height*0.04
        width: _testWindow.width
        anchors.top: _testWindow.top
        color: _testWindow.color
        Text {
            id: _taskText
            anchors.centerIn: _taskTextContainer
            text: " "//titles.isEraQuestions?titles.getEraTitle():titles.getArtTitle()
            font{
                pointSize:Math.min(_taskTextContainer.height===0?1:_taskTextContainer.height/2,
                                   _taskTextContainer.width===0?1:_taskTextContainer.width*0.03)
            }
            verticalAlignment: Text.AlignVCenter
        }
    }
    function chooseRightPath(path)
    {
        //если путь начинается с :, значит он из ресурсов и нужно подняться на 2 каталога выше текущего
        if(path[0]===":")
        {
            return "../../"+path.substring(2);
        }
        else
        {
            return "file:///"+path;
        }
    }

    DragGrid{
        id: _dADGrid
        width: (_testWindow.width/2)-_testWindow.width*0.005
        height: _testWindow.height*0.89
        anchors.top: _taskTextContainer.bottom
        anchors.left: parent.left
    }
    DropGrid{
        id:_dropGrid
        width: (_testWindow.width/2)-_testWindow.width*0.005
        height: _testWindow.height*0.89
        anchors.right: parent.right
        anchors.top: _taskTextContainer.bottom
    }
    //Контейнер хранит drag Item при его переносе, для наложения поверх всех элементов
    //а не под ними
    Item{
        id:_dragContainer
        width: _dropGrid.width*0.45
        height: _dropGrid.height*0.45
    }

    Button {
        id:_nextButton
        anchors.bottom:parent.bottom
        anchors.right: parent.right
        width: _testWindow.width*0.9
        height: _testWindow.height*0.06
        anchors.rightMargin: _testWindow.width*0.05
        Text{
            anchors.centerIn: _nextButton
            text: qsTr("Далее")
            font{
                pointSize: Math.min(_nextButton.height===0?1:_nextButton.height
                                    ,_nextButton.width===0?1:_nextButton.width)/2
            }
        }
        background: Rectangle
        {
            color:_nextButton.down? "lawngreen":"greenyellow"
            radius:_nextButton.height
        }
    }
}

