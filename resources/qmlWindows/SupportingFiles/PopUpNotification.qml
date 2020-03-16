import QtQuick 2.0
import QtQuick.Controls 2.1

ToolTip {
    id: toast
    delay: 200
    timeout: 3000
    x: (parent.width - width) / 2
    y: parent.height*0.8

    Text {
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
    background: Rectangle {
        color: "gray"
        radius: parent.width*0.03
    }
}

