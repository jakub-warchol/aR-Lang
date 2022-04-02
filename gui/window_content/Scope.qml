import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Shapes 1.15
import GuiStyle 1.0

import "qrc:/gui/components/blocks"

Rectangle {
    id: root

    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: true

        onClicked: {
            forceActiveFocus()
            guiEngine.deselectAll()
        }
    }

    Repeater {
        id: blocksRepeater
        anchors.fill: parent
        model: guiEngine.blocksModel
        delegate: ScopeBlock {
            id: scopeDelegate
            property bool initialized: false
            x: root.width * model.x
            y: root.height * model.y
            width: 100
            height: 50
            color: "white"
            border.color: "black"
            minimumXDrag: 0
            maximumXDrag: root.width - width
            minimumYDrag: 0
            maximumYDrag: root.height - height
            blockIdx: index
            value: model.value
            readOnly: !model.canModified
            inputCount: model.isDestination ? model.inputCount : 0
            hasOutput: model.isSource
            selected: model.selected

            Component.onCompleted: {
                scopeDelegate.x = root.width * model.x
                scopeDelegate.y = root.height * model.y
                scopeDelegate.initialized = true

                scopeDelegate.addLineToModel()
            }

            Component.onDestruction: {
                scopeDelegate.removeLineFromModel()
            }

            onXChanged: {
                if(scopeDelegate.initialized) {
                    model.x = Number(x / (root.width * 1.)).toFixed(2)
                }
            }

            onYChanged: {
                if(scopeDelegate.initialized) {
                    model.y = Number(y / (root.height * 1.)).toFixed(2)
                }
            }

            onValueChanged: {
                if(scopeDelegate.initialized) {
                    model.value = value
                }
            }

            onSelectedToggled: {
                model.selected = !model.selected

            }

            Connections {
                target: root
                enabled: scopeDelegate.initialized

                function onWidthChanged() {
                    scopeDelegate.x = root.width * model.x
                }

                function onHeightChanged() {
                    scopeDelegate.y = root.height * model.y
                }
            }
        }
    }

    DropArea {
        id: addBlockDropArea
        anchors.fill: parent
        enabled: true
        keys: "add_block"

        onDropped: {
            if(drop.action === Qt.CopyAction) {
                const formats = drop.formats
                if(formats !== []) {
                    const type  = drop.getDataAsString(formats[1])
                    const point = mapToItem(root, drop.x, drop.y)
                    guiEngine.blocksModel.addBlock(type, point.x / root.width, point.y / root.height)
                }
            }
        }
    }

    Connections {
        target: blocksRepeater.model
        function onBlocksFromFileAttached(source, target, targetInput) {
            const sourceBlock = blocksRepeater.itemAt(source)
            const targetBlock = blocksRepeater.itemAt(target)
            if(sourceBlock !== null && targetBlock !== null) {
                const input  = targetBlock.inputBlocks.blocksRepeater.itemAt(targetInput)
                const output = sourceBlock.outputBlock
                if(input !== null && output !== null) {
                    input.attachToBlockOut(output, targetInput)
                }
            }
        }
    }

    states: State {
        name: "block_adding"
        when: addBlockDropArea.containsDrag

        PropertyChanges {
            target: root
            color: Qt.darker(GuiStyle.color3, 1.25)
        }
    }
}
