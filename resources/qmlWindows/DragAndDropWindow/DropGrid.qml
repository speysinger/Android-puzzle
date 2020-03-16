import QtQuick 2.0
import dropgridmodel 1.0

Rectangle {
    id:_dropGridRectangle
    color: "wheat"
    radius: Math.pow(_dropGridRectangle.height*0.0076,2)

    Connections{
        target: _nextButton
        onClicked:_dropModel.setNextDropQuad()
    }

    Connections{
        target: titles
        onNewQuestionsHaveEraType:{
            _dropGridContentType.text="Эпохи"
        }
    }

    Connections{
        target: titles
        onNewQuestionsHaveAuthorType:{
            _dropGridContentType.text="Авторы"
        }
    }

    GridView {
        id: _dropGrid
        anchors.fill: parent
        interactive: false
        cellWidth: _dropGridRectangle.width*0.5
        cellHeight: _dropGridRectangle.height*0.5
        Text {
            id: _dropGridContentType
            anchors.centerIn: _dropGrid
            text: " "
            font{
                pointSize:Math.min(_dropGrid.height===0?1:_dropGrid.height*0.04
                                   ,_dropGrid.width===0?1:_dropGrid.width*0.03)
            }
        }
        model: DropGridModel{
            id: _dropModel
        }

        delegate: DropGridItem{
            id:_dropGridItem
            width: _dropGrid.cellWidth
            height: _dropGrid.cellHeight
        }

    }
}
