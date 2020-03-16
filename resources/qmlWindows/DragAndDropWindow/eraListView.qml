import QtQuick 2.7
import QtQuick.Controls 2.1
import TestingResultsModel 1.0;


Rectangle {
    id: _awaiting
    color: "lightgrey"
    border.color: "green"

    ListView {
        id: _listViewId
        anchors.fill: _eraListView
        /*anchors.topMargin: _eraListView.width*0.002//чтобы рамка не перекрывалась
        anchors.bottomMargin: _eraListView.width*0.004
        anchors.leftMargin: _eraListView.width*0.004
        anchors.rightMargin: _eraListView.width*0.004*/
        width: _eraListView.width
        height: _eraListView.height
        clip: true
        flickableDirection: Flickable.VerticalFlick
        boundsBehavior: Flickable.StopAtBounds

        model: TestingResultsModel {
            id:_listModel
        }
        delegate: EraListItemResults {
            height: _eraListView.height*0.2
            width: _eraListView.width
        }
        focus: true
        ScrollBar.vertical: ScrollBar {}
    }

}



