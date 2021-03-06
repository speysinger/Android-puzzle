import QtQuick 2.0

Item{
  //id:_dropItem
  objectName: "dropItem"
  width: parent.width
  height: parent.height
  signal changeDroppedItemName()
  property string fontFamlily: "hAndy"

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
      opacity: 0.5
      font.family: fontFamlily
      font.pointSize: Math.min(_firstTextDropRectangle.width===0? 1 : _firstTextDropRectangle.width/12,
                               _firstTextDropRectangle.height===0? 1: _firstTextDropRectangle.height/16)
      antialiasing: true
      elide: Text.ElideRight
      wrapMode: Text.WordWrap
      horizontalAlignment: Text.AlignHCenter
      verticalAlignment: Text.AlignVCenter
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


