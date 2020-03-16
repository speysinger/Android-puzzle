import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import SortFilter 1.0
import StatisticModel 1.0

TableView {
    id: tableView
    frameVisible: false
    sortIndicatorVisible: true

    Connections  {
        target: _chooseNumberOfQuestions
        onAnyButtonPressed: sourceModel.modeChanged(buttonText)
    }

    TableViewColumn {
        id: _eraColumn
        title: "Эпоха"
        role: "eraName"
        movable: false
        resizable: false
        width:  tableView.viewport.width / tableView.columnCount
    }

    TableViewColumn {
        id: _assembledPuzzleArtsColumn
        title: "Завершено"
        role: "assembledPuzzleArts"
        movable: false
        resizable: false
        width:  tableView.viewport.width / tableView.columnCount
    }

    TableViewColumn {
        id: _worstTimeColumn
        title: "Худшее время"
        role: "worstTime"
        movable: false
        resizable: false
        width:  tableView.viewport.width / tableView.columnCount
    }

    TableViewColumn {
        id: _bestTimeColumn
        title: "Лучшее время"
        role: "bestTime"
        movable: false
        resizable: false
        width:  tableView.viewport.width / tableView.columnCount
    }

    itemDelegate: Item {
        id: _rowItem
        Text {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            color: "black"
            elide: Text.ElideRight
            text: styleData.value
            font.pixelSize: Math.min(_rowItem.width===0?1:_rowItem.width/3,
                                     _rowItem.height===0?1:_rowItem.height/3)
            wrapMode: Text.WrapAnywhere
        }
        Rectangle {
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            //anchors.bottomMargin: 1
            //anchors.topMargin: 1
            width: _rowItem.width*0.015
            color: "#ccc"
        }
    }

    rowDelegate: Rectangle {
        height: tableView.height*0.15
        SystemPalette {
            id: myPalette;
            colorGroup: SystemPalette.Active
        }
        color: {
            var baseColor = styleData.alternate?myPalette.alternateBase:myPalette.base
            return styleData.selected?myPalette.highlight:baseColor
        }
    }
    style: TableViewStyle {
        alternateBackgroundColor: "white"
        headerDelegate: Rectangle {
            id: _header
            height: tableView.height * 0.11
            width:  tableView.viewport.width / tableView.columnCount
            color: "lightsteelblue"
            //текст заголовка
            Text {
                id: textItem
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: styleData.value
                font.pointSize: Math.min(_header.width===0?1:_header.width/3,
                                         _header.height===0?1:_header.height/3)
                //elide: Text.ElideRight
                color: textColor
                renderType: Text.NativeRendering
                wrapMode: Text.WrapAnywhere
            }
            //разделительная линия
            Rectangle {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                //anchors.bottomMargin: 1
                //anchors.topMargin: 1
                width: _header.width*0.015
                color: "#ccc"
            }
        }
    }

    model:
        SortFilterProxyModel {
        id: proxyModel
        source: sourceModel.count() > 0 ? sourceModel : null

        sortOrder: tableView.sortIndicatorOrder
        sortCaseSensitivity: Qt.CaseInsensitive
        sortRole: sourceModel.count() > 0 ? "eraName" : ""

        filterString: "*" + searchBox.text + "*"
        filterSyntax: SortFilterProxyModel.Wildcard
        filterCaseSensitivity: Qt.CaseInsensitive
    }

    StatisticModel{
        id:sourceModel
    }
}
