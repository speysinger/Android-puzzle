import QtQuick 2.7
import QtQuick.Controls 2.1
import EraListModel 1.0;

ListView {
    id: _listViewId
    anchors.fill: parent
    anchors.topMargin: parent.width*0.002
    anchors.bottomMargin: parent.width*0.004
    anchors.leftMargin: parent.width*0.004
    anchors.rightMargin: parent.width*0.004
    width: parent.width
    height: parent.height
    clip: true
    flickableDirection: Flickable.VerticalFlick
    boundsBehavior: Flickable.StopAtBounds

    focus: true
    ScrollBar.vertical: ScrollBar {}
}




