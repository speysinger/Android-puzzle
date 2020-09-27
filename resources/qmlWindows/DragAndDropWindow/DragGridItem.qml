import QtQuick 2.7

Item {
  id: root
  property string typeKey: itemType

  Rectangle {
    id: _imageRectangle
    anchors.fill: parent
    anchors.margins: Math.min(root.height * 0.05, root.width * 0.05)
    border {
      color: "green"
      width: Math.min(root.height === 0 ? 1 : root.height * 0.005,
                      root.width === 0 ? 1 : root.width * 0.005)
    }
    MouseArea {
      id: mouseArea
      width: _imageRectangle.width
      height: _imageRectangle.height
      anchors.centerIn: parent
      property Item dropObject: null
      drag.target: _dragImage
      Image {
        id: _dragImage
        source: chooseRightPath(dragItemImageSource)
        property string name: dragItemImageSource
        property bool caught: false
        width: parent.width
        height: parent.height
        antialiasing: true
        fillMode: Image.PreserveAspectCrop
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        Drag.keys: [typeKey]
        Drag.active: mouseArea.drag.active
        Drag.hotSpot.x: 32
        Drag.hotSpot.y: 32
        states: State {
          when: mouseArea.drag.active
          ParentChange {
            target: _dragImage
            parent: _dragContainer
          }
          AnchorChanges {
            target: _dragImage
            anchors.horizontalCenter: undefined
            anchors.verticalCenter: undefined
          }
        }
      }

      onReleased: {
        //parent = _dragImage.Drag.target !== null ? (_dragImage.Drag.target) : root
        if (dropObject === null) //айтем нигде не был
        {
          if (_dragImage.Drag.target.objectName === "DropArea") {
            //console.log(_dragImage.Drag.target.isBusy)
            if (!_dragImage.Drag.target.isBusy) //если перемещаем в дроп и он свободен
            {
              dropObject = _dragImage.Drag.target //запомнили, что находимся в конкретном дропе
              parent = _dragImage.Drag.target //переместили в дроп
              _dragImage.Drag.drop() //сигнал дропа, теперь ячейка занята
              dropObject.changeDroppedItemName(dragItemName)
            } else
              parent = root //Дроп занят, значит вернулись
          } else
            parent = root //Дроп занят, значит вернулись или перемещают не в дроп, то вернуть на место
        } else {
          if (_dragImage.Drag.target === null) //если по нему кликнули или потащили назад в его грид
          {
            dropObject.isBusy = false
            dropObject = null
            parent = root
          } else //если его перетаскивают в другой дроп
          {
            if (!_dragImage.Drag.target.isBusy) //он свободен
            {
              dropObject.isBusy = false //текущий освободили
              _dragImage.Drag.target.isBusy = true //следующий заняли
              dropObject = _dragImage.Drag.target //запомнили где будем находиться
              parent = _dragImage.Drag.target
              dropObject.changeDroppedItemName(dragItemName)
            }
          }
        }
      }
    }
  }
}
