import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Shapes 1.15
import GuiStyle 1.0

import "qrc:/gui/components/blocks"

Rectangle {
    id: root

    Repeater {
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
            value: model.value
            readOnly: !model.canModified

            Component.onCompleted: {
                scopeDelegate.x = root.width * model.x
                scopeDelegate.y = root.height * model.y
                scopeDelegate.initialized = true
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
}
