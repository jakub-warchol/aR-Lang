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
    property alias moveable: mouseArea.enabled
    property alias value: valueLbl.text
    property alias readOnly: valueLbl.readOnly
    property alias inputCount: blocksIn.inputCount
    property alias hasOutput: blockOut.visible
    property alias inputBlocks: blocksIn
    property alias outputBlock: blockOut
    property bool selected: false
    property int blockIdx: -1
    property int minimumXDrag: 0
    property int maximumXDrag: 0
    property int minimumYDrag: 0
    property int maximumYDrag: 0

    signal selectedToggled

    function addLineToModel() {
        guiEngine.connectionLinesModel.addLine(line)
    }

    function removeLineFromModel() {
        guiEngine.connectionLinesModel.removeLine(line)
    }

    BlocksIn {
        id: blocksIn
        width: 10
        height: parent.height
        anchors.left: parent.left

        onBlockAttached: {
            guiEngine.blocksModel.attachBlocks(blockIdx, root.blockIdx, inputIdx)
        }
    }

    AppTextField {
        id: valueLbl
        anchors.fill: parent
        padding: 2
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        bgColor: "transparent"
        inputMethodHints: Qt.ImhDigitsOnly
        validator: RegExpValidator{
            regExp: /^[-+]?[0-9]*\.?[0-9]+$/
        }
    }

    BlockOut {
        id: blockOut
        x: root.width
        y: (root.height - height) * 0.5
        width: 10
        height: width
        canMove: true

        onLineSelected: {
            line.selected = !line.selected
            guiEngine.connectionLinesModel.toggleLineSelectionStatus(line)
        }
    }

    ConnectionLine {
        id: line
        lineWidth: 2
        lineColor: blockOut.isInDropArea ? GuiStyle.color7 : "black"
        selectedLineColor: GuiStyle.color7
        startX: root.width
        startY: root.height * 0.5
        endX: blockOut.x
        endY: blockOut.y + blockOut.height * 0.5

        onLineRemoved: {
            line.selected = !line.selected
            blockOut.detachFromTarget()
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.axis: Drag.XAndYAxis
        drag.target: parent
        drag.minimumX: root.minimumXDrag
        drag.maximumX: root.maximumXDrag
        drag.minimumY: root.minimumYDrag
        drag.maximumY: root.maximumYDrag

        onClicked: {
            forceActiveFocus()
            root.selectedToggled()
        }

        onDoubleClicked: {
            valueLbl.focus = true
        }
    }

    states: State {
        name: "selected"
        when: root.selected

        PropertyChanges {
            target: root
            border.color: GuiStyle.color7
        }

        PropertyChanges {
            target: valueLbl
            color: GuiStyle.color7
        }
    }
}
