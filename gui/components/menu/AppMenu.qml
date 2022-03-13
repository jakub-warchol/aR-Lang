import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import GuiStyle 1.0

Menu {
    id: root

    delegate: MenuItem {
        id: menuItem
        implicitWidth: 200
        implicitHeight: 20

        contentItem: Text {
            leftPadding: menuItem.indicator.width
            rightPadding: menuItem.arrow.width
            text: menuItem.text
            font: menuItem.font
            opacity: enabled ? 1.0 : 0.3
            color: "black"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 20
            opacity: enabled ? 1 : 0.3
            color: menuItem.highlighted ? Qt.darker(GuiStyle.color1, 1.25) : "transparent"
        }
    }

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 20
        color: GuiStyle.color1
        radius: 2
    }
}
