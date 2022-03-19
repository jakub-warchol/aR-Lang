import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import GuiStyle 1.0

import "qrc:/"

TriangleShape {
    id: root
    property alias dragActive: dragArea.drag.active

    Drag.active: dragArea.drag.active
    Drag.dragType: Drag.Automatic

    onDragActiveChanged: {
        if(dragActive) {
            inner.savePosition()
            Drag.start()
        } else {
            if(Drag.target !== null) {
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

        function restorePosition() {
            root.x = lastX
            root.y = lastY
        }

        function savePosition() {
            lastX = root.x
            lastY = root.y
        }
    }

    MouseArea {
        id: dragArea
        anchors.fill: parent
        drag.axis: Drag.XAndYAxis
        drag.target: root.canMove ? parent : null
    }

    states: State {
        name: "detach_parent"
        when: dragArea.drag.active

        PropertyChanges {
            target: root
            fillColor: GuiStyle.color7
        }
    }
}
