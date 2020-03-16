import QtQuick 2.7
import QtQuick.Controls 2.1
import EraListModel 1.0;

Rectangle {
    id:_awaiting
    color: "lightgrey"
    border.color: "green"
    property var isTesting:false
    property var isTestingResultsWindow:false

    signal listLoading();
    signal nothingIsSelected()
    signal somethingSelected()

    Connections {
        target: _listModel
        onNothingIsSelected: nothingIsSelected()
    }

    Connections {
        target: _listModel
        onSomethingSelected: somethingSelected()
    }

    Connections{
        target: _listModel
        onListModelReady: _awaiting.color="white"
    }

    Connections{
        target: _listModel
        onItTestingModule: isTesting=true
    }

    Connections{
        target: _listModel
        onNotTestingModule: isTesting=false
    }

    Connections{
        target:_backButton
        onClicked:{
            _listModel.clearList();
            _awaiting.color="lightgrey";
        }
    }

    Connections{
        target: _listModel
        onListViewWindowOpened:{
            _awaiting.color="lightgrey";
            _epochList.listLoading();
        }
    }


    function chooseCorrectModelData(callerName){
        if(callerName==="testSettings")
            _listModel.getSelectedElements(true, _chooseNumberOfQuestions.currentIndex);
        else
            _listModel.getSelectedElements(false,-1)
    }

    ListView {
        id: _listViewId
        anchors.fill: _epochList
        anchors.topMargin: _epochList.width*0.002
        anchors.bottomMargin: _epochList.width*0.004
        anchors.leftMargin: _epochList.width*0.004
        anchors.rightMargin: _epochList.width*0.004
        width:_epochList.width
        height: _epochList.height
        clip: true
        flickableDirection: Flickable.VerticalFlick
        boundsBehavior: Flickable.StopAtBounds

        model: EraListModel{
            id:_listModel
        }

        delegate: EpochListItem {
            height: _epochList.height*0.2
            width: _epochList.width
        }

        focus: true
        ScrollBar.vertical: ScrollBar {}

        Connections{
            target: _switchPanel
            onActivated: _listModel.changeListOfTheSelectedEpoch(firstSwitchChecked,secondSwitchChecked)
        }
    }

}



