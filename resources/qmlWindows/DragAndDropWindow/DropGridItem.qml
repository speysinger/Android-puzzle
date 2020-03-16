import QtQuick 2.0

Item{
    //id:_dropItem
    objectName: "dropItem"
    signal changeDroppedItemName()

    Rectangle{
        id:_imageRectangle
        objectName:"dropRectangle"
        anchors.fill: parent
        anchors.margins: Math.min(parent.width*0.05,parent.height*0.05)

        Image {
            id: _firstDropRectangle
            objectName:"dropImage"
            source: chooseRightPath(dropItemImageSource)
            width: _imageRectangle.width
            height: _imageRectangle.height
            opacity: 0.5
            antialiasing: true
            fillMode: Image.PreserveAspectCrop
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            states: [
                State {
                    when: _firstDragTarget.containsDrag
                    PropertyChanges {
                        target: _firstDropRectangle
                        source:_firstDropRectangle.source
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


