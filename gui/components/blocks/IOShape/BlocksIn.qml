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
            x: root.x - 2
            y: root.y + root.height * index / (blocks.count - 1) - height * index
            width: root.width
            height: width
            fillColor: "transparent"

            DropArea {
                anchors.fill: parent
                enabled: true

                Rectangle {
                    anchors.fill: parent
                    color: GuiStyle.color7
                    visible: parent.containsDrag
                }

                onDropped: {
                    console.log(drop.source)
                }
            }
        }
    }
}
