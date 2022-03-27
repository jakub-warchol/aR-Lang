import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import GuiStyle 1.0
import AddBlocks 1.0

import "qrc:/gui/components/blocks"

Window {
    id: root
    title: qsTr("Add Block")

    Component.onCompleted: {
        minimumHeight = height
        maximumHeight = height

        minimumWidth  = width
        maximumWidth  = width
    }

    GridView {
        id: blocksGv
        readonly property int spacing: 40
        height: parent.height - spacing * 2
        width: cellWidth * 2
        anchors.centerIn: parent
        cellWidth: 100 + spacing
        cellHeight: 50 + spacing
        boundsBehavior: GridView.StopAtBounds
        interactive: false
        model: AddBlocksModel{}
        delegate: Item {
            width: 100
            height: 50

            ScopeBlock {
                id: blockDelegate
                anchors.fill: parent
                color: "white"
                border.color: "black"
                blockIdx: index
                value: model.value
                readOnly: true
                inputCount: model.isDestination ? model.inputCount : 0
                hasOutput: model.isSource
                moveable: false

                Drag.active: mouseArea.drag.active
                Drag.dragType: Drag.Automatic
                Drag.supportedActions: Qt.CopyAction
                Drag.mimeData: {
                    "add_block": true,          // to enable drag and drop by THIS key
                    "block_type": model.type
                }
                Drag.hotSpot.x: -10
                Drag.hotSpot.y: -10

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    drag.target: parent
                    drag.axis: Drag.XAndYAxis

                    onPressed: {
                        blockDelegate.grabToImage((obj) => parent.Drag.imageSource = obj.url)
                    }
                }
            }
        }
    }
}
