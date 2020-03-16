import QtQuick 2.0
import QtQuick.Controls 2.1

ToolTip {
    id: toast
    delay: 200
    timeout: 3000
    x: (parent.width - width) / 2
    y: (parent.height - 100)

    background: Rectangle {
        color: "gray"
        radius: 15
    }
}

