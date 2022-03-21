import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import GuiStyle 1.0

import "qrc:/"

Item {
    id: root
    property alias inputCount: blocks.model

    Repeater {
        id: blocks
        delegate: TriangleShape {
            property bool connectedToBlock: false
            x: root.x - width * 0.5
            y: blocks.count === 1 ? (root.height - height) * 0.5 :root.y + root.height * index / (blocks.count - 1) - height * index
            width: root.width
            height: width
            fillColor: "transparent"

            DropArea {
                anchors.fill: parent
                enabled: !parent.connectedToBlock
                keys: "connect_blocks"

                Rectangle {
                    anchors.fill: parent
                    color: GuiStyle.color7
                    visible: parent.containsDrag
                }

                onDropped: {
                    const blockOut = drag.source as BlockOut
                    if(blockOut.parent === parent.parent.parent) { // block connection to yourself
                        console.error("connect to yourself")
                        drop.accepted = false
                        return
                    }

                    blockOut.attachToTarget(parent)
                    parent.connectedToBlock = true
                }
            }
        }
    }
}
