import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import GuiStyle 1.0

import "qrc:/"

MenuBar {
    id: root

    AppMenu {
        title: qsTr("File")

        Action {
            text: qsTr("Open file...")
            onTriggered: {

            }
        }

        Action {
            text: qsTr("Save file...")
            onTriggered: {

            }
        }

        MenuSeparator{}

        Action {
            text: qsTr("Quit")
            onTriggered: {
                Qt.quit()
            }
        }
    }

    AppMenu {
        title: qsTr("About...")

        Action {
            text: qsTr("Application")
        }

        Action {
            text: qsTr("Qt")
            onTriggered: {
                guiEngine.aboutQt()
            }
        }
    }

    delegate: MenuBarItem {
        id: menuBarItem

        contentItem: Text {
            text: menuBarItem.text
            font: menuBarItem.font
            opacity: enabled ? 1.0 : 0.3
            color: "black"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            implicitWidth: 40
            implicitHeight: 20
            opacity: enabled ? 1 : 0.3
            color: menuBarItem.highlighted ? Qt.darker(GuiStyle.color1, 1.25) : "transparent"
        }
    }

    background: Rectangle {
        implicitWidth: 40
        implicitHeight: 20
        color: GuiStyle.color1

        Rectangle {
            color: "black"
            width: parent.width
            height: 1
            anchors.bottom: parent.bottom
        }
    }
}
