import QtQuick 2.7
import QtQuick.Controls 2.1
import TestingResultsModel 1.0;
import "../SupportingFiles"

Rectangle {
    id: _awaiting
    color: "lightgrey"
    border.color: "green"

    DataListView {
       id: _listViewId
       model: TestingResultsModel {
           id:_listModel
       }
       delegate: EraListItemResults {
           height: _eraListView.height*0.2
           width: _eraListView.width
       }
    }
}



