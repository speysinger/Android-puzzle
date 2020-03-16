import QtQuick 2.7
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4

ProgressBar {
    id:root
    value:0.5
    style: ProgressBarStyle {
        background: Rectangle {
            radius: 2
            color: "lightgray"
            border.color: "gray"
            border.width: 1
            implicitWidth: root.width
            implicitHeight: root.height
        }
        progress: Rectangle {
            color: "lightsteelblue"
            border.color: "steelblue"
        }
    }
}
