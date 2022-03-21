import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import GuiStyle 1.0

import "qrc:/"
import "qrc:/gui/components/blocks/IOShape"
import "qrc:/gui/components/text"

Rectangle {
    id: root
    radius: 20
    border.width: 2

    property alias value: valueLbl.text
    property alias readOnly: valueLbl.readOnly
    property alias inputCount: blocksIn.inputCount
    property alias hasOutput: blockOut.visible
    property int minimumXDrag: 0
    property int maximumXDrag: 0
    property int minimumYDrag: 0
    property int maximumYDrag: 0

    signal clicked()

    //TODO: add line by drag from BlockOut and drop in BlockIn
    BlocksIn {
        id: blocksIn
        width: 10
        height: parent.height
        anchors.left: parent.left
    }

    AppTextField {
        id: valueLbl
        anchors.fill: parent
        padding: 2
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        bgColor: "transparent"
        inputMethodHints: Qt.ImhDigitsOnly
    }

    BlockOut {
        id: blockOut
        x: root.width
        y: (root.height - height) * 0.5
        width: 10
        height: width
        canMove: true
    }

    //TODO: during adding new ScopeBlock, add ConnectionLine to a vector
    ConnectionLine {
        id: line
        lineWidth: 2
        lineColor: blockOut.isInDropArea ? GuiStyle.color7 : "black"
        startX: root.width
        startY: root.height * 0.5
        endX: blockOut.x
        endY: blockOut.y + blockOut.height * 0.5
    }

    MouseArea {
        anchors.fill: parent
        drag.axis: Drag.XAndYAxis
        drag.target: parent
        drag.minimumX: root.minimumXDrag
        drag.maximumX: root.maximumXDrag
        drag.minimumY: root.minimumYDrag
        drag.maximumY: root.maximumYDrag

        onClicked: {
            forceActiveFocus()
            root.clicked()
        }

        onDoubleClicked: {
            valueLbl.focus = true
        }
    }
}
