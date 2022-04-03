import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import GuiStyle 1.0

import "qrc:/"

TriangleShape {
    id: root
    property alias dragActive: dragArea.drag.active
    property bool isInDropArea: Drag.target !== null
    property var targetInput: null

    signal lineSelected()

    function attachToTarget(target) {
        root.x = parent.mapFromItem(target.parent, target.x, target.y).x
        root.y = parent.mapFromItem(target.parent, target.x, target.y).y
        root.targetInput = target
        root.canMove = false
    }

    function detachFromTarget() {
        guiEngine.blocksModel.detachBlocks(root.parent.blockIdx, root.targetInput.parent.parent.blockIdx)
        root.targetInput.connectedToBlock = false

        root.x           = Qt.binding(() => root.parent.width)
        root.y           = Qt.binding(() => (root.parent.height - root.height) * 0.5)
        root.targetInput = null
        root.canMove     = true
        inner.outputClicked = false
    }

    Drag.active: dragArea.drag.active
    Drag.dragType: Drag.Automatic
    Drag.keys: "connect_blocks"

    onDragActiveChanged: {
        if(dragActive) {
            inner.savePosition()
            Drag.start()
        } else {            
            if(Drag.target !== null && Drag.target.parent.parent.parent !== root.parent) { // block connection to yourself
                Drag.drop()
            } else {
                Drag.cancel()
                inner.restorePosition()
            }
        }
    }

    QtObject {
        id: inner
        property real lastX: 0.
        property real lastY: 0.
        property bool outputClicked: false

        function restorePosition() {
            root.x = lastX
            root.y = lastY
        }

        function savePosition() {
            lastX = root.x
            lastY = root.y
        }

        function changeX() {
            if(root.targetInput !== null) {
                root.x = root.parent.mapFromItem(root.targetInput.parent, root.targetInput.x, root.targetInput.y).x
            }
        }

        function changeY() {
            if(root.targetInput !== null) {
                root.y = root.parent.mapFromItem(root.targetInput.parent, root.targetInput.x, root.targetInput.y).y
            }
        }
    }

    Connections {
        target: root.targetInput !== null ? root.targetInput.parent.parent : null
        enabled: root.targetInput !== null

        function onXChanged() {
            inner.changeX()
        }

        function onYChanged() {
            inner.changeY()
        }
    }

    Connections {
        target: root.parent
        enabled: root.targetInput !== null

        function onXChanged() {
            inner.changeX()
        }

        function onYChanged() {
            inner.changeY()
        }
    }

    MouseArea {
        id: dragArea
        anchors.fill: parent
        drag.axis: Drag.XAndYAxis
        drag.target: root.canMove ? parent : null

        onClicked: {
            if(root.targetInput !== null) {
                root.lineSelected()
//                inner.outputClicked = !inner.outputClicked
            }
        }
    }

    states: [
        State {
            name: "drag_active"
            when: dragArea.drag.active

            PropertyChanges {
                target: root
                fillColor: GuiStyle.color7
            }
        },
        State {
            name: "arrow_clicked"
            when: inner.outputClicked

            PropertyChanges {
                target: root
                fillColor: GuiStyle.color7
            }
        }

    ]
}
