import QtQuick 2.0

Item{
  //id:_dropItem
  objectName: "dropItem"
  width: parent.width
  height: parent.height
  signal changeDroppedItemName()

  Rectangle{
    id:_imageRectangle
    objectName:"dropRectangle"
    anchors.fill: parent
    anchors.margins: Math.min(parent.width*0.05,parent.height*0.05)

    Text {
      id: _firstTextDropRectangle
      text: dropItemName
      anchors.centerIn: _imageRectangle
      objectName:"dropImage"
      anchors.fill: parent
      // width: _imageRectangle.width
      //height: _imageRectangle.height
      opacity: 0.5
      font.pointSize: Math.min(_firstTextDropRectangle.width===0? 1 : _firstTextDropRectangle.width/5,
                               _firstTextDropRectangle.height===0? 1: _firstTextDropRectangle.height/8)
      antialiasing: true
      wrapMode: Text.WrapAnywhere
      horizontalAlignment: Text.AlignHCenter
      verticalAlignment: Text.AlignVCenter
      //anchors.horizontalCenter: parent.horizontalCenter
      //anchors.verticalCenter: parent.verticalCenter
      states: [
        State {
          when: _firstDragTarget.containsDrag
          PropertyChanges {
            target: _firstTextDropRectangle
            opacity:0.03
          }
        }
      ]
    }
  }
  DropArea {
    id: _firstDragTarget
    objectName:"DropArea"
    property string typeKey:itemType
    property alias dropProxy: _firstDragTarget
    property bool isBusy:false

    function changeDroppedItemName(droppedItemName){
      _dropModel.setData(_dropModel.index(index,0),droppedItemName,260)
    }

    anchors.fill: parent
    onDropped: {
      isBusy=true
    }
    keys: [typeKey]
  }
}


