import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import GuiStyle 1.0

import "qrc:/"

ToolBar {
    id: control

    ListView {
        id: selectedBlocksLv
        model: guiEngine.selectedBlocksModel
        delegate: Item{}
    }

    Row {
        anchors.fill: parent
        anchors.leftMargin: 20
        spacing: 20

        AppToolButton {
            icon.source: "qrc:/resources/icons/duplicate.png"
            enabled: selectedBlocksLv.count > 0
            onClicked: {
                guiEngine.blocksModel.duplicateSelectedBlocks()
            }
        }

        AppToolButton {
            icon.source: "qrc:/resources/icons/bin.png"
            enabled: selectedBlocksLv.count > 0 || guiEngine.connectionLinesModel.selectedLinesCount > 0
            onClicked: {
                guiEngine.connectionLinesModel.removeSelectedLines()
                guiEngine.blocksModel.removeSelectedBlocks()

                //TODO: check why all lines have been gone
            }
        }

        AppToolButton {
            icon.source: "qrc:/resources/icons/add.png"
            onClicked: {
                mainWindow.openAddBlocksWindow()
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
                guiEngine.startCalculation()
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
