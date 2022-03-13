import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import GuiStyle 1.0

import "qrc:/"

ToolBar {
    id: control

    Row {
        anchors.fill: parent
        anchors.leftMargin: 20
        spacing: 20

        AppToolButton {
            icon.source: "qrc:/resources/icons/duplicate.png"
            onClicked: {
            }
        }

        AppToolButton {
            icon.source: "qrc:/resources/icons/bin.png"
            onClicked: {
            }
        }

        AppToolButton {
            icon.source: "qrc:/resources/icons/add.png"
            onClicked: {
            }
        }

        ToolSeparator{
            height: parent.height
            contentItem: Rectangle {
                implicitWidth: 1
                implicitHeight: 24
                color: "black"
            }
        }

        AppToolButton {
            icon.source: "qrc:/resources/icons/play.png"
            onClicked: {
            }
        }
    }

    background: Rectangle {
        implicitHeight: 40
        color: GuiStyle.color2

        Rectangle {
            width: parent.width
            height: 1
            anchors.bottom: parent.bottom
            color: "transparent"
            border.color: "black"
        }
    }
}
