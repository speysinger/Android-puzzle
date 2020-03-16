import QtQuick 2.0
import draggridmodel 1.0

Rectangle {
    id:_dragGridRectangle
    color: "lightsalmon"
    radius: Math.pow(_dragGridRectangle.height*0.0076,2)

    GridView {
        id: _dragGrid
        anchors.fill: parent
        interactive: false
        cellWidth: _dragGridRectangle.width*0.5
        cellHeight: _dragGridRectangle.height*0.5
        Text {
            id: _dragGridContentType
            anchors.centerIn: _dragGrid
            text: "Картины"
            font{
                pointSize:Math.min(_dragGrid.height===0?1:_dragGrid.height*0.04,
                                   _dragGrid.width===0?1:_dragGrid.width*0.03)
            }
        }

        model: DragGridModel{
            id: _dragModel
        }

        delegate: DragGridItem{
            width: _dragGrid.cellWidth
            height: _dragGrid.cellHeight
        }
    }
}
