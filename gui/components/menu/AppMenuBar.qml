import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Dialogs 1.3
import GuiStyle 1.0

import "qrc:/"

MenuBar {
    id: root

    AppMenu {
        title: qsTr("File")

        FileDialog {
            id: selectFile
            visible: false
            nameFilters: ["*.arfile"]
            folder: shortcuts.home
            sidebarVisible: true

            function loadFile() {
                selectExisting = true
                title = qsTr("Load file...")
                visible = true
            }

            function saveFile() {
                selectExisting = false
                title = qsTr("Save file...")
                visible = true
            }

            onAccepted: {
                const filePath = String(fileUrl).replace("file://", "")
                if(selectExisting) {
                    guiEngine.loadFromFile(filePath)
                } else {
                    guiEngine.saveToFile(filePath)
                }
            }
        }

        Action {
            text: qsTr("Open file...")
            onTriggered: {
                selectFile.loadFile()
            }
        }

        Action {
            text: qsTr("Save file...")
            onTriggered: {
                selectFile.saveFile()
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
            onTriggered: {
                aboutApp.open()
            }
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
